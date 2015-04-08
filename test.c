#include <assert.h>
#include <locale.h>
#include <limits.h>
#include <stdio.h>  //! BUFSIZ
#include <string.h>
#include <time.h>

#include "timely/day_of_year.h"
#include "timely/iso8601_utc_timestamp.h"
#include "timely/moment.h"
#include "timely/num_days_in_month.h"
#include "timely/rfc1123_timestamp.h"
#include "timely/set_default_locale.h"
#include "timely/tm_ctor.h"

int timely_moment_test(char dest[], time_t timer);

struct tm *timely_timer_to_tm(struct tm *dest, const time_t *timer);

#ifndef TIME_UTC
    #define TIME_UTC 1
#endif

int main(void)
{
    // Set our locale to enable localized numeric formatting.
    timely_set_default_locale();

    time_t t = time(NULL);
    assert(t != (time_t)(-1));

    tzset();

    printf("[extern int  daylight]: %d\n"
           "[extern long timezone]: %ld\n",
           daylight, timezone);
    //! <http://www.informit.com/guides/content.aspx?g=cplusplus&seqNum=331>
    printf("[extern char *tzname[2]]: <local standard time> %s, "
           "<local alternate time> %s\n", tzname[0], tzname[1]);
    printf("\n\n");
    /**
     * ```sh
     * $ > [TIME_UTC]: 1
     * $ > [extern int  daylight]: 1
     * $ > [extern long timezone]: 18000
     * $ > [extern char *tzname[2]]: <local standard time> EST, <local alternate time> EDT
     * ```
     */

    // ------------------------------------------------------------

    char dest[ISO8601_UTC_SIZE] = {0};
    iso8601_utc_timestamp(dest, &t);

    char dest2[ISO8601_UTC_SIZE] = {0};
    stdlib_iso8601_utc_timestamp(dest2, &t);

    printf("## iso8601_timestamp\n\n%s\n%s\n\n", dest, dest2);
    printf("\n===================\n");

    struct tm timer_tm;
    timely_tm_ctor(&timer_tm, &t);

    printf("[timely]\n");
    printf("[tm_sec]: %d\n", timer_tm.tm_sec);
    printf("[tm_min]: %d\n", timer_tm.tm_min);
    printf("[tm_hour]: %d\n", timer_tm.tm_hour);
    printf("[tm_mday]: %d\n", timer_tm.tm_mday);
    printf("[tm_mon]: %d\n", timer_tm.tm_mon);
    printf("[tm_year]: %d\n", timer_tm.tm_year);
    printf("[tm_wday]: %d\n", timer_tm.tm_wday);
    printf("[tm_yday]: %d\n", timer_tm.tm_yday);
    printf("[tm_isdst]: %d\n", timer_tm.tm_isdst);
}
