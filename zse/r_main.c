#include "r_lib.h"
#include "map_lib.h"

void r_init()
{
	initscr();
	raw();
	cbreak();
	start_color();
	use_default_colors();
	curs_set(0);
}

void r_exit()
{
	endwin();
}