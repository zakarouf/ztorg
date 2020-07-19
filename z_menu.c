#include "z.h"


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
