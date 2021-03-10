#include "map_lib.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

ST_WORLD_t* zse_map_init_empty_st(int x, int y, int z)
{

	ST_WORLD_t *map = malloc(sizeof(ST_WORLD_t));

	map->Xsize = x;
	map->Ysize = y;
	map->Zsize = z;

	map->chunk = malloc(sizeof(plotdata_t) * map->Xsize * map->Ysize * map->Zsize);
	memset(map->chunk, 0, map->Xsize*map->Ysize*map->Zsize * sizeof(plotdata_t));

	return map;
}



void zse_map_delete_st(ST_WORLD_t *map)
{
	free(map->chunk);
	free(map);
}


// Infinity Map

static plotdata_t **zse_map_create_chunks (unsigned int x, unsigned int y, unsigned z, unsigned chunks) {


	chunks = zse_mapInSideCLen(chunks)* zse_mapInSideCLen(chunks);
	
	plotdata_t **arr = malloc(chunks * sizeof(plotdata_t*));

	for (int i = 0; i < chunks; ++i)
	{
		arr[i] = malloc(x*y*z *sizeof(plotdata_t));
	}

    return arr;

}

IN_WORLD_t zse_map_init_empty_in()
{
	IN_WORLD_t mapIN;

	mapIN._MaxChunkRadius = ZSE_mapIN_CHUNKRADIUSSIZE_DEFAULT;
	mapIN.ChunkSizeXY = ZSE_mapIN_CHUNK_XY_SIZE_DEFAULT;
	mapIN.ChunkSizeZ = ZSE_mapIN_CHUNK_Z_SIZE_DEFAULT;

	mapIN.chunks = zse_map_create_chunks (mapIN.ChunkSizeXY, mapIN.ChunkSizeXY, mapIN.ChunkSizeZ, mapIN._MaxChunkRadius);

	return mapIN;
}

void zse_map_fillChunkGenerate2D_in(plotdata_t *chunk, uint16_t dimentionXY ,int chunkXY[2])
{
	for (int i = 0; i < dimentionXY; ++i)
	{
		for (int j = 0; j < dimentionXY; ++j)
		{
			*chunk = zse_map_gen2d_get_solo(zse_mapINAbsPos(j, chunkXY[0], dimentionXY), zse_mapINAbsPos(i, chunkXY[1], dimentionXY), 0.1, 4);
			chunk++;
		}
	}
}

void zse_map_delete_in(IN_WORLD_t *mapIN, int isptr, size_t size)
{
	for (int k = 0; k < size; ++k)
	{
		for (int i = 0; i < mapIN[k]._MaxChunkRadius; ++i)
		{
			free(mapIN[k].chunks[i]);
		}
		free(mapIN[k].chunks);
	}
	if (isptr)
	{
		free(mapIN);
	}
}



