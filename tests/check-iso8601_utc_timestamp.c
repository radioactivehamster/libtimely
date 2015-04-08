#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <check.h>
#include "../include/timely.h"

// ------------------------------------------------------------

int stdlib_iso8601_utc_timestamp(char *restrict dest, const time_t *restrict timer)
{
    if (*timer == (time_t)(-1)) return 0;

    struct tm *timeptr = gmtime(timer);

    if (timeptr == NULL) return 0;

    const char *restrict format = "%04d-%02d-%02dT%02d:%02d:%02dZ";
    struct tm *tm_ptr = gmtime(timer);

    return snprintf(dest, ISO8601_UTC_SIZE, format,
        tm_ptr->tm_year + 1900,
        tm_ptr->tm_mon + 1,
        tm_ptr->tm_mday,
        tm_ptr->tm_hour,
        tm_ptr->tm_min,
        tm_ptr->tm_sec);
}

// ------------------------------------------------------------

START_TEST(test_iso8601_utc_strcmp)
{
    time_t t = time(NULL);
    assert(t != (time_t)(-1));

    char timely_buf[ISO8601_UTC_SIZE] = {0};
    char gmtime_buf[ISO8601_UTC_SIZE] = {0};

    stdlib_iso8601_utc_timestamp(timely_buf, &t);
    timely_iso8601_utc_timestamp(gmtime_buf, &t);

    ck_assert_str_eq(timely_buf, gmtime_buf);
}
END_TEST

// ------------------------------------------------------------

Suite *iso8601_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("ISO8601");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_iso8601_utc_strcmp);
    suite_add_tcase(s, tc_core);

    return s;
}

// ------------------------------------------------------------

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
