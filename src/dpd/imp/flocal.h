void flocal0(float4 *zip0, ushort4 *zip1, int np, int *start, int *count, float seed, float* ff) {
    static InfoDPD c;
    if( !fdpd_init ) {
        setup();
        mps();
        fdpd_init = true;
    }
    tex(zip0, zip1, np, start, count);
    c.ncells = make_int3( XS, YS, ZS );
    c.nxyz = XS * YS * ZS;
    c.ff = ff;
    c.seed = seed;

    if (!is_mps_enabled)
	CC( cudaMemcpyToSymbolAsync( info, &c, sizeof( c ), 0, cudaMemcpyHostToDevice) );
    else
	CC( cudaMemcpyToSymbol( info, &c, sizeof( c ), 0, cudaMemcpyHostToDevice ) );

    int np32 = np;
    if( np32 % 32 ) np32 += 32 - np32 % 32;
    CC( cudaMemsetAsync( ff, 0, sizeof( float )* np32 * 3) );

    if( c.ncells.x % MYCPBX == 0 && c.ncells.y % MYCPBY == 0 && c.ncells.z % MYCPBZ == 0 ) {
        merged<<< dim3( c.ncells.x / MYCPBX, c.ncells.y / MYCPBY, c.ncells.z / MYCPBZ ), dim3( 32, MYWPB ), 0>>> ();
        CC(cudaPeekAtLastError());
        transpose<<< 28, 1024, 0>>>(np);
        CC(cudaPeekAtLastError());
    } else {
        fprintf( stderr, "Incompatible grid config\n" );
    }
}

void flocal(float4 *zip0, ushort4 *zip1, int n, int *start, int *count,
	    rnd::KISS* rnd, /**/ Force *ff) {
    if (n <= 0) return;
    flocal0(zip0, zip1, n, start, count, rnd->get_float(), (float*)ff);
}
