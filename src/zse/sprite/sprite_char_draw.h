#ifndef ZAKAROUF_ZSE__SPRITE_CHAR_DRAW_n_MANIPULATE_H
#define ZAKAROUF_ZSE__SPRITE_CHAR_DRAW_n_MANIPULATE_H

#include "sprite_char_def.h"

void zse_sprite__sCharDraw_circle (zse_T_Sprite_sChar *spr ,z__Vint3 on , z__i32 r, zset__spritechtype val, z__u16 color);
void zse_sprite__sChar_swapColors(zse_T_Sprite_sChar *spr, z__u32 frame ,z__i32 targetColo, z__i32 colorCode);

void zse_sprite__sChar_copyFrame(zse_T_Sprite_sChar *spr, z__u32 from, z__u32 to);

#endif
