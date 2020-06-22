/*
-----------------------------------------------------
MAIN GAME SEGMENT
	- Also Includes Editor Profile.
----------------------------------------------------*/
#include <stdint.h>
#include <math.h>

#include "g_main.h"

#include "map.h"
#include "map_update.h"

#include "player.h"
#include "editor.h"

#include "it_common.h"

#include "render.h"

//---------------------------------------------------//
#define MVMT_SPD 1.0f
#define TURN_SPEED DEGREE_90
//---------------------------------------------------//

enum{
	HP,
	MP,
	XP
};

char g_editor () {

	const char on_off[2][4] = {"OFF", "ON"};

	mapED.crnt=1;
	int x = mapED.X>>1, y = mapED.Y>>1;

	uint8_t brush_enable=0;
	uint8_t brush_size = 0;

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
				brush_enable ^= 1;
				break;
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
				if(option == 'a') { 
									e1.X = x;
									e1.Y = y;
									mask[e1.Y][e1.X]='A'; 
								  }
				if(option == '[') { draw_box (x, y, e1.X, e1.Y ,trail);		 }
				if(option == ']') { fillup_box (x, y, e1.X, e1.Y, trail);	 }
				if(option == 'o') { fillup_circle(x, y, brush_size, trail);	 }
				if(option == 'c') { draw_circle(x, y, trail);				 }
				if(option == 'v') { scanw("%d", &brush_size);				 }
				noecho();
			case 'e':
				option = wgetch(status);
				if(option =='q'){
									p1.MODE = 'y';
									mapED.crnt=0;
									return p1.MODE;
								}
				if(option == 's'){ save_map(e1.linkcount); }
				break;
			default:
				break;
		}

		option= ' ';

		if(x < 0 || y < 0 || x >= mapED.X || y >= mapED.Y){x = p1.X; y=p1.Y;}
		p1.pX = x;
		p1.pY = y;

		if (brush_enable)
		{
			fillup_circle(x, y, brush_size, trail);
		}
		mask[y][x]=p1.SELF;
		//render_scr_win_ED ();
		render_scr_fin_ED (x, y, scrX, scrY);
		
		wclear(status);
		box(status, 0, 0);
		mvwprintw(status, 1, 1, "X - %d Y - %d", x, y);
		mvwprintw(status, 2, 1, "BRUSH[%s] >> %c || SIZE >> %d", on_off[brush_enable], trail, brush_size);

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

		render_scr_fin (0, 0, x, y, 16, 16);
		key = getch();
	}
	return 0;
}

int g_raytest (float x, float y, float A) {

	const char direction[5][6]={"West","South","East","North","West"};
	const char weapons[TOTAL_WEAPONS][12]= {"Melee", "Gun", "Orb", "Slasher", "Wand", "Mist", "Spell Book", "Gun Mod", "Summon"};
	int direction_int = 1;
	map1.crnt=1;

	float turn_speed = TURN_SPEED;

	int screenX;                // Console screen size X (columns)
	int screenY;               // Console screen size Y (rows)

	char key = ' ';
	uint8_t weapon_wield = 0;

	//Get current screen Size
	getmaxyx(stdscr, screenY, screenX);

	//stats WINDOW
	WINDOW *hud[3]; 
	hud[HP] = newwin(3, 10, screenY-4, 0);

	//initialize shade;
	init_pair(COLOR_WHITE, COLOR_WHITE, COLOR_WHITE);
	init_pair(COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW);
	init_pair(COLOR_RED, COLOR_RED, COLOR_RED);

	while (p1.MODE == 'n') {

		
		p1.X = x;
		p1.Y = y;


		switch(key)
		{

			// Movement
			// FORWARD / BACKWARD
			case 'w':
				x += (int)sinf(A) * MVMT_SPD;
				y += (int)cosf(A) * MVMT_SPD;
				break;
			case 's':
				x -= (int)sinf(A) * MVMT_SPD;
				y -= (int)cosf(A) * MVMT_SPD;
				break;
			// STRAFE LEFT / RIGHT
			case 'e':
				x += (int)cosf(A) * MVMT_SPD;
				y += (int)sinf(A) * MVMT_SPD;				
				break;
			case 'q':
				x -= (int)cosf(A) * MVMT_SPD;
				y -= (int)sinf(A) * MVMT_SPD;
				break;
			// TURN LEFT / RIGHT
			case 'a':
				A -= turn_speed;
				direction_int -= 1;
				if(A <= 0.0f ){A = PI_VAL*2; direction_int = 5;}
				break;
			case 'd':
				A += turn_speed;
				direction_int += 1;
				if(A >= PI_VAL*2-1 ){A = 0; direction_int = 1;}
				break;
			// Movement END

			case 'x':
				mvprintw(screenY-1, screenX>>1, "DAMAGED >%d<", w_hitdamage_check(x, y, A, weapon_wield));
				getch();
				wrefresh(stdscr);
			case 'z':
				weapon_wield++;
				if(weapon_wield >= TOTAL_WEAPONS)
				{
					weapon_wield = 0;
				}
			case 'g':
				x = p1.X;
				y = p1.Y;
				change_map(x, y);
				break;

			// QUIT GAME
			case '`':
				p1.MODE='y';
				return 'y';
				break;
			default:
				break;
		}

		if(map1.world[(int)y][(int)x] == '#'){x = p1.X; y = p1.Y; p1.status.HP--;}

		// MOVABLE OBJECTS '*'
		if(map1.world[(int)y][(int)x] == '*'){
			if(key == 'w')
			{
				if(map1.world[(int)(y+cosf(A)*MVMT_SPD)][(int)(x+sinf(A)*MVMT_SPD)] == ' ')
				{
					map1.world[(int)y][(int)x] = ' ';
					map1.world[(int)(y+(int)cosf(A)*MVMT_SPD)][(int)(x+(int)sinf(A)*MVMT_SPD)] = '*';
				}
				else 
				{
					x = p1.X; 
					y = p1.Y;
				}
			}
			else if (key == 's') 
			{
				x = p1.X; 
				y = p1.Y;
			}
		}

		if((x < 0 || y < 0 || x >= map1.X || y >= map1.Y))
		{	
			clear();
			switch_neighbour(x, y);
			x = p1.X;
			y = p1.Y;
		}

		p1.pX = x;
		p1.pY = y;	

		// MAIN SCREEN
		raycasting_test(x, y , A, screenX, screenY);
		mvprintw(1, (screenX>>1) - 6, "[%s]" ,direction[direction_int]);
		mvprintw(9, 0,"[%s]", weapons[weapon_wield]);
		refresh();

		// HUD STUFF
		box(hud[HP] , 0 , 0);
		mvwaddstr(hud[HP], 0, 1, "HP");
		mvwprintw(hud[HP], 1, 1, "%4d", p1.status.HP);
		wrefresh(hud[HP]);

		if(p1.status.HP == 0)
		{
			return GAME_OVER;	
		}
		key = getch();
	}
	return 0;
}