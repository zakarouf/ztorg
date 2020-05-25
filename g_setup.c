#include "g_setup.h"
#include "g_main.h"
#include "player.h"

void g_setup_p (char state) {

	char quit='n';

	p1.pX = p1.X = e1.X = 0;
	p1.pY = p1.Y = e1.Y = 0;
	p1.SELF = '@';
	p1.MODE = state;

	while(quit != 'y') {
		switch(p1.MODE)
		{
			case 'n':
				quit = g_normal(p1.X, p1.Y, 0);
			case 'e':
				quit = g_editor();
			default:break;
		}
	}
}