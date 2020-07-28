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
				z_init_main(Ztg_PLAY_NORMAL); //Main Game
				break;
			case 2:
				z_init_main(Ztg_EDITOR_NEW); // Editor
				break;
			case 3:

				break;
			case 4:
				z_init_main(Ztg_TEDITOR_NEW);
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
				z_init_main(Ztg_DEBUGMODE); //DEBUG
			default:
				break;
		}
	}

	endwin();
	return 0;
}