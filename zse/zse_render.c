#include "zse_render.h"
#include "sprites_lib.h"

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

int zse_render_sprite
(
	WINDOW *win,
	int startX,
	int startY,
	SPRITES_t* spr,
	int startframe,
	int endframe
)
{
	clock_t start_time, end_time;
	double time_taken;
	int atframe = 0;



	for(;;)
	{
		start_time = clock();
		for(;;)
		{
			end_time = clock();
			time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;

			if(time_taken > spr->dt)
			{
				for (int i = 0; i < spr->Y; ++i)
				{
					for (int j = 0; j < spr->X; ++j)
					{
						attrset(COLOR_PAIR(spr->plot[getindex3d(j, i, atframe, spr->X, spr->Y)]>>8));
						mvwaddch(win,i+startY, j+startX, spr->plot[getindex3d(j, i, atframe, spr->X, spr->Y)]&0xFF);
						attrset(A_NORMAL);
					}
				}
				atframe++;
				goto NEXT_FRAME;

			}
		}
	NEXT_FRAME:
		wrefresh(win);
		if(atframe >= spr->frames)
		{
			goto FUNTION_END;
		}
	}
	

FUNTION_END:
	return 0;
}
