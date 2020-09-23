
#include "../r_curses/r_sprites.h"
#include "../sprites/sprites_lib.h"

static void r_render_showSeditorNormal
(
	WINDOW *win,
	sprite_data_t *chunk,
	bool colormode,
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
	char lowerzc;

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
			if(!colormode)
			{
			
				lowerzc = chunk[getindex3d(j, i, lower_z, Xsize, Ysize)]&255;
				if(lowerzc != ' ' && lowerzc == (chunk[getindex3d(j, i, z, Xsize, Ysize)]&255))attrset(COLOR_PAIR(1));
				addch(chunk[getindex3d(j, i, z, Xsize, Ysize)]&255);
				if(lower_z >= 0 && (lowerzc != ' ') && (chunk[getindex3d(j, i, z, Xsize, Ysize)]&255) == ' ' )
				{
					attrset(COLOR_PAIR(5));
					addch('\b');
					addch(lowerzc);
				}
			}
			else
			{
				//Colormode;
				attrset(COLOR_PAIR(chunk[getindex3d(j, i, z, Xsize, Ysize)]>>8));
				addch(chunk[getindex3d(j, i, z, Xsize, Ysize)]&255);
			}

			attrset(A_NORMAL);

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

static int zse_sprites_edtior_func_copy_lastframe(sprite_data_t* data, int fromframe,int atframe, int xsize, int ysize, int zsize)
{
	if(fromframe < 0)
	{
		return 1;
	}
	for (int i = 0; i < xsize*ysize; ++i)
	{
		data[atframe*xsize*ysize +i] = data[fromframe*xsize*ysize +i];
	}

	return 0;
}

static int zse_sprites_edtior(SPRITES_t *spr)
{

	char Toggle[2][4] = {"Off", "On"};

	BRUSH_t brush = {0, 0, 0, ' ', 0, 0};
	char key;
	char name[ZSE_MAX_FILENAME_SIZE];
	char tmp_op;
	bool colormode = 1;
	char brush_colo = 0x01;
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
				break;
			case 'v':
				brush.toggle ^= 1;
				break;
			case 'c':
				brush.ink &= 0xFF00;
				brush.ink |= getch();
				break;
			case 'e':
				brush.ink &= 0x00FF;
				brush.ink |= (brush_colo * 0x100);
				break;

			case 'h':
				mvwscanw(status, 4, 0 ,"%f" , &spr->dt);
				break;
			case ' ':
				zse_render_sprite(status ,0, 0, spr, 0, spr->frames);
				break;
			case ':':
				tmp_op = getch();
				if(tmp_op == 'o')colormode ^= 1;
				if(tmp_op == 'c'){zse_sprites_edtior_func_copy_lastframe(spr->plot, brush.z-1, brush.z, spr->X, spr->Y, spr->frames);}
				if(tmp_op == 's')
				{
					mvwprintw(status, 3, 0 ,"Save Sprite As >> ");wrefresh(status);
					wgetstr(status,name);
					zse_sprites_sin_export(spr, name);
				}
				break;
			case '-':
				brush_colo --;
				if(brush_colo < 0){brush_colo = 0;}
				break;
			case '=':
				brush_colo ++;
				if(brush_colo > 7){brush_colo = 7;}
				break;

			case '`':
				return 0;
				break;
		}

		if(brush.toggle)
		{
			spr->plot[getindex3d(brush.x, brush.y, brush.z, spr->X, spr->Y)] = brush.ink; 
		}

		mvwprintw(status, 0, 0,"Brush[%3s] -> %c {%s} :: %d =Color={%d}"
			, Toggle[brush.toggle], brush.ink , "NONE", brush.size, brush_colo) ;
		attrset(COLOR_PAIR(brush_colo));waddstr(status,"###\n");attrset(COLOR_PAIR(A_NORMAL));

		mvwprintw(status, 1, 0, "POS [%hd,%hd] Frame - %3d/%3d Color No. %d| "
			, brush.x, brush.y, brush.z, spr->frames-1, spr->plot[getindex3d(brush.x, brush.y, brush.z, spr->X, spr->Y)]>>8);

		
		r_render_showSeditorNormal(stdscr, spr->plot, colormode, spr->X, spr->Y, spr->frames, brush.x, brush.y, brush.z, 0, 0);
		wrefresh(status);
	}



	return 0;
}


static void zse_sprite_newCreateMenu(SPRITES_t *spr)
{
	clear();
	printw("Create New Map(Y)");
	char yes = getch();
	clear();

	if(yes == 'Y')
	{
		mvprintw(0, 0, "Get X 	     : ");
		mvprintw(1, 0, "Get Y 	     : ");
		mvprintw(2, 0, "Get Frames   : ");
		mvprintw(3, 0, "Get DeltaTime: ");
		mvprintw(4, 0, "Get Max Color: ");

		mvscanw(0, 14, "%hd", &spr->X);
		mvscanw(1, 14, "%hd", &spr->Y);
		mvscanw(2, 14, "%d", &spr->frames);
		mvscanw(3, 14, "%f", &spr->dt);
		mvscanw(4, 14, "%hd", &spr->colorused);


		spr->plot = malloc(sizeof(sprite_data_t) * spr->X * spr->Y * spr->frames);

		for (int i = 0; i < spr->X * spr->Y * spr->frames; ++i)
		{
			spr->plot[i] = ' ';
		}

		spr->colorP = zse_r_colorsPallete_create (spr->colorused);
	}
	else
	{
		char name[ZSE_MAX_FILENAME_SIZE];
		getstr(name);
		*spr = zse_sprites_sin_load(name);
	}

}

static int zse_sprites_debug(SPRITES_t *spr)
{
	fprintf(stdout, "%d\n%d\n %d", spr->X, spr->Y, spr->frames);
	fprintf(stdout, "%f\n%d", spr->dt, spr->colorused);

	return 0;
}


int zse_tool_spriteEditor_main()
{
	zse_r_color_initpairs_Default();
	SPRITES_t spr;
	
	zse_sprite_newCreateMenu(&spr);

	zse_sprites_edtior(&spr);



	return 0;
}