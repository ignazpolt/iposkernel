/*****************************************************************************
 FILE:              OCICONS.H
 
 COPYRIGHT:         Glance AG (Steinmaur)
 
 PROJECT:           MedORA - Oracle - Anbindung an das Clinicum (Medica, Steinmaur)
 PRODUCT:           DDSORA.DLL
 
 AUTHOR:            Glance AG, CH-Steinmaur
                    F. Loeliger
 
 DATE:              14.02.1996
 
 DESCRIPTION:       additional constants used for oci interface
                    
 
 ENVIRONMENT:       Windows Application
 			 	            MS Visual C++ V1.50
 	 			            Oracle Call Interface, Release 7.1
 	 	    		        MKS - RCS is used for the revision controlling
                    
 VERSION:           0.9 15.03.96 first freezed version (beta released)   
 										0.1    The DLL is manually ported from the sybase DLL Rev 1.3
 
 STATUS:            beta released
 
 MODIFIED:          
   22.02.96 FL  LONG Type added 
   14.02.96 FL	created
   
*****************************************************************************/

#ifndef ORATYPES
#include <oratypes.h>
#endif /* ORATYPES */

#ifndef INCL_OCICONS
#define INCL_OCICONS


/*  internal/external datatype codes */
#define OCI_VARCHAR2_TYPE       		     1
#define OCI_NUMBER_TYPE      		    	   2
#define OCI_INT_TYPE                		 3
#define OCI_FLOAT_TYPE          		     4
#define OCI_STRING_TYPE     		         5
#define OCI_LONG_TYPE	     		   	   	   8
#define OCI_ROWID_TYPE            		  11
#define OCI_DATE_TYPE         		      12
#define OCI_RAW_TYPE      		          23
#define OCI_LONGRAW_TYPE          		  24  

/*  ORACLE error codes used in demonstration programs */
#define OCI_SUCCESS						    		   0
#define OCI_WRN_VAR_NOT_IN_LIST       1007
#define OCI_WRN_NO_DATA_FOUND         1403
#define OCI_WRN_NULL_VALUE_RETURNED   1405
#define OCI_WRN_SEQ_NOT_YET_DEFINED   8002

/*  some SQL and OCI function codes */
#define OCI_FT_INSERT        			       3
#define OCI_FT_SELECT             		   4
#define OCI_FT_UPDATE 			 	           5
#define OCI_FT_DELETE         		       9
#define OCI_FC_OOPEN               		  14

/* some parameter values */
#define OCI_DEFFLG_DEFERRED       		   1
#define OCI_LNGFLG_ORACLE7       		     2
#define OCI_CANCEL                 			 1

/* Indicator variables */
#define OCI_IND_NULL										-1

/*
** Size of HDA area:
** 512 for 64 bit architectures
** 256 for 32 bit architectures
*/

#if (defined(__osf__) && defined(__alpha)) || defined(CRAY) || defined(KSR)
# define HDA_SIZE 512
#else
# define HDA_SIZE 256
#endif


#endif      /* INCL_OCICONS */

