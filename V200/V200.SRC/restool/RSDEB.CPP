/*-----< Debug - Handling im Restool >------*/
//
//  $Header:   P:/marille/clinicum/restool/rev/rsdeb.cpv   1.37   07 Jun 2000 11:51:40   Wolfgang  $
//  $Log:   P:/marille/clinicum/restool/rev/rsdeb.cpv  $
// 
//    Rev 1.37   07 Jun 2000 11:51:40   Wolfgang
// 1.) WatchVar gibt wenn nicht in Breakpoint "???" statt "" zurueck.
// 
//    Rev 1.36   24 May 2000 17:35:10   Wolfgang
// 1.) Fehler in GetWatchOutText korrigiert.
//     (== statt lstrcmp und h doppelt deklariert. VERDAMMTES C!)
// 
//    Rev 1.35   19 May 2000 18:23:12   Wolfgang
// 1.) GetWatchOutText beruecksichtigt ActiveScope und uebergibt Context.
//     (Schlaueres SHIFT-F9)
// 2.) Auch in WatchVar auf DDStatus pruefen.
// 
//    Rev 1.34   16 Feb 2000 15:03:54   Wolfgang
// 1.) Anzeige der Komponenten der Basisstruktur zu einer Struktur 
//     im Watchfenster.
// 2.) Anzeige der Komponenten aller Strukturen eines Listenelements.
// 
//    Rev 1.33   23 Nov 1999 17:15:56   Wolfgang
// 1.) Keine Debug-Info bei *.?DD-Files.
// 
//    Rev 1.32   23 Nov 1999 15:49:12   Wolfgang
// 1.) Auch Felder aus abgeleiteten Strukturen watchbar.
// 2.) ScriptContent bei %-Scripts von DDS holen.
// 
//    Rev 1.31   26 Mar 1999 18:14:36   Wolfgang
// 1.) Anzahl Bildchen hat sich geaendert.
// 
//    Rev 1.30   05 Oct 1998 11:27:56   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.29   12 Aug 1998 19:18:12   Wolfgang
// 1.) Verschiedene SDI-Files je nach erstem Buchstaben der Extension.
// 
//    Rev 1.28   06 Jan 1998 19:59:02   Gerhold
// WatchVar fuer die Tooltips ein bisschen erweitert
// 
//    Rev 1.27   05 Jan 1998 07:53:22   Hannes
// Einsparungen im Scriptheader
// 
//    Rev 1.26   19 Nov 1997 18:44:16   Hannes
// Restool 32 Bit umstellung
// 
//    Rev 1.25   05 Nov 1997 09:00:36   Gerhold
// 32 Bit
// 
//    Rev 1.24   08 Sep 1997 12:19:32   Hannes
// Fehlerkorrektur bei Benutzerdefinierten Formularen
// 
//    Rev 1.23   28 Aug 1997 15:50:30   gerhold
// Umstellung 32 Bit
// 
//    Rev 1.22   20 Jun 1997 11:54:34   Hannes
// 
//    Rev 1.21   19 Feb 1997 12:15:18   Hannes
// Ableitungen von Strukturen, Funktionsadresse zur Identifikation von
// Funktionsaufrufen
// 
//    Rev 1.20   27 Nov 1996 18:22:46   HANNES
// 
//    Rev 1.19   26 Nov 1996 08:09:44   HANNES
// Automatischer Update
// 
//    Rev 1.18   28 Oct 1996 11:50:02   HANNES
// 
//    Rev 1.17   28 Oct 1996 08:47:18   HANNES
// 
//    Rev 1.16   21 Oct 1996 18:56:34   HANNES
// Erweiterte Debugfunktionalitaet
// 
//    Rev 1.15   02 Feb 1996 10:50:58   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.14   12 Oct 1995 17:44:50   THOMAS
// Auch Clear in die Standard break aufgenommen
// 
//    Rev 1.13   24 Aug 1995 00:16:44   HANNES
// Debuggerverbesserungen
// 
//    Rev 1.12   11 Jul 1995 12:46:14   HANNES
// Debuggerdefinitionen umgelagert
// 
//    Rev 1.11   09 Jun 1995 00:29:16   HANNES
// CSYSRECS
// 
//    Rev 1.10   26 Apr 1995 15:27:42   GERHOLD
// 
//    Rev 1.9   30 Mar 1995 10:25:58   GERHOLD
// #pragma optimize
// 
//    Rev 1.8   26 Mar 1995 18:41:22   GERHOLD
// 
//    Rev 1.7   16 Feb 1995 12:39:58   GERHOLD
// Dialog fuer das Anzeigen von Watch-Variablen bevor sie uebernommen werden
// 
//    Rev 1.6   13 Jan 1995 16:54:26   HANNES
// Variablen-Breakpoints
// 
//    Rev 1.5   10 Jan 1995 17:31:52   HANNES
// Syntaxkorrektur fuer 8er Compiler
// 
//    Rev 1.4   09 Jan 1995 12:17:22   HANNES
// Debugger eingebaut
// 
//    Rev 1.3   04 Jan 1995 13:41:06   HANNES
// 
//    Rev 1.2   03 Jan 1995 12:04:10   HANNES
// 
//    Rev 1.1   03 Jan 1995 09:54:40   HANNES
// 
//    Rev 1.0   02 Jan 1995 18:32:52   HANNES
// Initial revision.
//
#include <windows.h>
#include <stdio.h>
#include <dos.h>
#include <memory.h>
#include "dds32.h"

#include "globmem.h"
#define NODDSDATA
#include "dds.hpp"
#include "hash.hpp"
#include "compile.hpp"
#include "scdb.hpp"
#define MODULENUM   144
#include "winass.hpp"
#include "dlladmin.h"
#include "dlladmin.hpp"
#include "scripthd.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "blandmdi.hpp"
#include "RESID.H"
#include "dlgtempl.hpp"

#include "msdntb.h"
#include "blandmdi.h"
#include "restool.hpp"
#include "communic.hpp"

#include "sc2d.hpp"
#include "font.hpp"
#include "printer.hpp"
#include "paint.hpp"
#include "mdichild.hpp"


void ShowWatch ();
DLLExport BOOL FAR PASCAL _export WatchVarDialog (HWND hDlg, UINT msg, WORD wP, LONG lP);


LPSTR GetFName(LPVOID fname)
  {
  LPSTR h = LPSTR(fname);
  LPSTR start = h;
  for ( ; *h ; h++) {
    if ((*h == '\\') || (*h == ':')) start = h+1;
    }
  AnsiUpper (start);
  return start;
  }

#pragma optimize("", off)
ScDebugInfo::ScDebugInfo (LPSTR fName)
  {
  char Name[128],fName1[128],fName2[128];
  lstrcpy (Name,GetFName(fName));
  lstrcpy (ProgName,Name);
  BOOL done = FALSE ;
  BOOL noDebugInfo = FALSE;
  for ( LPSTR h = Name ; *h ; h++) {
    if (*h == '.') {
      if (*(h+1)) {
        if (lstrcmpi (h+2,"DD") == 0)
          noDebugInfo = TRUE;
        lstrcpy (h+2,SDIEXT);
        }
      else
        lstrcpy (h+1,SDIEXT);
      done = TRUE ;
      break ;
      }
    }
  if (!noDebugInfo) {
    if (!done) {
      *h = '.' ;
      lstrcpy (h+1,SDIEXT);
      }
    GetDebugFileName (Name,fName1,fName2);
    OFSTRUCT Of;
    int fi = OpenFile (fName1,&Of,OF_READ);
    if (fi > 0) {
      DWORD dwSize = _llseek (fi,0L,SEEK_END);
      _llseek (fi,0L,SEEK_SET);
      hGDInfo = GlobalAlloc (GMEM_MOVEABLE,dwSize);
      hd = (DebugHeader FAR *) GlobalLock (hGDInfo);
      WIN_ASSERT (_hread (fi,hd,dwSize) == LONG(dwSize));
      LPDWORD lpSDISize = LPDWORD(hd+1);
      AnzFuncs = (*lpSDISize - sizeof(DWORD)) / sizeof (*sdi);
      sdi = (ScriptDebugInfo FAR *) (lpSDISize+1);
      LPDWORD lpLVISize = LPDWORD(((char _huge *) lpSDISize)+*lpSDISize);
      lvi = (LocalVarInfo FAR *) (lpLVISize+1);
      lviEnd = (LocalVarInfo FAR *) (((char _huge *) lpLVISize)+*lpLVISize);
      _lclose (fi);
      }
    }
  }
#pragma optimize("", on)

ScDebugInfo::~ScDebugInfo ()
  {
  if (hGDInfo) {
    GlobalUnlock (hGDInfo);
    GlobalFree (hGDInfo);
    }
  }

int ScDebugInfo::GetIncNmbr (LPSTR fName)
  {
  char Name[128];
  lstrcpy (Name,fName);
  LPSTR s = GetFName (Name);
  for (int i = 0 ; i < hd->AnzFiles ; i++) {
    if (lstrcmp (hd->ent[i].FName,s) == 0) return i ;
    }
  return -1;
  }

ScriptDebugInfo FAR *ScDebugInfo::GetSDI(DWORD i)
  {
  char _huge *base = (char huge *) sdi;
  static ScriptDebugInfo ss;
  hmemcpy (&ss,base + i * DWORD(sizeof(ss)),sizeof(ss));
  return &ss;
  }

static LocalVarInfo FAR *NextLVI;
static char LVIbuffer[256];
int LocalVarInfo::GetSize()
  {
  char _huge *h = Name;
  for (int res = 0 ; *h ; h++ , res ++ ) ;
  return sizeof(*this)+res ;
  }
LocalVarInfo FAR *ScDebugInfo::GetLVI()
  {
  if (lvi != NULL) {
    int ActSize = lvi->GetSize();
    hmemcpy (LVIbuffer,lvi,ActSize);
    NextLVI = (LocalVarInfo FAR *) ((char _huge *) lvi + LONG(ActSize));
    return (LocalVarInfo FAR *) LVIbuffer;
    }
  else  
    return NULL;
  }
LocalVarInfo FAR *ScDebugInfo::GetNextLVI()
  {
  if (NextLVI < lviEnd) {
    int ActSize = NextLVI->GetSize();
    hmemcpy (LVIbuffer,NextLVI,ActSize);
    NextLVI = (LocalVarInfo FAR *) ((char _huge *) NextLVI + LONG(ActSize));
    return (LocalVarInfo FAR *) LVIbuffer;
    }
  else
    return NULL ;
  }

BPInfo FAR *FirstBP;

LPSTR PushString (LPSTR old,LPSTR strtopush)
  {
  int oldsize = (old != NULL) ? lstrlen(old) : 0 ;
  int nSize = oldsize + lstrlen(strtopush) + 1;
  LPSTR res = LPSTR (GetGlobMem (nSize));
  if (old != NULL)
    lstrcpy (res,old);
  lstrcat (res,strtopush);
  if (old != NULL) FreeGlobMem (old);
  return res;
  }

LPSTR BPInfo::GetIniString ()
  {
  LPSTR res = PushString (NULL,PName);
  res = PushString (res,",");
  res = PushString (res,FName);
  res = PushString (res,",");
  char otxt[20];
  wsprintf (otxt,"%d",LineNmbr);
  res = PushString (res,otxt);
  res = PushString (res,",");
  int AnzOffs = GetBlockSize (pOffs) / sizeof(DWORD);
  for (int i = 0 ; i < AnzOffs ; i++) {
    wsprintf (otxt,"%ld",pOffs[i]);
    res = PushString (res,otxt);
    res = PushString (res,",");
    }
  wsprintf (otxt,"%d",modeMask);
  res = PushString (res,otxt);
  return res;
  }

void PushToBPList (LPSTR fName,LPSTR pName,int LineNmbr,DWORD FAR *pOffs,int AnzpOffs,WORD ModeMask)
  {
  BPInfo FAR *bp = (BPInfo FAR *) GetGlobMem (sizeof(*bp));
  if (FirstBP == NULL)
    FirstBP = bp;
  else {
    for (BPInfo FAR *h = FirstBP ; h->Next != NULL ; h = h->Next ) ;
    h->Next = bp;
    }
  bp->LineNmbr = LineNmbr ;
  lstrcpy (bp->FName,GetFName(fName));
  lstrcpy (bp->PName,GetFName(pName));
  bp->pOffs = (DWORD FAR *) GetGlobMem (sizeof(DWORD) * AnzpOffs);
  bp->modeMask = ModeMask;
  lmemcpy (bp->pOffs,pOffs,sizeof(DWORD) * AnzpOffs);

  SetDDSBreak (bp);
  }

BOOL IsBreakLine (int LineNr,LPSTR fName)
  {
  if (fName == NULL) return FALSE ;
  LPSTR x = GetFName (fName);
  for (BPInfo FAR *h = FirstBP; h != NULL ; h = h->Next) {
    if ((h->LineNmbr == LineNr) && (lstrcmp (x,h->FName) == 0)) return TRUE ;
    }
  return FALSE ;
  }

void DelBreakPoint (int LineNr,LPSTR fName)
  {
  LPSTR x = GetFName (fName);
  BPInfo FAR *prev = NULL ;
  for (BPInfo FAR *h = FirstBP; h != NULL ; h = h->Next) {
    if ((h->LineNmbr == LineNr) && (lstrcmp (x,h->FName) == 0)) {
      ClearDDSBreak (h);
      if (prev != NULL) prev->Next = h->Next ;
      else              FirstBP = h->Next ;
      FreeGlobMem (h->pOffs);
      FreeGlobMem (h);
      break ;
      }
    prev = h ;
    }
  }
BPInfo FAR *GetBPInfo(int Nr)
  {
  int i = 0 ;
  for (BPInfo FAR *h = FirstBP; h != NULL ; h = h->Next , i ++ ) {
    if (i == Nr) return h ;
    }
  return NULL ;
  }
BOOL TryToSetBreakPoint (ScDebugInfo FAR *sd,int LineNmbr,LPSTR fName)
  {
  if (sd->hGDInfo) {
    DWORD OffsToBreak[256];
    int AnzFound = 0;
    int IncNmbr = sd->GetIncNmbr (fName);
    if (IncNmbr >= 0) {
      for (DWORD i = 0 ; i < sd->AnzFuncs ; i++) {
        ScriptDebugInfo FAR *s = sd->GetSDI(i);
        if ((LineNmbr == s->LineNmbr) && (IncNmbr == s->IncNmbr))
          OffsToBreak[AnzFound++] = s->progOffs;
          }
      if (AnzFound > 0) {
        PushToBPList (fName,sd->ProgName,LineNmbr,OffsToBreak,AnzFound,EM_LOAD | EM_UPDATE | EM_RESET | EM_CLEAR);
        return TRUE ;
        }
      }
    return FALSE ;
    }
  else
    return FALSE ;
  }
BOOL ScDebugInfo::SetBreakPoint (int LineNmbr,LPSTR fName)
  {
  if (fName == NULL) return FALSE ;
  if (IsBreakLine (LineNmbr,fName)) {
    DelBreakPoint (LineNmbr,fName);
    return TRUE ;
    }
  else {
    if (TryToSetBreakPoint (this,LineNmbr,fName)) return TRUE ;
    // Durchsuchen aller offenen Files 
    HWND hwndT;
    ScDebugInfo FAR *res;
    BOOL Found = FALSE ;
    for (hwndT = GetWindow(hwndMDIClient, GW_CHILD) ; hwndT ; ) {
      // Skip the icon title windows 
      while (hwndT && GetWindow(hwndT, GW_OWNER))
        hwndT = GetWindow(hwndT, GW_HWNDNEXT);
      if (hwndT) {
        // Durchsuchen, ob das vielleich das richtige ist
        res = GetDebugInfoFromWindow (hwndT,fName,&Found,TRUE);
        if (Found) {
          if (TryToSetBreakPoint (res,LineNmbr,fName)) return TRUE ;
          }
        hwndT = GetWindow (hwndT, GW_HWNDNEXT);  
        }
      }
    return FALSE ;
    }
  }

LONG ScDebugInfo::GetLineFromAddress (DWORD progOffs,LPSTR sName)
  {
  if (progOffs == 0L) return -1;
  LONG fault = 1000000L;
  LONG res = -1;
  for (DWORD i = 0 ; i < AnzFuncs ; i++) {
    ScriptDebugInfo FAR *s = GetSDI(i);
    LONG nFault = LONG(s->progOffs) - LONG(progOffs);
    if (nFault < 0) nFault = -nFault ;
    if (nFault < fault) {
      if (sName != NULL)
        lstrcpy (sName,hd->ent[s->IncNmbr].FName);
      res = LONG(s->LineNmbr);
      fault = nFault;
      }
    }
  return res;
  }

extern LPSTR IniFile();
int AnzIniRead ;
void DestroyBreakList ()
  {
  for ( int i = 0 ; FirstBP != NULL ; i++) {
    BPInfo FAR *Next = FirstBP->Next ;
    LPSTR text = FirstBP->GetIniString ();
    char iname[32];
    wsprintf (iname,"DebugBreak%d",i);
    WritePrivateProfileString ("Debug",iname,text,IniFile());
    FreeGlobMem (text);
    ClearDDSBreak (FirstBP);
    FreeGlobMem (FirstBP->pOffs);
    FreeGlobMem (FirstBP);
    FirstBP = Next ;
    }
  for ( ; i < AnzIniRead ; i++) {
    char iname[32];
    wsprintf (iname,"DebugBreak%d",i);
    WritePrivateProfileString ("Debug",iname,"",IniFile());
    }
  }

LPSTR GetStringPart (LPSTR h,LPSTR nbuff)
  {
  BOOL ready = FALSE ;
  for ( LPSTR r = nbuff ; !ready ; ) {
    switch (*h) {
      case ',' :
        ready = TRUE ;
        h ++ ;
        *r = '\0' ;
        break ;
      case '\0' :
        ready = TRUE ;
        *r = '\0' ;
        break ;
      default :
        *r++ = *h++ ;
      }
    }
  return h ;
  }

void LoadBreakList ()
  {
  for ( int i = 0 ; ; i++) {
    char InString [1024];
    char iname[32];
    wsprintf (iname,"DebugBreak%d",i);
    if (GetPrivateProfileString ("Debug",iname,"",InString,sizeof(InString),IniFile())) {
      char pname[40],fname[40],nbuff[30];
      int LineNmbr;
      DWORD offs[64];
      LPSTR h = GetStringPart (InString,pname);
      h = GetStringPart (h,fname);
      h = GetStringPart (h,nbuff);
      sscanf (nbuff,"%d",&LineNmbr);
      for ( int AnzOffs = 0 ; ; ) {
        h = GetStringPart (h,nbuff);
        sscanf (nbuff,"%ld",&offs[AnzOffs]);
        AnzOffs ++ ;
        if (*h == '\0') break ;
        }
      PushToBPList (fname,pname,LineNmbr,offs,AnzOffs - 1,WORD(offs[AnzOffs-1]));
      }
    else
      break ;
    }
  AnzIniRead = i ;
  }

void SetBreakList ()
  {
  for (BPInfo FAR *h = FirstBP; h != NULL ; h = h->Next)
    SetDDSBreak (h);
  }

BOOL InvlidateBreakLine (HWND hWnd,LPSTR FName,int LineNmbr);
void InvalidateBreakLine (BPInfo FAR *h)
  {
  for (HWND hwndT = GetWindow(hwndMDIClient, GW_CHILD) ; hwndT ; ) {
    // Skip the icon title windows 
    while (hwndT && GetWindow(hwndT, GW_OWNER))
      hwndT = GetWindow(hwndT, GW_HWNDNEXT);
    if (hwndT) {
      // Durchsuchen, ob das vielleich das richtige ist
      if (InvlidateBreakLine (hwndT,h->FName,h->LineNmbr)) break ;
      hwndT = GetWindow (hwndT, GW_HWNDNEXT);  
      }
    }
  }

void DestroyBreakPointsFrom (LPSTR Name)
  {
  LPSTR x = GetFName (Name);
  BPInfo FAR *prev = NULL ;
  for (BPInfo FAR *h = FirstBP; h != NULL ; ) {
    BPInfo FAR *Next = h->Next;
    if (lstrcmp (x,h->FName) == 0) {
      InvalidateBreakLine (h);
      ClearDDSBreak (h);
      if (prev != NULL) prev->Next = h->Next ;
      else              FirstBP = h->Next ;
      FreeGlobMem (h->pOffs);
      FreeGlobMem (h);
      }
    else
      prev = h ;
    h = Next;
    }
  }

/*-----< Watch - Window >--------*/
void DivideVarName (LPSTR VarName,LPSTR TableName,LPSTR PartName)
  {
  int state = 0 ;
  LPSTR t = TableName ;
  LPSTR p = PartName ;
  for (LPSTR h = VarName ; *h ; h++) {
    switch (state) {
      case 0 :  // Kopieren der Tabelle
        if (*h) {
          if (*h == '.') state = 1 ;
          else           *t++ = *h ;
          }
        break ;
      case 1 :
        if (*h) {
          if (*h == '.') *h = '\0';   // so nicht
          else           *p++ = *h ;
          }
        break ;
      }
    }
  *t = '\0';
  *p = '\0';
  if (state == 0) {
    // Keinen Punkt gefunden
    lstrcpy (PartName,VarName);
    *TableName = '\0';
    }
  }

BOOL IsLocal (LPSTR PartName,WORD FAR *TableNr,WORD FAR *VarNr,WORD FAR *mType,ScDebugInfo FAR *scdeb,DWORD fOffs)
  {
  // Zuerst nur die Funktions - lokalen Variable ansehen
  for (LocalVarInfo FAR *lvi = scdeb->GetLVI(); lvi != NULL ; lvi = scdeb->GetNextLVI()) {
    if ((lstrcmp (PartName,lvi->Name) == 0) && (lvi->fOffs == fOffs)) {
      *TableNr = lvi->TableNr ;
      *VarNr = lvi->VarNr ;
      *mType = lvi->mType ;
      return TRUE ;
      }
    }
  // Dann erst die lokalen Variablen ansehen
  for (lvi = scdeb->GetLVI(); lvi != NULL ; lvi = scdeb->GetNextLVI()) {
    if ((lstrcmp (PartName,lvi->Name) == 0) && (lvi->fOffs == 0L)) {
      *TableNr = lvi->TableNr ;
      *VarNr = lvi->VarNr ;
      *mType = lvi->mType ;
      return TRUE ;
      }
    }
  return FALSE ;
  }

BOOL IsThereTheVar (LPTABLEDEF td,LPSTR PartName,WORD FAR *VarNr,WORD FAR *mType)
  {
  BOOL found ;
  *VarNr = td->GetVarID (PartName,mType,&found);
  return found ;
  }

BOOL TryInThisFile (ScDebugInfo FAR *sd,LPSTR fName)
  {
  if ((sd->hGDInfo) && (sd->GetIncNmbr (fName) >= 0)) return TRUE ;
  else                                                return FALSE ;
  }
ScDebugInfo FAR *FindDebugInfo (LPSTR fName)
  {
  if (fName == NULL) return FALSE ;
  // Durchsuchen aller offenen Files 
  HWND hwndT;
  ScDebugInfo FAR *res;
  BOOL Found = FALSE ;
  for (hwndT = GetWindow(hwndMDIClient, GW_CHILD) ; hwndT ; ) {
    // Skip the icon title windows 
    while (hwndT && GetWindow(hwndT, GW_OWNER))
      hwndT = GetWindow(hwndT, GW_HWNDNEXT);
    if (hwndT) {
      // Durchsuchen, ob das vielleich das richtige ist
      res = GetDebugInfoFromWindow (hwndT,fName,&Found,FALSE);
      if ((Found) && (res != NULL)) {
        if (TryInThisFile (res,fName)) return res ;
        }
      hwndT = GetWindow (hwndT, GW_HWNDNEXT);  
      }
    }
  return NULL ;
  }

BOOL GetVarInfo (LPSTR VarName,LPSTR Scope,WORD FAR *TableNr,WORD FAR *VarNr,WORD FAR *mType,ScDebugInfo FAR *scdb,LPTABLEDEF FAR *lptd,LPVOID Context)
  {
  *lptd = NULL ;
  *TableNr = 0xFFFF;
  if (scdb == NULL) scdb = FindDebugInfo (Scope);
  DWORD fOffs;
  if (Context != NULL) {
    fOffs = GetFuncFOffs (Context);
    }
  else
    fOffs = 0L;
  char ProgName[13];
  if (scdb == NULL)
    lstrcpy (ProgName,Scope);
  else
    lstrcpy (ProgName,scdb->ProgName);

  // Untersuchen, ob Varname voll qualifiziert ist
  char TableName[128],TableName1[128];
  char PartName[128];
  DivideVarName (VarName,TableName,PartName);
  GetPrefix (TableName1,ProgName);
  lstrcat (TableName1,TableName);

  // Laden des Scriptheaders
  LoadScriptContent ();
  LPSCRIPTCONTENT schd = NULL;
  if (ProgName[0] == '%')
    AddScriptEntry(ProgName, (LPSCRIPTCONTENT) GetScriptHd (ProgName));
  schd = GetScriptEntry(ProgName);
  if (schd != NULL) {
    if ((*TableName == '\0') && (scdb != NULL)) {
      // Zuerst untersuchen, ob eine ganze Tabelle gemeint sein koennte
      BOOL dobreak = FALSE ;
      char PrefixPart[128];
      GetPrefix (PrefixPart,ProgName);
      lstrcat (PrefixPart,PartName);
      for (int i = 0 ; ((i < int (schd->AnzTables)) && (!dobreak)) ; i++) {
            LPTABLEDEF td = GetTableAdmin()->GetTableDef(schd->TRef[i].TableNr,schd->TRef[i].Version);
            if (td == NULL) continue ;
            if ((td != NULL) && (
                  (lstrcmp (td->GetName(),PartName) == 0) ||
                  (lstrcmp (td->GetName(),PrefixPart) == 0))) {
              *lptd = td ;
              *TableNr = WORD(i+CSYSRECS);
              dobreak = TRUE ;
              }
            else if (td != NULL)
              GetTableAdmin()->FreeTable (schd->TRef[i].TableNr,schd->TRef[i].Version);
            }
      LPALIASDEF a = schd->AliasDef ;
      for (i = 0 ; ((i < int (schd->AnzAlias)) && (!dobreak)) ; i++) {
              if (lstrcmp (a->AliasName,PartName) == 0) {
                LPTABLEDEF td = GetTableAdmin()->GetTableDef(schd->TRef[a->TableNr].TableNr,schd->TRef[a->TableNr].Version);
                if (td == NULL) continue ;
                *lptd = td ;
                *TableNr = WORD(a->TableNr+CSYSRECS);
                dobreak = TRUE ;
                }
              a = a->Next();
              }
      }
    // Untersuchen, ob es sich um eine lokale Variable oder um eine Helpvariable
    // handelt
    if ((*lptd == NULL) && (!((*TableName == '\0') && (scdb != NULL) && (IsLocal (PartName,TableNr,VarNr,mType,scdb,fOffs))))) {
      // Laden des Scriptheaders
      BOOL dobreak = FALSE ;
      LPALIASDEF a = schd->AliasDef ;
      for (int i = 0 ; ((i < int (schd->AnzAlias)) && (!dobreak) && (*TableName)) ; i++) {
        if (lstrcmp (a->AliasName,TableName) == 0) {
          BOOL parentEnd = FALSE ;
          for ( WORD TNr = a->TableNr ; ((!parentEnd) && (!dobreak)) ; ) {
            LPTABLEDEF td = GetTableAdmin()->GetTableDef(schd->TRef[TNr].TableNr,schd->TRef[TNr].Version);
            if (td != NULL) {
              if (IsThereTheVar (td,PartName,VarNr,mType)) {
                *TableNr = WORD(TNr + CSYSRECS);
                dobreak = TRUE ;
                }
              GetTableAdmin()->FreeTable (schd->TRef[TNr].TableNr,schd->TRef[TNr].Version);
              if (td->GetParentID() != 0) TNr ++ ;
              else                        parentEnd = TRUE ;
              }
            else
              parentEnd = TRUE ;
            }
          }
        a = a->Next();
        }
      for (i = 0 ; ((i < int (schd->AnzTables)) && (!dobreak)) ; i++) {
        BOOL parentEnd = FALSE ;
        BOOL NameEqual = FALSE;
        for ( WORD TNr = i ; ((!parentEnd) && (!dobreak)) ; ) {
          LPTABLEDEF td = GetTableAdmin()->GetTableDef(schd->TRef[TNr].TableNr,schd->TRef[TNr].Version);
          if (td != NULL) {
            if ((TNr == WORD (i)) &&
                (*TableName != '\0') &&
                (lstrcmp (td->GetName(),TableName) != 0) &&
                (lstrcmp (td->GetName(),TableName1) != 0))
              parentEnd = TRUE;
            if (!parentEnd) {
              if (IsThereTheVar (td,PartName,VarNr,mType)) {
                *TableNr = WORD(TNr+CSYSRECS);
                dobreak = TRUE ;
                }
              if (td->GetParentID() == 0) 
                parentEnd = TRUE ;
              }
            GetTableAdmin()->FreeTable(schd->TRef[TNr].TableNr,schd->TRef[TNr].Version);
            TNr ++ ;
            }
          else
            parentEnd = TRUE ;
          }
        }
      }
    }
  return (*TableNr != 0xFFFF);
  }

BOOL GetVarInfo_Table (LPSTR VarName,LPSTR Scope,WORD FAR *TableNr,WORD FAR *VarNr,WORD FAR *mType,ScDebugInfo FAR *scdb,LPTABLEDEF td,WORD StartTableNr)
  {
  if (scdb == NULL) scdb = FindDebugInfo (Scope);
  char ProgName[13];
  if (scdb == NULL)
    lstrcpy (ProgName,Scope);
  else
    lstrcpy (ProgName,scdb->ProgName);
  *VarNr = 0xFFFF ;
  if (IsThereTheVar (td,VarName,VarNr,mType)) 
    *TableNr = StartTableNr;
  else if (td->GetParentID() != 0) {
    *TableNr = 0xFFFF ;
    // Laden des Scriptheaders
    LoadScriptContent ();
    LPSCRIPTCONTENT schd = NULL;
    if (ProgName[0] == '%')
      AddScriptEntry(ProgName, (LPSCRIPTCONTENT) GetScriptHd (ProgName));
    schd = GetScriptEntry(ProgName);
    if (schd != NULL) {
      BOOL dobreak = FALSE ;
      for ( WORD TNr = StartTableNr - CSYSRECS; (!dobreak) ; ) {
        TNr ++ ; // StartTableNr wurde vorher bereits ueberprueft
        LPTABLEDEF td = GetTableAdmin()->GetTableDef(schd->TRef[TNr].TableNr,schd->TRef[TNr].Version);
        if (td != NULL) {
          if (IsThereTheVar (td,VarName,VarNr,mType)) {
            *TableNr = WORD(TNr+CSYSRECS);
            dobreak = TRUE ;
            }
          if (td->GetParentID() == 0) 
            dobreak = TRUE ;
          GetTableAdmin()->FreeTable(schd->TRef[TNr].TableNr,schd->TRef[TNr].Version);
          }
        else
          dobreak = TRUE ;
        }
      }
    }
  return (*TableNr != 0xFFFF);
  }

void GetWatchOutText (ScDebugInfo FAR *scdb,LPSTR VarName,LPSTR OutTxt);

struct FAR FVLine {
  FVLine *Next;
  LPSTR Text ;
  LPVOID ExtraInfo;
  BOOL IsExpanded;
  };

class FAR FastView {
 public :
  int charheight ;
  HWND hParent ;
  FVLine *FirstLine,*ActLine;
  FastView (HWND h)
    { hParent = h ; }
  ~FastView ();
  void AddLineAtStart (LPSTR Text,LPVOID Extra = NULL,int extraSize = 0);
  void AddLineAtEnd (LPSTR Text,LPVOID Extra = NULL,int extraSize = 0);
  void AddLineBehind (LPSTR Text,LPVOID Extra = NULL,int extraSize = 0,LPVOID CmdData = NULL);
  void GetRect (HWND hParent,LPRECT rc);

  LPVOID operator new (size_t size)
    { return GetGlobMem (size) ; }
  void operator delete (LPVOID obj)
    { FreeGlobMem (obj) ; }
  };
typedef FastView FAR *LPFASTVIEW;

FastView::~FastView ()
  {
  for ( ; FirstLine != NULL ; ) {
    FVLine FAR *Next = FirstLine->Next;
    FreeGlobMem (FirstLine->Text);
    if (FirstLine->ExtraInfo) 
      FreeGlobMem (FirstLine->ExtraInfo);
    FreeGlobMem (FirstLine);
    FirstLine = Next ;
    }
  }

void FastView::AddLineAtStart (LPSTR Text,LPVOID extra,int extraSize)
  {
  FVLine FAR *n = (FVLine FAR *) GetGlobMem (sizeof(*n));
  n->Next = FirstLine ;
  FirstLine = n;
  n->Text = LPSTR (GetGlobMem (lstrlen(Text)+1));
  lstrcpy (n->Text,Text);
  if (extra != NULL) {
    n->ExtraInfo = GetGlobMem (extraSize);
    lmemcpy (n->ExtraInfo,extra,extraSize);
    }
  }

void FastView::AddLineAtEnd (LPSTR Text,LPVOID extra,int extraSize)
  {
  FVLine FAR *n = (FVLine FAR *) GetGlobMem (sizeof(*n));
  n->Next = NULL;
  if (FirstLine == NULL)
    FirstLine = n;
  else {
    for (FVLine FAR *h = FirstLine ; ; h = h->Next) {
      if (h->Next == NULL) {
        h->Next = n;
        break ;
        }
      }
    }
  n->Text = LPSTR (GetGlobMem (lstrlen(Text)+1));
  lstrcpy (n->Text,Text);
  if (extra != NULL) {
    n->ExtraInfo = GetGlobMem (extraSize);
    lmemcpy (n->ExtraInfo,extra,extraSize);
    }
  }

void FastView::AddLineBehind (LPSTR Text,LPVOID extra,int extraSize,LPVOID CmpData)
  {
  FVLine FAR *n = (FVLine FAR *) GetGlobMem (sizeof(*n));
  n->Next = NULL;
  if (FirstLine == NULL)
    FirstLine = n;
  else {
    for (FVLine FAR *h = FirstLine ; ; h = h->Next) {
      if ((h->ExtraInfo != NULL) && (GetBlockSize(h->ExtraInfo) == GetBlockSize(CmpData)) &&
          (lmemcmp(h->ExtraInfo,CmpData,GetBlockSize(h->ExtraInfo)))) {
        n->Next = h->Next ;
        h->Next = n ;
        break ;
        }
      if (h->Next == NULL) {
        h->Next = n;
        break ;
        }
      }
    }
  n->Text = LPSTR (GetGlobMem (lstrlen(Text)+1));
  lstrcpy (n->Text,Text);
  if (extra != NULL) {
    n->ExtraInfo = GetGlobMem (extraSize);
    lmemcpy (n->ExtraInfo,extra,extraSize);
    }
  }

void FastView::GetRect (HWND hParent,LPRECT rc)
  {
  RECT rcp;
  GetClientRect (hParent,&rcp);
  charheight = 0 ;
  HDC hDC = CreateDC("DISPLAY",NULL,NULL,NULL);
  int xmax = 0;
  int AnzLines = 0;
  for (FVLine FAR *h = FirstLine ; h != NULL ; h = h->Next) {


    int cx, cy;
#ifdef WIN32
    SIZE size;
          GetTextExtentPoint32 (hDC,h->Text,lstrlen(h->Text), &size);
          cx = size.cx;
          cy = size.cy;
#else
    DWORD dwExt = GetTextExtent (hDC,h->Text,lstrlen(h->Text));
    cx = LOWORD(dwExt);
    cy = HIWORD(dwExt);
#endif

    if (charheight == 0) charheight = cy;
    if (cx > (WORD) xmax) xmax = cx;
    AnzLines += 1 ;
    }
  DeleteDC (hDC);

  SetRect (rc,0,0,xmax,charheight * AnzLines);
  InflateRect (rc,15,15);
  int dx = rcp.right / 2 - (rc->right - rc->left) / 2;
  int dy = rcp.bottom / 2 - (rc->bottom - rc->top) / 2;

  POINT pt;
  pt.x = rc->left ;
  pt.y = rc->top;
  ClientToScreen (hParent,&pt);

  OffsetRect (rc,dx,dy);
  OffsetRect (rc,pt.x,pt.y);
  }

extern HWND hwndFrame;
static LPVOID SelectedData;
void Expand (HWND hWnd,LPVOID ExtraData,LPFASTVIEW fv);
LPFASTVIEW lpfact ;
void Fill (HWND hDlg)
  {
  if (lpfact != NULL) {
    for (FVLine FAR *h = lpfact->FirstLine ; h != NULL ; h = h->Next)
      SendDlgItemMessage (hDlg,100,LB_ADDSTRING,0,LONG(h->Text));
    }
  SelectedData = NULL ;
  }

DLLExport BOOL _export FAR PASCAL WatchProc (HWND hDlg,unsigned msg,WPARAM wP,LONG lP)
  {
  switch (msg) {
    case WM_INITDIALOG :
      {
      LPFASTVIEW fv = lpfact = LPFASTVIEW (lP);
      Fill (hDlg);
      return TRUE ;
      }
      break ;
    case WM_COMMAND :
      {
      CRACKER_VARS
      CRACK_MESSAGEsc

      switch (CRACKER_wID) {
              case IDCANCEL :
                delete lpfact ;
                EndDialog (hDlg,CRACKER_wID);
                break ;

              case IDOK :
                {
                int Id = int (SendDlgItemMessage (hDlg,100,LB_GETCURSEL,0,0L));
                lpfact->ActLine = NULL ;
                FVLine FAR * h = lpfact->FirstLine ;
                for (int i = 0 ; ((i < Id) && (h != NULL)) ; i++) {
                  h = h->Next ;
                  }
                lpfact->ActLine = h ;
                if ((lpfact->ActLine != NULL) && (lpfact->ActLine->ExtraInfo != NULL)) {
                  SelectedData = GetGlobMem (GetBlockSize(lpfact->ActLine->ExtraInfo));
                  lmemcpy (SelectedData,lpfact->ActLine->ExtraInfo,GetBlockSize(lpfact->ActLine->ExtraInfo));
                  }
                delete lpfact ;
                EndDialog (hDlg,CRACKER_wID);
                }
                break ;
              case 100 :
                if (CRACKER_wNotify == LBN_DBLCLK) {
                  int Id = int (SendDlgItemMessage (hDlg,100,LB_GETCURSEL,0,0L));
                  lpfact->ActLine = NULL ;
                  FVLine FAR* h = lpfact->FirstLine ;
                  for (int i = 0 ; ((i < Id) && (h != NULL)) ; i++) {
                    h = h->Next ;
                    }
                  lpfact->ActLine = h ;
                  if ((lpfact->ActLine != NULL) && (lpfact->ActLine->ExtraInfo != NULL) &&
                              (!lpfact->ActLine->IsExpanded)) {
                    lpfact->ActLine->IsExpanded = TRUE ;
                    Expand (hDlg,lpfact->ActLine->ExtraInfo,lpfact);
                    SendDlgItemMessage (hDlg,100,LB_RESETCONTENT,0,0L);
                    Fill (hDlg);
                    SendDlgItemMessage (hDlg,100,LB_SETCURSEL,Id,0L);
                    }
                  else {
                    SendDlgItemMessage (hDlg,IDOK,WM_COMMAND,0,0L);
                    }
                  }
                break ;
              }
      return TRUE ;
      break ;
      }
    }
  return FALSE;
  }

void CreateWatchWindow (HWND hParent,LPFASTVIEW fv,BOOL withOk)
  {
  RECT rc;
  fv->GetRect (hParent,&rc);
  DWORD dbu = GetDialogBaseUnits ();
  int x = rc.left   * 4 / LOWORD(dbu) ;
  int y = rc.bottom * 8 / HIWORD(dbu) ;
  int dx = (rc.right - rc.left) * 4 / LOWORD(dbu) ;
  int dy = (rc.bottom - rc.top) * 8 / HIWORD(dbu) ;
  dx += 10 ;
  dy += 34 ;
  int dxmin;
  if (withOk) dxmin = 85 ;
  else        dxmin = 45 ;
  if (dx < dxmin) dx = dxmin ;

  DlgContainer dc (DialogBoxHeader (WS_DLGFRAME | DS_MODALFRAME | 
                                    WS_POPUP | 
                                    WS_SYSMENU | WS_VISIBLE | 
                                    WS_CLIPSIBLINGS,
                                    x,y,dx,dy, "Caption"));
  dc += ControlData (5,dy - 19,35,14,IDCANCEL,
                     WS_GROUP | BS_DEFPUSHBUTTON | 
                     WS_TABSTOP | WS_VISIBLE | WS_CHILD,
                     0x80,
                     "Zurück");
  if (withOk) {
    dc += ControlData (45,dy - 19,35,14,IDOK,
                     WS_GROUP | BS_DEFPUSHBUTTON | 
                     WS_TABSTOP | WS_VISIBLE | WS_CHILD,
                     0x80,
                     "Zu Zeile");
    }
  dc += ControlData (5,5,dx-10,dy-34,100,
                      WS_VISIBLE | WS_CHILD | LBS_NOTIFY | WS_GROUP | WS_VSCROLL | WS_TABSTOP | LBS_HASSTRINGS, 
                      0x83, ""
                    );

#ifdef WIN32
  LPDLGTEMPLATE lpTemplate = (LPDLGTEMPLATE)GlobalLock (dc.res);
  DialogBoxIndirectParam (MyInstance, lpTemplate, hParent, DLGPROC(WatchProc), LPARAM(fv));
  GlobalUnlock (dc.res);
#else
  DialogBoxIndirectParam (MyInstance, dc.res, hParent, DLGPROC(WatchProc),LPARAM(fv));
#endif
  }

void ShowQuickWatch (HWND hParent,LPSTR VarName,LPSTR OutTxt)
  {
  LPSTR res = PushString (NULL,VarName);
  res = PushString (res," = ");
  res = PushString (res,OutTxt);

  LPFASTVIEW fv = new FastView (hParent);
  fv->AddLineAtStart (res);
  FreeGlobMem (res);

  CreateWatchWindow (hParent,fv,FALSE);
  }

extern int DDSStatus ;
extern char ActiveBreakModule[];
extern int  ActiveBreakLine;
#define DDSSTATUS_BREAKDONE   1

void WatchVar (ScDebugInfo FAR *scdb,HWND hWParent,LPSTR VarName,LPSTR res)
  {
  HWND hDDSWnd;
  if ((DDSStatus == DDSSTATUS_BREAKDONE) && (hDDSWnd = GetDDSMainWnd ())) {
    char OutTxt[1024];
    GetWatchOutText (scdb,VarName,OutTxt);
    if (res != NULL)
      lstrcpy (res, OutTxt);
    else
      ShowQuickWatch (hWParent,VarName,OutTxt);
    }
  else {
    if (res != NULL)
      strcpy (res, "???");
    else
      MessageBeep (0);
    }
  }

struct RSStackInfo {
  char FName[13];
  int LineNmbr;
  DWORD Id;
  };
void PushStackLine (LPFASTVIEW fv,LPSTR sName,int LineNmbr,DWORD Id)
  {
  char szLNmbr[20];
  LPSTR res = PushString (NULL,sName);
  res = PushString (res," : ");
  wsprintf (szLNmbr,"%d",LineNmbr);
  res = PushString (res,szLNmbr);
  RSStackInfo rss;
  lstrcpy (rss.FName,sName);
  rss.LineNmbr = LineNmbr;
  rss.Id = Id;
  fv->AddLineAtStart (res,&rss,sizeof(rss));
  FreeGlobMem (res);
  }

void TryToSetContext (DWORD Id);
void WatchStack (HWND hWParent)
  {
  HWND hDDSWnd;
  if ((DDSStatus == DDSSTATUS_BREAKDONE) && (hDDSWnd = GetDDSMainWnd ())) {
    LPFASTVIEW fv = new FastView (hWParent);
    for (int i = 0 ; ; i++) {
      CallStackInfo csi;
      if (!SendMessage (hDDSWnd,WMC_GETSTACKINFO,WORD(i),RSetData(&csi,sizeof(csi))))
        break ;
      RGetData (&csi,sizeof(csi));
      char sName[13];
      lstrcpy (sName,csi.ProgName);
      LONG LineNmbr = SearchModuleLine (hWParent,&csi,sName,TRUE);
      PushStackLine (fv,sName,int(LineNmbr),DWORD(csi.c));
      }
    fv->ActLine = fv->FirstLine;
    CreateWatchWindow (hWParent,fv,TRUE);

    if (SelectedData != NULL) {
      RSStackInfo FAR *rsi = (RSStackInfo FAR *) SelectedData;
      if (rsi->LineNmbr > 0) {
        SetModuleActive (rsi->FName,rsi->LineNmbr);
        }
      TryToSetContext (rsi->Id);
      FreeGlobMem (SelectedData);
      }
    }
  else
    MessageBeep (0);
  }

struct ULInfo {
  RSStackInfo rss;
  int Nmbr;
  };

void PushUpdateLine (int Nmbr,HWND hWParent,FastView FAR *fv,DebFifoInfo FAR *dfi,LPVOID Extra)
  {
  char lstr[20];
  CallStackInfo csi;
  char sName[13];
  lstrcpy (csi.ProgName,dfi->ModuleName);
  lstrcpy (sName,csi.ProgName);
  csi.progOffs = dfi->CmdOffset;
  int LineNmbr;
  if (*csi.ProgName)
    LineNmbr = int (SearchModuleLine (hWParent,&csi,sName,TRUE));
  else
    LineNmbr = -1;

  ULInfo ui;
  lstrcpy (ui.rss.FName,sName);
  ui.rss.LineNmbr = LineNmbr;
  ui.Nmbr = Nmbr;
  ui.rss.Id = DWORD(csi.c);

  LPSTR res;
  if (Nmbr == -1)
    res = PushString (NULL,"[");
  else {
    if (Extra != NULL)
      res = PushString (NULL,"  ");
    else
      res = NULL;
    }
  if (*dfi->ModuleName) {
    res = PushString (res,dfi->ModuleName);
    wsprintf (lstr," %d (",LineNmbr);
    res = PushString (res,lstr);
    }
  else {
    res = PushString (res,"??? ");
    }
  BOOL first = TRUE ;
  for (int i = 0 ; i < dfi->AnzVars ; i++) {
    char TableName[64],VarName[64];
    TableName[0] = '\0';
    VarName[0] = '\0';

    WORD TableID = dfi->Var[i].tRef.TableNr;
    WORD Version = dfi->Var[i].tRef.Version;
    WORD VarID = dfi->Var[i].VarNr;
    if (((TableID == 0xFFFE) || (TableID == 0xFFFF)) && (*dfi->Var[i].Scope)) {
      // Versuch, die Variable als Lokale Variable zu indentifieren
      if (TableID == 0xFFFE) TableID = 0;
      if (TableID == 0xFFFF) TableID = 1;
      BOOL found = FALSE ;
      ScDebugInfo FAR *sdeb = FindDebugInfo (dfi->Var[i].Scope);
      if (sdeb != NULL) {
        for (LocalVarInfo FAR *lvi = sdeb->GetLVI(); ((lvi != NULL) && (!found)) ; lvi = sdeb->GetNextLVI()) {
          if ((lvi->VarNr == VarID) && (lvi->TableNr == TableID)) {
            lstrcpy (VarName,lvi->Name);
            lstrcpy (TableName,dfi->Var[i].Scope);
            lstrcat (TableName,"::");
            found = TRUE ;
            }
          }
        }
      }
    else if (TableID < 0xFFFE) {
      // Die Variable kann ganz normal gehandhabt werden
      LPTABLEDEF td = GetTableAdmin()->GetTableDef(TableID,Version);
      if (td != NULL) {
        lstrcpy (TableName,td->GetName());
        lstrcat (TableName,".");
        LPVARDEF v = td->GetVarDef (VarID);
        if (v != NULL)
          lstrcpy (VarName,v->GetName());
        GetTableAdmin()->FreeTable(TableID,Version);
        }
      }
    if (!first)
      res = PushString (res,",");
    if (lstrlen (res) > 90) {
      res = PushString (res,"...");
      break ;
      }
    else {
      if ((TableName[0]) && (VarName[0])) {
        res = PushString (res,TableName);
        }
      if (VarName[0]) {
        res = PushString (res,VarName);
        }
      first = FALSE ;
      }
    }
  res = PushString (res,")");
  if (Nmbr == -1)
    res = PushString (res,"]");

  if (Extra == NULL)
    fv->AddLineAtEnd (res,&ui,sizeof(ui));
  else
    fv->AddLineBehind (res,&ui.rss,sizeof(ui.rss),Extra);
  FreeGlobMem (res);
  }

void WatchUpdateList (HWND hWParent)
  {
  HWND hDDSWnd;
  if ((DDSStatus == DDSSTATUS_BREAKDONE) && (hDDSWnd = GetDDSMainWnd ())) {
    LPFASTVIEW fv = new FastView (hWParent);
    for (int i = -1 ; ; i++) {
      DebFifoInfo dfi;
      if (!SendMessage (hDDSWnd,WMC_GETCMDFIFOINFO,WORD(i),RSetData (&dfi,sizeof(dfi))))
        break ;
      RGetData (&dfi,sizeof(dfi));
      PushUpdateLine (i,hWParent,fv,&dfi,NULL);
      }
    fv->ActLine = fv->FirstLine;
    CreateWatchWindow (hWParent,fv,TRUE);

    if (SelectedData != NULL) {
      RSStackInfo FAR *rsi = (RSStackInfo FAR *) SelectedData;
      if (rsi->LineNmbr > 0)
        SetModuleActive (rsi->FName,rsi->LineNmbr);
      TryToSetContext (rsi->Id);
      FreeGlobMem (SelectedData);
      }
    }
  else
    MessageBeep (0);
  }

void Expand (HWND hWnd,LPVOID ExtraData,LPFASTVIEW fv)
  {
  HWND hDDSWnd;
  if ((GetBlockSize (ExtraData) == sizeof(ULInfo)) && (hDDSWnd = GetDDSMainWnd ())) {
    ULInfo FAR *ui = (ULInfo FAR *) ExtraData;
    for (int i = 0 ; ; i++) {
      DebFifoInfo dfi;
      WORD InfoFrom;
      InfoFrom = BYTE(ui->Nmbr) + (BYTE(i) << 8);
      if (!SendMessage (hDDSWnd,WMC_FURTHERINFO,InfoFrom,RSetData (&dfi,sizeof(dfi))))
        break ;
      RGetData (&dfi,sizeof(dfi));
      PushUpdateLine (i,GetParent(hWnd),fv,&dfi,ExtraData);
      }
    }
  else
    MessageBeep (0);
  }

/*------------< Watchlist >-------------------*/
#define WL_NORMAL     1
#define WL_TABLENAME  2
#define WL_LISTNAME   3
#define WL_LISTENTRY  4
#define WL_SUBSTRUCT  5
#define WL_SUBLIST    6

#define BREAKACTIVE "B  "
#define TABLECLOSE  "+"
#define TABLEOPEN   "-"
#define LISTCLOSE   "*+"
#define LISTOPEN    "*-"
#define ENTCLOSE    "+"
#define ENTOPEN     "-"
#define BASEENTRY   "^" // Darf nur ein Zeichen sein!
struct PrefixBuffer {
  short TypeOfEntry;
  char Prefix[5];
  LPVOID oldData;
  PrefixBuffer FAR *Next;
  };

PrefixBuffer FAR *pb;
void PushPrefix (short t,LPSTR p,LPVOID d)
  {
  PrefixBuffer FAR *n = (PrefixBuffer FAR *) GetGlobMem (sizeof(*n));
  n->TypeOfEntry = t;
  lstrcpy (n->Prefix,p);
  n->oldData = d;
  n->Next = pb;
  pb = n;
  }
void DelPrefixBuffer ()
  {
  for ( ; pb != NULL ; ) {
    PrefixBuffer FAR *n = pb->Next ;
    FreeGlobMem (pb);
    pb = n ;
    }
  }
class FAR WatchLine {
 public :
  WatchLine FAR *Next;
  WatchLine FAR *Parent;

  short TypeOfEntry;  // WL_..

  WORD VarNr;         // Nur Gueltig, wenn Parent->TypeOfEntry == WL_LISTENTRY
  WORD mType;         // --""--
  WORD TableNr;       // Nur Gueltig, wenn TypeOfEntry == WL_TABLENAME

  union ChildData {     // Daten fuer die Subeintraege
    LPTABLEDEF td;  // WL_TABLENAME
    struct {
      int AnzRecs;     // WL_LISTNAME
      LPVOID ListPtr;
      } ln;
    struct {
      int Index;
      LPDBRECORD rec; // WL_LISTENTRY
      } le;
    } cd;

  LPSTR VarName;
  LPSTR OutText;
  LPVOID _breakContext;
  char Prefix[5];
  char _breakScope[13];

  void RecalcVal (LPSTR Scope,LPVOID Context);

  WatchLine (LPSTR VName);
  WatchLine (WatchLine FAR *p,LPSTR VName);
  WatchLine (WatchLine FAR *p,LPSTR TName,LPSTR VName,WORD mType,WORD VarNr,LPVOID cdRec);
  WatchLine (WatchLine FAR *p,LPSTR VName,int Index);
  void StoreOldPrefix ()
    {
    if (TypeOfEntry == WL_LISTENTRY)
      PushPrefix (TypeOfEntry,Prefix,cd.le.rec);
    else if (TypeOfEntry == WL_LISTNAME)
      PushPrefix (TypeOfEntry,Prefix,cd.ln.ListPtr);
    }
  void TogglePrefix ()
    {
    char * prefixToToggle;
    if (*Prefix == *BASEENTRY)
      prefixToToggle = Prefix + 1;
    else
      prefixToToggle = Prefix;
    if      (lstrcmp (prefixToToggle,TABLEOPEN) == 0)  lstrcpy (prefixToToggle,TABLECLOSE);
    else if (lstrcmp (prefixToToggle,TABLECLOSE) == 0) lstrcpy (prefixToToggle,TABLEOPEN);
    else if (lstrcmp (prefixToToggle,LISTOPEN) == 0)   lstrcpy (prefixToToggle,LISTCLOSE);
    else if (lstrcmp (prefixToToggle,LISTCLOSE) == 0)  lstrcpy (prefixToToggle,LISTOPEN);
    else if (lstrcmp (prefixToToggle,ENTOPEN) == 0)    lstrcpy (prefixToToggle,ENTCLOSE);
    else if (lstrcmp (prefixToToggle,ENTCLOSE) == 0)   lstrcpy (prefixToToggle,ENTOPEN);
    }
  void GetDefaultPrefix ()
    {
    BOOL found = FALSE ;
    for ( PrefixBuffer FAR *n = pb ; n != NULL ; n = n->Next) {
      if (n->TypeOfEntry == TypeOfEntry) {
        if (((TypeOfEntry == WL_LISTENTRY) && (LPVOID (cd.le.rec) == n->oldData)) ||
              ((TypeOfEntry == WL_LISTNAME) && (LPVOID (cd.ln.ListPtr) == n->oldData))) {
          lstrcpy (Prefix,n->Prefix);
          found = TRUE ;
          }
        }
      }
    if (!found) {
      char * prefixToSet;
      if ((TypeOfEntry == WL_SUBSTRUCT) && (Parent != NULL) && (TableNr != Parent->TableNr)) {
        lstrcpy (Prefix, BASEENTRY);
        prefixToSet = Prefix + 1;
        }
      else
        prefixToSet = Prefix;
      if (TypeOfEntry == WL_LISTENTRY)
        lstrcpy (prefixToSet,ENTCLOSE);
      else if (TypeOfEntry == WL_LISTNAME) 
        lstrcpy (prefixToSet,LISTCLOSE);
      else if (TypeOfEntry == WL_TABLENAME) 
        lstrcpy (prefixToSet,TABLECLOSE);
      }
    }
  BOOL IsBreakDone ()
    {
    return (*Prefix == *BREAKACTIVE) ;
    }
  BOOL IsToBreak ()
    {
    return (*Prefix == '\0') ;
    }
  int GetLevel()
    {
    WatchLine FAR *h = this ;
    for (int i = 0 ; (h->Parent != NULL) ; h = h->Parent , i++) ;
    return i;
    }
  LPSTR FormatOutput ();
  ~WatchLine ();

  LPVOID operator new (size_t size)
    { return GetGlobMem (size); }
  void operator delete (LPVOID obj)
    { FreeGlobMem (obj); }
  };

BOOL lstrncat (LPSTR t1,LPSTR t2,int mSize)
  {
  int s1 = lstrlen(t1);
  int s2 = lstrlen(t2);
  if (s1 < mSize) {
    int maxs2 = mSize - 1 - s1 ;
    int l2 = min(s2,maxs2);
    lmemcpy (t1 + s1,t2,l2);
    t1[s1 + l2] = '\0' ;
    return TRUE ;
    }
  else
    return FALSE ;
  }
void WatchLine::RecalcVal (LPSTR _Scope,LPVOID _Context)
  {
  if (OutText != NULL) FreeGlobMem (OutText);
  OutText = NULL;
  char Txt[1024];
  LPTABLEDEF tdn;
  LPDBRECORD r = NULL;
  if ((Parent != NULL) && (Parent->TypeOfEntry == WL_TABLENAME)) {
    GetVarInfo_Table (VarName,_Scope,&TableNr,&VarNr,&mType,NULL,Parent->cd.td,Parent->TableNr);
    TypeOfEntry = WL_SUBSTRUCT ;
    }
  else if ((Parent != NULL) && (Parent->TypeOfEntry == WL_LISTNAME)) {
    TypeOfEntry = WL_LISTENTRY ;
    }
  else if ((Parent != NULL) && (Parent->TypeOfEntry == WL_LISTENTRY)) {
    r = cd.le.rec;
    TableNr = 0xFFFF ;
    TypeOfEntry = WL_SUBLIST ;
    }
  else {
    TypeOfEntry = WL_NORMAL ;
    GetVarInfo (VarName,_Scope,&TableNr,&VarNr,&mType,NULL,&tdn,_Context);
    if (tdn != NULL) {
      cd.td = tdn ;
      TypeOfEntry = WL_TABLENAME ;
      }
    }

  switch (TypeOfEntry) {
    case WL_TABLENAME :
      if (!*Prefix)
        lstrcpy (Prefix,TABLECLOSE);
      *Txt = '\0' ;
      break ;
    case WL_LISTENTRY :
      {
      BOOL IsActive;
      cd.le.rec = LPDBRECORD (GetRecordPointer (Parent->cd.ln.ListPtr,cd.le.Index,&IsActive));
      if (IsActive)
        wsprintf (Txt,"->%lX",LONG(cd.le.rec));
      else
        wsprintf (Txt,"%lX",LONG(cd.le.rec));
      TableRef tr;
      GetRecTable (cd.le.rec,&tr);
      LPTABLEDEF td = GetTableAdmin()->GetTableDef (tr.TableNr,tr.Version) ;
      for (int i = 0 ; i < int (td->GetAnzVars()) ; i++) {
        LPVOID Data = GetRecData (cd.le.rec,i);
        char Txt1[512];
        if (Data != NULL)
          FormatOutTxt (Txt1,Data,td->GetVarDef(i)->mType);
        else
          lstrcpy (Txt1,"NULL");
        if (i == 0) {
          if (!lstrncat (Txt,"=",160)) break ;
          }
        else {
          if (!lstrncat (Txt,",",160)) break ;
          }
        if (!lstrncat (Txt,Txt1,160)) break ;
        }
      GetTableAdmin()->FreeTable (tr.TableNr,tr.Version) ;
      if (!*Prefix)
        GetDefaultPrefix ();
      }
      break ;
    case WL_LISTNAME :
      WIN_ASSERT(FALSE);
      break ;
    case WL_NORMAL :
    case WL_SUBSTRUCT :
    case WL_SUBLIST :
      if ((TableNr != 0xFFFF) || (r != NULL)) {
        LPVOID data;
        if (r != NULL)
          data = GetRecData (r,VarNr);
        else
          data = GetVarValueExtended (TableNr,VarNr,_Scope,_Context);
        if (data != NULL) {
#ifdef WIN32
          if (LONG(data) == 1L) {
#else
          if (FP_SEG(data) == 0) {
#endif
            if ((TypeOfEntry == WL_SUBSTRUCT) && (Parent != NULL) && (TableNr != Parent->TableNr))
              lstrcpy (Prefix, BASEENTRY);
            else
              *Prefix = '\0';
            lstrcpy (Txt,"<not loaded>");
            }
          else {
            int count;
            char name[64];
            if (IsListPtr (data,&count,name)) {
              TypeOfEntry   = WL_LISTNAME ;
              cd.ln.ListPtr = GetGlobMem (GetBlockSize (data)) ;
              lmemcpy (cd.ln.ListPtr,data,GetBlockSize (data)) ;
              cd.ln.AnzRecs = count ;
              wsprintf (Txt," [%d] {%s}",count,LPSTR(name));
              if (!*Prefix)
                GetDefaultPrefix ();
              }
            else {
              if ((TypeOfEntry == WL_SUBSTRUCT) && (Parent != NULL) && (TableNr != Parent->TableNr))
                lstrcpy (Prefix, BASEENTRY);
              else
                *Prefix = '\0';
              FormatOutTxt (Txt,data,mType);
              }
            }
          }
        else {
          if ((TypeOfEntry == WL_SUBSTRUCT) && (Parent != NULL) && (TableNr != Parent->TableNr))
            lstrcpy (Prefix, BASEENTRY);
          else
            *Prefix = '\0';
          lstrcpy (Txt,"<NULL>");
          }
        }
      else {
        *Prefix = '\0';
        lstrcpy (Txt,"???") ;
        }
      break ;
      }

  OutText = LPSTR(GetGlobMem (lstrlen(Txt)+1));
  lstrcpy (OutText,Txt);
  }

LPSTR WatchLine::FormatOutput ()
  {
  LPSTR res = NULL ;
  int l = GetLevel();
  for (int i = 0 ; i < l ; i++)
    res = PushString (res,"   ");
  if (*Prefix)
    res = PushString (res,Prefix);
  res = PushString (res,VarName);
  if ((TypeOfEntry == WL_NORMAL) || (TypeOfEntry == WL_SUBLIST) || (TypeOfEntry == WL_SUBSTRUCT) || (TypeOfEntry == WL_LISTNAME)) {
    res = PushString (res," = ");
    if (OutText != NULL)
      res = PushString (res,OutText);
    else 
      res = PushString (res,"<no context>");
    }
  else if ((OutText != NULL) && (*OutText)) {
    res = PushString (res,OutText);
    }


  return res;
  }

WatchLine::WatchLine (LPSTR VName)
  {
  VarName = LPSTR(GetGlobMem (lstrlen(VName)+1));
  lstrcpy (VarName,VName);
  }

WatchLine::WatchLine (WatchLine FAR *p,LPSTR VName)
  {
  VarName = LPSTR(GetGlobMem (lstrlen(VName)+1));
  lstrcpy (VarName,VName);
  Parent = p ;
  }

WatchLine::WatchLine (WatchLine FAR *p,LPSTR VName,int Index)
  {
  VarName = LPSTR(GetGlobMem (lstrlen(VName)+1));
  lstrcpy (VarName,VName);
  cd.le.Index = Index ;
  Parent = p ;
  }

WatchLine::WatchLine (WatchLine FAR *p,LPSTR TName,LPSTR VName,WORD vn,WORD mt,LPVOID cdRec)
  {
  if (TName != NULL) {
    VarName = LPSTR(GetGlobMem (lstrlen(TName)+1+lstrlen(VName)+1));
    lstrcpy (VarName,TName);
    lstrcat (VarName,".");
    lstrcat (VarName,VName);
    }
  else {
    VarName = LPSTR(GetGlobMem (lstrlen(VName)+1));
    lstrcpy (VarName,VName);
    }
  VarNr = vn ;
  mType = mt ;
  Parent = p ;
  cd.le.rec = (LPDBRECORD) cdRec;
  }

WatchLine::~WatchLine ()
  {
  if (lstrcmp (Prefix,BREAKACTIVE) == 0)
    ClearVarBreak (TableNr,VarNr,_breakScope,_breakContext) ;
  if (VarName != NULL) FreeGlobMem (VarName);
  if (OutText != NULL) FreeGlobMem (OutText);
  if ((TypeOfEntry == WL_TABLENAME) && (cd.td != NULL))
    GetTableAdmin()->FreeTable(cd.td->GetTableID(),cd.td->GetTableID());
  if ((TypeOfEntry == WL_LISTNAME) && (cd.ln.ListPtr != NULL)) {
    FreeGlobMem (cd.ln.ListPtr);
    }
  }

#define GWL_WVOFFS      4
class FAR WatchView {
 public :
  WatchLine FAR *FirstLine;

  WatchView ();
  ~WatchView ();

  int AnzLines ();
  void AddLine (LPSTR VarName,ContextBuffer FAR *h);
  void AddLine (WatchLine FAR *parent,LPSTR VarName,ContextBuffer FAR *h);
  void AddLine (WatchLine FAR *parent,LPSTR TName,LPSTR VarName,WORD VarNr,WORD mTyp,ContextBuffer FAR *h,LPVOID rec);
  void AddLine (WatchLine FAR *parent,int Index,ContextBuffer FAR *h);
  void AddLineAfter (WatchLine FAR *l,WatchLine FAR *parent);
  void FillContextCombo (ContextBuffer FAR *fcnt);
  void Expand (WatchLine FAR *h,ContextBuffer FAR *c) ;
  void ExpandParent (WORD TNr, WatchLine FAR *h,ContextBuffer FAR *c, LPSCRIPTCONTENT schd) ;
  void RecalcVals (int sel = 0,ContextBuffer FAR *cntBuff = NULL);
  void SetBreak (WatchLine FAR *ActLine,LPSTR Scope,LPVOID Context);
  void ClearBreak (WatchLine FAR *ActLine);
  void DelWatch (WatchLine FAR *ActLine);
  BOOL DelSubVars (WatchLine FAR *rec);
  WatchLine FAR *GetLine (int Nr);
  int IsWatched (LPSTR VarName);
  ContextBuffer FAR *GetActiveScope ();

  LPVOID operator new (size_t size)
    { return GetGlobMem (size); }
  void operator delete (LPVOID obj)
    { FreeGlobMem (obj); }
  };

WatchView::WatchView ()
  {
  }

int WatchView::AnzLines ()
  {
  int res = 0 ;
  for (WatchLine FAR *h = FirstLine ; h != NULL ; h = h->Next)
    res ++ ;
  return res;
  }

WatchLine FAR *WatchView::GetLine (int Nr)
  {
  int i = 0 ;
  for (WatchLine FAR *h = FirstLine ; h != NULL ; h = h->Next , i ++ ) {
    if (i == Nr) return h ;
    }
  return NULL ;
  }

// static HWND actWatchDlg;
static WatchView FAR *lpActWatchView;

void GetWatchOutText (ScDebugInfo FAR *scdb,LPSTR VarName,LPSTR OutTxt)
  {
  if (scdb == NULL) {
    lstrcpy (OutTxt,"<no Debuginfo>");
    return ;
    }

  WORD TableNr,VarNr,mType;
  LPTABLEDEF td;
  ContextBuffer FAR *h;
  if (lpActWatchView == NULL)
    h = NULL;
  else {
    h = lpActWatchView->GetActiveScope();
    if (lstrcmp (h->fName, scdb->ProgName))
      h = NULL;
    }
  if (h == NULL) {
    static ContextBuffer vc;
    if (GetFirstContext (&vc))
      h = &vc;
    else
      h = NULL;
    }
  if (h == NULL)
    GetVarInfo (VarName,scdb->ProgName,&TableNr,&VarNr,&mType,scdb,&td,NULL);
  else
    GetVarInfo (VarName,h->fName,&TableNr,&VarNr,&mType,NULL,&td,h->c);

  // Aufruf der Marille zum Zwecke 
  if ((TableNr != 0xFFFF) && (td == NULL)) {
    LPVOID data = GetVarValue (TableNr,VarNr);
    if (data != NULL) {
#ifdef WIN32
      if (LONG(data) == 1L)
#else
      if (FP_SEG(data) == 0)
#endif
        lstrcpy (OutTxt,"<not loaded>");
      else
        FormatOutTxt (OutTxt,data,mType);
      }
    else
      lstrcpy (OutTxt,"<NULL>");
    }
  else
    lstrcpy (OutTxt,"???");
  }


HWND hWndContext,hWndWatchList,hWatchToolbar;
void FillWatchDlg (HWND hList,int sel = -1,int fvisible = -1)
  {
  SendMessage (hList,LB_RESETCONTENT,0,0L);
  int x0 = 20 ;
  SendMessage (hList,LB_SETTABSTOPS,1,LPARAM(LPSTR(&x0)));
  for (WatchLine FAR *h = lpActWatchView->FirstLine ; h != NULL ; h = h->Next) {
    LPSTR txt = h->FormatOutput ();
    SendMessage (hList,LB_ADDSTRING,0,LPARAM(txt));
    FreeGlobMem (txt);
    }
  if (sel < 0) sel = int(SendMessage (hList,LB_GETCOUNT,0,0L)) - 1;
  if (sel >= 0)
    SendMessage (hList,LB_SETCURSEL,sel,0L);
  if (fvisible >= 0)
    SendMessage (hList,LB_SETTOPINDEX,fvisible,0L);
  }

void WatchView::FillContextCombo (ContextBuffer FAR *fcnt)
  {
  BOOL res,first = TRUE ;
  ContextBuffer vc;
  SendMessage (hWndContext,CB_RESETCONTENT,0,0L);
  for ( res = GetFirstContext (&vc) ; res ; res = GetNextContext (&vc) ) {
    char outTxt[32];
    wsprintf (outTxt,"%lX %s",vc.c,LPSTR(vc.fName));
    SendMessage (hWndContext,CB_ADDSTRING,0,LONG(LPSTR(outTxt)));
    if (first) *fcnt = vc , first = FALSE ;
    }
  SendMessage (hWndContext,CB_SETCURSEL,0,0L);
  }

void WatchView::ExpandParent (WORD TNr, WatchLine FAR *h,ContextBuffer FAR *c, LPSCRIPTCONTENT schd)

  {
  if (schd == NULL) {
    ScDebugInfo FAR *scdb = FindDebugInfo (c->fName);
    char ProgName[13];
    if (scdb == NULL)
      lstrcpy (ProgName,c->fName);
    else
      lstrcpy (ProgName,scdb->ProgName);
    // Laden des Scriptheaders
    LoadScriptContent ();
    if (ProgName[0] == '%')
      AddScriptEntry(ProgName, (LPSCRIPTCONTENT) GetScriptHd (ProgName));
    schd = GetScriptEntry(ProgName);
    }
  if (schd != NULL) {
    LPTABLEDEF td = GetTableAdmin()->GetTableDef(schd->TRef[TNr].TableNr,schd->TRef[TNr].Version);
    if (td != NULL) {
      if (td->GetParentID() != 0) 
        ExpandParent (TNr + 1, h, c, schd);
      for (int i = 0 ; i < int (td->GetAnzVars()) ; i++)
        AddLine (h,td->GetVarDef(i)->GetName(),c);
      GetTableAdmin()->FreeTable(schd->TRef[TNr].TableNr,schd->TRef[TNr].Version);
      }
    }
  }

void WatchView::Expand (WatchLine FAR *h,ContextBuffer FAR *c) 
  {
  char * prefixToCheck;
  if (*h->Prefix == *BASEENTRY)
    prefixToCheck = h->Prefix + 1;
  else
    prefixToCheck = h->Prefix;
  if ((h->TypeOfEntry == WL_TABLENAME) && (lstrcmp (prefixToCheck,TABLEOPEN) == 0)) {   // Tabelle ist offen
    if (h->cd.td->GetParentID() != 0)
      ExpandParent (h->TableNr - CSYSRECS + 1, h, c, NULL);
    for (int i = 0 ; i < int (h->cd.td->GetAnzVars()) ; i++)
      AddLine (h,h->cd.td->GetVarDef(i)->GetName(),c);
    }
  else if ((h->TypeOfEntry == WL_LISTNAME) && (lstrcmp (prefixToCheck,LISTOPEN) == 0)) {
    for (int i = 0 ; i < h->cd.ln.AnzRecs ; i++)
      AddLine (h,i,c);
    }
  else if ((h->TypeOfEntry == WL_LISTENTRY) && (lstrcmp (prefixToCheck,ENTOPEN) == 0)) {
    BOOL firstTime;
    LPVOID cdRec;
    for (firstTime = TRUE, cdRec = h->cd.le.rec ; 
         (firstTime || ((cdRec != NULL) && (cdRec != h->cd.le.rec))); 
         GetNextInCycl (cdRec, &cdRec)) {
      TableRef tr;
      GetRecTable (cdRec,&tr);
      LPTABLEDEF td = GetTableAdmin()->GetTableDef (tr.TableNr,tr.Version);
      LPSTR tName;
      if (!firstTime) 
        tName = td->GetName();
      else
        tName = NULL;
      for (int i = 0 ; i < int (td->GetAnzVars()) ; i++)
        AddLine (h,tName,td->GetVarDef(i)->GetName(),i,td->GetVarDef(i)->mType,c,cdRec);
      GetTableAdmin()->FreeTable (tr.TableNr,tr.Version) ;
      firstTime = FALSE;
      }
    }
  }
void WatchView::RecalcVals (int sel,ContextBuffer FAR *cntBuff)
  {
  if (lpActWatchView) {
    ContextBuffer fcnt;
    if (cntBuff == NULL) {
      FillContextCombo (&fcnt);
      cntBuff = &fcnt;
      }

    for (WatchLine FAR *h = FirstLine ; h != NULL ; h = h->Next)
      h->StoreOldPrefix();
    for (h = FirstLine ; h != NULL ; h = h->Next) {
      DelSubVars (h);
      h->RecalcVal (cntBuff->fName,cntBuff->c);
      Expand (h,FALSE);        // Wieder Aufmachen, wenn noetig
      }
    DelPrefixBuffer ();

    FillWatchDlg (hWndWatchList,sel);
    }
  }

BOOL WatchView::IsWatched (LPSTR VarName)
  {
  int i = 0 ;
  for (WatchLine FAR *h = FirstLine ; h != NULL ; h = h->Next) {
    if (lstrcmp (h->VarName,VarName) == 0) return i ;
    else                                   i ++ ;
    }
  return -1 ;
  }

void WatchView::AddLine (LPSTR VarName,ContextBuffer FAR *h)
  {
  WatchLine FAR *l = new WatchLine (VarName);
  if (FirstLine == NULL) FirstLine = l;
  else {
    for (WatchLine FAR *x = FirstLine ; x != NULL ; x = x->Next) {
      if (x->Next == NULL) {
        x->Next = l;
        break ;
        }
      }
    }
  if (h != NULL)
    l->RecalcVal (h->fName,h->c);
  }

void WatchView::AddLineAfter (WatchLine FAR *l,WatchLine FAR *parent)
  {
  for ( WatchLine FAR *p = parent ; p != NULL ; ) {
    if (p->Next == NULL) {
      p->Next = l ;
      break ;
      }
    else if (p->Next->Parent != parent) {
      l->Next = p->Next ;
      p->Next = l ;
      break ;
      }
    p = p->Next ;
    }
  }
void WatchView::AddLine (WatchLine FAR *parent,LPSTR VarName,ContextBuffer FAR *h)
  {
  WatchLine FAR *l = new WatchLine (parent,VarName);
  AddLineAfter (l,parent);
  if (h != NULL)
    l->RecalcVal (h->fName,h->c);
  }
void WatchView::AddLine (WatchLine FAR *parent,LPSTR TName,LPSTR VarName,WORD VarNr,WORD mType,ContextBuffer FAR *h,LPVOID rec)
  {
  WatchLine FAR *l = new WatchLine (parent,TName,VarName,VarNr,mType,rec);
  AddLineAfter (l,parent);
  if (h != NULL)
    l->RecalcVal (h->fName,h->c);
  }
void WatchView::AddLine (WatchLine FAR *parent,int Index,ContextBuffer FAR *h)
  {
  char vname[32];
  wsprintf (vname,"[%d] ",Index);
  WatchLine FAR *l = new WatchLine (parent,vname,Index);
  AddLineAfter (l,parent);
  if (h != NULL)
    l->RecalcVal (h->fName,h->c);
  }

void WatchView::SetBreak (WatchLine FAR *ActLine,LPSTR Scope,LPVOID Context)
  {
  if (ActLine == NULL) return ;
  if ((lstrcmp (ActLine->Prefix,BREAKACTIVE) != 0) && 
        (SetVarBreak (ActLine->TableNr,ActLine->VarNr,Scope,Context))) {
    lstrcpy (ActLine->Prefix,BREAKACTIVE);
    lstrcpy (ActLine->_breakScope,Scope);
    ActLine->_breakContext = Context;
    }
  }

void WatchView::ClearBreak (WatchLine FAR *ActLine)
  {
  if (ActLine == NULL) return ;
  if ((lstrcmp (ActLine->Prefix,BREAKACTIVE) == 0) && 
        (ClearVarBreak (ActLine->TableNr,ActLine->VarNr,ActLine->_breakScope,ActLine->_breakContext))) {
    *ActLine->Prefix = '\0';
    }
  }

BOOL WatchView::DelSubVars (WatchLine FAR *rec)
  {
  BOOL res = FALSE ;
  if ((rec->TypeOfEntry == WL_TABLENAME) || (rec->TypeOfEntry == WL_LISTNAME) || (rec->TypeOfEntry == WL_LISTENTRY)) {
    WatchLine FAR *prev = rec ;
    if ((rec->Next == NULL) || (rec->Next->Parent != rec)) return FALSE ;
    for (WatchLine FAR *h = rec->Next ; h != NULL ; ) {
      DelSubVars (h);
      WatchLine FAR *Next = h->Next ;
      if (h->Parent == rec) {
        if (prev != NULL) prev->Next = h->Next ;
        else              FirstLine = h->Next ;
        res = TRUE ;
        delete h ;
        }
      else
        prev = h ;
      h = Next ;
      }
    }
  return res;
  }
void WatchView::DelWatch (WatchLine FAR *ActLine)
  {
  WatchLine FAR *Prev = NULL ;
  for (WatchLine FAR *h = FirstLine ; h != NULL ; h = h->Next) {
    if (h == ActLine) {
      if (Prev != NULL) Prev->Next = h->Next ;
      else              FirstLine = h->Next ;
      char * prefixToCheck;
      if (*h->Prefix == *BASEENTRY)
        prefixToCheck = h->Prefix + 1;
      else
        prefixToCheck = h->Prefix;
      if (lstrcmp (prefixToCheck,TABLEOPEN) == 0) {
        DelSubVars (h);
        }
      delete h;
      break ;
      }
    Prev = h ;
    }
  }

WatchView::~WatchView ()
  {
  for ( ; FirstLine != NULL ; ) {
    WatchLine FAR *Next = FirstLine->Next;
    delete FirstLine;
    FirstLine = Next;
    }
  }

#define CMD_WATCH_BASE  501
static BOOL WatchIsOpen;
BOOL IsWatchOpen ()
  {
  return WatchIsOpen;
  }
void DefineWacthToolbar ()
  {
  if (!hWatchToolbar) {
#ifdef WIN32
    HFONT hFnt = HFONT(SendMessage (hWndDock, TBD_GETCONTROLFONT, 0, 0));
#else
    HFONT hFnt = LOWORD(SendMessage (hWndDock, TBD_GETCONTROLFONT, 0, 0));
#endif

    hWndContext = CreateWindow ("COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL |
                              CBS_DROPDOWNLIST | CBS_HASSTRINGS, 
                              0, 0, 80, 10, hwndFrame, (HMENU)ID_CONTEXTCOMBO, MyInstance, NULL);
    SendMessage (hWndContext, WM_SETFONT, WPARAM(hFnt), 1);
    SendMessage (hWndContext, CB_SETEXTENDEDUI, TRUE, 0);
    int xwnd = 200;
    int ywnd = 145;
    hWndWatchList = CreateWindow ("LISTBOX", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_BORDER |
                                              LBS_USETABSTOPS | LBS_DISABLENOSCROLL | LBS_NOTIFY ,
                              0, 0, xwnd, ywnd, hwndFrame, (HMENU)ID_WATCHLIST, MyInstance, NULL);
    SendMessage (hWndWatchList, WM_SETFONT, WPARAM(hFnt), 1);

    RECT rc;
    GetClientRect (hWndContext,&rc);
    TBBUTTON tbWatchButton[] = 
                {
                { 250, ID_CONTEXTCOMBO  ,   TBSTATE_ENABLED, TBSTYLE_SEP   , MAKELONG(rc.bottom - rc.top,0), 0  },
                { -1,                0  ,   TBSTATE_ENABLED, TBSTYLE_SEP   , 0L, 0  },
                { 1,  MI_EXPANDWATCH    ,   TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0 },
                { 0,  MI_DELWATCH       ,   TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0 },
                { 2,  MI_WATCHBREAK     ,   TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0 } ,
                { -1,                0  ,   TBSTATE_ENABLED, TBSTYLE_SEP   , 0L, 0  },
                { 600, ID_WATCHLIST     ,   TBSTATE_ENABLED, TBSTYLE_SEP   , MAKELONG(200,0), 0  }
                };
    hWatchToolbar = CreateToolbar ("Watch",hWndDock,       // Parent
                                  WS_VISIBLE, 
                                  CMD_WATCH_BASE, 
                                  24,             // Anzahl der Bildchen im Bitmap
                                  MyInstance, 
                                  IDR_TOOLICONS, 
                                  tbWatchButton, 
                                  7              // Anzahl der Knöpfe inkl. Separator
                                );
    SetParent (hWndContext, hWatchToolbar);
    SetParent (hWndWatchList, hWatchToolbar);
#ifdef WIN32
    SendMessage (hWndDock, TB_SHOWTOOLBAR, FALSE, LPARAM(hWatchToolbar));
#else
    SendMessage (hWndDock, TB_SHOWTOOLBAR, FALSE, MAKELONG(hWatchToolbar, 0));
#endif
    }
  }
void CreateWatchDock ()
  {
  if (hWatchToolbar)
#ifdef WIN32
    SendMessage (hWndDock, TB_SHOWTOOLBAR, TRUE, LPARAM(hWatchToolbar));
#else
    SendMessage (hWndDock, TB_SHOWTOOLBAR, TRUE, MAKELONG(hWatchToolbar, 0));
#endif
  WatchIsOpen = TRUE ;
  }

void DestroyWatchDock()
  {
  if (hWatchToolbar)
#ifdef WIN32
    SendMessage (hWndDock, TB_SHOWTOOLBAR, FALSE, LPARAM(hWatchToolbar));
#else
    SendMessage (hWndDock, TB_SHOWTOOLBAR, FALSE, MAKELONG(hWatchToolbar, 0));
#endif
  WatchIsOpen = FALSE ;
  }

BOOL ToggleWatchWnd ()
  {
  if (WatchIsOpen)
    DestroyWatchDock ();
  else
    CreateWatchDock ();
  if (WatchIsOpen)
    CheckMenuItem (GetMenu(hwndFrame),MI_SHOWWATCHVAR,MF_BYCOMMAND | MF_CHECKED);
  else
    CheckMenuItem (GetMenu(hwndFrame),MI_SHOWWATCHVAR,MF_BYCOMMAND | MF_UNCHECKED);
  return WatchIsOpen ;
  }

LPSTR lpWatchVar;
void AddWatchLine (LPSTR VarName, LPSTR Scope,LPVOID actContext)
  {
  if (!WatchIsOpen)
    CreateWatchDock ();
  char Buffer[256];
  if (actContext == NULL) {
    wsprintf (Buffer,"Kein Kontext für Scope %s gefunden",Scope);
    MessageBox (GetActiveWindow (),Buffer,"Fehler",MB_ICONEXCLAMATION | MB_TASKMODAL | MB_OK);
    return ;
    }
  lstrcpy (Buffer, VarName);
  lpWatchVar = Buffer;
  
  DLGPROC watchdlgproc = MakeProcInstance (DLGPROC(WatchVarDialog), MyInstance);
  BOOL res = DialogBox (MyInstance, "WATCHDIALOG", GetActiveWindow(), watchdlgproc);
  FreeProcInstance (watchdlgproc);
  
  if (res) {
    BOOL doShow = FALSE ;
    int Sel;
    ContextBuffer cb;
    ContextBuffer FAR *lpcb;
    if (lpActWatchView == NULL) {
      lpActWatchView->FillContextCombo (&cb);
      lpActWatchView = new WatchView() ;
      doShow = TRUE ;
      lpcb = &cb;
      }
    else
      lpcb = lpActWatchView->GetActiveScope ();
    if ((Sel = lpActWatchView->IsWatched (lpWatchVar)) < 0) {
      lpActWatchView->AddLine (lpWatchVar,lpcb);
      if (!doShow)
        FillWatchDlg (hWndWatchList);
      }
    else
      SendMessage (hWndWatchList,LB_SETCURSEL,Sel,0L);
    if (doShow)
      ShowWatch ();
    }
  }

BOOL IsWatchDialogMessage (LPMSG lpMsg)
  {
  return FALSE ;
  }

//--------------------------  WatchVarDialog  -------------------------------
//
// Zuständig für die Übernahme des aktuellen Wortes aus dem Editor in das 
// Watch-Window, bzw. Eingabe eines neuen Wortes in das EDIT-Feld.
//---------------------------------------------------------------------------
DLLExport BOOL FAR PASCAL _export WatchVarDialog (HWND hDlg, UINT msg, WORD wP, LONG lP)
  {
  BOOL RetVal = FALSE ;

  switch (msg) {
    case WM_INITDIALOG:
      SendDlgItemMessage (hDlg, ID_EDITWATCH, WM_SETTEXT, 0, LPARAM(lpWatchVar));
      break;
      
    case WM_COMMAND :
      {
      CRACKER_VARS
      CRACK_MESSAGEsc

      switch (CRACKER_wID) {

              case IDOK :
                GetDlgItemText (hDlg, ID_EDITWATCH, lpWatchVar, 256);
                EndDialog (hDlg,TRUE);
                break ;
              case IDCANCEL :
                EndDialog (hDlg,FALSE);
                break ;
              }
      }
      break ;
    }
  return RetVal;
  }

BOOL doLoad,doUpdate,doReset;

void FillBPList (HWND hDlg,int sel)
  {
  SendDlgItemMessage (hDlg,101,LB_RESETCONTENT,0,0L);
  for ( BPInfo FAR *h = FirstBP ; h != NULL ; h = h->Next) {
    char outtxt [128];
    char modestring[30];
    *modestring = '\0' ;
    if (h->modeMask & EM_LOAD)   lstrcat (modestring,"LOAD ") ;
    if (h->modeMask & EM_UPDATE) lstrcat (modestring,"UPDATE ") ;
    if (h->modeMask & EM_RESET)  lstrcat (modestring,"RESET ") ;
                                if (h->modeMask & EM_CLEAR)  lstrcat (modestring,"CLEAR ") ;
    if (lstrcmp (h->FName,h->PName) != 0)
      wsprintf (outtxt,"%s(%s): %d [%s]",h->FName,h->PName,h->LineNmbr,LPSTR(modestring));
    else
      wsprintf (outtxt,"%s: %d [%s]",h->FName,h->LineNmbr,LPSTR(modestring));
    SendDlgItemMessage (hDlg, 101, LB_ADDSTRING, 0, LPARAM(LPSTR(outtxt)));
    }
  SendDlgItemMessage (hDlg,101,LB_SETCURSEL,sel,0L);
  }

DLLExport BOOL FAR PASCAL _export BPMODEProc (HWND hDlg, UINT msg, WORD wP, LONG lP)
  {
  BOOL RetVal = FALSE ;

  switch (msg) {
    case WM_INITDIALOG:
      if (doLoad)   SendDlgItemMessage (hDlg,101,BM_SETCHECK,TRUE,0L);
      if (doUpdate) SendDlgItemMessage (hDlg,102,BM_SETCHECK,TRUE,0L);
      if (doReset)  SendDlgItemMessage (hDlg,103,BM_SETCHECK,TRUE,0L);
      break;
      
    case WM_COMMAND :
      {
      CRACKER_VARS
      CRACK_MESSAGEsc

      switch (CRACKER_wID) {
              case IDOK :
                doLoad =   BOOL (SendDlgItemMessage (hDlg,101,BM_GETCHECK,0,0L));
                doUpdate = BOOL (SendDlgItemMessage (hDlg,102,BM_GETCHECK,0,0L));
                doReset =  BOOL (SendDlgItemMessage (hDlg,103,BM_GETCHECK,0,0L));
                EndDialog (hDlg,TRUE);
                break ;
              }
      break ;
      }
    }
  return RetVal;
  }

DLLExport BOOL FAR PASCAL _export BPLISTProc (HWND hDlg, UINT msg, WORD wP, LONG lP)
  {
  BOOL RetVal = FALSE ;

  switch (msg) {
    case WM_INITDIALOG:
      FillBPList (hDlg,0);
      break;
      
    case WM_COMMAND :
      {
      CRACKER_VARS
      CRACK_MESSAGEsc

      switch (CRACKER_wID) {
              case IDOK :
                EndDialog (hDlg,TRUE);
                break ;
              case 107 :
                // Loeschen
                {
                int sel = int(SendDlgItemMessage (hDlg,101,LB_GETCURSEL,0,0L));
                BPInfo FAR *h = GetBPInfo (sel);
                if (h != NULL) {
                  InvalidateBreakLine (h);
                  DelBreakPoint (h->LineNmbr,h->FName);
                  FillBPList (hDlg,sel);
                  }
                }
                break ;
              case 106 :
                // Modus
                {
                int sel = int(SendDlgItemMessage (hDlg,101,LB_GETCURSEL,0,0L));
                BPInfo FAR *h = GetBPInfo (sel);
                if (h != NULL) {
                  doLoad = ((h->modeMask & EM_LOAD) != 0) ;
                  doUpdate = ((h->modeMask & EM_UPDATE) != 0) ;
                  doReset = ((h->modeMask & EM_RESET) != 0) ;
                  DLGPROC bmproc = MakeProcInstance (DLGPROC(BPMODEProc), MyInstance);
                  DialogBox (MyInstance, "BPMODE", hDlg, bmproc);
                  FreeProcInstance (bmproc);
                  if (doLoad)   h->modeMask |= EM_LOAD   ; else h->modeMask &= ~EM_LOAD   ; 
                  if (doUpdate) h->modeMask |= EM_UPDATE ; else h->modeMask &= ~EM_UPDATE ; 
                  if (doReset)  h->modeMask |= EM_RESET  ; else h->modeMask &= ~EM_RESET  ; 
                  ClearDDSBreak (h);
                  FillBPList (hDlg,sel);
                  SetDDSBreak (h);
                  }
                }
                break ;
              }
      }
      break ;
    }
  return RetVal;
  }

void ShowBreakList ()
  {
  DLGPROC blproc = MakeProcInstance (DLGPROC(BPLISTProc), MyInstance);
  DialogBox (MyInstance, "BPLIST", GetActiveWindow(), blproc);
  FreeProcInstance (blproc);
  }

void ShowWatch ()
  {
  if (lpActWatchView == NULL)
    lpActWatchView = new WatchView ();
  lpActWatchView->RecalcVals ();
  }

LPVOID GetActContext(LPSTR Scope)
  {
  HWND hDDSWnd = GetDDSMainWnd ();
  Scope = GetFName (Scope);
  if (IsWindow (hDDSWnd)) {
    for (int i = 0 ; ; i++) {
      CallStackInfo csi;
      if (!SendMessage (hDDSWnd,WMC_GETSTACKINFO,WORD(i),RSetData(&csi,sizeof(csi)))) {
        RGetData (&csi,sizeof(csi));
              return csi.c ;
              break ;
              }
      }
    }
  return NULL ;
  }

void UpdateVals ()
  {
  if (lpActWatchView != NULL)
    lpActWatchView->RecalcVals ();
  }

ContextBuffer FAR *WatchView::GetActiveScope ()
  {
  static ContextBuffer cb;
  int sel = int(SendMessage (hWndContext,CB_GETCURSEL,0,0L));
  if (GetContextBuffer (&cb,sel)) return &cb;
  else                            return NULL;
  }

void ContextChanged (LONG lP)
  {
  if (HIWORD (lP) == CBN_SELCHANGE) {
    int sel = int(SendMessage (hWndWatchList,LB_GETCURSEL,0,0L));
    ContextBuffer FAR *cb = lpActWatchView->GetActiveScope ();
    if (cb != NULL)
      lpActWatchView->RecalcVals (sel,cb);
    }
  }

void DelWatch ()
  {
  int sel = int(SendMessage (hWndWatchList,LB_GETCURSEL,0,0L));
  WatchLine FAR *h = lpActWatchView->GetLine (sel) ;
  if (h != NULL) {
    if (lpActWatchView->DelSubVars (h)) {
      lpActWatchView->DelWatch (h);
      FillWatchDlg (hWndWatchList,sel - 1);
      }
    else {
      lpActWatchView->DelWatch (h);
      SendMessage (hWndWatchList,LB_DELETESTRING,sel,0L);
      }

    int anzSels = int (SendMessage (hWndWatchList,LB_GETCOUNT,0,0L));
    if (sel >= anzSels)
      sel = anzSels - 1 ;
    if (sel >= 0)
      SendMessage (hWndWatchList,LB_SETCURSEL,sel,0L);
    }
  }

void ExpandWatch ()
  {
  // Expand
  int sel = int(SendMessage (hWndWatchList,LB_GETCURSEL,0,0L));
  WatchLine FAR *h = lpActWatchView->GetLine (sel) ;
  if (h != NULL) {
    h->TogglePrefix ();
    if (!lpActWatchView->DelSubVars (h)) lpActWatchView->Expand (h,lpActWatchView->GetActiveScope());
    FillWatchDlg (hWndWatchList,sel);
    }
  }

void BreakWatch ()
  {
  int sel = int(SendMessage (hWndWatchList,LB_GETCURSEL,0,0L));
  WatchLine FAR *h = lpActWatchView->GetLine (sel) ;
  if (h != NULL) {
    if (h->IsBreakDone())
      lpActWatchView->ClearBreak (h);
    else if (h->IsToBreak ()) {
      ContextBuffer FAR *cb = lpActWatchView->GetActiveScope ();
      if (cb != NULL) lpActWatchView->SetBreak (h,cb->fName,cb->c);
      }
    LPSTR res = h->FormatOutput ();
    SendMessage (hWndWatchList,LB_DELETESTRING,sel,0L);
    SendMessage (hWndWatchList,LB_INSERTSTRING,sel,LPARAM(res));
    SendMessage (hWndWatchList,LB_SETCURSEL,sel,0L);
    FreeGlobMem (res);
    }
  }

void WatchChanged (LONG lP)
  {
  if (lP == LBN_DBLCLK) {
    int sel = int(SendMessage (hWndWatchList,LB_GETCURSEL,0,0L));
    WatchLine FAR *h = lpActWatchView->GetLine (sel) ;
    if ((h->IsBreakDone()) || (h->IsToBreak ()))
      BreakWatch();
    else
      ExpandWatch();
    }
  }

void FocusToWatchList ()
  {
  if (hWndWatchList) SetFocus (hWndWatchList);
  }

void TryToSetContext (DWORD Id)
  {
  if (lpActWatchView != NULL) {
    char sstr [32];
    wsprintf (sstr,"%lX",Id);
//    int sel = int (SendMessage (hWndContext,CB_FINDSTRING,0,LONG(LPSTR(sstr))));
    int sel = (int) SendMessage (hWndContext,CB_FINDSTRING,0,LONG(LPSTR(sstr)));
    if (sel != CB_ERR) {
      SendMessage (hWndContext,CB_SETCURSEL,sel,0L);
      ContextChanged (MAKELONG(0,CBN_SELCHANGE));
      }
    }
  }



