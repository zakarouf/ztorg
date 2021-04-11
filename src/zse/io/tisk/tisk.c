#include <unistd.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include "tisk.h"


frinl void zse_rtT__D_setCur(int x, int y)
{
    printf("\x1b[%d;%dH", x, y);
}

frinl void zse_rtT__D_set00(void)
{
    fputs("\x1b[H",  stdout);
}

frinl void zse_rtT__init(void)
{
    fputs("\x1b[2J", stdout);
}

frinl void zse_rtT__exit(void)
{
    zse_rtT__D_set00();
    //fputs("\x1b[2J", stdout);
}

frinl void zse_rtT__D_showCursor(void)
{
    fputs("\x1b[?25h",  stdout);
}

frinl void zse_rtT__D_hideCursor(void)
{
    fputs("\x1b[?25l",  stdout);
}

zset__rtT_TiskWin zse_rtT__Win_create(z__u32 x, z__u32 y, z__u32 buffs)
{
    zset__rtT_TiskWin win = {
        .size.x = x,
        .size.y = y,
        .bufferCount = buffs,

        .buffers = z__CALLOC(buffs, sizeof(*win.buffers)),
        
    };

    for (int i = 0; i < buffs; ++i)
    {
        win.buffers[i] = z__CALLOC(x * y ,sizeof(**win.buffers));
    }
    win.mainWin = win.buffers[0];

    return win;
}

void zse_rtT__Win_deleteContent(zset__rtT_TiskWin *win)
{
    for (int i = 0; i < win->bufferCount; ++i)
    {
        z__FREE(win->buffers[i]);
    }
    z__FREE(win->buffers);

    win->size.x = -1;
    win->size.y = -1;
    win->bufferCount = -1;
}

/*
void zse_rtT_tiskTest()
{
    zse_rtT_init();
    zse_rtT_hideCursor();
    char buff1[] = "Asfjasj alshfa lsajsf  ashfaj fs ajshfakjf ajshf\n";
    char buff2[] = "sdfjsglkawljahw jawhdjahwflah lakfj\n";


    zse_rtT__set00();
    sleep(1);
    write(STDOUT_FILENO, buff1, sizeof(buff1));
    
    for (int i = 0; i < 12; i++) {
        write(STDOUT_FILENO, buff2, sizeof(buff2));
        sleep(1);
    }

    zse_rtT_showCursor();
    zse_rtT_exit();

    return;
}
*/
