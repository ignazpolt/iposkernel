//////////////////////////////////////////////////
//  Allgemeine Hilfsfunktionen fuer Dictionary
//////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/rev/dict.cpv   1.5   23 Feb 1999 15:10:26   Hannes  $
//  $Log:   P:/marille/clinicum/rev/dict.cpv  $
// 
//    Rev 1.5   23 Feb 1999 15:10:26   Hannes
// Fehlertoleranter
// 
//    Rev 1.4   13 Nov 1997 12:40:42   Hannes
// diverse Fehlerkorrekturen
// 
//    Rev 1.3   10 Nov 1997 10:48:34   Hannes
// Fehlerkorrektur
// 
//    Rev 1.2   07 Nov 1997 14:52:40   Hannes
// 
//    Rev 1.1   06 Nov 1997 19:25:58   Hannes
// diverse Fehlerkorrekturen
// 
//    Rev 1.0   27 Oct 1997 19:50:42   Hannes
// Initial revision.
// 
//
#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#include "globmem.h"
#include "dds.hpp"

#include "printer.hpp"
#include "sc2d.hpp"
#include "font.hpp"
#include "paint.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "scripthd.hpp"
#include "mdichild.hpp"
#define MODULENUM 184
#include "winass.hpp"
#include "winextra.hpp"

#include "cfield.hpp"

#include "hash.hpp"
#include "compile.hpp"

#define MODE_CS             0
#define MODE_CIS            1
#define MODE_FIRSTEQUAL     2
#pragma pack(1)
struct FAR DictNode {
  char ch;
  DWORD Alt;
  DWORD Next;
  WORD mode;
  DWORD NodeData;
  };
struct FAR DictStart {
  WORD mode;
  DWORD Start;
  };
typedef DictNode FAR *LPDICTNODE;
typedef DictStart FAR *LPDICTSTART;
struct FAR GetDictNode_param {
  WORD parSize;
  DWORD Node;
  DWORD blob;
  DWORD String;
  DWORD mode;
  DWORD NodeData;
  };
struct FAR AddDictNode_param {
  WORD parSize;
  DWORD blob;
  DWORD String;
  DWORD mode;
  DWORD NodeData;
  };
#pragma pack()
DictNode FAR *FindDictNode_CS (char huge * Base,DWORD Start,char ch,LPDWORD lpAlt)
  {
  DictNode FAR *h = (DictNode FAR *) (Base + Start);
  for ( ; ; ) {
    if (h->ch == ch) break;
    if (h->Alt != 0L)
      h = (DictNode FAR *) (Base + h->Alt);
    else {
      if (h != NULL)
        *lpAlt = (char huge *) &h->Alt - Base;
      h = NULL;
      break ;
      }
    }
  return h ;
  }

char ToUpper (char ch)
  {
#ifdef WIN32
  char x[2];
  x[0] = ch ;
  x[1] = '\0';
  CharUpper(x);
  return x[0];
#else
  return (char) (DWORD) AnsiUpper(LPSTR (MAKELP(0,ch)));
#endif
  }

DictNode FAR *FindDictNode_CIS (char huge * Base,DWORD Start,char ch,LPDWORD lpAlt)
  {
  DictNode FAR *h = (DictNode FAR *) (Base + Start);
  for ( ; ; ) {
    if (ToUpper (h->ch) == ToUpper(ch)) break ;
    if (h->Alt != 0L)
      h = (DictNode FAR *) (Base + h->Alt);
    else {
      if (h != NULL)
        *lpAlt = (char huge *) &h->Alt - Base;
      h = NULL;
      break ;
      }
    }
  return h ;
  }

DWORD AddNodeData (LPBLOBDESC bd,WORD Size)
  {
  DWORD nSize,nOffs;
  if (0xFFFF - (bd->Size & 0xFFFF) > Size) {
    nSize = bd->Size + Size;
    nOffs = bd->Size;
    }
  else {
    nOffs = ((bd->Size / 0x10000) + 1) * 0x10000;
    nSize = nOffs + DWORD(Size);
    }
  bd->hGmem = GlobalReAlloc (bd->hGmem,nSize,GMEM_MOVEABLE);
  bd->Size = nSize;
  lmemset ((char huge *) GlobalLock (bd->hGmem) + nOffs,'\0',Size);
  GlobalUnlock (bd->hGmem);

  return nOffs;
  }

DWORD GetDictNode_CS (BlobDesc FAR *bd,char ch)
  {
  DWORD nOffs = AddNodeData (bd,sizeof(DictNode));
  LPDICTNODE n = LPDICTNODE ((char huge *) GlobalLock (bd->hGmem) + nOffs);
  lmemset (n,'\0',sizeof(*n));
  n->ch = ch;
  GlobalUnlock (bd->hGmem);
  return nOffs;
  }

DWORD GetDictNode_CIS (BlobDesc FAR *bd,char ch)
  {
  DWORD nOffs = AddNodeData (bd,sizeof(DictNode));
  LPDICTNODE n = LPDICTNODE ((char huge *) GlobalLock (bd->hGmem) + nOffs);
  lmemset (n,'\0',sizeof(*n));
  n->ch = ToUpper (ch);
  GlobalUnlock (bd->hGmem);
  return nOffs;
  }

typedef DictNode FAR *(* FINDDICTNODE) (char huge * Base,DWORD Start,char ch,LPDWORD lpApt);
typedef DWORD (* GETDICTNODE) (BlobDesc FAR *bd,char ch);
FINDDICTNODE fdn[2] = {
  FindDictNode_CS,
  FindDictNode_CIS
  };
GETDICTNODE gdn[2] = {
  GetDictNode_CS,
  GetDictNode_CIS
  };
BOOL AddDictNode (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    AddDictNode_param FAR *par = (AddDictNode_param FAR *)param;
    LPSTR String = LPSTR (c->ReadlData (par->String));
    LPBLOBDESC blob = LPBLOBDESC (c->ReadlData (par->blob));
    LPWORD mode = LPWORD (c->ReadlData (par->mode));
    LPVOID NodeData = c->ReadlData (par->NodeData);
    WIN_ASSERT ((mode != NULL) && (String != NULL) && (NodeData != NULL) &&
                (*mode >= 0) && (*mode <= 1));
    LPDICTSTART base;
    BlobDesc bd;
    if (blob != NULL) {
      bd = *blob;
      base = LPDICTSTART (GlobalLock (bd.hGmem));
      DBWIN_ASSERT (base->mode == *mode);
      }
    else {
      bd.hGmem = GlobalAlloc (GMEM_MOVEABLE,sizeof(DictStart));
      bd.Size = sizeof(DictStart);
      base = LPDICTSTART (GlobalLock (bd.hGmem));
      base->mode = *mode;
      base->Start = 0L;
      }

    FINDDICTNODE f = fdn[*mode];
    GETDICTNODE g = gdn[*mode];
    DWORD Start = base->Start;
    DWORD lpAlt = (char huge *)&base->Start - (char huge *) base;
    LPDICTNODE n = NULL ;
    LPSTR h = String ;
    if (Start != 0L) {
      for ( ; (*h) ; h ++) {
        // Im Aktuellen Pfad Suchen
        //--------------------------
        n = (*f) (LPSTR (base),Start,*h,&lpAlt);
        if (n == NULL) break ;
        else {
          Start = n->Next;
          if (Start == 0L) {
            lpAlt = (char huge *)&n->Next - (char huge *) base;
            h ++ ;  // Das aktuelle Zeichen abhacken
            break ;
            }
          }
        }
      }
    GlobalUnlock (bd.hGmem);
    for ( ; (*h) ; h++) {
      // Neue Knoten Anlegen
      //--------------------------
      DWORD nOffs = (* g) (&bd,*h);
      base = LPDICTSTART (GlobalLock (bd.hGmem));
      *(DWORD FAR *) ((char huge *) base + lpAlt) = nOffs;
      n = LPDICTNODE ((char huge *) base + nOffs);
      lpAlt = (char huge *) &n->Next - (char huge *) base;
      GlobalUnlock (bd.hGmem);
      }
    DWORD oldNodeData = n->NodeData;

    // Knotendaten ablegen
    //--------------------------
    char huge *hbase = (char huge *)GlobalLock(bd.hGmem);
    DWORD NodeOffs = (char huge *)&n->NodeData - hbase ;
    GlobalUnlock(bd.hGmem);
    DWORD NodeDataOffs = AddNodeData (&bd,GetBlockSize (NodeData) + sizeof(WORD) + sizeof(DWORD));
    hbase = (char huge *)GlobalLock(bd.hGmem);
    *(DWORD FAR *) (hbase + NodeOffs) = NodeDataOffs;
    LPSTR nData = (char huge *)GlobalLock(bd.hGmem) + NodeDataOffs;
    *(DWORD FAR *) nData = oldNodeData;
    *(WORD FAR *) (nData + sizeof(DWORD)) = GetBlockSize (NodeData);
    lmemcpy (nData + sizeof(WORD) + sizeof(DWORD),NodeData,GetBlockSize (NodeData));
    GlobalUnlock(bd.hGmem);

    c->WritelData (par->blob,&bd,sizeof(bd),LPSTR(param) - sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    AddDictNode_param FAR *par = (AddDictNode_param FAR *)param;
    c->ClearlConnection (par->String,LPSTR(param) - sizeof(WORD));
    c->ClearlConnection (par->NodeData,LPSTR(param) - sizeof(WORD));
    c->ClearlConnection (par->mode,LPSTR(param) - sizeof(WORD));
    }
  return FALSE ;
  }

struct FAR NodePtr {
  DWORD NextDataPtr;
  DWORD NodeOffs[1];
  int Count()
    {
    return (this != NULL) ? (GetBlockSize(this) / sizeof(DWORD) - 1) : 0 ;
    }
  };
typedef NodePtr FAR* LPNODEPTR;
LPNODEPTR PushNode (LPNODEPTR old,DWORD Data)
  {
  LPNODEPTR n;
  if (old != NULL) {
    n = LPNODEPTR (GetGlobMem (GetBlockSize (old) + sizeof(Data)));
    lmemcpy (n,old,GetBlockSize(old));
    n->NodeOffs[GetBlockSize (old) / sizeof(DWORD) - 1] = Data;
    FreeGlobMem (old);
    }
  else {
    n = LPNODEPTR (GetGlobMem (sizeof (*n)));
    n->NextDataPtr = 0;
    n->NodeOffs[0] = Data;
    }
  return n;
  }

LPNODEPTR PopNode (LPNODEPTR old)
  {
  LPNODEPTR n;
  if (GetBlockSize (old) > sizeof(*old)) {
    n = LPNODEPTR (GetGlobMem (GetBlockSize (old) - sizeof(DWORD)));
    lmemcpy (n,old,GetBlockSize(n));
    FreeGlobMem (old);
    }
  else {
    FreeGlobMem (old);
    n = NULL ;
    }
  return n;
  }

BOOL NextNode (mdiChild *c,GetDictNode_param FAR *par,LPNODEPTR FAR *NodeData,BlobDesc FAR *bd,BOOL TakeFirst = FALSE)
  {
  char huge *base = (char huge *) GlobalLock (bd->hGmem);
  if ((*NodeData)->NextDataPtr) {
    // Daten schreiben und fertig
    GlobalUnlock (bd->hGmem);
    c->WritelData (par->Node,base + (*NodeData)->NextDataPtr + sizeof(WORD) + sizeof(DWORD),
            *(WORD FAR*) (base + (*NodeData)->NextDataPtr + sizeof(DWORD)),LPSTR(par)-sizeof(WORD));
    (*NodeData)->NextDataPtr = *(DWORD FAR*) (base + (*NodeData)->NextDataPtr);
    c->WritelData (par->NodeData,*NodeData,GetBlockSize (*NodeData),LPSTR(par)-sizeof(WORD));
    FreeGlobMem (*NodeData);
    GlobalUnlock (bd->hGmem);
    return TRUE ;
    }
  else {
    int cnt = (*NodeData)->Count() - 1;
    LPDICTNODE n = LPDICTNODE ((* NodeData)->NodeOffs [cnt] + base);
    if ((TakeFirst) && (n->NodeData)) {
      // Daten schreiben und fertig
      GlobalUnlock (bd->hGmem);
      c->WritelData (par->Node,base + n->NodeData + sizeof(WORD) + sizeof(DWORD),
              *(WORD FAR*) (base + n->NodeData + sizeof(DWORD)),LPSTR(par)-sizeof(WORD));
      (*NodeData)->NextDataPtr = *(DWORD FAR*) (base + n->NodeData);
      c->WritelData (par->NodeData,*NodeData,GetBlockSize (*NodeData),LPSTR(par)-sizeof(WORD));
      FreeGlobMem (*NodeData);
      return TRUE ;
      }
    if (n->Next != 0L) {
      *NodeData = PushNode (*NodeData,n->Next);
      if (NextNode (c,par,NodeData,bd,TRUE)) {
        GlobalUnlock (bd->hGmem);
        return TRUE ;
        }
      }
    for ( ; (cnt > 0) ; ) {
      LPDICTNODE n = LPDICTNODE (base + (* NodeData)->NodeOffs [cnt]);
      if (n->Alt != NULL) {
        (* NodeData)->NodeOffs [cnt] = n->Alt ;
        if (NextNode (c,par,NodeData,bd,TRUE)) {
          GlobalUnlock (bd->hGmem);
          return TRUE;
          }
        }
      *NodeData = PopNode (*NodeData);
      cnt = (*NodeData)->Count() - 1;
      }
    GlobalUnlock (bd->hGmem);
    }
  return FALSE ;
  }

BOOL GetFirstDictNode (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    GetDictNode_param FAR *par = (GetDictNode_param FAR *) param;
    LPSTR String = LPSTR (c->ReadlData (par->String));
    LPBLOBDESC blob = LPBLOBDESC (c->ReadlData (par->blob));
    LPWORD mode = LPWORD (c->ReadlData (par->mode));
    WIN_ASSERT ((mode != NULL) && (String != NULL));
    LPDICTSTART base;
    if ((blob != NULL) && (blob->Size > 0L))
      base = LPDICTSTART (GlobalLock (blob->hGmem));
    else
      return FALSE ;
    FINDDICTNODE f = fdn[base->mode];
    DWORD Start = base->Start;
    LPDICTNODE n = LPDICTNODE ((char huge *) base + Start);
    DWORD lpAlt;
    LPSTR h = String ;
    for ( ; ((*h) && (*h != '%')) ; ) {
      n = (*f) (LPSTR (base),Start,*h,&lpAlt);
      if (n == NULL) break ;
      h ++ ;
      if ((*h == '\0') || (*h == '%')) break;
      else {
        Start = n->Next;
        if (Start == 0L) {
          n = NULL;
          break ;
          }
        }
      }
    if ((*h == '\0') || (*h == '%')) {
      if (*mode & MODE_FIRSTEQUAL) {
        LPNODEPTR NodeData = PushNode (NULL,(char huge *)n - (char huge *)base);
        NextNode (c,par,&NodeData,blob,TRUE);
        }
      else {
        if (n->NodeData) {
          LPWORD NodeSize = LPWORD ((char huge *) base + n->NodeData + sizeof(DWORD));
          c->WritelData (par->Node,NodeSize + 1,*NodeSize,LPSTR(param) - sizeof(WORD));
          short dummy;
          c->WritelData (par->NodeData,&dummy,sizeof(short),LPSTR (param) - sizeof(WORD));
          }
        else {
          c->DellData (par->Node,LPSTR (param) - sizeof(WORD));
          c->DellData (par->NodeData,LPSTR (param) - sizeof(WORD));
          }
        }
      }
    else {
      c->DellData (par->NodeData,LPSTR (param) - sizeof(WORD));
      c->DellData (par->Node,LPSTR (param) - sizeof(WORD));
      }
    GlobalUnlock (blob->hGmem);
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    GetDictNode_param FAR *par = (GetDictNode_param FAR *) param;
    c->ClearlConnection (par->String,LPSTR(param) - sizeof(WORD));
    c->ClearlConnection (par->blob,LPSTR(param) - sizeof(WORD));
    c->ClearlConnection (par->mode,LPSTR(param) - sizeof(WORD));
    }
  return FALSE ;
  }


BOOL GetNextDictNode (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    GetDictNode_param FAR *par = (GetDictNode_param FAR *) param;
    LPNODEPTR nOld = LPNODEPTR (c->ReadlData (par->NodeData));
    LPBLOBDESC blob = LPBLOBDESC (c->ReadlData (par->blob));
    if ((nOld != NULL) && (GetBlockSize (nOld) > sizeof(short))) {
      LPNODEPTR NodeData = LPNODEPTR (GetGlobMem (GetBlockSize (nOld)));
      lmemcpy (NodeData,nOld,GetBlockSize(nOld));
      if (!NextNode (c,par,&NodeData,blob,FALSE)) {
        c->DellData (par->Node,LPSTR (param) - sizeof(WORD));
        c->DellData (par->NodeData,LPSTR (param) - sizeof(WORD));
        }
      }
    else
      c->DellData (par->Node,LPSTR (param) - sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    GetDictNode_param FAR *par = (GetDictNode_param FAR *) param;
    c->ClearlConnection (par->String,LPSTR(param) - sizeof(WORD));
    c->ClearlConnection (par->blob,LPSTR(param) - sizeof(WORD));
    }
  return FALSE ;
  }
