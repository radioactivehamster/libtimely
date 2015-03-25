#ifndef TIMELY_EPOC_H
#define TIMELY_EPOC_H

#include <stdint.h>
#include <time.h>
#include "timely/types/timely_year.h"

//! `typedef long __darwin_time_t;` in `/usr/include/i386/_types.h`
struct timely_epoc {
    time_t time;
    uint16_t year;
    uint16_t num_years;
    time_t num_days; //!< @todo Is `time_t` the right type? <T> should be signed.
    struct timely_year years[];
};

#endif /* TIMELY_EPOC_H */
