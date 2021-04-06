#ifndef ZAKAROUF_ZSE__MAP_CHUNKTYPE_H
#define ZAKAROUF_ZSE__MAP_CHUNKTYPE_H

#include "../common.h"

/*------------------------------------------------------------------------------*/
/*---------------------------------------Types----------------------------------*/
typedef z__u8 zset__mapChPlot;

/*----------MapType------------*/

typedef struct __ZSE_MAP__TYPE_
{
	z__Vint4 size; 	  			// Map size in x, y, z, w
	zset__mapChPlot **chunks;

}zset__mapCh;

// Funcs
zset__mapCh *zse_map__ch_createEmpty(z__u32 x, z__u32 y, z__u32 z, z__u32 w);
void zse_map__ch_deleteChunks(zset__mapCh *map);


// ---||--- //
void zse_map__ch_export_singleChunk(char mapname[] ,zset__mapCh *map, z__u32 chunk, z__Vint3 Chunk_cords);
void zse_map__ch_export_commondata(char file[], zset__mapCh *map);
void zse_map__ch_export__st(char pathName[ static 1 ], zset__mapCh *map);
// ---||--- //
zset__mapCh *zse_map__ch_load__st(char mapname[ static 1 ]);
// ---||--- //

void zse_map__ch_allocChunks(zset__mapCh *map, z__Vint4 sz);

/*------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------*/


#endif