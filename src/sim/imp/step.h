void step(float driving_force0, bool wall0, int it) {
    distribute_flu();
    if (solids0) distribute_rig();
    if (rbcs)    distribute_rbc();

    forces(wall0);

    dump_diag0(it);
    if (wall0 || solids0) dump_diag_after(it);
    body_force(driving_force0);
    
    update_solvent(it);
    if (solids0) update_solid();
    if (rbcs)    update_rbc(it);

    if (wall0) bounce();
    if (sbounce_back && solids0) bounce_solid_old(it);
    // if (sbounce_back && solids0) bounce_solid_v2(it);
}
