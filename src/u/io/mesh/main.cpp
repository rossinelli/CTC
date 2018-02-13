#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#include <conf.h>
#include "inc/conf.h"

#include "coords/ini.h"

#include "utils/msg.h"
#include "utils/mc.h"
#include "utils/error.h"

#include "mpi/glb.h"
#include "mpi/wrapper.h"

#include "io/off/imp.h"
#include "io/mesh/imp.h"

#include "parser/imp.h"

static void write(MPI_Comm cart, const Coords *c, const char *o, OffRead *cell) {
    int nc;
    MeshWrite *mesh;
    Particle *pp;

    UC(mesh_write_ini_off(cell, o, /**/ &mesh));

    nc = 1; pp = NULL;
    UC(mesh_write_dump(mesh, cart, c, nc, pp, 0));

    UC(mesh_write_fin(mesh));
}

static void log(OffRead *cell) {
    int nv, nt, md;
    md = off_get_md(cell);
    nv = off_get_nv(cell);
    nt = off_get_nt(cell);
    msg_print("nv, nt, max degree: %d %d %d", nv, nt, md);
}

int main(int argc, char **argv) {
    Config *cfg;
    OffRead *cell;
    Coords *coords;
    int rank, dims[3];
    MPI_Comm cart;
    const char *i, *o; /* input and output */
    
    m::ini(&argc, &argv);
    m::get_dims(&argc, &argv, dims);
    m::get_cart(MPI_COMM_WORLD, dims, &cart);

    MC(m::Comm_rank(cart, &rank));
    msg_ini(rank);

    UC(conf_ini(/**/ &cfg));
    UC(conf_read(argc, argv, /**/ cfg));

    UC(coords_ini_conf(cart, cfg, /**/ &coords));

    UC(conf_lookup_string(cfg, "i", &i));
    UC(conf_lookup_string(cfg, "o", &o));

    msg_print("i = '%s'", i);
    msg_print("o = '%s'", o);
    UC(off_read(i, &cell));
    UC(log(cell));

    write(cart, coords, o, cell);

    UC(coords_fin(coords));
    UC(off_fin(cell));
    UC(conf_fin(cfg));

    MC(m::Barrier(cart));
    m::fin();
}
