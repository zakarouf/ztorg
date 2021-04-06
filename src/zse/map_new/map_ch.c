#include <stdlib.h>

#include "map_ch.h"

void zse_map__ch_allocChunks(zset__mapCh *map, z__Vint4 sz)
{
	map->chunks = z__MALLOC(sizeof(zset__mapChPlot*) * sz.w);
	for (int i = 0; i < sz.w; ++i)
	{
		map->chunks[i] = z__MALLOC(sizeof(zset__mapChPlot) * sz.x * sz.y * sz.z);
	}

	map->size = sz;
}

zset__mapCh *zse_map__ch_createEmpty(z__u32 x, z__u32 y, z__u32 z, z__u32 w)
{
	zset__mapCh *map = z__MALLOC(sizeof(zset__mapCh));

	zse_map__ch_allocChunks(map, (z__Vint4){x, y, z, w});

	return map;
}

void zse_map__ch_deleteChunks(zset__mapCh *map)
{
	for (int i = 0; i < map->size.w; ++i)
	{
		free(map->chunks[i]);
	}
	free(map->chunks);

	map->size.x = 0;
	map->size.y = 0;
	map->size.z = 0;
	map->size.w = 0;
}
