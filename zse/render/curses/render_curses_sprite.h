#ifndef ZSE_RENDER_SPRITES_H
#define ZSE_RENDER_SPRITES_H

#include "curses.h"

#include "../../sprite/sprite_lib.h"

int zse_r_sprite_full
(
	WINDOW *win,
	int startX,
	int startY,
	SPRITES_t* spr,
	int startframe,
	int endframe
);

void zse_r_sprite
(
	WINDOW *win,
	int startX,
	int startY,
	SPRITES_t* spr,
	const int atframe
);

int zse_r_ssmooth(float pos, float slength);

#endif