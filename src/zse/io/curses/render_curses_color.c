#include "curses.h"
#include <ncurses/ncurses.h>

int zse_rtC_color_initpairs(void)
{

	// Colors Text w/ Black b/g from 0 to 256
	for (int i = 0; i < COLORS; ++i)
	{
		init_pair(i, i, -1);
	}

	return 0;
}

int zse_rtC_colors_test_showall(WINDOW *win, int atx, int aty)
{
	int tmpx = atx;
	for (int i = 0; i < COLORS; ++i)
	{
		if (i % 6 == 0)
		{
			aty++;
			atx = tmpx;
		}

		wattrset(win, COLOR_PAIR(i));
		mvwprintw(win, aty, atx*5, " %3d ", i);
		wattrset(win, A_NORMAL);
		atx++;

		
	}

	zse_rtC_color_initpairs();

	return 0;
}


