#ifndef ZTORG_CONFIG_H
#define ZTORG_CONFIG_H


// PI VAL
#define PI_VAL     3.1415926535f
#define DEGREE_90  PI_VAL/2.0f
#define DEGREE_270 3.0f*PI_VAL/2.0f
#define DEGREE_1   0.0174533f


// General
#define ZTORG_VERSION "0.3"

/*Toggle Free Rotation*/
// #define Z_FREE_ROTATION


// PLAY
#define Z_TURN_NORMAL DEGREE_90
#define Z_TURN_FREELOOK DEGREE_1 * 3.0f

// Render
#define RAY_DISTANCE_INCREMENT 0.1f

// Key Config
#define KEY_MOVE_UP_FOR 	'w'
#define KEY_MOVE_DOWN_BACK 	's'
#define KEY_MOVE_SIDE_LEFT 	'a'
#define KEY_MOVE_SIDE_RIGHT 'd'





// Defs
								//  Y  X
#define LOOK_DIRECTION_N	{-1, 0}
#define LOOK_DIRECTION_S	{1, 0}
#define LOOK_DIRECTION_E	{0, 1}
#define LOOK_DIRECTION_W	{0, -1}

#endif