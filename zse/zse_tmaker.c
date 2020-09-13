#include "zse.h"

#include <string.h>

#define ATTR_TXT_RAW "//////Attributes//////\n\n INVI\n WALL\n MOVE\n DEST\n FLUD\n TOXI\n WALK\n FUNC\n"


static int t_selectile_raw (TILE_t *tile, int t_size, int *t_select)
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
				mvprintw(y-1, 0, ">>                    ");refresh();
				mvscanw(y-1, 3, "%d", t_select);
				noecho();
				break;
			case 'q':
				return 0;
				break;
		}


		clear();
		for (int i = pagestart; i < y + pagestart -2; ++i)
		{
			if (i < t_size)
			{
				mvprintw(i - pagestart+1, 0, "[%d] %32s|", i , tile[i].name_id);	
			}

		}

		mvprintw(y-2, 0, "[e]Enter TileNum | [q]Confirm || Current : <%d> |%s|", *t_select, tile[t_select[0]].name_id);

		refresh();
		key = getch();
	}

	return 0;
}

static int t_edit_attribute (TILE_t *tile, int current_tile)
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

static void t_main_scr (TILE_t *tile, int c_tile, int tile_size)
{
	clear();
	static char tf[2][6] = {"False", "True"};
	mvprintw(1, 1, "Current Tile -- %s\n   |-- ID.%3d \\\\ Symb. %c", tile[c_tile].name_id, c_tile, tile[c_tile].symb);
	mvprintw(4, 1, ATTR_TXT_RAW);

	int cur = 6;
	for (int i = 0; i < 8; ++i)
	{
		mvprintw(cur, 7, "%s", tf[  (tile[c_tile].attr &(0x0000000000000001<< i)) ? 1:0  ]);
		cur++;
	}

	mvprintw(getmaxy(stdscr) -2, 0, "[x]Expand MaxTiles | [n]Change TileName | [e]Edit Attribute | [c]Change Tile || MaxT %d", tile_size);

}

int zse_tile_maker_main ()
{
	int tile_size = 8;
	TILE_t *tile = zse_tile_intiempty(8);

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
			case 'e':
				t_edit_attribute (tile, current_tile);
				refresh();
				break;
			case 'n':
				echo();
				mvprintw(y-1, 0, "New Tile Name >> ");
				mvscanw(y-1, 17, "%s", tile[current_tile].name_id);
				noecho();
				break;
			case 'x':
				echo();
				mvprintw(y-1, 0, "Expand Tile : Enter New size >> ");
				unsigned int newsize;
				mvscanw(y-1, 32, "%d", &newsize);
				tile = zse_tile_realloc(&tile_size, newsize, tile);
				noecho();
				break;
			case 'w':
				echo();
				mvprintw(y-1, 0, "Change Map Symb >> ");
				mvscanw(y-1, 19, "%c", &tile[current_tile].symb);
				break;
			case 'q':
				echo();
				clear();

				mvaddstr(y/2, x/2 - 9, "Really Quit? (Y/n)");
				refresh();

				if(getch() == 'Y')
				{	
					free(tile);
					quit |= 1;
					return 0;
				}

				noecho();
				break;
			case '0':
				echo();
				clear();

				char name[16];
				mvaddstr(y/2, x/2 - 18, "Save Tile Set As / Enter 0 To Cancle");
				mvaddstr(y/2 +1, x/2 - 18, ">> ");
				mvscanw(y/2 +1, x/2 - 15, "%s", name);

				if(strcmp(name, "0") != 0)
				{
					zse_tile_export(tile, tile_size ,name, true);
				}
				
				noecho();
				break;
			default:
				break;

		}

		

		t_main_scr (tile, current_tile, tile_size);
		refresh();
		key = getch();

	}

	return 0;
}