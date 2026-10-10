 /****************************************************************
 *       Copyright (C) 1988-1997, by Sybase, Inc.                *
 *       All rights reserved. No part of this software may be    *
 *       reproduced in any form or by any means - graphic,       *
 *       electronic or mechanical, including photocopying,       *
 *       recording, taping or information storage and retrieval  *
 *       systems - except with the written permission of         *
 *       Sybase, Inc.                                            *
 ****************************************************************/

#ifndef _SQLCA_H_INCLUDED
#define _SQLCA_H_INCLUDED
#define II_SQLCA

/******************************************************************/
/*  NOTE: _SQL_OS_<operating-system> will be defined by the       */
/*        preprocessor -o option.                                 */
/*      - also use macros that are defined in various environments*/
/*        by various compilers to set the appropriate _SQL_OS     */
/*        macro for those files that are not preprocessed         */
/******************************************************************/

#if defined( __MWERKS__ ) || defined( SC ) || defined( THINK_C )
    #define _SQL_OS_MAC
#endif

/* As the macintosh Windows.h file also defines __WINDOWS__ */

#if defined( __WINDOWS__ ) && !defined( _SQL_OS_MAC )
    #ifdef __386__
        #define _SQL_OS_WIN386
    #else
	#define _SQL_OS_WINDOWS
    #endif
#endif

#ifdef WINNT
    #define _SQL_OS_WINNT
#endif

#if defined( __QNX__ )
    #if defined( __386__ )
	#define _SQL_OS_QNX32
    #else
	#define _SQL_OS_QNX
    #endif
#endif

#if defined( __OS2__ ) && defined( __WATCOMC__ )
    #if defined( __386__ )
        #define _SQL_OS_OS232
    #else
        #define _SQL_OS_OS2
    #endif
#endif

#if defined( PHAR_286 )
    #define _SQL_OS_DOS286
#endif

#if defined( UNIX )
    #define _SQL_OS_UNIX
#endif

/******************************************************************/
/*  Make sure that one of the _SQL_OS_ macros has been defined    */
/******************************************************************/

#ifndef _SQL_OS_DOS
 #ifndef _SQL_OS_DOS286
  #ifndef _SQL_OS_DOS386
   #ifndef _SQL_OS_WINDOWS
    #ifndef _SQL_OS_WIN386
     #ifndef _SQL_OS_WINNT
      #ifndef _SQL_OS_QNX
       #ifndef _SQL_OS_QNX32
        #ifndef _SQL_OS_OS2
         #ifndef _SQL_OS_OS232
          #ifndef _SQL_OS_PEN
           #ifndef _SQL_OS_MAC
            #ifndef _SQL_OS_UNIX
             #ifndef _SQL_OS_NETWARE
	       #error The appropriate _SQL_OS macro has not been defined
	     #endif
	    #endif
	   #endif
	  #endif
	 #endif
	#endif
       #endif
      #endif
     #endif
    #endif
   #endif
  #endif
 #endif
#endif


/******************************************************************/
/*  Define _SQL16 or _SQL32 based on target operating-system.     */
/******************************************************************/

#if defined( __386__ )
    #define _SQL32
#elif defined( _SQL_OS_DOS386 )
    #define _SQL32
#elif defined( _SQL_OS_WIN386 )
    #define _SQL32
#elif defined( _SQL_OS_WINNT )
    #define _SQL32
#elif defined( _SQL_OS_QNX32 )
    #define _SQL32
#elif defined( _SQL_OS_OS232 )
    #define _SQL32
#elif defined( _SQL_OS_MAC )
    #define _SQL32
#elif defined( _SQL_OS_UNIX )
    #define _SQL32
#elif defined( _SQL_OS_NETWARE )
    #define _SQL32
#else
    #define _SQL16
#endif


/******************************************************************/
/*  Define _sqlfar macro based on environment                     */
/******************************************************************/

#ifdef __386__
    #define _sqlfar
#endif
#ifdef _SQL_OS_DOS386
    #define _sqlfar
#endif
#ifdef _SQL_OS_QNX32
    #define _sqlfar
#endif
#ifdef _SQL_OS_WINNT
    #define _sqlfar
#endif
#ifdef _SQL_OS_OS232
    #define _sqlfar
#endif
#ifdef _SQL_OS_MAC
    #define _sqlfar
#endif
#ifdef _SQL_OS_UNIX
    #define _sqlfar
#endif

#ifdef _sqlfar
    #define _sqlfar_isfar	0
#else
    #define _sqlfar		far
    #define _sqlfar_isfar	1
#endif

/******************************************************************/
/*  Structure definitions                                         */
/******************************************************************/

#if defined( __WATCOMC__ )
    #pragma pack( push, 1 )
#endif

typedef long int        an_sql_code;
typedef char            an_sql_state[6];

struct sqlwarn{
    unsigned char   sqlwarn0;
    unsigned char   sqlwarn1;
    unsigned char   sqlwarn2;
    unsigned char   sqlwarn3;
    unsigned char   sqlwarn4;
    unsigned char   sqlwarn5;
    unsigned char   sqlwarn6;
    unsigned char   sqlwarn7;
    unsigned char   sqlwarn8;
    unsigned char   sqlwarn9;
};

#ifdef __cplusplus
typedef struct _sqlca{
#else
typedef struct sqlca{
#endif
    unsigned char       sqlcaid[8];
    long                sqlcabc;
    an_sql_code         sqlcode;
    short               sqlerrml;
    unsigned char       sqlerrmc[70];
    unsigned char       sqlerrp[8];
    long                sqlerrd[6];
    struct sqlwarn	sqlwarn;
    an_sql_state	sqlstate;
} SQLCA;

#ifndef SQLCAPTR
    #define SQLCAPTR	    sqlcaptr
#endif

#ifndef SQLCODE
    #define SQLCODE         SQLCAPTR->sqlcode
    #define SQLWARN0        SQLCAPTR->sqlwarn.sqlwarn0
    #define SQLWARN1        SQLCAPTR->sqlwarn.sqlwarn1
    #define SQLWARN2        SQLCAPTR->sqlwarn.sqlwarn2
    #define SQLWARN3        SQLCAPTR->sqlwarn.sqlwarn3
    #define SQLWARN4        SQLCAPTR->sqlwarn.sqlwarn4
    #define SQLWARN5        SQLCAPTR->sqlwarn.sqlwarn5
    #define SQLWARN6        SQLCAPTR->sqlwarn.sqlwarn6
    #define SQLWARN7        SQLCAPTR->sqlwarn.sqlwarn7
    #define SQLWARN8        SQLCAPTR->sqlwarn.sqlwarn8
    #define SQLWARN9        SQLCAPTR->sqlwarn.sqlwarn9
    #define SQLSTATE        SQLCAPTR->sqlstate
    
    #define SQLIOCOUNT_F    sqlerrd[1]
    #define SQLCOUNT_F      sqlerrd[2]
    #define SQLIOESTIMATE_F sqlerrd[3]

    #define SQLIOCOUNT      SQLCAPTR->SQLIOCOUNT_F
    #define SQLCOUNT        SQLCAPTR->SQLCOUNT_F
    #define SQLIOESTIMATE   SQLCAPTR->SQLIOESTIMATE_F
#endif


#define DECL_VARCHAR( size )  \
        struct { unsigned short int len; \
                 unsigned char array[size+1];  \
        } 

#define DECL_LONGVARCHAR( size )  \
        struct { unsigned long int len; \
                 unsigned char array[size+1];  \
        } 

#define DECL_BINARY( size )  \
        struct { unsigned short int len; \
                 unsigned char array[size];  \
        } 

#define DECL_LONGBINARY( size )  \
        struct { unsigned long int len; \
                 unsigned char array[size];  \
        } 

#define DECL_DECIMAL( prec, scale )  \
        struct { char   array[ ((prec)/2) + 1 ]; \
        }

#define DECL_FIXCHAR( size )  \
        struct { char   array[ size ]; \
	}

#define DECL_DATETIME  \
        struct sqldatetime

typedef struct VARCHAR {
    unsigned short int  len;
    char                array[1];
} VARCHAR;

typedef struct BINARY {
    unsigned short int  len;
    char                array[1];
} BINARY;

typedef struct TYPE_DECIMAL {
    char                array[1];
} TYPE_DECIMAL;

typedef struct sqldatetime {
    unsigned short	year;		/* e.g. 1992			*/
    unsigned char	month;		/* 0-11				*/
    unsigned char	day_of_week;	/* 0-6  0=Sunday, 1=Monday, ... */
    unsigned short	day_of_year;	/* 0-365			*/
    unsigned char	day;		/* 1-31				*/
    unsigned char	hour;		/* 0-23				*/
    unsigned char	minute;		/* 0-59				*/
    unsigned char	second;		/* 0-59				*/
    unsigned long	microsecond;	/* 0-999999			*/
} SQLDATETIME;
#if !defined( _SQL_OS_OS2 )  &&  !defined( _SQL_OS_OS232 )
    typedef SQLDATETIME	    DATETIME;
#endif

typedef short int       a_sql_statement_number;

struct a_dblib_info;

struct sqlda;


/******************************************************************/
/*  Define __SMALLDATA__ based on other compiler macros           */
/******************************************************************/

#ifndef __SMALLDATA__
    #ifdef M_I86SM
	#define __SMALLDATA__
    #endif
    #ifdef M_I86MM
	#define __SMALLDATA__
    #endif
    #ifdef __TURBOC__
	#if defined( __TINY__) || defined(__SMALL__) || defined(__MEDIUM__)
	    #define __SMALLDATA__
	#endif
    #endif
#endif


/******************************************************************/
/*  PLATFORM specific definitions                                 */
/******************************************************************/

#if defined( _SQL_OS_WINDOWS )
    #define _esqlentry_         far pascal
    #ifdef __SMALLDATA__
	#undef _SQL_FAR_PTRS
	#define _SQL_FAR_PTRS
    #endif
#elif defined( _SQL_OS_OS2 )
    #define _esqlentry_         far pascal
    #ifdef __SMALLDATA__
	#undef _SQL_FAR_PTRS
	#define _SQL_FAR_PTRS
    #endif
#elif defined( _SQL_OS_OS232 )
    #ifdef __BORLANDC__
	#define _esqlentry_		__syscall
    #else
	#define _esqlentry_		_System
    #endif
#elif defined( _SQL_OS_WINNT )
    #define _esqlentry_			__stdcall
#elif defined( _SQL_OS_DOS286 )
    #define _esqlentry_
#endif

#ifdef _SQL_FAR_PTRS
    #define _fd_		    far
    #define _sql_ptrchk_(p)	    ((p) == 0 ? (void far *)0L : (void far *)p)
    #define _sql_ptrtypechk_(p,t)   ((p) == 0 ? (t far *)0L : (t far *)p)
#else
    #define _fd_ 
    #define _sql_ptrchk_(p)	    ((void *) (p))
    #define _sql_ptrtypechk_(p,t)   ((t *)p)
#endif

#ifndef _esqlentry_
    #define _esqlentry_
#endif

#ifdef __cplusplus
    #define SQLNULL		    0
    #define SQLFARNULL		    0
#else
    #define SQLNULL		    (void _fd_ *)0
    #define SQLFARNULL		    (void _sqlfar *)0
#endif

/* Windows callback index */
typedef enum {
    DB_CALLBACK_START = 0,
    DB_CALLBACK_WAIT,
    DB_CALLBACK_FINISH,
    DB_CALLBACK_ASYNC_RESPONSE,
    DB_CALLBACK_TRANSLATE_IN,
    DB_CALLBACK_TRANSLATE_OUT,
    DB_CALLBACK_UNKNOWN_EVENT,	    /* For Macintosh, initially */
    DB_MAX_CALLBACK
} a_db_callback_index;


typedef enum {
    SQLDA_CLEAR,
    SQLDA_NOCLEAR,
    SQLDA_NOEXEC
} a_descriptor_behaviour;

typedef enum {
    SQLDA_TYPE,
    SQLDA_LENGTH,
    SQLDA_RETURNED_LENGTH,
    SQLDA_PRECISION,
    SQLDA_SCALE,
    SQLDA_NULLABLE,
    SQLDA_INDICATOR
} a_descriptor_field;


#ifndef II_SQL_FUNCS
#define II_SQL_FUNCS

#ifdef __cplusplus
    extern "C" {
#endif

/* external sqlca data structure */

extern SQLCA		sqlca;
extern SQLCA		_fd_ *sqlcaptr;


/* Macros for multiple sqlca management */

#define db_set_sqlca( sqlca )	    sqlcaptr = sqlca
#define db_get_sqlca()		    sqlcaptr


/* Generate function pointers or function prototypes */

#ifndef _NO_FUNC_INFO
#ifdef _USE_ESQLDLL
#define FUNC_INFO( scope, rettype, call, fname, parms ) \
        extern rettype ( call * fname ) parms;
#include "sqlfuncs.h"
#undef FUNC_INFO
#else
#define FUNC_INFO( scope, rettype, call, fname, parms ) \
        scope rettype call fname parms;
#include "sqlfuncs.h"
#undef FUNC_INFO
#endif
#endif

#if defined( __WATCOMC__ )
    #pragma pack( pop )
#endif

#ifdef __cplusplus
    }
#endif

#endif

#endif

