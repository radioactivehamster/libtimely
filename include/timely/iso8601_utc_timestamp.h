#ifndef TIMELY_ISO8601_UTC_TIMESTAMP_H
#define TIMELY_ISO8601_UTC_TIMESTAMP_H

#include <stdio.h>
#include <time.h>
#include "./tm_ctor.h"

#define ISO8601_UTC_SIZE 21

static inline int timely_iso8601_utc_timestamp(char *restrict dest, const time_t *restrict timer)
{
    if (*timer == (time_t)(-1)) return 0;

    struct tm *timeptr = gmtime(timer);

    if (timeptr == NULL) return 0;

    const char *restrict format = "%04d-%02d-%02dT%02d:%02d:%02dZ";

    struct tm tm_ptr;
    assert(timely_tm_ctor(&tm_ptr, timer) != NULL);


    return snprintf(dest, ISO8601_UTC_SIZE, format,
        tm_ptr.tm_year + 1900,
        tm_ptr.tm_mon + 1,
        tm_ptr.tm_mday,
        tm_ptr.tm_hour,
        tm_ptr.tm_min,
        tm_ptr.tm_sec);
}

#endif  /* TIMELY_ISO8601_UTC_TIMESTAMP_H */
