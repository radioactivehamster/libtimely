#include <assert.h>
#include "timely.h"

void time_h_tm_dump(struct tm *restrict t);
void time_h_scratch(void);
void timely_day_scratch(void);

// --------------------

int main(void)
{
    time_h_scratch();
}

// --------------------

void time_h_tm_dump(struct tm *restrict t)
{
    //-/ size_t col = 60;

    printf("(struct tm) {\n"
           "    .tm_sec    = %02d,     /* seconds (0 - 60)              */\n"
           "    .tm_min    = %02d,     /* minutes (0 - 59)              */\n"
           "    .tm_hour   = %02d,     /* hours (0 - 23)                */\n"
           "    .tm_mday   = %02d,     /* day of month (1 - 31)         */\n"
           "    .tm_mon    = %02d,     /* month of year (0 - 11)        */\n"
           "    .tm_year   = %04d,   /* year - 1900                   */\n"
           "    .tm_wday   = %02d,     /* day of week (Sunday   = 0)    */\n"
           "    .tm_yday   = %03d,    /* day of year (0 - 365)         */\n"
           "    .tm_isdst  = %1d,      /* is summer time in effect?     */\n"
           "    .tm_zone   = \"%s\",  /* abbreviation of timezone name */\n"
           "    .tm_gmtoff = %ld  /* offset from UTC in seconds    */\n"
           "}\n",
           t->tm_sec,
           t->tm_min,
           t->tm_hour,
           t->tm_mday,
           t->tm_mon,
           t->tm_year,
           t->tm_wday,
           t->tm_yday,
           t->tm_isdst,
           t->tm_zone,
           t->tm_gmtoff);
}

// --------------------

//! @link <http://stackoverflow.com/questions/3068397/finding-the-length-of-an-integer-in-c#answer-3068420>
double num_digitsl(long l)
{
    //! `signbit()` > Nonzero integral value if arg is negative, ​0​ otherwise.

    //!< @link Errors are reported as specified in math_errhandling.
    return (l == 0) ? 1 : floor(log10(abs(l))) + 1;
}

// --------------------

//! @link <stackoverflow.com/questions/1068849/how-do-i-determine-the-number-of-digits-of-an-integer-in-c#answer-1068937>
int int_num_recurse_digitsl(long l)
{
    if (l < 0) {
        return int_num_recurse_digitsl(l == LONG_MIN ? LONG_MAX : -l);
    }

    if (l < 10) {
        return 1;
    }

    return int_num_recurse_digitsl(l / 10) + 1;
}


// --------------------

//! @link <stackoverflow.com/questions/1068849/how-do-i-determine-the-number-of-digits-of-an-integer-in-c#answer-1068937>
int int_num_iter_placesl(long n) {
    int r = 1;

    if (n < 0) n = (n == LONG_MIN) ? LONG_MAX : -n;

    while (n > 9) {
        n /= 10;
        ++r;
    }

    return r;
}

// --------------------

//! @link <stackoverflow.com/questions/1068849/how-do-i-determine-the-number-of-digits-of-an-integer-in-c#answer-1068937>
int int_num_digitsl(long l)
{
    if (l < 0) {
        return int_num_digitsl(l == LONG_MIN ? LONG_MAX : -l);
    }

    if (l < 10) {
        return 1;
    }

    return int_num_digitsl(l / 10) + 1;
}

// --------------------

void time_h_scratch(void)
{
    time_t now = time(NULL);
    printf("(ctime) %s\n", ctime(&now));

    printf("-----\n\n");

    struct tm *t = localtime(&now);
    time_h_tm_dump(t);

    char buffer[BUFSIZ] = {0};
    snprintf(buffer, BUFSIZ, "%ld", t->tm_gmtoff);

    printf("\n\"%s\" : %02zu : <log> %f\n", buffer, strlen(buffer), num_digitsl(t->tm_gmtoff));
    printf("<truc log> %f\n", trunc(num_digitsl(t->tm_gmtoff)));
    printf("<int cast log> %d\n", (int) num_digitsl(t->tm_gmtoff));
    printf("<int cast truc log> %d\n", (int) trunc(num_digitsl(t->tm_gmtoff)));
    printf("<int_num_recurse_digitsl> %d\n", int_num_recurse_digitsl(t->tm_gmtoff));
    printf("<int_num_digitsl> %d\n", int_num_digitsl(t->tm_gmtoff));
    printf("<int_num_iter_placesl> %d\n", int_num_iter_placesl(t->tm_gmtoff));
    //printf("<floor log> %f\n", floor(num_digitsl(t->tm_gmtoff)));
    //printf("<ceil log> %f\n", ceil(num_digitsl(t->tm_gmtoff)));
    //printf("<round log> %f\n", round(num_digitsl(t->tm_gmtoff)));

    printf("\n | [(epoc).num_days]: %ld | \n\n", (now / TIMELY_DAY_SECONDS_PER));

    printf("\n-----\n\n");

    t = gmtime(&now);
    time_h_tm_dump(t);

    memset(buffer, 0, BUFSIZ);
    snprintf(buffer, BUFSIZ, "%ld", t->tm_gmtoff);

    printf("\n\"%s\" : %02zu : <log> %f\n", buffer, strlen(buffer), num_digitsl(t->tm_gmtoff));
    printf("<truc log> %f\n", trunc(num_digitsl(t->tm_gmtoff)));
    printf("<int cast log> %d\n", (int) num_digitsl(t->tm_gmtoff));
    printf("<int cast truc log> %d\n", (int) trunc(num_digitsl(t->tm_gmtoff)));
    printf("<int_num_recurse_digitsl> %d\n", int_num_recurse_digitsl(t->tm_gmtoff));
    printf("<int_num_digitsl> %d\n", int_num_digitsl(t->tm_gmtoff));
    printf("<int_num_iter_placesl> %d\n", int_num_iter_placesl(t->tm_gmtoff));
    //printf("<floor log> %f\n", floor(num_digitsl(t->tm_gmtoff)));
    //printf("<ceil log> %f\n", ceil(num_digitsl(t->tm_gmtoff)));
    //printf("<round log> %f\n", round(num_digitsl(t->tm_gmtoff)));

    printf("\n | [(epoc).num_days]: %ld | \n\n", (now / TIMELY_DAY_SECONDS_PER));

    printf("\n");

    // struct timely_epoc timely_epoc_ctor(time_t timer);
    printf("\n | [(ctor).num_days]: %ld | \n\n", (timely_epoc_ctor(now)).num_days);
}

// --------------------

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
