#include <assert.h>
#include "timely.h"

int main(void)
{
    //struct timely_day day = timely_month_ctor(NULL);

    //printf("<name>: %s\n<abbr_name>: %s\n<day_of_week>: %d\n<day_of_year>: %d\n\n",
    //       day.name, day.abbr_name, day.day_of_week, day.day_of_year);

    // Start at `1` since we covered the `0` index already.
    //for (int m = 1; m < month_days[TIMELY_MONTH_JANUARY]; ++m) {
    //    day = timely_month_ctor(&day);

    //    printf("<name>: %s\n<abbr_name>: %s\n<day_of_week>: %d\n<day_of_year>: %d\n\n",
    //           day.name, day.abbr_name, day.day_of_week, day.day_of_year);
    //}

    //!
    //! ```c
    //! struct timely_day {
    //!     uint8_t wday;    //!< > day of week (Sunday = 0)
    //!     uint8_t mon;     //!< > month of year (0 - 11)
    //!     uint8_t mday;    //!< > day of month (1 - 31)
    //! };
    //! ```
    //!
    //struct timely_day day = timely_day_epoc_ctor();

    struct timely_day day;

    for (int m = 0; m < month_days[TIMELY_MONTH_JANUARY]; ++m) {
        day = (m == 0) ? timely_month_ctor(NULL) : timely_month_ctor(&day);

        // printf("## " TIMELY_MONTH_NAME(TIMELY_MONTH_JANUARY) " ##\n"
            // "<mday>: %d\n<mon>: %d\n<wday>: %d\n\n",
            // day.mday, day.mon, day.wday);


        // printf("## %s | %s ##\n" "<mday>: %d\n<mon>: %d\n<wday>: %d\n\n",
            // TIMELY_MONTH_NAME(TIMELY_MONTH_JULY),
            // TIMELY_DAY_NAME(dn), day.mday, day.mon, day.wday);

        printf("\n## NEW DAY ##\n");
        printf("<day.of_month>: %02d\n", day.of_month);
        printf("<day.of_week>:  %02d\n", day.of_week);
        printf("<day.of_year>:  %03d\n", day.of_year);
    }

    char buffer[BUFSIZ] = {0};

    rsize_t rbuf = timely_day_name_var(NULL, 0, 0);

    printf("\n-------\n\n<rbuf>: %zu\n", rbuf);

    if (timely_day_name_var(buffer, 0, BUFSIZ) == 0) {
        fprintf(stderr, "Sad face writing to our dest buffer. :(\n");
        //exit(-1);
    } else {
        printf("\n--------\n\n%s\n\n", buffer);
    }

    buffer[0] = '\0';
}
