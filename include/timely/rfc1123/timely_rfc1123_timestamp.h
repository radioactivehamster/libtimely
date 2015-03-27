#ifndef TIMELY_RFC1123_TIMESTAMP_H
#define TIMELY_RFC1123_TIMESTAMP_H

#include "timely.h"

size_t timely_rfc1123_timestamp(char *dest, rsize_t dmax, const time_t *restrict timer);

#endif  /* TIMELY_RFC1123_TIMESTAMP_H */
