#ifndef Z_RENDER_LIB_H
#define Z_RENDER_LIB_H

#include <ncurses/ncurses.h>
#include "../colors/colors.h"

int zse_r_init();
void zse_r_exit();


int zse_getint();
int zse_getint_printw_option(char str[]);
int zse_r_selectListS(WINDOW *win, int x, int y, char **list, int listsize, char *getname);

#endif
