#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <check.h>
#include "../include/timely.h"
#include "./include/stdlib_iso8601_utc_timestamp.h"

// ------------------------------------------------------------

START_TEST(test_iso8601_utc_timestamp)
{
    time_t t = time(NULL);
    assert(t != (time_t)(-1));

    char stdlib_buf[ISO8601_UTC_SIZE] = {0};
    char timely_buf[ISO8601_UTC_SIZE] = {0};

    stdlib_iso8601_utc_timestamp(timely_buf, &t);
    timely_iso8601_utc_timestamp(stdlib_buf, &t);

    ck_assert_str_eq(stdlib_buf, timely_buf);
}
END_TEST

// ------------------------------------------------------------

START_TEST(test_tm_ctor)
{
    time_t t = time(NULL);
    assert(t != (time_t)(-1));

    struct tm *stdlib = gmtime(&t);
    struct tm *timely = gmtime(&t);

    ck_assert_int_eq(stdlib->tm_sec, timely->tm_sec);
    ck_assert_int_eq(stdlib->tm_min, timely->tm_min);
    ck_assert_int_eq(stdlib->tm_hour, timely->tm_hour);
    ck_assert_int_eq(stdlib->tm_mday, timely->tm_mday);
    ck_assert_int_eq(stdlib->tm_mon, timely->tm_mon);
    ck_assert_int_eq(stdlib->tm_year, timely->tm_year);
    ck_assert_int_eq(stdlib->tm_wday, timely->tm_wday);
    ck_assert_int_eq(stdlib->tm_yday, timely->tm_yday);

    //! @todo Look into how this will be handled or if it should be optional
    ck_assert_int_eq(stdlib->tm_isdst, timely->tm_isdst);
}
END_TEST

// ------------------------------------------------------------

Suite *libtimely_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("libtimely");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_iso8601_utc_timestamp);
    tcase_add_test(tc_core, test_tm_ctor);
    suite_add_tcase(s, tc_core);

    return s;
}

// ------------------------------------------------------------

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = libtimely_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
