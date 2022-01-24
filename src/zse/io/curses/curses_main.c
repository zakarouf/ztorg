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

int zse_rtC__selectListS(WINDOW *win, int x, int y, char const **list, int const listsize, char *getstringS, int stringSize)
{
    int scr_y = getmaxy(win), pagestart = 0, exit = 0;
    char key = ' ';
    int tmpr;

    while(!exit) 
    {
        switch(key) {
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
                mvwprintw(win ,scr_y-2, 0, ">>                    ");
                wrefresh(win);
                mvwgetnstr(win, scr_y-2, 3, getstringS, stringSize);
                noecho();
                return 0;
                
                break;
            case 'n':
                echo();
                mvwprintw(win ,scr_y-2, 0, ">>                    ");
                wrefresh(win);
                mvwscanw(win ,scr_y-2, 3, "%d", &tmpr);
                noecho();
                tmpr = tmpr >= listsize ? listsize-1: tmpr;
                //sprintf(getname, "%s", list[tmpr]); <- Wanted to return the string too, but not working :(

                return tmpr;
                break;
            case 'q':
                return -1;
                break;
        }


        werase(win);
        for (int i = pagestart; i < scr_y-1 + pagestart -2; ++i)
        {
            if (i < listsize)
            {
                mvwprintw(win ,i - pagestart+1 +y, 0+x, "|%03d: %s", i ,list[i]);
            }

        }

        wmove(win, scr_y-2, 0);
        wprintw(win, "[n]Enter NumID | [e]Enter Name | ");
        wprintw(win, "[q]Go Back");
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

void zse_rtC__drawHorizortalGraphRuler_nocheck(
      WINDOW *win
    , z__u32 at_x
    , z__u32 at_y
    , z__u32 upto_x
    , z__f32 ruler_x
    , z__f32 ruler_increment
    , z__u32 rulerGap
)
{
    wmove(win, at_y, at_x);
    whline(win, ACS_HLINE, upto_x - at_x);

    rulerGap += 1;

    for (z__u32 i = at_x; i < upto_x; i += rulerGap)
    {
        mvwaddch(win ,at_y, i, ACS_TTEE);
        mvwprintw(win, at_y+1, i-1, "%.1f", ruler_x);
        ruler_x += ruler_increment;
    }
}

void zse_rtC__drawVerticalGraphRuler_nocheck(
      WINDOW *win
    , z__u32 at_x
    , z__u32 at_y
    , z__u32 upto_y
    , z__f32 ruler_y
    , z__f32 ruler_increment
    , z__u32 rulerGap
)
{
    wmove(win, at_y, at_x);
    wvline(win, ACS_VLINE, upto_y - at_y);

    rulerGap += 1;

    for (int i = at_y; i < upto_y; i += rulerGap)
    {
        mvwaddch(win, i, at_x, ACS_RTEE);
        mvwprintw(win, i, at_x-4, "%.1f", ruler_y);
        ruler_y += ruler_increment;
    }
}
