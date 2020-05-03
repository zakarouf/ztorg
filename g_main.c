#include <ncurses.h>
#include <stdint.h>
#include "g_main.h"
#include "player.h"
#include "render.h"
#include "editor.h"
#include "map.h"
#include "map_update.h"


char g_editor () {

	mapED.crnt=1;
	int x = 0, y = 0;
	uint8_t trail_enable=0;
	int scr_x=0, scr_y=0;
	char key=' ', option, trail=mapED.world[y][x];
	char name[54];
	if(e1.linkcount > 1){e1.linkcount = 0;}
	render_scr();
	//endwin();

	while (p1.MODE == 'e') {

		p1.X = x;
		p1.Y = y;

		mapED.world[y][x]=trail;


		switch(key)
		{
			case 'w':
					y--;
				break;
			case 'a':
					x--;
				break;
			case 's':
					y++;
				break;
			case 'd':
					x++;
				break;
			case 'c':
				printw("\nChange Trail ");
				trail = getch();break;
			case 'v':
				trail_enable = trail_enable^1;break;
			case 'g':
					e1.X = x; e1.Y = y;
					echo();
					printw("\nMap Name : ");
					scanw("%s", name);
					p1.SELF = 'X';
					e1.linkcount = add_map_linker(x, y, name, e1.linkcount);
					p1.SELF = '@';
					x = e1.X; y = e1.Y;
			case 'f':
				printw("\nDraw\n");
				echo();
				option = getch();
				if(option == 'a'){e1.X = x; e1.Y = y;}
				if(option == '['){draw_box (x, y, e1.X, e1.Y ,trail);}
				if(option == ']'){fillup_box (x, y, e1.X, e1.Y, trail);}
				if(option == 's'){fillup_circle(x, y, trail);}
				if(option == 'c'){draw_circle(x, y, trail);}
				noecho();
			case 'e':
				option = getch();
				if(option=='q'){p1.MODE = 'y';mapED.crnt=0;return p1.MODE;}
				if(option== 's'){save_map(e1.linkcount);}break;
				break;
			default:
				break;
		}

		option= ' ';

		if(x < 0 || y < 0 || x >= mapED.X || y >= mapED.Y){x = p1.X; y=p1.Y;}
		p1.pX = x;
		p1.pY = y;

		if (!trail_enable)
		{
			trail=mapED.world[y][x];
		}
		mapED.world[y][x]=p1.SELF;

		render_scr_ED(scr_x, scr_y);
		mvprintw(e1.Y, e1.X*2+1,"X");
		mvprintw(mapED.Y+2, scr_x,"X - %d Y - %d\nTRAIL - %d:%c", x, y, trail_enable, trail);

		key = getch();
		//endwin();
	}

	mapED.crnt=0;
	clear();
	echo();
	return p1.MODE;

}




int g_normal (int x, int y, unsigned int emode) {
	map1.crnt=1;
	char key=' ', trail=map1.world[y][x];

	while (p1.MODE == 'n') {

		
		p1.X = x;
		p1.Y = y;

		map1.world[y][x]=trail;


		switch(key)
		{
			case 'w':
					y--;
				break;
			case 'a':
					x--;
				break;
			case 's':
					y++;
				break;
			case 'd':
					x++;
				break;
			case 'g':
				if(emode == 0){
					change_map(x, y);x = p1.X; y = p1.Y;
					break;
				}
				
			case 'e':
				if(emode == 1) {
					mapED.link[e1.linkcount][2] = x;
					mapED.link[e1.linkcount][3] = y;
					map1.crnt = 0;
				}return 4;
			default:
				break;
		}

		if(map1.world[y][x] == '#'){x = p1.X; y = p1.Y;}

		if((x < 0 || y < 0 || x >= map1.X || y >= map1.Y) && (emode != 1))
		{	
			clear();
			switch_neighbour(x, y);
			x = p1.X;
			y = p1.Y;
		}

		p1.pX = x;
		p1.pY = y;
		trail=map1.world[y][x];

		// update player
		map1.world[y][x]=p1.SELF;

		render_scr();
		key = getch();
	}
	return 0;
}