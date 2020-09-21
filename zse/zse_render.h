#ifndef ZSE_RENDER_MAIN_H
#define ZSE_RENDER_MAIN_H

#include "r_lib.h"
#include "sprites_lib.h"

void r_render_show2dworld
(
	WINDOW *win,
	plotdata_t *chunk,
	const int Xsize,
	const int Ysize,
	const int Zsize,
	int x,
	int y,
	int z,
	const int resizeX,
	const int resizeY
);

int zse_render_sprite
(
	WINDOW *win,
	int startX,
	int startY,
	SPRITES_t* spr,
	int startframe,
	int endframe
);

#endif