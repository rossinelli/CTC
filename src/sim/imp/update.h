void clear_vel() {
    scheme::move::clear_vel(flu.q.n, flu.q.pp);
    if (solids) scheme::move::clear_vel(rig.q.n, rig.q.pp);
    if (rbcs  ) scheme::move::clear_vel(rbc.q.n, rbc.q.pp);
}

void update_solid(Rig *s) {
    if (!s->q.n) return;
    rig::Quants *q = &s->q;
    
    rig::update(q->n, s->ff, q->rr0, q->ns, /**/ q->pp, q->ss);
    rig::update_mesh(q->ns, q->ss, q->nv, q->dvv, /**/ q->i_pp);
    // for dump
    cD2H(q->ss_dmp, q->ss, q->ns);
    rig::reinit_ft(q->ns, /**/ q->ss);
}

void bounce_solid(long it, BounceBack *bb, Rig *s) {
    int n, nm, nt, nv, *ss, *cc, nmhalo, counts[comm::NFRAGS];
    int4 *tt;
    Particle *pp, *i_pp;
    int3 L = make_int3(XS, YS, ZS);

    rig::Quants *qs = &s->q;
    BBexch       *e = &bb->e; 
    
    nm = qs->ns;
    nt = qs->nt;
    nv = qs->nv;
    tt = qs->dtt;
    i_pp = qs->i_pp;

    n  = flu.q.n;
    pp = flu.q.pp;
    cc = flu.q.cells.counts;
    ss = flu.q.cells.starts;

    /* send meshes to frags */

    exch::mesh::build_map(nm, nv, i_pp, /**/ &e->p);
    exch::mesh::pack(nv, i_pp, /**/ &e->p);
    exch::mesh::download(&e->p);

    UC(exch::mesh::post_send(&e->p, &e->c));
    UC(exch::mesh::post_recv(&e->c, &e->u));

    exch::mesh::wait_send(&e->c);
    exch::mesh::wait_recv(&e->c, &e->u);

    /* unpack at the end of current mesh buffer */
    exch::mesh::unpack(nv, &e->u, /**/ &nmhalo, i_pp + nm * nv);
    
    /* perform bounce back */
    
    meshbb::reini(n, /**/ bb->d);
    if (nm + nmhalo)
        CC(d::MemsetAsync(bb->mm, 0, nt * (nm + nmhalo) * sizeof(Momentum)));

    meshbb::find_collisions(nm + nmhalo, nt, nv, tt, i_pp, L, ss, cc, pp, flu.ff, /**/ bb->d);
    meshbb::select_collisions(n, /**/ bb->d);
    meshbb::bounce(n, bb->d, flu.ff, nt, nv, tt, i_pp, /**/ pp, bb->mm);

    /* send momentum back */

    exch::mesh::get_num_frag_mesh(&e->u, /**/ counts);
    
    exch::mesh::packM(nt, counts, bb->mm + nm * nt, /**/ &e->pm);
    exch::mesh::downloadM(counts, /**/ &e->pm);

    UC(exch::mesh::post_recv(&e->cm, &e->um));
    UC(exch::mesh::post_send(&e->pm, &e->cm));
    exch::mesh::wait_recv(&e->cm, &e->um);
    exch::mesh::wait_send(&e->cm);

    exch::mesh::upload(&e->um);
    exch::mesh::unpack_mom(nt, &e->p, &e->um, /**/ bb->mm);
    
    /* gather bb momentum */
    meshbb::collect_rig_momentum(nm, nt, nv, tt, i_pp, bb->mm, /**/ qs->ss);

    /* for dump */
    cD2H(qs->ss_dmp_bb, qs->ss, nm);
}


void update_solvent(long it, /**/ Flu *f) {
    scheme::move::main(dpd_mass, f->q.n, f->ff, f->q.pp);
}

void update_rbc(long it, Rbc *r) {
    bool cond;
    cond = multi_solvent && color_freq && it % color_freq == 0;
    if (cond) {MSG("recolor"); gen_colors(r, &colorer, /**/ &flu);}; /* TODO: does not belong here*/
    scheme::move::main(rbc_mass, r->q.n, r->ff, r->q.pp);
}

void restrain(long it, Flu *f, Rbc *r) {
    scheme::restrain::QQ qq;
    scheme::restrain::NN nn;
    qq.o = f->q.pp;
    qq.r = r->q.pp;

    nn.o = f->q.n;
    nn.r = r->q.n;
    scheme::restrain::main(m::cart, f->q.cc, nn, it, /**/ qq);
}

void bounce_wall(const Wall *w, /**/ Flu *f, Rbc *r) {
    bounce(w->sdf, f->q.n, /**/ f->q.pp);
    if (rbcs) bounce(w->sdf, r->q.n, /**/ r->q.pp);
}
