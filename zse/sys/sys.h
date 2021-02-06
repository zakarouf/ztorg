#ifndef ZSE_SYSTEM_H
#define ZSE_SYSTEM_H

#include "../common.h"

void zse_free2dchar(char **mem, int size);
char **zse_malloc_2D_array_char (unsigned int x, unsigned int y);
char **zse_realloc_2D_array_char (char **arr , unsigned int x, unsigned int y, unsigned int newy);
char** zse_dir_getfnames(char path[], int *getitems);

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

#endif