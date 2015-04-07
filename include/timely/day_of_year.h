#ifndef TIMELY_DAY_OF_YEAR_H
#define TIMELY_DAY_OF_YEAR_H

#include <stdint.h>
#include "./num_days_in_month.h"

static inline int16_t timely_day_of_year(uint16_t year, uint8_t month, uint8_t day)
{
    int16_t day_of_year = (-1);

    for (uint8_t m = 1; m < month; ++m)
        day_of_year += timely_num_days_in_month(year, month);

    //for (uint8_t m = 0; m < (month - 1); ++m)
    //    day_of_year += timely_num_days_in_month(year, month);

    day_of_year += day;

    return day_of_year;
}

#endif  /* TIMELY_DAY_OF_YEAR_H */
