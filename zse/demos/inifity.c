#include "../zse.h"

int demo_perlin()
{
	int zse_map_GetNoiseSeed(void);
	void zse_map_SetNoiseSeed(int seed);
	double zse_map_gen2d_get_solo(double x, double y, double freq, int depth);

	zse_map_SetNoiseSeed(random());
	
	
	uint8_t ls[] = {32, 32, 32, 33, 32, 32, 32, 32, 32, 32, 32, 33 ,185, 70, 34, 40, 28, 22};

	int x = 0, y = 0;

	while(TRUE)
	{

		switch(getch())
		{
			case 'w':
				y-=5;
				break;
			case 's':
				y+=5;
				break;
			case 'a':
				x-=5;
				break;
			case 'd':
				x+=5;
				break;
			case '`':
				return 0;
				break;
			default:
				break;
		}
		clear();
		move(0, 0);
		for (int i = 0; i < getmaxy(stdscr); ++i)
		{
			for (int j = 0; j < getmaxx(stdscr); ++j)
			{

				attron(COLOR_PAIR(ls[(int)(zse_map_gen2d_get_solo(j + x, i + y, 0.1, 4) * 0xA)]) | A_REVERSE);
				//printf("%2d", (int)(zse_map_gen2d_get_solo(j, i, 0.1, 4) * 0x10));
				mvaddstr(i, j , "  ");
				attrset(A_NORMAL);
			}
			printw("\n");
		}

		mvprintw(0, 0, "%ld", zse_sys_getRamUsage());
		refresh();

	}

	return 0;
}