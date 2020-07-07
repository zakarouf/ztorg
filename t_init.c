#include "t_lib.h"
#include "alloc.h"

#include <string.h>
#include <stdio.h>

int t_apply_tileattr (TILEATTR *tile, int attr_int)
{

	if(attr_int > 8)
	{
		return -1;
	}

	TILEATTR default_t[8] = {
	//	 ISINVI	ISWALL 	  ISMOVE ISBREAK   ISLIQUID	 ISTOXIC ISWALK
		{	0	, false	, false	, false	,	false	, false	, true	}, // 000 SPACE/FLOOR 
		{	0	, true	, false	, false	,	false	, false	, false }, // 001 WALL 
		{	0	, true	, true	, false	,	false	, false	, false }, // 002 WALL_MOVEABLE
		{	0	, true	, false	, true 	,	false	, false	, false }, // 003 WALL_BREAKABLE
		{	0	, true	, false	, true	,	false	, false	, false }, // 004 WALL_INVISIBLE
		{	0	, true	, false	, true	,	true	, true	, true 	}, // 005 FLOOR_TOXIC
		{	0	, true	, false	, true	,	true	, false	, true 	}, // 006 FLOOL_WATER
		{	0	, true	, false	, true	,	true	, false	, true 	}, // 007 FLOOR_NULL
	};



		tile[0].isinvi = default_t[attr_int].isinvi;
		tile[0].iswall = default_t[attr_int].iswall;
		tile[0].ismove = default_t[attr_int].ismove;
		tile[0].isbreak = default_t[attr_int].isbreak;
		tile[0].isliquid = default_t[attr_int].isliquid;
		tile[0].istoxic = default_t[attr_int].istoxic;
		tile[0].iswalk = default_t[attr_int].iswalk;

	return 0;

}

TILE *init_TILESET (char tileset_name[])
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
			t_apply_tileattr (&tileset[i].attr, i);
			sprintf(tileset[i].name_id,"%s", tile_desc[i]);
			tileset[i].coloc = colo[i];
			tileset[i].symb = symb[i];
			tileset[i].tex_id = 0;
		}

		return tileset;
	}

	return NULL;
}
