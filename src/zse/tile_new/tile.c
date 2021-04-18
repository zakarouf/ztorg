#include <string.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

#include "tile_def.h"

#define _TILE_DEFAULT_EXPORT_DIRECTORY "./" "tiles/"

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
    ts.tileTextureIDs = z__CALLOC(ts.tileCount, sizeof(*ts.tileTextureIDs));

    return ts;
}

void zse_tile__tileset_deleteContent(zset__Tileset *ts)
{
    free(ts->tiles);
    free(ts->tileTextureIDs);

    ts->tileCount = -1;
}

void zse_tile__tileset_export(zset__Tileset *ts, char filename [ static 1 ])
{
    char fullpath[128];
    snprintf(fullpath, sizeof(fullpath), _TILE_DEFAULT_EXPORT_DIRECTORY "%s", filename);

    FILE *fp = fopen (fullpath, "wb");
    if(!fp)
    {
        return;
    }

    fwrite(ZSE_ENGINE_VERSION, ZSE_ENGINE_VERSION_SIGN_SIZE, 1, fp);

    fwrite(&ts->tileCount, sizeof(ts->tileCount), 1, fp);
    struct zset__Stile *tile = ts->tiles;
    for (int i = 0; i < ts->tileCount; ++i)
    {
        fwrite(tile->name, sizeof(*tile->name), sizeof(tile->name)/sizeof(*tile->name), fp);
        fwrite(&tile->mapSymb, sizeof(tile->mapSymb), 1, fp);
        fwrite(&tile->attr, sizeof(tile->attr), 1, fp);

        tile++;
    }

    fwrite(ts->tileTextureIDs, sizeof(*ts->tileTextureIDs), ts->tileCount, fp);
    fclose(fp);
}

zset__Tileset zse_tile__tileset_load(char const filename [ static 1 ])
{
    zset__Tileset ts = {0};

    char fullpath[128];
    snprintf(fullpath, sizeof(fullpath), _TILE_DEFAULT_EXPORT_DIRECTORY "%s", filename);

    FILE *fp = fopen (fullpath, "rb");
    if(!fp)
    {
        return ts;
    }

    char version[ZSE_ENGINE_VERSION_SIGN_SIZE];
    fread(version, ZSE_ENGINE_VERSION_SIGN_SIZE, 1, fp);
    fread(&ts.tileCount, sizeof(ts.tileCount), 1, fp);

    ts.tiles = z__CALLOC(sizeof(&ts.tiles), ts.tileCount);

    struct zset__Stile *tile = ts.tiles;
    for (int i = 0; i < ts.tileCount; ++i)
    {
        fread(tile->name, sizeof(*tile->name), sizeof(tile->name)/sizeof(*tile->name), fp);
        fread(&tile->mapSymb, sizeof(tile->mapSymb), 1, fp);
        fread(&tile->attr, sizeof(tile->attr), 1, fp);

        tile++;
    }

    fread(ts.tileTextureIDs, sizeof(*ts.tileTextureIDs), ts.tileCount, fp);
    fclose(fp);

    return ts;
}
