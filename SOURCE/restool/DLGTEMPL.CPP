///////////////////////////////////////////////////////
//  Anzeige einer Dialog-Box zur Auswahl von Templates
///////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/restool/rev/dlgtempl.cpv   1.14   15 Jun 1999 16:28:34   WOLFGANG  $
//  $Log:   P:/marille/clinicum/restool/rev/dlgtempl.cpv  $
// 
//    Rev 1.14   15 Jun 1999 16:28:34   WOLFGANG
// 1.) Now ohne Parameter verwenden.
// 
//    Rev 1.13   15 Mar 1999 14:38:30   Wolfgang
// 1.) %D% fuer Datum, %T% fuer Zeit und %$varname% fuer Environmentvariablen
//     eingebaut.
// 
//    Rev 1.12   05 Mar 1999 16:16:12   Wolfgang
// 1.) Templates fuer 32Bit aktiviert.
// 2.) Suche nach Templates in [Script] template und template1.
// 3.) Preview (Bitmap) auch bei Oeffnen.
// 
//    Rev 1.11   05 Oct 1998 11:25:42   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.10   05 Nov 1997 10:01:58   Gerhold
// #include compile.hpp
// 
//    Rev 1.9   05 Nov 1997 09:49:24   Gerhold
// 32 Bit
// 
//    Rev 1.7   02 Feb 1996 10:50:18   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.6   27 Aug 1995 13:00:24   HANNES
// 
//    Rev 1.5   07 Aug 1995 14:25:06   GERHOLD
// Nach "begin" und "procedure" case-Sensitive suchen
// 
//    Rev 1.4   07 Jun 1995 12:11:16   GERHOLD
// Hintergrund der Preview-Bitmaps wird jetzt immer geloescht
// 
//    Rev 1.3   15 May 1995 08:29:40   HANNES
// Versuche der besseren Invalidierung
// 
//    Rev 1.2   26 Apr 1995 15:26:20   HANNES
// 
//    Rev 1.1   25 Apr 1995 14:32:42   GERHOLD
// 
//    Rev 1.0   24 Apr 1995 15:42:56   GERHOLD
// Initial revision.
///////////////////////////////////////////////////////
#include <windows.h>
#include <dos.h>
#include <stdio.h>
#include <memory.h>
#include "dds32.h"

#include "globmem.h"
#include "hash.hpp"
#include "restool.hpp"
#include "resid.h"
#include "wonscrip.hpp"

#define NODDSDATA
#include "dds.hpp"

#include "dlgtempl.hpp"
#include "compile.hpp"


extern HINSTANCE MyInstance;

struct DialogTemplate;
typedef DialogTemplate FAR* LPDIALOGTEMPLATE;

struct DialogTemplate {
  LPDIALOGTEMPLATE Next;
  
  char  szFileName[256];
  char  szTemplateName[64];
  LPSTR lpszDescription;
  char  szBitmapName[256];
  };

LPDIALOGTEMPLATE FirstTemplate, CurrentTemplate;


inline BOOL mystrcmp (LPSTR ltxt,LPSTR stxt)
  {
  for ( ; ((*ltxt) && (*stxt) && (*stxt == *ltxt)) ; stxt ++ , ltxt ++ ) ;
  return (*stxt == '\0');
  }

#define  STARTID  100
#define  MAXID    100

int      AnzSubstitutes = 0;

//------------------------  GetTemplateString  ------------------------------
//
// Liest einen Text der zwischen Anfuehrungszeichen steht
//---------------------------------------------------------------------------
LPSTR GetTemplateString (LPSTR lpszText, LPSTR lpszResult)
  {
  lpszResult[0] = '\0';
  if (lpszText == NULL)
    return NULL;
  
  LPSTR p = lpszText;  
  int i = 0;
  for ( ; *p && (*p != '"'); i++, p++);  // bis zum ersten <"> lesen

  if (*p == '\0')
    return NULL;
    
  // bis zum naechsten <"> lesen
  lpszText = ++p;
  for (i++ ; *lpszText && (*lpszText != '"'); i++, lpszText++);
  lpszText++;
  
  lmemcpy (lpszResult, p, lpszText - 1 - p);
  lpszResult[lpszText - 1 - p] = '\0';
  
  return lpszText;
  }

//------------------------  GetTemplateInfo  --------------------------------
//
// liest die Template-Eigenschaften fuer die Dialog-Box
// (Kurzbeschreibung, genaue Beschreibung, Preview-Bitmap)
//---------------------------------------------------------------------------
void GetTemplateInfo (LPSTR pathName, LPSTR FileName)
  {
  OFSTRUCT of;
  char szBuf[1024];
  char fileNameBuf[256];
  lstrcpy (fileNameBuf, pathName);
  lstrcat (fileNameBuf, FileName);
  
  HFILE hFile = OpenFile (fileNameBuf, &of, OF_READ);
  if (hFile == HFILE_ERROR)
    return;
    
  UINT cbRead = _lread (hFile, szBuf, sizeof(szBuf));
  _lclose (hFile);

  LPDIALOGTEMPLATE lpTempl = (LPDIALOGTEMPLATE)GetGlobMem (sizeof(DialogTemplate));
  if (lpTempl != NULL) {
    lstrcpy (lpTempl->szFileName, fileNameBuf);
    LPSTR lpBuf = GetTemplateString (szBuf, lpTempl->szTemplateName);

    char szTemp[1024];
    lpBuf = GetTemplateString (lpBuf, szTemp);
    lpTempl->lpszDescription = (LPSTR)GetGlobMem (lstrlen(szTemp)+1);
    lstrcpy (lpTempl->lpszDescription, szTemp);

    lpBuf = GetTemplateString (lpBuf, fileNameBuf);
    lstrcpy (lpTempl->szBitmapName, pathName);
    lstrcat (lpTempl->szBitmapName, fileNameBuf);
    
    lpTempl->Next = NULL;

    if (FirstTemplate == NULL)
      FirstTemplate = lpTempl;
    else {
      for (LPDIALOGTEMPLATE lptpl = FirstTemplate; lptpl->Next != NULL; lptpl = lptpl->Next);
      lptpl->Next = lpTempl;
      }
    }
  
  }


//------------------------  FreeTemplateInfo  -------------------------------
//
//---------------------------------------------------------------------------
void FAR PASCAL FreeTemplateInfo ()
  {
  LPDIALOGTEMPLATE lpNext = NULL;
  for (LPDIALOGTEMPLATE lptpl = FirstTemplate; lptpl != NULL; ) {
    if (lptpl->lpszDescription != NULL)
      FreeGlobMem (lptpl->lpszDescription);

    lpNext = lptpl->Next;
    FreeGlobMem (lptpl);
    if (lpNext == NULL)
      break;
    lptpl = lpNext;
    }
  }


inline int AnzTemplates ()
  {
  int i = 0;
  for (LPDIALOGTEMPLATE p = FirstTemplate; (p != NULL) && (p->Next != NULL); p = p->Next, i++);
    
  return i;
  }

//------------------------  GetTemplateText  --------------------------------
//
// Liest aus <lpszText> Zeichen bis zum ersten Auftreten von CR-LF
// (entspricht einem ReadLn aus einer Text-Datei)
//---------------------------------------------------------------------------
LPSTR GetTemplateText (LPSTR lpszText, LPSTR lpszResult)
  {
  lpszResult[0] = '\0';
  if (lpszText == NULL)
    return NULL;
  
  LPSTR p = lpszResult;  

  for ( ; *lpszText && ((*lpszText != '\r') && (*lpszText != '\n')); )
    *p ++ = *lpszText++ ;
  *p = '\0';

  if (*lpszText == '\r') lpszText++  ;
  if (*lpszText == '\n') lpszText++  ;
  
  return lpszText;
  }

 

#define  ENQUIRE      "#ENQUIRE"
#define  TEMPLATE     "#TEMPLATE"
#define  PROCEDURE    "#PROCEDURES"
#define  PROCSTART    "procedure"
#define  BEGINSTART   "begin"

#define FNTHNUM   16
#define FNTHDENUM 10
//----------------------  ExtractEnquire  -----------------------------------
//
// Extrahiert die Texte, die als Beschreibung vor den Eingabe-Feldern stehen.
//---------------------------------------------------------------------------
#define MAXANZENQ 25
BOOL ExtractEnquire (LPSTR lpszBuf, DlgContainer FAR *dc)
  {
  BOOL bFound = FALSE;
  for ( ; *lpszBuf ; lpszBuf++)
    if (mystrcmp(lpszBuf, ENQUIRE)) {
      lpszBuf += (lstrlen(ENQUIRE) + 2);  // \r\n!!
//      MessageBeep (0);
      bFound = TRUE;
      break;
      }
  
  LPSTR lpBuf = lpszBuf;
  char szStatic[64], szEdit[64],szText[128];
  int y = 10;

  int h = 12;
  if (bFound) {
    int ID = STARTID;
    AnzSubstitutes = 0;
    do {
      lpBuf = GetTemplateText (lpBuf, szText);
      LPSTR p = GetTemplateString (szText, szStatic);
      p = GetTemplateString (p, szEdit);

      if (szStatic[0] != '\0') {

        DWORD dwStyle;
        if (AnzSubstitutes > MAXANZENQ - 1)
          dwStyle = WS_CHILD;
        else
          dwStyle = WS_VISIBLE | WS_CHILD;

        *dc += ControlData (8,y,52,8,WORD(-1),dwStyle, 0x82,szStatic);

        if (AnzSubstitutes > MAXANZENQ - 1)
          dwStyle = WS_TABSTOP | WS_GROUP | ES_LEFT | 
                          ES_AUTOHSCROLL | WS_CHILD | WS_BORDER | WS_DISABLED;
        else  
          dwStyle = WS_TABSTOP | WS_GROUP | ES_LEFT | 
                          ES_AUTOHSCROLL | WS_VISIBLE | WS_CHILD | 
                          WS_BORDER;
                          
        *dc += ControlData (73, y-2, 82, h, ID, dwStyle, 0x81, szEdit);

        y += (h + 2);
        ID++;
        AnzSubstitutes++;
        }
      }
    while (*lpBuf != '#');
    }

  return bFound;
  }


//------------------------  SubstituteTextInTemplate  -----------------------
//
// sucht alle Zeichenfolgen <%num%> und ersetzt diese durch die Substitute.
//---------------------------------------------------------------------------
void SubstituteTextInTemplate (LPSTR dest, LPSTR lpText, LPSTR FAR * Substitutes, int anzSubstitutes)
  {
  LPSTR lpstr = lpText;
  *dest = '\0';
  packdate pd;
  packtime pt;
  INTTIME ts = Now ();
  UnPackTime (ts, &pd);
  UnPackSeconds (ts, &pt);
  for ( ; *lpstr ; ) {
    for ( ; *lpstr && (*lpstr != '%'); )
      *dest++ = *lpstr++ ; // erstes Prozent-Zeichen + Kopieren
    if (*lpstr && (*lpstr == '%') && (*(lpstr+1) != '%')) {
      char szBuf[40];
      int ID;
    
      // Template-Nummer zwischen den Prozent-Zeichen extrahieren
      lpstr++;
    
      LPSTR p = lpstr;
      for ( ; *lpstr && (*lpstr != '%'); lpstr++);  // abschliessendes Prozent
      lmemcpy (szBuf, p, lpstr-p);
      szBuf[lpstr-p] = '\0';
      if (strcmp (szBuf, "D") == 0) {
        char datum[11];
        FormatDate (datum, &pd, "dd.mm.yyyy");
        lstrcpy (dest, datum);                      // Aktuelles Datum einfuegen
        dest += lstrlen (dest);                     // an das Ende zeigen
        }
      else if (strcmp (szBuf, "T") == 0) {
        char zeit[9];
        writeTimeStr (zeit, 0, &pt);
        lstrcpy (dest, zeit);                       // Aktuelle Zeit einfuegen
        dest += lstrlen (dest);                     // an das Ende zeigen
        }
      else if (*szBuf == '$') {
        char *envvar = getenv (szBuf + 1);
        if (envvar) {
          lstrcpy (dest, envvar);                   // Environment Variable einfuegen
          dest += lstrlen (dest);                   // an das Ende zeigen
          }
        }
      else if (scint(szBuf, &ID) && (ID <= anzSubstitutes)) {
        lstrcpy (dest, Substitutes[ID-1]);          // Text einfuegen
        dest += lstrlen (dest);                     // an das Ende zeigen
        }
      if (*lpstr) lpstr++;                          // Prozent ueberlesen
      }
    else if (*lpstr && (*lpstr == '%') && (*(lpstr+1) == '%')) {
      lpstr ++ ;
      *dest ++ = *lpstr ++ ;
      }
    }
  *dest = '\0';
  }

//------------------------  ExtractProcedures  ------------------------------
//
//---------------------------------------------------------------------------
BOOL IsKeyWord (LPSTR Text)
  {
  return ((mystrcmp (Text,PROCEDURE)) ||
          (mystrcmp (Text,TEMPLATE)) ||
          (mystrcmp (Text,ENQUIRE))) ;
  }

void ExtractProcedures (LPSTR lpszBuf, LPSTR FAR *Substitutes, int anzSubstitutes)
  {
  // sucht das Vorkommen des Textes TEMPLATE
  BOOL bFound = FALSE;
  for ( ; *lpszBuf ; lpszBuf++)
    if (mystrcmp(lpszBuf, PROCEDURE)) {
      lpszBuf += (lstrlen(PROCEDURE) + 2);  // \r\n!!
      bFound = TRUE;
      break;
      }

  LPSTR lpBuf = lpszBuf;
  char szStatic[2048];  // sehr lange Eintraege moeglich

  if (bFound) {
    //---------------------------------------------------------------------
    // zuerst suchen (case-Sensitive!!), ob zwischen einem begin-end-Block, 
    // wenn nicht dann suchen ob zwischen einem procedure-endproc-Block.
    // Nach gelungener Suche jeweils vor den Zeilen mit den beiden 
    // Schluesselwoertern einfuegen.
    //---------------------------------------------------------------------
    bFound = SearchTextInScript ("begin", FALSE, FALSE);
    if (!bFound)
      bFound = SearchTextInScript ("procedure", FALSE, FALSE);
    if (bFound) {  
      int i = 0;
      while (*lpBuf && !IsKeyWord (lpBuf)) {
        char destLine[2048];
        lpBuf = GetTemplateText (lpBuf, szStatic);  // eine Zeile auslesen
        SubstituteTextInTemplate (destLine, szStatic, Substitutes, anzSubstitutes);
        
        lstrcat (destLine, "\r\n");
        InsertTextIntoScript (destLine);
        }
      }
    }
  }

//------------------------  ExtractTemplates  -------------------------------
//
// Wird beim Schliessen des Template-Dialoges aufgerufen
// Parameter : lpszBuf ... Zeiger auf den gesamten Text aus der Datei
//---------------------------------------------------------------------------
void ExtractTemplates (LPSTR lpszBuf, LPSTR FAR* Substitutes, int anzSubstitutes)
  {
  // sucht das Vorkommen des Textes TEMPLATE
  BOOL bFound = FALSE;
  for ( ; *lpszBuf ; lpszBuf++)
    if (mystrcmp(lpszBuf, TEMPLATE)) {
      lpszBuf += (lstrlen(TEMPLATE) + 2);  // \r\n!!
      bFound = TRUE;
      break;
      }

  LPSTR lpBuf = lpszBuf;
  char szStatic[2048];  // sehr lange Eintraege moeglich

  if (bFound) {
    int i = 0;
    while (*lpBuf && !IsKeyWord (lpBuf)) {
      char destLine[2048];
      lpBuf = GetTemplateText (lpBuf, szStatic);  // eine Zeile auslesen
      SubstituteTextInTemplate (destLine, szStatic, Substitutes, anzSubstitutes);
      
      lstrcat (destLine, "\r\n");
      InsertTextIntoScript (destLine);
      }
    }

  ExtractProcedures (lpszBuf, Substitutes, anzSubstitutes);
  }


//------------------------  GetSubstitutes  ---------------------------------
//
// Liest aus den Eingabe-Feldern die Ersetzungstexte
//---------------------------------------------------------------------------
void GetSubstitutes (HWND hWnd, LPSTR FAR* Substitutes, int anzSubstitutes)
  {
  int ID = STARTID;
  
  char szBuf[64];
  for (int i = 0 ; i < anzSubstitutes; i++) {
    GetDlgItemText (hWnd, ID+i, szBuf, sizeof(szBuf));
    Substitutes[i] = LPSTR(GetGlobMem(lstrlen(szBuf)+1));
    lstrcpy(Substitutes[i], szBuf);
    }
  }


DLLExport BOOL _export FAR PASCAL DlgScriptTemplateProc (HWND hDlg, unsigned msg, WORD wP, LONG lP)
  {
  BOOL ret = FALSE;

  LPSTR lpszBuf = (LPSTR)GetWindowLong(hDlg, DWL_USER);

  switch (msg) {
    case WM_INITDIALOG :
      {
      SetWindowLong (hDlg, DWL_USER, LONG(LPSTR(lP)));

      int cy;
      if (AnzSubstitutes < MAXANZENQ) {
        if (AnzSubstitutes < 3)
          cy = (12 + 2) * 3 + 10;
        else  
          cy = (12 + 2) * AnzSubstitutes + 10;
        }
      else 
        cy = (12 + 2) * MAXANZENQ + 10;

      RECT rc;
      SetRect (&rc, 0, 0, 0, cy);
      MapDialogRect (hDlg, &rc);
      cy = rc.bottom;
      
      GetWindowRect (hDlg, &rc);
      cy += (GetSystemMetrics (SM_CYCAPTION) + 2*GetSystemMetrics(SM_CYDLGFRAME));
      MoveWindow (hDlg, rc.left, rc.top, rc.right-rc.left, cy, TRUE);
//      SetWindowPos (hDlg, 0, 
      }
      return TRUE;

    case WM_COMMAND :
      CRACKER_VARS
      CRACK_MESSAGEsc

      switch (CRACKER_wID) {
        case IDOK :
          {
          if (lpszBuf) {
            LPSTR Substitutes[MAXID];        // 100 Ersetzungen sind wohl genug!
            
            lmemset (Substitutes, NULL, sizeof(LPSTR)*MAXID);
            GetSubstitutes (hDlg, Substitutes, AnzSubstitutes);
            ExtractTemplates (lpszBuf, Substitutes, AnzSubstitutes);
//            FreeGlobMem (lpszBuf);
            
            for (int i = 0; i < MAXID; i++)
              if (Substitutes[i] != NULL)
                FreeGlobMem (Substitutes[i]);

//            FreeTemplateInfo ();
//            FreeGlobMem (lpszBuf);
            }

          EndDialog (hDlg, CRACKER_wID);
          }
          break;
          
        case IDCANCEL :
          EndDialog (hDlg, CRACKER_wID);
          break;
        }  
        
      break;
      }
  return ret;    
  }


//----------------------  GetValuesForTemplate  -----------------------------
//
//
//---------------------------------------------------------------------------
void GetValuesForTemplate (HWND hWndParent)
  {
  if (CurrentTemplate == NULL)
    return;

  OFSTRUCT of;
      
  // den ganzen Wurschtel aus der Datei lesen
  HFILE hFile = OpenFile (LPSTR(CurrentTemplate->szFileName), &of, OF_READ);
  if (hFile == HFILE_ERROR)
    return;
      
  LONG lFileLen = _llseek (hFile, 0, 2);  // Dateilaenge bestimmen
  _llseek (hFile, 0, 0);  // wieder an den Anfang
      
  LPSTR lpszBuf = (LPSTR)GetGlobMem(UINT(lFileLen + 1));
    
  UINT cbRead = _lread (hFile, lpszBuf, UINT(lFileLen));
  _lclose (hFile);
  

  DialogBoxHeader dbh (WS_DLGFRAME | DS_MODALFRAME | WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_CLIPSIBLINGS,
                     18,18,227,93,"Template",10,"Arial");
  DlgContainer dc (dbh);

  if (ExtractEnquire (lpszBuf, &dc)) { // die Editfelder + Static bestimmen
    dc += ControlData (180,8,32,14,IDOK,WS_GROUP | BS_PUSHBUTTON | WS_TABSTOP | WS_VISIBLE | WS_CHILD,0x80,
                       "Ok");
    dc += ControlData (180,24,32,14,IDCANCEL,WS_GROUP | BS_PUSHBUTTON | WS_TABSTOP | WS_VISIBLE | WS_CHILD,0x80,
                       "Abbruch");
#ifdef WIN32
    LPDLGTEMPLATE lpTemplate = (LPDLGTEMPLATE)GlobalLock (dc.res);
    DialogBoxIndirectParam (MyInstance, lpTemplate, hWndParent, DLGPROC(DlgScriptTemplateProc), LPARAM(lpszBuf));
    GlobalUnlock (dc.res);
#else
    DialogBoxIndirectParam (MyInstance, dc.res, hWndParent, DLGPROC(DlgScriptTemplateProc), LPARAM(lpszBuf));
#endif
    }
  else {
    // Keine Eingaben notwendig ==> gleich einfuegen
    ExtractTemplates (lpszBuf, NULL, 0);
    }
    
  if (lpszBuf) {
    FreeTemplateInfo ();
    FreeGlobMem (lpszBuf);
    }  

  }



//***************************************************************************
//*                                                                         *
//* Prozeduren fuer das Zeichnen und Bearbeiten des Template-Dialogs        *
//*                                                                         *
//***************************************************************************


//------------------------  PaintBitmap  ------------------------------------
//
//---------------------------------------------------------------------------
static HBITMAP PaintBitmap (HWND hWnd, GLOBALHANDLE hDIBInfo, int cx, int cy)
  {
  HDC hdc = GetDC (hWnd);
  HDC hdcMem = CreateCompatibleDC (hdc);

  LPBITMAPINFOHEADER lpbi = LPBITMAPINFOHEADER (GlobalLock (hDIBInfo));

  int bmWidth  = int (lpbi->biWidth) ;
  int bmHeight = int (lpbi->biHeight) ;

  HBITMAP hBitmap = CreateCompatibleBitmap (hdc,bmWidth,bmHeight);
  
  WORD offBits = (WORD) (lpbi->biSize + lpbi->biClrUsed * sizeof(RGBQUAD));
  SetDIBits(hdc, hBitmap, 0, (WORD)lpbi->biHeight,
                          (LPSTR)lpbi + offBits,
                          (LPBITMAPINFO)lpbi, DIB_RGB_COLORS);
  HBITMAP hOldBitmap = (HBITMAP)SelectObject (hdcMem,hBitmap);

  int x = (cx - bmWidth) / 2;
  int y = (cy - bmHeight) / 2;

  BitBlt(hdc,    x, y, (WORD)lpbi->biWidth, (WORD)lpbi->biHeight,
         hdcMem, 0, 0, SRCCOPY);

  SelectObject (hdcMem, hOldBitmap);

  DeleteDC (hdcMem);
  ReleaseDC (hWnd, hdc);
  GlobalUnlock (hDIBInfo);

  return hBitmap ;
  }


//--------------------------  ReadBitmap  -----------------------------------
//
//---------------------------------------------------------------------------
static BOOL ReadBitmap (HWND hWnd, LPSTR fname, int cx, int cy)
  {
  BOOL res = FALSE ;
  OFSTRUCT of;

  int fh = OpenFile (fname, &of, OF_READ);
  if (fh == -1) 
    return res;

  GLOBALHANDLE hDIBInfo = GlobalAlloc (GHND,
                        sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD));

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

  // !!!!! for now, don't even deal with CORE headers */
  if (lpbi->biSize == sizeof(BITMAPCOREHEADER))
    goto ErrExit;

  int nNumColors;
  if (!(nNumColors = (WORD)lpbi->biClrUsed)) {
    // no color table for 24-bit, default size otherwise */
    if (lpbi->biBitCount != 24)
      nNumColors = 1 << lpbi->biBitCount; /* standard size table */
    }

  // fill in some default values if they are zero */
  if (lpbi->biClrUsed == 0)
      lpbi->biClrUsed = (DWORD)nNumColors;

  if (lpbi->biSizeImage == 0)
    lpbi->biSizeImage = ((((lpbi->biWidth * (DWORD)lpbi->biBitCount) + 31) 
                      & ~31) >> 3) * lpbi->biHeight;

  // get a proper-sized buffer for header, color table and bits */ 
  GlobalUnlock(hDIBInfo);
  hDIBInfo = GlobalReAlloc(hDIBInfo, lpbi->biSize +
       nNumColors * sizeof(RGBQUAD) +
    lpbi->biSizeImage, 0);
  if (!hDIBInfo) return FALSE ;

  lpbi = (LPBITMAPINFOHEADER) GlobalLock(hDIBInfo);

  // read the color table */
  _lread (fh, (LPSTR)(lpbi) + lpbi->biSize, nNumColors * sizeof(RGBQUAD));

  // offset to the bits from start of DIB header */
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
    PaintBitmap (hWnd, hDIBInfo, cx, cy);
    }

  _lclose(fh);
  GlobalFree (hDIBInfo);

  return res;
  }

//------------------------  PaintWindow  ------------------------------------
//
//---------------------------------------------------------------------------
void PaintWindow (HWND hWnd, LPSTR lpszBitmap)
  {
  RECT   rc;
  
  GetClientRect (hWnd, &rc);
  InflateRect (&rc, -2, -2);
  
  HDC hDC = GetDC (hWnd);

  // statisches Fenster explizit mit hellgrau loeschen
  COLORREF OldBack = SetBkColor  (hDC, RGB(0xC0, 0xC0, 0xC0));
  ExtTextOut (hDC, 0, 0, ETO_OPAQUE, &rc, NULL, 0, NULL);
  SetBkColor (hDC, OldBack);

  ReleaseDC (hWnd, hDC);
  
  // Bitmap lesen und anzeigen
  ReadBitmap (hWnd, lpszBitmap,rc.right,rc.bottom);
  }

//------------------------  PaintPreview  -----------------------------------
//
//---------------------------------------------------------------------------
void PaintPreview (HWND hDlg, LPSTR lpszBitmap)
  {
  HWND hWndCtrl = GetDlgItem(hDlg, IDS_PREVIEWTEMPL);

//  InvalidateRect (hDlg, NULL, FALSE);

//  InvalidateRect (hWndCtrl, NULL, TRUE);
//  UpdateWindow (hWndCtrl);

  PaintWindow (hWndCtrl, lpszBitmap);
  }



//------------------------  DlgTemplateProc  --------------------------------
//
//---------------------------------------------------------------------------
DLLExport BOOL _export FAR PASCAL DlgTemplateProc (HWND hDlg, UINT msg, WPARAM wP, LPARAM lP)
  {
  BOOL res = FALSE;
  
  switch (msg) {
    case WM_INITDIALOG :
      {
      for (LPDIALOGTEMPLATE lptpl = FirstTemplate; lptpl != NULL; lptpl = lptpl->Next) {
        SendDlgItemMessage (hDlg, IDLB_TEMPLATENAME, LB_ADDSTRING, 0, 
                                  LPARAM(lptpl->szTemplateName));
        }
      SendDlgItemMessage (hDlg, IDLB_TEMPLATENAME, LB_SETCURSEL, 0, 0);

#ifdef WIN32
      SendMessage (hDlg,
                   WM_COMMAND,
                   MAKELONG (IDLB_TEMPLATENAME, LBN_SELCHANGE),
                   LONG (GetDlgItem(hDlg, IDLB_TEMPLATENAME))
                  );
#else
      SendMessage (hDlg,WM_COMMAND, IDLB_TEMPLATENAME,
                                    MAKELONG(GetDlgItem(hDlg, IDLB_TEMPLATENAME),LBN_SELCHANGE));
#endif
      res = TRUE;
      }
      break;

    case WM_PAINT :
      {
      PAINTSTRUCT ps;
      HDC hDC = BeginPaint (hDlg, &ps);
      InvalidateRect (GetDlgItem(hDlg, IDS_PREVIEWTEMPL), NULL, TRUE);
      UpdateWindow (GetDlgItem(hDlg, IDS_PREVIEWTEMPL));
      if (CurrentTemplate != NULL)
        PaintPreview (hDlg, CurrentTemplate->szBitmapName);
      EndPaint (hDlg, &ps);
      }
      break;
      
    case WM_COMMAND :
      {
      CRACKER_VARS
      CRACK_MESSAGEsc

      switch (CRACKER_wID) {
        case IDLB_TEMPLATENAME :
          {
          if (CRACKER_wNotify == LBN_SELCHANGE) {
            DWORD dwIndex = SendDlgItemMessage (hDlg, IDLB_TEMPLATENAME, LB_GETCURSEL, 0, 0);
            if (dwIndex != LB_ERR) {
              char szBuf[64];
              SendDlgItemMessage (hDlg, IDLB_TEMPLATENAME, LB_GETTEXT, WPARAM(dwIndex), 
                                                     LPARAM(LPSTR(szBuf)));
              int Cnt = 0;
              BOOL Found = FALSE;
              for (LPDIALOGTEMPLATE lptpl = FirstTemplate; 
                                    lptpl != NULL; 
                                    lptpl = lptpl->Next, Cnt++) {
                if (!lstrcmp(szBuf, lptpl->szTemplateName)) {
                  Found = TRUE;
                  break;
                  }
                }
              
              if (Found) {
                CurrentTemplate = lptpl;
                SendDlgItemMessage (hDlg, IDED_DESCRIPTION, WM_SETTEXT, 
                                    0, LPARAM(lptpl->lpszDescription));
                PaintPreview (hDlg, lptpl->szBitmapName);
//                InvalidateRect (HWND(LOWORD(lP)), NULL, TRUE);
//                InvalidateRect (hDlg, NULL, FALSE);
                }
              else  
                SendDlgItemMessage (hDlg, IDED_DESCRIPTION, WM_SETTEXT, 0, LPARAM(LPSTR("Error occured")));
              }
            }
          }
          break;
          
        case IDOK :
          {
          HWND hWndParent = GetParent(hDlg);
          EndDialog (hDlg, CRACKER_wID);
          GetValuesForTemplate (hWndParent);
          }
          break;
          
        case IDCANCEL :    
          CurrentTemplate = NULL;
          EndDialog (hDlg, CRACKER_wID);
          break;
        }
      res = TRUE;
      }
      break;
      
    };
  
  return res;
  }
  
//------------------------  ShowDialogWithTemplates  ------------------------
//
//---------------------------------------------------------------------------
void GetTemplates (LPSTR iniEintrag)
  {
  char TplPath[128];
  char searchPath[256];
  if (GetPrivateProfileString ("Script", iniEintrag, "", TplPath, sizeof(TplPath), MYINI) > 0) {
    strcpy (searchPath, TplPath);
    lstrcat(searchPath, "*.tpl");

#ifndef WIN32
    _find_t finfo;
  
    _dos_findfirst(searchPath, _A_NORMAL, &finfo);
    do {
      GetTemplateInfo (TplPath, finfo.name);
      }
    while (_dos_findnext(&finfo) == 0);
#else
    WIN32_FIND_DATA  fileData;
    HANDLE           hSearch;

    lmemset (&fileData,'\0',sizeof(fileData));
    hSearch = FindFirstFile (searchPath, &fileData);
    if (hSearch != INVALID_HANDLE_VALUE) {
      do {
        if ((fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) {
          GetTemplateInfo (TplPath, fileData.cFileName);
          }
        }
      while (FindNextFile (hSearch,&fileData));
      FindClose (hSearch);
      }
#endif

    }

  }

void ShowDialogWithTemplates (HWND hWnd)
  {
  FirstTemplate = NULL;

  GetTemplates ("template");
  GetTemplates ("template1");
  
  if (DialogBox (MyInstance, "TEMPLATEDIALOG", hWnd, DLGPROC(DlgTemplateProc)) == IDCANCEL)
    FreeTemplateInfo ();
  }

