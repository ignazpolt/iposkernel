///////////////////////////////////////////////////////////////
//  Arbeiten mit Datensaetzen in der Marille
///////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/include/rev/dbrecord.hpv   1.74   07 Jun 2000 10:22:58   Wolfgang  $
//  $Log:   P:/marille/clinicum/include/rev/dbrecord.hpv  $
// 
//    Rev 1.74   07 Jun 2000 10:22:58   Wolfgang
// 1.) DBOP_PARSE neu.
// 2.) ParseRecBuffer neu.
// 
//    Rev 1.73   26 Apr 2000 00:49:38   Hannes
// AnzahlVerwendetMitParameter
// 
//    Rev 1.72   18 Nov 1999 18:40:34   Hannes
// FreeAllJoins
// 
//    Rev 1.71   20 Oct 1999 07:49:28   Hannes
// 
//    Rev 1.70   12 May 1999 17:16:12   Wolfgang
// 1.) CompareEqual hat neuen Parameter segsFound.
// 2.) Neue Funktion CheckSegments.
// 
//    Rev 1.69   03 May 1999 15:56:52   Wolfgang
// 1.) FindRecord mit TableRefs und optionalem Mode Parameter.
// 3.) IsHashed mit optionalen Parametern fuer Rueckgabe der Hashtabelle.
// 4.) Neue Funktion CompareEqual.
// 
//    Rev 1.68   16 Apr 1999 22:30:58   Hannes
// RecRoot - Speicherverwaltung umgebaut
// 
//    Rev 1.67   31 Mar 1999 08:12:38   Hannes
// Update (DBRecord ..) exportiert
// 
//    Rev 1.66   17 Feb 1999 21:00:48   Hannes
// Verbesserungen an Moveconnection
// 
//    Rev 1.65   15 Feb 1999 20:03:52   Hannes
// FreeOutParam
// 
//    Rev 1.64   05 Feb 1999 21:38:00   Martin
// verbessertes Errorhandling
// 
//    Rev 1.63   29 Jan 1999 09:54:58   Hannes
// Prototyp AddRec*
// 
//    Rev 1.62   28 Jan 1999 12:20:46   Hannes
// Erweiterte SQL - Syntax
// 
//    Rev 1.61   11 Jan 1999 08:19:04   Hannes
// Austausch Records im Aufrufer-> Kontextaustauch in Kindern
// 
//    Rev 1.60   16 May 1998 14:11:52   Martin
// SortParam ...
// 
//    Rev 1.59   23 Feb 1998 20:00:46   Hannes
// SetParam mit NULL - Wert
// 
//    Rev 1.58   10 Feb 1998 18:26:26   Hannes
// Verbessertes Nextsamehandling
// 
//    Rev 1.57   16 Dec 1997 16:07:44   Hannes
// 
//    Rev 1.56   01 Dec 1997 19:38:34   Hannes
// Diverse Anpassungen
// 
//    Rev 1.55   21 Nov 1997 10:38:34   Hannes
// Verbesserung des For - STatements
// 
//    Rev 1.54   19 Nov 1997 18:45:20   Hannes
// Restool 32 Bit umstellung
// 
//    Rev 1.53   05 Aug 1997 22:41:20   Hannes
// IsEleHashed
// 
//    Rev 1.52   22 Jul 1997 21:07:58   Hannes
// 
//    Rev 1.51   18 Jul 1997 08:06:58   Hannes
// 
//    Rev 1.50   14 Jul 1997 07:52:24   Hannes
// Pragma pack um VarElem herum
// 
//    Rev 1.49   11 Jul 1997 10:14:14   Hannes
// 
//    Rev 1.48   08 Jul 1997 12:00:00   Hannes
// 
//    Rev 1.47   09 Jun 1997 13:10:24   Hannes
// 
//    Rev 1.46   19 Feb 1997 12:01:28   Hannes
// Scriptfunktionen -> Zylische liste mit Ableitungen
// 
//    Rev 1.45   17 Dec 1996 11:52:28   HANNES
// ENDOFUPDATE, STARTOFUPDATE
// 
//    Rev 1.44   12 Dec 1996 12:20:12   HANNES
// Alte Parameter fuer den Refresh der Joins
// 
//    Rev 1.43   26 Nov 1996 08:07:50   HANNES
// Automatischer Update
// 
//    Rev 1.42   08 Nov 1996 13:29:32   HANNES
// Replikator
// 
//    Rev 1.41   31 Oct 1996 16:08:40   HANNES
// Connection auf Liste: Eigene OwnerID
// 
//    Rev 1.40   28 Oct 1996 08:43:00   HANNES
// OwnerID,DocumentID
// 
//    Rev 1.39   12 Sep 1996 23:29:56   HANNES
// Segmentierte Indizess auf Listen
// 
//    Rev 1.38   03 Sep 1996 10:04:08   HANNES
// ANZRECSPRERLINE verkleinert
// 
//    Rev 1.37   18 May 1996 21:01:44   HANNES
// BlobDsc
// 
//    Rev 1.36   27 Mar 1996 18:04:26   MARTIN
// ParamBlock.AnzPars
// 
//    Rev 1.35   04 Feb 1996 15:45:18   gerhold
// einiges in DDSMEM gewandert
// 
//    Rev 1.34   04 Feb 1996 14:25:14   HANNES
// 
//    Rev 1.33   02 Feb 1996 11:01:00   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.31   20 Nov 1995 11:44:04   HANNES
// GetAnzCachedRecords
// 
//    Rev 1.30   25 Oct 1995 13:53:22   HANNES
// Aenderungen Hannes
// 
//    Rev 1.29   14 Sep 1995 14:31:48   MARTIN
// CB_PARAM von 32 auf 64 erhoeht
// 
//    Rev 1.28   24 Aug 1995 00:12:18   HANNES
// Debuggerverbesserun
// 
//    Rev 1.27   14 Aug 1995 08:21:30   HANNES
// FillIn exportiert, GetVarElem
// 
//    Rev 1.26   10 Aug 1995 09:18:20   HANNES
// JoinRecords ... alte Primaerschluessel fuers losloesen aufbewahrt
// 
//    Rev 1.25   14 Jul 1995 16:53:48   HANNES
// Horizontale Fileteilung
// 
//    Rev 1.24   11 Jul 1995 12:36:46   HANNES
// GetAsyncFifoPtr beschleunigt
// 
//    Rev 1.23   02 Jul 1995 18:26:54   HANNES
// SortList in beide Richtungen
// 
//    Rev 1.22   09 Jun 1995 00:31:16   HANNES
// VarElem::Property
// Hashtabelle fuer Indizierte Elemente in DBRecord
// 
//    Rev 1.21   08 May 1995 18:08:20   HANNES
// 
//    Rev 1.20   24 Apr 1995 12:52:02   HANNES
// 
//    Rev 1.19   21 Mar 1995 16:21:28   HANNES
// 
//    Rev 1.18   20 Mar 1995 12:16:04   HANNES
// Konstantenhanling, RunNmbr
// 
//    Rev 1.17   03 Mar 1995 18:12:06   HANNES
// 
//    Rev 1.16   24 Feb 1995 11:16:38   HANNES
//  
// 
//    Rev 1.15   16 Feb 1995 13:02:12   HANNES
//  
// 
//    Rev 1.14   29 Jan 1995 11:46:56   HANNES
// 
//    Rev 1.13   13 Jan 1995 16:56:12   HANNES
// Variablen-Breakpoints
// 
//    Rev 1.12   09 Jan 1995 12:11:40   HANNES
// Debugger eingebaut
// 
//    Rev 1.11   07 Dec 1994 18:29:44   HANNES
// 
//    Rev 1.10   15 Nov 1994 10:58:14   HANNES
// DBRecord::Update
// 
//    Rev 1.9   07 Nov 1994 11:45:00   HANNES
// Spezifisches Loeschen von Kommandos
// 
//    Rev 1.8   31 Oct 1994 10:42:48   hannes
// Initialize
// 
//    Rev 1.7   19 Oct 1994 22:35:32   hannes
// 
//    Rev 1.6   03 Sep 1994 19:49:28   HANNES
// FindRecord ... Um Probleme im Zusammenhang mit ungueltigem Primaerschluessel
// und ReUse zu vermeiden...
// 
//    Rev 1.5   10 Aug 1994 12:08:30   HANNES
// Ueberpruefung im DeleteRecRoot ... -> Friend function
// 
//    Rev 1.4   05 Aug 1994 17:15:56   HANNES
// DBList von DBRecordList abgeleitet
// 
//    Rev 1.3   17 Jul 1994 14:34:54   HANNES
// Umorganisieren der Primaerschluesselverwaltung
// 
//    Rev 1.2   13 Jul 1994 21:18:10   HANNES
// Verwaltung der Extradaten auch im Updatezweig, um Mehrfachverwendung von Proz
// Prozeduren zu erlauben
// 
//    Rev 1.1   12 Jul 1994 18:30:22   HANNES
// AddRecAtTail exportiert
// 
//    Rev 1.0   24 Jun 1994 17:01:08   HANNES
// Neuuebernahme clinicum
//


/*--------< Definition eines Requestbuffers >-----------*/
#define CB_SELECTIONNAME  64
#define CB_TABLEDEF       16
#define CB_PARAM          64
#define CB_SORTPARAM      8
#define MANZSEGS          4
struct FAR DBRequest;
typedef DBRequest FAR *LPDBREQUEST;
struct FAR OldParams {
  LPVOID Param[CB_TABLEDEF][MANZSEGS];  // Werte, die zuletzt fuer den Join verwendet wurden
  };
typedef OldParams FAR *LPOLDPARAM;
struct FAR ForeignDescription {
#ifdef UEBERLEGT
  WORD TableID;       // Tabelle, aus der der Foreignkey genommen wird
#endif
  WORD Type;          // Typ des Foreign - Request (siehe CLKJ_...)
  WORD VarID[MANZSEGS];      // Variable, die als Foreignkey fungiert

  LPWORD VarIndex;    // Zuordnung Request zu Variable
  LPDBREQUEST freq;   // Request fuer den Aufruf
  };

#define DBCALLTYPE_EXTENDED         0   // Aufruf einer gespeicherten Prozedur
#define DBCALLTYPE_STANDARDGET      1   // Standard - Get Statement mit Tabelle als Parameter
#define DBCALLTYPE_GETLIST          2   // Liste (inkl. OrderStatement)
#define DBCALLTYPE_STANDARDUPDATE   3   // Standard - Update
#define DBCALLTYPE_STANDARDDELETE   4   // Standardmaessiges Loeschen (kann auch mehrere Datensaetze auf einmal loeschen)
#define DBCALLTYPE_STANDARDINSERT   5   // Einfuegen (Autoinc - Keys werden auf 0 gesetzt, Datensatz kommt wieder zuruek)
#define DBCALLTYPE_EXECUTE          6   // Ausfuehren eines SQL - Statements, ohne Rueckgabe
#define DBCALLTYPE_EXECUTESINGLE    7   // Ausfuehren eines SQL - Statements, Der erste Parameter dient als Resultat (nur einfache Werte)
#define DBCALLTYPE_CLOSEALL         8   // Alle Files schliessen
#define DBCALLTYPE_TEST             1000   // Testen der Tabelle
#define DBCALLTYPE_CREATE           1001

class FAR DBRecord;
typedef DBRecord FAR *LPDBRECORD;
struct OutParam {
  WORD parNum;
  OutParam FAR *Next;
  LPVOID Data;
  };
struct FAR DBRequest {
  DWORD StructSize;
  DWORD ProgVersion;
  LPSTR SelectionName;
  LPSTR OrderStatement;
  LPSTR AlternateName;
  LPOLDPARAM oldP;
  DWORD DocID;
  DWORD AnzTables;
  TableRef tRef;
  WORD  Type;       // Siehe DBCALLTYPE_...
  LPTABLEDEF TableDef[CB_TABLEDEF];
  BOOL       doLock  [CB_TABLEDEF];
  DWORD AnzParam;
  LPVOID Param[CB_PARAM];
  WORD   ParamType[CB_PARAM];
  DWORD AnzSortParam;
  LPVOID SortParam[CB_SORTPARAM];
  WORD   SortParamType[CB_SORTPARAM];
  BOOL Transactional;
  ForeignDescription fdsc[CB_TABLEDEF];
  BOOL foreignDone;
  OutParam FAR *op;
  DLLExport LPREQELEM _export WINAPI BuildForeign ();
  DLLExport void _export WINAPI ClearForeign ();
  DLLExport void _export WINAPI SaveOldParams (LPDBRECORD rec,WORD TablePart,LPOLDPARAM op);
  DLLExport LPOLDPARAM _export WINAPI SaveOldParams (LPDBRECORD rec);

  LONG AnzElems;
  LPREQELEM elem;

  BOOL StraightForward;

  LPVOID ErrorCBP;

  DLLExport void _export WINAPI AddTableDef (LPTABLEDEF td,BOOL doLock = FALSE);
  DLLExport void _export WINAPI AddTableDef (WORD TableID,WORD Version,BOOL doLock = FALSE);
  DLLExport void _export WINAPI SetReqElem  (int Num,WORD TableID,WORD VarID);
  DLLExport void _export WINAPI SetReqElemDirect (int Num,WORD TableNumber,WORD VarID);
  DLLExport void _export WINAPI FreeTableDefs ();
  DLLExport void _export WINAPI SetNewDimension (int AnzElems);

  BOOL CheckSortVals ();

  DLLHANDLE GetDLLHandle ()
    { return TableDef[0]->GetDLLHandle() ; }
  void SetOrderStatement (LPSTR stmt)
    {
    if (OrderStatement != NULL) FreeGlobMem (OrderStatement);
    OrderStatement = LPSTR(GetGlobMem (lstrlen(stmt)+1)) ;
    lstrcpy (OrderStatement,stmt);
    }
  void SetParam (WORD parNo,LPVOID data,WORD dSize)
    { 
    if (data != NULL) {
      if (parNo > AnzParam) AnzParam = parNo ;
      lmemcpy (Param[parNo] = GetGlobMem (dSize),data,dSize); 
      }
    }
  void SetOutParam (WORD parNo,LPVOID data,WORD dSize)
    { 
    for (OutParam FAR *h = op ; h != NULL ; h = h->Next) {
      if (h->parNum == parNo) {
        if (h->Data != NULL) FreeGlobMem (h->Data) , h->Data = NULL;
        if (data != NULL)
          h->Data = GetGlobMem (dSize) , lmemcpy (h->Data,data,dSize);
        return ;
        }
      }
    h = (OutParam FAR *) GetGlobMem (sizeof(*h));
    h->parNum = parNo;
    if (data != NULL)
      h->Data = GetGlobMem (dSize) , lmemcpy (h->Data,data,dSize);
    h->Next = op;
    op = h;
    }
  void SetParamType (WORD parNo,WORD Type)
    {
    ParamType[parNo] = Type ;
    }
  void SetSortParam (WORD parNo,LPVOID data,WORD dSize)
    {
    if (data != NULL) {
      if (parNo > AnzSortParam) AnzSortParam = parNo ;
      lmemcpy (SortParam[parNo] = GetGlobMem (dSize),data,dSize); 
      }
    }
  void SetSortParamType (WORD parNo,WORD Type)
    {
    SortParamType[parNo] = Type ;
    }
  void ClearParams ()
    {
    for (int i = 0 ; i < CB_PARAM ; i++) if (Param[i] != NULL) FreeGlobMem(Param[i]) , Param[i] = NULL ;
    for (i = 0 ; i < CB_SORTPARAM ; i++) if (SortParam[i] != NULL) FreeGlobMem(SortParam[i]) , SortParam[i] = NULL ;
    }
  void ClearOutParam ()
    {
    for ( ; op != NULL ; ) {
      OutParam FAR *h = op;
      op = h->Next;
      if (h->Data != NULL) FreeGlobMem (h->Data);
      FreeGlobMem (h);
      }
    }
  void SetSelection (LPSTR n)
    {
    if (SelectionName != NULL) FreeGlobMem (SelectionName);
    SelectionName = LPSTR(GetGlobMem (lstrlen(n)+1));
    lstrcpy (SelectionName,n);
    }

  DLLExport WORD _export WINAPI GetVarNumber (WORD TableID,WORD VarID,BOOL FAR *done = NULL);
  DLLExport WORD _export WINAPI GetVarNumberByNum (WORD TableNr,WORD VarID,BOOL FAR *done = NULL);
        // Suchen eines Eintrages fuer die entsprechende Tabelle und 
        // Variable (return: Nummer des Eintrage, done ... Erfolgsmeldung)
  DLLExport LPREQELEM _export WINAPI GetElemsOf (WORD TableID);
  DLLExport void _export WINAPI SetReqElemExtended (int Num,WORD TableID,WORD Version,WORD VarID,BOOL doLock);

  DLLExport BOOL _export WINAPI IsUpdateDone (LPDBRECORD rec,WORD TablePart,LPOLDPARAM oldP);
  DLLExport void _export WINAPI CheckPrimKeySegs ();

  void SetTableID(WORD Id,WORD Version)
    { tRef.TableNr  = Id ; tRef.Version = Version ; }
  WORD GetTableID()
    { return tRef.TableNr ; }
  WORD GetVersion()
    { return tRef.Version ; }
  };

DLLExport LPDBREQUEST _export WINAPI InitializeRequest (LPSTR SelectionName,int AnzElems,int Type,DWORD DocID);
DLLExport void _export WINAPI FreeRequest (LPDBREQUEST req);
DLLExport void _export WINAPI FreeOldParam (LPOLDPARAM oldP);

#define DBOP_RESET         0
#define DBOP_GETFIRST      1
#define DBOP_GETNEXT       2
#define DBOP_GETLAST       3
#define DBOP_GETPREV       4
#define DBOP_DELETE        5
#define DBOP_INSERT        6
#define DBOP_UPDATE        7
#define DBOP_GET           8
#define DBOP_UNLOCK        9
#define DBOP_ENDOFCONVERSION  10
#define DBOP_STARTOFUPDATE    11
#define DBOP_ENDOFUPDATE      12
#define DBOP_PARSE        13


/*----< Definition eines Datensatzes im Speicher >----------*/
#define PRIMKEYSIZE     8

class FAR PrimKey {
 public :
  LPVOID Data;
  DLLExport BOOL _export WINAPI operator == (PrimKey FAR &b);
  DLLExport PrimKey & _export WINAPI operator = (PrimKey FAR &b);
  DLLExport BOOL _export WINAPI IsNullKey ();
  DLLExport void _export WINAPI SetKeyNull ();
  DLLExport void _export WINAPI PushKeySeg (LPVOID SegData,int SegSize);

  PrimKey ()
    { Data = NULL ; }
  ~PrimKey ()
    { if (Data != NULL) FreeGlobMem (Data) ; }
  LPVOID operator new (size_t size)
    { return GetGlobMem (size); }
  void operator delete (LPVOID obj)
    { FreeGlobMem (obj); }
  };
typedef PrimKey FAR *LPPRIMKEY;

//////////////////////////////////////////////////////////////////
//  Kommandosortierung
//////////////////////////////////////////////////////////////////
struct FAR cmdcount {
  WORD counter[1];
  int AnzCounter ()
    { 
    return (GetBlockSize(this) / sizeof(counter[0])) ; 
    }
  void Increment ()
    { 
    // counter[AnzCounter()-1] += 32 ; 
    counter[AnzCounter()-1] += 2 ; 
    }
  void IncrementSingle ()
    { 
    counter[AnzCounter()-1] ++ ; 
    }
  void DecrementSingle ()
    { 
    counter[AnzCounter()-1] -- ; 
    }
  DLLExport cmdcount FAR *_export WINAPI Copy ();
  };
typedef cmdcount FAR *LPCMDCOUNT;

DLLExport LPCMDCOUNT _export WINAPI GetCount(WORD DocumentNumber);
DLLExport LPCMDCOUNT _export WINAPI PushBlock(LPCMDCOUNT old,WORD initVal = 0);
DLLExport LPCMDCOUNT _export WINAPI PopBlock(LPCMDCOUNT old);

DLLExport int _export WINAPI Compare (LPCMDCOUNT c1,LPCMDCOUNT c2);

#define MAXRUNS 5
struct ctrlist {
  LPCMDCOUNT c;
  };
typedef ctrlist FAR *LPCTRLIST;

void SetCounter (LPCTRLIST h,LPCMDCOUNT x);
void RemoveCount (LPCTRLIST h);
LPCMDCOUNT GetCounter (LPCTRLIST h);

///////////////////////////////////////////////////////////////
//  Kommandfifo - Verwaltung
///////////////////////////////////////////////////////////////
struct FAR VarElem;
typedef VarElem FAR *LPVARELEM;
struct FAR HistEle {
  LPVOID cmd;
  LPVARELEM FAR *fk;
  BOOL EleReferenced (LPVARELEM k);
  void CopyEntry (LPVARELEM k);
  void CopyEntry (HistEle FAR *h);
  void CopyEntry (HistEle FAR *h,LPVARELEM k);
  int AnzKeys () { return (fk != NULL) ? GetBlockSize (fk) / sizeof (*fk) : 0 ; }
  };

#define EXTRATYPE_NONE    0
#define EXTRATYPE_LIST    1
#define EXTRATYPE_REC     2
struct FAR CmdFifoEntry {
  CmdFifoEntry FAR *Next;
  CmdFifoEntry FAR *Prev;
  DWORD DocumentID;
  WORD mode;
  LPVOID Cmd;
  int ExtraType;
  LPVOID ExtraData;
  LPCMDCOUNT counter;
  HistEle History[1];        // Geschichte des Aufrufes
  int HistCount ()
    { return (GetBlockSize (this) - sizeof(*this)) / sizeof(HistEle) + 1 ; }
  };
typedef struct CmdFifoEntry FAR *LPCMDFIFO;

typedef void (WINAPI * EXTCHKMSG) (LPMSG lpmsg);
DLLExport void _export WINAPI SetupQueue (HWND hWnd,EXTCHKMSG ext);
class FAR fifo {
 private :
  LPCMDFIFO GetCmdFifo ();
  void Insert (LPCMDFIFO);

 public :
  LPVOID cHash;
  LPCMDFIFO head,tail,act;
  
  DLLExport void _export WINAPI PutCommandFifo (DWORD DocId,WORD mode,LPVOID Cmd,LPVOID MyCmd,LPVARELEM k,LPCMDCOUNT cnt,int ExtraType = EXTRATYPE_NONE,LPVOID ExtraData = NULL,int ExtraSize = 0);
  DLLExport LPCMDFIFO _export WINAPI GetCommandFifo ();
  DLLExport BOOL _export WINAPI IsCommandFifoEmpty (void);
  DLLExport void _export WINAPI DelCommandFifoEntry (DWORD DocId,LPVOID Cmd); 
  DLLExport void _export WINAPI DelCommandFifoEntry (DWORD DocId,LPVOID Cmd,int eType,LPVOID eData);
  DLLExport void _export WINAPI DelDocumentEntrys (DWORD DocID);
  DLLExport void _export WINAPI FreeFifoEntry (LPCMDFIFO h);

  BOOL IsUpdateFrom (LPVARELEM ele);
  int UpdateEleCount ();
  LPCMDFIFO GetCmdFifoByNumber (int Nmbr);  // -1 um das Aktuelle Element zu
                                            // erfragen
  };

DLLExport BOOL _export WINAPI IsUpdateFrom (LPVARELEM ele);
DLLExport int _export WINAPI UpdateEleCount ();
DLLExport void _export WINAPI NoFurtherUpdates(DWORD DocumentID);
DLLExport void _export WINAPI DocumentIsDestroyed(DWORD DocumentID);
DLLExport LPVOID _export WINAPI GetUpdateExtraData (int FAR *ExtraType = NULL);

#ifdef DDL
DLLExport fifo FAR *_export WINAPI GetAsync_cmdfifo();
DLLExport fifo FAR *_export WINAPI GetSync_cmdfifo();
#else
#ifdef DDS_MAIN
fifo FAR *AsyncFifoPtr;
DLLExport fifo FAR *_export WINAPI GetAsync_cmdfifo();
DLLExport fifo FAR *_export WINAPI GetSync_cmdfifo();
#else
extern fifo FAR *AsyncFifoPtr;
DLLExport fifo FAR *_export WINAPI GetAsync_cmdfifo();
DLLExport fifo FAR *_export WINAPI GetSync_cmdfifo();
#endif
#endif

struct FAR UpdateElem ;
typedef UpdateElem FAR *LPUPDATEELEM;
struct FAR UpdateElem {
  LPUPDATEELEM Next;
  DWORD        OwnerID;
  DWORD        DocumentID;
  LPVOID       Cmd;
  int          UpdateExtraType;
  LPVOID       UpdateExtraData;
  LPCMDCOUNT   c;

  BOOL CheckExtaType (int Type,LPVOID ExtraData,int DataSize,LPVOID recData);
  };

#define DBR_TYPE_FULL       0
#define DBR_TYPE_REDUCED    1

#define MODE_UPDATE   0x0004
struct FAR BlobDesc {
  DWORD Size;
  GLOBALHANDLE hGmem ;

  void FreeHandle ()
    {
    if (hGmem)
      GlobalFree (hGmem);
    }
  };
typedef BlobDesc FAR *LPBLOBDESC ;
#define VEP_STATIC   1
#define VEP_PARAM    2
#pragma pack(1)
struct FAR VarElem {
  LPVOID    data;      // Zeiger auf die eigentlichen Daten
  LPVARELEM NextSame;  // Herstellung einer Zyklischen Liste aller
                       // gleichen Elemente, auch wenn sie in verschiedenen
                       // Records vorkommen
  LPUPDATEELEM UpdateList;// Liste der Updates, die im Falle des Set bzw.
                          // Del auszufuehern sind
  DWORD Erzeuger;
  BYTE UpdateDone;        // Ist ein Update gemacht worden
  BYTE Property;          // Ist das Element statisch (keine Updates)
  short AnzahlVerwendetMitParameter;   // Anzahl der Verwendung in GetParameterWithCode
  void UpdateMe(DWORD DocumentID);
  inline BOOL isStatic ()
    {
    return (Property & VEP_STATIC) ;
    }
  inline BOOL isParam ()
    {
    return (Property & VEP_PARAM) ;
    }

  inline LPVOID Get()
    { 
    return data ; 
    }
  inline LPTSTR GetStr()
    {
#ifdef UNICODE
    if (data != NULL) {
      LPCPLSTR str = (LPCPLSTR)data;
      if (WITHOUT_BOM(str)) {
        //LPCPLSTR newStr = AnsiToBomStr((LPASTR)str);
        int len = GetBlockSize32 (str);  //es koennte sich um eine \0 separierte Liste handeln
        LPTSTR newStr = (LPTSTR)GetGlobMem((len + 1) * sizeof(TCHAR));
        newStr[0] = BOM;
        MultiByteToWideChar(CP_THREAD_ACP, 0, (LPASTR)str, len, newStr + 1, len);
        //if (isIndexed()) BeforeUpdate();
        FreeGlobMem(data) ;
        data = newStr;
        //if (isIndexed()) AfterUpdate();
        }
      return LPTSTR(data) + 1;
      }
    else
      return NULL;
#else
    if (data != NULL) {
      LPCPLSTR str = (LPCPLSTR)data;
      if (WITH_BOM(str)) {
        int len = GetBlockSize32 (str)/ sizeof(WCHAR) - 1;
        LPASTR newStr = (LPASTR)GetGlobMem(len);
        WideCharToMultiByte( CP_THREAD_ACP, 0, ((LPWSTR)str) + 1, len, newStr, len, NULL, NULL);
        //if (isIndexed()) BeforeUpdate();
        FreeGlobMem(data) ;
        data = newStr;
        //if (isIndexed()) AfterUpdate();
        }
      return LPTSTR(data);
      }
    else
      return NULL;
#endif
    }
  inline void Del()
    { 
    if (data != NULL) FreeGlobMem(data) , data = NULL ; 
    UpdateDone = TRUE ;
    }
  inline void Set(LPVOID d,WORD Size)
    { 
    if (data != NULL) {
      if (GetBlockSize(data) != Size) {
        FreeGlobMem(data) ; 
        data = GetGlobMem(Size) ; 
        }
      }
    else
      data = GetGlobMem(Size) ; 
    lmemcpy (data,d,Size); 
    UpdateDone = TRUE ;
    }
  inline void Initialize(LPVOID d,WORD Size)
    { 
    if (data != NULL) FreeGlobMem(data) ; 
    data = GetGlobMem(Size) ; 
    lmemcpy (data,d,Size); 
    }
  inline BOOL IsUpdateDone ()
    {
    return UpdateDone ;
    }
  inline void ResetUpdateFlag ()
    {
    UpdateDone = FALSE;
    }
  DLLExport void _export WINAPI Update(LPVOID MyCmd,LPVOID recData,int ExtraType,LPVOID UpdateExtraData,int ExtraDataSize);
  DLLExport void _export WINAPI SetConnection (DWORD OwnerID,DWORD DocumentID,LPVOID Cmd,LPCMDCOUNT c,int ExtraType = EXTRATYPE_NONE,LPVOID UpdateExtraData = NULL,int ExtraDataSize = 0);
  DLLExport void _export WINAPI ClearConnection (DWORD OwnerID,DWORD DocumentID,LPVOID Cmd,int ExtraType = EXTRATYPE_NONE,LPVOID UpdateExtraData = NULL,int ExtraDataSize = 0);
  DLLExport void _export WINAPI FreeMem();

  void MoveConnections (LPVARELEM n,DWORD DocumentID,DWORD OwnerID);
  DLLExport void _export WINAPI FillIn (LPVARELEM n);
  void DelConnections (DWORD DocID);
  };
#pragma pack()

struct FAR JoinRecList {
  LPDBRECORD rec;
  int TableInd;
  };
typedef JoinRecList FAR *LPJOINRECLIST;

struct FAR DebFifoInfo;
#define RECORDTYPE_DBNORMAL     0
#define RECORDTYPE_DBLOCAL      1
#define RECORDTYPE_DBHELP       2
#define RECORDTYPE_DBCONST      3
struct FAR DoWithList ;
typedef DoWithList FAR *LPWLIST;
struct FAR RecWithAnchore {
  LPWLIST w;
  RecWithAnchore FAR *Next;
  };
typedef struct RecWithAnchore FAR *LPWITHANCHORE;
class FAR DBRecord {
 protected :
  WORD Type;      // DBR_TYPE_...
  GLOBALHANDLE hGTbl;
  TableRef tRef;
  WORD AnzTables;
  LPTABLEDEF tbdef[CB_TABLEDEF];
  LPVARELEM  vartbl;
  PrimKey k;
  LPPRIMKEY kj[CB_TABLEDEF];
  LPREQELEM elem;

  void Initialize (LPTABLEDEF def);
  WORD AnzVars;

  LPDWORD OwnerID;

  BOOL islocked;
  BOOL doUpdate;
 public :
  LPDBRECORD NextInCycl;
  LPWITHANCHORE lpWithAnchore;
  BOOL isLocked()
    { return islocked ; }
  void setLocked()
    { islocked = TRUE ; }
  void AvoidUpdates ()
    { doUpdate = FALSE ; }
  void ClearPrimKey ()
    { k.SetKeyNull(); }
  LPPRIMKEY GetPrimKey ()
    { return &k ; }
  void SetPrimKey (LPPRIMKEY pk)
    { k = *pk ; }
  WORD GetAnzVars ()
    { return AnzVars ; }
  WORD GetType ()
    { return Type ; }
  LPTABLEDEF GetTableDef (WORD VarNr,WORD FAR *VarId)
    { 
    if (elem != NULL) {
      *VarId = elem[VarNr].VarID ; 
      return tbdef[elem[VarNr].TableNumber] ; 
      }
    else {
      *VarId = VarNr ;
      return tbdef[0];
      }
    }
  WORD GetTableNumber (WORD VarNr)
    {
    if (elem != NULL)
      return elem[VarNr].TableNumber ; 
    else
      return 0;
    }
  LPVARELEM GetVarElem(WORD VarId)
    {
    return &vartbl[VarId];
    }
  WORD GetVarNumber (int TableNumber,WORD VarID,BOOL FAR *done = NULL);
  WORD GetTableID()
    { return tRef.TableNr; }
  WORD GetVersion()
    { return tRef.Version; }
  void SetTableID(WORD Id,WORD Version)
    { tRef.TableNr = Id; tRef.Version = Version ; }
  void MoveConnections(DBRecord FAR *n,DWORD DocumentID,DWORD OwnerID);

  virtual void DoAllJoins ();
  virtual void FillIn (LPVARELEM v,int TableNr,WORD VarID);
  virtual void FreeJoins();
  virtual void FreeAllJoins();
  virtual void FreeJoins(DWORD eNummer);
  DLLExport void _export WINAPI CalcPrimKey (int TableNumber,LPPRIMKEY k);

  // Datenzugriffe
  DLLExport void _export WINAPI Set (WORD VarID,LPVOID data,WORD dataSize,LPVOID MyCmd = NULL,BOOL doUpdate = FALSE,int ExtraType = EXTRATYPE_NONE,LPVOID UpdateExtraData = NULL,int ExtraDataSize = 0);
  DLLExport void _export WINAPI Initialize (WORD VarID,LPVOID data,WORD dataSize);
  DLLExport void _export WINAPI Del (WORD VarID,LPVOID MyCmd = NULL,BOOL doUpdate = FALSE,int ExtraType = EXTRATYPE_NONE,LPVOID UpdateExtraData = NULL,int ExtraDataSize = 0);
  LPVOID Get (WORD VarID) 
    { 
    return vartbl[VarID].Get() ; 
    }
  LPTSTR GetStr (WORD VarID)
    {
    return vartbl[VarID].GetStr() ;
    }
  WORD GetDataType(WORD VarID)
    {
    WORD vint;
    LPTABLEDEF td = GetTableDef (VarID,&vint);
    return td->GetVarDef(vint)->mType ;
    }
  virtual DLLExport void _export WINAPI SetConnection (DWORD OwnerID,WORD VarID,DWORD DocID,LPVOID cmd,LPCMDCOUNT c,int UpdateExtraType = EXTRATYPE_NONE,LPVOID UpdateExtraData = NULL,int ExtraDataSize = 0);
  virtual DLLExport void _export WINAPI ClearConnection (DWORD OwnerID,WORD VarID,DWORD DocID,LPVOID cmd,int ExtraType = EXTRATYPE_NONE,LPVOID UpdateExtraData = NULL,int ExtraDataSize = 0);
  inline BOOL IsUpdateFromEle (WORD ID)
    {
    return IsUpdateFrom (&vartbl[ID]);
    }

  DLLExport void _export WINAPI Update(LPDBRECORD n);
  DLLExport void _export WINAPI Update(DWORD DocumentID);

  // Von wem wird der Record benoetigt
  DLLExport void _export WINAPI UseBy(DWORD OwnerId);
  DLLExport BOOL _export WINAPI IsUsedBy(DWORD Id);
  DLLExport void _export WINAPI ReleaseFrom(DWORD OwnerID);

  // Konstruktor, Destruktor
  DLLExport _export WINAPI DBRecord (WORD AnzVars);
  DLLExport _export WINAPI DBRecord (LPTABLEDEF d);
  DLLExport _export WINAPI DBRecord (LPDBREQUEST req);
  virtual DLLExport _export WINAPI ~DBRecord();
  WORD UseCount()
    { return GetBlockSize (OwnerID) / sizeof(DWORD) ; }
  DLLExport void _export WINAPI GetOutTxt (LPSTR res,WORD VarID);
  DLLExport int _export WINAPI GetVarSize (WORD VarNr);
  void DelConnections (DWORD DocID);

  virtual int GetRecordType ()
    { return RECORDTYPE_DBNORMAL ; }

  // Operatoren....
  LPVOID operator new (size_t size)
    { return GetGlobMem (size); }
  void operator delete (LPVOID obj)
    { FreeGlobMem (obj); }
  DLLExport BOOL _export WINAPI IsUpdateDone ();
  DLLExport void _export WINAPI ResetUpdateFlags ();
  DLLExport void _export WINAPI DelJoins (WORD Tbnr);
  DLLExport void _export WINAPI NewJoins (WORD Tbnr);
  DLLExport void _export WINAPI RefreshJoin (LPDBREQUEST req,WORD TablePart,LPVOID FAR *ExtParams,int AnzExtra,LPOLDPARAM oldP);
  DLLExport BOOL _export WINAPI IsValid ();

  DLLExport void _export FAR PASCAL SetSortVals (LPDBREQUEST req);
  virtual void UseRecordForJoins ();
  virtual void FreeRecordForJoins ();

  friend DLLExport BOOL _export WINAPI GetCmdFifoInfo (int Nmbr,DebFifoInfo FAR *dff);
  friend DLLExport BOOL _export WINAPI GetCmdMoreInfo (BYTE CmdNmbr,BYTE HistNmbr,DebFifoInfo FAR *di);
  friend void CheckRecordInHistory(DebFifoInfo FAR *DFF,LPDBRECORD REC,LPSTR Scope,LPCMDFIFO res);
  friend BOOL CheckVarElemIn (DebFifoInfo FAR *dff,LPDBRECORD rec,LPSTR Scope,LPVARELEM vToSearch);
  friend class DBRecordAdmin;
  friend struct FAR RecRoot;
  friend LPDBRECORD FindRecordInCycl (LPDBRECORD rs,TableRef FAR *x);
  };

class FAR DBLocalRecord : public DBRecord {
 public :
  virtual void UseRecordForJoins ()
    { }
  virtual void FreeRecordForJoins ()
    { }
  virtual void DoAllJoins ()
    { }
  virtual void FillIn (LPVARELEM v,int TableNr,WORD VarID)
    { }
  virtual void FreeJoins()
    { }
  virtual void FreeJoins(DWORD eNummer)
    { }
  virtual int GetRecordType ()
    { return RECORDTYPE_DBLOCAL ; }

  DLLExport _export WINAPI DBLocalRecord (WORD AnzVars,DWORD Id);
  };

class FAR DBHelpRecord : public DBLocalRecord {
 public :

  virtual int GetRecordType ()
    { return RECORDTYPE_DBHELP ; }

  virtual DLLExport void _export WINAPI SetConnection (DWORD OwnerID,WORD VarID,DWORD DocID,LPVOID cmd,LPCMDCOUNT c,int UpdateExtraType = EXTRATYPE_NONE,LPVOID UpdateExtraData = NULL,int ExtraDataSize = 0);
  virtual DLLExport void _export WINAPI ClearConnection (DWORD OwnerID,WORD VarID,DWORD DocID,LPVOID cmd,int ExtraType = EXTRATYPE_NONE,LPVOID UpdateExtraData = NULL,int ExtraDataSize = 0);

  DLLExport _export WINAPI DBHelpRecord (WORD AnzVars,DWORD Id);
  };

class FAR DBConstRecord : public DBHelpRecord {
 public :

  virtual int GetRecordType ()
    { return RECORDTYPE_DBCONST ; }

  DLLExport _export WINAPI DBConstRecord (WORD AnzVars,DWORD Id,GLOBALHANDLE hGConstMem);
  virtual DLLExport _export WINAPI ~DBConstRecord();
  };

#define ANZRECSPERLINE  2
struct FAR RecBufferLine {
  RecBufferLine FAR *Next;
  LPDBRECORD rec[ANZRECSPERLINE];
  };

/*-----< Definition eines der Recordbuffer: Resultat einer Abfrage >------*/
#define ADDLINEPOS_START   1
#define ADDLINEPOS_END     2
struct FAR RecBuffer {
  RecBufferLine FAR *first;
  RecBufferLine FAR *act ;
  DLLExport void _export WINAPI AddLine (WORD AnzTables,WORD postion);
  void SetRes (int TblNum,LPDBRECORD r)
    { act->rec[TblNum] = r; }
  DLLExport void _export WINAPI Clear ();

  RecBufferLine FAR *First()
    { return first ; }
  RecBufferLine FAR *Last()
    { RecBufferLine FAR *h = first ; 
      for ( ; ((h != NULL) && (h->Next != NULL)) ; h = h->Next) ;
      return h;
    }
  };
typedef RecBuffer FAR *LPRECBUFFER;

struct FAR ParseRecBuffer : RecBuffer {
  LPSTR parseCmd;
  LONG error;
  LPSTR errorMsg;
  DBINT errorOfs;
  DLLExport void _export WINAPI Clear ();
  };
typedef ParseRecBuffer FAR *LPPARSERECBUFFER;


/*-------< Herstellung der Verbindung einer Abfrage und einer Liste >------*/
struct FAR ParamBlock {
  int AnzPars;
  LPVOID ptr[CB_PARAM-2];   // Zeiger muessen mit GetBlockSize verifizierbar sein!
  WORD pType[CB_PARAM-2];
  };
typedef ParamBlock FAR *LPPARAM;

#define FIND_FIRST  0
#define FIND_LAST   1

DLLExport BOOL _export WINAPI CompareEqual (LPDBRECORD h, TableRef FAR *tr, int FAR *IdToFind, 
                                            LPVOID FAR *Data, int AnzSegs, int *segsFound);
struct FAR DBRecordList ;
typedef DBRecordList FAR *LPDBRECORDLIST;
struct FAR RLPtr {
  LPDBRECORDLIST ptr;   // Zeiger auf naechsten Datensatz
  BOOL SelectionEnd;    // Flag, das anzeigt ob im Falle eines NULL
                        // Zeigers auch die Datenbank NULL sagen 
  };

struct FAR DBRecordList {
  RLPtr    Next,Prev;      // Doppelt verkettete Liste

  LPDBRECORD rec;          // Aktueller Record
  OutParam FAR *op;

  BYTE isUsed;
  BYTE ShouldBeDeleted;
  LPOLDPARAM oldP;

  // Verwaltung der UseFlags (+ Mitteilungen an den Recordmanager)
  void UseRecord (DWORD OwnerID,DWORD DocumentID,BOOL doUpdate);
  void ReleaseRecord (DWORD OwnerID,DWORD DocumentID);
  BOOL IsUsed ()          { return isUsed ;  }

  void DeleteRecord ()    { delete rec ; }
  };

#ifndef HASH_INCLUDED
  class FAR hash;
#endif
class FAR RecordList {
 protected :
  DWORD DocumentID;
  LPTABLEDEF td;
  BOOL   doUpdate;
  LPDBRECORDLIST head,tail;
  LPSTR order;
  int cCache;
  
  LPDBRECORDLIST FindRec (LPDBRECORD rec);
  LPDBRECORDLIST FindRec (OutParam FAR *op);
  void RemoveRecord (LPDBRECORDLIST h);
  int AnzElesToIndex;
  hash FAR *FAR *eleHash;
  int FAR *IndexedElemes;
  int AnzExtraIndex;
  hash FAR *FAR *segHash;
  int FAR *FAR *segIndex;
  int AnzSegIndex;

  int AnzSegsInIndex (int IndexNr)
    {
    return GetBlockSize (segIndex[IndexNr]) / sizeof(segIndex[0][0]) ;
    }
 public :

  virtual void ExtConnections (LPDBRECORD r,BOOL doSet);
  DLLExport void _export WINAPI RemoveRecFromHashs (LPDBRECORD rec);

  // Verwaltung der doppelt verketteten List
  DLLExport void _export WINAPI SetVarToHash (int Id);
  DLLExport LPDBRECORD _export WINAPI FindRecord (TableRef FAR *tr,int FAR *IdToFind,LPVOID FAR *Data,
                                                  int AnzSegs, int Mode = FIND_FIRST);
  DLLExport BOOL _export FAR PASCAL IsHashed (TableRef FAR *tr,int FAR *Id,int AnzSegs, 
                                              BOOL FAR *isSeg = NULL, int FAR *segNr = NULL);
  DLLExport BOOL _export WINAPI CheckSegments (TableRef FAR *tr, int AnzSegs, int alreadyChecked);

  // Verwaltung der doppelt verketteten List
  DLLExport LPDBRECORD _export WINAPI AddRecAtTail  (LPDBRECORD rec,LPDBREQUEST req,BOOL doUse = FALSE);
  DLLExport LPDBRECORD _export WINAPI AddRecAtHead  (LPDBRECORD rec,LPDBREQUEST req,BOOL doUse = FALSE);
  DLLExport LPDBRECORD _export WINAPI AddRecBehind  (LPDBRECORD rec,LPDBRECORD insertafter,LPDBREQUEST req,BOOL doUse = FALSE);
  DLLExport LPDBRECORD _export WINAPI AddRecBefore  (LPDBRECORD rec,LPDBRECORD insertbefore,LPDBREQUEST req,BOOL doUse = FALSE);
  DLLExport LPDBRECORD _export WINAPI FindRec   (LPPRIMKEY k);
  void SetOrder (LPSTR o)
    { 
    if (order != NULL) FreeGlobMem (order);
    order = LPSTR (GetGlobMem (lstrlen(o) + 1)) ; 
    lstrcpy (order,o) ;
    }

  void MarkTailAsEnd () { if (tail != NULL) tail->Next.SelectionEnd = TRUE ; }
  void MarkHeadAsEnd () { if (head != NULL) head->Prev.SelectionEnd = TRUE ; }

  // Alle ueberfluessigen Records rausschmeissen
  void  ClearCached ();

  /*-< Arbeiten mit den aktiven Datensaetzen >-*/
  DLLExport LPDBRECORD _export WINAPI GetFirstActive ();               // Erster Record, der als verwendet markiert ist
  DLLExport LPDBRECORD _export WINAPI GetNextActive (LPDBRECORD rec);  // Naechster Aktiver
  DLLExport LPDBRECORD _export WINAPI GetLastActive ();                // Letzter Record, -''-

  DLLExport OutParam FAR *_export WINAPI GetFirstActiveParam ();               // Erster Record, der als verwendet markiert ist
  DLLExport OutParam FAR *_export WINAPI GetNextActiveParam (OutParam FAR *op);  // Naechster Aktiver
  DLLExport OutParam FAR *_export WINAPI GetLastActiveParam ();                // Letzter Record, -''-


  DLLExport void _export WINAPI ThrowRecord     (OutParam FAR *op);
  DLLExport void _export WINAPI ThrowRecord     (LPDBRECORD rec);      // Datensatz wieder freigeben
  DLLExport void _export WINAPI ThrowAtHeadParam (OutParam FAR *op);
  DLLExport void _export WINAPI ThrowAtHead     (LPDBRECORD rec);      // Alle Datensaetze am Kopf bis
                                                                 // auf rec freigeben
  DLLExport void _export WINAPI ThrowAtTail     (LPDBRECORD rec);      // Alle Datensaetze am Ende
                                                                 // freigeben
  DLLExport void _export WINAPI ThrowList       ();                    // Alle Datensaetze der Liste
                                                                 // freigeben
  DLLExport void _export WINAPI ThrowFirstUsed();
  DLLExport void _export WINAPI ThrowLastUsed();
  DLLExport BOOL _export WINAPI IsMoreOnHead();
  DLLExport BOOL _export WINAPI IsMoreOnTail();

  DLLExport void _export WINAPI SortList (int AnzSegsToSort,int FAR *TableInd,TableRef FAR *tref,int dir);

  virtual DLLExport LPDBRECORD _export WINAPI GetFirst  ();                    // Lesen des ersten Records der Abfrage
  virtual DLLExport LPDBRECORD _export WINAPI GetLast   ();                    // Lesen des letzten Records
  virtual DLLExport LPDBRECORD _export WINAPI GetNext   (LPDBRECORD rec);      // Lesen des vorhergehende Records
  virtual DLLExport LPDBRECORD _export WINAPI GetPrev   (LPDBRECORD rec);      // Lesen des naechsten Records
  virtual DLLExport void _export WINAPI MarkRecordUnused (LPDBRECORD rec);

  DLLExport _export WINAPI RecordList (LPTABLEDEF tb,DWORD Id,int RecsToCache,BOOL Update);
  virtual DLLExport _export WINAPI RecordList::~RecordList ();

  virtual DLLExport BOOL _export WINAPI ExtUpdate ();
  virtual DLLExport void _export WINAPI SetConnectionInfo (LPVOID ca,LPVOID cc);

  LPVOID operator new (size_t size)
    { return GetGlobMem (size); } 
  void operator delete (LPVOID obj)
    { FreeGlobMem (obj) ; }

  DLLExport int _export WINAPI GetAnzCachedRecords();
  LPTABLEDEF GetTableDef()
    {
    return td;
    }
  };

class FAR DBList : public RecordList {
 private :
  int cGet;
  LPSTR access;
  ParamBlock pb;
  LPVOID hstmt;

  LPVOID ConnectionAddress,_ccount;

  // Resultate eintrage
  void AddRecordsAtHead (LPRECBUFFER data);
  void AddRecordsAtTail (LPRECBUFFER data);

  // Datenbankaufrufe
  int DoDBCall (WORD Op,LPDBRECORD rec = NULL);
  void TestRes (int stat);
   
  LPREQELEM ElesToGet;
  LPDBREQUEST req;

  BOOL StraightForward;

  LPVOID ErrorCBP;

 public :
  void SetSimpleList ()
    {
    StraightForward = TRUE;
    }
  LPDBREQUEST GetRequest()
    {
    return req;
    }
  virtual void ExtConnections (LPDBRECORD r,BOOL doSet);
  /////////////////////////////////////////////////////////////////////////
  //  Datenbankzugriffe: 
  //       Als Parameter fuer die Abfrage werden die Parameter des 
  //       Konstruktors (bzw. von SetParams) verwendet (sofern welche 
  //       angegeben)
  /////////////////////////////////////////////////////////////////////////
  virtual DLLExport OutParam FAR * _export WINAPI GetFirstParam ();
  virtual DLLExport LPDBRECORD _export WINAPI GetFirst  ();                    // Lesen des ersten Records der Abfrage
  virtual DLLExport OutParam FAR * _export WINAPI GetLastParam ();
  virtual DLLExport LPDBRECORD _export WINAPI GetLast   ();                    // Lesen des letzten Records
  virtual DLLExport OutParam FAR *_export WINAPI GetNextParam (OutParam FAR *op);
  virtual DLLExport LPDBRECORD _export WINAPI GetNext   (LPDBRECORD rec);      // Lesen des vorhergehende Records
  virtual DLLExport OutParam FAR *_export WINAPI GetPrevParam (OutParam FAR *op);
  virtual DLLExport LPDBRECORD _export WINAPI GetPrev   (LPDBRECORD rec);      // Lesen des naechsten Records
  DLLExport LPDBRECORD _export WINAPI Get (LPPARAM Params);      // Zugriff mit Parametern fuer den Get
                                              // Nach dem Get werden die normalen Parameter 
                                              // wieder restauriert. Fuer die Abfrage
                                              // werden die standard Parameter mit den
                                              // angegebenen kombiniert

  DLLExport void _export WINAPI AddElemsToGet (WORD FAR *VarId,int AnzVars);
  DLLExport void _export WINAPI RefreshJoins (LPVOID FAR *ExtParams,int AnzExtra);

  DLLExport void _export WINAPI SetParams         (LPPARAM Params);    // Neusetzten der Parameter

  DLLExport _export WINAPI DBList (LPTABLEDEF tb, // Tabelle fuer die der ganze Bloedsinn gemacht 
                                            // werden soll
        DWORD DocumentID,      // Abhaengigkeiten fuer die Liste
        LPSTR AccessName,
        int AnzRecsToGet,      // Anzahl Records, die von der Datenbank in
                               // einem Rutsch gefordert werden sollen
        int RecsToCache,       // Anzahl Records, die an den Enden maximal
                               // gecacht werden sollen
        LPPARAM Params = NULL, // Parameter (fuer Filterkriterien...)
        BOOL doUpdate = TRUE   // Sollen Records mit Updateliste gefuehrt 
                               // werden ?
                            );
  virtual DLLExport _export WINAPI ~DBList ();
  virtual DLLExport BOOL _export WINAPI ExtUpdate ();
  virtual DLLExport void _export WINAPI SetConnectionInfo (LPVOID ca,LPVOID cc);
  void SetAccess(LPSTR n)
    {
    if (access != NULL) FreeGlobMem (access);
    access     = LPSTR(GetGlobMem (lstrlen(n)+1));
    lstrcpy (access,n);
    if (req != NULL) req->SetSelection (n);
    }
  virtual DLLExport void _export WINAPI MarkRecordUnused (LPDBRECORD rec);
  };

// Liste der Records, die Systemweit aktiv sind
/////////////////////////////////////////////////////
struct FAR GlobRecordList {
  GlobRecordList FAR *Next;
  GlobRecordList FAR *Prev;
  LPDBRECORD rec;
  };
typedef GlobRecordList FAR *LPGRECLIST;

class FAR DBRecordAdmin {
 private :
  LPGRECLIST rl;

  void Add (LPDBRECORD n);
  BOOL FindSame (LPDBRECORD n);

 public :
  WORD GetSameRecords (LPDBRECORD h,WORD TableID,WORD Version,LPPRIMKEY k,LPJOINRECLIST jl);
  LPDBRECORD Use (LPDBRECORD h,DWORD OwnerID,DWORD DocumentID);
  DLLExport LPDBRECORD _export WINAPI Find (LPPRIMKEY k,WORD TableID,WORD Version);
  DLLExport BOOL _export WINAPI Release (LPDBRECORD h,DWORD DocumentID,DWORD OwnerID); // Wird noch nicht geloescht !

  friend void CheckAdministratiedRecords(DWORD OwnerID,DWORD DocumentID);
  friend DLLExport BOOL _export WINAPI GetCmdFifoInfo (int Nmbr,DebFifoInfo FAR *dff);
  friend void GetDataInfoFor (DebFifoInfo FAR *dff,LPVARELEM v);
  friend struct FAR RecRoot;
  };
typedef DBRecordAdmin FAR *LPDBRECORDADMIN;

DLLExport LPDBRECORDADMIN _export WINAPI GetDBRecordAdmin();

#define DBCALL_SUCCESS              0
#define DBCALL_ERROR_NOACCESS       1
#define DBCALL_NODATA               2
#define DBCALL_ERROR                3
#define DBCALL_ENDOFFILE            4

/////////////////////////////////////////////////////////////////////////
//  RecRoot:  Zeiger auf die Records eines Datensatzes
/////////////////////////////////////////////////////////////////////////
struct FAR RecRoot;
typedef RecRoot FAR *LPRECROOT;
class FAR mdiChild;
#define CSYSRECS  5
struct FAR RecRootRef {
  mdiChild *rrOwner;
  LPRECROOT rr;
  WORD tnr;
  };
typedef RecRootRef FAR *LPRRR;
struct FAR RecRoot {
 private :
  WORD AnzTables;
 public :
  RecRootRef FAR *NextInKontext;
  RecRootRef FAR *PrevInKontext;
 private :
  LPDBRECORD rec[1];
 public :

  LPDBRECORD GetRecord(WORD TableNr)
    { return rec[TableNr] ; }
  void SetRecord(WORD TableNr,LPDBRECORD r)
    { rec[TableNr] = r ; }

  inline LPVOID Get(DWORD lID)
    { 
    return GetRecord(LOWORD(lID))->Get(HIWORD(lID));
    }
  inline LPTSTR GetStr(DWORD lID)
    {
    return GetRecord(LOWORD(lID))->GetStr(HIWORD(lID));
    }
  inline void Set(DWORD lID,LPVOID Data,WORD DataSize,LPVOID cmd,BOOL doUpdate,int ExtraType,LPVOID ExtraData,int ExtraSize)
    {
    GetRecord(LOWORD(lID))->Set(HIWORD(lID),Data,DataSize,cmd,doUpdate,ExtraType,ExtraData,ExtraSize);
    }
  inline void Del(DWORD lID,LPVOID cmd,BOOL doUpdate,int ExtraType,LPVOID ExtraData,int ExtraSize)
    {
    GetRecord(LOWORD(lID))->Del(HIWORD(lID),cmd,doUpdate,ExtraType,ExtraData,ExtraSize);
    }
  inline void SetConnection(DWORD OwnerID,DWORD lID,DWORD DocID,LPVOID cmd,LPCMDCOUNT c,int ExtraType = EXTRATYPE_NONE,LPVOID UpdateExtraData = NULL,int ExtraDataSize = 0)
    {
    GetRecord(LOWORD(lID))->SetConnection((OwnerID != 0L) ? OwnerID : DWORD(this) + LOWORD(lID),HIWORD(lID),DocID,cmd,c,ExtraType,UpdateExtraData,ExtraDataSize);
    }
  inline void ClearConnection(DWORD OwnerID,DWORD lID,DWORD DocID,LPVOID cmd,int ExtraType = EXTRATYPE_NONE,LPVOID UpdateExtraData = NULL,int ExtraDataSize = 0)
    {
    LPDBRECORD r = GetRecord(LOWORD(lID));
    if (r != NULL) r->ClearConnection((OwnerID != 0L) ? OwnerID : DWORD(this) + LOWORD(lID),HIWORD(lID),DocID,cmd,ExtraType,UpdateExtraData,ExtraDataSize);
    }
  inline BOOL IsUpdateFromEle (DWORD lID)
    {
    return GetRecord(LOWORD(lID))->IsUpdateFromEle(HIWORD(lID));
    }
  inline WORD GetDataType (DWORD lID)
    {
    return GetRecord(LOWORD(lID))->GetDataType(HIWORD(lID)) ;
    }

  DLLExport void _export WINAPI SetRec (LPDBRECORD rec,WORD TableNr,DWORD DocumentID,BOOL fromInsert);
  friend DLLExport LPRECROOT _export WINAPI InitializeRecRoot (WORD AnzTables);
  friend DLLExport void _export WINAPI DeleteRecRoot (LPRECROOT rr,DWORD DocumentID);
  friend DLLExport LPVOID _export WINAPI DDSGetVarVal (LPVOID Context,WORD TableNr,WORD VarNr);
  friend BOOL BeforeWrite (mdiChild FAR *c,WORD TableID,WORD VarID);
  friend void AfterWrite (mdiChild FAR *c,WORD TableID,WORD VarID);
  };

struct MDIListEntry {
  mdiChild FAR *ent;
  MDIListEntry FAR *Next;
  };

DLLExport MDIListEntry FAR *_export WINAPI GetMDILEFirst() ;

struct OldMDIListEntry {
  GLOBALHANDLE commands;
  char fName[13];
  OldMDIListEntry FAR *Next;
  };

DLLExport OldMDIListEntry FAR *_export WINAPI GetOLDMDILEFirst() ;

DLLExport LPRECROOT _export WINAPI InitializeRecRoot (WORD AnzTables);
DLLExport void _export WINAPI DeleteRecRoot (LPRECROOT rr);
DLLExport void _export WINAPI FormatOutTxt (LPSTR res,LPVOID data,WORD mType);
DLLExport void _export WINAPI ConnectToSQL (HWND hWndWorkArea,LPSTR FName);
DLLExport void _export WINAPI DBTest (BOOL doCreate);
DLLExport void _export WINAPI AddFileTranslation (DWORD Id,LPSTR oldName,LPSTR newName);
DLLExport void _export WINAPI RemoveFileTranslation (DWORD Id,LPSTR newName);

DLLExport BOOL _export WINAPI Out (LPDBRECORD rec,int hGresID,WORD op,DWORD FAR *Id0,LPSTR Selection,LPVOID p1 = NULL,int s1 = 0,WORD m1 = 0,
                                                             LPVOID p2 = NULL,int s2 = 0,WORD m2 = 0,
                                                             LPVOID p3 = NULL,int s3 = 0,WORD m3 = 0);
DLLExport LPDBRECORD _export WINAPI Ask (LPTABLEDEF td,LPSTR Selection,LPVOID p1 = NULL,int s1 = 0,WORD m1 = 0,
                                              LPVOID p2 = NULL,int s2 = 0,WORD m2 = 0,
                                              LPVOID p3 = NULL,int s3 = 0,WORD m3 = 0);
DLLExport void _export WINAPI Excute (LPSTR Command,DLLHANDLE dllh,LPVOID p1 = NULL,int s1 = 0,WORD m1 = 0,
                           LPVOID p2 = NULL,int s2 = 0,WORD m2 = 0,
                           LPVOID p3 = NULL,int s3 = 0,WORD m3 = 0);
DLLExport void _export WINAPI OnManipulate (LPDBRECORD r,short updateMode,LPTABLEDEF td = NULL,LPVOID KeyBuffer = NULL);
DLLExport void _export WINAPI StartSystemUpdate ();
DLLExport void _export WINAPI CheckDBOut ();
DLLExport void _export WINAPI CheckDBIn ();
DLLExport LONG _export WINAPI GetDBToken (LPSTR TableName,LPVOID PrimKey,BOOL FAR *showLockedScreen);
DLLExport LONG _export WINAPI UnlockDBToken (LONG tnum);
DLLExport void _export ClearMyTokens();

// Header, wie er zum Replizieren verwendet wird
#pragma pack(1)
struct RepBase {
  char Kennung[30];     // Kennung (muss sein: IPOSREPKENNUNG)
  LONG Version;         // Version des Wurzelsatzes
  LONG PrimKey;         // Primaerschluessel des Wurzelsatzes
  short RepNum;         // Replikationsvorschrift, mit der der Satz erzeugt wurde
  short AussenStelle;   // Aussenstelle, von der der Datensatz kommt
  LONG RecordVersion;   // Primaerschluessel der dortigen RecordVersion
  LONG AnzRecords;      // Anzahl Records die folgen 
  DWORD GesSize;
  };
struct RecBase {
  TableRef tRef;
  short AnzVars;        // Anzahl Variablen, die Folgen
  LONG Version;
  LONG RecordVersion;
  };
struct VarBase {
  short VarID;        // VarID, wie in DataDict angegeben
  short size;         // Groesse der Variable, die Folgt
  };
#pragma pack()


// Errorhandling:

// ACHTUNG: der Aufrufer der Funktion GetLastErrorCBP() uebernimmt
// den retournierten Speicherblock in seine Hoheit und muss ihn also
// auch freigeben, wenn er nicht mehr benoetigt wird

typedef DLLExport LPVOID _export (WINAPI *GLE_PROC)(void);
typedef DLLExport void _export (WINAPI *BEH_PROC)(LPVOID ErrorCBP,DLLHANDLE hd);
typedef DLLExport void _export (WINAPI *EEH_PROC)(LPVOID ErrorCBP,DLLHANDLE hd);
DLLExport void _export WINAPI SetErrorHandlingProcs(GLE_PROC GLEproc,BEH_PROC BEHproc,EEH_PROC EEHproc);
DLLExport LPVOID _export WINAPI GetLastErrorCBP(void);
DLLExport void _export WINAPI BeginErrorHandling(LPVOID ErrorCBP,DLLHANDLE hd);
DLLExport void _export WINAPI EndErrorHandling(LPVOID ErrorCBP,DLLHANDLE hd);

