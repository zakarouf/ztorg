#include "alloc.h"

char **malloc_2D_array_char (unsigned int x, unsigned int y) {

	char **arr = (char**) malloc(y * sizeof(char*));
	for (int i = 0; i < y; ++i)
	{
		arr[i] = (char*)malloc(y * sizeof(char));
	}

    return arr;

}

uint8_t **malloc_2D_array_uint8 (unsigned int x, unsigned int y, int intialized_int, uint8_t to_be) {

	uint8_t **arr = (uint8_t**) malloc(y * sizeof(uint8_t*));
	for (int i = 0; i < y; ++i)
	{
		arr[i] = (uint8_t*)malloc(y * sizeof(uint8_t));
	}

	if (intialized_int != 0)
	{
		for (int i = 0; i < y; ++i)
		{
			for (int j = 0; j < x; ++j)
			{
				arr[i][j] = to_be;
			}
		}
	}

    return arr;

}

uint16_t **malloc_2D_array_uint16 (unsigned int x, unsigned int y, int intialized_int, uint8_t to_be) {

	uint16_t **arr = (uint16_t**) malloc(y * sizeof(uint16_t*));
	
	for (int i = 0; i < y; ++i)
	{
		arr[i] = (uint16_t*)malloc(y * sizeof(uint16_t));
	}

	if (intialized_int != 0)
	{
		for (int i = 0; i < y; ++i)
		{
			for (int j = 0; j < x; ++j)
			{
				arr[i][j] = to_be;
			}
		}
	}

    return arr;

}