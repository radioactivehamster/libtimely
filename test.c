#include <assert.h>
#include <locale.h>
#include "timely.h"

void time_h_tm_dump(struct tm *restrict t);
void time_h_scratch(void);
void timely_day_scratch(void);
void timely_epoc_seconds_days_months(void);
void timely_locale_set_default(void);

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
    size_t tslen;

    //printf("<time>: %ld\n", t);

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
}
