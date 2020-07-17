#include "t_lib.h"
#include "r_lib.h"
#include "t_io.h"
#include "alloc.h"

#include <string.h>

#define ATTR_TXT_RAW "//////Attributes//////\n\n INVI\n WALL\n MOVE\n DEST\n FLUD\n TOXI\n WALK\n FUNC\n"



int t_selectile_raw (TILE *tile, int t_size, int *t_select)
{
	clear();
	int y = getmaxy(stdscr), pagestart = 0, exit = 0;
	char key = ' ';

	while(!exit) 
	{

		switch(key)
		{
			case 'w':
				pagestart--;
				if(pagestart < 0)
				{
					pagestart = 0;
				}
				break;
			case 's':
				pagestart++;
				if(pagestart >= t_size)
				{
					pagestart = t_size -1;
				}
				break;
			case 'e':
				echo();
				mvprintw(y-1, 0, ">> ");refresh();
				mvscanw(y-1, 3, "%d", &t_select[0]);
				noecho();
			case 'q':
				return 0;
				break;
		}


		clear();
		for (int i = pagestart; i < y + pagestart; ++i)
		{
			if (i < t_size)
			{
				mvprintw(i - pagestart, 0, "[%d] %32s|", i , tile[i].name_id);	
			}

		}

		refresh();
		key = getch();
	}

	return 0;
}


void t_main_scr (TILE *tile, int c_tile)
{
	clear();
	char tf[2][6] = {"False", "True"};
	mvprintw(1, 1, "Current Tile -- %s\n   |-- ID.%3d", tile[c_tile].name_id, c_tile);
	mvprintw(4, 1, 	"%s", ATTR_TXT_RAW);

	int cur = 6;
	for (int i = 0; i < 8; ++i)
	{
		mvprintw(cur, 7, "%s", tf[  (tile[c_tile].attr &(0x0000000000000001<< i)) ? 1:0  ]);
		cur++;
	}

	mvprintw(getmaxy(stdscr) -2, 0, "[e]Expand MaxTiles | [s]Change TileName | [x]Edit Attribute | [c]Select Tile");

}


int t_edit_attribute (TILE *tile, int current_tile)
{
	clear();
	int y = getmaxy(stdscr);
	char tf[2][6] = {"False", "True"};
	char attr_name[MAX_ATTRIBUTE][16] = {
		"Invisble",
		"Impassable",
		"Movable",
		"Destructable",
		"Fluid",
		"Toxic",
		"Floor",
		"NOTSET",
		"NOTSET",
		"NOTSET",
		"NOTSET",
		"NOTSET",
		"NOTSET",
		"NOTSET",
		"NOTSET",
		"NOTSET",
	};

	mvaddstr(1, 1, "//////Edit Atributes//////");

	int curi = 3, pagestart = 0, exit = 0;
	char key = ' ';

	while(!exit)
	{
		clear();
		for (int i = pagestart; i < y+pagestart; ++i)
		{
			if (i + curi <= y && i < MAX_ATTRIBUTE)
			{
				mvprintw(i + curi - pagestart, 1, "[%d] %24s |> %5s %x", i-pagestart, attr_name[i - pagestart], tf[  (tile[current_tile].attr &(0x0001<< i)) ? 1:0 ], tile[current_tile].attr &(0x1<< i));
			}
			
		}
		refresh();

		key = getch();

		switch(key)
		{
			case 'w':
				pagestart--;
				if(pagestart < 0)
				{
					pagestart = 0;
				}
				break;
			case 's':
				pagestart++;
				if(pagestart >= MAX_ATTRIBUTE)
				{
					pagestart = MAX_ATTRIBUTE -1;
				}
				break;
			case 'e':
				echo();
				mvprintw(y-1, 0, "Attribute No. >> ");refresh();
				uint8_t si;
				mvscanw(y-1, 18, "%d", &si);

				tile[current_tile].attr ^= 0x0000000000000001 << si;

				noecho();
				break;
			case 'q':
				return 0;
				break;
		}
	}
	return 0;
}


int t_maker_main ()
{
	int tile_size = 8;
	TILE *tile = t_malloc_initempty_tile (tile_size);

	bool quit = 0;
	uint8_t key = ' ';
	int current_tile = 0;
	uint16_t y, x;
	getmaxyx(stdscr, y, x);


	while(!quit)
	{

		switch(key)
		{
			case 'c':
				t_selectile_raw(tile, tile_size, &current_tile);
				refresh();
				break;
			case 'x':
				t_edit_attribute (tile, current_tile);
				refresh();
				break;
			case 's':
				echo();
				mvprintw(y-1, 0, "New Tile Name >> ");
				mvscanw(y-1, 17, "%s", tile[current_tile].name_id);
				noecho();
				break;
			case 'e':
				echo();
				mvprintw(y-1, 0, "Expand Tile : Enter New size >> ");
				uint8_t newsize;
				mvscanw(y-1, 32, "%hhd", &newsize);
				tile = t_realloc_initempty_tile(tile_size, newsize, tile);
				tile_size = newsize;
				noecho();
				break;
			case 'q':
				echo();
				clear();
				mvaddstr(y/2, x/2 - 9, "Really Quit? (Y/n)");
				refresh();
				uint8_t cuit = getch();
				if(cuit == 'Y')
				{	
					free(tile);
					quit |= 1;
					return 0;
				}
				noecho();
			case '0':
				echo();
				clear();

				char name[16];
				mvaddstr(y/2, x/2 - 18, "Save Tile Set As / Enter 0 To Cancle");
				mvaddstr(y/2 +1, x/2 - 18, ">> ");
				mvscanw(y/2 +1, x/2 - 15, "%s", name);

				if(strcmp(name, "0") != 0)
				{
					t_create_tile (tile, name, tile_size, true);
				}
				
				noecho();
				break;

		}

		

		t_main_scr (tile, current_tile);
		refresh();
		key = getch();

	}

	return 0;
}
