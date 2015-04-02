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

    //-/ struct timely_moment {
    //-/     uint16_t year;
    //-/     uint8_t month;
    //-/     uint8_t day;
    //-/     time_t unixtime;
    //-/ };

    struct timely_epoc epoc;
    struct timely_day day;
    bool is_leap_year;
    uint8_t month_num_days;
    int month_num_seconds;
    struct timely_moment moment = { .year = TIMELY_YEAR_EPOC, .month = 1, .day = 1 };

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
    is_leap_year = timely_year_is_leap(TIMELY_YEAR_EPOC);

    //! 5. Get the number of days in the representation month.
    month_num_days = (day.in_month != TIMELY_MONTH_FEBRUARY || is_leap_year == false)
        ? ((uint8_t[TIMELY_MONTHS_IN_YEAR]) { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 })[day.in_month]
        : 29;  //!< February 29; leap day.

    //! 6. Calculate the amount of seconds the month consists of.
    month_num_seconds = (month_num_days * TIMELY_DAY_SECONDS_PER);

    //! 7. Check if we have enough time in our timer for the entire month.
    t -= month_num_seconds;

    if (t < 0) {
        //-/ Handle a partial month...
    }

    //! 8. Iteratively process the remaining days of the month.
    do {
        //! @todo Factor in counting down the unixtime: `TIMELY_DAY_SECONDS_PER`
        printf("[year]: 1970, [month]: January, [day]: %hhu\n", moment.day);
    } while (moment.day++ < month_num_days);

    // ------------------------------------------------------------

    moment.month += 1;
    month_num_days = ((moment.month - 1) != TIMELY_MONTH_FEBRUARY || is_leap_year == false)
        ? ((uint8_t[TIMELY_MONTHS_IN_YEAR]) { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 })[moment.month - 1]
        : 29;  //!< February 29; leap day.

    t -= (month_num_days * TIMELY_DAY_SECONDS_PER);

    if (t < 0) {
        //-/ Handle a partial month...
    }

    printf("\n==========\n\n");

    moment.day = 1;

    do {
        printf("[year]: 1970, [month]: February, [day]: %hhu\n", moment.day);
    } while (moment.day++ < month_num_days);

    // ------------------------------------------------------------

    //printf("[epoc]: %'lu, [days]: %ld, [month num days]: %hhu, [month num seconds]: %'d\n",
    //    epoc.time, epoc.num_days, month_num_days, month_num_seconds);
}

// --------------------
