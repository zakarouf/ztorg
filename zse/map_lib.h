#ifndef MAP_LIB_H
#define MAP_LIB_H

#include "common.h"

#define MAX_MAP_Xsize 1024
#define MAX_MAP_Ysize 1024
#define MAX_MAP_Zsize 8


//---------------------------------------Defs---------------------------------------------
typedef uint8_t plotdata_t;


//------------------------------------------
// Static World
//------------------------------------------

typedef struct _MAPDEF_STATIC_WORLD_t
{
	uint16_t Xsize;
	uint16_t Ysize;
	uint8_t  Zsize;
	plotdata_t *chunk;

}ST_WORLD_t;

//------------------------------------------
// Infinite World
//------------------------------------------

typedef struct _MAPDEF_INFITY_WORLD_t
{
	uint8_t Xsize;
	uint8_t Ysize;
	uint8_t Zsize;
	plotdata_t *chunk;

}IN_WORLD_t;




/*
---------------------------------------------------------------------
MAP FILE FORMAT
---------------------------------------------------------------------*/
#define MAP_DIR_NAME "./maps/"

#define VACANT_MAP "VACANT_MAP_1"

#define MAP_DATAFILE_COMMON "commondata.bin"
#define MAP_DATAFILE_WORLD 	"worlddata.bin"
#define MAP_DATAFILE_LINK	"linkdata.bin"
/*---------------------------------------------------------------------*/

//-------------------------Functions--------------------------------------------------------
//Perlin Noise
double zse_map_perlin2d_get_solo(double x, double y, double freq, int depth);
void zse_map_set_perlin_seed(int seed);


//MAP_In && MAP_Out

ST_WORLD_t* zse_map_load_st (char name[], char *returntilesetname);
int zse_map_export_st(ST_WORLD_t *map, char name[], char tilesetname[], bool newmap);

//MAP Draw
void zse_map_draw_circle (ST_WORLD_t *map, int x, int y, int z ,int r , plotdata_t tile);


//MAP misc
void zse_map_delete_st(ST_WORLD_t *map);
ST_WORLD_t* zse_map_init_empty_st(int x, int y, int z);


#endif