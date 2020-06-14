/*
-----------------------------------------------------
MAIN GAME SEGMENT
	- Includes Also Editor Profile.
----------------------------------------------------*/
#include <stdint.h>
#include <math.h>
#include "g_main.h"
#include "player.h"
#include "render.h"
#include "editor.h"
#include "map.h"
#include "map_update.h"

#define MVMT_SPD .25f

enum{
	HP,
	MP,
	XP
};

char g_editor () {

	mapED.crnt=1;
	int x = mapED.X/2, y = mapED.Y/2;
	uint8_t trail_enable=0;
	int brush_size = 0;

	int scrX, scrY;
	getmaxyx(stdscr, scrY, scrX);

	char key=' ', option, trail=mapED.world[y][x];
	char name[54];

	if(e1.linkcount > 1){e1.linkcount = 0;}

	WINDOW * status = newwin(5, scrX, scrY - 5, 0);




	while (p1.MODE == 'e') {

		p1.X = x;
		p1.Y = y;

		mask[y][x]=' ';

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
				mvwprintw(status, 3, 1,"Change Trail ");
				wrefresh(status);
				trail = wgetch(status);break;
			case 'v':
				trail_enable = trail_enable^1;break;
			case 'g':
					e1.X = x; e1.Y = y;
					echo();
					mvwprintw(status, 3, 1,"Map Name : ");
					mvwscanw(status, 3, 11, "%s", name);
					refresh();
					p1.SELF = 'X';
					e1.linkcount = add_map_linker(x, y, name, e1.linkcount);
					p1.SELF = '@';
					x = e1.X; y = e1.Y;
			case 'f':
				mvwprintw(status, 3, 1, "Draw");
				wrefresh(status);
				echo();
				option = wgetch(status);
				if(option == 'a'){e1.X = x; e1.Y = y;mask[e1.Y][e1.X]='A';}
				if(option == '['){draw_box (x, y, e1.X, e1.Y ,trail);}
				if(option == ']'){fillup_box (x, y, e1.X, e1.Y, trail);}
				if(option == 'o'){fillup_circle(x, y, brush_size, trail);}
				if(option == 'c'){draw_circle(x, y, trail);}
				if(option == 'v'){scanw("%d", &brush_size);}
				noecho();
			case 'e':
				option = wgetch(status);
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

		if (trail_enable)
		{
			fillup_circle(x, y, brush_size, trail);
		}
		mask[y][x]=p1.SELF;
		//render_scr_win_ED ();
		render_scr_fin_ED (x, y, scrX, scrY);
		
		wclear(status);
		box(status, 0, 0);
		mvwprintw(status, 1, 1, "X - %3d Y - %3d", x, y);
		mvwprintw(status, 2, 1, "TRAIL - %d:%c", trail_enable, trail);
		refresh();
		wrefresh(status);
		key = wgetch(status);

	}

	mapED.crnt=0;
	clear();
	echo();
	return p1.MODE;

}



int g_normal (int x, int y, unsigned int emode) {
	map1.crnt=1;
	char key=' ', trail=map1.world[y][x];

	if(emode == 1){
		p1.MODE = 'n';
	}
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
			case 'e':
				if(emode == 1) {
					mapED.link[e1.linkcount][2] = x;
					mapED.link[e1.linkcount][3] = y;
					map1.crnt = 0;
					p1.MODE='e';
				}return 4;
			default:
				break;
		}

		if((x < 0 || y < 0 || x >= map1.X || y >= map1.Y))
		{	
			x = p1.X;
			y = p1.Y;
		}

		p1.pX = x;
		p1.pY = y;
		trail=map1.world[y][x];

		// update player
		map1.world[y][x]=p1.SELF;

		render_scr_fin (x,y);
		key = getch();
	}
	return 0;
}

int g_raytest (float x, float y, float A) {

	//const char direction[]="ESWNE";
	int direction_int = 1;
	map1.crnt=1;

	float turn_speed = DEGREE_90;

	int screenX;                // Console screen size X (columns)
	int screenY;               // Console screen size Y (rows)

	char key=' ';

	//Get current screen Size
	getmaxyx(stdscr, screenY, screenX);

	//stats WINDOW
	WINDOW *hud[3]; 
	hud[HP] = newwin(3, 5, screenY-4, 0);

	//initialize shade;
	init_pair(COLOR_WHITE, COLOR_WHITE, COLOR_WHITE);
	init_pair(COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW);


	while (p1.MODE == 'n') {

		
		p1.X = x;
		p1.Y = y;


		switch(key)
		{
			case 'w':
				x += sinf(A) * MVMT_SPD;
				y += cosf(A) * MVMT_SPD;
				break;
			case 's':
				x -= sinf(A) * MVMT_SPD;
				y -= cosf(A) * MVMT_SPD;
				break;
			case 'e':
				x += cosf(A) * MVMT_SPD;
				y += sinf(A) * MVMT_SPD;				
				break;
			case 'q':
				x -= cosf(A) * MVMT_SPD;
				y -= sinf(A) * MVMT_SPD;
				break;
			case 'a':
				A -= turn_speed;
				direction_int -= 1;
				if(A <= 0.0f ){A = PI_VAL*2; direction_int = 0;}
				break;
			case 'd':
				A += turn_speed;
				direction_int += 1;
				if(A > PI_VAL*2 ){A = 0; direction_int = 1;}
				break;
			case '`':
				p1.MODE='y';
				return 'y';
				break;
			default:
				break;
		}

		if(map1.world[(int)y][(int)x] == '#'){x = p1.X; y = p1.Y; p1.status.HP--;}

		if((x < 0 || y < 0 || x >= map1.X || y >= map1.Y))
		{	
			clear();
			switch_neighbour(x, y);
			x = p1.X;
			y = p1.Y;
		}

		p1.pX = x;
		p1.pY = y;	

		raycasting_test(x, y, A, screenX, screenY);
		refresh();

		box(hud[HP] , 0 , 0);
		mvwaddstr(hud[HP], 0, 1, "HP");
		mvwprintw(hud[HP], 1, 1, "%3d", p1.status.HP);
		wrefresh(hud[HP]);

		if(p1.status.HP == 0)
		{
			return GAME_OVER;	
		}
		key = getch();
	}
	return 0;
}