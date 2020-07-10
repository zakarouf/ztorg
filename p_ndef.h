#ifndef NPC_DEF_H
#define NPC_DEF_H

#include "p_def.h"
#include "map_def.h"

/*
	Make NPC Structure
*/

enum
{
	GUARD,
	PATROL,
	SEARCH,
	HUNTING,
	FLEEING,
}NPC_STATE;


typedef struct NPC_MAIN
{
	uint8_t sight;
	uint8_t state;
	uint8_t weild;
	uint8_t aliance;
	float X;
	float Y;
	struct STATUS_ATTR stat;

}NPC;

#endif