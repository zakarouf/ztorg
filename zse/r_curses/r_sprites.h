#ifndef ZSE_RENDER_SPRITES_H
#define ZSE_RENDER_SPRITES_H

#include "r_lib.h"

#include "../sprites/sprites_lib.h"

int zse_render_sprite
(
	WINDOW *win,
	int startX,
	int startY,
	SPRITES_t* spr,
	int startframe,
	int endframe
);

#endif