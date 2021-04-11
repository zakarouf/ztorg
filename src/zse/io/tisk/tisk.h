#ifndef ZSE_RENDER_TISK_TERMINAL_H
#define ZSE_RENDER_TISK_TERMINAL_H


#include "../../common.h"

#include "tisk_def.h"
#include "tisk_color.h"
#include "tisk_io.h"

#define zse_rtT__getmaxx() 300
#define zse_rtT__getmaxy() 90

void zse_rtT__D_setCur(int x, int y);
void zse_rtT__D_set00(void);

void zse_rtT__init(void);
void zse_rtT__exit(void);

void zse_rtT__D_showCursor(void);
void zse_rtT__D_hideCursor(void);

#endif
