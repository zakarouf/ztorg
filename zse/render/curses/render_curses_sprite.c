#include "render_curses_sprite.h"

int zse_r_sprite_full
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

int zse_r_ssmooth(float pos, float slength)
{
	return (pos * slength)+(pos*1/slength) -slength;
}

void zse_r_sprite
(
	WINDOW *win,
	int startX,
	int startY,
	SPRITES_t* spr,
	const int atframe
)
{
	for (int i = 0; i < spr->Y; ++i)
	{
		for (int j = 0; j < spr->X; ++j)
		{
			if((spr->plot[zse_xyz3Dto1D(j, i, atframe, spr->X, spr->Y)]&0xFF) != 0xFF){
				mvwaddch(win, startY + i, startX + j, spr->plot[zse_xyz3Dto1D(j, i, atframe, spr->X, spr->Y)]&0xFF);
			}
		}
	}
}