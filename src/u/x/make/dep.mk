$B/algo/minmax.o: $S/algo/minmax.h $B/conf.h $S/d/api.h $S/d/ker.h $S/d/q.h $S/inc/conf.h $S/inc/def.h $S/inc/dev.h $S/inc/type.h $S/msg.h $S/utils/cc.h $S/utils/kl.h
$B/algo/scan/imp.o: $S/algo/scan/cpu/imp.h $S/algo/scan/cuda/imp.h $S/algo/scan/dev.h $S/algo/scan/int.h $B/conf.h $S/d/api.h $S/d/ker.h $S/d/q.h $S/inc/conf.h $S/inc/def.h $S/inc/dev.h $S/msg.h $S/utils/cc.h $S/utils/kl.h
$B/clist/imp.o: $S/algo/scan/int.h $S/clist/dev.h $S/clist/int.h $B/conf.h $S/d/api.h $S/d/ker.h $S/d/q.h $S/inc/conf.h $S/inc/def.h $S/inc/dev.h $S/inc/type.h $S/mpi/glb.h $S/msg.h $S/utils/cc.h $S/utils/kl.h
$B/cnt/imp.o: $S/algo/scan/int.h $S/clist/int.h $S/cnt/dev/bulk.h $S/cnt/dev/code.h $S/cnt/dev/decl.h $S/cnt/dev/fetch.h $S/cnt/dev/halo.h $S/cnt/dev/map/bulk.h $S/cnt/dev/map/common.h $S/cnt/dev/map/halo.h $S/cnt/dev/pop.h $S/cnt/imp/bind.h $S/cnt/imp/build.h $S/cnt/imp/bulk.h $S/cnt/imp/decl.h $S/cnt/imp/fin.h $S/cnt/imp/halo.h $S/cnt/imp/ini.h $S/cnt/imp/setup.h $B/conf.h $S/d/api.h $S/d/ker.h $S/d/q.h $S/dbg/imp.h $S/forces/imp.h $S/forces/pack.h $S/forces/type.h $S/frag.h $S/glb.h $S/inc/conf.h $S/inc/def.h $S/inc/dev.h $S/inc/dev/common.h $S/inc/dev/index.h $S/inc/dev/read.h $S/inc/dev/write.h $S/inc/tmp/pinned.h $S/inc/tmp/wrap.h $S/inc/type.h $S/mpi/basetags.h $S/mpi/glb.h $S/mpi/wrapper.h $S/msg.h $S/rnd/dev.h $S/rnd/imp.h $S/utils/cc.h $S/utils/kl.h $S/utils/mc.h $S/utils/te.h $S/utils/texo.h
$B/comm/imp.o: $S/comm/imp.h $B/conf.h $S/inc/conf.h $S/mpi/wrapper.h $S/utils/mc.h
$B/d/api.o: $B/conf.h $S/d/api.h $S/d/common.h $S/d/cpu/imp.h $S/d/cuda/imp.h $S/inc/conf.h $S/msg.h
$B/dbg/imp.o: $B/conf.h $S/d/api.h $S/dbg/dev.h $S/dbg/error.h $S/dbg/imp.h $S/dbg/macro/switch.h $S/inc/conf.h $S/inc/dev.h $S/inc/type.h $S/msg.h $S/utils/cc.h $S/utils/kl.h
$B/dpdr/imp.o: $B/conf.h $S/d/api.h $S/d/ker.h $S/d/q.h $S/dpdr/buf.h $S/dpdr/dev/common.h $S/dpdr/dev/fill.h $S/dpdr/fin.h $S/dpdr/imp.h $S/dpdr/ini.h $S/dpdr/recv.h $S/dpdr/type.h $S/frag.h $S/inc/conf.h $S/inc/def.h $S/inc/dev.h $S/inc/dev/common.h $S/inc/dev/read.h $S/inc/type.h $S/mpi/glb.h $S/mpi/type.h $S/mpi/wrapper.h $S/msg.h $S/rnd/imp.h $S/utils/cc.h $S/utils/kl.h $S/utils/mc.h
$B/dpdr/int.o: $S/cloud/generic/int.h $S/cloud/generic/type.h $B/conf.h $S/d/api.h $S/dpdr/imp.h $S/dpdr/int.h $S/dpdr/type.h $S/frag.h $S/hforces/imp.h $S/inc/conf.h $S/inc/def.h $S/inc/dev.h $S/inc/type.h $S/mpi/basetags.h $S/msg.h $S/rnd/imp.h $S/utils/cc.h
$B/dual/imp.o: $B/conf.h $S/d/api.h $S/dual/int.h $S/dual/type.h $S/inc/conf.h $S/inc/dev.h $S/msg.h $S/utils/cc.h
$B/field.o: $B/conf.h $S/field.h $S/inc/conf.h $S/inc/type.h $S/io/field.h $S/mpi/glb.h $S/msg.h
$B/flu/imp.o: $B/conf.h $S/d/api.h $S/d/ker.h $S/d/q.h $S/flu/dev0.h $S/flu/dev1.h $S/flu/imp.h $S/inc/conf.h $S/inc/def.h $S/inc/dev.h $S/inc/type.h $S/io/restart.h $S/mpi/wrapper.h $S/msg.h $S/utils/cc.h $S/utils/kl.h $S/utils/mc.h
$B/flu/int.o: $S/clist/int.h $B/conf.h $S/d/api.h $S/flu/imp.h $S/flu/int.h $S/inc/conf.h $S/inc/def.h $S/inc/dev.h $S/inc/type.h $S/msg.h $S/rnd/imp.h $S/utils/cc.h
$B/fsi/imp.o: $S/algo/scan/int.h $S/clist/int.h $B/conf.h $S/d/api.h $S/d/ker.h $S/d/q.h $S/dbg/imp.h $S/dual/int.h $S/dual/type.h $S/forces/imp.h $S/forces/pack.h $S/forces/type.h $S/frag.h $S/fsi/dev/bulk.h $S/fsi/dev/common.h $S/fsi/dev/decl.h $S/fsi/dev/fetch.h $S/fsi/dev/halo.h $S/fsi/dev/map.common.h $S/fsi/dev/map/bulk.h $S/fsi/dev/map/halo.h $S/fsi/dev/pair.h $S/fsi/dev/type.h $S/fsi/imp/bind.h $S/fsi/imp/bulk.h $S/fsi/imp/decl.h $S/fsi/imp/fin.h $S/fsi/imp/halo.h $S/fsi/imp/ini.h $S/fsi/imp/setup.h $S/inc/conf.h $S/inc/def.h $S/inc/dev.h $S/inc/dev/common.h $S/inc/dev/index.h $S/inc/dev/read.h $S/inc/dev/write.h $S/inc/tmp/pinned.h $S/inc/tmp/wrap.h $S/inc/type.h $S/io/field.h $S/io/rbc.h $S/mpi/basetags.h $S/mpi/glb.h $S/mpi/type.h $S/msg.h $S/rbc/int.h $S/rnd/dev.h $S/rnd/imp.h $S/sim/int.h $S/utils/cc.h $S/utils/kl.h $S/utils/mc.h $S/utils/te.h $S/utils/texo.h
$B/glb.o: $B/conf.h $S/d/api.h $S/glb.h $S/inc/conf.h $S/mpi/glb.h
$B/hforces/imp.o: $S/cloud/generic/get.h $S/cloud/generic/type.h $B/conf.h $S/d/api.h $S/d/ker.h $S/d/q.h $S/forces/imp.h $S/forces/pack.h $S/forces/type.h $S/forces/use.h $S/hforces/dev.h $S/hforces/dev.map.h $S/hforces/imp.h $S/inc/conf.h $S/inc/def.h $S/inc/dev.h $S/inc/dev/common.h $S/inc/dev/read.h $S/inc/type.h $S/mpi/glb.h $S/msg.h $S/rnd/dev.h $S/rnd/imp.h $S/utils/cc.h $S/utils/kl.h
$B/inter/imp.o: $S/algo/scan/int.h $S/clist/int.h $B/conf.h $S/d/api.h $S/d/ker.h $S/d/q.h $S/dbg/imp.h $S/dual/int.h $S/dual/type.h $S/flu/int.h $S/frag.h $S/inc/conf.h $S/inc/def.h $S/inc/dev.h $S/inc/tmp/pinned.h $S/inc/tmp/wrap.h $S/inc/type.h $S/inter/imp.h $S/inter/int.h $S/mpi/basetags.h $S/mpi/type.h $S/mpi/wrapper.h $S/msg.h $S/rbc/int.h $S/rig/int.h $S/rnd/imp.h $S/sdf/int.h $S/sdf/type.h $S/utils/cc.h $S/utils/kl.h $S/utils/mc.h $S/utils/texo.h $S/wall/int.h
$B/io/bop/imp.o: $B/conf.h $S/d/api.h $S/inc/conf.h $S/inc/def.h $S/inc/type.h $S/io/bop/imp.h $S/mpi/glb.h $S/mpi/type.h $S/mpi/wrapper.h $S/msg.h $S/utils/mc.h $S/utils/os.h
$B/io/diag.o: $B/conf.h $S/inc/conf.h $S/inc/type.h $S/io/diag.h $S/mpi/glb.h $S/mpi/wrapper.h $S/msg.h
$B/io/field.o: $B/conf.h $S/inc/conf.h $S/inc/type.h $S/io/field.h $S/io/field/dump.h $S/io/field/field.h $S/io/field/grid.h $S/io/field/imp.h $S/io/field/scalar.h $S/io/field/wrapper.h $S/mpi/glb.h $S/mpi/wrapper.h $S/utils/mc.h $S/utils/os.h
$B/io/off.o: $S/io/off.h $S/io/off/imp.h
$B/io/ply.o: $S/inc/def.h $S/inc/type.h $S/io/ply.h $S/io/ply/ascii.h $S/io/ply/bin.h $S/io/ply/common.h $S/msg.h
$B/io/rbc.o: $B/conf.h $S/inc/conf.h $S/inc/type.h $S/io/rbc.h $S/io/rbc/imp.h $S/mpi/glb.h $S/mpi/wrapper.h $S/utils/mc.h $S/utils/os.h
$B/io/restart.o: $B/conf.h $S/inc/conf.h $S/inc/def.h $S/inc/type.h $S/io/restart.h $S/mpi/glb.h $S/msg.h
$B/io/rig.o: $B/conf.h $S/inc/conf.h $S/inc/type.h
$B/lforces/local.o: $S/cloud/lforces/get.h $S/cloud/lforces/int.h $B/conf.h $S/d/api.h $S/d/ker.h $S/d/q.h $S/forces/imp.h $S/forces/pack.h $S/forces/type.h $S/inc/conf.h $S/inc/def.h $S/inc/dev.h $S/inc/type.h $S/lforces/dev/core.h $S/lforces/dev/decl.h $S/lforces/dev/dpd.h $S/lforces/dev/fetch.h $S/lforces/dev/float.h $S/lforces/dev/merged.h $S/lforces/dev/pack.h $S/lforces/dev/tex.h $S/lforces/dev/transpose.h $S/lforces/imp/decl.h $S/lforces/imp/flocal.h $S/lforces/imp/info.h $S/lforces/imp/setup.h $S/lforces/imp/tex.h $S/lforces/imp/type.h $S/lforces/local.h $S/lforces/local0.h $S/msg.h $S/rnd/dev.h $S/rnd/imp.h $S/utils/cc.h $S/utils/kl.h
$B/main.o: $B/conf.h $S/d/api.h $S/glb.h $S/inc/conf.h $S/mpi/glb.h $S/msg.h $S/sim/int.h
$B/math/linal.o: $S/math/linal.h
$B/mbounce/imp.o: $B/conf.h $S/d/api.h $S/d/ker.h $S/d/q.h $S/inc/conf.h $S/inc/def.h $S/inc/dev.h $S/inc/type.h $S/mbounce/_release/check.h $S/mbounce/bbstates.h $S/mbounce/dbg.h $S/mbounce/dev.h $S/mbounce/gen.h $S/mbounce/gen.intersect.h $S/mbounce/gen.tri.h $S/mbounce/hst.h $S/mbounce/imp.h $S/mbounce/roots.h $S/mpi/glb.h $S/msg.h $S/utils/cc.h $S/utils/kl.h
$B/mcomm/imp.o: $B/conf.h $S/d/api.h $S/d/ker.h $S/d/q.h $S/inc/conf.h $S/inc/def.h $S/inc/dev.h $S/inc/type.h $S/mcomm/dev.h $S/mcomm/fin.h $S/mcomm/imp.h $S/mcomm/ini.h $S/mcomm/type.h $S/mpi/glb.h $S/mpi/type.h $S/mpi/wrapper.h $S/msg.h $S/utils/cc.h $S/utils/kl.h $S/utils/mc.h
$B/mcomm/int.o: $S/algo/minmax.h $B/conf.h $S/d/api.h $S/inc/conf.h $S/inc/def.h $S/inc/dev.h $S/inc/tmp/pinned.h $S/inc/type.h $S/mcomm/imp.h $S/mcomm/int.h $S/mcomm/type.h $S/mpi/basetags.h $S/msg.h $S/utils/cc.h
$B/mdstr/imp.o: $B/conf.h $S/d/api.h $S/inc/conf.h $S/inc/def.h $S/inc/dev.h $S/inc/type.h $S/mdstr/dev.h $S/mdstr/imp.h $S/mdstr/ini.h $S/mpi/glb.h $S/mpi/type.h $S/mpi/wrapper.h $S/msg.h $S/utils/cc.h $S/utils/mc.h
$B/mdstr/int.o: $B/conf.h $S/inc/conf.h $S/inc/def.h $S/mdstr/buf.h $S/mdstr/imp.h $S/mdstr/int.h $S/mdstr/tic.h $S/mpi/basetags.h $S/mpi/glb.h $S/mpi/wrapper.h $S/msg.h
$B/mesh/bbox.o: $S/algo/minmax.h $S/inc/type.h $S/mesh/bbox.h
$B/mesh/collision.o: $B/conf.h $S/d/api.h $S/d/ker.h $S/d/q.h $S/inc/conf.h $S/inc/def.h $S/inc/dev.h $S/inc/type.h $S/mesh/collision.h $S/msg.h $S/utils/cc.h $S/utils/kl.h $S/utils/texo.h
$B/mesh/dist.o: $S/inc/type.h $S/mesh/dist.h
$B/mesh/props.o: $S/inc/type.h $S/mesh/props.h
$B/mpi/glb.o: $S/inc/conf.h $S/mpi/glb.h $S/mpi/wrapper.h $S/utils/mc.h
$B/mpi/type.o: $S/inc/conf.h $S/inc/type.h $S/mpi/type.h $S/utils/mc.h
$B/mpi/wrapper.o: $S/mpi/wrapper.h
$B/mrescue.o: $B/conf.h $S/d/api.h $S/d/ker.h $S/d/q.h $S/inc/conf.h $S/inc/def.h $S/inc/dev.h $S/inc/type.h $S/mesh/collision.h $S/mrescue.h $S/msg.h $S/utils/cc.h $S/utils/kl.h $S/utils/texo.h
$B/msg.o: $S/mpi/glb.h $S/msg.h
$B/odstr/halo/imp.o: $B/conf.h $S/d/api.h $S/d/ker.h $S/d/q.h $S/inc/conf.h $S/inc/def.h $S/inc/dev.h $S/inc/macro.h $S/inc/type.h $S/mpi/glb.h $S/msg.h $S/odstr/halo/_release/check.h $S/odstr/halo/common.h $S/odstr/halo/int.h $S/utils/cc.h $S/utils/kl.h
$B/odstr/imp.o: $S/algo/scan/int.h $B/conf.h $S/d/api.h $S/d/ker.h $S/d/q.h $S/dual/int.h $S/dual/type.h $S/frag.h $S/inc/conf.h $S/inc/def.h $S/inc/dev.h $S/inc/dev/common.h $S/inc/dev/read.h $S/inc/dev/write.h $S/inc/macro.h $S/inc/type.h $S/mpi/glb.h $S/mpi/type.h $S/mpi/wrapper.h $S/msg.h $S/odstr/_release/dev/check.h $S/odstr/dev/common.h $S/odstr/dev/gather.h $S/odstr/dev/shift.h $S/odstr/dev/subindex.h $S/odstr/dev/utils.h $S/odstr/halo/int.h $S/odstr/imp.h $S/odstr/imp/buf.h $S/odstr/imp/fin.h $S/odstr/imp/ini.h $S/odstr/imp/mpi.h $S/odstr/imp/mpi.ii.h $S/odstr/type.h $S/utils/cc.h $S/utils/kl.h
$B/odstr/int.o: $S/algo/scan/int.h $S/clist/int.h $B/conf.h $S/d/api.h $S/d/ker.h $S/d/q.h $S/dual/type.h $S/flu/int.h $S/inc/conf.h $S/inc/def.h $S/inc/dev.h $S/inc/dev/index.h $S/inc/dev/read.h $S/inc/type.h $S/mpi/basetags.h $S/mpi/type.h $S/mpi/wrapper.h $S/msg.h $S/odstr/com.h $S/odstr/imp.h $S/odstr/int.h $S/odstr/type.h $S/rnd/imp.h $S/utils/cc.h $S/utils/kl.h
$B/rbc/imp.o: $B/conf.h $S/d/api.h $S/d/ker.h $S/glb.h $S/inc/conf.h $S/inc/def.h $S/inc/dev.h $S/inc/tmp/pinned.h $S/inc/tmp/wrap.h $S/inc/type.h $S/io/off.h $S/io/rbc.h $S/io/restart.h $S/math/float3.h $S/mpi/glb.h $S/mpi/wrapper.h $S/msg.h $S/params/rbc.inc0.h $S/rbc/imp.h $S/rbc/imp/dev.h $S/rbc/imp/dev0.h $S/rbc/imp/ic.h $S/rbc/imp/imp.h $S/utils/cc.h $S/utils/kl.h $S/utils/te.h $S/utils/texo.h
$B/rbc/int.o: $B/conf.h $S/d/api.h $S/d/ker.h $S/glb.h $S/inc/conf.h $S/inc/def.h $S/inc/dev.h $S/inc/tmp/pinned.h $S/inc/type.h $S/mpi/basetags.h $S/msg.h $S/params/rbc.inc0.h $S/rbc/imp.h $S/rbc/int.h $S/rbc/int/imp.h $S/utils/cc.h $S/utils/texo.h
$B/rdstr/imp.o: $S/algo/minmax.h $B/conf.h $S/d/api.h $S/d/ker.h $S/d/q.h $S/inc/conf.h $S/inc/def.h $S/inc/dev.h $S/inc/type.h $S/mdstr/buf.h $S/mdstr/gen.h $S/mpi/glb.h $S/mpi/type.h $S/mpi/wrapper.h $S/msg.h $S/rdstr/dev.h $S/rdstr/imp.h $S/utils/cc.h $S/utils/kl.h $S/utils/mc.h
$B/rdstr/int.o: $B/conf.h $S/d/api.h $S/d/ker.h $S/inc/conf.h $S/inc/def.h $S/inc/dev.h $S/inc/tmp/pinned.h $S/inc/type.h $S/mdstr/buf.h $S/mdstr/int.h $S/mdstr/tic.h $S/mpi/basetags.h $S/mpi/glb.h $S/mpi/wrapper.h $S/msg.h $S/rdstr/imp.h $S/rdstr/int.h $S/utils/cc.h $S/utils/texo.h
$B/rig/imp.o: $B/conf.h $S/d/api.h $S/d/ker.h $S/inc/conf.h $S/inc/def.h $S/inc/dev.h $S/inc/type.h $S/io/ply.h $S/io/restart.h $S/mesh/bbox.h $S/mesh/collision.h $S/mesh/dist.h $S/mpi/glb.h $S/mpi/type.h $S/mpi/wrapper.h $S/msg.h $S/rig/ic.h $S/rig/imp.h $S/rig/ini.h $S/rig/share.h $S/rigid/int.h $S/utils/cc.h $S/utils/mc.h $S/utils/texo.h
$B/rig/int.o: $B/conf.h $S/d/api.h $S/inc/conf.h $S/inc/def.h $S/inc/dev.h $S/inc/type.h $S/mpi/glb.h $S/msg.h $S/rig/imp.h $S/rig/int.h $S/utils/cc.h
$B/rigid/imp.o: $B/conf.h $S/inc/conf.h $S/inc/dev.h $S/inc/type.h $S/math/linal.h $S/mesh/props.h $S/rigid/_cuda/dev.h $S/rigid/_cuda/imp.h $S/rigid/common.h $S/rigid/int.h $S/rigid/utils.h $S/utils/kl.h
$B/rnd/imp.o: $S/rnd/imp.h
$B/sdf/imp.o: $B/conf.h $S/d/api.h $S/d/ker.h $S/d/q.h $S/field.h $S/glb.h $S/inc/conf.h $S/inc/def.h $S/inc/dev.h $S/inc/dev/wvel.h $S/inc/macro.h $S/inc/type.h $S/mpi/glb.h $S/msg.h $S/sdf/cheap.dev.h $S/sdf/dev.h $S/sdf/imp.h $S/sdf/type.h $S/utils/cc.h $S/utils/kl.h
$B/sdf/int.o: $B/conf.h $S/d/api.h $S/d/ker.h $S/inc/conf.h $S/inc/def.h $S/inc/dev.h $S/inc/macro.h $S/inc/type.h $S/mpi/glb.h $S/msg.h $S/sdf/imp.h $S/sdf/int.h $S/sdf/type.h $S/utils/cc.h
$B/sim/imp.o: $S/algo/scan/int.h $S/bbhalo.decl.h $S/bbhalo.impl.h $S/clist/int.h $S/cnt/int.h $B/conf.h $S/d/api.h $S/d/ker.h $S/d/q.h $S/dbg/imp.h $S/dpdr/int.h $S/dpdr/type.h $S/dual/int.h $S/dual/type.h $S/field.h $S/flu/int.h $S/forces/imp.h $S/forces/type.h $S/frag.h $S/fsi/int.h $S/glb.h $S/inc/conf.h $S/inc/def.h $S/inc/dev.h $S/inc/dev/common.h $S/inc/dev/index.h $S/inc/dev/read.h $S/inc/dev/write.h $S/inc/tmp/pinned.h $S/inc/tmp/wrap.h $S/inc/type.h $S/inter/int.h $S/io/bop/imp.h $S/io/diag.h $S/io/field.h $S/io/off.h $S/io/rbc.h $S/io/restart.h $S/io/rig.h $S/lforces/local.h $S/lforces/x/dev.h $S/lforces/x/imp.h $S/mbounce/imp.h $S/mcomm/int.h $S/mcomm/type.h $S/mdstr/buf.h $S/mdstr/int.h $S/mdstr/tic.h $S/mesh/bbox.h $S/mesh/collision.h $S/mpi/basetags.h $S/mpi/glb.h $S/mpi/type.h $S/mpi/wrapper.h $S/mrescue.h $S/msg.h $S/odstr/int.h $S/odstr/type.h $S/rbc/int.h $S/rdstr/int.h $S/rig/int.h $S/rigid/int.h $S/rnd/dev.h $S/rnd/imp.h $S/sdf/int.h $S/sdf/type.h $S/sdstr/dec.h $S/sdstr/dev.h $S/sdstr/imp.h $S/sdstr/templ.h $S/sim/0dev/bounce.h $S/sim/0dev/update.h $S/sim/0hst/bounce.h $S/sim/0hst/distr.h $S/sim/0hst/update.h $S/sim/_release/0dev/distr.h $S/sim/_release/force/common.h $S/sim/_release/force/dev.h $S/sim/_release/force/dpd.h $S/sim/_release/force/imp.h $S/sim/_release/step.h $S/sim/_release/update.h $S/sim/colors.h $S/sim/dec.h $S/sim/dev.h $S/sim/dump.h $S/sim/fin.h $S/sim/imp.h $S/sim/ini.h $S/sim/int.h $S/sim/odstr/none.h $S/sim/odstr/release.h $S/sim/odstr/safe.h $S/sim/rbc.h $S/sim/run.h $S/sim/scheme/euler.h $S/sim/scheme/vv.h $S/sim/type.h $S/tcells/int.h $S/utils/cc.h $S/utils/kl.h $S/utils/mc.h $S/utils/te.h $S/utils/texo.h $S/wall/int.h $S/x/int.h
$B/tcells/imp.o: $S/algo/scan/int.h $B/conf.h $S/d/api.h $S/d/ker.h $S/d/q.h $S/inc/conf.h $S/inc/def.h $S/inc/dev.h $S/inc/type.h $S/msg.h $S/tcells/int.h $S/utils/cc.h $S/utils/kl.h
$B/tcells/int.o: $S/algo/scan/int.h $B/conf.h $S/d/api.h $S/inc/conf.h $S/inc/def.h $S/inc/dev.h $S/inc/type.h $S/msg.h $S/tcells/imp.h $S/tcells/int.h $S/utils/cc.h
$B/utils/cc.o: $B/conf.h $S/d/api.h $S/inc/conf.h $S/msg.h $S/utils/cc/common.h
$B/utils/mc.o: $B/conf.h $S/inc/conf.h $S/utils/mc.h
$B/utils/os.o: $S/utils/os.h
$B/wall/exch.o: $B/conf.h $S/inc/conf.h $S/inc/type.h $S/mpi/glb.h $S/mpi/wrapper.h
$B/wall/imp.o: $S/clist/int.h $B/conf.h $S/d/api.h $S/d/ker.h $S/d/q.h $S/forces/imp.h $S/forces/pack.h $S/forces/type.h $S/glb.h $S/inc/conf.h $S/inc/def.h $S/inc/dev.h $S/inc/dev/wvel.h $S/inc/macro.h $S/inc/type.h $S/io/restart.h $S/msg.h $S/rnd/dev.h $S/rnd/imp.h $S/sdf/cheap.dev.h $S/sdf/int.h $S/sdf/type.h $S/utils/cc.h $S/utils/kl.h $S/utils/te.h $S/utils/texo.h $S/wall/dev.h $S/wall/exch.h $S/wall/imp.h $S/wall/strt.h
$B/wall/int.o: $S/clist/int.h $B/conf.h $S/d/api.h $S/d/ker.h $S/inc/conf.h $S/inc/def.h $S/inc/dev.h $S/inc/type.h $S/mpi/glb.h $S/msg.h $S/rnd/imp.h $S/sdf/int.h $S/sdf/type.h $S/utils/cc.h $S/utils/texo.h $S/wall/imp.h $S/wall/int.h
$B/x/imp.o: $S/algo/scan/int.h $S/clist/int.h $S/cnt/int.h $B/conf.h $S/d/api.h $S/d/ker.h $S/d/q.h $S/dbg/imp.h $S/dual/int.h $S/dual/type.h $S/field.h $S/flu/int.h $S/forces/imp.h $S/forces/type.h $S/frag.h $S/fsi/int.h $S/glb.h $S/inc/conf.h $S/inc/def.h $S/inc/dev.h $S/inc/dev/common.h $S/inc/dev/index.h $S/inc/dev/read.h $S/inc/dev/write.h $S/inc/tmp/pinned.h $S/inc/tmp/wrap.h $S/inc/type.h $S/mcomm/int.h $S/mcomm/type.h $S/mdstr/buf.h $S/mdstr/int.h $S/mdstr/tic.h $S/mpi/basetags.h $S/mpi/glb.h $S/mpi/type.h $S/mpi/wrapper.h $S/msg.h $S/odstr/int.h $S/odstr/type.h $S/rbc/int.h $S/rdstr/int.h $S/rex/copy.h $S/rex/decl.h $S/rex/dev/common.h $S/rex/dev/decl.h $S/rex/dev/pack.h $S/rex/dev/scan.h $S/rex/dev/scatter.h $S/rex/dev/type.h $S/rex/dev/unpack.h $S/rex/dev/x.h $S/rex/ini.h $S/rex/pack.h $S/rex/recv.h $S/rex/scan.h $S/rex/send.h $S/rex/type.h $S/rex/unpack.h $S/rex/wait.h $S/rnd/dev.h $S/rnd/imp.h $S/sdf/int.h $S/sdf/type.h $S/sim/int.h $S/utils/cc.h $S/utils/kl.h $S/utils/mc.h $S/utils/te.h $S/utils/texo.h $S/wall/int.h $S/x/decl.h $S/x/fin.h $S/x/imp.h $S/x/ini.h $S/x/ticketcom.h $S/x/ticketpack.h $S/x/ticketpinned.h $S/x/ticketr.h $S/x/tickettags.h $S/x/type.h
