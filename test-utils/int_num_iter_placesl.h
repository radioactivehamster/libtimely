#include <limits.h>

//! @link <stackoverflow.com/questions/1068849/how-do-i-determine-the-number-of-digits-of-an-integer-in-c#answer-1068937>
int int_num_iter_placesl(long n) {
    int r = 1;

    if (n < 0) n = (n == LONG_MIN) ? LONG_MAX : -n;

    while (n > 9) {
        n /= 10;
        ++r;
    }

    return r;
}
