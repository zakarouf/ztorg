#ifndef PLAYER_H
#define PLAYER_H

typedef struct{
	float X;
	float Y;
	float pX;
	float pY;
	char SELF;
	char MODE;
}PLAYER;

typedef struct{
	int X;
	int Y;
	int linkcount;
}EDITOR;

EDITOR e1;
PLAYER p1;

#endif