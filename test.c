#include <assert.h>
#include <locale.h>
#include "timely.h"
#include "_utils.h"

//!
//! @todo Break down the tests for epic(ish) focus. DO IT ME!!!!!
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

    //! 2. Create a representation of the epoc day (1970-01-01T00:00:00Z).
    struct timely_moment moment = {
        .year         = TIMELY_YEAR_EPOC,
        .month        = 1,
        .day          = 1,
        .seconds      = -1,  //!< `int32_t`
        .unix_time    = t,   //!< `time_t`
        .in_leap_year = false
     };

    uint8_t month_num_days;

    // ------------------------------------------------------------

    do {
        //! 3. Determine if the representation is in a leap year. (initially we won't be)
        moment.in_leap_year = timely_year_is_leap(moment.year);  //-/ (TIMELY_YEAR_EPOC);

        //! 4. Iteratively process the days of each month in the year.
        for (moment.month = 1; moment.month <= 12 && moment.unix_time > 0; ++moment.month) {
            month_num_days = timely_month_num_days(moment.year, moment.month);

            //! 5. Iteratively process the days of the month.
            for (moment.day = 1; moment.day <= month_num_days && moment.unix_time > 0;
                ++moment.day, moment.unix_time -= TIMELY_DAY_SECONDS_PER  //!< 86400
            ) {
                printf("%04hu-%02hhu-%02hhu\n", moment.year, moment.month, moment.day);
            }

        }

    } while (moment.unix_time > 0 && ++moment.year);

    // ------------------------------------------------------------
}
