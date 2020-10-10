#ifndef ZSE_COLOR_H
#define ZSE_COLOR_H

#include "../common.h"


typedef int color_pairs;

typedef struct COLOR_PROFILE_
{
    unsigned short r;
    unsigned short g;
    unsigned short b;

}COLORrgb_p;

#define zse_setcolor(x) attron(COLOR_PAIR(x))
#define zse_createcolor(at, r, g, b) init_color(at, r, g, b)



COLORrgb_p* zse_r_colorsPallete_create (size_t size);
void zse_delete_colorpallete(COLORrgb_p * pallate);
COLORrgb_p* zse_r_colorPload_default(void);

int zse_r_color_initpairs256();

#endif