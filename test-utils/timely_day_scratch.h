#include <stdio.h>

void timely_day_scratch(void)
{
    struct timely_day day;

    for (int m = 0; m < month_days[TIMELY_MONTH_JANUARY]; ++m) {
        day = (m == 0) ? timely_month_ctor(NULL) : timely_month_ctor(&day);

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
