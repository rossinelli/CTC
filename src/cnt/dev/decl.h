enum {
    XOFFSET = XS / 2,
    YOFFSET = YS / 2,
    ZOFFSET = ZS / 2
};

namespace c { /* common */
texture<int, cudaTextureType1D> starts, id;
// __constant__ float *FF[MAX_OBJ_TYPES];
}
