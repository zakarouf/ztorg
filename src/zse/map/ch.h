#ifndef ZAKAROUF_ZSE__MAP_CHUNKTYPE_H
#define ZAKAROUF_ZSE__MAP_CHUNKTYPE_H

#include "../common.h"
#include "ch_def.h"

#include <stdio.h>

void zse_map_ch_createEmpty__raw(
	  z__u32 const x, z__u32 const y, z__u32 const z, z__u32 const chunkRadius
	, z__size plotsize
	, void * **chunk, zse_T_Map_ObjectSetsArr **objectSets, z__size *chunkAndObjCount);

#define zse_map_ch_createEmpty(map, x1, y1, z1, r)\
	{											\
		(map)->chunkRadius = r;					\
		zse_map_ch_createEmpty__raw(			\
			  x1, y1, z1, (map)->chunkRadius	\
			, sizeof(**(map)->chunks)			\
			, (void***)&(map)->chunks			\
			, &(map)->objectSets				\
			, &(map)->chunkCount);				\
		(map)->size.x = x1;						\
		(map)->size.y = y1;						\
		(map)->size.z = z1;						\
	}



void zse_map_ch_delete__raw(
	  void **chunks
	, zse_T_Map_ObjectSetsArr *objectSets
	, z__size Count);

#define zse_map_ch_delete(map)\
		zse_map_ch_delete__raw((void**)(map)->chunks, (map)->objectSets, (map)->chunkCount)

/*------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------*/

#endif
