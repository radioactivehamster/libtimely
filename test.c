#include <assert.h>
#include <locale.h>
#include "timely.h"

void time_h_tm_dump(struct tm *restrict t);
void time_h_scratch(void);
void timely_day_scratch(void);
void timely_epoc_seconds_days_months(void);

void timely_locale_set_default(void)
{
    const char *lc = setlocale(LC_ALL, NULL);

    //!< Random heads up msg for debug yo...
    printf("> [INFO] Initial Locale: %s\n", lc);

    setlocale(LC_ALL, "");
}

void _printnl(void)
{
    printf("\n");
}

// --------------------

//!
//! @todo Remove cruft and break down the tests into smaller files for epic(ish)
//!       focus and then align the RFC1123 timestamp to mirror the Timely(!!!!!)
//!       test calls. DO IT ME!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!
//!
int main(void)
{
    timely_locale_set_default();
    _printnl();

    timely_epoc_seconds_days_months();
}

// --------------------

//!< `#define TIMELY_MONTH_JANUARY 0`
int _num_days_in_month(uint16_t year, uint8_t month)
{
    printf("(YEAR) %s\n", timely_year_is_leap(year) == true ? "<leap-year>" : "<common-year>");

    if (month != TIMELY_MONTH_FEBRUARY || timely_year_is_leap(year) == false) {
        return ((uint8_t[TIMELY_MONTHS_IN_YEAR]) {
            31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
        })[month];
    }

    return 29; //!< February 29; leap day.
}

void timely_epoc_seconds_days_months(void)
{
    static const char *const mon_names[TIMELY_MONTHS_IN_YEAR] = {
        "January", "February", "March", "April", "May", "June", "July",
        "August", "September", "October", "November", "December"
    };

    time_t now = time(NULL);
    struct tm gmt;
    struct timely_epoc epoc = timely_epoc_ctor(now);

    time_t t = epoc.time; //-/ 0;
    gmt = *gmtime(&t);
    int m = 0;
    int ndays;
    int tdays = t / TIMELY_DAY_SECONDS_PER;

    // -----

    enum { RFC1123_SIZE = 30 };
    char tsbuf[RFC1123_SIZE] = {0};
    size_t tslen; //!< `size_t timely_rfc1123_timestamp(char *dest, rsize_t dmax, const time_t *restrict timer);`

    //printf("<time>: %ld\n", t);

    ndays = _num_days_in_month(1970, m);
    //!/ ndays = _num_days_in_month(gmt.tm_year, gmt.tm_mon);
    printf("<time:tdays:month:days_in>  %'ld : %'d : %-8s : %d\n", t, tdays, mon_names[m], ndays);
    //!/ printf("<time:tdays:month:days_in>  %'ld : %'d : %-8s : %d\n", t, tdays, mon_names[gmt.tm_mon], ndays);
    tslen = timely_rfc1123_timestamp(tsbuf, RFC1123_SIZE, &t);
    printf("<rfc1123:timestamp>         %s\n", tsbuf);

    printf("\n-----\n");
    _printnl();

    t     -= (TIMELY_DAY_SECONDS_PER / ndays);
    m     += 1;
    tdays  = (t / TIMELY_DAY_SECONDS_PER);
    gmt    = *gmtime(&t);

    memset(tsbuf, 0, RFC1123_SIZE);

    //-/ =====

    ndays = _num_days_in_month(1970, m);
    printf("<time:tdays:month:days_in>  %'ld : %'d : %-8s : %d\n", t, tdays, mon_names[m], ndays);
    tslen = timely_rfc1123_timestamp(tsbuf, RFC1123_SIZE, &t);
    printf("<rfc1123:timestamp>         %s\n", tsbuf);

    printf("\n-----\n");
    _printnl();

    t     -= (TIMELY_DAY_SECONDS_PER / ndays);
    m     += 1;
    tdays  = (t / TIMELY_DAY_SECONDS_PER);
    gmt    = *gmtime(&t);

    memset(tsbuf, 0, RFC1123_SIZE);

    //-/ =====

    ndays = _num_days_in_month(1970, m);
    printf("<time:tdays:month:days_in>  %'ld : %'d : %-8s : %d\n", t, tdays, mon_names[m], ndays);
    tslen = timely_rfc1123_timestamp(tsbuf, RFC1123_SIZE, &t);
    printf("<rfc1123:timestamp>         %s\n", tsbuf);

    printf("\n-----\n");
    _printnl();

    t     -= (TIMELY_DAY_SECONDS_PER / ndays);
    m     += 1;
    tdays  = (t / TIMELY_DAY_SECONDS_PER);
    gmt    = *gmtime(&t);

    memset(tsbuf, 0, RFC1123_SIZE);

    //-/ =====

    //printf("<time>:     %ld\n", epoc.time);
    //for (time_t t = epoc.time; t; --t) {
    //uint16_t days = epoc.num_days;
    //printf("<time>:     %ld\n", t / );
    //}

    //printf("<time>:     %ld\n", epoc.time);
    //printf("<num_days>: %ld\n", epoc.num_days);

    //!< `bool timely_year_is_leap(uint16_t year);`
    //int ndays = _num_days_in_month(1970, TIMELY_MONTH_JANUARY);
    //printf("<month:days_in>: %d\n", ndays);
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
