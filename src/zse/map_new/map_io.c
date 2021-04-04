
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "map.h"

#define MAP_GENERAL_DIRECTORY "./maps"

#define VACANT_MAP "\0"

#define MAP_DATAFILE_COMMON "cd.bin"
#define MAP_DATAFILE_LINK "ld.bin"

#define MAP_DATAFILE_EXTENTION ".bin"
/*----
 main world data file naming format 'x,y,z.bin'
----*/

/*
int zse_map_export_st(ST_WORLD_t *map, char name[], char tilesetname[], char newmap)
{
	char mapdir[48] = MAP_DIR_NAME;
	char dirpos[74] = "";
	strcat(mapdir, name);

	if (newmap)
	{
		mkdir(mapdir, 0777);
	}

	sprintf(dirpos, "%s/%s", mapdir, MAP_DATAFILE_COMMON);
	_map_export_commondata_st(map, tilesetname, dirpos);


	sprintf(dirpos, "%s/%s", mapdir, MAP_DATAFILE_WORLD);
	_map_export_plotdatadata_st(map->chunk, map->Xsize, map->Ysize, map->Zsize, dirpos);

	
	return 0;

}
*/

static void _zse_map__export_commondata_aChunk(char file[], zset__map *map)
{
	FILE *fp = fopen(file, "wb");

	fwrite(ZSE_ENGINE_VERSION, 8, 1, fp);
	fwrite( &map->size, sizeof(z__Vint4), 4, fp);

	fclose(fp);
}


zset__map *zse_map__export(char pathName[])
{
	zset__map *map = z__MALLOC(sizeof(zset__map));



	return map;
}
