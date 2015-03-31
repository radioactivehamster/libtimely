#ifndef TIMELY_EPOC_CTOR_H
#define TIMELY_EPOC_CTOR_H

// #include "timely.h"
#include "timely/types/timely_epoc.h"

#ifndef TIMELY_DAY_SECONDS_PER
    #define TIMELY_DAY_SECONDS_PER  86400
#endif

struct timely_epoc timely_epoc_ctor(time_t timer);

#endif  /* TIMELY_EPOC_CTOR_H */
