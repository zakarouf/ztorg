#include "sys.h"

#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>

#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef WIN32
#include <windows.h>
#elif _POSIX_C_SOURCE >= 199309L
#include <time.h>   // for nanosleep
#else
#include <unistd.h> // for usleep
#endif

void zse_sys_msleep(int milliseconds)
{ // cross-platform sleep function
#ifdef WIN32
    Sleep(milliseconds);
#elif _POSIX_C_SOURCE >= 199309L
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
#else
    if (milliseconds >= 1000)
      sleep(milliseconds / 1000);
    usleep((milliseconds % 1000) * 1000);
#endif
}

long zse_sys_getRamUsage(void)
{
    struct rusage usage;
    int ret;
    ret = getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss;
}

z__StringLines zse_dir_getfnames(char path[])
{
    DIR * drip = opendir(path);
    if(drip == NULL) return (z__StringLines){0} ;
    struct dirent* dp;


    int items = 8;
    int i = 0;
    z__StringLines fnames = z__StringLines_createEmpty(ZSE_MAX_FILENAME_SIZE, items);

    while((dp = readdir(drip)) != NULL)
    {
        sscanf(dp->d_name, "%s", fnames.data[i]);
        i++;
        if(i >= items)
        {
            items += 8;
            z__StringLines_Resize_Y(&fnames, items);
        }
    }
    closedir(drip);

    return fnames;
}

z__int zse_sswitch(z__int i)
{
    return i* -1;
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

z__i8Arr zse_sys_readFile(char filename[])
{
    FILE *fp;
    if ((fp = fopen(filename, "rb")) == NULL)
    {
        return (z__i8Arr){NULL, -1, -1};
    }

    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);  /* same as rewind(f); */

    void *data = malloc(fsize + 1);
    fread(data, 1, fsize, fp);
    fclose(fp);

    return (z__i8Arr) {
        .data = data,
        .len = fsize +1,
        .lenUsed = fsize +1
    };

}
