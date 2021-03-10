#ifndef ZSE_SYSTEM_H
#define ZSE_SYSTEM_H

#include "../common.h"

StringLines_t zse_dir_getfnames(char path[]);

int zse_sys_formatCheck(char version[]);
long zse_sys_getRamUsage(void);

zse_int zse_sswitch(zse_int i);
zse_int zse_sswitchS(zse_int i);

#define zse_sswitch_M(i) i* -1
#define zse_sswitchS_M(i) (0b11111111111111111111111111111111 ^ i) + 1

int zse_sys_getLocalTime(int *h, int *m, int *s);

#define zse_sys_fillArrayVal(array, val, len)\
    for (int i = 0; i < len; ++i)\
        array[i] = val;\



// Looger
void zse_sys_log(void * fileStream ,const char * restrict, ...);

#endif
