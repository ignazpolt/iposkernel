////////////////////////////////////////////////////////////
//  Datenbank zur Dokumentenverwaltung
////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/include/rev/dlist.hpv   1.1   02 Feb 1996 11:00:20   GERHOLD  $
//  $Log:   P:/marille/clinicum/include/rev/dlist.hpv  $
// 
//    Rev 1.1   02 Feb 1996 11:00:20   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.0   24 Jun 1994 17:01:14   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.4   09 Dec 1993 15:05:30   HANNES
// Direktes Include der Pascal Files
// 
//    Rev 1.3   29 Nov 1993 08:40:20   HANNES
// Loeshcen eines Eintrages
// 
//    Rev 1.2   15 Nov 1993 14:03:16   HANNES
// Loeschen eines Eintrages
// 
//    Rev 1.1   22 Sep 1993 09:22:40   HANNES
// Version nach St. Poelten
// 
//    Rev 1.0   05 Sep 1993 22:09:46   HANNES
// Initial revision.
//
struct GEP_LfndNmbrs {
  WORD AnzRecs;
  LONG LFNdr[1];
  };

DLLExport void _export WINAPI ReleaseDFallNummer (WORD FallNummer);
DLLExport GLOBALHANDLE _export WINAPI DList_First (t_PatientenNummer FAR *pat,LONG FAR *lplfnr,WORD FAR *FallNummer);
DLLExport GLOBALHANDLE _export WINAPI DList_Last (t_PatientenNummer FAR *pat,LONG FAR *lplfnr,WORD FAR *FallNummer,GLOBALHANDLE FAR *sList);
DLLExport GLOBALHANDLE _export WINAPI DList_Next (t_PatientenNummer FAR *pat,LONG FAR *lplfnr,WORD FAR *FallNummer);
DLLExport GLOBALHANDLE _export WINAPI DList_Prev (t_PatientenNummer FAR *pat,LONG FAR *lplfnr,WORD FAR *FallNummer);
DLLExport GLOBALHANDLE _export WINAPI GetDListRec (
          WORD FAR *FallNummer,       // FallNummer der Beschreibung
          LPSTR DocName,              // Dokumentenname
          t_PatientenNummer FAR *pat, // Patient
          WORD RecType,               // Datensatz des Dokumentes, zu dem Eine
                                      // beschreibung gesucht werden soll
          WORD rFallNummer            // FallNummer des Datensatzes
                                            );
DLLExport void _export WINAPI PutDListRec (WORD FallNummer,GLOBALHANDLE hGmem);
DLLExport void _export WINAPI CloseDList ();
DLLExport BOOL _export WINAPI DList_Get (LONG FAR *Lfndr,WORD FNr);
DLLExport GLOBALHANDLE _export WINAPI DList_Eq (LONG lplfnr,WORD FAR *FallNummer);
DLLExport BOOL _export WINAPI DelDListRec (WORD FallNummer);
DLLExport void _export WINAPI DelOtherDListRecs (t_PatientenNummer FAR *pat,WORD rFallNummer,WORD RecType);
DLLExport void _export WINAPI DelAllDListRecs (t_PatientenNummer FAR *pat);

