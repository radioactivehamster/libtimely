#ifndef TIMELY_GMT_RFC1123_TIMESTAMP_H
#define TIMELY_GMT_RFC1123_TIMESTAMP_H

#include <limits.h>
#include <time.h>

//! This maximum number of characters in an RFC1123 date is 29 + 1 for '\0'.
enum { RFC1123_GMT_SIZE = 30 };

static inline int timely_gmt_rfc1123_timestamp(char *restrict dest, const time_t *restrict timer)
{
    if (*timer == (time_t)(-1)) return 0;

    struct tm *timeptr = gmtime(timer);

    if (timeptr == NULL) return 0;

    const char *format = "%a, %d %b %Y %T GMT";
    size_t dlen = strftime(dest, RFC1123_GMT_SIZE, format, timeptr);

    return (dlen <= INT_MAX) ? (int)dlen : -1;
}

#endif  /* TIMELY_GMT_RFC1123_TIMESTAMP_H */
