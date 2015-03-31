#include <limits.h>

//! @link <stackoverflow.com/questions/1068849/how-do-i-determine-the-number-of-digits-of-an-integer-in-c#answer-1068937>
int int_num_recurse_digitsl(long l)
{
    if (l < 0) {
        return int_num_recurse_digitsl(l == LONG_MIN ? LONG_MAX : -l);
    }

    if (l < 10) {
        return 1;
    }

    return int_num_recurse_digitsl(l / 10) + 1;
}
