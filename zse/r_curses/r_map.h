#ifndef ZSE_RENDER_MAP_H
#define ZSE_RENDER_MAP_H

#include "r_lib.h"
#include "../map/map_lib.h"
#include "../tile/tile_lib.h"

void r_render_show2dworld
(
	WINDOW *win,
	TILE_t *t,
	plotdata_t *chunk,
	const int Xsize,
	const int Ysize,
	const int Zsize,
	int x,
	int y,
	int z,
	const int resizeX,
	const int resizeY,
	char scale_
);

#endif