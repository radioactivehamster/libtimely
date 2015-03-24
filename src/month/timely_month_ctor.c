#ifndef TIMELY_MONTH_CTOR_H
#define TIMELY_MONTH_CTOR_H

#include <stdint.h>
#include "timely.h"
#include "timely/types/timely_day.h"

///
/// > In C NULL is generally defined as the following
/// > `#define NULL ((void*)0)`
/// > This means that it's a pointer value. In this case your attempting to
/// > assign a pointer (NULL) to a non-pointer value item::element and getting
/// > the appropriate message.
///
/// - <http://stackoverflow.com/questions/11416359/c-setting-a-struct-to-null-incompatible-types-in-assignment>
///
/// TL;DR - A data type must be a pointer to set it as `NULL`.
///
struct timely_day timely_month_ctor(struct timely_day *restrict prev_day)
{
    //!
    //! @todo Maybe use a static var instead of passing the struct argv manually?
    //!       Nope, then it wouldn't be reentrant duh!
    //!

    //! <http://www.timeanddate.com/calendar/?year=1970&country=1>
    if (!prev_day) {
        return timely_day_epoc_ctor();
    }

    uint8_t day_of_week = prev_day->wday + 1;

    if (day_of_week >= TIMELY_DAYS_IN_WEEK) {
        day_of_week = 0;
    }

    return (struct timely_day) {
        .mday = prev_day->mday + 1,  //!< day of month (1 - 31)
        .mon  = prev_day->mon,       //!< month of year (0 - 11)
        .wday = day_of_week          //!< day of week (Sunday = 0)
    };
}

#endif  /* TIMELY_MONTH_CTOR_H */
