#include "r_sprites.h"

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
