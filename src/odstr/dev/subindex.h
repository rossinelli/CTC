namespace odstr { namespace sub { namespace dev {

__device__ void warpco(/**/ int *ws, int *dw) { /* warp [co]ordinates */
    /* ws: start, dw: shift (lane) */
    int warp;
    warp = threadIdx.x / warpSize;
    *dw   = threadIdx.x % warpSize;
    *ws   = warpSize * warp + blockDim.x * blockIdx.x;
}

struct Pa { /* local particle */
    float2 d0, d1, d2;
};

struct Lo { /* particle [lo]cation in memory
               d: shift in wrap, used for collective access  */
    float2 *p;
    int d;
};

__device__ void pp2Lo(float2 *pp, int n, int ws, /**/ Lo *l) {
    int dwe; /* warp or buffer end relative wrap start */
    dwe  = min(warpSize, n - ws);
    l->p = pp + 3*ws;
    l->d = dwe;
}

__device__ int endLo(Lo *l, int d) { /* is `d' behind the end? */
    return d >= l->d;
}

__device__ void readPa(Lo l, /**/ Pa *p) {
    k_read::AOS6f(l.p, l.d, /**/ p->d0, p->d1, p->d2);
}

__device__ void writePa(Pa *p, /**/ Lo l) {
    k_write::AOS6f(/**/ l.p, l.d, /*i*/ p->d0, p->d1, p->d2);
}

__device__ void shiftPa(float r[3], Pa *p) {
    enum {X, Y, Z};
    p->d0.x += r[X];   p->d0.y += r[Y];   p->d1.x += r[Z];
}

__device__ void Pa2r(Pa *p, /**/ float r[3]) { /* to position */
    enum {X, Y, Z};
    r[X] = p->d0.x;   r[Y] = p->d0.y;   r[Z] = p->d1.x;
}

__device__ void Pa2v(Pa *p, /**/ float v[3]) { /* to velocity */
    enum {X, Y, Z};
    v[X] = p->d1.y;   v[Y] = p->d2.x;   v[Z] = p->d2.y;
}

__device__ void subindex0(int ws, int dw, const int strt[], /*io*/ Pa *p, int *counts, /**/ uchar4 *subids) {
    enum {X, Y, Z};
    int fid;     /* fragment id */
    int xi, yi, zi, cid, subindex;
    float shift[3], r[3], v[3];

    fid  = k_common::fid(strt, ws + dw);
    fid2shift(fid, /**/ shift);
    shiftPa(shift, p);

    Pa2r(p, /**/ r);
    xi = x2c(r[X], XS);
    yi = x2c(r[Y], YS);
    zi = x2c(r[Z], ZS);

    Pa2v(p, /**/ v);
    check_vel(v[X], XS);
    check_vel(v[Y], YS);
    check_vel(v[Z], ZS);

    cid = xi + XS * (yi + YS * zi);
    subindex = atomicAdd(counts + cid, 1);
    subids[ws + dw] = make_uchar4(xi, yi, zi, subindex);
}

__global__ void subindex(const int n, const int strt[], /*io*/ float2 *pp, int *counts, /**/ uchar4 *subids) {
    enum {X, Y, Z};
    int ws, dw;  /* warp start and shift (lane) */

    Lo l; /* location in memory */
    Pa p;

    warpco(&ws, &dw); /* warp coordinates */
    if (ws >= n) return;
    pp2Lo(pp, n, ws, /**/ &l);
    readPa(l, /**/ &p);   /* collective */

    if (!endLo(&l, dw))
        subindex0(ws, dw, strt, /*io*/ &p, counts, /**/ subids);
    writePa(&p, /**/ l); /* collective */
}

}}} /* namespace */
