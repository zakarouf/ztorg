#include "r_lib.h"

int zse_r_init()
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
        return(1);
    }

    if (!(can_change_color()))
    {
        printw("Cant Change Color");
        return(1);
    }

	use_default_colors();
	curs_set(0);

	return 0;
}

void zse_r_exit()
{
	endwin();
}

int zse_getint()
{
    int r;
    scanw("%d", &r);
    return r;
}

int zse_getint_printw_option(char str[])
{
    int r;
    clear();
    addstr(str);
    scanw("%d", &r);
    return r;
}

int zse_r_selectListS(WINDOW *win, int x, int y, char **list, int listsize, char *getname){
    int scr_y = getmaxy(win), pagestart = 0, exit = 0;
    char key = ' ';

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
                noecho();
                return zse_getint();
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
                mvwprintw(win ,i - pagestart+1 +y, 0+x, "[%d] %s|", i ,list[i]);
            }

        }

        mvwprintw(win,scr_y-2, 0, "[n]Enter NumID | [e]Enter Name | [q]Confirm || ");
        wrefresh(win);

        key = wgetch(win);
    }
    return 0;
}
