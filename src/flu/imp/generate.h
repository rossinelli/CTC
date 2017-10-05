static void zip(const Particle *pp, const int n, /**/ float4 *zip0, ushort4 * zip1) {
    assert(sizeof(Particle) == 6 * sizeof(float)); /* :TODO: implicit dependency */
    KL(dev::zip,
       ((n + 1023) / 1024, 1024, 1024 * 6 * sizeof(float)),
       (zip0, zip1, (float*)pp, n));
}

void get_ticketZ(Quants q, /**/ TicketZ *t) {
    if (q.n == 0) return;
    float4  *zip0 = t->zip0;
    ushort4 *zip1 = t->zip1;
    zip(q.pp, q.n, /**/ zip0, zip1);
}

static int gen0(Particle *pp) { /* generate particle positions and velocities */
    enum {X, Y, Z};
    assert(XS * YS * ZS * numberdensity < MAX_PART_NUM);
    srand48(123456);
    int iz, iy, ix, l, nd = numberdensity;
    int n = 0; /* particle index */
    float x, y, z, dr = 0.99;
    for (iz = 0; iz < ZS; iz++)
    for (iy = 0; iy < YS; iy++)
    for (ix = 0; ix < XS; ix++) {
        /* edge of a cell */
        int xlo = -0.5*XS + ix, ylo = -0.5*YS + iy, zlo = -0.5*ZS + iz;
        for (l = 0; l < nd; l++) {
            Particle p;
            x = xlo + dr * drand48(), y = ylo + dr * drand48(), z = zlo + dr * drand48();
            p.r[X] = x; p.r[Y] = y; p.r[Z] = z;
            p.v[X] = 0; p.v[Y] = 0; p.v[Z] = 0;
            pp[n++] = p;
        }
    }
    MSG("ic::gen: %d solvent particles", n);
    return n;
}

static int genColor(/*o*/ Particle *pp, int *color, /*w*/ Particle *pp_hst, int *color_hst) {
    int n = gen0(pp_hst);
    inter::color_hst(pp_hst, n, /**/ color_hst);
    cH2D(color, color_hst, n);
    cH2D(   pp,    pp_hst, n);
    return n;
}

static int genGrey(/*o*/ Particle *dev, /*w*/ Particle *hst) {
    int n = gen0(hst);
    cH2D(dev, hst, n);
    return n;
}

void gen_quants(Quants *q) {
    if (multi_solvent)
        q->n = genColor(q->pp, q->cc, /*w*/ q->pp_hst, q->cc_hst);
    else
        q->n = genGrey(q->pp, /*w*/ q->pp_hst);
}

static void ii_gen0(const long n, int *ii) {
    long i0 = 0;
    MC(m::Exscan(&n, &i0, 1, MPI_LONG, MPI_SUM, m::cart));
    for (long i = 0; i < n; ++i) ii[i] = i + i0;
}

static void ii_gen(const int n, int *ii_dev, int *ii_hst) {
    ii_gen0(n, ii_hst);
    cH2D(ii_dev, ii_hst, n);
}

void gen_ids(const int n, Quants *q) {
    ii_gen(n, q->ii, q->ii_hst);
}
