D = @d () { test -d "$$1" || mkdir -p -- "$$1"; } && \
    d $B/algo       && \
    d $B/algo/scan  && \
    d $B/clist      && \
    d $B/cnt        && \
    d $B/d          && \
    d $B/dbg        && \
    d $B/dpdr       && \
    d $B/dual       && \
    d $B/flu        && \
    d $B/fsi        && \
    d $B/hforces    && \
    d $B/inter      && \
    d $B/io         && \
    d $B/io/bop     && \
    d $B/lforces    && \
    d $B/math       && \
    d $B/mbounce    && \
    d $B/mcomm      && \
    d $B/mdstr      && \
    d $B/mesh       && \
    d $B/mpi        && \
    d $B/odstr      && \
    d $B/odstr/halo && \
    d $B/rbc        && \
    d $B/rdstr      && \
    d $B/rig        && \
    d $B/rigid      && \
    d $B/rnd        && \
    d $B/sdf        && \
    d $B/sim        && \
    d $B/tcells     && \
    d $B/utils      && \
    d $B/wall       && \
    d $B/x         
