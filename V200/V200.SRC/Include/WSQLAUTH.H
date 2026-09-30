#if !defined( _WSQLAUTH_H_INCLUDED )
#define _WSQLAUTH_H_INCLUDED

#define AUTH_BLK_FLAGSIZE	16
#define AUTH_BLK_CBSIZE		12
#define AUTH_BLK_DATASIZE	64
#define AUTH_STR_MAXLEN		79
#define AUTH_BLK_HALFSIZE	(AUTH_BLK_FLAGSIZE + AUTH_BLK_CBSIZE + AUTH_BLK_DATASIZE + 1 + 2 * ( AUTH_STR_MAXLEN + 1 ))
#define AUTH_ENCRYPT_SIZE	( 2 * ( AUTH_STR_MAXLEN + 1 ) )

// Size is actually only 506 bytes, but a 512-byte copy buffer won't hurt.
#define AUTH_NUM_LONGS		128

#define AUTH_BLK_STR_SIZE	24

typedef struct an_auth_block {
    unsigned char	    flagstr[AUTH_BLK_FLAGSIZE];
    unsigned char	    string1[AUTH_STR_MAXLEN + 1];
    unsigned char	    string2[AUTH_STR_MAXLEN + 1];
    unsigned char	    callback[AUTH_BLK_CBSIZE];
    unsigned char	    data[AUTH_BLK_DATASIZE];
    unsigned char	    term_null;
    unsigned char	    patchstuff[AUTH_BLK_HALFSIZE];
} an_auth_block;

typedef struct an_auth_block_tag {
    unsigned char	    auth_blk_str[ AUTH_BLK_STR_SIZE ];
    struct an_auth_block    auth_blk;
} an_auth_block_tag;

typedef short an_auth_error;

#define AUTHERR_MPI_FAILED	-6
#define AUTHERR_OLD_DLL		-5
#define AUTHERR_MISSING_DLL	-4
#define AUTHERR_NO_MEMORY	-3
#define AUTHERR_BAD_PARMS	-2
#define AUTHERR_FAILURE		-1
#define AUTHERR_SUCCESS		0

typedef short an_auth_parm;

#define AUTHPARM_DBLIB_DLLNAME	1
#define AUTHPARM_AUTH_BLOCK	2

#if defined(_SQL_OS_WINDOWS) || defined(_SQL_OS_WINNT)
    extern an_auth_error	DBAuthSetParm( an_auth_parm, void * );
    extern an_auth_error	DBAuthInit( unsigned int );
    extern void			DBAuthFini( void );
#else
    extern an_auth_error	DBAuthSetParm( an_auth_parm, void * );
    extern an_auth_error	DBAuthInit( void );
    extern void			DBAuthFini( void );
#endif

#define _mk_nybble( nybble )	( (char)((nybble) + 'A') )
#define _get_nybble( ch )	( (unsigned long)((ch) - 'A') )

/* Possible parm values to db_authenticate's second argument */
#define DB_AUTH_INIT		0
#define DB_AUTH_FINI		1

#endif
