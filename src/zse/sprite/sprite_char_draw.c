#include "sprite_char_draw.h"

void zse_sprite__sCharDraw_circle (zset__SpriteChar *spr ,z__Vint3 on , z__i32 r, zset__spritechtype val, z__u8 color)
{
	z__i32 i = on.y - r;
	z__i32 end_i = on.y + r + 1;
	z__i32 end_j = on.x + r + 1;

	if(i < 0) {
		i = 0;
	}
	if (end_i >= spr->y) {
		end_i = spr->y;
	}
	if(end_j >= spr->x) {
		end_j = spr->x;
	}
	
	z__i32 tmp_j = (on.x - r < 0)? 0: on.x - r;

    for (; i < end_i; ++i) {
    	int j = tmp_j;

        for (; j < end_j ; ++j) {

            if( ((j - on.x) * (j - on.x) + (i - on.y) * (i - on.y)) <= r * r ) {
                	spr->plot[zse_xyz3Dto1D(j, i, on.z, spr->x, spr->y)] = val;
                	spr->colormap[zse_xyz3Dto1D(j, i, on.z, spr->x, spr->y)] = color;
            }
        }
    }
}

void zse_sprite__sChar_swapColors(zset__SpriteChar *spr, z__u32 frame ,z__i32 targetColo, z__i32 colorCode)
{
    for (int i = 0; i < spr->x * spr->y; ++i)
    {
        if(ZSE_sprite__sChar_getColor(spr[0], i, 0, frame) == targetColo) {
        	ZSE_sprite__sChar_getColor(spr[0], i, 0, frame) = colorCode;
        }
    }
}
