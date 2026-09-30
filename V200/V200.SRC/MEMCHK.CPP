/*
**      Ueberpruefen der GETGLOBALMEM, FREEGLOBALMEM
**
*/

// $Header:   P:/marille/clinicum/rev/memchk.cpv   1.1   02 Feb 1996 10:36:20   GERHOLD  $
// $Log:   P:/marille/clinicum/rev/memchk.cpv  $
// 
//    Rev 1.1   02 Feb 1996 10:36:20   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.0   24 Jun 1994 17:05:16   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.0   02 Dec 1992 15:37:34   HANNES
// Initial revision.

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "dds32.h"

int fhandle;
void preplog ()
  {
  OFSTRUCT Of ;
  fhandle = OpenFile ("allocs.txt",&Of,OF_CREATE|OF_WRITE);
  }

void closelog ()
  {
  _lclose (fhandle);
  }

static int lfnr;
static int flfnr;

int Getlfnr (void) {
  return lfnr;
  }
HANDLE GAlloc (WORD mode,DWORD Len)
  {
  HANDLE res = GlobalAlloc (mode,Len);
  char txt[30];
  sprintf (txt,"A:%u(%d)\r\n",res,lfnr++);
  _lwrite (fhandle,txt,strlen(txt));
  return res ;
  }

HANDLE LAlloc (WORD mode,WORD Len)
  {
  HANDLE res = LocalAlloc (mode,Len);
  char txt[30];
  sprintf (txt,"G:%u(%d)\r\n",res,lfnr++);
  _lwrite (fhandle,txt,strlen(txt));
  return res ;
  }

HANDLE GFree (HANDLE or)
  {
  HANDLE res = GlobalFree (or);
  char txt[30];
  sprintf (txt,"%d=F:%u(%d)\r\n",res,or,flfnr++);
  _lwrite (fhandle,txt,strlen(txt));
  return res ;
  }

HANDLE LFree (HANDLE or)
  {
  HANDLE res = LocalFree (or);
  char txt[30];
  sprintf (txt,"R:%u(%d)\r\n",or,flfnr++);
  _lwrite (fhandle,txt,strlen(txt));
  return res ;
  }

void MtoF (HANDLE or)
  {
  char txt[30];
  sprintf (txt,"0=F:%u(%d)\r\n",or,flfnr++);
  _lwrite (fhandle,txt,strlen(txt));
  }

void MtoA (HANDLE or)
  {
  char txt[30];
  sprintf (txt,"A:%u(%d)\r\n",or,lfnr++);
  _lwrite (fhandle,txt,strlen(txt));
  }

void ExtMtoG (HANDLE h,WORD Offs)
  {
  char txt[30];
  sprintf (txt,"L%u:%u(%d)\r\n",h,Offs,lfnr++);
  _lwrite (fhandle,txt,strlen(txt));
  }

void ExtMtoF (HANDLE h,WORD Offs)
  {
  char txt[30];
  sprintf (txt,"U%u:%u(%d)\r\n",h,Offs,flfnr++);
  _lwrite (fhandle,txt,strlen(txt));
  }

