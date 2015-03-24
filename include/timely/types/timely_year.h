#ifndef TIMELY_YEAR_H
#define TIMELY_YEAR_H

#include <stdbool.h>
#include <stdint.h>
#include "timely/types/timely_month.h"

struct timely_year {
    uint16_t num;
    bool leap_year;
    uint16_t num_days;
    struct timely_month months[12];
};

#endif
