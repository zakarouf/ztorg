#include <string.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

#include "tile_def.h"

static struct zset__Stile* _tiles_getdefault(z__i32 *tileCount)
{
    enum {MaxTiles = 8};
    struct zset__Stile *tiles = z__MALLOC(sizeof(*tiles) * MaxTiles);

    char tile_desc[MaxTiles][16] = {
            {"Floor/Space"},
            {"WALL"},
            {"WALL_MOVEABLE"},
            {"WALL_BREAKABLE"},
            {"WALL_INVISIBLE"},
            {"FLOOR_TOXIC"},
            {"FLOOR_WATER"},
            {"FLOOR_NULL"},
        };

    z__u32 attr[MaxTiles] = {

        0,                                                                                      // 000 AIR
        ZSE_TILE__ATTR_IS_opaque | ZSE_TILE__ATTR_IS_block,                                     // 001 WALL 
        ZSE_TILE__ATTR_IS_moveable | ZSE_TILE__ATTR_IS_block | ZSE_TILE__ATTR_IS_opaque,        // 002 WALL_MOVEABLE
        ZSE_TILE__ATTR_IS_destructable | ZSE_TILE__ATTR_IS_block |ZSE_TILE__ATTR_IS_opaque,     // 003 WALL_BREAKABLE
        ZSE_TILE__ATTR_IS_block,                                                                // 004 WALL_INVISIBLE
        ZSE_TILE__ATTR_IS_toxic | ZSE_TILE__ATTR_IS_floor,                                      // 005 FLOOR_TOXIC
        ZSE_TILE__ATTR_IS_liquid | ZSE_TILE__ATTR_IS_floor,                                     // 006 FLOOL_WATER
        ZSE_TILE__ATTR_IS_floor,                                                                // 007 FLOOR_NULL
    };

    uint8_t 
        symb[MaxTiles] = 
        {' ', '#', '&', '*', '\\', '%', '~', '.'};

    for(int i = 0; i < MaxTiles; i++)
        {
            sprintf(tiles[i].name,"%s", tile_desc[i]);
            tiles[i].mapSymb = symb[i];
            tiles[i].attr = attr[i];
            
        }

    *tileCount = MaxTiles;
    return tiles;
}

zset__Tileset zse_tile__tileset_getDefault(void)
{
    zset__Tileset ts;
    ts.tiles = _tiles_getdefault(&ts.tileCount);
    ts.tileTextureIDs = NULL;

    return ts;
}

void zse_tile__tileset_deleteContent(zset__Tileset *ts)
{
    free(ts->tiles);
    free(ts->tileTextureIDs);

    ts->tileCount = -1;
}