struct RigPinInfo;

struct RigGenInfo {
    float mass;
    const RigPinInfo *pi;
    int nt, nv;
    const int4 *tt;
    const float *vv;
};

struct FluInfo {
    Particle *pp;
    int *n;
};

namespace gen {
void gen_rig_from_solvent(const Coords *coords, MPI_Comm comm, RigGenInfo rgi,
                          /* io */ FluInfo fluinfo,
                          /* o */ int *ns, int *nps, int *n, float *rr0_hst, Solid *ss_hst, Particle *pp_hst);

void set_rig_ids(MPI_Comm comm, int n, /**/ Solid * ss);
} // gen
