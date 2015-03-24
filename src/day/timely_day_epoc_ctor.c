#include "timely/day/timely_day_epoc_ctor.h"

struct timely_day timely_day_epoc_ctor(void)
{
    return (struct timely_day) {
        .wday = TIMELY_DAY_OF_WEEK_THURSDAY,  //!< day of week (Sunday = 0)
        .mon  = TIMELY_MONTH_JANUARY,         //!< month of year (0 - 11)
        .mday = 1                             //!< day of month (1 - 31)
    };
}
