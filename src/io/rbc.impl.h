static void shift0(Particle* f, /**/ Particle* t) {
    enum {X, Y, Z};
    int *c;
    c = m::coords;
    t->r[X] = f->r[X] + 0.5*XS + c[X]*XS;
    t->r[Y] = f->r[Y] + 0.5*YS + c[Y]*YS;
    t->r[Z] = f->r[Z] + 0.5*ZS + c[Z]*ZS;
}

static void shift(Particle* f, int n, /**/ Particle* t) {
    /* f, t: from, to */
    int i;
    for (i = 0; i < n; i++) shift0(f++, t++);
}

static void write(const void * const ptr, const int nbytes32, MPI_File f) {
    MPI_Offset base;
    MC(MPI_File_get_position(f, &base));
    MPI_Offset offset = 0, nbytes = nbytes32;
    MC(MPI_Exscan(&nbytes, &offset, 1, MPI_OFFSET, MPI_SUM, m::cart));
    MPI_Status status;
    MC(MPI_File_write_at_all(f, base + offset, ptr, nbytes, MPI_CHAR, &status));
    MPI_Offset ntotal = 0;
    MC(MPI_Allreduce(&nbytes, &ntotal, 1, MPI_OFFSET, MPI_SUM, m::cart) );
    MC(MPI_File_seek(f, ntotal, MPI_SEEK_CUR));
}

static void dump0(Particle  *_particles, int *faces,
                  int nc, int nv, int nt, MPI_File f) {
    std::vector<Particle> particles(_particles, _particles + nc * nv);
    int NPOINTS = 0;
    const int n = particles.size();
    l::m::Reduce(&n, &NPOINTS, 1, MPI_INT, MPI_SUM, 0, m::cart) ;
    const int ntriangles = nt * nc;
    int NTRIANGLES = 0;
    l::m::Reduce(&ntriangles, &NTRIANGLES, 1, MPI_INT, MPI_SUM, 0, m::cart) ;
    std::stringstream ss;
    if (m::rank == 0) {
        ss <<  "ply\n";
        ss <<  "format binary_little_endian 1.0\n";
        ss <<  "element vertex " << NPOINTS << "\n";
        ss <<  "property float x\nproperty float y\nproperty float z\n";
        ss <<  "property float u\nproperty float v\nproperty float w\n";
        ss <<  "element face " << NTRIANGLES << "\n";
        ss <<  "property list int int vertex_index\n";
        ss <<  "end_header\n";
    }
    std::string content = ss.str();
    write(content.c_str(), content.size(), f);

    write(&particles.front(), sizeof(Particle) * n, f);
    int poffset = 0;
    MPI_Exscan(&n, &poffset, 1, MPI_INTEGER, MPI_SUM, m::cart);
    std::vector<int> buf;
    for(int j = 0; j < nc; ++j)
    for(int i = 0; i < nt; ++i) {
        int primitive[4] = { 3,
                             poffset + nv * j + faces[3 * i + 0],
                             poffset + nv * j + faces[3 * i + 1],
                             poffset + nv * j + faces[3 * i + 2] };
        buf.insert(buf.end(), primitive, primitive + 4);
    }
    write(&buf.front(), sizeof(int) * buf.size(), f);
}

static void dump1(Particle  *pp, int *faces, int nc, int nv, int nt, MPI_File f) {
    int sz, n;
    Particle* pp0;
    n = nc * nv;
    sz = n*sizeof(Particle);
    pp0 = (Particle*)malloc(sz);
    shift(pp, n, /**/ pp0); /* copy-shift to global coordinates */
    dump0(pp0, faces, nc, nv, nt, f);
    free(pp0);
}

static void dump2(Particle  *pp, int *faces, int nc, int nv, int nt, const char *fn) {
    MPI_File f;
    MPI_File_open(m::cart, fn, MPI_MODE_WRONLY |  MPI_MODE_CREATE, MPI_INFO_NULL, &f);
    MPI_File_set_size(f, 0);
    dump1(pp, faces, nc, nv, nt, f);
    MPI_File_close(&f);
}

void rbc_dump(Particle *pp, int *faces, int nc, int nv, int nt, int id) {
    const char *fmt = DUMP_BASE "/r/%05d.ply";
    char f[BUFSIZ]; /* file name */
    sprintf(f, fmt, id);
    if (m::rank == 0) os::mkdir(DUMP_BASE "/r");
    dump2(pp, faces, nc, nv, nt, f);
}
