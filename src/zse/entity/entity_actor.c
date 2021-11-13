#include <stdlib.h>
#include "actor.h"

zse_T_Actor *zse_entity__player_new(void) {
	return z__New0(zse_T_Actor, 1);
}
