#ifndef TIMELY_MOMENT_H
#define TIMELY_MOMENT_H

#include <stdbool.h>
#include <stdint.h>
#include <time.h>

//struct tmly_moment_lt {
//struct TmlyMoment {
//struct TimelyMoment {
struct timely_moment {
    uint16_t year;
    uint8_t month;
    uint8_t day;
    /** @todo Add `.seconds` into the day property */
    int32_t seconds;
    time_t unix_time;
    bool in_leap_year;
};

#endif /* TIMELY_MOMENT_H */
