struct Outflow {
    int *kk; /* die or stay alive? */
};

void ini(int maxp, /**/ Outflow *o);
void fin(/**/ Outflow *o);

void filter_particles_circle(float R, int n, const Particle *pp, Outflow *o);
