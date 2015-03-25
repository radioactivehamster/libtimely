#include "timely/epoc/timely_epoc_ctor.h"

struct timely_epoc timely_epoc_ctor(time_t timer)
{
    //! time_t num_days; //!< @todo Is `time_t` the right type? <T> should be signed.
    time_t ndays = timer / TIMELY_DAY_SECONDS_PER;

    //!
    //! ```c
    //! while(ndays--) { [break-down tm algorithm...] }
    //! ```
    //!

    return (struct timely_epoc) { .num_days = ndays };
}
