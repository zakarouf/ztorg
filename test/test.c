#include <ncurses.h>
#include <stdio.h>
#include <string.h>

#define SCREEN_X_range 21/2
#define SCREEN_Y_range 21/2

int main(int argc, char const *argv[])
{
    initscr();
    printw("%i\n %i", SCREEN_X_range, SCREEN_Y_range);
    refresh();
    getch();
    endwin();


    return 0;
}