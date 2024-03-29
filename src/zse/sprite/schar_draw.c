#include <string.h>
#include "schar_draw.h"

void zse_sprite__sCharDraw_circle (zse_T_Sprite_sChar *spr ,z__Vint3 on , z__i32 r, zset__spritechtype val, z__u16 color)
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

void zse_sprite__sChar_swapColors(zse_T_Sprite_sChar *spr, z__u32 frame ,z__i32 targetColo, z__i32 colorCode)
{
    z__u16 *plot = &spr->colormap[zse_xyz3Dto1D(0, 0, frame, spr->x, spr->y)];
    for (int i = 0; i < (spr->x * spr->y); ++i)
    {
        
        if(*plot == targetColo) {
        	*plot = colorCode;
        }
        plot += 1;

    }
}
inline void zse_sprite__sChar_copyFrame(zse_T_Sprite_sChar *spr, z__u32 from, z__u32 to)
{
    memcpy(&spr->plot[zse_xyz3Dto1D(0, 0, to, spr->x, spr->y)]
         , &spr->plot[zse_xyz3Dto1D(0, 0, from, spr->x, spr->y)]
         , sizeof(*spr->plot) * spr->x * spr->y);

    memcpy(&spr->colormap[zse_xyz3Dto1D(0, 0, to, spr->x, spr->y)]
         , &spr->colormap[zse_xyz3Dto1D(0, 0, from, spr->x, spr->y)]
         , sizeof(*spr->colormap) * spr->x * spr->y);
}

