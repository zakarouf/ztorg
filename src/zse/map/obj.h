#ifndef ZAKAROUF_ZSE__MAP_RAWOBJECTS_H
#define ZAKAROUF_ZSE__MAP_RAWOBJECTS_H

#include "obj_def.h"


void zse_map_ch_obj_push__raw(
	  zse_T_Map_ObjectSetsArr *objectSets
	, z__size at
	, void *obj, z__size unitsize, z__size len, z__u8 id);

#define zse_map_ch_obj_push(map, at, ptr, usize, len, id)\
		zse_map_ch_obj_push__raw((map)->objectSets, at, ptr, usize, len, id)

#endif

