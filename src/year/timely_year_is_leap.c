#include "timely/year/timely_year_is_leap.h"

/**
 * __INT10-C. Do not assume a positive remainder when using the % operator__
 * @see https://www.securecoding.cert.org/confluence/pages/viewpage.action?pageId=6422581
 * @see https://www.securecoding.cert.org/confluence/display/c/INT33-C.+Ensure+that+division+and+remainder+operations+do+not+result+in+divide-by-zero+errors
 * @see https://www.securecoding.cert.org/confluence/display/c/INT09-C.+Ensure+enumeration+constants+map+to+unique+values
 * @see https://www.securecoding.cert.org/confluence/display/c/INT35-C.+Use+correct+integer+precisions
 * @see https://www.securecoding.cert.org/confluence/display/c/INT15-C.+Use+intmax_t+or+uintmax_t+for+formatted+IO+on+programmer-defined+integer+types
 * @see https://www.securecoding.cert.org/confluence/display/c/INT36-C.+Converting+a+pointer+to+integer+or+integer+to+pointer
 */
bool timely_year_is_leap(uint16_t year)
{
    // > `if (year is not divisible by 4) then (it is a common year)`
    if (year % TIMELY_YEAR_APPROX_YEARS_PER_LEAP != 0) return false;

    // > `else if (year is not divisible by 100) then (it is a leap year)`
    if (year % 100 != 0) return true;

    // > `else if (year is not divisible by 400) then (it is a common year)`
    if (year % 400 != 0) return false;

    // > `else (it is a leap year)`
    return true;
}
