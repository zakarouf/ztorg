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

	enum {MAX_MENU_ITEMS = 4};

	char menu_txt[MAX_MENU_ITEMS][16] = 
	{
		"PLAY",
		"EDITOR (NEW)",
		"EDITOR (OPEN)",
		"QUIT"
	};

	clear();
	printw("ZTORG\n----------------------\n");
	for (int i = 0; i < MAX_MENU_ITEMS; ++i)
	{
		printw("%d. %s\n", i, menu_txt[i]);
	}

	refresh();
	
	while(!execute)
	{
		mvprintw(MAX_MENU_ITEMS + 2, 0, ">>                    ");

		option = confirm;
		option -= 48;

		if(option < MAX_MENU_ITEMS && option >= 0)
		{
			mvprintw(MAX_MENU_ITEMS + 2, 3, "%s\nPress 'e' to Confirm", menu_txt[option]);
			mvprintw(MAX_MENU_ITEMS + 3, 0, "                    ");
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
			case 0:
				z_init_main(1);
				break;
			case 1:
				z_init_main(2);
				break;
			case 3:
				quit = 1;
				break;
			default:
				break;
		}
	}

	endwin();
	return 0;
}