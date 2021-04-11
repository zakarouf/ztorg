#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <string.h>

#include "_intra.h"
#include "tisk.h"
#include "tisk_io.h"

/* OUTPUT */

void zse_rtT_io_printString(z__String *s)
{
    fwrite(s->data, sizeof(*s->data), s->size, stdout);
    fflush(stdout);
}

/*INPUTS*/

z__u32 zse_rtT__io_getstr(char *str, z__u32 size)
{
    fgets(str, size, stdin);
    z__u32 used = strcspn(str, "\n");
    str[used] = '\0';

    return used;

}

/* TODO: generic Input */
z__u32 zse_rtT__io_input(char *str, char const * const msg, z__u32 strsize)
{
    printf("%s", msg);
    return zse_rtT__io_getstr(str, strsize);
}

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
