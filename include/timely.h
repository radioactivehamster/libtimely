#ifndef TIMELY_H
#define TIMELY_H

//! Time base values for `timespec_get` as per the C11 spec
#ifndef TIME_UTC
    #define TIME_UTC (1)
#endif

//-/ --------------------

#include "timely/day_of_year.h"
#include "timely/iso8601_utc_timestamp.h"
#include "timely/moment.h"
#include "timely/num_days_in_month.h"
#include "timely/rfc1123_gmt_timestamp.h"
#include "timely/tm_ctor.h"

#endif  /* TIMELY_H */
