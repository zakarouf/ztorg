#ifndef ZSE_RENDER_CURSES_TERMINAL_H
#define ZSE_RENDER_CURSES_TERMINAL_H

#include "curses_def.h"
#include "curses_color.h"

int zse_rtC_init();
void zse_rtC_exit();


int zse_rtC__getint(WINDOW *win);
int zse_rtC__msgGetint(WINDOW *win, char const msg[]);
int zse_rtC__mvmsgGetint(WINDOW *win, int y, int x, char const msg[]);
int zse_rtC__selectListS(
	  WINDOW *win
	, int x, int y
	, char const **list, int const listsize
	, char *getstringS, int stringSize);
void zse_rtC__clearPortion(WINDOW *win, int x, int y, int uptoX, int uptoY);

void zse_rtC__drawHorizortalGraphRuler_nocheck(
	  WINDOW *win
	, z__u32 at_x
	, z__u32 at_y
	, z__u32 upto_x
	, z__f32 ruler_x
	, z__f32 ruler_increment
	, z__u32 rulerGap);

void zse_rtC__drawVerticalGraphRuler_nocheck(
      WINDOW *win
    , z__u32 at_x
    , z__u32 at_y
    , z__u32 upto_y
    , z__f32 ruler_y
    , z__f32 ruler_increment
    , z__u32 rulerGap
);

#endif
