#include <unistd.h>
#include <termios.h>
#include <stdio.h>

#include "tisk.h"
#include "tisk_intra.h"
#include "render_tisk_io.h"

/* OUTPUT */

void zse_rtT_io_printString(String_t *s)
{
    write(STDOUT_FILENO, s->str, s->size);
}

/*INPUTS*/


char zse_rtT_getkey(void)
{
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if(tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if(tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if(read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if(tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return buf;
}
