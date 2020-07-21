#ifndef MAP_LIB_H
#define MAP_LIB_H

#include "map_def.h"

/*
---------------------------------------------------------------------
MAP SUPPORTED VERSION AND SIGNATURE

IT refers to the current supported version of MAP

IT remains the same until a new MAP LOADER build makes it unable
to load legacy map files in which case A new Version Will be set
corresponding to the Map Version last supported.

---------------------------------------------------------------------*/
#define MAP_VERSION_CURRENT_SIG ZTORG_VERSION
#define MAP_VERSION_SUPPORT_SIG "0.3"
/*-------------------------------------------------------------------*/

/*
---------------------------------------------------------------------
Map Directory Structure
---------------------------------------------------------------------*/
#define MAP_DIR_NAME "./maps"
/*-------------------------------------------------------------------*/


/*-------------*/
// 	  READ 	   //
/*-------------*/


uint8_t **map_read_world (char map_name [], uint16_t *X, uint16_t *Y, char tilename[] ,uint8_t *error_n);

/*
-------------------------------------------------------------
uint8_t **read_map_world (char[], uint16_t, uint16_t, uint8_t *error_n); 
___ERROR_CODE___

0 - ALL OK
1 - map does not exist
2 - world does not exist
3 - link does not exist

-------------------------------------------------------------*/


/*-------------*/
// 	  WRITE    //
/*-------------*/
int map_write_world (MAP *map, char map_name[], char tilename[], bool new_map);



#endif