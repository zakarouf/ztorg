#include "r_lib.h"
#include "map_lib.h"

int zse_r_init()
{
	initscr();
	raw();
	cbreak();

	if(!has_colors())
    {
        endwin();   /* exit Ncurses */
        puts("Terminal cannot do colors");
        return(1);
    }
    
/* initialize Ncurses colors */
    if(start_color() != OK)
    {
        endwin();
        puts("Unable to start colors.");
        return(1);
    }

    if (!(can_change_color()))
    {
        printw("Cant Change Color");
        return(1);
    }

	use_default_colors();
	curs_set(0);

	return 0;
}

void zse_r_exit()
{
	endwin();
}