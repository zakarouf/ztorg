#ifndef ZSE_RENDER_SPRITES_H
#define ZSE_RENDER_SPRITES_H

#include "curses.h"

#include "../../sprite/sprite_char_def.h"

int zse_rtC_spritePrintAll
(
	WINDOW *win,
	int startX,
	int startY,
	zset__SpriteChar* spr,
	int startframe,
	int endframe
);

void zse_rtC_sprite__Print
(
	WINDOW *win,
	int startX,
	int startY,
	zset__SpriteChar* spr,
	const int atframe
);

void zse_rtC__sprite__sChar_PrintPadEnd
(
	WINDOW *win,
	int startX,
	int startY,
	int padxend,
	int padyend,
	zset__SpriteChar* spr,
	const int atframe
);

int zse_rtC_spriteSmooth(float pos, float slength);

#endif
