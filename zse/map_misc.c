#include "map_lib.h"


ST_WORLD_t* map_init_empty_st(int x, int y, int z)
{

	ST_WORLD_t *map = malloc(sizeof(ST_WORLD_t));

	map->Xsize = x;
	map->Ysize = y;
	map->Zsize = z;

	map->chunk = malloc(sizeof(plotdata_t) * map->Xsize * map->Ysize * map->Zsize);
	for (int i = 0; i < map->Xsize*map->Ysize*map->Zsize; ++i)
	{
		map->chunk[i] = 0;
	}

	return map;
}



void map_delete_st(ST_WORLD_t *map)
{
	free(map->chunk);
	free(map);
}
