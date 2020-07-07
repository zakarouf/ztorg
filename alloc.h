#ifndef MALLOC_H
#define MALLOC_H

#include <stdlib.h>
#include <stdint.h>

char **malloc_2D_array_char (unsigned int x, unsigned int y);
uint8_t **malloc_2D_array_uint8 (unsigned int x, unsigned int y, int intialized_int, uint8_t to_be);
uint16_t **malloc_2D_array_uint16 (unsigned int x, unsigned int y, int intialized_int, uint8_t to_be);


#endif