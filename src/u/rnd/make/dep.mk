$B/comm/imp.o: $S/comm/imp.h $S/comm/imp/fin.h $S/comm/imp/ini.h $S/comm/imp/main.h $B/conf.h $S/d/api.h $S/frag/imp.h $S/inc/conf.h $S/mpi/glb.h $S/mpi/wrapper.h $S/msg.h $S/utils/cc.h $S/utils/error.h $S/utils/imp.h $S/utils/mc.h
$B/d/api.o: $B/conf.h $S/d/api.h $S/d/common.h $S/d/cpu/imp.h $S/d/cuda/imp.h $S/inc/conf.h $S/utils/error.h $S/utils/imp.h
$B/frag/imp.o: $B/conf.h $S/frag/imp.h $S/inc/conf.h
$B/math/rnd/imp.o: $S/math/rnd/imp.h $S/utils/error.h $S/utils/imp.h
$B/mpi/glb.o: $B/conf.h $S/inc/conf.h $S/mpi/glb.h $S/mpi/wrapper.h $S/utils/mc.h
$B/mpi/type.o: $S/inc/conf.h $S/inc/type.h $S/mpi/type.h $S/utils/mc.h
$B/mpi/wrapper.o: $S/mpi/wrapper.h
$B/msg.o: $S/mpi/glb.h $S/msg.h
$B/u/rnd/main.o: $S/math/rnd/imp.h $S/mpi/glb.h $S/msg.h $S/utils/error.h
$B/utils/cc.o: $B/conf.h $S/d/api.h $S/inc/conf.h $S/utils/cc/common.h $S/utils/error.h
$B/utils/error.o: $S/msg.h $S/utils/error.h
$B/utils/imp.o: $S/utils/error.h $S/utils/imp.h
$B/utils/mc.o: $B/conf.h $S/inc/conf.h $S/utils/error.h $S/utils/mc.h
$B/utils/os.o: $S/msg.h $S/utils/error.h $S/utils/os.h