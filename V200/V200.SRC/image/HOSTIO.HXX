/******************************************************************************
**	Filename:   	HostIO.h
**	Purpose:     	Definitions for the IO file for a particular host
**	Authors:    	Jim Graham and Dave Formanek
**	Environment:	Portable code, Originally designed 
**	             	for MAC, DOS, MSWindows, HP-UX, and OS/2
**	Library:     	None
**	History:
**	Version:    	2.0
**
**	(c) Copyright Hewlett-Packard Company, 1988, 1989, 1990.
**	All rights are reserved. Copying or other reproduction of
**	this program except for archival purposes is prohibited
**	without the prior written consent of Hewlett-Packard Company.
**
**	Notes to U.S. Government Users:
**	
**			  RESTRICTED RIGHTS LEGEND
**
**	Use, duplication, or disclosure by the Government is subject to 
**	restrictions as set forth in paragraph (b) (3) (B) of the Rights 
**	in Technical Data and Computer Software clause in DAR 7-104.9(a).
**
**	Use, duplication, or disclosure by the Government is subject to 
**	restrictions as set forth in paragraph (c) (1) (ii) of the Rights 
**	in Technical Data and Computer Software clause at DFARS 252.227-7013.
**
**	HEWLETT-PACKARD COMPANY
**	Greeley, Colorado
******************************************************************************/

#ifndef __HOSTIO__
#define __HOSTIO__


/**----------------------------------------------------------------------------
								Definitions
----------------------------------------------------------------------------**/
#include "Host.h"

#define SEEK_SET			0
#define SEEK_CUR			1
#define	SEEK_END			2

/**----------------------------------------------------------------------------
							Function Prototypes
----------------------------------------------------------------------------**/

#ifdef __UNIX__
INT16 FileClose( /* INT16 handle */ ); 
INT16 FileCreate ( /* PUINT8 pName */ );
INT16 FileDelete( /* PUINT8 pName */ );
INT32 FileSeek  ( /* INT16 handle, UINT8 Mode, INT32 Offset */ );
INT32 FileWrite  ( /* INT16 handle, PUINT8 pBuffer, INT32 Length */ );

#ifdef __READ__
INT16 FileOpen ( /* PUINT8 pName */ );
INT32 FileRead   ( /* INT16 handle, PUINT8 pBuffer, INT32 Length */ );
#endif

#else /* Mac and DOS */
INT16 FileClose( INT16 handle ); 
INT16 FileCreate ( PUINT8 pName );
INT16 FileDelete( PUINT8 pName );
INT32 FileSeek  ( INT16 handle, UINT8 Mode, INT32 Offset );
INT32 FileWrite  ( INT16 handle, PUINT8 pBuffer, INT32 Length );

#ifdef __READ__
INT16 FileOpen ( PUINT8 pName );
INT32 FileRead   ( INT16 handle, PUINT8 pBuffer, INT32 Length );
#endif

#ifdef __MAC__
void  SetTypes( OSType creator, OSType fileType );
void  SetvRefNum( INT16 vRefNum );
#endif

#endif

#endif /* __HOSTIO__ */
