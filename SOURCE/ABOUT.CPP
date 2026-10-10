//////////////////////////////////////
//  about.cpp
//////////////////////////////////////
//  for the DentoMedical Workstation
//  Norbert
//  1.12.92
//
// $Header:   P:/marille/clinicum/rev/about.cpv   1.20   12 Apr 2000 22:04:52   Martin  $
// $Log:   P:/marille/clinicum/rev/about.cpv  $
// 
//    Rev 1.20   12 Apr 2000 22:04:52   Martin
// GetProductVersion
// 
//    Rev 1.19   23 Jun 1999 18:05:48   Martin
// GetVersionInfo erweitert um OS-Version
// 
//    Rev 1.18   24 Feb 1999 21:19:00   Hannes
// ClearConnection auf ProfilString
// 
//    Rev 1.17   21 Dec 1998 20:19:38   Martin
// GetSystemPath
// 
//    Rev 1.16   10 Nov 1998 12:54:08   Martin
// GetVersionInfo
// 
//    Rev 1.15   05 Oct 1998 11:53:40   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.14   15 Jul 1998 09:37:06   Gerhold
// Versionsinformation wird jetzt aus der ResourceInfo gelesen
// vorher war die Info in einem INCLUDE
// 
//    Rev 1.13   15 Jun 1998 17:18:02   Martin
// Inifile angebbar
// 
//    Rev 1.12   22 May 1998 10:30:30   Gerhold
// In der ABOUT-Box wird die Product-Version eingetragen
// 
//    Rev 1.11   30 Mar 1998 20:22:10   Martin
// ProfileOverrideBuffer
// 
//    Rev 1.10   06 Aug 1997 10:11:12   gerhold
// Windows-Version und Debug-Version
// 
//    Rev 1.9   04 Apr 1997 15:16:04   Gerhold
// Die Versionsnummern werden mit Unterversionen verwaltet
// 
//    Rev 1.8   10 Jun 1996 10:06:30   GERHOLD
// pragma pack(1)
// 
//    Rev 1.7   02 Feb 1996 10:34:48   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.6   02 Nov 1995 10:34:42   GERHOLD
// ScriptVersion (Funktion, globale Variable und Text in Aboutbox)
// 
//    Rev 1.5   04 Oct 1995 16:02:48   MARTIN
// Clinicum raus
// 
//    Rev 1.4   24 Aug 1995 00:20:04   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.3   20 Mar 1995 11:55:00   HANNES
// Konstantenhanling, RunNmbr...
// 
//    Rev 1.2   09 Dec 1994 20:44:38   GERHOLD
// subclass raus!
// 
//    Rev 1.1   15 Nov 1994 12:12:54   MARTIN
// GetProfileString: optionaler Parameter Translate
// 
//    Rev 1.0   24 Jun 1994 17:04:00   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.9   20 Apr 1994 10:38:16   MARTIN
// DMWS Logo raus
// 
//    Rev 1.8   17 Jan 1994 09:04:22   HANNES
// DMWSVersion als Versionsnummer eingefuehrt
// 
//    Rev 1.7   20 Oct 1993 13:43:38   HANNES
// Neue Lizenz - DLL
// 
//    Rev 1.6   10 Jun 1993 18:34:18   HANNES
// GetOwner beschleunigt (Nur einmal entschluesseln)
// 
//    Rev 1.5   28 May 1993 21:10:32   HANNES
// Bitmaps in's Exe verlagert
// 
//    Rev 1.4   02 Apr 1993 17:29:58   HANNES
// Strukturbereinigung, Beschleunigung
// 
//    Rev 1.3   17 Mar 1993 17:21:10   HANNES
// License Manager
// 
//    Rev 1.2   17 Dec 1992 17:06:58   NORBERT
// "logo.bmp" auf "swlogo.bmp" augebessert
// 
//    Rev 1.1   12 Dec 1992 00:15:14   NORBERT
// added the "dento" bitmap
// 
//    Rev 1.0   02 Dec 1992 15:16:56   HANNES
// Initial revision.
//

#include <windows.h>
#include "dds32.h"
#include "about.h"
#include "stdio.h"

#define MODULENUM 16
#include "dds.hpp"
#include "winass.hpp"
#include "lisencr.hpp"
//#include "subclass.hpp"
#include "globmem.h"
#include "printer.hpp"
#include "sc2d.hpp"
#include "font.hpp"
#include "paint.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "scripthd.hpp"
#include "mdichild.hpp"

#include "hash.hpp"
#include "compile.hpp"

#include "ddsvers.h"

void GetOwner(LPSTR str,int buffsize)
  {
  static char OwnerStr[128];
  if (*OwnerStr == '\0') {
    BOOL res = GetFSBuffer (OwnerStr,sizeof(OwnerStr));
    if (!res)
      lstrcpy (OwnerStr, "??");
    DBWIN_ASSERT (res);
    }
  lstrncpy (str,OwnerStr,buffsize);
  }

#ifdef UEBERLEGT
extern char *DMWSVersion;         // Versionsnummer des EXE-Files
static char FAR *ScriptVersion;   // Versionsnummer des Scripts
#endif

#ifdef UEBERLEGT
static HBITMAP StretchBitmap (GLOBALHANDLE hDIBInfo,int bmHeight,int bmWidth)
  {
  HDC hdc = CreateDC ("DISPLAY",NULL,NULL,NULL);
  HDC hdcMem = CreateCompatibleDC (hdc);

  LPBITMAPINFOHEADER lpbi = LPBITMAPINFOHEADER (GlobalLock (hDIBInfo));

  // Erzeugen eines Bitmaps
//  bmHeight = int ((LONG (bmWidth) * lpbi->biHeight) / lpbi->biWidth) ;
  bmWidth  = int (lpbi->biWidth) ;
  bmHeight = int (lpbi->biHeight) ;

  HBITMAP hBitmap = CreateCompatibleBitmap (hdc,bmWidth,bmHeight);
  SelectObject (hdcMem,hBitmap);

  // Durchfuehren des Stretch's
  //    (!ohne eigene Palette zu Realisieren...)
  SetStretchBltMode (hdcMem,COLORONCOLOR);
  WORD offBits = (WORD) (lpbi->biSize + lpbi->biClrUsed * sizeof(RGBQUAD));
  LPSTR lpbits = LPSTR (lpbi) + offBits;
  StretchDIBits (hdcMem,0,0,bmWidth,bmHeight,
                        0,0,
                        int(lpbi->biWidth),
                        int(lpbi->biHeight),
                        lpbits,
                        LPBITMAPINFO (lpbi),
                        DIB_RGB_COLORS,SRCCOPY
                );

  // Fertig
  DeleteDC (hdcMem);
  DeleteDC (hdc);
  GlobalUnlock (hDIBInfo);

  return hBitmap ;
  }

static BOOL ReadBitmap (HBITMAP FAR *hbm,LPSTR fname,int bmHeight,int bmWidth)
  {
  BOOL res = FALSE ;
  OFSTRUCT of;
  GLOBALHANDLE hDIBInfo = GlobalAlloc (GHND,
                        sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD));
  int fh = OpenFile (fname, &of, OF_READ);
  if (fh == -1) return FALSE ;
  WORD offBits;

  LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER) GlobalLock(hDIBInfo);

  // Lesen des FileHeaders
  BITMAPFILEHEADER bf;
  if (sizeof (bf) != _lread (fh, (LPSTR)&bf, sizeof (bf)))
    goto ErrExit;

  if (bf.bfType != 0x4d42) /* 'BM' */
    goto ErrExit;

  if (sizeof(BITMAPINFOHEADER) != _lread (fh, (LPSTR)lpbi, sizeof(BITMAPINFOHEADER)))
    goto ErrExit;

  /* !!!!! for now, don't even deal with CORE headers */
  if (lpbi->biSize == sizeof(BITMAPCOREHEADER))
    goto ErrExit;

  int nNumColors;
  if (!(nNumColors = (WORD)lpbi->biClrUsed)) {
    /* no color table for 24-bit, default size otherwise */
    if (lpbi->biBitCount != 24)
      nNumColors = 1 << lpbi->biBitCount; /* standard size table */
    }

  /* fill in some default values if they are zero */
  if (lpbi->biClrUsed == 0)
      lpbi->biClrUsed = (DWORD)nNumColors;

  if (lpbi->biSizeImage == 0)
    lpbi->biSizeImage = ((((lpbi->biWidth * (DWORD)lpbi->biBitCount) + 31) 
                      & ~31) >> 3) * lpbi->biHeight;

  /* get a proper-sized buffer for header, color table and bits */ 
  GlobalUnlock(hDIBInfo);
  hDIBInfo = GlobalReAlloc(hDIBInfo, lpbi->biSize +
       nNumColors * sizeof(RGBQUAD) +
    lpbi->biSizeImage, 0);
  if (!hDIBInfo) return FALSE ;

  lpbi = (LPBITMAPINFOHEADER) GlobalLock(hDIBInfo);

  /* read the color table */
  _lread (fh, (LPSTR)(lpbi) + lpbi->biSize, nNumColors * sizeof(RGBQUAD));

  /* offset to the bits from start of DIB header */
  offBits = (WORD)lpbi->biSize + nNumColors * sizeof(RGBQUAD);

  if (bf.bfOffBits != 0L)
    _llseek(fh,bf.bfOffBits,SEEK_SET);

  if (lpbi->biSizeImage == 
        DWORD(_lread(fh, (LPSTR)lpbi + offBits, WORD (lpbi->biSizeImage))))
    res = TRUE;

ErrExit:
  GlobalUnlock(hDIBInfo);
  if (res) {
    // Skalieren der Bitmaps
    *hbm = StretchBitmap (hDIBInfo,bmHeight,bmWidth);
    }

  _lclose(fh);
  GlobalFree (hDIBInfo);

  return res;
  }
#else

static BOOL ReadBitmap (HBITMAP FAR *hbm,LPSTR fname,int bmHeight,int bmWidth)
  {
  *hbm = LoadBitmap (WBase::hInstance,fname);
  return TRUE ;
  }

#endif

static void PaintBitmap (HDC hDC,HBITMAP hBitmap,int x0,int y0)
  {
  HDC hmemDC = CreateCompatibleDC (hDC);
  HBITMAP hOldBmp = (HBITMAP)SelectObject (hmemDC,hBitmap);
  BITMAP bm;
  GetObject (hBitmap,sizeof(bm),&bm);
  BitBlt (hDC,x0,y0,bm.bmWidth,bm.bmHeight,hmemDC,0,0,SRCCOPY);
  SelectObject (hmemDC,hOldBmp);
  DeleteDC (hmemDC);
  }

DLLExport BOOL FAR PASCAL _export AboutDlgProc (HWND hDlg, UINT message, WPARAM wP,
                                                               LPARAM lP)
  {
  static HBITMAP hMyBitmap1;
//     static HBITMAP hMyBitmap2;
  RECT r;
  BOOL res = FALSE;
  switch (message) {
    //-----------------------------------------------------------------
    case WM_INITDIALOG:
      {
      DWORD dwVerInfoSize;
      DWORD dwVerHnd;

      char szFullPath[256];

      // Produktname .............................
      char outstr[128];
      if (!SearchFSItem ("ProduktName",outstr,sizeof(outstr)))
        lstrcpy(outstr,"Clinicum");
      SetDlgItemText(hDlg, PRODUCTNAME, outstr);

      // Version of DentoMedical .................
      //        float version = GetDdsVersion();
      //        sprintf(outstr, "%2.1f", version);
//      wsprintf (outstr, "%s / (%s)", LPSTR(DMWSVersion), LPSTR(ScriptVersion));

//      wsprintf (outstr, "%d.%d", PROGRAM_VERSION, SUB_VERSION);
#ifdef WIN32
      GetModuleFileName (WBase::hInstance, szFullPath, sizeof(szFullPath));
      dwVerInfoSize = GetFileVersionInfoSize (szFullPath, &dwVerHnd);
      if (dwVerInfoSize) {
        HANDLE hMem;
        LPVOID lpvMem;
        LPVOID lszVer = NULL;
        UINT cchVer = 0;
        char szGetName[256];
        BOOL fRet;

        lstrcpy(szGetName, "\\StringFileInfo\\040704E4\\ProductVersion");

        hMem = GlobalAlloc (GMEM_MOVEABLE, dwVerInfoSize);
        lpvMem = GlobalLock (hMem);
        GetFileVersionInfo (szFullPath, dwVerHnd, dwVerInfoSize, lpvMem);
        fRet = VerQueryValue (lpvMem, szGetName, &lszVer, &cchVer);
        if (fRet && cchVer && lszVer)
          lstrcpy (outstr, LPSTR(lszVer));
        GlobalUnlock (hMem);
        GlobalFree (hMem);
        }
#else
      wsprintf (outstr, "%s", PRODUCT_VERSION);
#endif
      SetDlgItemText(hDlg, VERSION, outstr);

      // Name/ID of User .........................
      char userstr[512];
      int buffsize = sizeof(userstr);
      GetOwner(userstr, buffsize);
      SetDlgItemText(hDlg, USER_ID, userstr);

#ifdef WIN32
//      GlobalMemoryStatus
#else
      // System resources ........................
      UINT SysResources = 
      GetFreeSystemResources(GFSR_SYSTEMRESOURCES);
      wsprintf(outstr, "%d", SysResources);
      SetDlgItemText(hDlg, SYSRESOURCES, outstr);
#endif

      // Free Space ..............................
      DWORD FreeSpace = GetFreeSpace(0); // result in Bytes
      sprintf(outstr, "%2.3f", double(FreeSpace)/1024.0/1000.0);
                                           // converted to KB
      SetDlgItemText(hDlg, FREESPACE, outstr);

      // Laden des Bitmaps
      GetClientRect (hDlg,&r);
#ifdef UEBERLEGT
      ReadBitmap (&hMyBitmap1,"swlogo.bmp",r.bottom / 3,r.right / 3);
      // ReadBitmap (&hMyBitmap2,"dento.bmp",r.bottom / 3,r.right / 3);
#else
      ReadBitmap (&hMyBitmap1,"swlogo",r.bottom / 3,r.right / 3);
      // ReadBitmap (&hMyBitmap2,"dento",r.bottom / 3,r.right / 3);
#endif

#ifdef WIN32
      SetDlgItemText(hDlg, WIN_VERSION, "32-Bit");
#else
      SetDlgItemText(hDlg, WIN_VERSION, "16-Bit");
#endif

#ifdef DEBUG
      SetDlgItemText(hDlg, DBG_VERSION, "Debug-Version");
#else
      SetDlgItemText(hDlg, DBG_VERSION, "Release-Version");
#endif


      }
      res = TRUE ;

    //-----------------------------------------------------------------
    case WM_COMMAND:
      {
      CRACKER_VARS
      CRACK_MESSAGEsc

      switch (CRACKER_wID) {
        case IDOK:
        case IDCANCEL:
          DeleteObject (hMyBitmap1);
          // DeleteObject (hMyBitmap2);
          EndDialog (hDlg, 0) ;
          return TRUE ;
        }
      }
      break ;

    //-----------------------------------------------------------------
    case WM_PAINT:
      {
      PAINTSTRUCT ps;
      GetClientRect (hDlg,&r);
      HDC hDC = BeginPaint (hDlg,&ps);
      PaintBitmap (hDC, hMyBitmap1, r.right / 4, r.bottom / 10);
      // PaintBitmap (hDC, hMyBitmap2, (31*r.right)/40, r.bottom / 20);
      EndPaint (hDlg,&ps);
      res = TRUE ;
      }
      break;
    
    }  // end switch()

  return res ;
  }


void ShowAbout (HINSTANCE hInst)
  {
  FARPROC lpfnAboutDlgProc ;
  lpfnAboutDlgProc = MakeProcInstance ((FARPROC) AboutDlgProc,
                                       hInst) ;
  DialogBox (hInst, "AboutBox", WBase::hFrameWin,
                 (DLGPROC)lpfnAboutDlgProc) ;
  FreeProcInstance (lpfnAboutDlgProc);
  }
#pragma pack(1)
struct GetCapStr_param {
  WORD parSize;
  DWORD pattern;
  DWORD res;
  };
#pragma pack()

BOOL GetCapStr (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    GetCapStr_param FAR *par = (GetCapStr_param FAR *) param;
    LPSTR pattern = LPSTR (c->ReadlData (par->pattern));
    DBWIN_ASSERT (pattern != NULL);
    char res[128];
    if (SearchFSItem (pattern,res,sizeof(res)))
      c->WritelData (par->res,res,lstrlen(res)+1,LPSTR(param)-sizeof(WORD));
    else
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }


#pragma pack(1)
struct GetProfileString_param {
  WORD parSize;
  WORD rRec,rId;    // Resultat
  WORD sRec,sId;    // Section
  WORD eRec,eId;    // Entry
  DWORD rTranslate; // interpretieren von '\'s, free
  DWORD OwnProfile; // Art: eigenes Profile(TRUE) oder win.ini (FALSE), free
  WORD fRec,fId;    // wenn angegeben, Filename des .ini files, free
  };
#pragma pack()

void EleminateSZ (LPSTR h)
  {
  LPSTR x1,x2;
  x1 = x2 = h;
  for ( ; *x2 ; ) {
    if (*x2 == '\\') {
      x2 ++ ;
      if (*x2 == 'r') *x1++ = '\r';
      else if (*x2 == 't') *x1++ = '\t';
      else if (*x2 == '\\') *x1++ = '\\';
      x2 ++ ;
      }
    else
      *x1++ = *x2++ ;
    }
  *x1++ = '\0';
  }

BOOL GetProfileString (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    GetProfileString_param FAR *par = (GetProfileString_param FAR *) param;
    char InString[512];
    LPSTR Section = LPSTR (c->ReadData (par->sRec,par->sId));
    LPSTR Entry   = LPSTR (c->ReadData (par->eRec,par->eId));
    DBWIN_ASSERT ((Section != NULL) && (Entry != NULL));
    if ((par->parSize < (sizeof(*par) - sizeof(DWORD))) ||
        (c->ReadConstInt(par->OwnProfile))) {
      if (par->parSize < sizeof(*par)) {
        // in dmw.ini nachsehen
        GetPrivateProfileString (Section,Entry,"",InString,sizeof(InString),
                                 MYINI
                                );
        }
      else {
        // in angegebenem .ini file nachsehen
        LPSTR IniName = LPSTR (c->ReadData (par->fRec,par->fId));
        GetPrivateProfileString (Section,Entry,"",InString,sizeof(InString),
                                 IniName
                                );
        }
      }
    else {
      // in win.ini nachsehen
      GetProfileString (Section,Entry,"",InString,sizeof(InString));
      }
    if ((par->parSize < (sizeof(*par) - (2 * sizeof(DWORD)))) ||
        (c->ReadConstInt(par->rTranslate)))
      EleminateSZ (InString);
    c->WriteData (par->rRec,par->rId,InString,lstrlen(InString)+1,
                    LPSTR(param)-sizeof(WORD),FALSE);
    }
  else {
    GetProfileString_param FAR *par = (GetProfileString_param FAR *) param;
    c->ClearConnection (par->sRec,par->sId,LPSTR(param) - sizeof(WORD));
    c->ClearConnection (par->eRec,par->eId,LPSTR(param) - sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct GetLicense_param {
  WORD parSize;
  DWORD Str;
  };
#pragma pack()

BOOL GetLicense (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    GetLicense_param FAR *par = (GetLicense_param FAR *) param;
    char OwnerName[128];
    GetOwner (OwnerName,sizeof(OwnerName));
    c->WritelData (par->Str,OwnerName,lstrlen(OwnerName)+1,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct Beeps_param {
  WORD parSize;
  DWORD rtype,rcount;
  };
#pragma pack()

BOOL Beeps(mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    Beeps_param FAR *par = (Beeps_param FAR *) param;
    int type = c->ReadConstInt (par->rtype);
    int count = c->ReadConstInt (par->rcount);
    for (int i = 0 ; i < count ; i++)
      MessageBeep (type);
    }
  return FALSE ;
  }

#pragma pack(1)
struct GetVersionInfo_param {
  WORD  parSize;
  DWORD AusliefVersion;
  DWORD DebugVersion;
  DWORD Win32Version;
  DWORD Platform;
  DWORD WinMajorVersion;
  DWORD WinMinorVersion;
  };
#pragma pack()

void GetProductVersion(LPSTR outstr)
  {
  char szFullPath[256];
  DWORD dwVerInfoSize;
  DWORD dwVerHnd;
  GetModuleFileName (WBase::hInstance, szFullPath, sizeof(szFullPath));
  dwVerInfoSize = GetFileVersionInfoSize (szFullPath, &dwVerHnd);
  if (dwVerInfoSize) {
    HANDLE hMem;
    LPVOID lpvMem;
    LPVOID lszVer = NULL;
    UINT cchVer = 0;
    char szGetName[256];
    BOOL fRet;

    lstrcpy(szGetName, "\\StringFileInfo\\040704E4\\ProductVersion");

    hMem = GlobalAlloc (GMEM_MOVEABLE, dwVerInfoSize);
    lpvMem = GlobalLock (hMem);
    GetFileVersionInfo (szFullPath, dwVerHnd, dwVerInfoSize, lpvMem);
    fRet = VerQueryValue (lpvMem, szGetName, &lszVer, &cchVer);
    if (fRet && cchVer && lszVer)
      lstrcpy (outstr, LPSTR(lszVer));
    GlobalUnlock (hMem);
    GlobalFree (hMem);
    }
  else
    wsprintf (outstr, "%s", PRODUCT_VERSION);
  }

BOOL GetVersionInfo (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    GetVersionInfo_param FAR *par = (GetVersionInfo_param FAR *) param;
    char outstr[128];
    GetProductVersion(outstr);
    c->WritelData (par->AusliefVersion,outstr,lstrlen(outstr)+1,LPSTR(param)-sizeof(WORD));
#ifdef DEBUG
    WORD DebugVersion = TRUE;
#else
    WORD DebugVersion = FALSE;
#endif
    c->WritelData (par->DebugVersion,&DebugVersion,sizeof(DebugVersion),LPSTR(param)-sizeof(WORD));
#ifdef WIN32
    WORD Win32Version = TRUE;
#else
    WORD Win32Version = FALSE;
#endif
    c->WritelData (par->Win32Version,&Win32Version,sizeof(Win32Version),LPSTR(param)-sizeof(WORD));
    if (par->parSize >= (sizeof(*par) - (2 * sizeof(DWORD)))) {
      OSVERSIONINFO vi;
      vi.dwOSVersionInfoSize = sizeof(vi);
      GetVersionEx(&vi);
      c->WritelData (par->Platform,&vi.dwPlatformId,sizeof(DWORD),LPSTR(param)-sizeof(WORD));
      if (par->parSize >= (sizeof(*par) - sizeof(DWORD)))
        c->WritelData (par->WinMajorVersion,&vi.dwMajorVersion,sizeof(DWORD),LPSTR(param)-sizeof(WORD));
      if (par->parSize >= sizeof(*par))
        c->WritelData (par->WinMinorVersion,&vi.dwMinorVersion,sizeof(DWORD),LPSTR(param)-sizeof(WORD));
      }
    }

  return FALSE ;
  }

#pragma pack(1)
struct SetProfileOverrideBuffer_param {
  WORD parSize;
  DWORD Priority;
  DWORD Str;
  };
#pragma pack()

BOOL ProfileOverrideBuffer (mdiChild *c,LPVOID param,WORD mode)
  {
  SetProfileOverrideBuffer_param FAR *par = (SetProfileOverrideBuffer_param FAR *) param;
  if (mode & EM_LOAD) {
    LPSTR buffer = LPSTR (c->ReadlData (par->Str));
    LPWORD lppriority = LPWORD (c->ReadlData (par->Priority));
    DBWIN_ASSERT(lppriority != NULL);
    AddProfileOverrideBuffer(*lppriority,buffer);
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    LPWORD lppriority = LPWORD (c->ReadlData (par->Priority));
    DBWIN_ASSERT(lppriority != NULL);
    RemoveProfileOverrideBuffer(*lppriority);
    }
  return FALSE ;
  }

#pragma pack(1)
struct GetSystemPath_param {
  WORD  parSize;
  DWORD Type;
  DWORD Path;
  };
#pragma pack()

extern DLLExport LPSTR _export WINAPI GetExePath (void);
BOOL GetSystemPath (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    GetSystemPath_param FAR *par = (GetSystemPath_param FAR *) param;
    LPWORD lpType = LPWORD (c->ReadlData (par->Type));
    DBWIN_ASSERT_TEXT(lpType != NULL,"GetSystemPath: no type specified !");
    char szFullPath[256];
    *szFullPath = '\0';
    switch (*lpType) {
      case 0:  // EXE-Pfad
        lstrcpy(szFullPath,GetExePath());
        break;
      case 1:  // INI-Pfad
        {
        lstrcpy(szFullPath,GetIniName());
        int i = lstrlen(szFullPath);
        for ( ; (i > 0) &&
               (szFullPath[i] != '\\') &&
               (szFullPath[i] != '/') &&
               (szFullPath[i] != ':'); i--);
        if (i > 0)
          szFullPath[i+1] = '\0';
        else
          *szFullPath = '\0';
        }
        break;
      case 2:  // aktueller Pfad
        GetCurrentDirectory(sizeof(szFullPath),szFullPath);
        break;
      case 3:  // Windows-Pfad
        GetWindowsDirectory(szFullPath,sizeof(szFullPath));
        break;
      case 4:  // System-Pfad
        GetSystemDirectory(szFullPath,sizeof(szFullPath));
        break;
      default:
        DBWIN_ASSERT_TEXT(FALSE,"GetSystemPath: unknown type specified !");
      }
    int len = lstrlen(szFullPath);
    if ((len > 0) && (szFullPath[len-1] != '\\')) {
      szFullPath[len++] = '\\';
      szFullPath[len] = '\0';
      }
    c->WritelData (par->Path,szFullPath,len+1,LPSTR(param)-sizeof(WORD));
    }

  return FALSE ;
  }

