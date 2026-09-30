/*
 * WEP.C
 *
 * WEP code for the DLL.  This function is placed in a separate
 * segment so marking the segment as FIXED is not hard on the
 * system.
 *
 * Version 1.1, October 1991, Kraig Brockschmidt
 */
  /*COPYRIGHT:

     (C) Copyright Microsoft Corp. 1993.  All rights reserved.
 
     You have a royalty-free right to use, modify, reproduce and
     distribute the Sample Files (and/or any modified version) in
     any way you find useful, provided that you agree that
     Microsoft has no warranty obligations or liability for any
     Sample Application Files which are modified.*/
 


#include <windows.h>


/*
 * WEP
 *
 * Purpose:
 *  Required DLL Exit function.  Does nothing.
 *
 * Parameters:
 *  bSystemExit     BOOL indicating if the system is being shut
 *                  down or the DLL has just been unloaded.
 *
 * Return Value:
 *  void
 *
 */

extern "C" {
int FAR PASCAL WEP(int bSystemExit)
    {
    if (bSystemExit)
        {
        //Shutdown
        }
    else
        {
        //DLL use count is zero
        }

    return 1;
    }
  }