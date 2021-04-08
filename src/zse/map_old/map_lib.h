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
  uint8_t _MaxChunkRadius;

  plotdata_t **chunks;

}IN_WORLD_t;


//------------------------------------------
// Common Funcs/Macro
//------------------------------------------

#endif
