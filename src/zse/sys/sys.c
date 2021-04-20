#include "sys.h"

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
