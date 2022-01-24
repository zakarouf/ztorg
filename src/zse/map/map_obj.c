#include "obj.h"

#include <stdlib.h>

void zse_map_ch_obj_push__raw(
	  zse_T_Map_ObjectSetsArr *objectSets
	, z__size at
	, void *obj, z__size unitsize, z__size len, z__u8 id, char const *comment, z__int comment_size)
{
	z__Dynt oset;
	z__Dynt_newFromRaw(&oset, obj, unitsize, len, id, comment, comment_size);
	oset.lenUsed = oset.len;
	
	if(z__Arr_getLen(objectSets[at]) <= 0) {
		z__Arr_new(&objectSets[at], 8);
	}

	z__Arr_push(&objectSets[at], oset);
}

void zse_map_ch_obj_pop__raw(
	  zse_T_Map_ObjectSetsArr *objectSets
	, z__size at)
{
	if(z__Arr_getUsed(objectSets[at]) <= 0) return;
	z__Dynt_delete(&z__Arr_getTop(objectSets[at]));	
	z__Arr_pop(&objectSets[at]);
}
