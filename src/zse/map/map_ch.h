#ifndef ZAKAROUF_ZSE__MAP_CHUNKTYPE_H
#define ZAKAROUF_ZSE__MAP_CHUNKTYPE_H

#include "../common.h"
#include "map_ch_def.h"

// Funcs
zset__MapCh *zse_map__ch_createEmpty(z__u32 x, z__u32 y, z__u32 z, z__u32 chunkRadius);
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
