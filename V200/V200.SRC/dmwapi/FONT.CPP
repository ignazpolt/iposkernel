////////////////////////////////////////////////////////////////////
//    Handling der Formate
////////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/dmwapi/rev/font.cpv   1.19   16 Aug 1999 18:37:42   Hannes  $
//  $Log:   P:/marille/clinicum/dmwapi/rev/font.cpv  $
// 
//    Rev 1.19   16 Aug 1999 18:37:42   Hannes
// Verbesserungen SlantFields
// 
//    Rev 1.18   05 Oct 1998 11:11:52   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.17   06 Aug 1998 20:42:02   Hannes
// 
//    Rev 1.16   06 Aug 1998 20:34:36   Hannes
// Fixe Fontgroessen eingebaut
// 
//    Rev 1.15   02 Jan 1998 13:20:30   Hannes
// 
//    Rev 1.14   28 Nov 1997 17:49:10   Hannes
// Fontabmessung in Dialogboxen auch fuer Drucker!
// 
//    Rev 1.13   21 Nov 1997 16:02:04   Hannes
// 
//    Rev 1.12   24 May 1996 19:33:08   HANNES
// 
//    Rev 1.11   02 Feb 1996 10:48:56   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.10   31 Jan 1996 18:17:38   GERHOLD
// 
//    Rev 1.9   11 Jan 1996 03:39:54   HANNES
// 
//    Rev 1.8   08 Jan 1996 17:41:52   HANNES
// Defaultmodify
// 
//    Rev 1.7   05 Jan 1996 20:00:26   HANNES
// Fehlerkorrektur Formatierung
// 
//    Rev 1.6   11 Jun 1995 19:16:58   MARTIN
// 
//    Rev 1.5   10 Jun 1995 22:02:28   HANNES
// MyGetExtent ... Abmessen aller Buchstaben fuer den Drucker
// 
//    Rev 1.4   09 Jun 1995 00:27:16   HANNES
// Minimale Optimierungen
// 
//    Rev 1.3   11 Oct 1994 08:59:48   HANNES
// 
//    Rev 1.2   17 Aug 1994 09:31:58   HANNES
// Aufloesungsunabhaengigkeit (begonnen)
// 
//    Rev 1.1   18 Jul 1994 12:01:04   GERHOLD
// 
//    Rev 1.0   24 Jun 1994 16:48:48   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.5   13 Apr 1994 14:30:24   HANNES
// Umstellung der SlantFields
// 
//    Rev 1.4   14 Feb 1994 19:50:30   HANNES
// Fensterspezifische Fontverwaltung
// 
//    Rev 1.3   24 May 1993 14:21:56   HANNES
// Schiefe Fonts
// 
//    Rev 1.2   22 Apr 1993 10:28:12   HANNES
// Korrektur von modifyOutFormat
// 
//    Rev 1.1   18 Apr 1993 22:29:52   HANNES
// ??
// 
//    Rev 1.0   02 Apr 1993 18:11:20   HANNES
// Initial revision.
//
#include <windows.h>
#include <stdio.h>
#include "dds32.h"
#include "globmem.h"
#include "hash.hpp"
#define FONT_MAIN
#include "font.hpp"

#define NODLL
#include "toolbar.hpp"
#define MODULENUM 163
#include "winass.hpp"

#include "printer.hpp"

static WORD LastIdent = 0xFFFF;
static LPFORMATINFO LastFormatInfo;
static WORD AnzFontsCreated = 0;
// #define SHOWCREATE
void HandleList::ResetHandles ()
  {
  for ( _HandleWidth FAR *h = w ; h != NULL ; ) {
    if (h->HFont) {
      DeleteObject (h->HFont);
      AnzFontsCreated -- ;
#ifdef SHOWCREATE
      char otxt[256];
      wsprintf (otxt,"Delete Font #%d",AnzFontsCreated);
      LogMsg(-1,-1,otxt);
#endif
      }
    if (h->bWidth) FreeGlobMem (h->bWidth);
    _HandleWidth FAR *n = h->Next;
    FreeGlobMem (h);
    h = n ;
    }
  w = NULL ;
  }

_HandleWidth FAR *HandleList::operator [] (int modify)
  {
  _HandleWidth FAR *prev = NULL ;
  for ( _HandleWidth FAR *h = w ; h != NULL ; prev = h , h = h->Next ) {
    if (h->modify == modify) return h ;
    }
  _HandleWidth FAR *n = (_HandleWidth FAR *) GetGlobMem (sizeof(*n));
  n->modify = modify ;
  if (prev != NULL) prev->Next = n ;
  else              w = n ;
  return n ;
  }

DLLExport void _export WINAPI RebuildList ()
  {
  LastIdent = 0xFFFF ;
  if (fListHash != NULL)
    delete fListHash ;
  fListHash = new hash (111,LONGKEY);
  LPFORMATINFO lpfi = GetFormatFirst ();
  for ( ; lpfi != NULL ; ) {
    fListHash->SetDataW (lpfi->fi.Ident,&lpfi,sizeof(lpfi));
    lpfi = GetFormatNext (lpfi);
    }
  }

DLLExport LPFORMATINFO _export WINAPI GetFormatInfo (WORD Ident)
  {
  if (Ident == LastIdent) return LastFormatInfo;
  if (fListHash == NULL) RebuildList ();
  LPFORMATINFO FAR *llp = (LPFORMATINFO FAR *)fListHash->GetDataW (Ident);
  if (llp == NULL) return GetFormatFirst ();
  else             { LastIdent = Ident ; LastFormatInfo = *llp ; return *llp; }
  }

DLLExport void _export WINAPI fntInsertFormat (WORD Ident,FontInfo FAR *fi)
  {
  LPFORMATINFO nf = LPFORMATINFO (GetGlobMem (sizeof(*nf)));
  fi->Ident = Ident;
  fi->HandleUsed = NULL;
  lmemcpy (&nf->fi,fi,sizeof(nf->fi));
  nf->fi.DefFormat = 0 ;
  if (nf->fi.lf.lfWeight > 500)
    nf->fi.DefFormat += FI_BOLD ;
  if (nf->fi.lf.lfItalic)
    nf->fi.DefFormat += FI_ITALIC ;
  if (nf->fi.lf.lfUnderline)
    nf->fi.DefFormat += FI_UNDERLINE ;
  if (nf->fi.lf.lfStrikeOut)
    nf->fi.DefFormat += FI_STRIKEOUT ;
  if (fifirst == NULL)
    fifirst = nf;
  else {
    for (LPFORMATINFO h = fifirst ; h -> Next != NULL ; h = h->Next) ;
    h->Next = nf;
    }
  }

DLLExport void _export WINAPI ResetHandles (LPFORMATINFO lpf)
  {
  hash FAR *h = lpf->fi.HandleUsed ;
  if (h == NULL) return ;
  for (int i = 0 ; i < 2 ; i++)
    lpf->fi.fh.HFont[i].ResetHandles();
  delete lpf->fi.HandleUsed;
  lpf->fi.HandleUsed = NULL;
  lpf->MetricInitialized = 0 ;
  }

DLLExport void _export WINAPI ResetWindowHandles (LPFORMATINFO lpf,HWND hWnd)
  {
  hash FAR *h = lpf->fi.HandleUsed ;
  if (h == NULL) return ;
  BOOL FAR *used = (BOOL FAR *) h->GetData(LONG(hWnd));
  if (used == NULL) return ;
  h->DelData (LONG(hWnd));
  if (h->IsHashEmpty ()) {
    for (int i = 0 ; i < 2 ; i++)
      lpf->fi.fh.HFont[i].ResetHandles ();
    delete (lpf->fi.HandleUsed);
    lpf->fi.HandleUsed = NULL;
    }
  }

DLLExport void _export WINAPI ResetWindowHandles (HWND hWnd)
  {
  for (LPFORMATINFO lpfi = GetFormatFirst() ; lpfi != NULL ; 
                        lpfi = GetFormatNext (lpfi)) {
    ResetWindowHandles (lpfi,hWnd);
    }
  }

DLLExport void _export WINAPI fntDeleteFormat (WORD Ident)
  {
  LPFORMATINFO prev = NULL;
  for (LPFORMATINFO lpfi = GetFormatFirst() ; lpfi != NULL ; 
                        lpfi = GetFormatNext (lpfi)) {
    if (lpfi -> fi.Ident == Ident) {
      if (prev != NULL)
        prev -> Next = lpfi->Next ;
      else
        fifirst = lpfi->Next;
      ResetHandles (lpfi);
      FreeGlobMem (lpfi);
      break ;
      }
    prev = lpfi;
    }
  }

DLLExport void _export WINAPI fntDeleteAllFormats ()
  {
  for (LPFORMATINFO lpfi = GetFormatFirst() ; lpfi != NULL ; ) {
    LPFORMATINFO next = lpfi->Next;
    ResetHandles (lpfi);
    FreeGlobMem (lpfi);
    lpfi = next;
    }
  // Loeschen der Hashtabelle
  LastIdent = 0xFFFF;
  if (fListHash != NULL)
    delete fListHash ;
  fListHash = NULL;
  fifirst = NULL;
  }

static int FAR *currentCharWidth;
int MyGetTextExtent (HDC hDC,LPSTR str,int count,int FAR *FAR *chars)
  {
  if (currentCharWidth) {
    int res = 0 ;
    if (chars != NULL) {
      if (*chars != NULL)
        FreeGlobMem (*chars);
      *chars = (int FAR *) GetGlobMem (sizeof(int) * count);
      for (int i = 0 ; i < count ; i++) {
        int w = currentCharWidth[(unsigned char) str[i]] ;
        (* chars)[i] = w ;
        res += w ;
        }
      }
    else {
      for (int i = 0 ; i < count ; i++) {
        res += currentCharWidth[(unsigned char) str[i]] ;
        }
      }
    return res;
    }
  else {
    int cx;
#ifdef WIN32
    SIZE size;
    GetTextExtentPoint32 (hDC,str,count,&size);
    cx = size.cx;
#else
    cx = LOWORD(GetTextExtent (hDC,str,count));
#endif
    return cx ;
    }
  }

DLLExport HFONT _export WINAPI GetFontHandle (HWND hWnd,int MapType,int Format,int Modify,int orientation,HDCCALLBACK CallBackSpacing,LPVOID CallBackData)
  {
  LPFORMATINFO lpf = GetFormatInfo (Format);

  HFONT res ;

  if ((MapType == MAPTYPE_GEOMETRIC) ||
      (MapType == MAPTYPE_TYPOGRAPHIC)) {

    int primind = MapType - 1;

    int Fontind;
    BOOL modify_lf;
    if ((Modify >= 0) && (Modify < 64))
      Fontind = Modify , modify_lf = TRUE ;
    else
      Fontind = lpf->fi.DefFormat , modify_lf = FALSE ;

    if (lpf->fi.HandleUsed == NULL)
      lpf->fi.HandleUsed = new hash (13,LONGKEY);
    BOOL FAR *lpused ;
    if ((lpused = (BOOL FAR *) lpf->fi.HandleUsed->GetData (LONG(hWnd))) == NULL) {
      BOOL nUsed = TRUE ;
      lpf->fi.HandleUsed->SetData (LONG(hWnd),&nUsed,sizeof(nUsed));
      }
    if (lpf->fi.fh.HFont[primind][Fontind]->HFont == 0) {
      lpf->fi.fh.HFont[primind][Fontind]->HFont = NULL;
      double fact;
#ifdef UEBERLEGT
      GetResolutionCF (&fact);
#else
      fact = 1.0;
#endif
      // Font muss erst erzeugt werden !!!
      LOGFONT lftemp;
      lmemcpy (&lftemp,&lpf->fi.lf,sizeof(LOGFONT));
      lftemp.lfOrientation = orientation;
      lftemp.lfEscapement = orientation;
      if (MapType == MAPTYPE_TYPOGRAPHIC)
        lftemp.lfHeight = - int (double (lpf->fi.cf.iPointSize) * 2.0 * fact) ;
      else
        lftemp.lfHeight = int (double (-lpf->fi.cf.iPointSize) 
                                           / 10.0 * 8.6944 * fact);
      if (modify_lf) {
        if (Fontind & FI_BOLD)
          lftemp.lfWeight = 700;
        else
          lftemp.lfWeight = 400;
        if (Fontind & FI_STRIKEOUT)
          lftemp.lfStrikeOut = TRUE ;
        else
          lftemp.lfStrikeOut = FALSE ;
        if (Fontind & FI_UNDERLINE)
          lftemp.lfUnderline = TRUE ;
        else
          lftemp.lfUnderline = FALSE ;
        if (Fontind & FI_ITALIC)
          lftemp.lfItalic = TRUE ;
        else
          lftemp.lfItalic = FALSE ;
        if ((Fontind & FI_HIGH) || (Fontind & FI_LOW)) {
          lftemp.lfHeight = lftemp.lfHeight * 2 / 3 ;
          }
        }

      HFONT fnt = CreateFont (
                  lftemp.lfHeight,
                  lftemp.lfWidth,
                  lftemp.lfEscapement,
                  lftemp.lfOrientation,
                  lftemp.lfWeight,
                  lftemp.lfItalic,
                  lftemp.lfUnderline,
                  lftemp.lfStrikeOut,
                  lftemp.lfCharSet,
                  OUT_TT_PRECIS,
                  CLIP_TT_ALWAYS,
                  PROOF_QUALITY,
                  lftemp.lfPitchAndFamily,
                  lftemp.lfFaceName);

      WIN_ASSERT (fnt != 0);
      lpf->fi.fh.HFont[primind][Fontind]->HFont = fnt;

#ifdef SHOWCREATE
      char otxt[256];
      wsprintf (otxt,"Create Font %d: %s (%d) = #%d",Format,LPSTR(lftemp.lfFaceName),lftemp.lfHeight,AnzFontsCreated);
      LogMsg(-1,-1,otxt);
#endif
      AnzFontsCreated ++ ;
      }

    if ((CallBackSpacing) && (lpf->fi.fh.HFont[primind][Fontind]->bWidth == NULL)) {
      HDC hMDc = (* CallBackSpacing) (0,CallBackData);
      if (hMDc) {
        HFONT oldFont = (HFONT)SelectObject (hMDc,lpf->fi.fh.HFont[primind][Fontind]->HFont);
        int FAR *res = (int FAR *) GetGlobMem (sizeof(int) * 256);
        lpf->fi.fh.HFont[primind][Fontind]->bWidth = res;
        for (int i = 0 ; i < 256 ; i++) {
          unsigned char ch = unsigned char(i);
          int cx;

#ifdef WIN32
          SIZE size;
          GetTextExtentPoint32 (hMDc,LPSTR(&ch),1,&size);
          cx = size.cx;
#else
          cx = LOWORD(GetTextExtent (hMDc,LPSTR(&ch),1));
#endif
          
          res[i] = cx;
          }
        SelectObject (hMDc,oldFont);
        (* CallBackSpacing) (hMDc,CallBackData);
        }
      }
    res = lpf->fi.fh.HFont[primind][Fontind]->HFont;
    currentCharWidth = lpf->fi.fh.HFont[primind][Fontind]->bWidth;
    }
  else {
    res = 0;
    currentCharWidth = NULL ;
    }

  return res;
  }

DLLExport LPFORMATINFO _export WINAPI GetFormatFirst ()
  {
  return fifirst ;
  }

DLLExport LPFORMATINFO _export WINAPI GetFormatNext (LPFORMATINFO lpf)
  {
  return lpf->Next ;
  }

extern void ExtSetGeomMap (HDC hDC,double scale,int xp,int yp,int xa,int ya);
extern void ExtSetTwipsMap (HDC hDC,double scale,int xp,int yp);
Printer FAR *GetDefPrinter ()
  {
  static Printer FAR *MyPr;
  if (MyPr == NULL) MyPr = GetPrinter(TRUE);
  return MyPr;
  }

BOOL GetMappedSize (int ptSize,int FAR *h,int FAR *bh)
  {
  static struct {
    short pt,h,bh;
    } ptlist [] = {
  { 20,46,30 },
  { 30,77,60 },
  { 40,92,75 },
  { 50,108,90 },
  { 60,154,120 },
  { 70,184,135 },
  { 80,215,165 },
  { 90,231,180 },
  { 100,246,195 },
  { 110,262,210 },
  { 120,278,225 },
  { 130,293,225 },
  { 140,339,270 },
  { 150,355,285 },
  { 160,370,285 },
  { 170,401,315 },
  { 180,417,315 },
  { 190,432,345 },
  { 200,493,390 },
  { 210,494,390 },
  { 220,509,405 },
  { 230,540,420 },
  { 240,556,435 },
  { 250,586,465 },
  { 260,617,480 },
  { 270,633,495 },
  { 280,648,510 },
  { 290,679,525 },
  { 300,695,540 },
  { 310,725,570 },
  { 320,756,585 },
  { 330,772,600 },
  { 340,772,600 },
  { 350,818,645 },
  { 360,849,675 },
  { 370,864,675 },
  { 380,895,705 },
  { 390,926,720 },
  { 400,926,720 },
  { 410,972,765 },
  { 420,1002,780 },
  { 430,1003,780 },
  { 440,1019,795 },
  { 450,1034,810 },
  { 460,1050,825 },
  { 470,1096,855 }
  } ;
  for (int i = 0 ; i < sizeof(ptlist) / sizeof(*ptlist) ; i++) {
    if (ptlist[i].pt == ptSize) {
      *bh = ptlist[i].bh;
      *h = ptlist[i].h;
      return TRUE;
      }
    }
  return FALSE;
  }
// #define MITFONTSIZEWRITE
void WriteFontSize (HDC hDC,int ptSize,HFILE hf)
  {
  LOGFONT lf;
  lmemset (&lf,'\0',sizeof(lf));
  lf.lfEscapement = 0;
  lf.lfOrientation = 0;

  lf.lfHeight = - ptSize * 2 ;

  HFONT hfnt = CreateFont (
                lf.lfHeight,
                0,
                0,
                0,
                400,
                0,
                0,
                0,
                DEFAULT_CHARSET,
                OUT_TT_PRECIS,
                CLIP_TT_ALWAYS,
                PROOF_QUALITY,
                34,
                "Arial");

  HFONT oldObject = (HFONT)SelectObject (hDC,hfnt);
  TEXTMETRIC tm;
  GetTextMetrics (hDC,&tm);
  SelectObject (hDC,oldObject);
  DeleteObject (hfnt);

  char outtxt[128];
  sprintf (outtxt,"{ %d,%d,%d },\r\n",ptSize,tm.tmHeight + tm.tmExternalLeading,tm.tmAscent);
  _lwrite (hf,outtxt,lstrlen(outtxt));
  }

DLLExport LPFORMATMETRIC _export WINAPI GetFormatMetrics (HWND hWnd,int MapType,int Format)
  {
  LPFORMATINFO lpf = GetFormatInfo (Format);
  int primind = MapType - 1;

  if ((lpf != NULL) && ((lpf->MetricInitialized & MapType) == 0)) {
    // Printer FAR *Pr = GetPrinter(TRUE);
    // HDC hDC = Pr->PrinterIC();
    if (!GetMappedSize (lpf->fi.cf.iPointSize,&lpf->fm[primind].yHeight,&lpf->fm[primind].yBaseHeight)) {
      HDC hDC = CreateDC ("DISPLAY",NULL,NULL,NULL);
      if (MapType == MAPTYPE_TYPOGRAPHIC)
        ExtSetTwipsMap (hDC,1.0,0,0);
      else
        ExtSetGeomMap (hDC,1.0,0,0,0,0);
      HFONT OldFont = (HFONT)SelectObject (hDC,GetFontHandle (hWnd,MapType,Format,0xFFFF));
      TEXTMETRIC tm;
      GetTextMetrics (hDC,&tm);

  #ifdef MITFONTSIZEWRITE
      HFILE hf;
      OFSTRUCT Of;
      static BOOL done;
      if (!done) {
        hf = OpenFile ("font.xxx",&Of,OF_CREATE);
        static BOOL first;
        for (int i = 20 ; i < 480 ; i += 10)
          WriteFontSize (hDC,i,hf);
        _lclose (hf);
        done = TRUE ;
        }
  #endif


      lpf->fm[primind].yHeight = tm.tmHeight + tm.tmExternalLeading;
      lpf->fm[primind].yBaseHeight = tm.tmAscent;
      lpf->fm[primind].xAveWidth = tm.tmAveCharWidth;

      SelectObject (hDC,OldFont);
      DeleteDC (hDC);
      }

    // Eintragen der Daten in den Buffer
    lpf->fm[primind].yExtraHeight = lpf->fi.fei.LineWidth;
    lpf->fm[primind].OutFormat = lpf->fi.fei.FormatMode;
    lpf->fm[primind].xLeft = lpf->fi.fei.xLeft ;
    lpf->fm[primind].xRight = lpf->fi.fei.xRight ;

    lpf->MetricInitialized |= MapType ;
    // Pr->ReleasePrDC();
    }
  return (lpf != NULL) ? lpf->fm + primind : NULL ;
  }

DLLExport void _export WINAPI fntGetFontExtraInfo (WORD Format,FontExtraInfo FAR *fei)
  {
  LPFORMATINFO lpf = GetFormatInfo (Format);
  if (lpf != NULL)
    lmemcpy (fei,&lpf->fi.fei,sizeof(*fei));
  }

DLLExport BOOL _export WINAPI fntGetFormatFaceName (WORD Format,LPSTR FaceName,int size)
  {
  LPFORMATINFO lpf = GetFormatInfo (Format);
  if (lpf != NULL)
    lstrncpy (FaceName,lpf->fi.lf.lfFaceName,size);
  return (lpf != NULL);
  }

DLLExport BOOL _export WINAPI fntGetFormatName (WORD Format,LPSTR Name,int size)
  {
  LPFORMATINFO lpf = GetFormatInfo (Format);
  if (lpf != NULL)
    lstrncpy (Name,lpf->fi.FormatName,size);
  return (lpf != NULL);
  }

DLLExport DWORD _export WINAPI fntGetFormatColor (WORD Format)
  {
  DWORD res = 0;
  LPFORMATINFO lpf = GetFormatInfo (Format);
  if (lpf != NULL)
    res = lpf->fi.cf.rgbColors;
  return res;
  }

DLLExport DWORD _export WINAPI fntGetFormatIvColor (WORD Format)
  {
  DWORD res = 0;
  LPFORMATINFO lpf = GetFormatInfo (Format);
  if (lpf != NULL) {
    res = lpf->fi.cf.rgbColors;
    if (res == 0) {
      // Nur schwarz wird invertiert
      res = RGB(0xFF,0xFF,0xFF);
      }
    }
  else res = RGB(0,0,0);

  return res;
  }

DLLExport int _export WINAPI fntGetMaxFormatId ()
  {
  int res = 0 ;
  for (LPFORMATINFO lfi = GetFormatFirst ();
        lfi != NULL ; lfi = GetFormatNext (lfi)) {
    if (int (lfi->fi.Ident) > res) res = int (lfi->fi.Ident);
    }
  return res;
  }

// Modifizieren des Ausgabeformates
////////////////////////////////////
static void ModifyFormatName (LPSTR szName,int OutFormat)
  {
  static char *ext[] = { "_l" , "_c" , "_r" , "_b" } ;
  int len = lstrlen (szName);
  if (len > 2) {
    // Nachschauen, ob sich noch kein Modifyer im Namen befindet
    for (int i = 0 ; i < 4 ; i++) {
      if (lstrcmp (szName + len - 2,ext[i]) == 0) {
        szName[len-2] = '\0' ;
        break ;
        }
      }
    }
  lstrcat (szName,ext[OutFormat]);
  }

static void PaddString (LPSTR str,int len)
  {
  for (int i = lstrlen (str) ; i < len ; i++)
    str[i] = '\0' ;
  }

static BOOL CompareFormats (FontInfo FAR *fi1,FontInfo FAR *fi2)
  {
  // Anlegen zweier Kopien der Formate
  FontInfo fit1,fit2 ;
  lmemcpy (&fit1,fi1,sizeof(FontInfo));
  lmemcpy (&fit2,fi2,sizeof(FontInfo));
  // Beide Formate so modifizieren, dass sie mit lmemcpy verglichen
  // werden koennen
  PaddString (fit1.lf.lfFaceName,sizeof(fit1.lf.lfFaceName));
  PaddString (fit2.lf.lfFaceName,sizeof(fit2.lf.lfFaceName));
  // Und vergleichen
  return ((fit1.cf.rgbColors == fit2.cf.rgbColors) &&
          (fit1.cf.iPointSize == fit2.cf.iPointSize) &&
          (fit1.fei.FormatMode == fit2.fei.FormatMode) &&
          (fit1.fei.LineWidth == fit2.fei.LineWidth) &&
          (lmemcmp (&fit1.lf,&fit2.lf,sizeof(LOGFONT))));
  }


DLLExport int _export WINAPI fntModifyOutFormat (int Format,int OutFormat)
  {
  int res = -1;

  // Erzeugen des neuen Formates
  //////////////////////////////
  FontInfo fitemp;
  lmemset (&fitemp,'\0',sizeof(fitemp));
  LPFORMATINFO lfi = GetFormatInfo (Format);
  if (lfi != NULL) {
    lmemcpy (&fitemp,&lfi->fi,sizeof(fitemp));
    // Modifizieren des aktuellen Formates
    fitemp.fei.FormatMode = OutFormat ;
    // Suchen, ob das Format schon vorhanden ist
    for (lfi = GetFormatFirst ();
                lfi != NULL ; lfi = GetFormatNext (lfi)) {
      if (CompareFormats (&lfi->fi,&fitemp)) {
        res = lfi->fi.Ident ;
        break ;
        }
      }
    if (res < 0) {
      // Leider nicht gefunden, Neu in die Datenbank einfuegen
      ModifyFormatName (fitemp.FormatName,OutFormat);
      fitemp.HandleUsed = NULL;
      res = fntGetMaxFormatId () + 1;
      fntInsertFormat (res,&fitemp);
      RebuildList ();
      }
    }
  return res;
  }

void FontSlantHandle::Create (FontInfo FAR *fi,double a,int m,int Modify,DWORD K)
  {
  if (hfnt == 0) {
    LOGFONT lf;
    lmemcpy (&lf,&fi->lf,sizeof(lf));
    maptype = m;
    modify = Modify;
    Kennung = K;
    ang = int (a * 10.0) ;
    lf.lfEscapement = ang;
    lf.lfOrientation = ang;
    if (Modify & FI_BOLD)
      lf.lfWeight = 700;
    if (Modify & FI_ITALIC)
      lf.lfItalic = TRUE ;
    if (Modify & FI_STRIKEOUT)
      lf.lfStrikeOut = TRUE ;
    if (Modify & FI_UNDERLINE)
      lf.lfUnderline = TRUE ;

    if (m == MAPTYPE_TYPOGRAPHIC)
      lf.lfHeight = -fi->cf.iPointSize * 2 ;
    else
      lf.lfHeight = int (double (-fi->cf.iPointSize) 
                                           / 10.0 * 8.6944);
    hfnt = CreateFont (
                  lf.lfHeight,
                  lf.lfWidth,
                  lf.lfEscapement,
                  lf.lfOrientation,
                  lf.lfWeight,
                  lf.lfItalic,
                  lf.lfUnderline,
                  lf.lfStrikeOut,
                  lf.lfCharSet,
                  OUT_TT_PRECIS,
                  CLIP_TT_ALWAYS,
                  PROOF_QUALITY,
                  lf.lfPitchAndFamily,
                  lf.lfFaceName);
    AnzFontsCreated ++ ;
    }
  refcount ++ ;
  }

BOOL FontSlantHandle::Delete ()
  {
  if (-- refcount == 0) {
    Destroy ();
    }
  return (refcount == 0) ;
  }

void FontSlantHandle::Destroy ()
  {
  DeleteObject (hfnt);
  AnzFontsCreated -- ;
#ifdef SHOWCREATE
  char otxt[256];
  wsprintf (otxt,"Delete Font #%d",AnzFontsCreated);
  LogMsg(-1,-1,otxt);
#endif
  }

BOOL FontSlantHandle::Check (double a,int m,int md)
  {
  return ((int (a * 10.0) == ang) && (m == maptype) && (modify == md)) ;
  }

HFONT FormatInfo::GetSlantHandle (double ang,int maptype,int Modify,DWORD Kennung,BOOL doCreate)
  {
  LPFSLANT h = slh ;
  for ( ; h != NULL ; h = h->Next) {
    if (h->Check (ang,maptype,Modify)) break ;
    }
  if ((h == NULL) || (doCreate)) {
    if (h == NULL) {
      h = LPFSLANT (GetGlobMem (sizeof(*h)));
      h->Next = slh ;
      slh = h ;
      }
    h->Create (&fi,ang,maptype,Modify,Kennung);
    }
  currentCharWidth = NULL;
  return h->hfnt;
  }

void FormatInfo::DelSlantHandle (DWORD Kennung)
  {
  LPFSLANT h = slh ;
  LPFSLANT prev = NULL ;
  for ( ; h != NULL ; ) {
    if (h->Kennung == Kennung) {
      LPFSLANT Next = h->Next;
      if (h->Delete ()) {
        if (prev != NULL) prev->Next = h->Next;
        else              slh = h->Next ;
        FreeGlobMem (h);
        }
      h = Next ;
      }
    else {
      prev = h;
      h = h->Next;
      }
    }
  }

DLLExport BOOL _export WINAPI GetBestScaling (HWND hWnd,int MapType,float FAR *sc,HDC hPrDC)
  {
  return FALSE;
  }

