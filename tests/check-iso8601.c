#include <assert.h>
#include <stdlib.h>
#include <time.h>

#include <check.h>
#include "timely.h"

#define ISO8601_MAX 30
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

START_TEST(test_iso8601_strcmp)
{
    time_t t = time(NULL);
    assert(t != (time_t)(-1));
    char timely_buf[ISO8601_MAX] = {0};
    char gmtime_buf[ISO8601_MAX] = {0};

    timely_iso8601(timely_buf, t);
    timely_iso8601(gmtime_buf, t);

    ck_assert_str_eq(timely_buf, gmtime_buf);
}
END_TEST

Suite *iso8601_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("ISO8601");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_iso8601_strcmp);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = iso8601_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

/*
## Example Results

```pass
Running suite(s): ISO8601
100%: Checks: 1, Failures: 0, Errors: 0
```

---

```fail
Running suite(s): ISO8601
0%: Checks: 1, Failures: 1, Errors: 0
tests/check-iso8601.c:89:F:Core:test_iso8601_strcmp:0: Assertion 'timely_buf==gmtime_buf' failed: timely_buf=="Fri, 03 Apr 2015 23:49:19 GMT", gmtime_buf=="hi"
```
*/
