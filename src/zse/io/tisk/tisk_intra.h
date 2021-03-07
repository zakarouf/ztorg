#ifndef ZAKAROUF__ZTORG_TISK_INTRA_H
#define ZAKAROUF__ZTORG_TISK_INTRA_H

#include <unistd.h>
#include <stdio.h>
#include "../../common.h"

frinl static void zse_rtT__setCur(int x, int y)
{
	printf("\x1b[%d;%dH", x, y);
}

frinl static void zse_rtT__set00()
{
    write(STDOUT_FILENO, "\x1b[H", sizeof("\x1b[H"));
}

frinl static void zse_rtT_init()
{
    write(STDOUT_FILENO, "\x1b[2J", sizeof("\x1b[2J"));
}

frinl static void zse_rtT_exit()
{
    zse_rtT__set00();
    write(STDOUT_FILENO, "\x1b[2J", sizeof("\x1b[2J"));
}

frinl static void zse_rtT_showCursor()
{
    write(STDOUT_FILENO, "\x1b[?25h", sizeof("\x1b[?25h"));
}

frinl static void zse_rtT_hideCursor()
{
    write(STDOUT_FILENO, "\x1b[?25l", sizeof("\x1b[?25l"));
}

#endif