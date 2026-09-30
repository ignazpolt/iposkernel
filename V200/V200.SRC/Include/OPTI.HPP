///////////////////////////////////////////////
//  Deklarationen fuer Optimierungsfunktion  //
///////////////////////////////////////////////
// $Header:   P:/marille/clinicum/include/rev/opti.hpv   1.4   10 Apr 1997 11:46:12   Martin  $
// $Log:   P:/marille/clinicum/include/rev/opti.hpv  $
// 
//    Rev 1.4   10 Apr 1997 11:46:12   Martin
// 32-bit-isiert
// 
//    Rev 1.3   10 Jun 1996 10:15:34   GERHOLD
// pragma pack
// 
//    Rev 1.2   02 Feb 1996 11:00:58   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.1   20 Mar 1995 12:16:42   HANNES
// Konstantenhanling, RunNmbr
// 
//    Rev 1.0   24 Jun 1994 17:01:54   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.2   17 May 1994 10:56:58   MARTIN
// MultiDivideCont
// 
//    Rev 1.1   13 Apr 1994 20:58:34   MARTIN
// uMultiDivideCont
// 
//    Rev 1.0   18 May 1993 17:43:14   MARTIN
// Initial revision.
// 

#pragma pack(1)
struct Referenz {
  WORD R, I;
  };
#pragma pack()

#pragma pack(1)
struct var {
  WORD R, I;              // Referenz auf die Variable (muss help sein !)
  DWORD minstep, maxstep; // minimale und maximale Schrittweite
  };
#pragma pack()

#pragma pack(1)
struct uOptimize_param {
  WORD ParSize;
  // Parameter Daten
  DWORD InitProc;         // Offset der Initialisierungsprozedur
  DWORD ErrorProc;        // Offset der Fehlerberechnungsprozedur
  WORD ErrorR, ErrorI;    // Referenz auf Fehlervariable
  DWORD PostProc;         // Offset der Nachbearbeitungsprozedur
  DWORD numvars;          // Anzahl der Variablen
  // free: numvars * var + beliebig * Referenz
  };
#pragma pack()


// interne Struktur fuer Variablen (wahrend Optimierungsvorgang)

typedef struct optvar FAR *LPOPTVAR;

struct optvar {
  LPOPTVAR next;
  var v;              // Scriptparameter
  float value;        // Wert der Variablen
  float laststep;     // letzte Schrittweite
  };

#pragma pack(1)
struct uContDist_param {
  WORD ParSize;
  // Parameter Daten
  WORD distR, distI;    // Ergebnis: Distanz
  DWORD num_points;     // Anzahl der Testpunkte zur Berechnung
  WORD cnt1R, cnt1I;    // erste Kontur
  WORD cnt2R, cnt2I;    // zweite Kontur
  };

struct uMultiDivideCont_param {
  WORD ParSize;
  // Parameter Daten
  DWORD cnt;      // Kontur
  DWORD begpt;    // Anfangspunkt der Kontur
  DWORD mode;     // modus: 0 = mit linearer Interpolation
                  //        1 = jeweils naechsten Punkt nehmen
  DWORD pts[1];   // free: Ergebnis - Punkte
  };
#pragma pack()

