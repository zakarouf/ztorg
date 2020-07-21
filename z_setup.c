#include "g_lib.h"

#include "r_lib.h"
#include "map_lib.h"
#include "p_lib.h"

#include "e_lib.h"
#include "t_lib.h"

#include "alloc.h"


int z_init_main(int mode)
{
	


	if (mode == 1) //MAIN GAME
	{
		// Declare map
		MAP map;

		uint8_t key = 1; // Keyboard Var
		// Initialize map stuff

		clear();
		echo();

		// Load Map
		printw("Enter Map Name\n");

		char *tilename = malloc(sizeof(char) * 64);

		while (key != 0)
		{
			scanw("%s", map.name);
			
			map.world = map_read_world (map.name, &map.X, &map.Y, tilename, &key);

			if(!key)
			{
				printw("ERROR");
			}
		}
		clear();
		//printw("MAP LOADED");getch();

		// Init Tile Properties
		TILE *tile;
		if((tile = init_TILESET(tilename, NULL)) == NULL)
		{
			printw("Could Not Create Tileset");
			refresh();
			getch();
			return 6;
		}
		free(tilename);

		// Init Player Stuff
		PLAYER *pp;
		pp = init_player(JACK);


		// Init Color Stuff
		init_pair(1, COLOR_WHITE, COLOR_WHITE);
		init_pair(2, COLOR_YELLOW, COLOR_YELLOW);
		init_pair(3, COLOR_RED, COLOR_RED);



		g_main_loop(pp, &map, tile);

		free(tile);
		free(map.world);
	}

	else if (mode == 2) // MAP EDITOR
	{

		clear();
		echo();

		char tilename[32];

		// Declare map & Tile
		MAP map;
		TILE *tile;


		// Input Stuff
		mvaddstr(1, 1,"Enter Map Name ");
		mvaddstr(2, 1,"Enter Map Dimention X ");
		mvaddstr(3, 1,"Enter Map Dimention Y ");
		mvaddstr(5, 1,"Enter Tile Set Name ");

		mvaddstr(1, 17, "<_________________>");
		mvscanw(1, 18, "%s", map.name);

		mvaddstr(2, 24, ">>");
		mvscanw(2, 27, "%d", &map.X);

		mvaddstr(3, 24, ">>");
		mvscanw(3, 27, "%d", &map.Y);

		mvaddstr(5, 21, "<________________>");
		mvscanw(5, 22, "%s", tilename);
		
		

		// Init Tile Properties & Making Map
		int maxtile;
		tile = init_TILESET(tilename, &maxtile);
		map.world = malloc_2D_array_uint8(map.X, map.Y, 1, 7);


		// Creating Player
		EDITOR ee;
		ee.X = map.X>>1;
		ee.Y = map.Y>>2;
		ee.linkcount = 0;


		// Initializing Main Loop
		noecho();
		e_main_loop(&ee, &map, tile, maxtile, tilename);

		free(tile);
		free(map.world);
	}

	else if (mode == 4) // TILE MAKE
	{
		t_maker_main ();
	}

	else if (mode == 5)
	{

	}

	else if (mode == 0)
	{
		clear();
		int a;
		TILE *A = init_TILESET("DEFAULT_EXT", &a);
		refresh();
		free(A);
		getch();
	}

	return 0;
	
}