#include <stdlib.h>

#include "map_ch.h"

void zse_map__ch_allocChunks(zset__mapCh *map, const z__Vint3 sz, const z__u32 chunkCount)
{
	map->chunks = z__MALLOC(sizeof(zset__mapChPlot*) * chunkCount);
	for (int i = 0; i < chunkCount; ++i)
	{
		map->chunks[i] = z__MALLOC(sizeof(zset__mapChPlot) * sz.x * sz.y * sz.z);
	}
	map->size = sz;
	map->chunkCount = chunkCount;
}

inline zset__mapCh *zse_map__ch_createEmpty(z__u32 x, z__u32 y, z__u32 z, z__u32 chunkCount)
{
	zset__mapCh *map = z__MALLOC(sizeof(zset__mapCh));

	zse_map__ch_allocChunks(map, (z__Vint3){x, y, z}, chunkCount);

	return map;
}

ZSE__INLINE_NST void zse_map__ch_deleteChunk(zset__mapChPlot **chunks, z__u32 at)
{
	free(chunks[at]);
}

void zse_map__ch_deleteChunks(zset__mapCh *map)
{
	for (int i = 0; i < map->chunkCount; ++i)
	{
		free(map->chunks[i]);
	}
	free(map->chunks);

	map->size.x = 0;
	map->size.y = 0;
	map->size.z = 0;
	map->chunkCount = 0;
}
