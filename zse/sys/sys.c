#include "../common.h"

#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>

#include <dirent.h>

char **zse_malloc_2D_array_char (unsigned int x, unsigned int y) {

	char **arr = malloc(y * sizeof(char*));
	for (int i = 0; i < y; ++i)
	{
		arr[i] = (char*)malloc(x * sizeof(char));
	}

    return arr;

}

char **zse_realloc_2D_array_char (char **arr , unsigned int x, unsigned int y, unsigned int newy) {


	arr = realloc(arr ,newy * sizeof(char*));

	for (int i = y; i < newy; ++i)
	{
		arr[i] = malloc(x * sizeof(char));
	}

    return arr;

}

void zse_free2dchar(char **mem, int size)
{
	for (int i = 0; i < size; ++i)
	{
		free(mem[i]);
	}
	free(mem);

}

long zse_sys_getRamUsage(void)
{
    struct rusage usage;
    int ret;
    ret = getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss;
}

char** zse_dir_getfnames(char path[], int *getitems)
{
    DIR * drip = opendir(path);
    if(drip == NULL) return NULL;
    struct dirent* dp;


    int items = 8;
    int i = 0;
    char **fnames = zse_malloc_2D_array_char(ZSE_MAX_FILENAME_SIZE, items);

    while((dp = readdir(drip)) != NULL)
    {
        sscanf(dp->d_name, "%s", fnames[i]);
        i++;
        if(i >= items)
        {
            items += 8;
            fnames = zse_realloc_2D_array_char(fnames, ZSE_MAX_FILENAME_SIZE, items - 8, items);
        }
    }
    closedir(drip);

    *getitems = items;
    return fnames;
}