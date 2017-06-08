
#### contact force: RBC and sphere in double Poiseuille
# sTEST: mix.contact.t1
# export PATH=../tools:$PATH
# rm -rf diag.txt h5 bop ply
#  x=5 y=17 z=8; echo 1 0 0 $x  0 1 0 $y  0 0 1 $z  0 0 0 1 > rbcs-ic.txt
# x=11 y=15 z=8; echo $x $y $z                              > ic_solid.txt
# cp data/sphere_R2.ply mesh_solid.ply
# :
# argp .conf.double.poiseuille.h -rbcs -tend=2.0 -part_freq=1500 \
#        -solids -sbounce_back -wall_creation=1                  \
#        -part_dumps -field_freq=1500                            \
#        -pushflow -doublepoiseuille                             \
#        -contactforces > .conf.h
# :
# { make clean &&  make -j && make -C ../tools; } > /dev/null
# ./udx
# ply2punto ply/rbcs-00002.ply | uscale 1 > ply.out.txt

#### no contact force: RBC and sphere in double Poiseuille
# cTEST: mix.no.contact.t1
# export PATH=../tools:$PATH
# rm -rf diag.txt h5 bop ply
#  x=5 y=17 z=8; echo 1 0 0 $x  0 1 0 $y  0 0 1 $z  0 0 0 1 > rbcs-ic.txt
# x=11 y=15 z=8; echo $x $y $z                              > ic_solid.txt
# cp data/sphere_R2.ply mesh_solid.ply
# :
# argp .conf.double.poiseuille.h -rbcs -tend=2.0 -part_freq=1500 \
#        -solids -sbounce_back -wall_creation=1                  \
#        -part_dumps -field_freq=1500                            \
#        -pushflow -doublepoiseuille                             \
#         > .conf.h
# :
# { make clean &&  make -j && make -C ../tools; } > /dev/null
# ./udx
# ply2punto ply/rbcs-00002.ply | uscale 1 > ply.out.txt
