//#include "timely.h"

// --------------------

#ifndef _UTIL_NL
#define _UTIL_NL

#include <stdio.h>

// --------------------

void _printnl(void)
{
    printf("\n");
}

// --------------------

void _printnnl(int n)
{
    int i = 0;

    while (i++ < n) {
        printf("[ %d ]!", i);
        _printnl();
    }
}

#endif /* _UTIL_NL */

// --------------------

#include "_utils/_num_days_in_month.h"
#include "_utils/_timely_epoc_seconds_days_months.h"
