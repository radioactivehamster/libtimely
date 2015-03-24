#ifndef TIMELY_MONTH_CTOR_H
#define TIMELY_MONTH_CTOR_H

#include <stdint.h>
#include "timely.h"
#include "timely/types/timely_day.h"

struct timely_day timely_month_ctor(struct timely_day *restrict prev_day);

#endif  /* TIMELY_MONTH_CTOR_H */
