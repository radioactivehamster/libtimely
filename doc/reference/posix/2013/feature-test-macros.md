# POSIX IEEE Std 1003.1, 2013 Edition

## The `_POSIX_C_SOURCE` Feature Test Macro

A POSIX-conforming application shall ensure that the feature test macro `_POSIX_C_SOURCE` is defined before inclusion of any header. When an application includes a header described by POSIX.1-2008, and when this feature test macro is defined to have the value __200809L__:

  1. All symbols required by POSIX.1-2008 to appear when the header is included shall be made visible.

  2. Symbols that are explicitly permitted, but not required, by POSIX.1-2008 to appear in that header (including those in reserved name spaces) may be made visible.

  3. Additional symbols not required or explicitly permitted by POSIX.1-2008 to be in that header shall not be made visible, except when enabled by another feature test macro.

Identifiers in POSIX.1-2008 may only be undefined using the `#undef` directive as described in [Use and Implementation of Interfaces][1] or [The Name Space][2]. These `#undef` directives shall follow all `#include` directives of any header in POSIX.1-2008.

## The `_XOPEN_SOURCE` Feature Test Macro

An XSI-conforming application shall ensure that the feature test macro
`_XOPEN_SOURCE` is defined with the value __700__ before inclusion of any header.
This is needed to enable the functionality described in [The `_POSIX_C_SOURCE`
Feature Test Macro][3] and to ensure that the XSI option is enabled.

Since this volume of POSIX.1-2008 is aligned with the ISO C standard, and
 since all functionality enabled by `_POSIX_C_SOURCE` set equal to __200809L__
is enabled by `_XOPEN_SOURCE` set equal to __700__, there should be no need to
define `_POSIX_C_SOURCE` if `_XOPEN_SOURCE` is so defined. Therefore, if
`_XOPEN_SOURCE` is set equal to __700__ and `_POSIX_C_SOURCE` is set equal to
__200809L__, the behavior is the same as if only `_XOPEN_SOURCE` is defined and
set equal to __700__. However, should `_POSIX_C_SOURCE` be set to a value greater
than __200809L__, the behavior is unspecified.

If `_XOPEN_SOURCE` is defined with the value __700__ and `_POSIX_C_SOURCE` is undefined before inclusion of any header, then the header may define the `_POSIX_C_SOURCE` macro with the value __200809L__

---

### XSI

XSI-conforming implementations shall set the symbolic constant `_XOPEN_UNIX` to a value other than __-1__ and shall set the symbolic constant `_XOPEN_VERSION` to the value __700__.

#### `_XOPEN_VERSION`

Integer value indicating version of the X/Open Portability Guide to which the implementation conforms. The value shall be `700`.

#### `_XOPEN_UNIX`

The implementation supports the XSI option.

[1]: http://pubs.opengroup.org/onlinepubs/9699919799/functions/V2_chap02.html#tag_15_01
[2]: http://pubs.opengroup.org/onlinepubs/9699919799/functions/V2_chap02.html#tag_15_02_02
[3]: http://pubs.opengroup.org/onlinepubs/9699919799/functions/V2_chap02.html#tag_15_02_01_01
