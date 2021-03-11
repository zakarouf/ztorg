#include <unistd.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include "tisk.h"


frinl void zse_rtT__setCur(int x, int y)
{
    printf("\x1b[%d;%dH", x, y);
}

frinl void zse_rtT__set00(void)
{
    fputs("\x1b[H",  stdout);
}

frinl void zse_rtT_init(void)
{
    fputs("\x1b[2J", stdout);
}

frinl void zse_rtT_exit(void)
{
    zse_rtT__set00();
    //fputs("\x1b[2J", stdout);
}

frinl void zse_rtT_showCursor(void)
{
    fputs("\x1b[?25h",  stdout);
}

frinl void zse_rtT_hideCursor(void)
{
    fputs("\x1b[?25l",  stdout);
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
