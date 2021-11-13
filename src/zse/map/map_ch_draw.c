#include <string.h>

#include "ch_draw.h"

void zse_map__draw_circle_raw (zse_T_MapCh_Plot *chunk, z__Vint3 on , z__Vint2 bounds , z__i32 r, zse_T_MapCh_Plot plot)
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

void zse_map__draw_circle__raw(void *chunk, z__size plotsize, z__Vint3 mapsize, z__Vint3 center, z__u32 radius, void *plot)
{
	const z__u32 radius_squared = radius * radius;

	z__i32 i = center.y - radius;
	z__i32 end_i = center.y + radius + 1;
	z__i32 end_j = center.x + radius + 1;

	if(i < 0){
		i = 0;
	}
	if(end_i >= mapsize.y){
		end_i = mapsize.y;
	}
	if(end_j >= mapsize.x){
		end_j = mapsize.x;
	}

	z__i32 const tmp_j = (center.x - radius) < 0? 0: center.x - radius;

	for(; i < end_i; i++){
		int j = tmp_j;
		for(; j < end_j; j++){
			if( ((j - center.x) * (j - center.x)) + ((i - center.y) * (i - center.y)) <= radius_squared){
				memcpy(&chunk[zse_xyz3Dto1D(j, i, center.z, mapsize.x, mapsize.y) * plotsize], plot, plotsize);
			}
		}
	}
}

void zse_map__draw_rect_raw(zse_T_MapCh_Plot *chunk, z__Vint2 bounds ,z__Vint2 from, z__Vint2 to, int level , zse_T_MapCh_Plot plot)
{
	const z__u64 z = level * bounds.x * bounds.y;
	for(int y = from.y; y < to.y; ++y)
		for(int x = from.x; x < to.x; ++x)
			chunk[x + (y * bounds.x) + z] = plot;

}
/*
void zse_map_fillupchunk_in(IN_WORLD_t *mapIN, int ChunkNo, int atChunkX, int atChunkY)
{
	int w = (atChunkX * mapIN->ChunkSizeXY);
	int q = (atChunkY * mapIN->ChunkSizeXY);


	for (int i = 0; i < zse_mapINxy(mapIN); ++i)
	{
		for (int j = 0; j < zse_mapINxy(mapIN); ++j)
		{
			mapIN->chunks[ChunkNo][zse_xyz3Dto1D(j, i, 0, zse_mapINxy(mapIN), zse_mapINxy(mapIN))] = zse_map_gen2d_get_solo(w+j, q+i, 0.3, 10) * 10;
		}
	}
}

void zse_map_fillentireChunks_in(IN_WORLD_t *mapIN, int px, int py)
{
	for (int i = 0; i < zse_mapInSideCLen(mapIN->_MaxChunkRadius); ++i)
	{
		for (int j = 0; j < zse_mapInSideCLen(mapIN->_MaxChunkRadius); ++j)
		{
			zse_map_fillupchunk_in(mapIN, zse_xyz3Dto1D(j, i, 0, zse_mapInSideCLen(mapIN->_MaxChunkRadius), zse_mapInSideCLen(mapIN->_MaxChunkRadius)), px+j, py+i);
		}
	}
}
*/
