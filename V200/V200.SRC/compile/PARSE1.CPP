///////////////////////////////////////////////////////////////
//      Neue Funktionen zur Behandlung der Expressions
///////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/compile/rev/parse1.cpv   1.49   16 Feb 2000 15:03:10   Wolfgang  $
//  $Log:   P:/marille/clinicum/compile/rev/parse1.cpv  $
// 
//    Rev 1.49   16 Feb 2000 15:03:10   Wolfgang
// 1.) In makecmplt auf doppelte Funktionen pruefen.
// 2.) Dazu lastoplist eingebaut.
// 
//    Rev 1.48   26 Mar 1999 18:15:26   Wolfgang
// 1.) FTYPE_VIRTUAL verarbeiten.
// 
//    Rev 1.47   14 Aug 1998 18:52:04   Hannes
// GetMainTable
// 
//    Rev 1.46   04 Aug 1998 17:47:16   Hannes
// Timestamp
// 
//    Rev 1.45   17 May 1998 17:52:56   Hannes
// Variable viele Parameter in Funktionsmappings
// 
//    Rev 1.44   26 Jan 1998 19:59:40   Hannes
// NULL als Schluesselwort
// 
//    Rev 1.43   05 Jan 1998 07:49:16   Hannes
// Einsparungen im Scriptheader
// 
//    Rev 1.42   19 Nov 1997 18:45:52   Hannes
// Restool 32 Bit umstellung
// 
//    Rev 1.41   07 Nov 1997 12:31:06   Hannes
// ~opfobj
// 
//    Rev 1.40   06 Nov 1997 19:25:44   Hannes
// Verbesserung der Updatenummer
// 
//    Rev 1.39   04 Nov 1997 14:54:40   Hannes
// 
//    Rev 1.38   24 Oct 1997 08:37:56   Hannes
// Umstellung von mdiChild zwecks Speichersparmassnahmen
// 
//    Rev 1.37   22 Aug 1997 12:01:54   Hannes
// TwoDim: GetGlobalMem ausgebaut
// 
//    Rev 1.36   19 Aug 1997 17:20:28   Martin
// Lookupfehler bei Segmentspruengen im ExpressionCompiler
// 
//    Rev 1.35   04 Aug 1997 12:35:04   Hannes
// CheckSegs nur, wenn die Funktion wirklich in das Compilat geschrieben wird
// 
//    Rev 1.34   08 Jul 1997 12:00:24   Hannes
// 
//    Rev 1.33   25 Jun 1997 16:26:30   Hannes
// Segmentueberlauf im Speicherhandling
// 
//    Rev 1.32   20 Jun 1997 14:38:58   Hannes
// Segmentfehler bei Expressions
// 
//    Rev 1.31   09 Jun 1997 13:09:54   Hannes
// 
//    Rev 1.30   27 May 1997 11:19:00   Hannes
// Private Strukturen im Scriptkompilat, L. als Expression
// 
//    Rev 1.29   07 May 1997 16:26:14   Hannes
// 
//    Rev 1.28   18 Mar 1997 16:31:24   Martin
// int's aus den Strukturen raus ...
// 
//    Rev 1.27   13 Mar 1997 19:06:50   Hannes
// Blobs als lokale Variablen, Matchexpression bei Funktionsaufrufen ohne
// Parameter
// 
//    Rev 1.26   28 Feb 1997 14:39:14   Hannes
// verschiedene Fehlerkorrekturen
// 
//    Rev 1.25   19 Feb 1997 12:04:30   Hannes
// Scriptfunktionen
// 
//    Rev 1.24   26 Nov 1996 07:57:10   HANNES
// Versionshistory von DDD's
// 
//    Rev 1.23   08 Nov 1996 13:24:50   HANNES
// Einbau von QLong
// 
//    Rev 1.22   21 Oct 1996 18:50:58   HANNES
// Einbau von Aliasnamen in das Script
// 
//    Rev 1.21   04 Feb 1996 15:30:34   gerhold
// Teile aus COMPILE in DDSMEM
// 
//    Rev 1.20   02 Feb 1996 10:41:26   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.19   02 Aug 1995 09:59:32   HANNES
// Prioritaetenhandling, verb. Fehlerabfrage, verb. Kapselung
// 
//    Rev 1.18   27 Jun 1995 13:55:56   HANNES
// Bitmaps und Bilder auch in Expressions
// 
//    Rev 1.17   09 Jun 1995 00:22:38   HANNES
// Umbau der Konstanten auf normale Tabelle
// 
//    Rev 1.16   24 May 1995 17:11:38   HANNES
// Abgespeckte Version fuer SQL - Compiler
// 
//    Rev 1.15   15 May 1995 08:23:02   HANNES
// structs im normalen Script
// 
//    Rev 1.14   28 Apr 1995 17:17:36   HANNES
// Verbessertes Handling fuer Konstanten in mappings
// 
//    Rev 1.13   31 Mar 1995 18:24:10   HANNES
// 
//    Rev 1.12   20 Mar 1995 12:08:28   HANNES
// Konstantenhanling, RunNmbr
// 
//    Rev 1.11   08 Mar 1995 09:11:44   HANNES
// Forschleifen u.a.
// 
//    Rev 1.10   24 Feb 1995 11:10:42   HANNES
// 
//    Rev 1.9   10 Jan 1995 14:59:50   HANNES
// Fehlerkorrektur
// 
//    Rev 1.8   09 Jan 1995 12:07:04   HANNES
// Debugger eingebaut
// 
//    Rev 1.7   09 Dec 1994 19:41:06   HANNES
// 
//    Rev 1.6   08 Dec 1994 22:04:14   HANNES
// 
//    Rev 1.5   07 Dec 1994 16:08:28   HANNES
// 
//    Rev 1.4   07 Dec 1994 16:05:38   HANNES
// 
//    Rev 1.3   07 Dec 1994 16:02:46   HANNES
// 
//    Rev 1.2   05 Dec 1994 17:37:22   HANNES
// Endgueltiger Einbau der Expressions
// 
//    Rev 1.1   05 Aug 1994 19:32:30   HANNES
// Time eingebaut
// 
//    Rev 1.0   24 Jun 1994 16:30:26   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.0   24 May 1993 14:26:16   HANNES
// Initial revision.
//

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "dds32.h"
#include "globmem.h"
#include "hash.hpp"
#include "btrieve.hpp"
#include "compile.hpp"
#include "express.hpp"
#define SYNTAX_MAIN
#include "syntax.hpp"
#include "twodim.hpp"
#define MODULENUM 138
#include "winass.hpp"
#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "scripthd.hpp"

void FAULT()
  {
  MessageBox (GetActiveWindow(),"!!! FATAL INTERNAL ERROR !!!","???",MB_ICONEXCLAMATION | MB_OK);
  }

// Stack fuer Daten der Expressions
//////////////////////////////////////
void ScriptCompiler::NextExpProc ()
  {
  _expdstack[_expdptr].hGExpBuffer = _actcmpl->hGExpBuffer;
  _expdstack[_expdptr].hGExpOffs = _actcmpl->hGExpOffs;
  _expdstack[_expdptr].hGExpPtr = _actcmpl->hGExpPtr;
  _expdstack[_expdptr].hGOffs = _actcmpl->hGOffs;
  _expdstack[_expdptr].ExpOffsList = ExpOffsList;
  _expdstack[_expdptr].fEDD = fEDD;
  _actcmpl->hGExpBuffer = 0;
  _actcmpl->hGExpOffs = 0;
  _actcmpl->hGExpPtr = 0;
  _actcmpl->hGOffs = 0;
  fEDD = NULL ;
  ExpOffsList = NULL;
  _expdptr ++ ;
  }

void ScriptCompiler::PrevExpProc ()
  {
  _expdptr -- ;
  WIN_ASSERT (_actcmpl->hGExpBuffer == 0);
  WIN_ASSERT (_actcmpl->hGExpOffs == 0);
  WIN_ASSERT (_actcmpl->hGExpPtr == 0);
  WIN_ASSERT (_actcmpl->hGOffs == 0);
  WIN_ASSERT (_actcmpl->fEDD == NULL);
  WIN_ASSERT (ExpOffsList == NULL);
  _actcmpl->hGExpBuffer = _expdstack[_expdptr].hGExpBuffer ;
  _actcmpl->hGExpOffs   = _expdstack[_expdptr].hGExpOffs   ;
  _actcmpl->hGExpPtr    = _expdstack[_expdptr].hGExpPtr    ;
  _actcmpl->hGOffs      = _expdstack[_expdptr].hGOffs      ;
  _actcmpl->hGOffs      = _expdstack[_expdptr].hGOffs      ;
  _actcmpl->fEDD        = _expdstack[_expdptr].fEDD        ;
  ExpOffsList           = _expdstack[_expdptr].ExpOffsList ;
  }
BOOL ScriptCompiler::ExpAllowed ()
  {
  return (_expdptr > 0) ;
  }

// Listen der Oparatoren
////////////////////////////
void PushPtr (LPVOID);
class FAR opfobj {
 public :
  void FAR *operator new (size_t size);
  void operator delete (void FAR *obj);
  opfobj () 
    { PushPtr(this) ; }
  virtual ~opfobj ()
    { } 
  };

void FAR *opfobj::operator new (size_t size)
  {
  return (GetGlobMem (size)) ; 
  }

void opfobj::operator delete (void FAR *obj)
  { 
  FreeGlobMem (obj) ; 
  }

#pragma pack(1)
struct FAR oparg {
  WORD Offset;          // Offset in der lokalen Kopie
  WORD vartyp;          // Typ des Argumentes
  };

struct FAR constarg {
  WORD Offset;
  WORD DataType;
  WORD dataSize;
  int Size()
    { return sizeof(*this) + dataSize ; }
  };
class FAR oplist {
 public :
  void FAR *operator new (size_t size)
    { return GetGlobMem (size) ; }
  void operator delete (void FAR *obj)
    { FreeGlobMem (obj); }

  oplist FAR *Next;
  WORD prio;
  short isbinop;
  BYTE FType;
  LPSCRIPTCONTENT destContext;
  DWORD procAddr;
  short AnzArgs;
  short AnzConsts;
  oparg resdesc ;       // Beschreibung des Resultates
  oparg FAR *args;      // Beschreibung der Argumente
  constarg FAR *cargs;  // Beschreibung der zusaetzlichen Konstanten
  constarg FAR *GetCArg(int n)
    {
    constarg FAR *res = cargs ;
    for (int i = 0 ; i < n ; i++) {
      res = (constarg FAR *) (LPSTR(res) + res->Size());
      }
    return res;
    }

  LPSTR cmplt;          // fertiges Kompilat
  short FncParCount;      // Anzahl der Parameter der Funktion
  WORD ExtraCount;      // Groesse des internen Speichers
  LPWORD TableInds;

  oplist ()
    { Next = NULL ; args = NULL ; cmplt = NULL ; }
  ~oplist();

  void AddArg (WORD);
  void makecmplt (funcdef FAR *fd);
  void makecmplt (funcdef FAR *fd,DWORD extraData);
  void makecmplt (funcdef FAR *fd,DWORD procAddr,LPSTR ModName,LPSTR FuncName,int AnzBytesBeforeParam,LPWORD ti,int Anzti);
  void SetProcAddr (DWORD extraData);
  void defarg (int fncargnum,pardsc FAR *pd,int opargnum);
  void defconstarg (int fncargnum,pardsc FAR *pd,LPVOID data,int dSize,WORD DataType);
  void defconstarg (int fncargnum,pardsc FAR *pd,DWORD cint);
  void defconstarg (int fncargnum,pardsc FAR *pd,float val);
  void defconstarg (int fncargnum,pardsc FAR *pd,fpt FAR *pt);
  void defconstarg (int fncargnum,pardsc FAR *pd,LPSTR str);
  void defres (int fncargnum,pardsc FAR *pd);
  };
#pragma pack()

static char tmpStrKey[256];
typedef char huge *HPSTR;
inline LPSTR GetStrKey (HPSTR k)
  {
  for (LPSTR h = tmpStrKey ; *k ; )
    *h++ = *k++ ;
  *h++ = '\0';
  return tmpStrKey ;
  }

inline LPSTR GetStrKey (HPSTR k,LPSTR Prefix,int far *len)
  {
  LPSTR h;
  if (Prefix != NULL) {
    lstrcpy (tmpStrKey,Prefix);
    h = tmpStrKey + lstrlen(tmpStrKey);
    *h ++ = '.' ;
    }
  else
    h = tmpStrKey ;
  LPSTR b = h ;
  for ( ; *k ; )
    *h++ = *k++ ;
  *h++ = '\0';
  *len = lstrlen(b);
  return tmpStrKey ;
  }

LPOPLIST FAR *CorrXPtr (GLOBALHANDLE res,DWORD xOffs)
  {
  HPSTR base = (HPSTR)GlobalLock (res);
  LPOPLIST FAR *x = (LPOPLIST FAR *) (base+xOffs);
  GlobalUnlock (res);
  return x ;
  }

GLOBALHANDLE StoreOpHash(hash *op,BYTE FType,BOOL FAR *IsEmpty)
  {
  // 1. Initialisierungen
  GLOBALHANDLE res = InitializeHandleForPush ();
  WORD count = 0 ;
  DWORD ActSize = 2 * sizeof(WORD);
  *IsEmpty = TRUE ;

  // 2. Den ganzen Schass anlegen
  for (int i = 0 ; i < int (op->hash_dimension) ; i++) {
    for (LPhash_entry e = op->Table + i ; e != NULL ; ) {
      if (!op->is_empty (e)) {
        // Schluessel Speichern
        LPOPLIST FAR *x = (LPOPLIST FAR *) e->Data;
        BOOL doIt = FALSE ;
        for (LPOPLIST h = *x ; h != NULL ; h = h->Next ) {
          if (h->FType == FType)
            doIt = TRUE ;
          }
        if (doIt) {
          *IsEmpty = FALSE ;
          PushDataToHugeHandle (&ActSize,e->key.strkey,lstrlen(e->key.strkey)+1,&res);
          // Daten Speichern
          PushDataToHugeHandle (&ActSize,&e->wDataSize,sizeof (WORD),&res);
          PushDataToHugeHandle (&ActSize,e->Data,e->wDataSize,&res);
          count ++ ;
          }
        }
      e = op->NextEnt (e);
      }
    }
  // 3. Count eintragen
  LPSTR base = (LPSTR)GlobalLock (res);
  HPSTR hb = HPSTR(base);
  ((WORD FAR *) base)[1] = count ;

  // 4. Noch mal das ganze von vorne, um die Liste nachzutragen
  DWORD bOffs = 2 * sizeof (WORD);
  for (i = 0 ; i < int (count) ; i++) {
    hb = HPSTR(GlobalLock (res));
    base = hb + bOffs;
    LPSTR key = GetStrKey (base);
    int keylen = lstrlen (key);
    LPOPLIST FAR *x = (LPOPLIST FAR *) (HPSTR(base)+keylen+1+sizeof(WORD));
    DWORD xOffs = HPSTR(x) - hb;
    GlobalUnlock (res);
    for ( ; *x != NULL ; ) {
      DWORD oldSize = ActSize;
      LPSTR oldcmplt = (*x)->cmplt;
      oparg FAR *oldargs = (*x)->args;
      constarg FAR *oldcargs = (*x)->cargs;
      WORD FAR *oldTableInds = (*x)->TableInds;
      if ((*x)->cmplt != NULL) {
        WORD ssize = GetBlockSize((*x)->cmplt);
        PushDataToHugeHandle (&ActSize,&ssize,sizeof(WORD),&res);
        x = CorrXPtr (res,xOffs);
        PushDataToHugeHandle (&ActSize,(*x)->cmplt,ssize,&res);
        x = CorrXPtr (res,xOffs);
        (*x)->cmplt = LPSTR(oldSize);
        }
      oldSize = ActSize;
      if ((*x)->args != NULL) {
        WORD ssize = GetBlockSize((*x)->args);
        PushDataToHugeHandle (&ActSize,&ssize,sizeof(WORD),&res);
        x = CorrXPtr (res,xOffs);
        PushDataToHugeHandle (&ActSize,(*x)->args,ssize,&res);
        x = CorrXPtr (res,xOffs);
        (*x)->args = (oparg FAR *)(oldSize);
        }
      oldSize = ActSize;
      if ((*x)->cargs != NULL) {
        WORD ssize = GetBlockSize((*x)->cargs);
        PushDataToHugeHandle (&ActSize,&ssize,sizeof(WORD),&res);
        x = CorrXPtr (res,xOffs);
        PushDataToHugeHandle (&ActSize,(*x)->cargs,ssize,&res);
        x = CorrXPtr (res,xOffs);
        (*x)->cargs = (constarg FAR *)(oldSize);
        }
      oldSize = ActSize;
      if ((*x)->TableInds != NULL) {
        WORD ssize = GetBlockSize((*x)->TableInds);
        PushDataToHugeHandle (&ActSize,&ssize,sizeof(WORD),&res);
        x = CorrXPtr (res,xOffs);
        PushDataToHugeHandle (&ActSize,(*x)->TableInds,ssize,&res);
        x = CorrXPtr (res,xOffs);
        (*x)->TableInds = (WORD FAR *)(oldSize);
        }
      oldSize = ActSize;
      PushDataToHugeHandle (&ActSize,*x,sizeof (**x),&res);
      x = CorrXPtr (res,xOffs);
      hb = (HPSTR) GlobalLock (res);
      LPOPLIST n = LPOPLIST(hb + oldSize);
      GlobalUnlock (res);
      (*x)->cmplt = oldcmplt ;
      (*x)->args = oldargs ;
      (*x)->cargs = oldcargs ;
      (*x)->TableInds = oldTableInds ;
      DWORD FAR *nOffs = (DWORD FAR *) (x) ;
      *nOffs = oldSize;
      x = &n->Next ;
      xOffs = (HPSTR(x) - hb);
      }
    bOffs += keylen + 1 + sizeof (WORD) + sizeof(DWORD) ;
    }

  GlobalUnlock (res);
  return res ;
  }

GLOBALHANDLE StoreOpList(LPOPLIST as)
  {
  // 1. Initialisierungen
  GLOBALHANDLE res = InitializeHandleForPush ();
  DWORD ActSize = 2 * sizeof(WORD);

  // 4. Noch die Liste 
  LPSTR base = (LPSTR)GlobalLock (res);
  HPSTR hb = HPSTR(base);
  base += 2 * sizeof (WORD);
  DWORD FAR *nOffs = NULL ;
  DWORD Root = 0L;
  PushDataToHugeHandle (&ActSize,&Root,sizeof(DWORD),&res);
  LPOPLIST FAR *x = (LPOPLIST FAR *) (base) ;
  DWORD xOffs = 2 * sizeof(WORD);
  for ( ; as != NULL ; ) {
    DWORD oldSize = ActSize;
    LPSTR oldcmplt = as->cmplt;
    oparg FAR *oldargs = as->args;
    constarg FAR *oldcargs = as->cargs;
    WORD FAR *oldTableInds = as->TableInds;
    if (as->cmplt != NULL) {
      WORD ssize = GetBlockSize(as->cmplt);
      PushDataToHugeHandle (&ActSize,&ssize,sizeof(WORD),&res);
      x = CorrXPtr (res,xOffs);
      PushDataToHugeHandle (&ActSize,as->cmplt,ssize,&res);
      x = CorrXPtr (res,xOffs);
      as->cmplt = LPSTR(oldSize);
      }
    oldSize = ActSize;
    if (as->args != NULL) {
      WORD ssize = GetBlockSize(as->args);
      PushDataToHugeHandle (&ActSize,&ssize,sizeof(WORD),&res);
      x = CorrXPtr (res,xOffs);
      PushDataToHugeHandle (&ActSize,as->args,ssize,&res);
      x = CorrXPtr (res,xOffs);
      as->args = (oparg FAR *)(oldSize);
      }
    oldSize = ActSize ;
    if (as->cargs != NULL) {
      WORD ssize = GetBlockSize(as->cargs);
      PushDataToHugeHandle (&ActSize,&ssize,sizeof(WORD),&res);
      x = CorrXPtr (res,xOffs);
      PushDataToHugeHandle (&ActSize,as->cargs,ssize,&res);
      x = CorrXPtr (res,xOffs);
      as->cargs = (constarg FAR *)(oldSize);
      }
    oldSize = ActSize;
    PushDataToHugeHandle (&ActSize,as,sizeof (*as),&res);
    x = CorrXPtr (res,xOffs);
    hb = (HPSTR) GlobalLock (res);
    LPOPLIST n = LPOPLIST(hb + oldSize);
    GlobalUnlock (res);
    as->cmplt = oldcmplt ;
    as->args = oldargs ;
    as->cargs = oldcargs ;
    as->TableInds = oldTableInds ;
    nOffs = (DWORD FAR *) (x) ;
    *nOffs = oldSize;
    x = &n->Next ;
    xOffs = (HPSTR)x - hb;
    as = as->Next ;
    }

  GlobalUnlock (res);
  return res ;
  }

void DelOpHash(hash *res)
  {
  for (int i = 0 ; i < int (res->hash_dimension) ; i++) {
    for (LPhash_entry e = res->Table + i ; e != NULL ; ) {
      if (!res->is_empty (e)) {
        // Schluessel Speichern
        LPOPLIST x = *((LPOPLIST FAR *) (e->Data));
        for ( ; x != NULL ; ) {
          LPOPLIST n = x->Next ;
          delete x ;
          x = n ;
          }
        }
      e = res->NextEnt (e);
      }
    }
  }

void DelOpList(LPOPLIST res)
  {
  LPOPLIST x = res ;
  for ( ; x != NULL ; ) {
    LPOPLIST n = x->Next ;
    delete x ;
    x = n ;
    }
  }

inline WORD wInfo (HPSTR h)
  {
  WORD res;
  hmemcpy (&res,h,sizeof(WORD));
  return res;
  }
DWORD IsReferenced (LPSTR sKey,char huge *base,LPSTR Prefix)
  {
  WORD count = ((WORD FAR *) base)[1];
  base += 2 * sizeof (WORD);
  for (int i = 0 ; i < int (count) ; i++) {
    WORD datasize;
    int keylen;
    LPSTR key = GetStrKey (base,Prefix,&keylen);
    datasize = wInfo (base + keylen + 1);
    if (lstrcmp (sKey,key) == 0) {
      return * ((DWORD FAR *) (base + keylen + 1 + sizeof(WORD)));
      }
    base += keylen + 1 + sizeof (WORD) + datasize ;
    }
  return 0L ;
  }

static LPSTR tmpBuff;
inline LPSTR GetTmpBuff (HPSTR h,int size)
  {
  tmpBuff = LPSTR (GetGlobMem (size));
  hmemcpy (tmpBuff,h,size);
  return tmpBuff;
  }

inline void CleanTmpBuff ()
  {
  FreeGlobMem (tmpBuff);
  }

void MyGetHugeHash (hash FAR *h,GLOBALHANDLE hGm,LPSTR Prefix,hash FAR *alreadSet)
  {
  HPSTR base = HPSTR(GlobalLock (hGm));
  WORD count = ((WORD FAR *) base)[1];
  base += 2 * sizeof (WORD);
  for (int i = 0 ; i < int (count) ; i++) {
    WORD datasize;
    int keylen ;
    LPSTR key = GetStrKey (base,Prefix,&keylen);
    datasize = wInfo (base + keylen + 1);
            // * ((WORD FAR *) (base + keylen + 1)) ;
    if (!h->SetData (key,GetTmpBuff (base+keylen+1+sizeof(WORD),datasize),datasize)) {
      BOOL flag = TRUE ;
      alreadSet->SetData (key,&flag,sizeof(flag));
      }
    CleanTmpBuff ();
    base += keylen + 1 + sizeof (WORD) + datasize ;
    }
  GlobalUnlock (hGm);
  }

void GetOpHash(GLOBALHANDLE hGmem,hash *res,LPSTR Prefix,int nFType,LPSCRIPTCONTENT destContext)
  {
  hash FAR *shash = new hash (11,STRKEY);
  MyGetHugeHash (res,hGmem,Prefix,shash);
  HPSTR hb = HPSTR(GlobalLock (hGmem));

  // Die Offsets in echte Zeiger umlegen
  for (int i = 0 ; i < int (res->hash_dimension) ; i++) {
    for (LPhash_entry e = res->Table + i ; e != NULL ; ) {
      DWORD offs ;
      if ((!res->is_empty (e)) && (offs = IsReferenced (e->key.strkey,hb,Prefix))) {
        if (shash->GetData (e->key.strkey)) {
          // Eine Funktion mit diesem Namen gibts schon -> 
          // Die Liste Durchsuchen, ob noch nicht gesetzt
          BOOL found = FALSE ;
          for ( ; ((offs != 0L) && (!found)) ; ) {
            LPOPLIST o = LPOPLIST(hb + offs);
            LPOPLIST FAR *lnext;
            for ( LPOPLIST r = * (LPOPLIST FAR *) (e->Data) ; ((r != NULL) && (!found)) ; r = r->Next) {
              if (r->AnzArgs == o->AnzArgs) {
                found = TRUE ;
                if (o->args != 0L) {
                  LPWORD ssize = LPWORD(hb + DWORD(o->args));
                  oparg FAR *a = (oparg FAR *) (ssize + 1) ;
                  for (int j = 0 ; j < r->AnzArgs ; j++)
                    if (r->args[j].vartyp != a[j].vartyp)
                      found = FALSE ;
                  }
                }
              lnext = &r->Next ;
              }
            if (!found) {
              // Diese Auspraegung wurde noch nicht gefunden ->
              // Funktion setzen
              //-----------------------------------------------
              LPOPLIST n = LPOPLIST(GetGlobMem (sizeof(*n)));
              hmemcpy (n,o,sizeof(*n));
              n->FType = nFType ;
              n->destContext = destContext;
              if (n->cmplt != NULL) {
                LPWORD ssize = LPWORD(hb + DWORD(n->cmplt));
                n->cmplt = LPSTR(GetGlobMem (*ssize));
                hmemcpy (n->cmplt,ssize+1,*ssize);
                }
              if (n->args != NULL) {
                LPWORD ssize = LPWORD(hb + DWORD(n->args));
                n->args = (oparg FAR *) (GetGlobMem (*ssize));
                hmemcpy (n->args,ssize+1,*ssize);
                }
              if (n->cargs != NULL) {
                LPWORD ssize = LPWORD(hb + DWORD(n->cargs));
                n->cargs = (constarg FAR *) (GetGlobMem (*ssize));
                hmemcpy (n->cargs,ssize+1,*ssize);
                }
              if (n->TableInds != NULL) {
                LPWORD ssize = LPWORD(hb + DWORD(n->TableInds));
                n->TableInds = (WORD FAR *) (GetGlobMem (*ssize));
                hmemcpy (n->TableInds,ssize+1,*ssize);
                }
              *lnext = n ;
              }
            offs = DWORD(o->Next);
            }
          }
        else {
          DWORD FAR *x = (DWORD FAR *) (e->Data);    // Noch leer
          // Die Liste Aufbauen
          for ( ; *x != 0L ; ) {
            LPOPLIST o = LPOPLIST(hb + *x);
            LPOPLIST n = LPOPLIST(GetGlobMem (sizeof(*n)));
            hmemcpy (n,o,sizeof(*n));
            n->FType = nFType ;
            n->destContext = destContext;
            if (n->cmplt != NULL) {
              LPWORD ssize = LPWORD(hb + DWORD(n->cmplt));
              n->cmplt = LPSTR(GetGlobMem (*ssize));
              hmemcpy (n->cmplt,ssize+1,*ssize);
              }
            if (n->args != NULL) {
              LPWORD ssize = LPWORD(hb + DWORD(n->args));
              n->args = (oparg FAR *) (GetGlobMem (*ssize));
              hmemcpy (n->args,ssize+1,*ssize);
              }
            if (n->cargs != NULL) {
              LPWORD ssize = LPWORD(hb + DWORD(n->cargs));
              n->cargs = (constarg FAR *) (GetGlobMem (*ssize));
              hmemcpy (n->cargs,ssize+1,*ssize);
              }
            if (n->TableInds != NULL) {
              LPWORD ssize = LPWORD(hb + DWORD(n->TableInds));
              n->TableInds = (WORD FAR *) (GetGlobMem (*ssize));
              hmemcpy (n->TableInds,ssize+1,*ssize);
              }
            *x = DWORD(n);
            x = (DWORD FAR *) &(n->Next) ;
            }
          }
        }
      e = res->NextEnt (e);
      }
    }
  }

LPOPLIST GetOpList(GLOBALHANDLE hGmem)
  {
  HPSTR hb = HPSTR(GlobalLock (hGmem));

  // Schluessel Speichern
  LPOPLIST res = NULL;
  DWORD FAR *x = (DWORD FAR *) (hb + 2 * sizeof(WORD));
  for ( ; *x != 0L ; ) {
    LPOPLIST o = LPOPLIST(hb + *x);
    LPOPLIST n = LPOPLIST(GetGlobMem (sizeof(*n)));
    if (res == NULL) res = n;
    hmemcpy (n,o,sizeof(*n));
    if (n->cmplt != NULL) {
      LPWORD ssize = LPWORD(hb + DWORD(n->cmplt));
      n->cmplt = LPSTR(GetGlobMem (*ssize));
      hmemcpy (n->cmplt,ssize+1,*ssize);
      }
    if (n->args != NULL) {
      LPWORD ssize = LPWORD(hb + DWORD(n->args));
      n->args = (oparg FAR *) (GetGlobMem (*ssize));
      hmemcpy (n->args,ssize+1,*ssize);
      }
    if (n->cargs != NULL) {
      LPWORD ssize = LPWORD(hb + DWORD(n->cargs));
      n->cargs = (constarg FAR *) (GetGlobMem (*ssize));
      hmemcpy (n->cargs,ssize+1,*ssize);
      }
    *x = DWORD(n);
    x = (DWORD FAR *) &(n->Next) ;
    }
  return res;
  }

oplist::~oplist ()
  {
  if (cmplt != NULL)
    FreeGlobMem (cmplt);
  if (args != NULL)
    FreeGlobMem (args);
  if (cargs != NULL)
    FreeGlobMem (cargs);
  if (TableInds != NULL)
    FreeGlobMem (TableInds);
  }

void oplist::makecmplt (funcdef FAR *fd)
  {
  int size = sizeof(WORD) + sizeof(WORD) + fd->ExtraCount + 
                2 * sizeof(WORD) * fd->parCount ;
  cmplt = LPSTR (GetGlobMem (size));
  ((WORD FAR *) cmplt)[0] = fd->funcId ;
  ((WORD FAR *) cmplt)[1] = size - sizeof(WORD) ;   // par_size
  ExtraCount = fd->ExtraCount ;
  FncParCount = fd->parCount;
  }

char GetArgBez (WORD vartype)
  {
  if (vartype < 26)
    return ('A' + char (vartype % 26)) ;
  else
    return 'Z' ;
  }

WORD vartypeFromBez (char ch)
  {
  return (ch - 'A') ;
  }

// Lokale Scriptfunktion
void oplist::makecmplt (funcdef FAR *fd,DWORD extraData)
  {
  int size = sizeof(WORD) + sizeof(WORD) + fd->ExtraCount + 
                2 * sizeof(WORD) * fd->parCount ;
  cmplt = LPSTR (GetGlobMem (size));
  ((WORD FAR *) cmplt)[0] = fd->funcId ;
  ((WORD FAR *) cmplt)[1] = size - sizeof(WORD) ;   // par_size
  lmemcpy (cmplt + 2 * sizeof(WORD),&extraData,sizeof(DWORD)) ;
  procAddr = 0xFFFFFFFF ;
  ExtraCount = fd->ExtraCount ;
  FncParCount = fd->parCount;
  }

void oplist::SetProcAddr (DWORD extraData)
  {
  if (procAddr == -1L)
    lmemcpy (cmplt + 2 * sizeof(WORD),&extraData,sizeof(DWORD)) ;
  else
    procAddr = extraData ;
  }

void SetProcAddr (LPVOID extra,DWORD extraData)
  {
  LPOPLIST (extra)->SetProcAddr (extraData);
  }

// Exportierte Scriptfunktion 
void oplist::makecmplt (funcdef FAR *fd,DWORD pAddr,LPSTR ModName,LPSTR FuncName,int AnzBytesBeforeParam,LPWORD ti,int Anzti)
  {
  char tmpString[128];
  lmemset (tmpString,'\0',sizeof(tmpString));
  int modLen ;
  if (ModName != NULL) {
    lstrcpy (tmpString,ModName);
    modLen = lstrlen(ModName) + 1;
    }
  else
    modLen = NULL ;
  lstrcpy (tmpString + modLen,FuncName);
  int argOffs = modLen + lstrlen(FuncName);
  tmpString[argOffs] = '@' ;
  for (int i = 0 ; i < AnzArgs ; i++)
    tmpString[argOffs + 1 + i] = GetArgBez(args[i].vartyp);
  int tmpLen = argOffs + 2 + AnzArgs ;
  procAddr = pAddr;
  WORD fixSize1 = fd->ExtraCount + // Platz fuer Extradaten
                 tmpLen ;         // Modul und Funktionsname
  if ((fixSize1 % 2) != 0) fixSize1 = (fixSize1 / 2 + 1) * 2 ; // Auf gerade Adresse zwingen
  WORD fixSize2 = Anzti * sizeof(WORD) ;
  int size = 2 * sizeof(WORD) + fixSize1 + fixSize2 + 2 * sizeof(WORD) * fd->parCount + AnzBytesBeforeParam;
  cmplt = LPSTR (GetGlobMem (size));
  ((WORD FAR *) cmplt)[0] = fd->funcId ;
  ((WORD FAR *) cmplt)[1] = size - sizeof(WORD) ;   // par_size
  lmemcpy (cmplt + 2 * sizeof(WORD) + fd->ExtraCount,tmpString,tmpLen);
  lmemcpy (cmplt + 2 * sizeof(WORD) + fixSize1,ti,fixSize2);
  ExtraCount = fixSize1 + fixSize2 + AnzBytesBeforeParam;
  FncParCount = fd->parCount;
  if (Anzti > 0) {
    TableInds = LPWORD(GetGlobMem (Anzti * sizeof(WORD)));
    lmemcpy (TableInds,ti,Anzti * sizeof(WORD));
    }
  }

void oplist::defarg (int fncargnum,pardsc FAR *pd,int opargnum)
  {
  opargnum -= 1;
  if ((opargnum < AnzArgs) && (fncargnum < FncParCount) 
        && ((pd == NULL) || ((pd->par_kind == PAR_VAR) && (pd->Extra == args[opargnum].vartyp))))
    args[opargnum].Offset = sizeof(WORD) + sizeof(WORD) + ExtraCount + 2 * sizeof(WORD) * fncargnum ;
  else _actcmpl->wError = PARERROR ;
  }

void oplist::defconstarg (int fncargnum,pardsc FAR *pd,LPVOID data,int dSize,WORD DataType)
  {
  int nSize = GetBlockSize (cargs) + sizeof(*cargs) + dSize ;
  constarg FAR *n = (constarg FAR *) GetGlobMem (nSize);
  if (cargs != NULL) {
    lmemcpy (n,cargs,GetBlockSize(cargs));
    FreeGlobMem (cargs);
    }
  cargs = n;
  constarg FAR *c = GetCArg(AnzConsts);
  c->Offset = sizeof(WORD) + sizeof(WORD) + ExtraCount + 2 * sizeof(WORD) * fncargnum ;
  c->DataType = DataType ;
  c->dataSize = dSize ;
  lmemcpy (c+1,data,dSize);
  AnzConsts ++ ;
  }

void oplist::defconstarg (int fncargnum,pardsc FAR *pd,DWORD cint)
  {
  if ((fncargnum < FncParCount) && (pd->par_kind == PAR_VAR)) {
    if (pd->Extra == VAR_LONG) 
      defconstarg (fncargnum,pd,&cint,sizeof(LONG),VAR_LONG);
    else if (pd->Extra == VAR_STRARR)
      defconstarg (fncargnum,pd,&cint,sizeof(WORD),VAR_STRARR);
    else _actcmpl->wError = PARERROR ;
    }
  else _actcmpl->wError = PARERROR ;
  }

void oplist::defconstarg (int fncargnum,pardsc FAR *pd,float val)
  {
  if ((fncargnum < FncParCount) && (pd->par_kind == PAR_VAR)) {
    if (pd->Extra == VAR_DEC) 
      defconstarg (fncargnum,pd,&val,sizeof(val),VAR_DEC);
    else _actcmpl->wError = PARERROR ;
    }
  else _actcmpl->wError = PARERROR ;
  }
void oplist::defconstarg (int fncargnum,pardsc FAR *pd,fpt FAR *pt)
  {
  if ((fncargnum < FncParCount) && (pd->par_kind == PAR_VAR)) {
    if (pd->Extra == VAR_POINT) 
      defconstarg (fncargnum,pd,pt,sizeof(*pt),VAR_POINT);
    else _actcmpl->wError = PARERROR ;
    }
  else _actcmpl->wError = PARERROR ;
  }
void oplist::defconstarg (int fncargnum,pardsc FAR *pd,LPSTR str)
  {
  if ((fncargnum < FncParCount) && (pd->par_kind == PAR_VAR)) {
    if (pd->Extra == VAR_STR) 
      defconstarg (fncargnum,pd,str,lstrlen(str)+1,VAR_STR);
    else _actcmpl->wError = PARERROR ;
    }
  else _actcmpl->wError = PARERROR ;
  }
void oplist::defres (int fncargnum,pardsc FAR *pd)
  {
  if ((fncargnum < FncParCount) 
        && (pd->par_kind == PAR_VAR) && (pd->Extra == resdesc.vartyp))
    resdesc.Offset = sizeof(WORD) + sizeof(WORD) + ExtraCount + 2 * sizeof(WORD) * fncargnum ;
  else _actcmpl->wError = PARERROR ;
  }


void oplist::AddArg (WORD vtyp)
  {
  oparg FAR *a = (oparg FAR *) GetGlobMem (sizeof(*a) * (AnzArgs + 1));
  if (args != NULL) {
    lmemcpy (a,args,sizeof(*a) * AnzArgs);
    FreeGlobMem (args);
    }
  args = a;
  args[AnzArgs].vartyp = vtyp ;
  AnzArgs++;
  }

void PushPtr (GLOBALHANDLE FAR *hGPtrMem,LPVOID ptr)
  {
  char huge *Buffer;
  DWORD oldsize;
  if (*hGPtrMem) {
    Buffer = (char huge *)GlobalLock (*hGPtrMem);
    oldsize = *((DWORD FAR *) Buffer);
    }
  else {
    *hGPtrMem = GlobalAlloc (GHND,sizeof(DWORD));
    Buffer = (char huge *)GlobalLock (*hGPtrMem);
    oldsize = *((DWORD FAR *) Buffer) = sizeof(DWORD);
    }
  GlobalUnlock (*hGPtrMem);
  *hGPtrMem = GlobalReAlloc (*hGPtrMem,oldsize + sizeof(LPVOID),GHND);
  Buffer = (char huge *)GlobalLock (*hGPtrMem);
  *((DWORD FAR *) Buffer) += sizeof(ptr);
  hmemcpy ((char _huge *) Buffer + oldsize,&ptr,sizeof(ptr));
  GlobalUnlock (*hGPtrMem);
  }

void PushPtr (LPVOID ptr)
  {
  PushPtr (&_actcmpl->hGPtrs,ptr);
  }

void PushNPtr (LPVOID ptr)
  {
  PushPtr (&_actcmpl->hGNPtrs,ptr);
  }

struct clrBuffer {
  DWORD size;
  union {
    opfobj huge *p[1];
    void huge *v[1];
    } x;
  };

#pragma optimize("", off)
void clearAllPtrs ()
  {
  if (_actcmpl->hGPtrs) {
    clrBuffer huge *b = (clrBuffer huge *) GlobalLock (_actcmpl->hGPtrs) ;
    DWORD Count = (b->size - sizeof(DWORD)) / sizeof(opfobj FAR *);
    for (DWORD i = 0 ; i < Count ; i++) {
      delete ((opfobj FAR * huge *)(b->x.p))[i];
      }
    GlobalUnlock (_actcmpl->hGPtrs);
    GlobalFree (_actcmpl->hGPtrs);
    _actcmpl->hGPtrs = 0;
    }
  if (_actcmpl->hGNPtrs) {
    clrBuffer huge *b = (clrBuffer huge *) GlobalLock (_actcmpl->hGNPtrs) ;
    DWORD Count = (b->size - sizeof(DWORD)) / sizeof(opfobj FAR *);
    for (DWORD  i = 0 ; i < Count ; i++)
      FreeGlobMem (b->x.v[i]);
    GlobalUnlock (_actcmpl->hGNPtrs);
    GlobalFree (_actcmpl->hGNPtrs);
    _actcmpl->hGNPtrs = 0;
    }
  }
#pragma optimize("",on)

void setbinop (void)
  {
  LPOPLIST ol = new oplist;
  LPSTR Name = (LPSTR)GlobalLock (_actcmpl->hPars0) + sizeof(WORD);

  if ((lstrcmp(Name,"+") == 0) ||
      (lstrcmp(Name,"-") == 0)) ol->prio = 2;
  else if ((lstrcmp(Name,"*") == 0) ||
           (lstrcmp(Name,"/") == 0)) ol->prio = 3;
  else ol->prio = 4 ;

  ol->isbinop = TRUE;
  ol->FType = FTYPE_NORMAL;
  ol->resdesc.vartyp = _actcmpl->actres;

  LPOPLIST FAR *oll;
  if (_actcmpl->hopHash != NULL)
    oll = (LPOPLIST FAR *) _actcmpl->hopHash->GetData(Name);
  else
    oll = NULL ;
  if (oll != NULL) {
    _actcmpl->lastoplist = *oll;
    // hinten anfuegen
    for (LPOPLIST h = *oll ; h ->Next != NULL ; h = h->Next ) ;
    h->Next = ol;
    }
  else {
    _actcmpl->lastoplist = ol;
    _actcmpl->hopHash->SetData (Name,&ol,sizeof(ol));
    }
  GlobalUnlock (_actcmpl->hPars0);
  _actcmpl->lastop = ol;
  }

void setcmpop (void)
  {
  LPOPLIST ol = new oplist;
  LPSTR Name = (LPSTR)GlobalLock (_actcmpl->hPars0) + sizeof(WORD);

  ol->prio = 1 ;
  ol->FType = FTYPE_NORMAL;

  ol->isbinop = TRUE;
  ol->resdesc.vartyp = BOOLVARFNC ;   // Vergleiche haben kein resultat im
                                      // herkoemmlichen Sinn

  LPOPLIST FAR *oll;
  if (_actcmpl->hcmpHash != NULL)
    oll = (LPOPLIST FAR *) _actcmpl->hcmpHash->GetData(Name);
  else
    oll = NULL ;
  if (oll != NULL) {
    _actcmpl->lastoplist = *oll;
    // hinten anfuegen
    for (LPOPLIST h = *oll ; h ->Next != NULL ; h = h->Next ) ;
    h->Next = ol;
    }
  else {
    _actcmpl->lastoplist = ol;
    _actcmpl->hcmpHash->SetData (Name,&ol,sizeof(ol));
    }
  GlobalUnlock (_actcmpl->hPars0);
  _actcmpl->lastop = ol;
  }

void setassop (void)
  {
  LPOPLIST ol = new oplist;
  ol->prio = 6 ;
  ol->FType = FTYPE_NORMAL;

  ol->isbinop = TRUE;
  ol->resdesc.vartyp = _actcmpl->actres;

  if (_actcmpl->hasList != NULL) {
    // hinten anfuegen
    for (LPOPLIST h = _actcmpl->hasList ; h ->Next != NULL ; h = h->Next ) ;
    h->Next = ol;
    }
  else
    _actcmpl->hasList = ol ;
  _actcmpl->lastoplist = _actcmpl->hasList;
  _actcmpl->lastop = ol;
  }

void setscondop (void)
  {
  LPOPLIST ol = new oplist;
  ol->prio = 1 ;
  ol->FType = FTYPE_NORMAL;

  ol->isbinop = TRUE;
  ol->resdesc.vartyp = BOOLVARFNC ;   // Conditions haben kein resultat im
                                      // normalen Sinn

  if (_actcmpl->hcndList != NULL) {
    // hinten anfuegen
    for (LPOPLIST h = _actcmpl->hcndList ; h ->Next != NULL ; h = h->Next ) ;
    h->Next = ol;
    }
  else
    _actcmpl->hcndList = ol ;
  _actcmpl->lastoplist = _actcmpl->hcndList;
  _actcmpl->lastop = ol;
  }

static char LastFuncName[64];
void setexpfnc (LPSTR Name)
  {
  LPOPLIST ol = new oplist;

  lstrncpy (LastFuncName,Name,sizeof(LastFuncName) - 1);
  ol->prio = 5;
  ol->FType = FTYPE_NORMAL;
  ol->isbinop = FALSE ;
  ol->resdesc.vartyp = _actcmpl->actres;

  LPOPLIST FAR *oll = (LPOPLIST FAR *) _actcmpl->hefHash->GetData(Name);
  if (oll != NULL) {
    _actcmpl->lastoplist = *oll;
    // hinten anfuegen
    for (LPOPLIST h = *oll ; h ->Next != NULL ; h = h->Next ) ;
    h->Next = ol;
    }
  else {
    _actcmpl->lastoplist = ol;
    _actcmpl->hefHash->SetData (Name,&ol,sizeof(ol));
    }
  _actcmpl->lastop = ol;
  }

void setexpfnc (LPSTR Name,BYTE FType,hash FAR *FAR *htbl,int offsToSet)
  {
  LPOPLIST ol = new oplist;

  ol->prio = 5;
  if (FType == FTYPE_IMPORT) FType = FTYPE_EXPORT ;
  ol->FType = FType;
  ol->isbinop = FALSE ;
  ol->resdesc.vartyp = _actcmpl->actres;

  lstrncpy (LastFuncName,Name + offsToSet,sizeof(LastFuncName) - 1);

  if (*htbl == NULL) *htbl = new hash (37,STRKEY);
  LPOPLIST FAR *oll = (LPOPLIST FAR *) (*htbl)->GetData(Name);
  if (oll != NULL) {
    _actcmpl->lastoplist = *oll;
    // hinten anfuegen
    for (LPOPLIST h = *oll ; h ->Next != NULL ; h = h->Next ) {
      if (h->FType != FType)
        _actcmpl->wError = PARERROR ;
      }
    h->Next = ol;
    }
  else {
    _actcmpl->lastoplist = ol;
    (*htbl)->SetData (Name,&ol,sizeof(ol));
    }
  _actcmpl->lastop = ol;
  }

void setexpfnc ()
  {
  LPSTR Name = (LPSTR)GlobalLock (_actcmpl->hPars0) + sizeof(WORD);
  setexpfnc (Name,FALSE,&_actcmpl->hefHash,0);
  GlobalUnlock (_actcmpl->hPars0);
  }

static int actfncarg;
void makecmplt ()
  {
  _actcmpl->lastop->makecmplt (&_actcmpl->scv.v.fd);
  BOOL found;
  LPOPLIST ol = _actcmpl->lastoplist;
  for ( found = FALSE; (ol != NULL) && !found ; ol = ol->Next) {
    if ((ol != _actcmpl->lastop) && 
        ((ol->AnzArgs == _actcmpl->lastop->AnzArgs) || 
         ((ol->AnzArgs > 0) && (ol->args[ol->AnzArgs - 1].vartyp == VAR_FREEPAR) && 
             (ol->AnzArgs < _actcmpl->lastop->AnzArgs)) ||
         ((_actcmpl->lastop->AnzArgs > 0) && (_actcmpl->lastop->args[_actcmpl->lastop->AnzArgs - 1].vartyp == VAR_FREEPAR) && 
             (_actcmpl->lastop->AnzArgs < ol->AnzArgs)))) {
      found = TRUE;
      for (int i = 0 ; i < min (ol->AnzArgs, _actcmpl->lastop->AnzArgs) ; i++) {
        if (ol->args[i].vartyp == VAR_FREEPAR)
          break;
        if (_actcmpl->lastop->args[i].vartyp == VAR_FREEPAR)
          break;
        if (ol->args[i].vartyp != _actcmpl->lastop->args[i].vartyp) {
          found = FALSE;
          break;
          }
        }
      if (found)
        break;
      }
    }
  if (found) {
    _actcmpl->wError = DOUBLEFUNCTION ;
    }
  actfncarg = 0;
  }

LPVOID makecmpltT (funcdef FAR *fd,DWORD procAddr)
  {
  _actcmpl->lastop->makecmplt (fd,procAddr);
  actfncarg = 0;
  return _actcmpl->lastop ;
  }

LPVOID makecmpltT (funcdef FAR *fd,DWORD procAddr,int AnzBytesBeforeParam,LPWORD ti,int Anzti)
  {
  _actcmpl->lastop->makecmplt (fd,procAddr,NULL,LastFuncName,AnzBytesBeforeParam,ti,Anzti);
  actfncarg = 0;
  return _actcmpl->lastop ;
  }

void makecmpltT (funcdef FAR *fd,DWORD procAddr,LPSTR ModName,int AnzBytesBeforeParam,LPWORD ti,int Anzti)
  {
  _actcmpl->lastop->makecmplt (fd,procAddr,ModName,LastFuncName,AnzBytesBeforeParam,ti,Anzti);
  actfncarg = 0;
  }

void defoparg ()
  {
  pardsc FAR *pdsc = (pardsc FAR *) GlobalLock (_actcmpl->hPars1);
  _actcmpl->lastop->defarg (actfncarg,&pdsc[actfncarg],int(_actcmpl->scv.v.int_val));
  GlobalUnlock (_actcmpl->hPars1);
  actfncarg ++ ;
  }

void defopargT (int i)
  {
  _actcmpl->lastop->defarg (actfncarg,NULL,i);
  actfncarg ++ ;
  }

void defopcint ()
  {
  pardsc FAR *pdsc = (pardsc FAR *) GlobalLock (_actcmpl->hPars1);
  _actcmpl->lastop->defconstarg (actfncarg,&pdsc[actfncarg],DWORD(_actcmpl->scv.v.int_val));
  GlobalUnlock (_actcmpl->hPars1);
  actfncarg ++ ;
  }

fpt pfdefres;
void defopcpy ()
  {
  pfdefres.y = _actcmpl->scv.v.float_val;
  pardsc FAR *pdsc = (pardsc FAR *) GlobalLock (_actcmpl->hPars1);
  _actcmpl->lastop->defconstarg (actfncarg,&pdsc[actfncarg],&pfdefres);
  GlobalUnlock (_actcmpl->hPars1);
  actfncarg ++ ;
  }
void defopcpx ()
  {
  pfdefres.x = _actcmpl->scv.v.float_val;
  }
void defopcstr ()
  {
  pardsc FAR *pdsc = (pardsc FAR *) GlobalLock (_actcmpl->hPars1);
  LPSTR res = (LPSTR)GlobalLock (_actcmpl->hPars0) + sizeof(WORD);
  _actcmpl->lastop->defconstarg (actfncarg,&pdsc[actfncarg],res);
  GlobalUnlock (_actcmpl->hPars1);
  actfncarg ++ ;
  }
void defopcfloat ()
  {
  pardsc FAR *pdsc = (pardsc FAR *) GlobalLock (_actcmpl->hPars1);
  _actcmpl->lastop->defconstarg (actfncarg,&pdsc[actfncarg],_actcmpl->scv.v.float_val);
  GlobalUnlock (_actcmpl->hPars1);
  actfncarg ++ ;
  }

void defopres ()
  {
  pardsc FAR *pdsc = (pardsc FAR *) GlobalLock (_actcmpl->hPars1);
  _actcmpl->lastop->defres (actfncarg,&pdsc[actfncarg]);
  GlobalUnlock (_actcmpl->hPars1);
  actfncarg ++ ;
  }

void defopresT (pardsc FAR *pd)
  {
  _actcmpl->lastop->defres (actfncarg,pd);
  actfncarg ++ ;
  }

void CheckAnzOPArgs ()
  {
  BOOL res = TRUE ;
  for (int i = 0 ; i < _actcmpl->lastop->AnzArgs ; i++) {
    if (_actcmpl->lastop->args[i].vartyp == VAR_FREEPAR) break ;
    res = res && (_actcmpl->lastop->args[i].Offset != 0) ;
    }
  if ((!res) || ((_actcmpl->lastop->resdesc.Offset == 0) && (_actcmpl->lastop->resdesc.vartyp != BOOLVARFNC)))
    _actcmpl->wError = PARERROR ;
  }

int kwtovartyp (int vartyp)
  {
  WORD res;
  switch (vartyp) {
    case PARSCALEVAR :
      res = VAR_SCALE ;
      break ;
    case PARFLAGVAR :
      res = VAR_FLAG ;
      break ;
    case PARSTRARR :
      res = VAR_STRARR ;
      break ;
    case PARCONTVAR :
      res = VAR_CONT ;
      break ;
    case PARPOINTVAR :
      res = VAR_POINT ;
      break ;
    case PARDECVAR :
      res = VAR_DEC ;
      break ;
    case PARINTVAR :
      res = VAR_LONG ;
      break ;
    case PARSTRVAR :
      res = VAR_STR ;
      break ;
    case PARPICTVAR :
      res = VAR_PICTURE ;
      break ;
    case PARBITMAPVAR :
      res = VAR_BITMAP ;
      break ;
    case PARDATEVAR :
      res = VAR_DATE ;
      break ;
    case PARBLOBVAR :
      res = VAR_BLOB ;
      break ;
    case PARTIMEVAR :
      res = VAR_TIME ;
      break ;
    case PARDATETIMEVAR :
      res = VAR_DATETIME ;
      break ;
    case PARPROCVAR :
      res = VAR_PROC ;
      break;
    case PARIMAGE :
      res = VAR_IMAGE ;
      break ;
    case PARDWORDVAR :
      res = VAR_LONG ;
      break ;
    case QLONGVAR :
      res = VAR_QLONG ;
      break ;
    case PAROBJVAR :
      res = VAR_OBJ ;
      break ;
    case FREEPAR:
      res = VAR_FREEPAR ;
      break ;
    }
  return res;
  }

void SetExpArg ()
  {
  _actcmpl->lastop->AddArg (kwtovartyp (_actcmpl->scv.v.k_ident));
  }

void SetExpArgT (BYTE t)
  {
  _actcmpl->lastop->AddArg (t);
  }

void StoreResTyp ()
  {
  _actcmpl->actres = kwtovartyp (_actcmpl->scv.v.k_ident);
  }


BOOL compiler::CheckopHash ()
  {
  if (hopHash == NULL) return FALSE ;
  LPSTR ident = (LPSTR)GlobalLock (hPars0) + sizeof(WORD);
  LPOPLIST FAR *ol;
  if (hopHash != NULL)
    ol = (LPOPLIST FAR *)hopHash->GetData (ident);
  else 
    ol = NULL ;
  if (ol != NULL) {
    scv.type = BINOP ;
    scv.v.vr = *ol ;
    }
  return (ol != NULL);
  }

int MaxAnzArgs (LPOPLIST ol)
  {
  int res = 0;
  for ( ; ol != NULL ; ol = ol->Next ) {
    if ((ol->AnzArgs > 0) && (ol->args[ol->AnzArgs - 1].vartyp == VAR_FREEPAR)) return 1000 ;
    if (ol->AnzArgs > res) res = ol->AnzArgs ;
    }
  return res ;
  }

static char LastModName[64];
BOOL CheckDeclareHash (LPSTR ident)
  {
  BOOL res = FALSE ;
  if ((_actcmpl != NULL) && (_actcmpl->hefHash != NULL)) {
    LPOPLIST FAR *ol = (LPOPLIST FAR *)_actcmpl->hefHash->GetData (ident);
    if ((ol == NULL) && (*ident == '.')) {
      // Noch ohne Punkt probieren, es koennte sich um eine
      // gerade definierte Funktion handeln
      ol = (LPOPLIST FAR *)_actcmpl->hefHash->GetData (ident + 1);
      }
    if ((ol != NULL) && (((*ol)->FType == FTYPE_DECLARE) || ((*ol)->FType == FTYPE_VIRTUAL) || 
                         ((*ol)->FType == FTYPE_EXPORT))) {
      _actcmpl->scv.type = VFNCEXP ;
      _actcmpl->scv.v.vr = *ol;
      res = TRUE ;
      }
    }
  return res ;
  }

BOOL IsImported (LPSTR Name)
  {
  int size = GetBlockSize (_actcmpl->MyImportModules);
  for ( LPSTR h = LPSTR(_actcmpl->MyImportModules) ; (h - LPSTR(_actcmpl->MyImportModules) < size) ; h = h + lstrlen (h) + 1 ) {
    if (lstrcmp (Name,h) == 0) return TRUE ;
    }
  return FALSE ;
  }

BOOL compiler::CheckefHash ()
  {
  if (hefHash == NULL) return FALSE ;
  LPSTR ident = (LPSTR)GlobalLock (hPars0) + sizeof(WORD);
  LPSTR s = ident ;
  LPSTR lastP = NULL ;
  BOOL res = FALSE ;
  for (LPSTR f = ident ; (*f) ; f++) {
    if (*f == '.') lastP = f ;
    }
  if (lastP)
    ident = lastP ;   // Es wird nur der Teil hinter dem Punkt untersucht
  LPOPLIST FAR *ol;
  if (hefHash != NULL) {
    ol = (LPOPLIST FAR *)hefHash->GetData (ident);
    }
  else
    ol = NULL;
  if ((ol != NULL) && ((*ol)->FType != FTYPE_DECLARE) && ((*ol)->FType != FTYPE_VIRTUAL) && 
                      ((*ol)->FType != FTYPE_EXPORT)) {
    if ((lastP) && ((*ol)->FType == FTYPE_IMPORT)) {
      for (LPSTR d = LastModName ; (s < lastP) ; *d++ = *s++ ) ;
      lstrcpy (d,".MOD");
      if (IsImported (LastModName)) {
        scv.type = FNCEXP ;
        scv.v.vr = *ol;
        res = TRUE ;
        }
      }
    else if ((lastP == NULL) && ((*ol)->FType == FTYPE_NORMAL)) {
      scv.type = FNCEXP ;
      scv.v.vr = *ol;
      res = TRUE ;
      }
    }
  GlobalUnlock (hPars0);
  return res ;
  }

BOOL compiler::CheckcmpHash(void)
  {
  if (hcmpHash == NULL) return FALSE ;
  LPSTR ident = (LPSTR)GlobalLock (hPars0) + sizeof(WORD);
  LPOPLIST FAR *ol;
  if (hcmpHash != NULL)
    ol = (LPOPLIST FAR *)hcmpHash->GetData (ident);
  else
    ol = NULL;
  if (ol != NULL) {
    scv.type = CMPOP ;
    scv.v.vr = *ol;
    }
  return (ol != NULL);
  }

#define MAXSUBNODES  32
class FAR exp_node : public opfobj {
 public :
  exp_node (WORD,WORD,WORD,BOOL,BOOL,int);
  exp_node (LPOPLIST,LPSTR);
  exp_node FAR *Parent;

  BOOL termnode;
  BOOL isready;
  int prio;

  WORD rtyp;
  vardef dwres;         // Resultat der Codegenerierung
  BOOL FixupDynamic;    // Resultat muss in die fixupdynamic - Liste
                        // geschrieben werden
  BOOL FixupPar;        // Parameter muss up to date gebracht werden
  BOOL FixupPtr;        // Resultat ist ein Zeiger, der noch korrigiert
                        // werden muss

  int progsize;         // Hilfsvariablen bei der Code - Generierung
  LPSTR MyProg ;
  LPOPLIST resop;
  int FixUpExtraOffs ;  // Auch die Extradaten muessen noch korrigiert werden
  // short extraDataOffs;
  LPVOID extraDataToSet;
  LPWORD extraIndToSet;
  WORD extraIndToSetOffset;
  WORD patchOffs;

  virtual ~exp_node ();

  union FAR {
    struct FAR {
      WORD vartyp;
      WORD r;
      WORD i;
      BOOL isdynamic;
      BOOL ispar;
      int TableNr;
      } v;
    struct FAR {
      LPSTR n;
      LPOPLIST o;
      } f;
    } i;
  int AnzSubNodes;

  exp_node FAR *FAR *sn;

  BOOL CheckAnzSubNodes ();
  void GenCode (BOOL);
  void GetProg (BOOL forExp = TRUE,BOOL withProg = TRUE);
  void FixupRes ();
  void WriteCode ();
  void SetRes ();
  };

exp_node::~exp_node ()
  {
  if (!termnode) {
    FreeGlobMem (i.f.n);
    }
  if (sn != NULL) {
    FreeGlobMem (sn);
    }
  if (MyProg != NULL)
    FreeGlobMem (MyProg);
  if (extraDataToSet != NULL)
    FreeGlobMem (extraDataToSet);
  if (extraIndToSet != NULL)
    FreeGlobMem (extraIndToSet);
  }

BOOL exp_node::CheckAnzSubNodes ()
  {
  BOOL res = ((!termnode) && (AnzSubNodes < MaxAnzArgs (i.f.o)));
  if (!res) _actcmpl->wError = PARERROR ;
  return res;
  }


exp_node::exp_node (WORD vartyp,WORD RecTyp,WORD varid,
                    BOOL isdynamic,BOOL ispar,int TableNr
                   )
  {
  i.v.vartyp     = vartyp;
  i.v.r          = RecTyp;
  i.v.i          = varid;
  i.v.isdynamic  = isdynamic;
  i.v.ispar      = ispar;
  i.v.TableNr    = TableNr ;
  prio = 0x7FFF;

  termnode = TRUE;

  // Herstellen der Verkettung
  if (_actcmpl->last != NULL) {
    this->Parent = _actcmpl->last;
    if (_actcmpl->last->CheckAnzSubNodes())
      _actcmpl->last->sn[_actcmpl->last->AnzSubNodes++] = this;
    }

  sn = NULL ;

  _actcmpl->last = this;
  }


void createvarnode (void)
  {
  new exp_node (_actcmpl->scv.v.vd.vartype,
                _actcmpl->scv.v.vd.vd.DBNummer,
                _actcmpl->scv.v.vd.vd.Ident,
                _actcmpl->scv.v.vd.isdynamic,
                FALSE,
                _actcmpl->scv.v.vd.TableNr
               );
  }

void createparnode (void)
  {
  new exp_node (_actcmpl->scv.v.pd.pd.Extra,
                _actcmpl->scv.v.pd.pd.par_kind,
                _actcmpl->scv.v.pd.Number,
                FALSE,
                TRUE,
                -1
               );
  }

void createconstnode ()
  {
  new exp_node (_actcmpl->constType,2,_actcmpl->constOffs,FALSE,FALSE,-1);
  }

#define VAR_FREE  0xFF
void pushnull ()
  {
  WORD Ident = _actcmpl->pushConst (NULL,0,0xFFFF,TRUE,TRUE);    // Vorbereiten des Null - Vals
  new exp_node (VAR_FREE,2,Ident,FALSE,FALSE,-1);
  }

exp_node::exp_node (LPOPLIST ol,LPSTR name)
  {
  i.f.o = ol;
  i.f.n = LPSTR (GetGlobMem (lstrlen(name)+1));
  lstrcpy (i.f.n,name);
  prio = ol->prio + _actcmpl->brlevel * 256;

  sn = (exp_node FAR * FAR *) GetGlobMem (
                        sizeof(exp_node FAR *) * MaxAnzArgs(ol)
                                         );
  if (_actcmpl->last == NULL) {
    _actcmpl->last = this;
    }
  else {
    if ((_actcmpl->last->termnode) || (_actcmpl->last->isready)) {
      exp_node FAR *h = _actcmpl->last->Parent;
      exp_node FAR *prev = _actcmpl->last;

      for ( ; ((h != NULL) && (h -> prio >= prio)) ; h = h->Parent)
        prev = h;

      if (h != NULL) {
        if (CheckAnzSubNodes ()) {
          sn[AnzSubNodes++] = h->sn[h->AnzSubNodes-1];
          h->sn[h->AnzSubNodes-1] = this;
          Parent = sn[0]->Parent;
          sn[0]->Parent = this;
          }
        }
      else {
        if (CheckAnzSubNodes ()) {
          sn[AnzSubNodes++] = prev;
          prev->Parent = this;
          Parent = NULL;
          }
        }
      _actcmpl->last = this;
      }
    else {
      WIN_ASSERT(FALSE);
      }
    }
  }

void createopnode (void)
  {
  if (_actcmpl->InInlineFunction())
    _actcmpl->wError = INLINENOTSUPPORTED;
  else
    new exp_node (LPOPLIST (_actcmpl->scv.v.vr),
                  (LPSTR)GlobalLock (_actcmpl->hPars0) + sizeof(WORD));
  }

void createassnode (void)
  {
  if (_actcmpl->InInlineFunction())
    _actcmpl->wError = INLINENOTSUPPORTED;
  else
    new exp_node (_actcmpl->hasList,"=");
  }

void createscondnode ()
  {
  if (_actcmpl->InInlineFunction())
    _actcmpl->wError = INLINENOTSUPPORTED;
  else
    new exp_node (_actcmpl->hcndList,"?");
  }

void createfncnode (void)
  {
  if (_actcmpl->InInlineFunction())
    _actcmpl->wError = INLINENOTSUPPORTED;
  else {
    pushexpression ();
    new exp_node (LPOPLIST (_actcmpl->scv.v.vr),
                 (LPSTR)GlobalLock (_actcmpl->hPars0) + sizeof(WORD));
    _actcmpl->last->patchOffs = 0 ;
    }
  }

void pushparexpression (parse_var FAR *v);
extern void TransformTableID(vardef FAR *h,int TableNr);
extern int GetTnr ();
void ExchangeTableToReuse ()
  {
  _actcmpl->TablesToReuse [++ _actcmpl->AnzTablesToReuse] = WORD(GetTnr());
  }
extern ScriptContent_Entry scent;
TableRef FAR *GetDestTableRef (LPOPLIST f,VirtFunctionCall FAR *fc,int i)
  {
  // Suchen der Basisableitung
  LPSCRIPTCONTENT sc = ((f != NULL) && (f->destContext != NULL)) ? 
        f->destContext : &scent ;
  static TableRef tr;
  for ( tr = sc->TRef[(fc != NULL) ? fc->Ind()[i] : i] ; ; ) {
    LPTABLEDEF td = GetTableAdmin()->GetTableDef (tr.TableNr,tr.Version);
    TableRef trp;
    trp.TableNr = td->GetParentID();
    trp.Version = td->GetParentVersion();
    GetTableAdmin()->FreeTable (tr.TableNr,tr.Version);
    if (trp.TableNr != 0) tr = trp ;
    else                  break ;
    }
  return &tr;
  }
short GetMainTableRef (int i)
  {
  // Suchen der Basisableitung
  LPSCRIPTCONTENT sc = &scent ;
  static TableRef tr;
  for ( ; ; ) {
    tr = sc->TRef[i];
    LPTABLEDEF td = GetTableAdmin()->GetTableDef (tr.TableNr,tr.Version);
    TableRef trp;
    trp.TableNr = td->GetParentID();
    trp.Version = td->GetParentVersion();
    GetTableAdmin()->FreeTable (tr.TableNr,tr.Version);
    if (trp.TableNr != 0) i = i + 1 ;
    else                  break ;
    }
  return i;
  }
void MarkTableToReuse ()
  {
  VirtFunctionCall FAR *fc = (VirtFunctionCall FAR *) (_actcmpl->LastVirtFunction->cmplt + sizeof(WORD));
  _actcmpl->last->extraIndToSetOffset = fc->IndOffs () 
            + sizeof(WORD) ;     // + Groesse des Prefixes
  if (_actcmpl->AnzTablesToReuse > 0) {
    _actcmpl->TablesToReuse[0] = _actcmpl->AnzTablesToReuse ;
    _actcmpl->last->extraIndToSet = LPWORD(GetGlobMem ((_actcmpl->AnzTablesToReuse + 1) * sizeof(WORD)));
    lmemcpy (_actcmpl->last->extraIndToSet,_actcmpl->TablesToReuse,(_actcmpl->AnzTablesToReuse + 1) * sizeof(WORD));
    if (fc->Ind()[-1] == _actcmpl->AnzTablesToReuse) {
      for (int i = 0 ; i < int(_actcmpl->AnzTablesToReuse) ; i ++ ) {
        if (!lmemcmp (GetDestTableRef (_actcmpl->LastVirtFunction,fc,i),&scent.TRef[GetMainTableRef (_actcmpl->TablesToReuse[i+1])],sizeof(scent.TRef[0])))
          _actcmpl->wError = INCOMPTABLES ;
        }
      }
    else
      _actcmpl->wError = INCOMPTABLES ;
    }
  _actcmpl->AnzTablesToReuse = 0;
  }
void createfncnode (parse_var FAR &mname)
  {
  // Die Expression des Modulnamens holen
  if (mname.v.vd.vartype == VAR_STR) {
    createfncnode ();
    // Das Kompilat (aller Auspraegungen) patchen
    LPOPLIST x = LPOPLIST (_actcmpl->scv.v.vr) ; 
    _actcmpl->LastVirtFunction = x ;
    VirtFunctionCall FAR *fc = (VirtFunctionCall FAR *) (x->cmplt + sizeof(WORD));
    TransformTableID (&mname.v.vd.vd,mname.v.vd.TableNr);
    _actcmpl->last->extraDataToSet = GetGlobMem (sizeof(mname.v.vd.vd));
    lmemcpy (_actcmpl->last->extraDataToSet,&mname.v.vd.vd,sizeof(mname.v.vd.vd));
    // _actcmpl->last->extraDataOffs = fc->ParOffs() + sizeof(WORD);
    if (mname.v.vd.isexpression) {
      _actcmpl->last->FixUpExtraOffs = fc->ParOffs() + sizeof(WORD);
      }
    MarkTableToReuse ();
    _actcmpl->AnzTablesToReuse = 0;
    }
  else
    _actcmpl->wError = PARERROR ;
  }
void patchcmpltstatic ()
  {
  _actcmpl->last->patchOffs = 1 ;
  }
void createfncnode_v ()
  {
  parse_var mname;
  // Die Expression des Modulnamens holen
  pushparexpression (&mname);
  createfncnode (mname);
  }

parse_var ass_v;
void createfncnode_r ()
  {
  // Die Expression des Modulnamens steht im Modul - Namen
  createfncnode (ass_v);
  }

void createfncnode_n ()
  {
  if (LPOPLIST (_actcmpl->scv.v.vr)->FType == FTYPE_IMPORT) {
    parse_var mname;
    // in LastModName steht der Modulname
    mname.v.vd.vd.Ident = _actcmpl->pushConst (LastModName,lstrlen(LastModName) + 1,VAR_STR);
    mname.v.vd.vartype = VAR_STR ;
    mname.v.vd.TableNr = 2 ;
    mname.v.vd.isexpression = FALSE ;
    mname.v.vd.isdynamic = FALSE ;
    mname.v.vd.doubleDefined = FALSE ;
    mname.v.vd.vd.DBNummer = 2 ;
    createfncnode (mname);
    }
  else
    createfncnode ();
  }

void GetLastTermSym (vardef FAR *h)
  {
  WIN_ASSERT (_actcmpl->last->termnode);
  h->DBNummer = _actcmpl->last->i.v.r;
  h->DBNummer = _actcmpl->last->i.v.i;
  _actcmpl->last = NULL ;
  }
BOOL CheckLastExp ()
  {
  return _actcmpl->last != NULL;
  }

void pushexpression (void)
  {
  _actcmpl->lstack[_actcmpl->lstacki++] = _actcmpl->last ;
  _actcmpl->last = NULL;
  }

void ScriptCompiler::InitializeExpProc ()
  {
  last = NULL ;
  brlevel = 0 ;
  lastop = NULL ;
  lastoplist = NULL ;
  actres = 0;
  _expdptr = 0;
  lstacki = 0;
  }

void popexpression (void)
  {
  exp_node FAR *top = _actcmpl->last;
  for ( ; ((top != NULL) && (top->Parent != NULL)) ; top = top->Parent) ;
  if (top != NULL)
    top->isready = TRUE ;

  exp_node FAR *h = _actcmpl->lstack[--_actcmpl->lstacki];
  
  if (h != NULL) {
    if (top == NULL) h->isready = TRUE ;
    if ((h->termnode) || (h->isready)) {
      exp_node FAR *p = h->Parent ;
      if (p != NULL) {
        if (p->CheckAnzSubNodes ())
          p->sn[p->AnzSubNodes++] = top ;
        top->Parent = p;
        }
      }
    else {
      top->Parent = h;
      if (h->CheckAnzSubNodes ())
        h->sn[h->AnzSubNodes++] = top;
      }
    }
  if (top)
    _actcmpl->last = top;
  else
    _actcmpl->last = h ;
  setopallowed();
  }

void poppush ()
  {
  popexpression ();
  pushexpression ();
  _actcmpl->opAllowed = FALSE;
  }

//
// Umwandeln der Expression in das Kompilat
//
//////////////////////////////////////////////
void exp_node::GetProg (BOOL forExp,BOOL withProg)
  {
  LPOPLIST f = NULL,fbest = NULL ;
  int AnzFound = 0,AnzFoundFree = 0 ;

  // Oparator / Funktions Match
  LPSTR n = i.f.n;
  int ExtraCmplt = 0;
  for (LPOPLIST ol = i.f.o ; ol != NULL ; ol = ol->Next) {
    if ((ol->AnzArgs == AnzSubNodes) || ((ol->AnzArgs > 0) && (ol->args[ol->AnzArgs - 1].vartyp == VAR_FREEPAR) && (ol->AnzArgs <= AnzSubNodes))) {
      BOOL res = TRUE ;
      BOOL freeDone = FALSE ;
      int j = 0 ;
      for (int i = 0 ; i < AnzSubNodes ; i++) {
        if (ol->args[j].vartyp == VAR_FREEPAR) continue ;
        if (ol->args[j].vartyp == sn[i]->rtyp) {
          j ++ ;
          continue ;
          }
        if ((sn[i]->rtyp == VAR_FREE) && (lstrcmp (n,"=") == 0)) {
          if (ass_v.v.vd.vartype == ol->resdesc.vartyp) continue ;
          res = FALSE ;
          break ;
          }
        if (sn[i]->rtyp == VAR_FREE) {
          freeDone = TRUE ; 
          j ++ ;
          continue ; 
          }
        res = FALSE ;
        break ;
        }
      if (res) {
        AnzFound ++ ;
        if (freeDone)
          AnzFoundFree ++ ;
        else {
          fbest = ol ;
          if (j < i)
            ExtraCmplt = sizeof(DWORD) * (i - j - 1);
          else
            ExtraCmplt = 0;
          }
        f = ol ;
        }
      }
    }

  // Es muss genau 1 Funktion oder Wildcards gefunden worden sein
  if (fbest != NULL) f = fbest ;
  if (f == NULL) 
    _actcmpl->wError = PARERROR ;
  if (AnzFound - AnzFoundFree > 1)
    _actcmpl->wError = SEM_ERROR ;

  if (_actcmpl->wError == 0) {
    if (withProg) {
      int size = sizeof(WORD) + sizeof(WORD) + f->ExtraCount + 
                          f->FncParCount * 2 * sizeof(WORD);
      if (!forExp) _actcmpl->CheckSegs (size + sizeof(DWORD));
      MyProg = LPSTR (GetGlobMem (size + ExtraCmplt));
      lmemcpy (MyProg,f->cmplt,size);
      ((WORD FAR *) MyProg)[1] += ExtraCmplt; // parSize vergroessern

      // ev. Extradaten eintragen
      if (extraDataToSet != NULL) {
        VirtFunctionCall FAR *fc = (VirtFunctionCall FAR *) (f->cmplt + sizeof(WORD));
        short extraDataOffs = fc->ParOffs() + sizeof(WORD);
        lmemcpy (MyProg + extraDataOffs,extraDataToSet,GetBlockSize (extraDataToSet));
        }
      if (extraIndToSetOffset > 0) {
        if (extraIndToSet == NULL) {
          // Verwenden der Default - Kontextkonvertierung
          VirtFunctionCall FAR *fc = (VirtFunctionCall FAR *) (f->cmplt + sizeof(WORD));
          WORD atr = fc->Ind()[-1];
          extraIndToSet = LPWORD(GetGlobMem ((atr + 1) * sizeof(WORD)));
          extraIndToSet[0] = atr ;
          for (int i = 0 ; i < int(atr) ; i++) {
            // Suchen der Basisableitung
            LPSCRIPTCONTENT sc = (f->destContext != NULL) ? f->destContext : &scent ;
            for ( TableRef tr = sc->TRef[fc->Ind()[i]] ; ; ) {
              LPTABLEDEF td = GetTableAdmin()->GetTableDef (tr.TableNr,tr.Version);
              TableRef trp;
              trp.TableNr = td->GetParentID();
              trp.Version = td->GetParentVersion();
              GetTableAdmin()->FreeTable (tr.TableNr,tr.Version);
              if (trp.TableNr != 0) tr = trp ;
              else                  break ;
              }
            // Suchen des Tabellenindex im aktuellen Script
            for ( int j = 0 ; j < int(scent.AnzTables) ; j++) {
              if (lmemcmp (&scent.TRef[j],&tr,sizeof(tr))) break ;
              }
            if (j == int(scent.AnzTables)) _actcmpl->wError = NOTRANSFERKONTEXT ;
            else extraIndToSet[i + 1] = WORD(j) ;
            }
          }
        if (extraIndToSet != NULL)
          lmemcpy (MyProg + extraIndToSetOffset,extraIndToSet,GetBlockSize (extraIndToSet));
        }
      if (patchOffs) {
        if ((*(WORD FAR *) MyProg == PREFIX_FUNCTIONCALL) || (*(WORD FAR *) MyProg == PREFIX_VIRTCALL)) {
          (*(WORD FAR *) MyProg) += 1 ;
          }
        else _actcmpl->wError = NOSTATICALLOWED ;
        }

      // Konstanten eintragen
      ////////////////////////////
      for (int i = 0 ; i < f->AnzConsts ; i++) {
        constarg FAR *c = f->GetCArg(i);
        DWORD ConstRef = MAKELONG(2,_actcmpl->pushConst (c + 1,c->dataSize,c->DataType)) ;
        lmemcpy (MyProg + c->Offset,&ConstRef,sizeof(ConstRef)) ;
        }

      // Resultate der Subnodes eintragen
      //////////////////////////////////////
      int k = 0 ;
      int actOffset;
      for (i = 0 ; i < AnzSubNodes ; i++) {
        if (f->args[k].vartyp == VAR_FREEPAR) {
          actOffset += sizeof(DWORD);
          }
        else {
          actOffset = f->args[k].Offset;
          k ++ ;
          }
        if (sn[i]->FixupPar) {
          // Parameter -> Idents in die Liste einhaengen
          BYTE FAR *testbytes = (BYTE FAR *) (MyProg + actOffset) ;
          for (int j = 0 ; j < 4 ; j++)
            testbytes[j] = BYTE(TESTBYTE + j);

          if (forExp)
            _actcmpl->pushfncExpPar (sn[i]->dwres.Ident,   // Entspricht der Parameternummer
                                    _actcmpl->ExpSize () + sizeof(LPVOID) + 
                                    actOffset + sizeof(DWORD)
                                    );
          else {
            dList d(&_actcmpl->actFncLookup);
            d[sn[i]->dwres.Ident] += 
              _actcmpl->fncOffs () + actOffset + sizeof(DWORD) + sizeof(DWORD);
            }
          }
        else {
          lmemcpy (MyProg + actOffset,&sn[i]->dwres,sizeof(DWORD));
          if (sn[i]->FixupDynamic) {
            // Ident in die liste der dynamisch zu vergebenden Idents
            if (_actcmpl->InInlineFunction()) {
              if (forExp)
                _actcmpl->PushInlineExpId (_actcmpl->ExpSize () + sizeof(LPVOID) + 
                                            actOffset + sizeof(DWORD) +
                                            sizeof(WORD),
                                            sn[i]->dwres.Ident
                                          );
              else
                _actcmpl->MarkInlineforLookup(_actcmpl->fncOffs () + 
                                            actOffset + sizeof(DWORD) +
                                            sizeof(WORD) + sizeof(DWORD),
                                            sn[i]->dwres.Ident
                                              );
              }
            else {
              if (forExp)
                _actcmpl->PushExpId (_actcmpl->ExpSize () + sizeof(LPVOID) + 
                                            actOffset + sizeof(DWORD) +
                                            sizeof(WORD),
                                            sn[i]->dwres.Ident
                                    );
              else
                _actcmpl->PushOffs (_actcmpl->progOffs() + 
                                            actOffset + sizeof(DWORD) +
                                            sizeof(WORD) + sizeof(DWORD),
                                            sn[i]->dwres.Ident
                                  );
              }
            }
          if (sn[i]->FixupPtr) {
            // Offset in die Liste der up to date zu bringenden Offsets
            if (forExp)
              _actcmpl->pushExpExpPtr (_actcmpl->ExpSize () + sizeof(LPVOID) +
                                            actOffset
                                      );
            else {
              if (_actcmpl->InInlineFunction())
                _actcmpl->MarkExpInlineForLookup (_actcmpl->fncOffs() + actOffset + sizeof(DWORD));
              else
                _actcmpl->MarkExpForLookup (_actcmpl->progOffs() + actOffset + sizeof(DWORD));
              }
            }
          }
        }
      progsize = size + ExtraCmplt;
      resop = f ;
      }
    rtyp = f->resdesc.vartyp;
    }
  }

//////////////////////////////////////////////////////////////////////
//      Expression - Buffer Verwaltung
//////////////////////////////////////////////////////////////////////
static LPVOID nullPtr = NULL;

// Zeiger aller Expressions im Buffer (die muessen zum Schluss einzeln
// ins endgueltige Resultat gebracht werden
////////////////////////////////////////////////////////////////////////
void compiler::pushPtr (DWORD offs,WORD size)
  {
  if (InInlineFunction())
    pushPtr (hGInlineExpPtr,offs,size);
  else
    pushPtr (hGExpPtr,offs,size);
  }

//
// Expression rausspielen
//
// (Vorerst ohne common Subexpressions)
//////////////////////////////////////////////////
GLOBALHANDLE PushDWToGlobBlock (GLOBALHANDLE hGmem,LPVOID data,DWORD size)
  {
  LPSTR Buffer;
  DWORD oldsize;
  if (hGmem) {
    Buffer = (LPSTR)GlobalLock (hGmem);
    oldsize = *((DWORD FAR *) Buffer);
    }
  else {
    hGmem = GlobalAlloc (GHND,sizeof(DWORD));
    Buffer = (LPSTR)GlobalLock (hGmem);
    oldsize = *((DWORD FAR *) Buffer) = sizeof(DWORD);
    }
  GlobalUnlock (hGmem);
  hGmem = GlobalReAlloc (hGmem,oldsize + size,GHND);
  Buffer = (LPSTR)GlobalLock (hGmem);
  *((DWORD FAR *) Buffer) += size;
  hmemcpy ((char _huge *) Buffer + oldsize,data,size);
  GlobalUnlock (hGmem);
  return hGmem;
  }

void compiler::PushExpressionData (LPVOID data,int size)
  {
  if (InInlineFunction())
    hGInlineExpBuffer = PushDWToGlobBlock (hGInlineExpBuffer,data,size);
  else
    hGExpBuffer = PushDWToGlobBlock (hGExpBuffer,data,size);
  }

void compiler::pushPtr (GLOBALHANDLE FAR &hGmem,DWORD offs,WORD size)
  {
  WORD count;
  LPSTR Buffer ;
  if (hGmem) {
    Buffer = (LPSTR)GlobalLock (hGmem);
    count = *((WORD FAR *) Buffer) ;
    GlobalUnlock (hGmem);
    }
  else {
    count = 0;
    hGmem = GlobalAlloc (GHND,sizeof(WORD));
    }
  hGmem = GlobalReAlloc (hGmem,(count + 1) * sizeof(ExpPtr) + 
                                        sizeof(WORD),GHND);
  Buffer = (LPSTR)GlobalLock (hGmem);
  ExpPtr FAR * e = (ExpPtr FAR *) (Buffer + sizeof(WORD));
  e[count].dwOffs = offs ;
  e[count].wSize = size;
  *((WORD FAR *) Buffer) += 1;
  }

void compiler::pushExpression (LPVOID data,WORD size)
  {
  pushPtr (ExpSize(),size);
  PushExpressionData (data,size);
  }

// aktuelle Groesse des Expression - Buffers
////////////////////////////////////////////////
DWORD compiler::ExpSize (GLOBALHANDLE hGmem)
  {
  DWORD res = 0;
  if (hGmem) {
    LPSTR Buffer = (LPSTR)GlobalLock (hGmem);
    res = *((DWORD FAR *) Buffer) - sizeof(DWORD);
    GlobalUnlock (hGmem);
    }
  return res;
  }

DWORD compiler::ExpSize ()
  {
  if (InInlineFunction ())
    return ExpSize (hGInlineExpBuffer);
  else
    return ExpSize (hGExpBuffer);
  }

// Offset vermerken, damit er spaeter korrigiert werden kann
//////////////////////////////////////////////////////////////
void compiler::pushExpExpPtr (DWORD Offs)
  {
  if (InInlineFunction ())
    hGInlineExpOffs = PushDWToGlobBlock (hGInlineExpOffs,&Offs,sizeof(DWORD));
  else
    hGExpOffs = PushDWToGlobBlock (hGExpOffs,&Offs,sizeof(DWORD));
  }

// Offsets auf die Expressions im Hauptprogramm
/////////////////////////////////////////////////
void compiler::pushExpPtr (DWORD Offs)
  {
  hGOffs = PushDWToGlobBlock (hGOffs,&Offs,sizeof(DWORD));
  }

void compiler::CorrectProgOffs (DWORD start,DWORD end)
  {
  if (hGOffs) {
    LPSTR expoffss = (LPSTR)GlobalLock (hGOffs);
    DWORD count = (*(DWORD FAR *) expoffss - sizeof(DWORD)) / sizeof(DWORD);
    DWORD huge *o = (DWORD huge *) (expoffss + sizeof(DWORD)) ;
    for (DWORD i = 0 ; i < count ; i++) {
      if ((o[i] >= start) && (o[i] < end))
        o[i] += sizeof (WORD) + sizeof(DWORD);
      }
    GlobalUnlock (hGOffs);
    }
  }

// Fuehrendes NULL Zeiger der Expression anhaengen
//////////////////////////////////////////////////////
void exp_node::WriteCode ()
  {
  if (_actcmpl->wError == 0) {
    LPSTR bf = LPSTR (GetGlobMem (progsize + sizeof(LPVOID)));
    lmemcpy (bf + sizeof(LPVOID),MyProg,progsize);
    _actcmpl->MarkForExpDebPush (_actcmpl->ExpSize ());
    _actcmpl->pushExpression (bf,progsize + sizeof(LPVOID));
    FreeGlobMem (bf);
    }
  }


//
// Aktuelles Resultat (Hilfszeiger vor der Expression)
// in den Code schreiben
////////////////////////////////////////////////////////
void exp_node::FixupRes ()
  {
  if (_actcmpl->wError == 0) {
    vardef FAR *res = (vardef FAR *) (MyProg + resop->resdesc.Offset) ;
    DWORD h = _actcmpl->ExpSize() ;
    h |= 0xEF000000;
    _actcmpl->pushExpExpPtr (_actcmpl->ExpSize() + 
                                  sizeof(LPVOID) + 
                                  resop->resdesc.Offset
                                  );
    res->DBNummer = HIWORD(h);
    res->Ident    = LOWORD(h);
    dwres.DBNummer = HIWORD(h);
    dwres.Ident    = LOWORD(h); 
    FixupPtr = TRUE ;

    if (FixUpExtraOffs) {
      _actcmpl->pushExpExpPtr (_actcmpl->ExpSize() + 
                                  sizeof(LPVOID) + 
                                  FixUpExtraOffs
                                  );
      }
    }
  }

//////////////////////////////////////////////////////////////////
// Code generieren
//////////////////////////////////////////////////////////////////
void exp_node::GenCode (BOOL doWrite)
  {
  for ( int j = 0 ; j < AnzSubNodes ; j++ ) {
    sn[j]->GenCode (TRUE);
    }
  if (termnode) {
    // Trivialer Fall: das Resultat wird kann direkt uebernommen werden
    dwres.DBNummer = i.v.r;
    dwres.Ident = i.v.i ;
    rtyp = i.v.vartyp;
    FixupDynamic = i.v.isdynamic ;
    FixupPar = i.v.ispar;
    if ((i.v.vartyp != VAR_BITMAP) && (i.v.vartyp != VAR_PICTURE))
      TransformTableID(&dwres,i.v.TableNr);
    if ((FixupPar) && (i.v.r != PAR_VAR))
      WIN_ASSERT(FALSE);
    }
  else {
    FixupDynamic = FALSE ;
    if ((doWrite) && (_actcmpl->wError == 0)) {
      GetProg ();
      FixupRes ();
      WriteCode ();
      }
    }
  }

void copyExpRes ()
  {
  if (_actcmpl->InInlineFunction())
    _actcmpl->wError = INLINENOTSUPPORTED;
  lmemcpy (&ass_v,&_actcmpl->scv,sizeof(ass_v));
  }

void copyExpConstRes ()
  {
  setconststr ();
  ass_v.v.vd.vd.Ident = _actcmpl->constOffs;
  ass_v.v.vd.vartype = BYTE(_actcmpl->constType) ;
  ass_v.v.vd.TableNr = 2 ;
  ass_v.v.vd.isexpression = FALSE ;
  ass_v.v.vd.isdynamic = FALSE ;
  ass_v.v.vd.doubleDefined = FALSE ;
  ass_v.v.vd.vd.DBNummer = 2 ;
  }

void exp_node::SetRes ()
  {
  if (_actcmpl->wError == 0) {
    // _actcmpl->CheckSegs (progsize + sizeof(DWORD));
    if ((rtyp == BOOLVARFNC) && (ass_v.v.vd.vartype)) {
      _actcmpl->PushProgOffs ();
      _actcmpl->pushData (MyProg,progsize);
      _actcmpl->Debug_SetProgOffs ();
      }
    else if (rtyp == ass_v.v.vd.vartype) {
      vardef FAR *res = (vardef FAR *) (MyProg + resop->resdesc.Offset) ;
      res->DBNummer = ass_v.v.vd.vd.DBNummer;
      res->Ident    = ass_v.v.vd.vd.Ident;
      TransformTableID(res,ass_v.v.vd.TableNr);
      if (ass_v.v.vd.isdynamic)
        _actcmpl->PushOffs (_actcmpl->progOffs() + resop->resdesc.Offset + sizeof(DWORD),
                            res->Ident
                          );
      _actcmpl->PushProgOffs ();
      _actcmpl->pushData (MyProg,progsize);
      _actcmpl->Debug_SetProgOffs ();
      }
    else if (rtyp == 0xFF) {
      // Es handelt sich um den Aufruf einer einzelnen Funktion
      // -> Kein Return Wert
      _actcmpl->PushProgOffs ();
      _actcmpl->pushData (MyProg,progsize);
      _actcmpl->Debug_SetProgOffs ();
      }
    else
      _actcmpl->wError = NOMATCH;
    }
  }

void matchexpression (void)
  {
  exp_node FAR *top = _actcmpl->last;
  if (top == NULL) {
    ass_v.v.vd.vartype = 0 ;
    return ;
    }
  for ( ; top->Parent != NULL ; top = top->Parent) ;

  if (ass_v.v.vd.vartype == BOOLVARFNC) {
    if (!top->termnode) {
      top->GenCode (FALSE);   // Letzte Funktion wird in das Hauptprogramm geschrieben
      top->GetProg (FALSE,FALSE);   // ev. notwendige Updates in das Hauptprogramm hinein
      if (top->rtyp != BOOLVARFNC) {
        createscondnode ();
        top = _actcmpl->last;
        for ( ; top->Parent != NULL ; top = top->Parent) ;
        top->GenCode (FALSE);   // Letzte Funktion wird in das Hauptprogramm geschrieben
        top->GetProg (FALSE);   // ev. notwendige Updates in das Hauptprogramm hinein
        top->SetRes ();
        }
      else {
        top->GetProg (FALSE);
        top->SetRes ();
        }
      }
    else {
      createscondnode ();
      top = _actcmpl->last;
      for ( ; top->Parent != NULL ; top = top->Parent) ;
      top->GenCode (FALSE);   // Letzte Funktion wird in das Hauptprogramm geschrieben
      top->GetProg (FALSE);   // ev. notwendige Updates in das Hauptprogramm hinein
      top->SetRes ();
      }
    ass_v.v.vd.vartype = 0 ;
    }
  else {
    if (!top->termnode) {
      top->GenCode (FALSE);   // Letzte Funktion wird in das Hauptprogramm geschrieben
      top->GetProg (FALSE);   // ev. notwendige Updates in das Hauptprogramm hinein
      top->SetRes ();
      }
    else {
      createassnode ();
      top = _actcmpl->last;
      for ( ; top->Parent != NULL ; top = top->Parent) ;
      top->GenCode (FALSE);   // Letzte Funktion wird in das Hauptprogramm geschrieben
      top->GetProg (FALSE);   // ev. notwendige Updates in das Hauptprogramm hinein
      top->SetRes ();
      }
    }
  _actcmpl->last = NULL ;
  }
                       
void setsimplecond ()
  {
  if (_actcmpl->InInlineFunction())
    _actcmpl->wError = INLINENOTSUPPORTED;
  ass_v.v.vd.vartype = BOOLVARFNC ;
  }

void setcmpcond ()
  {
  if (_actcmpl->InInlineFunction())
    _actcmpl->wError = INLINENOTSUPPORTED;
  else
    new exp_node (LPOPLIST (_actcmpl->scv.v.vr),
                  (LPSTR)GlobalLock (_actcmpl->hPars0) + sizeof(WORD));
  ass_v.v.vd.vartype = BOOLVARFNC ;
  }
////////////////////////////////////////////////////////////////////
//
//      Expressions hinten am Code anhaengen
//
////////////////////////////////////////////////////////////////////
void compiler::CheckExpSegs (DWORD Offs,WORD Size)
  {
  // Nachsehen, ob die Expression nicht an einer Segmentgrenze zu 
  // liegen kommt
  DWORD ActSize = progOffs ();
  DWORD SegOffs = ActSize % 0xFFFF ;
  if (LONG(SegOffs) >= LONG(0xFFFF - Size - 5)) {
    GLOBALHANDLE hGmem = GlobalAlloc (GHND,Size + 0x10);
    LPSTR DummyBuffer = (LPSTR)GlobalLock (hGmem);
    ((WORD FAR *) DummyBuffer)[0] = PREFIX_NOP;
    ((WORD FAR *) DummyBuffer)[1] = Size + 0x10 - sizeof(WORD);
    for (WORD i = 2 * sizeof(WORD) ; i < Size + 0x10 ; i++) {
      DummyBuffer[i] = char(i) ;
      }
    pushData (DummyBuffer,Size + 0x10);
    GlobalUnlock (hGmem);
    GlobalFree (hGmem);
    // Vermerken, dass Offset korrigiert wurde
    _actcmpl->corr_offs[_actcmpl->corr_ptr].dwOffs = Offs;
    _actcmpl->corr_offs[_actcmpl->corr_ptr].wSize = Size + 0x10 ;
    _actcmpl->corr_ptr ++ ;
    }
  }

// Korrigieren eines Offsets, da es zu Verschiebungen wegen der Segment-
// korrekturen kommen koennte
////////////////////////////////////////////////////////////////////////
DWORD compiler::Correct_dwOffs (DWORD Offset)
  {
  DWORD dwres = 0;
  for ( int i = 0 ; i < _actcmpl->corr_ptr ; i++) {
    if (Offset < _actcmpl->corr_offs[i].dwOffs) break ;
    dwres += _actcmpl->corr_offs[i].wSize ;
    }
  return Offset + dwres ;
  }

// Debuginfo Schreiben
extern void SetDebugOffset (DWORD Offs);
struct ExpDebugInfo {
  DWORD Offs;
  DWORD LineNmbr;
  DWORD IncNmbr;
  };

// Stueck fuer Stueck der Expressions hinten anhaengen
void compiler::AddExpressions ()
  {
  if (hGExpPtr) {
    LPSTR Buffer = (LPSTR)GlobalLock (hGExpPtr);
    WORD count = *((WORD FAR *) Buffer);
    ExpPtr FAR * e = (ExpPtr FAR *) (Buffer + sizeof(WORD));
    char huge *expbuffer = (char huge *) GlobalLock (hGExpBuffer) + 
                                sizeof(DWORD);
    for (WORD i = 0 ; i < count ; i++) {
      CheckExpSegs (e[i].dwOffs,e[i].wSize);
      pushData (expbuffer + e[i].dwOffs,e[i].wSize);
      }
    GlobalUnlock (hGExpPtr);
    GlobalFree (hGExpPtr);
    GlobalUnlock (hGExpBuffer);
    GlobalFree (hGExpBuffer);
    hGExpPtr = 0;
    hGExpBuffer = 0;
    }
  }

// Alle Zeiger korrigieren
//////////////////////////////
void compiler::CorrectExpOffs (char huge *base,DWORD boffs,DWORD rOffs)
  {
  if (hGExpOffs) {
    LPSTR expoffss = (LPSTR)GlobalLock (hGExpOffs);
    DWORD count = (*(DWORD FAR *) expoffss - sizeof(DWORD)) / sizeof(DWORD);
    DWORD huge *o = (DWORD huge *) (expoffss + sizeof(DWORD)) ;
    for (DWORD i = 0 ; i < count ; i++) {
      DWORD or = Correct_dwOffs(o[i]) + boffs;
      vardef FAR *ref = (vardef FAR *) (base + or) ;
      DWORD h = MAKELONG(ref->Ident,ref->DBNummer);
      if ((h & 0xFF000000) == 0xEF000000) {
        h &= 0x00FFFFFF ;
        h = Correct_dwOffs(h) + boffs + rOffs + sizeof(WORD);
        h |= 0xEF000000 ;
        ref->DBNummer = HIWORD(h);
        ref->Ident = LOWORD(h);
        }
      else {
        WIN_ASSERT(FALSE);
        }
      }
    GlobalUnlock (hGExpOffs);
    GlobalFree (hGExpOffs);
    hGExpOffs = 0;
    }
  }

void pushparexpression (parse_var FAR *v)
  {
  exp_node FAR *top = _actcmpl->last;
  if (v == NULL) {
    for ( ; top->Parent != NULL ; top = top->Parent) ;
    }

  parse_var h;
  h = _actcmpl->scv;
  if (!top->termnode) {
    // Expression
    top->GenCode (TRUE);

    // Und noch eine Variable vortaeuschen
    if (_actcmpl->wError == 0) {
      if (v != NULL) {
        v->type = VARID;
        v->v.vd.vd.Ident     = top->dwres.Ident ;
        v->v.vd.vd.DBNummer  = 0xEF00 | top->dwres.DBNummer ;
        v->v.vd.isdynamic    = FALSE ;
        v->v.vd.isexpression = TRUE ;
        v->v.vd.vartype      = BYTE (top->resop->resdesc.vartyp) ;
        v->v.vd.TableNr = -1;
        }
      else {
        if (v != NULL) {
          v->type = VARID;
          v->v.vd.vd.Ident     = top->dwres.Ident ;
          v->v.vd.vd.DBNummer  = 0xEF00 | top->dwres.DBNummer ;
          v->v.vd.isdynamic    = FALSE ;
          v->v.vd.isexpression = TRUE ;
          v->v.vd.vartype      = BYTE (top->resop->resdesc.vartyp) ;
          v->v.vd.TableNr = -1;
          }
        else {
          _actcmpl->scv.type = VARID;
          _actcmpl->scv.v.vd.vd.Ident     = top->dwres.Ident ;
          _actcmpl->scv.v.vd.vd.DBNummer  = 0xEF00 | top->dwres.DBNummer ;
          _actcmpl->scv.v.vd.isdynamic    = FALSE ;
          _actcmpl->scv.v.vd.isexpression = TRUE ;
          _actcmpl->scv.v.vd.vartype      = BYTE (top->resop->resdesc.vartyp) ;

          // Den Zeiger nun noch ins Programm schreiben
          _actcmpl->pushpar () ;
          }
        }
      }
    }
  else {
    // Reine Variable
    if (top->i.v.ispar) {
      WIN_ASSERT (v == NULL);
      _actcmpl->scv.type = PARID ;
      _actcmpl->scv.v.pd.pd.Extra    = BYTE(top->i.v.vartyp) ;
      _actcmpl->scv.v.pd.pd.par_kind = BYTE(top->i.v.r) ;
      _actcmpl->scv.v.pd.Number      = top->i.v.i;

      _actcmpl->pushfncpar ();
      }
    else {
      if (v != NULL) {
        v->type = VARID;
        v->v.vd.vd.Ident     = top->i.v.i ;
        v->v.vd.vd.DBNummer  = top->i.v.r ;
        v->v.vd.isdynamic    = top->i.v.isdynamic ;
        v->v.vd.isexpression = FALSE ;
        v->v.vd.vartype      = BYTE (top->i.v.vartyp) ;
        v->v.vd.TableNr      = top->i.v.TableNr;
        }
      else {
        _actcmpl->scv.type = VARID;
        _actcmpl->scv.v.vd.vd.Ident     = top->i.v.i ;
        _actcmpl->scv.v.vd.vd.DBNummer  = top->i.v.r ;
        _actcmpl->scv.v.vd.isdynamic    = top->i.v.isdynamic ;
        _actcmpl->scv.v.vd.isexpression = FALSE ;
        _actcmpl->scv.v.vd.vartype      = BYTE (top->i.v.vartyp) ;
        _actcmpl->scv.v.vd.TableNr      = top->i.v.TableNr ;

        // Die Variable direkt ins Programm schreiben
        _actcmpl->pushpar ();
        }
      }
    }
  _actcmpl->scv = h;
  if (v != NULL) {
    if (top->Parent != NULL) {
      top->Parent->AnzSubNodes -- ;
      _actcmpl->last = top->Parent ;
      }
    else
      _actcmpl->last = NULL ;
    }
  else
    _actcmpl->last = NULL ;
  }
void pushparexpression ()
  {
  pushparexpression (NULL);
  }

void getparexpression (vardef FAR *vd,DWORD varOffset,int FAR *TableNr)
  {
  *TableNr = -1;
  exp_node FAR *top = _actcmpl->last;
  for ( ; top->Parent != NULL ; top = top->Parent) ;

  if (!top->termnode) {
    // Expression
    top->GenCode (TRUE);

    // Und noch eine Variable vortaeuschen
    if (_actcmpl->wError == 0) {
      vd->Ident = top->dwres.Ident;
      vd->DBNummer = 0xEF00 | top->dwres.DBNummer ;
      _actcmpl->MarkExpForLookup (varOffset);
      }
    }
  else {
    // Reine Variable
    if (top->i.v.ispar) {
      WIN_ASSERT (FALSE);
      }
    else {
      vd->Ident = top->i.v.i ;
      vd->DBNummer = top->i.v.r ;
      *TableNr = top->i.v.TableNr ;
      }
    }
  _actcmpl->last = NULL ;
  }

void setopallowed ()
  {
  _actcmpl->opAllowed = TRUE;
  }

void popexpression1 ()
  {
  popexpression ();
  setopallowed ();
  }

void popexpression2 ()
  {
  popexpression ();
  popexpression ();
  setopallowed ();
  }

void ScriptCompiler::FixupExpOffs (char _huge *base,DWORD boffs,DWORD roffs)
  {
  for ( ; ExpOffsList != NULL ; ) {
    DWORD or = ExpOffsList->Offs;
    vardef FAR *ref = (vardef FAR *) (base + or - sizeof(DWORD) - roffs);
    DWORD h = MAKELONG (ref->Ident,ref->DBNummer);
    if ((h & 0xFF000000) == 0xEF000000) {
      h &= 0x00FFFFFF ;
      h = Correct_dwOffs(h) + boffs + sizeof(WORD);
      h |= 0xEF000000 ;
      ref->DBNummer = HIWORD(h);
      ref->Ident = LOWORD(h);
      }
    else {
      WIN_ASSERT(FALSE);
      }
    LPLUE next = ExpOffsList->Next;
    FreeGlobMem (ExpOffsList);
    ExpOffsList = next;
    }
  }

DLLExport DWORD _export WINAPI GetFunctionsAddress (LPSTR Name,LPVOID exportDef,LPWORD FAR *TableInds,WORD FAR *Restype)
  {
  // Suchen des @ als Trennzeichne
  char tmp[128];
  LPSTR x = tmp;
  for (LPSTR p = Name ; *p != '@' ; *x++ = *p++) ;
  p ++ ; *x = '\0' ;

  // Suchen der Liste mit den Funktionsprototypen
  HPSTR hb = HPSTR(exportDef);
  DWORD ListBeg = IsReferenced (tmp,(char huge *) exportDef,NULL);
  for ( ; ListBeg != 0L ; ) {
    LPOPLIST o = LPOPLIST(hb + ListBeg);
    BOOL found ;
    if (o->args != 0L) {
      LPWORD ssize = LPWORD(hb + DWORD(o->args));
      oparg FAR *arg = (oparg FAR *) (ssize+1);
      found = TRUE ;
      for (int i = 0 ; i < o->AnzArgs ; i++) {
        found = found && (p[i] == GetArgBez(arg[i].vartyp));
        }
      found = found && (p[i] == '\0') ;
      }
    else
      found = (*p == '\0') ;
    if (found) {
      if (o->TableInds != 0L) {
        LPWORD ssize = LPWORD(hb + DWORD(o->TableInds));
        *TableInds = LPWORD (ssize+1);
        *Restype = o->resdesc.vartyp ;
        }
      return o->procAddr ;
      }
    ListBeg = DWORD (o->Next) ;
    }
  return 0L ;
  }

DLLExport void _export WINAPI GetFunctionName (LPSTR Name,LPSTR buffer,int AnzArgs,WORD FAR *vtype)
  {
  lstrcpy (buffer,Name);
  lstrcat (buffer,"@");
  buffer += lstrlen(buffer);
  for ( int i = 0 ; i < AnzArgs ; i++)
    buffer[i] = GetArgBez (vtype[i]);
  buffer[i] = '\0';
  }

BOOL IsDeclared ()
  {
  if (_actcmpl->hefHash == NULL) return FALSE ;
  char decname[128];
  decname[0] = '.' ;
  lstrncpy (decname + 1,LastFuncName,sizeof(decname)-2);
  LPOPLIST FAR *ol = (LPOPLIST FAR *)_actcmpl->hefHash->GetData (decname);
  if (ol != NULL) {
    for (LPOPLIST x = *ol ; x != NULL ; x = x->Next) {
      if ((x->AnzArgs == _actcmpl->lastop->AnzArgs) &&
          (x->resdesc.vartyp == _actcmpl->lastop->resdesc.vartyp)) {
        BOOL found = TRUE ;
        for (int i = 0 ; ((i < x->AnzArgs) && (found)) ; i++) {
          if (x->args[i].vartyp != _actcmpl->lastop->args[i].vartyp)
            found = FALSE ;  
          }
        if (found) return (x->FType == FTYPE_DECLARE);
        }
      }
    }
  return FALSE ;
  }

