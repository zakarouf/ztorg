#include "e_intra.h"


void fillup_circle (MAP *map, int x, int y, int r , uint8_t tile) {

	int i = y - r;
	int end_i = y + r + 1;
	int end_j = x + r + 1;

	if(i < 0)
	{
		i = 0;
	}
	if (end_i >= map->Y)
	{
		end_i = map->Y;
	}
	if(end_j >= map->X)
	{
		end_j = map->X;
	}
	

    for (; i < end_i; ++i) {
    	int j = x - r;

    	if(j < 0)
    	{
    		j = 0;
    	}

        for (; j < end_j ; ++j) {

            if( ((j - x) * (j - x) + (i - y) * (i - y)) <= r * r ) {
                	map->world[i][j] = tile;
            }
        }
    }
}