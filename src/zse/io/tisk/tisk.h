#ifndef ZSE_RENDER_TISK_TERMINAL_H
#define ZSE_RENDER_TISK_TERMINAL_H


#include "../../common.h"

#include "render_tisk_color.h"
#include "render_tisk_sprite.h"
#include "render_tisk_io.h"


#define zse_rtT_getmaxx() 1390
#define zse_rtT_getmaxy() 800

void zse_rtT_init(void);
void zse_rtT_exit(void);

void zse_rtT_showCursor(void);
void zse_rtT_hideCursor(void);
void zse_rtT__setCur(int x, int y);
void zse_rtT__set00(void);

#endif
