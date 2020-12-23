#include "sys.h"

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

zse_int zse_sswitch(zse_int i)
{
    return i* -1;
}

zse_int zse_sswitchS(zse_int i)
{
    return (0b11111111111111111111111111111111 ^ i) + 1;
}

int zse_sys_formatCheck(char version[])
{
    for (int i = 0; i < sizeof(ZSE_ENGINE_VERSION); ++i)
    {
        if (version[i] != ZSE_ENGINE_VERSION[i])
        {
            return 1;
        }
    }
    return 0;
}

int zse_sys_getLocalTime(int *h, int *m, int *s)
{
    time_t tCurrentTime;
    struct tm *timeinfo;
    time(&tCurrentTime);
    timeinfo = localtime(&tCurrentTime);
    *h = timeinfo->tm_hour;
    *m = timeinfo->tm_min;
    *s = timeinfo->tm_sec;

    return 0;
}