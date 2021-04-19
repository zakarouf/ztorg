#include "curses.h"
#include <ncurses/ncurses.h>

int zse_rtC_color_initpairs(void)
{

	short pair = 0;

	for (int i = 0; i < COLORS; ++i)
	{
		init_pair(pair, i, -1);

		pair++;
	}
	// Colors Text w/ b/g from 1 to 256
	for (int i = 1; i < 128; i += 1) // Bg
	{
		for (int j = 0; j < COLORS; ++j)
		{
			init_pair(pair, j, i);
			pair++;
		}

	}

#if 0 // Checks
	short p = 258;
	init_pair(p, 5, 1);

	wcolor_set(stdscr, (0x4300) | (0x43) , NULL);
	addstr("adawd");
	wcolor_set(stdscr, 578 , NULL);
	addstr("adawdadsa\n");

	wcolor_set(stdscr, 7777 , NULL);
	addstr("adawdadsa\n");

	
	wcolor_set(stdscr, p, NULL);
	addstr("Abc\n");


	wcolor_set(stdscr, 1, NULL);
	addstr("mss\n");


	refresh();
	getch();

#endif

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


