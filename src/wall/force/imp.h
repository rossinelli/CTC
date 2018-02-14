struct PairParams;
struct PaArray;

struct WallForce { /* local wall data */
    Sdf_v sdf_v;
    Texo<int> start;
    Texo<float4> pp;
    int n;
    int3 L;
};

void wall_force_apply(const PairParams*, Wvel_v wv, const Coords *c, const PaArray *parray, int n, RNDunif *rnd, WallForce wa, /**/ Force *ff);
