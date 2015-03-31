#include "timely/rfc1123/timely_rfc1123_timestamp.h"
// #pragma once

void _timely_epoc_seconds_days_months(void)
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
