/*
ZTORG
-----------------------------------------------------
MAIN FILE.
-----------------------------------------------------
NOTES :-

-----------------------------------------------------*/

#include "z.h"
#include "z_setup.h"


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