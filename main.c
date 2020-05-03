/*
ZTORG
-----------------------------------------------------
MAIN FILE.
-----------------------------------------------------
# v0.2c
	- Reworked the Whole stuff In Ncurses Lib
# v0.2b
	- Added Linker To Maps now you can Link one map 
		with others.
	- Upgraded Color function. Full 8bit color Support
# v0.2a
	- Code is Now Clean (To an Extent).
 	- EDITOR is now here and fully functional.
-----------------------------------------------------*/
#include <ncurses.h>
#include "map_load.h"
#include "g_setup.h"

#define VERSION "0.2c"
#define MAX_OPTION 3

int menu () {
	char key;
	int opt=10;
	int csry = 2, csr = 2;


	char menu_s[MAX_OPTION][12] = {
		{"PLAY"},
		{"EDITOR"},
		{"QUIT"},
	};
	//initscr();
	noecho();
	clear();
	printw("ZACK v%s", VERSION);
	printw("\n/// MAIN MENU /// \n"
			"%s\n"
			"%s\n"
			"%s\n", menu_s[0], menu_s[1], menu_s[2]);
	move(csry, 0);

	while(1) {
		csr = csry;
		key = getch();
		switch(key){
			case 'w':
				csry--;break;
			case 's':
				csry++;break;
			case 'e':
				return csry-2;
			default:
				break;
		}
		if(csry-2 >= MAX_OPTION || csry-2 < 0){csry = csr;}
		move(csry, 0);
		refresh();
	}

	refresh();
	clear();
	//endwin();

	return opt;
}

int main(int argc, char const *argv[])
{
	int quit = 0;
	int option,eror;
	char map_name[54] ;


	initscr();
	while(quit == 0){
		option = menu();
		clear();

		if(option == 2){
			quit = 1;
		}
		else if(option == 0){
			echo();
			mvprintw(0, 0,"Enter Map Name");
			mvscanw(1, 0,"%s", map_name);
			eror = process_map_file(map_name);clear();
			if (eror == 0)
			{
				setup_p('n');
			}
			
		}
		else if(option == 1){
			map_autogen ();setup_p('e');
		}
		refresh();
	}
	endwin();
	return 0;
}