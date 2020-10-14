#include "../common.h"
#include "../sprite/sprite_lib.h"

#include "color.h"

void zse_rs_sprite_print(SPRITES_t *spr, int frame)
{
	for (int i = 0; i < spr->Y; ++i)
	{
		for (int j = 0; j < spr->X; ++j)
		{
			zse_rs_color256Fg_set(spr->plot[getindex3d(i, j, frame, spr->X, spr->Y)]>>8);
			putc(spr->plot[getindex3d(i, j, frame, spr->X, spr->Y)]&0xFF, stdout);
		}
		putc('\n', stdout);
	}

}
