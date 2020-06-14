#ifndef PLAYER_H
#define PLAYER_H

struct STATS {
	unsigned int HP;
	unsigned int MP;
	unsigned int XP;
};

typedef struct{
	float X;
	float Y;
	float pX;
	float pY;
	char SELF;
	char MODE;
	struct STATS status;
}PLAYER;

typedef struct{
	int X;
	int Y;
	int linkcount;
}EDITOR;

EDITOR e1;
PLAYER p1;

#endif