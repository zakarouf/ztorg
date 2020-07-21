#ifndef PLAYER_DEF_H
#define PLAYER_DEF_H

#include <stdint.h>

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
	uint8_t wpn_holding;
	uint16_t wpn_carry;
}
PLAYER;

#endif