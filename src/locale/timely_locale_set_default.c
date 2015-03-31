#include <locale.h>
#include <stdio.h>

void timely_locale_set_default(void)
{
    const char *lc = setlocale(LC_ALL, NULL);

    //!< Random heads up msg for debug yo...
    printf("> [INFO] Initial Locale: %s\n", lc);

    setlocale(LC_ALL, "");
}
