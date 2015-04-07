#ifndef TIMELY_IS_LEAP_YEAR_H
#define TIMELY_IS_LEAP_YEAR_H

#include <stdint.h>
#include <stdlib.h>

static inline int8_t timely_is_leap_year(uint16_t year)
{
    enum { COMMON_YEAR, LEAP_YEAR, APPROX_YEARS_PER_LEAP = 4, EPOC_YEAR = 1970 };

    if (year <= APPROX_YEARS_PER_LEAP) return -1;

    // > `if (year is not divisible by 4) then (it is a common year)`
    if (year % APPROX_YEARS_PER_LEAP != 0) return COMMON_YEAR;

    // > `else if (year is not divisible by 100) then (it is a leap year)`
    if (year % 100 != 0) return LEAP_YEAR;

    // > `else if (year is not divisible by 400) then (it is a common year)`
    if (year % 400 != 0) return COMMON_YEAR;

    // > `else (it is a leap year)`
    return LEAP_YEAR;
}

#endif  /* TIMELY_IS_LEAP_YEAR_H */
