#include "g_lib.h"

#include "r_lib.h"
#include "map_lib.h"
#include "p_lib.h"

#include "e_lib.h"
#include "t_lib.h"

#include "alloc.h"


void z_init_main(int mode)
{

	// Init Tile Properties
	TILE *tile = init_TILESET(TILESET_DEFAULT);
	
	// Declare map
	MAP map;

	if (mode == 1) 
	{

		uint8_t key = 1; // Keyboard Var
		// Initialize map stuff

		clear();
		echo();

		// Load Map
		printw("Enter Map Name\n");
		while (key != 0)
		{
			scanw("%s", map.name);
			map.world = map_read_world (map.name, &map.X, &map.Y, &key);
			if(!key)
			{
				printw("ERROR");
			}
		}
		clear();
		//printw("MAP LOADED");getch();

		// Init Player Stuff
		PLAYER pp;
		init_player(&pp);


		// Init Color Stuff
		init_pair(1, COLOR_WHITE, COLOR_WHITE);
		init_pair(2, COLOR_YELLOW, COLOR_YELLOW);
		init_pair(3, COLOR_RED, COLOR_RED);



		g_main_loop(&pp, &map, tile);


		free(map.world);
	}

	else if (mode == 2)
	{

		clear();
		echo();


		printw("Enter Map Dimention\n");
		scanw("%d %d", &map.X, &map.Y);
		printw("Enter Map Name\n");
		scanw("%s", map.name);

		map.world = malloc_2D_array_uint8(map.X, map.Y, 1, 7);


		EDITOR ee;
		ee.X = map.X>>1;
		ee.Y = map.Y>>2;
		ee.linkcount = 0;

		noecho();
		e_main_loop(&ee, &map, tile);

		free(map.world);
	}

	else if (mode == 0)
	{
		clear();
		TILE *A = init_TILESET("zak");
		refresh();
		free(A);
		getch();
	}
	free(tile);
}