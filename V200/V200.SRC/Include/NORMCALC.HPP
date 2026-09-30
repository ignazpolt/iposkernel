//////////////////////////////////////////////////
//  Deklarationen fuer Normwert - Berechnungen  //
//////////////////////////////////////////////////
// $Header:   P:/marille/clinicum/include/rev/normcalc.hpv   1.4   23 Mar 1998 23:12:44   Martin  $
// $Log:   P:/marille/clinicum/include/rev/normcalc.hpv  $
// 
//    Rev 1.4   23 Mar 1998 23:12:44   Martin
// GetGrowthVal: mode -> rmode
// 
//    Rev 1.3   10 Jun 1996 10:15:32   GERHOLD
// pragma pack
// 
//    Rev 1.2   02 Feb 1996 11:01:26   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.1   20 Mar 1995 12:16:42   HANNES
// Konstantenhanling, RunNmbr
// 
//    Rev 1.0   24 Jun 1994 17:01:52   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.1   10 Nov 1993 14:26:18   MARTIN
// neue Funktion GetGrowthVal
// 
//    Rev 1.0   15 Oct 1993 10:32:26   MARTIN
// Initial revision.
// 


// Definitionen fuer Indextypen:  (NC_ = NormCalc)
#define NC_VARTYPE(x) (((x) / 1000L) % 10L)
#define NC_TYPENO(x) (x)     // nur fuer NC_SAMEAS
#define NC_SAMEAS       0L   // gleicher Block wie Nummer NC_TYPENO
#define NC_UNDEF        1L   // Norm (in diesem Unterbaum) nicht definiert
#define NC_FLAG         2L   // BOOLEAN Variable
#define NC_STRIND       3L   // STRFIELD Variable
#define NC_DECVAR       4L   // DEC Variable
#define NC_SUBTYPE(x) (((x) / 100L) % 10L)
#define NC_END          0L   // kein Unterbaum mehr (Blatt)
#define NC_FIX          1L   // alle Unterbaeume sehen gleich aus
#define NC_VARIABLE     2L   // Unterbaeume einzeln angegeben
#define NC_DECTYPE(x) (((x) / 10L) % 10L)
#define NC_NOTHING      0L   // nichts angegeben (zw. 0.0 und dimsize - 1)
#define NC_MINMAX       1L   // min / max sind angegeben
#define NC_BASEPTS      2L   // Stuetzpunkte sind angegeben
// zusaetzliche Flags fuer NC_DECVAR
#define NC_INTTYPE(x) ((x) % 10L)
#define NC_CUTOFF       0L   // Kommastellen abschneiden
#define NC_ROUND        1L   // Kommastellen runden
#define NC_LININT       2L   // linear interpolieren
#define NC_MMTYPE(x) (((x) / 10000L) % 10L)
#define NC_DEFIF        0L   // min, wenn < min bzw. max, wenn > max
#define NC_UNDEFIF      1L   // undefiniert, wenn ausserhalb min / max

#pragma pack(1)
struct NormCalc {
  BOOL interpol;   // soll linear interpoliert werden ?
  float interval;  // Interpolationswert (zw. 0.0 und 1.0)
  int Index;       // Index in der Werte-Tabelle
  };
#pragma pack()

typedef NormCalc FAR *LPNORMCALC;

#pragma pack(1)
struct DefNormObj_param {
  WORD ParSize;
  // zusaetzliche Parameter Daten
  DWORD normobj;  // Ergebnisobjekt
  DWORD free[1];  // freie Parameter
  };
#pragma pack()

#pragma pack(1)
struct DefNormTab_param {
  WORD ParSize;
  // zusaetzliche Parameter Daten
  DWORD normtab;  // Ergebnisobjekt
  // free: Tabelle mit Normwerten
  };
#pragma pack()

#pragma pack(1)
struct GetNorm_param {
  WORD ParSize;
  // zusaetzliche Parameter Daten
  DWORD normval;  // Ergebniswert
  DWORD normobj;  // Normobjekt
  DWORD normtab;  // Normtabellenobjekt
  };
#pragma pack()


// Definitionen fuer GetGrowthVal_param.mode:
#define GGV_ABSOLUT   0
#define GGV_RELATIV   1
#define GGV_EXPABS    2
#define GGV_EXPREL    3

#pragma pack(1)
struct GetGrowthVal_param {
  WORD ParSize;
  // zusaetzliche Parameter Daten
  DWORD gres;   // vorhergesagter Wert
  DWORD gold;   // aktueller Wert
  DWORD onobj;  // Normobjekt fuer aktuelles Alter
  DWORD nnobj;  // Normobjekt fuer vorherzusagendes Alter
  DWORD ntab;   // Normtabellenobjekt
  DWORD rmode;   // siehe Konstanten
  // folgende Parameter gelten nur fuer mode == GGV_EXPONENT
  DWORD a;      // Referenz auf a     \      neue Abweichung = alte Abw. *
  DWORD t;      // Referenz auf t      |-->  1.0+(1.0-a)*(exp(-t/tau)-1.0)
  DWORD tau;    // Referenz auf tau   /
  };
#pragma pack()

