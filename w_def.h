#ifndef WEAPON_DEFINITAION_H
#define WEAPON_DEFINITAION_H

#include "z_include.h"

#define MAX_WEAPONSLOT 16

typedef struct WEAPON_PERK
{
	uint8_t range;
	uint8_t dmg;
	int maxShots;

}WEAPONperk_t;


typedef struct WEAPON_MAIN_LOAD
{
	char *name[16];
	//char **skin;
	WEAPONperk_t *perk;

}WEAPON_t;


#endif