struct Vectors {
    int type;
    int n;
    union {
        const float *rr;
        const Particle *pp;
    } D;
    const Coords *coords;
};

static void float_get(Vectors*, int i, float r[3]);

static void positions_get(Vectors*, int i, float r[3]);
static void positions_edge_get(Vectors*, int i, float r[3]);

static void velocities_get(Vectors*, int i, float r[3]);
static void zero_get(Vectors*, int i, float r[3]);

enum {FLOAT, POSITIONS, POSITIONS_EDGE, VELOCITIES, ZERO};
static void (*get[])(Vectors*, int i, float r[3]) =
{ float_get,  positions_get, positions_edge_get, velocities_get, zero_get };
