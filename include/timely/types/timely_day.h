#ifndef TIMELY_DAY_H
#define TIMELY_DAY_H

#include <stdint.h>

struct timely_day {
    uint8_t in_month;  //!< month of year (0 - 11)                   - [rel] `struct tm.tm_mon`
    int16_t in_year;   //!< year - 1900                              - `struct tm.tm_year`
    int8_t is_dst;     //!< is summer time in effect? (-1 if unsure) - `struct tm.tm_isdst`
    uint8_t of_month;  //!< day of month (1 - 31)                    - `struct tm.tm_mday`
    uint8_t of_week;   //!< day of week (Sunday = 0)                 - `struct tm.tm_wday`
    int16_t of_year;   //!< day of year (0 - 365)                    - `struct tm.tm_yday`

    //! ------------------------
    //! POSIX `struct tm` fields
    //! ------------------------
    //!< char *tm_zone;  /* abbreviation of timezone name */ - e.g. "utc" (???)
    //!< long tm_gmtoff; /* offset from UTC in seconds */


    //-/ int tm_sec;     /* seconds (0 - 60) */
    //-/ int tm_min;     /* minutes (0 - 59) */
    //-/ int tm_hour;    /* hours (0 - 23) */
    //-/ int tm_isdst;   /* is summer time in effect? */
    //-/ char *tm_zone;  /* abbreviation of timezone name */
    //-/ long tm_gmtoff; /* offset from UTC in seconds */
};

#endif  /* TIMELY_DAY_H */
