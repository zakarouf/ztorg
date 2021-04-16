#include "../../common.h"
#include "../../sprite/sprite_char_def.h"

#include "tisk_color.h"
#include <stdio.h>

void zse_rtT__spriteChar__print(const zset__SpriteChar *spr, int frame)
{
	zset__spritechtype *plot = &spr->plot[zse_xyz3Dto1D(0, 0, frame, spr->x, spr->y)];
	z__u16 *color = &spr->colormap[zse_xyz3Dto1D(0, 0, frame, spr->x, spr->y)];
	for (int i = 0; i < spr->x; ++i)
	{
		for (int j = 0; j < spr->y; ++j, color++,plot++)
		{
			zse_rtT__color256Fg_set(*color&0xff);
			zse_rtT__color256Bg_set(*color >> 8);
			putc(*plot, stdout);
		}
		putc('\n', stdout);
	}
}
