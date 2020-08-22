#ifndef Z_COMMON_H
#define Z_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <ncurses.h>

#include <math.h>

#include "config.h"


#define getindex3d(x, y, z, X, Y) x + ((y)*X) + ((z)*X*Y)


int zse_getint();
int zse_getint_printw_option(char str[]);

#endif