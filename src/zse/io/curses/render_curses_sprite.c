#include <ncurses/ncurses.h>
#include "render_curses_sprite.h"

int zse_rtC_spritePrintAll
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
						if((spr->plot[zse_xyz3Dto1D(j, i, atframe, spr->X, spr->Y)]&0xFF) != 0xFF){
							attrset(COLOR_PAIR(spr->plot[zse_xyz3Dto1D(j, i, atframe, spr->X, spr->Y)]>>8));
							mvwaddch(win,i+startY, j+startX, spr->plot[zse_xyz3Dto1D(j, i, atframe, spr->X, spr->Y)]&0xFF);
							attrset(A_NORMAL);
						}
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

void zse_rtC_spritePrintf
(
	WINDOW *win,
	int startX,
	int startY,
	SPRITES_t* spr,
	const int atframe
)
{
	sprite_data_t *sprp = &spr->plot[zse_xyz3Dto1D(0, 0, atframe, spr->X, spr->Y)];	
	for (int i = 0; i < spr->Y; ++i)
	{
		for (int j = 0; j < spr->X; ++j)
		{
			//if((*sprp) != 0xFF){
				mvwaddch(win, startY + i, startX + j, *sprp);
			//}

			sprp++;
		}
	}
}