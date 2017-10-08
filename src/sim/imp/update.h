void clear_vel() {
    scheme::clear_vel(o::q.pp, o::q.n);
    if (solids) scheme::clear_vel(s::q.pp, s::q.n);
    if (rbcs  ) scheme::clear_vel(r::q.pp, r::q.n);
}

void update_solid() {
    if (!s::q.n) return;

    rig::update(s::ff, s::q.rr0, s::q.n, s::q.ns, /**/ s::q.pp, s::q.ss);
    rig::update_mesh(s::q.ss, s::q.ns, s::q.nv, s::q.dvv, /**/ s::q.i_pp);
    // for dump
    cD2H(s::q.ss_dmp, s::q.ss, s::q.ns);
    rig::reinit_ft(s::q.ns, /**/ s::q.ss);
}

void bounce_solid(long it) {
    int n, nm, nt, nv, *ss, *cc, nmhalo, counts[comm::NFRAGS];
    int4 *tt;
    Particle *pp, *i_pp;
    int3 L = make_int3(XS, YS, ZS);
    
    nm = s::q.ns;
    nt = s::q.nt;
    nv = s::q.nv;
    tt = s::q.dtt;
    i_pp = s::q.i_pp;

    n  = o::q.n;
    pp = o::q.pp;
    cc = o::q.cells.counts;
    ss = o::q.cells.starts;

    /* send meshes to frags */

    exch::mesh::build_map(nm, nv, i_pp, /**/ &s::e.p);
    exch::mesh::pack(nv, i_pp, /**/ &s::e.p);
    exch::mesh::download(&s::e.p);

    exch::mesh::post_send(&s::e.p, &s::e.c);
    exch::mesh::post_recv(&s::e.c, &s::e.u);

    exch::mesh::wait_send(&s::e.c);
    exch::mesh::wait_recv(&s::e.c, &s::e.u);

    /* unpack at the end of current mesh buffer */
    exch::mesh::unpack(nv, &s::e.u, /**/ &nmhalo, i_pp + nm * nv);
    
    /* perform bounce back */
    
    meshbb::reini(n, /**/ bb::bbd);
    CC(d::MemsetAsync(bb::mm, 0, nt * (nm + nmhalo) * sizeof(Momentum)));

    meshbb::find_collisions(nm + nmhalo, nt, nv, tt, i_pp, L, ss, cc, pp, o::ff, /**/ bb::bbd);
    meshbb::select_collisions(n, /**/ bb::bbd);
    meshbb::bounce(n, bb::bbd, o::ff, nt, nv, tt, i_pp, /**/ pp, bb::mm);

    /* send momentum back */

    exch::mesh::get_num_frag_mesh(&s::e.u, /**/ counts);
    
    exch::mesh::packM(nt, counts, bb::mm + nm * nt, /**/ &s::e.pm);
    exch::mesh::downloadM(counts, /**/ &s::e.pm);

    exch::mesh::post_recv(&s::e.cm, &s::e.um);
    exch::mesh::post_send(&s::e.pm, &s::e.cm);
    exch::mesh::wait_recv(&s::e.cm, &s::e.um);
    exch::mesh::wait_send(&s::e.cm);

    exch::mesh::upload(&s::e.um);
    exch::mesh::unpack_mom(nt, &s::e.p, &s::e.um, /**/ bb::mm);
    
    /* gather bb momentum */
    meshbb::collect_rig_momentum(nm, nt, nv, tt, i_pp, bb::mm, /**/ s::q.ss);

    /* for dump */
    cD2H(s::q.ss_dmp_bb, s::q.ss, nm);
}


void update_solvent(long it) {
    scheme::move(dpd_mass, o::q.pp, o::ff, o::q.n);
}

void update_rbc(long it) {
    bool cond;
    cond = multi_solvent && color_freq && it % color_freq == 0;
    if (cond) {MSG("recolor"); gen_colors();};
    scheme::move(rbc_mass, r::q.pp, r::ff, r::q.n);
}

void restrain() {
    scheme::restrain(o::q.cc, o::q.n, it, /**/ o::q.pp);
}

void bounce_wall() {
    sdf::bounce(&w::qsdf, o::q.n, /**/ o::q.pp);
    // if (rbcs) sdf::bounce(&w::qsdf, r::q.n, /**/ r::q.pp);
}

void bounce_rbc() {
    // TODO
}
