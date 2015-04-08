##  4.15 Seconds Since the Epoch

A value that approximates the number of seconds that have elapsed since the Epoch. A Coordinated Universal Time name (specified in terms of seconds (tm_sec), minutes (tm_min), hours (tm_hour), days since January 1 of the year (tm_yday), and calendar year minus 1900 (tm_year)) is related to a time represented as seconds since the Epoch, according to the expression below.

If the year is <1970 or the value is negative, the relationship is undefined. If the year is >=1970 and the value is non-negative, the value is related to a Coordinated Universal Time name according to the C-language expression, where tm_sec, tm_min, tm_hour, tm_yday, and tm_year are all integer types:

    tm_sec + tm_min*60 + tm_hour*3600 + tm_yday*86400 +
        (tm_year-70)*31536000 + ((tm_year-69)/4)*86400 -
        ((tm_year-1)/100)*86400 + ((tm_year+299)/400)*86400

The relationship between the actual time of day and the current value for seconds since the Epoch is unspecified.

How any changes to the value of seconds since the Epoch are made to align to a desired relationship with the current actual time is implementation-defined. As represented in seconds since the Epoch, each and every day shall be accounted for by exactly 86400 seconds.

Note:
    The last three terms of the expression add in a day for each year that follows a leap year starting with the first leap year since the Epoch. The first term adds a day every 4 years starting in 1973, the second subtracts a day back out every 100 years starting in 2001, and the third adds a day back in every 400 years starting in 2001. The divisions in the formula are integer divisions; that is, the remainder is discarded leaving only the integer quotient.

## 8.3 Other Environment Variables

### `TZ`

This variable shall represent timezone information. The contents of the environment variable named TZ shall be used by the ctime(), ctime_r(), localtime(), localtime_r() strftime(), mktime(), functions, and by various utilities, to override the default timezone. The value of TZ has one of the two forms (spaces inserted for clarity):

    :characters

or:

    std offset dst offset, rule

If TZ is of the first format (that is, if the first character is a <colon>), the characters following the <colon> are handled in an implementation-defined manner.

The expanded format (for all TZ s whose value does not have a <colon> as the first character) is as follows:

    stdoffset[dst[offset][,start[/time],end[/time]]]

Where:

    std and dst
        Indicate no less than three, nor more than {TZNAME_MAX}, bytes that are the designation for the standard (std) or the alternative (dst -such as Daylight Savings Time) timezone. Only std is required; if dst is missing, then the alternative time does not apply in this locale.

Each of these fields may occur in either of two formats quoted or unquoted:

In the quoted form, the first character shall be the <less-than-sign> ( '<' ) character and the last character shall be the <greater-than-sign> ( '>' ) character. All characters between these quoting characters shall be alphanumeric characters from the portable character set in the current locale, the <plus-sign> ( '+' ) character, or the minus-sign ( '-' ) character. The std and dst fields in this case shall not include the quoting characters.

In the unquoted form, all characters in these fields shall be alphabetic characters from the portable character set in the current locale.

        The interpretation of these fields is unspecified if either field is less than three bytes (except for the case when dst is missing), more than {TZNAME_MAX} bytes, or if they contain characters other than those specified.
    offset
        Indicates the value added to the local time to arrive at Coordinated Universal Time. The offset has the form:

        hh[:mm[:ss]]

        The minutes (mm) and seconds (ss) are optional. The hour (hh) shall be required and may be a single digit. The offset following std shall be required. If no offset follows dst, the alternative time is assumed to be one hour ahead of standard time. One or more digits may be used; the value is always interpreted as a decimal number. The hour shall be between zero and 24, and the minutes (and seconds)-if present-between zero and 59. The result of using values outside of this range is unspecified. If preceded by a '-', the timezone shall be east of the Prime Meridian; otherwise, it shall be west (which may be indicated by an optional preceding '+' ).
    rule
        Indicates when to change to and back from the alternative time. The rule has the form:

        date[/time],date[/time]

        where the first date describes when the change from standard to alternative time occurs and the second date describes when the change back happens. Each time field describes when, in current local time, the change to the other time is made.

        The format of date is one of the following:

        Jn
            The Julian day n (1 <= n <= 365). Leap days shall not be counted. That is, in all years-including leap years-February 28 is day 59 and March 1 is day 60. It is impossible to refer explicitly to the occasional February 29.
        n
            The zero-based Julian day (0 <= n <= 365). Leap days shall be counted, and it is possible to refer to February 29.
        Mm.n.d
            The d'th day (0 <= d <= 6) of week n of month m of the year (1 <= n <= 5, 1 <= m <= 12, where week 5 means "the last d day in month m" which may occur in either the fourth or the fifth week). Week 1 is the first week in which the d'th day occurs. Day zero is Sunday.

        The time has the same format as offset except that no leading sign ( '-' or '+' ) is allowed. The default, if time is not given, shall be 02:00:00.

---

### Olson format specification

```sh
➜  /var  ls /usr/share/zoneinfo/America/
Adak           Catamarca      Godthab        Louisville     Noronha        Scoresbysund
Anchorage      Cayenne        Goose_Bay      Lower_Princes  North_Dakota   Shiprock
Anguilla       Cayman         Grand_Turk     Maceio         Ojinaga        Sitka
Antigua        Chicago        Grenada        Managua        Panama         St_Barthelemy
Araguaina      Chihuahua      Guadeloupe     Manaus         Pangnirtung    St_Johns
Argentina      Coral_Harbour  Guatemala      Marigot        Paramaribo     St_Kitts
Aruba          Cordoba        Guayaquil      Martinique     Phoenix        St_Lucia
Asuncion       Costa_Rica     Guyana         Matamoros      Port-au-Prince St_Thomas
Atikokan       Creston        Halifax        Mazatlan       Port_of_Spain  St_Vincent
Atka           Cuiaba         Havana         Mendoza        Porto_Acre     Swift_Current
Bahia          Curacao        Hermosillo     Menominee      Porto_Velho    Tegucigalpa
Bahia_Banderas Danmarkshavn   Indiana        Merida         Puerto_Rico    Thule
Barbados       Dawson         Indianapolis   Metlakatla     Rainy_River    Thunder_Bay
Belem          Dawson_Creek   Inuvik         Mexico_City    Rankin_Inlet   Tijuana
Belize         Denver         Iqaluit        Miquelon       Recife         Toronto
Blanc-Sablon   Detroit        Jamaica        Moncton        Regina         Tortola
Boa_Vista      Dominica       Jujuy          Monterrey      Resolute       Vancouver
Bogota         Edmonton       Juneau         Montevideo     Rio_Branco     Virgin
Boise          Eirunepe       Kentucky       Montreal       Rosario        Whitehorse
Buenos_Aires   El_Salvador    Knox_IN        Montserrat     Santa_Isabel   Winnipeg
Cambridge_Bay  Ensenada       Kralendijk     Nassau         Santarem       Yakutat
Campo_Grande   Fort_Wayne     La_Paz         New_York       Santiago       Yellowknife
Cancun         Fortaleza      Lima           Nipigon        Santo_Domingo
Caracas        Glace_Bay      Los_Angeles    Nome           Sao_Paulo
```

```sh
➜  /var  ls /usr/share/zoneinfo/
+VERSION    CET         Eire        GMT0        Japan       Navajo      Turkey      posixrules
Africa      CST6CDT     Etc         Greenwich   Kwajalein   PRC         UCT         zone.tab
America     Canada      Europe      HST         Libya       PST8PDT     US
Antarctica  Chile       Factory     Hongkong    MET         Pacific     UTC
Arctic      Cuba        GB          Iceland     MST         Poland      Universal
Asia        EET         GB-Eire     Indian      MST7MDT     Portugal    W-SU
Atlantic    EST         GMT         Iran        Mexico      ROC         WET
Australia   EST5EDT     GMT+0       Israel      NZ          ROK         Zulu
Brazil      Egypt       GMT-0       Jamaica     NZ-CHAT     Singapore   iso3166.tab
```

<http://www.gnu.org/software/libc/manual/html_node/TZ-Variable.html>
<http://www.ibm.com/developerworks/aix/library/au-aix-posix/index.html>

---

## A.8.2 Internationalization Variables

Utilities conforming to the Shell and Utilities volume of POSIX.1-2008 and written in standard C can access the locale variables by issuing the following call:

setlocale(LC_ALL, "")

If this were omitted, the ISO C standard specifies that the C locale would be used.

## 7. Locale

### LC_TIME C-Language Access

The following constants used to identify items of langinfo data can be used as arguments to the nl_langinfo() function to access information in the LC_TIME category. These constants are defined in the <langinfo.h> header.

ABDAY_x
The abbreviated weekday names (for example, Sun), where x is a number from 1 to 7.

DAY_x
The full weekday names (for example, Sunday), where x is a number from 1 to 7.

ABMON_x
The abbreviated month names (for example, Jan), where x is a number from 1 to 12.

MON_x
The full month names (for example, January), where x is a number from 1 to 12.

D_T_FMT
The appropriate date and time representation.

D_FMT
The appropriate date representation.

T_FMT
The appropriate time representation.

AM_STR
The appropriate ante-meridiem affix.
PM_STR
The appropriate post-meridiem affix.

T_FMT_AMPM
The appropriate time representation in the 12-hour clock format with AM_STR and PM_STR.

ERA
The era description segments, which describe how years are counted and displayed for each era in a locale. Each era description segment shall have the format:
direction:offset:start_date:end_date:era_name:era_format
according to the definitions below. There can be as many era description segments as are necessary to describe the different eras. Era description segments are separated by <semicolon> characters.

direction
Either a '+' or a '-' character. The '+' character shall indicate that years closer to the start_date have lower numbers than those closer to the end_date. The '-' character shall indicate that years closer to the start_date have higher numbers than those closer to the end_date.
offset
The number of the year closest to the start_date in the era.
start_date
A date in the form yyyy/mm/dd, where yyyy, mm, and dd are the year, month, and day numbers respectively of the start of the era. Years prior to AD 1 shall be represented as negative numbers.
end_date
The ending date of the era, in the same format as the start_date, or one of the two special values "-*" or "+*". The value "-*" shall indicate that the ending date is the beginning of time. The value "+*" shall indicate that the ending date is the end of time.
era_name
The era, corresponding to the %EC conversion specification.
era_format
The format of the year in the era, corresponding to the %EY conversion specification.

ERA_D_FMT
The era date format.

ERA_T_FMT
The locale's appropriate alternative time format, corresponding to the %EX conversion specification.

ERA_D_T_FMT
The locale's appropriate alternative date and time format, corresponding to the %Ec conversion specification.

ALT_DIGITS
The alternative symbols for digits, corresponding to the %O conversion specification modifier. The value consists of <semicolon>-separated symbols. The first is the alternative symbol corresponding to zero, the second is the symbol corresponding to one, and so on. Up to 100 alternative symbols may be specified.


### <tzfile.h>

```c
#define SECSPERMIN  60
#define MINSPERHOUR 60
#define HOURSPERDAY 24
#define DAYSPERWEEK 7
#define DAYSPERNYEAR    365
#define DAYSPERLYEAR    366
#define SECSPERHOUR (SECSPERMIN * MINSPERHOUR)
#define SECSPERDAY  ((long) SECSPERHOUR * HOURSPERDAY)
#define MONSPERYEAR 12

#define TM_SUNDAY   0
#define TM_MONDAY   1
#define TM_TUESDAY  2
#define TM_WEDNESDAY    3
#define TM_THURSDAY 4
#define TM_FRIDAY   5
#define TM_SATURDAY 6

#define TM_JANUARY  0
#define TM_FEBRUARY 1
#define TM_MARCH    2
#define TM_APRIL    3
#define TM_MAY      4
#define TM_JUNE     5
#define TM_JULY     6
#define TM_AUGUST   7
#define TM_SEPTEMBER    8
#define TM_OCTOBER  9
#define TM_NOVEMBER 10
#define TM_DECEMBER 11

#define TM_YEAR_BASE    1900

#define EPOCH_YEAR  1970
#define EPOCH_WDAY  TM_THURSDAY

/*
** Accurate only for the past couple of centuries;
** that will probably do.
*/

#define isleap(y) (((y) % 4) == 0 && (((y) % 100) != 0 || ((y) % 400) == 0))

/*
** Since everything in isleap is modulo 400 (or a factor of 400), we know that
**  isleap(y) == isleap(y % 400)
** and so
**  isleap(a + b) == isleap((a + b) % 400)
** or
**  isleap(a + b) == isleap(a % 400 + b % 400)
** This is true even if % means modulo rather than Fortran remainder
** (which is allowed by C89 but not C99).
** We use this to avoid addition overflow problems.
*/
```
