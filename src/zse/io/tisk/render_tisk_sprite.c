#include "../../common.h"
#include "../../sprite/sprite_lib.h"

#include "render_tisk_color.h"
#include <stdio.h>

void zse_rtT_sprite_print(SPRITES_t *spr, int frame)
{
	for (int i = 0; i < spr->Y; ++i)
	{
		for (int j = 0; j < spr->X; ++j)
		{
			zse_rtT__color256Fg_set(spr->plot[zse_xyz3Dto1D(i, j, frame, spr->X, spr->Y)]>>8);
			putc(spr->plot[zse_xyz3Dto1D(i, j, frame, spr->X, spr->Y)]&0xFF, stdout);
		}
		putc('\n', stdout);
	}

}
