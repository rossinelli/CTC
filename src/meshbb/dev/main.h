namespace dev {

template <typename T> static __device__ T min3(T a, T b, T c) {return min(a, min(b, c));}
template <typename T> static __device__ T max3(T a, T b, T c) {return max(a, max(b, c));}

template <typename T3>
static __device__ T3 min3T3(T3 a, T3 b, T3 c) {
    T3 v;
    v.x = min3(a.x, b.x, c.x);
    v.y = min3(a.y, b.y, c.y);
    v.z = min3(a.z, b.z, c.z);
    return v;
}

template <typename T3>
static __device__ T3 max3T3(T3 a, T3 b, T3 c) {
    T3 v;
    v.x = max3(a.x, b.x, c.x);
    v.y = max3(a.y, b.y, c.y);
    v.z = max3(a.z, b.z, c.z);
    return v;
}

static __device__ int3 get_cidx(int3 L, real3_t r) {
    int3 c;
    c.x = floor((double) r.x + L.x/2);
    c.y = floor((double) r.y + L.y/2);
    c.z = floor((double) r.z + L.z/2);

    c.x = min(L.x-1, max(0, c.x));
    c.y = min(L.y-1, max(0, c.y));
    c.z = min(L.z-1, max(0, c.z));
    return c;
}

static __device__ void get_cells(int3 L, float tol, real3_t A, real3_t B, real3_t C, /**/ int3 *lo, int3 *hi) {
    real3_t lf, hf;
    lf = min3T3(A, B, C);
    hf = max3T3(A, B, C);

    lf.x -= tol; lf.y -= tol; lf.z -= tol;
    hf.x += tol; hf.y += tol; hf.z += tol;
    
    *lo = get_cidx(L, lf);
    *hi = get_cidx(L, hf);
}

static __device__ void find_collisions_cell(int tid, int start, int count, const Particle *pp, const Force *ff,
                                            const rPa *A, const rPa *B, const rPa *C,
                                            /**/ int *ncol, float4 *datacol, int *idcol) {
    int i, entry;
    rPa p, p0; Force f;
    BBState state;
    real_t tc, u, v;
    
    for (i = start; i < start + count; ++i) {
        p = P2rP(pp + i);
        f = ff[i];
        rvprev(&p.r, &p.v, f.f, /**/ &p0.r, &p0.v);

        state = intersect_triangle(&A->r, &B->r, &C->r, &A->v, &B->v, &C->v, &p0, /**/ &tc, &u, &v);
        
        if (state == BB_SUCCESS) {
            entry = atomicAdd(ncol + i, 1);

            if (entry >= MAX_COL) {
                state = BB_MAXCOL;
                break;
            }

            entry += i * MAX_COL;
            datacol[entry] = make_float4(tc, u, v, 0);
            idcol[entry] = tid;
        }
        dbg::log_states(state);
    }
}

static __device__ void revert_r(float h, rPa *p) {
    enum {X, Y, Z};
    p->r.x -= p->v.x * h;
    p->r.y -= p->v.y * h;
    p->r.z -= p->v.z * h;
}

static __device__ void fetch_triangle(int id, int nt, int nv, const int4 *tt, const Particle *i_pp,
                                      /**/ rPa *A, rPa *B, rPa *C) {
    int4 t;
    int tid, mid;
    tid = id % nt;
    mid = id / nt;

    t = tt[tid];
    t.x += mid * nv;
    t.y += mid * nv;
    t.z += mid * nv;
    
    *A = P2rP( i_pp + t.x );
    *B = P2rP( i_pp + t.y );
    *C = P2rP( i_pp + t.z );
}

__global__ void find_collisions(int nm, int nt, int nv, const int4 *tt, const Particle *i_pp,
                                int3 L, const int *starts, const int *counts, const Particle *pp, const Force *ff,
                                /**/ int *ncol, float4 *datacol, int *idcol) {
    
    int gid, ix, iy, iz, cid;
    rPa A, B, C;
    int3 str, end;
    gid = threadIdx.x + blockIdx.x * blockDim.x;

    if (gid >= nm * nt) return;

    fetch_triangle(gid, nt, nv, tt, i_pp, /**/ &A, &B, &C);

    revert_r(dt, &A);
    revert_r(dt, &B);
    revert_r(dt, &C);

    get_cells(L, 5e-1f, A.r, B.r, C.r, /**/ &str, &end);
    
    for (iz = str.z; iz <= end.z; ++iz) {
        for (iy = str.y; iy <= end.y; ++iy) {
            for (ix = str.x; ix <= end.x; ++ix) {
                cid = ix + L.x * (iy + L.y * iz);
                
                find_collisions_cell(gid, starts[cid], counts[cid], pp, ff, &A, &B, &C, /**/ ncol, datacol, idcol);
            }
        }
    }
}

__global__ void select_collisions(int n, /**/ int *ncol, float4 *datacol, int *idcol) {
    int i, c, j, dst, src, argmin;
    float tmin;
    float4 d;
    i = threadIdx.x + blockIdx.x * blockDim.x;

    if (i >= n) return;

    c = ncol[i];

    argmin = 0; tmin = 2*dt;
    for (j = 0; j < c; ++j) {
        src = MAX_COL * i + j;
        d = datacol[src];
        if (d.x < tmin) {
            argmin = j;
            tmin = d.x;
        }
    }

    if (c) {
        src = MAX_COL * i + argmin;
        dst = MAX_COL * i;
        idcol[dst]   = idcol[src];
        datacol[dst] = datacol[src];
        ncol[i] = 1; /* we can use find_collisions again */
    }
}

static __device__ void get_collision_point(const float4 dcol, rPa A, rPa B, rPa C,
                                           /**/ real3_t *rw, real3_t *vw) {
    enum {X, Y, Z};
    float h, u, v, w;    

    /* d.x is collision time */
    h = dt - dcol.x;
    revert_r(h, &A);
    revert_r(h, &B);
    revert_r(h, &C);

    u = dcol.y;
    v = dcol.z;
    w = 1 - u - v;

    rw->x = w * A.r.x + u * B.r.x + v * C.r.x;
    rw->y = w * A.r.y + u * B.r.y + v * C.r.y;
    rw->z = w * A.r.z + u * B.r.z + v * C.r.z;

    vw->x = w * A.v.x + u * B.v.x + v * C.v.x;
    vw->y = w * A.v.y + u * B.v.y + v * C.v.y;
    vw->z = w * A.v.z + u * B.v.z + v * C.v.z;    
}

// static __device__ int get_side(const float r[3], const float A[3], const float B[3], const float C[3]) {
//     float n[3], a[3], b[3];
// }

__global__ void perform_collisions(int n, const int *ncol, const float4 *datacol, const int *idcol,
                                   const Force *ff, int nt, int nv, const int4 *tt, const Particle *i_pp,
                                   /**/ Particle *pp, Momentum *mm) {
    int i, id, entry;
    float4 d;
    rPa p1, p0, pn, A, B, C;
    Force f;
    real3_t rw, vw;
    Momentum m;
    i = threadIdx.x + blockIdx.x * blockDim.x;

    if (i >= n || ncol[i] == 0) return;

    entry = i * MAX_COL;
    id = idcol[entry];
    d  = datacol[entry];

    p1 = P2rP( pp + i );
    f  = ff[i];
    
    rvprev(&p1.r, &p1.v, f.f, /**/ &p0.r, &p0.v);

    fetch_triangle(id, nt, nv, tt, i_pp, /**/ &A, &B, &C);
    
    get_collision_point(d, A, B, C, /**/ &rw, &vw);

    bounce_back(&p0, &rw, &vw, d.x, /**/ &pn);
    
    pp[i] = rP2P(&pn);

    /* add momentum */

    lin_mom_change(    p1.v, pn.v, /**/ m.P);
    ang_mom_change(rw, p1.v, pn.v, /**/ m.L);

    atomicAdd(mm[id].P + X, m.P[X]);
    atomicAdd(mm[id].P + Y, m.P[Y]);
    atomicAdd(mm[id].P + Z, m.P[Z]);

    atomicAdd(mm[id].L + X, m.L[X]);
    atomicAdd(mm[id].L + Y, m.L[Y]);
    atomicAdd(mm[id].L + Z, m.L[Z]);
}

} // dev
