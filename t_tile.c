/*
-----------------------------------------------------
This is Tile Loading Segment
----------------------------------------------------*/

#include <string.h>
#include <stdio.h>

#include "r_lib.h"
#include "t_lib.h"
#include "alloc.h"

int t_apply_tileattr (TILEATTR *tile, int attr_int)
{

	if(attr_int > 8)
	{
		return -1;
	}

	TILEATTR default_t[8] = {
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



		tile[0].isinvi = default_t[attr_int].isinvi;
		tile[0].iswall = default_t[attr_int].iswall;
		tile[0].ismove = default_t[attr_int].ismove;
		tile[0].isbreak = default_t[attr_int].isbreak;
		tile[0].isliquid = default_t[attr_int].isliquid;
		tile[0].istoxic = default_t[attr_int].istoxic;
		tile[0].iswalk = default_t[attr_int].iswalk;

	return 0;

}

TILE *load_custom_tile (char tile_name[], uint8_t *maxtile)
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
		return NULL;
	}

	TILE *r_tile;

	fgets(buffer, 128, fp); // get version
    fgets(buffer, 128, fp); // get XY
    sscanf(buffer, "%hhd", &maxtile[0]);

    if((r_tile = malloc(sizeof(TILE) * maxtile[0])) == NULL){
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
    }

    fgets(buffer, 128, fp);
    fgets(buffer, 128, fp);

    for(int i = 0; i < maxtile[0]; i++)
    {
    	fscanf(fp, "%hhd", &r_tile[i].coloc);
    }

    fgets(buffer, 128, fp);
    fgets(buffer, 128, fp);


    for(int i = 0; i < maxtile[0]; i++)
    {

    	fscanf(fp, "%hhd", &r_tile[i].attr.isinvi);
		fscanf(fp, "%hhd", &r_tile[i].attr.iswall);
		fscanf(fp, "%hhd", &r_tile[i].attr.ismove);
		fscanf(fp, "%hhd", &r_tile[i].attr.isbreak); 
		fscanf(fp, "%hhd", &r_tile[i].attr.isliquid);
		fscanf(fp, "%hhd", &r_tile[i].attr.istoxic );
		fscanf(fp, "%hhd", &r_tile[i].attr.iswalk);
    }








    for(int i = 0; i < maxtile[0]; i++)
    {
    	printw("%s | %c | %d\n", r_tile[i].name_id, r_tile[i].symb, r_tile[i].coloc);
    }
    for(int i = 0; i < maxtile[0]; i++)
    {

    	printw("%hhd ", r_tile[i].attr.isinvi);
		printw("%hhd ", r_tile[i].attr.iswall);
		printw("%hhd ", r_tile[i].attr.ismove);
		printw("%hhd ", r_tile[i].attr.isbreak); 
		printw("%hhd ", r_tile[i].attr.isliquid);
		printw("%hhd ", r_tile[i].attr.istoxic );
		printw("%hhd\n", r_tile[i].attr.iswalk);
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
		TILE  *r_v = load_custom_tile(tileset_name, &maxtile);
		return r_v;
	}

	return NULL;
}
