#ifndef ZSE_RENDER__CURSES_TERMINAL_ALIAS_H
#define ZSE_RENDER__CURSES_TERMINAL_ALIAS_H

#include <ncurses/ncurses.h>

#define zse_rtC_L__printw    printw
#define zse_rtC_L__mvprintw  mvprintw
#define zse_rtC_L__mvwprintw mvwprintw

#define zse_rtC_L__getch 	getch
#define zse_rtC_L__wgetch 	wgetch
#define zse_rtC_L__mvwgetch mvwgetch

#define zse_rtC_L__addch 	addch
#define zse_rtC_L__waddch 	waddch
#define zse_rtC_L__mvwaddch mvwaddch

#define zse_rtC_L__scanw    scanw
#define zse_rtC_L__mvscanw  mvscanw
#define zse_rtC_L__mvwscanw mvwscanw

#define zse_rtC_L__addstr    addstr
#define zse_rtC_L__waddstr   waddstr
#define zse_rtC_L__mvwaddstr mvwaddstr

#define zse_rtC_L__attron 	attron
#define zse_rtC_L__attroff 	attroff
#define zse_rtC_L__attrset 	attrset
#define zse_rtC_L__wattrset wattrset

#define zse_rtC_L__noecho noecho
#define zse_rtC_L__raw raw

typedef WINDOW zset_rtC_L_WINDOW;
typedef chtype zset_rtC_L_chtype;

#endif