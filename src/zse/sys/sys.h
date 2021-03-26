#ifndef ZSE_SYSTEM_H
#define ZSE_SYSTEM_H

#include "../common.h"

z__StringLines zse_dir_getfnames(char path[]);

int zse_sys_formatCheck(char version[]);
long zse_sys_getRamUsage(void);

z__int zse_sswitch(z__int i);

#define zse_sswitch_M(i) i* -1

int zse_sys_getLocalTime(int *h, int *m, int *s);
void zse_sys_msleep(int milliseconds);

#define zse_sys_fillArrayVal(array, val, len)\
    for (int i = 0; i < len; ++i)\
        array[i] = val;\


z__i8Arr zse_sys_readFile(char filename[]);

// Logger
void zse_sys_log(void * fileStream ,const char * restrict, ...);

#endif
