/*-----------------------------------------------------
			Sprite Editer For ZSE
//---------------------------------------------------//

	+-----------------------------------------------+
	|The sprites used for zse is in custom format   |
	|single sprite is stored as .zspr format		|
	+-----------------------------------------------+
	
	
-----------------------------------------------------*/

#include "zse_tools.h"

#define ZSE_T_SPRSR_OP_COLORS    0x1
#define ZSE_T_SPRSR_OP_TRANSENAB 0x2
#define ZSE_T_SPRSR_OP_TRANSSHOW 0x4

#define ZSE_T_SPRSR_OP_HELPTEXT \
	"Sprite Help:\n"\
	"w,a,s,d   Move Brush\n"\
	"z, x      Move To Layer Up/Down\n"\
	"c         Change Ink\n"\
	"v         Toggle Brush\n"\
    "b         Change Size\n"\
    "h         Realloc Frames\n"\
    "r         Change dt\n"\
    ":         Commands\n"\
    "e         Apply Colour\n"\
    "-,=,_,+   Change Colour\n"\
    "`         Exit\n"


static void _render_showSeditorNormal
(
	WINDOW *win,
	sprite_data_t *chunk,
	char options,
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
	uint8_t lowerzc;

	for (; i < end_i; ++i)
	{
		j = x - (int)(screensizeX>>1) -1;
		if (end_j >= Xsize) {end_j = Xsize; j = Xsize - screensizeX -1;}
		if (j < 0) {j = 0;
			if(screensizeX <= Xsize){
				end_j = screensizeX+1;
			}
		}
        lowerzc = chunk[zse_xyz3Dto1D(j, i, lower_z, Xsize, Ysize)]&0xff;

		wmove(win ,cursor_y, cursor_x);

		for (; j < end_j; ++j)
		{

			if ((chunk[zse_xyz3Dto1D(j, i, z, Xsize, Ysize)]&0xff) != 0xff) // IF plot point is not transperant (0xff)
			{
				if(!(options&ZSE_T_SPRSR_OP_COLORS))
				{

					if(lowerzc == (chunk[zse_xyz3Dto1D(j, i, z, Xsize, Ysize)]&0xff)) // Check is Lower Z value and Z value is Same(Not Counting SPACE)
                    {
						wattrset(win ,COLOR_PAIR(1));
                        waddch(win ,chunk[zse_xyz3Dto1D(j, i, z, Xsize, Ysize)]&0xFF);
                    }
                    else
                    {
                        waddch(win ,chunk[zse_xyz3Dto1D(j, i, z, Xsize, Ysize)]&0xFF);
                    }

				}

				else
				{
					//Colormode;

					wattrset(win ,COLOR_PAIR(chunk[zse_xyz3Dto1D(j, i, z, Xsize, Ysize)]>>8));
					waddch(win ,chunk[zse_xyz3Dto1D(j, i, z, Xsize, Ysize)]&255);
				}
			}

			else
			{
				wattrset(win, COLOR_PAIR(7));

				if (options&ZSE_T_SPRSR_OP_TRANSENAB)
				{

                    
					for (int l = lower_z; l >= 0; --l)
                    {
                        if ((chunk[zse_xyz3Dto1D(j, i, l, Xsize, Ysize)]&255) == 0xff)
                        {
                            continue;
                        }
                        else
                        {
                            if (options&ZSE_T_SPRSR_OP_TRANSSHOW)
                            {
                                wattrset(win ,COLOR_PAIR(0xff) | A_REVERSE);      
                            }
                            else
                            {
                                wattrset(win ,COLOR_PAIR(chunk[zse_xyz3Dto1D(j, i, l, Xsize, Ysize)]>>8));
                            }
                            
                            waddch(win ,chunk[zse_xyz3Dto1D(j, i, l, Xsize, Ysize)]&0xff);
                            break;
                        }
                    }
				}
				else
				{
					waddch(win, ' ');
				}
			}


			wattrset(win, A_NORMAL);

			if(j == x && i == y)
			{
				waddstr(win, "\b@");
			}

		}
		wprintw(win, "| %d", i);
		cursor_y++;
	}

	// Add Cursor
	wrefresh(win);
}

static int _zse_sprites_edtior_func_CopyFrame(sprite_data_t* data, int fromframe,int atframe, int xsize, int ysize, int zsize)
{
	if(fromframe < 0 || fromframe >= zsize)
	{
		return 1;
	}
	for (int i = 0; i < xsize*ysize; ++i)
	{
		data[atframe*xsize*ysize +i] = data[fromframe*xsize*ysize +i];
	}

	return 0;
}

static int _zse_sprites_edtior(SPRITES_t *spr)
{

	char Toggle[2][4] = {"Off", "On"};
	size_t sessions = 1;

	BRUSH_t brush = {0, 0, 0, '.', 0, 0};

	char name[ZSE_MAX_FILENAME_SIZE];
	char tmp_op;
	char r_options = ZSE_T_SPRSR_OP_COLORS | ZSE_T_SPRSR_OP_TRANSENAB | ZSE_T_SPRSR_OP_TRANSSHOW;
	short brush_colo = 0x01;
	// NOTE: z is the frame

	WINDOW * status = newwin(5, getmaxx(stdscr), getmaxy(stdscr) - 5, 0);

	wclear(stdscr);
	_render_showSeditorNormal(stdscr, spr->plot, r_options, spr->X, spr->Y, spr->frames, brush.x, brush.y, brush.z, 0, 0);
	while(TRUE)
	{

		switch(getch()){
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
			case 'x':
				if(brush.z -1 >= 0){brush.z--;}
				break;


            // Brush
			case 'b':
                echo();
                mvwprintw(status, 4, 0 ,"Brush Size >>");wrefresh(status);
				mvwscanw(status, 4, 14 ,"%hhd" , &brush.size);
                noecho();
				break;
			case 'v':
				brush.toggle ^= 1;
				break;
			case 'c':
				brush.ink &= 0xFF00;
				brush.ink |= getch();
				break;


            // Canvas Manupilation
			case 'h':
                // Realloc Frames
				break;
			case 'r':
                // Edit dt
				mvwscanw(status, 4, 0 ,"%f" , &spr->dt);
				break;

            // Commands
			case ':':
				tmp_op = getch();

                // Enable To Render Colours
				if(tmp_op == 'o')r_options ^= ZSE_T_SPRSR_OP_COLORS;
                // Enable Transparency
                if(tmp_op == 'p')r_options ^= ZSE_T_SPRSR_OP_TRANSENAB;
                // Make Transparent stand out
                if(tmp_op == 'i')r_options ^= ZSE_T_SPRSR_OP_TRANSSHOW;

                // Copy Last Frame
				if(tmp_op == 'c'){_zse_sprites_edtior_func_CopyFrame(spr->plot, brush.z-1, brush.z, spr->X, spr->Y, spr->frames);}

                //Copy From Selected Frame
                if(tmp_op == 'f')
                {
                    int frame;
                    wscanw(status, "%d", &frame);
                    _zse_sprites_edtior_func_CopyFrame(spr->plot, frame, brush.z, spr->X, spr->Y, spr->frames);
                }

                // Save Sprite
				if(tmp_op == 's')
				{
					echo();
					mvwprintw(status, 3, 0 ,"Save Sprite As >> ");wrefresh(status);
					wgetstr(status,name);
					noecho();
					zse_sprites_sin_export(spr, name);
				}

                // Slide Show Sprite
                if(tmp_op == ' ')zse_rtC_spritePrintAll(stdscr ,0, 0, spr, 0, spr->frames);

                // Select Transparent Char
				if(tmp_op == 'x')brush.ink |= 0xFF;

                // Help
                if(tmp_op == 'h')
                {
                    mvwprintw(stdscr, 0,0, "%s", ZSE_T_SPRSR_OP_HELPTEXT);
                    wgetch(stdscr);
                }

				break;

			// Colour Stuff
            case 'e':
                brush.ink &= 0x00FF;    // Clear any Previous color
                brush.ink |= (brush_colo * 0x100); // Apply color
                break;
			case '-':
				brush_colo --;
				if(brush_colo < 0){brush_colo = COLORS -1;}
				break;
			case '=':
				brush_colo ++;
				if(brush_colo > COLORS){brush_colo = 0;}
				break;
			case '_':
				brush_colo += 6;
				if(brush_colo < 0){brush_colo = COLORS -1;}
				break;
			case '+':
				brush_colo += 6;
				if(brush_colo > COLORS){brush_colo = 0;}
				break;
			case 127: // Delete
				zse_rtC_colors_test_showall(stdscr, getmaxx(stdscr)/5 -(6*3), 0);
				getch();
				break;

			case '!':
				//sessions++;
				//spr = realloc(spr, sessions);

				break;

            // Exit
			case '`':
				zse_delete_sprites_ptr(spr, sessions);
				return 0;
				break;
			default:
				break;
		}

		if(brush.toggle)
		{
			spr->plot[zse_xyz3Dto1D(brush.x, brush.y, brush.z, spr->X, spr->Y)] = brush.ink; 
		}

		mvwprintw(status, 0, 0,"Brush[%3s] -> %c {%s} :: %d =Color={%hi}"
			, Toggle[brush.toggle], brush.ink , "NONE", brush.size, brush_colo);

		wattrset(status, COLOR_PAIR(brush_colo));
		waddstr(status,"##  \n");
		wattrset(status, COLOR_PAIR(A_NORMAL));


		mvwprintw(status, 1, 0, "POS [%hd,%hd] Frame - %3d/%3d Color No. %d"
			, brush.x, brush.y, brush.z, spr->frames-1, spr->plot[zse_xyz3Dto1D(brush.x, brush.y, brush.z, spr->X, spr->Y)]>>8);

        mvwprintw(status, 2, 0, "Show: Colors %d  TransEnable %d  TransShow %d", r_options&ZSE_T_SPRSR_OP_COLORS? 1:0, r_options&ZSE_T_SPRSR_OP_TRANSENAB? 1:0, r_options&ZSE_T_SPRSR_OP_TRANSSHOW? 1:0);

		wclear(stdscr);
		_render_showSeditorNormal(stdscr, spr->plot, r_options, spr->X, spr->Y, spr->frames, brush.x, brush.y, brush.z, 0, 0);
		wrefresh(status);

	}



	return 0;
}


static int _zse_sprite_newCreateMenu(SPRITES_t *spr)
{
	
	
	while(TRUE)
	{
		clear();
		printw("Create (N)ew Sprite Or (O)pen A Sprite file || (Q)uit");
		char yes = getch();
		clear();

		if(yes == 'N')
		{
			mvprintw(0, 0, "Get X 	     	: ");
			mvscanw(0, 16, "%hd", &spr->X);

			mvprintw(1, 0, "Get Y 	     	: ");
			mvscanw(1, 16, "%hd", &spr->Y);

			mvprintw(2, 0, "Get Frames   	: ");
			mvscanw(2, 16, "%d", &spr->frames);

			mvprintw(3, 0, "Get DeltaTime	: ");
			mvscanw(3, 16, "%f", &spr->dt);

			mvprintw(4, 0, "Get Max Sequence: ");
			mvscanw(4, 16, "%hd", &spr->seqMax);


			spr->plot = malloc(sizeof(sprite_data_t) * spr->X * spr->Y * spr->frames);

			for (int i = 0; i < spr->X * spr->Y * spr->frames; ++i)
			{
				spr->plot[i] = ' ';
			}

			spr->sequences[0] = malloc(sizeof(sequence_data_t) * spr->seqMax);
			spr->sequences[1] = malloc(sizeof(sequence_data_t) * spr->seqMax);

			return 0;
		}
		else if(yes == 'O')
		{

			char *name = malloc(sizeof(char) * ZSE_MAX_FILENAME_SIZE);
			sprintf(name, "bloc");

			int items;
			char **fnames = zse_dir_getfnames(SPRITES_PARENTDIR, &items);
			zse_rtC_selectListS(stdscr, 0, 0, fnames, items, name);
			zse_free2dchar(fnames, items);

			*spr = zse_sprites_sin_load(name);
			free(name);

			return 0;
		}
		else if(yes == 'Q')
		{
			return 1;
		}
	}


}


int zse_tool_spriteEditor_main()
{
	SPRITES_t *spr = malloc(sizeof(SPRITES_t));
	
	if(_zse_sprite_newCreateMenu(spr))
		return 0;

	_zse_sprites_edtior(spr);

	return 0;
}