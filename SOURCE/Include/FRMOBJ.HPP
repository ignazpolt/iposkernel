///////////////////////////////////////////////////////////////////////
//
//  Objekte, die in Formularen vorkommen koennen
//
///////////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/include/rev/frmobj.hpv   1.57   02 Feb 2000 20:49:42   Martin  $
//  $Log:   P:/marille/clinicum/include/rev/frmobj.hpv  $
// 
//    Rev 1.57   02 Feb 2000 20:49:42   Martin
// ClickPoint in ActivationRegion
// 
//    Rev 1.56   25 Nov 1999 02:52:24   Hannes
// ObjInfo als String
// 
//    Rev 1.55   23 Nov 1999 17:22:42   Hannes
// Div. Erweiterungen
// 
//    Rev 1.54   04 Aug 1999 18:27:40   Wolfgang
// 1.) skipNextChar neu.
// 2.) Date/Time-OnChar in OnKeyDown umgebaut.
// 
//    Rev 1.53   28 Jul 1999 16:50:38   Wolfgang
// 1.) OnChar fuer FrmDate und FrmTime neu.
// 
//    Rev 1.52   10 May 1999 18:45:28   Martin
// doPrev richtiggestellt
// 
//    Rev 1.51   07 May 1999 00:19:52   Hannes
// NextObjDef beim uFrmShowObject
// 
//    Rev 1.50   05 Mar 1999 10:55:54   Hannes
// Diverse Verbesserunge Combo - Liste
// 
//    Rev 1.49   09 Oct 1998 18:14:10   Hannes
// Farben in Strings
// 
//    Rev 1.48   05 Oct 1998 11:24:36   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.47   24 Jul 1998 18:48:48   Wolfgang
// 1.) SetInActiveIf virtuell.
// 2.) Activation-Region mit eigenem SetInActiveIf.
// 
//    Rev 1.46   09 Jul 1998 17:49:12   Hannes
// CheckActivation
// 
//    Rev 1.45   08 Jun 1998 23:30:54   Hannes
// Neuen Check - Typ
// 
//    Rev 1.44   08 Jun 1998 14:51:38   Martin
// FieldColor in FrmField
// 
//    Rev 1.43   04 Jun 1998 15:50:58   Hannes
// SetDirKey sauber
// 
//    Rev 1.42   21 Apr 1998 19:31:40   Hannes
// Erweiterung des Containerbausteines
// 
//    Rev 1.41   13 Mar 1998 17:21:56   Hannes
// 
//    Rev 1.40   16 Feb 1998 08:07:32   Gerhold
// VC++5.x ... explicit darf nicht als Var. verwendet werden (Schluesselwort)
// 
//    Rev 1.39   01 Dec 1997 19:38:36   Hannes
// Diverse Anpassungen
// 
//    Rev 1.38   29 Oct 1997 18:59:44   Hannes
// Textbausteine
// 
//    Rev 1.37   08 Sep 1997 11:06:58   Gerhold
// rechte Maustaste in Formularen
// 
//    Rev 1.36   03 Sep 1997 10:26:54   Hannes
// 
//    Rev 1.35   18 Aug 1997 18:13:22   Martin
// VTO Formular-faehig
// 
//    Rev 1.33   07 Aug 1997 14:04:08   Martin
// rEnable in FrmCheckField
// 
//    Rev 1.32   06 Aug 1997 14:15:38   Martin
// CHECK_RADIO
// 
//    Rev 1.31   13 Mar 1997 14:10:40   Hannes
// SetModifyFlag
// 
//    Rev 1.30   08 Nov 1996 13:29:44   HANNES
// Zahlenformatierung
// 
//    Rev 1.29   17 Jun 1996 17:21:44   HANNES
// FrmTime:: Mit Modifier
// 
//    Rev 1.28   10 Jun 1996 10:15:12   GERHOLD
// pragma pack
// 
//    Rev 1.27   04 Apr 1996 18:36:56   HANNES
// Korrekturen des Seitenumbruchhandlings
// 
//    Rev 1.26   24 Mar 1996 12:21:22   martin
// Umstellung auf mehrseitige cFields
// 
//    Rev 1.25   22 Mar 1996 12:14:52   HANNES
// Aenderungen Hannes
// 
//    Rev 1.24   02 Feb 1996 11:00:26   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.23   10 Jan 1996 21:05:18   MARTIN
// 
//    Rev 1.22   29 Nov 1995 11:15:56   GERHOLD
// StaticBitmap (SetConnection, Reset, Update)
// 
//    Rev 1.21   20 Nov 1995 11:45:02   HANNES
// GetLastFormPressedChar
// 
//    Rev 1.20   09 Nov 1995 20:24:12   MARTIN
// CHECK_TRIPLE
// 
//    Rev 1.19   27 Aug 1995 13:05:46   HANNES
// 
//    Rev 1.18   10 Aug 1995 09:18:50   HANNES
// FormatDate,Checkbox und Feld zusammengehaengt
// 
//    Rev 1.17   11 Jun 1995 19:17:28   MARTIN
// Laengenbegrenzung bei frmobjs
// 
//    Rev 1.16   11 Jun 1995 10:03:18   MARTIN
// Objekte fuer die Druckvorlagen
// 
//    Rev 1.15   31 Mar 1995 13:12:02   HANNES
//  
// 
//    Rev 1.14   30 Mar 1995 11:32:46   GERHOLD
// 
//    Rev 1.13   20 Mar 1995 12:16:20   HANNES
// Konstantenhanling, RunNmbr
// 
//    Rev 1.12   09 Jan 1995 12:11:52   HANNES
// Debugger eingebaut
// 
//    Rev 1.11   15 Nov 1994 10:57:36   HANNES
// 
//    Rev 1.10   31 Oct 1994 09:50:28   martin
// FrmTab - Objekte auf Referenz umgestellt
// 
//    Rev 1.9   20 Oct 1994 17:54:28   GERHOLD
// FrmField-Maus Nachrichten geaendert
// 
//    Rev 1.8   22 Sep 1994 16:12:04   GERHOLD
// 
//    Rev 1.7   20 Sep 1994 11:30:32   HANNES
// Trc_DefFilledCont
// 
//    Rev 1.6   05 Aug 1994 20:43:46   HANNES
// FrmTime
// 
//    Rev 1.5   05 Aug 1994 17:16:34   HANNES
// LoadDefIcon
// 
//    Rev 1.4   27 Jun 1994 11:00:02   MARTIN
// exportierte virtuelle Funktionen nicht mehr inline
// 
//    Rev 1.3   27 Jun 1994 10:09:26   MARTIN
// new, delete von FrmObjectList nicht exportiert
// 
//    Rev 1.2   24 Jun 1994 20:21:32   HANNES
// 
//    Rev 1.1   24 Jun 1994 19:18:20   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.52   19 Apr 1994 18:22:56   MARTIN
// SetInActive ....
// 
//    Rev 1.51   13 Apr 1994 20:55:52   MARTIN
// image - Sachen in frmobj3.hpp ausgelagert
// 
//    Rev 1.50   10 Mar 1994 11:26:34   MARTIN
// Weichteil in Bild malen
// 
//    Rev 1.49   02 Mar 1994 21:00:46   MARTIN
// farbige Bilder
// 
//    Rev 1.47   09 Feb 1994 19:15:08   MARTIN
// Lampstate
// 
//    Rev 1.46   04 Feb 1994 17:01:14   MARTIN
// TWAIN sauberer (Martin)
// OnRecChange (Hannes)
// 
//    Rev 1.45   26 Jan 1994 20:48:58   HANNES
// IsField() bei CheckBoxen korrigiert
// 
//    Rev 1.44   16 Jan 1994 18:57:48   HANNES
// Neuer Item in FrmRecInd
// 
//    Rev 1.43   11 Jan 1994 19:08:30   HANNES
// FrmField::field public zugaenglich gemacht
// 
//    Rev 1.42   04 Jan 1994 17:08:56   HANNES
// Neue virtuelle Funktion: NewPrinter... Setzen eines anderen Druckers
// 
//    Rev 1.41   09 Dec 1993 15:05:48   HANNES
// Direktes Include der Pascal Files
// Benutzerliste auch mit Kuerzel
// 
//    Rev 1.40   29 Nov 1993 08:47:10   HANNES
// 
//    Rev 1.39   16 Nov 1993 04:24:56   HANNES
// 
//    Rev 1.38   18 Oct 1993 19:52:32   HANNES
// DefFrmBField
// 
//    Rev 1.37   15 Oct 1993 10:06:10   HANNES
// Hilfe bei den Punkten
// 
//    Rev 1.36   06 Oct 1993 09:53:00   HANNES
// PrgIcon,FrmStaticBitmap
// 
//    Rev 1.35   04 Oct 1993 09:46:04   HANNES
// Klasse DocObject
// 
//    Rev 1.34   22 Sep 1993 09:22:52   HANNES
// Version nach St. Poelten
// 
//    Rev 1.33   05 Sep 1993 22:20:10   HANNES
// ??
// 
//    Rev 1.32   25 Aug 1993 16:00:20   MARTIN
// Filterfunktionen
// 
//    Rev 1.31   23 Aug 1993 19:01:02   MARTIN
// Image-Umstellung (FrmImage)
// 
//    Rev 1.30   18 Aug 1993 12:51:48   MARTIN
// Prototyp von OnScanReady
// 
//    Rev 1.29   18 Aug 1993 10:40:40   HANNES
// Endgueltige Umstellung auf Tools
// 
//    Rev 1.28   12 Jul 1993 07:59:36   HANNES
// ???
// 
//    Rev 1.27   06 Jul 1993 20:06:46   MARTIN
// TrcImage
// 
//    Rev 1.26   05 Jul 1993 14:50:12   HANNES
// Multiselektionslisten, InvalidateOnUpdate
// 
//    Rev 1.25   19 Jun 1993 19:37:44   HANNES
// Multiselektionslisten
// 
//    Rev 1.24   17 Jun 1993 09:25:20   HANNES
// Erste Versuche mit der Multiliste
// 
//    Rev 1.23   08 Jun 1993 17:44:30   MARTIN
// FrmDefDec
// 
//    Rev 1.22   25 May 1993 11:51:08   HANNES
// lastactive eingefuegt
// 
//    Rev 1.21   24 May 1993 14:20:22   HANNES
// Slant - Felder
// 
//    Rev 1.20   13 May 1993 13:17:42   HANNES
// Startexternpaint, Endexternpaint
// 
//    Rev 1.19   10 May 1993 12:51:46   HANNES
// Kuerzelsystem eingebaut
// 
//    Rev 1.18   06 May 1993 20:59:22   ANDI
// vertikale Zahlenfolgen in Tabellenfeldern
// 
// 
//    Rev 1.17   28 Apr 1993 18:50:08   NORBERT
// neue Tabelle-funktionen: DefFrmTabStrList, DefFrmTabDate
// 
//    Rev 1.16   22 Apr 1993 21:06:08   MARTIN
// Rueckgabewert von GetPtToObjVect geaendert auf BOOL
// 
//    Rev 1.15   18 Apr 1993 22:56:20   MARTIN
// Checkbox erweitert
// 
//    Rev 1.14   02 Apr 1993 18:04:36   HANNES
// Erweiterungen (speziell Tabellen)
// 
//    Rev 1.13   17 Mar 1993 18:02:30   HANNES
// 32 bit Umstellung
// 
//    Rev 1.12   11 Mar 1993 11:41:04   HANNES
// Mehrseitensupport
// 
//    Rev 1.11   08 Mar 1993 14:17:44   HANNES
// Erweiterungen in bezug auf den Formulareditor
// 
//    Rev 1.10   03 Mar 1993 15:40:54   MARTIN
// Erweiterung von FrmObject::OnLButtonDown um den wP Parameter
// (auch fuer OnLButtonDblClk und OnLButtonUp)
// 
//    Rev 1.9   02 Mar 1993 22:37:38   HANNES
// Erweiterungen bei EdWin
// 
//    Rev 1.8   26 Feb 1993 13:49:24   HANNES
// Formulareditor
// 
//    Rev 1.7   22 Feb 1993 17:23:12   HANNES
// Kurze Stringlisten, DirKeys
// 
//    Rev 1.6   17 Feb 1993 15:26:04   MARTIN
// Erweiterungen fuer VTO
// 
//    Rev 1.5   16 Feb 1993 19:46:20   MARTIN
// Anpassung fuer Trc_Objects
// 
//    Rev 1.4   16 Feb 1993 13:07:42   HANNES
// Verschiedene Erweiterungen, Verbesserungen...
// 
//    Rev 1.3   14 Feb 1993 15:54:40   HANNES
// Gleiche Objekte fuer Formulare und Tracings
// 
//    Rev 1.2   11 Feb 1993 14:19:24   HANNES
// DefFrmSozNr
// 
//    Rev 1.1   05 Feb 1993 19:40:56   HANNES
// Verschiedene Verbesserungen an der Klasse FrmSLDec
// 
//    Rev 1.0   01 Feb 1993 12:12:38   HANNES
// Initial revision.
//
//
#define TYPE_FORM   0
#define KAT_STRING  0
#define KAT_DATE    1
#define KAT_TIME    2
#define KAT_FLOAT   3
#define KAT_SHORT   4
#define KAT_LONG    5
#define KAT_NONE    -1

// Definition der Parameter der Einzelnen Objekte
///////////////////////////////////////////////////////
DLLExport extern void _export WINAPI MyUnionRect (LPRECT,LPRECT,LPRECT);
DLLExport void _export WINAPI InitFrmObjLib(HWND hFrameWin, HINSTANCE hInstance, DCCB_VOID_VOID FAR *dccallbacks,BOOL forEdit = FALSE);

class FrmObject;
typedef FrmObject FAR *LPFRMOBJ;


extern LPFRMOBJ ContextObject;    // ausgewaehltes Objekt bei Mausereignissen

#pragma pack(1)
struct FrmObjPar_Header {
  WORD par_Size;
  LPFRMOBJ ObjInst;
  WORD ObjRec,ObjId;
  };
#pragma pack()

typedef FrmObjPar_Header FAR *LPFRMOBJHEADER;
inline LPFRMOBJ GetObjectFromPar (LPVOID param,mdiChild *c)
  {
  return ((LPFRMOBJHEADER) param)->ObjInst;
  }

// Feld Allgemein
//////////////////////////////
#pragma pack(1)
struct Frm_DefField {
  FrmObjPar_Header hd;
  // zus. Daten von dem Script
  WORD DataRec,DataId;    // Referenz auf die zu referenzierende Objekte
  WORD PtRec,PtId;        // Referenz auf den Ursprung
  DWORD rx0,ry0;             // Offset zum Ursprung
  DWORD rFormat;            // Format des Feldes
  DWORD rWidth;             // Laenge des Feldes
  DWORD rAnzLines;          // Anzahl Zeilen
  DWORD rdoSelect;          // Soll Selektionsrahmen um das Feld gezeichnet
                          // werden
  WORD HlpRec,HlpId;      // Hilfe - Text
  };
#pragma pack()

typedef Frm_DefField FAR *LPFRMDEFFIELD ;

#pragma pack(1)
struct Frm_DefDate {
  Frm_DefField fld;
  WORD prfRec,prfId;      // Eventuell angegebener Formatierungsstring
  };
#pragma pack()

typedef Frm_DefDate FAR *LPFRMDATEFIELD ;

#pragma pack(1)
struct Frm_DefTime {
  Frm_DefField fld;
  WORD prfRec,prfId;      // Eventuell angegebener Formatierungsstring
  };
#pragma pack()

typedef Frm_DefTime FAR *LPFRMTIMEFIELD ;

#pragma pack(1)
struct Frm_DefSlantField {
  Frm_DefField fld;
  WORD aR,aI;
  };
#pragma pack()

typedef Frm_DefSlantField FAR *LPFRMAFIELD ;

#pragma pack(1)
struct Frm_MultiField {
  Frm_DefField fld;
  WORD lRec,lId;
  };
#pragma pack()

typedef Frm_MultiField FAR *LPMDEFFIELD;

#pragma pack(1)
struct Frm_DefTabField {
  struct Frm_DefField f;
  DWORD rReihe,rSpalte;
  };
#pragma pack()

typedef Frm_DefTabField FAR *LPFRMTABFIELD ;

#pragma pack(1)
struct Frm_DefDec {
  Frm_DefField fld;
  WORD prfRec,prfId;      // Eventuell angegebener Formatierungsstring
  };
#pragma pack()

typedef Frm_DefDec FAR *LPFRMDEFDEC ;

#pragma pack(1)
struct Frm_DefDefDec {
  Frm_DefDec fld;
  WORD defR,defI;    // Defaultwert
  WORD flagR,flagI;
  };
#pragma pack()
typedef Frm_DefDefDec FAR *LPFRMDDEC ;

#pragma pack(1)
struct Frm_DefSlantDec {
  Frm_DefDec fld;
  WORD aR,aI;
  };
#pragma pack()
typedef Frm_DefSlantDec FAR *LPFRMADEC ;

#pragma pack(1)
struct Frm_DefTabDec {
  Frm_DefDec dec;       // Formatierungsstring muss immer angegeben werden
  DWORD rReihe,rSpalte;
  };
#pragma pack()
typedef Frm_DefTabDec FAR *LPFRMDEFTABDEC ;

#define TABCOLMODE_COL    0
#define TABCOLMODE_ROW    1
#pragma pack(1)
struct Frm_DefTabColDec { 
  FrmObjPar_Header hd;
  WORD TabRec,TabId;        // Verweis auf die Tabelle
  WORD svalr,svali;         // Verweis auf den Startwert
  WORD evalr,evali;         // Verweis auf den EndWert
  DWORD rReihe,rSpalte;        // Tabellenfeld
  DWORD rmode;                // Siehe TABCOLMODE_...
  DWORD rx0,ry0;               // Offset zum Ursprung
  DWORD rFormat;              // Format des Feldes
  DWORD rwidth;               // Laenge des Feldes
  WORD fr,fi;               // Format zum Drucken (bsp. <"%.2f">)
  };
#pragma pack()

typedef Frm_DefTabColDec FAR *LPTABCOLDEC ;

#pragma pack(1)
struct Frm_FKurveSp {
  WORD valr,vali;
  WORD cdr,cdi;
  };
#pragma pack()

#pragma pack(1)
struct Frm_DefFKurve {
  FrmObjPar_Header hd;
  WORD colr,coli;
  DWORD rmode;
  Frm_FKurveSp x[1];
  };
#pragma pack()
typedef Frm_DefFKurve FAR *LPFCURVE;

#pragma pack(1)
struct Frm_DefStrList {
  Frm_DefField fld;
  WORD srRec,srId;        // Eventuell angegebene Stringresource
  };
#pragma pack()

typedef Frm_DefStrList FAR *LPFRMSTRLISTPAR;

#pragma pack(1)
struct Frm_DefTabStrList {
  Frm_DefStrList slist;
  DWORD rReihe,rSpalte;
  };
#pragma pack()
typedef Frm_DefTabStrList FAR *LPFRMTABSTRLISTPAR;

#pragma pack(1)
struct Frm_DefTabShortStrList {
  Frm_DefStrList slist;
  DWORD rReihe,rSpalte;
  };
#pragma pack()
typedef Frm_DefTabShortStrList FAR *LPFRMDEFTABSHORTSTRLIST ;

#pragma pack(1)
struct Frm_SozVersNr {
  struct Frm_DefField fld;
  WORD DateRec,DateId;    // Zusaetzlich wird noch das geburtsdatum gebraucht
  };
#pragma pack()
typedef Frm_SozVersNr FAR *LPFRMSOZVERSNR ;

#pragma pack(1)
struct Frm_DefDevDec {
  struct Frm_DefField fld;
  WORD NormRec,NormId;    // Zusaetzlich wird noch die Norm und die
  WORD DevRec,DevId;      // Stdabw. angegeben
  DWORD rf1,rf2;             // Formate bei ev. Abweichung
  };
#pragma pack()
typedef Frm_DefDevDec FAR *LPFRMDEVDEC ;

#pragma pack(1)
struct Frm_RIField {
  struct Frm_DefField d;
  DWORD rRecordtype;        // Typ der Liste, die aufgebaut werden soll
  DWORD savedone;
  };
#pragma pack()
typedef Frm_RIField FAR *LPRIDEFFIELD ;

#pragma pack(1)
struct Frm_BenField {
  struct Frm_DefField d;
  DWORD rshowShortName;     // Sollen Kurznamen oder Vollnamen angezeigt werden
  };
#pragma pack()
typedef Frm_BenField FAR *LPBENDEFFIELD ;

// Linie
//////////////////
#pragma pack(1)
struct Frm_DefLine {
  FrmObjPar_Header hd;
  // zus. Daten vom Script
  WORD p1Rec,p1Id;      // Referenz auf Punkt eins und zwei
  WORD p2Rec,p2Id;
  WORD cRec,cId;          // Referenz auf die Farbe
  };
#pragma pack()
typedef Frm_DefLine FAR *LPDEFLINE;

// Tabelle
////////////////////////////
#pragma pack(1)
struct Frm_Tab {
  FrmObjPar_Header hd;
  WORD pR,pI;         // li. o. Punkt
  DWORD rAnzSpalten;
  DWORD rAnzReihen;
  DWORD rs1Width;       // Weite der 1. Spalte
  DWORD rsWidth;        // Weite der rest. Spalten
  DWORD rr1Height;      // Hoehe der 1. Reihen
  DWORD rrHeight;       // Hoehe der weiteren Reihen
  WORD cuR,cuI;       // Farbe der Umrandung
  WORD cv1R,cv1I;     // Farbe der 1. vert. Linie
  WORD cvR,cvI;       // Farben der vert. inneren Linien
  WORD ch1R,ch1I;     // Farbe der 1. hor. Linien
  WORD chR,chI;       // Farbe der restlichen Linien
  };
#pragma pack()
typedef Frm_Tab FAR *LPFRM_TAB;

#ifdef UEBERLEGT
// Metafile
////////////////////
#pragma pack(1)
struct Frm_DefPattern {
  FrmObjPar_Header hd;
  // zus. Daten vom Script
  WORD PicRec,PicId;      // Bild - Referenz
  WORD PtRec,PtId;        // li. oberer Punkt des MF's
  DWORD rscale;            // Vergroesserungsfaktor des Bildes
  DWORD rMirror_x,rMirror_y; // Welche Seite gehoert gespiegelt
  };
#pragma pack()
#endif

// Definitionen fuer Frm_DefCheckBox_par.DispType
#define CHECK_NORMAL 0
#define CHECK_GREY   1
#define CHECK_BLACK  2
#define CHECK_TRIPLE 3
#define CHECK_RADIO  4
#define CHECK_BLACK_WITH  5

#pragma pack(1)
struct FAR Frm_DefCheckBox_par {
  FrmObjPar_Header hd;        // das uebliche
  WORD flagRec,flagId;        // Flag, das gezeichnet werden soll
  WORD PtRec,PtId;            // Relativ - Punkt
  DWORD rxOff,ryOff;             // xOffset,yOffset
  DWORD rwidth;                 // Weite der Checkbox
  DWORD rdiPen;                 // Stift, der verwendet werden soll
  WORD hlpRec,hlpId;          // Hilfe zu der Checkbox
  DWORD rDispType;             // Art der Darstellung (optional)
  DWORD rEnable;               // Enable / Disable (optional, default enable)
  BOOL IsEnabled (dllChild *c) {
    if (hd.par_Size == sizeof(*this)) return BOOL(c->GetConstInt(rEnable));
    else                              return TRUE ;
    }
  };
#pragma pack()
typedef Frm_DefCheckBox_par FAR *LPDEFCHECKBOX;

#pragma pack(1)
struct FAR Frm_DefCheckBox_OhneEnable_par {
  FrmObjPar_Header hd;        // das uebliche
  WORD flagRec,flagId;        // Flag, das gezeichnet werden soll
  WORD PtRec,PtId;            // Relativ - Punkt
  DWORD rxOff,ryOff;             // xOffset,yOffset
  DWORD rwidth;                 // Weite der Checkbox
  DWORD rdiPen;                 // Stift, der verwendet werden soll
  WORD hlpRec,hlpId;          // Hilfe zu der Checkbox
  DWORD rDispType;             // Art der Darstellung (optional)
  };
struct Frm_DefTabFlag {
  Frm_DefCheckBox_OhneEnable_par flg;
  DWORD rReihe,rSpalte;
  };
#pragma pack()
typedef Frm_DefTabFlag FAR *LPFRMDEFTABFLAG ;

#pragma pack(1)
struct Frm_DefCheckField_par {
  FrmObjPar_Header hd;        // das uebliche
  WORD flagRec,flagId;        // Flag, das gezeichnet werden soll
  WORD PtRec,PtId;            // Relativ - Punkt
  DWORD rxOff,ryOff;             // xOffset,yOffset
  DWORD rwidth;                 // Weite der Checkbox
  DWORD rheight;                // Hoehe der Checkbox
  DWORD rdiPen;                 // Stift, der verwendet werden soll
  WORD hlpRec,hlpId;          // Hilfe zu der Checkbox
  DWORD rDispType;             // Art der Darstellung (optional)
  DWORD rEnable;               // Enable / Disable (optional, default enable)
  BOOL IsEnabled (dllChild *c) {
    if (hd.par_Size == sizeof(*this)) return BOOL(c->GetConstInt(rEnable));
    else                              return TRUE ;
    }
  };
#pragma pack()
typedef Frm_DefCheckField_par FAR *LPDEFCHECKFIELD;

#pragma pack(1)
struct Frm_DefCheckField_OhneEnable_par {
  FrmObjPar_Header hd;        // das uebliche
  WORD flagRec,flagId;        // Flag, das gezeichnet werden soll
  WORD PtRec,PtId;            // Relativ - Punkt
  DWORD rxOff,ryOff;             // xOffset,yOffset
  DWORD rwidth;                 // Weite der Checkbox
  DWORD rheight;                // Hoehe der Checkbox
  DWORD rdiPen;                 // Stift, der verwendet werden soll
  WORD hlpRec,hlpId;          // Hilfe zu der Checkbox
  DWORD rDispType;             // Art der Darstellung (optional)
  };
struct Frm_DefTabCheckField {
  Frm_DefCheckField_OhneEnable_par fld;
  DWORD rReihe,rSpalte;
  };
#pragma pack()
typedef Frm_DefTabCheckField FAR *LPFRMDEFTABCHECKFIELD ;

#pragma pack(1)
struct GetFieldLeftLower_par {
  WORD par_Size;
  short xold,yold;
  WORD pr,pi;
  WORD or,oi;
  struct {
    WORD tr,ti;
    } dep[1];
  };
#pragma pack()

#pragma pack(1)
struct GetFieldLeftLowerSeite_par {
  WORD par_Size;
  short xold,yold;
  WORD pr,pi;
  WORD or,oi;
  DWORD Seite;
  struct {
    WORD tr,ti;
    } dep[1];
  };
#pragma pack()

// Struktur fuer Move - Objekte
struct FAR MoveObj {
 private:
  WORD EdType;  // siehe Konstanten ET_*
  WORD Moving;
  BOOL ClearOld;
  RECT XORRect;
  POINT StartPos;
  long StartTime;
  DWORD DblClkProc;
  BOOL CheckNE(LPFRMOBJ o, POINT pt);
  BOOL CheckSE(LPFRMOBJ o, POINT pt);
  BOOL CheckSW(LPFRMOBJ o, POINT pt);
  BOOL CheckNW(LPFRMOBJ o, POINT pt);
  BOOL CheckN (LPFRMOBJ o, POINT pt);
  BOOL CheckE (LPFRMOBJ o, POINT pt);
  BOOL CheckS (LPFRMOBJ o, POINT pt);
  BOOL CheckW (LPFRMOBJ o, POINT pt);
  BOOL CheckM (LPFRMOBJ o, POINT pt);
  void DrawXOR (PaintContext *pc, RECT FAR *r);
 public:
  DLLExport void _export WINAPI SetEdType(WORD et);
  DLLExport void _export WINAPI SetDblClkProc(DWORD procoffs);
  DLLExport void _export WINAPI GetMinMax(LPFRMOBJ o);
  DLLExport BOOL _export WINAPI OnLButtonDown(LPFRMOBJ o, int x, int y);
  DLLExport void _export WINAPI OnLButtonDblClk(LPFRMOBJ o, int x, int y);
 private:
  void DoActMove(LPFRMOBJ o, int x, int y, RECT FAR *r, BOOL DoXOR);
 public:
  DLLExport BOOL _export WINAPI OnMouseMove(LPFRMOBJ o, int x, int y, RECT FAR *r);
  DLLExport BOOL _export WINAPI OnLButtonUp(LPFRMOBJ o, int x, int y, RECT FAR *r);
  DLLExport BOOL _export WINAPI OnSetCursor(LPFRMOBJ o, int x, int y);
  DLLExport void _export WINAPI Paint(LPFRMOBJ o, PaintContext *pc);
  };
typedef MoveObj FAR *LPMOVEOBJ ;

// Konstanten fuer MoveObj.EdType;
#define ET_N        0x0001
#define ET_NE       0x0002
#define ET_E        0x0004
#define ET_SE       0x0008
#define ET_S        0x0010
#define ET_SW       0x0020
#define ET_W        0x0040
#define ET_NW       0x0080
#define ET_M        0x0100
#define ET_RECT     0x0200
#define ET_LINE     0x0400
#define ET_REALTIME 0x0800
#define ET_NEGXY    0x1000


// Far - Klassen fuer die Objekte
////////////////////////////////////
// Basis Klasse
class FAR FrmFarObject {
 public :
  DLLExport LPVOID _export WINAPI operator new (size_t);
  DLLExport void _export WINAPI operator delete (LPVOID size);
  };

#ifndef FRECT_DEFINED
struct FAR fRECT {
  int left,top,right,bottom;
  };
#define FRECT_DEFINED
#endif

#define DIRID_UP       0
#define DIRID_DOWN     1
#define DIRID_LEFT     2
#define DIRID_RIGHT    3

#define SETCURSOR_NONE      0
#define SETCURSOR_DONE      1
#define SETCURSOR_WANTDEF   2
struct FAR LogRectNode {
  int Seite;
  fRECT r;
  LogRectNode FAR *Next;
  };

#pragma pack(1)
struct FAR uFrmShowObject_par {
  WORD par_Size;
  WORD ObjRec;
  WORD ObjId;
  DWORD _sSide;         // Seite fuer das Objekt
  DWORD _sdoPrint;      // Objekt druckbar
  DWORD prevObj;        // Sollte ein Vorgaengerobjekt angegeben Sein
  DWORD nextObj;        // Sollte ein Nachfolgerobjekt angegeben Sein

  int _Side (mdiChild *c);
  BOOL _doPrint(mdiChild *c);
  BOOL CheckSort();
  BOOL doPrev ()    // Nur Gueltig wenn CheckSort...
    {
    return ((par_Size >= (sizeof(*this) - sizeof(nextObj))) && (LOWORD(prevObj) != 2)) ;
    }
  };
#pragma pack()

typedef uFrmShowObject_par FAR *LPSHOWOBJPAR;
struct ObjectDef {
  LPSHOWOBJPAR par;
  BOOL doPrint;             // Druckbares objekt?
  int ErsteSeite;           // Seite, auf der das Objekt zu erscheinen hat
  BOOL selected;            // selektiert fuer VTO
  DWORD SelColor;           // Farbe, wenn selektiert
  mdiChild *objdoc;         // Dokument, in dem das Objekt definiert wurde
  FrmObject FAR *obj;
  ObjectDef FAR *NextObjDef;
  ObjectDef FAR *PrevObjDef;
  };
typedef ObjectDef FAR *LPOBJDEF;



//---------------------------------------------------------------------------
//
//  Struct fuer die Menubefehle im Script
// 
//---------------------------------------------------------------------------
struct FAR FrmMenuList {
  FrmMenuList FAR *Next;
  LPSTR       Text;
  DWORD       Proc;
  UINT        Flags;
//  LPVOID      MenuPrivData;
//  LPVOID      MenuProcPar;
  };
typedef FrmMenuList FAR * LPFRMMENULIST;


//---------------------------------------------------------------------------
//
//  Klasse FrmObject
// 
//---------------------------------------------------------------------------
class FAR FrmObject : public FrmFarObject {
 private :
  LogRectNode FAR * LogRectList ;

  LogRectNode FAR * GetLogRectNode (int Seite)
    {
    for (LogRectNode FAR *h = LogRectList ; h != NULL ; h = h->Next)
      if (h->Seite == Seite) return h ;
    return NULL ;
    }

  LPOBJDEF       odef ;
  LPFRMMENULIST  lpMenu;             // die Menueintraege eines Objektes

 public :
  int AnzSeiten;
  virtual int MenuType () {
    return KAT_NONE;
    }
  void SetNode (LPOBJDEF n)
    { odef = n ; }
  DWORD RefForWrite;
  LPOBJDEF GetNode ()
    { return odef ; }
  int ErsteSeite()
    { if (odef != NULL) return odef->ErsteSeite ; else return 0 ; }
  int AnzahlSeiten()
    { return (AnzSeiten > 0) ? AnzSeiten : 1 ; }
  void SetzeAnzahlSeiten (int i)
    {
    AnzSeiten = i ;
    }
  void ResetLogRectList ();
  LPFRMOBJHEADER ScriptParam;       // Zeiger auf den Parameterblock
  LPVOID Offset()
    { return LPSTR(ScriptParam) - sizeof (WORD); }
  BOOL rcLogRectInitialized;
  LPRECT GetLogRect(int Seite) // Koordinaten des Objectes in log. Koordinates
    {
    LogRectNode FAR *l = GetLogRectNode(Seite);
    if (l != NULL) return LPRECT (&l->r);
    else           return NULL ;
    }
  void SetLogRect (LPRECT r,int Seite)
    {
    LogRectNode FAR *prev = NULL ;
    for (LogRectNode FAR *h = LogRectList ; h != NULL ; h = h->Next) {
      if (h->Seite == Seite) {
        lmemcpy (&h->r,r,sizeof(h->r));
        return ;
        }
      prev = h ;
      }
    LogRectNode FAR *n = (LogRectNode FAR *) GetGlobMem (sizeof(LogRectNode));
    n->Seite = Seite ;
    lmemcpy (&n->r,r,sizeof(n->r));
    if (prev != NULL) prev->Next = n ;
    else              LogRectList = n ;
    }
  BOOL Initialized;         // Objekt initialisiert
  int schwerx, schwery;     // Schwerpunkt...
  DLLExport void _export WINAPI GetUnionRect(int Seite,LPRECT r);
  DLLExport BOOL _export WINAPI GetDeviceRect(int Seite,LPRECT);
  DWORD CallBackProc;
  DWORD OnActivateProc;
  DWORD OnDeactivateProc;
  DLLExport FrmObject FAR * _export WINAPI GetNBar (int);
                          // phys. Koordinaten des Objectes
  virtual DLLExport BOOL _export WINAPI IsToPaint (int Seite,PaintContext *); // Untersuchnung, ob
                          // Object wirklich gezeichnet werden muss
  DLLExport void _export WINAPI ScrollInto ();
  DLLExport void _export WINAPI Invalidate (int Seite,BOOL erase = TRUE);   // Objekt zum Neuzeichnen zwingen

  dllChild m;   // Referenz auf das Dokument (nicht direkt zugreifen !!!!)

  DWORD NObjs[4];            // Nachbar - Objekte fuer Pfeiltasten
  LPSTR oinf;
  void SetDirKey (DWORD id,int i)
    { NObjs[i] = id ; }
  void SetObjInfo (LPSTR x)
    { 
    if (oinf != NULL) FreeGlobMem (oinf);
    oinf = NULL;
    if (x != NULL) {
      oinf = LPSTR(GetGlobMem (GetBlockSize(x)));
      lstrcpy (oinf,x);
      }
    }
  LPSTR GetObjInfo ()
    {
    return oinf; 
    }
  DLLExport _export WINAPI FrmObject (LPVOID p,mdiChild *mc);
  BOOL IsNextKey (WORD wP)
    { return ((wP == '\t') && (GetKeyState (VK_SHIFT) >= 0)) ; }
  BOOL IsPrevKey (WORD wP)
    { return ((wP == '\t') && (GetKeyState (VK_SHIFT) < 0)) ; }
  BOOL IsCharToSkip (WORD wP)
    { return (wP == '\t') ; }

  virtual DLLExport void _export WINAPI Load ();             // Laden der Daten
  virtual DLLExport void _export WINAPI Update ();           // Irgenwelche Daten haben sich
                                    // geaendert
  virtual DLLExport BOOL _export WINAPI InvalidOnUpdate();   // soll Objekt bei jedem Update
                                    // automatisch neu gezeichnet werden ?
  virtual DLLExport void _export WINAPI Save ();             // Objekt wird angehalten, die Daten
                                    // Neu in die Datenbank zu schreiben
  virtual DLLExport void _export WINAPI GetResource ();      // Resourcen sind gefragt
  virtual DLLExport BOOL _export WINAPI OnValRead (double);  // Schiebelehre...

  virtual DLLExport void _export WINAPI SetConnection();           // Aufsetzen der Verbindung
                                          // zur Datenbank
  virtual DLLExport void _export WINAPI Reset(BOOL);               // Verbindung zur Datenbank
                                          // loeschen, Aufrauemarbeiten
  virtual DLLExport WORD _export WINAPI GetMainRec ();
  virtual DLLExport void _export WINAPI Paint (PaintContext *,int);    // Zeichnen
  virtual DLLExport void _export WINAPI PaintSel (PaintContext *,int); // Zeichnen selektiert
  virtual DLLExport void _export WINAPI PaintTrans (PaintContext *, int, tr2 FAR *); // transformiert
  virtual DLLExport void _export WINAPI Reformat (BOOL forPrinter = FALSE); // Neu Formatieren
  virtual DLLExport void _export WINAPI GetMinMax ();              // Berechnen des rcLogRects
  virtual DLLExport BOOL _export WINAPI GetPtToObjVect (int Ptx, int Pty,
                 int FAR *Vectx, int FAR *Vecty);  // Vektor Pt->Obj

  virtual DLLExport BOOL _export WINAPI IsToActivate ();           // Kann Feld aktiviert werden
  virtual DLLExport DWORD _export WINAPI GetHelpPrefix ();

 private:
  virtual DLLExport void _export WINAPI SetActive (int Seite,BOOL bexplicit);          // Objekt aktivieren setzen
  virtual DLLExport void _export WINAPI SetInActive (int Seite);            // Objekt deaktivieren

 public:
  BOOL IsActive;
  DLLExport void _export WINAPI SetActiveIf (int Seite,BOOL bexplicit);
  virtual DLLExport void _export WINAPI SetInActiveIf (int Seite);
  virtual DLLExport int _export WINAPI OnSetCursor (int,int,int);

  virtual DLLExport BOOL _export WINAPI OnLButtonDown (WPARAM,int,int,int);   // Bearbeiten der Mousenachrichten
  virtual DLLExport BOOL _export WINAPI OnLButtonDblClk (WPARAM,int,int,int); // -..-
  virtual DLLExport BOOL _export WINAPI OnMouseMove (WPARAM,int,int,int);     // -..-
  virtual DLLExport BOOL _export WINAPI OnLButtonUp (WPARAM,int,int,int);     // -..-
  virtual DLLExport BOOL _export WINAPI OnRButtonDown (HWND,WPARAM,int,int,int,BOOL);   // -..-

  virtual BOOL AppendContextMenu (HMENU hMenu);
  virtual BOOL AppendUserContextMenu (HMENU hMenu);
  virtual BOOL GetContextMenu (HWND hWnd, LPFRMOBJ lpfrmobj, int x, int y, int Seite, BOOL ActivateMenu);
  virtual DLLExport void _export WINAPI SetContextMenu (LPSTR text, DWORD proc, UINT flags, WORD mode);
  virtual DLLExport void _export WINAPI RemoveContextMenu ();
  virtual DLLExport BOOL _export WINAPI FrmObject::OnCommand (WPARAM wID);

  virtual DLLExport BOOL _export WINAPI OnKeyDown (WORD,int);          // Bearbeiten der Tastaturnachr.
  virtual DLLExport BOOL _export WINAPI OnChar (WORD,int);             // -..-
  virtual DLLExport BOOL _export WINAPI OnKeyUp (WORD,int);            // -..-

  virtual DLLExport void _export WINAPI WorkOn (LPVOID);            // Spezialfunktion (z.B. F2)
  virtual DLLExport void _export WINAPI GetWord (LPVOID Info);      // Umsetzung des Codes in ein Wort
  virtual DLLExport void _export WINAPI TestChar (LPVOID Info);     // Testen eines Buchstabens

  virtual DLLExport void _export WINAPI OnMapChange (double,int,int,int,int,int);
  virtual DLLExport void _export WINAPI OnPageChange (int);
  DLLExport void _export WINAPI ToDevKoord (int,int,POINT *);      // Umrechnung der Koordinaten in
                                          // dev. Koordinaten (fuer Feldn.)

  virtual DLLExport void _export WINAPI StartExternPaint ();
  virtual DLLExport void _export WINAPI EndExternPaint ();
  virtual DLLExport void _export WINAPI OnRecChange (WORD rType);

  virtual DLLExport int  _export WINAPI OnPrivate1 (int);          // Tabposition berechnen
  virtual DLLExport void _export WINAPI GetSelText ();             // Liefert den aktuellen Text einer Listbox
  virtual DLLExport BOOL _export WINAPI IsCheckBox ();
  virtual DLLExport BOOL _export WINAPI IsInputObj ();
  virtual DLLExport BOOL _export WINAPI IsField ();                // Ist das Objekt ein Feld (oder CheckBox)
#ifdef SDOC
  virtual DLLExport BOOL _export WINAPI IsNodeObject ();
#endif
  virtual DLLExport int _export WINAPI yLower (int Seite);
  virtual DLLExport void _export WINAPI NewPrinter ();

  DLLExport void _export WINAPI Write (FrmObject FAR *,BOOL doUpdate = TRUE); // Den zeiger auf sich selber
                                                     // in die Datenbank schreiben
  void Write ()
    { Write (this) ; }

  // Virtuelle Funktionen zur Zusammenarbeit mit dem Formular - Editor
  /////////////////////////////////////////////////////////////////////
  virtual DLLExport _export WINAPI ~FrmObject ();

  virtual DLLExport BOOL _export WINAPI IsCont();   // ist Objekt eine Kontur ? (fuer Chirurgie)

  virtual DLLExport BOOL _export WINAPI IsTextField();
  virtual DLLExport BOOL _export WINAPI IsmNum ();
  DLLExport HDC _export WINAPI PrinterContext();

  virtual DLLExport BOOL _export WINAPI ForceToBackground ();

  virtual DLLExport LPMOVEOBJ _export WINAPI moptr();
  virtual DLLExport RECT _export WINAPI GetSnapOffsets();

  virtual DLLExport void _export WINAPI CheckActivation ();
  };


// Die Objekte im Einzelnen:
////////////////////////////////
//---------------------------------------------------------------------------
//
//  Klasse FrmField
// 
//---------------------------------------------------------------------------
class FAR FrmCheckBox;
class FrmField : public FrmObject {
 public :
  cField *field;
  BOOL doSelect;
  int MaxStringSize;
  DWORD ModifyParam;
  DWORD ColorParam;
  DWORD FieldColor;
  BOOL skipNextChar;
  virtual int MenuType () {
    return KAT_STRING;
    }

  LPFRMDEFFIELD Par() { return LPFRMDEFFIELD (ScriptParam); }
  DLLExport _export WINAPI FrmField (LPVOID p,mdiChild *c);
  cField *MyField () { return field; }
  virtual DLLExport _export WINAPI ~FrmField () ;
  virtual DLLExport BOOL _export WINAPI IsTextField();

  virtual DLLExport BOOL _export WINAPI GetOrg (POINT *);
  DLLExport BOOL _export WINAPI GetFldPos (POINT *,int *width = NULL);
  DLLExport void _export WINAPI GetField (int);
  DLLExport void _export WINAPI GetField ();
  DLLExport void _export WINAPI GetSlantField (int Format,WORD aR,WORD aI,float FAR *oA);
  DLLExport void _export WINAPI CheckSlantField (WORD aR,WORD aI,float FAR *oA);
  DLLExport void _export WINAPI FrmSlantUpdate (int Format,WORD aR,WORD aI,float FAR *oA);
  DLLExport void _export WINAPI SetFieldMode (DWORD mode);
  DLLExport int _export WINAPI AnzLines ();
  DLLExport LPSTR _export WINAPI HlpStr ();

  virtual DLLExport void _export WINAPI SetText ();
  void OnCaretPosChg ();

  virtual DLLExport WORD _export WINAPI GetMainRec ();
  virtual DLLExport void _export WINAPI Paint (PaintContext *,int);
  virtual DLLExport void _export WINAPI Reformat (BOOL forPrinter = FALSE);
  virtual DLLExport void _export WINAPI GetMinMax ();
  virtual DLLExport void _export WINAPI SetConnection();
  virtual DLLExport void _export WINAPI Reset(BOOL);
  virtual DLLExport BOOL _export WINAPI IsToActivate ();
  virtual DLLExport void _export WINAPI Load ();
  virtual DLLExport void _export WINAPI Update ();
  virtual DLLExport void _export WINAPI Save ();
  virtual DLLExport int _export WINAPI OnSetCursor (int,int,int);
  virtual DLLExport int _export WINAPI yLower (int Seite);

  virtual DLLExport void _export WINAPI OnMapChange (double,int,int,int,int,int);
  virtual DLLExport void _export WINAPI OnPageChange (int);

  virtual DLLExport void _export WINAPI SetActive (int,BOOL);
  virtual DLLExport void _export WINAPI SetInActive (int);
  virtual DLLExport BOOL _export WINAPI IsField ();

  virtual DLLExport void _export WINAPI StartExternPaint ();
  virtual DLLExport void _export WINAPI EndExternPaint ();

  virtual DLLExport BOOL _export WINAPI OnLButtonDown (WPARAM,int,int,int);   // Bearbeiten der Mousenachrichten
  virtual DLLExport BOOL _export WINAPI OnLButtonDblClk (WPARAM,int,int,int); // -..-
  virtual DLLExport BOOL _export WINAPI OnMouseMove (WPARAM,int,int,int);     // -..-
  virtual DLLExport BOOL _export WINAPI OnLButtonUp (WPARAM,int,int,int);   // Bearbeiten der Mousenachrichten
  virtual DLLExport BOOL _export WINAPI OnRButtonDown (HWND,WPARAM,int,int,int,BOOL);   // -..-

  virtual BOOL AppendContextMenu (HMENU hMenu);
  virtual DLLExport BOOL _export WINAPI OnCommand (WPARAM wID);

  virtual DLLExport BOOL _export WINAPI OnKeyDown (WORD,int);          // Bearbeiten der Tastaturnachr.
  virtual DLLExport BOOL _export WINAPI OnChar (WORD,int);             // -..-
  virtual DLLExport BOOL _export WINAPI OnKeyUp (WORD,int);            // -..-

  virtual DLLExport int  _export WINAPI OnPrivate1 (int);          // Tabposition berechnen
  virtual DLLExport int  _export WINAPI GetStringSize ();          // max. Groesse des Strings abfragen
  DLLExport void _export WINAPI SetStringSize (int size);          // max. Groesse des Strings setzen
  DLLExport void _export WINAPI SetModifyParam (DWORD mParam);
  DLLExport void _export WINAPI SetColorParam (DWORD mParam);

  friend BOOL GetFieldLeftLower (mdiChild *c,LPVOID param,WORD mode);

  virtual DLLExport RECT _export WINAPI GetSnapOffsets();
  virtual DLLExport void _export WINAPI WorkOn (LPVOID);            // Spezialfunktion (z.B. F2)

  virtual DLLExport void _export WINAPI CheckActivation ();
  virtual DLLExport DWORD _export WINAPI GetHelpPrefix ();
  };
typedef FrmField FAR *LPFRMFIELD;

class FrmBField : public FrmField {
 public :
  DLLExport _export WINAPI FrmBField (LPVOID p,mdiChild *c);
  virtual DLLExport void _export WINAPI Load ();
  virtual DLLExport void _export WINAPI Update ();
  };

class FrmMultiField : public FrmField {
 public :
  LPMDEFFIELD Par() { return LPMDEFFIELD (ScriptParam); }
  DLLExport _export WINAPI FrmMultiField (LPVOID p,mdiChild *c);
#ifdef MULTI_INCLUDED
  LPMLI List;
#else
  LPVOID List;
#endif
  virtual DLLExport BOOL _export WINAPI SkipNonex();
  virtual DLLExport void _export WINAPI Load ();
  virtual DLLExport void _export WINAPI Update ();
  virtual DLLExport void _export WINAPI WorkOn (LPVOID);           // F2 -> Selektionsliste
  virtual DLLExport void _export WINAPI GetWord (LPVOID Info);
  virtual DLLExport void _export WINAPI TestChar (LPVOID Info);
  virtual DLLExport int  _export WINAPI GetStringSize ()
    { return -1 ; }
  };

class FrmSlantField : public FrmField {
 public :
  LPFRMAFIELD APar () { return LPFRMAFIELD (ScriptParam); }
  DLLExport _export WINAPI FrmSlantField (LPVOID p,mdiChild *c);
  float oldAng;
  DLLExport void _export WINAPI GetField ();
  virtual DLLExport void _export WINAPI Load ();
  virtual DLLExport void _export WINAPI Update ();
  virtual DLLExport void _export WINAPI SetConnection ();
  virtual DLLExport void _export WINAPI Reset (BOOL doClear);

  };

class FrmTabField : public FrmField {
 protected :
  LPFRMTABFIELD Par() { return LPFRMTABFIELD (ScriptParam) ; }
 public :
  DLLExport _export WINAPI FrmTabField (LPVOID p,mdiChild *c);
  virtual DLLExport BOOL _export WINAPI GetOrg (POINT *);
  };

// Spezialfelder
//////////////////////////
class FrmDate : public FrmField {
 public :
  virtual int MenuType () {
    return KAT_DATE;
    }
  LPFRMDATEFIELD DPar() { return LPFRMDATEFIELD (ScriptParam) ; }
  DLLExport _export WINAPI FrmDate (LPVOID p,mdiChild *c);
  virtual DLLExport void _export WINAPI SetText ();
  virtual DLLExport void _export WINAPI Save ();
  virtual DLLExport void _export WINAPI SetInActive (int);
  virtual DLLExport BOOL _export WINAPI OnKeyDown (WORD,int);
  virtual DLLExport void _export WINAPI WorkOn (LPVOID);      // F2 -> heutiges Datum
  virtual DLLExport int  _export WINAPI GetStringSize ()
    { return -1 ; }
  virtual BOOL AppendContextMenu (HMENU hMenu);
  virtual DLLExport BOOL _export WINAPI OnCommand (WPARAM wID);

  };


class FrmTime : public FrmField {
 public :
  virtual int MenuType () {
    return KAT_TIME;
    }
  LPFRMDATEFIELD DPar() { return LPFRMDATEFIELD (ScriptParam) ; }
  LPFRMTIMEFIELD TPar() { return LPFRMTIMEFIELD (ScriptParam) ; }
  DLLExport _export WINAPI FrmTime (LPVOID p,mdiChild *c);
  virtual DLLExport void _export WINAPI SetText ();
  virtual DLLExport void _export WINAPI Save ();
  virtual DLLExport void _export WINAPI SetInActive (int);
  virtual DLLExport BOOL _export WINAPI OnKeyDown (WORD,int);
  virtual DLLExport void _export WINAPI WorkOn (LPVOID);      // F2 -> Aktuelle Zeit
  virtual DLLExport int  _export WINAPI GetStringSize ()
    { return -1 ; }
  virtual BOOL AppendContextMenu (HMENU hMenu);
  virtual DLLExport BOOL _export WINAPI OnCommand (WPARAM wID);
  };

class FrmTabDate : public FrmDate {
 protected :  // Date hat gleiche Parameter wie "field"
  LPFRMTABFIELD Par() { return LPFRMTABFIELD (ScriptParam) ; }
 public :
  DLLExport _export WINAPI FrmTabDate (LPVOID p,mdiChild *c);
  virtual DLLExport BOOL _export WINAPI GetOrg (POINT *);
  };


class FrmSozNr : public FrmField {
 public :
  LPFRMSOZVERSNR Par() { return LPFRMSOZVERSNR (ScriptParam); }
  DLLExport _export WINAPI FrmSozNr (LPVOID p,mdiChild *c);
  virtual DLLExport void _export WINAPI SetText ();
  virtual DLLExport void _export WINAPI SetConnection ();
  virtual DLLExport void _export WINAPI SetInActive (int);
  virtual DLLExport void _export WINAPI Reset (BOOL);
  virtual DLLExport int  _export WINAPI GetStringSize ()
    { return -1 ; }
  };

class FrmDec : public FrmField {
 protected :
  char fstring[16];
 public :
  virtual int MenuType () {
    return KAT_FLOAT;
    }
  LPFRMDEFDEC DPar() { return LPFRMDEFDEC (ScriptParam) ; }
  DLLExport _export WINAPI FrmDec (LPVOID p,mdiChild *c);
  virtual DLLExport void _export WINAPI Load ();
  virtual DLLExport void _export WINAPI Reset(BOOL);
  virtual DLLExport void _export WINAPI Update ();
  virtual DLLExport void _export WINAPI SetText ();
  virtual DLLExport void _export WINAPI Save ();
  DLLExport void _export WINAPI SetDecFieldMode ();
  virtual DLLExport BOOL _export WINAPI OnValRead (double);
  virtual DLLExport void _export WINAPI SetActive (int,BOOL);
  virtual DLLExport void _export WINAPI SetInActive (int);
  virtual DLLExport BOOL _export WINAPI IsSchiebe ();
  virtual DLLExport int  _export WINAPI GetStringSize ()
    { return -1 ; }
  };

class FrmShort : public FrmDec {
 public :
  virtual int MenuType () {
    return KAT_SHORT;
    }
  DLLExport _export WINAPI FrmShort (LPVOID p,mdiChild *c);
  virtual DLLExport void _export WINAPI SetText ();
  virtual DLLExport void _export WINAPI Save ();
  };

class FrmLong : public FrmDec {
 public :
  virtual int MenuType () {
    return KAT_LONG;
    }
  DLLExport _export WINAPI FrmLong (LPVOID p,mdiChild *c);
  virtual DLLExport void _export WINAPI SetText ();
  virtual DLLExport void _export WINAPI Save ();
  virtual DLLExport void _export WINAPI SetConnection();           // Aufsetzen der Verbindung
  virtual DLLExport void _export WINAPI Reset(BOOL);
  };

class FrmMoney : public FrmDec {
 public :
  virtual int MenuType () {
    return KAT_LONG;
    }
  DLLExport _export WINAPI FrmMoney (LPVOID p,mdiChild *c);
  virtual DLLExport void _export WINAPI SetText ();
  virtual DLLExport void _export WINAPI Save ();
  };

class FrmSlantDec : public FrmDec {
 public :
  LPFRMADEC APar () { return LPFRMADEC (ScriptParam); }
  DLLExport _export WINAPI FrmSlantDec (LPVOID p,mdiChild *c);
  float oldAng;
  DLLExport void _export WINAPI GetField ();
  virtual DLLExport void _export WINAPI Load ();
  virtual DLLExport void _export WINAPI Update ();
  virtual DLLExport void _export WINAPI SetConnection ();
  virtual DLLExport void _export WINAPI Reset (BOOL doClear);
  };

class FrmSlantSLDec : public FrmSlantDec {
 public :
  DLLExport _export WINAPI FrmSlantSLDec (LPVOID p,mdiChild *c);
  virtual DLLExport BOOL _export WINAPI IsSchiebe ();
  };

class FrmTabDec : public FrmDec {
 protected :
  LPFRMDEFTABDEC Par() { return LPFRMDEFTABDEC (ScriptParam) ; }
 public :
  DLLExport _export WINAPI FrmTabDec (LPVOID p,mdiChild *c);
  virtual DLLExport BOOL _export WINAPI GetOrg (POINT *);
  };

struct FKpt {
  BOOL isValid;
  BOOL isBorder;
  BOOL hIsValid;
  int x0,x1;
  int y,yb;
  };
typedef FKpt FAR *LPFKPT;
typedef cField FAR *LPCFIELD;
class FrmTabColDec : public FrmObject {
 protected :
  LPTABCOLDEC Par() { return LPTABCOLDEC (ScriptParam) ; }

  int x0;
  int y0,y1;
  int LineHeight;       // Basishoehe einer Zeile
                        // (ist zur Berechnung ausreichend, da nur Zahlen 
                        // gebraucht werden)
  double val0;
  double dval;
  void GetNextRound (double FAR *res, double dmin);
  void val(double FAR *res, int num)
    { *res = val0 + double(num) * dval ; } 
  double a,b;           // fldpos(val) = a * val + b;
  void fldpos (double FAR *res, double val)
    { *res = (val * a + b) ; }
  void valfrompos (double FAR *res, double fldpos)
    { *res = (fldpos - b) / a ; }
  int AnzFields;

  void InitializeTrans ();  // Setzt AnzFields,a,b,val0,dval ... 

  LPCFIELD FAR *fields;
  void FldTopPos(LPPOINT pt,int i);
  void GetFields();
  void DelFields();

 public :
  DLLExport _export WINAPI FrmTabColDec (LPVOID p,mdiChild *c);

  virtual DLLExport void _export WINAPI Load ();             // Laden der Daten
  virtual DLLExport void _export WINAPI Update ();           // Irgenwelche Daten haben sich
                                    // geaendert
  virtual DLLExport void _export WINAPI SetConnection();           // Aufsetzen der Verbindung
                                          // zur Datenbank
  virtual DLLExport void _export WINAPI Reset(BOOL);               // Verbindung zur Datenbank
                                          // loeschen, Aufrauemarbeiten
  virtual DLLExport void _export WINAPI Paint (PaintContext *,int);    // Zeichnen
  virtual DLLExport void _export WINAPI Reformat (BOOL forPrinter = FALSE);               // Neu Formatieren
  virtual DLLExport void _export WINAPI GetMinMax ();              // Berechnen des rcLogRects

  virtual DLLExport void _export WINAPI OnMapChange (double,int,int,int,int,int);

  DLLExport void _export WINAPI GetValPos (LPFKPT pt,double val);
  };
typedef FrmTabColDec FAR *LPTABDECOBJ;

class FrmFKurve : public FrmObject {
 protected :
  DWORD color;
  LPFKPT points;
  int Anz;
  void InitializeLogRect (LPRECT);
  void CheckLogRect (LPRECT rcLogRect,int x,int y);
 public :
  LPFCURVE Par() { return LPFCURVE (ScriptParam) ; }
  DLLExport _export WINAPI FrmFKurve (LPVOID p,mdiChild *c);
  int AnzRows ()
    { return ((Par()->hd.par_Size - sizeof (Frm_DefFKurve)) / 
                sizeof(Frm_FKurveSp)) + 1 ; }
  virtual DLLExport void _export WINAPI Load ();             // Laden der Daten
  virtual DLLExport void _export WINAPI Update ();           // Irgenwelche Daten haben sich
                                    // geaendert
  virtual DLLExport void _export WINAPI SetConnection();           // Aufsetzen der Verbindung
                                          // zur Datenbank
  virtual DLLExport void _export WINAPI Reset(BOOL);               // Verbindung zur Datenbank
                                          // loeschen, Aufrauemarbeiten
  virtual DLLExport void _export WINAPI Paint (PaintContext *,int);    // Zeichnen
  virtual DLLExport void _export WINAPI GetMinMax ();              // Berechnen des rcLogRects
  };

class FrmSLDec : public FrmDec {
 public :
  DLLExport _export WINAPI FrmSLDec (LPVOID p,mdiChild *c);
  virtual DLLExport BOOL _export WINAPI IsSchiebe ();
  };

class FrmDevDec : public FrmDec {
 public :
  LPFRMDEVDEC DDPar () { return LPFRMDEVDEC (ScriptParam) ; }
  DLLExport _export WINAPI FrmDevDec (LPVOID p,mdiChild *c);
  int oldFormat ;
  DLLExport int _export WINAPI GetFormat ();
  virtual DLLExport void _export WINAPI SetText ();
  virtual DLLExport void _export WINAPI Load ();
  virtual DLLExport void _export WINAPI Update ();
  virtual DLLExport void _export WINAPI SetConnection ();
  virtual DLLExport void _export WINAPI Reset (BOOL);
  };

class FrmDefDec : public FrmDec {
 public :
  LPFRMDDEC DefPar () { return LPFRMDDEC (ScriptParam); }
  DLLExport _export WINAPI FrmDefDec (LPVOID p,mdiChild *c);
  virtual DLLExport void _export WINAPI SetText ();
  virtual DLLExport void _export WINAPI SetInActive (int);
  virtual DLLExport void _export WINAPI Save ();
  virtual DLLExport void _export WINAPI SetConnection ();
  virtual DLLExport void _export WINAPI Reset (BOOL doClear);
  virtual DLLExport void _export WINAPI WorkOn (LPVOID);      // F2 -> ruecksetzen auf Defaultwert
  };

class FrmStrList : public FrmField {
 public :
  virtual int MenuType () {
    return KAT_NONE;
    }
  LPFRMSTRLISTPAR SPar () { return LPFRMSTRLISTPAR (ScriptParam) ; }
  GLOBALHANDLE hGRecTxt;
  WORD wInd;
  DLLExport LPSTR _export WINAPI GetStrRes ();
  DLLExport _export WINAPI FrmStrList (LPVOID p,mdiChild *c);
  virtual DLLExport void _export WINAPI Load ();
  virtual DLLExport void _export WINAPI Update ();
  virtual DLLExport void _export WINAPI SetText ();
  virtual DLLExport void _export WINAPI Save ();
  virtual DLLExport void _export WINAPI GetResource ();
  virtual DLLExport void _export WINAPI GetSelText ();             
  virtual DLLExport void _export WINAPI Reset (BOOL);


  virtual DLLExport void _export WINAPI ShowList (LPSTR);
  DLLExport int _export WINAPI CheckOneSel (GLOBALHANDLE hG,LPSTR txt);
  DLLExport int _export WINAPI CheckBestSel (GLOBALHANDLE hG,LPSTR txt);
  virtual DLLExport int  _export WINAPI GetStringSize ()
    { return -1 ; }
  };

class FrmTabStrList : public FrmStrList {
 protected :
  LPFRMTABSTRLISTPAR Par() { return LPFRMTABSTRLISTPAR (ScriptParam) ; }
 public :
  DLLExport _export WINAPI FrmTabStrList (LPVOID p,mdiChild *c);
  virtual DLLExport BOOL _export WINAPI GetOrg (POINT *);
  };

class FrmStrShortList : public FrmStrList {
 public :
  DLLExport _export WINAPI FrmStrShortList (LPVOID p,mdiChild *c);
  virtual DLLExport void _export WINAPI GetSelText ();             
  };

class FrmDivStrList : public FrmStrShortList {
 public :
  DLLExport _export WINAPI FrmDivStrList (LPVOID p,mdiChild *c);
  virtual DLLExport void _export WINAPI ShowList (LPSTR);
  };

class FrmTabShortStrList : public FrmStrShortList {
 protected :
  LPFRMDEFTABSHORTSTRLIST Par() { return LPFRMDEFTABSHORTSTRLIST (ScriptParam) ; }
 public :
  DLLExport _export WINAPI FrmTabShortStrList (LPVOID p,mdiChild *c);
  virtual DLLExport BOOL _export WINAPI GetOrg (POINT *);
  };

struct CmtLE {          // Strukturen werden von der Untersuchungsliste
  int Ind;              // benoetigt
  };

struct CmtDLE {
  int AnzRecs;
  CmtLE c[1];
  };

// graphische Objekte
/////////////////////////
class FrmCheckBox : public FrmObject {
 protected :
  LPSTR hlpStr;
  DWORD DispType;
 public :
  virtual DLLExport BOOL _export WINAPI IsCheckField ();
  LPDEFCHECKBOX Par() { return LPDEFCHECKBOX (ScriptParam); }
  LPDEFCHECKFIELD FPar() { return LPDEFCHECKFIELD (ScriptParam); }
  DLLExport _export WINAPI FrmCheckBox (LPVOID p,mdiChild *c);
  int x1,y1;
  int x2,y2;
  BOOL State;
  BOOL IsActive;

  DLLExport BOOL _export WINAPI GetCheckPos ();
  DLLExport void _export WINAPI ReadFlag ();
  virtual DLLExport void _export WINAPI GetMinMax ();
  virtual DLLExport void _export WINAPI Load ();
  virtual DLLExport void _export WINAPI Update ();
  virtual DLLExport void _export WINAPI Save ();
  virtual DLLExport void _export WINAPI SetConnection ();
  virtual DLLExport void _export WINAPI Reset (BOOL);
  virtual DLLExport void _export WINAPI Paint (PaintContext *,int);
  virtual DLLExport BOOL _export WINAPI OnKeyDown (WORD,int);
  virtual DLLExport BOOL _export WINAPI OnLButtonDown (WPARAM,int,int,int);
  virtual DLLExport BOOL _export WINAPI IsToActivate ();
  virtual DLLExport void _export WINAPI SetActive (int,BOOL);
  virtual DLLExport void _export WINAPI SetInActive (int);
  virtual DLLExport BOOL _export WINAPI IsCheckBox ();
  virtual DLLExport WORD _export WINAPI GetMainRec ();
  virtual DLLExport BOOL _export WINAPI GetOrg (POINT *o);
  DLLExport BOOL _export WINAPI HelpExist();
  DLLExport void _export WINAPI ShowFieldHelp();
  FrmField FAR *fieldForCheck;
  void SetField (FrmField FAR *f)
    {
    fieldForCheck = f ;
    }
  };

class FrmCheckField : public FrmCheckBox {
 public :
  virtual DLLExport BOOL _export WINAPI IsCheckField () { return TRUE ; }
  DLLExport _export WINAPI FrmCheckField (LPVOID p,mdiChild *c);
  };

class FrmTabFlag : public FrmCheckBox {
 protected :
  LPFRMDEFTABFLAG Par() { return LPFRMDEFTABFLAG (ScriptParam) ; }
 public :
  DLLExport _export WINAPI FrmTabFlag (LPVOID p,mdiChild *c);
  virtual DLLExport BOOL _export WINAPI GetOrg (POINT *o);
  };

class FrmTabCheckField : public FrmCheckField {
 protected :
  LPFRMDEFTABCHECKFIELD Par() { return LPFRMDEFTABCHECKFIELD (ScriptParam) ; }
 public :
  DLLExport _export WINAPI FrmTabCheckField (LPVOID p,mdiChild *c);
  virtual DLLExport BOOL _export WINAPI GetOrg (POINT *o);
  };

class FrmLine : public FrmObject {
 public :
  LPDEFLINE Par() { return LPDEFLINE (ScriptParam); }
  int x1,y1,x2,y2;
  LONG diPen;

  DLLExport _export WINAPI FrmLine (LPVOID p,mdiChild *c);

  virtual DLLExport void _export WINAPI GetMinMax ();
  virtual DLLExport void _export WINAPI Load();
  virtual DLLExport void _export WINAPI Update();
  virtual DLLExport void _export WINAPI SetConnection();
  virtual DLLExport void _export WINAPI Reset(BOOL);
  virtual DLLExport void _export WINAPI Paint(PaintContext *pc,int);
  };

class FrmTab : public FrmObject {
 protected :
  LPFRM_TAB Par() { return LPFRM_TAB (ScriptParam); }
 public :
  int x0,y0;
  ffpt p0;
  int width,height;
  DWORD cu,cv1,cv,ch1,ch;
  DLLExport _export WINAPI FrmTab (LPVOID p,mdiChild *c);
  virtual DLLExport void _export WINAPI Load ();
  virtual DLLExport void _export WINAPI Update ();
  virtual DLLExport void _export WINAPI SetConnection ();
  virtual DLLExport void _export WINAPI Reset (BOOL);
  virtual DLLExport void _export WINAPI Paint (PaintContext *,int);
  virtual DLLExport void _export WINAPI GetMinMax ();

  DLLExport BOOL _export WINAPI CalcLogFieldPos (POINT FAR *o,int Reihe,int Spalte);
  DLLExport BOOL _export WINAPI GetFieldPos (POINT FAR *pt,dllChild FAR *c,LONG rReihe,LONG rSpalte);
  DLLExport BOOL _export WINAPI CalcFieldPos (fpt FAR *p,int Reihe,int Spalte);
  };
typedef FrmTab FAR *LPFRMTABOBJ;

#pragma pack(1)
struct FAR mNumSize_param {
  WORD parSize;
  DWORD Obj;            // Datenbankreferenz fuer den Zeiger
  DWORD rx0,ry0;           // Koordinaten der ersten Zeile
  DWORD rnamWidth;        // Weite des Namens
  DWORD runionWidth;      // Weite der Einheiten
  DWORD rxWidth;          // Weite einer normalen Spalte
  DWORD rxspcWidth;       // Weite des Randes, der zwichen den Linien
                        // frei bleiben soll
  DWORD ryspcHeight;      // Hoehe der Unterstreichung (die Linie wird einfach
                        // in die Mitte davon gesetzt)
  DWORD rnamFormat;       // die verschiedenen Schriftformate
  DWORD rvalFormat;
  DWORD rhdnamFormat;
  DWORD rhdvalFormat;
  DWORD rdiPen;           // Stift, mit dem die Linien gezeichnet werden 
                        // sollen
  DWORD valDesc;        // Ueberschrift -> Wie wird Wert geschrieben
  DWORD normDesc;       // Norm -..-
  DWORD devDesc;        // Abweichung -..-

  DWORD rAnzRows;        // Anzahl Gesamtspalten (zur Berechnung der 
                        //    Gesamtbreite schon am beginn ..)

  int HdHeight(dllChild m);
  int ValHeight(dllChild m);
  };
#pragma pack()
typedef mNumSize_param FAR *LPMNSIZE;

#define NMTYPE_HEADLINE   1   // Ueberschrift
#define NMTYPE_NORMAL     2   // Normale Zeile
#define NMTYPE_DESC       3   // Beschreibungszeile ?

#pragma pack(1)
struct mNum_param {
  FrmObjPar_Header hd;
  DWORD prevObj;         // Objekt hinter dem 
  DWORD SizeDesc;        // Beschreibung der Groesse, Formate ...
  DWORD Name;            // Name des Wertes (bzw. der Ueberschrift)
  DWORD Union;           // Einheit
  DWORD rMode;             // Art der Darstellung... (siehe obige Defines)
  DWORD doShow;          // Soll Wert ueberhaupt angezeigt werden
  DWORD rKontextNr;       // Kontext in der Hilfe
  DWORD val,norm,stddev; // Wert, Norm, Standardabweichung
  };
#pragma pack()

class mNum : public FrmObject {
 private :
  inline mNum_param FAR *Par () { return (mNum_param FAR *) ScriptParam; }
 public :
  DLLExport _export WINAPI mNum (LPVOID param,mdiChild *c);
  cField FAR *fld[5];      // max. vier Felder
  int x0,y0;
  int xl,xw,xe,yl;
  DWORD diPen;
  int Run;
  int height;
  BOOL doShow;
  BOOL IsHeadLine ()
    { return (m.GetConstInt(Par()->rMode) == NMTYPE_HEADLINE) ; }
  DLLExport void _export WINAPI GetOrigin ();
  DLLExport int _export WINAPI GetWidth (LPMNSIZE p);
  DLLExport cField FAR * _export WINAPI createField (int x,int format,int w);
  DLLExport void _export WINAPI DelFields ();
  DLLExport void _export WINAPI GetFields ();
  DLLExport void _export WINAPI SetText ();
  DLLExport LPSTR _export WINAPI UnionString ();
  DLLExport LPSTR _export WINAPI ValStr (LPSTR buffer,int size,float FAR *v);
  DLLExport LPSTR _export WINAPI NormStr (LPSTR buffer,int size,float FAR *n);
  DLLExport LPSTR _export WINAPI DevStr (double fval,double fnorm);
  DLLExport BOOL _export WINAPI IsActive ();
  DLLExport void _export WINAPI ShowHelp ();
  DLLExport BOOL _export WINAPI GetGaussData (double FAR *val,double FAR *norm,double FAR *dev,int FAR *anz);
  DLLExport void _export WINAPI ShowGauss ();

  virtual DLLExport void _export WINAPI GetMinMax ();
  virtual DLLExport void _export WINAPI Load ();
  virtual DLLExport void _export WINAPI SetConnection();
  virtual DLLExport void _export WINAPI Reset(BOOL);
  virtual DLLExport void _export WINAPI Reformat (BOOL forPrinter = FALSE);
  virtual DLLExport void _export WINAPI OnMapChange (double scale,int MapType,int xp,int yp,int x0,int y0);
  virtual DLLExport void _export WINAPI StartExternPaint ();
  virtual DLLExport void _export WINAPI EndExternPaint ();
  virtual DLLExport BOOL _export WINAPI IsToActivate ();
  virtual DLLExport void _export WINAPI Update();
  virtual DLLExport void _export WINAPI SetActive (int,BOOL); 
  virtual DLLExport void _export WINAPI SetInActive (int);
  virtual DLLExport void _export WINAPI Paint (PaintContext *pc,int);
  virtual DLLExport BOOL _export WINAPI OnKeyDown (WORD,int);
  virtual DLLExport BOOL _export WINAPI OnChar (WORD,int);
  virtual DLLExport BOOL _export WINAPI OnLButtonDown (WPARAM,int,int,int);
  virtual DLLExport int _export WINAPI yLower (int Seite);
  virtual DLLExport BOOL _export WINAPI IsmNum ();
  };

class FAR FrmObjectList {
 public :
  LPVOID operator new (size_t);
  void operator delete (LPVOID size);

  LPOBJDEF act,head,tail,lastactive;

  mdiChild *c;
  FrmObjectList (mdiChild *m) 
    { c = m ; }

  // Listenverwaltung
  void Add (FrmObject FAR *,int,BOOL,LPSHOWOBJPAR par,mdiChild FAR *caller);
  void Remove (LPSHOWOBJPAR par);
  void Remove (FrmObject FAR *obj);
  LPOBJDEF Find (FrmObject FAR *obj);
  LPOBJDEF Find (LPSHOWOBJPAR par);
  void Change (FrmObject FAR *,LPSHOWOBJPAR par);
  void Change (FrmObject FAR *,FrmObject FAR *);
  void Select (FrmObject FAR *obj, DWORD SelColor);
  void Deselect (FrmObject FAR *obj );
  void BringToTail (FrmObject FAR *obj);

  // Benutzerinteraktion
  void FirstActive ();
  LPOBJDEF GetFirstActive ();
  LPOBJDEF GetLastActive ();
  void NextActive ();
  void PrevActive ();
  void GetLogKoords (LONG,int *,int *);

  BOOL OnSetFocus (BOOL expl = FALSE);
  BOOL OnKillFocus ();
  void DeactivateNode ();
  BOOL OnSetCursor ();
  void SetActiveExplicit (FrmObject FAR *obj,BOOL doExplicit = TRUE);

  ObjectDef FAR *Next(ObjectDef FAR *d);
  ObjectDef FAR *Prev(ObjectDef FAR *d);

  BOOL OnKeyDown (WORD);
  BOOL OnChar    (WORD);
  BOOL OnKeyUp   (WORD);

  void StartExternPaint ();
  void EndExternPaint ();
  void OnRecChange (WORD rType);
  void NewPrinter ();

  BOOL OnButtonDown   (WPARAM,LPARAM,UINT);
  BOOL OnLButtonDblClk (WPARAM,LPARAM);
  BOOL OnMouseMove     (WPARAM,LPARAM);
  BOOL OnLButtonUp     (WPARAM,LPARAM);

  BOOL OnValRead       (double);
  void OnDigitized     (UINT msg,GLOBALHANDLE hGmem);
  void GetMinMax       (LPRECT,BOOL forScreen = TRUE);

  BOOL CheckSide (LPOBJDEF);
  BOOL CheckForPaint (LPOBJDEF,PaintContext *);
  void Paint (PaintContext *);
  void Reformat (BOOL forPrinter = FALSE);

  void OnMapChange ();
  BOOL OnPalChange (HWND hWnd, BOOL ontop);

  BOOL CheckDirKey (WORD);                // Untersuchen der Richtungstasten

  void OrderVTOObjs ();
  void MoveToTail (LPFRMOBJ obj);
  void ChangeSides (int diff);

#ifdef SDOC
  void StoreSubDocs ();
#endif

  ~FrmObjectList ();
  };

#pragma pack(1)
struct PrgIcon_param {
  FrmObjPar_Header hd;
  DWORD prgName;      // Programm, zu dem das Icon gezeichnet werden soll
  DWORD pt0;          // Ursprung des Icons
  };
#pragma pack()

#define ICONELE_BITMAP  0
#define ICONELE_ICON    1
class PrgIcon : public FrmObject {
 protected :
  PrgIcon_param FAR *Par () { return (PrgIcon_param FAR *) ScriptParam ; }
 public :
  DLLExport _export WINAPI PrgIcon (LPVOID p,mdiChild *c);
  int x0l,y0l;
  WORD type;
  union FAR {
    LPBITMAPINFO lpbi;
    HICON  hico;
    } pict;
  DLLExport int          _export WINAPI GetPictHeight ();
  DLLExport int          _export WINAPI GetPictWidth ();
  virtual DLLExport void _export WINAPI Paint (PaintContext *,int);
  virtual DLLExport void _export WINAPI Load ();
  virtual DLLExport void _export WINAPI GetMinMax ();
  virtual DLLExport void _export WINAPI Reset(BOOL);
  virtual DLLExport void _export WINAPI SetConnection();
  virtual DLLExport void _export WINAPI Update ();
  };

#pragma pack(1)
struct FrmStaticBitmap_param {
  FrmObjPar_Header hd;
  DWORD org;
  DWORD pict;
  DWORD ri,rj;
  DWORD transparentColor;
  };
#pragma pack()

class FrmStaticBitmap : public FrmObject {
 protected :
  FrmStaticBitmap_param FAR *Par () { return (FrmStaticBitmap_param FAR *) ScriptParam ; }
 public :
  DLLExport _export WINAPI FrmStaticBitmap (LPVOID p,mdiChild *c);

  HBITMAP hbmp;
  int x0l,y0l;
  int bmpWidth,bmpHeight,xStart,yStart;
  DWORD TransparentColor;
  virtual DLLExport void _export WINAPI Paint (PaintContext *,int);
  virtual DLLExport void _export WINAPI Load ();
  virtual DLLExport void _export WINAPI GetMinMax ();
  virtual DLLExport void _export WINAPI Reset(BOOL);
  virtual DLLExport void _export WINAPI SetConnection();
  virtual DLLExport void _export WINAPI Update ();
  };

#pragma pack(1)
struct ActivationRegion_par {
  FrmObjPar_Header hd;
  DWORD p1,p2;
  DWORD procPtr;
  DWORD mitRahmen;
  DWORD ClickPoint;

  BOOL MitMitRahmen ()
    {
    return (hd.par_Size >= (sizeof(*this) - sizeof(DWORD)));
    }
  BOOL MitClickPoint ()
    {
    return (hd.par_Size >= sizeof(*this));
    }
  };
#pragma pack()

class ActivationRegion : public FrmObject {
 protected :
  ActivationRegion_par FAR * Par() { return (ActivationRegion_par FAR *) ScriptParam ; }
  BOOL mitUmrandung;
 public :
  DLLExport _export WINAPI ActivationRegion (LPVOID p,mdiChild *c);

  int x0,y0,x1,y1;
  virtual DLLExport void _export WINAPI Load ();
  virtual DLLExport void _export WINAPI Update ();
  virtual DLLExport BOOL _export WINAPI OnLButtonDown (WPARAM,int,int,int);
  virtual DLLExport void _export WINAPI Paint (PaintContext *,int);
  virtual DLLExport void _export WINAPI GetMinMax ();
  virtual DLLExport BOOL _export WINAPI OnChar (WORD,int);
  virtual DLLExport void _export WINAPI Reset(BOOL);
  virtual DLLExport void _export WINAPI SetConnection();
  virtual DLLExport BOOL _export WINAPI IsToActivate ();
  virtual DLLExport void _export WINAPI SetActive (int,BOOL); 
  virtual DLLExport void _export WINAPI SetInActive (int);
  virtual DLLExport void _export WINAPI SetInActiveIf (int);

  DLLExport void _export WINAPI CallIt ();
  DLLExport BOOL _export WINAPI IsAct ();
  };


#pragma pack(1)
struct OutVGrid_param {
  FrmObjPar_Header hd;
  DWORD vdef;
  DWORD sdef;
  DWORD color;
  };
#pragma pack()

class FAR OutVGrid : public FrmObject {
 protected :
  OutVGrid_param FAR * Par() { return (OutVGrid_param FAR *) ScriptParam ; }
 public :
#ifdef VORONOI_INCLUDED
  uGetVGrid_param FAR *v;
#else
  LPVOID v;
#endif
  DLLExport _export WINAPI OutVGrid (LPVOID p,mdiChild *c);
  tr2 FAR *sc;

  virtual DLLExport void _export WINAPI Load ();
  virtual DLLExport void _export WINAPI GetMinMax ();
  virtual DLLExport void _export WINAPI Paint (PaintContext *,int);
  virtual DLLExport void _export WINAPI Reset(BOOL);
  virtual DLLExport void _export WINAPI SetConnection();
  virtual DLLExport void _export WINAPI Update ();
  };

extern void InitFrmObjDll(void);

extern void GetDocumentContext (PaintContext *pc,mdiChild *c);
extern void WriteObjectToPar (FrmObject FAR *obj,LPVOID param,mdiChild *c);
extern void InterpreteMode (mdiChild *c,LPVOID param,WORD mode);

// fuer frmobj.dll:
extern DLLExport void _export WINAPI Sc2dLog(tr2 FAR *sc, int FAR *dx, int FAR *dy, int sx, int sy);
extern void GetDocumentContext (PaintContext *pc,dllChild m);
extern void SetCallback (FrmObject FAR *obj,cField FAR *f,dllChild m);
DLLExport WORD _export WINAPI GetLastFormPressedChar ();

DLLExport HICON _export WINAPI LoadDefIcon ();

DLLExport void _export WINAPI SetTranslateColor (DWORD color);
DLLExport void _export WINAPI ResetTranslateColor ();


// Move-Objekte

class MoveField : public FrmField {
  MoveObj mo;
 public :
  DLLExport _export WINAPI MoveField (LPVOID p,mdiChild *c);
  virtual DLLExport LPMOVEOBJ _export WINAPI moptr();
  virtual DLLExport void _export WINAPI GetMinMax ();
  virtual DLLExport BOOL _export WINAPI OnLButtonDown (WPARAM,int,int,int);
  virtual DLLExport BOOL _export WINAPI OnLButtonDblClk (WPARAM,int,int,int);
  virtual DLLExport BOOL _export WINAPI OnMouseMove (WPARAM,int,int,int);
  virtual DLLExport BOOL _export WINAPI OnLButtonUp (WPARAM,int,int,int);
  virtual DLLExport int _export WINAPI OnSetCursor (int,int,int);
  virtual DLLExport BOOL _export WINAPI IsToActivate ();
  virtual DLLExport void _export WINAPI SetActive (int,BOOL);
  virtual DLLExport void _export WINAPI SetInActive (int);
  virtual DLLExport BOOL _export WINAPI OnKeyDown (WORD,int);
  virtual DLLExport BOOL _export WINAPI OnChar (WORD,int);
  virtual DLLExport BOOL _export WINAPI OnKeyUp (WORD,int);
  virtual DLLExport void _export WINAPI Paint(PaintContext *pc,int);
  };

class MoveLine : public FrmLine {
  MoveObj mo;
  void SetSuitableEdType();
 public :
  DLLExport _export WINAPI MoveLine (LPVOID p,mdiChild *c);
  virtual DLLExport LPMOVEOBJ _export WINAPI moptr();
  virtual DLLExport void _export WINAPI GetMinMax ();
  virtual DLLExport BOOL _export WINAPI OnLButtonDown (WPARAM,int,int,int);
  virtual DLLExport BOOL _export WINAPI OnLButtonDblClk (WPARAM,int,int,int);
  virtual DLLExport BOOL _export WINAPI OnMouseMove (WPARAM,int,int,int);
  virtual DLLExport BOOL _export WINAPI OnLButtonUp (WPARAM,int,int,int);
  virtual DLLExport int _export WINAPI OnSetCursor (int,int,int);
  virtual DLLExport BOOL _export WINAPI IsToActivate ();
  virtual DLLExport void _export WINAPI SetActive (int,BOOL);
  virtual DLLExport void _export WINAPI SetInActive (int);
  virtual DLLExport BOOL _export WINAPI OnKeyDown (WORD,int);
  virtual DLLExport BOOL _export WINAPI OnChar (WORD,int);
  virtual DLLExport BOOL _export WINAPI OnKeyUp (WORD,int);
  virtual DLLExport void _export WINAPI Paint(PaintContext *pc,int);
  };

// Hilfslinienobjekt
////////////////////
#pragma pack(1)
struct Frm_HelpLine {
  FrmObjPar_Header hd;
  // zus. Daten vom Script
  WORD kRec,kId;      // Referenz auf x- bzw. y-Koordinate
  WORD tRec,tId;      // Referenz auf Typ (horizontal oder vertikal)
  WORD cRec,cId;      // Referenz auf die Farbe
  };
#pragma pack()
typedef Frm_HelpLine FAR *LPHELPLINE;
// Konstanten fuer Frm_HelpLine.tRec/tId
#define HL_HORIZ 0
#define HL_VERT 1

class HelpLine : public FrmObject {
  MoveObj mo;
  void GetTemporaryMinMax();
 public :
  LPHELPLINE Par() { return LPHELPLINE (ScriptParam); }
  int x1,y1,x2,y2;
  LONG diPen;
  int type;

  virtual DLLExport BOOL _export WINAPI IsToPaint (int Seite,PaintContext *);
  virtual DLLExport void _export WINAPI Load();
  virtual DLLExport void _export WINAPI Update();
  virtual DLLExport BOOL _export WINAPI InvalidOnUpdate();
  virtual DLLExport void _export WINAPI SetConnection();
  virtual DLLExport void _export WINAPI Reset(BOOL);

  DLLExport _export WINAPI HelpLine (LPVOID p,mdiChild *c);
  virtual DLLExport LPMOVEOBJ _export WINAPI moptr();
  virtual DLLExport void _export WINAPI GetMinMax ();
  virtual DLLExport BOOL _export WINAPI OnLButtonDown (WPARAM,int,int,int);
  virtual DLLExport BOOL _export WINAPI OnLButtonDblClk (WPARAM,int,int,int);
  virtual DLLExport BOOL _export WINAPI OnMouseMove (WPARAM,int,int,int);
  virtual DLLExport BOOL _export WINAPI OnLButtonUp (WPARAM,int,int,int);
  virtual DLLExport int _export WINAPI OnSetCursor (int,int,int);
  virtual DLLExport BOOL _export WINAPI IsToActivate ();
  virtual DLLExport void _export WINAPI SetActive (int,BOOL);
  virtual DLLExport void _export WINAPI SetInActive (int);
  virtual DLLExport BOOL _export WINAPI OnKeyDown (WORD,int);
  virtual DLLExport BOOL _export WINAPI OnChar (WORD,int);
  virtual DLLExport BOOL _export WINAPI OnKeyUp (WORD,int);
  virtual DLLExport void _export WINAPI Paint(PaintContext *pc,int);
  };

