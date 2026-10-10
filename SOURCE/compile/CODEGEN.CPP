// $Header:   P:/marille/clinicum/compile/rev/codegen.cpv   1.27   26 Mar 1999 18:15:10   Wolfgang  $
// $Log:   P:/marille/clinicum/compile/rev/codegen.cpv  $
// 
//    Rev 1.27   26 Mar 1999 18:15:10   Wolfgang
// 1.) VirtualModule eingebaut.
// 
//    Rev 1.26   01 Mar 1999 13:16:52   Wolfgang
// 1.) WriteDebugInfo hat bei Formularen kein Default-Dir.
// 
//    Rev 1.25   26 Feb 1999 17:38:12   Wolfgang
// 1.) WriteDebugInfo bei entsprechender Einstellung auch fuer Formulare.
// 
//    Rev 1.24   24 Feb 1999 21:10:28   Hannes
// Buffergroesse erweitert
// 
//    Rev 1.23   12 Aug 1998 19:16:58   Wolfgang
// 1.) Verschiedene SDI-Files je nach erstem Buchstaben der Extension.
// 
//    Rev 1.22   06 Aug 1998 22:11:32   Hannes
// Konstantengroesse auf 2 KB erhoeht..
// 
//    Rev 1.21   27 May 1998 20:15:56   Hannes
// Konstantensegment - Groesse: Ueberfluessigen WinAssert raus
// 
//    Rev 1.20   26 Jan 1998 19:59:26   Hannes
// NULL als Schluesselwort
// 
//    Rev 1.19   05 Jan 1998 07:49:26   Hannes
// Einsparungen im Scriptheader
// 
//    Rev 1.18   15 Dec 1997 17:58:00   Hannes
// Diverse Verbesserungen
// 
//    Rev 1.17   08 Jul 1997 12:00:18   Hannes
// 
//    Rev 1.16   09 Jun 1997 13:09:54   Hannes
// No change.
// 
//    Rev 1.15   13 Mar 1997 19:05:22   Hannes
// GenerateScriptFromBlob
// 
//    Rev 1.14   19 Feb 1997 12:04:12   Hannes
// Scriptfunktionen
// 
//    Rev 1.13   26 Nov 1996 07:56:50   HANNES
// Versionshistory von DDD's
// 
//    Rev 1.12   21 Oct 1996 18:50:46   HANNES
// Einbau von Aliasnamen in das Script
// 
//    Rev 1.11   17 Jun 1996 15:27:58   HANNES
// Einfuehrung von BLOBS
// 
//    Rev 1.10   02 Feb 1996 10:41:32   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.9   11 Jul 1995 12:44:16   HANNES
// Statische Daten in die Klasse
// 
//    Rev 1.8   09 Jun 1995 00:22:10   HANNES
// Umbau der Konstaten auf normale Tabelle
// 
//    Rev 1.7   15 May 1995 08:23:00   HANNES
// structs im normalen Script
// 
//    Rev 1.6   26 Apr 1995 15:33:44   HANNES
// 
//    Rev 1.5   24 Feb 1995 11:10:34   HANNES
// 
//    Rev 1.4   10 Jan 1995 14:59:10   HANNES
// Fehlerkorrektur
// 
//    Rev 1.3   09 Jan 1995 12:06:56   HANNES
// Debugger eingebaut
// 
//    Rev 1.2   07 Dec 1994 14:01:24   GERHOLD
// Umwandlung von (*LPDWORD(res)) -> *(LPDWORD)res
// 
//    Rev 1.1   05 Dec 1994 17:36:10   HANNES
// Endgueltiger Einbau der Expressions
// 
//    Rev 1.0   24 Jun 1994 16:30:22   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.15   03 Apr 1994 18:58:12   HANNES
// pushData auf DWORD umgebaut (speziell fuer Pop)
// 
//    Rev 1.14   04 Feb 1994 16:52:32   HANNES
// Dynamisches Linken eingebaut
// 
//    Rev 1.13   27 Oct 1993 19:59:54   HANNES
// dds.hpp umstellung
// 
//    Rev 1.12   08 Oct 1993 17:55:22   HANNES
// pushConst
// 
//    Rev 1.11   24 Sep 1993 22:45:12   HANNES
// Verkettung der Help - Zeiger
// 
//    Rev 1.10   05 Sep 1993 22:06:32   HANNES
// ?
// 
//    Rev 1.9   20 Jul 1993 12:36:38   HANNES
// Icons fuer die Programme
// 
//    Rev 1.8   07 Jun 1993 15:11:58   HANNES
// Bufferhandling
// 
//    Rev 1.7   24 May 1993 14:23:12   HANNES
// Expressions
// 
//    Rev 1.6   02 Apr 1993 18:07:56   HANNES
// Erweiterungen..
// 
//    Rev 1.5   11 Mar 1993 20:05:36   HANNES
// Mehr als 2 Btrieve Records in einem Programm
// 
//    Rev 1.4   08 Mar 1993 14:19:22   HANNES
// Erweiterungen in Bezug auf den Editor
// 
//    Rev 1.3   22 Feb 1993 17:27:06   HANNES
// Code auf mehrer Records aufteilen, unabhaengiges Konstantensegment
// 
//    Rev 1.2   18 Jan 1993 16:55:14   HANNES
// Die Kategorie im Compile - Header vermerken
// 
//    Rev 1.1   13 Jan 1993 18:54:34   HANNES
// Veraenderungen des Headers eines Dokumentes
// 
//    Rev 1.0   02 Dec 1992 16:14:48   HANNES
// Initial revision.
/*-----------------------------------------------------
        Funktionen fuer die Code - Generierung
        Bufferverwaltung
-----------------------------------------------------*/
// #define TEST

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "dds32.h"
#define JUST_EM
#include "dds.hpp"
#include "globmem.h"
#include "hash.hpp"
#include "btrieve.hpp"
#include "compile.hpp"
#include "data.hpp"
#define MODULENUM 50
#include "winass.hpp"

#include "scripthd.hpp"
#include "dlladmin.h"
#include "dlladmin.hpp"

#include "scdb.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"


void compiler::inclevel ()
  {
  if (level < MAX_DEPTH - 1) level++;
  else wError = TERM_TOOCOMPLEX;
  }

/*------------------------------------------------------------------*/
/* pushData:                                                        */
/* Es werden Daten in den aktuellen buffer (= level) geschrieben,   */
/* In den Buffern ist prinzipiell das erste WORD die Groesse des    */
/* Buffers                                                          */
/*------------------------------------------------------------------*/
#define BUFFERSTEP    0x1000
inline GLOBALHANDLE MyGlobalAlloc (UINT flags,DWORD size)
  {
  size /= BUFFERSTEP;
  size = (size + 1) * BUFFERSTEP ;
  return GlobalAlloc (flags,size);
  }

inline GLOBALHANDLE MyGlobalReAlloc (GLOBALHANDLE hGmem,DWORD size,UINT flags)
  {
  size /= BUFFERSTEP;
  size = (size + 1) * BUFFERSTEP ;
  return GlobalReAlloc (hGmem,size,flags);
  }

void compiler::PrepCodeGen (void)
  {
  level = 0 ;
  codebuffer[0] = MyGlobalAlloc (GHND,2 * sizeof (DWORD));
  char FAR *base = LPSTR(GlobalLock (codebuffer[0]));
  *(WORD FAR *) base = 2 * sizeof (DWORD);
  GlobalUnlock (codebuffer[0]);
  }

void compiler::pushData (void FAR *data,DWORD size)
  {
  char FAR *base;
  DWORD actsize;
  if (codebuffer[level]) {
    // Realloc des Buffers
    base = LPSTR(GlobalLock (codebuffer[level]));
    actsize = * (DWORD FAR *)base ;
    GlobalUnlock (codebuffer[level]);
    codebuffer[level] = MyGlobalReAlloc (codebuffer[level],actsize+size,
                                       GMEM_MOVEABLE);
    }
  else {
    codebuffer[level] = MyGlobalAlloc (GHND,sizeof (DWORD) + size);
    actsize = sizeof (DWORD);
    }
  base = LPSTR(GlobalLock (codebuffer[level]));
  hmemcpy ((char _huge *) base+actsize,data,size);
  *(DWORD FAR *) base = actsize + size;
  GlobalUnlock (codebuffer[level]);
  }

void compiler::pushWord (WORD w)
  {
  pushData (&w,sizeof (WORD));
  }

void compiler::pushDWord (DWORD w)
  {
  pushData (&w,sizeof (DWORD));
  }

void compiler::pushPars0 ()
  {
  char FAR *str = LPSTR(GlobalLock (hPars0));
  pushData (str+sizeof (WORD),* (WORD FAR *) str - sizeof (WORD));
  GlobalUnlock (hPars0);
  }

WORD compiler::sizePars0 ()
  {
  WORD res ;
  char FAR *str = LPSTR(GlobalLock (hPars0));
  res = * (WORD FAR *) str - sizeof (WORD);
  GlobalUnlock (hPars0);
  return res ;
  }

DWORD compiler::actSize ()
  {
  DWORD res ;
  if (codebuffer[level]) {
    DWORD FAR *base = (DWORD FAR *) GlobalLock (codebuffer[level]) ;
    res = *base - sizeof (DWORD);
    GlobalUnlock (codebuffer[level]);
    }
  else res = 0 ;
  return res ;
  }

void ScriptCompiler::pushOp (WORD Op)
  {
  if (level > 0) {
    DWORD size = actSize ();
    level -- ;
    pushWord (Op);
    pushDWord (size + sizeof (DWORD));
    level ++ ;
    Pop ();
    DWORD end = progOffs() - sizeof(DWORD);
    CorrectLookupIdents (end - size,end);
    if (InInlineFunction()) {
      end = fncOffs() - sizeof(WORD);
      CorrectIdentOffsets (end - size,end);
      }
    }
  else
    wError = SEM_ERROR ;
  }

void compiler::Pop (void)
  {
  if (level > 0) {
    if (codebuffer[level]) {
      char FAR *base = LPSTR(GlobalLock (codebuffer[level]));
      level -- ;
      pushData (base+sizeof (DWORD),* (DWORD FAR *) base - sizeof (DWORD));
      level ++ ;
      GlobalUnlock (codebuffer[level]);
      }
    Clear ();
    }
  else
    wError = SEM_ERROR ;
  }

void ScriptCompiler::MarkCond(void)
  {
  bCondBuffer[level] |= IS_CONDITION ;
  }

void ScriptCompiler::MarkProcBuffer(void)
  {
  bCondBuffer[level] |= IS_PROCEDURE ;
  }

void ScriptCompiler::ClearCond(void)
  {
  bCondBuffer[level] &= ~IS_CONDITION ;
  }

void ScriptCompiler::ClearProcBuffer(void)
  {
  bCondBuffer[level] &= ~IS_PROCEDURE ;
  }

void compiler::Clear (void)
  {
  if (level > 0) {
    if (codebuffer[level]) GlobalFree (codebuffer[level]) ;
    codebuffer[level] = NULL ;
    level -- ;
    }
  else
    wError = SEM_ERROR ;
  }

#define MAXHANDLES  16
// Aufbau eines Sammelblocks:
//  - WORD AnzahlBlocks
//  - DWORD * MAXHANDLES: Offset der Bloecke
//  - DWORD * MAXHANDLES: Laenge der Bloecke
GLOBALHANDLE UnionBlocks (GLOBALHANDLE FAR *hG,int AnzHandles)
  {
  DWORD blockOffs[MAXHANDLES];
  DWORD blockLen[MAXHANDLES];
  WIN_ASSERT ((MAXHANDLES >= AnzHandles) && (AnzHandles > 0)) ;
  lmemset (blockOffs,'\0',sizeof(blockOffs));
  lmemset (blockLen,'\0',sizeof(blockLen));
  for (int i = 0 ; i < AnzHandles ; i++) {
    if (i == 0)
      blockOffs[0] = sizeof(WORD) + sizeof (blockOffs) + sizeof(blockLen);
    else
      blockOffs[i] = blockOffs[i-1] + blockLen[i-1];
    blockLen [i] = GlobalSize (hG[i]);
    }
  GLOBALHANDLE hGres = GlobalAlloc (GMEM_MOVEABLE,blockOffs[AnzHandles-1] + blockLen[AnzHandles-1]);
  WIN_ASSERT (hGres);
  LPSTR base = LPSTR(GlobalLock (hGres));
  lmemcpy (base,&AnzHandles,sizeof(WORD));
  lmemcpy (base+sizeof(WORD),blockOffs,sizeof(blockOffs));
  lmemcpy (base+sizeof(WORD)+sizeof(blockOffs),blockLen,sizeof(blockLen));
  for (i = 0 ; i < AnzHandles ; i++) {
    LPSTR blmem = LPSTR(GlobalLock (hG[i]));
    hmemcpy (((char huge *)base) + blockOffs[i],blmem,blockLen[i]);
    GlobalUnlock (hG[i]);
    }
  GlobalUnlock (hGres);

  return hGres;
  }

void ScriptCompiler::PutConstBuffer (GLOBALHANDLE hGc)
  {
  // Kopieren der Konstanten in den Buffer
#ifdef UEBERLEGT
  if (hGc) {
    progkey hlpkey;
    lmemcpy (&hlpkey,key,sizeof(progkey));
    hlpkey.RecordType -= 1 ;
    LPSTR lpconst = GlobalLock (hGc);
    GLOBALHANDLE hGtmp = GlobalAlloc (GHND,
                      *((WORD FAR *) lpconst) + sizeof (progkey) 
                                     );
    char FAR *buffer = GlobalLock (hGtmp);
    lmemcpy (buffer,&hlpkey,sizeof(progkey));
    lmemcpy (buffer+sizeof(progkey),lpconst,*((WORD FAR *) lpconst));
#ifndef TEST
    ProgFile->Put (buffer,*((WORD FAR *) lpconst) + sizeof(progkey));
#endif
    GlobalUnlock (hGc);
    GlobalUnlock (hGtmp);
    GlobalFree (hGtmp);
    }
#endif
  }

ScriptContent_Entry scent;
LPSTR GetFName(LPVOID fname)
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

void GetTypes (hash *h,BYTE FAR *Types,WORD DBNummer)
  {
  GLOBALHANDLE hGres = 0;
  for (int i = 0 ; i < int (h->hash_dimension) ; i++) {
    for (LPhash_entry e = h->Table + i ; e != NULL ; ) {
      if (!h->is_empty (e)) {
        full_vardef FAR *d = (full_vardef FAR *) e->Data;
        if (d->vd.DBNummer == DBNummer) {
          Types[d->vd.Ident] = d->vartype ;
          }
        }
      e = h->NextEnt (e);
      }
    }
  }

WORD GetTypeSize (hash *h,WORD DBNummer)
  {
  GLOBALHANDLE hGres = 0;
  WORD res = 0 ;
  for (int i = 0 ; i < int (h->hash_dimension) ; i++) {
    for (LPhash_entry e = h->Table + i ; e != NULL ; ) {
      if (!h->is_empty (e)) {
        full_vardef FAR *d = (full_vardef FAR *) e->Data;
        if (d->vd.DBNummer == DBNummer) {
          res ++ ;
          }
        }
      e = h->NextEnt (e);
      }
    }
  return res ;
  }

WORD GetFuncTypeSize (LocalHashList FAR *lhlist)
  {
  WORD res = 0 ;
  for (LocalHashList FAR *lh = lhlist ; lh != NULL ; lh = lh->Next) {
    res += sizeof(_FuncTypeList);
    res += GetTypeSize (lh->h,DYNLOCALDATA);
    res += GetTypeSize (lh->h,STATICLOCALDATA);
    }
  return res;
  }

void GetFuncTypes (LocalHashList FAR *lhlist,char huge *h)
  {
  _FuncTypeList FAR *prev = NULL ;
  DWORD actOffset = 0L ;
  for (LocalHashList FAR *lh = lhlist ; lh != NULL ; lh = lh->Next) {
    _FuncTypeList FAR *ft = (_FuncTypeList FAR *) h ;
    ft->procPtr = lh->procOffset;
    ft->d.NextTypeListOffset = 0L ;
    if (prev != NULL)
      prev->d.NextTypeListOffset = actOffset ;
    ft->AnzDynLocals = GetTypeSize (lh->h,DYNLOCALDATA);
    ft->AnzStaticLocals = GetTypeSize (lh->h,STATICLOCALDATA);
    h += sizeof(*ft); actOffset += sizeof(*ft);
    GetTypes (lh->h,(BYTE FAR *) h,DYNLOCALDATA);
    h += ft->AnzDynLocals; actOffset += ft->AnzDynLocals;
    GetTypes (lh->h,(BYTE FAR *) h,STATICLOCALDATA);
    h += ft->AnzStaticLocals; actOffset += ft->AnzStaticLocals;
    prev = ft ;
    }
  }

extern WORD GetAliasSize (short FAR *AnzAlias);
extern void GetAliasData (char huge *Buffer);
LPSTR PushVersionString (LPSTR old,LPSTR h,LPSTR prefix,char connect);
extern LPSTR GetUpdateProperty_From ();
extern LPSTR GetUpdateProperty_To ();
GLOBALHANDLE StoreOpHash(hash *op,BYTE FTyp,BOOL FAR *IsEmpty);
LPVOID PushToGlobMem (LPVOID old,LPVOID data,int Size)
  {
  LPVOID r;
  if (old) {
    r = GetGlobMem (GetBlockSize (old) + Size);
    lmemcpy (r,old,GetBlockSize(old));
    lmemcpy (LPSTR(r) + GetBlockSize(old),data,Size);
    FreeGlobMem (old);
    }
  else {
    r = GetGlobMem (Size);
    lmemcpy (r,data,Size);
    }
  return r ;
  }

DLLExport void _export WINAPI ScriptCompiler::EndOfWriteRes (LPSTR FromVersion,GLOBALHANDLE hGres,DWORD gSize)
  {
  if (FromVersion == NULL)
    WriteScriptData (0,scent.fName,hGres,gSize);
  else {
    WriteScriptData (3,scent.fName,hGres,gSize);
    CreateUpdateScriptContent(scent.fName);
    }

  GlobalUnlock (hGres);
  GlobalFree   (hGres);
  // Schreiben der Debug - Info
  WriteDebugInfo (scent.fName,DEBUGENT,DEBUGDEF);
  }

DLLExport void _export WINAPI BlobScriptCompiler::EndOfWriteRes (LPSTR FromVersion,GLOBALHANDLE hGres,DWORD gSize)
  {
  hGRes = hGres;
  SizeOfRes = gSize;
  WriteDebugInfo (scent.fName,DEBUGFORMSENT,"");
  }

void ScriptCompiler::WriteRes (LPVOID key,LPVOID fname)
  {
  if ((codebuffer[0]) && (edp == NULL)) {   // Beim editor wird kein resultat geschrieben
    // Nachtragen der Ident - Nummern (auch im Editor)
    /////////////////////////////////////////////////////
    char FAR *res = LPSTR(GlobalLock (codebuffer[0]));
    IdentHash *h = FixLUHash ();
    h->LookUpIdents ((BYTE FAR *) res);
    ReleaseLUHash ();

    // Anhaengen der Expressions
    ///////////////////////////////////
    DWORD ExpBaseOffs = *((DWORD FAR *) res);
    GlobalUnlock (codebuffer[0]);

    AddExpressions ();

    res = LPSTR(GlobalLock (codebuffer[0]));

    // Korrigieren aller Offsets in den Expressions
    ///////////////////////////////////////////////////
    CorrectExpOffs ((char huge *) res,ExpBaseOffs,0L);

    // Korrigieren aller Offsets auf Expressions im Hauptblock
    /////////////////////////////////////////////////////////////
    FixupExpOffs ((char huge *) res,ExpBaseOffs,0L);

    WORD ExtHdSize = 0;
    GLOBALHANDLE hDIB = 0;
    if (*IconName)
      hDIB = ReadProgIcon (IconName,&ExtHdSize);

    LPSTR FromVersion = GetUpdateProperty_From();
    LPSTR ToVersion = GetUpdateProperty_To();

    if ((FromVersion != NULL) && (ToVersion == NULL))
      wError = NODESTVERSION;
    if (wError == 0) {
      // Daten schreiben
      LPSTR lpconst = LPSTR(GlobalLock (constbuffer));
      if (constbuffer)
        lpconst = LPSTR(GlobalLock (constbuffer));
      else
        lpconst = NULL;
      TableRef FAR *aTRef = scent.TRef;
      scent.TRef = NULL ;
      lstrncpy (scent.Name,fullname,sizeof(scent.Name));
      lstrcpy  (scent.fName,GetFName(fname));
      scent.Category  = Category;
      scent.Type      = Type;
      scent.fSize     = *(LPDWORD)res ;
      scent.cSize     = DWORD ((constbuffer != 0) ? *(LPWORD (lpconst)) : 0);
      scent.AnzLocals = ActFreeVar;
      scent.AnzHelps  = ActFreeHVar;
      scent.AnzConsts = AnzConsts;
      scent.IconSize  = ExtHdSize;
      scent.IconData  = NULL;   // IconDaten werden dann hinter dem
                                // Header angefuegt
      scent.PropertyData = NULL ;
      if (FromVersion != NULL) {
        PropertyString = PushVersionString (PropertyString,FromVersion,NULL,',');
        PropertyString = PushVersionString (PropertyString,ToVersion,NULL,',');
        }
      if (PropertyString != NULL)
        scent.PropertySize = lstrlen(PropertyString) + 1 ;
      else
        scent.PropertySize = 0 ;
      scent.AliasDefSize = GetAliasSize (&scent.AnzAlias);
      scent.FuncTypeSize = GetFuncTypeSize (lhlist);
      if (MyImportModules != NULL) {
        char n = '\0' ;
        MyImportModules = PushToGlobMem (MyImportModules,&n,1);
        scent.ImportModuleSize = GetBlockSize(MyImportModules);
        }
      else {
        scent.ImportModuleSize = 0;
        }
      if (MyBaseModules != NULL) {
        char n = '\0' ;
        MyBaseModules = PushToGlobMem (MyBaseModules,&n,1);
        scent.BaseModuleSize = GetBlockSize(MyBaseModules);
        }
      else {
        scent.BaseModuleSize = 0;
        }
      if (MyVirtualModules != NULL) {
        char n = '\0' ;
        MyVirtualModules = PushToGlobMem (MyVirtualModules,&n,1);
        scent.VirtualModuleSize = GetBlockSize(MyVirtualModules);
        }
      else {
        scent.VirtualModuleSize = 0;
        }
      BOOL IsEmpty;
      GLOBALHANDLE hEfMem;
      if (!ImportDone)
        hEfMem = StoreOpHash (hefHash,FTYPE_EXPORT,&IsEmpty);
      else {
        IsEmpty = TRUE ;
        hEfMem = 0;
        }
      if (!IsEmpty)
        scent.ExportTypeSize = int(GlobalSize (hEfMem));
      else
        scent.ExportTypeSize = 0;

      // Alle Daten zusammenholen
      DWORD gSize = sizeof(scent) + 
                          DWORD(scent.IconSize) + 
                          DWORD(scent.AnzTables * sizeof(TableRef)) +
                          DWORD(scent.PropertySize) +
                          scent.cSize + scent.fSize + 
                          sizeof(BYTE) * scent.AnzLocals + 
                          sizeof(BYTE) * scent.AnzHelps +
                          DWORD (scent.ExportTypeSize) +
                          DWORD (scent.FuncTypeSize) +
                          DWORD (scent.AliasDefSize) +
                          DWORD (scent.ImportModuleSize) +
                          DWORD (scent.BaseModuleSize) +
                          DWORD (scent.VirtualModuleSize) ;

      GLOBALHANDLE hGres = GlobalAlloc (GMEM_MOVEABLE,gSize);
      LPSTR base = LPSTR(GlobalLock (hGres));
      char huge *h = (char huge *) base;
      lmemcpy (h,&scent,sizeof(scent));
      h += sizeof(scent);
      if (hDIB) {
        lmemcpy (h,GlobalLock (hDIB),ExtHdSize);
        GlobalUnlock (hDIB);
        GlobalFree (hDIB);
        h += ExtHdSize;
        }
      if (PropertyString != NULL) {
        lmemcpy (h,PropertyString,lstrlen(PropertyString)+1);
        h += scent.PropertySize ;
        }
      if (aTRef != NULL) {
        lmemcpy (h,aTRef,scent.AnzTables * sizeof(TableRef));
        h += DWORD(scent.AnzTables * sizeof(TableRef));
        }
      GetAliasData (h);
      h += scent.AliasDefSize ;
      if (MyImportModules) {
        hmemcpy (h,MyImportModules,scent.ImportModuleSize);
        h += scent.ImportModuleSize;
        }
      if (MyBaseModules) {
        hmemcpy (h,MyBaseModules,scent.BaseModuleSize);
        h += scent.BaseModuleSize;
        }
      if (MyVirtualModules) {
        hmemcpy (h,MyVirtualModules,scent.VirtualModuleSize);
        h += scent.VirtualModuleSize;
        }
      if (scent.ExportTypeSize) {
        hmemcpy (h,GlobalLock (hEfMem),scent.ExportTypeSize);
        GlobalUnlock (hEfMem);
        }
      h += scent.ExportTypeSize ;

      // Die Restlichen Daten werden erst bei dem Laden des Programms ausgefuehrt
      GetTypes (hVrHash,LPBYTE(h),0);   // Typen der Localen Daten
      h += sizeof(BYTE) * scent.AnzLocals;
      GetTypes (hVrHash,LPBYTE(h),HELPDATA);   // Typen der Help Daten
      h += sizeof(BYTE) * scent.AnzHelps;
      GetFuncTypes (lhlist,h);
      h += scent.FuncTypeSize ;
      if (constbuffer)
        hmemcpy (h,lpconst,scent.cSize);
      h += scent.cSize;
      hmemcpy (h,res,scent.fSize);

      EndOfWriteRes (FromVersion,hGres,gSize);

      if (hEfMem) GlobalFree (hEfMem);
      if (aTRef != NULL)
        FreeGlobMem (aTRef);
      }
    }
  }

WORD ScriptCompiler::pushConst (void FAR *data,WORD size,WORD mType,BOOL WriteLength,BOOL MultiUse)
  {
  if (constbuffer == 0) {
    constbuffer = MyGlobalAlloc (GHND,4 * sizeof(WORD));  // 1. Wort: Groesse des Buffers
                                                          // 2. Wort: Start der Help Zeiger
    WORD FAR *lpsize = (WORD FAR *) GlobalLock (constbuffer);
    *lpsize = 2 * sizeof(WORD);
    GlobalUnlock (constbuffer);
    }
  LPSTR buffer = LPSTR(GlobalLock (constbuffer));
  WORD res = *((WORD FAR *) buffer);
  // Anlegen des Laengenbytes
  LPSTR dtopush;
  char GBuffer[0x2000];
  if (size > sizeof(GBuffer) - 2 * sizeof(WORD)) {
    WIN_ASSERT_TEXT(FALSE,"Konstante groesser als 2 KB nicht erlaubt");
    }
  WORD pushsize;
  WORD extoffs;
  if (WriteLength) {
    ((WORD FAR *) GBuffer)[0] = mType;
    ((WORD FAR *) GBuffer)[1] = size;
    lmemcpy (GBuffer + 2 * sizeof(WORD),data,size);
    dtopush = GBuffer;
    pushsize = size + 2 * sizeof(WORD);
    extoffs = 2 * sizeof(WORD);
    }
  else {
    ((WORD FAR *) GBuffer)[1] = mType;
    lmemcpy (GBuffer + sizeof(WORD),data,size);
    dtopush = GBuffer;
    pushsize = size + sizeof(WORD);
    extoffs = sizeof(WORD);
    }

  // Untersuchen, ob Daten mehrfach verwendet werden koennen
  BOOL found = FALSE ;
  WORD gSize = *(WORD FAR *)buffer;
  if (MultiUse) {
    int j = 0 ;
    for (WORD act = 2 * sizeof(WORD) + 2 * sizeof(WORD); 
                  act < gSize; 
                          act += 2 * sizeof(WORD) + ((WORD FAR *) (buffer + act))[-1] ) {
      if (lmemcmp(buffer + act - 2 * sizeof(WORD),dtopush,pushsize)) {
        found = TRUE ;
        res = j ;
        }
      j ++ ;
      }
    }
  GlobalUnlock (constbuffer);
  if (!found) {
#ifndef WIN32
    WIN_ASSERT ((gSize + pushsize) < BUFFERSIZE);
#endif
    // Hilft nichts, muss neu angelegt werden
    constbuffer = MyGlobalReAlloc (constbuffer,gSize + pushsize,GMEM_MOVEABLE);
    buffer = LPSTR(GlobalLock (constbuffer));
    lmemcpy (buffer + gSize,dtopush,pushsize);
    *((WORD FAR *) buffer) += pushsize;
    GlobalUnlock (constbuffer);
    res = AnzConsts ;
    AnzConsts ++ ;
    }
  return res ;
  }

WORD ScriptCompiler::ConstSize ()
  {
  WORD res;
  if (constbuffer == 0) 
    res = 0 ;
  else {
    WORD FAR *lpsize = (WORD FAR *) GlobalLock (constbuffer);
    res = *lpsize ;
    GlobalUnlock (constbuffer);
    }
  return res;
  }

// Es geht darum, zu verhindern, dass irgendein Parameterblock auf eine
// 64 k Grenze stoesst. Dadurch reicht es aus, wenn der Interpreter alleine
// mit huge Arithmetik arbeitet
//////////////////////////////////////////////////////////////////////////
void compiler::CheckSegs (WORD Size)
  {
  if ((_actcmpl != NULL) && (_actcmpl->dontCheckSeg)) return ;
  if (Size < 0x0100)
    Size = 0x0100;
  DWORD ActSize = progOffs ();
  DWORD SegOffs = ActSize % 0xFFFF ;
  if (LONG(SegOffs) >= LONG(0xFFFF - Size - 5)) {
    GLOBALHANDLE hGmem = GlobalAlloc (GHND,Size + 0x10);
    LPSTR DummyBuffer = LPSTR(GlobalLock (hGmem));
    ((WORD FAR *) DummyBuffer)[0] = PREFIX_NOP;
    ((WORD FAR *) DummyBuffer)[1] = Size + 0x10 - sizeof(WORD);
    pushData (DummyBuffer,Size + 0x10);
    GlobalUnlock (hGmem);
    GlobalFree (hGmem);
    }
  }

void compiler::CheckSegs ()
  {
  CheckSegs (0x0100);
  }

/*--------------< Debugger - Infos >-------------*/
void ScriptCompiler::InitializeDebugInfo ()
  {
  lmemset (&dHd,'\0',sizeof(dHd));
  hGDebugInfo = 0;
  fEDD = NULL;
  }

void ScriptCompiler::FreeDebugInfo ()
  {
  if (hGDebugInfo) GlobalFree (hGDebugInfo) , hGDebugInfo = 0 ;
  }

int ScriptCompiler::GetIncludeNumber ()
  {
  LPSTR Name = (in_include) ? finame : fmname ;
  LPSTR FName = GetFName(Name);
  for (int i = 0 ; i < dHd.AnzFiles ; i++) {
    if (lstrcmp (dHd.ent[i].FName,FName) == 0) return i ;
    }
  lstrcpy (dHd.ent[i].FName,FName);
  dHd.AnzFiles ++ ;
  return i ;
  }

void ScriptCompiler::PushProgOffs ()
  {
  lastProgOffs = progOffs();
  }

GLOBALHANDLE PushDData (GLOBALHANDLE hGData,LPVOID data,int size)
  {
  LPSTR base;
  DWORD actsize;
  if (hGData) {
    // Realloc des Buffers
    base = LPSTR(GlobalLock (hGData));
    actsize = * (DWORD FAR *)base ;
    GlobalUnlock (hGData);
    hGData = MyGlobalReAlloc (hGData,actsize+size,
                                       GMEM_MOVEABLE);
    }
  else {
    hGData = MyGlobalAlloc (GHND,sizeof (DWORD) + size);
    actsize = sizeof (DWORD);
    }
  base = LPSTR(GlobalLock (hGData));
  hmemcpy ((char _huge *) base+actsize,data,size);
  *(DWORD FAR *) base = actsize + size;
  GlobalUnlock (hGData);
  return hGData;
  }

void ScriptCompiler::DebugPush (ScriptDebugInfo FAR *sdi)
  {
  hGDebugInfo = PushDData (hGDebugInfo,sdi,sizeof(*sdi));
  }

void ScriptCompiler::Debug_SetProgOffs ()
  {
  ScriptDebugInfo sdi;
  sdi.IncNmbr = GetIncludeNumber ();
  sdi.LineNmbr = (in_include) ? IncLineNr : LineNr;
  sdi.progOffs = lastProgOffs;
  DebugPush (&sdi);
  }

void ScriptCompiler::MarkForExpDebPush (DWORD Offs)
  {
  ExpDebData FAR *n = (ExpDebData FAR *) GetGlobMem (sizeof(*n));
  n->Next = fEDD;
  fEDD = n;
  n->sdi.IncNmbr = GetIncludeNumber ();
  n->sdi.LineNmbr = (in_include) ? IncLineNr : LineNr;
  n->sdi.progOffs = Offs;
  }
void ScriptCompiler::DoExpDebPush (DWORD Offs)
  {
  for ( ; fEDD != NULL ; ) {
    ExpDebData FAR *n = fEDD->Next;
    // fEDD->sdi.progOffs += Offs;
    fEDD->sdi.progOffs = Correct_dwOffs(fEDD->sdi.progOffs) + Offs + sizeof(WORD);
    DebugPush (&fEDD->sdi);
    FreeGlobMem (fEDD);
    fEDD = n;
    }
  }

GLOBALHANDLE GetLocalData (GLOBALHANDLE hGres,hash *h,DWORD fOffs)
  {
  LocalVarInfo lv;
  for (int i = 0 ; i < int (h->hash_dimension) ; i++) {
    for (LPhash_entry e = h->Table + i ; e != NULL ; ) {
      if (!h->is_empty (e)) {
        full_vardef FAR *d = (full_vardef FAR *) e->Data;
        if ((d->vd.DBNummer < CSYSRECS) || (d->vd.DBNummer == HELPDATA)) {
          if (d->vd.DBNummer == HELPDATA)
            lv.TableNr = 1;
          else
            lv.TableNr = d->vd.DBNummer;
          lv.fOffs = fOffs ;
          lv.VarNr = d->vd.Ident;
          lv.mType = d->vartype;
          hGres = PushDData (hGres,&lv,sizeof(lv)-sizeof(lv.Name));
          hGres = PushDData (hGres,e->key.strkey,lstrlen(e->key.strkey)+1);
          }
        }
      e = h->NextEnt (e);
      }
    }
  return hGres;
  }

void ScriptCompiler::WriteDebugInfo (LPSTR name, LPSTR dirIniName, LPSTR dirDefName)
  {
  char fName[128];
  char fName1[128];
  if (GetPrivateProfileString (SCRIPTSECTION,dirIniName,dirDefName,fName1,sizeof(fName1),MYINI) > 0) {
    lstrcpy (fName,name);
    BOOL done = FALSE ;
    for ( LPSTR h = fName ; *h ; h++) {
      if (*h == '.') {
        if (*(h+1))
          lstrcpy (h+2,SDIEXT);
        else
          lstrcpy (h+1,SDIEXT);
        done = TRUE ;
        break ;
        }
      }
    if (!done) {
      *h = '.' ;
      lstrcpy (h+1,SDIEXT);
      }
    OFSTRUCT Of;
    lstrcat (fName1,fName);
    int fi = OpenFile (fName1,&Of,OF_WRITE | OF_CREATE);
  
#ifdef WIN32
    _lwrite (fi,LPSTR(&dHd),sizeof(dHd));
#else
    _lwrite (fi,&dHd,sizeof(dHd));
#endif
  
    if (hGDebugInfo) {
      LPSTR dbi = LPSTR(GlobalLock (hGDebugInfo));
      _hwrite (fi,dbi,*((DWORD FAR *) dbi));
      GlobalUnlock (hGDebugInfo);
      }
    else {
      DWORD none = 0L;
  
#ifdef WIN32
      _lwrite (fi,LPSTR(&none),sizeof(none));
#else
      _lwrite (fi,&none,sizeof(none));
#endif
      }
  
    GLOBALHANDLE hGLocalData = 0;
    hGLocalData = GetLocalData (hGLocalData,hVrHash,0L);
    for (LocalHashList FAR *lh = lhlist ; lh != NULL ; lh = lh->Next)
      hGLocalData = GetLocalData (hGLocalData,lh->h,lh->procOffset);
    if (hGLocalData) {
      LPSTR dbi = LPSTR(GlobalLock (hGLocalData));
      _hwrite (fi,dbi,*((DWORD FAR *) dbi));
      GlobalUnlock (hGLocalData);
      GlobalFree (hGLocalData);
      }
    else {
      DWORD none = 0L;
  
#ifdef WIN32
      _lwrite (fi,LPSTR(&none),sizeof(none));
#else
      _lwrite (fi,&none,sizeof(none));
#endif
  
      }
  
    _lclose (fi);
    }
  }

