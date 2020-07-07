#include "e_lib.h"
#include "e_intra.h"

#include "r_lib.h"
#include "p_lib.h"

#define B_TOG 0
#define B_INK 1
#define B_SIZ 2

void e_main_loop (EDITOR *e1, MAP *map, TILE *tile)
{
	char key = 0, Toggle[2][4] = {"OFF", "ON"};
	int ex, ey;

	uint8_t
	//brush_type = 0,
	brush_ink = 0,
	brush_size = 0,
	brush_toggle = 0,
	option,
	quit = 0;

	int scrX, scrY;
	getmaxyx(stdscr, scrY, scrX);

	WINDOW * status = newwin(5, scrX, scrY - 5, 0);

	WINDOW * h_log = newwin(scrY - 6, scrX - scrX/3, 5, scrX - scrX/3);

	// MODIFYING FOR MAIN SCR
	scrY -= 10;
	scrX -= (scrX/3);

	while (!quit)
	{
		ex = e1->X;
		ey = e1->Y;

		switch(key)
		{
			case 'w':
				e1->Y--;
				break;
			case 's':
				e1->Y++;
				break;
			case 'a':
				e1->X--;
				break;
			case 'd':
				e1->X++;
				break;
			case 'c':
				for(int i = 0; i < 8; ++i)
				{
					wprintw(h_log, "%d - %s\n", i, tile[i].name_id);
				}
				wrefresh(h_log);
				wscanw(h_log ,"%hhd", &brush_ink);
				wclear(h_log);
				break;
			case 'v':
				brush_toggle ^= 1;
				break;
			case 'b':
				wprintw(h_log ,"Change Brush Size\n>> ");
				wscanw(h_log, "%hhd", &brush_size);
			case 'e':
				option = getch();
				if (option == 'q') {quit = 1;}
				if (option == 's') {save_map(map);}
				break;
			default:break;
		}

		if((e1->X < 0 || e1->Y < 0 || e1->X >= map->X || e1->Y >= map->Y))
		{
			e1->Y = ey;
			e1->X = ex;
		}

		if(brush_toggle)
		{
			fillup_circle (map, e1->X, e1->Y, brush_size, brush_ink);
		}



		r_editor_main (e1, map, tile, scrX, scrY);
		

		mvwprintw(status, 0, 0,"Brush[%s] -> %s || %d\n", Toggle[brush_toggle], tile[brush_ink].name_id, brush_size);
		mvwprintw(status, 4, 0, "X - %d || Y - %d", e1->X, e1->Y);



		refresh();
		wrefresh(status);


		key = getch();
	}

}