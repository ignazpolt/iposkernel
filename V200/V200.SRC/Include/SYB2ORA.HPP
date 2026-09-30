/*****************************************************************************
 FILE:              OCIPORT.H
 
 COPYRIGHT:         Glance AG (Steinmaur)
 
 PROJECT:           MedORA - Oracle - Anbindung an das Clinicum (Medica, Steinmaur)
 PRODUCT:           DDSORA.DLL
 
 AUTHOR:            Glance AG, CH-Steinmaur
                    F. Loeliger
 
 DATE:              14.02.1996
 
 DESCRIPTION:       additional porting routines 
                    
 
 ENVIRONMENT:       Windows Application
 			 	            MS Visual C++ V1.50
 	 			            Oracle Call Interface, Release 7.1
 	 	    		        MKS - RCS is used for the revision controlling
                    
 VERSION:           0.9 15.03.96 first freezed version (beta released)   
 										0.1    The DLL is manually ported from the sybase DLL Rev 1.3
 
 STATUS:            beta released
 
 MODIFIED:
   15.03.96 FL  dbglog_force added
   08.03.96 FL  Exchanged the datatypes for RAW and LONG RAW
   07.03.96 FL  date is retrieved as a string (changed the Dateformat CS_DATETIME_TYPE)
   05.03.96 FL  changed datatype of small character arrays from CHAR to VARCHAR2 to avoid space padding
	 23.02.96 FL  Help for Debugging added 
   22.02.96 FL  LONG Type added 
   14.02.96 FL	created
   
*****************************************************************************/

#ifndef ORATYPES
#include <oratypes.h>
#endif /* ORATYPES */
	extern "C" {
		#include <oratypes.h>
		#include <ocidfn.h>	      // LDA and CDA struct declarations
		#include <ociapr.h>
		//#ifdef __STDC__
		//#include <ociapr.h>
		//#else
		//#include <ocikpr.h>
		//#endif
		#include "ocicons.h" 			// oci constants additionally used
	}

#ifndef INCL_OCIPORT
#define INCL_OCIPORT

#include "csconfig.h"		// sybase styled types


#define DBG_ASSERT_TEXT(cond,text1,text2) { if (!(cond)) dbglog(MODULENUM, __LINE__, __FILE__, text1, text2); }
#define DBGFORCE_ASSERT_TEXT(cond,text1,text2) { if (!(cond)) dbglog_force(MODULENUM, __LINE__, __FILE__, text1, text2); }

// cstypes.h: additional definitions from cstypes.h unchanged:

		typedef char CS_CHAR;
		#define CS_MAX_NAME       (CS_INT)(128 + 4)
		#define CS_LOCALE         CS_VOID
		/*
		** Define the bit values used in the format element of the CS_DATAFMT
		** structure. The CS_FMT_JUSTIFY_RT flag exists for future use only.
		*/
		#define CS_FMT_UNUSED           (CS_INT)0x0
		#define CS_FMT_NULLTERM         (CS_INT)0x1
		#define CS_FMT_PADNULL          (CS_INT)0x2
		#define CS_FMT_PADBLANK         (CS_INT)0x4
		#define CS_FMT_JUSTIFY_RT       (CS_INT)0x8
		/*
		** Define the core return codes.
		*/
		#define CS_SUCCEED              (CS_RETCODE)1
		#define CS_FAIL                 (CS_RETCODE)0
		#define CS_MEM_ERROR            (CS_RETCODE)-1
		#define CS_PENDING              (CS_RETCODE)-2
		#define CS_QUIET                (CS_RETCODE)-3
		#define CS_BUSY                 (CS_RETCODE)-4
		#define CS_INTERRUPT            (CS_RETCODE)-5
		#define CS_BLK_HAS_TEXT         (CS_RETCODE)-6
		#define CS_CONTINUE             (CS_RETCODE)-7
		#define CS_FATAL                (CS_RETCODE)-8
		/*
		** Define error offsets. All other CS_RETCODE error codes should be
		** based off of these values to avoid define conflicts.
		*/
		#define CS_CONV_ERR             (CS_RETCODE)(-100)
		#define CS_EXTERNAL_ERR         (CS_RETCODE)(-200)
		#define CS_INTERNAL_ERR         (CS_RETCODE)(-300)
		/*
		** Special returns for ct_fetch().
		*/
		#define CS_END_DATA             (CS_RETCODE)(CS_EXTERNAL_ERR - 4)
		#define CS_ROW_FAIL             (CS_RETCODE)(CS_EXTERNAL_ERR - 3)
		#define CS_END_RESULTS          (CS_RETCODE)(CS_EXTERNAL_ERR - 5)		
		
		/*
		** Special returns for not available sequence numbers in oracle 
		*/
		#define CS_NOT_AVAIL						CS_ROW_FAIL
		#define CS_LAST_DATA            CS_END_RESULTS


// adapted definitions
#define CS_VOID				void
#define CS_CONNECTION void			// connection handle is not used in oracle
#define CS_CONTEXT		Lda_Def  	// maps oracle lda handle structure to sybase style structure
#define CS_COMMAND    Cda_Def   // Cursor contains the command analogously to the sybase style

/* datetime 
   for the first approach we use the format : DDMMYYYYHH24MISS
   attn: there is neiter a delimiter nor a null termination symbol used here.
*/
#define OCI_DATETIME_FORMAT 			 "DDMMYYYYHH24MISS"
#define OCI_DATETIME_LEN    14
typedef struct _datetime { 
	char dt[OCI_DATETIME_LEN+1];
	} OCI_DATETIME;

/* Datatyp mapping for the binding structures */
#define CS_INT_TYPE       OCI_INT_TYPE       	
#define CS_SMALLINT_TYPE  OCI_INT_TYPE	
#define CS_REAL_TYPE      OCI_FLOAT_TYPE	
#define CS_TEXT_TYPE_BIG  OCI_LONG_TYPE	
#define CS_TEXT_TYPE      OCI_STRING_TYPE	
#define CS_CHAR_TYPE      OCI_STRING_TYPE
// #define CS_BINARY_TYPE    OCI_RAW_TYPE
// #define CS_IMAGE_TYPE     OCI_LONGRAW_TYPE
// #define CS_DATETIME_TYPE  OCI_DATE_TYPE
#define CS_BINARY_TYPE    OCI_LONGRAW_TYPE // >> FL 08.03.96: Exchanged the datatypes
#define CS_IMAGE_TYPE     OCI_RAW_TYPE     // >> FL 08.03.96: Exchanged the datatypes
#define CS_DATETIME_TYPE  OCI_STRING_TYPE  // >> FL 07.03.96: date is retrieved as a string (to_char)

/*****************************************************************************
**
** User-accessible information structures.
**
*****************************************************************************/

/*
** The data format structure used by Open Client/Server.
**
** name[CS_MAX_NAME]    The name of the data.
**
** namelen              The actual length of the name.
**
** datatype             The datatype field indicates what Sybase
**                      or user defined datatype is being represented.
**
** format               The format field tells whether or not data
**                      should be padded to the full length of the
**                      variable. This will only be used if the type
**                      of the variable is character or binary. The 
**                      format field also tells whether the data
**                      should be null-terminated (for char
**                      variables, only). This is a bit field in which
**                      the format values are or'd together.
**      
** maxlength            The max length the data might be.
**
** scale                This is used if dataytype needs it (e.g.
**                      CS_NUMERIC)
**
** precision            This is used if dataytype needs it.
**
** status               Additional data status values. This is a bit
**                      field in which the status values are or'd
**                      together.
**
** count                If binding data, the count field tells how
**                      many rows should be bound.
**
** usertype             User-defined datatype code passed back from
**                      the Server.
**
** *locale              Pointer to the locale for this data.
*/
typedef struct _cs_datafmt
{
// CS_CHAR         name[CS_MAX_NAME];
// CS_INT          namelen;
	CS_INT          datatype;
  CS_INT          format;
  CS_INT          maxlength;
// CS_INT          scale;
// CS_INT          precision;
// CS_INT          status;
  CS_INT          count;
// CS_INT          usertype;
// CS_LOCALE       *locale;
} CS_DATAFMT;

/* Datatypes for creation of the database with SQL 
   The Types are Mapped to the Clinicum Types VAR_xxx
*/
#define DB_TYPE_VAR_LONG_AUTO   "NUMBER"
#define DB_TYPE_VAR_LONG        "INT"  // FL maximal 4 Bytes (signed)
#define DB_TYPE_VAR_DEC         "REAL"
#define DB_TYPE_VAR_STR_BIG     "LONG VARCHAR" 
#define DB_TYPE_VAR_STR			    "VARCHAR2"     
#define DB_TYPE_VAR_STR_SMALL   "VARCHAR2"  // >> FL 05.03.96 changed from CHAR to VARCHAR2 to avoid space padding
#define DB_TYPE_VAR_POINT       "RAW"
#define DB_TYPE_VAR_CONT        "LONG RAW"
#define DB_TYPE_VAR_STRARR_AUTO "NUMBER"
#define DB_TYPE_VAR_STRARR      "SMALLINT"
#define DB_TYPE_VAR_FLAG        "SMALLINT"
#define DB_TYPE_VAR_SCALE       "RAW"
#define DB_TYPE_VAR_DATE        "DATE"
#define DB_TYPE_VAR_OBJ_BIG     "LONG RAW"
#define DB_TYPE_VAR_OBJ_SMALL   "RAW"
#define DB_TYPE_VAR_TIME        "DATE"
#define DB_TYPE_VAR_TIMESTAMP   "DATE"


/* #define context				lda	*/			// lda represents the context in oracle

/* special attributation to ensure easier adaptions */
#define VARLEN_TYPE							ub2
#define VARRETCODE_TYPE 				ub2
#define VARIND_TYPE 						sb2
#define cMAX_ORADESCRIPTOR      30
#define cMAX_VARNAMESIZE        cMAX_ORADESCRIPTOR
#define cMAX_SEQUENCENAME       cMAX_ORADESCRIPTOR

#define PREFIX_SEQUENCE					"s_"   // the name of a sequence is the table's name prefixed with "s_"
#define PREFIX_ADAPTION					"x"    // all leading non alpha characters in attribute names will be changed to "x"
/* conversion and error routines */

  CS_RETCODE ociretmap(const sword retcode);  
	void ocierr_report(const Lda_Def *lda, const Cda_Def *cursor);
  CS_RETCODE ocirethandling(const Lda_Def *lda, const Cda_Def *cda);
  
  void dbglog(const int ModuleNr, const int LineNr, const char *FileName, const char *text1, const char *text2);
  void dbglog_force(const int ModuleNr, const int LineNr, const char *FileName, const char *text1, const char *text2);
  BOOL IsToIgnore (int errnr,BOOL FAR *doLast);
#endif      /* INCL_OCIPORT */

