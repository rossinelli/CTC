void forces(bool wall0) {
    clear_forces(flu.ff, flu.q.n);
    if (solids0) clear_forces(s::ff, s::q.n);
    if (rbcs)    clear_forces(r::ff, r::q.n);

    forces_dpd(&flu);
    if (wall0 && w::q.n) forces_wall();
    if (rbcs) forces_rbc();

    forces_objects(&flu);
    
    dSync();
}
