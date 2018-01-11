void eobj_pack_fin(EObjPack *p) {
    UC(emap_fin(NFRAGS, /**/ &p->map));
    UC(bags_fin(PINNED, NONE, /**/ &p->hpp, &p->dpp));
}

void eobj_comm_fin(EObjComm *c) {
    UC(comm_fin(&c->pp));
    UC(comm_fin(&c->ff));
}

void eobj_unpack_fin(EObjUnpack *u) {
    UC(bags_fin(PINNED_DEV, NONE, /**/ &u->hpp, &u->dpp));
}

void eobj_packf_fin(EObjPackF *p) {
    UC(bags_fin(PINNED_DEV, NONE, /**/ &p->hff, &p->dff));
}

void eobj_unpackf_fin(EObjUnpackF *u) {
    UC(bags_fin(PINNED_DEV, NONE, /**/ &u->hff, &u->dff));
}
