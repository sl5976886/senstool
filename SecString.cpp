#include "SecString.h"
#include <Windows.h>


int sec_strcpy(char *strDst, unsigned int uiDstSize, const char *strSrc)
{
    char *p;
    unsigned int available;

    if ((NULL == strDst) || (uiDstSize < 1) || (NULL == strSrc))    return -1;

    p = strDst;
    available = uiDstSize;
    while ((*p++ = *strSrc++) != 0 && --available > 0);

    if (0 == available) { strDst[uiDstSize-1] = 0; }

    return uiDstSize-available;
}

int sec_strcat(char *strDst, unsigned int uiDstSize, const char *strSrc)
{
    char *p;
    unsigned int available;

    if ((NULL == strDst) || (uiDstSize < 1) || (NULL == strSrc))    return -1;

    p = strDst;
    available = uiDstSize;
    while (available > 0 && *p != 0)
    {
        p++;
        available--;
    }

    if (available == 0)     { return 0; }

    while ((*p++ = *strSrc++) != 0 && --available > 0);

    if (available == 0)  { strDst[uiDstSize-1] = 0; }

    return uiDstSize-available;
}

