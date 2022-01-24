#include <string.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

#include "tile_def.h"
#include "../config/config_tile.h"

#include <z_/types/autotype.h>


static struct zset__Stile* _tiles_getdefault(z__u32 *tileCount)
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
            z__Arr_new(&tiles[i].textures, 8);
        }

    *tileCount = MaxTiles;
    return tiles;
}

zse_T_Tileset zse_tile__tileset_getDefault(void)
{
    zse_T_Tileset ts;
    ts.tiles.data = _tiles_getdefault(&ts.tiles.lenUsed);

    return ts;
}



zse_T_Tileset zse_tile__tileset_createEmpty(z__size tileCount, z__size textureCount)
{
    zse_T_Tileset tileset;
    z__Arr_new(&tileset.tiles, tileCount);

    z__Arr_foreach(z__auto i, tileset.tiles) {
        z__Arr_new(&i->textures, textureCount);
    }

    return tileset;
}

void zse_tile__tileset_deleteContent(zse_T_Tileset *ts)
{
    for(int i = 0; i < ts->tiles.len; i++) {
        z__Arr_delete(&ts->tiles.data[i].textures);
    }
    z__Arr_delete(&ts->tiles);
}

void zse_tile__tileset_export(zse_T_Tileset *ts, char filename [ static 1 ])
{
    char fullpath[128];
    snprintf(fullpath, sizeof(fullpath), _TILE_DEFAULT_EXPORT_DIRECTORY "%s", filename);

    FILE *fp = fopen (fullpath, "wb");
    if(!fp)
    {
        return;
    }

    fwrite(ZSE_ENGINE_VERSION, ZSE_ENGINE_VERSION_SIGN_SIZE, 1, fp);

    fwrite(&ts->tiles.lenUsed, sizeof(ts->tiles.lenUsed), 1, fp);

    struct zset__Stile *tile = ts->tiles.data;
    for (int i = 0; i < ts->tiles.lenUsed; ++i)
    {
        fwrite(tile->name, sizeof(*tile->name), sizeof(tile->name)/sizeof(*tile->name), fp);
        fwrite(&tile->mapSymb, sizeof(tile->mapSymb), 1, fp);
        fwrite(&tile->attr, sizeof(tile->attr), 1, fp);
        fwrite(&z__Arr_getUsed(tile->textures), sizeof(z__Arr_getUsed(tile->textures)), 1, fp);
        fwrite(tile->textures.data, sizeof(*tile->textures.data), z__Arr_getUsed(tile->textures), fp);

        tile++;
    }

    fclose(fp);
}

zse_T_Tileset zse_tile__tileset_load(char const filename [ static 1 ])
{
    zse_T_Tileset ts = {0};

    char fullpath[128];
    snprintf(fullpath, sizeof(fullpath), _TILE_DEFAULT_EXPORT_DIRECTORY "%s", filename);

    FILE *fp = fopen (fullpath, "rb");
    if(!fp)
    {
        return ts;
    }

    char version[ZSE_ENGINE_VERSION_SIGN_SIZE];
    fread(version, ZSE_ENGINE_VERSION_SIGN_SIZE, 1, fp);
    
    z__typeof(ts.tiles.len) tcount;

    fread(&tcount, sizeof(tcount), 1, fp);
    
    z__Arr_new(&ts.tiles, tcount);

    struct zset__Stile *tile = ts.tiles.data;
    for (int i = 0; i < ts.tiles.len; ++i)
    {
        fread(tile->name, sizeof(*tile->name), sizeof(tile->name)/sizeof(*tile->name), fp);
        fread(&tile->mapSymb, sizeof(tile->mapSymb), 1, fp);
        fread(&tile->attr, sizeof(tile->attr), 1, fp);

        
        fread(&z__Arr_getUsed(tile->textures), sizeof(z__Arr_getUsed(tile->textures)), 1, fp);

        int tmp_a = z__Arr_getUsed(tile->textures);
        z__Arr_new(&tile->textures, tmp_a);
        z__Arr_getLen(tile->textures) = z__Arr_getUsed(tile->textures);

        fread(tile->textures.data, sizeof(*tile->textures.data), z__Arr_getUsed(tile->textures), fp);

        tile++;
    }

    fclose(fp);
    z__Arr_getUsed(ts.tiles) = z__Arr_getLen(ts.tiles);

    return ts;
}
