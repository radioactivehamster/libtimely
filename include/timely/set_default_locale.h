#ifndef TIMELY_SET_DEFAULT_LOCALE_H
#define TIMELY_SET_DEFAULT_LOCALE_H

#include <locale.h>

static inline void timely_set_default_locale(void)
{
    setlocale(LC_ALL, "");
}

#endif  /* TIMELY_SET_DEFAULT_LOCALE_H */
