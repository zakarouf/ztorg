#ifndef ZSE_ENTITY_H
#define ZSE_ENTITY_H

#include "../common.h"

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


struct _ENT_STATUS
{
	uint32_t HP;
	uint32_t MP;
	uint32_t XP;
	float SPD;
};

struct _ENT_STRATS {
	uint16_t atk;
	uint16_t def;	
};

typedef struct _ENT_ENTTIES
{
	float X;
	float Y;
	float Z;
	float A;
	struct _ENT_STRATS strats;
	struct _ENT_STATUS status;
}ENTT_t;

#endif