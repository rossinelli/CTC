void halo(Pap26 PP, Fop26 FF, int counts[26]) {
    int i, s, n;
    int starts[27];
    starts[0] = 0;
    for (i = s = 0; i < 26; ++i) starts[i + 1] = (s += counts[i]);
    n = starts[26];

    CC(cudaMemcpyToSymbolAsync(dev::g::counts, counts, 26*sizeof(counts[0]), 0, H2D));
    CC(cudaMemcpyToSymbolAsync(dev::g::starts, starts, sizeof(starts), 0, H2D));
    CC(cudaMemcpyToSymbolAsync(dev::g::pp, PP.d, 26*sizeof(PP.d[0]), 0, H2D));
    CC(cudaMemcpyToSymbolAsync(dev::g::ff, FF.d, 26*sizeof(FF.d[0]), 0, H2D));
    KL(dev::halo, (k_cnf(n)), (n, rgen->get_float()));
}
