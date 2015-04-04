#include <assert.h>
#include <locale.h>
#include "timely.h"
#include "_utils.h"

int16_t timely_year_day_of(uint16_t year, uint8_t month, uint8_t day)
{
    int16_t day_of_year = (-1);

    for (uint8_t m = 0; m < (month - 1); ++m) {
        day_of_year += timely_month_num_days(year, month);
    }

    day_of_year += day;

    return day_of_year;
}

//!
//! @todo Generate a broken-down time `tm` struct.
//!
//! ### `struct tm` Members
//!
//! ```c
//! int tm_sec;     /* seconds (0 - 60) */
//! int tm_min;     /* minutes (0 - 59) */
//! int tm_hour;    /* hours (0 - 23) */
//! int tm_mday;    /* day of month (1 - 31) */
//! int tm_mon;     /* month of year (0 - 11) */
//! int tm_year;    /* year - 1900 */
//! int tm_wday;    /* day of week (Sunday = 0) */
//! int tm_yday;    /* day of year (0 - 365) */
//! int tm_isdst;   /* is summer time in effect? */
//! char *tm_zone;  /* [non-standard] abbreviation of timezone name */
//! long tm_gmtoff; /* [non-standard] offset from UTC in seconds */
//! ```
//!
//! ```c
//! size_t
//! strftime(char *restrict s, size_t maxsize, const char *restrict format,
//!     const struct tm *restrict timeptr);
//! ```
//!
int main(void)
{
    // Set our locale to enable localized numeric formatting.
    timely_locale_set_default();

    //! 1. Get the number of seconds since the epoc.
    time_t t = time(NULL);
    assert(t != (time_t)(-1));

    //! ISO 8601 Format
    //! ---------------
    //!   2015-04-01T04:41:51-04:00 [[in EST]]
    //!   2015-04-01T08:41:51+00:00 [[in UTC]]
    //!   2015-04-01T08:41:51Z

    //! @see https://en.wikipedia.org/wiki/ISO_8601#Durations

    struct {
        int y;
        int m;
        int d;
    } dt = { .y = 2015, .m = 4, .d = 4 };

    int16_t day_of_year = timely_year_day_of(dt.y, dt.m, dt.d);

    printf("%04d-%02d-%02d\n", dt.y, dt.m, dt.d);
    printf("[timely] Day of year: %hu\n", day_of_year);

    struct tm *timeptr = gmtime(&t);

    printf("%04d-%02d-%02d\n", (timeptr->tm_year + 1900), (timeptr->tm_mon + 1), timeptr->tm_mday);
    printf("[stdlib] Day of year: %d\n", timeptr->tm_yday);


    // ------------------------------------------------------------

    ///printf("[libtimely:iso8601]: %04hu-%02hhu-%02hhuT%02d:%02d:%02dZ\n",
    ///    moment.year, moment.month, moment.day, h, m, s);
    ///printf("[gmtime:iso8601]:    %04d-%02d-%02dT%02d:%02d:%02dZ\n",
    ///    (timeptr->tm_year + 1900), (timeptr->tm_mon + 1), timeptr->tm_mday,
    ///    timeptr->tm_hour, timeptr->tm_min, timeptr->tm_sec);
}
