// $Header:   P:/marille/clinicum/ddsmem/rev/ddsmem.cpv   1.7   26 Feb 1999 17:38:28   Wolfgang  $
// $Log:   P:/marille/clinicum/ddsmem/rev/ddsmem.cpv  $
// 
//    Rev 1.7   26 Feb 1999 17:38:28   Wolfgang
// 1.) Auch debugforms-Verzeichnis durchsuchen.
// 2.) GetIncludeFileName liefert BOOL zurueck.
// 
//    Rev 1.6   17 Feb 1999 18:44:56   Martin
// FindClose bei rekursivem DirectoryTree-Aufruf
// 
//    Rev 1.5   05 Oct 1998 11:10:18   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.4   15 Aug 1998 18:15:14   Hannes
// GetIncludefilename
// 
//    Rev 1.3   05 Dec 1997 17:47:34   Hannes
// 
//    Rev 1.2   05 May 1997 12:24:36   Hannes
// 
//    Rev 1.1   21 Oct 1996 18:52:30   HANNES
// Pfade auch fuer Debugfiles
// 
//    Rev 1.0   04 Feb 1996 15:24:40   GERHOLD
// Initial revision.
#include <windows.h>
#include <dos.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "dds32.h"
#include "dds.h"
#define NODDSDATA
#include "dds.hpp"
#include "globmem.h"
#include "hash.hpp"
#define NOCOMPILE
#include "compile.hpp"
#define MODULENUM 139
#include "winass.hpp"

HINSTANCE MyInstance;

#define STATISTICS

//---------------------------  LogMsg  --------------------------------------
//
// Schreiben von Fehlermeldungen in eine Datei
//---------------------------------------------------------------------------
DLLExport void _export WINAPI LogMsg (LPSTR txt,LPSTR fName)
  {
  static BOOL bFirstCall = TRUE;

  OFSTRUCT Of;
  static char *_fname = "COMPILE.ERR";
  LPSTR fname;
  if (fName != NULL)
    fname = fName ;
  else
    fname = _fname ;
  HFILE f = OpenFile (fname,&Of,OF_EXIST);
  if (f == HFILE_ERROR)
    f = OpenFile (fname,&Of,OF_CREATE);
  else {
    f = OpenFile (fname,&Of,OF_READWRITE);
    _llseek (f,0L,SEEK_END);
    }
  if (f >= 0) {
    char logstr[200];
    //------------------------------------------------------------------
    // nur beim ersten mal innerhalb eines Uebersetzungsvorganges werden
    // Datum und Uhrzeit in die Datei geschrieben
    if (bFirstCall) {
      static char date[64],time[64];
      
      _strdate (date);
      _strtime (time);
      wsprintf (logstr,"\r\n\r\n%s, %s\r\n",LPSTR(date),LPSTR(time));
      _lwrite (f,logstr,lstrlen(logstr));

      bFirstCall = FALSE;
      }
      
    if (txt != NULL)
      wsprintf (logstr, "%s\r\n", txt);
    
    _lwrite (f,logstr,lstrlen(logstr));
    _lclose (f);
    }
  else
    MessageBeep (0);
  }

BOOL DirectoryTree (LPSTR name,LPSTR Path,LPSTR Buffer)
  {
  // 1. Untersuchen, ob im Directory
  OFSTRUCT Of;
  lstrcpy (Buffer,Path);
  lstrcat (Buffer,name);
  int fi = OpenFile (Buffer,&Of,OF_EXIST);
  if (fi > 0) {
    return TRUE ;
    }
  else {
    static char Buffer1static[256];

#ifndef WIN32
    static _find_t ftstatic;
    struct _find_t ft;
#endif

    char Buffer1[256];
    lstrcpy (Buffer1,Path);
    lstrcat (Buffer1,"*");
    lstrcpy (Buffer1static,Buffer1);

#ifdef WIN32
    WIN32_FIND_DATA  FileData, FileDataStatic;
    HANDLE           hSearch;
    BOOL             bFinished = FALSE;

    hSearch = FindFirstFile (Buffer1static, &FileDataStatic);
    if (hSearch != INVALID_HANDLE_VALUE) {
      FileData = FileDataStatic;
      while (!bFinished) {
        if ((*FileData.cFileName != '.') && 
            (FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
          lstrcpy(Buffer1,Path);
          lstrcat(Buffer1,FileData.cFileName);
          lstrcat(Buffer1,"\\");
          if (DirectoryTree(name,Buffer1,Buffer)) {
            FindClose (hSearch);
            return TRUE ;      /* recursive call */
            }
          }

        FileDataStatic = FileData;
        if (!FindNextFile(hSearch, &FileDataStatic))
          bFinished = TRUE;
        FileData = FileDataStatic;
        }

      FindClose (hSearch);
      }

#else

    int st = _dos_findfirst(Buffer1static, _A_SUBDIR, &ftstatic);
    ft = ftstatic;
    while (st == 0) {
      if ((*ft.name != '.') && ((ft.attrib & _A_SUBDIR) == _A_SUBDIR)) {
        lstrcpy(Buffer1,Path);
        lstrcat(Buffer1,ft.name);
        lstrcat(Buffer1,"\\");
        if (DirectoryTree(name,Buffer1,Buffer))
          return TRUE ;      /* recursive call */
        }
      ftstatic = ft;
      st = _dos_findnext(&ftstatic);
      ft = ftstatic;
      }
#endif

    }
  return FALSE ;
  }

DLLExport BOOL _export WINAPI GetIncludeFileName (LPSTR name,LPSTR NamBuffer,LPSTR finame,LPSTR Item)
  {
  // Untersuchung, ob '\"' wirklich weggeschnitten wurden
  BOOL therewasaquote = FALSE;
  for (LPSTR h = name ; *h ; h++) {
    if (*h == '"') {
      *h = '\0' ;
      therewasaquote = TRUE ;
      break ;
      }
    }
  lstrcpy (finame,name);
  lstrcpy (NamBuffer,name);

  if (therewasaquote)
    *h = '"';     // Anfuehrungszeichen wieder einfuegen

  // Mal sehen, ob im ini File etwas steht
  char Item0[32],Item1[32];
  if (Item != NULL) {
    lstrcpy (Item0,Item);
    lstrcpy (Item1,Item);
    lstrcat (Item1,"1");
    }
  else {
    lstrcpy (Item0,INCLUDE);
    lstrcpy (Item1,INCLUDE1);
    }
  char path[128];
  BOOL res = FALSE ;
  if (GetPrivateProfileString (SCRIPTSECTION,Item0,INCLUDEDEF,
                           path,128,
                           MYINI
                              ) > 0)
    res = DirectoryTree (finame,path,NamBuffer);
  if ((!res) && (GetPrivateProfileString (SCRIPTSECTION,Item1,INCLUDEDEF,
                               path,128,
                               MYINI
                           ) > 0))
    res = DirectoryTree (finame,path,NamBuffer);
  return res;
  }

DLLExport void _export WINAPI GetDebugFileName (LPSTR name,LPSTR NamBuffer,LPSTR finame)
  {
  // Untersuchung, ob '\"' wirklich weggeschnitten wurden
  BOOL therewasaquote = FALSE;
  for (LPSTR h = name ; *h ; h++) {
    if (*h == '"') {
      *h = '\0' ;
      therewasaquote = TRUE ;
      break ;
      }
    }
  lstrcpy (finame,name);
  lstrcpy (NamBuffer,name);

  if (therewasaquote)
    *h = '"';     // Anfuehrungszeichen wieder einfuegen

  // Mal sehen, ob im ini File etwas steht
  char path[128];
  BOOL res = FALSE ;
  if (GetPrivateProfileString (SCRIPTSECTION,DEBUGENT,DEBUGDEF,
                           path,128,
                           MYINI
                              ) > 0)
    res = DirectoryTree (finame,path,NamBuffer);
  if ((!res) && (GetPrivateProfileString (SCRIPTSECTION,DEBUG1ENT,DEBUGDEF,
                               path,128,
                               MYINI
                           ) > 0))
    res = DirectoryTree (finame,path,NamBuffer);
  if ((!res) && (GetPrivateProfileString (SCRIPTSECTION,DEBUGFORMSENT,DEBUGDEF,
                               path,128,
                               MYINI
                           ) > 0))
    res = DirectoryTree (finame,path,NamBuffer);
  }

///////////////////////////////////////////////////////////////////////
//      Initialisieren der DLL
///////////////////////////////////////////////////////////////////////
#ifdef STATISTICS
extern void WriteSizeStat ();
#endif

extern void InitializeLinMem (HINSTANCE);
//---------------------------------------------------------------------------
//
// Einsprungspunkte fuer die DLL
//
//---------------------------------------------------------------------------
// 32-Bit Version
//---------------------------------------------------------------------------
#ifdef WIN32
BOOL WINAPI DllMain (HINSTANCE hModule, DWORD fdwReason, LPVOID lpReserved)
  {
  switch (fdwReason) {
    case DLL_PROCESS_ATTACH:
      MyInstance = hModule;
      InitializeLinMem (MyInstance);
      break;

    case DLL_THREAD_ATTACH:
      break;

    case DLL_THREAD_DETACH:
      break;

    case DLL_PROCESS_DETACH:
      break;

    }

  return TRUE;
  }

#else
//---------------------------------------------------------------------------
// 16-Bit Version
//---------------------------------------------------------------------------
int WINAPI WEP (int nShutdownFlag)
  {
  return 1 ;
  }

extern "C" {
int WINAPI LibMain (HANDLE hInstance,WORD wDataSeg, WORD wHeapSize,
                        LPSTR lpszCmdLine)
  {
  MyInstance = hInstance;

  if (wHeapSize > 0)
    LocalInit (wDataSeg,NULL,wHeapSize);

  InitializeLinMem (MyInstance);

  return 1 ;
  }
}

#endif

