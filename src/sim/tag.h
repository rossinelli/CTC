/* set tags of particles according to the RBCs */
void gen_tags() {

    if (mc::tc.first) mcomm::post_recv(/**/ &mc::tc, &mc::tr);
    mcomm::extents(r::q.pp, r::q.nv, r::q.nc, /**/ &mc::ts);
    int nbulk = mcomm::pack(r::q.pp, r::q.nv, r::q.nc, /**/ &mc::ts);
    mcomm::post_send(r::q.nv, &mc::ts, /**/ &mc::tc);
    mcomm::wait_recv(/**/ &mc::tc);
    int nm = mcomm::unpack(r::q.nv, nbulk, /**/ &mc::tr);
    mcomm::post_recv(/**/ &mc::tc, &mc::tr);

    /* tmp texture object; TODO: make a ticket? */
    Texo<float2> texvert;
    texvert.setup((float2*) mc::tr.pp, nm * 3 * r::q.nv);

    collision::get_tags(o::q.pp, o::q.n, texvert, r::tt.textri, r::q.nt, r::q.nv, nm, /**/ o::qt.ii);

    texvert.destroy();
    mc::tc.first = false;
}
