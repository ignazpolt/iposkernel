/*--------------------------------------------------------------**
**                                                              **
**              Basisklasse der Hash Tabellen                   **
**                                                              **
**--------------------------------------------------------------*/
// $Header:   P:/marille/clinicum/include/rev/hash.hpv   1.8   04 Feb 1996 18:35:40   HANNES  $
// $Log:   P:/marille/clinicum/include/rev/hash.hpv  $
// 
//    Rev 1.8   04 Feb 1996 18:35:40   HANNES
// 
//    Rev 1.7   04 Feb 1996 17:51:10   HANNES
// 
//    Rev 1.6   04 Feb 1996 16:44:14   HANNES
// 
//    Rev 1.5   04 Feb 1996 16:17:08   HANNES
// 
//    Rev 1.4   04 Feb 1996 15:45:20   gerhold
// einiges in DDSMEM gewandert
// 
//    Rev 1.3   02 Feb 1996 11:00:22   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.2   14 Sep 1995 22:35:46   HANNES
// 
//    Rev 1.1   20 Sep 1994 11:31:00   HANNES
// Verbessertes Handling von Void Keys
// 
//    Rev 1.0   24 Jun 1994 17:01:44   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.5   14 Feb 1994 17:57:50   HANNES
// IsHashEmpty exportiert
// 
//    Rev 1.4   04 Feb 1994 16:51:46   HANNES
// StoreHugeHash, GetHugeHash
// 
//    Rev 1.3   04 Jan 1994 17:09:42   HANNES
// Funktionen PushDataToHandle in alle Auspr„gungen exportiert
// 
//    Rev 1.2   02 Apr 1993 18:00:00   HANNES
// Speicherverwaltung
// 
//    Rev 1.1   08 Mar 1993 14:07:32   HANNES
// Segmentsplitting
// 
//    Rev 1.0   02 Dec 1992 15:57:44   HANNES
// Initial revision.

#ifndef HASH_INCLUDED
#define HASH_INCLUDED
union _rData {
  LPSTR strkey;
  LPVOID vkey;
  LONG lKey;
  WORD wKey;
  };
struct hash_entry {
  _rData key;                   // Schluessel
  hash_entry FAR *Next;         // Zeiger auf den naechsten hash - Eintrag
  LPVOID Data;                  // Zeiger auf die Daten
  WORD wDataSize;               // Groesse des Datenblockes
  };
typedef hash_entry FAR * LPhash_entry;

// Schluesseltypen
#define LONGKEY         1       
#define STRKEY          2       
#define WORDKEY         3
#define SPECIALKEY      4
#define VOIDKEY         5

class FAR hash {
 public :
  WORD hash_dimension;          // Groesse der Hash - Tabelle
  LPhash_entry Table;           // Tabell
  BYTE Type;                    // Schluesseltyp
  LPVOID SpcElement;            // Offset in ev. vorhandens Spezialelement

  /*------< Speicherverwaltung >------*/
  DLLExport LPVOID _export WINAPI operator new (size_t);
  DLLExport void _export WINAPI operator delete (void FAR *);
  /*------< Berechnung des Hash - Index >-----*/
  //    (Koennen fuer anspruchsvollere Anwendungen ueberladen, bzw.
  //      fuer weitere Schluesseltypen erweitert werden)
  WORD hash_index (char FAR *string) { WORD res ; for ( res = 0 ; *string ; string++) res += *string ; return res % hash_dimension ; }
  WORD hash_index (LONG ident) { return (WORD) (DWORD(ident) % DWORD (hash_dimension)) ; }
  WORD hash_indexw(WORD ident) { return ident % hash_dimension ; }
  WORD hash_indexv(LPVOID data,int size) { WORD res ; int i ; LPSTR h = LPSTR(data) ; for ( i = 0 , res = 0 ; i < size ; i++ ) res += *h++ ; return res % hash_dimension ; }
  /*------< Check, ob Daten gefunden wurden >-----*/
  BOOL compareKey  (LPSTR,LPhash_entry);
  BOOL compareKeyv  (LPVOID,LPhash_entry,int);
  BOOL compareKey  (LONG,LPhash_entry);
  BOOL compareKeyW (WORD,LPhash_entry);
  /*------< Verschiedene Hilfsfunktionen >------*/
  BOOL is_empty (hash_entry FAR *e) { return (e->Data == NULL) ; }
  LPVOID DataPtr (hash_entry FAR *e) { return e->Data ; }
  LPhash_entry NextEnt (hash_entry FAR *e) { return e->Next ; }
  void SetKey  (LPSTR key,hash_entry FAR *e) 
    { e->key.strkey = LPSTR (GetGlobMem (lstrlen(key)+1)); lstrcpy(e->key.strkey,key); }
  void SetKey  (LONG key,hash_entry FAR *e) { e->key.lKey = key; }
  void SetKeyW (WORD key,hash_entry FAR *e) { e->key.wKey = key; }
  void SetKeyv (LPVOID key,hash_entry FAR *e,WORD size) 
    { e->key.vkey = GetGlobMem (size); lmemcpy(e->key.vkey,key,size); }
  void StoreData (LPVOID d,int size,hash_entry FAR *e) 
    { e->Data = GetGlobMem (e->wDataSize = size) ; lmemcpy (e->Data,d,size) ; }
  LPhash_entry newent () 
    { return LPhash_entry (GetGlobMem (sizeof (hash_entry))) ; }
  /*------< Suchen von Daten >------*/
  DLLExport LPVOID _export WINAPI GetData (char FAR *);       // Resultat: Daten oder NULL
  DLLExport LPVOID _export WINAPI GetDatav (LPVOID,int);
  DLLExport LPVOID _export WINAPI GetData (LONG);
  DLLExport LPVOID _export WINAPI GetDataW (WORD);
  DLLExport void _export WINAPI ChangeDataW (WORD,void FAR *,int);
  /*------< Speichern von Daten >-------*/
  DLLExport BOOL _export WINAPI SetData  (char FAR *,void FAR *,int);   // Resultat:
  DLLExport BOOL _export WINAPI SetDatav (LPVOID,void FAR *,int,int);         // FALSE ... Fehlversuch (Doppelter Schluessel)
  DLLExport BOOL _export WINAPI SetData  (LONG,void FAR *,int);         // FALSE ... Fehlversuch (Doppelter Schluessel)
  DLLExport BOOL _export WINAPI SetDataW (WORD,void FAR *,int);         // FALSE ... Fehlversuch (Doppelter Schluessel)
  /*------< Loeschen von Daten >--------*/
  DLLExport BOOL _export WINAPI DelData (char FAR *);
  DLLExport BOOL _export WINAPI DelDatav (LPVOID key,int size);
  DLLExport BOOL _export WINAPI DelData (LONG);
  DLLExport BOOL _export WINAPI DelDataW (WORD);
  /*------< Spezialelement >--------*/
  LPVOID GetSpcEle () { return SpcElement; }
  void InitializeSpcEle (WORD);
  /*------< Konstruktor, Destruktor >--------*/
  DLLExport _export WINAPI hash (WORD,WORD,GLOBALHANDLE hGm = NULL);  
                                        // Aufbau einer Leertabelle 
                                        // Angabe der Hashdimension und des Schluesseltyps
                                        // Lesen der Daten aus hGm
                                        // (hGm == NULL) -> Leertabelle
  virtual DLLExport _export WINAPI ~hash ();                     // Freigabe aller Daten
  /*------< Aufbau bzw. Abbau von Daten >------*/
  DLLExport void _export WINAPI GetHash (GLOBALHANDLE);          // Lesen der Daten aus dem Datenblock
  DLLExport void _export WINAPI GetHugeHash (GLOBALHANDLE);
  DLLExport GLOBALHANDLE _export WINAPI StoreHash (void);        // Abspeichern aller Daten in einen
                                        // Block, Resultat: Die Ganze Hashtabelle, 1. Word des globalen Buffers
                                        // ist die Groesse des Blockes
  DLLExport GLOBALHANDLE _export WINAPI StoreHugeHash (void);
  DLLExport BOOL _export WINAPI IsHashEmpty (void);

  /*------< Analyse / Statistik >------*/
  void GetHashInfo (int FAR *,float FAR *,float FAR *,int FAR *,int FAR *);
  };

// Eine etwas abgeaenderte Hash - Tabelle:
// Datenelemente mit gl. Schluessel werden in Listen gehalten
typedef void (* HashTrFunction) (LPVOID,LPVOID);
struct hashlist_entry {
  hashlist_entry FAR *Next;  // Zeiger auf die Daten
  WORD Size;                 // Groesse des Datenblocks
  };
typedef hashlist_entry FAR *LPhashlist_entry;

class hashlist : public hash {
  hashlist (WORD dim,WORD typ) : hash (dim,typ,NULL) { }
  BOOL SetData (LPSTR,LPVOID,int);          // Resultat pr. immer TRUE
  BOOL SetData (LONG,LPVOID,int);           // Resultat pr. immer TRUE
  LPhashlist_entry NextEle (LPhashlist_entry e) 
    { return e->Next ; } 
  void TrEle (LPSTR,HashTrFunction,LPVOID);   // Alle Elemente mit gl. Schluessel
                                              // abgehen
  void TrEle (LONG,HashTrFunction,LPVOID);
  void DelList (LPhash_entry);                // Loeschen der ganzen Liste
  BOOL DelData (LPSTR);
  BOOL DelData (LONG);
  };

/* 
** Format der Daten, die mit StoreHash gespeichert werden, bzw die mit
** mit GetHash gelesen werden koennen
** 1. WORD: GesamtGroesse des Buffers
** 2. WORD: Anzahl der Eintraege
**
** Danach kommen alle Eintraege nach folgendem Schema
**      Schluessel (muss mit dem Typ uebereinstimmen -> Schluesselgroesse
**                  ist bekannt !, bei Strings mit '\0' abgeschlossen)
**      Datengroesse (WORD)
**      Daten
**
** Bei GetHash kann auch in eine bereits existierende Tabelle eingelesen 
** werden. Wichtig ist nur, dass der Schluesseltyp, der bei der Erzeugung
** angegeben wurde, mit dem Schluesseltyp in dem Block uebereinstimmt.
*/

DLLExport GLOBALHANDLE _export WINAPI InitializeHandleForPush (void);
DLLExport void _export WINAPI PushDataToHandle (LPSTR str,GLOBALHANDLE FAR *res);
DLLExport void _export WINAPI PushDataToHandle (LPVOID data,int size,GLOBALHANDLE FAR *res);
DLLExport void _export WINAPI PushDataToHandle (WORD Ident,LPVOID data,int size,GLOBALHANDLE FAR *res);
DLLExport void _export WINAPI PushDataToHugeHandle (DWORD FAR *ActSize,LPVOID data,int size,GLOBALHANDLE FAR *res);

#endif
