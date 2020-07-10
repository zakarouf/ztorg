#include "p_npc.h"

int npc_set_stat (NPC* npc, int member, int tier)
{
	if (tier == 1)	{
	struct STATUS_ATTR status[8] = {
	//	  HP  MP   ATT	 DEF   IN
		{  5,	1,	2 ,  2  ,	1}, // 000 MadMiner
		{ 10,  10,	5 ,  1  ,	2}, // 001 NoviceMage
		{ 12,  76,	3 ,  2  ,	5}, // 002 Assassin
		{ 24,  98, 16 ,  5  ,  12}, // 003 MasterMage
		{  1,  20, 50 ,  1  ,	9}, // 004 MadFollower
		{ 53,  13, 10 , 10  ,	2}, // 005 Knight
		{ 78,	1,	6 , 12  ,	1}, // 006 Chimera
		{200,  20, 17 , 16  ,	4}, // 007 CultLeader

	};

	npc[0].stat.HP = status[member].HP ;
	npc[0].stat.MP = status[member].MP ;
	npc[0].stat.ATT = status[member].ATT ;
	npc[0].stat.DEF = status[member].DEF ;
	npc[0].stat.IN = status[member].IN ;
	}
	else
	{
		return -1;
	}

	return 0;

}