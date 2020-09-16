#include "zse.h"

static void r_render_showSeditor
(
	WINDOW *win,
	sdata *chunk,
	COLORrgb_p *colo,
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

	//const int lower_z = (z-1>=0)? z-1:0;

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
			attron(COLOR_PAIR(getindex3d(j, i, z, Xsize, Ysize)));
			addch(' ');
			attroff(COLOR_PAIR(getindex3d(j, i, z, Xsize, Ysize)));

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

static int zse_sprites_edtior(SPRITES_t *spr)
{
	//SPRITES_t spr;
	// Get All Atributes

	char Toggle[2][4] = {"Off", "On"};

	BRUSH_t brush = {0, 0, 0, 0, 0, 0};
	char key;
	// note z is the frame

	WINDOW * status = newwin(5, getmaxx(stdscr), getmaxy(stdscr) - 5, 0);
	

	while(true)
	{
		key = getch();

		switch(key){
			case 'w':if(brush.y -1 >= 0)brush.y--;
				break;
			case 's':if(brush.y +1 < spr->Y)brush.y++;
				break;
			case 'a':if(brush.x -1 >= 0)brush.x--;
				break;
			case 'd':if(brush.x +1 < spr->X)brush.x++;
				break;
			case 'z':
				if(brush.z +1 < spr->frames){brush.z++;}
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
				
				break;

			case 'h':
				
				break;

			case '`':
				return 0;
		}

		if(brush.toggle)
		{
			spr->plot[getindex3d(brush.x, brush.y, brush.z, spr->X, spr->Y)] = brush.ink; 
		}

		mvwprintw(status, 0, 0,"Brush[%3s] -> ID.%3d {%s} :: %d\n", Toggle[brush.toggle], brush.ink , "NONE", brush.size);
		mvwprintw(status, 1, 0, "X - %3d || Y - %3d || Z - %3d", brush.x, brush.y, brush.z);
		r_render_showSeditor(stdscr, spr->plot, spr->colorP, spr->X, spr->Y, spr->frames, brush.x, brush.y, brush.z, 5, 10);
		wrefresh(status);
	}



	return 0;
}


static void zse_sprite_newCreateMenu(SPRITES_t *spr)
{
	mvprintw(0, 0, "Get X : ");
	mvprintw(1, 0, "Get Y : ");
	mvprintw(2, 0, "Get F : ");
	mvscanw(0, 8, "%hd", &spr->X);
	mvscanw(1, 8, "%hd", &spr->Y);
	mvscanw(2, 8, "%d", &spr->frames);

	spr->plot = malloc(sizeof(sdata) * spr->X * spr->Y * spr->frames);

	for (int i = 0; i < spr->X * spr->Y * spr->frames; ++i)
	{
		spr->plot[i] = 0;
	}
}


int zse_sprites_setup()
{
	SPRITES_t spr;
	zse_r_colorPload_default(spr.colorP);
	zse_sprite_newCreateMenu(&spr);

	zse_sprites_edtior(&spr);



	return 0;
}