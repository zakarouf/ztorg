#ifndef Z_COMMON_H
#define Z_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>


#include <time.h>
#include <math.h>

#include "config.h"


#define getindex3d(x, y, z, X, Y) x + ((y)*X) + ((z)*X*Y)

typedef struct _map_editor_brush_t
{

	int x;
	int y;
	int z;
	int ink;
	unsigned char size;
	bool toggle;

}BRUSH_t;

void zse_free2dchar(char **mem, int size);
char **zse_malloc_2D_array_char (unsigned int x, unsigned int y);
char **zse_realloc_2D_array_char (char **arr , unsigned int x, unsigned int y, unsigned int newy);
char** zse_dir_getfnames(char path[], int *getitems);



#endif