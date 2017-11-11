namespace rbc { namespace forces {
struct Quants {
    int n, nc;             /* number of particles, cells            */
    Particle *pp, *pp_hst; /* vertices particles on host and device */
    float *av;             /* area and volume on device             */

    int *ii;               /* global ids (on host) */
    
    int nt, nv;            /* number of triangles and vertices per mesh */
    int *adj0, *adj1;      /* adjacency lists on device                 */
    int4 *tri, *tri_hst;   /* triangles: vertex indices                 */
};

/* textures ticket */
struct TicketT {
    Texo <float2> texvert;
    Texo <int> texadj0, texadj1;
    Texo <int4> textri;
};

void ini(Quants *q);
void fin(Quants *q);

void gen_ticket(const Quants q, TicketT *t);
void fin_ticket(TicketT *t);

void gen_quants(const char *r_templ, const char *r_state, Quants *q);
void strt_quants(const char *r_templ, const int id, Quants *q);
void strt_dump(const int id, const Quants q);

void forces(const Quants q, const TicketT t, /**/ Force *ff);

}} /* namespace */
