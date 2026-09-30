/////////////////////////////////////////////////
// Routinen fuer Fonts und Farben
/////////////////////////////////////////////////
//         $Header:   P:/marille/clinicum/restool/rev/fontcol.cpv   1.18   05 Oct 1998 11:26:06   Gerhold  $
//         $Log:   P:/marille/clinicum/restool/rev/fontcol.cpv  $
// 
//    Rev 1.18   05 Oct 1998 11:26:06   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.17   04 Feb 1998 14:32:22   Gerhold
// 16-32-Bit Problemchen
// 
//    Rev 1.16   05 Nov 1997 08:58:24   Gerhold
// 32 Bit
// 
//    Rev 1.15   04 Nov 1997 17:19:46   Gerhold
// mehr als 64K Formate
// 
//    Rev 1.14   28 Aug 1997 16:26:54   gerhold
//  kleiner 16-32-Bit Fehler
// 
//    Rev 1.13   28 Aug 1997 15:50:52   gerhold
// Umstellung 32 Bit
// 
//    Rev 1.12   24 Mar 1996 12:16:24   HANNES
// UmStellung auf mehrseitige cFields
// 
//    Rev 1.11   02 Feb 1996 10:50:50   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.10   03 Jan 1995 16:17:40   HANNES
// 
//    Rev 1.9   02 Jan 1995 16:41:52   GERHOLD
// Font fuer den Editor aus der Ini-Datei lesen
// 
//    Rev 1.8   02 Jan 1995 09:29:46   GERHOLD
// Umstellung auf MDI
// 
//    Rev 1.7   30 Aug 1994 13:16:04   GERHOLD
// fi%d auf fi%d%c fuer Small und Large-Fonts erweitert
// 
//    Rev 1.6   17 Aug 1994 09:33:12   HANNES
// Fontnamen aufloesungsabhaengig
// 
//    Rev 1.5   12 Aug 1994 12:11:12   GERHOLD
// Dialog Initialisierungen
// 
//    Rev 1.4   08 Aug 1994 17:38:46   GERHOLD
// Format und Farb-Werte werden jetzt auch auf OK in die entsprechenden
// Edit-Elemente geschrieben.
// 
//    Rev 1.3   01 Aug 1994 15:37:50   GERHOLD
// Drag & Drop fuer Farben
// 
//    Rev 1.2   25 Jul 1994 12:04:52   GERHOLD
// in WM_LBUTTONUP auf alle Faelle DefWndProc aufrufen
// 
//    Rev 1.1   25 Jul 1994 09:48:30   GERHOLD
// 
//    Rev 1.0   20 Jul 1994 17:42:32   HANNES
// Initial revision.
// 
//    Rev 1.0   20 Jul 1994 17:02:20   GERHOLD
// Initial revision.
/////////////////////////////////////////////////
#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#include "globmem.h"
#include "font.hpp"
#include "restool.hpp"

#define NODDSDATA
#include "dds.hpp"

#include "sc2d.hpp"
#include "printer.hpp"
#include "paint.hpp"
#include "cfield.hpp"
#include "drdrop.hpp"

#ifndef WIN32
  #include <custcntl.h>
  #include "muscroll.hpp"
  #include "muexport.hpp"
#endif

#include "hash.hpp"
#include "compile.hpp"

extern void MyMoveTo (HDC hDC, int x, int y);
extern void MyLineTo (HDC hDC, int x, int y, double mapFact, int Style, int Width);


extern HINSTANCE MyInstance;
//extern LPSTR GetStartDirName();    // in RESTOOL.CPP

#define TWIPSTOMM       56.7

//////////////////////////////////////////////////////////
//  Schreiben der Daten
//////////////////////////////////////////////////////////
LPSTR MyLRString (int id) 
  {  
  static char statstrspace[50];
  LoadString (MyInstance, id, statstrspace, sizeof(statstrspace)); 
  return statstrspace ; 
  }

GLOBALHANDLE PushToGlobBlock (GLOBALHANDLE hGmem,LPVOID data,int size)
  {
  char huge *Buffer;
  DWORD oldsize;
  if (hGmem) {
    Buffer = (char huge *)GlobalLock (hGmem);
    oldsize = *((DWORD FAR *) Buffer);
    }
  else {
    hGmem = GlobalAlloc (GHND,sizeof(DWORD));
    Buffer = (char huge *)GlobalLock (hGmem);
    oldsize = *((DWORD FAR *) Buffer) = sizeof(DWORD);
    }
  GlobalUnlock (hGmem);
  hGmem = GlobalReAlloc (hGmem,oldsize + size,GHND);
  Buffer = (char huge *)GlobalLock (hGmem);
  *((DWORD FAR *) Buffer) += size;
  hmemcpy (Buffer + oldsize,data,size);
  GlobalUnlock (hGmem);
  return hGmem;
  }

LPSTR PutString (LPSTR h,LPSTR name)
  {
  *h++ = '"' ;
  lstrcpy (h,name);
  h += lstrlen(name);
  *h++ = '"' ;
  return h;
  }

LPSTR PutName (LPSTR h,LPSTR name)
  {
  lstrcpy (h,name);
  h += lstrlen(name);
  return h;
  }

LPSTR PutNumber (LPSTR h,int i)
  {
  char nstr[10];
  wsprintf (nstr,"%d",i);
  return PutName (h,nstr);
  }

LPSTR PutNumber (LPSTR h,WORD i)
  {
  return PutNumber (h,int (i));
  }

LPSTR PutByte (LPSTR h,BYTE b)
  {
  return PutNumber (h,int (b));
  }

LPSTR PutNumInd (LPSTR h,int ind,int base,int m)
  {
  return PutName (h,MyLRString (base+min (ind,m)));
  }

LPSTR PutColon (LPSTR h)
  {
  return PutName (h,": ");
  }

LPSTR PutComma (LPSTR h)
  {
  return PutName (h,"; ");
  }

GLOBALHANDLE WriteFormatLine (GLOBALHANDLE hGmem,FontInfo FAR *fi)
  {
  char outtxt[1024];
  LPSTR h = outtxt;
  h = PutNumber (h,fi->Ident);
  h = PutColon (h);
  h = PutString (h,fi->FormatName);
  h = PutComma (h);
  h = PutString (h,fi->FormatDesc);
  h = PutComma (h);
  h = PutString (h,fi->lf.lfFaceName);
  h = PutComma (h);
  h = PutNumber (h,fi->cf.iPointSize);
  h = PutComma (h);
  h = PutNumber (h,fi->lf.lfHeight);
  h = PutComma (h);
  h = PutNumInd (h,fi->fei.FormatMode,RCFI_BASE,4);
  h = PutComma (h);
  h = PutNumber (h,fi->fei.LineWidth);
  h = PutComma (h);
  h = PutNumber (h,fi->fei.xLeft);
  h = PutComma (h);
  h = PutNumber (h,fi->fei.xRight);
  h = PutComma (h);
  h = PutNumber (h,fi->lf.lfEscapement);
  h = PutComma (h);
  h = PutNumber (h,fi->lf.lfOrientation);
  h = PutComma (h);
  h = PutNumber (h,fi->lf.lfWeight);
  h = PutComma (h);
  h = PutByte (h,fi->lf.lfItalic);
  h = PutComma (h);
  h = PutByte (h,fi->lf.lfUnderline);
  h = PutComma (h);
  h = PutByte (h,fi->lf.lfStrikeOut);
  h = PutComma (h);
  h = PutByte (h,fi->lf.lfCharSet);
  h = PutComma (h);
  h = PutByte (h,fi->lf.lfOutPrecision);
  h = PutComma (h);
  h = PutByte (h,fi->lf.lfClipPrecision);
  h = PutComma (h);
  h = PutByte (h,fi->lf.lfQuality);
  h = PutComma (h);
  h = PutByte (h,fi->lf.lfPitchAndFamily);
  h = PutComma (h);
  int r = int (fi->cf.rgbColors & 0xFF) ;
  int g = int ((fi->cf.rgbColors >> 8) & 0xFF) ;
  int b = int ((fi->cf.rgbColors >> 16) & 0xFF) ;
  h = PutNumber (h,r);
  h = PutComma (h);
  h = PutNumber (h,g);
  h = PutComma (h);
  h = PutNumber (h,b);
  h = PutName (h,"\r\n");
  return PushToGlobBlock (hGmem,outtxt,lstrlen(outtxt));
  }

void WriteFormatInfo ()
  {
  LPFORMATINFO lfi;
  GLOBALHANDLE hGmem = 0;

  // Zusammenstellen des Textes
  for (lfi = GetFormatFirst ();
                lfi != NULL ; lfi = GetFormatNext (lfi) ) {
    hGmem = WriteFormatLine (hGmem,&lfi->fi);
    }

  // Schreiben des Blockes auf das File
  if (hGmem) {
    char fname[128],fpattern[128];
    GetPrivateProfileString ("Fonts","FormatDescription","fi%d%c.txt",
                                fpattern,sizeof(fpattern),
                                MYINI
                            );
    int resx = GetSystemMetrics (SM_CXSCREEN);
    DWORD dbu = GetDialogBaseUnits();
    char c = (LOWORD(dbu) > 9) ? 'L' : 'S';
    wsprintf (fname,fpattern,resx,c);
    OFSTRUCT Of;
    int find = OpenFile (fname,&Of,OF_WRITE | OF_CREATE);
    if (find >= 0) {
      LPSTR buffer = (LPSTR)GlobalLock (hGmem);
      _hwrite (find,buffer+sizeof(DWORD),*(DWORD FAR *) (buffer));
      _lclose (find);
      GlobalUnlock (hGmem);
      GlobalFree (hGmem);
      }
    }
  }

//----------------------------------------------------------------------------
// Schreibt den Font bei einer Fontaenderung in die INI-Datei
//----------------------------------------------------------------------------
extern LPSTR IniFile();
const int FONTSIZE = 128;
void WriteEditorFont (HFONT hFont)
  {
  LOGFONT lf;

  char OutText[256];
  LPSTR szFont = OutText; 

  GetObject (hFont, sizeof(lf), &lf);
  
  szFont = PutNumber (szFont, lf.lfHeight);
  szFont = PutComma (szFont);
  szFont = PutNumber (szFont, lf.lfWidth);
  szFont = PutComma (szFont);
  szFont = PutNumber (szFont, lf.lfEscapement);
  szFont = PutComma (szFont);
  szFont = PutNumber (szFont, lf.lfOrientation);
  szFont = PutComma (szFont);
  szFont = PutNumber (szFont, lf.lfWeight);
  szFont = PutComma (szFont);
  szFont = PutByte (szFont, lf.lfItalic);
  szFont = PutComma (szFont);
  szFont = PutByte (szFont, lf.lfUnderline);
  szFont = PutComma (szFont);
  szFont = PutByte (szFont, lf.lfStrikeOut);
  szFont = PutComma (szFont);
  szFont = PutByte (szFont, lf.lfCharSet);
  szFont = PutComma (szFont);
  szFont = PutByte (szFont, lf.lfOutPrecision);
  szFont = PutComma (szFont);
  szFont = PutByte (szFont, lf.lfClipPrecision);
  szFont = PutComma (szFont);
  szFont = PutByte (szFont, lf.lfQuality);
  szFont = PutComma (szFont);
  szFont = PutByte (szFont, lf.lfPitchAndFamily);
  szFont = PutComma (szFont);
  szFont = PutString (szFont, lf.lfFaceName);
  *szFont = '\0';

  WritePrivateProfileString ("EDITOR", "Font", OutText, IniFile());
  }

inline int myround (double f)
  {
  return (f > 0.0) ? int (f + 0.5) : int (f - 0.5) ;
  }

static void prfloat (LPSTR txt,double f)
  {
  int x = myround (f * 10.0) ;
  wsprintf (txt,"%d",x);
  int l = lstrlen (txt);
  if (l > 1) {
    txt[l] = txt[l-1];
    txt[l-1] = '.' ;
    txt[l+1] = '\0';
    }
  else {
    txt[3] = '\0';
    txt[2] = txt[0];
    txt[1] = '.';
    txt[0] = '0';
    }
  }



void PaintFont (HWND hDlg, int nFormatNr);

/////////////////////////////////////////////////////////////////////////////
//
// Initialisiert und oeffnet die Standard-Font-Dialogbox aus der COMMDLG.DLL
//
/////////////////////////////////////////////////////////////////////////////
void GetFontDialogBox (HWND hDlg, WORD Ident)
  {
  LPFORMATINFO lpf = GetFormatInfo (Ident);
  FontInfo FAR *f = &lpf->fi;
  Printer *Pr = GetPrinter (TRUE);
  PaintContext pc(Pr);
  pc.LogicalTwips ();
  f->cf.hDC = pc.hDC ;
  f->cf.Flags = CF_INITTOLOGFONTSTRUCT | CF_BOTH
                | CF_SCALABLEONLY | CF_EFFECTS | CF_WYSIWYG;
  f->cf.lpLogFont = &f->lf;
  f->cf.hwndOwner = hDlg;
  f->cf.lStructSize = sizeof (CHOOSEFONT);

  ChooseFont (&f->cf);   // bei OK werden die Daten in der Struktur "f->cf" gespeichert
  // Loeschen der Fonts
  ResetHandles (lpf);
  f->DefFormat = GetFormatFlags (f);
  PaintFont (hDlg, Ident);
  }



////////////////////////////////////////////////////////////////////////////
//
//
//
//   Deklarationen f�r die Dialogbox Zusatzinformationen
//   (Name, Einz�ge, Absatz
//
//
////////////////////////////////////////////////////////////////////////////

void SetDlgInt (HWND hDlg, WORD Id, int num)
  {
  double mm = double (num) / TWIPSTOMM ;
  char szdbl[10];

  prfloat (szdbl, mm);
  SetDlgItemText (hDlg, Id, szdbl);
  }


int GetDlgInt (HWND hDlg, WORD Id)
  {
  char szdbl[10];
  float mm;
  int res;

  GetDlgItemText (hDlg, Id, szdbl, sizeof(szdbl));
  if (sscanf (szdbl, "%f", &mm) == 1) 
    res = int (mm * TWIPSTOMM);
  else
    res = -1;

  return res;
  }



DLLExport BOOL FAR PASCAL _export ExtraFormatInfoDlgProc(HWND hDlg, UINT message, WPARAM wP, LPARAM lP)
  {
  static int nFormatNr;
  BOOL RetVal = FALSE;
  
  switch (message) {
    case WM_INITDIALOG:
      {
      nFormatNr = LOWORD(lP);

      LPFORMATINFO lpf = GetFormatInfo (nFormatNr);
      FontInfo FAR *f = &lpf->fi;

      SetDlgItemText (hDlg, IDED_NAME,  f->FormatName);
      SetDlgItemText (hDlg, IDED_DESCR, f->FormatDesc);

      SetDlgInt (hDlg, IDED_LEFT , f->fei.xLeft);
      SetDlgInt (hDlg, IDED_RIGHT, f->fei.xRight);
      SetDlgInt (hDlg, IDED_DIST,  f->fei.LineWidth);

      CheckRadioButton (hDlg, IDRB_LEFT, IDRB_BLOCK, IDRB_LEFT+f->fei.FormatMode);

      RetVal = TRUE;
      }
      break;
    case WM_COMMAND:
      CRACKER_VARS;
      CRACK_MESSAGEsc

      switch (CRACKER_wID) {
        case IDOK:
          {
          LPFORMATINFO lpf = GetFormatInfo (nFormatNr);
          FontInfo FAR *f = &lpf->fi;
          
          GetDlgItemText (hDlg, IDED_NAME,  f->FormatName, sizeof(f->FormatName));
          GetDlgItemText (hDlg, IDED_DESCR, f->FormatDesc, sizeof(f->FormatDesc));
          f->fei.xLeft = GetDlgInt (hDlg, IDED_LEFT);
          f->fei.xRight = GetDlgInt (hDlg, IDED_RIGHT);
          f->fei.LineWidth = GetDlgInt (hDlg, IDED_DIST);

          for (int i = IDRB_LEFT; i <= IDRB_BLOCK; i++)
            if (IsDlgButtonChecked (hDlg, i) > 0) {
              f->fei.FormatMode = i-IDRB_LEFT;
              break;
              }

          ResetHandles (lpf);
          PaintFont (GetParent(hDlg), nFormatNr);
          RetVal = TRUE;
          EndDialog(hDlg, RetVal);
          break;
          }
        case IDCANCEL:
          EndDialog(hDlg, FALSE);
          break;
        }
      break;
    }    
  
  return RetVal;
  }


BOOL GetInfoDialogBox (HWND hDlg, int nFormatNr)
  {
  DLGPROC dlgProc = DLGPROC (MakeProcInstance (FARPROC(ExtraFormatInfoDlgProc), MyInstance));
  BOOL res = DialogBoxParam (MyInstance, "EXTRAFORMATINFO", hDlg, dlgProc, MAKELPARAM(nFormatNr, 0));
  FreeProcInstance (dlgProc);
  
  return res;
  }

////////////////////////////////////////////////////////////////////////////
//
//   Deklarationen f�r die allgemeine Format Dialogbox 
//   (Liste aller verf�gbaren Formate, Preview)
//
//
////////////////////////////////////////////////////////////////////////////
static HWND hFmtWnd ;

void PushIntStr (LPSTR txt, LPSTR patt, int id)
  {
  char buffer[50];
  wsprintf (buffer, patt, id);
  lstrcat (txt,buffer);
  }

void PushDecStr (LPSTR txt, LPSTR patt, double id)
  {
  char buffer[50];
  char szdbl[10];
  
  prfloat (szdbl, id);
  wsprintf (buffer, patt, LPSTR(szdbl));
  lstrcat (txt, buffer);
  }

void PushStr (LPSTR txt,LPSTR patt)
  {
  lstrcat (txt,patt);
  }

void ShowDescription (HWND hDlg, WORD Ident)
  {
  // Ermitteln des zu interpretierenden Blockes
  LPFORMATINFO lpf = GetFormatInfo (Ident);
  FontInfo FAR *f = &lpf->fi;

  char dsc[200];
  *dsc = '\0' ;
  PushIntStr (dsc, MyLRString(IDS_DSC+0),f->Ident);
  PushStr    (dsc,MyLRString(IDS_DSC+1));
  char faceName[32];
  lstrcpy (faceName,f->lf.lfFaceName);
  PushStr    (dsc,faceName);
  PushIntStr (dsc,MyLRString(IDS_DSC+2),f->cf.iPointSize/10);

  if (f->DefFormat & FI_BOLD)
    PushStr (dsc,MyLRString(IDS_DSC+10));
  if (f->DefFormat & FI_ITALIC)
    PushStr (dsc,MyLRString(IDS_DSC+11));
  if (f->DefFormat & FI_UNDERLINE)
    PushStr (dsc,MyLRString(IDS_DSC+12));
  if (f->DefFormat & FI_STRIKEOUT)
    PushStr (dsc,MyLRString(IDS_DSC+13));

  PushStr    (dsc, MyLRString(IDS_DSC+3+f->fei.FormatMode));
  PushDecStr (dsc, MyLRString(IDS_DSC+7), double(f->fei.xLeft) / TWIPSTOMM);
  PushDecStr (dsc, MyLRString(IDS_DSC+8), double(f->fei.xRight) / TWIPSTOMM);
  PushDecStr (dsc, MyLRString(IDS_DSC+9), double(f->fei.LineWidth) / TWIPSTOMM);

  SetDlgItemText (hDlg, IDED_FMTINFO, dsc);
//  SetDlgItemText (hDlg,ID_DESC2,f->FormatDesc);
  }


/*--------------------------------------------------------------------------*\
* Da die Formatnummern nicht lueckenlos sind, wird ueberprueft, an welcher   *
* Stelle in der Liste das Format mit der Nummer <fmtId> wirklich ist.        *
\*--------------------------------------------------------------------------*/
int GetListEntryFromFormatId (int fmtId)
  {
  int i = 0 ;
  for (LPFORMATINFO fi = GetFormatFirst(); fi != NULL; fi = GetFormatNext(fi), i++)
    if (int(fi->fi.Ident) == fmtId)
      return i;
      
  return 0;   
  }

/*--------------------------------------------------------------------------*\
* gibt die Formatnr. anhand des Listeneintrages zur�ck (s.o.)                *
\*--------------------------------------------------------------------------*/
int GetFormatByNr (int Nr)
  {
  int i = 0 ;
  for (LPFORMATINFO fi = GetFormatFirst () ; ((fi != NULL) && (i < Nr)) ; fi = GetFormatNext (fi) , i++) ;
  return fi->fi.Ident;
  }


void FillListBox (HWND hDlg)
  {
  LPFORMATINFO lpfi = GetFormatFirst ();
  for ( ; lpfi != NULL ; ) {
    SendDlgItemMessage (hDlg, IDLB_FORMAT, LB_ADDSTRING, 0, LONG(lpfi->fi.FormatName));
    lpfi = GetFormatNext (lpfi);
    }
  SendDlgItemMessage (hDlg, IDLB_FORMAT, LB_SETCURSEL, 0, 0);
  }


#define XSPACING  20
#define YSPACING  30

#define SCALE float(1.0)

void PaintWindow (HWND hWnd, int nFormatNr)
  {
  char TestTxt[] = "AaBbCcDdEeFf";

  PaintContext pc (hWnd,PENDATA(RGB(0xC0,0xC0,0xC0)),WHITE_BRUSH,DO_WORK);
  RECT r;
  r = *(LPRECT (&pc.cr));
  pc << r ;
  pc.LogicalTwips (0, 0, SCALE);

  int x  = pc.XPHYStoLOG(XSPACING);
  int x1 = pc.XPHYStoLOG(pc.cr.right - XSPACING);
  LPFORMATMETRIC lpfm = GetFormatMetrics (0,MAPTYPE_TYPOGRAPHIC,nFormatNr);
  int y1 ;
  int y = (y1 = pc.YPHYStoLOG(pc.cr.bottom - YSPACING)) - lpfm->yBaseHeight ;
  cField *f = new cField (TRANSPARENT,nFormatNr,x,y,pc.XPHYStoLOG(pc.cr.right - 2 * XSPACING),-1,FALSE);
  f->SetWindow (hWnd);
  f->SetScale (SCALE,MAPTYPE_TYPOGRAPHIC);
  f->SetVOrg (0,0,0);
  *f = TestTxt;
  f->Paint (pc.hDC,0,FALSE);
  pc << Line (x,y1-300,x,y1+20);
  pc << Line (x-20,y1,x+300,y1);
  pc << Line (x1,y1-300,x1,y1+20);
  pc << Line (x1-300,y1,x1+20,y1);
  delete f;
  }


void PaintFont (HWND hDlg, int nFormatNr)
  {
  HWND hWndCtrl = GetDlgItem(hDlg, IDS_PREVIEW);

  InvalidateRect (hWndCtrl, NULL, TRUE);
  UpdateWindow (hWndCtrl);
  PaintWindow (hWndCtrl, nFormatNr);

  ShowDescription (hDlg, nFormatNr);
  }


extern void ReadFormatInfo (void);
int GetLegalFormatNr()
  {
  int mx = 0 ;
  for (LPFORMATINFO fi = GetFormatFirst () ; fi != NULL ; fi = GetFormatNext (fi)) {
    if (int(fi->fi.Ident) >= mx) mx = fi->fi.Ident + 1 ;
    }
  return mx;
  }



BOOL OnLButtonDown (HWND hWnd, LONG lP, int nFormatNr)
  {
  POINT pt;
  pt.x = LOWORD(lP);
  pt.y = HIWORD(lP);
  return DDOnMouseMove (DDTYPE_FORMAT, &nFormatNr, &pt, hWnd, FALSE);
  }

void OnMouseMove (HWND hWnd, LONG lP, int nFormatNr)
  {
  POINT pt;
  pt.x = LOWORD(lP);
  pt.y = HIWORD(lP);
  DDOnMouseMove (DDTYPE_FORMAT, &nFormatNr, &pt, hWnd, FALSE);
  }

void OnLButtonUp (HWND hWnd, LONG lP, int nFormatNr)
  {
  POINT pt;
  pt.x = LOWORD (lP);
  pt.y = HIWORD (lP);
  DDOnMouseMove (DDTYPE_FORMAT, &nFormatNr, &pt, hWnd, TRUE);
  }


WNDPROC DefaultProc;
//-----------------------------------------------------------------
// Dialog-Prozedur um einer Listbox ein Drag&Drop zu ermoeglichen
//-----------------------------------------------------------------
DLLExport LONG _export FAR PASCAL VarListWndProc (HWND hWnd, UINT msg, WPARAM wP, LPARAM lP)
  {
  static int nFormatNr;
  static BOOL CaptureDone;
  LONG RetVal = 0L;

  switch (msg) {
    case WM_LBUTTONDOWN :
#ifdef STRICT
      RetVal = CallWindowProc (WNDPROC(DefaultProc), hWnd, msg, wP, lP);
#else
      RetVal = CallWindowProc (FARPROC(DefaultProc), hWnd, msg, wP, lP);
#endif
      nFormatNr = GetFormatByNr (int (SendMessage (hWnd, LB_GETCURSEL, 0, 0)));

#ifdef WIN32
      SendMessage (GetParent(hWnd),WM_COMMAND,MAKELONG(LBN_SELCHANGE, IDLB_FORMAT), 0);
#else
      SendMessage (GetParent(hWnd),WM_COMMAND,IDLB_FORMAT,MAKELONG(0,LBN_SELCHANGE));
#endif

      if (CaptureDone = OnLButtonDown (hWnd, lP, nFormatNr))
        SetCapture (hWnd);
      break ;

    case WM_MOUSEMOVE :
      if (CaptureDone)
        OnMouseMove (hWnd, lP, nFormatNr);
      else
#ifdef STRICT
        RetVal = CallWindowProc (WNDPROC(DefaultProc), hWnd, msg, wP, lP);
#else
        RetVal = CallWindowProc (FARPROC(DefaultProc), hWnd, msg, wP, lP);
#endif
      break;

    case WM_LBUTTONUP :
      if (CaptureDone) {
        OnLButtonUp (hWnd, lP, nFormatNr);
        ReleaseCapture ();

        RECT rc;
        GetClientRect (hWnd, &rc);
        POINT pt;
        pt.x = LOWORD(lP);
        pt.y = HIWORD(lP);
        if (!PtInRect(&rc, pt))
#ifdef WIN32
          SendMessage (GetParent(hWnd),WM_COMMAND,MAKELONG(0, IDOK),0L);
#else
          SendMessage (GetParent(hWnd),WM_COMMAND,IDOK,0L);
#endif
        }
//      else
#ifdef STRICT
      RetVal = CallWindowProc (WNDPROC(DefaultProc), hWnd, msg, wP, lP);
#else
      RetVal = CallWindowProc (FARPROC(DefaultProc), hWnd, msg, wP, lP);
#endif

      CaptureDone = FALSE;
      break ;  

    default :
#ifdef STRICT
      RetVal = CallWindowProc (WNDPROC(DefaultProc), hWnd, msg, wP, lP);
#else
      RetVal = CallWindowProc (FARPROC(DefaultProc), hWnd, msg, wP, lP);
#endif
    }
  return RetVal ;
  }



extern HWND hWndActEdit;  // Editfenster, welches zum ">" -Knopf gehoert
BOOL DDEnabled;
DLLExport BOOL FAR PASCAL _export FormatInfoDlgProc (HWND hDlg, UINT message, WPARAM wP, LPARAM lP)
  {
  static int nFormatNr;

  BOOL RetVal = FALSE;
  switch (message) {
    case WM_INITDIALOG:            
      {
      char szFormat[10];

      hFmtWnd = hDlg;
      FillListBox (hDlg);
      nFormatNr = 0;

      if (DDEnabled) {
        // Eintrag aus der Editbox abholen, die diesen Vorgang provoziert hat
        SendMessage (hWndActEdit, WM_GETTEXT, sizeof(szFormat), LONG(LPSTR(szFormat)));
        sscanf (szFormat, "%d", &nFormatNr);
        DefaultProc = WNDPROC(SetWindowLong(GetDlgItem(hDlg, IDLB_FORMAT),
                              GWL_WNDPROC, LONG(VarListWndProc)));
        }
      SendDlgItemMessage (hDlg, IDLB_FORMAT, LB_SETCURSEL, 
                          GetListEntryFromFormatId(nFormatNr), 0);
      }
      return (TRUE);

    case WM_PAINT:
      {
      PAINTSTRUCT ps;
      HDC hDC = BeginPaint (hDlg, &ps);

      PaintFont (hDlg, nFormatNr);
      
      EndPaint (hDlg, &ps);
      }

    case WM_COMMAND:               
      CRACKER_VARS
      CRACK_MESSAGEsc

      switch (CRACKER_wID) {
        case IDLB_FORMAT :
          switch (CRACKER_wNotify) {
            case LBN_DBLCLK:
              SendMessage (hDlg, WM_COMMAND, ID_VIEW, 0L);
              break;
            case LBN_SELCHANGE:
              ResetWindowHandles (0);
              nFormatNr = GetFormatByNr (int (SendDlgItemMessage (hDlg, IDLB_FORMAT, LB_GETCURSEL, 0, 0)));
              PaintFont (hDlg, nFormatNr);
              break;
            }  // switch (HIWORD(lParam))
          break ;
        case IDB_FONT:
          GetFontDialogBox (hDlg, nFormatNr);
          break;
        case IDB_DELETE:
          fntDeleteFormat (nFormatNr);
          RebuildList ();
          {
          int index = int(SendDlgItemMessage (hDlg, IDLB_FORMAT, LB_GETCURSEL, 0, 0));
          SendDlgItemMessage (hDlg, IDLB_FORMAT, LB_DELETESTRING, index, 0);
          int mx = int (SendDlgItemMessage (hDlg, IDLB_FORMAT, LB_GETCOUNT, 0, 0L));
          if (index >= mx)
            SendDlgItemMessage (hDlg, IDLB_FORMAT, LB_SETCURSEL, index-1, 0);
          else
            SendDlgItemMessage (hDlg, IDLB_FORMAT, LB_SETCURSEL, index, 0);
          nFormatNr = GetFormatByNr (int (SendDlgItemMessage (hDlg, IDLB_FORMAT, LB_GETCURSEL, 0, 0)));
          PaintFont (hDlg, nFormatNr);
          }
          break;
        case IDB_NEW:
          {
          FontInfo fitmp ;
          lmemset (&fitmp,'\0',sizeof(fitmp)) ;
          nFormatNr = GetLegalFormatNr();
          fntInsertFormat (nFormatNr,&fitmp);
          RebuildList ();
          SendDlgItemMessage (hDlg,IDLB_FORMAT,LB_ADDSTRING,0,LONG(LPSTR("")));
          int Anz = int (SendDlgItemMessage (hDlg,IDLB_FORMAT,LB_GETCOUNT,0,0));
          SendDlgItemMessage (hDlg,IDLB_FORMAT,LB_SETCURSEL,Anz-1,0);
          GetFontDialogBox (hDlg, nFormatNr);
          }
          break;
        case IDB_EXTRA:
          if (GetInfoDialogBox (hDlg, nFormatNr)) {
            LPFORMATINFO lpf = GetFormatInfo (nFormatNr);

            int index = int(SendDlgItemMessage (hDlg, IDLB_FORMAT, LB_GETCURSEL, 0, 0));
            SendDlgItemMessage (hDlg, IDLB_FORMAT, LB_DELETESTRING, index, 0);
            SendDlgItemMessage (hDlg, IDLB_FORMAT, LB_INSERTSTRING, index, LONG(lpf->fi.FormatName));
            SendDlgItemMessage (hDlg, IDLB_FORMAT, LB_SETCURSEL, index, 0);
            }
          break;
        case IDOK:
          if (lP != 0)
            DDOnOKButton (DDTYPE_FORMAT, &nFormatNr, hWndActEdit);
          WriteFormatInfo ();
          fntDeleteAllFormats ();
          ReadFormatInfo ();
          hFmtWnd = 0;
          EndDialog(hDlg, TRUE);
          break;
        case IDCANCEL:
          ResetWindowHandles (0);       // Informationen werden gespeichert
          fntDeleteAllFormats ();
          ReadFormatInfo ();
          hFmtWnd = 0;
          EndDialog(hDlg, FALSE);
          break;
        }  // switch (wParam)
      break;
    }  // switch (message)
  return RetVal;               
  }




//****************************************************************************
//                                                                           *
//  Funktionen f�r die Linien-Stile-Dialogbox                                *
//                                                                           *
//****************************************************************************
LONG     LineAttr;
COLORREF LineColor = 0;
int      LineWidth = 0;
LONG     LineStyle = 0;
LONG     WidthIndex = 0;

const int MAXCOLORS = 16;

DWORD rgColors16[MAXCOLORS] = {RGB(  0,   0, 0),       //Black
                               RGB(128,   0, 0),       //Dark red
                               RGB(  0, 128, 0),       //Dark green
                               RGB(128, 128, 0),       //Dark yellow
                               RGB(  0,   0, 128),     //Dark blue
                               RGB(128,   0, 128),     //Dark purple
                               RGB(  0, 128, 128),     //Dark aqua
                               RGB(128, 128, 128),     //Dark grey
                               RGB(192, 192, 192),     //Light grey
                               RGB(255,   0, 0),       //Light red
                               RGB(  0, 255, 0),       //Light green
                               RGB(255, 255, 0),       //Light yellow
                               RGB(  0,   0, 255),     //Light blue
                               RGB(255,   0, 255),     //Light purple
                               RGB(  0, 255, 255),     //Light aqua
                               RGB(255, 255, 255),     //White
                               };
                               
/*-----------------------------------------------------*\
* gibt den Index der Farbe im 16-Farben-Array zurueck   *
\*-----------------------------------------------------*/
WORD ColorIndex (COLORREF Color)
  {
  for (int i = 0; i < MAXCOLORS; i++)
    if (Color == rgColors16[i])
      return i;
      
  return 0;   
  }

/*-----------------------------------------------------*\
* ruft die Farbdialogbox aus der COMMDLG.DLL auf        *
\*-----------------------------------------------------*/
COLORREF GetCommonColor (HWND hDlg)
  {
  CHOOSECOLOR  cc;

  lmemset(&cc, 0, sizeof(CHOOSECOLOR));
  cc.lStructSize = sizeof(CHOOSECOLOR);

  cc.lpCustColors = rgColors16;    

  cc.hwndOwner = hDlg;
  cc.rgbResult = LineColor;
  cc.Flags = CC_RGBINIT | CC_FULLOPEN;
  ChooseColor(&cc);

  return cc.rgbResult;
  }


/*--------------------------------------------------------------------------*\
* zeichnet eine Linie mit dem gewuenschten Stil und der Farbe                *
\*--------------------------------------------------------------------------*/
void PaintLine (HDC hDC, RECT rc, WORD Style, COLORREF Color)
  {
  InflateRect (LPRECT(&rc), -1, -1);
  SetBkColor (hDC, RGB(0xC0, 0xC0, 0xC0));
  ExtTextOut (hDC, 0, 0, ETO_OPAQUE, &rc, NULL, 0, NULL);

  double mapFact = double (GetDeviceCaps(hDC, LOGPIXELSX)/1440.0);
  LineWidth = (int(WidthIndex)*(GetDeviceCaps(hDC, LOGPIXELSX))/72);

  HPEN OldPen = (HPEN)SelectObject (hDC, CreatePen (PS_SOLID, LineWidth, Color));

  MyMoveTo (hDC, rc.left, (rc.top+rc.bottom) / 2);
  MyLineTo (hDC, rc.right, (rc.top+rc.bottom) / 2, mapFact, Style, LineWidth);

  DeleteObject (SelectObject(hDC, OldPen));
  }


/*--------------------------------------------------------------------------*\
*                                                                            *
\*--------------------------------------------------------------------------*/
BOOL OnPreviewLButtonDown (HWND hWnd, LONG lP)
  {
  POINT pt;
  pt.x = LOWORD(lP);
  pt.y = HIWORD(lP);
  return DDOnMouseMove (DDTYPE_COLOR, &LineAttr, &pt, hWnd, FALSE);
  }

/*--------------------------------------------------------------------------*\
*                                                                            *
\*--------------------------------------------------------------------------*/
void OnPreviewMouseMove (HWND hWnd, LONG lP)
  {
  POINT pt;
  pt.x = LOWORD(lP);
  pt.y = HIWORD(lP);
  DDOnMouseMove (DDTYPE_COLOR, &LineAttr, &pt, hWnd, FALSE);
  }

/*--------------------------------------------------------------------------*\
*                                                                            *
\*--------------------------------------------------------------------------*/
void OnPreviewLButtonUp (HWND hWnd, LONG lP)
  {
  POINT pt;
  pt.x = LOWORD (lP);
  pt.y = HIWORD (lP);
  DDOnMouseMove (DDTYPE_COLOR, &LineAttr, &pt, hWnd, TRUE);
  }



/*--------------------------------------------------------------------------*\
*                                                                            *
\*--------------------------------------------------------------------------*/
WNDPROC StaticPreviewDefaultProc;
DLLExport LONG _export FAR PASCAL StaticPreviewWndProc (HWND hWnd, UINT msg, WPARAM wP, LPARAM lP)
  {
  LONG Res = 0L;
  static BOOL Captured;

  switch (msg) {
    case WM_PAINT:
    case WM_NCPAINT:
    case WM_ERASEBKGND:
      {
      RECT rc;
      GetClientRect (hWnd, LPRECT(&rc));
    
      HDC hDC = GetDC (hWnd);
      HRGN hRgn = CreateRectRgn (rc.left, rc.top, rc.right, rc.bottom);
      SelectClipRgn (hDC, hRgn);

      PaintLine (hDC, rc, int(LineStyle & 0xF), LineColor);

      SelectClipRgn (hDC, NULL);
      DeleteObject (hRgn);
      ReleaseDC (hWnd, hDC);
      Res = 0L;
      break;
      }

    case WM_LBUTTONDOWN:
      Captured = OnPreviewLButtonDown (hWnd, lP);
      if (Captured)
        SetCapture (hWnd);
      Res = 0L;
      break;
    
    case WM_MOUSEMOVE:
      if (Captured) 
        OnPreviewMouseMove (hWnd, lP);
      Res = 0L;
      break;

    case WM_LBUTTONUP:
      if (Captured) {
        OnPreviewLButtonUp (hWnd, lP);
        ReleaseCapture();
        Captured = FALSE;
        SendMessage (GetParent(hWnd),WM_COMMAND,IDOK,0L);
        }
      Res = 0L;
      break;
    
    default:  
#ifdef STRICT
      Res = CallWindowProc (WNDPROC(StaticPreviewDefaultProc), hWnd, msg, wP, lP);
#else
      Res = CallWindowProc (FARPROC(StaticPreviewDefaultProc), hWnd, msg, wP, lP);
#endif
    }
  return Res;
  }


/*--------------------------------------------------------------------------*\
*  Linie mit dem Up-Down-Control                                             *
\*--------------------------------------------------------------------------*/
WNDPROC StaticLineDefaultProc;
DLLExport LONG _export FAR PASCAL StaticLineWndProc (HWND hWnd, UINT msg, WPARAM wP, LPARAM lP)
  {
  switch (msg) {
    case WM_PAINT:
    case WM_NCPAINT:
    case WM_ERASEBKGND:
      {
      char szPtSize[10];
      RECT rc;
      GetClientRect (hWnd, LPRECT(&rc));
    
      HDC hDC = GetDC (hWnd);
      HRGN hRgn = CreateRectRgn (rc.left, rc.top, rc.right, rc.bottom);
      SelectClipRgn (hDC, hRgn);

      PaintLine (hDC, rc, PS_SOLID, 0);

      rc.right /= 2;
      if (((WidthIndex+1)/2) > 0)
        sprintf (szPtSize, " %lu", (WidthIndex+1)/2);
      else
        lstrcpy (szPtSize, " ");

      if ((WidthIndex+1) % 2)
        lstrcat (szPtSize, "�");
      lstrcat (szPtSize, " pt.");

	    int dx, dy;
#ifdef WIN32
	    SIZE size;

      GetTextExtentPoint32 (hDC, szPtSize, lstrlen(szPtSize), &size);
      dx = size.cx;
      dy = size.cy;
#else
      DWORD extent = GetTextExtent(hDC, szPtSize, lstrlen(szPtSize));
      dx = LOWORD(extent);
      dy = HIWORD(extent);
#endif

      ExtTextOut (hDC, rc.left, ((rc.bottom-rc.top)-dy) / 2, 
                  ETO_OPAQUE, &rc, szPtSize, lstrlen(szPtSize), NULL);
      
      SelectClipRgn (hDC, NULL);
      DeleteObject (hRgn);
      ReleaseDC (hWnd, hDC);
      return 0L;
      break;
      }
    default:  
#ifdef STRICT
      return CallWindowProc (WNDPROC(StaticLineDefaultProc), hWnd, msg, wP, lP);
#else
      return CallWindowProc (FARPROC(StaticLineDefaultProc), hWnd, msg, wP, lP);
#endif
    }
  }



#define IDB_COLOR       101
#define ID_SPINWIDTH    102
#define IDS_PREVIEWLINE 103
#define IDS_WIDTH       104
#define IDCB_STYLE      105
#define IDCB_COLOR      106

/*--------------------------------------------------------------------------*\
*                                                                            *
\*--------------------------------------------------------------------------*/
void DrawItemStyle (LPDRAWITEMSTRUCT pDI)
  {
  COLORREF  crBack;

  if ((int)pDI->itemID < 0)
    return;

  if (pDI->itemAction & (ODA_DRAWENTIRE | ODA_SELECT)) {
    if (ODS_SELECTED & pDI->itemState) {
      // setze die Hintergrundfarbe bei selektierten Eintr�gen
      crBack = SetBkColor(pDI->hDC, GetSysColor(COLOR_HIGHLIGHT));
      }

    // setze die Hintergrundfarben f�r ExtTextOut
    if (pDI->CtlID == IDCB_COLOR) {
      crBack = SetBkColor(pDI->hDC, rgColors16[pDI->itemID]);
      InflateRect (&pDI->rcItem, -3, -3);
      }
    
    // bei der Stil-Box wird nur bei der Selektion die Hintergrundfarbe gesetzt,
    // bei der Farb-Box wird jede Grundfarbe gezeichnet
    ExtTextOut (pDI->hDC, pDI->rcItem.left, pDI->rcItem.top, ETO_OPAQUE,
               &pDI->rcItem, NULL, 0, NULL);

    if (pDI->CtlID == IDCB_STYLE) {
      double mapFact = double (GetDeviceCaps(pDI->hDC, LOGPIXELSX)/1440.0);
  
      MyMoveTo (pDI->hDC, pDI->rcItem.left, (pDI->rcItem.top+pDI->rcItem.bottom) / 2);
      MyLineTo (pDI->hDC, pDI->rcItem.right, (pDI->rcItem.top+pDI->rcItem.bottom) / 2, 
                mapFact, pDI->itemID, 0);
      }
    
    //Restore original colors if we changed them above.
    if (pDI->itemState & ODS_SELECTED)
      SetBkColor(pDI->hDC,   crBack);
    }

  if ((pDI->itemAction & ODA_FOCUS) || (pDI->itemState & ODS_FOCUS))
    DrawFocusRect(pDI->hDC, &pDI->rcItem);

  return;
  }


/*--------------------------------------------------------------------------*\
*                                                                            *
\*--------------------------------------------------------------------------*/
DLLExport BOOL FAR PASCAL _export LineStyleDlgProc (HWND hDlg, UINT msg, WPARAM wP, LPARAM lP)
  {
  BOOL RetVal = FALSE;

  switch (msg) {
    //-----------------------------------------------------------------
    case WM_INITDIALOG:
      {
      int i;
      char szColor[25];

      if (DDEnabled) {
        // Eintrag aus der Editbox abholen, die diesen Vorgang provoziert hat
        SendMessage (hWndActEdit, WM_GETTEXT, sizeof(szColor), LONG(LPSTR(szColor)));
        sscanf (szColor, "<long(%ld)>", &LineAttr);
        }
      
      LineColor = LineAttr & 0x00FFFFFF;
      WidthIndex = (LineAttr & 0x0F000000) >> 24;
      LineStyle = (LineAttr & 0xF0000000) >> 28;

#ifndef WIN32
      // Strichst�rke nur von 1/2 pkt. bis 8 pkt. (Schrittweite 1/2 pkt.)
      MSDwRangeSet (GetDlgItem(hDlg, ID_SPINWIDTH), 0, 15);
      MSWCurrentPosSet (GetDlgItem(hDlg, ID_SPINWIDTH), int(WidthIndex & 0x0F));
#endif

      // Linienstile an die Combo-Box und gleich den richtigen Stil anzeigen
      SendMessage(GetDlgItem(hDlg, IDCB_STYLE), CB_RESETCONTENT, 0, 0L);
      for (i = 0; i < 5; i++)
        SendMessage (GetDlgItem(hDlg, IDCB_STYLE), CB_ADDSTRING, 0, 0L);
      SendMessage (GetDlgItem(hDlg, IDCB_STYLE), CB_SETCURSEL, int(LineStyle & 0xF), 0L);

      // Linienfarben an die Combo-Box und gleich die richtige Farbe anzeigen
      for (i = 0; i < 15; i++)
        SendMessage (GetDlgItem(hDlg, IDCB_COLOR), CB_ADDSTRING, 0, 0L);
      SendMessage (GetDlgItem(hDlg, IDCB_COLOR), CB_SETCURSEL, 
                   ColorIndex(LineColor), 0L);

      // Prozeduren der statischen Elemente speichern und neu besetzen
      StaticPreviewDefaultProc = WNDPROC(SetWindowLong(GetDlgItem(hDlg, IDS_PREVIEWLINE),
                                       GWL_WNDPROC, LONG(StaticPreviewWndProc)));
      StaticLineDefaultProc = WNDPROC(SetWindowLong(GetDlgItem(hDlg, IDS_WIDTH),
                                       GWL_WNDPROC, LONG(StaticLineWndProc)));
      RetVal = TRUE;
      }
      break;

    //-----------------------------------------------------------------
    // informiert Windows bzw.die Combo-Box �ber die H�he der Eintr�ge
    case WM_MEASUREITEM:
      {
      LPMEASUREITEMSTRUCT pMI;

      pMI = (LPMEASUREITEMSTRUCT)lP;
      if ((wP == IDCB_STYLE) || (wP == IDCB_COLOR))
        pMI->itemHeight = 20;
      RetVal = TRUE;
      }
      break;

    //-----------------------------------------------------------------
    case WM_DRAWITEM:
      DrawItemStyle ((DRAWITEMSTRUCT FAR *)lP);
      RetVal = TRUE;
      break;  

    //-----------------------------------------------------------------
    // die Spin-Box meldet sich mit einer Scroll-Nachricht
    case WM_VSCROLL:
#ifdef WIN32
      if (LOWORD(wP) == SB_THUMBTRACK)
#else
      if (wP == SB_THUMBTRACK)
#endif
        break;

      HWND hWndCntrl;

#ifdef WIN32
      hWndCntrl = HWND(lP);
#else
      hWndCntrl = HWND(HIWORD(lP));
#endif
      if (hWndCntrl == GetDlgItem(hDlg, ID_SPINWIDTH)) {

#ifdef WIN32
        WidthIndex = LONG(HIWORD(wP));
#else
        WidthIndex = LONG(LOWORD(lP));
#endif
        InvalidateRect (GetDlgItem(hDlg, IDS_WIDTH), NULL, TRUE);
        InvalidateRect (GetDlgItem(hDlg, IDS_PREVIEWLINE), NULL, TRUE);
        UpdateWindow (hDlg);
        }
      break;
      
    //-----------------------------------------------------------------
    // da die statischen Elemente keine Mausnachrichten auswerten, mu�
    // man WINDOWS(�) ein bisschen bescheissen, und die Events die an
    // die Dialog-Box gehen weiter an das statische Element schicken!
    case WM_LBUTTONDOWN:
    case WM_MOUSEMOVE:
    case WM_LBUTTONUP:
      if (DDEnabled) {
        RECT rc;
        POINT pt;
      
        // Screen-Koordinaten des Preview-Static-Elementes
        GetWindowRect (GetDlgItem(hDlg, IDS_PREVIEWLINE), LPRECT(&rc));

#ifdef WIN32
        LONG2POINT (lP, pt);
#else
        pt = MAKEPOINT (lP);
#endif

        // Screen-Koordinaten der Maus
        ClientToScreen (hDlg, &pt);
        if (PtInRect(&rc, pt)) {  // Maus-Event im Preview-Fenster?
          LineAttr = LineColor;
          LineAttr |= (WidthIndex & 0xF) << 24;
          LineAttr |= (LineStyle & 0xF) << 28;

          ScreenToClient (GetDlgItem(hDlg, IDS_PREVIEWLINE), (POINT FAR*)&lP);
          SendMessage (GetDlgItem(hDlg, IDS_PREVIEWLINE), msg, wP, lP);
          }
        }
      break;

    //-----------------------------------------------------------------
    // wird von den Steuerelementen in der Dialogbox verschickt
    case WM_COMMAND:
      CRACKER_VARS
      CRACK_MESSAGEsc

      switch (CRACKER_wID) {
        //---------------------------------------------------
        // Aufruf der Dialogbox f�r die Festlegung der Farben
        case IDB_COLOR:
          LineColor = GetCommonColor (hDlg);
          InvalidateRect (hDlg, NULL, FALSE);
          break;

        case IDCB_COLOR:
        case IDCB_STYLE:
          {
          int i = (UINT)SendMessage(GetDlgItem(hDlg, CRACKER_wID), CB_GETCURSEL, 0, 0L);
          if (CRACKER_wID == IDCB_COLOR)
            LineColor = rgColors16[i];
          else
            LineStyle = i;
            
          InvalidateRect (GetDlgItem(hDlg, IDS_PREVIEWLINE), NULL, TRUE);
          UpdateWindow (hDlg);
          }
          break;

        case IDOK:
          {
          LineAttr = LineColor;
          LineAttr |= (WidthIndex & 0xF) << 24;
          LineAttr |= (LineStyle & 0xF) << 28;
          
          if (lP != 0)
            DDOnOKButton (DDTYPE_COLOR, &LineAttr, hWndActEdit);
          EndDialog (hDlg, TRUE);
          RetVal = TRUE;
          }
          break;

        case IDCANCEL:
          EndDialog (hDlg, FALSE);
          RetVal = FALSE;
          break;
        }   // end switch (wP)
      break;

    }  // end switch (msg)
  return RetVal;
  }




//**************************************************************************
//*                                                                        *
//*          Funktionen die vom Hauptprogramm aufgerufen werden            *
//*                                                                        *
//**************************************************************************
void ShowFormat (HWND hWnd, BOOL EnableDragDrop)
  {
  DDEnabled = EnableDragDrop;
  if (hFmtWnd)
    ShowWindow (hFmtWnd,SW_SHOW);
  else {
    DLGPROC dlgProc = DLGPROC (MakeProcInstance (FARPROC(FormatInfoDlgProc), MyInstance));
    DialogBox (MyInstance, "FORMATINFO", hWnd, (DLGPROC)dlgProc);
    FreeProcInstance (dlgProc);
    }
  DDEnabled = FALSE;   // vorsichtshalber Drag & Drop wieder disablen
  }


COLORREF ShowColor (HWND hWnd, BOOL EnableDragDrop)
  {
  DDEnabled = EnableDragDrop;

  DLGPROC dlgProc = DLGPROC (MakeProcInstance (FARPROC(LineStyleDlgProc), MyInstance));
  DialogBox (MyInstance, "LINESTYLE", hWnd, dlgProc);
  FreeProcInstance (dlgProc);

  DDEnabled = FALSE;   // vorsichtshalber Drag & Drop wieder disablen

  return LineColor;
  }


  
