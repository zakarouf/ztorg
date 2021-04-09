#ifndef ZAKAROUF_ZSE__SPRITE_CHAR_H
#define ZAKAROUF_ZSE__SPRITE_CHAR_H

#include "sprite_char_def.h"

void zse_sprite__sChar_export(const zset__SpriteChar *spr ,const char filename[ static 1 ]);
zset__SpriteChar zse_sprite__sChar_load(const char filename[ static 1 ]);

zset__SpriteChar zse_sprite__sChar_createEmpty(z__u16 x, z__u16 y, z__u16 frames, z__float dt, z__u16 seqCount);
void zse_sprite__sChar_delete(zset__SpriteChar *spr);

#endif