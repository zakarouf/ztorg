#ifndef ZAKAROUF_ZSE__ENTITY_PLAYER_DEF_H
#define ZAKAROUF_ZSE__ENTITY_PLAYER_DEF_H

#include "../common.h"


#if 0
#define zse_T_Actor(M, ...)\
	struct {						\
		z__u64 uid;					\
		z__Vector3 pos, velocity;	\
		M map;						\
		__VA_ARGS__;				\
	}

#else

#define zse_T_Actor(Name, M, V, ...)\
	z__Record(Name, (z__u64, uid), (z__Vector3, pos, velocity), (M, map), (V, visual), __VA_ARGS__)

#endif


typedef
	struct {
		z__u64 uid;
		z__Vector3 pos, velocity;
} zse_T_Actor;

#endif

