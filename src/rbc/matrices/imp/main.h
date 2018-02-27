static const int MAX_N = 999999;

static int read_matrix(FILE *f, double A[16]) {
    int i;
    for (i = 0; i < 16; i++)
        if (fscanf(f, "%lf", &A[i]) != 1) return 0;
    return 1;
}

static int read_d3(FILE *f, double A[16]) {
    enum {X, Y, Z};
    int i;
    double r[3];
    for (i = 0; i < 3; i++)
        if (fscanf(f, "%lf", &r[i]) != 1) return 0;
    i = 0;
    A[i++] = 1; A[i++] = 0; A[i++] = 0; A[i++] = r[X];
    A[i++] = 0; A[i++] = 1; A[i++] = 0; A[i++] = r[Y];
    A[i++] = 0; A[i++] = 0; A[i++] = 1; A[i++] = r[Z];
    A[i++] = 0; A[i++] = 0; A[i++] = 0; A[i++] = 1;
    return 1;
}

void matrices_read(const char *path, /**/ Matrices **pq) {
    int n;
    FILE *f;
    Matrices *q;
    EMALLOC(1, &q);
    EMALLOC(MAX_N, &q->m);
    UC(efopen(path, "r", /**/ &f));
    UC(efclose(f));
    n = 0;
    while (read_matrix(f, /**/ q->m[n++].D)) ;
    q->n = n;
    *pq = q;
}

void matrices_read_r(const char *path, /**/ Matrices **pq) {
    int n;
    FILE *f;
    Matrices *q;
    EMALLOC(1, &q);
    EMALLOC(MAX_N, &q->m);
    UC(efopen(path, "r", /**/ &f));
    UC(efclose(f));
    n = 0;
    while (read_d3(f, /**/ q->m[n++].D)) ;
    q->n = n;
    *pq = q;
}


void matrices_fin(Matrices *q) { EFREE(q->m); EFREE(q); }
