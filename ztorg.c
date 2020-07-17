/*
ZTORG
-----------------------------------------------------
MAIN FILE.
-----------------------------------------------------
NOTES :-

-----------------------------------------------------*/

#include <stdint.h>
#include <ncurses.h>

#include "z_setup.h"


int main_menu (void) {

	uint8_t option;
	char confirm = 0;
	bool execute = 0;

	enum {MAX_MENU_ITEMS = 5};

	char menu_txt[MAX_MENU_ITEMS][16] = 
	{
		"Quit",
		"Play",
		"Editor -> New",
		"Editor -> Open",
		"TileEd -> New"
	};

	clear();
	printw("ZTORG\n----------------------\n");
	for (int i = 1; i < MAX_MENU_ITEMS; ++i)
	{
		if (i == 2)
		{
			printw("\n////Maker////\n");
		}
		printw("\n%d. %s", i, menu_txt[i]);

	}


	mvprintw(getmaxy(stdscr) - 1, 0, "%s(0)", menu_txt[0]);
	refresh();
	
	while(!execute)
	{
		mvprintw(MAX_MENU_ITEMS + 2 +3, 0, ">>                    ");

		option = confirm;
		option -= 48;

		if(option < MAX_MENU_ITEMS && option >= 0)
		{
			mvprintw(MAX_MENU_ITEMS + 2 +3, 3, "%s\nPress 'e' to Confirm", menu_txt[option]);
			mvprintw(MAX_MENU_ITEMS + 3 +3, 0, "                    ");
		}

		refresh();
		confirm = getch();

		if(confirm == 'e' && option >= 0 && option < MAX_MENU_ITEMS)
		{
			execute = 1;
		}
	}

	clear();
	return option;
}


int main (int argc, char const *argv[])
{

	bool quit = 0;

	initscr();
	raw();
	cbreak();
	start_color();
	use_default_colors();
	curs_set(0);

	noecho();

	while (!quit) 
	{
		int option = main_menu();

		switch(option)
		{
			case 1:
				z_init_main(1); //Main Game
				break;
			case 2:
				z_init_main(2); // Editor
				break;
			case 3:

				break;
			case 4:
				z_init_main(4);
				break;
			case 5:

				break;
			case 6:

				break;
			case 7:

				break;
			case 8:

				break;

		///////////////////////
			case 0:
				quit = 1;
				break;
			case 9:
				z_init_main(0); //DEBUG
			default:
				break;
		}
	}

	endwin();
	return 0;
}