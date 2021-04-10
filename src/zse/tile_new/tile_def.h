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


struct zset__Stile
{
    char name[32];
    z__u8 mapSymb;
    z__u32 attr;

};

typedef struct _zse_tile__tileset
{
    struct zset__Stile *tiles;
    z__i32 *tileTextureIDs;
    z__i32 tileCount;
} zset__Tileset;

#define ZSE_tile__checkAttributeRAW(n, attr) ((n)&(attr))
#define ZSE_tile__checkAttributeTILE(tile, attr) ((tile).attr&(attr))
#define ZSE_tile__checkAttributeTILESET(tileset,n, attr) (tileset.tiles[n].attr&(attr))

#define ZSE_tile__setAttributeRAW(n, attr) { n |= attr }
#define ZSE_tile__setAttributeTILE(tile, attr) { (tile).attr |= attr }
#define ZSE_tile__setAttributeTILESET(tileset, n, attr) { tileset.tiles[n].attr |= attr }

#define ZSE_tile__switchAttributeRAW(n, attr) { n ^= attr }
#define ZSE_tile__switchAttributeTILE(tile, attr) { (tile).attr ^= attr }
#define ZSE_tile__switchAttributeTILESET(tileset, n, attr) { tileset.tiles[n].attr ^= attr }

#endif
