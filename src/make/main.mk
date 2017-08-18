# a fragment of makefile
# see src/make/ and tools/udeps
# B: binary dir
# S: source dir
#
# O: list of objects

# commands
# D: create directories
# N: nvcc compile
# NN: special nvcc compile command
# X: c++ compile
# L: link

NVCC     ?= nvcc
ARCH     ?= -arch compute_35 -code sm_35
OPT	     ?= -O2 -g

CXXFLAGS  +=  -I$B -I$S
COMMON     =  -std=c++11 ${OPT}
NCFLAGS    =           $(CXXFLAGS)
XCFLAGS    = $(COMMON) $(CXXFLAGS)
NVCCFLAGS += $(COMMON) -use_fast_math 
LIBS      += -lcudart

N  = $(NVCC)  $(ARCH) $(NVCCFLAGS) --compiler-options '$(NCFLAGS)' -dc $< -c -o $@
X  = $(NVCC)  $(ARCH)              --compiler-options '$(XCFLAGS)'     $< -c -o $@
NN = $(NVCC)  $(ARCH) $(NVCCFLAGS) --compiler-options '$(NCFLAGS)' -dc $< -c -o $@
L  = $(NVCC)  $(ARCH) -dlink $O $(NVCCLIBS) -o $B/gpuCode.o && \
	$(LINK)  $B/gpuCode.o $O $(LIBS) -o $@

$B/udx: $O; $L
$O:  $B/.cookie
$B/.cookie:;       $D ; touch $@

# special rules
# $B/glb.o: $S/glb.cu; $(NN)
# $B/bund.o: $S/bund.cu; $(NN)
clean:; -rm -f $B/udx $O $B/gpuCode.o $B/.cookie

.PHONY = clean all D
