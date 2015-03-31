#include <assert.h>
#include <locale.h>
#include "timely.h"
#include "_utils.h"

// void time_h_tm_dump(struct tm *restrict t);
// void time_h_scratch(void);
// void timely_day_scratch(void);
// void timely_epoc_seconds_days_months(void);


//!
//! @todo Remove cruft and break down the tests into smaller files for epic(ish)
//!       focus and then align the RFC1123 timestamp to mirror the Timely(!!!!!)
//!       test calls. DO IT ME!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!
//!
int main(void)
{
    timely_locale_set_default();
    _printnl();

    _timely_epoc_seconds_days_months();

    printf("\n-----\n");
    _printnnl(5);
    printf("\n-----\n");
}

// --------------------
