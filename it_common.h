#ifndef ITEMS_COMMON
#define ITEMS_COMMON

enum {
	IT_MELEE_W,
	IT_GUN_W,
	IT_ORB_W,
	IT_SLASHER_W,
	IT_WAND_W,
	IT_MIST_W,
	IT_SPELLBOOK_W,
	IT_GUNMOD_W,
	IT_SUMMON_W,
};

#define TOTAL_WEAPONS 9

int w_hitdamage_check (int x,int y, float angle, int w_id);

#endif