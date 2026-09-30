/////////////////////////////////////////////////////////////////
//  Verwaltung von Prozeduren, die Dupliziert werden sollen
/////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/include/rev/multipro.hpv   1.7   21 Apr 1997 20:45:36   Hannes  $
//  $Log:   P:/marille/clinicum/include/rev/multipro.hpv  $
// 
//    Rev 1.7   21 Apr 1997 20:45:36   Hannes
// Abfrage der echten - Multiporc Adresse
// 
//    Rev 1.6   28 Feb 1997 14:47:20   Hannes
// Hashtabellen in Multipro
// 
//    Rev 1.5   19 Feb 1997 12:02:12   Hannes
// Mehrfachinkludierung verhindert
// 
//    Rev 1.4   02 Feb 1996 11:01:10   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.3   14 Jun 1995 13:04:04   HANNES
// ExpPtr ep in ProcPtr
// 
//    Rev 1.2   05 Dec 1994 17:37:06   HANNES
// Endgueltiger Einbau der Expressions
// 
//    Rev 1.1   24 Aug 1994 19:45:20   HANNES
// Erweiterung auf Multiprozedurfaehigkeit
// 
//    Rev 1.0   05 Aug 1994 17:17:36   HANNES
// Initial revision.
// 

struct ProcEntry ;
typedef ProcEntry FAR *LPPROCENT;
struct FAR ProcEntry {
  LPPROCENT Next;
  LPPROCENT Prev;
  LPPRIMKEY key;
  LPEXPPTR  ep;
  void RemoveExpressions ()
    {
    for ( ; ep != NULL ; ) {
      LPEXPPTR n = ep->Next;
      ep->v.FreeMem();
      FreeGlobMem (ep);
      ep = n;
      }
    }
  };

struct FAR ProcInfo {
  int Typ;
  DWORD ProcPtr;
  };
class FAR MultiProc {
 private :
  int AnzTypes;
  ProcInfo FAR *pinfo;
  mdiChild *c;
#ifdef VOIDKEY
  hash FAR *kHash;
#else
  LPVOID kHash;
#endif

  LPPROCENT head;
  LPPROCENT tail;

  DWORD ProcPtr (int typ);
  int ProcSize (int typ);
  int EntSize (int typ);
 public :
  MultiProc (mdiChild *m,DWORD p,BOOL useHash = FALSE);
  MultiProc (mdiChild *m,int FAR *t,DWORD FAR *p,int Anz);
  char huge *TailProc ()
    {
    return (char huge *) (tail + 1);
    }
    
  ~MultiProc ();

  void AddProc (LPPRIMKEY k,int type = 0);
  void AddProcAtHead (int type = 0);
  void AddProcAtTail (int type = 0);

  BOOL ExCute (LPPRIMKEY k,WORD mode,SetExtraInfo *x);
  BOOL ExCuteLast (WORD mode,SetExtraInfo *x);
  BOOL ExCuteFirst (WORD mode,SetExtraInfo *x);

  BOOL Remove (LPPRIMKEY k);
  BOOL RemoveFirst ();
  BOOL RemoveLast ();
  void RemoveAll ();

  LPVOID operator new (size_t s)
    { return GetGlobMem (s); }
  void operator delete (LPVOID obj)
    { FreeGlobMem (obj) ; }

  DWORD CorrOffs(int type = 0)
    { return ProcPtr(type); }
  friend LPEXPPTR FAR *GetExpNode (LPVOID Cmd);
  };

inline LPEXPPTR FAR *GetExpNode (LPVOID Cmd)
  {
  return &(LPPROCENT (Cmd))[-1].ep ;
  }

#define MULTIPRO_INCLUDED

