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

typedef enum ENITY_ALLIANCE
{
	ENT_ALLHOST,
	ENT_ALLPEACE,
	ENT_CUSTOM,

}ENTT_ALL;


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

struct _ENT_SOCIALBIO
{
	uint16_t alliaceID;
};

typedef struct _ENT_ENTTIES
{
	float X;
	float Y;
	float Z;
	float A;
	int Cx;
	int Cy;
	int Cz;
	struct _ENT_STRATS strats;
	struct _ENT_STATUS status;
	uint16_t sign;
}ENTT_t;

typedef struct _ENT_ENTTIESPACK
{
	ENTT_t* ent;
	int esize;
}ENTTP_t;


ENTT_t *zse_entt_init_ENTT_t (ENTCLASS class);
void zse_entt_delete (ENTT_t *ent);

#endif