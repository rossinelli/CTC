static void gen_flu(Sim *s) {
    Flu *flu = &s->flu;
    UC(flu_gen_quants(s->coords, s->opt.params.numdensity, s->gen_color, &flu->q));
    UC(flu_build_cells(&flu->q));
    if (s->opt.fluids) flu_gen_ids(s->cart, flu->q.n, &flu->q);
}

static void gen_rbc(Sim *s) {
    MeshRead *cell = s->rbc.cell;
    Rbc *rbc = &s->rbc;
    const Opt *opt = &s->opt;
    if (opt->rbc.active) {
        rbc_gen_mesh(s->coords, s->cart, cell, "rbcs-ic.txt", /**/ &rbc->q);
    }
}

static void gen_wall(Sim *s) {
    Flu *flu = &s->flu;
    Wall *w = s->wall;
    bool dump_sdf = s->opt.dump_field;
    
    if (!s->opt.wall) return;

    UC(wall_gen(s->cart, s->coords, s->opt.params, dump_sdf,
                &flu->q.n, flu->q.pp, w));
}

static void freeze(Sim *s) { /* generate */
    Flu *flu = &s->flu;
    const Opt *opt = &s->opt;
    
    InterWalInfos winfo = get_winfo(s);
    InterFluInfos finfo = get_finfo(s);
    InterRbcInfos rinfo = get_rinfo(s);
    InterRigInfos sinfo = get_sinfo(s);

    UC(gen_rbc(s));
    UC(gen_wall(s));
    dSync();    
    UC(inter_freeze(s->coords, s->cart, winfo, /*io*/ finfo, rinfo, sinfo));
    clear_vel(s);

    if (opt->flucolors) {
        Particle *pp = flu->q.pp;
        int n = flu->q.n;
        int *cc = flu->q.cc;
        inter_color_apply_dev(s->coords, s->gen_color, n, pp, /*o*/ cc);
    }
}

void sim_gen(Sim *s) {
    const Opt *opt = &s->opt;
    float tstart = 0;
    s->equilibrating = true;

    UC(gen_flu(s));

    MC(m::Barrier(s->cart));

    run(tstart, s->time.eq, s);

    freeze(/**/ s);
    dSync();

    if (opt->rbc.active && opt->flucolors) UC(colors_from_rbc(s));

    tstart = s->time.eq;
    pre_run(s);
    run(tstart, s->time.end, s);

    /* final strt dump*/
    if (opt->dump_strt) dump_strt_final(s);
}

static void gen_from_restart(Sim *s) {
    Flu *flu = &s->flu;
    Rbc *rbc = &s->rbc;
    Rig *rig = &s->rig;
    MeshRead *cell, *mesh;
    cell = s->rbc.cell;
    mesh = s->rig.mesh;
    const Opt *opt = &s->opt;
    const char *base = opt->strt_base_read;
    bool dump_sdf = opt->dump_field;
    
    flu_strt_quants(s->cart, base, RESTART_BEGIN, &flu->q);
    if (opt->rbc.active) rbc_strt_quants(s->cart, base, cell, RESTART_BEGIN, &rbc->q);
    if (opt->rig.active) rig_strt_quants(s->cart, mesh, base, RESTART_BEGIN, &rig->q);
    if (opt->wall) wall_restart(s->cart, s->coords, opt->params, dump_sdf, base, s->wall);
    if (opt->vcon) vcont_strt_read(base, RESTART_BEGIN, s->vcon.vcont);
}

void sim_strt(Sim *s) {
    const Opt *opt = &s->opt;

    gen_from_restart(s); 

    MC(m::Barrier(s->cart));

    pre_run(s);
    run(s->time.eq, s->time.end, s);
    if (opt->dump_strt) dump_strt_final(s);
}
