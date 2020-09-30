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

#include <sys/types.h>
#include <dirent.h>

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

int zse_showdir_list(WINDOW* win ,int x, int y, char name[])
{
    DIR * drip = opendir(name);
    if(drip == NULL) return -1;
    struct dirent* dp;
    while((dp = readdir(drip)) != NULL)
    {
        mvwprintw(win, y, x, "%s", dp->d_name);
        y++;
    }
    closedir(drip);
    return 0;
}