#ifndef TIMELY_TM_CTOR_H
#define TIMELY_TM_CTOR_H

#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include "./day_of_year.h"
#include "./is_leap_year.h"
#include "./moment.h"
#include "./num_days_in_month.h"

struct tm *timely_tm_ctor(struct tm *dest, const time_t *timer)
{
    enum { THURSDAY = 5, EPOC_YEAR = 1970, SECONDS_PER_DAY = 86400 };

    struct timely_moment moment = {
        .year         = EPOC_YEAR,
        .month        = 1,
        .day          = 1,
        .day_of_week  = THURSDAY, //!< Not using zero index.
        .seconds      = (-1),
        .unix_time    = *timer,
        .in_leap_year = false
    };

    uint8_t month_num_days;

    // ------------------------------------------------------------

    do {
        moment.in_leap_year = timely_is_leap_year(moment.year);

        for (moment.month = 1;
            moment.month <= 12 && moment.unix_time >= SECONDS_PER_DAY;
            ++moment.month
        ) {
            month_num_days = timely_num_days_in_month(moment.year, moment.month);

            for (moment.day = 1;
                moment.day <= month_num_days && moment.unix_time >= SECONDS_PER_DAY;
                ++moment.day, moment.unix_time -= SECONDS_PER_DAY,
                    moment.day_of_week = (moment.day_of_week == 7) ?
                        1 : (moment.day_of_week + 1)
            );

            if (moment.unix_time < SECONDS_PER_DAY) {
                break;
            }
        }
    } while (moment.unix_time >= SECONDS_PER_DAY && ++moment.year);

    // ------------------------------------------------------------

    assert(moment.unix_time <= INT_MAX);

    int h = (-1), m = (-1), s = (-1);

    s = moment.unix_time;

    m = (s / 60);
    s -= (m * 60);

    h = (m / 60);
    m -= (h * 60);

    dest->tm_sec   = s;
    dest->tm_min   = m;
    dest->tm_hour  = h;
    dest->tm_mday  = moment.day;
    dest->tm_mon   = (moment.month - 1);
    dest->tm_year  = (moment.year - 1900);
    dest->tm_wday  = (moment.day_of_week - 1);
    dest->tm_yday  = timely_day_of_year(moment.year, moment.month, moment.day);
    dest->tm_isdst = 0;

    /**
     * @todo These are BSD (and adopeted GNU extension) members. Need to look
     *       into the proper feature test macros to enable these.
     * <https://www.gnu.org/software/libc/manual/html_node/Broken_002ddown-Time.html>
     */
    //?//?// tp->tm_zone = "GMT";
    //?//?// tp->tm_gmtoff = 0L;

    return dest;
}

#endif  /* TIMELY_TM_CTOR_H */
