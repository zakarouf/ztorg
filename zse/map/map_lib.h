#ifndef MAP_LIB_H
#define MAP_LIB_H

#include "../common.h"

#define MAX_MAP_DEFAULT_Xsize 1024
#define MAX_MAP_DEFAULT_Ysize 1024
#define MAX_MAP_DEFAULT_Zsize 8


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

typedef struct _MAPDEF_INFINITE_WORLD_t
{
  uint8_t ChunkSizeXY;
  uint8_t ChunkSizeZ;
  uint8_t _MaxChunk;

  plotdata_t **chunk;

}IN_WORLD_t;

/*
  . . . . . 
  . . . . . <- Each . is a chunk of (ChunkSizeXY * ChunkSizeXY) * ChunkSizeZ
  . . @ . .  - @ is the chunk inhabitate by the player
  . . . . .  - Chunk Size is 2 here
  . . . . . 

   /---------/
      . . .
      . @ . <- Chunk No. Size = 1 (DEFAULT) _MaxChunk
      . . .

   /---------/

    . . . . . . .
    . . . . . . .
    . . . . . . .
    . . . @ . . .
    . . . . . . .
    . . . . . . .
    . . . . . . .

*/

/*
    Chunk Size Increase In terms Of a Cube :-
        3, 5, 7, 9
        ^  ^  ^  ^
        1, 2, 3, 4 
        
        Chunks(n) = (1 + 2*n)


    /-----------------------------------------/
  Chunk Mid Point :-
      1 5 13 

      ChunksMid(n) = (int)( (float)(Chunks(n)/2) + 0.5f )

  Chunk lastline First Point :-


    /-----------------------------------------/
    Chunks File Size :-

      #EXECUTABLE DIR
        |- maps
          |- #MAP NAME
            |- MAP_DATAFILE_WORLD
            |- CHUNK CORD (eg. 1,1,1.bin
                               -1,1,0.bin)


*/

//------------------------------------------
// Common Funcs/Macro
//------------------------------------------

#define zse_mapx(map) map->Xsize
#define zse_mapy(map) map->Ysize
#define zse_mapz(map) map->Zsize

#define ZSE_mapIN_CHUNKSIZE_DEFAULT 1
#define ZSE_mapIN_CHUNK_XY_SIZE_DEFAULT 32
#define ZSE_mapIN_CHUNK_Z_SIZE_DEFAULT 1

#define zse_absMapINPos(p, C) (p)*(C)
#define zse_mapINxy(mapIN) mapIN->ChunkSizeXY
#define zse_mapInChunks(n) (1 + 2*n)
#define zse_mapInChunksMid(n) (int)( (float)(Chunks(n)/2) + 0.5f )
#define zse_mapINChunks_Atgetxyz(chunkno, x, y, z, mapIN) (IN_WORLD_t*)mapIN->chunk[chunkno][zse_xyz3Dto1D(x, y, z, mapIN->ChunkSizeXY, mapIN->ChunkSizeXY)]

/*
---------------------------------------------------------------------
MAP FILE FORMAT
---------------------------------------------------------------------*/
#define MAP_DIR_NAME "./maps/"

#define VACANT_MAP "VACANT_MAP_1"

#define MAP_DATAFILE_COMMON "commondata.bin"
#define MAP_DATAFILE_COMMON_EXTENTION ".bin"

#define MAP_DATAFILE_WORLD  "worlddata.bin"
#define MAP_DATAFILE_LINK "linkdata.bin"

/*----------------*/
//  INFINITE MAP  //
/*----------------*/

#define MAP_INFINITY_DATAFILE_COMMON "commondata.bin"
#define MAP_INFINITY_DATAFILE_COMMON_EXTENTION ".bin"

#define MAP_INFINITY_DATAFILE_WORLD  "worlddata.bin"
#define MAP_INFINITY_DATAFILE_LINK "linkdata.bin"

/*---------------------------------------------------------------------*/

//-------------------------Functions--------------------------------------------------------
//Perlin Noise
double zse_map_gen2d_get_solo(double x, double y, double freq, int depth);
int zse_map_GetNoiseSeed(void);
void zse_map_SetNoiseSeed(int seed);


//MAP_In && MAP_Out
ST_WORLD_t* zse_map_load_st (char name[], char *returntilesetname);
int zse_map_export_st (ST_WORLD_t *map, char name[], char tilesetname[], char newmap);

//MAP Edit/draw
void zse_map_draw_circle (ST_WORLD_t *map, int x, int y, int z ,int r , plotdata_t tile);


//MAP misc
void zse_map_delete_st(ST_WORLD_t *map);
ST_WORLD_t* zse_map_init_empty_st(int x, int y, int z);


#endif