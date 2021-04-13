#ifndef ZSE_RENDER_CURSES_TERMINAL_DEFS_H
#define ZSE_RENDER_CURSES_TERMINAL_DEFS_H

#include "../../common.h"
#include "curses_alias.h"

// Clears Line whilst pretaining the position of window cursor
ZSE__INLINE void zse_rtC_clearLine (WINDOW *win, int line)
{
	int y, x;           
	getyx(win, y, x); 
	wmove(win ,line, 0);     
	wclrtoeol(win);        
	wmove(win ,y, x);        
}

// Clears Line and set the cursor to 0
ZSE__INLINE void zse_rtC_clearLine_set0 (WINDOW *win)
{
	wmove(win ,getcury(win), 0);     // move to begining of line
	wclrtoeol(win);          		 // clear line
}

#endif
