/*
 * $Header:   P:/marille/clinicum/include/rev/oratypes.h_v   1.1   06 Nov 1996 18:40:04   MARTIN  $ 
 */

/* Copyright (c) Oracle Corporation 1986, 1992.  All Rights Reserved. */
/*
   NAME
     oratypes.h - System-dependent external definitions of Oracle types
                  (VMS version).
   DESCRIPTION
     This header file defines C types used by Oracle demonstration
     code, and code samples in documentation (such as the _Programmer's
     Guide to the ORACLE Call Interfaces_).

   NOTES
     Porters must modify oratypes.h to reflect the reality of their ports.

     The symbol 'VMSC2X' should be defined from the command line when
     using one of the older 2.x version VMS C compilers.
   MODIFIED   (MM/DD/YY)
    ccongdon   10/21/92 -  Creation 
*/

#ifndef ORASTDDEF
# include <stddef.h>
# define ORASTDDEF
#endif

#ifndef ORALIMITS
# include <limits.h>
# define ORALIMITS
#endif

#ifndef  SX_ORACLE
#define  SX_ORACLE
#define  SX
#define  ORATYPES

#ifndef TRUE
# define TRUE  1
# define FALSE 0
#endif

# ifndef signed
#  define signed
# endif /* signed */

typedef          int eword;   /* use where sign not important */
typedef unsigned int uword;   /* use where unsigned important */
typedef   signed int sword;   /* use where   signed important */

#define  EWORDMAXVAL  ((eword) INT_MAX)
#define  EWORDMINVAL  ((eword)       0)
#define  UWORDMAXVAL  ((uword)UINT_MAX)
#define  UWORDMINVAL  ((uword)       0)
#define  SWORDMAXVAL  ((sword) INT_MAX)
#define  SWORDMINVAL  ((sword) INT_MIN)
#define  MINEWORDMAXVAL  ((eword)  32767)
#define  MAXEWORDMINVAL  ((eword)      0)
#define  MINUWORDMAXVAL  ((uword)  65535)
#define  MAXUWORDMINVAL  ((uword)      0)
#define  MINSWORDMAXVAL  ((sword)  32767)
#define  MAXSWORDMINVAL  ((sword) -32767)
 
typedef          char  eb1;   /* use where sign not important */
typedef unsigned char  ub1;   /* use where unsigned important */
typedef   signed char  sb1;   /* use where   signed important */

#define EB1MAXVAL ((eb1)SCHAR_MAX)
#define EB1MINVAL ((eb1)        0)
#ifdef VMSC2X
# ifndef lint
#  define UB1MAXVAL (UCHAR_MAX)
# endif
#endif

#ifndef UB1MAXVAL
# define UB1MAXVAL ((ub1)UCHAR_MAX)
#endif
#define UB1MINVAL ((ub1)        0)
#define SB1MAXVAL ((sb1)SCHAR_MAX)
#define SB1MINVAL ((sb1)SCHAR_MIN)
#define MINEB1MAXVAL ((eb1)  127)
#define MAXEB1MINVAL ((eb1)    0)
#define MINUB1MAXVAL ((ub1)  255)
#define MAXUB1MINVAL ((ub1)    0)
#define MINSB1MAXVAL ((sb1)  127)
#define MAXSB1MINVAL ((sb1) -127)

#define UB1BITS          CHAR_BIT
#define UB1MASK              0xff

typedef  unsigned char text;

typedef          short    eb2;   /* use where sign not important */
typedef unsigned short    ub2;   /* use where unsigned important */
typedef   signed short    sb2;   /* use where   signed important */

#define EB2MAXVAL ((eb2) SHRT_MAX)
#define EB2MINVAL ((eb2)        0)
#define UB2MAXVAL ((ub2)USHRT_MAX)
#define UB2MINVAL ((ub2)        0)
#define SB2MAXVAL ((sb2) SHRT_MAX)
#define SB2MINVAL ((sb2) SHRT_MIN)
#define MINEB2MAXVAL ((eb2) 32767)
#define MAXEB2MINVAL ((eb2)     0)
#define MINUB2MAXVAL ((ub2) 65535)
#define MAXUB2MINVAL ((ub2)     0)
#define MINSB2MAXVAL ((sb2) 32767)
#define MAXSB2MINVAL ((sb2)-32767)
 
typedef          long  eb4;   /* use where sign not important */
typedef unsigned long  ub4;   /* use where unsigned important */
typedef   signed long  sb4;   /* use where   signed important */

#define EB4MAXVAL ((eb4) LONG_MAX)
#define EB4MINVAL ((eb4)        0)
#define UB4MAXVAL ((ub4)ULONG_MAX)
#define UB4MINVAL ((ub4)        0)
#define SB4MAXVAL ((sb4) LONG_MAX)
#define SB4MINVAL ((sb4) LONG_MIN)
#define MINEB4MAXVAL ((eb4) 2147483647)
#define MAXEB4MINVAL ((eb4)          0)
#define MINUB4MAXVAL ((ub4) 4294967295)
#define MAXUB4MINVAL ((ub4)          0)
#define MINSB4MAXVAL ((sb4) 2147483647)
#define MAXSB4MINVAL ((sb4)-2147483647)

# define CONST const

#ifndef VMSC2X
# define CONST const
#else
# define CONST
#endif

#ifdef VMSC2X
# define dvoid char
#else
# define dvoid void
#endif

typedef void (*lgenfp_t)(/*_ void _*/);

#define boolean int

#define SIZE_TMAXVAL UB4MAXVAL
#define MINSIZE_TMAXVAL (size_t)65535

#endif /* SX_ORACLE */

