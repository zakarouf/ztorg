#include "colors.h"

int zse_r_colors_init(void)
{

/* test for color ability of the terminal */
    if(!has_colors())
    {
        endwin();   /* exit Ncurses */
        puts("Terminal cannot do colors");
        return(1);
    }
    
/* initialize Ncurses colors */
    if(start_color() != OK)
    {
        endwin();
        puts("Unable to start colors.");
        return(1);
    }


    return(0);
}

COLORrgb_p* zse_r_colorsPallete_create (size_t size)
{
	COLORrgb_p *pallete = malloc(size * sizeof(COLORrgb_p));

	for (int i = 0; i < size; ++i)
	{
		pallete[i].r = 0;
		pallete[i].g = 0;
		pallete[i].b = 0;
	}

	return pallete;

}

int zse_r_color_initpairs(void)
{

	// Colors Text w/ Black b/g from 0 to 256
	for (int i = 0; i < COLORS; ++i)
	{
		init_pair(i, i, COLOR_BLACK);
	}

	return 0;
}

int zse_colors_test_showall(WINDOW *win, int atx, int aty)
{
	int tmpx = atx;
	for (int i = 0; i < COLORS; ++i)
	{
		if (i % 6 == 0)
		{
			aty++;
			atx = tmpx;
		}



		wattrset(win, COLOR_PAIR(i));
		mvwprintw(win, aty, atx*5, " %3d ", i);
		wattrset(win, A_NORMAL);
		atx++;

		
	}

	zse_r_color_initpairs();

	return 0;
}


void zse_delete_colorpallete(COLORrgb_p * pallate)
{
	free(pallate);
}

