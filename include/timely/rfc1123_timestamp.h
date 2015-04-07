#ifndef TIMELY_RFC1123_TIMESTAMP_H
#define TIMELY_RFC1123_TIMESTAMP_H

//#include "timely.h"
#include <time.h>
// #include <stdlib.h>

#ifndef _RSIZE_T
    #define _RSIZE_T
    typedef size_t rsize_t;
#endif

static inline size_t timely_rfc1123_timestamp(char *restrict dest, rsize_t dmax, const time_t *restrict timer)
{
    if (dmax <= 0 || *timer == (time_t)(-1)) return 0;

    struct tm *timeptr = gmtime(timer);

    if (timeptr == NULL) return 0;

    //! This maximum number of characters in an RFC1123 date is 29 + 1 for '\0'.
    enum { RFC1123_SIZE = 30 };
    const char *RFC1123_FORMAT = "%a, %d %b %Y %T GMT";
    size_t dlen = strftime(dest, RFC1123_SIZE, RFC1123_FORMAT, timeptr);

    if (dlen <= 0) {
        dest[0] = '\0';
        return 0;
    }

    return dlen;
}

#endif  /* TIMELY_RFC1123_TIMESTAMP_H */
