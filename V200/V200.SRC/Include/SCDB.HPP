/*-------------< Script - Debugger >---------*/
//
//  $Header:   P:/marille/clinicum/include/rev/scdb.hpv   1.12   12 Aug 1998 19:19:02   Wolfgang  $
//  $Log:   P:/marille/clinicum/include/rev/scdb.hpv  $
// 
//    Rev 1.12   12 Aug 1998 19:19:02   Wolfgang
// 1.) SDITEXT nur mehr DI, da erstes Zeichen der Originalextension bleibt.
// 
//    Rev 1.11   06 Jan 1998 19:57:56   Gerhold
// Watchvar ... optionaler Parameter Result
// 
//    Rev 1.10   19 Nov 1997 18:45:18   Hannes
// Restool 32 Bit umstellung
// 
//    Rev 1.9   19 Feb 1997 12:02:58   Hannes
// Scriptfunktionen->Erweiterung des Headers
// 
//    Rev 1.8   02 Feb 1996 11:00:14   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.7   24 Aug 1995 00:12:22   HANNES
// Debuggerverbesserun
// 
//    Rev 1.6   11 Jul 1995 12:41:58   HANNES
// Scriptdebuggerdaten in compile.hpp verlagert
// 
//    Rev 1.5   13 Jan 1995 16:56:14   HANNES
// Variablen-Breakpoints
// 
//    Rev 1.4   09 Jan 1995 12:11:56   HANNES
// Debugger eingebaut
// 
//    Rev 1.3   04 Jan 1995 13:41:22   HANNES
// 
//    Rev 1.2   03 Jan 1995 12:04:30   HANNES
// 
//    Rev 1.1   03 Jan 1995 09:54:50   HANNES
// 
//    Rev 1.0   02 Jan 1995 18:32:24   HANNES
// Initial revision.
//

#define SDIEXT    "DI"
#pragma pack(1)
struct FAR LocalVarInfo {
  WORD TableNr;
  DWORD fOffs;
  WORD VarNr;
  WORD mType;
  char Name[1];

  int GetSize();
  };
#pragma pack ()

//
//---- Aufbau der Debuginfo -----
//
//  - DebugHeader
//  - DWORD SizeOfDebugInfo
//  - ScriptDebugInfo (sooft wie in SizeOfDebugInfo platz hat)
//  - DWORD SizeOfLocalData
//  - LocalVarInfo (sooft wie in SizeOfLocalData platz hat, wobei die
//    die einzelnen strukturen verschieden gross sind, durch '\0' in
//    Name getrennt)
//

struct FAR BPInfo {
  BPInfo FAR *Next;
  int LineNmbr;
  WORD modeMask;
  char FName[13];
  char PName[13];
  DWORD FAR *pOffs;
  LPSTR Extra;

  LPSTR GetIniString ();
  };

class FAR mdiChild;
struct FAR CallStackInfo {
  mdiChild FAR *c;
  char ProgName[13];
  DWORD progOffs;
  };

class FAR ScDebugInfo {
 public :
  char ProgName[13];
  GLOBALHANDLE hGDInfo;
  DebugHeader FAR *hd;
  ScriptDebugInfo FAR *sdi;
  LocalVarInfo FAR *lvi,FAR *lviEnd;
  ScriptDebugInfo FAR *GetSDI(DWORD Index);
  DWORD AnzFuncs;

  int GetIncNmbr (LPSTR fName);

  LocalVarInfo FAR *GetLVI();
  LocalVarInfo FAR *GetNextLVI();

  ScDebugInfo (LPSTR fName);
  ~ScDebugInfo ();

  BOOL SetBreakPoint (int LineNmbr,LPSTR fName);
  LONG GetLineFromAddress (DWORD progOffs,LPSTR SName);

  LPVOID operator new (size_t size)
    { return GetGlobMem (size) ; }
  void operator delete (LPVOID obj)
    { FreeGlobMem (obj); }
  friend void GetWatchOutText (ScDebugInfo FAR *scdb,LPSTR VarName,LPSTR OutTxt);
  };

DLLExport BOOL _export WINAPI Exception (mdiChild *c = NULL,WORD mode = 0xFFFF,LPSTR extra = NULL);
void BeforeExecution (LPVOID Context,WORD mode,LPSTR fName,DWORD progOffs);

BOOL IsBreakLine (int LineNr,LPSTR fName);
void DestroyBreakList ();
void LoadBreakList ();
void SetBreakList ();
void DestroyBreakPointsFrom (LPSTR Name);
void WatchVar (ScDebugInfo FAR *scdb,HWND hWParent,LPSTR VarName,LPSTR res = NULL);

void AddBreakpoint (BPInfo FAR *h);
void RemoveBreakpoint (BPInfo FAR *h);
void RemoveAllBreakPoints ();
DLLExport void _export WINAPI PushToCallStack (mdiChild *c,LPSTR fName,DWORD progOffs);
DLLExport void _export WINAPI PopFromCallStack ();
DLLExport void _export WINAPI ClearCallStack ();
DLLExport LONG _export WINAPI GetStackInfo (WORD wP,CallStackInfo FAR *csi);
void WatchStack (HWND hWParent);
LONG WatchWndProc (HWND hWnd,unsigned msg,WPARAM wP,LPARAM lP,BOOL FAR *done);
mdiChild *GetLastStackChild ();
DLLExport LONG _export WINAPI GetLastStackAddress ();
DLLExport BOOL _export WINAPI WaitForRestool (mdiChild *c,BPInfo FAR *h,WORD mode,LPSTR fName,DWORD progOffs,WORD modeMask);
DLLExport int _export WINAPI GetModuleLine (LPSTR fName,DWORD progOffset,LPSTR incName = NULL);

#define DBMODE_NORMAL   0
#define DBMODE_STEP     1
#define DBMODE_STEPINTO 2

struct FAR LastBreakInfo {
  char LastModuleBreak[13];
  int  LastModuleLine;
  int  LastStackBreak;
  WORD LastModeMask;
  int ActCSPtr;
  int dbMode;
  };
DLLExport LastBreakInfo FAR *_export WINAPI GetLBI ();

