#include "../../common.h"
#include "../../sprite/sprite_char_def.h"

#include "render_tisk_color.h"
#include <stdio.h>

void zse_rtT__spriteChar__print(const zset__SpriteChar *spr, int frame)
{
	for (int i = 0; i < spr->x; ++i)
	{
		for (int j = 0; j < spr->y; ++j)
		{
			zse_rtT__color256Fg_set(spr->colormap[zse_xyz3Dto1D(i, j, frame, spr->x, spr->y)]);
			putc(spr->plot[zse_xyz3Dto1D(i, j, frame, spr->x, spr->y)]&0xff, stdout);
		}
		putc('\n', stdout);
	}
}
