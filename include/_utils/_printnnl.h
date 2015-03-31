#ifndef _UTIL__PRINTNNL
#define _UTIL__PRINTNNL

#include "_utils/_printnl.h"

void _printnnl(int n)
{
    int i = 0;

    while (i++ < n) {
        _printnl();
    }
}

#endif  /* _UTIL__PRINTNNL */
