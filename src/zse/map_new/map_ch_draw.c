#include "map_ch.h"

void zse_map__draw_circle (zset__mapChPlot *chunk, z__Vint3 on , z__Vint2 bounds , z__i32 r, zset__mapChPlot plot)
{
	z__i32 i = on.y - r;
	z__i32 end_i = on.y + r + 1;
	z__i32 end_j = on.x + r + 1;

	if(i < 0) {
		i = 0;
	}
	if (end_i >= bounds.y) {
		end_i = bounds.y;
	}
	if(end_j >= bounds.x) {
		end_j = bounds.x;
	}
	
	z__i32 tmp_j = (on.x - r < 0)? 0: on.x - r;

    for (; i < end_i; ++i) {
    	int j = tmp_j;

        for (; j < end_j ; ++j) {

            if( ((j - on.x) * (j - on.x) + (i - on.y) * (i - on.y)) <= r * r ) {
                	chunk[zse_xyz3Dto1D(j, i, on.z, bounds.x, bounds.y)] = plot;
            }
        }
    }
}
