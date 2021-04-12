#ifndef ZSE_COLOR_H
#define ZSE_COLOR_H

#include "curses_alias.h"

#define zse_rtC__setcolor_MF(x) 		      attron(COLOR_PAIR(x))
#define zse_rtC__createcolor_MF(at, r, g, b)  init_color(at, r, g, b)


int zse_rtC_colors_test_showall(WINDOW *win, int atx, int aty);
int zse_rtC_color_initpairs(void);

#endif
