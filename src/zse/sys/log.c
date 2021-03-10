#include <stdarg.h>
#include <stdio.h>
#include "sys.h"

void zse_sys_log(void * fileStream ,const char * restrict format, ...)
{
    va_list args;

    fputs("LOG: ", stdout);

    va_start(args, format);
    vfprintf(fileStream, format, args);
    va_end(args);

}
