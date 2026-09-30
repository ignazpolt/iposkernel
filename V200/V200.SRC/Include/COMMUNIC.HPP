/*
**  Kommunikation zwischen Restool und dem Hauptprogramm
*/
// $Header:   P:/marille/clinicum/include/rev/communic.hpv   1.15   16 Feb 2000 15:02:34   Wolfgang  $
// $Log:   P:/marille/clinicum/include/rev/communic.hpv  $
// 
//    Rev 1.15   16 Feb 2000 15:02:34   Wolfgang
// 1.) GetNextInCycl neu.
// 
//    Rev 1.14   23 Nov 1999 15:48:58   Wolfgang
// 1.) WMC_GETSCRIPTHD und GetScriptHd-Prototyp neu.
// 
//    Rev 1.13   12 Jan 1998 18:22:44   Hannes
// 
//    Rev 1.12   19 Nov 1997 18:45:16   Hannes
// Restool 32 Bit umstellung
// 
//    Rev 1.11   29 Jan 1997 13:03:18   HANNES
// pragma pack()
// 
//    Rev 1.10   26 Nov 1996 08:07:44   HANNES
// Automatischer Update
// 
//    Rev 1.9   28 Oct 1996 08:42:48   HANNES
// Erweiterte Funktionalitaet IsListPtr
// 
//    Rev 1.8   21 Oct 1996 18:53:38   HANNES
// Erweiterte Debugkommandos
// 
//    Rev 1.7   02 Feb 1996 11:00:18   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.6   24 Aug 1995 00:12:22   HANNES
// Debuggerverbesserun
// 
//    Rev 1.5   13 Jan 1995 16:56:12   HANNES
// Variablen-Breakpoints
// 
//    Rev 1.4   09 Jan 1995 12:11:38   HANNES
// Debugger eingebaut
// 
//    Rev 1.3   04 Jan 1995 13:41:22   HANNES
// 
//    Rev 1.2   03 Jan 1995 12:04:32   HANNES
// 
//    Rev 1.1   02 Jan 1995 12:20:48   HANNES
// 
//    Rev 1.0   02 Jan 1995 12:16:38   HANNES
// Initial revision.
//

// Messages, die an das Hauptfenster des Hauptprogrammes
// gesendet werden
#pragma pack(1)
#define MAX_DEBFINFO  16
#ifndef TABLEREF_DEFINED
struct FAR TableRef {
  WORD Version;
  WORD TableNr;
  };
#define TABLEREF_DEFINED
#endif
struct UpdVarInfo {
  char  Scope[13];
  WORD  VarNr;
  TableRef tRef;
  };

struct FAR DebFifoInfo {
  char   ModuleName[13];
  DWORD  DocumentID;
  LPVOID Cmd;
  DWORD  CmdOffset;
  int    AnzVars;
  UpdVarInfo Var[MAX_DEBFINFO];
  };
struct FAR VarValExtended {
  char Scope[13];
  LPVOID actContext;
  WORD TableID;
  WORD VarID;
  };
struct ContextBuffer {
  char fName[13];
  LPVOID c;
  LPVOID dummy;
  };

struct DBGGetRecordPtr {
  LPVOID ListPtr;
  int Index;
  BOOL IsActive;
  };
struct DBGIsListPtr {
  LPVOID ListPtr;
  int AnzRecs;
  char StructName[64];
  };
#pragma pack()
#define WMC_BASE            WM_USER + 0x2000
#define WMC_CLEARCEACHE     WMC_BASE + 0x0      // lP ... Name des Programmes,
                                                // das aus dem Cache verschwinden
                                                // soll
#define WMC_CONTINUEEXECUTION   WMC_BASE + 0x1  // wP,lP ... unbedeutend
#define WMC_ACTIVATE            WMC_BASE + 0x2  // Restool soll sich in den
                                                // Vordergrund schalten mit
                                                // lP ... Zeiger auf BPInfo, 
                                                // gefundener Breakpoint
#define WMC_INQUIREBPLIST       WMC_BASE + 0x3  // DDS will die Liste der
                                                // Breakpoints haben
#define WMC_SETBREAKPOINT       WMC_BASE + 0x4  // Setzen eines Breakpoints
#define WMC_REMOVEBREAKPOINT    WMC_BASE + 0x5  // Loeschen eines Breakpoints
#define WMC_GETVARVAL           WMC_BASE + 0x6  // Erfragen eines Watchwertes
#define WMC_GETSTACKINFO        WMC_BASE + 0x7  // Erfragen Adresse auf dem Stack
                                                // wP ... Index (von 0 aufwaerts)
                                                // lP ... Adresse auf CallStackInfo
#define WMC_GETMODULELINE       WMC_BASE + 0x8  // DDS will eine Programmzeile fuer
                                                // einen entsprechenden Offset
#define WMC_DOSTEP              WMC_BASE + 0x9  // DDS soll eine Zeile ausfuehren
#define WMC_DOSTEPINTO          WMC_BASE + 0xA  // DDS soll eine Zeile ausfuehren (inkl. Reinspringen)
#define WMC_GETCMDFIFOINFO      WMC_BASE + 0xB  // Erfragen der Fifo - Info, 
                                                // wP ... Nummer der Info (0xFFFF -> aktuellen Eintrag)
                                                // lP ... Zeiger auf DebFifoInfo
#define WMC_FURTHERINFO         WMC_BASE + 0xC  // Genaueres Erfragen der Fifo - Info,
                                                // LOBYTE(wP) Nummer in der Update Liste (= Info von Oben)
                                                // HIBYTE(wP) Nummer in dem History Array
                                                // lP ... Zeiger auf DebFifoInfo
#define WMC_GETVARVAL_SCOPE     WMC_BASE + 0xD  // lP ... Zeiger auf VarValExtended
#define WMC_SETVARBREAK         WMC_BASE + 0xE  // lP ... Zeiger auf VarValExtended
#define WMC_CLEARVARBREAK       WMC_BASE + 0xF  // lP ... Zeiger auf VarValExtended
#define WMC_GETFIRSTCONTEXT     WMC_BASE + 0x10 // lP ... Zeiger auf ContextBuffer
#define WMC_GETNEXTCONTEXT      WMC_BASE + 0x11 // lP ... Zeiger auf ContextBuffer
#define WMC_GETRECORDPTR        WMC_BASE + 0x12 // lP ... Zeiger auf DBGGetRecordPtr
#define WMC_ISLISTPTR           WMC_BASE + 0x13 // lP ... Zeiger auf DBGIsListPtr
#define WMC_GETFUNCOFFS         WMC_BASE + 0x14 // lP ... Zeiger auf mdiChild
#define WMC_GETRECDATA          WMC_BASE + 0x15 // wP ... Index,lP ... Zeiger auf DBRecord
#define WMC_GETRECTABLE         WMC_BASE + 0x16 // lP ... Zeiger auf DBRecord
#define WMC_BREAKIMMEDIATELY    WMC_BASE + 0x17 
#define WMC_CLOSE               WMC_BASE + 0x18
#define WMC_GETSCRIPTHD         WMC_BASE + 0x19
#define WMC_GETNEXTINCYCL       WMC_BASE + 0x20 // lP ... Zeiger auf DBRecord

#define WMC_MAX   0x21
#ifndef JUST_MSG
HWND GetDDSMainWnd ();
void ClearCachedProg (LPSTR Name);
void RunDDS ();
void StepDDS ();
void StepIntoDDS ();
struct FAR BPInfo;
struct FAR CallStackInfo;
class FAR ScDebugInfo;
void ActivateRestool (HWND hWnd,WORD mode,LONG lp);
void SetDDSBreak (BPInfo FAR *h);
void ClearDDSBreak (BPInfo FAR *h);
LPSTR GetFName(LPVOID fname);
BOOL CheckWindowForBreak (HWND hwndT,LPSTR FName,int LineNmbr);
LPVOID GetVarValue (WORD TableNr,WORD VarNr);
LONG SearchModuleLine (HWND hWnd,CallStackInfo FAR * lParam,LPSTR SName,BOOL doOpen = TRUE);
ScDebugInfo FAR *GetDebugInfoFromWindow (HWND hwndT,LPSTR fName,BOOL FAR *Found,BOOL UseInclude);
BOOL IsActiveBreakLine (int LineNr,LPSTR fName);
void SetModuleActive (LPSTR h_FName,int h_LineNmbr);
void WatchUpdateList (HWND hWParent);
ScDebugInfo FAR *SearchDebugInfo (LPSTR fName,BOOL doOpen);
void RecalcWatchVals ();
LPVOID GetVarValueExtended (WORD TableID,WORD VarID,LPSTR Scope,LPVOID actContext);
LPVOID GetScriptHd (CHAR FAR * ProgName);
void AddWatchLine (LPSTR VarName,LPSTR Scope,LPVOID Context);
BOOL ClearVarBreak (WORD TableID,WORD VarID,LPSTR Scope,LPVOID actContext);
BOOL SetVarBreak (WORD TableID,WORD VarID,LPSTR Scope,LPVOID actContext);
BOOL GetFirstContext (ContextBuffer FAR *vc);
BOOL GetNextContext (ContextBuffer FAR *vc);
BOOL GetContextBuffer (ContextBuffer FAR *vc,int sel);
LPVOID GetRecordPointer (LPVOID ListPtr,int Index,BOOL FAR *IsActive);
BOOL IsListPtr (LPVOID ListPtr,int FAR *AnzRecs,LPSTR Name);
LONG GetFuncFOffs (LPVOID c);
LPVOID GetRecData (LPVOID r,int i);
void GetRecTable (LPVOID r,TableRef FAR *tr);
void GetNextInCycl (LPVOID r,LPVOID *nr);
#endif
BOOL DDSGetCmdFifoInfo (int Nmbr,DebFifoInfo FAR *di);
BOOL DDSGetCmdMoreInfo (BYTE CmdNmbr,BYTE HistNmbr,DebFifoInfo FAR *di);
DLLExport LPVOID _export WINAPI DDSGetVarValExtended (VarValExtended FAR *ve);
void DDSSetVarBreak (VarValExtended FAR *ve);
void DDSClearVarBreak (VarValExtended FAR *ve);
LPVOID GetActContext(LPSTR Scope);
DLLExport BOOL _export WINAPI IsValidChild (LPVOID Context);

DLLExport LONG _export WINAPI GetDDSFirstContext (ContextBuffer FAR *vc);
DLLExport LONG _export WINAPI GetDDSNextContext (ContextBuffer FAR *vc);

LPVOID DDSGetRecordPtr (DBGGetRecordPtr FAR *d);
BOOL DDSIsListPtr (DBGIsListPtr FAR *d);

DLLExport LONG _export FAR PASCAL SetPointer (LPVOID data);
DLLExport LPVOID _export FAR PASCAL GetPointer (LONG lP);
DLLExport void _export FAR PASCAL CreateCommunic ();
DLLExport void _export FAR PASCAL DestroyCommunic ();

extern void ROpenCommunic ();
extern void RDestroyCommunic ();
LONG RSetData (LPVOID data,int Size);
LPVOID RGetPointer (LONG lP);
void RGetData (LPVOID res,int Size);
LPVOID RGetPointer_Size (LONG lP);

