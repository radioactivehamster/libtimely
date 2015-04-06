#include <assert.h>
#include <locale.h>
#include "timely.h"
#include "_utils.h"

int timely_moment_test(char dest[], time_t timer);

int16_t timely_year_day_of(uint16_t year, uint8_t month, uint8_t day)
{
    int16_t day_of_year = (-1);

    for (uint8_t m = 0; m < (month - 1); ++m) {
        day_of_year += timely_month_num_days(year, month);
    }

    day_of_year += day;

    return day_of_year;
}

struct tm *timely_timer_to_tm(struct tm *dest, const time_t *timer);

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

    //struct {
    //    int y;
    //    int m;
    //    int d;
    //} dt = { .y = 2015, .m = 4, .d = 4 };

    //int16_t day_of_year = timely_year_day_of(dt.y, dt.m, dt.d);

    //printf("%04d-%02d-%02d\n", dt.y, dt.m, dt.d);
    //printf("[timely] Day of year: %hu\n", day_of_year);

    //struct tm *timeptr = gmtime(&t);

    //printf("%04d-%02d-%02d\n", (timeptr->tm_year + 1900), (timeptr->tm_mon + 1), timeptr->tm_mday);
    //printf("[stdlib] Day of year: %d\n", timeptr->tm_yday);


    // ------------------------------------------------------------

    ///printf("[libtimely:iso8601]: %04hu-%02hhu-%02hhuT%02d:%02d:%02dZ\n",
    ///    moment.year, moment.month, moment.day, h, m, s);
    ///printf("[gmtime:iso8601]:    %04d-%02d-%02dT%02d:%02d:%02dZ\n",
    ///    (timeptr->tm_year + 1900), (timeptr->tm_mon + 1), timeptr->tm_mday,
    ///    timeptr->tm_hour, timeptr->tm_min, timeptr->tm_sec);

    char dest[BUFSIZ] = {0};
    #define ISO8601_MAX 30
    #define ISO8601_FMT "%04d-%02d-%02dT%02d:%02d:%02dZ"
    struct tm *stdlib_tm_ptr = gmtime(&t);
    snprintf(dest, ISO8601_MAX, ISO8601_FMT, (stdlib_tm_ptr->tm_year + 1900),
        (stdlib_tm_ptr->tm_mon + 1), stdlib_tm_ptr->tm_mday,
        stdlib_tm_ptr->tm_hour, stdlib_tm_ptr->tm_min, stdlib_tm_ptr->tm_sec);
    printf("%s\n", dest);
    //timely_moment_test(dest, t);

    printf("[stdlib]\n");
    printf("[tm_sec]: %d\n", stdlib_tm_ptr->tm_sec);
    printf("[tm_min]: %d\n", stdlib_tm_ptr->tm_min);
    printf("[tm_hour]: %d\n", stdlib_tm_ptr->tm_hour);
    printf("[tm_mday]: %d\n", stdlib_tm_ptr->tm_mday);
    printf("[tm_mon]: %d\n", stdlib_tm_ptr->tm_mon);
    printf("[tm_year]: %d\n", stdlib_tm_ptr->tm_year);
    printf("[tm_wday]: %d\n", stdlib_tm_ptr->tm_wday);
    printf("[tm_yday]: %d\n", stdlib_tm_ptr->tm_yday);
    printf("[tm_isdst]: %d\n", stdlib_tm_ptr->tm_isdst);

    printf("\n===================\n");

    //struct tm *timer_tm_ptr = {0};
    //! `struct tm *timely_timer_to_tm(struct tm *dest, const time_t *timer);```
    //!/!!! struct tm *timer_tm_ptr = malloc(sizeof(struct tm));
    //!/!!! timely_timer_to_tm(timer_tm_ptr, &t);

    /**
     * @HEADSUP! This works (method researched in glibc) and coincidently cannot
     * be passed into `free`.
     */
    struct tm timer_tm;
    timely_timer_to_tm(&timer_tm, &t);
    /** @HEADSUP! ...this doesn't */
    //!!!!! struct tm *timer_tm_ptr = NULL;
    //!!!!! timely_timer_to_tm(timer_tm_ptr, &t);

    printf("[timely]\n");
    printf("[tm_sec]: %d\n", timer_tm.tm_sec);
    printf("[tm_min]: %d\n", timer_tm.tm_min);
    printf("[tm_hour]: %d\n", timer_tm.tm_hour);
    printf("[tm_mday]: %d\n", timer_tm.tm_mday);
    printf("[tm_mon]: %d\n", timer_tm.tm_mon);
    printf("[tm_year]: %d\n", timer_tm.tm_year);
    printf("[tm_wday]: %d\n", timer_tm.tm_wday);
    printf("[tm_yday]: %d\n", timer_tm.tm_yday);
    printf("[tm_isdst]: %d\n", timer_tm.tm_isdst);

    //!!!!! printf("[tm_sec]: %d\n", timer_tm_ptr->tm_sec);
    //!!!!! printf("[tm_min]: %d\n", timer_tm_ptr->tm_min);
    //!!!!! printf("[tm_hour]: %d\n", timer_tm_ptr->tm_hour);
    //!!!!! printf("[tm_mday]: %d\n", timer_tm_ptr->tm_mday);
    //!!!!! printf("[tm_mon]: %d\n", timer_tm_ptr->tm_mon);
    //!!!!! printf("[tm_year]: %d\n", timer_tm_ptr->tm_year);
    //!!!!! printf("[tm_wday]: %d\n", timer_tm_ptr->tm_wday);
    //!!!!! printf("[tm_yday]: %d\n", timer_tm_ptr->tm_yday);
    //!!!!! printf("[tm_isdst]: %d\n", timer_tm_ptr->tm_isdst);
    //!!!?? free(timer_tm_ptr);
}

int timely_moment_test(char dest[], time_t timer)
{
    struct timely_moment moment = {
        .year         = TIMELY_YEAR_EPOC,
        .month        = 1,
        .day          = 1,
        .day_of_week  = (TIMELY_DAY_THURSDAY + 1), //!< Not using zero index.
        .seconds      = -1,
        .unix_time    = timer,
        .in_leap_year = false
    };

    uint8_t month_num_days;

    // ------------------------------------------------------------

    do {
        moment.in_leap_year = timely_year_is_leap(moment.year);

        for (moment.month = 1;
            moment.month <= 12 && moment.unix_time >= TIMELY_DAY_SECONDS_PER;
            ++moment.month
        ) {
            month_num_days = timely_month_num_days(moment.year, moment.month);

            for (moment.day = 1;
                moment.day <= month_num_days && moment.unix_time >= TIMELY_DAY_SECONDS_PER;
                ++moment.day, moment.unix_time -= TIMELY_DAY_SECONDS_PER,
                    moment.day_of_week = (moment.day_of_week == 7) ?
                        1 : (moment.day_of_week + 1)
            );

            if (moment.unix_time < TIMELY_DAY_SECONDS_PER) {
                break;
            }
        }
    } while (moment.unix_time >= TIMELY_DAY_SECONDS_PER && ++moment.year);

    // ------------------------------------------------------------

    printf("\n");

    printf("[timely] Day of week: %hhd\n", moment.day_of_week);

    struct tm *tptr = gmtime(&timer);
    //!< Add one for comparison since `tm.tm_wday` is zero indexed.
    //!< `int tm_wday;    /* day of week (Sunday = 0) */`
    printf("[stdlib] Day of week: %d\n", (tptr->tm_wday + 1));

    assert(moment.unix_time <= INT_MAX);

    int h = (-1), m = (-1), s = (-1);

    s = moment.unix_time;

    m = (s / 60);
    s -= (m * 60);

    h = (m / 60);
    m -= (h * 60);

    return timely_rfc1123_timestamp(dest, 21, &timer);
}

// ---------------------------------------------------

struct tm *timely_timer_to_tm(struct tm *dest, const time_t *timer)
{
    struct timely_moment moment = {
        .year         = TIMELY_YEAR_EPOC,
        .month        = 1,
        .day          = 1,
        .day_of_week  = (TIMELY_DAY_THURSDAY + 1), //!< Not using zero index.
        .seconds      = (-1),
        .unix_time    = *timer,
        .in_leap_year = false
    };

    uint8_t month_num_days;

    // ------------------------------------------------------------

    do {
        moment.in_leap_year = timely_year_is_leap(moment.year);

        for (moment.month = 1;
            moment.month <= 12 && moment.unix_time >= TIMELY_DAY_SECONDS_PER;
            ++moment.month
        ) {
            month_num_days = timely_month_num_days(moment.year, moment.month);

            for (moment.day = 1;
                moment.day <= month_num_days && moment.unix_time >= TIMELY_DAY_SECONDS_PER;
                ++moment.day, moment.unix_time -= TIMELY_DAY_SECONDS_PER,
                    moment.day_of_week = (moment.day_of_week == 7) ?
                        1 : (moment.day_of_week + 1)
            );

            if (moment.unix_time < TIMELY_DAY_SECONDS_PER) {
                break;
            }
        }
    } while (moment.unix_time >= TIMELY_DAY_SECONDS_PER && ++moment.year);

    // ------------------------------------------------------------

    //printf("\n");

    //printf("[timely] Day of week: %hhd\n", moment.day_of_week);

    //!?//!!!? struct tm *tptr = gmtime(timer);
    //!< Add one for comparison since `tm.tm_wday` is zero indexed.
    //!< `int tm_wday;    /* day of week (Sunday = 0) */`
    //printf("[stdlib] Day of week: %d\n", (tptr->tm_wday + 1));

    assert(moment.unix_time <= INT_MAX);

    int h = (-1), m = (-1), s = (-1);

    s = moment.unix_time;

    m = (s / 60);
    s -= (m * 60);

    h = (m / 60);
    m -= (h * 60);

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
    //! `int16_t timely_year_day_of(uint16_t year, uint8_t month, uint8_t day);`

    //-// struct tm *timely_tm = malloc(sizeof(struct tm));
    //-// timely_tm->tm_sec   = s;
    //-// timely_tm->tm_min   = m;
    //-// timely_tm->tm_hour  = h;
    //-// timely_tm->tm_mday  = moment.day;
    //-// timely_tm->tm_mon   = (moment.month - 1);
    //-// timely_tm->tm_year  = (moment.year - 1900);
    //-// timely_tm->tm_wday  = (moment.day_of_week - 1);
    //-// timely_tm->tm_yday  = timely_year_day_of(moment.year, moment.month, moment.day);
    //-// timely_tm->tm_isdst = (-1);
    //-// return timely_tm;

    dest->tm_sec   = s;
    dest->tm_min   = m;
    dest->tm_hour  = h;
    dest->tm_mday  = moment.day;
    dest->tm_mon   = (moment.month - 1);
    dest->tm_year  = (moment.year - 1900);
    dest->tm_wday  = (moment.day_of_week - 1);
    dest->tm_yday  = timely_year_day_of(moment.year, moment.month, moment.day);

    //-//-// dest->tm_isdst = (-1);

    /**
     * @todo DST is not applicable to UTC apparently, that makes sense but need
     * to verify!
     */
    dest->tm_isdst = 0;

    /**
     * @todo These are BSD (and adopeted GNU extension) members. Need to look
     *       into the proper feature test macros to enable these.
     * <https://www.gnu.org/software/libc/manual/html_node/Broken_002ddown-Time.html>
     */
    //?//?// tp->tm_zone = "GMT";
    //?//?// tp->tm_gmtoff = 0L;

    return dest;

    //-// return &(struct tm) {
    //-//     .tm_sec   = s,
    //-//     .tm_min   = m,
    //-//     .tm_hour  = h,
    //-//     .tm_mday  = moment.day,
    //-//     .tm_mon   = (moment.month - 1),
    //-//     .tm_year  = (moment.year - 1900),
    //-//     .tm_wday  = (moment.day_of_week - 1),
    //-//     .tm_yday  = timely_year_day_of(moment.year, moment.month, moment.day),
    //-//     .tm_isdst = (int)-1
    //-// };
}
