#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#include "timely.h"
#include "minunit.h"

#define ISO8601_MAX 21
#define ISO8601_FMT "%04d-%02d-%02dT%02d:%02d:%02dZ"

int timely_iso8601(char dest[], time_t timer)
{
    struct timely_moment moment = {
        .year         = TIMELY_YEAR_EPOC,
        .month        = 1,
        .day          = 1,
        .seconds      = -1,     //!< `int32_t`
        .unix_time    = timer,  //!< `time_t`
        .in_leap_year = false
    };

    uint8_t month_num_days;

    // ------------------------------------------------------------

    do {
        moment.in_leap_year = timely_year_is_leap(moment.year);

        for (moment.month = 1;
            moment.month <= 12 && moment.unix_time >= TIMELY_DAY_SECONDS_PER;
            ++moment.month
        ) {
            month_num_days = timely_month_num_days(moment.year, moment.month);

            for (moment.day = 1;
                 moment.day <= month_num_days && moment.unix_time >= TIMELY_DAY_SECONDS_PER;
                ++moment.day, moment.unix_time -= TIMELY_DAY_SECONDS_PER
            );

            if (moment.unix_time < TIMELY_DAY_SECONDS_PER) {
                break;
            }
        }
    } while (moment.unix_time >= TIMELY_DAY_SECONDS_PER && ++moment.year);

    // ------------------------------------------------------------

    assert(moment.unix_time <= INT_MAX);

    int h = (-1), m = (-1), s = (-1);

    s = moment.unix_time;

    m = (s / 60);
    s -= (m * 60);

    h = (m / 60);
    m -= (h * 60);

    return timely_rfc1123_timestamp(dest, ISO8601_MAX, &timer);
}

// --- |

int gmtime_iso8601(char dest[], time_t timer)
{
    struct tm *t = gmtime(&timer);

    return snprintf(dest, ISO8601_MAX, ISO8601_FMT, (t->tm_year + 1900),
        (t->tm_mon + 1), t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
}

// ---|

MU_TEST(iso8601_strcmp) {
    time_t t = time(NULL);
    assert(t != (time_t)(-1));

    char timely_buf[ISO8601_MAX] = {0};
    char gmtime_buf[ISO8601_MAX] = {0};

    timely_iso8601(timely_buf, t);
    timely_iso8601(gmtime_buf, t);

    mu_check(strcmp(timely_buf, gmtime_buf) == 0);
}

// ---|

MU_TEST_SUITE(iso8601_suite) {
    MU_RUN_TEST(iso8601_strcmp);
}

int main(void)
{
    MU_RUN_SUITE(iso8601_suite);
    MU_REPORT();
}

/*
## Example Results

```pass
.

1 tests, 1 assertions, 0 failures

Finished in 0.00160094 seconds (real) 0.00014400 seconds (proc)
```

---

```fail
F
iso8601_strcmp failed:
    tests/minunit-iso8601.c:89: strcmp(timely_buf, gmtime_buf) == 0


1 tests, 1 assertions, 1 failures

Finished in 0.00075452 seconds (real) 0.00013500 seconds (proc)
```
*/
