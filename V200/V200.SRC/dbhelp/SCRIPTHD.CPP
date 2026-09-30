//////////////////////////////////////////////////////
//  Verwaltung der Scripts
//////////////////////////////////////////////////////
//  $Header:   F:/marille/clinicum/dbhelp/rev/scripthd.cpv   1.49   14 May 2000 17:35:04   Hannes  $
//  $Log:   F:/marille/clinicum/dbhelp/rev/scripthd.cpv  $
// 
//    Rev 1.49   14 May 2000 17:35:04   Hannes
// GetFirst & GetNextScript
// 
//    Rev 1.48   07 Dec 1999 10:09:36   Hannes
// 
//    Rev 1.47   23 Nov 1999 15:48:34   Wolfgang
// 1.) DDSCopyScriptEntry zum Kopieren eines ScriptEntrys an den Debugger neu.
// 
//    Rev 1.46   01 Apr 1999 09:20:42   Wolfgang
// 1.) VirtualModule eingebaut.
// 
//    Rev 1.45   29 Apr 1998 20:38:16   Hannes
// Property auch mit Zahlen
// 
//    Rev 1.44   22 Apr 1998 18:12:08   Hannes
// Nachster Versuch -> Script ohne Kostante...
// 
//    Rev 1.43   22 Apr 1998 16:16:38   Hannes
// 
//    Rev 1.42   06 Feb 1998 08:18:58   Hannes
// ClearCachedScripts vorerst raus
// 
//    Rev 1.41   13 Jan 1998 11:42:12   Martin
// ueberfluessige Klammer weg
// 
//    Rev 1.40   12 Jan 1998 18:14:04   Hannes
// Fehlerkorrektur CachedSize...
// 
//    Rev 1.39   05 Jan 1998 07:50:50   Hannes
// Einsparungen im Scriptheader
// 
//    Rev 1.38   16 Dec 1997 08:00:30   Hannes
// 
//    Rev 1.37   15 Dec 1997 17:35:34   Hannes
// Zusammenspiel Debugger / Formulargenerierung
// 
//    Rev 1.36   01 Dec 1997 19:40:28   Hannes
// Diverse Anpassungen / Replikator / Speicherfresser
// 
//    Rev 1.35   20 Nov 1997 20:29:18   Martin
// noch eine Stelle, wo SizeOverAll vermindert werden muss, nachgetragen
// 
//    Rev 1.34   10 Nov 1997 10:48:54   Hannes
// Beschleunigungsmassnahmen
// 
//    Rev 1.33   06 Nov 1997 19:32:06   Hannes
// 
//    Rev 1.32   05 Nov 1997 14:30:34   Hannes
// 
//    Rev 1.31   04 Nov 1997 14:55:22   Hannes
// 
//    Rev 1.30   31 Oct 1997 17:05:56   Hannes
// 
//    Rev 1.29   27 Oct 1997 19:52:44   Hannes
// Zusammenspiel Debugger
// 
//    Rev 1.28   24 Oct 1997 08:38:08   Hannes
// Umstellung von mdiChild zwecks Speichersparmassnahmen
// 
//    Rev 1.27   11 Jun 1997 12:36:08   Martin
// 32bit-faehig gemacht
// 
//    Rev 1.26   27 May 1997 11:14:50   Hannes
// GetTableID mit Identifier, GetConstData
// 
//    Rev 1.25   05 May 1997 11:36:18   Hannes
// Speicherfresser verbessert
// 
//    Rev 1.24   30 Apr 1997 11:09:52   Hannes
// 
//    Rev 1.23   30 Apr 1997 09:20:08   Hannes
// 
//    Rev 1.22   30 Apr 1997 09:10:58   Hannes
// Globallock wieder reaktiviert
// 
//    Rev 1.21   16 Apr 1997 11:46:30   Hannes
// 
//    Rev 1.20   16 Apr 1997 10:59:28   Hannes
// Fehlerkorrektur bei der Hashtabellentrennung
// 
//    Rev 1.19   16 Apr 1997 10:01:46   Hannes
// HashTabellen - Handling veraendert
// 
//    Rev 1.18   13 Mar 1997 19:03:00   Hannes
// GetScriptEntry (FROM Blob)
// 
//    Rev 1.17   28 Feb 1997 16:25:52   Hannes
// 
//    Rev 1.16   20 Feb 1997 16:25:14   Hannes
// Fehlerkorrekturen in Verbindung mit ClearCachedScript
// 
//    Rev 1.15   20 Feb 1997 11:22:20   Martin
// hGProg -> *hGProg
// 
//    Rev 1.14   19 Feb 1997 12:06:42   Hannes
// Scriptfunktionen -> Header erweitert
// 
//    Rev 1.12   26 Nov 1996 07:54:10   HANNES
// Automatischer Update
// 
//    Rev 1.11   21 Oct 1996 18:51:58   HANNES
// Einbau von Aliasnamen in das Script
// 
//    Rev 1.10   20 Jun 1996 18:56:38   HANNES
// 
//    Rev 1.9   17 Jun 1996 15:46:06   HANNES
// Einbau von BLOBS
// 
//    Rev 1.8   04 Feb 1996 15:37:04   gerhold
// Teile von DBHELP in DDSMEM
// 
//    Rev 1.7   02 Feb 1996 10:42:56   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.6   15 May 1995 08:23:56   HANNES
// Propertys
// 
//    Rev 1.5   24 Feb 1995 11:12:46   HANNES
//  
// 
//    Rev 1.4   16 Feb 1995 12:48:48   HANNES
//  
// 
//    Rev 1.3   10 Jan 1995 15:00:38   HANNES
// 
//    Rev 1.2   09 Jan 1995 12:09:30   HANNES
// Debugger eingebaut
// 
//    Rev 1.1   05 Dec 1994 17:40:00   HANNES
// Endgueltiger Einbau der Expressions
// 
//    Rev 1.0   24 Jun 1994 16:44:50   HANNES
// Neuuebernahme clinicum
//
#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#include "globmem.h"
#include "dlladmin.h"
#include "dlladmin.hpp"
#include "scripthd.hpp"
#include "hash.hpp"
#define NOCOMPILE
#include "compile.hpp"
#define MODULENUM 99
#include "winass.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "communic.hpp"

DWORD SizeOverAll;
class FAR ScriptNode {
 public :
  LPSCRIPTCONTENT ent;
  GLOBALHANDLE hGScriptBackUp;
  GLOBALHANDLE hGConstBackUp;
  LPDBRECORD constRecBackUp;
  int CacheCount;
  BOOL doFreeConsts;
  BOOL FreeNext;
  BOOL dataFromBlob;
  hash FAR *NameHash;
  ScriptNode FAR *Next;
  void ClearPointers ()
    {
    if (ent->IconData != NULL)
      FreeGlobMem (ent->IconData);
    if (ent->LocalTypes != NULL)
      FreeGlobMem (ent->LocalTypes);
    if (ent->HelpTypes != NULL)
      FreeGlobMem (ent->HelpTypes);
    if (ent->PropertyData != NULL)
      FreeGlobMem (ent->PropertyData);
    if (ent->ftlist != NULL)
      FreeGlobMem (ent->ftlist);
    if (ent->TRef != NULL)
      FreeGlobMem (ent->TRef);
    if (ent->AliasDef != NULL)
      FreeGlobMem (ent->AliasDef);
    if (ent->ImportModules != NULL)
      FreeGlobMem (ent->ImportModules);
    if (ent->BaseModules != NULL)
      FreeGlobMem (ent->BaseModules);
    if (ent->VirtualModules != NULL)
      FreeGlobMem (ent->VirtualModules);
    if (ent->ExportDef)
      FreeGlobMem (ent->ExportDef);
    }
  void Clear ()
    {
    if (ent->hData != 0) {
      SizeOverAll -= (ent->GesSize_ProgStart() + ent->fSize + ent->cSize);
      if (!dataFromBlob)
        GlobalFree (ent->hData) , ent->hData = 0;
      }
    if (hGScriptBackUp)
      GlobalFree (hGScriptBackUp) , hGScriptBackUp = 0;
    if (hGConstBackUp)
      GlobalFree (hGConstBackUp) , hGConstBackUp = 0;
    if (constRecBackUp != NULL)
      delete constRecBackUp , constRecBackUp = NULL;
    ClearPointers ();
    if (NameHash != NULL) delete NameHash;
    FreeGlobMem (ent);
    }
  void SetContent (LPSCRIPTCONTENT s)
    {
    BYTE FAR *oldLocalTypes = ent->LocalTypes;
    BYTE FAR *oldHelpTypes = ent->HelpTypes;
    hmemcpy (ent,s,sizeof(*ent));
    if (ent->IconSize > 0) {
      ent->IconData = GetGlobMem (ent->IconSize);
      hmemcpy (ent->IconData,((char huge *) s) + sizeof(*s),ent->IconSize);
      }
    else
      ent->IconData = NULL ;
    if (ent->PropertySize > 0) {
      ent->PropertyData = LPSTR (GetGlobMem (ent->PropertySize)) ;
      hmemcpy (ent->PropertyData,((char huge *) s) + sizeof(*s) + ent->IconSize,ent->PropertySize);
      }
    else
      ent->PropertyData = NULL ;
    if (ent->AnzTables > 0) {
      ent->TRef = (TableRef FAR *) GetGlobMem (ent->AnzTables * sizeof(TableRef)) ;
      hmemcpy (ent->TRef,((char huge *) s) + ent->TRefOffs (),ent->AnzTables * sizeof(TableRef));
      }
    else
      ent->TRef = NULL ;
    if (ent->AliasDefSize > 0) {
      ent->AliasDef = LPALIASDEF(GetGlobMem (ent->AliasDefSize)) ;
      hmemcpy (ent->AliasDef,((char huge *) s) + ent->AliasDefOffs (),ent->AliasDefSize);
      }
    else
      ent->AliasDef = NULL ;
    if (ent->ImportModuleSize > 0) {
      ent->ImportModules = LPSTR(GetGlobMem (ent->ImportModuleSize));
      hmemcpy (ent->ImportModules,((char huge *) s) + ent->ImportModuleOffs (),ent->ImportModuleSize);
      }
    else
      ent->ImportModules = NULL ;
    if (ent->BaseModuleSize > 0) {
      ent->BaseModules = LPSTR(GetGlobMem (ent->BaseModuleSize));
      hmemcpy (ent->BaseModules,((char huge *) s) + ent->BaseModuleOffs (),ent->BaseModuleSize);
      }
    else
      ent->BaseModules = NULL ;
    if (ent->VirtualModuleSize > 0) {
      ent->VirtualModules = LPSTR(GetGlobMem (ent->VirtualModuleSize));
      hmemcpy (ent->VirtualModules,((char huge *) s) + ent->VirtualModuleOffs (),ent->VirtualModuleSize);
      }
    else
      ent->VirtualModules = NULL ;
    if (ent->ExportTypeSize > 0) {
      ent->ExportDef = LPSTR(GetGlobMem (ent->ExportTypeSize));
      hmemcpy (ent->ExportDef,((char huge *) s) + ent->ExportOffset (),ent->ExportTypeSize);
      }
    else
      ent->ExportDef = NULL ;
    ent->LocalTypes = oldLocalTypes ;
    ent->HelpTypes = oldHelpTypes ;

    ent->hData = NULL;

    if (NameHash != NULL) delete NameHash , NameHash = NULL;
    }
  ScriptNode (LPSCRIPTCONTENT s)
    {
    ent = LPSCRIPTCONTENT (GetGlobMem (sizeof(*s))) ;
    SetContent (s);
    ent->LocalTypes = NULL ;
    ent->HelpTypes = NULL ;
    ent->ftlist = NULL ;
    }
  ~ScriptNode ()
    {
    if ((ent != NULL) && (ent->hData != 0)) {
      SizeOverAll -= (ent->GesSize_ProgStart() + ent->fSize + ent->cSize);
      GlobalFree (ent->hData) , ent->hData = 0;
      }
    Clear ();
    }
  ScriptNode FAR &operator = (LPSCRIPTCONTENT s)
    {
    SetContent (s);
    return *this;
    }
  LPVOID operator new (size_t size)
    {
    return GetGlobMem (size) ;
    }
  void operator delete (LPVOID obj)
    {
    FreeGlobMem (obj);
    }
  };

void ScriptContent_Entry::SetTypes (char huge *base)
  {
  if (LocalTypes != NULL) FreeGlobMem (LocalTypes) , LocalTypes = NULL ;
  if (HelpTypes != NULL) FreeGlobMem (HelpTypes) , HelpTypes = NULL ;
  if (ftlist != NULL) FreeGlobMem (ftlist) , ftlist = NULL ;
  if (AnzLocals > 0) {
    LocalTypes = LPBYTE(GetGlobMem (AnzLocals * sizeof(BYTE)));
    hmemcpy (LocalTypes,base + LocalTypeOffs(),AnzLocals * sizeof(BYTE));
    }
  else
    LocalTypes = NULL ;
  if (AnzHelps > 0) {
    HelpTypes = LPBYTE(GetGlobMem (AnzHelps * sizeof(BYTE)));
    hmemcpy (HelpTypes,base + HelpTypeOffs(),AnzHelps * sizeof(BYTE));
    }
  else
    HelpTypes = NULL ;
  if (FuncTypeSize > 0) {
    ftlist = (_FuncTypeList FAR *) GetGlobMem (FuncTypeSize);
    hmemcpy (ftlist,base + FuncTypeOffs (),FuncTypeSize);
    }
  else
    ftlist = NULL ;
  }

class FAR ScriptBlock {
 public :
  GLOBALHANDLE hGmem;
  DWORD        GesSize;
  LPSTR        base;
  ScriptBlock (DWORD AllocSize)
    {
    hGmem = GlobalAlloc (GMEM_MOVEABLE,AllocSize) ;
    GesSize = 0L ;
    base = (LPSTR)GlobalLock (hGmem) ;
    }
  ~ScriptBlock ()
    {
    if (hGmem) {
      GlobalUnlock (hGmem);
      GlobalFree (hGmem);
      }
    }
  void Enlarge (DWORD Size)
    {
    }
  void AddBlock (LPVOID Data,DWORD Size)
    {
    Enlarge (Size);
    hmemcpy ((char huge *) base + GesSize,Data,Size);
    GesSize += Size;
    }
  ScriptBlock &operator += (LPSCRIPTCONTENT e)
    {
    AddBlock (e,sizeof(*e));
    if (e->IconData != NULL)
      AddBlock (e->IconData,e->IconSize);
    if (e->PropertyData != NULL)
      AddBlock (e->PropertyData,e->PropertySize);
#ifdef UEBERLEGT
    if (e->LocalTypes != NULL)
      AddBlock (e->LocalTypes,e->AnzLocals * sizeof(WORD));
    if (e->HelpTypes != NULL)
      AddBlock (e->HelpTypes,e->AnzHelps * sizeof(WORD));
#endif
    if (e->AnzTables > 0)
      AddBlock (e->TRef,e->AnzTables * sizeof(TableRef));
    if (e->AliasDef != NULL)
      AddBlock (e->AliasDef,e->AliasDefSize);
    if (e->ImportModules != NULL)
      AddBlock (e->ImportModules,e->ImportModuleSize);
    if (e->BaseModules != NULL)
      AddBlock (e->BaseModules,e->BaseModuleSize);
    if (e->VirtualModules != NULL)
      AddBlock (e->VirtualModules,e->VirtualModuleSize);
    if (e->ExportDef != NULL)
      AddBlock (e->ExportDef,e->ExportTypeSize);
    return *this;
    }
  ScriptBlock &operator += (LPSCRIPTCONT h)
    {
    AddBlock (h,sizeof(*h));
    return *this;
    }
  };

static LPSTR GetFName(LPVOID fname)
  {
  LPSTR h = LPSTR(fname);
  LPSTR start = h;
  for ( ; *h ; h++) {
    if ((*h == '\\') || (*h == ':')) start = h+1;
    }
  WIN_ASSERT (lstrlen(start) < 13);
  AnsiUpper (start);
  return start;
  }

class FAR ScriptList {
 public :
  ScriptNode FAR *first;
  hash FAR *NodeHash;
  hash FAR *ENodeHash;
  BOOL IsLoaded ()
    {
    return (first != NULL) ;
    }
  ScriptList &operator += (LPSCRIPTCONTENT s)
    {
    ScriptNode FAR *n = new ScriptNode (s);
    n->Next = first ;
    first = n;
    if (NodeHash == NULL) NodeHash = new hash (137,STRKEY);
    if (ENodeHash == NULL) ENodeHash = new hash (137,LONGKEY);
    if (!NodeHash->SetData (n->ent->fName,&n,sizeof(n))) {
      NodeHash->DelData (n->ent->fName);
      NodeHash->SetData (n->ent->fName,&n,sizeof(n));
      }
    if (!ENodeHash->SetData (LONG(n->ent),&n,sizeof(n))) {
      ENodeHash->DelData (LONG(n->ent));
      ENodeHash->SetData (LONG(n->ent),&n,sizeof(n));
      }
    return *this;
    }
  ScriptList &operator -= (LPSTR Name)
    {
    ScriptNode FAR *prev = NULL;
    LPSTR c = GetFName(Name);
    NodeHash->DelData (c);
    for (ScriptNode FAR *n = first ; n != NULL ; n = n->Next) {
      if (lstrcmp (n->ent->fName,c) == 0) {
        ENodeHash->DelData (LONG (n->ent));
        if (prev != NULL) prev->Next = n->Next;
        else              first      = n->Next;
        delete n;
        break ;
        }
      prev = n;
      }
    if (first == NULL) {
      delete NodeHash , NodeHash = NULL ;
      delete ENodeHash , ENodeHash = NULL ;
      }
    return *this;
    }
  ScriptNode FAR *operator [] (LPSTR Name)
    {
    if (NodeHash == NULL) return NULL;
    LPSTR c = GetFName(Name);
    ScriptNode FAR *FAR *n = (ScriptNode FAR *FAR *) NodeHash->GetData (c);
    if (n != NULL)
      return *n ;
    else
      return NULL ;
    return NULL;
    }
  LPSCRIPTCONTENT operator [] (int Num)
    {
    int act = 0;
    for (ScriptNode FAR *n = first ; n != NULL ; n = n->Next , act ++) {
      if (act == Num) return n->ent;
      }
    return NULL;
    }
  ScriptNode FAR * operator [] (LPSCRIPTCONTENT ent)
    {
    if (ENodeHash == NULL) return NULL;
    ScriptNode FAR *FAR *n = (ScriptNode FAR *FAR *) ENodeHash->GetData (LONG (ent));
    if (n != NULL)
      return *n ;
    else
      return NULL ;
    return NULL;
    }
  void Clear ()
    {
    for ( ; first != NULL ; ) {
      ScriptNode FAR *n = first->Next ;
      delete first ;
      first = n;
      }
    delete NodeHash , NodeHash = NULL ;
    delete ENodeHash , ENodeHash = NULL ;
    }
  DWORD Size (LPSCRIPTCONTENT e)
    {
    return sizeof(*e) + e->IconSize + e->PropertySize +
           e->AliasDefSize + e->ImportModuleSize + e->BaseModuleSize + e->VirtualModuleSize + 
           e->ExportTypeSize + (e->AnzTables * sizeof (TableRef));
    }
  int Anz (DWORD FAR *GesSize)
    {
    int res = 0 ;
    *GesSize = sizeof(WORD) ;
    for (ScriptNode FAR *n = first ; n != NULL ; n = n->Next) {
      *GesSize += Size (n->ent);
      res ++ ;
      }
    return res;
    }
  };

static ScriptList scl,scu;
DLLExport void _export WINAPI LoadScriptContent()
  {
  if (!scl.IsLoaded()) {
    DWORD DataSize;
    GLOBALHANDLE hGScriptCont = ReadScriptData (1,"_CONT",&DataSize);
    if (hGScriptCont) {
      LPSCRIPTCONT shd = LPSCRIPTCONT (GlobalLock (hGScriptCont));
      LPSCRIPTCONTENT ent = LPSCRIPTCONTENT (shd + 1);
      for (int i = 0 ; i < int (shd->AnzScripts) ; i++) {
        scl += ent;
        ent = LPSCRIPTCONTENT ((char huge *) (ent) + scl.first->ent->GesSize_Content());
        }
      GlobalUnlock (hGScriptCont);
      GlobalFree (hGScriptCont);
      }
    }
  }

DLLExport void _export WINAPI LoadUpdateScriptContent()
  {
  if (!scu.IsLoaded()) {
    DWORD DataSize;
    GLOBALHANDLE hGScriptCont = ReadScriptData (4,"_CONT",&DataSize);
    if (hGScriptCont) {
      LPSCRIPTCONT shd = LPSCRIPTCONT (GlobalLock (hGScriptCont));
      LPSCRIPTCONTENT ent = LPSCRIPTCONTENT (shd + 1);
      for (int i = 0 ; i < int (shd->AnzScripts) ; i++) {
        scu += ent;
        ent = LPSCRIPTCONTENT ((char huge *) (ent) + scu.first->ent->GesSize_Content());
        }
      GlobalUnlock (hGScriptCont);
      GlobalFree (hGScriptCont);
      }
    }
  }

DLLExport void _export WINAPI UnloadScriptContent()
  {
  scl.Clear ();
  }

DLLExport void _export WINAPI UnloadUpdateScriptContent()
  {
  scu.Clear ();
  }

DLLExport void _export WINAPI FillScriptDlg (HWND hDlg,WORD Id)
  {
  for (ScriptNode FAR *n = scl.first ; n != NULL ; n = n->Next) {
    char outtxt[256];
    wsprintf (outtxt,"%s\t%s\t%ld\t%ld\t%d\t%d",n->ent->Name,n->ent->fName,n->ent->fSize,n->ent->cSize,n->ent->AnzLocals,n->ent->AnzHelps);
    SendDlgItemMessage (hDlg,Id,LB_ADDSTRING,0,LONG(LPSTR(outtxt)));
    }
  }

BOOL IsUpdateScript (LPSCRIPTCONTENT sc)
  {
  char buffer[512];
  return sc->GetProperty("FromVersion",buffer,sizeof(buffer));
  }

DLLExport void _export WINAPI CreateScriptContent(LPSTR fName)
  {
  DWORD DataSize;
  GLOBALHANDLE hGmem;

  LoadScriptContent();

  if ((fName != NULL) && (scl[fName] != NULL)) {
    scl -= fName;
    hGmem = ReadScriptData (0,GetFName(fName),&DataSize);
    if (hGmem) {
      scl += LPSCRIPTCONTENT(GlobalLock(hGmem));
      GlobalUnlock (hGmem);
      GlobalFree (hGmem);
      }
    }
  else if (fName != NULL) {
    hGmem = ReadScriptData (0,GetFName(fName),&DataSize);
    if (hGmem) {
      scl += LPSCRIPTCONTENT(GlobalLock(hGmem));
      GlobalUnlock (hGmem);
      GlobalFree (hGmem);
      }
    }
  else {
    scl.Clear();
    DBList FAR *scList = GetAllScriptData (0);
    BOOL first = FALSE ;
    for ( LPDBRECORD rec = scList->GetFirst () ; rec != NULL ; rec = scList->GetNext(rec) ) {
      LPBLOBDESC bd = LPBLOBDESC (rec->Get (3));
      if ((bd != NULL) && (bd->hGmem)) {
        scl += LPSCRIPTCONTENT(GlobalLock(bd->hGmem));
        GlobalUnlock (bd->hGmem);
        }
      if (!first)
        scList->ThrowAtHead (rec);
      }
    delete scList ;
    }
  ScriptContent_Header hd ;
  DWORD GesSize;
  hd.AnzScripts = scl.Anz(&GesSize);
  ScriptBlock b(GesSize);
  b += &hd;
  for (ScriptNode FAR *n = scl.first ; n != NULL ; n = n->Next) {
    b += n->ent;
    }
  WriteScriptData (1,"_CONT",b.hGmem,b.GesSize);
//  GlobalFree (b.hGmem);
  }

DLLExport void _export WINAPI CreateUpdateScriptContent(LPSTR fName)
  {
  DWORD DataSize;
  GLOBALHANDLE hGmem;

  LoadUpdateScriptContent();

  if ((fName != NULL) && (scu[fName] != NULL)) {
    scu -= fName;
    hGmem = ReadScriptData (3,GetFName(fName),&DataSize);
    if (hGmem) {
      scu += LPSCRIPTCONTENT(GlobalLock(hGmem));
      GlobalUnlock (hGmem);
      GlobalFree (hGmem);
      }
    }
  else if (fName != NULL) {
    hGmem = ReadScriptData (3,GetFName(fName),&DataSize);
    if (hGmem) {
      scu += LPSCRIPTCONTENT(GlobalLock(hGmem));
      GlobalUnlock (hGmem);
      GlobalFree (hGmem);
      }
    }
  else {
    scu.Clear();
    DBList FAR *scList = GetAllScriptData (3);
    BOOL first = FALSE ;
    for ( LPDBRECORD rec = scList->GetFirst () ; rec != NULL ; rec = scList->GetNext(rec) ) {
      LPBLOBDESC bd = LPBLOBDESC (rec->Get (3));
      if ((bd != NULL) && (bd->hGmem)) {
        scu += LPSCRIPTCONTENT(GlobalLock(bd->hGmem));
        GlobalUnlock (bd->hGmem);
        }
      if (!first)
        scList->ThrowAtHead (rec);
      }
    delete scList ;
    }
  ScriptContent_Header hd ;
  DWORD GesSize;
  hd.AnzScripts = scu.Anz(&GesSize);
  ScriptBlock b(GesSize);
  b += &hd;
  for (ScriptNode FAR *n = scu.first ; n != NULL ; n = n->Next) {
    b += n->ent;
    }
  WriteScriptData (4,"_CONT",b.hGmem,b.GesSize);
//  GlobalFree (b.hGmem);
  }

DLLExport BOOL _export WINAPI CheckScriptContent(LPSTR fName)
  {
  LoadScriptContent();

  return ((fName != NULL) && (scl[fName] != NULL)) ;
  }

DLLExport BOOL _export WINAPI CheckUpdateScriptContent(LPSTR fName)
  {
  LoadUpdateScriptContent();

  return ((fName != NULL) && (scu[fName] != NULL)) ;
  }

DLLExport BOOL _export WINAPI GetScriptFName (LPSTR fName,int Sel)
  {
  LPSCRIPTCONTENT ent = scl[Sel];
  if (ent != NULL) lstrcpy (fName,ent->fName);
  else             *fName = '\0';
  return (ent != NULL) ;
  }

static WORD kbToCache = WORD(-1);
LPSCRIPTCONTENT LastUsedScript (ScriptNode FAR *FAR *x)
  {
  LPSCRIPTCONTENT res = NULL;
  *x = NULL;
  for (ScriptNode FAR *s = scl.first ; s != NULL ; s = s->Next) {
    if ((s->ent->hData) && ((res == NULL) || (res->LastTimeUsed < s->ent->LastTimeUsed))) {
      res = s->ent;
      *x = s;
      }
    }
  return res ;
  }

void ClearCachedScripts()
  {
#ifdef UEBERLEGT
  if (kbToCache < 0) {
    kbToCache = GetPrivateProfileInt ("Script","BufferSize",1024,MYINI);
    if (kbToCache < 0) kbToCache = 0;
    }
  LPSCRIPTCONTENT ce;
  ScriptNode FAR *s;
  for ( ; ((SizeOverAll > DWORD(kbToCache) * 1024L) && ((ce = LastUsedScript (&s)) != NULL)) ; ) {
    if (!s->dataFromBlob)
      GlobalFree (ce->hData) , ce->hData = 0;
    SizeOverAll -= (ce->GesSize_ProgStart() + ce->fSize + ce->cSize);
    }
#endif
  }

DLLExport BOOL _export WINAPI ScriptContent_Entry::GetProperty (LPSTR Property,LPSTR buffer,int buffersize)
  {
  BOOL found = FALSE,ready = FALSE ;
  if (PropertyData != NULL) {
#define STATE_HD    0
#define STATE_ENT   1
    int state = STATE_HD ;
    buffersize -= 1 ;
    for ( LPSTR h = PropertyData ; ((*h) && (!ready)) ; ) {
      switch (state) {
        case STATE_HD :
          if (IsCharAlpha (*h)) {
            LPSTR e = h ;
            for ( ; ((IsCharAlpha (*h)) || ((*h > '0') && (*h <= '9'))) ; h++) ;
            char oldchar = *h ;
            *h = '\0' ;
            found = (lstrcmp (Property,e) == 0) ;
            *h = oldchar ;
            }
          else if (*h == '=') {
            state = STATE_ENT ;
            h ++ ;
            }
          else h++ ;
          break ;
        case STATE_ENT :
          if (found) {
            for ( int i = 0 ; ((*h != ',') && (*h)) ; h++ )
              if (i < buffersize) buffer[i++] = *h ;
            buffer[i] = '\0' ;
            ready = TRUE ;
            }
          else {
            if (*h == ',') state = STATE_HD ;
            h ++ ;
            }
          break ;
        }
      }
    }
  return ready ;
  }

DLLExport void _export WINAPI ScriptContent_Entry::GetScriptData (GLOBALHANDLE FAR *hGProg,GLOBALHANDLE FAR *hGConst,LPDBRECORD FAR *constRec)
  {
  BOOL doSetTypes = FALSE ;
  ScriptNode FAR *n = scl[fName];
  if (n == NULL)
    n = scu[fName];
  if (hData == NULL) {
    // Nachsehen, obs nicht Backup - Kopieen im Scriptnode gibt
    WIN_ASSERT (n != NULL);
    if (n->hGScriptBackUp) {
      *hGProg  = GlobalAlloc (GMEM_MOVEABLE,fSize);
      hmemcpy (GlobalLock (*hGProg),GlobalLock (n->hGScriptBackUp),fSize);
      GlobalUnlock (*hGProg);
      GlobalUnlock (n->hGScriptBackUp);
      *hGConst = n->hGConstBackUp;
      *constRec = n->constRecBackUp ;
      return ;
      }
    DWORD DataSize;
    char tmpName[128];
    lstrcpy (tmpName,fName);
    AnsiUpper (tmpName);
    hData = ReadScriptData (0,tmpName,&DataSize);
    if (hData == NULL)
      hData = ReadScriptData (3,tmpName,&DataSize); // Vielleicht handelt es sich um ein
                                                    // Updatescript
    SizeOverAll += (GesSize_ProgStart() + fSize + cSize);
    doSetTypes = TRUE ;
    }
  WIN_ASSERT(hData != NULL);
  char huge *data = (char huge *) GlobalLock (hData);

  // Daten neu uebernehmen, die koennten sich ja geaendert haben
  ////////////////////////////////////////////////////////////////
  *hGProg  = GlobalAlloc (GMEM_MOVEABLE,fSize);
  if (doSetTypes)
    SetTypes (data);
  hmemcpy (GlobalLock (*hGProg),data+cSize+GesSize_ProgStart(),fSize);
  GlobalUnlock (*hGProg);
  if ((cSize) && (!n->hGConstBackUp) && (AnzConsts > 0)) {
    n->hGConstBackUp = GlobalAlloc (GMEM_MOVEABLE,cSize);
    hmemcpy (GlobalLock (n->hGConstBackUp),data+GesSize_ProgStart(),cSize);
    GlobalUnlock (n->hGConstBackUp);
    n->constRecBackUp = new DBConstRecord (AnzConsts,0L,n->hGConstBackUp);
    }

  *hGConst = n->hGConstBackUp;
  *constRec = n->constRecBackUp ;
  if (n->doFreeConsts) {
    n->hGConstBackUp = NULL;
    n->constRecBackUp = NULL;
    }

  GlobalUnlock (hData);
  LastTimeUsed = GetTickCount();

  ClearCachedScripts();
  }

LPSTR GetConstData (LPSCRIPTCONTENT scent)
  {
  WIN_ASSERT (scent->hData != NULL);
  LPSTR data = (LPSTR)GlobalLock (scent->hData);
  LPSTR res = data+scent->GesSize_ProgStart();
  GlobalUnlock (scent->hData);    // Der ist sowieso schon einmal gelockt
  return res;
  }

DLLExport void _export WINAPI ScriptContent_Entry::GetCacheScriptData (GLOBALHANDLE FAR *hGProg,GLOBALHANDLE FAR *hGConst,LPDBRECORD FAR *constRec)
  {
  ScriptNode FAR *n = scl[fName];
  if (n == NULL)
    n = scu[fName];
  WIN_ASSERT (n != NULL);
  if (n->CacheCount > 0) {
    *hGProg  = n->hGScriptBackUp;
    *hGConst = n->hGConstBackUp;
    *constRec = n->constRecBackUp;
    n->CacheCount ++ ;
    }
  else {
    if (n->hGScriptBackUp == NULL) {
      if (hData == NULL) {
        DWORD DataSize;
        char tmpName[128];
        lstrcpy (tmpName,fName);
        AnsiUpper (tmpName);
        hData = ReadScriptData (0,tmpName,&DataSize);
        WIN_ASSERT(hData != NULL);
        SizeOverAll += (GesSize_ProgStart() + fSize + cSize);
        }
      char huge *data = (char huge *) GlobalLock (hData);

      // Daten neu uebernehmen, die koennten sich ja geaendert haben
      ////////////////////////////////////////////////////////////////
      *hGProg  = GlobalAlloc (GMEM_MOVEABLE,fSize);
      SetTypes (data);
      hmemcpy (GlobalLock (*hGProg),data+cSize+GesSize_ProgStart(),fSize);
      GlobalUnlock (*hGProg);
      if ((cSize) && (AnzConsts > 0)) {
        *hGConst = GlobalAlloc (GMEM_MOVEABLE,cSize);
        hmemcpy (GlobalLock (*hGConst),data+GesSize_ProgStart(),cSize);
        GlobalUnlock (*hGConst);
        *constRec = new DBConstRecord (AnzConsts,0L,*hGConst);
        }
      else {
        *hGConst = NULL;
        *constRec = NULL;
        }
      n->hGScriptBackUp = *hGProg ;
      n->hGConstBackUp = *hGConst ;
      n->constRecBackUp = *constRec;
      SizeOverAll -= (GesSize_ProgStart() + fSize + cSize);
      GlobalUnlock (hData);
      GlobalFree (hData);
      hData = NULL ;
      }
    else {
      *hGProg  = n->hGScriptBackUp;
      *hGConst = n->hGConstBackUp;
      *constRec = n->constRecBackUp;
      }
    n->CacheCount = 1 ;
    }
  LastTimeUsed = GetTickCount();
  ClearCachedScripts ();
  }

DLLExport LPSCRIPTCONTENT _export WINAPI GetScriptEntry(LPSTR fName)
  {
  ScriptNode FAR *snode = scl[fName];
  if (snode == NULL)
    snode = scu[fName];
  if (snode != NULL) return snode->ent;
  else               return NULL;
  }

DLLExport LPSCRIPTCONTENT _export WINAPI GetScriptEntry(GLOBALHANDLE hGmem)
  {
  LPSCRIPTCONTENT s = LPSCRIPTCONTENT (GlobalLock (hGmem));
  ScriptList *sclist;
  if (IsUpdateScript (s)) sclist = &scu;
  else                    sclist = &scl;
  ScriptNode FAR *snode = (*sclist)[s->fName];
  if (snode == NULL) {
    *sclist += s ;
    snode = (*sclist)[s->fName];
    }
  else {
    *snode = s ;
    }
    
  SizeOverAll += (s->GesSize_ProgStart() + s->fSize + s->cSize);
  snode->dataFromBlob = TRUE ;
  snode->ent->hData = hGmem ;
  snode->hGConstBackUp = NULL;
  snode->constRecBackUp = NULL;
  snode->ent->SetTypes ((char huge *)s);
  snode->doFreeConsts = TRUE ;
  GlobalUnlock (hGmem);
  return snode->ent;
  }

DLLExport LPSCRIPTCONTENT _export WINAPI DDSCopyScriptEntry(LPSCRIPTCONTENT schd)

  {
  if (schd != NULL) {
    ScriptBlock b (4);
    LPVOID commBase = GetPointer (NULL);
    LPSTR oldBase = b.base;
    b.base = (LPSTR) commBase;
    if (b.base != NULL)
      b += schd;
    b.base = oldBase;
    return (LPSCRIPTCONTENT) commBase;
    }
  else
    return schd;
  }

DLLExport void _export WINAPI AddScriptEntry(LPSTR fName, LPSCRIPTCONTENT schd)
  {
  scl-=fName;
  if (schd != NULL)
    scl+=schd;
  }

DLLExport void _export WINAPI SetHDataNULL (LPSTR fName)
  {
  ScriptNode FAR *snode = scl[fName];
  if (snode == NULL) snode = scu[fName];
  snode->ent->hData = 0;
  if (snode->hGConstBackUp) {
    GlobalFree (snode->hGConstBackUp);
    snode->hGConstBackUp = 0;
    }
  if (snode->constRecBackUp)
    delete snode->constRecBackUp;
  snode->constRecBackUp = NULL;
  SizeOverAll -= (snode->ent->GesSize_ProgStart() + snode->ent->fSize + snode->ent->cSize);
  }

static hash FAR *FuncHash;
DLLExport hash FAR *_export WINAPI GetFuncHash ()
  {
  if (FuncHash == NULL) FuncHash = new hash (257,STRKEY);
  return FuncHash;
  }
DLLExport void _export WINAPI ClearFuncHash()
  {
  if (FuncHash != NULL) delete FuncHash , FuncHash = NULL;
  }

DLLExport void _export WINAPI ClearCachedScript(LPSTR fName)
  {
  ScriptNode FAR *snode = scl[fName];
  if (snode != NULL) {
    if (snode->CacheCount > 0) {
      snode->FreeNext = TRUE ;
      }
    else {
      if (FuncHash != NULL) delete FuncHash , FuncHash = NULL;
      if (snode->ent->hData != 0) {
        GlobalFree (snode->ent->hData) , snode->ent->hData = 0;
        SizeOverAll -= (snode->ent->GesSize_ProgStart() + snode->ent->fSize + snode->ent->cSize);
        }
      if (snode->hGScriptBackUp)
        GlobalFree (snode->hGScriptBackUp) , snode->hGScriptBackUp = 0;
      if (snode->hGConstBackUp)
        GlobalFree (snode->hGConstBackUp) , snode->hGConstBackUp = 0;
      snode->constRecBackUp = NULL;
      DWORD DataSize;
      GLOBALHANDLE hGmem = ReadScriptData (0,snode->ent->fName,&DataSize);
      LPSCRIPTCONTENT sce = LPSCRIPTCONTENT (GlobalLock (hGmem));
      *snode = sce ;
      GlobalUnlock (hGmem);
      GlobalFree (hGmem);
      snode->FreeNext = FALSE ;
      }
    }
  }

DLLExport LPSCRIPTCONTENT _export WINAPI GetFirstScript (int anzProperty,LPSTR FAR *property,LPSTR Name)
  {
  if (anzProperty == 0) {
    return (scl.first != NULL) ? scl.first->ent : NULL ;
    }
  else {
    for ( ScriptNode FAR *h = scl.first ; (h != NULL) ; h = h->Next ) {
      for (int i = 0 ; i < anzProperty ; i++) {
        char buffer[256];
        if (h->ent->GetProperty(property[i],buffer,sizeof(buffer))) {
          if (Name != NULL) {
            lstrcpy (Name,h->ent->fName);
            }
          return h->ent;
          }
        }
      }
    }
  return NULL;
  }

DLLExport LPSCRIPTCONTENT _export WINAPI GetNextScript (LPSCRIPTCONTENT old,int anzProperty,LPSTR FAR *property,LPSTR Name)
  {
  ScriptNode FAR *act = scl[old];
  if (act->Next != NULL) {
    if (anzProperty == 0) return act->Next->ent;
    for ( ScriptNode FAR *h = act->Next ; (h != NULL) ; h = h->Next) {
      for (int i = 0 ; i < anzProperty ; i++) {
        char buffer[256];
        if (h->ent->GetProperty(property[i],buffer,sizeof(buffer))) {
          if (Name != NULL) {
            lstrcpy (Name,h->ent->fName);
            }
          return h->ent;
          }
        }
      }
    }
  return NULL;
  }

DLLExport LPSCRIPTCONTENT _export WINAPI GetFirstUpdateScript ()
  {
  LoadUpdateScriptContent();
  return (scu.first != NULL) ? scu.first->ent : NULL ;
  }

DLLExport LPSCRIPTCONTENT _export WINAPI GetNextUpdateScript (LPSCRIPTCONTENT old)
  {
  ScriptNode FAR *act = scu[old];
  if (act->Next != NULL)
    return act->Next->ent ;
  else
    return NULL;
  }

#pragma pack (1)
struct cTableStart {
  WORD AnzVars;
  BYTE mType[1];
  };

struct FAR TData {
  WORD TableID;
  WORD Version;
  WORD res;
  };
#pragma pack()
DLLExport int _export WINAPI GetTableNr (LPSCRIPTCONTENT scent,WORD FAR *TableID,WORD FAR *Version,LPSTR TableName,DWORD ExtraID)
  {
  ScriptNode FAR *s = scl[scent];

  if (s != NULL) {
    if (s->NameHash == NULL) {
      s->NameHash = new hash (37,STRKEY);
      LPALIASDEF h = scent->AliasDef ;
      for ( int i = 0 ; i < scent->AnzAlias ; i++) {
        TData tdata;
        if (scent->TRef[h->TableNr].TableNr == 0) {
          tdata.TableID = 0 ;
          tdata.Version = scent->TRef[h->TableNr].Version ;
          }
        else {
          tdata.TableID = scent->TRef[h->TableNr].TableNr;
          tdata.Version = scent->TRef[h->TableNr].Version;
          }
        tdata.res = h->TableNr + CSYSRECS ;
        s->NameHash->SetData (h->AliasName,&tdata,sizeof(tdata));

        h = h->Next() ;
        }

      for (i = 0 ; (i < int (scent->AnzTables)) ; i++) {
        if (scent->TRef[i].TableNr > 0) {
          LPTABLEDEF td = GetTableAdmin()->GetTableDef(scent->TRef[i].TableNr,scent->TRef[i].Version);

          TData tdata;
          tdata.TableID = scent->TRef[i].TableNr;
          tdata.Version = scent->TRef[i].Version;
          tdata.res = i + CSYSRECS ;
          s->NameHash->SetData (td->GetName(),&tdata,sizeof(tdata));

          GetTableAdmin()->FreeTable (scent->TRef[i].TableNr,scent->TRef[i].Version);
          }
        else {
          LPSTR TableName = GetConstData (scent) + scent->TRef[i].Version ;

          TData tdata;
          tdata.TableID = 0;
          tdata.Version = scent->TRef[i].Version;
          tdata.res = i + CSYSRECS ;

          s->NameHash->SetData (TableName,&tdata,sizeof(tdata));
          }
        }
      }

    TData FAR *tx = (TData FAR *) s->NameHash->GetData (TableName);
    if (tx == NULL) {
      char t1[256],t2[256];
      lstrcpy (t1,TableName);
      GetVersionFrom (t1);
      GetPrefix (t2,scent->fName);
      lstrcat (t2,t1);
      tx = (TData FAR *) s->NameHash->GetData (t2);
      }

    if (tx != NULL) {
      if (tx->TableID == 0) {
        LPSTR TableName = GetConstData (scent) + tx->Version ;
        cTableStart FAR *ct = (cTableStart FAR *) (TableName + lstrlen(TableName) + 1) ;
        *TableID = GetTableDefFromID (ExtraID,ct->AnzVars,ct->mType);
        *Version = 0 ;
        }
      else {
        *TableID = tx->TableID ;
        *Version = tx->Version;
        }
      return tx->res ;
      }
    else
      return -1;
    }
  else {
    // Es handelt sich um eine Scriptkompilat oder um ein Updatescript
    // -> Keine Hashtabelle, Normales Handling aus der Liste
    //----------------------------------------------------------------
    LPALIASDEF h = scent->AliasDef ;
    for ( int i = 0 ; i < scent->AnzAlias ; i++) {
      if (lstrcmp (TableName,h->AliasName) == 0) {
        if (scent->TRef[h->TableNr].TableNr == 0) {
          LPSTR TableName = GetConstData (scent) + scent->TRef[h->TableNr].Version ;
          cTableStart FAR *ct = (cTableStart FAR *) (TableName + lstrlen(TableName) + 1) ;
          *TableID = GetTableDefFromID (ExtraID,ct->AnzVars,ct->mType);
          *Version = 0 ;
          }
        else {
          *TableID = scent->TRef[h->TableNr].TableNr;
          *Version = scent->TRef[h->TableNr].Version;
          }
        return h->TableNr + CSYSRECS ;
        }
      h = h->Next() ;
      }
    char t1[256],t2[256];
    lstrcpy (t1,TableName);
    WORD rVersion = GetVersionFrom (t1);
    GetPrefix (t2,scent->fName);
    lstrcat (t2,t1);
    for (i = 0 ; (i < int (scent->AnzTables)) ; i++) {
      if (scent->TRef[i].TableNr > 0) {
        LPTABLEDEF td = GetTableAdmin()->GetTableDef(scent->TRef[i].TableNr,scent->TRef[i].Version);
        if (((lstrcmp (td->GetName(),t1) == 0) ||
            (lstrcmp (td->GetName(),t2) == 0)) &&
            ((rVersion == 0xFFFF) || (rVersion == td->GetVersion()))) {
          *TableID = scent->TRef[i].TableNr;
          *Version = scent->TRef[i].Version;
          GetTableAdmin()->FreeTable (scent->TRef[i].TableNr,scent->TRef[i].Version);
          return i + CSYSRECS ;
          }
        GetTableAdmin()->FreeTable (scent->TRef[i].TableNr,scent->TRef[i].Version);
        }
      else {
        LPSTR TableName = GetConstData (scent) + scent->TRef[i].Version ;
        if (lstrcmp (TableName,t1) == 0) {
          cTableStart FAR *ct = (cTableStart FAR *) (TableName + lstrlen(TableName) + 1) ;
          *TableID = GetTableDefFromID (ExtraID,ct->AnzVars,ct->mType);
          *Version = 0 ;
          return i + CSYSRECS ;
          }
        }
      }

    return -1 ;
    }
  }

DLLExport int _export WINAPI GetTableNr (LPSCRIPTCONTENT scent,WORD FAR *TableID,WORD FAR *Version,LPSTR TableName)
  {
  return GetTableNr (scent,TableID,Version,TableName,0L);
  }

DLLExport void _export WINAPI FreeScriptData(GLOBALHANDLE FAR *hGProg,GLOBALHANDLE hGConst,LPDBRECORD constRec,LPSTR fName)
  {
  ScriptNode FAR *s = scl[fName];
  if (s == NULL) s = scu[fName];
  if ((s->hGScriptBackUp == *hGProg) && (s->hGConstBackUp == hGConst)) {
    s->CacheCount -- ;
    if ((s->CacheCount == 0) && (s->FreeNext))
      ClearCachedScript (fName);
    if (*hGProg) GlobalUnlock (*hGProg);
    *hGProg = 0 ;
    }
  else {
    SizeOverAll -= (s->ent->GesSize_ProgStart() + s->ent->fSize + s->ent->cSize);
#ifndef DEBUG
    if (!s->dataFromBlob) {
      if (*hGProg) GlobalUnlock (*hGProg) , GlobalFree (*hGProg);
      }
#endif
    if (s->doFreeConsts) {
      if (hGConst) 
        GlobalFree (hGConst);
      if (constRec) 
        delete constRec;
      }
    }
  }

