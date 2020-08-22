#include "r_lib.h"

void r_render_show2dworld
(
	WINDOW *win,
	plotdata_t *chunk,
	const int Xsize,
	const int Ysize,
	const int Zsize,
	int x,
	int y,
	int z,
	const int resizeX,
	const int resizeY
)
{
	const int screensizeX = getmaxx(win) -(resizeX);
	const int screensizeY = getmaxy(win) -(resizeY);

	int cursor_y = 0, cursor_x = 0;

	int i = y - (int)(screensizeY>>1) -1, j;

	int end_i = y + (int)(screensizeY>>1) +1;
	int end_j = x + (int)(screensizeX>>1) +1;

	if (end_i >= Ysize) {end_i = Ysize; i = Ysize - screensizeY -1;}
	if (i < 0) {
		i = 0;
		if(screensizeY <= Ysize){
			end_i = screensizeY+1;
		}
	}

	const int lower_z = (z-1>=0)? z-1:0;

	wclear(win);

	for (; i < end_i; ++i)
	{
		j = x - (int)(screensizeX>>1) -1;
		if (end_j >= Xsize) {end_j = Xsize; j = Xsize - screensizeX -1;}
		if (j < 0) {j = 0;
			if(screensizeX <= Xsize){
				end_j = screensizeX+1;
			}
		}

		wmove(win ,cursor_y, cursor_x);

		for (; j < end_j; ++j)
		{
			if (chunk[getindex3d(j, i, z, Xsize, Ysize)])
			{
				addch('#');
			}
			else 
			{
				if (chunk[getindex3d(j, i, lower_z, Xsize, Ysize)])
				{
					addch('.');
				}

				else
				{
					addch(' ');
				}
			}

			if(j == x && i == y)
			{
				addstr("\b@");
			}

		}
		printw("| %d", i);
		cursor_y++;
	}

	// Add Cursor
	wrefresh(win);
}