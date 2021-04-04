#include <stdlib.h>

#include "map.h"

zset__map *zse_map__createEmpty(z__u32 x, z__u32 y, z__u32 z, z__u32 w)
{
	zset__map *map = z__MALLOC(sizeof(zset__map));

	map->size.x = x;
	map->size.y = y;
	map->size.z = z;
	map->size.w = w;

	map->chunks = z__MALLOC(sizeof(zset__mapPlot*) * w);
	for (int i = 0; i < w; ++i)
	{
		map->chunks[i] = z__MALLOC(sizeof(zset__mapPlot) * x * y * z);
	}

	return map;
}

void zse_map__deleteChunks(zset__map *map)
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
