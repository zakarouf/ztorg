#ifndef Z_RENDER_LIB_H
#define Z_RENDER_LIB_H

#include "map_lib.h"
#include <ncurses.h>



void r_init();
void r_exit();

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

#endif
