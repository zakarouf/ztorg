#include "map_lib.h"
#include "e_intra.h"

void save_map (MAP *map)
{
	map_write_world (map, map->name, true);
}