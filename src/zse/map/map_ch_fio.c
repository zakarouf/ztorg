
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <z_/types/result.h>
#include <z_/types/option.h>
#include <z_/imp/sys.h>
#include <z_/imp/fio.h>

#include "ch.h"
#include "ch_fio.h"
#include "../config/config_map_ch.h"


#define ZSE_MAP_CH_IO_DEBUG
#ifdef ZSE_MAP_CH_IO_DEBUG
	#define logprint(c, fmt, ...) z__logfile_cl256(stdout ,c, "MAP::CH| " fmt "\n", __VA_ARGS__)
#else
	#define logprint(fmt, ...)
#endif

#define COLOR_NORMAL 7
#define COLOR_ERROR 1
#define COLOR_WARNING 2

/*----
 main world data file naming format 'x,y,z.bin'
----*/


FILE* zse_map_ch_export_chunk__raw(
	  char const *mapname
	, z__Vint3 const Chunk_cords
	, void const *chunk
	, z__size const plotsize
	, z__Vint3 const chunksize
	, zse_T_Map_ObjectSetsArr const objectSet
	, z__bool should_writeObjects)
{
	#define lgp(fmt, ...)	logprint(5, "Writing Map Chunk: " fmt, __VA_ARGS__)
	#define lgpERROR(fmt, ...)	logprint(1, "Writing Map Chunk: ERROR: " fmt, __VA_ARGS__)
	#define lgpWARNING(fmt, ...)	logprint(2, "Writing Map Chunk: WARNING: " fmt, __VA_ARGS__)

	char file[128];
	snprintf(file, 128, "%s/%d,%d,%d.bin", mapname, Chunk_cords.x, Chunk_cords.y, Chunk_cords.z);
	FILE *fp = fopen(file, "wb");

	if(fp == NULL) {
		lgpERROR("Map Chunk Save Failed, %s", mapname);
		return NULL;
	}

	/* Dump All the Plot data */
	fwrite(chunk, plotsize, chunksize.x * chunksize.z * chunksize.y, fp);

	/* Dump All the Generic Objects */
	if(should_writeObjects) {
		lgp("Dumping %d Objects", z__Arr_getUsed(objectSet));
		fwrite(&z__Arr_getUsed(objectSet), sizeof(z__Arr_getUsed(objectSet)), 1, fp);

		for(int i = 0; i < z__Arr_getUsed(objectSet); i++) {

			z__Dynt *_obj = &z__Arr_getVal(objectSet, i);
			z__fio_Dynt_dump(_obj, fp);

			lgp("(%d/%d) Objects %s(s) Dump\n"
				"       |- ID %d\n"
				"       |- UnitSize %ld bytes\n"
				"       |- Count %d\n"
				"       |- In Memory %p\n" , i+1
									, z__Arr_getUsed(objectSet)
									, _obj->comment
									, _obj->typeID
									, _obj->unitsize
									, _obj->lenUsed
									, _obj->data);
		}
		
	} else {
		lgp("No Objects To Dump%s", "");

		z__Arr(int) _tmp;
		z__typeof(z__Arr_getUsed(_tmp)) _count = 0;
		fwrite(&_count, sizeof(_count), 1, fp);
	}

	return fp;

	#undef lgp
	#undef lgpERROR
	#undef lgpWARNING

}

FILE* zse_map_ch_export_commondata__raw(
	  char const mapname[]
	, z__Vint3 chunksize)
{
	#define lgp(fmt, ...)	logprint(COLOR_NORMAL, "Writing Map Common Data: " fmt, __VA_ARGS__)
	#define lgpERROR(fmt, ...)	logprint(COLOR_ERROR, "Writing Map Common Data: ERROR: " fmt, __VA_ARGS__)
	#define lgpWARNING(fmt, ...)	logprint(COLOR_WARNING, "Writing Map Common Data: WARNING: " fmt, __VA_ARGS__)

	char file[128];
	snprintf(file, 128, "%s/" MAP_DATAFILE_COMMON, mapname);
	FILE *fp = fopen(file, "wb");
	if(fp == NULL) {
		lgpERROR("Map Common Data Save Failed, %s", mapname);
		return NULL;
	}

	lgp("Writing Version %s", "");
	fwrite(ZSE_ENGINE_VERSION, ZSE_ENGINE_VERSION_SIGN_SIZE, 1, fp);

	lgp("Writing Chunk Size %d, %d, %d", chunksize.x, chunksize.y, chunksize.z);
	fwrite(&chunksize, sizeof(chunksize), 1, fp);

	return fp;
	
	#undef lgp
	#undef lgpERROR
	#undef lgpWARNING
}

void zse_map_ch_export_st__raw(
	  char const *mapname
	, void const *chunk
	, z__size const plotsize
	, z__Vint3 const chunksize
	, zse_T_Map_ObjectSetsArr const objectSet
	, z__bool should_writeObjects
	, FILE **cd_fp
	, FILE **ch_fp)
{
	#define lgp(fmt, ...)	logprint(COLOR_NORMAL, "Exporting Map: " fmt, __VA_ARGS__)
	#define lgpERROR(fmt, ...)	logprint(COLOR_ERROR, "Exporting Map: ERROR: " fmt, __VA_ARGS__)
	#define lgpWARNING(fmt, ...)	logprint(COLOR_WARNING, "Exporting Map: WARNING: " fmt, __VA_ARGS__)

	mkdir(mapname, 0777);
	lgp("Map Directory \"%s\"", mapname);

	*cd_fp = zse_map_ch_export_commondata__raw(mapname, chunksize);
	*ch_fp = zse_map_ch_export_chunk__raw(mapname, (z__Vint3){{0, 0, 0}}, chunk, plotsize, chunksize, objectSet, should_writeObjects);

	if(ch_fp == NULL || cd_fp == NULL){
		lgpERROR("Map Save Failed, %s", mapname);
	} else {
		lgp("Map Saved as in %s", mapname);
	}

	#undef lgp
	#undef lgpERROR
	#undef lgpWARNING
}

FILE* zse_map_ch_load_chunk__raw(
	  const char mapname[]
	, z__Vint3 const Chunk_cords
	, z__size const plotsize
	, z__Vint3 const chunksize
	, void **chunk
	, zse_T_Map_ObjectSetsArr *objectSet)
{
	#define lgp(fmt, ...)	logprint(COLOR_NORMAL, "Loading Map Chunk: " fmt, __VA_ARGS__)
	#define lgpERROR(fmt, ...)	logprint(1, "Loading Map Chunk: ERROR: " fmt, __VA_ARGS__)
	#define lgpWARNING(fmt, ...)	logprint(2, "Loading Map Chunk: WARNING: " fmt, __VA_ARGS__)

	lgp("%s", mapname);
	lgp("Chunk Cord %d, %d, %d", Chunk_cords.x, Chunk_cords.y, Chunk_cords.z);

	char file[128];
	snprintf(file, 128, "%s/%d,%d,%d.bin", mapname, Chunk_cords.x, Chunk_cords.y, Chunk_cords.z);
	
	FILE *fp = fopen(file, "rb");
	if (fp == NULL) {
		lgpERROR("Cant Open Map Chunk %s", mapname);
		return NULL;
	}

	lgp("Reading Map Data %s", "");
	fread(*chunk, plotsize, chunksize.x * chunksize.z * chunksize.y, fp);

	lgp("Reading Object Data %s", "");
	/* Read Objects */	
	zse_T_Map_ObjectSetsArr *objs = objectSet;

	z__typeof(objs->lenUsed) sz;

	// Read the total no. of objects. 
	fread(&sz, sizeof(sz), 1, fp);
	lgp("Total Unique Object Sets is %i", sz);

	if(sz == 0) {
		lgp("No Objects At All %s", "");
		fclose(fp);
		return NULL;
	}

	if(objs->len <= 0) {
		z__Arr_new(objs, sz);
	} else if(objs->len < sz) {
		z__Arr_resize(objs, sz);
	}

	for(int o = 0; o < objs->len; o++) {
		z__Dynt *i = &objs->data[o];
		z__fio_Dynt_newLoad(i, fp);		
		lgp("(%d/%d) Object %s(s) Loaded\n"
			"       |- ID %d\n"
			"       |- UnitSize %ld bytes\n"
			"       |- Count %d\n"
			"       |- In Memory %p\n", o+1, objs->len, i->comment, i->typeID, i->unitsize, i->lenUsed, i->data);
	}
	
	return fp;

	#undef lgp
	#undef lgpERROR
	#undef lgpWARNING
}


FILE* zse_map_ch_load_commondata__raw(
	  const char mapname[]
	, z__Vint3 *chunksize)
{
	#define lgp(fmt, ...)	logprint(COLOR_NORMAL, "Loading Map Common Data: " fmt, __VA_ARGS__)
	#define lgpERROR(fmt, ...)	logprint(1, "Loading Map Common Data: ERROR: " fmt, __VA_ARGS__)
	#define lgpWARNING(fmt, ...)	logprint(2, "Loading Map Common Data: WARNING: " fmt, __VA_ARGS__)

	char file[128];
	snprintf(file, 128, "%s/" MAP_DATAFILE_COMMON, mapname);
	FILE *fp = fopen(file, "rb");
	if(!fp) {
		lgpERROR("%s :: Couldn't Load Common Data", mapname);
		return NULL;
	}

	lgp("%s :: Loading Map Common Data", mapname);
	char version[ZSE_ENGINE_VERSION_SIGN_SIZE];

	fread( version, ZSE_ENGINE_VERSION_SIGN_SIZE, 1, fp);
	lgpWARNING("Version :: NOT APPLIED YET %s", "");

	fread( chunksize, sizeof(*chunksize), 1, fp);
	lgp("Chunk Size %dx%dx%d", chunksize->x, chunksize->y, chunksize->z);

	return fp;

	#undef lgp
	#undef lgpERROR
	#undef lgpWARNING
}


int zse_map_ch_load_st__raw(
	  char const *mapname
	, z__size const plotsize
	, void ***chunk
	, z__Vint3 *chunksize
	, zse_T_Map_ObjectSetsArr **objectSet
	, z__size *objCount
	, FILE **cd_fp
	, FILE **ch_fp)
{
	#define lgp(fmt, ...)	logprint(COLOR_NORMAL, "Loading Map: " fmt, __VA_ARGS__)
	#define lgpERROR(fmt, ...)	logprint(1, "Loading Map: ERROR: " fmt, __VA_ARGS__)
	#define lgpWARNING(fmt, ...)	logprint(2, "Loading Map: WARNING: " fmt, __VA_ARGS__)

//	*chunk = z__MALLOC(plotsize * chunksize->x * chunksize->y * chunksize->z);
	if((*cd_fp = zse_map_ch_load_commondata__raw(mapname, chunksize)) == NULL){
		lgpERROR("Failed To load Map %s", "");
		return -1;
	}
		
	zse_map_ch_createEmpty__raw(chunksize->x, chunksize->y, chunksize->z, 0, plotsize, chunk, objectSet, objCount);
	*ch_fp = zse_map_ch_load_chunk__raw(mapname, (z__Vint3){{0, 0, 0}}, plotsize, *chunksize, *chunk, *objectSet);

	lgp("Map Loaded %s", mapname);

	return 1;

	#undef lgp
	#undef lgpERROR
	#undef lgpWARNING
}
