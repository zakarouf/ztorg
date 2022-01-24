#ifndef ZAKAROUF_ZSE__MAP_CHUNKTYPE_FIO_H
#define ZAKAROUF_ZSE__MAP_CHUNKTYPE_FIO_H

#include <stdio.h>

#include "../common.h"
#include "ch_def.h"
#include "obj.h"

//---------------------//

FILE* zse_map_ch_export_commondata__raw(
	  char const mapname[]
	, z__Vint3 chunksize);

FILE* zse_map_ch_export_chunk__raw(
	  char const *mapname
	, z__Vint3 const Chunk_cords
	, void const *chunk
	, z__size const plotsize
	, z__Vint3 const chunksize
	, zse_T_Map_ObjectSetsArr const objectSet
	, z__bool should_writeObjects);


FILE* zse_map_ch_load_commondata__raw(
	  const char mapname[]
	, z__Vint3 *chunksize);

FILE* zse_map_ch_load_chunk__raw(
	  const char mapname[]
	, z__Vint3 const Chunk_cords
	, z__size const plotsize
	, z__Vint3 const chunksize
	, void **chunk
	, zse_T_Map_ObjectSetsArr *objectSet);


int zse_map_ch_load_st__raw(
	  char const *mapname
	, z__size const plotsize
	, void ***chunk
	, z__Vint3 *chunksize
	, zse_T_Map_ObjectSetsArr **objectSet
	, z__size *objCount
	, FILE **cd_fp
	, FILE **ch_fp);


void zse_map_ch_export_st__raw(
	  char const *mapname
	, void const *chunk
	, z__size const plotsize
	, z__Vint3 const chunksize
	, zse_T_Map_ObjectSetsArr const objectSet
	, z__bool should_writeObjects
	, FILE **cd_fp
	, FILE **ch_fp);

//----------------------------------------------------------------//

#define zse_map_ch_load_st(map, name)\
	{\
		FILE *_map_ch_lod_st_cd, *_map_ch_lod_st_ch;	\
		zse_map_ch_load_st__raw(						\
				  name									\
				, sizeof(**(map)->chunks)				\
				, (void***)&(map)->chunks				\
				, &(map)->size							\
				, &(map)->objectSets					\
				, &(map)->chunkCount					\
				, &_map_ch_lod_st_ch					\
				, &_map_ch_lod_st_cd);					\
		fclose(_map_ch_lod_st_ch); fclose(_map_ch_lod_st_cd); \
	}

#define zse_map_ch_load_st_fp(map, name, ch, cd)\
	{\
		zse_map_ch_load_st__raw(						\
				  name									\
				, sizeof(**(map)->chunks)				\
				, (void***)&(map)->chunks				\
				, &(map)->size							\
				, &(map)->objectSets					\
				, &(map)->chunkCount					\
				, &cd									\
				, &ch);									\
	}


#define zse_map_ch_export_st(map, name, chunkno, shouldwriteObjects)\
	{													\
		FILE *_map_ch_exp_st_cd, *_map_ch_exp_st_ch;	\
		z__typeof(chunkno) _map_ch_exp_st_chN = chunkno;\
		if(_map_ch_exp_st_chN < (map)->chunkCount){		\
			zse_map_ch_export_st__raw(					\
				  name									\
				, (map)->chunks[_map_ch_exp_st_chN]		\
				, sizeof(**(map)->chunks)				\
				, (map)->size							\
				, (map)->objectSets[_map_ch_exp_st_chN]	\
				, shouldwriteObjects					\
				, &_map_ch_exp_st_cd					\
				, &_map_ch_exp_st_ch);					\
			fclose(_map_ch_exp_st_cd);					\
			fclose(_map_ch_exp_st_ch);					\
		}												\
	}

#define zse_map_ch_export_st_fp(map, name, chunkno, shouldwriteObjects, ch, cd)\
	{													\
		z__typeof(chunkno) _map_ch_exp_st = chunkno;	\
		if(chunkno < (map)->chunkCount{					\
			zse_map_ch_export_st__raw(					\
				  name									\
				, (map)->chunks[chunkno]				\
				, sizeof(**(map)->chunks)				\
				, (map)->size							\
				, (map)->objectSets[_map_ch_exp_st]		\
				, shouldwriteObjects					\
				, &cd									\
				, &ch);									\
		}												\
	}

#define zse_map_ch_export_commondata_fp(name, map, fp)\
	{																\
		*(fp) = zse_map_ch_export_commondata__raw(name, (map)->size);	\
	}

#define zse_map_ch_export_chunk_fp(name, cord, map, chnum, should_writeObjects, fp)\
	{												\
		*(fp) = zse_map_ch_export_chunk__raw(		\
				  name								\
				, cord								\
				, (map)->chunks[chnum]				\
				, sizeof(**(map)->chunks)			\
				, (map)->size						\
				, (map)->objectSets[chnum]			\
				, should_writeObjects);				\
	}


#define zse_map_ch_export_commondata(name, map)\
	{																	\
		fclose(zse_map_ch_export_commondata__raw(name, (map)->size));	\
	}

#define zse_map_ch_export_chunk(name, cord, map, chnum, should_writeObjects)\
	{												\
		fclose(zse_map_ch_export_chunk__raw(		\
				  name								\
				, cord								\
				, (map)->chunks[chnum]				\
				, sizeof(**(map)->chunks)			\
				, (map)->size						\
				, (map)->objectSets[chnum]			\
				, should_writeObjects));			\
	}

#define zse_map_ch_load_commondata_fp(name, map)\
		zse_map_ch_load_commondata__raw(			\
					name,							\
					&(map)->size					\
				);									\

#define zse_map_ch_load_chunk_fp(name, cords, map, chnum)\
		zse_map_ch_load_chunk__raw(				\
					name						\
				  , cords						\
				  , sizeof(**(map)->chunks)		\
				  , (map)->size					\
				  , &(map)->chunks[chnum]		\
				  , &(map)->objectSets[chnum]); \


/*------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------*/

#endif

