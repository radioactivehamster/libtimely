#ifndef TIMELY_DAY_H
#define TIMELY_DAY_H

#include <stdint.h>

struct timely_day {
    uint8_t wday;           //!< day of week (Sunday = 0)
    uint8_t mon;            //!< month of year (0 - 11)
    uint8_t mday;           //!< day of month (1 - 31)
    //uint8_t day_of_year;
    //uint8_t yday;
};

#endif
