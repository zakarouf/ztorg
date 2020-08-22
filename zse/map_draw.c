#include "map_lib.h"


void map_draw_circle (ST_WORLD_t *map, int x, int y, int z ,int r , plotdata_t tile)
{

	int i = y - r;
	int end_i = y + r + 1;
	int end_j = x + r + 1;

	if(i < 0)
	{
		i = 0;
	}
	if (end_i >= map->Ysize)
	{
		end_i = map->Ysize;
	}
	if(end_j >= map->Xsize)
	{
		end_j = map->Xsize;
	}
	
	int tmp_j = (x-r < 0)? 0:x-r;

    for (; i < end_i; ++i) {
    	int j = tmp_j;

        for (; j < end_j ; ++j) {

            if( ((j - x) * (j - x) + (i - y) * (i - y)) <= r * r ) {
                	map->chunk[getindex3d(j, i, z, map->Xsize, map->Ysize)] = tile;
            }
        }
    }
}