#ifndef ZAKAROUF__ZTORG_TISK_IO_H
#define ZAKAROUF__ZTORG_TISK_IO_H

#include "../../common.h"

/* OUT */
void zse_rtT_io_printString(z__String *s);

z__u32 zse_rtT__io_getstr(char *str, z__u32 size);
z__u32 zse_rtT__io_input(char *str, char const * const msg, z__u32 strsize);

/* IN */
char zse_rtT_getkey(void);

#endif
