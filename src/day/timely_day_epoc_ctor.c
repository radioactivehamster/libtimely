#include "timely/day/timely_day_epoc_ctor.h"

struct timely_day timely_day_epoc_ctor(void)
{
    return (struct timely_day) {
        .in_month = TIMELY_MONTH_JANUARY,      //! `0` - calendar month index (0 - 11) - [no map to `struct tm`]
        .of_month = TIMELY_EPOC_DAY_OF_MONTH,  //! `1` - day of month (1 - 31)         - `struct tm.tm_mday`
        .of_week  = TIMELY_DAY_THURSDAY,       //! `4` - day of week (Sunday = 0)      - `struct tm.tm_wday`
        .of_year  = TIMELY_EPOC_DAY_OF_YEAR    //! `1` - month of year (0 - 11)        - `struct tm.tm_mon`
    };
}
