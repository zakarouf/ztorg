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

StringLines_t zse_dir_getfnames(char path[])
{
    DIR * drip = opendir(path);
    if(drip == NULL) return (StringLines_t){0} ;
    struct dirent* dp;


    int items = 8;
    int i = 0;
    StringLines_t fnames = z__StringLines_createEmpty(ZSE_MAX_FILENAME_SIZE, items);

    while((dp = readdir(drip)) != NULL)
    {
        sscanf(dp->d_name, "%s", fnames.lines[i]);
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

zse_int zse_sswitch(zse_int i)
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
