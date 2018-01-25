void bop_ini(MPI_Comm comm, BopWork **w) {
    BopWork *t;
    size_t sz;
    UC(emalloc(sizeof(BopWork), (void**) w));
    t = *w;
    if (m::is_master(comm))
        UC(os_mkdir(DUMP_BASE "/bop"));

    sz = 9 * MAX_PART_NUM * sizeof(float);
    UC(emalloc(sz, (void**) &t->w_pp));
}

void bop_fin(BopWork *t) {
    UC(efree(t->w_pp));
    UC(efree(t));
}

static void p2f3(const Particle p, /**/ float3 *r, float3 *v) {
    enum {X, Y, Z};
    r->x = p.r[X];
    r->y = p.r[Y];
    r->z = p.r[Z];

    v->x = p.v[X];
    v->y = p.v[Y];
    v->z = p.v[Z];
}

static void f2f3(const Force fo, /**/ float3 *f) {
    enum {X, Y, Z};
    f->x = fo.f[X];
    f->y = fo.f[Y];
    f->z = fo.f[Z];
}

static void copy_shift(const Coords *c, const Particle *pp, long n, /**/ float3 *w) {
    float3 r, v;
    for (int j = 0; j < n; ++j) {
        p2f3(pp[j], /**/ &r, &v);
        local2global(c, r, /**/ &w[2*j]);
        w[2*j + 1] = v;
    }
}

static void copy_shift_with_forces(const Coords *coords, const Particle *pp, const Force *ff, long n, /**/ float3 *w) {
    float3 r, v, f;
    for (int j = 0; j < n; ++j) {
        p2f3(pp[j], /**/ &r, &v);
        f2f3(ff[j], /**/ &f);
        local2global(coords, r, /**/ &w[3*j]);
        w[3*j + 1] = v;
        w[3*j + 2] = f;
    }
}

#define PATTERN "%s-%05d"
    
static void header(long n, const char *name, int id, const char *type, const char *fields) {
    char fname[256] = {0};
    FILE *f;
    
    sprintf(fname, DUMP_BASE "/bop/" PATTERN ".bop", name, id);
        
    UC(efopen(fname, "w", /**/ &f));

    fprintf(f, "%ld\n", n);
    fprintf(f, "DATA_FILE: " PATTERN ".values\n", name, id);
    fprintf(f, "DATA_FORMAT: %s\n", type);
    fprintf(f, "VARIABLES: %s\n", fields);

    UC(efclose(f));
}

static void header_pp(long n, const char *name, int id) {
    header(n, name, id, "float", "x y z vx vy vz");
}

static void header_pp_ff(long n, const char *name, int id) {
    header(n, name, id, "float", "x y z vx vy vz fx fy fz");
}

static void header_ii(long n, const char *name, const char *fields, int id) {
    header(n, name, id, "int", fields);
}

static long write_data(MPI_Comm cart, const void *data, long n, size_t bytesperdata, MPI_Datatype datatype, const char *fname) {
    MPI_File f;
    MPI_Status status;
    MPI_Offset base, offset = 0;
    MPI_Offset len = n * bytesperdata;
    long ntot = 0;

    MC(m::Reduce(&n, &ntot, 1, MPI_LONG, MPI_SUM, 0, cart));
    MC(MPI_File_open(cart, fname, MPI_MODE_CREATE | MPI_MODE_WRONLY, MPI_INFO_NULL, &f));
    MC(MPI_File_set_size(f, 0));
    MC(MPI_File_get_position(f, &base)); 

    MC( MPI_Exscan(&len, &offset, 1, MPI_OFFSET, MPI_SUM, cart) );
    MC( MPI_File_write_at_all(f, base + offset, data, n, datatype, &status) ); 
    MC( MPI_File_close(&f) );
    return ntot;
}
    
void bop_parts(MPI_Comm cart, const Coords *coords, const Particle *pp, long n, const char *name, int id, BopWork *t) {
    copy_shift(coords, pp, n, /**/ (float3*) t->w_pp);
        
    char fname[256] = {0};
    sprintf(fname, DUMP_BASE "/bop/" PATTERN ".values", name, id);

    long ntot = write_data(cart, t->w_pp, n, sizeof(Particle), datatype::particle, fname);
    if (m::is_master(cart))
        header_pp(ntot, name, id);
}

void bop_parts_forces(MPI_Comm cart, const Coords *coords, const Particle *pp, const Force *ff, long n, const char *name, int id, /*w*/ BopWork *t) {
    copy_shift_with_forces(coords, pp, ff, n, /**/ (float3*) t->w_pp);
            
    char fname[256] = {0};
    sprintf(fname, DUMP_BASE "/bop/" PATTERN ".values", name, id);

    long ntot = write_data(cart, t->w_pp, n, sizeof(Particle) + sizeof(Force), datatype::partforce, fname);
    
    if (m::is_master(cart))
        header_pp_ff(ntot, name, id);
}

static void intdata(MPI_Comm cart, const int *ii, long n, const char *name, const char *fields, int id) {
    char fname[256] = {0};
    sprintf(fname, DUMP_BASE "/bop/" PATTERN ".values", name, id);

    long ntot = write_data(cart, ii, n, sizeof(int), MPI_INT, fname);
    
    if (m::is_master(cart))
        header_ii(ntot, name, fields, id);
}

void bop_ids(MPI_Comm cart, const int *ii, long n, const char *name, int id) {
    intdata(cart, ii, n, name, "id", id);
}

void bop_colors(MPI_Comm cart, const int *ii, long n, const char *name, int id) {
    intdata(cart, ii, n, name, "color", id);
}

#undef PATTERN
