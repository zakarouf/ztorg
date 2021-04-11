#ifndef ZSE_RENDER_TISK_TERMINAL_DEF_H
#define ZSE_RENDER_TISK_TERMINAL_DEF_H

#include "../../common.h"

typedef struct
{
	z__Vint2 size;
	z__i32 bufferCount;

	z__char **buffers;
	z__char *mainWin;

} zset__rtT_TiskWin;

#endif