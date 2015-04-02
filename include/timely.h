#ifndef TIMELY_H
#define TIMELY_H

//#pragma once

#include <assert.h>
#include <inttypes.h>
#include <iso646.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>  // `EXIT_{SUCCESS/FAILURE}`
#include <string.h>
#include <time.h>

// Time base values for `timespec_get` as per the C11 spec
#ifndef TIME_UTC
    #define TIME_UTC (1)
#endif

// Temporary monkeypatchs...

#ifndef _ERRNO_T
    #define _ERRNO_T
    typedef int errno_t;
#endif

#ifndef _RSIZE_T
    #define _RSIZE_T
    typedef size_t rsize_t;
#endif

#ifndef RSIZE_MAX
    #define RSIZE_MAX (SIZE_MAX >> 1)
#endif

//./ --------------------

enum { TIMELY_DAYS_IN_WEEK = 7, TIMELY_MONTHS_IN_YEAR = 12 };
       //-/ , TIMELY_EPOC_YEAR = 1970 };

#define TIMELY_YEAR_EPOC  1970

#define TIMELY_EPOC_YEAR          1970
#define TIMELY_EPOC_DAY_OF_MONTH  1
#define TIMELY_EPOC_DAY_OF_YEAR   1

//-/ `tm_wday` - day of week (Sunday = 0)
//!
//! @deprecated Use the `TIMELY_DAY_x` macros instead.
//!
enum { TIMELY_DAY_OF_WEEK_SUNDAY, TIMELY_DAY_OF_WEEK_MONDAY,
       TIMELY_DAY_OF_WEEK_TUESDAY, TIMELY_DAY_OF_WEEK_WEDNESDAY,
       TIMELY_DAY_OF_WEEK_THURSDAY, TIMELY_DAY_OF_WEEK_FRIDAY,
       TIMELY_DAY_OF_WEEK_SATURDAY };

//-/ enum { SECONDS_PER_DAY = 86400 };

#define TIMELY_DAY_SECONDS_PER  86400

#define TIMELY_DAY_SUNDAY       0
#define TIMELY_DAY_MONDAY       1
#define TIMELY_DAY_TUESDAY      2
#define TIMELY_DAY_WEDNESDAY    3
#define TIMELY_DAY_THURSDAY     4
#define TIMELY_DAY_FRIDAY       5
#define TIMELY_DAY_SATURDAY     6

#define TIMELY_MONTH_JANUARY    0
#define TIMELY_MONTH_FEBRUARY   1
#define TIMELY_MONTH_MARCH      2
#define TIMELY_MONTH_APRIL      3
#define TIMELY_MONTH_MAY        4
#define TIMELY_MONTH_JUNE       5
#define TIMELY_MONTH_JULY       6
#define TIMELY_MONTH_AUGUST     7
#define TIMELY_MONTH_SEPTEMBER  8
#define TIMELY_MONTH_OCTOBER    9
#define TIMELY_MONTH_NOVEMBER   10
#define TIMELY_MONTH_DECEMBER   11

//./ --------------------

/*
# This is the POSIX locale definition for
# the LC_TIME category.
#
# Abbreviated weekday names (%a)
abday      "<S><u><n>";"<M><o><n>";"<T><u><e>";"<W><e><d>";\
           "<T><h><u>";"<F><r><i>";"<S><a><t>"
*/
static const char *const day_abbr_names[TIMELY_DAYS_IN_WEEK] = {
    "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
};

static const char *const day_names[TIMELY_DAYS_IN_WEEK] = {
    "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
};  //-/ "-unknown-" <-- Listed in C11 draft example but not part of spec.

//./ --------------------

static const uint8_t month_days[TIMELY_MONTHS_IN_YEAR] = {
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

static const char *const month_abbr_names[TIMELY_MONTHS_IN_YEAR] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

static const char *const month_names[TIMELY_MONTHS_IN_YEAR] = {
    "January", "February", "March", "April", "May", "June", "July",
    "August", "September", "October", "November", "December"
};

//-/ --------------------

#include "timely/timely-posix.h"

//!
//! POSIX Locale `DAY_x` mapping macros.
//!
#define TIMELY_INC_DAY_0 DAY_1
#define TIMELY_INC_DAY_1 DAY_2
#define TIMELY_INC_DAY_2 DAY_3
#define TIMELY_INC_DAY_3 DAY_4
#define TIMELY_INC_DAY_4 DAY_5
#define TIMELY_INC_DAY_5 DAY_6
#define TIMELY_INC_DAY_6 DAY_7

//-/ --------------------

#define TIMELY_INCREMENTED_DAY_NAME(d)   TIMELY_INC_DAY_ ## d
#define TIMELY_DAY_NAME(d)               TIMELY_INCREMENTED_DAY_NAME(d)

//static inline void timely_invoke_macro_day_0(void)
//{
    //TIMELY_DAY_NAME(0)
//}

//static inline void timely_day_name_var(uint8_t d)
//{
    //switch (d) {
    //    case 0:
    //        timely_invoke_macro_day_0();
    //        break;
    //};
//}

static inline rsize_t timely_day_name_var(char *dest, uint8_t d, rsize_t dmax)
{
    const char *const day_names[TIMELY_DAYS_IN_WEEK] = {
        "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
    };  //-/ "-unknown-" <-- Listed in C11 draft example but not part of spec.

    if (d > (TIMELY_DAYS_IN_WEEK - 1)) {
        //!< @todo Implement constraint handler.
        return 0;
    }

    const char *day_name = day_names[d];

    //!< @todo Add the `strnlen_s()` lib and use it instead of `strlen()`.
    rsize_t len = strlen(day_name);

    //! Remember to add one for the NUL byte.
    rsize_t req_bufsiz = len + 1;

    if (!dest) {
        return req_bufsiz;
    }

    if (dmax < req_bufsiz) {
        //!< @todo Implement constraint handler.
        fprintf(stderr, "\n[error]: Provided `dmax` is less than the required "
            "buffer in: `%s()`.\n\n", __func__);
        return 0;
    }

    if (strncpy(dest, day_name, len) == NULL) {
        return 0;
    }

    return len;
}

//-/ --------------------

//!
//! POSIX Locale `MON_x` mapping macros.
//! P.S. Wrapping the macro values in parens is bad mojo in this case due to chaining.
//!
#define TIMELY_INC_MON_0  MON_1
#define TIMELY_INC_MON_1  MON_2
#define TIMELY_INC_MON_2  MON_3
#define TIMELY_INC_MON_3  MON_4
#define TIMELY_INC_MON_4  MON_5
#define TIMELY_INC_MON_5  MON_6
#define TIMELY_INC_MON_6  MON_7
#define TIMELY_INC_MON_7  MON_8
#define TIMELY_INC_MON_8  MON_9
#define TIMELY_INC_MON_9  MON_10
#define TIMELY_INC_MON_10 MON_11
#define TIMELY_INC_MON_11 MON_12

//-/ --------------------

#define TIMELY_INCREMENTED_MONTH_NAME(m) TIMELY_INC_MON_ ## m
#define TIMELY_MONTH_NAME(m)             TIMELY_INCREMENTED_MONTH_NAME(m)

//-/ --------------------

// ## Year
#include "timely/year/timely_year_definitions.h"

// ## Type
#include "timely/types/timely_day.h"
#include "timely/types/timely_month.h"
#include "timely/types/timely_year.h"
#include "timely/types/timely_epoc.h"
#include "timely/types/timely_moment.h"

#include "timely/epoc/timely_epoc_ctor.h"
#include "timely/year/timely_year_is_leap.h"
#include "timely/day/timely_day_epoc_ctor.h"
#include "timely/month/timely_month_ctor.h"
#include "timely/month/timely_month_num_days.h"

// ## Locale
#include "timely/locale/timely_locale_set_default.h"

// ## RFC1123
#include "timely/rfc1123/timely_rfc1123_timestamp.h"

//-/ --------------------

#endif  /* TIMELY_H */
