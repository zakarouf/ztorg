#include <unistd.h>
#include <sys/ioctl.h>


void zse_rtT_tiskTest()
{
	char buff1[] = "abc";

    write(STDOUT_FILENO, buff1, sizeof(buff1) - 1);
    sleep(1);

    for (int i = 0; i < sizeof(buff1); ++i)
    {
    	write(STDOUT_FILENO, "\b", 1);
    }
    for (int i = 0; i < sizeof(buff1); ++i)
    {
    	write(STDOUT_FILENO, " ", 1);
    }
    
    sleep(1);

    write(STDOUT_FILENO, "\n", 1);

    return;
}

void zse_rtT_rewind(int x)
{
    for (int i = 0; i < x; ++i)
    {
        write(STDOUT_FILENO, "\b", 1);
    }
}