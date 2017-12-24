void force(Wvel_v wv, Coords c, Sdf *sdf, const Quants q, const Ticket t, Cloud cloud, const int n, Force *ff) {
    Wa wa; /* local wall data */

    to_view(sdf, &wa.sdf_v);
    wa.start = t.texstart;
    wa.pp  = t.texpp;
    wa.n      = q.n;

    force(wv, c, cloud, n, t.rnd, wa, /**/ ff);
}
