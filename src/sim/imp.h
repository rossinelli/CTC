/* see bund.cu for more sim:: functions */

void create_walls() {
    int nold = o::q.n;
    wall::gen_quants(w::qsdf, &o::q.n, o::q.pp, &w::q); o::q.cells->build(o::q.pp, o::q.n);
    MSG("solvent particles survived: %d/%d", o::q.n, nold);
}

void create_solids() {
    cD2H(o::q.pp_hst, o::q.pp, o::q.n);
    rig::gen_quants(/*io*/ o::q.pp_hst, &o::q.n, /**/ &s::q);
    MC(l::m::Barrier(m::cart));
    cH2D(o::q.pp, o::q.pp_hst, o::q.n);
    MC(l::m::Barrier(m::cart));
    MSG("created %d solids.", s::q.ns);
}

void freeze() {
    MC(MPI_Barrier(m::cart));
    if (solids)           create_solids();
    if (walls && rbcs  )  remove_rbcs();
    if (walls && solids)  remove_solids();
    if (solids)           rig::set_ids(s::q);
}

void clear_vel() {
    if (o::q.n)           dev::clear_vel<<<k_cnf(o::q.n)>>>(o::q.pp, o::q.n);  
    if (solids && s::q.n) dev::clear_vel<<<k_cnf(s::q.n)>>>(s::q.pp, s::q.n);
    if (rbcs   && r::q.n) dev::clear_vel<<<k_cnf(r::q.n)>>>(r::q.pp, r::q.n);
}

void gen() { /* generate */
    run_eq(wall_creation);
    if (walls) {
        dSync();
        sdf::ini(&w::qsdf);
        create_walls();
    }
    freeze();
    clear_vel();
}

void sim_gen() {
    flu::gen_quants(&o::q);
    if (global_ids) flu::gen_ids(o::q.n, &o::qi);
    o::q.cells->build(o::q.pp, o::q.n);
    flu::get_ticketZ(o::q, &o::tz);
    flu::get_ticketRND(&o::trnd);
    if (rbcs) {
        rbc::gen_quants("rbc.off", "rbcs-ic.txt", /**/ &r::q);
        rbc::gen_ticket(r::q, &r::tt);
    }
    MC(MPI_Barrier(m::cart));
  
    long nsteps = (int)(tend / dt);
    MSG0("will take %ld steps", nsteps);
    if (walls || solids) {
        solids0 = false;  /* global */
        gen();
        dSync();
        if (walls) wall::gen_ticket(w::q, &w::t);
        flu::get_ticketZ(o::q, &o::tz);
        flu::get_ticketRND(&o::trnd);
        solids0 = solids;
        run(wall_creation, nsteps);
    } else {
        solids0 = solids;
        run(            0, nsteps);
    }
    /* final strt dump*/
    if (strt_dumps) dump_strt(restart::FINAL);
}

void sim_strt() {
    long nsteps = (int)(tend / dt);
    
    /*Q*/
    flu::strt_quants(restart::BEGIN, &o::q);
    if (global_ids) flu::strt_ii("id", restart::BEGIN, &o::qi);
    o::q.cells->build(/* io */ o::q.pp, o::q.n);

    if (rbcs) rbc::strt_quants("rbc.off", restart::BEGIN, &r::q);
    dSync();

    if (solids) rig::strt_quants(restart::BEGIN, &s::q);

    if (walls) wall::strt_quants(&w::q);

    /*T*/
    flu::get_ticketZ(o::q, &o::tz);
    flu::get_ticketRND(&o::trnd);
    if (rbcs)   rbc::gen_ticket(r::q, &r::tt);
    if (walls) wall::gen_ticket(w::q, &w::t);

    MC(MPI_Barrier(m::cart));
    if (walls) {
        dSync();
        sdf::ini(&w::qsdf);
    }

    solids0 = solids;

    MSG0("will take %ld steps", nsteps - wall_creation);
    run(wall_creation, nsteps);
    
    /* final strt dump*/
    if (strt_dumps) dump_strt(restart::FINAL);
}
