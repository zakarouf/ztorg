#include <ncurses/ncurses.h>

#include "curses.h"

int zse_rtC_init()
{
	initscr();
	raw();
	cbreak();

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
        return 1;
    }

    if (!(can_change_color()))
    {
        printw("Cant Change Color");
        return 1;
    }



	use_default_colors();
	curs_set(0);

    int zse_rtC_color_initpairs(void);
        zse_rtC_color_initpairs();

	return 0;
}

void zse_rtC_exit()
{
	endwin();
}

int zse_rtC__getint(WINDOW *win)
{
    int r;
    wscanw(win, "%d", &r);
    return r;
}

int zse_rtC__msgGetint(WINDOW *win, char const msg[])
{
    int rval;
    waddstr(win, msg);
    wscanw(win ,"%d", &rval);
    return rval;
}

int zse_rtC__mvmsgGetint(WINDOW *win, int y, int x, char const msg[])
{
    int rval;
    mvwaddstr(win, y, x, msg);
    wscanw(win ,"%d", &rval);
    return rval;
}

int zse_rtC_selectListS(WINDOW *win, int x, int y, char **list, int listsize, char *getname)
{
    int scr_y = getmaxy(win), pagestart = 0, exit = 0;
    char key = ' ';
    int tmpr;

    while(!exit) 
    {

        switch(key)
        {
            case 'w':
                pagestart--;
                if(pagestart < 0)
                {
                    pagestart = 0;
                }
                break;
            case 's':
                pagestart++;
                if(pagestart >= listsize)
                {
                    pagestart = listsize -1;
                }
                break;
            case 'e':
                echo();
                mvwprintw(win ,scr_y-1, 0, ">>                    ");
                wrefresh(win);
                mvwscanw(win, scr_y-1, 3, "%s", getname);
                noecho();
                return 0;
                
                break;
            case 'n':
                echo();
                mvwprintw(win ,scr_y-1, 0, ">>                    ");
                wrefresh(win);
                mvwscanw(win ,scr_y-1, 3, "%d", &tmpr);
                noecho();
                tmpr = tmpr >= listsize ? listsize-1: tmpr;
                //sprintf(getname, "%s", list[tmpr]); <- Wanted to return the string too, but not working :(

                return tmpr;
                break;
            case 'q':
                return 0;
                break;
        }


        wclear(win);
        for (int i = pagestart; i < scr_y + pagestart -2; ++i)
        {
            if (i < listsize)
            {
                mvwprintw(win ,i - pagestart+1 +y, 0+x, "[%d] %s", i ,list[i]);
            }

        }

        mvwprintw(win,scr_y-2, 0, "[n]Enter NumID | [e]Enter Name | [q]Confirm");
        wrefresh(win);

        key = wgetch(win);
    }
    return 0;
}

void zse_rtC_clearPortion(WINDOW *win, int x, int y, int uptoX, int uptoY)
{
    const int ylim = y + uptoY;
    const int xlim = x + uptoX;
    for (; y < ylim; ++y)
    {
        for (; x < xlim; ++x)
        {
            mvwaddch(win , y, x, ' ');
        }
    }
}
