#include "obj.h"

#include <stdlib.h>

void zse_map_ch_obj_push__raw(
	  zse_T_Map_ObjectSetsArr *objectSets
	, z__size at
	, void *obj, z__size unitsize, z__size len, z__u8 id)
{
	z__Dynt oset;
	z__Dynt_newFromRaw(&oset, obj, unitsize, len, id, "", 0);
	oset.lenUsed = oset.len;
	
	if(z__Arr_getLen(objectSets[at]) <= 0) {
		z__Arr_new(&objectSets[at], 8);
	}

	z__Arr_push(&objectSets[at], oset);
}
