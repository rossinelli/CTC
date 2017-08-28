namespace dbg {
namespace dev {

enum {X, Y, Z};

static __device__ void report(err_type e) {
    if (e != err::NONE) atomicExch(&error, e);
}

static __device__ err_type check_float(float a) {
    if (isnan(a)) return err::NAN_VAL;
    if (isinf(a)) return err::INF_VAL;
    return err::NONE;
}

static __device__ err_type check_float3(const float a[3]) {
    err_type e;
#define check_ret(A) if ((e = check_float(A)) != err::NONE) return e
    check_ret(a[0]);
    check_ret(a[1]);
    check_ret(a[2]);
#undef check_ret
    return err::NONE;
}

static __device__ bool valid_pos(float x, int L, bool verbose) {
    if (x < -L/2 || x > L/2) {
        if (verbose) printf("DBG: x = %g (L = %d)\n", x, L);
        return false;
    }
    return true;
}

static __device__ bool valid_unpacked_pos(float  x, float  y, float  z, bool verbose) {
    bool ok = true;
    ok &= valid_pos(x, XS, verbose);
    ok &= valid_pos(y, YS, verbose);
    ok &= valid_pos(z, ZS, verbose);
    
    return ok;
}

static __device__ err_type valid_pos(const Particle *p, bool verbose) {
    float x, y, z;
    err_type e;
    x  = p->r[X];  y = p->r[Y];  z = p->r[Z];
    e = check_float3(p->r);
    if (e != err::NONE) return e;
    if (valid_unpacked_pos(x, y, z, verbose)) e = err::NONE;
    else                                      e = err::INVALID;
    return e;
}

static __global__ void check_pos(const Particle *pp, int n, bool verbose = true) {
    int i = threadIdx.x + blockIdx.x * blockDim.x;
    if (i >= n) return;
    err_type e = valid_pos(pp + i, verbose);
    report(e);
}

static __device__ bool valid_unpacked_pos_pu(float x, float y, float z, bool verbose) {
    bool ok = true;
    ok &= valid_pos(x, 3*XS, verbose);
    ok &= valid_pos(y, 3*YS, verbose);
    ok &= valid_pos(z, 3*ZS, verbose);

    return ok;
}

static __device__ err_type valid_pos_pu(const Particle *p, bool verbose) {
    float x, y, z;
    err_type e;
    x  = p->r[X];  y = p->r[Y];  z = p->r[Z];
    e = check_float3(p->r);
    if (e != err::NONE) return e;
    if (valid_unpacked_pos_pu(x, y, z, verbose)) e = err::NONE;
    else                                         e = err::INVALID;
    return e;
}

static __global__ void check_pos_pu(const Particle *pp, int n, bool verbose = true) {
    int i = threadIdx.x + blockIdx.x * blockDim.x;
    if (i >= n) return;
    err_type e = valid_pos(pp + i, verbose);
    report(e);
}

static __device__ bool valid_vel(float v, int L, bool verbose) {
    float dx = fabs(v * dt);
    if (dx > L/2) {
        if (verbose) printf("DBG: v = %g (L = %d)\n", v, L);
        return false;
    }
    return true;
}

static __device__ bool valid_vel3(float vx, float vy, float vz, bool verbose) {
    bool ok = true;
    ok &= valid_vel(vx, XS, verbose);
    ok &= valid_vel(vy, YS, verbose);
    ok &= valid_vel(vz, ZS, verbose);

    return ok;
}

static __device__ err_type valid_vv(const Particle *p, bool verbose) {
    err_type e;
    const float *v = p->v;
    e = check_float3(v);
    if (e != err::NONE) return e;
    if ( valid_vel3(v[X], v[Y], v[Z], verbose)) e = err::NONE;
    else                                        e = err::INVALID;
    return e;
}

static __global__ void check_vv(const Particle *pp, int n, bool verbose = true) {
    int i = threadIdx.x + blockIdx.x * blockDim.x;
    if (i >= n) return;
    err_type e = valid_vv(pp + i, verbose);
    report(e);
}

static __device__ bool valid_acc(float a, int L, bool verbose) {
    float dx = fabs(a * dt * dt);
    if (dx > L/2) {
        if (verbose) printf("DBG: a = %g (L = %d)\n", a, L);
        return false;
    }
    return true;
}

static __device__ bool valid_unpacked_f(float fx, float fy, float fz, bool verbose) {
    bool ok = true;
    ok &= valid_acc(fx, XS, verbose);
    ok &= valid_acc(fy, YS, verbose);
    ok &= valid_acc(fz, ZS, verbose);

    return ok;
}

static __device__ err_type valid_f(const Force *f, bool verbose) {
    float fx, fy, fz;
    err_type e;
    fx = f->f[X]; fy = f->f[Y]; fz = f->f[Z];
    e = check_float3(f->f);
    if (e != err::NONE) return e;
    if (valid_unpacked_f(fx, fy, fz, verbose)) e = err::NONE;
    else                                       e = err::INVALID;
    return e;
}

static __global__ void check_ff(const Force *ff, int n, bool verbose = true) {
    int i = threadIdx.x + blockIdx.x * blockDim.x;
    if (i >= n) return;
    err_type e = valid_f(ff + i, verbose);
    report(e);
}

} // dev
} // dbg
