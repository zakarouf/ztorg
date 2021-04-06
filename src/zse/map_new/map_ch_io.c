
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "map_ch.h"

#define MAP_GENERAL_DIRECTORY "./maps/"

#define VACANT_MAP "\0"

#define MAP_DATAFILE_COMMON "cd.bin"
#define MAP_DATAFILE_LINK "ld.bin"

#define MAP_DATAFILE_EXTENTION ".bin"
/*----
 main world data file naming format 'x,y,z.bin'
----*/

void zse_map__ch_load_singleChunk(const char mapname[] ,zset__mapCh *map, z__u32 chunk, z__Vint3 Chunk_cords)
{
	char file[128];
	snprintf(file, 128, MAP_GENERAL_DIRECTORY "%s/%d,%d,%d.bin", mapname, Chunk_cords.x, Chunk_cords.y, Chunk_cords.z);
	FILE *fp = fopen(file, "rb");

	fread(map->chunks[chunk], sizeof(**map->chunks), map->size.x * map->size.z * map->size.y, fp);

	fclose(fp);
}

static void zse_map__ch_load_commondata(const char mapname[], zset__mapCh *map)
{
	char file[128];
	snprintf(file, 128, MAP_GENERAL_DIRECTORY "%s" MAP_DATAFILE_COMMON, mapname);
	FILE *fp = fopen(file, "rb");

	char version[ZSE_ENGINE_VERSION_SIGN_SIZE];

	fread( version, ZSE_ENGINE_VERSION_SIGN_SIZE, 1, fp);
	fread( &map->size, sizeof(map->size), 1, fp);

	fclose(fp);
}

zset__mapCh *zse_map__ch_load__st(const char mapname[ static 1 ])
{
	zset__mapCh *map = z__MALLOC(sizeof(zset__mapCh));

	zse_map__ch_load_commondata(mapname, map);
	zse_map__ch_allocChunks(map, map->size, 1);

	zse_map__ch_load_singleChunk(mapname, map, 0, (z__Vint3){0,0,0});

	return map;
}

void zse_map__ch_export_singleChunk(char mapname[] ,zset__mapCh *map, z__u32 chunk, z__Vint3 Chunk_cords)
{
	char file[128];
	snprintf(file, 128, MAP_GENERAL_DIRECTORY "%s/%d,%d,%d.bin", mapname, Chunk_cords.x, Chunk_cords.y, Chunk_cords.z);
	FILE *fp = fopen(file, "wb");

	fwrite(map->chunks[chunk], sizeof(**map->chunks), map->size.x * map->size.z * map->size.y, fp);

	fclose(fp);
}

void zse_map__ch_export_commondata(char mapname[], zset__mapCh *map)
{
	char file[128];
	snprintf(file, 128, MAP_GENERAL_DIRECTORY "%s/" MAP_DATAFILE_COMMON, mapname);
	FILE *fp = fopen(file, "wb");

	fwrite(ZSE_ENGINE_VERSION, ZSE_ENGINE_VERSION_SIGN_SIZE, 1, fp);
	fwrite( &map->size, sizeof(map->size), 1, fp);


	fclose(fp);
}


void zse_map__ch_export__st(char mapname[ static 1 ], zset__mapCh *map)
{
	char mapdir[96] = MAP_GENERAL_DIRECTORY;
	strncat(mapdir, mapname, sizeof(mapdir) - sizeof(MAP_GENERAL_DIRECTORY));

		mkdir(mapdir, 0755);

	zse_map__ch_export_commondata(mapname, map);
	zse_map__ch_export_singleChunk(mapname , map, 0, (z__Vint3){0, 0, 0});
}
