struct Wvel;
struct WvelStep;

struct WvelCste_v;
struct WvelShear_v;
struct WvelHS_v;

struct float3;
struct Config;

enum {
    WALL_VEL_V_CSTE,
    WALL_VEL_V_SHEAR,
    WALL_VEL_V_HS,
};

// tag::mem[]
void wvel_ini(Wvel **wv);
void wvel_fin(Wvel *wv);

void wvel_step_ini(WvelStep **wv);
void wvel_step_fin(WvelStep *wv);
// end::mem[]

// tag::ini[]
void wvel_set_cste(float3 u, Wvel *vw);
void wvel_set_shear(float gdot, int vdir, int gdir, int half, Wvel *vw);
void wvel_set_shear_sin(float gdot, int vdir, int gdir, int half, float w, int log_freq, Wvel *vw);
void wvel_set_hs(float u, float h, Wvel *vw);
void wvel_set_timestep(float dt, Wvel *vw);
// end::ini[]

// tag::cnf[]
void wvel_set_conf(const Config *cfg, Wvel *vw);
// end::cnf[]

// tag::int[]
void wvel_get_step(float dt, long it, const Wvel *wv, /**/ WvelStep *view);
// end::int[]

int wvel_get_type(const WvelStep *w);

void wvel_get_view(const WvelStep *w, /**/ WvelCste_v *v);
void wvel_get_view(const WvelStep *w, /**/ WvelShear_v *v);
void wvel_get_view(const WvelStep *w, /**/ WvelHS_v *v);
