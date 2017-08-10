namespace rex {
struct RemoteHalo {
    History h;
    DeviceBuffer<Particle> dstate;
    PinnedHostBuffer<Particle> hstate;
    PinnedHostBuffer<Force> ff;
    std::vector<Particle> pmessage;
};

namespace re {
void resize(RemoteHalo *r, int n) {
    r->dstate.resize(n);
    r->hstate.preserve_resize(n);
    r->ff.resize(n);
    r->h.update(n);
}

int expected(RemoteHalo *r) {
    return (int)ceil(r->h.max() * 1.1);
}

}
}
