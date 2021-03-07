#include <unistd.h>
#include <sys/ioctl.h>
#include "../../common/common_string.h"
#include "tisk_intra.h"

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