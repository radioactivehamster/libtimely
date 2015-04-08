#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <check.h>
#include "../include/timely.h"
#include "./include/stdlib_iso8601_utc_timestamp.h"

// ------------------------------------------------------------

START_TEST(test_iso8601_utc_strcmp)
{
    time_t t = time(NULL);
    assert(t != (time_t)(-1));

    char timely_buf[ISO8601_UTC_SIZE] = {0};
    char stdlib_buf[ISO8601_UTC_SIZE] = {0};

    stdlib_iso8601_utc_timestamp(timely_buf, &t);
    timely_iso8601_utc_timestamp(stdlib_buf, &t);

    ck_assert_str_eq(timely_buf, stdlib_buf);
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
