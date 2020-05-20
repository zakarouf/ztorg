/*
ZTORG
-----------------------------------------------------
MAIN FILE.
-----------------------------------------------------
NOTES :-

-----------------------------------------------------*/
#include <ncurses.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "map_load.h"
#include "g_setup.h"

#define VERSION "0.2f"
#define MAX_OPTION 4
#define REQUIRED_TERM_X 67
#define REQUIRED_TERM_Y 35

int menu () {
	char key;
	int opt=10;
	int csry = 2, csr = 2;


	char menu_s[MAX_OPTION][13] = {
		{"PLAY"},
		{"EDITOR(NEW)"},
		{"EDITOR(OPEN)"},
		{"QUIT"},
	};
	noecho();
	clear();
	printw("ZACK v%s", VERSION);
	printw("\n/// MAIN MENU /// \n"
			"%s\n"
			"%s\n"
			"%s\n"
			"%s\n", menu_s[0], menu_s[1], menu_s[2], menu_s[3]);
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

	return opt;
}

int main(int argc, char const *argv[])
{
	int quit = 0;
	int option,eror;
	char map_name[54] ;

	struct winsize term_size;

	initscr();
	cbreak();raw();
	start_color();
	init_pair(1, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	use_default_colors();

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &term_size);

	if ((int)term_size.ws_col < REQUIRED_TERM_X || (int)term_size.ws_row < REQUIRED_TERM_Y) {

		clear();
		attron(COLOR_PAIR(2));
		printw(" WARNING YOUR TERMINAL WINDOW SIZE IS SET BELOW THE REQUIRED LIMIT \n");
		attroff(COLOR_PAIR(2));

		printw ("\n- Required Row Size : %d\n", REQUIRED_TERM_X);
    	printw ("- Required Columns Size : %d\n\n", REQUIRED_TERM_Y);
    	printw ("- Your Row Size : %d\n", term_size.ws_row);
    	printw ("- Your Columns Size : %d\n", term_size.ws_col);

    	printw ("\nPress Any Key to Exit");
    	getch();

    	refresh();
    	endwin();
    	return -1;
	}

	while(quit == 0){
		option = menu();
		clear();

		if(option == 3){
			quit = 1;
		}
		else if(option == 0){
			echo();
			mvprintw(0, 0,"Enter Map Name");
			mvscanw(1, 0,"%s", map_name);
			eror = process_map_file(map_name);clear();
			if (eror == 0)
			{
				g_setup_p('n');
			}
			
		}
		else if(option == 1){
			map_autogen ();g_setup_p('e');
		}
		else if (option == 2) {
			mvprintw(0, 0,"Enter Map Name");
			mvscanw(1, 0,"%s", map_name);
			eror = process_map_file_ED(map_name);clear();
			if(eror == 0){
				g_setup_p('e');
			}
		}
		refresh();
	}
	endwin();
	return 0;
}
