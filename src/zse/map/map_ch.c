#include <stdlib.h>

#include "ch.h"
#include <z_/types/autotype.h>

#define zset__mapChPlot zse_T_MapCh_Plot

inline void zse_map_ch_createEmpty__raw(
	  z__u32 const x, z__u32 const y, z__u32 const z, z__u32 const chunkRadius
	, z__size plotsize
	, void * **chunk, zse_T_Map_ObjectSetsArr **objectSets, z__size *chunkAndObjCount)
{
	*chunkAndObjCount = ZSE_map__CH_calcChunk_Count_fromRad__num(chunkRadius);
	*objectSets = z__New0(**objectSets, *chunkAndObjCount);

	*chunk = z__CALLOC(sizeof(*chunk), *chunkAndObjCount);
	for(int i = 0; i < *chunkAndObjCount; i++) {
		*chunk[i] = z__CALLOC(plotsize, x * y * z);
	}
}


inline void zse_map_ch_delete__raw(
	  void **chunks
	, zse_T_Map_ObjectSetsArr *objectSets
	, z__size Count)
{
	for(z__size i = 0; i < Count; i++){
		z__FREE(chunks[i]);
		if(objectSets[i].len > 0){
			for(int j = 0; j < objectSets[i].lenUsed; j++){
				if(objectSets[i].data[j].len > 0) {
					z__Dynt_delete(&objectSets[i].data[j]);
				}
			}
			z__Arr_delete(&objectSets[i]);
		}
	}
	z__FREE(chunks);
	z__FREE(objectSets);
}

