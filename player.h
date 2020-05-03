#ifndef PLAYER_H
#define PLAYER_H

typedef struct{
	int X;
	int Y;
	int pX;
	int pY;
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