//  Implementierung der Objekte (speziell fuer Form)
//
/////////////////////////////////////////////////////////////////////////
// $Header:   P:/marille/clinicum/frmobj/rev/frmobj.cpv   1.96   10 Apr 2000 15:02:14   Wolfgang  $
// $Log:   P:/marille/clinicum/frmobj/rev/frmobj.cpv  $
// 
//    Rev 1.96   10 Apr 2000 15:02:14   Wolfgang
// 1.) Feld-Update bei allen Feldern mit Button.
// 
//    Rev 1.95   07 Apr 2000 17:12:12   Wolfgang
// 1.) Feld-Update nur bei BTNWITHINPUT statt nicht bei demselben.
// 
//    Rev 1.94   21 Feb 2000 08:13:42   Hannes
// 
//    Rev 1.93   16 Feb 2000 23:35:24   Hannes
// Updateverhalten etwas modifiziert
// 
//    Rev 1.92   25 Nov 1999 02:52:32   Hannes
// ObjInfo als String
// 
//    Rev 1.91   23 Nov 1999 17:23:32   Hannes
// @ - Interpretation in Hilfstext...
// 
//    Rev 1.90   04 Aug 1999 18:27:24   Wolfgang
// 1.) Datum/Zeit +, - etc. Umbau von OnChar auf IsCharCallbackInstalled.
// 2.) skipNextChar eingebaut.
// 
//    Rev 1.89   28 Jul 1999 16:50:30   Wolfgang
// 1.) Datum mittels (h)eute,(g)estern,(m)orgen,(+),(-) setzbar.
// 2.) Zeit mittels (j)etzt,(+),(-) setzbar.
// 
//    Rev 1.88   15 Jun 1999 16:27:48   WOLFGANG
// 1.) TimeNow durch Now ersetzt.
// 
//    Rev 1.87   25 Nov 1998 19:22:44   Martin
// WIN_ASSERT bei SetInactiveIf raus
// 
//    Rev 1.86   09 Oct 1998 18:53:38   Hannes
// Farbfunktionen in Strings
// 
//    Rev 1.85   05 Oct 1998 11:18:28   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.84   16 Sep 1998 11:54:00   Hannes
// Updateverhalten nur, wenn kein Knopf vorhanden ist
// 
//    Rev 1.83   15 Sep 1998 18:34:10   Hannes
// Neuformatierung beim Update erst, wenn Feld nicht mehr den Focus hat...
// 
//    Rev 1.82   19 Aug 1998 21:33:40   Hannes
// Listenobj NULL
// 
//    Rev 1.81   09 Jul 1998 17:49:34   Hannes
// 
//    Rev 1.80   02 Jul 1998 16:58:56   Hannes
// Erweiterte Sonderzeichen
// 
//    Rev 1.79   29 Jun 1998 19:53:10   Hannes
// 
//    Rev 1.78   08 Jun 1998 23:31:04   Hannes
// Neuen Checktyp
// 
//    Rev 1.77   08 Jun 1998 14:57:48   Martin
// FieldColor eingebaut
// 
//    Rev 1.76   04 Jun 1998 15:52:10   Hannes
// SetDirKey sauber
// 
//    Rev 1.75   16 Mar 1998 12:07:00   Hannes
// Bei SetActiveExplicit: Initialized abgefragt
// 
//    Rev 1.74   17 Feb 1998 09:01:50   Hannes
// Oje Oje, da hat der Gerhold noch ein explicit vergessen
// 
//    Rev 1.73   16 Feb 1998 08:05:56   Gerhold
// VC++5.x ... explicit darf nicht als Var. verwendet werden (Schluesselwort)
// 
//    Rev 1.72   09 Feb 1998 18:12:40   Hannes
// Rueckbau der Funktione SetInactiveIf
// 
//    Rev 1.71   03 Feb 1998 19:29:26   Hannes
// SetInactiveIf: Keine Daten loeschen
// 
//    Rev 1.70   03 Feb 1998 11:42:50   Hannes
// WorkOn->RefForWrite neu belegen
// 
//    Rev 1.69   16 Dec 1997 12:00:12   Martin
// lpMenu in RemoveContext auf NULL setzen
// 
//    Rev 1.68   15 Dec 1997 17:59:18   Hannes
// Cursor - Handling 32 BIT
// 
//    Rev 1.67   01 Dec 1997 19:39:14   Hannes
// Diverse Anpassungen, Format variabel
// 
//    Rev 1.66   29 Oct 1997 18:58:10   Hannes
// Textbausteine
// 
//    Rev 1.65   26 Sep 1997 16:44:10   Gerhold
// das Modify-Flag kann im Kontext-Menu geloescht werden
// 
//    Rev 1.64   26 Sep 1997 10:14:54   Gerhold
// in HandlePopupMenu (LPtoDP wegen scrollen)
// 
//    Rev 1.63   17 Sep 1997 14:58:16   Hannes
// DoSelect im Fall neu Berechnen
// 
//    Rev 1.62   08 Sep 1997 11:02:56   Gerhold
// Grosse Aenderungen fuer rechte Maustaste in Formularen
// 
//    Rev 1.61   08 Aug 1997 21:31:06   Martin
// CheckBox::GetMinMax: HalfPenWidth beruecksichtigen
// 
//    Rev 1.60   08 Aug 1997 21:12:26   Martin
// CHECK_RADIO: naechster Versuch
// 
//    Rev 1.59   08 Aug 1997 20:52:20   Martin
// CHECK_RADIO verbessert
// 
//    Rev 1.58   06 Aug 1997 14:55:18   Martin
// Set/ClearConnections auf alle Parameter von CheckBox und CheckField
// 
//    Rev 1.57   06 Aug 1997 14:14:12   Martin
// CHECK_RADIO
// 
//    Rev 1.56   27 Jun 1997 18:59:16   gerhold
// FrmDec::OnValRead ...... if (RefForWrite != 0L)
// 
//    Rev 1.55   26 Jun 1997 18:24:46   Hannes
// 
//    Rev 1.54   25 Jun 1997 10:29:52   Hannes
// 
//    Rev 1.53   20 Jun 1997 22:03:06   Hannes
// 
//    Rev 1.52   17 Jun 1997 17:57:32   Gerhold
// TranslateColor ... color == 0L auskommentiert
// 
//    Rev 1.51   13 Mar 1997 19:08:30   Hannes
// RefForWrite ... Flag, das beim Beschreiben einer Variable gesetzt wird
// 
//    Rev 1.50   07 Mar 1997 11:26:10   Hannes
// FrmField::Update neu geschrieben
// 
//    Rev 1.49   19 Feb 1997 12:11:04   Hannes
// Connection auf Anzahl Zeilen
// 
//    Rev 1.48   08 Nov 1996 13:32:04   HANNES
// Zahlenformatierung
// 
//    Rev 1.47   28 Oct 1996 08:42:24   HANNES
// Beim DblClk Aufruf der Liste
// 
//    Rev 1.46   08 Oct 1996 11:09:08   MARTIN
// FrmField::Update -> wenn Update, wo FldPos immer noch nicht definiert
// ist, dann kann field == NULL sein -> entsprechende Abfrage
// 
//    Rev 1.45   06 Aug 1996 18:10:38   MARTIN
// Fehlerkorrektur: wenn Feld nicht Initialized war und IsEnables sich
// aenderte, bekam das das Feld nicht mit.
// 
//    Rev 1.44   17 Jun 1996 17:22:08   MARTIN
// Formatangabe beim DefFrmTime
// 
//    Rev 1.43   10 Jun 1996 10:11:42   GERHOLD
// int FAR * => DBINT FAR *
// 
//    Rev 1.42   18 May 1996 20:51:18   HANNES
// FrmField::Save
// 
//    Rev 1.41   04 Apr 1996 15:21:34   GERHOLD
// FrmMoney .... Formatierungen geaendert
// 
//    Rev 1.40   24 Mar 1996 12:11:14   HANNES
// UmStellung auf mehrseitige cFields
// 
//    Rev 1.39   22 Mar 1996 12:15:26   HANNES
// Aenderungen Hannes
// 
//    Rev 1.38   02 Feb 1996 10:49:04   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.37   11 Jan 1996 03:30:28   HANNES
// 
//    Rev 1.36   10 Jan 1996 18:22:58   MARTIN
// FrmField::OnCaretPosChange
// 
//    Rev 1.35   12 Dec 1995 12:12:52   GERHOLD
// FrmObj::SetActiveIf (Abfrage auf GetActiveField() == NULL)
// 
//    Rev 1.34   23 Nov 1995 17:41:44   GERHOLD
// SetFieldMode "ODERt" zum Parameter mode cField::GetFieldMode
// 
//    Rev 1.33   20 Nov 1995 11:45:48   HANNES
// GetLastFormPressedChar
// 
//    Rev 1.32   09 Nov 1995 20:24:08   MARTIN
// CHECK_TRIPLE
// 
//    Rev 1.31   31 Oct 1995 10:45:46   GERHOLD
// Gueltigkeitsueberpruefung fuer short, long, money - Felder
// 
//    Rev 1.30   01 Sep 1995 09:02:58   HANNES
// 
//    Rev 1.29   27 Aug 1995 21:36:24   HANNES
// 
//    Rev 1.28   27 Aug 1995 12:46:04   HANNES
// FrmShort,FrmLong,FrmMoney
// 
//    Rev 1.27   24 Aug 1995 00:15:06   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.26   10 Aug 1995 09:21:08   HANNES
// Connect Fields,Checkboxen, Formatdate
// 
//    Rev 1.25   26 Jul 1995 14:29:12   HANNES
// ProjectPoint - Erweiterung
// 
//    Rev 1.24   11 Jul 1995 12:45:44   HANNES
// 
//    Rev 1.23   11 Jun 1995 19:18:50   MARTIN
// Laengenbegrenzung bei Formularfelder
// 
//    Rev 1.22   11 Jun 1995 10:05:02   HANNES
// Errweiterungen fuer die Druckvorlagen
// 
//    Rev 1.21   12 Apr 1995 12:29:14   HANNES
// 
//    Rev 1.20   04 Apr 1995 12:14:58   HANNES
// 
//    Rev 1.19   02 Apr 1995 17:48:24   HANNES
// 
//    Rev 1.18   31 Mar 1995 13:11:22   HANNES
// 
//    Rev 1.17   20 Mar 1995 12:13:34   HANNES
// Konstantenhanling, RunNmbr
// 
//    Rev 1.16   10 Jan 1995 17:25:02   HANNES
// Syntaxkorrektur fuer 8er Compiler
// 
//    Rev 1.15   09 Jan 1995 12:11:08   HANNES
// Debugger eingebaut
// 
//    Rev 1.14   05 Dec 1994 17:41:16   HANNES
// Endgueltiger Einbau der Expressions
// 
//    Rev 1.13   20 Nov 1994 18:01:20   HANNES
// Combobuttom fuer Felder mit Callbackfunktion
// 
//    Rev 1.12   15 Nov 1994 10:57:32   HANNES
// 
//    Rev 1.11   11 Nov 1994 17:31:26   MARTIN
// DBWIN_ASSERT in Invalidate entschaerft
// 
//    Rev 1.10   10 Nov 1994 14:30:32   MARTIN
// top < bottom
// 
//    Rev 1.9   20 Oct 1994 17:52:26   GERHOLD
// FrmField - Maus - Nachrichten
// 
//    Rev 1.8   17 Oct 1994 14:59:38   HANNES
// Opaque bei Feldern nur in Formularen
// 
//    Rev 1.7   13 Oct 1994 19:09:56   GERHOLD
// 
//    Rev 1.6   13 Oct 1994 18:23:48   GERHOLD
// im cField-Konstruktor von TRANSPARENT auf OPAQUE
// 
//    Rev 1.5   22 Sep 1994 16:10:38   GERHOLD
// Callbackfunktionen fuer Farbaenderung in der ObjList (GetSysColor)
// 
//    Rev 1.4   20 Sep 1994 11:24:48   HANNES
// Trc_DefFilledCont
// 
//    Rev 1.3   09 Aug 1994 09:31:36   HANNES
// FrmTime
// 
//    Rev 1.2   25 Jul 1994 18:12:28   HANNES
// SetButtonField
// 
//    Rev 1.1   27 Jun 1994 11:00:52   MARTIN
// exportierte virtuelle Funktionen nicht mehr inline
// 
//    Rev 1.0   24 Jun 1994 16:45:42   MARTIN
// Neuuebernahme clinicum
//

#include <windows.h>
#include <stdio.h>
#include <math.h>
#include "dds32.h"
#define NODDSDATA
#include "dds.hpp"
#include "dds.h"
#include "printer.hpp"
#include "sc2d.hpp"
#include "font.hpp"
#include "paint.hpp"
#define CARETHANDLING_DONE
#include "globmem.h"
#include "cfield.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "scripthd.hpp"
#include "mdichild.hpp"
#define DLLCHILD_MAIN
#include "dllchild.hpp"

#define MODULENUM     4
#include "winass.hpp"

#include "mdiclien.hpp"
#include "dictlist.hpp"
#include "voronoi.hpp"
#include "frmobj.hpp"

#include "cntmenu.hpp"


//------------------------------------------
// Identifier fuer Kontext-Menu
//------------------------------------------
#define   MI_TODAY   105
#define   MI_TIME    106

#define   MI_RESET   110


BOOL BlockIsActive;

// Ersatzfunktion fuer SCHEISS Microsoft Library
extern BOOL strtofloat (LPSTR txt,float FAR *f);
static BOOL _ForEdit;

DLLExport _export WINAPI FrmObject::FrmObject (LPVOID p,mdiChild *mc)
  { 
  ScriptParam = LPFRMOBJHEADER (p);
  m.PrivData = mc;
  if (!_ForEdit) {
    LPCONNEXTRAINFO x = mc->_GetRecExtra () ;
    if (x != NULL) {
      m.Extra = LPCONNEXTRAINFO (GetGlobMem (GetBlockSize(x)));
      lmemcpy (m.Extra,x,GetBlockSize(x));
      }
    else
      m.Extra = NULL;
    }
  else
    m.Extra = NULL;

  lpMenu = NULL;     // noch nix im Kontext-Menu
  for (int i = 0 ; i < sizeof(NObjs) / sizeof(*NObjs) ; i++)
    NObjs[i] = 0xFFFFFFFF;
  }
DLLExport _export WINAPI FrmField::FrmField (LPVOID p,mdiChild *c) : FrmObject (p,c)
  {
  MaxStringSize = -1;
  ModifyParam = 0xFFFFFFFF ;
  ColorParam = 0xFFFFFFFF ;
  FieldColor = 0xFFFFFFFF ;
  }

DLLExport _export WINAPI FrmBField::FrmBField (LPVOID p,mdiChild *c) : FrmField (p,c) { }
DLLExport _export WINAPI FrmSlantField::FrmSlantField (LPVOID p,mdiChild *c) : FrmField (p,c) { }
DLLExport _export WINAPI FrmMultiField::FrmMultiField (LPVOID p,mdiChild *c) : FrmField (p,c) { }
DLLExport _export WINAPI FrmTabField::FrmTabField (LPVOID p,mdiChild *c) : FrmField (p,c) { }
DLLExport _export WINAPI FrmDate::FrmDate (LPVOID p,mdiChild *c) : FrmField (p,c) { }
DLLExport _export WINAPI FrmTime::FrmTime (LPVOID p,mdiChild *c) : FrmField (p,c) { }
DLLExport _export WINAPI FrmTabDate::FrmTabDate (LPVOID p,mdiChild *c) : FrmDate (p,c) { }
DLLExport _export WINAPI FrmSozNr::FrmSozNr (LPVOID p,mdiChild *c) : FrmField (p,c) { }
DLLExport _export WINAPI FrmDec::FrmDec (LPVOID p,mdiChild *c) : FrmField (p,c) { }
DLLExport _export WINAPI FrmShort::FrmShort (LPVOID p,mdiChild *c) : FrmDec (p,c) { }
DLLExport _export WINAPI FrmLong::FrmLong (LPVOID p,mdiChild *c) : FrmDec (p,c) { }
DLLExport _export WINAPI FrmMoney::FrmMoney (LPVOID p,mdiChild *c) : FrmDec (p,c) { }
DLLExport _export WINAPI FrmSlantDec::FrmSlantDec (LPVOID p,mdiChild *c) : FrmDec (p,c) { }
DLLExport _export WINAPI FrmSlantSLDec::FrmSlantSLDec (LPVOID p,mdiChild *c) : FrmSlantDec (p,c) { }
DLLExport _export WINAPI FrmTabDec::FrmTabDec (LPVOID p,mdiChild *c) : FrmDec (p,c) { }
DLLExport _export WINAPI FrmTabColDec::FrmTabColDec (LPVOID p,mdiChild *c) : FrmObject (p,c) { }
DLLExport _export WINAPI FrmFKurve::FrmFKurve (LPVOID p,mdiChild *c) : FrmObject (p,c) { }
DLLExport _export WINAPI FrmSLDec::FrmSLDec (LPVOID p,mdiChild *c) : FrmDec (p,c) { }
DLLExport _export WINAPI FrmDevDec::FrmDevDec (LPVOID p,mdiChild *c) : FrmDec (p,c) { }
DLLExport _export WINAPI FrmDefDec::FrmDefDec (LPVOID p,mdiChild *c) : FrmDec (p,c) { }
DLLExport _export WINAPI FrmStrList::FrmStrList (LPVOID p,mdiChild *c) : FrmField (p,c) { }
DLLExport _export WINAPI FrmTabStrList::FrmTabStrList (LPVOID p,mdiChild *c) : FrmStrList (p,c) { }
DLLExport _export WINAPI FrmStrShortList::FrmStrShortList (LPVOID p,mdiChild *c) : FrmStrList (p,c) { }
DLLExport _export WINAPI FrmDivStrList::FrmDivStrList (LPVOID p,mdiChild *c) : FrmStrShortList (p,c) { }
DLLExport _export WINAPI FrmTabShortStrList::FrmTabShortStrList (LPVOID p,mdiChild *c) : FrmStrShortList (p,c) { }
DLLExport _export WINAPI FrmCheckBox::FrmCheckBox (LPVOID p,mdiChild *c) : FrmObject (p,c) { }
DLLExport _export WINAPI FrmCheckField::FrmCheckField (LPVOID p,mdiChild *c) : FrmCheckBox (p,c) { }
DLLExport _export WINAPI FrmTabFlag::FrmTabFlag (LPVOID p,mdiChild *c) : FrmCheckBox (p,c) { }
DLLExport _export WINAPI FrmTabCheckField::FrmTabCheckField (LPVOID p,mdiChild *c) : FrmCheckField (p,c) { }
DLLExport _export WINAPI FrmLine::FrmLine (LPVOID p,mdiChild *c) : FrmObject (p,c) { }
DLLExport _export WINAPI FrmTab::FrmTab (LPVOID p,mdiChild *c) : FrmObject (p,c) { }
DLLExport _export WINAPI mNum::mNum (LPVOID param,mdiChild *c) : FrmObject (param,c) { }
DLLExport _export WINAPI PrgIcon::PrgIcon (LPVOID p,mdiChild *c) : FrmObject (p,c) { }
DLLExport _export WINAPI FrmStaticBitmap::FrmStaticBitmap (LPVOID p,mdiChild *c) : FrmObject (p,c) { }
DLLExport _export WINAPI ActivationRegion::ActivationRegion (LPVOID p,mdiChild *c) : FrmObject (p,c) { }
DLLExport _export WINAPI OutVGrid::OutVGrid (LPVOID p,mdiChild *c) : FrmObject (p,c) { }

#include "image.hpp"
#include "frmobj3.hpp"
#include "cutcont.hpp"
#include "trcobj.hpp"
#include "entpt.hpp"
#include "winextra.hpp"

HINSTANCE hLibInst;
HWND      WBase_hFrameWin;
HINSTANCE WBase_hInstance;

// #define DO_PROFILE
#ifdef DO_PROFILE
extern BOOL UseLines () ;
extern BOOL UseFields () ;
extern BOOL UsePatterns () ;
extern BOOL UseSetconn () ;
extern BOOL UseShow () ;

extern void IncAnzFields ();
extern void IncAnzLines ();
extern void IncAnzPatterns ();
extern void IncAnzShows ();
extern void IncAnzSetData ();
extern void IncAnzGetData ();
extern void IncAnzUpdate ();
extern void IncAnzSetConnection ();
extern void IncAnzGetKey ();

#endif

void NeedScroll (NeedScroll_Info FAR *nsi,dllChild m)
  {
  m.GetDocInfo (NEEDSCROLL,0,nsi);
  }

struct CallBackBuffer {
  dllChild m;
  FrmObject FAR *obj;
  };
typedef CallBackBuffer FAR *LPCALLBACKBUFFER;

DWORD newColor;
BOOL doTranslate;
DLLExport void _export WINAPI SetTranslateColor (DWORD color)
  {
  newColor = color ;
  doTranslate = TRUE ;
  }

DLLExport void _export WINAPI ResetTranslateColor ()
  {
  doTranslate = FALSE ;
  }

BOOL translateAlways ()
  {
  static BOOL TranslateAlways;
  static BOOL TranslateAlwaysDone;
  if (!TranslateAlwaysDone) {
    doTranslate = TRUE ;
    char buf[30];
    GetPrivateProfileString ("Fonts","TranslateAlways", "no", buf, sizeof(buf),GetIniName());
    if (lstrcmp (buf,"yes") == 0)
      TranslateAlways = TRUE ;
    else 
      TranslateAlways = FALSE ;
    TranslateAlwaysDone = TRUE ;
    }
  return TranslateAlways;
  }
DWORD TranslateColor (DWORD color)
  {
  if ((doTranslate) && ((color == 0L) || (translateAlways()))) {
    return newColor;
    }
  else
    return color ;
  }

Printer *GetStaticPrinter()
  {
  static Printer FAR *sp;
  if (sp == NULL)
    sp = GetPrinter(TRUE);
  return sp;
  }

static WORD LastPressedChar;
DLLExport WORD _export WINAPI GetLastFormPressedChar ()
  {
  return LastPressedChar ;
  }
BOOL IsPrintable (WORD wP)
  {
  return ((wP == '+') || 
          (wP == '-') || 
          (wP == '*') || 
          (wP == '/') || 
          (wP == '%') || 
          (wP == '$') || 
          (wP == '#') || 
          (wP == '|') || 
          (wP == '?') || 
          (wP == '.') || 
          (wP == '!') || 
          (wP == ':') || 
          (wP == '!'));
  }
void SetLastPressedChar (WORD wP)
  {
  if ((IsCharAlphaNumeric(char (wP))) || (wP == '') || (wP == '\b') ||
      (IsPrintable (wP)))
    LastPressedChar = wP ;
  else
    LastPressedChar = 0 ;
  }
static LPFRMOBJ WorkOnObj;
DLLExport LPFRMOBJ _export WINAPI GetWorkObject ()
  {
  return WorkOnObj;
  }
DLLExport void _export WINAPI cFieldCallBackFnc (int cmd,LPVOID Info,LPVOID MyInfo)
  {
  Printer *Pr;
  switch (cmd) {
    case CALLBACKCMD_SAVESTR :
      LPCALLBACKBUFFER(MyInfo)->obj->Save ();
      break ;
    case CALLBACKCMD_SHOWLIST :
      {
      LPFRMOBJ o = LPCALLBACKBUFFER(MyInfo)->obj;
      if (o->CallBackProc != 0) {
        SetLastPressedChar (WORD(*(LPSTR(Info))));
        LPFRMOBJ o = LPCALLBACKBUFFER(MyInfo)->obj;
        WorkOnObj = o;
        o->m.ExCuteProc (o->CallBackProc,EM_LOAD);
        WorkOnObj = NULL;
        SetLastPressedChar (0);
        }
      else
        ((FrmStrList FAR *) LPCALLBACKBUFFER(MyInfo)->obj)->ShowList (LPSTR(Info));
      }
      break ;
    case CALLBACKCMD_NEEDSCROLL :
      {
      NeedScroll ((NeedScroll_Info FAR *) Info,LPCALLBACKBUFFER(MyInfo)->m);
      }
      break ;
    case CALLBACKCMD_ISLOCKED :
      *((BOOL FAR *) Info) = 
            (LPCALLBACKBUFFER(MyInfo)->m.IsDocLocked (
                  LPCALLBACKBUFFER(MyInfo)->obj->GetMainRec ()
                                                     ));
      break ;
    case CALLBACKCMD_SHOWHELP :
      LPCALLBACKBUFFER(MyInfo)->m.SetStatus (LPSTR (Info));
      LPCALLBACKBUFFER(MyInfo)->m.SetCaretShown ();
      break ;
    case CALLBACKCMD_RELEASEHELP :
      LPCALLBACKBUFFER(MyInfo)->m.SetNoCaret ();
      break ;
    case CALLBACKCMD_GETPRDC :
      Pr = LPCALLBACKBUFFER(MyInfo)->m.Pr();
      if (Pr == NULL) {
        Pr = GetStaticPrinter ();
        }
      *((HDC FAR *) Info) = Pr->PrinterDC();
      break ;
    case CALLBACKCMD_RELEASEPRDC :
      Pr = LPCALLBACKBUFFER(MyInfo)->m.Pr();
      if (Pr == NULL) {
        Pr = GetStaticPrinter ();
        }
      Pr->ReleasePrDC ();
      break ;
    case CALLBACKCMD_TESTWORD :
      // ehemals Kuerzel ...
      break ;

    case CALLBACKCMD_ISCHARALLOWED :
      if (!LPCALLBACKBUFFER(MyInfo)->m.IsDocLocked (
                  LPCALLBACKBUFFER(MyInfo)->obj->GetMainRec ()
                                                     )) {
        LPFRMOBJ o = LPCALLBACKBUFFER(MyInfo)->obj;
        if (o->CallBackProc == 0) {
          SetLastPressedChar (((TCI FAR *)Info)->wP);
          LPCALLBACKBUFFER(MyInfo)->obj->TestChar (Info);
          SetLastPressedChar (0);
          }
        }
      else
        MessageBeep (0);
      break ;

    case CALLBACKCMD_SHWORKON :
      {
      LPFRMOBJ o = LPCALLBACKBUFFER(MyInfo)->obj;
      if (o->CallBackProc != 0) {
        SetLastPressedChar (WORD(*(LPSTR(Info))));
        LPFRMOBJ o = LPCALLBACKBUFFER(MyInfo)->obj;
        WorkOnObj = o;
        o->m.ExCuteProc (o->CallBackProc,EM_LOAD);
        WorkOnObj = NULL;
        SetLastPressedChar (0);
        }
      else {
        if (!LPCALLBACKBUFFER(MyInfo)->m.IsDocLocked (
                    LPCALLBACKBUFFER(MyInfo)->obj->GetMainRec ()
                                                       ))
          LPCALLBACKBUFFER(MyInfo)->obj->WorkOn(Info);
        else
          MessageBeep (0);
        }
      }
      break ;

    case CALLBACKCMD_GETWORD :
      LPCALLBACKBUFFER(MyInfo)->obj->GetWord(Info);
      break ;

    case CALLBACKCMD_TRANSLATECLR :
      *((DWORD FAR *) Info) = TranslateColor (*((DWORD FAR *) Info));
      break ;

    case CALLBACKCMD_GETMAXANZCHARS :
      *((int FAR *) (Info)) = LPFRMFIELD(LPCALLBACKBUFFER(MyInfo)->obj)->GetStringSize();
      break ;
    case CALLBACKCMD_CARETPOSCHG :
      LPFRMFIELD(LPCALLBACKBUFFER(MyInfo)->obj)->OnCaretPosChg ();
      break ;
    case CALLBACKCMD_GETFONTREFWND :
      {
      FontRefWndBuffer FAR *f = (FontRefWndBuffer FAR *) Info;
      f->IsDone = TRUE ;
      f->RefWnd = LPFRMFIELD(LPCALLBACKBUFFER(MyInfo)->obj)->m.MyHandle ();
      }
      break ;
    }
  }

static CFIELDCALLBACK cfb;
void SetCallback (FrmObject FAR *obj,cField FAR *f,dllChild m)
  {
  if (cfb == NULL)
#ifdef MAIN_VERSION
    cfb = CFIELDCALLBACK (
       MakeProcInstance (FARPROC(cFieldCallBackFnc),hLibInst)
                         );
#else
    cfb = CFIELDCALLBACK (cFieldCallBackFnc);
#endif

  CallBackBuffer p;
  p.m = m;
  p.obj = obj ;
  f->InstallCallBack (cfb,&p,sizeof(p));
  }

DLLExport void _export WINAPI MyUnionRect (LPRECT r,LPRECT r1,LPRECT r2)
  {
  if (IsRectEmpty (r1)) {
    CopyRect (r,r2);
    }
  else if (IsRectEmpty (r2)) {
    CopyRect (r,r1) ;
    }
  else {
    int x1min = min (r1->left,r1->right);
    int y1min = min (r1->top,r1->bottom);
    int x2min = min (r2->left,r2->right);
    int y2min = min (r2->top,r2->bottom);

    int x1max = max (r1->left,r1->right);
    int y1max = max (r1->top,r1->bottom);
    int x2max = max (r2->left,r2->right);
    int y2max = max (r2->top,r2->bottom);

    r->left   = min (x1min,x2min);
    r->right  = max (x1max,x2max);
    r->top    = min (y1min,y2min);
    r->bottom = max (y1max,y2max);
    }
  }

void GetDocumentContext (PaintContext *pc,dllChild m)
  {
  int MapType;
  pc->GetContext (m.MyHandle(),0xFFFF,0xFFFF,DO_WORK);
  m.GetDocInfo (GETMAPTYPE,0,&MapType);
  if (MapType == MAPTYPE_GEOMETRIC) {
    POINT pt;
    m.GetDocInfo (GETWINDOWORG,0,&pt);
    pc->Map (m_scale(),pt.x,pt.y,m.xp(),m.yp());
    }
  else
    pc->LogicalTwips (m.xp(),m.yp(),m_scale());
  }



//---------------------------------------------------------------------------
// HandlePopupMenu
//
// Oeffnet fuer ein Formularobjekt ein Kontext-Menu
//
// Parameter:
//     hWnd       Handle des Fensters in dem das Menu erscheinen soll
//     pt         Koordinaten an denen das Kontextmenu geoeffnet wird
//     lpfrmobj   Zeiger auf das Formularobjekt 
//
// Rueckgabewert:
//     TRUE wenn die Funktion erfolgreich war
//     FALSE sonst
//
//---------------------------------------------------------------------------
BOOL HandlePopupMenu (HWND hWnd, POINT pt, LPFRMOBJ lpfrmobj)
  {
  HMENU hmenu;            // menu template          
  HMENU hmenuTrackPopup;  // floating pop-up menu

  BOOL res = FALSE;

  //-----------------------------------------------------------
  // die logischen Koordinaten in Screen.Koordinaten umwandeln
  //-----------------------------------------------------------
  PaintContext pc;

  GetDocumentContext (&pc, lpfrmobj->m);

  LPtoDP (pc.hDC, &pt, 1);

  ClientToScreen(hWnd, (LPPOINT) &pt); 
 
  //------------------
  // Menu vorbereiten
  //------------------
  hmenu = LoadMenu(hLibInst, "ContextMenu"); 
  if (hmenu == NULL) 
    return FALSE; 
         
  hmenuTrackPopup = GetSubMenu(hmenu, 0); 

  //-------------------------------------------
  // die objektspezifischen Menues hinzufuegen
  //-------------------------------------------
  res = lpfrmobj->AppendContextMenu (hmenuTrackPopup);

  //-------------------------------------------
  // die scriptdefinierten Menues hinzufuegen
  //-------------------------------------------
  res |= lpfrmobj->AppendUserContextMenu (hmenuTrackPopup);

  //-----------------------------------------------------------------
  // nach TrackPopupMenu wird an das Fenster mit dem Handle hWnd ein
  // WM_COMMAND mit der entsprechenden Menu-Id geschickt
  //-----------------------------------------------------------------
  if (res) {
    RECT rc;
    GetWindowRect (hWnd, &rc);
    TrackPopupMenu(hmenuTrackPopup, TPM_LEFTALIGN | TPM_RIGHTBUTTON, 
        pt.x, pt.y, 0, hWnd, &rc);
    }
         
  DestroyMenu(hmenu);     // Ich brauche dich nicht mehr

  return res;
  }

//***************************************************************************
//*                                                                         *
//*  Basisklasse FrmFarObject                                               *
//*                                                                         *
//***************************************************************************
LPVOID FrmFarObject::operator new (size_t size)
  {
  LPVOID res = GetGlobMem (size);
  if (res == NULL) {
    DBWIN_ASSERT(FALSE);
    }
  return res;
  }

void FrmFarObject::operator delete (LPVOID object)
  {
  FreeGlobMem (object);
  }


//***************************************************************************
//*                                                                         *
//* Implementierung der Klasse FrmObject                                    *
//*                                                                         *
//***************************************************************************
FrmObject FAR *FrmObject::GetNBar (int Dirid)
  {
  if (NObjs[Dirid] != 0xFFFFFFFF) {
    LPFRMOBJ FAR *addr =
          (LPFRMOBJ FAR *) m.ReadlData (NObjs[Dirid]);
    if (addr != NULL) return *addr;
    else              return NULL;
    }
  else
    return NULL;
  }

void FrmObject::GetUnionRect(int Seite,LPRECT r)
  { 
  if (Initialized) {
    if (!rcLogRectInitialized) {
      GetMinMax ();
      rcLogRectInitialized = TRUE ;
      }
    for (int i = ErsteSeite() ; i < ErsteSeite() + AnzahlSeiten () ; i ++ ) {
      LPRECT logr = GetLogRect (i);
      if (logr != NULL) {
        MyUnionRect (r,r,logr);
        }
      }
    }
  }

BOOL FrmObject::GetDeviceRect (int Seite,LPRECT r)
  {
  PaintContext pchlp;
  GetDocumentContext (&pchlp,m);
  LPRECT logr = GetLogRect (Seite);
  if (logr != NULL) {
    pchlp.LogRecttoPhys (r,logr);
    int dummy;
    if (r->top > r->bottom) 
      dummy = r->bottom , r->bottom = r->top , r->top = dummy;
    if (r->left > r->right) 
      dummy = r->left , r->left = r->right , r->right = dummy;
    InflateRect (r,1,1);
    return TRUE ;
    }
  else {
    SetRectEmpty (r);
    return FALSE ;
    }
  }

void FrmObject::Invalidate (int Seite,BOOL erase)
  {
  HWND hWnd = m.MyHandle();
  if (!IsWindow (hWnd)) return ;
  if (Initialized) {
    if (!rcLogRectInitialized) {
      GetMinMax ();
      rcLogRectInitialized = TRUE ;
      }
    RECT r;
    if (GetDeviceRect (Seite,&r)) {
      InvalidateRect (hWnd,&r,erase);
      }
    }
  }

BOOL FrmObject::IsToPaint (int Seite,PaintContext *pc)
  {
  if (!Initialized) return FALSE ;
  if (pc->mode != DO_PAINT)
    return TRUE;
  else {
    LPRECT logr = GetLogRect (Seite);
    if (logr != NULL) {
      int dx = pc->XPHYStoLOG(1);
      RECT r;
      CopyRect (&r,logr);
      int swap;
      if (r.top > r.bottom) swap = r.top, r.top = r.bottom, r.bottom = swap;
      if (r.right < r.left) swap = r.right, r.right = r.left, r.left = swap;
      InflateRect (&r,dx,dx);
      return RectVisible (pc->hDC,&r);
      }
    else
      return FALSE ;
    }
  }


void FrmObject::Write (FrmObject FAR *obj,BOOL doUpdate)
  {
  m.WriteData (ScriptParam->ObjRec,ScriptParam->ObjId,
                              &obj,sizeof(obj),Offset (),doUpdate
               );
  }


void FrmObject::ResetLogRectList ()
  {
  for (LogRectNode FAR *h = LogRectList ; h != NULL ; ) {
    LogRectNode FAR *n = h->Next ;
    FreeGlobMem (h);
    h = n ;
    }
  LogRectList = NULL ; 
  }

FrmObject::~FrmObject ()
  {
  RemoveContextMenu ();

  if (m.Extra != NULL)
    FreeGlobMem (m.Extra);
  if (oinf)
    FreeGlobMem (oinf);
  ResetLogRectList ();
  }


BOOL FrmObject::GetPtToObjVect(int Ptx, int Pty, int FAR *Vectx, int FAR *Vecty)
  {
  *Vectx = schwerx - Ptx;
  *Vecty = schwery - Pty;
  return TRUE;
  }


// virtuelle Funktionen
//////////////////////////
void FrmObject::Load () { }
void FrmObject::Update () { }
BOOL FrmObject::InvalidOnUpdate () { return TRUE ; }
void FrmObject::Save () { }
BOOL FrmObject::OnValRead (double) { return FALSE ; }
void FrmObject::GetResource () { }
void FrmObject::SetConnection() { }
void FrmObject::Reset(BOOL Clear) { }
void FrmObject::Paint (PaintContext *pc,int Seite) { }
void FrmObject::PaintSel (PaintContext *pc,int Seite) { DBWIN_ASSERT(FALSE); }
void FrmObject::PaintTrans (PaintContext *pc, int Seite, tr2 FAR *sc) { DBWIN_ASSERT(FALSE); }
void FrmObject::Reformat (BOOL forPrinter) { }
void FrmObject::GetMinMax () { }
BOOL FrmObject::IsToActivate () { return FALSE ; }
void FrmObject::SetActive (int Seite,BOOL bexplicit) { }
void FrmObject::SetInActive (int Seite) { }
void FrmObject::SetActiveIf (int Seite,BOOL bexplicit)
  {
  if ((!IsActive) && (Initialized)) {
//    DBWIN_ASSERT(Initialized);    haha, sehr witzig
    if (OnActivateProc != 0)
      m.ExCuteProc (OnActivateProc,EM_LOAD);
    SetActive(Seite,bexplicit);
    IsActive = TRUE;
    }
  }
void FrmObject::SetInActiveIf (int Seite)
  {
  if (IsActive) {
//    DBWIN_ASSERT(Initialized);
    SetInActive(Seite);
    if (OnDeactivateProc != 0)
      m.ExCuteProc (OnDeactivateProc,EM_LOAD);
    IsActive = FALSE;
    }
  }
BOOL FrmObject::OnSetCursor (int,int,int) { return FALSE ; }
BOOL FrmObject::OnLButtonDown (WPARAM,int,int,int) { return FALSE ; }
BOOL FrmObject::OnLButtonDblClk (WPARAM,int,int,int) { return FALSE ; }
BOOL FrmObject::OnMouseMove (WPARAM,int,int,int) { return FALSE ; }
BOOL FrmObject::OnLButtonUp (WPARAM,int,int,int) { return FALSE ; }
DWORD FrmObject::GetHelpPrefix () { return 0L; }

//---------------------------------------------------------------------------
// OnRButtonDown
//
// Zweck: Wird bei Druecken der rechten Maustaste aufgerufen
//---------------------------------------------------------------------------
BOOL FrmObject::OnRButtonDown (HWND hWnd, WPARAM wP, int x, int y, int Seite, 
                               BOOL ActivateMenu) 
  {
  BOOL res = FALSE;

  if (GetContextMenu (hWnd, this, x, y, Seite, ActivateMenu))
    res = TRUE;

  return res;
  }

//---------------------------------------------------------------------------
// GetContextMenu
//
// Zweck: ruft die Funktion auf die das Kontextmenu herzeigt
//---------------------------------------------------------------------------
BOOL FrmObject::GetContextMenu (HWND hWnd, LPFRMOBJ lpfrmobj, int x, int y, 
                                int Seite, BOOL ActivateMenu) 
  {
  BOOL res = FALSE;

  POINT pt;
  pt.x = x;
  pt.y = y;

  LPRECT logr = GetLogRect (Seite);
  if ((logr != NULL) && PtInRect(logr, pt)) {

    if (ActivateMenu)
//      if (Initialized && IsToActivate())
      res = HandlePopupMenu (hWnd, pt, lpfrmobj);
    else
      res = TRUE;
    }

  return res;
  }

//---------------------------------------------------------------------------
// SetContextMenu
//
// Zweck: Befuellt die objektspezifische Menu-Liste fuer das Kontext-Menu
//---------------------------------------------------------------------------
DLLExport void _export WINAPI FrmObject::SetContextMenu (LPSTR text, 
                                                         DWORD proc, 
                                                         UINT flags, 
                                                         WORD mode) 
  {
  //----------------------------------------------------
  // im Ladezweig wird ein Element erzeugt und befuellt
  //----------------------------------------------------
  if (mode & EM_LOAD) {
    LPFRMMENULIST lpml = (LPFRMMENULIST)GetGlobMem (sizeof(*lpml));

    lpml->Text = (LPSTR)GetGlobMem (lstrlen(text)+1);
    lstrcpy (lpml->Text, text);

    lpml->Flags = flags;
    lpml->Proc = proc;
    lpml->Next = NULL;

    if (lpMenu != NULL) {
      for (LPFRMMENULIST l = lpMenu; l->Next != NULL; l = l->Next);
      l->Next = lpml;
      }
    else
      lpMenu = lpml;
    }
  else {
    //---------------------------------------------------------------------
    // im Updatezweig wird das Element gesucht und der Text bzw. die Flags
    // werden geaendert. (Auf die Proc ist keine Connection gesetzt; 
    // d.h. sie ist konstant und wird deshalb missbraucht, um das passende 
    // Menu in der Liste zu finden
    //---------------------------------------------------------------------
    for (LPFRMMENULIST l = lpMenu; l != NULL; l = l->Next)
      if (l->Proc == proc) {
        if (l->Text != NULL)          // alten Text loeschen
          FreeGlobMem (l->Text);

        l->Text = (LPSTR)GetGlobMem (lstrlen(text)+1);
        lstrcpy (l->Text, text);

        l->Flags = flags;
        break;
        }
    }
  }


//---------------------------------------------------------------------------
// AppendContextMenu
//
// Zweck: Angabe der Default-Menus fuer das jeweilige Objekt.
//        Wird nach dem rechten Mausclick vor dem Oeffnen des Menus aufgerufen
//---------------------------------------------------------------------------
BOOL FrmObject::AppendContextMenu (HMENU hMenu)
  {
  BOOL res = FALSE;    // kein Default Menu-Eintrag

  //--------------------------------------------------------------------------
  // darf das Objekt veraendert werden wird geprueft, ob das Modify-Flag 
  // durch einen Schreibvorgang geaendert wurde, und das Menu fuer das 
  // Ruecksetzen des Modify-Flags enabled.
  //--------------------------------------------------------------------------
  if (RefForWrite != 0L) {
    DBINT FAR *done = (DBINT FAR *) m.ReadData (LOWORD(RefForWrite),HIWORD(RefForWrite));

    UINT Modify = MF_STRING;

    if (done && *done)
      Modify |= MF_ENABLED;
    else
      Modify |= MF_GRAYED;

    AppendMenu (hMenu, Modify, MI_RESET, "R�cksetzen");
    res = TRUE;
    }
  else  
    RemoveMenu (hMenu, 0, MF_BYPOSITION);

  return res;
  }


//---------------------------------------------------------------------------
// AppendUserContextMenu
//
// Zweck: Diese Menu-Eintraege werden in einer Script-Funktion definiert und
//        an die objektspezifische Variable  <lpMenu> hinzugefuegt.
//        Wird nach dem rechten Mausclick vor dem Oeffnen des Menus aufgerufen
//---------------------------------------------------------------------------
BOOL FrmObject::AppendUserContextMenu (HMENU hMenu)
  {
  BOOL res = FALSE;

  if (lpMenu != NULL) {
    if (hMenu) {
      for (LPFRMMENULIST l = lpMenu; l != NULL; l = l->Next) {

        //-------------------------------------------------------
        // l->Proc wird als ID fuer das WM_COMMAND missbraucht
        //-------------------------------------------------------
        AppendMenu (hMenu, l->Flags, UINT(l->Proc), l->Text);
        }
      }

    res = TRUE;
    }

  return res;
  }

//---------------------------------------------------------------------------
// RemoveContextMenu
//
// Zweck: Entfernt die zu einem Frmobject gehoerenden Menu-Eintraege
//---------------------------------------------------------------------------
DLLExport void _export WINAPI FrmObject::RemoveContextMenu ()
  {
  if (lpMenu != NULL) {

    LPFRMMENULIST Next = NULL;
    for (LPFRMMENULIST l = lpMenu; l != NULL; ) {
      Next = l->Next;
      if (l->Text != NULL)
        FreeGlobMem (l->Text);

      FreeGlobMem (l);
      l = Next;
      }
    lpMenu = NULL;
    }
  }

//---------------------------------------------------------------------------
// OnCommand
//
// Zweck: Wird von WM_COMMAND aufgerufen und ist das Ergebnis eines
//        kontextsensitiven Menu-Eintrages
//---------------------------------------------------------------------------
DLLExport BOOL _export WINAPI FrmObject::OnCommand (WPARAM wID)
  {
  BOOL res = FALSE;

  switch (wID) {
    case MI_RESET:
      if (RefForWrite != 0L) {
        m.DelData (LOWORD(RefForWrite),HIWORD(RefForWrite),Offset());
        res = TRUE;
        }
      break;

    default:
      for (LPFRMMENULIST l = lpMenu; l != NULL; l = l->Next) {
        //-------------------------------------------------------
        // l->Proc wurde als ID fuer das WM_COMMAND missbraucht
        //-------------------------------------------------------
        if (l->Proc == wID) {
          m.ExCuteProc (l->Proc, 0);
          res = TRUE;
          }
        }
      if (!res)
        CallContextMenu (wID,this);
      break;

    }   // switch (wID)

  return res;
  }


BOOL FrmObject::OnKeyDown (WORD,int) { return FALSE ; }
BOOL FrmObject::OnChar (WORD,int) { return FALSE ; }
BOOL FrmObject::OnKeyUp (WORD,int) { return FALSE ; }
int  FrmObject::OnPrivate1 (int) { return 0; }
BOOL FrmObject::IsCont() { return FALSE; }
void FrmObject::GetSelText () { }

// Implementierung der Klasse FrmField
/////////////////////////////////////////////
FrmField::~FrmField ()
  {
  DBWIN_ASSERT(field == NULL);
  }

void FrmField::Paint (PaintContext *pc,int Seite)
  {
  DBWIN_ASSERT(field != NULL);
  if (pc->mode == DO_EXTERN)
    field->PaintToMeta (pc->hDC);
  else
    field->Paint (pc->hDC,Seite,(pc->mode == DO_PRINT));
  }

void FrmField::OnMapChange (double scale,int MapType,int xp,int yp,int x0,int y0)
  {
  if (field != NULL) {
    field->SetScale (scale,MapType);
    field->SetVOrg (xp,yp,ErsteSeite());
    field->SetWOrg (x0,y0);
    }
  }

void FrmField::OnPageChange (int Seite)
  {
  if (field != NULL)
    field->SetVOrg (m.xp(),m.yp(),Seite);
  }

void FrmField::StartExternPaint ()
  {
  if (field != NULL) field->StartExternPaint ();
  }

void FrmField::EndExternPaint ()
  {
  if (field != NULL) field->EndExternPaint ();
  }

void FrmField::Reformat (BOOL forPrinter)
  {
  if (Initialized) {
    DBWIN_ASSERT(field != NULL);
    field->Reformat ((forPrinter) ? PrinterContext() : 0);
    }
  }

void FrmField::GetMinMax ()
  {
  if (Initialized) {
    DBWIN_ASSERT(field != NULL);
    int es = ErsteSeite();
    ResetLogRectList();
    for (int i = 0 ; ; i++) {
      RECT r;
      if (field->GetFullFieldRect (&r,es + i)) {
        InflateRect (&r,5,5);
        SetLogRect (&r,es + i);
        }
      else
        break ;
      }
    SetzeAnzahlSeiten ((i > 0) ? i : 1);
    }
  }

void FrmField::SetConnection ()
  {
  m.SetConnection (Par()->DataRec,Par()->DataId,Offset());
  m.SetConnection (Par()->PtRec,Par()->PtId,Offset());
  m.SetlConnection (Par()->rFormat,Offset());
  m.SetlConnection (Par()->rWidth,Offset());
  m.SetlConnection (Par()->rdoSelect,Offset());
  m.SetlConnection (Par()->rx0,Offset());
  m.SetlConnection (Par()->ry0,Offset());
  if (Par()->hd.par_Size >= sizeof(Frm_DefField) - 2 * sizeof(WORD) - sizeof(LONG))
    m.SetlConnection(Par()->rAnzLines,Offset()) ;
  }

void FrmField::Reset (BOOL Clear)
  {
  m.ClearConnection (Par()->DataRec,Par()->DataId,Offset());
  m.ClearConnection (Par()->PtRec,Par()->PtId,Offset());
  m.ClearlConnection (Par()->rFormat,Offset());
  m.ClearlConnection (Par()->rWidth,Offset());
  m.ClearlConnection (Par()->rdoSelect,Offset());
  m.ClearlConnection (Par()->rx0,Offset());
  m.ClearlConnection (Par()->ry0,Offset());
  if (Par()->hd.par_Size >= sizeof(Frm_DefField) - 2 * sizeof(WORD) - sizeof(LONG))
    m.ClearlConnection(Par()->rAnzLines,Offset()) ;
  if (field != NULL)
    delete field;
  field = NULL ;
  }

BOOL FrmField::GetOrg (POINT *pt)
  {
  fpt FAR *org = (fpt FAR *) m.ReadData (Par()->PtRec,Par()->PtId);
  if ((org != NULL) && (org->x < 1.0E9)) {
    pt->x = m.WorldToLog (org->x);
    pt->y = m.WorldToLog (org->y);
    return TRUE ;
    }
  return FALSE ;
  }

BOOL FrmField::GetFldPos (POINT *pt,int *width)
  {
  BOOL res;
  int MappingType;
  if ((Initialized) && (Par()->PtRec == 0xFFFE)) {
    // Nochmaliges lesen waere toedlich
    DBWIN_ASSERT (field != NULL);
    *field >> *pt;
    if (width != NULL) {
      DBINT FAR *lpwidth = (DBINT FAR *) m.ReadlData (Par()->rWidth);
      if (lpwidth != NULL) *width = *lpwidth / 4;
      else                 *width = -1;
      }
    res = TRUE ;
    }
  else {
    m.GetDocInfo (GETMAPTYPE,0,&MappingType);
    DBINT FAR *lpx = (DBINT FAR *) m.ReadlData (Par()->rx0);
    DBINT FAR *lpy = (DBINT FAR *) m.ReadlData (Par()->ry0);
    if ((lpx != NULL) && (lpy != NULL)) {
      if (MappingType == MAPTYPE_GEOMETRIC) {
        pt->x = *lpx / 4 ;
        pt->y = *lpy / 4 ;
        if (width != NULL) {
          DBINT FAR *lpwidth = (DBINT FAR *) m.ReadlData (Par()->rWidth);
          if (lpwidth != NULL) *width = *lpwidth / 4;
          else                 *width = -1;
          }
        }
      else {
        pt->x = *lpx ;
        pt->y = *lpy ;
        if (width != NULL) {
          DBINT FAR *lpwidth = (DBINT FAR *) m.ReadlData (Par()->rWidth);
          if (lpwidth != NULL) *width = *lpwidth ;
          else                 *width = -1;
          }
        }

      POINT o;
      if (GetOrg(&o)) {
        pt->x += o.x ;
        pt->y += o.y ;
        res = TRUE ;
        }
      else
        res = FALSE ;
      }
    else
      res = FALSE ;
    }
  return res;
  }

int FrmField::yLower (int Seite)
  {
  int res;
  if (field != NULL) {
    POINT pt;
    field->GetLeftLower (&pt,Seite);
    res = pt.y;
    }
  else
    res = -1;
  return res;
  }

void FrmField::GetField (int format)
  {
  DBWIN_ASSERT(field == NULL);
  POINT pt;
  int width;
  if (Initialized = GetFldPos (&pt,&width)) {

    int MapType;
    m.GetDocInfo (GETMAPTYPE,0,&MapType);

    int dmode ;
    if (MapType == MAPTYPE_GEOMETRIC)
      dmode = TRANSPARENT ;
    else 
      dmode = (IsToActivate ()) ? OPAQUE : TRANSPARENT ;
    field = new cField (dmode,format,pt.x,pt.y,width,-1,FALSE);
    SetCallback (this,field,m) ;
    field->SetWindow (m.MyHandle());
    field->SetScale (m_scale(),MapType);
    field->SetVOrg (m.xp(),m.yp(),ErsteSeite());
    if (MapType == MAPTYPE_GEOMETRIC) {
      POINT pt;
      m.GetDocInfo (GETWINDOWORG,0,&pt);
      field->SetWOrg (pt.x,pt.y);
      }

    if (FieldColor != 0xFFFFFFFF)
      field->SetOutColor (FieldColor);

    DBWIN_ASSERT(field != NULL);
    }
  }

void FrmField::GetField ()
  {
  GetField (m.GetConstInt (Par()->rFormat));
  }

BOOL FrmField::IsToActivate ()
  {
  if (Par()->hd.par_Size >= sizeof(Frm_DefField) - 2 * sizeof(WORD))
    doSelect = m.GetConstInt (Par()->rdoSelect);
  else
    doSelect = FALSE ;

  return ((Initialized) && (doSelect) && (!m.IsDocLocked(GetMainRec ())));
  }

void FrmField::SetText ()
  {
  if (Initialized) {
    char empty = '\0';
    LPSTR txt = LPSTR (m.ReadData (Par()->DataRec,Par()->DataId));
    if (txt != NULL)
      *field = txt;
    else
      *field = &empty;
    }
  }

int FrmField::GetStringSize ()
  {
  DBWIN_ASSERT (Initialized);
  return (MaxStringSize >= 0) ? MaxStringSize :
          m.GetVarSize(MAKELONG(Par()->DataRec,Par()->DataId));
  }

void FrmField::SetStringSize (int size)
  {
  DBWIN_ASSERT (Initialized);
  MaxStringSize = size;
  }

int FrmField::AnzLines ()
  {
  if (Par()->hd.par_Size >= sizeof(Frm_DefField) - 2 * sizeof(WORD) - sizeof(LONG))
    return m.GetConstInt(Par()->rAnzLines) ;
  else
    return 1;
  }

LPSTR SkipHeader (LPSTR txt)
  {
  if (*txt == '@') {
    for ( ++ txt ; ((*txt >= '0') && (*txt <= '9')) ; txt ++ ) ;
    }
  return txt ;
  }

LPSTR FrmField::HlpStr ()
  {
  if (Par()->hd.par_Size >= sizeof(Frm_DefField))
    return (SkipHeader (LPSTR (m.ReadData (Par()->HlpRec,Par()->HlpId))));
  else
    return NULL;
  }

DWORD FrmField::GetHelpPrefix ()
  {
  LPSTR h = LPSTR (m.ReadData (Par()->HlpRec,Par()->HlpId));
  DWORD res = 0;
  if (*h == '@')
    for ( ++ h ; ((*h >= '0') && (*h <= '9')) ; res = 10L * res + *h ++ - '0') ;
  return res;
  }

void FrmObject::CheckActivation ()
  {
  }
void FrmField::CheckActivation ()
  {
  if (Initialized) {
    if (IsToActivate())
      field->SetSelectionPen (m.hActivePen(),
                              m.hInactivePen()
                            );
    else
      field->SetSelectionPen (0,
                              0
                            );
    }
  }
void FrmField::SetFieldMode (DWORD mode)
  {
  if (Initialized) {
    if (IsToActivate())
      field->SetSelectionPen (m.hActivePen(),
                              m.hInactivePen()
                            );
    else
      field->SetSelectionPen (0,
                              0
                            );

    mode |= field->GetFieldMode();

    // Anzahl Zeilen Setzen
    int AnzL = AnzLines ();
    if (!IsToActivate())
      mode |= FM_OUTLINEONLY;
    else
      mode &= ~FM_OUTLINEONLY;

    if ((AnzL > 1) || (AnzL < 0)) {
      field->SetAnzLines (AnzL);
      mode = mode & (~FM_SINGLELINE);
      }
    else
      mode |= FM_SINGLELINE;
    field->SetFieldMode (mode);
  
    // HilfeText setzen
    LPSTR hlp = HlpStr ();
    if (hlp != NULL)
      field->SetHelpString (hlp);
    }
  }

void FrmField::Load ()
  {
  if (Par()->hd.par_Size >= sizeof(Frm_DefField) - 2 * sizeof(WORD))
    doSelect = m.GetConstInt (Par()->rdoSelect);
  else
    doSelect = FALSE ;
  GetField ();

  // Feld Aktivieren
  if (Initialized) {
    SetFieldMode (FM_NOSELECTION);
    // Und noch den Text hinmalen
    SetText ();
    }
  }

void FrmBField::Load ()
  {
  FrmField::Load ();
  SetFieldMode (FM_NOSELECTION | FM_FIRSTCHARBIG);
  }

void FrmField::Update ()
  {
  POINT pt;
  int nWidth;
  int nFormat = m.GetConstInt (Par()->rFormat);
  if (Par()->hd.par_Size >= sizeof(Frm_DefField) - 2 * sizeof(WORD))
    doSelect = m.GetConstInt (Par()->rdoSelect);
  else
    doSelect = FALSE ;
  if (Initialized = GetFldPos (&pt,&nWidth)) {
    if (field != NULL) {
      // Versionen von "Kein Update auf aktives Feld" <=> (GetActiveField () != field):
      // 1.) Keine zus�tzliche Bedingung
      //     => Schlecht fuer Felder mit ComboButton
      // 2.) zus�tzlich ausser wenn ComboButton <=> || (field->HasButton)
      //     => Schlecht fuer ?
      // 3.) zus�tzlich nur wenn kein eingebbares Feld <=> && ((field->GetFieldMode() & FM_BTNWITHINPUT) == 0)
      //     => Schlecht fuer ComboButton mit eingebbaren Feld und eigenem Dialog
      // 4.) zus�tzlich nur wenn Fenster Fokus hat <=> (GetFocus() != m.MyHandle())
      //     => immer noch schlecht fuer ComboButton wenn Dialog wieder zugeht bevor Wert gesetzt wird, 
      //        oder erst gar nicht aufgeht (z.B. ICD-Auswahl)
      // 5.) statt 3.) nur wenn eingebbares Feld <=> && ((field->GetFieldMode() & FM_BTNWITHINPUT) == 1)
      //     => Schlecht fuer ComboButtons ohne eingebbares Feld
      // 6.) Bedingung die bei 3.) (field->GetFieldMode()...) dazukam wieder entfernt, da Sinn nicht
      //     mehr bekannt
      if ((GetActiveField () != field) || (field->HasButton) || (GetFocus() != m.MyHandle()))
        SetText ();
      POINT oldPos;
      *field >> oldPos;
      if (!lmemcmp (&oldPos,&pt,sizeof(pt))) *field = pt;
      if (nWidth != field->GetWidth()) 
        field->SetWidth (nWidth);
      if (nFormat != field->GetDefFormat())
        field->SetDefFormat (nFormat);
      SetFieldMode (FM_NOSELECTION);
      }
    else {
      GetField ();
      if (field != NULL) {
        if (CallBackProc != 0L) {
          SetFieldMode (FM_NOSELECTION);
          field->SetFieldMode (FM_LSELECTION | FM_NOSELECTION);
          field->SetButtonField (TRUE);
          }
        else
          SetFieldMode (FM_NOSELECTION);
        }
      if ((GetActiveField () != field) || (field->HasButton)) {
        SetText ();
        field->Reformat ();
        }
      }
    }
  else {
    if (field != NULL) {
      delete field ;
      field = NULL ;
      }
    }
  }

void FrmBField::Update ()
  {
  FrmField::Update ();
  SetFieldMode (FM_NOSELECTION | FM_FIRSTCHARBIG);
  }

void FrmField::SetActive (int Seite,BOOL bexplicit)
  {
  DBWIN_ASSERT (field != NULL);
  if (!(field->HasCaretPos ()))
    field->SetCaretToStart ();
  field->OnSetFocus (bexplicit,Seite);
  }

void FrmField::SetInActive (int Seite)
  {
  DBWIN_ASSERT (field != NULL);
  if (IsTextField())
    SetText ();
  field->OnKillFocus (0,Seite);
  }

void FrmField::Save ()
  {
  DBWIN_ASSERT (field != NULL);
  GLOBALHANDLE hGtmp ;
  *field >> hGtmp;
  LPSTR txt = LPSTR(GlobalLock (hGtmp));
  
  m.WriteData (Par()->DataRec,Par()->DataId,
                txt,lstrlen(txt)+1,Offset()
               );
  GlobalUnlock (hGtmp);
  GlobalFree (hGtmp);
  RECT rcold;
  LPRECT logr_old = GetLogRect (m.ActSide());
  if (logr_old != NULL)
    CopyRect (&rcold,logr_old);
  else
    SetRectEmpty (&rcold);
  GetMinMax ();
  LPRECT logr = GetLogRect (m.ActSide());
  if ((logr != NULL) && (!lmemcmp (&rcold,logr,sizeof(rcold)))) {
    RECT rcnew;
    CopyRect (&rcnew,logr);
    if (!IsRectEmpty (&rcold)) {
      SetLogRect (&rcold,m.ActSide());
      Invalidate (m.ActSide());
      }
    SetLogRect (&rcnew,m.ActSide());
    m.Rescale (&rcnew);
    Invalidate (m.ActSide());      // Rahmen muss neu gezeichnet werden
    }
  if (RefForWrite != 0L) {
    DBINT done = TRUE ;
    m.WriteData (LOWORD(RefForWrite),HIWORD(RefForWrite),&done,sizeof(TRUE),Offset());
    }
  }

void FrmObject::ToDevKoord (int x,int y,POINT *p)
  {
  PaintContext pc;
  GetDocumentContext (&pc,m);
  p->x = x ; p->y = y ;
  LPtoDP (pc.hDC,p,1);
  }

BOOL FrmField::OnLButtonDown (WPARAM wP,int x,int y,int Seite)
  {
  BOOL res = FALSE ;
  if (Initialized) {
    POINT pt;
    DBWIN_ASSERT (field != NULL);
    ToDevKoord (x,y,&pt);
    if (IsToActivate ())
      res = field->OnLButtonDown (wP, pt, Seite);
    }
  return res;
  }

BOOL FrmField::OnRButtonDown (HWND hWnd, WPARAM wP, int x, int y, int Seite,
                              BOOL ActivateMenu)
  {
  BOOL res = FALSE;

  if ((IsToActivate()) || (AppendUserContextMenu (NULL))) {
    res = FrmObject::OnRButtonDown (hWnd, wP, x, y, Seite, ActivateMenu);
    }

  return res;
  }

//---------------------------------------------------------------------------
// OnCommand
//
// Zweck: Wird von WM_COMMAND aufgerufen und ist das Ergebnis eines
//        kontextsensitiven Menu-Eintrages
//---------------------------------------------------------------------------
DLLExport BOOL _export WINAPI FrmField::OnCommand (WPARAM wID)
  {
  BOOL res = FALSE;

  if (!FrmObject::OnCommand (wID)) {
    switch (wID) {
      case MI_Cut:
      case MI_Copy:
      case MI_Insert:
        SendMessage (WBase_hFrameWin, WM_COMMAND, wID, 0);
        res = TRUE;
        break;

      default:
        break;
      }
    }

  return res;
  }


//---------------------------------------------------------------------------
//  AppendContextMenu
//
//  Zweck: Hinzufuegen von objektspezifischen Kontext-Menueintraegen
//---------------------------------------------------------------------------
BOOL FrmField::AppendContextMenu (HMENU hPopupMenu)
  {
  BOOL res = FALSE;
  
  FrmObject::AppendContextMenu (hPopupMenu);

  if (IsToActivate()) {
//    AppendMenu (hPopupMenu, MF_SEPARATOR, 0xFFFF, NULL);

    //---------------------------------------------------------------------
    // Der Text kann nur ausgeschnitten oder kopiert werden, wenn auch ein
    // Teil des selben selektiert ist!
    //---------------------------------------------------------------------
    UINT Modify = MF_STRING;

  //  if (field->JustStringsSelected())
    if (!field->IsSomeTextSelected())
      Modify |= MF_GRAYED;
    
    AppendMenu (hPopupMenu, Modify, MI_Cut, "Ausschneiden\tStrg+X");
    AppendMenu (hPopupMenu, Modify, MI_Copy, "Kopieren\tStrg+C");

    //---------------------------------------------------------------------
    // Nur wenn siche lesbare Daten in der Zwischenablage befinden
    // koennen diese eingefuegt werden!
    //---------------------------------------------------------------------
    Modify = MF_STRING | MF_GRAYED;
    if (IsClipboardFormatAvailable(CF_TEXT) || IsClipboardFormatAvailable(CF_OEMTEXT))
      Modify &= ~MF_GRAYED;

    AppendMenu (hPopupMenu, Modify, MI_Insert, "Einf�gen\tStr+V");

    res = TRUE;
    }

  char NameBuffer [512];
  for ( WORD id = GetFirstContextMenu (TYPE_FORM,MenuType(),NameBuffer,sizeof(NameBuffer)); (id) ; ) {
    AppendMenu (hPopupMenu,0,id,NameBuffer);
    id = GetNextContextMenu (TYPE_FORM,MenuType(),id,NameBuffer,sizeof(NameBuffer));
    }

  return res;
  }


BOOL FrmField::OnLButtonUp (WPARAM wP,int x,int y,int Seite)
  {
  BOOL res = FALSE ;
  if (Initialized) {
    POINT pt;
    DBWIN_ASSERT (field != NULL);
    ToDevKoord (x,y,&pt);
    if (IsToActivate ())
      res = field->OnLButtonUp (wP, pt, Seite);
    }
  return res;
  }

BOOL FrmField::OnSetCursor (int x,int y,int mode)
  {
  if ((Initialized) && (IsToActivate())) {
    POINT mpt;
    mpt.x = x , mpt.y = y;
    LPRECT logr = GetLogRect (m.ActSide());
    if ((logr != NULL) && (PtInRect (logr,mpt))) {
      SetCursor (LoadCursor (NULL,IDC_IBEAM));
      return SETCURSOR_DONE ;
      }
    }
  return FALSE ;
  }

BOOL FrmField::OnLButtonDblClk (WPARAM wP,int x,int y, int Seite) 
  {
  BOOL res = FALSE ;
  if (Initialized) {
    DBWIN_ASSERT (field != NULL);
    POINT mpt;
    mpt.x = x , mpt.y = y;
    LPRECT logr = GetLogRect (Seite);
    if ((logr != NULL) && (IsToActivate ()) && (PtInRect (logr,mpt)))
      res = field->OnLButtonDblClk (wP, mpt, Seite);
    else
      res = FALSE ;
    }
  return res;
  }

BOOL FrmField::OnMouseMove (WPARAM wP,int x,int y,int Seite)
  {
  POINT pt;
  BOOL res = FALSE ;
  if (Initialized) {
    DBWIN_ASSERT (field != NULL);
    ToDevKoord (x,y,&pt);
    BOOL res;
    if (IsToActivate ())
      res = field->OnMouseMove (wP,pt,Seite);
    }
  return res;
  }

BOOL FrmField::OnKeyDown (WORD wP,int Seite)
  {
  BOOL res = FALSE ;
  if (Initialized) {
    DBWIN_ASSERT (field != NULL);
    if (IsToActivate ())
      res = field->OnKeyDown (wP,Seite);
    }
  return res;
  }

BOOL FrmField::OnChar (WORD wP,int Seite)
  {
  BOOL res = FALSE ;
  if (Initialized) {
    if (!skipNextChar) {
      DBWIN_ASSERT (field != NULL);
      if (IsToActivate ())
        res = field->OnChar (wP,Seite);
      }
    else {
      skipNextChar = FALSE;
      res = TRUE;
      }
    }
  return res;
  }

BOOL FrmField::OnKeyUp (WORD wP,int Seite)
  {
  return FALSE ;
  }

#define LOGICALCM       575               // 1 cm in logical twips ausgedrueckt
int FrmField::OnPrivate1 (int x) 
  { 
  int Mult = (x / LOGICALCM) + 1;
  return Mult * LOGICALCM ;
  }

//
//  Implementierung der Klasse FrmDate
/////////////////////////////////////////////////////////////////
void FrmDate::SetText ()
  {
  if (Initialized) {
    char dtext[100];
    packdate FAR *pd = (packdate FAR *)
        m.ReadData (Par()->DataRec,Par()->DataId);

    char fstring[16];
    if (DPar()->fld.hd.par_Size >= sizeof (Frm_DefDate))
      lstrcpy (fstring,LPSTR (m.ReadData(DPar()->prfRec,
                                         DPar()->prfId)));
    else
      lstrcpy (fstring,"");
        
    *dtext = '\0';
    if (pd != NULL) {
      packdate pdl;
      lmemcpy (&pdl,pd,sizeof(pdl));
      if (*fstring)
        FormatDate (dtext,&pdl,fstring);
      else
        writeDateStr (dtext,&pdl);
      }
    *field = dtext;
    }
  }

void FrmField::WorkOn (LPVOID Info)
  {
  // Untersuchen, ob es nur ein Feld gibt...
  char NameBuffer [512];
  WORD id = GetFirstContextMenu (TYPE_FORM,MenuType(),NameBuffer,sizeof(NameBuffer));
  CallContextMenu (id,this);
  }

void FrmDate::SetInActive (int Seite)
  {
  FrmField::SetInActive (Seite);
/*
  // wenn in dem Feld nix drin steht, war das Datum ungueltig => quitschen
  //----------------------------------------------------------------------
  DBWIN_ASSERT (field != NULL);

  GLOBALHANDLE hGtmp;
  *field  >> hGtmp;

  char ldatetxt[100];
  lstrncpy (ldatetxt,GlobalLock (hGtmp),sizeof(ldatetxt));
  if (ldatetxt[0] == '\0')
    MessageBeep (0);

  GlobalUnlock (hGtmp);
  GlobalFree (hGtmp);
*/
  }

void FrmDate::Save ()
  {
  DBWIN_ASSERT (field != NULL);

  GLOBALHANDLE hGtmp;
  *field  >> hGtmp;

  // Aktueller Text steht in der Argumentenliste
  char ldatetxt[100];
  lstrncpy (ldatetxt,LPSTR(GlobalLock (hGtmp)),sizeof(ldatetxt));
  packdate resdate;
  if (readDateStr (ldatetxt,&resdate))
    m.WriteData (Par()->DataRec,Par()->DataId,
                   &resdate,sizeof(resdate),Offset()
                 );
  else
    m.DelData (Par()->DataRec,Par()->DataId,
                   Offset()
               );
  GlobalUnlock (hGtmp);
  GlobalFree (hGtmp);
  if (RefForWrite != 0L) {
    DBINT done = TRUE ;
    m.WriteData (LOWORD(RefForWrite),HIWORD(RefForWrite),&done,sizeof(TRUE),Offset());
    }
  }

#define c_SecsPerDay LONG (86400)

BOOL FrmDate::OnKeyDown (WORD wP,int Seite)
  {
  skipNextChar = FALSE;
  if (Initialized) {
    BOOL baseOnNow = TRUE;
    int setDate = 0x8000;
    if (wP == 'G') {
      setDate = -1;
      baseOnNow = TRUE;
      }
    else if (wP == 'H') {
      setDate = 0;
      baseOnNow = TRUE;
      }
    else if (wP == 'M') {
      setDate = 1;
      baseOnNow = TRUE;
      }
    else if ((wP == VK_SUBTRACT) || (wP == VK_DOWN)) {
      setDate = -1;
      baseOnNow = FALSE;
      }
    else if ((wP == VK_ADD) || (wP == VK_UP)) {
      setDate = 1;
      baseOnNow = FALSE;
      }
    if (setDate != 0x8000) {
      INTTIME t;
      if (baseOnNow)
        t = Now ();
      else {
        packdate FAR *pdCurrent = (packdate FAR *) m.ReadData (Par()->DataRec,Par()->DataId);
        if (pdCurrent != NULL)
          t = PackTime (pdCurrent);
        else
          return FrmField::OnKeyDown (wP, Seite);
        }
      packdate pd;
      t = t + setDate * c_SecsPerDay;
      UnPackTime (t,&pd);
      m.WriteData (Par()->DataRec,Par()->DataId,&pd,sizeof(pd),Offset());
      SetText();
      Invalidate(m.ActSide());
      if (RefForWrite != 0L) {
        DBINT done = TRUE ;
        m.WriteData (LOWORD(RefForWrite),HIWORD(RefForWrite),&done,sizeof(TRUE),Offset());
        }
      skipNextChar = TRUE;
      return TRUE;
      }
    else
      return FrmField::OnKeyDown (wP, Seite);
    }
  else
    return FALSE;
  }

void FrmDate::WorkOn (LPVOID Info)
  {
  DBWIN_ASSERT (field != NULL);

  INTTIME t = Now ();
  packdate resdate;
  UnPackTime (t,&resdate);
  m.WriteData (Par()->DataRec,Par()->DataId,
                &resdate,sizeof(resdate),Offset());
  SetText();
  Invalidate(m.ActSide());
  if (RefForWrite != 0L) {
    DBINT done = TRUE ;
    m.WriteData (LOWORD(RefForWrite),HIWORD(RefForWrite),&done,sizeof(TRUE),Offset());
    }
  }

//---------------------------------------------------------------------------
//  AppendContextMenu
//
//  Zweck: Hinzufuegen von objektspezifischen Kontext-Menueintraegen
//---------------------------------------------------------------------------
BOOL FrmDate::AppendContextMenu (HMENU hPopupMenu)
  {
  if (FrmField::AppendContextMenu (hPopupMenu)) {
    AppendMenu (hPopupMenu, MF_SEPARATOR, 0xFFFF, NULL);
    AppendMenu (hPopupMenu, MF_STRING, MI_TODAY, "heutiges Datum\tF2");
    return TRUE;
    }

  return FALSE;
  }


//---------------------------------------------------------------------------
//  OnCommand
//
//  Zweck: Ausfuehren von objektspezifischen Menue-Befehlen
//---------------------------------------------------------------------------
DLLExport BOOL _export WINAPI FrmDate::OnCommand (WPARAM wID)
  {
  BOOL res = FALSE;

  if (!FrmObject::OnCommand (wID)) {
    switch (wID) {
      case MI_TODAY:
        WorkOn (NULL);
        res = TRUE;
        break;

      default:
        break;
      }
    }

  return res;
  }


//
//  Implementierung der Klasse FrmTime
/////////////////////////////////////////////////////////////////
void FrmTime::SetText ()
  {
  if (Initialized) {
    char dtext[100];
    packtime FAR *pt = (packtime FAR *)
        m.ReadData (Par()->DataRec,Par()->DataId);
    *dtext = '\0';

    char fstring[16];
    if (DPar()->fld.hd.par_Size >= sizeof (Frm_DefDate))
      lstrcpy (fstring,LPSTR (m.ReadData(DPar()->prfRec,
                                         DPar()->prfId)));
    else
      lstrcpy (fstring,"");
        
    *dtext = '\0';
    if (pt != NULL) {
      if (*fstring)
        FormatTime (dtext,pt,fstring);
      else
        writeTimeStr (dtext,0,pt);
      }
    *field = dtext;
    }
  }

void FrmTime::SetInActive (int Seite)
  {
  FrmField::SetInActive (Seite);
  }

void FrmTime::Save ()
  {
  DBWIN_ASSERT (field != NULL);

  GLOBALHANDLE hGtmp;
  *field  >> hGtmp;

  // Aktueller Text steht in der Argumentenliste
  char ldatetxt[100];
  lstrncpy (ldatetxt,LPSTR(GlobalLock (hGtmp)),sizeof(ldatetxt));
  packtime restime;
  if (readTimeStr (ldatetxt,0,&restime))
    m.WriteData (Par()->DataRec,Par()->DataId,
                   &restime,sizeof(restime),Offset()
                 );
  else
    m.DelData (Par()->DataRec,Par()->DataId,
                   Offset()
               );
  GlobalUnlock (hGtmp);
  GlobalFree (hGtmp);
  if (RefForWrite != 0L) {
    DBINT done = TRUE ;
    m.WriteData (LOWORD(RefForWrite),HIWORD(RefForWrite),&done,sizeof(TRUE),Offset());
    }
  }

BOOL FrmTime::OnKeyDown (WORD wP,int Seite)
  {
  skipNextChar = FALSE;
  if (Initialized) {
    BOOL baseOnNow;
    int setTime = 0x8000;
    if ((wP == 'j') || (wP == 'J')) {
      setTime = 0;
      baseOnNow = TRUE;
      }
    else if ((wP == VK_SUBTRACT) || (wP == VK_DOWN)) {
      setTime = -1;
      baseOnNow = FALSE;
      }
    else if ((wP == VK_ADD) || (wP == VK_UP)) {
      setTime = 1;
      baseOnNow = FALSE;
      }
    if (setTime != 0x8000) {
      INTTIME t;
      if (baseOnNow)
        t = Now ();
      else {
        packtime FAR *ptCurrent = (packtime FAR *) m.ReadData (Par()->DataRec,Par()->DataId);
        if (ptCurrent != NULL)
          t = PackSeconds (ptCurrent);
        else
          return FrmField::OnKeyDown (wP, Seite);
        }
      int setFactor;
      if (setTime != 0) {
        char fstring[16];
        if (DPar()->fld.hd.par_Size >= sizeof (Frm_DefDate)) {
          lstrcpy (fstring,LPSTR (m.ReadData(DPar()->prfRec,
                                             DPar()->prfId)));
          if ((strchr (fstring, 's') != NULL) || (strchr (fstring, 'S') != NULL))
            setFactor = 1;    // Sekunden angezeigt
          else if ((strchr (fstring, 'm') != NULL) || (strchr (fstring, 'M') != NULL))
            setFactor = 60;   // Minuten angezeigt
          else if ((strchr (fstring, 'h') != NULL) || (strchr (fstring, 'H') != NULL))
            setFactor = 3600; // Stunden angezeigt
          else
            setFactor = 1;    // Seltames Format, aber nehmen wir halt Sekunden
          }
        else
          setFactor = 1;
        }
      else
        setFactor = 1;
      packtime pt;
      t = t + setTime * setFactor;
      UnPackSeconds (t,&pt);
      m.WriteData (Par()->DataRec,Par()->DataId,&pt,sizeof(pt),Offset());
      SetText();
      Invalidate(m.ActSide());
      if (RefForWrite != 0L) {
        DBINT done = TRUE ;
        m.WriteData (LOWORD(RefForWrite),HIWORD(RefForWrite),&done,sizeof(TRUE),Offset());
        }
      skipNextChar = TRUE;
      return TRUE;
      }
    else
      return FrmField::OnKeyDown (wP, Seite);
    }
  else
    return FALSE;
  }

void FrmTime::WorkOn (LPVOID Info)
  {
  DBWIN_ASSERT (field != NULL);

  packtime restime;
  UnPackSeconds (Now (), &restime);
  m.WriteData (Par()->DataRec,Par()->DataId,
                &restime,sizeof(restime),Offset());
  SetText();
  Invalidate(m.ActSide());
  if (RefForWrite != 0L) {
    DBINT done = TRUE ;
    m.WriteData (LOWORD(RefForWrite),HIWORD(RefForWrite),&done,sizeof(TRUE),Offset());
    }
  }


//---------------------------------------------------------------------------
//  AppendContextMenu
//
//  Zweck: Hinzufuegen von objektspezifischen Kontext-Menueintraegen
//---------------------------------------------------------------------------
BOOL FrmTime::AppendContextMenu (HMENU hPopupMenu)
  {
  if (FrmField::AppendContextMenu (hPopupMenu)) {
    AppendMenu (hPopupMenu, MF_SEPARATOR, 0xFFFF, NULL);
    AppendMenu (hPopupMenu, MF_STRING, MI_TIME, "aktuelle Uhrzeit\tF2");
    return TRUE;
    }

  return FALSE;
  }


//---------------------------------------------------------------------------
//  OnCommand
//
//  Zweck: Ausfuehren von objektspezifischen Menue-Befehlen
//---------------------------------------------------------------------------
DLLExport BOOL _export WINAPI FrmTime::OnCommand (WPARAM wID)
  {
  BOOL res = FALSE;

  if (!FrmObject::OnCommand (wID)) {
    switch (wID) {
      case MI_TIME:
        WorkOn (NULL);
        res = TRUE;
        break;

      default:
        break;
      }
    }

  return res;
  }


//
//  Implementierung der Klasse FrmDec
/////////////////////////////////////////////////////////////////
void FrmDec::Load ()
  {
  FrmField::Load ();
  SetDecFieldMode ();
  }

void FrmDec::Reset(BOOL doClear)
  {
  FrmField::Reset (doClear);
  *fstring = '\0';
  }

void FrmDec::SetDecFieldMode ()
  {
  DWORD mode = FM_SINGLELINE | FM_DECIMAL | FM_NOSELECTION;
  if (!IsToActivate())
    mode |= FM_OUTLINEONLY;
  if (Initialized)
    field->SetFieldMode (mode);
  }

void FrmDec::Update()
  {
  FrmField::Update ();
  SetDecFieldMode ();
  }

void FrmDec::SetText ()
  {
  if (Initialized) {
    if (*fstring == '\0') {
      if (DPar()->fld.hd.par_Size >= sizeof (Frm_DefDec))
        lstrcpy (fstring,LPSTR (m.ReadData(DPar()->prfRec,
                                DPar()->prfId)));
      else
        lstrcpy (fstring,"%.1f");
      }
      
    float FAR *v = (float FAR *)
      m.ReadData (Par()->DataRec,Par()->DataId);
    char ftext[128];
    char fs[16];
    lstrcpy (fs,fstring);
    *ftext = '\0';
    if ((v != NULL) && (*v < 1.0E9))
      sprintf (ftext,fs,*v);
    *field = ftext;
    }
  }

void FrmShort::SetText ()
  {
  if (Initialized) {
    DBINT FAR *v = (DBINT FAR *)
      m.ReadData (Par()->DataRec,Par()->DataId);
    char ftext[32];
    if (v != NULL) {
      GetShortStr (ftext,*v);
      }
    else
      *ftext = '\0' ;
    *field = ftext;
    }
  }

void FrmLong::SetConnection ()
  {
  FrmField::SetConnection ();
  if (DPar()->fld.hd.par_Size >= sizeof(Frm_DefDec))
    m.SetConnection(DPar()->prfRec,DPar()->prfId,Offset()) ;
  }
void FrmLong::Reset (BOOL Clear)
  {
  FrmField::Reset (Clear);
  if (DPar()->fld.hd.par_Size >= sizeof(Frm_DefDec))
    m.ClearConnection(DPar()->prfRec,DPar()->prfId,Offset()) ;
  }

void FrmLong::SetText ()
  {
  if (Initialized) {
    LONG FAR *v = (LONG FAR *)
      m.ReadData (Par()->DataRec,Par()->DataId);
    BOOL doT = FALSE ;
    BOOL doM = FALSE ;
    BOOL mitVorzeichen = FALSE;
    if (DPar()->fld.hd.par_Size >= sizeof(Frm_DefDec)) {
      LPSTR format = LPSTR(m.ReadData (DPar()->prfRec,DPar()->prfId));
      if (format != NULL) {
        if (lstrcmp (format,"%l.d") == 0)
          doT = TRUE;
        else if ((lstrcmp (format,"%md") == 0) || (lstrcmp (format,"%m.d") == 0))
          doM = TRUE;
        else if ((lstrcmp (format,"%+md") == 0) || (lstrcmp (format,"%+m.d") == 0))
          doM = TRUE , mitVorzeichen = TRUE;
        else if (lstrcmp (format,"%+ld") == 0)
          mitVorzeichen = TRUE;
        else if (lstrcmp (format,"%+l.d") == 0)
          doT = TRUE , mitVorzeichen = TRUE;
        }
      }
    char ftext[32];
    if (v != NULL) {
      LPSTR dest;
      if ((mitVorzeichen) && (*v >= 0L)) {
        ftext[0] = '+' ;
        dest = ftext + 1 ;
        }
      else
        dest = ftext ;
      if (doM)
        GetMoneyStr (dest,*v);
      else
        GetLongStr (dest,*v,doT);
      }
    else
      *ftext = '\0' ;
    *field = ftext;
    }
  }

void FrmMoney::SetText ()
  {
  if (Initialized) {
    LONG FAR *v = (LONG FAR *)
      m.ReadData (Par()->DataRec,Par()->DataId);
    char ftext[32];
    if (v != NULL) {
      GetMoneyStr (ftext,*v);
      }
    else
      *ftext = '\0' ;
    *field = ftext;
    }
  }

void FrmDec::SetInActive (int Seite)
  {
  FrmField::SetInActive (Seite);
  if ((IsSchiebe()) && (m.schd()->Type == CHWND_FORM))
    m.DestroySchiebeLehre ();
  }

void FrmDec::Save ()
  {
  DBWIN_ASSERT (field != NULL);

  GLOBALHANDLE hGtmp;
  *field  >> hGtmp;

  // Aktueller Text steht in der Argumentenliste
  float res;
  char txt[128];
  lstrncpy (txt,LPSTR(GlobalLock (hGtmp)),sizeof(txt));
#ifdef SCHEISS_MICROSOFT
  if (wsscanf(txt,"%f",&res) != 1)
#else
  if (!strtofloat(txt,&res))
#endif
    m.DelData (Par()->DataRec,Par()->DataId,
                        Offset()
               );
  else
    m.WriteData (Par()->DataRec,Par()->DataId,
                        &res,sizeof(res),Offset()
                 );
  GlobalUnlock (hGtmp);
  GlobalFree (hGtmp);
  if (RefForWrite != 0L) {
    DBINT done = TRUE ;
    m.WriteData (LOWORD(RefForWrite),HIWORD(RefForWrite),&done,sizeof(TRUE),Offset());
    }
  }

void FrmShort::Save ()
  {
  DBWIN_ASSERT (field != NULL);

  GLOBALHANDLE hGtmp;
  *field  >> hGtmp;

  // Aktueller Text steht in der Argumentenliste
  int res;
  char txt[128];
  lstrncpy (txt,LPSTR(GlobalLock (hGtmp)),sizeof(txt));
  if (!scint (txt,&res))
    m.DelData (Par()->DataRec,Par()->DataId,
                        Offset()
               );
  else
    m.WriteData (Par()->DataRec,Par()->DataId,
                        &res,sizeof(short),Offset()
                 );
  GlobalUnlock (hGtmp);
  GlobalFree (hGtmp);
  if (RefForWrite != 0L) {
    DBINT done = TRUE ;
    m.WriteData (LOWORD(RefForWrite),HIWORD(RefForWrite),&done,sizeof(TRUE),Offset());
    }
  }

void FrmLong::Save ()
  {
  DBWIN_ASSERT (field != NULL);

  GLOBALHANDLE hGtmp;
  *field  >> hGtmp;

  // Aktueller Text steht in der Argumentenliste
  LONG res;
  char txt[128];
  lstrncpy (txt,LPSTR(GlobalLock (hGtmp)),sizeof(txt));
  BOOL done,doM;
  if (DPar()->fld.hd.par_Size >= sizeof(Frm_DefDec)) {
    LPSTR format = LPSTR(m.ReadData (DPar()->prfRec,DPar()->prfId));
    doM = FALSE ;
    if (format != NULL) {
      if ((lstrcmp (format,"%md") == 0) ||
          (lstrcmp (format,"%+md") == 0) ||
          (lstrcmp (format,"%m.d") == 0) ||
          (lstrcmp (format,"%+m.d") == 0))
        doM = TRUE;
      }
    }
  else
    doM = FALSE ;
  if (doM)
    done = scmony(txt,&res);
  else
    done = sclongint(txt,&res);
  if (!done)
    m.DelData (Par()->DataRec,Par()->DataId,
                        Offset()
              );
  else
    m.WriteData (Par()->DataRec,Par()->DataId,
                        &res,sizeof(LONG),Offset()
                );
  GlobalUnlock (hGtmp);
  GlobalFree (hGtmp);
  if (RefForWrite != 0L) {
    DBINT done = TRUE ;
    m.WriteData (LOWORD(RefForWrite),HIWORD(RefForWrite),&done,sizeof(TRUE),Offset());
    }
  }

void FrmMoney::Save ()
  {
  DBWIN_ASSERT (field != NULL);

  GLOBALHANDLE hGtmp;
  *field  >> hGtmp;

  // Aktueller Text steht in der Argumentenliste
  LONG res;
  char txt[128];
  lstrncpy (txt,LPSTR(GlobalLock (hGtmp)),sizeof(txt));
  if (!scmony(txt,&res))
    m.DelData (Par()->DataRec,Par()->DataId,
                        Offset()
               );
  else
    m.WriteData (Par()->DataRec,Par()->DataId,
                        &res,sizeof(LONG),Offset()
                 );
  GlobalUnlock (hGtmp);
  GlobalFree (hGtmp);
  if (RefForWrite != 0L) {
    DBINT done = TRUE ;
    m.WriteData (LOWORD(RefForWrite),HIWORD(RefForWrite),&done,sizeof(TRUE),Offset());
    }
  }

//
//  Implementierung der Klasse FrmSLDec
/////////////////////////////////////////////////////////////////
void FrmDec::SetActive (int Seite,BOOL bexplicit)
  {
  FrmField::SetActive (Seite,bexplicit);
  if ((IsSchiebe()) && (m.schd()->Type == CHWND_FORM))
    m.SetUpSchiebeLehre ();
  }

BOOL FrmDec::OnValRead (double val)
  {
  if (IsSchiebe()) {
    DBWIN_ASSERT (field != NULL);
    // Text in das Feld schreiben und Wert in die Datenbank
    char txt[50];
    sprintf (txt,"%.1f",val);
    *field = txt ;
    field->Reformat ();
    float fval = float (val);
//    c->WriteData (Par()->DataRec,Par()->DataId,c->RunNmbr,&fval,sizeof(fval),Offset());
    m.WriteData (Par()->DataRec,Par()->DataId,&fval,sizeof(fval),NULL);
    MessageBeep (WORD(-1));           // It's all ok

    if (RefForWrite != 0L) {
      DBINT done = TRUE ;
      m.WriteData (LOWORD(RefForWrite),HIWORD(RefForWrite),&done,sizeof(TRUE),Offset());
      }
    
    return TRUE ;
    }
  return FALSE ;
  }

void FrmStrList::Load ()
  {
  FrmField::Load ();
  if (Initialized) {
    field->SetFieldMode (FM_LSELECTION | FM_NOSELECTION);
    field->SetButtonField (TRUE);
    }
  }

void FrmStrList::Update ()
  {
  FrmField::Update ();
  if (Initialized) {
    field->SetFieldMode (FM_LSELECTION | FM_NOSELECTION);
    field->SetButtonField (TRUE);
    }
  }

LPSTR FrmStrList::GetStrRes ()
  {
  LPSTR res = NULL;
  if (Par()->hd.par_Size >= sizeof(Frm_DefStrList)) {
    // Eine Resource ist vorhanden
    res = LPSTR (m.ReadData (SPar()->srRec,SPar()->srId)) ;
    if (res != NULL) {
      DBWIN_ASSERT ((res[GetBlockSize(res)-1] == '\0') && 
                    (res[GetBlockSize(res)-2] == '\0'));
      res -= sizeof(WORD); // Vor den eigentlichen Daten steht das
                           // Laengenbyte !!!
      }
    }
  else {
    DBWIN_ASSERT (FALSE);
    }
  DBWIN_ASSERT (res != NULL);
  return res;
  }

static void GetIndText (LPSTR Base,int wInd,LPSTR buffer)
  {
  LPSTR txt = Base + sizeof (WORD) ;
  LPSTR ht;
  for (int i = 0 ; i < int (wInd) ; i++) {
    for (ht = txt ; *ht ; ht++) ;
    ht++;
    if (*ht == '\0') break ;       // Doppel - Null -> letzten Satz
                                   // verwenden
    txt = ht ;
    }

  lstrcpy (buffer,txt);
  }

void FrmStrList::GetSelText ()
  {
  // Suchen des Textes Nummer m.sli.Ind...
  LPSTR Base = GetStrRes ();
  GetIndText (Base,m.Get_sli_Ind(),m.Get_sli_actTxt());
  }

void FrmStrList::SetText ()
  {
  if (Initialized) {
    char outtxt[256];

    // Index aus der Datenbank lesen
    WORD FAR *DInd = (WORD FAR *) m.ReadData (Par()->DataRec,Par()->DataId);
    if (DInd != NULL) {
      wInd = *DInd ;
      }
    else {
      wInd = 0 ;        // 1. String ist default
      m.WriteData (Par()->DataRec,Par()->DataId,&wInd,sizeof(wInd),Offset(),FALSE);
      }

    m.Set_sli_Ind(wInd);
    m.Set_sli_actTxt(outtxt);
    GetSelText ();
    *field = outtxt;
    }
  }

void FrmStrShortList::GetSelText ()
  {
  FrmStrList::GetSelText ();
  for (LPSTR txt = m.Get_sli_actTxt() ;
        ((*txt) && (*txt != ' ') && (*txt != '\t')) ; txt++);
  *txt = '\0' ;
  }

void FrmStrList::Save ()
  {
  wInd = m.Get_sli_Ind() ;
  m.WriteData (Par()->DataRec,Par()->DataId,
                &wInd,sizeof(WORD),Offset());
  if (RefForWrite != 0L) {
    DBINT done = TRUE ;
    m.WriteData (LOWORD(RefForWrite),HIWORD(RefForWrite),&done,sizeof(TRUE),Offset());
    }
  }

void FrmStrList::GetResource ()
  {
  m.Set_sli_Ind(wInd);
  LPSTR Buffer = GetStrRes ();
  WORD Extra ;
  if (Par()->hd.par_Size >= sizeof(Frm_DefStrList))
    Extra = 2;
  else
    Extra = 0;
  m.Set_sli_res(GlobalAlloc (GMEM_MOVEABLE | GMEM_ZEROINIT , 
                                  *(WORD FAR *) Buffer + Extra));
  LPSTR ResBuffer = LPSTR(GlobalLock (m.Get_sli_res()));
  lmemcpy (ResBuffer,Buffer,*(WORD FAR *) Buffer + Extra);
  *((WORD FAR *) ResBuffer) += Extra;
  }

void FrmStrList::Reset (BOOL doClear)
  {
  if (hGRecTxt)
    GlobalFree (hGRecTxt);
  hGRecTxt = 0;
  FrmField::Reset (doClear);
  }

//
// Implementierung der Klasse FrmLine
////////////////////////////////////////////////
void FrmLine::GetMinMax ()
  {
  if (Initialized) {
    int hpw = m.HalfPenWidth(diPen) ;
    RECT r;
    if (y1 < y2)
      r.top    = y1 - hpw ,
      r.bottom = y2 + hpw ;
    else
      r.top    = y2 - hpw ,
      r.bottom = y1 + hpw ;

    if (x1 < x2)
      r.left   = x1 - hpw ,
      r.right  = x2 + hpw ;
    else
      r.left   = x2 - hpw ,
      r.right  = x1 + hpw ;
    SetLogRect (&r,ErsteSeite());
    }
  }

void FrmLine::Paint (PaintContext *pc,int Seite)
  {
  if (Initialized) {
    pc->diPen (diPen);
    *pc << Line (x1,y1,x2,y2);
    }
  }

void FrmLine::Load ()
  {
  fpt FAR *p1 = (fpt FAR *) m.ReadData (Par()->p1Rec,Par()->p1Id);
  fpt FAR *p2 = (fpt FAR *) m.ReadData (Par()->p2Rec,Par()->p2Id);
  LONG FAR *color = (LONG FAR *) m.ReadData (Par()->cRec,Par()->cId);
  if ((p1 != NULL) && (p1->x < 1.0E9) && (p2 != NULL) && (p2->x < 1.0E9)
          && (color != NULL)) {
    x1 = m.WorldToLog (p1->x) ;    y1 = m.WorldToLog (p1->y) ;
    x2 = m.WorldToLog (p2->x) ;    y2 = m.WorldToLog (p2->y) ;
    diPen = *color;
    Initialized = TRUE ;
    }
  else
    Initialized = FALSE ;
  }

void FrmLine::Update ()
  {
  Load ();
  }

void FrmLine::SetConnection()
  {
  m.SetConnection (Par()->p1Rec,Par()->p1Id,Offset());
  m.SetConnection (Par()->p2Rec,Par()->p2Id,Offset());
  m.SetConnection (Par()->cRec,Par()->cId,Offset());
  }

void FrmLine::Reset (BOOL doClear)
  {
  m.ClearConnection (Par()->p1Rec,Par()->p1Id,Offset());
  m.ClearConnection (Par()->p2Rec,Par()->p2Id,Offset());
  m.ClearConnection (Par()->cRec,Par()->cId,Offset());
  }

void FrmSozNr::SetText ()
  {
  if (Initialized) {
    LPSTR Txt = LPSTR (
              m.ReadData (Par()->fld.DataRec,Par()->fld.DataId)
                      );
    if ((Txt == NULL) || (*Txt == '\0')) {
      // Sozialversicherungsnummer so zusammenbasteln
      ///////////////////////////////////////////////
      packdate FAR *pdl = (packdate FAR *)
        m.ReadData(Par()->DateRec,Par()->DateId);
      if (pdl != NULL) {
        char txt[20];
        int year = pdl->year - 1900;
        if (year < 0) year = 0;
        sprintf (txt,"%02d%02d%02d",pdl->day,pdl->month,year);
        m.WriteData(Par()->fld.DataRec,Par()->fld.DataId,
                      txt,lstrlen(txt)+1,Offset());
        }
      }
    FrmField::SetText ();
    }
  }

void FrmSozNr::SetConnection ()
  {
  FrmField::SetConnection ();
  m.SetConnection (Par()->DateRec,Par()->DateId,Offset());
  }

void FrmSozNr::Reset (BOOL Clear)
  {
  m.ClearConnection (Par()->DateRec,Par()->DateId,Offset());
  FrmField::Reset (Clear);
  }

BOOL CheckVersNummer (LPSTR str)
  {
  static char *gew = "3790584216" ; 
  BOOL ok = FALSE ;
  if (lstrlen (str) == 10) {
    int summe = 0;
    for (int i = 0 ; i < 10 ; i++)
      summe = summe + (str[i] - '0') * (gew[i] - '0') ;
    summe = summe % 11 ;
    ok = ((summe != 10) && (str[3] == summe + '0'));
    }
  return ok;
  }

void FrmSozNr::SetInActive (int Seite)
  {
  static BOOL Asked;
  if (!Asked) {
    LPSTR txt = LPSTR (
          m.ReadData (Par()->fld.DataRec,Par()->fld.DataId)
                      );
    if ((txt != NULL) && (!CheckVersNummer (txt))) {
      Asked = TRUE ;
      MessageBeep (0);
      }
    }
  Asked = FALSE ;
  FrmField::SetInActive (Seite);
  }

void FrmDevDec::Load ()
  {
  GetField (oldFormat = GetFormat ());

  // Feld Aktivieren
  if (Initialized) {
    SetFieldMode (FM_NOSELECTION);
    // Und noch den Text hinmalen
    SetText ();
    }
  }

void FrmDevDec::SetText ()
  {
  if (Initialized) {
    float FAR *v = (float FAR *)
      m.ReadData (Par()->DataRec,Par()->DataId);
    char ftext[128];
    *ftext = '\0';
    if ((v != NULL) && (*v < 1.0E9))
      sprintf (ftext,"%.1f",*v);
    *field = ftext;
    }
  }

void FrmDevDec::Update ()
  {
  if (field != NULL) {
    POINT pt;
    if (Initialized = GetFldPos (&pt)) {
      int format = GetFormat ();
      if (format != oldFormat) {
        delete field ;
        field = NULL ;
        GetField (oldFormat = format);
        SetFieldMode (FM_NOSELECTION);
        oldFormat = format;
        }
      *field = pt;
      }
    else {
      delete field ;
      field = NULL ;
      }
    }
  else {
    GetField (GetFormat());
    SetFieldMode (FM_NOSELECTION);
    }

  SetText ();
  if (field != NULL)
    field->Reformat ();
  }

void FrmDevDec::SetConnection ()
  {
  m.SetConnection (DDPar()->NormRec,DDPar()->NormId,Offset());
  m.SetConnection (DDPar()->DevRec,DDPar()->DevId,Offset());
  FrmDec::SetConnection ();
  }

void FrmDevDec::Reset (BOOL doClear)
  {
  m.ClearConnection (DDPar()->NormRec,DDPar()->NormId,Offset());
  m.ClearConnection (DDPar()->DevRec,DDPar()->DevId,Offset());
  FrmDec::Reset (doClear);
  }

int FrmDevDec::GetFormat ()
  {
  int res;
  float FAR *Val = (float FAR *) m.ReadData (DDPar()->fld.DataRec,
                                      DDPar()->fld.DataId);
  float FAR *Norm = (float FAR *)m.ReadData (DDPar()->NormRec,
                                      DDPar()->NormId);
  float FAR *Dev = (float FAR *)m.ReadData (DDPar()->DevRec,
                                      DDPar()->DevId);
  int ind ;
  if ((Val != NULL) && (*Val < 1.0E9) &&
        (Norm != NULL) && (*Norm < 1.0E9) &&
        (Dev != NULL) && (*Dev < 1.0E9) && (*Dev >= 1.0E-3)) {
    ind = int (fabs (*Val - *Norm) / *Dev);
    }
  else 
    ind = 0;
  if (ind == 0)
    res = m.GetConstInt(DDPar()->fld.rFormat);
  else if (ind == 1)
    res = m.GetConstInt(DDPar()->rf1);
  else
    res = m.GetConstInt(DDPar()->rf2);

  return res;
  }

BOOL FrmCheckBox::GetOrg (POINT *o)
  {
  fpt FAR *org = (fpt FAR *) m.ReadData (Par()->PtRec,Par()->PtId);
  if (org != NULL) {
    o->x = m.WorldToLog (org->x);
    o->y = m.WorldToLog (org->y);
    return TRUE ;
    }
  else
    return FALSE ;
  }

BOOL FrmCheckBox::GetCheckPos ()
  {
  if ((Initialized) && (Par()->PtRec == 0xFFFE))
    return TRUE ;
  POINT o;
  if (GetOrg (&o)) {
    x1 = o.x ;
    y1 = o.y ;
    DBINT FAR *lpx = (DBINT FAR *) m.ReadlData (Par()->rxOff);
    DBINT FAR *lpy = (DBINT FAR *) m.ReadlData (Par()->ryOff);
    if ((lpx != NULL) && (lpy != NULL)) {
      x1 += *lpx;
      y1 += *lpy;
      Initialized = TRUE ;
      int w = m.GetConstInt (Par()->rwidth);
      x2 = x1 + w ;
      y2 = y1 + (IsCheckField() ? m.GetConstInt(FPar()->rheight) : w);
      return TRUE ;
      }
    else
      return FALSE ;
    }
  return FALSE ;
  }

void FrmCheckBox::ReadFlag ()
  {
  DBBOOL FAR *flag = (DBBOOL FAR *) 
      m.ReadData (Par()->flagRec,Par()->flagId);
  if (flag != NULL)
    State = *flag ;
  else {
    if (DispType == CHECK_TRIPLE) {
      State = -1 ;
      }
    else {
      State = FALSE ;
      m.WriteData (Par()->flagRec,Par()->flagId,&State,sizeof(State),Offset(),FALSE);
      }
    }
  }

void FrmCheckBox::GetMinMax ()
  {
  DWORD color = IsCheckField() ? m.GetConstLong (FPar()->rdiPen) : m.GetConstLong (Par()->rdiPen);
  int width = m.HalfPenWidth(color);
  RECT rcLogRect ;
  rcLogRect.left   = x1 - width ;
  rcLogRect.right  = x2 + width ;
  rcLogRect.top    = y1 - width ;
  rcLogRect.bottom = y2 + width ;
  SetLogRect (&rcLogRect,ErsteSeite());
  }

void FrmCheckBox::Load()
  {
  if (IsCheckField()) {
    if (FPar()->hd.par_Size >= (sizeof(Frm_DefCheckField_par) - 2 * sizeof(DWORD)))
      hlpStr = SkipHeader (LPSTR (m.ReadData (FPar()->hlpRec,FPar()->hlpId)));
    DispType = CHECK_NORMAL;
    if (FPar()->hd.par_Size >= (sizeof(Frm_DefCheckField_par) - sizeof(DWORD)))
      DispType = m.GetConstInt (FPar()->rDispType);
    }
  else {
    if (Par()->hd.par_Size >= (sizeof(Frm_DefCheckBox_par) - 2 * sizeof(DWORD)))
      hlpStr = SkipHeader (LPSTR (m.ReadData (Par()->hlpRec,Par()->hlpId)));
    DispType = CHECK_NORMAL;
    if (Par()->hd.par_Size >= (sizeof(Frm_DefCheckBox_par) - sizeof(DWORD)))
      DispType = m.GetConstInt (Par()->rDispType);
    }
  if (Initialized = GetCheckPos ())
    ReadFlag ();
  }

void FrmCheckBox::Update ()
  {
  Load();
  }

void FrmCheckBox::Save ()
  {
  if (Initialized) {
    if (State == -1)
      m.DelData (Par()->flagRec,Par()->flagId,Offset());
    else
      m.WriteData (Par()->flagRec,Par()->flagId,&State,sizeof(State),Offset());
    }
  if (RefForWrite != 0L) {
    DBINT done = TRUE ;
    m.WriteData (LOWORD(RefForWrite),HIWORD(RefForWrite),&done,sizeof(TRUE),Offset());
    }
  }

void FrmCheckBox::SetConnection ()
  {
  m.SetConnection (Par()->flagRec,Par()->flagId,Offset());
  m.SetConnection (Par()->PtRec,  Par()->PtId,  Offset());
  m.SetlConnection (Par()->rxOff,Offset());
  m.SetlConnection (Par()->ryOff,Offset());
  m.SetlConnection (Par()->rwidth,Offset());
  if (IsCheckField()) {
    m.SetlConnection (FPar()->rheight,Offset());
    m.SetlConnection (FPar()->rdiPen,Offset());
    if (FPar()->hd.par_Size >= (sizeof(Frm_DefCheckField_par) - 2 * sizeof(DWORD)))
      m.SetConnection (FPar()->hlpRec,FPar()->hlpId,Offset());
    if (FPar()->hd.par_Size >= (sizeof(Frm_DefCheckField_par) - sizeof(DWORD)))
      m.SetlConnection (FPar()->rDispType,Offset());
    if (FPar()->hd.par_Size >= sizeof(Frm_DefCheckField_par))
      m.SetlConnection (FPar()->rEnable,Offset());
    }
  else {
    m.SetlConnection (Par()->rdiPen,Offset());
    if (Par()->hd.par_Size >= (sizeof(Frm_DefCheckBox_par) - 2 * sizeof(DWORD)))
      m.SetConnection (Par()->hlpRec,Par()->hlpId,Offset());
    if (Par()->hd.par_Size >= (sizeof(Frm_DefCheckBox_par) - sizeof(DWORD)))
      m.SetlConnection (Par()->rDispType,Offset());
    if (Par()->hd.par_Size >= sizeof(Frm_DefCheckBox_par))
      m.SetlConnection (Par()->rEnable,Offset());
    }
  }

void FrmCheckBox::Reset (BOOL doClear)
  {
  m.ClearConnection (Par()->flagRec,Par()->flagId,Offset());
  m.ClearConnection (Par()->PtRec,  Par()->PtId,  Offset());
  m.ClearlConnection (Par()->rxOff,Offset());
  m.ClearlConnection (Par()->ryOff,Offset());
  m.ClearlConnection (Par()->rwidth,Offset());
  if (IsCheckField()) {
    m.ClearlConnection (FPar()->rheight,Offset());
    m.ClearlConnection (FPar()->rdiPen,Offset());
    if (FPar()->hd.par_Size >= (sizeof(Frm_DefCheckField_par) - 2 * sizeof(DWORD)))
      m.ClearConnection (FPar()->hlpRec,FPar()->hlpId,Offset());
    if (FPar()->hd.par_Size >= (sizeof(Frm_DefCheckField_par) - sizeof(DWORD)))
      m.ClearlConnection (FPar()->rDispType,Offset());
    if (FPar()->hd.par_Size >= sizeof(Frm_DefCheckField_par))
      m.ClearlConnection (FPar()->rEnable,Offset());
    }
  else {
    m.ClearlConnection (Par()->rdiPen,Offset());
    if (Par()->hd.par_Size >= (sizeof(Frm_DefCheckBox_par) - 2 * sizeof(DWORD)))
      m.ClearConnection (Par()->hlpRec,Par()->hlpId,Offset());
    if (Par()->hd.par_Size >= (sizeof(Frm_DefCheckBox_par) - sizeof(DWORD)))
      m.ClearlConnection (Par()->rDispType,Offset());
    if (Par()->hd.par_Size >= sizeof(Frm_DefCheckBox_par))
      m.ClearlConnection (Par()->rEnable,Offset());
    }
  }

void FrmCheckBox::Paint (PaintContext *pc,int Seite)
  {
  if (Initialized) {
    DWORD diPen = IsCheckField() ? m.GetConstLong (FPar()->rdiPen) : m.GetConstLong (Par()->rdiPen);
    DWORD actPen = diPen;   // ist Rot oder normal, je nach IsActive
  
    if (IsActive) {
      actPen = diPen & 0xFF000000;
      actPen |= 0x000000FF ;
      }

    switch (DispType) {
      case CHECK_NORMAL:
        pc->diPen (actPen);
        *pc << Line (x1,y1,x2,y1);
        *pc << Line (x2,y1,x2,y2);
        *pc << Line (x2,y2,x1,y2);
        *pc << Line (x1,y2,x1,y1);
        if (State) {
          *pc << Line (x1,y1,x2,y2);
          *pc << Line (x1,y2,x2,y1);
          }
        break;
      case CHECK_GREY:
        pc->diPen (actPen);
        if (State) {
          HBRUSH gb = (HBRUSH)CreateSolidBrush(RGB(0xC0,0xC0,0xC0));
          HBRUSH oldb = (HBRUSH)SelectObject(pc->hDC,gb);
          HPEN oldpen = (HPEN)SelectObject(pc->hDC,GetStockObject(NULL_PEN));
          int dx = pc->XPHYStoLOG(1);
          Rectangle(pc->hDC,x1,y1,x2+dx,y2+dx);
          SelectObject(pc->hDC,oldb);
          SelectObject(pc->hDC,oldpen);
          DeleteObject(gb);
          }
        if (pc->mode != DO_PRINT) {
          *pc << Line (x1,y1,x2,y1);
          *pc << Line (x2,y1,x2,y2);
          *pc << Line (x2,y2,x1,y2);
          *pc << Line (x1,y2,x1,y1);
          }
        break;
      case CHECK_BLACK:
      case CHECK_BLACK_WITH:
        pc->diPen (actPen);
        if (State) {
          HBRUSH gb = (HBRUSH)CreateSolidBrush(RGB(0x00,0x00,0x00));
          HBRUSH oldb = (HBRUSH)SelectObject(pc->hDC,gb);
          HPEN oldpen = (HPEN)SelectObject(pc->hDC,GetStockObject(NULL_PEN));
          int dx = pc->XPHYStoLOG(1);
          Rectangle(pc->hDC,x1,y1,x2+dx,y2+dx);
          SelectObject(pc->hDC,oldb);
          SelectObject(pc->hDC,oldpen);
          DeleteObject(gb);
          }
        if ((pc->mode != DO_PRINT) || (DispType == CHECK_BLACK_WITH)) {
          *pc << Line (x1,y1,x2,y1);
          *pc << Line (x2,y1,x2,y2);
          *pc << Line (x2,y2,x1,y2);
          *pc << Line (x1,y2,x1,y1);
          }
        break;
      case CHECK_TRIPLE:
        pc->diPen (actPen);
        *pc << Line (x1,y1,x2,y1);
        *pc << Line (x2,y1,x2,y2);
        *pc << Line (x2,y2,x1,y2);
        *pc << Line (x1,y2,x1,y1);
        if (State >= 0) {
          int x1p = pc->XLOGtoPHYS(x1);
          int x2p = pc->XLOGtoPHYS(x2);
          int y1p = pc->YLOGtoPHYS(y1);
          int y2p = pc->YLOGtoPHYS(y2);
          int xm = (x1p + x2p) / 2;
          int ym = (y1p + y2p) / 2;
          int dx = pc->XLOGtoPHYS((x2 - x1) / 8);
          int dy = pc->XLOGtoPHYS((y2 - y1) / 8);
          if (State == 1)
            *pc << Line (pc->XPHYStoLOG(xm),pc->YPHYStoLOG(y1p + dy),
                         pc->XPHYStoLOG(xm),pc->YPHYStoLOG(y2p - dy + 1));
          *pc << Line (pc->XPHYStoLOG(x1p + dx),pc->YPHYStoLOG(ym),
                       pc->XPHYStoLOG(x2p - dx + 1),pc->YPHYStoLOG(ym));
          }
        break;
      case CHECK_RADIO:
        {
        pc->diPen (actPen);
        HBRUSH oldb = (HBRUSH)SelectObject(pc->hDC,GetStockObject(NULL_BRUSH));
        int ddx = pc->XPHYStoLOG(1);
        Ellipse(pc->hDC,x1,y1,x2+ddx,y2+ddx);
        SelectObject(pc->hDC,oldb);
        if (State) {
          pc->diPen (actPen & 0xFF000000);
          HBRUSH gb = (HBRUSH)CreateSolidBrush(RGB(0x00,0x00,0x00));
          oldb = (HBRUSH)SelectObject(pc->hDC,gb);
          int x1p = pc->XLOGtoPHYS(x1);
          int x2p = pc->XLOGtoPHYS(x2);
          int y1p = pc->YLOGtoPHYS(y1);
          int y2p = pc->YLOGtoPHYS(y2);
          int dx = pc->XLOGtoPHYS((x2 - x1) / 5);
          int dy = pc->XLOGtoPHYS((y2 - y1) / 5);
          Ellipse(pc->hDC,pc->XPHYStoLOG(x1p + dx),pc->YPHYStoLOG(y1p + dy),
                  pc->XPHYStoLOG(x2p - dx + 1),pc->YPHYStoLOG(y2p - dy + 1));
          SelectObject(pc->hDC,oldb);
          DeleteObject(gb);
          }
        }
        break;
      default:
        DBWIN_ASSERT(FALSE);
      }
    }
  }

BOOL FrmCheckBox::OnKeyDown (WORD key,int Seite)
  {
  if ((key == VK_SPACE) && 
      (!m.IsDocLocked(GetMainRec ()))) {
    if (DispType == CHECK_TRIPLE) {
      if (State == -1)     State = 1;
      else if (State == 1) State = 0;
      else                 State = -1;
      }
    else {
      State = !State ;
      }
    Write (this,TRUE);
    Save ();
    Invalidate (Seite);
    return TRUE ;
    }
  return FALSE ;
  }

void FrmObject::ScrollInto ()
  {
  RECT r;
  POINT pt[2];
  LPRECT logr = GetLogRect (m.ActSide());
  if (logr != NULL) {
    {
    PaintContext pcscreen;
    GetDocumentContext (&pcscreen,m);
    CopyRect (&r,(LPRECT)&pcscreen.cr);
  
    // Berechnen des Bildschirmkoordinaten
    pt[0].x = logr->left ;
    pt[0].y = logr->top ;
    pt[1].x = logr->right ;
    pt[1].y = logr->bottom ;

    LPtoDP (pcscreen.hDC,pt,2);
    }     // Invoke Destruktor for pcscreen

    InflateRect (&r,-10,-10);
    if ((!PtInRect (&r,pt[0])) || (!PtInRect (&r,pt[1]))) {
      if (pt[0].x > pt[1].x) {
        int dummy = pt[1].x ; pt[1].x = pt[0].x ; pt[0].x = dummy ;
        }
      int dx,dy ;
      if (pt[0].x < r.left)          dx = pt[0].x - r.left ;
      else if (pt[1].x > r.right) {
        dx = pt[1].x - r.right ;
        if (pt[0].x - dx < r.left)   dx = 0;
        }
      else                           dx = 0 ;

      if (pt[0].y < r.top)           dy = pt[0].y - r.top ;
      else if (pt[1].y > r.bottom)   dy = pt[1].y - r.bottom ;
      else                           dy = 0 ;

      NeedScroll_Info nsi;
      nsi.pt.x = dx ;
      nsi.pt.y = dy ;
      nsi.Seite = m.ActSide() ;
      NeedScroll (&nsi,m);
      }
    }
  }

void FrmCheckBox::SetActive (int Seite,BOOL bexplicit)
  {
  IsActive = TRUE ;
  Invalidate (Seite);
  if (HelpExist()) {
    ShowFieldHelp();
    m.SetCaretShown ();
    }

  if (bexplicit)
    ScrollInto ();
  }

void FrmCheckBox::SetInActive (int Seite)
  {
  IsActive = FALSE ;
  Invalidate (Seite);
  m.SetNoCaret ();
  }

BOOL FrmCheckBox::OnLButtonDown (WPARAM wP,int x,int y,int Seite)
  {
  POINT pt;
  pt.x = x ;
  pt.y = y ;
  LPRECT logr ;
  if (fieldForCheck != NULL)
    logr = fieldForCheck->GetLogRect(Seite);
  else
    logr = NULL ;
  if ((Initialized) &&
      ((((LONG (x - x1) * LONG (x - x2)) < 0) &&
       ((LONG (y - y1) * LONG (y - y2)) < 0)) ||
         ((logr != NULL) && (PtInRect (logr,pt)))) && 
      (IsCheckField() ? FPar()->IsEnabled (&m) : Par()->IsEnabled (&m)) &&
      (!m.IsDocLocked(GetMainRec ()))) {
    if (DispType == CHECK_TRIPLE) {
      if (State == -1)     State = 1;
      else if (State == 1) State = 0;
      else                 State = -1;
      }
    else {
      State = !State ;
      }
    Write (this,TRUE);
    Save ();
    Invalidate (Seite);
    return TRUE ;
    }
  return FALSE ;
  }

BOOL FrmCheckBox::HelpExist() 
  {
  return ((hlpStr != NULL) && (*hlpStr)) ;
  }

void FrmCheckBox::ShowFieldHelp()
  {
  m.SetStatus (hlpStr);
  }

// allgemeine Hilfsfunktionen

// float Runden auf int
inline int myround(float x)
  {
  return (x < 0.0) ? int(x - 0.5) : int (x + 0.5);
  }


// skalieren in logischen Koordinaten
DLLExport void _export WINAPI Sc2dLog(tr2 FAR *sc, int FAR *dx, int FAR *dy, int sx, int sy)
  {
  fpt pt;
  pt.x = float(sx);
  pt.y = float(sy);
  Sc2d(sc, &pt, &pt);
  *dx = myround(pt.x);
  *dy = myround(pt.y);
  }

typedef uGetVGrid_param FAR *LPGVP;
void OutVGrid::Load ()
  {
  LPGVP FAR *p = (LPGVP FAR *) m.ReadlData (Par()->vdef);
  if (Initialized = ((p != NULL) && (*p != NULL))) {
    v = *p;
    tr2 FAR *lpsc = (tr2 FAR *) m.ReadlData (Par()->sdef);
    if (lpsc != NULL) {
      sc = (tr2 FAR *) GetGlobMem (sizeof(*sc));
      lmemcpy (sc,lpsc,sizeof(*sc));
      }
    else
      Initialized = FALSE ;
    }
  }

void OutVGrid::Update ()
  {
  if (sc != NULL) FreeGlobMem (sc);
  sc = NULL;
  Load();
  }

void OutVGrid::SetConnection ()
  {
  m.SetlConnection (Par()->sdef,Offset());
  }

void OutVGrid::Reset (BOOL doClear)
  {
  m.ClearlConnection (Par()->sdef,Offset());
  if (sc != NULL) FreeGlobMem (sc);
  sc = NULL;
  }

inline void chk(float &xmin,float &xmax,float x)
  {
  if (x < xmin) xmin = x ;
  if (x > xmax) xmax = x ;
  }

void OutVGrid::GetMinMax ()
  {
  float xmin = float(1.0E10);
  float ymin = float(1.0E10);
  float xmax = float(-1.0E10);
  float ymax = float(-1.0E10);
  for (int i = 0 ; i < v->v->AnzPts ; i++) {
    fpt xn;
    Sc2d (sc,&xn,v->v->pts+i);
    chk (xmin,xmax,xn.x);
    chk (ymin,ymax,xn.y);
    }
  xmin -= float(3.0);  ymin -= float(3.0);
  xmax += float(3.0);  ymax += float(3.0);
  RECT rcLogRect;
  rcLogRect.left   = m.WorldToLog (xmin);
  rcLogRect.right  = m.WorldToLog (xmax);
  rcLogRect.top    = m.WorldToLog (ymin);
  rcLogRect.bottom = m.WorldToLog (ymax);
  SetLogRect (&rcLogRect,ErsteSeite());
  }

void OutVGrid::Paint (PaintContext *pc,int Seite)
  {
  pc->diPen (Par()->color);
  v->v->Paint(pc->hDC,sc);
  }


// Library - Notwendigkeiten

DLLExport void _export WINAPI InitFrmObjLib(HWND hFrameWin, HINSTANCE hInstance, DCCB_VOID_VOID FAR *dccallbacks,BOOL forEdit)
  {
  WBase_hFrameWin = hFrameWin;
  WBase_hInstance = hInstance;
  lmemcpy(&dcfunc, dccallbacks, sizeof(DCCB_VOID_VOID) * ANZ_DC_FUNCS);

  _ForEdit = forEdit;
  }


// ehemalige inline-Funktionen:
DLLExport WORD _export WINAPI FrmObject::GetMainRec ()
  { return 0; }
DLLExport void _export WINAPI FrmObject::WorkOn (LPVOID)            // Spezialfunktion (z.B. F2)
  { }
DLLExport void _export WINAPI FrmObject::GetWord (LPVOID Info)      // Umsetzung des Codes in ein Wort
  { }
DLLExport void _export WINAPI FrmObject::TestChar (LPVOID Info)     // Testen eines Buchstabens
  { }
DLLExport void _export WINAPI FrmObject::OnMapChange (double,int,int,int,int,int)
  { }                                   // Mapping - Positionen haben
                                        // sich geaendert
DLLExport void _export WINAPI FrmObject::OnPageChange (int Seite)
  { }                                   // Mapping - Positionen haben
                                        // sich geaendert
DLLExport void _export WINAPI FrmObject::StartExternPaint ()
  { }
DLLExport void _export WINAPI FrmObject::EndExternPaint ()
  { }
DLLExport void _export WINAPI FrmObject::OnRecChange (WORD rType)
  { }
DLLExport BOOL _export WINAPI FrmObject::IsCheckBox ()
  { return FALSE ; } // Ist das Objekt eine Checkbox ?
DLLExport BOOL _export WINAPI FrmObject::IsInputObj ()
  { return FALSE ; }
DLLExport BOOL _export WINAPI FrmObject::IsField ()                 // Ist das Objekt ein Feld (oder CheckBox)
  { return FALSE ; }
#ifdef SDOC
DLLExport BOOL _export WINAPI FrmObject::IsNodeObject ()
  { return FALSE ; }
#endif
DLLExport int _export WINAPI FrmObject::yLower (int Seite)
  { return 0 ; }
DLLExport void _export WINAPI FrmObject::NewPrinter ()
  { }
DLLExport BOOL _export WINAPI FrmObject::IsTextField()
  { return FALSE ; }
DLLExport BOOL _export WINAPI FrmObject::IsmNum ()
  { return FALSE ; }
DLLExport BOOL _export WINAPI FrmObject::ForceToBackground ()
  { return FALSE ; }
DLLExport BOOL _export WINAPI FrmField::IsTextField()
  { return TRUE ; }
DLLExport WORD _export WINAPI FrmField::GetMainRec ()
  { return Par()->DataRec ; }
DLLExport BOOL _export WINAPI FrmField::IsField ()                 
  { return TRUE ; }
DLLExport BOOL _export WINAPI FrmMultiField::SkipNonex()
  { return TRUE ; }
DLLExport BOOL _export WINAPI FrmDec::IsSchiebe ()
  { return FALSE ; }
DLLExport BOOL _export WINAPI FrmSlantSLDec::IsSchiebe ()
  { return TRUE ; }
DLLExport BOOL _export WINAPI FrmSLDec::IsSchiebe ()
  { return TRUE ; }
DLLExport BOOL _export WINAPI FrmCheckBox::IsCheckField ()
  { return FALSE ; }
DLLExport BOOL _export WINAPI FrmCheckBox::IsToActivate ()
  { return ((Initialized) && (IsCheckField() ? FPar()->IsEnabled (&m) : Par()->IsEnabled (&m))) ; }
DLLExport BOOL _export WINAPI FrmCheckBox::IsCheckBox ()
  { return TRUE ; }
DLLExport WORD _export WINAPI FrmCheckBox::GetMainRec ()
  { return Par()->flagRec ; }
DLLExport BOOL _export WINAPI mNum::IsmNum ()
  { return TRUE ; }

void FrmField::OnCaretPosChg ()
  {
  if (ModifyParam != 0xFFFFFFFF) {
    WORD newModify = field->GetActModify ();
    WORD FAR *oldModify = (WORD FAR *)
      m.ReadlData (ModifyParam) ;
    if ((oldModify == NULL) || (*oldModify != newModify))
      m.WriteData (LOWORD(ModifyParam),HIWORD(ModifyParam),&newModify,sizeof(newModify),Offset());
    }
  if (ColorParam != 0xFFFFFFFF) {
    DWORD newColor = field->GetActColor ();
    DWORD FAR *oldColor = (DWORD FAR *)
      m.ReadlData (ColorParam) ;
    if ((oldColor == NULL) || (*oldColor != newColor))
      m.WriteData (LOWORD(ColorParam),HIWORD(ColorParam),&newColor,sizeof(newColor),Offset());
    }
  }

DLLExport void _export WINAPI FrmField::SetModifyParam (DWORD mParam)
  {
  ModifyParam = mParam ;
  OnCaretPosChg ();
  }

DLLExport void _export WINAPI FrmField::SetColorParam (DWORD mParam)
  {
  ColorParam = mParam ;
  OnCaretPosChg ();
  }

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
      hLibInst = hModule;
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
extern "C" {
int WINAPI WEP (int nShutdownFlag)
  {
  return 1 ;
  }

int WINAPI LibMain (HANDLE hInstance,WORD wDataSeg, WORD wHeapSize,
                        LPSTR lpszCmdLine)
  {
  hLibInst = hInstance;

  if (wHeapSize > 0)
    LocalInit (wDataSeg,NULL,wHeapSize);

  return 1 ;
  }
}

#endif

