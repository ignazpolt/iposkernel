//
//      Arbeiten mit Hash - Tabellen
//
// $Header:   P:/marille/clinicum/ddsmem/rev/hash.cpv   1.6   13 Sep 1996 10:11:26   HANNES  $
// $Log:   P:/marille/clinicum/ddsmem/rev/hash.cpv  $
// 
//    Rev 1.6   13 Sep 1996 10:11:26   HANNES
// StoreHugeHash mit VOIDKEY
// 
//    Rev 1.5   04 Feb 1996 18:35:40   HANNES
// 
//    Rev 1.4   04 Feb 1996 17:51:10   HANNES
// 
//    Rev 1.3   04 Feb 1996 15:20:56   GERHOLD
// 
//    Rev 1.2   02 Feb 1996 10:41:34   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.1   20 Sep 1994 11:21:14   HANNES
// Verbessertes Void - Key Handling
// 
//    Rev 1.0   24 Jun 1994 16:37:06   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.5   14 Feb 1994 17:58:02   HANNES
// IshashEmpty exportiert
// 
//    Rev 1.4   04 Feb 1994 16:53:20   HANNES
// StoreHugeHash, GetHugeHash
// 
//    Rev 1.3   04 Jan 1994 17:24:58   HANNES
// Alle Auspr„gungen von PushToHandle extern zug„nglich gemacht
// Neue Auspr„gung von PushToHandle: (Ident,size,data..)
// 
//    Rev 1.2   18 Apr 1993 22:31:56   HANNES
// Fehlerkorrekturen bei der Speicherfreigabe
// 
//    Rev 1.1   05 Apr 1993 10:37:12   HANNES
// SetData (LONG..)
// 
//    Rev 1.0   02 Apr 1993 20:06:54   HANNES
// Initial revision.
// 
//    Rev 1.4   02 Apr 1993 18:09:20   HANNES
// Andere Speicherverwaltung
// 
//    Rev 1.3   11 Mar 1993 19:48:58   HANNES
// Fehlerkorrektur bei LONG Tabellen
// 
//    Rev 1.2   08 Mar 1993 14:52:54   HANNES
// Korrektur der letzten Aenderung
// 
//    Rev 1.1   08 Mar 1993 14:07:18   HANNES
// Segmentsplitting
// 
//    Rev 1.0   02 Dec 1992 15:31:28   HANNES
// Initial revision.
//

#include <windows.h>
#include <stdio.h>
#include <dos.h>
#include "dds32.h"
#include "globmem.h"
#include "hash.hpp"


/*-------------< Window's Speicherverwaltung >------------------*/
DLLExport LPVOID _export WINAPI hash::operator new (size_t size)
  {
  return GetGlobMem (size);
  }

DLLExport void _export WINAPI hash::operator delete (LPVOID obj)
  {
  FreeGlobMem (obj);
  }

/*-------< Vergleich von Schluessel mit dem Eintrag >--------*/
BOOL hash::compareKey (char FAR *str,LPhash_entry ent)
  {
  if (is_empty (ent)) return FALSE ;
  else                return (lstrcmp (ent->key.strkey,str) == 0);
  }

BOOL hash::compareKeyv (LPVOID key,LPhash_entry ent,int size)
  {
  if (is_empty (ent)) return FALSE ;
  else                return ((GetBlockSize(ent->key.vkey) == WORD(size)) && lmemcmp (ent->key.vkey,key,size));
  }

BOOL hash::compareKey (LONG ident,LPhash_entry ent)
  {
  if (is_empty (ent)) return FALSE ;
  else                return ent->key.lKey == ident;
  }

BOOL hash::compareKeyW (WORD ident,LPhash_entry ent)
  {
  if (is_empty (ent)) return FALSE ;
  else                return ident == ent->key.wKey;
  }

/*-----------< Suchen von Daten >-------------*/
LPVOID hash::GetData (LPSTR key)
  {
  WORD index = hash_index (key);

  for (LPhash_entry e = Table + index ; e != NULL ; ) {
    if (compareKey (key,e)) break ;
    e = NextEnt (e);
    }

  if (e != NULL) return DataPtr (e) ;
  else           return NULL ;
  }

DLLExport LPVOID _export WINAPI hash::GetDatav (LPVOID key,int size)
  {
  WORD index = hash_indexv (key,size);

  for (LPhash_entry e = Table + index ; e != NULL ; ) {
    if (compareKeyv (key,e,size)) break ;
    e = NextEnt (e);
    }

  if (e != NULL) return DataPtr (e) ;
  else           return NULL ;
  }

DLLExport LPVOID _export WINAPI hash::GetData (LONG key)
  {
  WORD index = hash_index (key);

  for (hash_entry FAR *e = Table + index ; e != NULL ; ) {
    if (compareKey (key,e)) break ;
    e = NextEnt (e);
    }

  if (e != NULL) return DataPtr (e);
  else           return NULL;
  }

static WORD _lastkey;
static LPVOID _lastres;
static hash FAR * _lasthash;
static LPVOID checkLast (WORD key,hash FAR *h)
  {
  if ((key == _lastkey) && (h == _lasthash)) {
    return _lastres;
    }
  return NULL;
  }

static void setlastres (WORD key,hash FAR *h,LPVOID res)
  {
  _lastkey = key;
  _lasthash = h;
  _lastres = res;
  }

static void invalidatelast ()
  {
  _lasthash = NULL;
  }

DLLExport LPVOID _export WINAPI hash::GetDataW (WORD key)
  {
  LPVOID res ;
//  if ((res = checkLast (key,this)) != NULL) return res;
  WORD index = hash_indexw (key);

  for (hash_entry FAR *e = Table + index ; e != NULL ; ) {
    if (compareKeyW (key,e)) break ;
    e = NextEnt (e);
    }
  if (e != NULL) res = DataPtr (e);
  else           res = NULL;
//  setlastres (key,this,res);
  return res;
  }

void hash::InitializeSpcEle (WORD key)
  {
  WORD index = hash_indexw (key);

  for (hash_entry FAR *e = Table + index ; e != NULL ; ) {
    if (compareKeyW (key,e)) break ;
    e = NextEnt (e);
    }

  if (e != NULL) SpcElement = e->Data;
  else           SpcElement = NULL;
  }

/*-----< Austauschen / Setzen von Daten >---------*/
DLLExport void _export WINAPI hash::ChangeDataW (WORD key,LPVOID data,int size)
  {
  WORD index = hash_indexw (key);

  for (LPhash_entry e = Table + index ; ; ) {
    if ((compareKeyW (key,e)) || (is_empty (e))) {
      e->key.wKey = key ;                // bei is_empty
      if (e->Data != NULL) 
        FreeGlobMem (e->Data);
      e->Data = GetGlobMem (size);
      e->wDataSize = size;
      lmemcpy (e->Data,data,size);
      break ;
      }
    if (e->Next == NULL) {
      // Daten existieren noch nicht
      e->Next = newent ();
      e = e->Next ;
      e->key.wKey = key;
      e->Next = NULL;
      e->Data = GetGlobMem (size);
      e->wDataSize = size;
      lmemcpy (e->Data,data,size);
      break ;
      }
    e = NextEnt (e);
    }

//  invalidatelast ();
  }               

/*------------< Daten in die hashtabelle einspeichern >----------*/
DLLExport BOOL _export WINAPI hash::SetData (LPSTR key,LPVOID Data,int size)
  {
  BOOL not_found = TRUE ;
  WORD index = hash_index (key);

  for (LPhash_entry e = Table + index ; ; ) {
    if (compareKey (key,e)) {
      not_found = FALSE ;
      break ;
      }
    else if (is_empty (e)) break ;
    else if (e->Next == NULL) {
      e->Next = newent ();
      e = e->Next ;
      break ;
      }
    e = NextEnt (e);
    }
  if (not_found) {
    SetKey (key,e);
    StoreData (Data,size,e);
    }
  return not_found ;
  }

DLLExport BOOL _export WINAPI hash::SetDatav (LPVOID key,LPVOID Data,int size,int keysize)
  {
  BOOL not_found = TRUE ;
  WORD index = hash_indexv (key,keysize);

  for (LPhash_entry e = Table + index ; ; ) {
    if (compareKeyv (key,e,keysize)) {
      not_found = FALSE ;
      break ;
      }
    else if (is_empty (e)) break ;
    else if (e->Next == NULL) {
      e->Next = newent ();
      e = e->Next ;
      break ;
      }
    e = NextEnt (e);
    }
  if (not_found) {
    SetKeyv (key,e,keysize);
    StoreData (Data,size,e);
    }
  return not_found ;
  }

DLLExport BOOL _export WINAPI hash::SetData (LONG key,void FAR *Data,int size)
  {
  BOOL not_found = TRUE ;
  WORD index = hash_index (key);
  for (LPhash_entry e = Table + index ; ; ) {
    if (compareKey (key,e)) {
      not_found = FALSE ;
      break ;
      }
    else if (is_empty (e)) break ;
    else if (e->Next == NULL) {
      e->Next = newent ();
      e = e->Next ;
      break ;
      }
    e = NextEnt (e);
    }
  if (not_found) {
    SetKey (key,e);
    StoreData (Data,size,e);
    }
  return not_found ;
  }

DLLExport BOOL _export WINAPI hash::SetDataW (WORD key,void FAR *Data,int size)
  {
  BOOL not_found = TRUE ;
  WORD index = hash_indexw (key);
  for (LPhash_entry e = Table + index ; ; ) {
    if (compareKeyW (key,e)) {
      not_found = FALSE ;
      break ;
      }
    else if (is_empty (e)) break ;
    else if (e->Next == NULL) {
      e->Next = newent ();
      e = e->Next;
      break ;
      }
    e = NextEnt (e);
    }
  if (not_found) {
    SetKeyW (key,e);
    StoreData (Data,size,e);
    }
//  invalidatelast ();
  return not_found ;
  }

/*------------< Loeschen von Daten aus der Hashtabelle >------------*/
DLLExport BOOL _export WINAPI hash::DelData (LPSTR key)
  {
  WORD index = hash_index (key);
  LPhash_entry prev = NULL ;
  BOOL found = FALSE ;
  for (LPhash_entry e = Table + index ; ; ) {
    if (compareKey (key,e)) {
      found = TRUE ;
      // Loeschen der Daten
      FreeGlobMem (e->Data);
      FreeGlobMem (e->key.strkey);
      // Loeschen des Knotens
      if (prev != NULL) {
        prev->Next = e->Next ;
        FreeGlobMem (e);
        }
      else if (e->Next) {
        // Nachfolger muss herein gezogen werden
        LPhash_entry n = NextEnt (e);
        lmemcpy (e,n,sizeof(hash_entry));
        FreeGlobMem (n);
        }
      else e->Data = NULL ;   // Leer setzen
      break ;
      }
    else if ((is_empty (e)) || (e->Next == NULL)) break ;
    prev = e ;
    e = NextEnt (e);
    }
  return found ;
  }

DLLExport BOOL _export WINAPI hash::DelDatav (LPVOID key,int size)
  {
  WORD index = hash_indexv (key,size);
  LPhash_entry prev = NULL ;
  BOOL found = FALSE ;
  for (LPhash_entry e = Table + index ; ; ) {
    if (compareKeyv (key,e,size)) {
      found = TRUE ;
      // Loeschen der Daten
      FreeGlobMem (e->Data);
      FreeGlobMem (e->key.vkey);
      // Loeschen des Knotens
      if (prev != NULL) {
        prev->Next = e->Next ;
        FreeGlobMem (e);
        }
      else if (e->Next) {
        // Nachfolger muss herein gezogen werden
        LPhash_entry n = NextEnt (e);
        lmemcpy (e,n,sizeof(hash_entry));
        FreeGlobMem (n);
        }
      else e->Data = NULL ;   // Leer setzen
      break ;
      }
    else if ((is_empty (e)) || (e->Next == NULL)) break ;
    prev = e ;
    e = NextEnt (e);
    }
  return found ;
  }

DLLExport BOOL _export WINAPI hash::DelData (LONG key)
  {
  WORD index = hash_index (key);
  LPhash_entry prev = NULL ;
  BOOL found = FALSE ;
  for (LPhash_entry e = Table + index ; ; ) {
    if (compareKey (key,e)) {
      found = TRUE ;
      // Loeschen der Daten
      FreeGlobMem (e->Data);
      // Loeschen des Knotens
      if (prev != NULL) {
        prev->Next = e->Next ;
        FreeGlobMem (e);
        }
      else if (e->Next) {
        // Nachfolger muss herein gezogen werden
        LPhash_entry n = NextEnt (e);
        lmemcpy (e,n,sizeof(hash_entry));
        FreeGlobMem (n);
        }
      else e->Data = NULL ;   // Leer setzen
      break ;
      }
    else if ((is_empty (e)) || (e->Next == 0)) break ;
    prev = e ;
    e = NextEnt (e);
    }
  return found ;
  }

DLLExport BOOL _export WINAPI hash::DelDataW (WORD key)
  {
  WORD index = hash_indexw (key);
  LPhash_entry prev = NULL ;
  BOOL found = FALSE ;
  for (LPhash_entry e = Table + index ; ; ) {
    if (compareKeyW (key,e)) {
      found = TRUE ;
      // Loeschen der Daten
      FreeGlobMem (e->Data);
      // Loeschen des Knotens
      if (prev != NULL) {
        prev->Next = e->Next ;
        FreeGlobMem (e);
        }
      else if (e->Next) {
        // Nachfolger muss herein gezogen werden
        LPhash_entry n = NextEnt (e);
        lmemcpy (e,n,sizeof(hash_entry));
        FreeGlobMem (n);
        }
      else e->Data = NULL ;   // Leer setzen
      break ;
      }
    else if ((is_empty (e)) || (e->Next == 0)) break ;
    prev = e ;
    e = NextEnt (e);
    }
  return found ;
  }

/*----------------< Konstruktor ... >----------------*/
DLLExport _export WINAPI hash::hash (WORD dimension,WORD key_type,GLOBALHANDLE hGm)
  {
  Type = int (key_type) ;
  // Anlegen der (Leer) Tabelle
  Table = LPhash_entry (GetGlobMem (
          (hash_dimension = dimension) * sizeof (hash_entry)
                                   )
                       );
  // Eventuelles Einordnen
  if (hGm) GetHash (hGm);
  }

DLLExport _export WINAPI hash::~hash ()
  {
  for (int i = 0 ; i < int (hash_dimension) ; i++) {
    BOOL first = TRUE ;
    for (LPhash_entry e = Table + i ; e != NULL ; ) {
      if (!is_empty (e)) {
        // Schluessel Speichern
        if (Type == STRKEY)
          FreeGlobMem (e->key.strkey);
        if (Type == VOIDKEY)
          FreeGlobMem (e->key.vkey);
        FreeGlobMem (e->Data);
        }
      LPhash_entry next = e->Next ;
      if (!first)
        FreeGlobMem (e);
      e = next;
      first = FALSE ;
      }
    }

  FreeGlobMem (Table);
  }

DLLExport void _export WINAPI PushDataToHandle (LPVOID data,int size,GLOBALHANDLE FAR *res)
  {
  LPSTR base = LPSTR(GlobalLock (*res));
  WORD ActSize = *((WORD FAR *)base);
  GlobalUnlock (*res);
  *res = GlobalReAlloc (*res,ActSize + size,GMEM_MOVEABLE);
  base = LPSTR(GlobalLock (*res));
  lmemcpy (base + ActSize,data,size);
  *((WORD FAR *) base) = ActSize + size;
  GlobalUnlock (*res);
  }

typedef char huge *HPSTR;
DLLExport void _export WINAPI PushDataToHugeHandle (DWORD FAR *ActSize,LPVOID data,int size,GLOBALHANDLE FAR *res)
  {
  *res = GlobalReAlloc (*res,*ActSize + DWORD(size),GMEM_MOVEABLE);
  HPSTR base = HPSTR(GlobalLock (*res));
  hmemcpy (base + *ActSize,data,size);
  GlobalUnlock (*res);
  *ActSize += DWORD(size);
  }

DLLExport void _export WINAPI PushDataToHandle (WORD Ident,LPVOID data,int size,GLOBALHANDLE FAR *res)
  {
  PushDataToHandle (&Ident,sizeof(WORD),res);
  PushDataToHandle (&size,sizeof(WORD),res);
  PushDataToHandle (data,size,res);
  LPSTR base = LPSTR(GlobalLock (*res));
  ((WORD FAR *) base)[1] += 1;    // Count erhoehen
  }

DLLExport void _export WINAPI PushDataToHandle (LPSTR str,GLOBALHANDLE FAR *res)
  {
  PushDataToHandle (str,lstrlen (str)+1,res);
  }

DLLExport GLOBALHANDLE _export WINAPI InitializeHandleForPush (void)
  {
  GLOBALHANDLE res = GlobalAlloc (GHND,sizeof (WORD) * 2);
  char FAR *base = LPSTR(GlobalLock (res));
  *((WORD FAR *) base) = 2 * sizeof (WORD);
  GlobalUnlock (res);
  return res ;
  }

DLLExport GLOBALHANDLE _export WINAPI hash::StoreHash()
  {
  GLOBALHANDLE res = InitializeHandleForPush ();
  WORD count = 0 ;
  for (int i = 0 ; i < int (hash_dimension) ; i++) {
    for (LPhash_entry e = Table + i ; e != NULL ; ) {
      if (!is_empty (e)) {
        // Schluessel Speichern
        switch (Type) {
          case LONGKEY :
            PushDataToHandle (&e->key.lKey,sizeof (LONG),&res);
            break ;
          case STRKEY :
            PushDataToHandle (e->key.strkey,&res);
            break ;
          case WORDKEY :
            PushDataToHandle (&e->key.wKey,sizeof (WORD),&res);
          }
        // Daten Speichern
        PushDataToHandle (&e->wDataSize,sizeof (WORD),&res);
        PushDataToHandle (e->Data,e->wDataSize,&res);
        count ++ ;
        }
      e = NextEnt (e);
      }
    }
  // Count eintragen
  LPSTR base = LPSTR(GlobalLock (res));
  ((WORD FAR *) base)[1] = count ;
  GlobalUnlock (res);
  return res ;
  }

DLLExport GLOBALHANDLE _export WINAPI hash::StoreHugeHash()
  {
  GLOBALHANDLE res = InitializeHandleForPush ();
  WORD count = 0 ;
  DWORD ActSize = 2 * sizeof(WORD);
  for (int i = 0 ; i < int (hash_dimension) ; i++) {
    for (LPhash_entry e = Table + i ; e != NULL ; ) {
      if (!is_empty (e)) {
        // Schluessel Speichern
        switch (Type) {
          case LONGKEY :
            PushDataToHugeHandle (&ActSize,&e->key.lKey,sizeof (LONG),&res);
            break ;
          case STRKEY :
            PushDataToHugeHandle (&ActSize,e->key.strkey,lstrlen(e->key.strkey)+1,&res);
            break ;
          case WORDKEY :
            PushDataToHugeHandle (&ActSize,&e->key.wKey,sizeof (WORD),&res);
            break ;
          case VOIDKEY :
            {
            WORD size = GetBlockSize (e->key.vkey);
            PushDataToHugeHandle (&ActSize,&size,sizeof(WORD),&res);
            PushDataToHugeHandle (&ActSize,e->key.vkey,size,&res);
            }
            break ;
          }
        // Daten Speichern
        PushDataToHugeHandle (&ActSize,&e->wDataSize,sizeof (WORD),&res);
        PushDataToHugeHandle (&ActSize,e->Data,e->wDataSize,&res);
        count ++ ;
        }
      e = NextEnt (e);
      }
    }
  // Count eintragen
  LPSTR base = LPSTR(GlobalLock (res));
  ((WORD FAR *) base)[1] = count ;
  GlobalUnlock (res);
  return res ;
  }

DLLExport void _export WINAPI hash::GetHash (GLOBALHANDLE hGm)
  {
  LPSTR base = LPSTR(GlobalLock (hGm));
  WORD count = ((WORD FAR *) base)[1];
  base += 2 * sizeof (WORD);
  for (int i = 0 ; i < int (count) ; i++) {
    int datasize ;
    switch (Type) {
      case LONGKEY :
        {
        datasize = * ((WORD FAR *) (base + sizeof (LONG))) ;
        LONG lKey = * ((LONG FAR *) base);
        SetData ((LONG) lKey,base+sizeof(LONG)+sizeof(WORD),datasize);
        base += sizeof (LONG) + sizeof (WORD) + datasize ;
        }
        break ;
      case STRKEY :
        {
        int keylen = lstrlen (base);
        datasize = * ((WORD FAR *) (base + keylen + 1)) ;
        SetData (base,base+keylen+1+sizeof (WORD),datasize);
        base += keylen + 1 + sizeof (WORD) + datasize ;
        }
        break ;
      case WORDKEY :
        datasize = * ((WORD FAR *) (base + sizeof (WORD))) ;
        WORD wKey = * ((WORD FAR *) base);
        SetDataW (wKey,base+sizeof(WORD)+sizeof(WORD),datasize);
        base += sizeof (WORD) + sizeof (WORD) + datasize ;
        break ;
      }
    }
  GlobalUnlock (hGm);
  }

static LPSTR tmpBuff;
static char tmpStrKey[256];

inline WORD wInfo (HPSTR h)
  {
  WORD res;
  hmemcpy (&res,h,sizeof(WORD));
  return res;
  }

inline LONG lInfo (HPSTR h)
  {
  LONG res;
  hmemcpy (&res,h,sizeof(LONG));
  return res;
  }

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

inline LPSTR GetStrKey (HPSTR k)
  {
  for (LPSTR h = tmpStrKey ; *k ; )
    *h++ = *k++ ;
  *h++ = '\0';
  return tmpStrKey ;
  }

DLLExport void _export WINAPI hash::GetHugeHash (GLOBALHANDLE hGm)
  {
  HPSTR base = HPSTR(GlobalLock (hGm));
  WORD count = ((WORD FAR *) base)[1];
  base += 2 * sizeof (WORD);
  for (int i = 0 ; i < int (count) ; i++) {
    WORD datasize,keysize ;
    switch (Type) {
      case LONGKEY :
        {
        datasize = wInfo (base + sizeof(LONG));
                // * ((WORD FAR *) (base + sizeof (LONG))) ;
        LONG lKey = lInfo (base);
                // * ((LONG FAR *) base);
        SetData ((LONG) lKey,GetTmpBuff (base+sizeof(LONG)+sizeof(WORD),datasize),
                                            datasize);
                // SetData ((LONG) lKey,base+sizeof(LONG)+sizeof(WORD),datasize);
        CleanTmpBuff ();
        base += sizeof (LONG) + sizeof (WORD) + datasize ;
        }
        break ;
      case STRKEY :
        {
        LPSTR key = GetStrKey (base);
        int keylen = lstrlen (key);
        datasize = wInfo (base + keylen + 1);
                // * ((WORD FAR *) (base + keylen + 1)) ;
        SetData (key,GetTmpBuff (base+keylen+1+sizeof(WORD),datasize),datasize);
                // SetData (base,base+keylen+1+sizeof (WORD),datasize);
        CleanTmpBuff ();
        base += keylen + 1 + sizeof (WORD) + datasize ;
        }
        break ;
      case WORDKEY :
        {
        datasize = wInfo (base + sizeof(WORD));
              // * ((WORD FAR *) (base + sizeof (WORD))) ;
        WORD wKey = wInfo (base);
              // * ((WORD FAR *) base);
        SetDataW (wKey,GetTmpBuff (base+sizeof(WORD)+sizeof(WORD),datasize),datasize);
              // SetDataW (wKey,base+sizeof(WORD)+sizeof(WORD),datasize);
        CleanTmpBuff ();
        base += sizeof (WORD) + sizeof (WORD) + datasize ;
        }
        break ;
      case VOIDKEY :
        keysize = wInfo (base);
        hmemcpy (tmpStrKey,base + sizeof(WORD),keysize);
        base += sizeof(WORD) + keysize ;
        datasize = wInfo (base) ;
        SetDatav (tmpStrKey,GetTmpBuff (base+sizeof(WORD),datasize),datasize,keysize);
        base += sizeof(WORD) + datasize ;
        break ;
      }
    }
  GlobalUnlock (hGm);
  }

DLLExport BOOL _export WINAPI hash::IsHashEmpty (void)
  {
  BOOL empty = TRUE ;
  for (int i = 0 ; i < int (hash_dimension) ; i++) {
    empty = is_empty (Table+i);
    if (!empty) break ;
    }
  return empty ;
  }

/*-------< Statistiken >-------------*/
void hash::GetHashInfo (int FAR *AnzEntrys,float FAR *ff,float FAR *fff,int FAR *MaxLen,int FAR *AnzEmpty)
  {
  *AnzEntrys = 0;
  *AnzEmpty = 0;
  *MaxLen = 0;
  int ActAnz;
  
  for (int i = 0 ; i < int (hash_dimension) ; i++) {
    BOOL first = TRUE ;
    ActAnz = 0;
    for (hash_entry FAR *e = Table + i ; e != NULL ; ) {
      if (!is_empty (e)) {
        (*AnzEntrys) ++ ;
        ActAnz ++;
        }
      else {
        if (first)
          (*AnzEmpty) ++ ;
        }
      e = NextEnt (e);
      first = FALSE ;
      }
    if (ActAnz > *MaxLen)
      *MaxLen = ActAnz ;
    }
  *ff = float (*AnzEntrys) / float (hash_dimension) ;
  if (*AnzEmpty < int (hash_dimension))
    *fff = *AnzEntrys / float (hash_dimension - *AnzEmpty);
  }

