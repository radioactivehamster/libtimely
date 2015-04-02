#include <assert.h>
#include <locale.h>
#include "timely.h"
#include "_utils.h"

//!
//! @todo Break down the testsfor epic(ish) focus. DO IT ME!!!!!
//!
int main(void)
{
    // Set our locale to enable localized numeric formatting.
    timely_locale_set_default();

    //! 1. Get the number of seconds since the epoc.
    time_t t = time(NULL);
    assert(t != (time_t)(-1));

    struct timely_moment moment = {
        .year         = TIMELY_YEAR_EPOC,
        .month        = 1,
        .day          = 1,
        .unix_time    = t,
        .in_leap_year = false
     };

    struct timely_epoc epoc;
    struct timely_day day;
    uint8_t month_num_days;
    //~/ int month_num_seconds;

    //! 2. Get the number of days since the epoc (via the epoc structure).
    epoc = timely_epoc_ctor(t);
        //!< { .time, .num_days }

    //! 3. Create a representation of the epoc day (1970.01.01).
    day = timely_day_epoc_ctor();
        //!< { .in_month, /* `0` - calendar month index (0 - 11) */
        //!    .of_month, /* `1` - day of month (1 - 31)         */
        //!    .of_week,  /* `4` - day of week (Sunday = 0)      */
        //!    .of_year } /* `1` - month of year (0 - 11)        */

    // ------------------------------------------------------------

    //! 4. Determine our representation is in a leap year. (initially we won't be)
    moment.in_leap_year = timely_year_is_leap(moment.year);  //-/ (TIMELY_YEAR_EPOC);

    //! ~5~. Get the number of days in the representation month.


    //! ~6~. Calculate the amount of seconds the month consists of.
    //~/month_num_seconds = (month_num_days * TIMELY_DAY_SECONDS_PER);

    //! ~7~. Check if we have enough time in our timer for the entire month.
    //~/t -= month_num_seconds;

    //~/ if (t < 0) {
        //-/ Handle a partial month...
    //~/ }

    //! 8. Iteratively process the days of each month in the year.
    while (moment.month <= 12) {
        month_num_days = timely_month_num_days(moment.year, moment.month);
        printf("[month_num_days]: %hhu\n", month_num_days);
        printf("--------------------\n");

        //! 8.1. Iteratively process the days of the month.
        for (moment.day = 1; (moment.day - 1) < month_num_days; ++moment.day, moment.unix_time -= TIMELY_DAY_SECONDS_PER) {
            printf("%04hu.%02hhu.[%02hhu]:<%ld>\n", moment.year, moment.month, moment.day, moment.unix_time);
        }
        printf("\n==========\n\n");
        ++moment.month;
    }

    // ------------------------------------------------------------

    //! Janky test thingy...
    ++moment.year;
    moment.month = 1;

    while (moment.month <= 12) {
        month_num_days = timely_month_num_days(moment.year, moment.month);
        printf("[month_num_days]: %hhu\n", month_num_days);
        printf("--------------------\n");

        //! 8.1. Iteratively process the days of the month.
        for (moment.day = 1; (moment.day - 1) < month_num_days; ++moment.day, moment.unix_time -= TIMELY_DAY_SECONDS_PER) {
            printf("%04hu.%02hhu.[%02hhu]:<%ld>\n", moment.year, moment.month, moment.day, moment.unix_time);
        }
        printf("\n==========\n\n");
        ++moment.month;
    }

    // ------------------------------------------------------------

    //! Janky test thingy part duex...
    ++moment.year;
    moment.month = 1;

    while (moment.month <= 12) {
        month_num_days = timely_month_num_days(moment.year, moment.month);
        printf("[month_num_days]: %hhu\n", month_num_days);
        printf("--------------------\n");

        //! 8.1. Iteratively process the days of the month.
        for (moment.day = 1; (moment.day - 1) < month_num_days; ++moment.day, moment.unix_time -= TIMELY_DAY_SECONDS_PER) {
            printf("%04hu.%02hhu.[%02hhu]:<%ld>\n", moment.year, moment.month, moment.day, moment.unix_time);
        }
        printf("\n==========\n\n");
        ++moment.month;
    }

}
