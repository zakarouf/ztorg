#include "common.h"

int zse_getint()
{
	int r;
	scanw("%d", &r);
	return r;
}

int zse_getint_printw_option(char str[])
{
	int r;
	clear();
	addstr(str);
	scanw("%d", &r);
	return r;
}