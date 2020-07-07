#ifndef PLAYER_DEF_H
#define PLAYER_DEF_H

enum {HP, MP, XP};

struct STATUS_ATTR 
{
	int HP;
	int MP;
	int ATT;
	int DEF;
	int IN;
	
};


typedef struct
{
	float X;
	float Y;
	float A;
	int stat[3];
}
PLAYER;

#endif