static void set_dev(WvelCste p, Wvel_d *wv) {
    wv->type = WALL_VEL_DEV_CSTE;
    wv->p.cste.u = p.u;
}

static void set_dev(WvelShear p, Wvel_d *wv) {
    wv->type = WALL_VEL_DEV_SHEAR;
    wv->p.shear.gdot = p.g;
}

static void set_dev(long it, WvelShearSin p, Wvel_d *wv) {
    float3 gdot;
    float t, w;
    bool cond;
    wv->type = WALL_VEL_DEV_SHEAR;

    w = p.w;
    t = it * dt;

    gdot.x = p.g.x * sin(w * t);
    gdot.y = p.g.y * sin(w * t);
    gdot.z = p.g.z * sin(w * t);
    
    wv->p.shear.gdot = gdot;

    cond = p.log_freq > 0 && it % p.log_freq == 0;
    if (cond)
        MSG("WVEL_SIN: gd = %6.3g %6.3g %6.3g", gdot.x, gdot.y, gdot.z);
}

void step2params(long it, /**/ Wvel *wv) {
    switch (wv->type) {
    case WALL_VEL_CSTE:
        set_dev(wv->p.cste, /**/ &wv->dev);
        break;
    case WALL_VEL_SHEAR:
        set_dev(wv->p.shear, /**/ &wv->dev);
        break;
    case WALL_VEL_SHEAR_SIN:
        // TODO
        break;
    default:
        ERR("wrong type provided: <%d>", wv->type);
        break;
    };
}
