#include "map_lib.h"


void zse_map_draw_circle (ST_WORLD_t *map, int x, int y, int z ,int r , plotdata_t tile)
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
                	map->chunk[zse_xyz3Dto1D(j, i, z, map->Xsize, map->Ysize)] = tile;
            }
        }
    }
}

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
