#include "map_lib.h"
#include <stdlib.h>

void map_delmap(MAP *map)
{
	free(map->world);


	free(map);
}

MAP *map_initmap(size_t size)
{
	MAP *map = malloc(sizeof(MAP) * size);


	return map;
}