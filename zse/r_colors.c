#include "r_colors.h"

int zse_r_colors_init()
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

/* colors are okay; continue */
    //printw("Colors initialized.\n");
    //printw("%d colors available.\n",COLORS);
    //printw("%d color pairs.",COLOR_PAIRS);
    //refresh();
    //getch();


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

void zse_r_colorPload_default(COLORrgb_p * colorP)
{
	colorP = zse_r_colorsPallete_create(8);

	COLORrgb_p def_p[8] = {
		{0, 0, 0},
		{1000, 1000, 1000},
		{1000, 200, 200},
		{200, 1000, 200},
		{200, 200, 1000},
		{500, 500, 100},
		{100, 600, 400},
		{1000, 800, 200}
	};

	for (int i = 0; i < 8; ++i)
	{
		colorP[i] = def_p[i];
		init_color(i, def_p[i].r, def_p[i].g, def_p[i].b);
		init_pair(i, i, i);
	}

}


void zse_delete_colorpallete(COLORrgb_p * pallate)
{
	free(pallate);
}

