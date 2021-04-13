#ifndef ZSE_RENDER_CURSES_TERMINAL_H
#define ZSE_RENDER_CURSES_TERMINAL_H

#include "curses_def.h"
#include "curses_color.h"

int zse_rtC_init();
void zse_rtC_exit();


int zse_rtC__getint(WINDOW *win);
int zse_rtC__msgGetint(WINDOW *win, char const msg[]);
int zse_rtC__mvmsgGetint(WINDOW *win, int y, int x, char const msg[]);
int zse_rtC_selectListS(WINDOW *win, int x, int y, char **list, int listsize, char *getname);
void zse_rtC_clearPortion(WINDOW *win, int x, int y, int uptoX, int uptoY);

#endif
