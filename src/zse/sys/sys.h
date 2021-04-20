#ifndef ZSE_SYSTEM_H
#define ZSE_SYSTEM_H

#include "../common.h"

int zse_sys_formatCheck(char version[]);

// Data Manipulation
#define zse_sys__draw_box_u8_fill1z(arr, boundx, boundy, startx, starty, atz ,endx, endy, val)\
	{ for(int y = starty; y < endy; ++y) memset(&arr[zse_xyz3Dto1D(startx, y, atz, boundx, boundy)], val, sizeof(*arr)*endx); }

#endif
