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
	{\
	    for (int i = 0; i < len; ++i)\
	        array[i] = val;\
	}


z__i8Arr zse_sys_readFile(char filename[]);
z__Dynt zse_sys__Dynt_readFile(const char filename[],const z__size subDiv,const char *comment, const z__i32 commentLen);

// Logger
void zse_sys_log(void * fileStream ,const char * restrict, ...);


// Data Manipulation
#define zse_sys__draw_u8_fill1z(arr, boundx, boundy, startx, starty, atz ,endx, endy, val)\
	{ for(int y = starty; y < endy; ++y) memset(&arr[zse_xyz3Dto1D(startx, y, atz, boundx, boundy)], val, sizeof(*arr)*endx); }

#endif
