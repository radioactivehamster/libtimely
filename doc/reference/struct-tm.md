```c
//!< # C11 Final Draft definitions

/**
 * > The `tm` structure shall contain at least the following members,
 * > in any order. The semantics of the members and their normal ranges
 * > are expressed in the comments. (The range [0, 60] for `tm_sec`
 * > allows for a positive leap second.)
 */
int tm_sec;   // seconds after the minute — [0, 60]
int tm_min;   // minutes after the hour — [0, 59]
int tm_hour;  // hours since midnight — [0, 23]
int tm_mday;  // day of the month — [1, 31]
int tm_mon;   // months since January — [0, 11]
int tm_year;  // years since 1900
int tm_wday;  // days since Sunday — [0, 6]
int tm_yday;  // days since January 1 — [0, 365]
int tm_isdst; // Daylight Saving Time flag
/**
 * > The value of tm_isdst is positive if Daylight Saving Time
 * > is in effect, zero if Daylight Saving Time is not in effect,
 * > and negative if the information is not available.
 */


//!< `struct tm` members
int tm_sec;     /* seconds (0 - 60) */
int tm_min;     /* minutes (0 - 59) */
int tm_hour;    /* hours (0 - 23) */
int tm_mday;    /* day of month (1 - 31) */
int tm_mon;     /* month of year (0 - 11) */
int tm_year;    /* year - 1900 */
int tm_wday;    /* day of week (Sunday = 0) */
int tm_yday;    /* day of year (0 - 365) */
int tm_isdst;   /* is summer time in effect? */
char *tm_zone;  /* [non-standard] abbreviation of timezone name */
long tm_gmtoff; /* [non-standard] offset from UTC in seconds */
```
