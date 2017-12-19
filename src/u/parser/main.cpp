#include <stdio.h>

#include "msg.h"
#include "mpi/glb.h"
#include "utils/error.h"
#include "parser/imp.h"

static void extract(const Config *c) {
    int a;
    float f;

    UC(conf_lookup_int(c, "a", &a));
    UC(conf_lookup_float(c, "f", &f));

    printf("%d %g\n", a, f);
}

int main(int argc, char **argv) {
    Config *cfg;
    m::ini(&argc, &argv);

    conf_ini(/**/ &cfg);
    conf_read(argc, argv, /**/ cfg);

    UC(extract(cfg));
    
    conf_destroy(/**/ cfg);    

    m::fin();
}