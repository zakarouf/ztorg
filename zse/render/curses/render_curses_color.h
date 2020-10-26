#ifndef ZSE_COLOR_H
#define ZSE_COLOR_H

#include "curses.h"

#define zse_setcolor(x) attron(COLOR_PAIR(x))
#define zse_createcolor(at, r, g, b) init_color(at, r, g, b)


int zse_colors_test_showall(WINDOW *win, int atx, int aty);
int zse_r_color_initpairs(void);

#endif