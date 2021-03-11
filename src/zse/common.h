#ifndef ZSE_COMMON_H
#define ZSE_COMMON_H

#include "config.h"
#include "common/common.h"

#define zse_xyz3Dto1D(x, y, z, X, Y) x + ((y)*X) + ((z)*X*Y)

typedef struct _Standart_brush_t
{

	z__Vint3 pos;
	int ink;
	unsigned char size;
	bool toggle;

}BRUSH_t;


#endif
