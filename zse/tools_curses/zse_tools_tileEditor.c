/*-----------------------------------------------------
			Tile Editer For ZSE
//---------------------------------------------------//

	+-----------------------------------------------+
	|												|
	+-----------------------------------------------+

	NOTE:

-----------------------------------------------------*/


#include "zse_tools.h"

#include "../tiles/tile_lib.h"
#include "../r_curses/r_lib.h"
#include "../sys/sys.h"

#include <string.h>

#define ATTR_TXT_RAW "//////Attributes//////\n\n INVI\n WALL\n MOVE\n DEST\n FLUD\n TOXI\n WALK\n FUNC\n"

static int _t_edit_attribute (TILE_t *tile, int current_tile)
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

static void _t_main_scr (TILE_t *tile, int c_tile, int tile_size)
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

static int _t_selectile_raw (TILE_t *tile, int t_size)
{
	char **tname = zse_malloc_2D_array_char(ZSE_MAX_FILENAME_SIZE, t_size);
	for (int i = 0; i < t_size; ++i)
	{
		sscanf(tile[i].name_id, "%s", tname[i]);
	}
	return zse_r_selectListS(stdscr, 0, 0, tname, t_size, "   ");

}

int zse_tool_tileEditor_main ()
{
	TILESET_t t = zse_tileset_init ();

	char quit = 0;
	uint8_t key = ' ';
	int current_tile = 0;
	uint16_t y, x;
	getmaxyx(stdscr, y, x);


	while(!quit)
	{

		switch(key)
		{
			case 'c':
				current_tile = _t_selectile_raw(t.tile, t.tsize);
				refresh();
				break;
			case 'e':
				_t_edit_attribute (t.tile, current_tile);
				refresh();
				break;
			case 'n':
				echo();
				mvprintw(y-1, 0, "New Tile Name >> ");
				mvscanw(y-1, 17, "%s", t.tile[current_tile].name_id);
				noecho();
				break;
			case 'x':
				echo();
				mvprintw(y-1, 0, "Expand Tile : Enter New size >> ");
				size_t newsize;
				mvscanw(y-1, 32, "%d", &newsize);
				zse_tileset_chsize(&t, newsize);
				noecho();
				break;
			case 'w':
				echo();
				mvprintw(y-1, 0, "Change Map Symb >> ");
				mvscanw(y-1, 19, "%c", &t.tile[current_tile].symb);
				break;
			case 'q':
				echo();
				clear();

				mvaddstr(y/2, x/2 - 9, "Really Quit? (Y/n)");
				refresh();

				if(getch() == 'Y')
				{	
					free(t.tile);
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
					zse_tileset_exp (name, &t, TRUE);
				}
				
				noecho();
				break;
			default:
				break;

		}

		

		_t_main_scr (t.tile, current_tile, t.tsize);
		refresh();
		key = getch();

	}

	return 0;
}