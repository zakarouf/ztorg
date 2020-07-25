/*
-----------------------------------------------------
This is Tile Loading Segment
----------------------------------------------------*/

#include <string.h>

#include "r_lib.h"
#include "t_lib.h"
#include "t_io.h"
#include "alloc.h"

TILE* t_malloc_initempty_tile (int t_size)
{
	TILE *tile = malloc(sizeof(TILE) * t_size);

	for (int i = 0; i < t_size ; i++)
	{
		sprintf(tile[i].name_id, "NULL");
		//tile[i].tex_id = 0;
		tile[i].symb = 32;
		tile[i].coloc = 0;
		tile[i].attr = 0;
	}
	
	return tile;
}

TILE* t_realloc_initempty_tile (int *old_size, int new_size, TILE *tile)
{
	TILE *tmp = tile;
	tmp = realloc (tile, sizeof(TILE) * new_size);

	if(tmp == NULL)
	{
		// Reallocation Fails Do Nothing. Return As Is
		return tile;
	}

	else {

		// Realloction Success. Initilize new formed tiles.
		for (int i = *old_size; i < new_size ; i++)
		{
			sprintf(tmp[i].name_id, "NULL");
			//tile[i].tex_id = 0;
			tmp[i].symb = 32;
			tmp[i].coloc = 0;
			tmp[i].attr = 0;
		}
		
		*old_size = new_size;
		return tmp;
	}
}

static int t_apply_default_tileattr (attribute_bit_t *tile, int attr_int)
{

	if(attr_int > 8)
	{
		return -1;
	}
/*
	TILEATTR default_tile_attr_a[8] = {
	//	 ISINVI	  ISWALL  ISMOVE ISBREAK   ISLIQUID	 ISTOXIC ISWALK
		{ false , false	, false	, false	,	false	, false	, true	}, // 000 SPACE/FLOOR
		{ false , true	, false	, false	,	false	, false	, false }, // 001 WALL 
		{ false , true	, true	, false	,	false	, false	, false }, // 002 WALL_MOVEABLE
		{ false , true	, false	, true 	,	false	, false	, false }, // 003 WALL_BREAKABLE
		{ true  , true	, false	, true	,	false	, false	, false }, // 004 WALL_INVISIBLE
		{ false , false	, false	, true	,	true	, true	, true 	}, // 005 FLOOR_TOXIC
		{ false , false	, false	, true	,	true	, false	, true 	}, // 006 FLOOL_WATER
		{ false , false	, false	, true	,	true	, false	, true 	}, // 007 FLOOR_NULL
	};
*/

	attribute_bit_t attr[64] = {

		TILE_ISWALK,				// 000 SPACE/FLOOR
		TILE_ISWALL,				// 001 WALL 
		TILE_ISWALL | TILE_ISMOVE,	// 002 WALL_MOVEABLE
		TILE_ISWALL | TILE_ISDEST,	// 003 WALL_BREAKABLE
		TILE_ISWALL | TILE_ISINVI,	// 004 WALL_INVISIBLE
		TILE_ISWALK | TILE_ISTOXI,	// 005 FLOOR_TOXIC
		TILE_ISWALK | TILE_ISFLUD,	// 006 FLOOL_WATER
		TILE_ISWALK,				// 007 FLOOR_NULL
	};


	for (int i = 0; i < 8; ++i)
	{
			tile[0] |= attr[attr_int];
	}



	return 0;

}


TILE *init_TILESET (char tileset_name[], int *maxtile)
{


	if(strcmp(tileset_name, TILESET_DEFAULT) == 0)
	{

		TILE *tileset = malloc(sizeof(TILE) * 8);

		char tile_desc[8][16] = {
			{"Floor/Space"},
			{"WALL"},
			{"WALL_MOVEABLE"},
			{"WALL_BREAKABLE"},
			{"WALL_INVISIBLE"},
			{"FLOOR_TOXIC"},
			{"FLOOR_WATER"},
			{"FLOOR_NULL"},
		};

		uint8_t 
		symb[8] = 
		{'.', '#', '#', '#', '#', '%', '~', ' '},
		colo[8] = 
		{1, 1, 2, 1, 1, 1, 1, 1};

		for(int i = 0; i < 8; i++)
		{
			t_apply_default_tileattr (&tileset[i].attr, i);
			sprintf(tileset[i].name_id,"%s", tile_desc[i]);
			tileset[i].coloc = colo[i];
			tileset[i].symb = symb[i];
			//tileset[i].tex_id = 0;
		}

		return tileset;


	}
	else
	{
		if(maxtile == NULL)
		{
			int tmp;
			return load_custom_tile(tileset_name, &tmp);
		}
		//printw("%s", tileset_name);
		return load_custom_tile(tileset_name, maxtile);
	}

	return NULL;
}
