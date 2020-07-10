#include "t_lib.h"
#include "r_lib.h"



int t_maker_main ()
{
	int tile_size = 8;
	TILE *tile = t_calloc_tile (tile_size);

	bool quit = 0;
	uint8_t key = ' ';
	int current_tile = 0;



	WINDOW *usr_bar = newwin(10, 20, getmaxy(stdscr), 10);


	while(!quit)
	{

		switch(key)
		{
			case 'l':
				wclear(usr_bar);
				r_t_show_all_tile (tile, tile_size);

				wprintw(usr_bar,"Select Tile\n>> ");
				wscanw(usr_bar, "%d", &current_tile);
				refresh();

				if(current_tile > tile_size)
				{
					current_tile = 0;
				}
				break;
			case 'x':
				clear();

				break;
		}

		key = getch();



	}

	return 0;
}
