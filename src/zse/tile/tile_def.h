#ifndef ZAKAROUF_ZSE__TILE_DEFINATION_H
#define ZAKAROUF_ZSE__TILE_DEFINATION_H

#include "../common.h"

typedef enum {
      ZSE_TILE__ATTR_NULL               = 0
    , ZSE_TILE__ATTR_IS_opaque          = 1 << 0
    , ZSE_TILE__ATTR_IS_block           = 1 << 1
    , ZSE_TILE__ATTR_IS_moveable        = 1 << 2
    , ZSE_TILE__ATTR_IS_destructable    = 1 << 3
    , ZSE_TILE__ATTR_IS_liquid          = 1 << 4
    , ZSE_TILE__ATTR_IS_toxic           = 1 << 5
    , ZSE_TILE__ATTR_IS_floor           = 1 << 6
} zset__E_tileAttributes;

typedef z__Vector(z__f32, x, y, height, width) z__Rectangal;

struct zset__Stile
{
    char name[32];
    z__u8 mapSymb;
    z__u32 attr;
    z__Arr(
        struct {
            z__Vint2 size;
            z__Vint2 id;
            z__Vector2 offset;
        }
    ) textures;
};

typedef struct {
    z__Arr(struct zset__Stile) tiles;
    //z__Vint2 unittex_size;
} zse_T_Tileset;



#define ZSE_tile__checkAttributeRAW(n, attr) ((n)&(attr))
#define ZSE_tile__checkAttributeTILE(tile, attr1) ((tile).attr&(attr1))
#define ZSE_tile__checkAttributeTILESET(tileset,n, attr1) ((tileset).tiles[n].attr&(attr1))

#define ZSE_tile__setAttributeRAW(n, attr) { n |= attr }
#define ZSE_tile__setAttributeTILE(tile, attr1) { (tile).attr |= attr1 }
#define ZSE_tile__setAttributeTILESET(tileset, n, attr1) { tileset.tiles[n].attr |= attr1 }

#define ZSE_tile__switchAttributeRAW(n, attr) { n ^= attr }
#define ZSE_tile__switchAttributeTILE(tile, attr1) { (tile).attr ^= attr1 }
#define ZSE_tile__switchAttributeTILESET(tileset, n, attr1) { tileset.tiles[n].attr ^= attr1 }

#endif
