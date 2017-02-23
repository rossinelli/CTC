enum {
  XSIZE_WALLCELLS = 2 * XMARGIN_WALL + XSIZE_SUBDOMAIN,
  YSIZE_WALLCELLS = 2 * YMARGIN_WALL + YSIZE_SUBDOMAIN,
  ZSIZE_WALLCELLS = 2 * ZMARGIN_WALL + ZSIZE_SUBDOMAIN,

  XTEXTURESIZE = 256,
  _YTEXTURESIZE = ((YSIZE_SUBDOMAIN + 2 * YMARGIN_WALL) * XTEXTURESIZE +
		   XSIZE_SUBDOMAIN + 2 * XMARGIN_WALL - 1) /
  (XSIZE_SUBDOMAIN + 2 * XMARGIN_WALL),

  YTEXTURESIZE = 16 * ((_YTEXTURESIZE + 15) / 16),
  _ZTEXTURESIZE = ((ZSIZE_SUBDOMAIN + 2 * ZMARGIN_WALL) * XTEXTURESIZE +
		   XSIZE_SUBDOMAIN + 2 * XMARGIN_WALL - 1) /
  (XSIZE_SUBDOMAIN + 2 * XMARGIN_WALL),
  ZTEXTURESIZE = 16 * ((_ZTEXTURESIZE + 15) / 16),
};

namespace Wall {
  Logistic::KISS* trunk;

  int solid_size;
  float4 *solid4;
  cudaArray *arrSDF;
  CellLists *wall_cells;
}
