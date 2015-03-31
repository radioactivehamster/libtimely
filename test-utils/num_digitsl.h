#include <math.h>
#include <stdlib.h>

//! @link <http://stackoverflow.com/questions/3068397/finding-the-length-of-an-integer-in-c#answer-3068420>
double num_digitsl(long l)
{
    //! `signbit()` > Nonzero integral value if arg is negative, ​0​ otherwise.

    //!< @link Errors are reported as specified in math_errhandling.
    return (l == 0) ? 1 : floor(log10(abs(l))) + 1;
}
