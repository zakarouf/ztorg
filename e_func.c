#include "map_lib.h"
#include "e_intra.h"

void save_map (MAP *map, char tile[])
{
	map_write_world (map, map->name, tile, true);
}