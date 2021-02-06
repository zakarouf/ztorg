/*-----------------------------------------------------
				 Map Editer For ZSE
//---------------------------------------------------//

	+-----------------------------------------------+
	|		A Bare Bones Map Editor For ZSE  	    |
	+-----------------------------------------------+

-----------------------------------------------------*/

#include "zse_tools.h"


#define EDITOR_LOG_X_START(stdscrXsize) (stdscrXsize) - 48

// 

static void _editor_help_st (WINDOW *win)
{

	wclear(win);

	wprintw(win,"Move UP/DOWN/LEFT/RIGHT/ : 'w/s/a/d |\nMove Layer UP/DOWN 'z/x'\n\n");
	wprintw(win,"Change Brush 'c' |\nChange Size 'b' |\nToggle Brush'v' |\n");
	wprintw(win,"Save 'e' |\nQuit '`'");

	wrefresh(win);

	getch();


	wclear(win);

}

static int _zse_t_ed_getbrush(TILESET_t *t)
{
	WINDOW *tmpw = newwin(getmaxy(stdscr) -1, getmaxx(stdscr), 0, getmaxx(stdscr)/3);

	char **n = zse_malloc_2D_array_char(ZSE_MAX_FILENAME_SIZE, t->tsize);
	for (int i = 0; i < t->tsize; ++i)
	{
		sscanf(t->tile[i].name_id, "%s", n[i]);
	}

	char tmp[12];
	int r = zse_rtC_selectListS(tmpw, 0, 0, n, t->tsize, tmp);
	delwin(tmpw);
	zse_free2dchar(n, t->tsize);

	return r;
}

static int _zse_editworld_st(ST_WORLD_t* map, TILESET_t* t, char name[])
{
	char key;
	char Toggle[2][4] = {"Off", "On"};

	BRUSH_t brush = {0, 0, 0, 0, 0, 0};

	WINDOW * status = newwin(5, getmaxx(stdscr), getmaxy(stdscr) - 5, 0);
	WINDOW * log = newwin(getmaxy(stdscr), getmaxx(stdscr), 0 , EDITOR_LOG_X_START(getmaxx(stdscr)));

	zse_rtC_map_show2dworld(stdscr, t->tile ,map->chunk, map->Xsize, map->Ysize, map->Zsize, brush.x, brush.y, brush.z, 3, 1, TRUE);
	scroll(log);


	// Main Loop
	while(TRUE)
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
			case 'd':if(brush.x +1 < map->Xsize)brush.x++;
				break;
			case 'z':
				if(brush.z +1 < map->Zsize){brush.z++;}
				break;
			case 'x':if(brush.z -1 >= 0){brush.z--;}
				break;

			case 'b':
				echo();
				mvwprintw(status, 4, 0, "Size >>");
				mvwscanw(status, 4, 8 ,"%hhd" , &brush.size);
				noecho();
				break;
			case 'v':
				brush.toggle ^= 1;
				break;
			case 'c':
				brush.ink = _zse_t_ed_getbrush(t);
				break;
			case 'e':
				zse_map_export_st(map, name, "DEFAULT", TRUE);
				break;

			case 'h':
				_editor_help_st(log);
				break;

			case '`':
				return 0;
		}

		if(brush.toggle)
		{
			zse_map_draw_circle (map, brush.x, brush.y, brush.z , brush.size , brush.ink);
		}

		
		

		// Draw Routine
		zse_rtC_map_show2dworld(stdscr, t->tile ,map->chunk, map->Xsize, map->Ysize, map->Zsize, brush.x, brush.y, brush.z, 3, 6, TRUE);

		mvwprintw(status, 0, 0,"Brush[%3s] -> ID.%3d {%s} :: %d\n", Toggle[brush.toggle], brush.ink , "NONE", brush.size);
		mvwprintw(status, 1, 0, "X - %3d || Y - %3d || Z - %3d", brush.x, brush.y, brush.z);
		mvwprintw(status, 2, 0, "[h]Help");

		wrefresh(stdscr);
		wrefresh(status);
		wrefresh(log);

	}
}


int zse_tool_mapEditor_st_main()
{

	clear();
	char op;

	printw("Select Option :-\nn - New Map\no - Open Exiting Map\nq - Go Back\n");

	op = getch();

	if (op == 'n')
	{

		ST_WORLD_t *map = zse_map_init_empty_st(zse_rtC_getint_printw_option("X - "), zse_rtC_getint_printw_option("Y - "), zse_rtC_getint_printw_option("Z - "));

		char returntilesetname[ZSE_MAX_FILENAME_SIZE];

		addstr("Map Name : ");
		getstr(returntilesetname);

		TILESET_t t = zse_tileset_get ("DEFAULT");

		_zse_editworld_st(map, &t, returntilesetname);

		zse_map_delete_st(map);
	}

	if (op == 'o')
	{
		char returntilesetname[ZSE_MAX_FILENAME_SIZE];
		char mapname[ZSE_MAX_FILENAME_SIZE];

		clear();

		printw("Name : ");
		getstr(mapname);

		
		ST_WORLD_t *map = zse_map_load_st(mapname, returntilesetname);

		TILESET_t t = zse_tileset_get (returntilesetname);
		

		

		_zse_editworld_st(map, &t, mapname);
		zse_map_delete_st(map);
	}

	if(op == 'q')
	{

		return 0;

	}





	return 0;

}