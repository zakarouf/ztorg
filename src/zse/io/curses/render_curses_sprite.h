#ifndef ZSE_RENDER_SPRITES_H
#define ZSE_RENDER_SPRITES_H

#include "curses.h"

#include "../../sprite/sprite_lib.h"

int zse_rtC_spritePrintAll
(
	WINDOW *win,
	int startX,
	int startY,
	SPRITES_t* spr,
	int startframe,
	int endframe
);

void zse_rtC_spritePrintf
(
	WINDOW *win,
	int startX,
	int startY,
	SPRITES_t* spr,
	const int atframe
);

int zse_rtC_spriteSmooth(float pos, float slength);

#endif