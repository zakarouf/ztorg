#include "map_lib.h"


ST_WORLD_t* zse_map_init_empty_st(int x, int y, int z)
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



void zse_map_delete_st(ST_WORLD_t *map)
{
	free(map->chunk);
	free(map);
}


// Infinity Map

static plotdata_t **zse_map_create_chunks (unsigned int x, unsigned int y, unsigned z, unsigned chunks) {

	plotdata_t **arr = malloc(chunks * sizeof(plotdata_t*));

	for (int i = 0; i < chunks; ++i)
	{
		arr[i] = malloc(x*y*z *sizeof(plotdata_t));
	}

    return arr;

}

IN_WORLD_t* zse_map_init_empty_in()
{
	IN_WORLD_t* mapIN = malloc(sizeof(IN_WORLD_t));

	mapIN->_MaxChunk = ZSE_mapIN_CHUNKSIZE_DEFAULT;
	mapIN->ChunkSizeXY = ZSE_mapIN_CHUNK_XY_SIZE_DEFAULT;
	mapIN->ChunkSizeZ = ZSE_mapIN_CHUNK_Z_SIZE_DEFAULT;

	mapIN->chunk = zse_map_create_chunks (mapIN->ChunkSizeXY, mapIN->ChunkSizeXY, mapIN->ChunkSizeZ, mapIN->_MaxChunk);

	return mapIN;
}

void zse_map_delete_in(IN_WORLD_t *mapIN)
{
	for (int i = 0; i < mapIN->_MaxChunk; ++i)
	{
		free(mapIN->chunk[i]);
	}
	free(mapIN->chunk);	
	free(mapIN);
}
