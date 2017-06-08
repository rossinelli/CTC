#!/usr/bin/sh

setup() {
    make -C ../tools/rbc install
    make -C ../tools install
    make -C ../post/build_smesh install
}

pre() {
    XS=40 YS=52 ZS=20
    df=1.0

    D="-XS=$XS -YS=$YS -ZS=$ZS"

    radius=3
    fraction=0.5
    sc=1 ang=0
    plcmt.ro $XS $YS $ZS $radius $fraction $sc $ang ic_solid.txt rbcs-ic.txt

    rm -rf diag.txt h5 bop ply solid-ply solid_diag*txt
    cp $HOME/geoms/128.dat      sdf.dat
    cp data/sphere_R1.ply mesh_solid.ply
    cp cells/rbc.496.off  rbc.off

    argp .conf.gx.base.h $D           \
	 -numberdensity=1             \
         -rbcs -solids -contactforces \
         -tend=3000.0 -part_freq=1000 \
         -walls -wall_creation=1      \
         -pushflow -driving_force=$df \
         -field_dumps -part_dumps -field_freq=1000 > .conf.h
}

compile() {
    { make clean && make -j ; } > /dev/null
}

#. ./gx.panda.sh
# . ./gx.daint.sh
. ./gx.interactive.sh

setup
pre
ini
compile
run
