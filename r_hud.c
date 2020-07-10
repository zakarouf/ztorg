#include "r_lib.h"

void r_t_show_all_tile (TILE *tile, int t_size)
{
	int x, y, p = 0, q = 0;
	getmaxyx(stdscr, y, x);

	for (int i = 0; i < t_size; ++i)
	{
		mvprintw(p, q, "[%d]%s", i, tile[i].name_id);
		p++;
		if(p == y - 10){
			p = 0;
			q += 10;
		}
	}
}