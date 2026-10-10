#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#include "globmem.h"
#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#define MODULENUM 40
#include "winass.hpp"
#include "ddsmsg.h"
#include "hash.hpp"

#define STATISTICS
/*--------------------------------------------------*/
/*  Hashtabellen - Handling, damit das Loeschen von */
/*  Eintraegen beschleunigt wird                    */
/*--------------------------------------------------*/
#ifdef STATISTICS
static LONG AnzPushCmd;
static LONG ActCmdsInFifo;
static LONG MaxCmdsInFifo;
static LONG AnzUnionHistory;
static LONG AnzCycls;
static int MaxHistLevel;
static LONG AnzInserts,InsSteps;
static LONG RefFound;

void PushInsSteps (int Steps)
  {
  InsSteps += Steps;
  AnzInserts ++ ;
  }

void PushRefFound ()
  {
  RefFound ++ ;
  }

void PushCmd ()
  {
  AnzPushCmd ++;
  ActCmdsInFifo ++;
  if (ActCmdsInFifo > MaxCmdsInFifo)
    MaxCmdsInFifo = ActCmdsInFifo;
  }

void PushCycls ()
  {
  AnzCycls ++ ;
  }

void PopCmd ()
  {
  ActCmdsInFifo -- ;
  }

void SetHistLevel (int level)
  {
  if (level > MaxHistLevel)
    MaxHistLevel = level ;
  }

void PushUnion ()
  {
  AnzUnionHistory ++ ;
  }

DLLExport void _export WINAPI ShowFifoStat (HFILE fi)
  {
  char outtxt[128];
  wsprintf (outtxt,"\r\n\r\n FIFO - Statistik: \r\n-------------------\r\n");
  _lwrite (fi,outtxt,lstrlen(outtxt));
  wsprintf (outtxt,"  PutCommandFifo: %ld\r\n",AnzPushCmd);
  _lwrite (fi,outtxt,lstrlen(outtxt));
  wsprintf (outtxt,"  Max. aktive Commandos: %ld (CheckSum: %ld)\r\n",MaxCmdsInFifo,ActCmdsInFifo);
  _lwrite (fi,outtxt,lstrlen(outtxt));
  wsprintf (outtxt,"  UnionHistory: %ld\r\n",AnzUnionHistory);
  _lwrite (fi,outtxt,lstrlen(outtxt));
  wsprintf (outtxt,"  Max. History - level: %d\r\n",MaxHistLevel);
  _lwrite (fi,outtxt,lstrlen(outtxt));
  wsprintf (outtxt,"  Anzahl Zyklen: %d\r\n",AnzCycls);
  _lwrite (fi,outtxt,lstrlen(outtxt));
  int dstep;
  if (AnzInserts > 0)
    dstep = int ((InsSteps + AnzInserts / 2) / AnzInserts);
  else
    dstep = 0;
  wsprintf (outtxt,"  Anzahl Suchschritte: %ld durchschn. Suchzeit: %d\r\n",InsSteps,dstep);
  _lwrite (fi,outtxt,lstrlen(outtxt));
  wsprintf (outtxt,"  Anzahl Doppelreferenzen beim Einsortieren: %ld\r\n",RefFound);
  _lwrite (fi,outtxt,lstrlen(outtxt));
  }

#else

DLLExport void _export WINAPI ShowFifoStat (HFILE fi)
  {
  }

#endif

struct FAR CHList {
  CHList FAR *Next;
  LPCMDFIFO ent;

  void RemoveEnt (fifo FAR *h);
  BOOL RemoveEnt (fifo FAR *h,int eType,LPVOID eData);
  };

void CHList::RemoveEnt (fifo FAR *h)
  {
#ifdef STATISTICS
  PopCmd ();
#endif
  if (ent->Prev != NULL)
    ent->Prev->Next = ent->Next;
  else
    h->head = ent->Next ;
  if (ent->Next != NULL)
    ent->Next->Prev = ent->Prev;
  else
    h->tail = ent->Prev;

  FreeGlobMem (ent->counter);
  if (ent->ExtraData != NULL) FreeGlobMem (ent->ExtraData);
  for (int i = 0 ; i < ent->HistCount () ; i++) {
    if (ent->History[i].fk != NULL) 
      FreeGlobMem (ent->History[i].fk);
    }
  FreeGlobMem (ent);
  }

BOOL CHList::RemoveEnt (fifo FAR *h,int eType,LPVOID eData)
  {
  if ((ent->ExtraType == eType) && 
      (lmemcmp (ent->ExtraData,eData,GetBlockSize (ent->ExtraData)))) {
#ifdef STATISTICS
    PopCmd ();
#endif
    if (ent->Prev != NULL)
      ent->Prev->Next = ent->Next;
    else
      h->head = ent->Next ;
    if (ent->Next != NULL)
      ent->Next->Prev = ent->Prev;
    else
      h->tail = ent->Prev;

    FreeGlobMem (ent->counter);
    if (ent->ExtraData != NULL) FreeGlobMem (ent->ExtraData);
    for (int i = 0 ; i < ent->HistCount () ; i++) {
      if (ent->History[i].fk != NULL) 
        FreeGlobMem (ent->History[i].fk);
      }
    FreeGlobMem (ent);
    return TRUE ;
    }
  return FALSE ;
  }

#define HASHDIM 127
struct FAR CHKey {
  LPVOID Cmd;
  };

struct FAR CHEnt {
  CHKey k;
  CHList FAR *l;
  CHEnt FAR *Next;

  void RemoveList (fifo FAR *h);
  BOOL RemoveList (fifo FAR *h,int eType,LPVOID eData);
  BOOL RemoveListEntry (LPCMDFIFO x);
  void InsertListEntry (LPCMDFIFO x);

  BOOL Check (CHKey FAR *c)
    { return lmemcmp (&k,c,sizeof(k)) ; }
  };
typedef CHEnt FAR *LPCHENT;

void CHEnt::RemoveList (fifo FAR *h)
  {
  for ( ; l != NULL ; ) {
    CHList FAR *n = l->Next ;
    l->RemoveEnt (h);
    FreeGlobMem (l);
    l = n ;
    }
  }

BOOL CHEnt::RemoveList (fifo FAR *h,int eType,LPVOID eData)
  {
  CHList FAR *p = NULL ;
  for ( CHList FAR *x = l ; x != NULL ; ) {
    CHList FAR *n = x->Next ;
    if (x->RemoveEnt (h,eType,eData)) {
      FreeGlobMem (x);
      if (p != NULL) p->Next = n ;
      else           l = n ;
      }
    else
      p = x ;     // Alte Version: p = l ;
    x = n ;
    }
  return (l == NULL) ;
  }

BOOL CHEnt::RemoveListEntry (LPCMDFIFO x)
  {
  CHList FAR *h = l ;
  CHList FAR *prev = NULL ;
  for ( ; h != NULL ; ) {
    if (x == h->ent) {
      CHList FAR *next = h->Next ;
      if (prev != NULL)
        prev->Next = h->Next ;
      else
        l = h->Next ;
      FreeGlobMem (h);
      break ;
      }
    else {
      prev = h ;
      h = h->Next ;
      }
    }
  // return (h == NULL); !!!???!!!
  return (l == NULL);
  }

void CHEnt::InsertListEntry (LPCMDFIFO x)
  {
  CHList FAR *h = (CHList FAR *)GetGlobMem (sizeof(*h));
  h->Next = l ;
  h->ent = x ;
  l = h ;
  }

class FAR CmdHash {
 public :
  CHEnt FAR *ent[HASHDIM];
  fifo FAR *f;

  int Index (CHKey FAR *c)
    { WORD r = 0 ; 
      LPINT h = LPINT (c) ;
      for (int i = 0 ; i < sizeof(*c)/sizeof(*h) ; i++) r += *h++ ;
      return r % HASHDIM ;
    }
  void RemoveEntList (CHKey FAR *c);
  void RemoveEntList (CHKey FAR *c,int eType,LPVOID eData);
  void RemoveEnt (CHKey FAR *c,LPCMDFIFO x);
  void InsertEnt (CHKey FAR *c,LPCMDFIFO x);
  };

void CmdHash::RemoveEntList (CHKey FAR *c)
  {
  LPCHENT FAR *p = &ent[Index(c)];
  CHEnt FAR *e = *p;
  for ( ; e != NULL ; ) {
    if (e->Check(c)) {
      e->RemoveList (f);
      *p = e->Next ;
      FreeGlobMem (e);
      }
    else
      p = &e->Next;
    e = *p;
    }
  }

void CmdHash::RemoveEntList (CHKey FAR *c,int eType,LPVOID eData)
  {
  LPCHENT FAR *p = &ent[Index(c)];
  CHEnt FAR *e = *p;
  for ( ; e != NULL ; ) {
    if ((e->Check(c)) && (e->RemoveList (f,eType,eData))) {
      *p = e->Next ;
      FreeGlobMem (e);
      }
    else
      p = &e->Next;
    e = *p;
    }
  }

void CmdHash::RemoveEnt (CHKey FAR *c,LPCMDFIFO x)
  {
  LPCHENT FAR *p = &ent[Index(c)];
  CHEnt FAR *e = *p;
  for ( ; e != NULL ; ) {
    if (e->Check(c)) {
      if (e->RemoveListEntry (x)) {
        *p = e->Next ;
        FreeGlobMem (e);
        break ;
        }
      }
    p = &e->Next;
    e = *p;
    }
  }

void CmdHash::InsertEnt (CHKey FAR *c,LPCMDFIFO x)
  {
  LPCHENT FAR *p = &ent[Index(c)];
  for ( ; ((*p != NULL) && !(*p)->Check(c)) ; p = &(*p)->Next ) ;
  if (*p == NULL) {
    *p = LPCHENT (GetGlobMem (sizeof (**p)));
    (*p)->k = *c;
    }
  (*p)->InsertListEntry (x);
  }

CmdHash c1,c2;
void BindCmdHash (LPVOID f1,LPVOID f2)
  {
  ((fifo FAR *) f1)->cHash = &c1;
  ((fifo FAR *) f2)->cHash = &c2;
  c1.f = (fifo FAR *) f1;
  c2.f = (fifo FAR *) f2;
  }


// #define MAXHANDLES  30
// static int AnzDestroyedDocuments;
// static DWORD destroyedDocuments[MAXHANDLES];

static hash FAR *destroyedDocs;

DLLExport void _export WINAPI NoFurtherUpdates(DWORD DocumentID)
  {
  if (destroyedDocs == NULL) destroyedDocs = new hash (57,LONGKEY);
  BOOL done = TRUE ;
  destroyedDocs->SetData (DocumentID,&done,sizeof(BOOL));
  // BOOL found = FALSE ;
  // for (int i = 0 ; i < AnzDestroyedDocuments ; i++) {
  //   if (destroyedDocuments[i] == DocumentID) {
  //     found = TRUE ;
  //     break ;
  //     }
  //   }
  // if (!found) {
  //   WIN_ASSERT (AnzDestroyedDocuments < MAXHANDLES - 1);
  //   destroyedDocuments[AnzDestroyedDocuments++] = DocumentID;
  //   }
  }

DLLExport void _export WINAPI DocumentIsDestroyed(DWORD DocumentID)
  {
  if (destroyedDocs == NULL) destroyedDocs = new hash (57,LONGKEY);
  destroyedDocs->DelData (DocumentID);
//  BOOL found = FALSE ;
//  for (int i = 0 ; i < AnzDestroyedDocuments ; i++) {
//    if (found)
//      destroyedDocuments[i-1] = destroyedDocuments[i];
//    found = found || (destroyedDocuments[i] == DocumentID);
//    }
//  if (found)
//    AnzDestroyedDocuments -= 1;
  }

void ResetCmdFifo ()
  {
  if (destroyedDocs != NULL)
    delete destroyedDocs;
  }

static BOOL IsUpdateAllowed(DWORD DocumentID)
  {
  if (destroyedDocs == NULL) destroyedDocs = new hash (57,LONGKEY);
  return (destroyedDocs->GetData (DocumentID) == NULL);
//  for (int i = 0 ; i < AnzDestroyedDocuments ; i++) {
//    if (destroyedDocuments[i] == DocumentID)
//      return FALSE ;
//    }
//  return TRUE ;
  }

static int _gfcount;
static fifo FAR *GotFrom [10];

static void PushFifo(fifo FAR *f)
  {
//  GotFrom[_gfcount++] = f;
  }

static void PopFifo()
  {
//  _gfcount -- ;
  }

static fifo async_fifo,sync_fifo;
static fifo FAR *TopFifo ()
  {
  return &async_fifo ;
  }

#define MAXKEYS   128
static struct KBUFFER {
  int AnzKeys;
  LPVARELEM k[MAXKEYS];
  void prep_pushKey ()
    { AnzKeys = 0; }
  void pushKey (LPVARELEM n)
    {
    for (int i = 0 ; i < AnzKeys ; i++)
      if (k[i] == n) break ;
    if (i >= AnzKeys) {
      WIN_ASSERT (i < MAXKEYS);
      k[i] = n ;
      AnzKeys ++ ;
      }
    }
  LPVARELEM FAR *getBuffer ()
    {
    if (AnzKeys > 0) {
      LPVARELEM FAR *res = (LPVARELEM FAR *) GetGlobMem (AnzKeys * sizeof(LPVARELEM));
      lmemcpy (res,k,AnzKeys * sizeof(LPVARELEM));
      return res;
      }
    else
      return NULL;
    }
  } kbuffer;

extern LPSTR WINAPI GetIniName();
BOOL UseHistory ()
  {
  static BOOL uh;
  static BOOL done;
  if (!done) {
    char name[64];
    GetPrivateProfileString ("Tools","History","no",
                          name,64,
                          GetIniName());
    uh = (lstrcmp (name,"yes") == 0);
    done = TRUE ;
    }
  return uh;
  }

HistEle FAR *UnionHistory (HistEle FAR *e1,int c1,HistEle FAR *e2,int c2,int FAR *ganz)
  {
#ifdef STATISTICS
  PushUnion ();
#endif

  if (!UseHistory()) {
    HistEle FAR *res = (HistEle FAR *) GetGlobMem (sizeof(*res));
    *ganz = 1;
    res->CopyEntry (&e1[0]);
    return res;
    }
  static int MAX_RBUFFER = 0;
  static HistEle FAR *rbuffer;
  if (!MAX_RBUFFER) {
    MAX_RBUFFER = 32767 / sizeof(HistEle);
    GLOBALHANDLE hrbuffer = GlobalAlloc(GHND,MAX_RBUFFER * sizeof(HistEle));
    rbuffer = (HistEle FAR *)GlobalLock(hrbuffer);
    // freigeben soll gefaelligst Windows ...
    }

  if (c2 > c1) {
    // Austauschen der Beiden zeiger, damit die groessere Variable
    // geiteilt werden kann
    ///////////////////////////////////////////////////////////////
    HistEle FAR *edummy = e1 ;
    e1 = e2 ;
    e2 = edummy;
    int idummy = c1 ;
    c1 = c2 ;
    c2 = idummy;
    }
  WIN_ASSERT (c1 < MAX_RBUFFER);
  lmemcpy (rbuffer,e1,c1 * sizeof (HistEle));
  for (int i = 0 ; i < c1 ; i++)
    rbuffer[i].CopyEntry (&e1[i]);
  *ganz = c1;
  for (i = 0 ; i < c2 ; i++) {
    BOOL found = FALSE ;
    for (int j = 0 ; j < c1 ; j++) {
      if ((e2[i].cmd == rbuffer[j].cmd)) {
        // Gefunden -> UpdateEles vereinigen
        kbuffer.prep_pushKey ();
        int kmax = e2[i].AnzKeys () ;
        for (int k = 0 ; k < kmax ; k++)
          kbuffer.pushKey (e2[i].fk[k]);
        kmax = rbuffer[j].AnzKeys () ;
        for (k = 0 ; k < kmax ; k++)
          kbuffer.pushKey (rbuffer[j].fk[k]);
        if (rbuffer[j].fk != NULL) FreeGlobMem (rbuffer[j].fk);
        rbuffer[j].fk = kbuffer.getBuffer();
        break ;
        }
      }
    if (j >= c1) {
      // Nicht gefunden -> ganz neuen Eintrag erzeugen
      rbuffer[*ganz] = e2[i];
      rbuffer[*ganz].CopyEntry (&e2[i]);
      (*ganz) ++ ;
      WIN_ASSERT (*ganz < MAX_RBUFFER);
      }
    }
  HistEle FAR *res = (HistEle FAR *) GetGlobMem (*ganz * sizeof (*res));
  lmemcpy (res,rbuffer,*ganz * sizeof (*res));
#ifdef STATISTICS
  SetHistLevel (*ganz);
#endif
  return res;
  }

#define VONVORNE
void fifo::Insert (LPCMDFIFO h)
  {
  if (head != NULL) {
#ifdef STATISTICS
    int Steps = 0;
#endif
#ifdef VONVORNE
    for (LPCMDFIFO x = head ; x != NULL ; x = x->Next) {
      if (Compare (h->counter,x->counter) <= 0) {
        // h gehoert vor x einsortiert (h <= x)
        if ((h->Cmd == x->Cmd) &&
            (((h->ExtraData == NULL) && (x->ExtraData == NULL)) ||
             ((GetBlockSize(h->ExtraData) == GetBlockSize(x->ExtraData)) &&
              (lmemcmp (h->ExtraData,x->ExtraData,GetBlockSize(h->ExtraData))))
            )
           ) {
#ifdef STATISTICS
          PushRefFound ();
#endif
          // h und x sind die gleichen -> Zusammenbinden
          int gcount;
          HistEle FAR *hn = UnionHistory (h->History,h->HistCount(),x->History,x->HistCount(),&gcount);
          LPCMDFIFO n = LPCMDFIFO (GetGlobMem 
              (sizeof(*h) - sizeof (HistEle) + gcount * sizeof(HistEle))
                                  );
          lmemcpy (n,h,sizeof (*h) - sizeof(HistEle));
          lmemcpy (&(n->History[0]),hn,gcount * sizeof(HistEle));
          FreeGlobMem (hn);
          n->counter = h->counter->Copy ();
          // Zeiger wieder richtig stellen
          n->Next = x->Next;
          n->Prev = x->Prev;
          if (x->Prev != NULL)
            x->Prev->Next = n;
          else
            head = n;
          if (x->Next != NULL)
            x->Next->Prev = n;
          else
            tail = n;

          // Freigabe von x
          FreeGlobMem (x->counter);
          if (x->ExtraData != NULL) FreeGlobMem (x->ExtraData);
          for (int i = 0 ; i < x->HistCount () ; i++) {
            if (x->History[i].fk != NULL) 
              FreeGlobMem (x->History[i].fk);
              }
          CHKey c;
          c.Cmd = x->Cmd;
          // Austausch von x und h
          ((CmdHash *) cHash)->RemoveEnt (&c,x);
#ifdef STATISTICS
          PopCmd ();
#endif
          FreeGlobMem (x);

          // Freigabe von h
          FreeGlobMem (h->counter);
          for (i = 0 ; i < h->HistCount () ; i++) {
            if (h->History[i].fk != NULL) 
              FreeGlobMem (h->History[i].fk);
            }
          FreeGlobMem (h);

          h = n;      // Das richtige hinten in der Hashtabelle einfuegen
          }
        else {
          h->Next = x ;
          h->Prev = x->Prev;
          if (x->Prev != NULL)
            x->Prev->Next = h;
          else
            head = h;
          x->Prev = h;
          }
        break ;
        }
#ifdef STATISTICS
      Steps++;
#endif
      }
    if (x == NULL) {
      // Nichts gefunden -> hinten einfuegen
      tail->Next = h;   // tail muss existieren, da head existiert
      h->Prev = tail;
      h->Next = NULL;
      tail = h;
      }
#else
    for (LPCMDFIFO x = tail ; x != NULL ; x = x->Prev) {
      if (Compare (h->counter,x->counter) >= 0) {
        // h gehoert hinter x einsortiert (h >= x)
        if ((h->Cmd == x->Cmd) &&
            (((h->ExtraData == NULL) && (x->ExtraData == NULL)) ||
             ((GetBlockSize(h->ExtraData) == GetBlockSize(x->ExtraData)) &&
              (lmemcmp (h->ExtraData,x->ExtraData,GetBlockSize(h->ExtraData))))
            )
           ) {
#ifdef STATISTICS
          PushRefFound ();
#endif
          // h und x sind die gleichen -> Zusammenbinden
          int gcount;
          HistEle FAR *hn = UnionHistory (h->History,h->HistCount(),x->History,x->HistCount(),&gcount);
          LPCMDFIFO n = LPCMDFIFO (GetGlobMem 
              (sizeof(*h) - sizeof (HistEle) + gcount * sizeof(HistEle))
                                  );
          lmemcpy (n,h,sizeof (*h) - sizeof(HistEle));
          lmemcpy (&(n->History[0]),hn,gcount * sizeof(HistEle));
          FreeGlobMem (hn);
          n->counter = h->counter->Copy ();
          // Zeiger wieder richtig stellen
          n->Next = x->Next;
          n->Prev = x->Prev;
          if (x->Prev != NULL)
            x->Prev->Next = n;
          else
            head = n;
          if (x->Next != NULL)
            x->Next->Prev = n;
          else
            tail = n;

          // Freigabe von x
          FreeGlobMem (x->counter);
          if (x->ExtraData != NULL) FreeGlobMem (x->ExtraData);
          for (int i = 0 ; i < x->HistCount () ; i++) {
            if (x->History[i].fk != NULL) 
              FreeGlobMem (x->History[i].fk);
              }
          CHKey c;
          c.Cmd = x->Cmd;
          // Austausch von x und h
          ((CmdHash *) cHash)->RemoveEnt (&c,x);
#ifdef STATISTICS
          PopCmd ();
#endif
          FreeGlobMem (x);

          // Freigabe von h
          FreeGlobMem (h->counter);
          for (i = 0 ; i < h->HistCount () ; i++) {
            if (h->History[i].fk != NULL) 
              FreeGlobMem (h->History[i].fk);
            }
          FreeGlobMem (h);

          h = n;      // Das richtige hinten in der Hashtabelle einfuegen
          }
        else {
          h->Prev = x ;
          h->Next = x->Next;
          if (x->Next != NULL)
            x->Next->Prev = h;
          else
            tail = h;
          x->Next = h;
          }
        break ;
        }
#ifdef STATISTICS
      Steps++;
#endif
      }
    if (x == NULL) {
      // Nichts gefunden -> vorne einfuegen
      head->Prev = h;   // head muss existieren, da head existiert
      h->Next = head;
      h->Prev = NULL;
      head = h;
      }
#endif
#ifdef STATISTICS
    PushInsSteps (Steps);
#endif
    }
  else {
    // Noch nichts drinnen
    head = tail = h;
    h->Next = h->Prev = NULL;
    }
  CHKey c;
  c.Cmd = h->Cmd;
  ((CmdHash *) cHash)->InsertEnt (&c,h);
#ifdef STATISTICS
  PushCmd ();
#endif
  }

BOOL HistEle::EleReferenced (LPVARELEM k)
  {
  if ((k != NULL) && (fk != NULL)) {
    int AnzEles = GetBlockSize (fk) / sizeof (*fk);
    BOOL found = FALSE ;
    for (int i = 0 ; ((i < AnzEles) && (!found)) ; i++) {
      found = found || (fk[i] == k);
      }
    return found ;
    }
  else return FALSE ;
  }

void HistEle::CopyEntry (LPVARELEM k)
  {
  if (k != NULL) {
    fk = (LPVARELEM FAR *) GetGlobMem (sizeof (k));
    fk[0] = k ;
    }
  else {
    fk = NULL ;
    }
  }

void HistEle::CopyEntry (HistEle FAR *h)
  {
  if (h->fk != NULL) {
    fk = (LPVARELEM FAR *) GetGlobMem (GetBlockSize (h->fk));
    lmemcpy (fk,h->fk,GetBlockSize(fk));
    }
  else {
    fk = NULL ;
    }
  }

void HistEle::CopyEntry (HistEle FAR *h,LPVARELEM k)
  {
  int size = 0;
  int o1 = 0;
  if (h->fk != NULL) size += (o1 = GetBlockSize (h->fk));
  if (k != NULL)     size += sizeof(k);
  if (size != NULL) {
    fk = (LPVARELEM FAR *) GetGlobMem (size);
    if (h->fk != NULL) lmemcpy (fk,h->fk,o1);
    if (k != NULL)     lmemcpy (LPSTR(fk)+o1,&k,sizeof(k));
    }
  else {
    fk = NULL ;
    }
  }

static HWND FrameWin;
EXTCHKMSG ExtChkMsg;
static BOOL BindCmdHash_done = FALSE ;
DLLExport void _export WINAPI SetupQueue (HWND hWnd,EXTCHKMSG ext)
  {
  FrameWin  = hWnd;
  ExtChkMsg = ext;
  if (!BindCmdHash_done) {
    BindCmdHash (GetAsync_cmdfifo(),GetSync_cmdfifo()) ;
    BindCmdHash_done = TRUE ;
    }
  }

static BOOL MsgInQueue;
void SetMsgToQueue ()
  {
  MSG msg;
  if (!MsgInQueue)
    // Ueberpruefen, obs wirklich stimmt
    MsgInQueue = PeekMessage (&msg,NULL,WMU_CALLCOMMAND,WMU_CALLCOMMAND,
                                  PM_NOREMOVE | PM_NOYIELD
                              );
  if (!MsgInQueue) {
    int st = PostMessage (FrameWin,WMU_CALLCOMMAND,0,0L);
    if (!st) {
      // Queu wahrscheinlich schon voll
      GetMessage (&msg,NULL,0,0);
      st = PostMessage (FrameWin,WMU_CALLCOMMAND,0,0L);
      (* ExtChkMsg) (&msg);
      }
    if (!st)
      FatalAppExit (0,"UPDATESYSTEM!!!");
    MsgInQueue = TRUE ;
    }
  }

DLLExport void _export WINAPI fifo::PutCommandFifo (DWORD DocumentID,WORD mode,
                      LPVOID Cmd,
                      LPVOID MyCmd,LPVARELEM updateEle,LPCMDCOUNT cnt,
                      int ExtraType,LPVOID ExtraData,int ExtraSize
                                             )
  {
  // Ueberpruefen, ob ueberhaupt hineingestellt werden darf
  BOOL doIt = ((Cmd != MyCmd) && (IsUpdateAllowed(DocumentID))) ;
  int extracount;
  if ((act != NULL) && (updateEle != NULL) && (doIt))
    extracount = act->HistCount ();
  else
    extracount = 0;
  if (doIt) {
    LPCMDFIFO h;
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    if ((!UseHistory()) && (extracount > 1))
      extracount = 1 ;

    h = LPCMDFIFO(GetGlobMem (sizeof(*h) + extracount * sizeof(HistEle)));
      
    h->Next       = NULL ;
    h->DocumentID = DocumentID;
    h->mode       = mode ;
    h->Cmd        = Cmd ;
    if (ExtraData != NULL) {
      h->ExtraType = ExtraType;
      h->ExtraData = GetGlobMem (ExtraSize);
      lmemcpy (h->ExtraData,ExtraData,ExtraSize);
      }
    if (updateEle != NULL) {
      h->History[0].cmd = MyCmd ;
      h->History[0].CopyEntry (updateEle);
      for (int i = 0 ; i < extracount ; i++) {
        h->History[i+1] = act->History[i];
        h->History[i+1].CopyEntry (&act->History[i]);
        }
      }
    else {
      for (int i = 0 ; i < extracount ; i++) {
        h->History[i] = act->History[i];
        h->History[i].CopyEntry (&act->History[i]);
        }
      }
#ifdef STATISTICS
    SetHistLevel (extracount);
#endif

    // Noch einsortieren
    h->counter = cnt->Copy ();
    Insert (h);
    }
  else {
    int i = 0;
#ifdef STATISTICS
    PushCycls ();
#endif
    }
  SetMsgToQueue ();
  }

LPCMDFIFO fifo::GetCmdFifo ()
  {
  LPCMDFIFO res = head;
  if (head != NULL)
    head = head->Next ;
  act = res;
  if (head != NULL) 
    head->Prev = NULL ;
  else
    tail = NULL ;
  if (res != NULL) {
    CHKey c;
    c.Cmd = res->Cmd;
    ((CmdHash *) cHash)->RemoveEnt (&c,res);
    }
#ifdef STATISTICS
  if (res != NULL)
    PopCmd ();
#endif
  return res;
  }

DLLExport LPCMDFIFO _export WINAPI fifo::GetCommandFifo ()
  {
  MsgInQueue = FALSE ;
  LPCMDFIFO h = GetCmdFifo ();
  if (h != NULL) {
    PushFifo(this);
    return h ;
    }
  else return NULL ;
  }

#ifdef DOPROFILE
static LONG AnzRemoved = 0;
static LONG MaxLen     = 0;
static LONG GesLen     = 0;

int Len (LPCMDFIFO h)
  {
  int l = 0 ;
  LPCMDFIFO beg = h ;
  for ( ; h != NULL ; h = h->Next )
    l ++ ;
  return l;
  }
#endif

DLLExport void _export WINAPI fifo::DelCommandFifoEntry (DWORD DocumentID,LPVOID Cmd) 
  {
#ifdef DOPROFILE
  AnzRemoved += 1 ;
  int ActLen = Len (head);
  if (ActLen > MaxLen) MaxLen = ActLen;
  GesLen += ActLen;
#endif

  if (head != NULL) {
    CHKey c;
    c.Cmd = Cmd;
    ((CmdHash *) cHash)->RemoveEntList (&c);
    }
  }

DLLExport void _export WINAPI fifo::DelCommandFifoEntry (DWORD DocumentID,LPVOID Cmd,int eType,LPVOID eData) 
  {
  if (head != NULL) {
    CHKey c;
    c.Cmd = Cmd;
    ((CmdHash *) cHash)->RemoveEntList (&c,eType,eData);
    }
  }

#ifdef DOPROFILE
DLLExport void _export WINAPI LogMsg (int modnum,int line,LPSTR txt);
void ShowStatistics ()
  {
  char outstr[128];
  LONG Avg = (AnzRemoved > 0) ? GesLen / AnzRemoved : 0 ;
  wsprintf (outstr,"DelCommandFifoEntry: Anz: %ld, Max: %ld, Avg: %ld",AnzRemoved,MaxLen,Avg);
  LogMsg (-1,-1,outstr);
  }
#else
void ShowStatistics ()
  {
  }
#endif

DLLExport void _export WINAPI fifo::DelDocumentEntrys (DWORD DocumentID)
  {
  LPCMDFIFO prev = NULL;
  for (LPCMDFIFO h = head ; h != NULL ; ) {
    if (h->DocumentID == DocumentID) {
      // Command muss geloescht werden
      // Verkettung, head und tail richtig stellen
      if (h->Prev != NULL)
        h->Prev->Next = h->Next;
      else
        head = h->Next;
      if (h->Next != NULL)
        h->Next->Prev = h->Prev;
      else
        tail = h->Prev;

      // Speicher noch freigeben
      LPCMDFIFO next = h->Next;
      FreeGlobMem (h->counter);
      if (h->ExtraData != NULL) FreeGlobMem (h->ExtraData);
      for (int i = 0 ; i < h->HistCount () ; i++) {
        if (h->History[i].fk != NULL) 
          FreeGlobMem (h->History[i].fk);
        }
      CHKey c;
      c.Cmd = h->Cmd;
      ((CmdHash *) cHash)->RemoveEnt (&c,h);
      FreeGlobMem (h);

      h = next ;
      }
    else
      h = h->Next ;
    }
  }

DLLExport BOOL _export WINAPI fifo::IsCommandFifoEmpty ()
  {
  return (head == NULL);
  }

DLLExport void _export WINAPI fifo::FreeFifoEntry (LPCMDFIFO h)
  {
  if (h->ExtraData != NULL) FreeGlobMem (h->ExtraData);
  FreeGlobMem (h->counter);
  for (int i = 0 ; i < h->HistCount () ; i++) {
    if (h->History[i].fk != NULL) 
      FreeGlobMem (h->History[i].fk);
    }
  FreeGlobMem (h);
  act = NULL;
  PopFifo();
  }

BOOL fifo::IsUpdateFrom (LPVARELEM key)
  {
  BOOL res ;
  if (act != NULL) {
    res = FALSE ;
    for (int i = 0 ; ((i < act->HistCount ()) && (!res)) ; i++) {
      for (int j = 0 ; ((j < act->History[i].AnzKeys()) && (!res)) ; j++) {
        res = (key == act->History[i].fk[j]) ;
        }
      if (j == 0) res = TRUE ;
      }
    }
  else res = TRUE ;
  return res;
  }

int fifo::UpdateEleCount ()
  {
  if (act != NULL) {
    kbuffer.prep_pushKey ();
    for (int i = 0 ; i < act->HistCount () ; i++) {
      int jmax = act->History[i].AnzKeys() ;
      for (int j = 0 ; j < jmax ; j++)
        kbuffer.pushKey (act->History[i].fk[j]);
      }
    LPVARELEM FAR *res = kbuffer.getBuffer();
    int Anz ;
    if (res != NULL) {
      Anz = GetBlockSize (res) / sizeof (*res);
      FreeGlobMem (res);
      }
    else
      Anz = 0;
    return Anz ;
    }
  else
    return 0;
  }

DLLExport BOOL _export WINAPI IsUpdateFrom (LPVARELEM key)
  {
  fifo *h = TopFifo ();
  return (h != NULL) ? h->IsUpdateFrom (key) : TRUE ;
  }

DLLExport int _export WINAPI UpdateEleCount ()
  {
  fifo *h = TopFifo ();
  return (h != NULL) ? h->UpdateEleCount () : 0 ;
  }

DLLExport LPVOID _export WINAPI GetUpdateExtraData (int FAR *ExtraType)
  {
  fifo *h = TopFifo ();
  if ((h != NULL) && (h->act != NULL)) {
    if (ExtraType != NULL)
      *ExtraType = h->act->ExtraType ;
    return h->act->ExtraData ;
    }
  else
    return NULL;
  }

DLLExport void _export WINAPI PushUpdateExtraData()
  {
  PushFifo (NULL);
  }

DLLExport void _export WINAPI PopUpdateExtraData()
  {
  PopFifo ();
  }

DLLExport fifo FAR *_export WINAPI GetAsync_cmdfifo()
  {
  return &async_fifo;
  }
DLLExport fifo FAR *_export WINAPI GetSync_cmdfifo()
  {
  return &sync_fifo;
  }

/*--------------< Erweiterungen fuer Debugger >------------------*/
LPCMDFIFO fifo::GetCmdFifoByNumber (int Nmbr)
  {
  if (Nmbr == -1) return act;
  int i = 0 ;
  for (LPCMDFIFO res = head; ((res != NULL) && (i < Nmbr)) ; i ++ , res = res->Next) ;
  return res;
  }

