#pragma once

#include "timely.h"

//!< `#define TIMELY_MONTH_JANUARY 0`
int _num_days_in_month(uint16_t year, uint8_t month)
{
    printf("(YEAR) %s\n", timely_year_is_leap(year) == true ? "<leap-year>" : "<common-year>");

    if (month != TIMELY_MONTH_FEBRUARY || timely_year_is_leap(year) == false) {
        return ((uint8_t[TIMELY_MONTHS_IN_YEAR]) {
            31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
        })[month];
    }

    return 29;  //!< February 29; leap day.
}
