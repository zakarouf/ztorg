#include <unistd.h>
#include <sys/ioctl.h>


void zse_r_tiskTest()
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