static void random(int n, RbcRnd *rnd, /**/ float **r) {
    if (RBC_RND) rbc_rnd_gen(rnd, n, /**/ r);
    else *r = NULL;
}

static void apply0(RbcParams_v parv, int nc, int nv,
                   const Particle *pp, RbcRnd *rnd,
                   const int *adj0, const int *adj1, const Shape shape,
                   float *av, /**/ Force *ff){
    float *rnd0;    
    int md;
    md = RBCmd;
    random(nc * md * nv, rnd, /**/ &rnd0);
    KL(dev::force, (k_cnf(nc*nv*md)), (parv, md, nv, nc, pp, rnd0,
                                       adj0, adj1, shape, av, /**/ (float*)ff));
}

void rbc_force_apply(const RbcQuants q, const RbcForce t, const RbcParams *par, /**/ Force *ff) {
    RbcParams_v parv;
    float *av;
    if (q.nc <= 0) return;
    parv = rbc_params_get_view(par);
    UC(area_volume_compute(q.area_volume, q.nc, q.pp, /**/ &av));
    apply0(parv, q.nc, q.nv, q.pp, t.rnd,
           q.adj0, q.adj1, q.shape, av, /**/ ff);
}
