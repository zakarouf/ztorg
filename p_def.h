#ifndef PLAYER_DEF_H
#define PLAYER_DEF_H

enum {HP, MP, XP};

typedef enum ENITY_CLASS_STATS
{
	GUNFIEND,
	MONK,
	ROUGE,
	KNIGHT,
	MAGE,
	CLERIC,
	JACK
}ENTCLASS;

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