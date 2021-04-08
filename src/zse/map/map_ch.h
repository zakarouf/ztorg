#ifndef ZAKAROUF_ZSE__MAP_CHUNKTYPE_H
#define ZAKAROUF_ZSE__MAP_CHUNKTYPE_H

#include "../common.h"

/*------------------------------------------------------------------------------*/
/*---------------------------------------Types----------------------------------*/
typedef z__u8 zset__mapChPlot;

/*----------MapType------------*/

typedef struct __ZSE_MAP__TYPE_
{
    z__Vint3 size;              // Map size in x, y, z, w
    zset__mapChPlot **chunks;

    z__i8 chunkCount;
    z__i8 chunkRadius;

}zset__MapCh;


/*------------------------------------------
 * Common Funcs/Macro
 *------------------------------------------
 */
/* <== Old
#define zse_mapx(map) map->Xsize
#define zse_mapy(map) map->Ysize
#define zse_mapz(map) map->Zsize

#define ZSE_mapIN_CHUNKRADIUSSIZE_DEFAULT 1
#define ZSE_mapIN_CHUNK_XY_SIZE_DEFAULT 32
#define ZSE_mapIN_CHUNK_Z_SIZE_DEFAULT 1

#define ZSE_map__ch_absPos(p, C, CSize) ((CSize)*(C)) + p
#define ZSE_map__ch_xy(mapIN) mapIN->ChunkSizeXY
#define ZSE_map__ch_SideCLen(_MaxChunkRadius) (1 + (2*(_MaxChunkRadius)))
#define ZSE_map__ch_TotalChunkNo(_MaxChunkRadius) zse_mapInSideCLen(_MaxChunkRadius)*zse_mapInSideCLen(_MaxChunkRadius)
#define ZSE_map__ch_ChunksMid(_MaxChunkRadius) (int)( ((float)zse_mapINTotalChunkNo(_MaxChunkRadius) /2) - 0.5f )
#define ZSE_map__ch_Chunks_Atgetxyz(chunkno, x, y, z, mapIN) (IN_WORLD_t*)mapIN->chunk[chunkno][zse_xyz3Dto1D(x, y, z, mapIN->ChunkSizeXY, mapIN->ChunkSizeXY)]

#define ZSE_map__ch_chunklineStartEnd(ch , start, end, _MaxChunkRadius) \
    {                                                               \
        end = zse_mapInSideCLen(_MaxChunkRadius) * ch;              \
        start = zse_mapInSideCLen(_MaxChunkRadius) * (ch>0? ch-1:0);\
    }
#define ZSE_map__ch_chunklineStartEndPLR(start, end ,_MaxChunkRadius) \
    {                                                                                                                   \
        end = (int) ((zse_mapInChunksMid(_MaxChunkRadius) + (float)(zse_mapInSideCLen(_MaxChunkRadius)/2 + 0.5f)));     \
        start = (int) ((zse_mapInChunksMid(_MaxChunkRadius) - (float)(zse_mapInSideCLen(_MaxChunkRadius)/2 - 0.5f)));   \
    }
*/

 // <== New




/* ----------------------------------------- * ----------------------------------------- * ----------------------------------------- */
/* ----------------------------------------- * ----------------------------------------- * ----------------------------------------- */

// Funcs
zset__MapCh *zse_map__ch_createEmpty(z__u32 x, z__u32 y, z__u32 z, z__u32 w);
void zse_map__ch_deleteChunks(zset__MapCh *map);

// ---||--- //
void zse_map__ch_export_singleChunk(char mapname[] ,zset__MapCh *map, z__u32 chunk, z__Vint3 Chunk_cords);
void zse_map__ch_export_commondata(char file[], zset__MapCh *map);
void zse_map__ch_export__st(char pathName[ static 1 ], zset__MapCh *map);
// ---||--- //
zset__MapCh *zse_map__ch_load__st(const char mapname[ static 1 ]);
// ---||--- //
void zse_map__ch_allocChunks(zset__MapCh *map, const z__Vint3 sz, const z__u32 chunkCount);

// ----Drawing---- //
void zse_map__draw_circle (zset__mapChPlot *chunk, z__Vint3 on , z__Vint2 bounds , z__i32 r, zset__mapChPlot plot);

/*------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------*/


#endif