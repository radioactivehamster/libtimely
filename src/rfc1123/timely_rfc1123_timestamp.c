#include "timely/rfc1123/timely_rfc1123_timestamp.h"

size_t timely_rfc1123_timestamp(char *dest, rsize_t dmax, const time_t *restrict timer) //! const time_t *restrict timer
{
    /**
     * @todo Add nullptr check to `timer` that defaults to "now".
     *
     *       ```c
     *       time_t now = time(NULL);
     *
     *       if (now == (time_t)(-1)) {
     *           // Handle error...
     *       }
     *       ```
     *
     * @todo Add nullptr check to `dmax` and possibly invoke a constraint
     *       handler.
     */

    //-/ ----------------------------------------------------------------------

    if (dmax <= 0) {
        return 0;
    }

    //-/ ----------------------------------------------------------------------

    //! > Upon successful completion, time() returns the value of time. Otherwise,
    //! > `(time_t)-1` is returned.
    if (*timer == (time_t)(-1)) {
        return 0;
    }

    //! This maximum number of characters in an RFC1123 date is 29 + 1 for '\0'.
    #define RFC1123_SIZE    30
    #define RFC1123_FORMAT "%a, %d %b %Y %T GMT"

    struct tm *timeptr = gmtime(timer);

    //!
    //! ## CERT - Detect and handle standard library errors
    //! @link <https://www.securecoding.cert.org/confluence/display/c/ERR33-C.+Detect+and+handle+standard+library+errors>
    //!
    //!  Function   | Successful Return           | Error Return
    //! ------------|-----------------------------|--------------
    //!  gmtime()   | Pointer to broken-down time | NULL
    //!  gmtime_s() | Pointer to broken-down time | NULL
    //!  time()     | Calendar time               | (time_t)(-1)
    //!
    if (timeptr == NULL) {
        return 0;
    }

    size_t dlen = strftime(dest, RFC1123_SIZE, RFC1123_FORMAT, timeptr);

    if (dlen <= 0) {
        dest[0] = '\0';
        return 0;
    }

    return dlen;
}
