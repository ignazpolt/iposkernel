// ----------------------------------
//      Diverse Hilfsfuntionen
// ----------------------------------
//
// $Header:   P:/marille/clinicum/rev/hlpfunc.cpv   1.2   02 Feb 1996 10:35:02   GERHOLD  $
// $Log:   P:/marille/clinicum/rev/hlpfunc.cpv  $
// 
//    Rev 1.2   02 Feb 1996 10:35:02   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.1   06 Feb 1995 16:52:30   HANNES
// 
//    Rev 1.0   24 Jun 1994 17:05:08   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.6   10 Jun 1993 18:46:36   HANNES
// MYINI
// 
//    Rev 1.5   05 Apr 1993 10:28:08   HANNES
// pushDWtoblock
// 
//    Rev 1.4   02 Apr 1993 17:34:48   HANNES
// Strukturbereinigung, Beschleunigung
// 
//    Rev 1.3   17 Mar 1993 17:24:34   HANNES
// CenterPopup
// 
//    Rev 1.2   08 Mar 1993 14:11:42   HANNES
// PushToGlobBlock
// 
//    Rev 1.1   22 Feb 1993 17:08:42   HANNES
// LRString: Initialisieren bei nichterfolg
// 
//    Rev 1.0   02 Dec 1992 15:34:38   HANNES
// Initial revision.
//
// #define DO_PROFILE

#include <windows.h>
#include <stdio.h>
#include "dds32.h"
#include "dds.hpp"
#include "globmem.h"

// 
// Lesen des Profilestrings:
// Als Schluessel wird der String aus der Resource Liste mit nkeyident genommen
// Als Default wird in der String - Resource Liste nachgesehen.
//
void PString (int nkeyident,int ndefStr,char FAR *res,int nSize)
  {
  char DefString[100];
  char szKey[100];
  LRString (nkeyident,szKey,sizeof(szKey));
  LRString (ndefStr,DefString,sizeof(DefString));
  GetProfileString (AppName,szKey,DefString,res,nSize);
  }

// 
// Anhaengen eine Backslash's
// (nur wenn noch keiner am Ende vorhanden ist)
//
void AddBackSlash (char *txt) 
  {
  if (*txt == '\0') *txt = '\\' , *(txt+1) = '\0' ;
  else {
    for ( ; *txt ; ) txt ++ ;
    if (*(txt-1) != '\\') *txt = '\\' , *(txt+1) = '\0' ;
    }
  }

void LRString (int id,char *txt,int size) 
  { 
  *txt = '\0';
  LoadString (WBase::hInstance,id,txt,size) ; 
  }

char *LRString (int id) 
  {  
  LoadString (WBase::hInstance,id,statstrspace,sizeof(statstrspace)); 
  return statstrspace ; 
  }

GLOBALHANDLE PushToGlobBlock (GLOBALHANDLE hGmem,LPVOID data,int size)
  {
  LPSTR Buffer;
  WORD oldsize;
  if (hGmem) {
    Buffer = (LPSTR)GlobalLock (hGmem);
    oldsize = *((WORD FAR *) Buffer);
    }
  else {
    hGmem = GlobalAlloc (GHND,sizeof(WORD));
    Buffer = (LPSTR)GlobalLock (hGmem);
    oldsize = *((WORD FAR *) Buffer) = sizeof(WORD);
    }
  GlobalUnlock (hGmem);
  hGmem = GlobalReAlloc (hGmem,oldsize + size,GHND);
  Buffer = (LPSTR)GlobalLock (hGmem);
  *((WORD FAR *) Buffer) += size;
  lmemcpy (Buffer + oldsize,data,size);
  GlobalUnlock (hGmem);
  return hGmem;
  }

GLOBALHANDLE PushDWToGlobBlock (GLOBALHANDLE hGmem,LPVOID data,DWORD size)
  {
  LPSTR Buffer;
  DWORD oldsize;
  if (hGmem) {
    Buffer = (LPSTR)GlobalLock (hGmem);
    oldsize = *((DWORD FAR *) Buffer);
    }
  else {
    hGmem = GlobalAlloc (GHND,sizeof(DWORD));
    Buffer = (LPSTR)GlobalLock (hGmem);
    oldsize = *((DWORD FAR *) Buffer) = sizeof(DWORD);
    }
  GlobalUnlock (hGmem);
  hGmem = GlobalReAlloc (hGmem,oldsize + size,GHND);
  Buffer = (LPSTR)GlobalLock (hGmem);
  *((DWORD FAR *) Buffer) += size;
  hmemcpy ((char _huge *) Buffer + oldsize,data,size);
  GlobalUnlock (hGmem);
  return hGmem;
  }


BOOL WINAPI CenterPopup(HWND hWnd,HWND hParentWnd)
  {
  /* local variables */
  int      xPopup;
  int      yPopup;
  int      cxPopup;
  int      cyPopup;
  int      cxScreen;
  int      cyScreen;
  int      cxParent;
  int      cyParent;
  RECT     rcWindow;

  /* retrieve main display dimensions */
  cxScreen = GetSystemMetrics( SM_CXSCREEN );
  cyScreen = GetSystemMetrics( SM_CYSCREEN );

  /* retrieve popup rectangle  */
  GetWindowRect( hWnd, (LPRECT)&rcWindow );

  /* calculate popup extents */
  cxPopup = rcWindow.right - rcWindow.left;
  cyPopup = rcWindow.bottom - rcWindow.top;

  /* calculate bounding rectangle */
  if (hParentWnd) {
    /* retrieve parent rectangle */
    GetWindowRect( hParentWnd, (LPRECT)&rcWindow );

    /* calculate parent extents */
    cxParent = rcWindow.right - rcWindow.left;
    cyParent = rcWindow.bottom - rcWindow.top;

    /* center within parent window */
    xPopup = rcWindow.left + ((cxParent - cxPopup)/2);
    yPopup = rcWindow.top + ((cyParent - cyPopup)/2);

    /* adjust popup x-location for screen size */
    if ( xPopup+cxPopup > cxScreen )
       xPopup = cxScreen - cxPopup;

    /* adjust popup y-location for screen size */
    if (yPopup+cyPopup > cyScreen)
      yPopup = cyScreen - cyPopup;
    }
  else {
   /* center within entire screen */
   xPopup = (cxScreen - cxPopup) / 2;
   yPopup = (cyScreen - cyPopup) / 2;
   }

  /* move window to new location & display */
  MoveWindow(hWnd,
             ( xPopup > 0 ) ? xPopup : 0,
             ( yPopup > 0 ) ? yPopup : 0,
             cxPopup,cyPopup,
             TRUE
            );

  /* normal return */
  return( TRUE );
  }

//////////////////////////////////////////////////////////////////////
//  Anzeigen einer Liste aller Segmente
//////////////////////////////////////////////////////////////////////
void ShowMemSegs ()
  {
  }

////////////////////////////////////////////////////////////////////////
//    Funktionsgruppenausblendung zur Entwicklung von Optimierungs-
//    strategien
////////////////////////////////////////////////////////////////////////
#ifdef DO_PROFILE
static int nlstrcmp (LPSTR t1,LPSTR t2)
  {
  for ( ; *t1 && *t2 ; ) {
    if (*t1++ != *t2++) return 1 ;
    }
  return 0;
  }

static BOOL findstr (LPSTR text,LPSTR subtxt)
  {
  LPSTR h = text;
  for ( ; *h ; h++) {
    if (nlstrcmp (h,subtxt) == 0)
      return TRUE ;
    }
  return FALSE ;
  }

static BOOL withFields;
static BOOL withLines;
static BOOL withPatterns;
static BOOL withSetconn;
static BOOL withUpdate;
static BOOL withShow;
extern LPSTR WINAPI GetIniName ();
#ifndef MYINI
  #define MYINI GetIniName ()
#endif
void CheckProfile ()
  {
  static BOOL ProfileRead;
  if (!ProfileRead) {
    char checkstr[512];
    GetPrivateProfileString ("Profile","Check","",
                                checkstr,sizeof(checkstr),
                                MYINI
                            );
    
    withFields = findstr (checkstr,"Fields");
    withLines = findstr (checkstr,"Lines");
    withPatterns = findstr (checkstr,"Patterns");
    withSetconn = findstr (checkstr,"Setconn");
    withUpdate = findstr (checkstr,"Update");
    withShow = findstr (checkstr,"Show");
    ProfileRead = TRUE ;
    }
  }

BOOL UseLines () { CheckProfile (); return withLines ; }
BOOL UseFields () { CheckProfile (); return withFields ; }
BOOL UsePatterns () { CheckProfile (); return withPatterns ; }
BOOL UseSetconn () { CheckProfile (); return withSetconn ; }
BOOL UseShow () { CheckProfile (); return withShow ; }

static long AnzFields;
static long AnzLines;
static long AnzPatterns;
static long AnzShows;
static long AnzSetData;
static long AnzGetData;
static long AnzUpdate;
static long AnzSetConnection;
static long AnzGetKey;

void IncAnzFields ()
  { AnzFields ++ ; }
void IncAnzLines ()
  { AnzLines ++ ; }
void IncAnzPatterns ()
  { AnzPatterns ++ ; }
void IncAnzShows ()
  { AnzShows ++ ; }
void IncAnzSetData ()
  { AnzSetData ++ ; }
void IncAnzGetData ()
  { AnzGetData ++ ; }
void IncAnzUpdate ()
  { AnzUpdate ++ ; }
void IncAnzSetConnection ()
  { AnzSetConnection ++ ; }
void IncAnzGetKey ()
  { AnzGetKey ++ ; }

void ShowAnzFunc ()
  {
  char outtxt[512];
  wsprintf (outtxt,"AnzFields %ld\rAnzLines %ld\rAnzPatterns %ld\rAnzShows %ld\rAnzSetData %ld\rAnzGetData %ld\rAnzUpdate %ld\rAnzSetConnection %ld\rAnzGetKey %ld",
                    AnzFields,
                    AnzLines,
                    AnzPatterns,
                    AnzShows,
                    AnzSetData,
                    AnzGetData,
                    AnzUpdate,
                    AnzSetConnection,
                    AnzGetKey);
  MessageBox (GetActiveWindow(),outtxt,"Funktionsstatistik",MB_OK);
  }
#endif


