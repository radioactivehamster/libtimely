#include "timely/locale/timely_locale_set_default.h"

void timely_locale_set_default(void)
{
    //!< @todo We probably want to storethis statically for later retrieval to restore the env.
    //const char *lc = setlocale(LC_ALL, NULL);

    //!< Random heads up msg for debug yo...
    //printf("> [INFO] Initial Locale: %s\n", lc);

    setlocale(LC_ALL, "");
}
