#include <assert.h>
#include <locale.h>
#include "timely.h"
#include "_utils.h"

//!
//! @todo Break down the testsfor epic(ish) focus. DO IT ME!!!!!
//!
int main(void)
{
    //! 1. Get the number of seconds since the epoc.
    time_t t = time(NULL);
    assert(t != (time_t)(-1));

    struct timely_moment{
        uint16_t year;
        uint8_t month;
        uint8_t day;
    };

    struct timely_epoc epoc;
    struct timely_day day;
    bool is_leap_year;
    uint8_t month_num_days;

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

    //-/ printf("[epoc]: %lu, [days]: %ld, [month num days]: %hhu\n", epoc.time, epoc.num_days, month_num_days);
}

// --------------------
