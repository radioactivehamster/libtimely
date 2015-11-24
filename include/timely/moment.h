#ifndef TIMELY_MOMENT_H
#define TIMELY_MOMENT_H

/**
 * @todo Rename this to "instant" as it is the correct term.
 *
 * @see <http://tools.ietf.org/html/rfc3339#section-2>
 *
 * > Timestamp  This term is used in this document to refer to an
 * >            unambiguous representation of some instant in time.
 */

#include <stdbool.h>
#include <stdint.h>
#include <time.h>

struct timely_moment {
    uint16_t year;
    uint8_t  month;
    uint8_t  day;
    int8_t   day_of_week;
    int32_t  seconds;
    time_t   unix_time;
    bool     in_leap_year;
};

#endif /* !TIMELY_MOMENT_H */
