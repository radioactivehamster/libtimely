#include <assert.h>
#include <locale.h>
#include <limits.h>
#include <stdio.h>  //! BUFSIZ
#include <string.h>
#include <time.h>

#include "timely/day_of_year.h"
#include "timely/moment.h"
#include "timely/num_days_in_month.h"
#include "timely/rfc1123_timestamp.h"
#include "timely/set_default_locale.h"

int timely_moment_test(char dest[], time_t timer);

struct tm *timely_timer_to_tm(struct tm *dest, const time_t *timer);

int main(void)
{
    // Set our locale to enable localized numeric formatting.
    timely_set_default_locale();

    time_t t = time(NULL);
    assert(t != (time_t)(-1));

    printf("[extern int  daylight]: %d\n"
           "[extern long timezone]: %ld\n",
           daylight, timezone);
           // "[extern char  *tzname[]]: %s\n\n",
           // daylight, timezone, *tzname);

    // ------------------------------------------------------------

    char dest[BUFSIZ] = {0};
    #define ISO8601_MAX 30
    #define ISO8601_FMT "%04d-%02d-%02dT%02d:%02d:%02dZ"
    struct tm *stdlib_tm_ptr = gmtime(&t);
    snprintf(dest, ISO8601_MAX, ISO8601_FMT, (stdlib_tm_ptr->tm_year + 1900),
        (stdlib_tm_ptr->tm_mon + 1), stdlib_tm_ptr->tm_mday,
        stdlib_tm_ptr->tm_hour, stdlib_tm_ptr->tm_min, stdlib_tm_ptr->tm_sec);
    printf("%s\n", dest);

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

    struct tm timer_tm;
    timely_timer_to_tm(&timer_tm, &t);

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
}

int timely_moment_test(char dest[], time_t timer)
{
    enum { THURSDAY = 5, EPOC_YEAR = 1970, SECONDS_PER_DAY = 86400 };

    struct timely_moment moment = {
        .year         = EPOC_YEAR,
        .month        = 1,
        .day          = 1,
        .day_of_week  = THURSDAY, //!< Not using zero index.
        .seconds      = -1,
        .unix_time    = timer,
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
