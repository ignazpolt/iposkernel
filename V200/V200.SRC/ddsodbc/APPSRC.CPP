//////////////////////////////////////////////////////////////
//  Sybase Anywhere Authentification
//////////////////////////////////////////////////////////////
//
//  $Header:   P:/marille/clinicum/ddsodbc/rev/appsrc.cpv   1.1   05 Oct 1998 11:10:52   Gerhold  $
//  $Log:   P:/marille/clinicum/ddsodbc/rev/appsrc.cpv  $
// 
//    Rev 1.1   05 Oct 1998 11:10:52   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.0   24 Mar 1998 12:33:42   Martin
// Initial revision.
//

#ifdef WIN32
#define _SQL_OS_WINNT 1
#else
#define _SQL_OS_WINDOWS 1
#endif

extern "C" {

#include "sqlcanew.h"

#if defined(_SQL_OS_WIN386) || defined(_SQL_OS_WINDOWS) || defined(_SQL_OS_WINNT)
    #include <windows.h>
#elif defined(_SQL_OS_OS2) || defined(_SQL_OS_OS232)
    #define INCL_DOSPROCESS
    #include "os2.h"
#endif
#include <stdlib.h>
#include <string.h>
#if defined(__QNX__)
    #include <i86.h>
#else
    #if !defined(__IBMC__)
        #include <dos.h>
    #endif
#endif

#include "wsqlauth.h"
#include "authblk.h"

#ifdef AUTH_BLOCK_TAG
    static an_auth_block	*AuthBlk = &AUTH_BLOCK_TAG.auth_blk;
#else
    static an_auth_block	*AuthBlk = &auth_blk;
#endif

#if defined(M68000)
    #include "rotate.h"
#endif

#if defined( _SQL32 )
    #define _cbfar
#else
    #define _cbfar	    far
#endif

#if defined(_SQL_OS_WINDOWS) || defined(_SQL_OS_WINNT)
    static HINSTANCE	    hDBLIB = NULL;
#else
    extern an_auth_error _esqlentry_ db_authenticate( an_auth_block _fd_ *, long );
#endif

#if defined(_SQL_OS_WINDOWS)
    static const char *AuthDblibName = "dbl50w.dll";
#endif
#if defined(_SQL_OS_WINNT)
    static const char *AuthDblibName = "dbl50t.dll";
#endif

static long _esqlentry_ auth_callback( long parm )
/************************************************/
{
    long		myval;

    #if defined(_SQL_OS_WINDOWS) || defined(_SQL_OS_WIN386)
	myval = (long)GetCurrentTask();
    #elif defined(_SQL_OS_WINNT)
	myval = (long)GetCurrentProcessId();
    #elif defined(_SQL_OS_OS232)
    {
	PTIB		ptib;
	PPIB		ppib;
	
	DosGetInfoBlocks( &ptib, &ppib );
	myval = (long)ppib->pib_ulpid;
    }
    #elif defined(_SQL_OS_OS2)
    {
	SEL		localseg;
	SEL		globalseg;
	LINFOSEG	far *localinfo;
    
	DosGetInfoSeg( &globalseg, &localseg );
	localinfo = MK_FP( localseg, 0 );
	myval = (long)localinfo->pidCurrent;
    }
    #else
	myval = 0L;
    #endif
    parm = _lrotl( parm, (int)(myval % 32) ) ^ myval ^ ( myval << 16 );
    return( parm );
}

static void store_cb_info( unsigned char *dest, void _cbfar *source )
/*******************************************************************/
{
    int			ctr;
    unsigned int	seg;
    unsigned int	off;

    #ifdef FP_SEG
	seg = FP_SEG( source );
	off = FP_OFF( source );
    #else
        seg = 0;
	off = (unsigned int)source;
    #endif
    for( ctr = 0; ctr < 4; ++ctr ) {
	dest[ctr] = _mk_nybble( (seg >> (ctr * 4)) & 0xF );
    }
    for( ctr = 0; ctr < sizeof( off ) * 2; ++ctr ) {
	dest[ctr + 4] = _mk_nybble( (off >> (ctr * 4)) & 0xF );
    }
}

#if defined(_SQL_OS_WINDOWS) || defined(_SQL_OS_WINNT)
extern an_auth_error __db_authinit( an_auth_block * blk,
				    unsigned	    hinst,
				    HINSTANCE *	    hdll )
/********************************************************/
{
    an_auth_error	    retval;
    FARPROC		    cb_ptr;
    an_auth_error	    (_esqlentry_ *dblib_authptr)( an_auth_block _fd_ *, long );

    if( hinst == 0 ) return( AUTHERR_BAD_PARMS );

    cb_ptr = MakeProcInstance( (FARPROC)auth_callback, (HANDLE)hinst );
    if( cb_ptr == NULL ) return( AUTHERR_MPI_FAILED );
    
    store_cb_info( blk->callback, (void _cbfar *)cb_ptr );

    *hdll = LoadLibrary( AuthDblibName );
    if( (unsigned)*hdll < 32 ) {
	FreeProcInstance( cb_ptr );
	return( AUTHERR_MISSING_DLL );
    }

    dblib_authptr = (an_auth_error (_esqlentry_ _cbfar *)( an_auth_block _fd_ *, long ))
			    GetProcAddress( *hdll, "db_authenticate" );
    if( dblib_authptr == NULL ) {
	FreeProcInstance( cb_ptr );
	FreeLibrary( *hdll );
	*hdll = NULL;
	return( AUTHERR_OLD_DLL );
    }
    retval = dblib_authptr( blk, (long)DB_AUTH_INIT );
    FreeProcInstance( cb_ptr );
    return( retval );
}
#endif

extern an_auth_error DBAuthSetParm( an_auth_parm parm, void *ptr )
/****************************************************************/
{
    switch( parm ) {
#if defined(_SQL_OS_WINDOWS) || defined(_SQL_OS_WINNT)
    case AUTHPARM_DBLIB_DLLNAME:
	AuthDblibName = (const char *) ptr;
	break;
#endif
    case AUTHPARM_AUTH_BLOCK:
	AuthBlk = (an_auth_block *) ptr;
	break;
    default:
        return( AUTHERR_BAD_PARMS );
    }
    return( AUTHERR_SUCCESS );
}

#if defined(_SQL_OS_WINDOWS) || defined(_SQL_OS_WINNT)
extern an_auth_error DBAuthInit( unsigned hinst )
#else
extern an_auth_error DBAuthInit( void )
#endif
/***********************************************/
{
    DBAuthFini();

    #if defined(_SQL_OS_WINDOWS) || defined(_SQL_OS_WINNT)
	return( __db_authinit( AuthBlk, hinst, &hDBLIB ) );
    #else
	store_cb_info( AuthBlk->callback, (void _cbfar *)auth_callback );
	return( db_authenticate( AuthBlk, (long)DB_AUTH_INIT ) );
    #endif
}

#if defined(_SQL_OS_WINDOWS) || defined(_SQL_OS_WINNT)
extern void __db_authfini( HINSTANCE *hdll )
/***************************************/
{
    an_auth_error	    (_esqlentry_ *dblib_authptr)( an_auth_block _fd_ *, long );
    
    if( (unsigned)*hdll >= 32 ) {
	dblib_authptr = (an_auth_error (_esqlentry_ _cbfar *)( an_auth_block _fd_ *, long ))
				GetProcAddress( *hdll, "db_authenticate" );
	if( dblib_authptr != NULL ) {
	    dblib_authptr( NULL, (long)DB_AUTH_FINI );
	}
	FreeLibrary( *hdll );
    }
    *hdll = NULL;
}
#endif

extern void DBAuthFini( void )
/****************************/
{
    #if defined(_SQL_OS_WINDOWS) || defined(_SQL_OS_WINNT)
	__db_authfini( &hDBLIB );
    #else
	db_authenticate( NULL, (long)DB_AUTH_FINI );
    #endif
}

}

extern HANDLE hLibInst;
void InitializeSybaseAnywhereAuthentication(void)
  {
  DBAuthInit((unsigned int)hLibInst);
  }

void FinishSybaseAnywhereAuthentication(void)
  {
  DBAuthFini();
  }

