/******************************************************************************
**	Filename:   	Hostmem.h
**	Purpose:     	Definitions for host-dependent memory file-Hostmem.c
**	Authors:    	Jim Graham and Dave Formanek
**	Environment:	Portable code, Originally designed 
**	             	for MAC, DOS, MSWindows, and HP-UX
**	Library:     	None
**	History:	    Spotted
**	Version:    	2.0
**
**	(c) Copyright Hewlett-Packard Company, 1988, 1989.
**	All rights are reserved. Copying or other reproduction of
**	this program except for archival purposes is prohibited
**	without the prior written consent of Hewlett-Packard Company.
**
**			  RESTRICTED RIGHTS LEGEND
**
**	Use, duplication, or disclosure by the Government
**	is subject to restrictions as set forth in
**	paragraph (b) (3) (B) of the Rights in Technical
**	Data and Computer Software clause in
**	DAR 7-104.9(a).
**
**	HEWLETT-PACKARD COMPANY
**	Greeley, Colorado
******************************************************************************/

#ifndef __HOSTMEM__
#define __HOSTMEM__

#include "Host.h"

/**----------------------------------------------------------------------------
							Function Prototypes
----------------------------------------------------------------------------**/

#ifdef __UNIX__

PUINT8 AllocPointer( /* UINT32 Size */ );
INT16  DumpPointer( /* PUINT8 pMemory */ );
UINT32 GetHandle( /* PUINT8 pMemory */ );
UINT32 PointerSize( /* PUINT8 pMemory */ );
PUINT8 ReallocPointer( /* PUINT8 pMemory, UINT32 Size, PINT16 pStatus */ );

UINT32 AllocHandle( /* UINT32 Size */ );
PUINT8 LockHandle( /* UINT32 Handle */ );
INT16  UnlockHandle( /* UINT32 Handle */ );
INT16  DumpHandle( /* UINT32 Handle */ );
UINT32 HandleSize( /* UINT32 Handle */ );
UINT32 ReallocHandle( /* UINT32 Handle, UINT32 Size */ );

UINT32 LargestFreeBlock( /* void */ );

#else /* Mac and DOS */

PUINT8 AllocPointer( UINT32 size );
INT16  DumpPointer( PUINT8 pMemory );
UINT32 GetHandle( PUINT8 pMemory );
UINT32 PointerSize( PUINT8 pMemory );
PUINT8 ReallocPointer( PUINT8 pMemory, UINT32 size, PINT16 pStatus );

UINT32 AllocHandle( UINT32 size );
PUINT8 LockHandle( UINT32 Handle );
INT16  UnlockHandle( UINT32 Handle );
INT16  DumpHandle( UINT32 Handle );
UINT32 HandleSize( UINT32 Handle );
UINT32 ReallocHandle( UINT32 Handle, UINT32 size );

UINT32 LargestFreeBlock( void );

#endif

#endif
