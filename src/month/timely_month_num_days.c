#include "timely/month/timely_month_num_days.h"

uint16_t timely_month_num_days(uint16_t year, uint8_t month)
{
    if ((month - 1) != TIMELY_MONTH_FEBRUARY || timely_year_is_leap(year) == false) {
        return ((uint8_t[TIMELY_MONTHS_IN_YEAR]) {
            31,  //! January
            28,  //! February
            31,  //! March
            30,  //! April
            31,  //! May
            30,  //! June
            31,  //! July
            31,  //! August
            30,  //! September
            31,  //! October
            30,  //! November
            31   //! December
        })[month - 1];
    }

    //!< February 29; leap day.
    return 29;
}
