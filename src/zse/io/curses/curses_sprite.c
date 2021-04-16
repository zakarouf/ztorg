#include <ncurses/ncurses.h>
#include "curses_sprite.h"

int zse_rtC_spritePrintAll
(
	WINDOW *win,
	int startX,
	int startY,
	zset__SpriteChar* spr,
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
				for (int i = 0; i < spr->x; ++i)
				{
					for (int j = 0; j < spr->x; ++j)
					{
							attrset(COLOR_PAIR(spr->colormap[zse_xyz3Dto1D(j, i, atframe, spr->x, spr->y)]));
							mvwaddch(win,i+startY, j+startX, spr->plot[zse_xyz3Dto1D(j, i, atframe, spr->x, spr->y)]);
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

__attribute__((always_inline)) inline int zse_rtC_spriteSmooth(float pos, float slength)
{
	return (pos * slength)+(pos*1/slength) -slength;
}

void zse_rtC_sprite__Print
(
	WINDOW *win,
	int startX,
	int startY,
	zset__SpriteChar* spr,
	const int atframe
)
{
	zset__spritechtype *sprp = &spr->plot[zse_xyz3Dto1D(0, 0, atframe, spr->x, spr->y)];
	z__u16 *color = &spr->colormap[zse_xyz3Dto1D(0, 0, atframe, spr->x, spr->y)];

	for (int i = 0; i < spr->y; ++i)
	{
		for (int j = 0; j < spr->x; ++j)
		{
			//if((*sprp) != 0xFF){
				wattrset(win, COLOR_PAIR(*color) );
				mvwaddch(win, startY + i, startX + j, *sprp);
			//}

			color++;
			sprp++;
		}
	}
}

void zse_rtC__sprite__sChar_PrintPadEnd
(
	WINDOW *win,
	int startX,
	int startY,
	int padxend,
	int padyend,
	zset__SpriteChar* spr,
	const int atframe
)
{
	int endx = (spr->x > getmaxx(win)- padxend ? getmaxx(win)- padxend: spr->x);
	int endy = (spr->y > getmaxy(win)- padyend ? getmaxy(win)- padyend: spr->y);

	zset__spritechtype *sprp = &spr->plot[zse_xyz3Dto1D(0, 0, atframe, spr->x, spr->y)];
	z__u16 *color = &spr->colormap[zse_xyz3Dto1D(0, 0, atframe, spr->x, spr->y)];
	for (int i = 0; i < endy; ++i)
	{
		for (int j = 0; j < endx; ++j)
		{
			//if((*sprp) != 0xFF){
				wcolor_set(win, *color, NULL );
				mvwaddch(win, startY + i, startX + j, (*sprp));
			//}

			color++;
			sprp++;
		}
	}

	wcolor_set(win, 0, NULL);
}