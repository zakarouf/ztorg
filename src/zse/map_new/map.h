#ifndef ZAKAROUF_ZSE__MAP_H
#define ZAKAROUF_ZSE__MAP_H

#include "../common.h"

/*------------------------------------------------------------------------------*/
/*---------------------------------------Types----------------------------------*/
typedef z__u8 zset__mapPlot;

/*----------MapType------------*/

typedef struct __ZSE_MAP__TYPE_
{
	z__Vint4 size; 	  			// Map size in x, y, z, w
	zset__mapPlot **chunks;

}zset__map;



// Funcs
zset__map *zse_map__createEmpty(z__u32 x, z__u32 y, z__u32 z, z__u32 w);
void zse_map__deleteChunks(zset__map *map);




/*------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------*/


#endif