--------
`#include <stdint.h>`
`INT8_MAX`  127
`INT16_MAX` 32767
`INT32_MAX` 2147483647
`INT64_MAX` 9223372036854775807

--------

```c
/* 7.18.2 Limits of specified-width integer types:
 *   These #defines specify the minimum and maximum limits
 *   of each of the types declared above.
 */


/* 7.18.2.1 Limits of exact-width integer types */
#define INT8_MAX         127
#define INT16_MAX        32767
#define INT32_MAX        2147483647
#define INT64_MAX        9223372036854775807LL

#define INT8_MIN          -128
#define INT16_MIN         -32768
   /*
      Note:  the literal "most negative int" cannot be written in C --
      the rules in the standard (section 6.4.4.1 in C99) will give it
      an unsigned type, so INT32_MIN (and the most negative member of
      any larger signed type) must be written via a constant expression.
   */
#define INT32_MIN        (-INT32_MAX-1)
#define INT64_MIN        (-INT64_MAX-1)

#define UINT8_MAX         255
#define UINT16_MAX        65535
#define UINT32_MAX        4294967295U
#define UINT64_MAX        18446744073709551615ULL

/* 7.18.2.2 Limits of minimum-width integer types */
#define INT_LEAST8_MIN    INT8_MIN
#define INT_LEAST16_MIN   INT16_MIN
#define INT_LEAST32_MIN   INT32_MIN
#define INT_LEAST64_MIN   INT64_MIN

#define INT_LEAST8_MAX    INT8_MAX
#define INT_LEAST16_MAX   INT16_MAX
#define INT_LEAST32_MAX   INT32_MAX
#define INT_LEAST64_MAX   INT64_MAX

#define UINT_LEAST8_MAX   UINT8_MAX
#define UINT_LEAST16_MAX  UINT16_MAX
#define UINT_LEAST32_MAX  UINT32_MAX
#define UINT_LEAST64_MAX  UINT64_MAX

/* 7.18.2.3 Limits of fastest minimum-width integer types */
#define INT_FAST8_MIN     INT8_MIN
#define INT_FAST16_MIN    INT16_MIN
#define INT_FAST32_MIN    INT32_MIN
#define INT_FAST64_MIN    INT64_MIN

#define INT_FAST8_MAX     INT8_MAX
#define INT_FAST16_MAX    INT16_MAX
#define INT_FAST32_MAX    INT32_MAX
#define INT_FAST64_MAX    INT64_MAX

#define UINT_FAST8_MAX    UINT8_MAX
#define UINT_FAST16_MAX   UINT16_MAX
#define UINT_FAST32_MAX   UINT32_MAX
#define UINT_FAST64_MAX   UINT64_MAX

/* 7.18.2.5 Limits of greatest-width integer types */
#define INTMAX_MIN        INT64_MIN
#define INTMAX_MAX        INT64_MAX

#define UINTMAX_MAX       UINT64_MAX

/* 7.18.3 "Other" */
#if __WORDSIZE == 64
#define PTRDIFF_MIN	  INT64_MIN
#define PTRDIFF_MAX	  INT64_MAX
#else
#define PTRDIFF_MIN       INT32_MIN
#define PTRDIFF_MAX       INT32_MAX
#endif

#if __WORDSIZE == 64
#define SIZE_MAX	  UINT64_MAX
#else
#define SIZE_MAX          UINT32_MAX
#endif

#if defined(__STDC_WANT_LIB_EXT1__) && __STDC_WANT_LIB_EXT1__ >= 1
#define RSIZE_MAX         (SIZE_MAX >> 1)
#endif

#define WINT_MIN	  INT32_MIN
#define WINT_MAX	  INT32_MAX

#define SIG_ATOMIC_MIN	  INT32_MIN
#define SIG_ATOMIC_MAX	  INT32_MAX

/* 7.18.4 Macros for integer constants */
#define INT8_C(v)    (v)
#define INT16_C(v)   (v)
#define INT32_C(v)   (v)
#define INT64_C(v)   (v ## LL)

#define UINT8_C(v)   (v ## U)
#define UINT16_C(v)  (v ## U)
#define UINT32_C(v)  (v ## U)
#define UINT64_C(v)  (v ## ULL)

#ifdef __LP64__
#define INTMAX_C(v)  (v ## L)
#define UINTMAX_C(v) (v ## UL)
#else
#define INTMAX_C(v)  (v ## LL)
#define UINTMAX_C(v) (v ## ULL)
#endif

#endif /* _STDINT_H_ */
```

---

```c
#define	CHAR_BIT	8		/* number of bits in a char */
#define	MB_LEN_MAX	6		/* Allow 31 bit UTF2 */

#if !defined(_ANSI_SOURCE) && (!defined(_POSIX_C_SOURCE) || defined(_DARWIN_C_SOURCE))
#define	CLK_TCK		__DARWIN_CLK_TCK	/* ticks per second */
#endif /* !_ANSI_SOURCE && (!_POSIX_C_SOURCE || _DARWIN_C_SOURCE) */

/*
 * According to ANSI (section 2.2.4.2), the values below must be usable by
 * #if preprocessing directives.  Additionally, the expression must have the
 * same type as would an expression that is an object of the corresponding
 * type converted according to the integral promotions.  The subtraction for
 * INT_MIN and LONG_MIN is so the value is not unsigned; 2147483648 is an
 * unsigned int for 32-bit two's complement ANSI compilers (section 3.1.3.2).
 * These numbers work for pcc as well.  The UINT_MAX and ULONG_MAX values
 * are written as hex so that GCC will be quiet about large integer constants.
 */
#define	SCHAR_MAX	127		/* min value for a signed char */
#define	SCHAR_MIN	(-128)		/* max value for a signed char */

#define	UCHAR_MAX	255		/* max value for an unsigned char */
#define	CHAR_MAX	127		/* max value for a char */
#define	CHAR_MIN	(-128)		/* min value for a char */

#define	USHRT_MAX	65535		/* max value for an unsigned short */
#define	SHRT_MAX	32767		/* max value for a short */
#define	SHRT_MIN	(-32768)	/* min value for a short */

#define	UINT_MAX	0xffffffff	/* max value for an unsigned int */
#define	INT_MAX		2147483647	/* max value for an int */
#define	INT_MIN		(-2147483647-1)	/* min value for an int */

#ifdef __LP64__
#define	ULONG_MAX	0xffffffffffffffffUL	/* max unsigned long */
#define	LONG_MAX	0x7fffffffffffffffL	/* max signed long */
#define	LONG_MIN	(-0x7fffffffffffffffL-1) /* min signed long */
#else /* !__LP64__ */
#define	ULONG_MAX	0xffffffffUL	/* max unsigned long */
#define	LONG_MAX	2147483647L	/* max signed long */
#define	LONG_MIN	(-2147483647L-1) /* min signed long */
#endif /* __LP64__ */

#define	ULLONG_MAX	0xffffffffffffffffULL	/* max unsigned long long */
#define	LLONG_MAX	0x7fffffffffffffffLL	/* max signed long long */
#define	LLONG_MIN	(-0x7fffffffffffffffLL-1) /* min signed long long */

#if !defined(_ANSI_SOURCE)
#ifdef __LP64__
#define LONG_BIT	64
#else /* !__LP64__ */
#define LONG_BIT	32
#endif /* __LP64__ */
#define	SSIZE_MAX	LONG_MAX	/* max value for a ssize_t */
#define WORD_BIT	32

#if (!defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE)) || defined(_DARWIN_C_SOURCE)
#define	SIZE_T_MAX	ULONG_MAX	/* max value for a size_t */

#define	UQUAD_MAX	ULLONG_MAX
#define	QUAD_MAX	LLONG_MAX
#define	QUAD_MIN	LLONG_MIN

#endif /* (!_POSIX_C_SOURCE && !_XOPEN_SOURCE) || _DARWIN_C_SOURCE */
#endif /* !_ANSI_SOURCE */

#endif /* _I386_LIMITS_H_ */
```
