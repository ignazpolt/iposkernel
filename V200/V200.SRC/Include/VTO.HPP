// $Header:   P:/marille/clinicum/include/rev/vto.hpv   1.7   18 Aug 1997 18:01:48   Martin  $
// $Log:   P:/marille/clinicum/include/rev/vto.hpv  $
// 
//    Rev 1.7   18 Aug 1997 18:01:48   Martin
// VTO Formular-faehig
// 
//    Rev 1.6   10 Apr 1997 11:13:56   Martin
// 32-bit-isiert
// 
//    Rev 1.5   10 Jun 1996 10:16:12   GERHOLD
// pragma pack
// 
//    Rev 1.4   02 Feb 1996 10:59:40   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.3   20 Mar 1995 12:16:46   HANNES
// Konstantenhanling, RunNmbr
// 
//    Rev 1.2   15 Nov 1994 12:13:38   MARTIN
// VtoContext
// 
//    Rev 1.1   20 Sep 1994 11:31:38   HANNES
// MultiProc Faehigkeit der VTO
// 
//    Rev 1.0   24 Jun 1994 17:01:22   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.15   04 Jan 1994 17:44:24   MARTIN
// Skalierungsfaktor fuer Koordinatenausgabe
// 
//    Rev 1.14   22 Sep 1993 09:12:28   MARTIN
// Version nach St. Poelten
// 
//    Rev 1.13   27 Aug 1993 16:47:04   MARTIN
// Vto_SetMode_par
// 
//    Rev 1.12   15 Jun 1993 23:25:30   MARTIN
// Vto_OnMove, Vto_DrawObject, ....
// 
//    Rev 1.11   19 Apr 1993 01:34:26   MARTIN
// Vto_ShowCut ausgemistet
// 
//    Rev 1.10   02 Apr 1993 18:06:16   MARTIN
// Diverse Aenderungen, die schon so lange zurueckliegen, dass ich
// mich nicht mehr erinnern kann, was ....
// 
//    Rev 1.9   17 Mar 1993 18:19:58   HANNES
// 32 bit Umstellung compiler..
// 
//    Rev 1.8   03 Mar 1993 15:31:26   MARTIN
// diverse Mitteilungen an den Script
// (im Script sind jetzt der Modus, die aktuelle Gruppe usw. verfuegbar)
// 
//    Rev 1.7   17 Feb 1993 15:26:20   MARTIN
// Umbau auf logische Koordinaten und FrmObjects
// 
//    Rev 1.6   14 Feb 1993 16:11:18   MARTIN
// Entwicklung
// 
//    Rev 1.5   05 Feb 1993 19:33:52   MARTIN
// Entwicklung
// 
//    Rev 1.4   01 Feb 1993 11:26:18   MARTIN
// Entwicklung
// 
//    Rev 1.3   29 Jan 1993 21:43:04   MARTIN
// Entwicklung
// 
//    Rev 1.2   29 Jan 1993 19:59:22   HANNES
// Konstruktor
// 
//    Rev 1.1   29 Jan 1993 19:49:42   MARTIN
// Entwicklungsphase (kleine Aenderungen)
// 
//    Rev 1.0   29 Jan 1993 18:33:06   MARTIN
// Initial revision.
// 
// to be included first: tracing.hpp


// Definitionen fuer LastAction

#define ACT_DEFINED 0
#define ACT_MOVED   1
#define ACT_CUT     2

#pragma pack(1)
struct Vto_GrpId {         // Gruppendefinition in Datenbank
  DWORD GrpId;
  WORD LastAction;
  DWORD oldGrpId;          // bei Update: Gruppenid vor der Aenderung
  };


struct Vto_PartDef {       // Gruppenaufteilungsvariable in Datenbank
  DWORD GrpId;             // Untergruppennummer
  WORD PartNum;            // gehoert zu Teilnummer
  };
#pragma pack()


// Definitionen fuer vtomode und grp->SelMode

#define VTO_NOTSEL     0
#define VTO_SELFORMOVE 1
#define VTO_SELFORSOFT 2
#define VTO_SELFORCUT  3

// Definitionen fuer updmode

#define UPD_SELF  0
#define UPD_PART  1
#define UPD_GROUP 2

// Masken fuer Vto_DefineGroup_param.modeflags

#define GRP_MOVEABLE  0x1L      // darf Gruppe bewegt werden ?
#define GRP_ROTABLE   0x2L      // darf Gruppe rotiert werden ?
#define GRP_SOFTEDIT  0x4L      // (nur Kontur) Weichteilkontur editierbar ?
#define GRP_CUTABLE   0x8L      // (nur Kontur) darf geschnitten werden ?
#define GRP_PARTABLE  0x10L     // darf Gruppe aufgeteilt werden ?
// nur interne Verwendung, nicht im Script zu gebrauchen:
#define GRP_ISPART    0x100L    // Gruppe ist Teil

#pragma pack(1)
struct Vto_OnMove_param {
  WORD ParSize;         // Groesse des Parameterblockes
  // Parameterdaten
  DWORD grpid;          // Gruppenid-Nummer
  DWORD MoveProc;       // Offset der Update Prozedur
  };
#pragma pack()

// Definitionen fuer Vto_DrawObject_param.mode:
#define DOM_NORMAL 0
#define DOM_XOR    1

#pragma pack(1)
struct Vto_DrawObject_param {
  WORD ParSize;         // Groesse des Parameterblockes
  // Parameterdaten
  WORD objR, objI;      // zu zeichnendes Objekt
  DWORD _color;          // Farbe zum zeichnen
  DWORD _mode;           // Modus (siehe Konstanten)
  };
#pragma pack()

#pragma pack(1)
struct Vto_SetMode_param {
  WORD ParSize;         // Groesse des Parameterblockes
  // Parameterdaten
  WORD modeR, modeI;    // zu setzender Modus M_* (longvar)
  };
#pragma pack()

// Definitionen fuer mode

#define M_INACTIVE 0
#define M_MOVE     1
#define M_SOFT     2
#define M_CUT      3

// Definitionen fuer state

#define S_NONESELECTED 0
#define S_GRPSELECTED  1
#define S_MOVING       2
#define S_TIMERWAIT    3
#define S_TIMERWAITSEL 4
#define S_ROTATING     5
#define S_CENTMOVING   6
#define S_SOFTEDITING  7
#define S_CUTTING      8

#define VTOTIMERID 2
#define VTODELAY   300
#define ROT_CENT_TOLERANCE 50.0

