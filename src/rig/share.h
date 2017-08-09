namespace rig {
namespace sub {
namespace ic {

static void share0(const int root, /**/ Particle *pp, int *n) {
    std::vector<int> counts(m::size), displs(m::size);
    std::vector<Particle> recvbuf(MAX_PSOLID_NUM);
    MC(MPI_Gather(n, 1, MPI_INT, counts.data(), 1, MPI_INT, root, l::m::cart) );

    if (m::rank == root)
    {
        displs[0] = 0;
        for (int j = 0; j < m::size - 1; ++j)
            displs[j+1] = displs[j] + counts[j];
    }

    MC(MPI_Gatherv(pp, *n,
                   datatype::particle, recvbuf.data(), counts.data(), displs.data(),
                   datatype::particle, root, l::m::cart) );

    if (m::rank == root) {
        *n = displs.back() + counts.back();
        for (int i = 0; i < *n; ++i) pp[i] = recvbuf[i];
    }
}

static void share(const int root, /**/ Particle *pp, int *n) {
    if (*n >= MAX_PSOLID_NUM) ERR("Number of solid particles too high for the buffer\n");
    // set to global coordinates and then convert back to local
    int i, c;
    const int L[3] = {XS, YS, ZS};
    int mi[3];

    for (c = 0; c < 3; ++c) mi[c] = (m::coords[c] + 0.5) * L[c];
    for (i = 0; i < *n; ++i) for (c = 0; c < 3; ++c) pp[i].r[c] += mi[c];

    share0(root, /**/ pp, n);

    for (i = 0; i < *n; ++i) for (c = 0; c < 3; ++c) pp[i].r[c] -= mi[c];

}

} // ic
} // rig
} // sub
