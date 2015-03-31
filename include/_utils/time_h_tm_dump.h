#include <stdio.h>
#include <time.h>

void time_h_tm_dump(struct tm *restrict t)
{
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
