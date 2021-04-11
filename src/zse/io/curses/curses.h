#ifndef Z_RENDER_LIB_H
#define Z_RENDER_LIB_H


#include <ncurses/ncurses.h>
#include "curses_color.h"

int zse_rtC_init();
void zse_rtC_exit();


int zse_rtC_getint();
int zse_rtC_getint_printw_option(char str[]);
int zse_rtC_selectListS(WINDOW *win, int x, int y, char **list, int listsize, char *getname);
void zse_rtC_clearPortion(WINDOW *win, int x, int y, int uptoX, int uptoY);

#endif
