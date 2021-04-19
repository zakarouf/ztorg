#include "test.h"

#include "../zse/zse.h"
#include "../zse/io/curses/curses.h"

#include <stdlib.h>

void t1(void)
{
		//zse_rtC__drawHorizortalGraphRuler_nocheck(stdscr, 1, 3, 8, 8, 0.23, 0);
	zse_rtC__drawHorizortalGraphRuler_nocheck(stdscr, 5, getmaxy(stdscr)-4, getmaxx(stdscr)-1, 2, 1, 2);
	napms(100);
	zse_rtC__drawVerticalGraphRuler_nocheck(stdscr, 5, 4, getmaxy(stdscr)-4, 2, 1, 0);
	napms(100);

	for (int i = 0; i < 30; ++i)
	{
		napms(200); 
		mvwaddch(stdscr, (random() % getmaxy(stdscr)), (random() % getmaxx(stdscr)), ACS_BULLET); 
		wrefresh(stdscr);
	}
	



	refresh();
	getch();
}

void stars(void)
{
	srandom(clock());
	//zse_rtC_colors_test_showall(stdscr, 0, 0); getch();

	for (int i = 0; true; i++)
	{
		mvwaddch(stdscr, (random() % getmaxy(stdscr)), (random() % getmaxx(stdscr) )

			, ACS_BULLET | COLOR_PAIR( (random() % 23) + 232  ) );
		napms((int)(random() & 7 ) );
		mvwprintw(stdscr, getmaxy(stdscr)-1, 0, "%0d |", i);


		wrefresh(stdscr);
	}

	refresh();
	wgetch(stdscr);
}

int zse___TEST___curses(void)
{
	zse_rtC_init();
	nodelay(stdscr, false);

	stars(); // demo



	zse_rtC_exit();
	return 0;
}