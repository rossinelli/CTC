static __device__ void p2rv(const float *p, int i, /**/
                            float  *x, float  *y, float  *z,
                            float *vx, float *vy, float *vz) {
    static_assert(sizeof(Particle) == 6 * sizeof(float),
                  "sizeof(Particle) != 6 * sizeof(float)");
    i *= 6;
     *x = p[i++];  *y = p[i++];  *z = p[i++];
    *vx = p[i++]; *vy = p[i++]; *vz = p[i++];
}

static __device__ void pp2p(const float *pp, int i, /**/ Pa *p) { /* TODO gets force::Pa directly */
    p2rv(pp, i, /**/ &p->x, &p->y, &p->z,   &p->vx, &p->vy, &p->vz);
}

static __device__ int p2map(int3 L, const int *start, int zplane, int n, const Pa p, /**/ Map *m) {
    /* particle to map */
    return r2map(L, start, zplane, n, p.x, p.y, p.z, m);
}

const static float EPS = 1e-6;
static __device__ float dist(Pa a, Pa b) {
    float dx, dy, dz;
    dx = a.x - b.x;
    dy = a.y - b.y;
    dz = a.z - b.z;
    return sqrt(dx*dx + dy*dy + dz*dz);
}

template <typename Par, typename Parray>
static __device__ void bulk0(Par params, const Pa a, Parray parray, int lid, const Map m, float seed, /**/
                             float *fx, float *fy, float *fz, float *ff) {
    /* "[a]ocal" and "[b]emote" particles */
    Pa b;
    Fo f;
    int i, rid;
    *fx = *fy = *fz = 0; /* local force */
    for (i = 0; !endp(m, i); ++i) {
        rid = m2id(m, i);
        parray_get(parray, rid, /**/ &b);
        f = ff2f(ff, rid);
        pair(params, a, b, random(lid, rid, seed), /**/ fx, fy, fz,   f);
    }
}

template <typename Par, typename Parray>
static __device__ void bulk1(Par params, const Pa a, Parray parray,
                             const Fo f, int i, const Map m, float seed, /**/ float *ff) {
    float fx, fy, fz; /* local force */
    bulk0(params, a, parray, i, m, seed, /**/ &fx, &fy, &fz, ff);
    atomicAdd(f.x, fx);
    atomicAdd(f.y, fy);
    atomicAdd(f.z, fz);
}

template <typename Par, typename Parray>
static __device__ void bulk2(Par params, int3 L, const int *start, float *ppA, Parray parray, int i, int zplane, int n, float seed,
                             /**/ float *ff, float *ff0) {
    Pa p;
    Fo f; /* "local" particle */
    Map m;
    pp2p(ppA, i, /**/ &p);
    f = ff2f(ff, i);
    if (!p2map(L, start, zplane, n, p, /**/ &m)) return;
    bulk1(params, p, parray, f, i, m, seed, /**/ ff0);
}

template <typename Par, typename Parray>
__global__ void bulk(Par params, int3 L, const int *start, float *ppA, Parray parray, int n0, int n1, float seed, float *ff, float *ff0) {
    int gid, i, zplane;
    gid    = threadIdx.x + blockDim.x * blockIdx.x;
    i      = gid / 3;
    zplane = gid % 3;
    if (i >= n0) return;
    bulk2(params, L, start, ppA, parray, i, zplane, n1, seed, ff, ff0);
}
