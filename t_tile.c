/*
-----------------------------------------------------
This is Tile Loading Segment
----------------------------------------------------*/

#include <string.h>
#include <stdio.h>

#include "r_lib.h"
#include "t_lib.h"
#include "alloc.h"
#include "calc.h"

int t_apply_tileattr (attribute_bit_t *tile, int attr_int)
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

		TILE_ISWALK,	// 000 SPACE/FLOOR
		TILE_ISWALL,	// 001 WALL 
		TILE_ISWALL | TILE_ISMOVE,	// 002 WALL_MOVEABLE
		TILE_ISWALL | TILE_ISDEST,	// 003 WALL_BREAKABLE
		TILE_ISWALL | TILE_ISINVI,	// 004 WALL_INVISIBLE
		TILE_ISWALK | TILE_ISTOXI,	// 005 FLOOR_TOXIC
		TILE_ISWALK | TILE_ISFLUD,	// 006 FLOOL_WATER
		TILE_ISWALK,	// 007 FLOOR_NULL
	};


	for (int i = 0; i < 8; ++i)
	{
			tile[0] |= attr[attr_int];
	}



	return 0;

}

TILE *load_custom_tile (char *tile_name, uint8_t *maxtile)
{
	char tile_dir[64] = "tiles/";
	char tile_file_name_buff[72];
	char buffer[128];

	strncat(tile_dir, tile_name, 64);
	sprintf(tile_file_name_buff, "%s/%s", tile_dir, "tload");

	FILE *fp;
	fp = fopen(tile_file_name_buff, "r");

	if(fp == NULL)
	{
		printw("NO SUCH TILESET EXIST");
		refresh();
		getch();
		return NULL;
	}

	TILE *r_tile;

	fgets(buffer, 128, fp); // get version
    fgets(buffer, 128, fp); // get XY
    sscanf(buffer, "%hhd", &maxtile[0]);

    if((r_tile = malloc(sizeof(TILE) * maxtile[0])) == NULL)
    {
    	printw("NO UNABLE TO ALLOCATE REQUIRED MEMORY");
    	refresh();
		getch();
    	return NULL;
    }


    for(int i = 0; i < maxtile[0]; i++)
    {
    	fscanf(fp, "%s", r_tile[i].name_id);
    }

    fgets(buffer, 128, fp);
    fgets(buffer, 128, fp);



    for(int i = 0; i < maxtile[0]; i++)
    {
    	fscanf(fp, "%hhd", &r_tile[i].symb);
    	fscanf(fp, "%hhd", &r_tile[i].coloc);
    	fscanf(fp, "%hd", &r_tile[i].attr);

    }

    fclose(fp);
    return r_tile;
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
	else
	{
		uint8_t maxtile;
		//printw("%s", tileset_name);
		TILE  *r_v = load_custom_tile(tileset_name, &maxtile);
		return r_v;
	}

	return NULL;
}
