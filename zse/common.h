#ifndef Z_COMMON_H
#define Z_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>


#include <time.h>
#include <math.h>

#include "config.h"

#define zse_xyz3Dto1D(x, y, z, X, Y) x + ((y)*X) + ((z)*X*Y)

typedef uint8_t  zse_u8_t;
typedef uint16_t zse_u16_t;
typedef uint32_t zse_u32_t;
typedef uint64_t zse_u64_t;

typedef int zse_int;

typedef int8_t  zse_i8_t;
typedef int16_t zse_i16_t;
typedef int32_t zse_i32_t;
typedef int64_t zse_i64_t;

typedef struct _map_editor_brush_t
{

	int x;
	int y;
	int z;
	int ink;
	unsigned char size;
	bool toggle;

}BRUSH_t;


#endif