namespace k_cnt {
enum {
    XCELLS = XS,
    YCELLS = YS,
    ZCELLS = ZS,
    XOFFSET = XCELLS / 2,
    YOFFSET = YCELLS / 2,
    ZOFFSET = ZCELLS / 2
};
texture<int, cudaTextureType1D> texCellsStart, texCellEntries;

namespace g {
__constant__ int ns[MAX_OBJ_TYPES];
__constant__ const float2 *csolutes[MAX_OBJ_TYPES];
__constant__ float *csolutesacc[MAX_OBJ_TYPES];

__constant__ int starts[27], counts[26];
__constant__ Particle *pp[26];
__constant__ Force *ff[26];
}
}
