/*-----------------------------------------------------
		Bare Bones Editor For ZSE
//---------------------------------------------------//

-----------------------------------------------------*/

#include "zse.h"

typedef struct _map_editor_brush_t
{

	int x;
	int y;
	int z;
	int ink;
	unsigned char size;
	bool toggle;

}BRUSH_t;


#define EDITOR_LOG_X_START(stdscrXsize) (stdscrXsize) - 48

// 

static void editor_help_st (WINDOW *win)
{

	wclear(win);

	wprintw(win,"Move UP/DOWN/LEFT/RIGHT/ : 'w/s/a/d |\nMove Layer UP/DOWN 'z/x'\n\n");
	wprintw(win,"Change Brush 'c' |\nChange Size 'b' |\nToggle Brush'v' |");

	wrefresh(win);

	getch();


	wclear(win);

}

static int zse_editworld_st(ST_WORLD_t* map, char name[])
{
	char key;
	char Toggle[2][4] = {"Off", "On"};

	BRUSH_t brush = {0, 0, 0, 0, 0, 0};

	WINDOW * status = newwin(5, getmaxx(stdscr), getmaxy(stdscr) - 5, 0);
	WINDOW * log = newwin(getmaxy(stdscr), getmaxx(stdscr), 0 , EDITOR_LOG_X_START(getmaxx(stdscr)));

	r_render_show2dworld(stdscr, map->chunk, map->Xsize, map->Ysize, map->Zsize, brush.x, brush.y, brush.z, 3, 1);



	// Main Loop
	while(true)
	{
		key = getch();
		switch(key)
		{

			case 'w':if(brush.y -1 >= 0)brush.y--;
				break;
			case 's':if(brush.y +1 < map->Ysize)brush.y++;
				break;
			case 'a':if(brush.x -1 >= 0)brush.x--;
				break;
			case 'd':if(brush.x +1 < map->Ysize)brush.x++;
				break;
			case 'z':
				if(brush.z +1 < map->Zsize){brush.z++;}
				break;
			case 'x':if(brush.z -1 >= 0){brush.z--;}
				break;

			case 'b':
				mvwscanw(status, 4, 0 ,"%hhd" , &brush.size);
			case 'v':
				brush.toggle ^= 1;
				break;
			case 'c':
				mvwscanw(status , 4, 0, "%hhd", &brush.ink);
				break;
			case 'e':
				zse_map_export_st(map, name, "NONE", true);
				break;

			case 'h':
				editor_help_st(log);
				break;

			case '`':
				return 0;
		}

		if(brush.toggle)
		{
			zse_map_draw_circle (map, brush.x, brush.y, brush.z , brush.size , brush.ink);
		}

		r_render_show2dworld(stdscr, map->chunk, map->Xsize, map->Ysize, map->Zsize, brush.x, brush.y, brush.z, 3, 6);

		mvwprintw(status, 0, 0,"Brush[%3s] -> ID.%3d {%s} :: %d\n", Toggle[brush.toggle], brush.ink , "NONE", brush.size);
		mvwprintw(status, 1, 0, "X - %3d || Y - %3d || Z - %3d", brush.x, brush.y, brush.z);

		wrefresh(status);


		
	}
}


int zse_editor_st_main()
{

	clear();
	char op;

	printw("Select Option :-\nn - New Map\no - Open Exiting Map\nq - Go Back\n");

	op = getch();

	if (op == 'n')
	{

		ST_WORLD_t *map = zse_map_init_empty_st(zse_getint_printw_option("X - "), zse_getint_printw_option("Y - "), zse_getint_printw_option("Z - "));

		char returntilesetname[ZSE_MAX_FILENAME_SIZE];

		addstr("Map Name : ");
		getstr(returntilesetname);

		zse_editworld_st(map, returntilesetname);

		zse_map_delete_st(map);
	}

	if (op == 'o')
	{
		char returntilesetname[ZSE_MAX_FILENAME_SIZE];
		char mapname[ZSE_MAX_FILENAME_SIZE];

		clear();

		printw("Name : ");
		getstr(mapname);

		//ST_WORLD_t *map = map_load_st(returntilesetname, returntilesetname);
		ST_WORLD_t *map = zse_map_load_st(mapname, returntilesetname);


		

		zse_editworld_st(map, returntilesetname);
		zse_map_delete_st(map);
	}

	if(op == 'q')
	{

		return 0;

	}





	return 0;

}