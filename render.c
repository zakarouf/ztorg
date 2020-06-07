/*
-----------------------------------------------------
SCREEN RENDERER SEGMENT
'fin' mode renders only surrounding of player (better
	for bigger maps.)

TODO: Fix error while rendering map with smaller scale
	  than SCREEN X/Y Dimention.
	  ADD Windows
----------------------------------------------------*/

#include "math.h"
#include "render.h"
#include "map.h"
#include "stdlibra.h"


void render_scr_ED (int x, int y) {
	clear();
	for (int i = 0; i < mapED.Y; ++i){

		move(i+y, x);addch('|');

		for (int j = 0; j < mapED.X; ++j){

			addch(mapED.world[i][j]);
			addch(' ');
		}
		printw("\b| %d", i);
	}	
}

void render_scr () {
	clear();
	for (int i = 0; i < map1.Y; ++i)
	{	
		move(i, 0);
		for (int j = 0; j < map1.X; ++j)
		{
			addch(map1.world[i][j]);
			addch(' ');
		}
	}
}


void render_scr_fin (int px, int py) {
	//clear();
	//mask[py][px] = '@';
	int sc = 1, sv = 0;

	int i = py - (int)(SCREEN_Y/2) -1, j;

	int end_i = py + (int)(SCREEN_Y/2) +1;
	int end_j = px + (int)(SCREEN_X/2) +1;

	if (end_i >= map1.Y) { end_i = map1.Y; i = map1.Y - SCREEN_Y -1; }
	if (end_j >= map1.X) { end_j = map1.X; j = map1.X - SCREEN_X -1; }
	
	if (i < 0) {i = 0;}

	for (; i < end_i; ++i)
	{

		j = px - (int)(SCREEN_X/2) -1;
		if (j < 0)  { j = 0;}
		

		move(sc, sv);
		for (; j < end_j; ++j)
		{

			addch(map1.world[i][j]);
			//if(mask[i][j] == '@')
			/*{
				addch('\b');
				addch('@');
			}*/
		}
		sc++;
	}
	mvaddch(py+1, px, '@');
	
}

void render_scr_fin_ED (int px, int py) {
	clear();
	int sc_y = 0, sc_x = 0;

	int i = py - (int)(SCREEN_Y/2) -1, j;

	int end_i = py + (int)(SCREEN_Y/2) +1;
	int end_j = px + (int)(SCREEN_X/2) +1;

	if (end_i >= mapED.Y) {end_i = mapED.Y; i = mapED.Y - SCREEN_Y -1;}
	if (i < 0) {i = 0;
		if(SCREEN_Y <= mapED.Y){
			end_i = SCREEN_Y+1;
		}
	}

	sc_y++;

	for (; i < end_i; ++i)
	{

		j = px - (int)(SCREEN_X/2) -1;
		if (end_j >= mapED.X) {end_j = mapED.X; j = mapED.X - SCREEN_X -1;}
		if (j < 0) {j = 0;
			if(SCREEN_X <= mapED.X){
				end_j = SCREEN_X+1;
			}
		}

		move(sc_y, sc_x);
		for (; j < end_j; ++j)
		{	
			if (mask[i][j] != ' ')
			{
				printw("%c ", mask[i][j]);
			}
			else {
				printw("%c ",mapED.world[i][j]); 		//plot map
			}
			
		}
		printw("\b| %d", i);
		sc_y++;
	}
	addch('\n');

	j = px - (int)(SCREEN_X/2) -1;
	if (end_j >= mapED.X) {end_j = mapED.X; j = mapED.X - SCREEN_X -1;}
	if (j < 0)  { j = 0;}
	for (; j < end_j; ++j)
	{
		printw("%i ", j%10);
	}
	addch('\n');

	j = px - (int)(SCREEN_X/2) -1;
	if (end_j >= mapED.X) {end_j = mapED.X; j = mapED.X - SCREEN_X -1;}
	if (j < 0)  { j = 0;}
	addch(' ');
	for (; j < end_j; j++)
	{
		if (j%10==0)
		{
			attron(COLOR_PAIR(1));
			printw("\b%d", j/10);
			attroff(COLOR_PAIR(1));
		};
		addch(' ');addch(' ');
	}
}

void raycasting_test (float playerX, float playerY, float playerA, int scrWIDTH,int scrHEIGHT) {
	clear();

	move(0, 0);

	for (int x = 0; x < scrWIDTH; x++) 
	{
		float ray_angle = (playerA - FOV / 2.0f) + ((float)x / (float)scrWIDTH * FOV);

		float ray_distance = 0;
		int chech_if_hitwall = 0;

		int out_of_bounds = 0;

		float p_eyeX = sinf(ray_angle);
		float p_eyeY = cosf(ray_angle);

		while (!chech_if_hitwall && ray_distance < DEPTH && !out_of_bounds)
		{
			ray_distance += 0.1f;

			int testX = (int)(playerX + p_eyeX * ray_distance);
			int testY = (int)(playerY + p_eyeY * ray_distance);

			if(testX < 0 || testX >= map1.X || testY < 0 || testY >= map1.Y){

				chech_if_hitwall = 1;
				//out_of_bounds = 1;
				ray_distance = DEPTH;
			}
			else {
				if(map1.world[testY][testX] == '#') {chech_if_hitwall = 1;}
			}	
		} // WHILE LOOP END

		int ceiling = (scrHEIGHT / 2) - scrHEIGHT / (ray_distance);
		int floor = scrHEIGHT - ceiling;

		for (int y = 0; y < scrHEIGHT; y++)
		{
			if(y > ceiling && y <= floor){
				attron(COLOR_PAIR(1));
				mvaddch(y, x, '#');
				attroff(COLOR_PAIR(1));
			}
		}
	}
	mvprintw(0, 0, "X %2f Y %f A %2f", playerX, playerY, playerA);
}

/*
void raycasting_test (float px, float py, float pa, int scrWIDTH,int scrHEIGHT) {

	clear();

	move(0, 0);
	for (int column = 0; column < scrWIDTH; ++column)
	{
        float rayAngle = (pa - FOV / 2.0f) + ((float)column / (float)scrWIDTH) * FOV;            
        float distance = 0.0f;
        int hitWall = 0;

        float eyeX = sinf(rayAngle); 
		float eyeY = cosf(rayAngle);

        while(!hitWall && distance < DEPTH)     // Find distance to wall
            {
                distance += 0.5f; // resolution
                
                int test_col = (int)(px + eyeX * distance);
                int test_row = (int)(py + eyeY * distance);
                
                // Test if ray is out of bounds
                if(test_col < 0 || test_col >= map1.X || test_row < 0 || test_row >= map1.Y )
                {
                    hitWall = 1;
                    distance = DEPTH;
                }
                
                else
                {
                    if(map1.world[test_col][test_row] == '#') hitWall = 1;
                }
            }
            int ceiling = (float)(scrHEIGHT / 2.0f) - scrHEIGHT / ((float)distance);
            int floor = scrHEIGHT - ceiling;
            
            // Shader walls based on distance
            char shade;
            
            if(distance <= DEPTH / 4.0) shade = '0'; // close
            else if(distance <= DEPTH / 3.0) shade = 'I'; // further;
            else if(distance <= DEPTH / 2.0) shade = ':';
            else if(distance <= DEPTH) shade = '`';
            else {shade = ' ';}

          	for(int row = 0; row < scrHEIGHT; row++)
            {
                if(row <= ceiling)
                {
                    mvaddch(row, column, ' ');
                }
                
                else if(row > ceiling && row <= floor)
                {
                    mvaddch(row, column, shade);
                }
                
                else
                {
                    // Shade floor based on distance
                    float b = 1.0f - (((float)row - scrHEIGHT / 2.0f) / ((float)scrHEIGHT / 2.0f));
                    
					if (b < 0.25) shade = '_';
					else if (b < 0.5) shade = '-';
					else if (b < 0.75) shade = '.';
					else if (b < 0.9) shade = '\'';
					else shade = ' ';
                    
                    mvaddch(row, column, shade);
                }
            }
	}

	mvprintw(0, 0, "X %2f Y %f A %2f", px, py, pa);
	

}
*/
