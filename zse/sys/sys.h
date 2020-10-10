#ifndef ZSE_SYSTEM_H
#define ZSE_SYSTEM_H



void zse_free2dchar(char **mem, int size);
char **zse_malloc_2D_array_char (unsigned int x, unsigned int y);
char **zse_realloc_2D_array_char (char **arr , unsigned int x, unsigned int y, unsigned int newy);
char** zse_dir_getfnames(char path[], int *getitems);


#endif