//
//  $Header:   P:/marille/clinicum/include/rev/mlist.hpv   1.1   02 Feb 1996 11:00:02   GERHOLD  $
//  $Log:   P:/marille/clinicum/include/rev/mlist.hpv  $
// 
//    Rev 1.1   02 Feb 1996 11:00:02   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.0   24 Jun 1994 18:24:20   HANNES
// Initial revision.
// 
//    Rev 1.0   28 May 1993 21:22:38   HANNES
// Initial revision.
//
//
#ifndef MLIST_INCLUDED
#define MAXINSELEKTION  20
#define MAXSELEKTION    5
#define MAXDSETCHARS    64
#define MAXDOCNAMECHARS 64
#define MAXROWS         8
struct MList_def {
  int AnzDSet;                // Anzahl Dokumente, die Zugeordnet werden muessen
  struct {                
    BOOL doSelect;            // Ist Selektion ueberhaupt erlaubt
    BOOL allowMulti;          // Multiselektion erlaubt
    char DocName[MAXDOCNAMECHARS];
    WORD RecType;             // Nur zur Zwischenspeicherung, wird nicht bearbeitet
    WORD FNr[MAXINSELEKTION]; // Fallnummern, die den Selektionen zugeordent sind, wird nicht bearbeitet
    int AnzDSet;
    char DSetName[MAXINSELEKTION][MAXDSETCHARS];  // Name des Datensatzes
    int AnzSelection;         // Anzahl der Selektionen (min. 1, wenn erlaubt)
    int Selektion[MAXSELEKTION];  // Selektionen des Dokumentes
    } d[MAXROWS];
  };
typedef MList_def FAR *LPMLIST;

DLLExport BOOL _export WINAPI ShowMultiList (HWND hWParent,LPMLIST Def);
#define MLIST_INCLUDED
#endif

