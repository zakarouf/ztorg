#include "tisk.h"
#include "tisk_intra.h"
#include "render_tisk_io.h"

void zse_rtT_io_printString(String_t *s)
{
	write(STDOUT_FILENO, s->str, s->size);
}

