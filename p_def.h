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
	int XP;
	
};


typedef struct
{
	float X;
	float Y;
	float A;
	struct STATUS_ATTR stat;
}
PLAYER;

#endif