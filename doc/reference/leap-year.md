# Leap Year

### Algorithm

The following pseudocode determines whether a year is a leap year or a common
year in the Gregorian calendar (and in the proleptic Gregorian calendar
before 1582). The year variable being tested is the integer representing the
number of the year in the Gregorian calendar, and the tests are arranged to
dispatch the most common cases first. Care should be taken in translating
mathematical integer divisibility into specific programming languages.

    if (year is not divisible by 4) then (it is a common year)
    else
    if (year is not divisible by 100) then (it is a leap year)
    else
    if (year is not divisible by 400) then (it is a common year)
    else (it is a leap year)

* http://en.wikipedia.org/wiki/Leap_year#Algorithm

----------------------------------------------------------------------------

### Leap Day

February 29 is a date that usually occurs every four years, and is called
leap day. This day is added to the calendar in leap years as a corrective
measure, because the Earth does not orbit around the sun in precisely 365
days.

* http://en.wikipedia.org/wiki/Leap_year#Leap_day
