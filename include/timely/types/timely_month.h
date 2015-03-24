#ifndef TIMELY_MONTH_H
#define TIMELY_MONTH_H

#include <stdint.h>
#include "timely/types/timely_day.h"

struct timely_month {
    const char *name;
    const char *abbr_name;
    struct timely_day days[31]; //-/ `tmly`? or is that lamesauce?
    uint8_t num_days;
};

#endif


// - POSIX
//========

// ABDAY_x
//
// The abbreviated weekday names (for example, Sun), where x is a number from 1 to 7.
//
// DAY_x
//
// The full weekday names (for example, Sunday), where x is a number from 1 to 7.
//
// ABMON_x
//
// The abbreviated month names (for example, Jan), where x is a number from 1 to 12.
//
// MON_x
//
// The full month names (for example, January), where x is a number from 1 to 12.
//
