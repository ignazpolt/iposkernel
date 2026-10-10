/******************************************************************************
**	Filename:    	Host.h
**	Purpose:    	This is the system independent typedefs and defines
**	Author:     	Mike Niquette, Jim Graham, Bob Sobol, Patty Lopez,
**					Dave Formanek, and Fred T. Moose.
**	Environment:	DOS, OS/2, HP-UX, and MAC.
**	Library:    	None.
**	History:    	Creation Date:  09/13/1988, MLN
**	Version:    	2.0				
**
**	(c) Copyright Hewlett-Packard Company, 1988, 1989, 1990, 1991.
**	All rights are reserved. Copying or other reproduction of
**	this program except for archival purposes is prohibited
**	without the prior written consent of Hewlett-Packard Company.
**
**			  RESTRICTED RIGHTS LEGEND
**
**	Use, duplication, or disclosure by the Government is subject to 
**	restrictions as set forth in paragraph (b) (3) (B) of the Rights 
**	in Technical Data and Computer Software clause in DAR 7-104.9(a).
**
**	HEWLETT-PACKARD COMPANY
**	Greeley, Colorado
*/


#ifndef   __HOST__
#define   __HOST__

/******************************************************************************
**                              IMPORTANT!!!                                 **
**                                                                           **
**      Uncomment the line which describes the environment you are using     **
**                                                                           **
******************************************************************************/

	 #define   __PC__              /* PC computers */
/*   #define   __DOS__        */     /* DOS  environment */
/*   #define   __OS2__        */     /* OS/2 environment */
   #define   __MSW3__            /* MS Windows 3.0 */
/*   #define   __MSW__        */     /* MS Windows 2.0 */
/*   #define   __PM11__       */     /* MS OS/2 Presentation Manager 1.1 */
/*	 #define   __PM12__       */     /* MS OS/2 Presentation Manager 1.2 */
/*   #define   __PM121__      */     /* MS OS/2 Presentation Manager 1.21 */
/*   #define   __PM20__       */     /* MS OS/2 Presentation Manager 2.0 */
	 #define   __FarProc__         /* 32 bit pointer to procedures */
	 #define   __FarData__         /* 32 bit pointer to data */

/*   #define   __UNIX__       */     /* Unix & Unix C */
/*	 #define   __MAC__    */    		 /* MacIntosh */
/*   #define   __MPW__        */     /* MacIntosh Programmers Workshop */
	 #define   __LIGHTSPEED__   	 /* MacIntosh LightSpeed C */

/*	 #define __NATIVE__   */       /* MOTO  */
 	 #define __NATIVE__			INTEL 

/*****************************************************************************/

#ifndef __FarProc__
#define FP
#define NP
#else
#define FP     far pascal
#define NP     near pascal
#endif
#ifndef __FarData__
#define FD
#define HD
#else
#define FD     far
#define HD     huge
#endif


typedef char                    INT8;
typedef unsigned char           UINT8;
typedef short int               INT16;
typedef unsigned short int      UINT16;
typedef long                    INT32;
typedef unsigned long           UINT32;
typedef float                   FLOAT32;
typedef double                  FLOAT64;
typedef char FD *               PINT8;
typedef unsigned char FD *      PUINT8;
typedef short int FD *          PINT16;
typedef unsigned short int FD * PUINT16;
typedef long FD *               PINT32;
typedef unsigned long FD *      PUINT32;
typedef float FD *              PFLOAT32;
typedef double FD *             PFLOAT64;

typedef INT16                   (FP *PFINT16)(); /* pointer to function */
typedef INT32                   (FP *PFINT32)();

#ifdef __PC__
typedef FLOAT64					FLOAT;
#else
typedef FLOAT32					FLOAT;
#endif
typedef FLOAT FD *				PFLOAT;

/*****************************************************************************
**
**						Standard GHC Definitions
**
*****************************************************************************/

#ifndef OKAY
#define OKAY			0
#endif

#ifndef ERROR
#define ERROR			-1
#endif

#ifndef TRUE
#define TRUE			1
#endif

#ifndef FALSE
#define FALSE			0
#endif

#ifndef ON
#define ON				1
#endif

#ifndef OFF
#define OFF				0
#endif

#ifndef NULL
#define NULL			0L
#endif

#ifndef BOOLEAN
#ifdef __MAC__
#define BOOLEAN			Boolean
#else
typedef UINT16			BOOLEAN;
#endif
#endif

#endif
