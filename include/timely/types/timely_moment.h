#ifndef TIMELY_MOMENT_H
#define TIMELY_MOMENT_H

#include <stdint.h>
#include <time.h>

//struct tmly_moment_lt {
//struct TmlyMoment {
//struct TimelyMoment {
struct timely_moment {
    uint16_t year;
    uint8_t month;
    uint8_t day;
    time_t unixtime;
};

#endif /* TIMELY_MOMENT_H */
