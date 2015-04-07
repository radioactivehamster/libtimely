#ifndef TIMELY_NUM_DAYS_IN_MONTH_H
#define TIMELY_NUM_DAYS_IN_MONTH_H

#include <stdint.h>
#include "./is_leap_year.h"

static inline int8_t timely_num_days_in_month(uint16_t year, uint8_t month)
{
    if (month == 0) return -1;

    enum { FEBRUARY = 2, MONTHS_PER_YEAR = 12 };

    if (month != FEBRUARY || !timely_is_leap_year(year)) {
        return ((uint8_t[]) {
            31,  //! January
            28,  //! February
            31,  //! March
            30,  //! April
            31,  //! May
            30,  //! June
            31,  //! July
            31,  //! August
            30,  //! September
            31,  //! October
            30,  //! November
            31   //! December
        })[month - 1];
    }

    //!< February 29; leap day.
    return 29;
}

#endif /* TIMELY_NUM_DAYS_IN_MONTH_H */
