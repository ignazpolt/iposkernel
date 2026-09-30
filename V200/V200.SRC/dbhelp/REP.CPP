//--------------------------------------------------------------------------
//  $Header:   P:/marille/clinicum/dbhelp/rev/rep.cpv   1.12   05 Feb 1999 21:37:14   Martin  $
//  $Log:   P:/marille/clinicum/dbhelp/rev/rep.cpv  $
// 
//    Rev 1.12   05 Feb 1999 21:37:14   Martin
// verbessertes Errorhandling
// 
//    Rev 1.11   05 Oct 1998 11:09:38   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.10   30 Jun 1998 15:08:56   Martin
// compilierbar gemacht
// 
//    Rev 1.9   29 Jun 1998 19:07:06   Hannes
// 
//    Rev 1.7   15 Dec 1997 17:35:34   Hannes
// Zusammenspiel Debugger / Formulargenerierung
// 
//    Rev 1.6   01 Dec 1997 19:40:28   Hannes
// Diverse Anpassungen / Replikator / Speicherfresser
// 
//    Rev 1.5   19 Nov 1997 18:45:46   Hannes
// Restool 32 Bit umstellung
// 
//    Rev 1.2   13 Dec 1996 13:27:00   GERHOLD
// CheckDBIn ... #ifndef WIN32 (Dateifunktionen sind noch nicht impl.)
// 
//    Rev 1.1   26 Nov 1996 07:53:48   HANNES
// Automatischer Update
// 
//    Rev 1.0   08 Nov 1996 13:27:58   HANNES
// Initial revision.
//    Hilfsfunktionen fuer den Replikator
//--------------------------------------------------------------------------
#define WITH_DB

#define REPKENNUNG    "Replikator V1.01"

#include <windows.h>
#include <stdio.h>
#include <dos.h>
#include "dds32.h"

#define NODDSDATA
#include "dds.hpp"

#include "globmem.h"
#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#define MODULENUM 170
#include "winass.hpp"
#include "dbrecord.hpp"
#include "hash.hpp"
#define NOCOMPILE
#include "compile.hpp"
#include "scripthd.hpp"

#include "btrieve.hpp"


#define UNIQUECONSTRAINEDFAILED   5

/*-- Hilfsfunktionen --*/
extern LPSTR WINAPI GetIniName();
static DWORD CounterMin,CounterMax;
DLLExport BOOL _export WINAPI OwnCounter ()
  {
  static BOOL aGelesen,ownCounter;
  if (!aGelesen) {
    char ans[32];
    GetPrivateProfileString ("Counter","OwnCounter","no",
                            ans,32,
                            GetIniName());
    aGelesen = TRUE ;
    ownCounter = (lstrcmp (ans,"yes") == 0);
    if (ownCounter) {
      GetPrivateProfileString ("Counter","CounterMin","0",
                              ans,32,
                              GetIniName());
      for ( LPSTR h = ans ; ((*h >= '0') && (*h <= '9')) ; h ++ )
        CounterMin = CounterMin * 10L + *h - '0' ;
      GetPrivateProfileString ("Counter","CounterMax","0",
                              ans,32,
                              GetIniName());
      for ( h = ans ; ((*h >= '0') && (*h <= '9')) ; h ++ )
        CounterMax = CounterMax * 10L + *h - '0' ;
      WIN_ASSERT (CounterMin > 0L);
      WIN_ASSERT (CounterMax > CounterMin);
      }
    }
  return ownCounter;
  }

short AussenStelle;
int AnzahlExterne;
struct ExternDefinition {
  short Nummer;
  LPSTR ExternDir;
  };
#define MAXAUSSEN 10
static ExternDefinition ed[MAXAUSSEN];
DLLExport BOOL _export WINAPI DoReplicate ()
  {
  static BOOL rGelesen,doReplicate;
  if (!rGelesen) {
    char ans[128];
    GetPrivateProfileString ("DataBase","Replicate","no",
                            ans,sizeof(ans),
                            GetIniName());
    rGelesen = TRUE ;
    if (doReplicate = (lstrcmp (ans,"yes") == 0)) {
      AussenStelle = GetPrivateProfileInt ("DataBase","Aussenstelle",-1,
                                           GetIniName());
      doReplicate = (AussenStelle > 0);
      }
    for (short i = 1 ; i <= MAXAUSSEN ; i++) {
      char anum[16];
      wsprintf (anum,"ADIR%d",i);
      if (GetPrivateProfileString ("DataBase",anum,"",
                              ans,sizeof(ans),
                              GetIniName()) > 0) {
        ed[AnzahlExterne].Nummer = i ;
        ed[AnzahlExterne].ExternDir = LPSTR(GetGlobMem (lstrlen(ans)+1));
        lstrcpy (ed[AnzahlExterne].ExternDir,ans);
        AnzahlExterne ++ ;
        }
      }
    }
  return doReplicate;
  }
BOOL IstAussenStelleAktiv (short as)
  {
  for (int i = 0 ; i < AnzahlExterne ; i++) {
    if (ed[i].Nummer == AussenStelle) continue ;
    if (ed[i].Nummer == as) return TRUE ;
    }
  return FALSE ;
  }

/*-- Darstellen des Fortschrittes ---*/
static char *MsgClass = "RMSGWIN";
extern HINSTANCE hLibInst;
static void RegisterMsgWnd ()
  {
  static BOOL registerDone;
  if (!registerDone) {
    WNDCLASS wndclass;
    wndclass.style         = CS_HREDRAW | CS_VREDRAW | CS_GLOBALCLASS;
    wndclass.lpfnWndProc   = DefWindowProc ;
    wndclass.cbClsExtra    = 0 ;
    wndclass.cbWndExtra    = 0 ;
    wndclass.hInstance     = hLibInst ;
    wndclass.hIcon         = NULL ;
    wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
    wndclass.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
    wndclass.lpszMenuName  = NULL ;
    wndclass.lpszClassName = MsgClass ;

    RegisterClass (&wndclass) ;
    registerDone = TRUE ;
    }
  }

HWND MsgWnd;
void CreateMsgWin ()
  {
  int w = 2 * GetSystemMetrics (SM_CXSCREEN) / 5 ;
  int h = 2 * GetSystemMetrics (SM_CYSCREEN) / 7 ; 
  int x0 = (GetSystemMetrics (SM_CXSCREEN) - w) / 2 ;
  int y0 = (GetSystemMetrics (SM_CYSCREEN) - h) / 2 ;
  RegisterMsgWnd ();
  MsgWnd = CreateWindowEx (
                        WS_EX_DLGMODALFRAME,
                        MsgClass,
                        "Replikationsfortschritt",
                        WS_POPUP | WS_CAPTION | WS_VISIBLE,
                        x0,y0,
                        w,h,
                        NULL,
                        0,
                        hLibInst,
                        NULL
                          );
  }

static void DestroyMsgWin ()
  {
  DestroyWindow (MsgWnd);
  }

static void PaintMsgWnd (LPSTR Text)
  {
  HDC hDC = GetDC (MsgWnd);
  RECT r;
  GetClientRect (MsgWnd,&r);
  r.top += r.bottom / 4;
  r.left += 10 ;
  r.right -= 10 ;
  HBRUSH oldBrush = (HBRUSH)SelectObject (hDC,GetStockObject (LTGRAY_BRUSH));
  HPEN oldPen = (HPEN)SelectObject (hDC,GetStockObject (NULL_PEN));
  Rectangle (hDC,r.left,r.top,r.right,r.bottom);
  SelectObject (hDC,oldPen);
  SelectObject (hDC,oldBrush);
  int oldmode = SetBkMode (hDC,TRANSPARENT);
  DrawText (hDC,Text,-1,&r,DT_CENTER | DT_WORDBREAK);
  SetBkMode (hDC,oldmode);
  ReleaseDC (MsgWnd,hDC);
  }

static void PaintMsgWnd (LPSTR Text,int Num)
  {
  char res[128];
  wsprintf (res,Text,Num);
  PaintMsgWnd (res);
  }

/*-- Definieren der Datenbanken, die fuer den Replikator benoetigt werden --*/
// I) Zuordnung Tabellenname zu Ident
RVarDef T2IVars [] = {
  { "Nummer" , sizeof(LONG) , VAR_LONG , VPROP_NOTNULL } ,
  { "TName" , 64 , VAR_STR , VPROP_NOTNULL }
  };
LPSTR T2ISeg0 [] = {
  "Nummer"
  } ;
RKeyDef T2IKeys [] = {
  { "_Nummer" , 1 , CLKD_AUTOINC | CLKD_UNIQUE , T2ISeg0 }
  } ;
// II) Counter
RVarDef T2CVars [] = {
  { "TId" , sizeof(LONG) , VAR_LONG , VPROP_NOTNULL } ,
  { "Counter" , sizeof(LONG) , VAR_LONG , VPROP_NOTNULL }
  };
LPSTR T2CSeg0 [] = {
  "TId"
  } ;
RKeyDef T2CKeys [] = {
  { "_Nummer" , 1 , CLKD_UNIQUE , T2CSeg0 }
  } ;
// III) TabellenVersionen
RVarDef T2VVars [] = {
  { "TId" , sizeof(LONG) , VAR_LONG , VPROP_NOTNULL } ,
  { "Version" , sizeof(LONG) , VAR_LONG , VPROP_NOTNULL }
  };
LPSTR T2VSeg0 [] = {
  "TId"
  } ;
RKeyDef T2VKeys [] = {
  { "_Nummer" , 1 , CLKD_UNIQUE , T2CSeg0 }
  } ;
// IV) Satzversionen
RVarDef SVVars [] = {
  { "Nummer" , sizeof(LONG) , VAR_LONG , VPROP_NOTNULL } ,
  { "TId" , sizeof(LONG) , VAR_LONG , VPROP_NOTNULL } ,
  { "SId" , sizeof(LONG) , VAR_LONG , VPROP_NOTNULL } ,
  { "Version" , sizeof(LONG) , VAR_LONG , VPROP_NOTNULL } ,
  { "AussenStelle" , sizeof(short) , VAR_STRARR , VPROP_NOTNULL } ,
  { "SatzVersion" , sizeof(LONG) , VAR_LONG , 0 } ,
  { "UpdateMode" , sizeof(DBINT) , VAR_STRARR , 0 } 
  };
LPSTR SVSeg0 [] = {
  "Nummer"
  } ;
LPSTR SVSeg1 [] = {
  "AussenStelle" ,
  "TId" ,
  "Version"
  } ;
LPSTR SVSeg2 [] = {
  "TId" ,
  "SId"
  } ;
LPSTR SVSeg3 [] = {
  "SatzVersion"
  } ;
RKeyDef SVKeys [] = {
  { "_Nummer" , 1 , CLKD_AUTOINC | CLKD_UNIQUE , SVSeg0 } ,
  { "_Tabelle" , 3 , CLKD_UNIQUE | CLKD_MODIFYABLE , SVSeg1 } ,
  { "_Satz" , 2 , CLKD_UNIQUE , SVSeg2 } ,
  { "_SubVersion" , 1 , CLKD_MODIFYABLE , SVSeg3 }
  } ;
// V) Aussenstelle zu Version
RVarDef A2VVars [] = {
  { "RecordVersion" , sizeof(LONG) , VAR_LONG , VPROP_NOTNULL } ,
  { "AussenStelle" , sizeof(short) , VAR_STRARR , VPROP_NOTNULL }
  };
LPSTR A2VSeg0 [] = {
  "RecordVersion",
  "AussenStelle"
  } ;
RKeyDef A2VKeys [] = {
  { "_Nummer" , 2 , CLKD_UNIQUE  , A2VSeg0 }
  } ;
// VI) Token
RVarDef TVars [] = {
  { "Nummer" , sizeof(LONG) , VAR_LONG , VPROP_NOTNULL } ,
  { "TId" , sizeof(LONG) , VAR_LONG , VPROP_NOTNULL } ,
  { "SId" , sizeof(LONG) , VAR_LONG , VPROP_NOTNULL } ,
  { "Value" , sizeof(short) , VAR_STRARR , VPROP_NOTNULL }
  };
LPSTR TSeg0 [] = {
  "Nummer"
  } ;
LPSTR TSeg1 [] = {
  "TId",
  "SId"
  } ;
RKeyDef TKeys [] = {
  { "_Nummer" , 1 , CLKD_UNIQUE | CLKD_AUTOINC , TSeg0 } ,
  { "_Satz" , 2 , CLKD_UNIQUE , TSeg1 } 
  } ;
// VII) Aktive Token
RVarDef ATVars [] = {
  { "Token" , sizeof(LONG) , VAR_LONG , VPROP_NOTNULL } ,
  { "NWAddress" , 32 , VAR_STR , VPROP_NOTNULL }
  };
LPSTR ATSeg0 [] = {
  "Token" 
  } ;
LPSTR ATSeg1 [] = {
  "NWAddress" 
  } ;
RKeyDef ATKeys [] = {
  { "_Token" , 1 , CLKD_UNIQUE , ATSeg0 } ,
  { "_NWAddress" , 1 , 0 , ATSeg1 }
  } ;
// VIII) Kommunikation
RVarDef C2Vars [] = {
  { "TId" , sizeof(LONG) , VAR_LONG , VPROP_NOTNULL } ,
  { "SId" , sizeof(LONG) , VAR_LONG , VPROP_NOTNULL } ,
  { "Prio" , sizeof(DBINT) , VAR_STRARR , VPROP_NOTNULL } ,
  { "RecordVersion" , sizeof(LONG) , VAR_LONG , VPROP_NOTNULL } ,
  { "Updatemode" , sizeof(DBINT) , VAR_STRARR , VPROP_NOTNULL } ,
  { "Daten" , sizeof(LONG) , VAR_BLOB , 0 }
  };
LPSTR C2Seg0 [] = {
  "TId" ,
  "SId"
  } ;
LPSTR C2Seg1 [] = {
  "Prio" ,
  "SId" 
  } ;
RKeyDef C2Keys [] = {
  { "_SKennung" , 2 , CLKD_UNIQUE , C2Seg0 } ,
  { "_PKennung" , 2 , CLKD_MODIFYABLE , C2Seg1 }
  } ;

LPTABLEDEF T2I,T2C,T2V,SV,A2V,A2VFremd[MAXAUSSEN],T,
           TFremd[MAXAUSSEN],AT,SVFremd[MAXAUSSEN],
           A2Communic[MAXAUSSEN],C2[MAXAUSSEN];
hash FAR *t2iHash;
GLOBALHANDLE hGRep;
int AnzReps;
LPREPNODE FAR *rNodes;
void GetCommName (LPSTR res,int anr)
  {
  wsprintf (res,"C%d",anr);
  }
void DefineRepDBs (DLLHANDLE ResDLL)
  {
  if ((DoReplicate()) || (OwnCounter()))
    T2I = DefineSQLDB ("TableToIdent",
                      T2IVars,sizeof(T2IVars) / sizeof(*T2IVars) ,
                      T2IKeys,sizeof(T2IKeys) / sizeof(*T2IKeys) ,
                      ResDLL
                      ) ;
  if (OwnCounter())
    T2C = DefineSQLDB ("TableToCounter",
                      T2CVars,sizeof(T2CVars) / sizeof(*T2CVars) ,
                      T2CKeys,sizeof(T2CKeys) / sizeof(*T2CKeys) ,
                      ResDLL
                      ) ;
  if (DoReplicate ()) {
    T2V = DefineSQLDB ("TableToVersion",
                      T2VVars,sizeof(T2VVars) / sizeof(*T2VVars) ,
                      T2VKeys,sizeof(T2VKeys) / sizeof(*T2VKeys) ,
                      ResDLL
                      ) ;
    SV = DefineSQLDB ("RecordVersion",
                     SVVars,sizeof(SVVars) / sizeof(*SVVars) ,
                     SVKeys,sizeof(SVKeys) / sizeof(*SVKeys) ,
                     ResDLL
                     ) ;
    A2V = DefineSQLDB ("LocationToVersion",
                      A2VVars,sizeof(A2VVars) / sizeof(*A2VVars) ,
                      A2VKeys,sizeof(A2VKeys) / sizeof(*A2VKeys) ,
                      ResDLL
                      ) ;
    T = DefineSQLDB ("Token",
                    TVars,sizeof(TVars) / sizeof(*TVars) ,
                    TKeys,sizeof(TKeys) / sizeof(*TKeys) ,
                    ResDLL
                    ) ;
    AT = DefineSQLDB ("AktiveToken",
                     ATVars,sizeof(ATVars) / sizeof(*ATVars) ,
                     ATKeys,sizeof(ATKeys) / sizeof(*ATKeys) ,
                     ResDLL
                     ) ;
                      
    // Definieren der DBs auf dem fremden Server fuer das
    // Einarbeiten von Replikationen
    //---------------------------------------------
    for (int i = 1 ; i <= MAXAUSSEN ; i++) {
      if (IstAussenStelleAktiv (i)) {
        char TableName[32];
        wsprintf (TableName,"RV%d",i);
        SVFremd[i-1] = DefineSQLDB (TableName,
                                   SVVars,sizeof(SVVars) / sizeof(*SVVars) ,
                                   SVKeys,sizeof(SVKeys) / sizeof(*SVKeys) ,
                                   ResDLL
                                   ) ;
        wsprintf (TableName,"L2V%d",i);
        A2VFremd[i-1] = DefineSQLDB (TableName,
                                    A2VVars,sizeof(A2VVars) / sizeof(*A2VVars) ,
                                    A2VKeys,sizeof(A2VKeys) / sizeof(*A2VKeys) ,
                                    ResDLL
                                    ) ;
        wsprintf (TableName,"T%d",i);
        TFremd[i-1] = DefineSQLDB (TableName,
                                  TVars,sizeof(TVars) / sizeof(*TVars) ,
                                  TKeys,sizeof(TKeys) / sizeof(*TKeys) ,
                                  ResDLL
                                  ) ;
        }
      if ((IstAussenStelleAktiv (i)) || (i == AussenStelle)) {
        char TableName[32];
        GetCommName (TableName,i);
        C2[i-1] = DefineSQLDB (TableName,
                               C2Vars,sizeof(C2Vars) / sizeof(*C2Vars) ,
                               C2Keys,sizeof(C2Keys) / sizeof(*C2Keys) ,
                               ResDLL
                              ) ;
        }
      }
    }
  }

/*---- Laden der Tabellenzuordnung und des Replikatorschemas ------*/
void Relocate (LPREPNODE r,LPSTR Base)
  {
  r->Selection = Base + DWORD(r->Selection);
  for (int i = 0 ; i < r->AnzSubNodes ; i++) {
    r->rpSub[i] = LPREPNODE (Base + DWORD(r->rpSub[i]));
    Relocate (r->rpSub[i],Base);
    }
  }

void DBTestTable (LPTABLEDEF t)
  {
  if (t != NULL) {
    LPDBREQUEST req = InitializeRequest ("",1,DBCALLTYPE_CREATE,NULL);
    req->AddTableDef (t);
    LPVOID hstmt = NULL;
    int res = GetDLLAdmin()->GetDLLEntry(req->GetDLLHandle())->DBCall (DBOP_GET,-1,req,&hstmt,NULL);
    GetDLLAdmin()->GetDLLEntry(req->GetDLLHandle())->DBCall (DBOP_RESET,-1,req,&hstmt,NULL);
    FreeRequest (req);
    }
  }

void LoadTableIdents (BOOL doCreate)
  {
  if ((DoReplicate()) || (OwnCounter())) {

    if (doCreate)
      DBTestTable (T2I);

    static ParamBlock p;
    lmemset (&p,'\0',sizeof(p));
    p.AnzPars = 0;


    DBList FAR *res = new DBList (T2I,0L,"",30,30,&p,FALSE);
    res->SetOrder ("Nummer");
    t2iHash = new hash (47,STRKEY);
    for ( LPDBRECORD r = res->GetFirst (); r != NULL ; r = res->GetNext(r)) {
      LPDWORD i = LPDWORD (r->Get(0));
      t2iHash->SetData (LPSTR(r->Get(1)),i,sizeof(*i));
      }

    delete res ;

    if (doCreate) {
      LPVOID h;
      for ( LPTABLEDEF t = GetTableAdmin()->GetFirstTableDef (&h) ;
                t != NULL ;
                    t = GetTableAdmin()->GetNextTableDef (&h) ) {
        if ((t->IsRealTable()) && (t2iHash->GetData(t->GetName()) == NULL)) {
          // Dieser Satz muss noch eingefuegt werden
          LPDBRECORD n = new DBRecord (T2I);
          n->Set (1,t->GetName(),lstrlen(t->GetName())+1) ;
          DWORD i;
          WIN_ASSERT (Out (n,-1,DBCALLTYPE_STANDARDINSERT,&i,""));
          t2iHash->SetData (LPSTR(n->Get(1)),&i,sizeof(i));
          delete n ;
          }
        }

      // Sicherheitshalber noch einen Touch auf die restlichen Tabellen !
      //-----------------------------------------------------------------
      DBTestTable (T2C);
      DBTestTable (T2V);
      DBTestTable (SV);
      DBTestTable (A2V);
      for (int i = 0 ; i < MAXAUSSEN ; i++)
        DBTestTable (A2VFremd[i]);
      DBTestTable (T);
      for (i = 0 ; i < MAXAUSSEN ; i++)
        DBTestTable (TFremd[i]);
      DBTestTable (AT);
      for (i = 0 ; i < MAXAUSSEN ; i++)
        DBTestTable (SVFremd[i]);
      for (i = 0 ; i < MAXAUSSEN ; i++)
        DBTestTable (C2[i]);
      }
    }
  if (DoReplicate()) {
    // Laden des Replikationsschemas
    DWORD DataSize;
    if (hGRep = ReadDataDict (2,0,0,&DataSize)) {
      LPSTR Base = (LPSTR)GlobalLock (hGRep);
      short FAR *Anz = (short FAR *) Base;
      AnzReps = *Anz;
      rNodes = (LPREPNODE FAR *) (Anz + 1);
      for (int i = 0 ; i < AnzReps ; i++) {
        rNodes[i] = LPREPNODE (Base + DWORD(rNodes[i]));
        Relocate (rNodes[i],Base);
        }
      }
    }
  }

/*---- Ermitteln des Primaerschluessels einer Tabelle ------*/
DLLExport DWORD _export WINAPI GetCounterValue (LPTABLEDEF t)
  {
  DWORD res ;
  DBWIN_ASSERT (OwnCounter());
  LPDWORD tn = LPDWORD (t2iHash->GetData(t->GetName()));
  DBWIN_ASSERT (tn != NULL);
  // Lesen des entsprechenden Wertes
  LPDBRECORD h = Ask (T2C,"TId = %1",tn,sizeof(*tn),VAR_LONG);

  if (h != NULL) {
    res = *(DWORD FAR *) h->Get(1);
    DWORD res1 = res + 1L ;
    // Und entsprechend den naechsten Wert setzten
    h->Set (1,&res1,sizeof(res1));
    DBWIN_ASSERT (Out (h,-1,DBCALLTYPE_STANDARDUPDATE,NULL,"TId = %1",tn,sizeof(*tn),VAR_LONG));
    delete h ;
    }
  else {
    // Auf der Datenbank muss der Extremwert gesucht werden
    char selection[512];
    LPSTR sName[1],tName[1];
    LPCLKEYDEF cd = t->GetKeyDef (0);
    DBWIN_ASSERT ((cd->Attribute & CLKD_AUTOINC) != 0);
    LPSTR PrimName = t->GetVarDef(cd->VarID)->GetName();
    sName[0] = PrimName;
    tName[0] = t->GetName();
    LPTABLEDEF q1 = GetTableAdmin()->GetTemporaryTable (1,sName,1,tName) ;
    wsprintf (selection,"%s = (SELECT MAX(%s) FROM %s WHERE %s >= %%1 AND %s <= %%2)",
                PrimName,PrimName,t->GetName(),PrimName,PrimName);
    LPDBRECORD m = Ask (q1,selection,&CounterMin,sizeof(CounterMin),VAR_LONG,&CounterMax,sizeof(CounterMax),VAR_LONG);
    if (m != NULL) {
      res = *(DWORD FAR *) m->Get(0) + 1;
      delete m ;
      }
    else
      res = CounterMin;

    h = new DBRecord (T2C);
    h->Set (0,tn,sizeof(*tn));
    DWORD res1 = res + 1L ;
    h->Set (1,&res1,sizeof(res1));
    DBWIN_ASSERT (Out (h,-1,DBCALLTYPE_STANDARDINSERT,NULL,""));
    delete h ;
    GetTableAdmin()->FreeTable (q1->GetTableID(),q1->GetVersion());
    }

  return res ;
  }

static int AnzRepNodes = -1;
static LPREPNODE FAR *RNodes;
static GLOBALHANDLE hGRepNode;
void FixupNode (RepNode FAR *r,LPSTR base)
  {
  r->Selection = LPSTR(base + DWORD(r->Selection)) ;
  for (int i = 0 ; i < r->AnzSubNodes ; i++) {
    r->rpSub[i] = LPREPNODE (base + DWORD(r->rpSub[i]));
    FixupNode (r->rpSub[i],base);
    }
  }
void LoadRepNodes ()
  {
  if (AnzRepNodes < 0) {
    DWORD Size;
    hGRepNode = ReadDataDict (2,0,0,&Size);
    if (hGRepNode) {
      LPSTR base = LPSTR (GlobalLock (hGRepNode));
      AnzRepNodes = *(short FAR *) base ;
      RNodes = (LPREPNODE FAR *) (base + sizeof(short)) ;
      for (int i = 0 ; i < AnzRepNodes ; i++) {
        RNodes[i] = LPREPNODE (base + DWORD(RNodes[i]));
        FixupNode (RNodes[i],base);
        }
      }
    else
      AnzRepNodes = 0 ;
    }
  }

BOOL IsInCheckIn;
#define TABLESTOCHECK   50
static WORD DontTNr[TABLESTOCHECK],DontV[TABLESTOCHECK];
static LPSTR RootTable[TABLESTOCHECK];
static DWORD RootVersion[TABLESTOCHECK];
static WORD AnzDont;
DLLExport void _export WINAPI NoManipulate (WORD TableNr,WORD Version,LPSTR VersionFromTable)
  {
  for (int i = 0 ; i < AnzDont ; i++) {
    if ((DontTNr[i] == TableNr) && (DontV[i] == Version)) {
      WIN_ASSERT (lstrcmp (RootTable[i],VersionFromTable) == 0);
      }
    }
  if (i == AnzDont) {
    WIN_ASSERT (AnzDont < TABLESTOCHECK);
    DontTNr[AnzDont] = TableNr;
    DontV[AnzDont] = Version;
    RootTable[AnzDont] = LPSTR(GetGlobMem (lstrlen(VersionFromTable) + 1));
    lstrcpy (RootTable[AnzDont],VersionFromTable);
    RootVersion [AnzDont] = 0L;
    AnzDont ++ ;
    }
  }

void SetVersionToList (LPSTR Name,DWORD nVersion)
  {
  for ( WORD i = 0 ; i < AnzDont ; i++) {
    if (lstrcmp (RootTable[i],Name) == 0) {
      RootVersion [i] = nVersion ;
      }
    }
  }

DLLExport void _export OnEndTransaction ()
  {
  for (WORD i = 0 ; i < AnzDont ; i++) {
    if (RootTable[i]) {
      FreeGlobMem (RootTable[i]) ; 
      RootTable[i] = NULL ;
      RootVersion[i] = 0;
      }
    }
  AnzDont = 0 ;
  }

DWORD VersionFromRoot (WORD TNr,WORD V)
  {
  for (WORD i = 0 ; i < AnzDont ; i++) {
    if ((TNr == DontTNr[i]) && (V == DontV[i]))
      return RootVersion[i];
    }
  return 0L ;
  }


int LastError ()
  {
  return (GetDLLAdmin()->GetDLLEntry (GetTransactionDLL())->DBGetLastError ());
  }

BOOL InSystemUpdate;
DLLExport void _export WINAPI StartSystemUpdate ()
  {
  InSystemUpdate = TRUE ;
  }

DLLExport void _export WINAPI OnManipulate (LPDBRECORD r,short updateMode,LPTABLEDEF td,LPVOID KeyBuffer)
  {
  if ((IsInCheckIn) || (InSystemUpdate)) return ;

  if (DoReplicate ()) {
    LoadRepNodes ();

    WORD vid;
    LPTABLEDEF t = (td != NULL) ? td : r->GetTableDef(0,&vid);

    for (int i = 0 ; i < AnzRepNodes ; i++) {
      if ((RNodes[i]->tRef.TableNr == t->GetTableID()) &&
          (RNodes[i]->tRef.Version == t->GetVersion()) &&
          (RNodes[i]->checkUpdateMode (updateMode))) {
        DWORD RootVersion = VersionFromRoot (RNodes[i]->tRef.TableNr,RNodes[i]->tRef.Version);
        //      1. Die Version aus TableZuVersion lesen,
        //         und die naechste Version in TableZuVersion 
        //         vermerken
        //--------------------------------------------------------
        DWORD v,v1;
        LPDWORD tn = LPDWORD (t2iHash->GetData(t->GetName()));
        DBWIN_ASSERT (tn != NULL);
        // Lesen des entsprechenden Wertes
        LPDBRECORD h = Ask (T2V,"TId = %1",tn,sizeof(*tn),VAR_LONG);
        if (h != NULL) {
          v = *(DWORD FAR *) h->Get(1);
          v1 = v + 1L ;
          // Und entsprechend den naechsten Wert setzten
          h->Set (1,&v1,sizeof(v1));
          DBWIN_ASSERT (Out (h,-1,DBCALLTYPE_STANDARDUPDATE,NULL,"TId = %1",tn,sizeof(*tn),VAR_LONG));
          delete h ;
          }
        else {
          // Als Resultat wird 1 verwendet, in die Datenbank wird als naechste Version
          // 2 geschrieben
          v = 1L ;
          v1 = 2L ;

          h = new DBRecord (T2V);
          h->Set (0,tn,sizeof(*tn));
          h->Set (1,&v1,sizeof(v1));
          DBWIN_ASSERT (Out (h,-1,DBCALLTYPE_STANDARDINSERT,NULL,""));
          delete h ;
          }
        //    2. Die Aktuelle Version in SatzVersion vermerken
        //---------------------------------------------------------
        DWORD SId;
        LPVOID KData;
        if (KeyBuffer != NULL)
          KData = KeyBuffer;
        else
          KData = r->GetPrimKey()->Data;
        DBWIN_ASSERT_TEXT (KData != NULL,"Primaerschluessel nicht gesetzt!");
        if (GetBlockSize(KData) == sizeof(LONG))
          SId = *(DWORD FAR *) KData;
        else if (GetBlockSize(KData) == sizeof(short))
          SId = *(DWORD FAR *) KData;
        else
          DBWIN_ASSERT_TEXT (FALSE,"Falscher Primaerschluessel");

        if (updateMode > UPDATEMODE_INSERT) {
          h = Ask (SV,"TId = %1 AND SId = %2",
                  tn,sizeof(*tn),VAR_LONG,
                  &SId,sizeof(SId),VAR_LONG
                  );
          }
        else
          h = NULL ;
        if (h != NULL) {
          // Der Satz muss mit der Neuen Version versehen werden
          h->Set(3,&v,sizeof(v));
          h->Set(4,&AussenStelle,sizeof(AussenStelle));
          #ifdef UEBERLEGT
          // if (RootVersion)
          //  h->Set (5,&RootVersion,sizeof(RootVersion));
          // else
          //  h->Del (5);
          #endif
          h->Set (6,&updateMode,sizeof(updateMode));

          DWORD FAR *lpn = (DWORD FAR *) h->Get(0);
          DBWIN_ASSERT (Out (h,-1,DBCALLTYPE_STANDARDUPDATE,NULL,"Nummer = %1",lpn,sizeof(*lpn),VAR_LONG));

          // Die Eintraege der Fremddatenbanken fuer die erfolgreiche Replikation
          // muessen geloescht werden
          //---------------------------------------------------------------------
          Excute ("DELETE FROM LocationToVersion WHERE RecordVersion = %1",
                 GetTransactionDLL(),lpn,sizeof(*lpn),VAR_LONG
                 );
          if (updateMode < UPDATEMODE_DELETE)
            SetVersionToList (t->GetName(),*lpn);
                        
          delete h;
          }
        else {
          // Der Satz muss up to date gebracht werden
          h = new DBRecord (SV);
          h->Set(1,tn,sizeof(*tn));
          h->Set(2,&SId,sizeof(SId));
          h->Set(3,&v,sizeof(v));
          h->Set(4,&AussenStelle,sizeof(AussenStelle));
          if (RootVersion)
            h->Set (5,&RootVersion,sizeof(RootVersion));
          else
            h->Del (5);
          h->Set (6,&updateMode,sizeof(updateMode));
          DWORD nVersion;
          DBWIN_ASSERT (Out (h,-1,DBCALLTYPE_STANDARDINSERT,&nVersion,""));
          if (updateMode < UPDATEMODE_DELETE)
            SetVersionToList (t->GetName(),nVersion);

          delete h;
          }
        // Fertig Version markieren
        }
      }
    }
  }

void FreeRepNodes ()
  {
  GlobalUnlock (hGRepNode);
  GlobalFree (hGRepNode);
  }

//-------------------------------------------------------------
// Zusammenbasteln der einzelnen Transaktionen zu Files
//-------------------------------------------------------------
int AussenStellenIndex ()
  {
  for (int i = 0 ; i < AnzahlExterne ; i++) {
    if (ed[i].Nummer == AussenStelle) return i ;
    }
  WIN_ASSERT(FALSE) ;
  return 0;
  }
struct VToDel {
  long Nummer;
  VToDel FAR *Next;
  };
VToDel FAR *vLst;
void PushVN (LONG n)
  {
  VToDel FAR *v = (VToDel FAR *) GetGlobMem (sizeof(*v));
  v->Nummer = n;
  v->Next = vLst;
  vLst = v;
  }
BOOL PopVN (DWORD FAR *n)
  {
  if (vLst) {
    *n = vLst->Nummer ;
    VToDel FAR *ol = vLst;
    vLst = vLst->Next;
    FreeGlobMem (ol);
    return FALSE ;
    }
  else
    return TRUE ;
  }

#ifdef WITH_DB
WORD GetPrio (DWORD TId,WORD updateMode)
  {
  WORD res = 0 ;
  LoadRepNodes ();
  for ( int i = 0 ; ((i < AnzRepNodes) && (res == 0)) ; i++) {
    if (!RNodes[i]->checkUpdateMode (updateMode)) continue ;
    LPTABLEDEF t = GetTableAdmin()->GetTableDef (RNodes[i]->tRef.TableNr,RNodes[i]->tRef.Version);

    LPDWORD tn = LPDWORD (t2iHash->GetData(t->GetName()));
    WIN_ASSERT (tn != NULL);
    if (*tn == TId) res = RNodes[i]->Prio;
    GetTableAdmin()->FreeTable (RNodes[i]->tRef.TableNr,RNodes[i]->tRef.Version);
    }
  WIN_ASSERT (res > 0);
  return res;
  }
void WriteToCommunic (int anr,DWORD tID,      // Table - ID
                              DWORD sID,      // Satz - ID
                              DWORD SV,       // Satz - Version
                              DBINT UpdMode,  // Art des zuletzt gemachten Updates
                              GLOBALHANDLE hGData,
                              DWORD dwSize
                     )
  {
  static LPSTR sName[1] = { "RecordVersion" } ;
  LPSTR tName[1];
  char actName [32];
  GetCommName(actName,anr);
  tName[0] = actName;
  LPTABLEDEF q1 = GetTableAdmin()->GetTemporaryTable (1,sName,1,tName) ;
  LPDBRECORD h = Ask (q1,"TId = %1 AND SId = %2",
                      &tID,sizeof(tID),VAR_LONG,
                      &sID,sizeof(sID),VAR_LONG
                     );
  if (h != NULL) {
    if (*((DWORD FAR *)h->Get(0)) < SV) {
      // Es muss ein Update gemacht werden, der Satz der bereits 
      // einmal geschrieben wurde, wurde nie abgeholt und ist
      // ist nicht mehr gueltig!
      //======================================================
      WORD prio = GetPrio (tID,UpdMode);
      LPDBRECORD r = new DBRecord (C2[anr - 1]);
      r->Set (0,&tID,sizeof(tID));
      r->Set (1,&sID,sizeof(sID));
      r->Set (2,&prio,sizeof(prio));
      r->Set (3,&SV,sizeof(SV));
      r->Set (4,&UpdMode,sizeof(UpdMode));
      BlobDesc bd;
      bd.hGmem = hGData ;
      bd.Size = dwSize;
      r->Set (5,&bd,sizeof(bd));

      WIN_ASSERT (Out (r,5,DBCALLTYPE_STANDARDUPDATE,NULL,"TId = %1 AND SId = %2",
                      &tID,sizeof(tID),VAR_STRARR,
                      &sID,sizeof(sID),VAR_LONG
                 ));

      r->Del (5) ;    // Damit hGmem nicht freigegeben wird
      }
    delete h ;
    }
  else {
    // Es muss ein Einfuegen gemacht werden
    //======================================================
    LPDBRECORD r = new DBRecord (C2[anr - 1]);
    WORD prio = GetPrio (tID,UpdMode);

    r->Set (0,&tID,sizeof(tID));
    r->Set (1,&sID,sizeof(sID));
    r->Set (2,&prio,sizeof(prio));
    r->Set (3,&SV,sizeof(SV));
    r->Set (4,&UpdMode,sizeof(UpdMode));
    BlobDesc bd;
    bd.hGmem = hGData ;
    bd.Size = dwSize;
    r->Set (5,&bd,sizeof(bd));

    WIN_ASSERT (Out (r,5,DBCALLTYPE_STANDARDINSERT,NULL,""));

    r->Del (5) ;    // Damit hGmem nicht freigegeben wird
    }
  GetTableAdmin()->FreeTable (q1->GetTableID(),q1->GetVersion());
  }
#else
HFILE OpenRepFile (LPSTR Dir)
  {
  char fname[13];
  char fullName[256];
  BOOL done = FALSE;
  HFILE res ;
  for (int i = 0 ; !((done) && (i < 100)) ; i++ ) {
    LONG t0 = Now();
    wsprintf (fname,"F%07lX.rep",(t0 + LONG(i)) & 0xFFFFFFF);
    lstrcpy (fullName,Dir);
    lstrcat (fullName,fname);
    OFSTRUCT Of;
    res = OpenFile (fullName,&Of,OF_EXIST);
    if (res == HFILE_ERROR) {
      // File nicht gefunden -> Versuch mit diesem Namen eins anzulegen
      return OpenFile (fullName,&Of,OF_CREATE | OF_SHARE_EXCLUSIVE);
      }
    else
      continue ;    // Mit dem naechsten Namen probieren
    }
  return HFILE(0);
  }
#endif

GLOBALHANDLE PrepareRepBuffer (DWORD FAR *Size,DWORD Version,DWORD RecordVersion,DWORD PrimKey,short RepNum)
  {
  *Size = sizeof(RepBase);
  GLOBALHANDLE hGmem = GlobalAlloc (GMEM_MOVEABLE,*Size);
  RepBase FAR *rp = (RepBase FAR *) GlobalLock (hGmem);
  lmemset (rp,'\0',sizeof(*rp));
  lstrcpy (rp->Kennung,REPKENNUNG);
  rp->Version = Version;
  rp->AussenStelle = AussenStelle;
  rp->RecordVersion = RecordVersion;
  rp->PrimKey = PrimKey;
  rp->RepNum = RepNum;
  rp->AnzRecords = 0;
  GlobalUnlock (hGmem);

  return hGmem;
  }

DWORD FindInSubVersion (LPDBRECORD r,DBList FAR *SubVersions,LONG FAR *svers)
  {
  WORD vid;
  LPTABLEDEF t = r->GetTableDef(0,&vid);
  for (LPDBRECORD h = SubVersions->GetFirst () ; h != NULL ; h = SubVersions->GetNext (h)) {
    if ((*(LPDWORD (t2iHash->GetData(t->GetName()))) == 
         *(LPDWORD (h->Get(1)))) && // Selbe Tabelle
        (*(LPDWORD (r->GetPrimKey()->Data)) ==
         *(LPDWORD (h->Get(2))))) {   // Selber Satz
      *svers = *(LPDWORD (h->Get(3)));    // Die Version zurueckgeben
      return *(LPDWORD (h->Get(0)));      // und die Kennung der Satzversion
      }
    }
  return 0L ;
  }

GLOBALHANDLE PushRecordToRepBuffer (GLOBALHANDLE hGmem,DWORD FAR *Size,LPDBRECORD r,DBList FAR *SubVersions)
  {
  DWORD rSize = sizeof(RecBase);
  for (int i = 0 ; i < int(r->GetAnzVars ()) ; i++) {
    LPVOID d = r->Get(i);
    if (d != NULL)
      rSize += sizeof(VarBase) + GetBlockSize(d);
    }

  hGmem = GlobalReAlloc (hGmem,*Size + rSize,GMEM_MOVEABLE);
  RepBase FAR *rp = (RepBase FAR *) GlobalLock (hGmem);
  rp->AnzRecords ++ ;

  RecBase FAR *cp = (RecBase FAR *) (LPSTR (rp) + *Size) ;
  cp->AnzVars = 0 ;
  cp->RecordVersion = FindInSubVersion (r,SubVersions,&cp->Version);
  cp->tRef.TableNr = r->GetTableID();
  cp->tRef.Version = r->GetVersion();

  VarBase FAR *vp = (VarBase FAR *) (cp + 1) ;

  for (i = 0 ; i < int(r->GetAnzVars ()) ; i++) {
    LPVOID d = r->Get(i);
    if (d != NULL) {
      vp->VarID = (short) i ;
      vp->size = GetBlockSize(d);
      lmemcpy (vp+1,d,vp->size);
      vp = (VarBase FAR *) (LPSTR (vp + 1) + vp->size);
      cp->AnzVars ++ ;
      }
    }

  GlobalUnlock (hGmem);

  *Size += rSize;
  rp->GesSize = *Size;

  return hGmem;
  }

// 
// Verwalten aller Datesaetze, die in einem Paket versandt worden sind
//
struct FAR _RDone {
  _RDone FAR *Next;
  PrimKey FAR *k;
  LPTABLEDEF td;
  };
typedef _RDone FAR *LPRDONE;
LPRDONE rd;
BOOL RecordDone (LPDBRECORD h,LPTABLEDEF td)
  {
  for (LPRDONE x = rd ; x != NULL ; x = x->Next) {
    if ((x->td->GetTableID() == td->GetTableID()) && (*(x->k) == *h->GetPrimKey()))
      return TRUE ;
    }
  return FALSE ;
  }
void MarkRecordDone (LPDBRECORD h,LPTABLEDEF td)
  {
  LPRDONE n = LPRDONE (GetGlobMem (sizeof(*n)));
  n->Next = rd;
  rd = n;
  n->k = new PrimKey ();
  *(n->k) = *(h->GetPrimKey()) ;
  n->td = td;
  }
void FreeRecordDoneList ()
  {
  for ( ; (rd != NULL) ; ) {
    LPRDONE n = rd->Next ;
    delete rd->k;
    FreeGlobMem (rd);
    rd = n ;
    }
  }
void ExtractRecord (LPREPNODE node,DWORD pID,LPDBRECORD Parent,GLOBALHANDLE FAR *hGmem,DWORD FAR *Size,DBList FAR *SubVersions)
  {
  // Lesen der Saetze in einer Liste
  BOOL doIt;
  DWORD pID1;
  BOOL doID1 = FALSE ;
  if (Parent != NULL) {
    LPDWORD lppID = LPDWORD(Parent->Get (node->pForeignVar));
    LPDWORD lppID1;
    if (node->pForeignVar1 != 0xFFFF)
      lppID1 = LPDWORD(Parent->Get (node->pForeignVar1));
    else
      lppID1 = NULL ;
    if (doIt = (lppID != NULL)) {
      if (GetBlockSize (lppID) == sizeof(DWORD)) 
        pID = *lppID ;
      else if (GetBlockSize (lppID) == sizeof(short)) 
        pID = DWORD ( *(short FAR *) lppID) ;
      else 
        WIN_ASSERT (FALSE);
      }
    if (lppID1 != NULL) {
      doID1 = TRUE ;
      if (GetBlockSize (lppID1) == sizeof(DWORD)) 
        pID1 = *lppID1 ;
      else if (GetBlockSize (lppID) == sizeof(short)) 
        pID1 = DWORD ( *(short FAR *) lppID1) ;
      else 
        WIN_ASSERT (FALSE);
      }
    }
  else
    doIt = TRUE ;

  if (doIt) {
    LPTABLEDEF td = GetTableAdmin()->GetTableDef (node->tRef.TableNr,node->tRef.Version);
    ParamBlock p;
    lmemset (&p,'\0',sizeof(p));
    p.AnzPars = 1;
    p.ptr[0] = GetGlobMem (sizeof(DWORD));
    *(DWORD FAR *) p.ptr[0] = pID;
    if (doID1) {
      p.AnzPars = 2;
      p.ptr[1] = GetGlobMem (sizeof(DWORD));
      *(DWORD FAR *) p.ptr[1] = pID1;
      }

    DBList FAR *recs = new DBList (td,0L,node->Selection,30,30,&p,FALSE);
    recs->SetOrder ("");

    for ( LPDBRECORD h = recs->GetFirst() ; h != NULL ; h = recs->GetNext (h) ) {
      // Den so gelieferten Datensatz Auf den Block legen
      //--------------------------------------------------
      if (!RecordDone (h,td)) {
        *hGmem = PushRecordToRepBuffer (*hGmem,Size,h,SubVersions);
        MarkRecordDone (h,td);
        }
      // Und rekursiv weitermachen
      //--------------------------------
      for (int i = 0 ; i < node->AnzSubNodes ; i++)
        ExtractRecord (node->rpSub[i],0L,h,hGmem,Size,SubVersions);
      }

    delete recs;

    FreeGlobMem (p.ptr[0]);

    GetTableAdmin()->FreeTable (node->tRef.TableNr,node->tRef.Version);
    }
  }

BOOL isASDone (short FAR *ASDone,int iASDone,short Nummer)
  {
  for (int i = 0 ; i < iASDone ; i++)
    if (Nummer == ASDone[i]) return TRUE ;
  return FALSE ;
  }


static char *CHECKOUTPATTERN = "%d Transaktionen erzeugt" ;
DLLExport void _export WINAPI CheckDBOut ()
  {
  if (DoReplicate ()) {
    BOOL msgCreated = FALSE ;
    int tNum = 0;

    LoadRepNodes ();
    for ( int i = 0 ; i < AnzRepNodes ; i++) {
      LPTABLEDEF t = GetTableAdmin()->GetTableDef (RNodes[i]->tRef.TableNr,RNodes[i]->tRef.Version);

      LPDWORD tn = LPDWORD (t2iHash->GetData(t->GetName()));
      WIN_ASSERT (tn != NULL);

      //
      // Laden aller Wurzelsaetze der Tabelle, die (ev.) repliziert werden 
      // muessen
      //

      ParamBlock p0;
      lmemset (&p0,'\0',sizeof(p0));
      p0.AnzPars = 2;
      p0.ptr[0] = GetGlobMem (sizeof(AussenStelle));
      p0.pType[0] = VAR_STRARR;
      *(short FAR *) p0.ptr[0] = AussenStelle;
      p0.ptr[1] = GetGlobMem (sizeof(*tn));
      *(long FAR *) p0.ptr[1] = *tn;

      static char *SVSelection[] = {
        "AussenStelle = %1 AND TId = %2 AND UpdateMode < 2",
        "AussenStelle = %1 AND TId = %2 AND UpdateMode >= 2"
        } ;
      DBList FAR *Versions = new DBList (SV,0L,SVSelection[RNodes[i]->updateModeIndex],30,30,&p0,FALSE);
      Versions->SetOrder ("AussenStelle,TId,Version");

      for (LPDBRECORD vr = Versions->GetFirst () ; vr != NULL ; vr = Versions->GetNext (vr) ) {
        short ASDone[MAXAUSSEN];
        int iASDone;
        //
        // Untersuchen, ob nicht vielleicht schon alle Aussenstellen sich 
        // eingetragen haben
        //
        ParamBlock p1;
        lmemset (&p1,'\0',sizeof(p1));
        p1.AnzPars = 1;
        p1.ptr[0] = GetGlobMem (sizeof(LONG));
        *(LONG FAR *) p1.ptr[0] = *(LONG FAR *) vr->Get(0);

        DBList FAR *ADone = new DBList (A2V,0L,"RecordVersion = %1",30,30,&p1,FALSE);
        ADone->SetOrder ("RecordVersion,AussenStelle");

        int arDone = AnzahlExterne - 1;
        iASDone = 0;
        for ( LPDBRECORD ar = ADone->GetFirst() ; ar != NULL ; ar = ADone->GetNext(ar) ) {
          ASDone[iASDone] = *(short FAR *) ar->Get(1);
          if (IstAussenStelleAktiv (*(short FAR *) ar->Get(1)))
            arDone -- ;
          }

        delete ADone ;
        FreeGlobMem (p1.ptr[0]);

        if (arDone == 0)
          // Der Satz darf Geloescht werden -> Vermerken fuer spaeter
          PushVN (*(LONG FAR *) vr->Get(0));
        else {
          // 
          // Der Satz muss abgearbeitet werden -> Durch Rekursiven Teil
          // Lesen aller Saetze
          //
          if (vr->Get (5) == NULL) {
            // Nur replizieren, wenn es sich um einen Subdatentyp handelt
            //-----------------------------------------------------------
            if (!msgCreated)
              CreateMsgWin () , msgCreated = TRUE ;
            PaintMsgWnd (CHECKOUTPATTERN,tNum);

            ParamBlock p2;
            lmemset (&p2,'\0',sizeof(p2));
            p2.AnzPars = 1;
            p2.ptr[0] = GetGlobMem (sizeof(DWORD));
            *(DWORD FAR *) p2.ptr[0] = *(DWORD FAR *) (vr->Get(0));
            DBList FAR *SubVersions = new DBList (SV,0L,"SatzVersion = %1",-1,-1,&p1,FALSE);
            SubVersions->SetOrder ("SatzVersion");

            DWORD DataSize ;
            GLOBALHANDLE hGmem = PrepareRepBuffer (&DataSize,* (DWORD FAR *) vr->Get(3),* (DWORD FAR *) vr->Get(0), * (DWORD FAR *) vr->Get(2),short (i));
            ExtractRecord (RNodes[i],*(DWORD FAR *) vr->Get(2),NULL,&hGmem,&DataSize,SubVersions);
            FreeRecordDoneList ();

            delete SubVersions ;
            FreeGlobMem (p2.ptr[0]);

            if (hGmem) {
              for (int i = 0 ; i < AnzahlExterne ; i++) {
                if (ed[i].Nummer == AussenStelle) continue ;    // Die eigene Aussenstelle zaehlt nicht
                if (!isASDone (ASDone,iASDone,ed[i].Nummer)) {
                  #ifdef WITH_DB
                  WriteToCommunic (ed[i].Nummer,
                                  *(DWORD FAR *)vr->Get(1),    // TId
                                  *(DWORD FAR *)vr->Get(2),    // SId
                                  *(DWORD FAR *)vr->Get(3),    // SV
                                  *(DBINT FAR *)vr->Get(6),    // UpdateModew
                                  hGmem,DataSize
                                  );
                  #else
                  HFILE hf = OpenRepFile (ed[i].ExternDir);
                  if (hf != HFILE_ERROR) {
                    _hwrite(hf,LPSTR(GlobalLock (hGmem)),DataSize);
                    _lclose (hf);
                    }
                  else
                    WIN_ASSERT_TEXT(FALSE,"Verbindung zu Aussenstelle konnte nicht aufgenommen werden");
                  #endif
                  }
                }

              PaintMsgWnd (CHECKOUTPATTERN,++ tNum);

              GlobalFree (hGmem);
              }
            else
              WIN_ASSERT(FALSE);
            }
          }
        }

      delete Versions ;

      FreeGlobMem (p0.ptr[0]);
      FreeGlobMem (p0.ptr[1]);
      GetTableAdmin()->FreeTable (RNodes[i]->tRef.TableNr,RNodes[i]->tRef.Version);

      DWORD vn;
      for ( BOOL empty = PopVN(&vn) ; (!empty) ; empty = PopVN(&vn) ) {
        BeginTransaction(FALSE);
        Excute ("DELETE FROM LocationToVersion WHERE RecordVersion = %1",GetTransactionDLL(),&vn,sizeof(vn),VAR_LONG);
        Excute ("DELETE FROM RecordVersion WHERE Nummer = %1",GetTransactionDLL(),&vn,sizeof(vn),VAR_LONG);
        EndTransaction();
        }
      }
    if (msgCreated)
      DestroyMsgWin ();
    }
  }

//--------------------------------------------
// Einarbeiten der einzelnen Transaktionen 
//--------------------------------------------
void DeleteTransaction (LPREPNODE node,DWORD pID,LPDBRECORD Parent,BOOL stopOnTopNode)
  {
  static char *delpattern1 = "DELETE FROM " ;
  static char *delpattern2 = " WHERE " ;

  BOOL doIt;
  DWORD pID1;
  BOOL doID1 = FALSE;
  if (Parent != NULL) {
    if (stopOnTopNode) {
      for (int i = 0 ; i < AnzRepNodes ; i++) {
        if ((RNodes[i]->tRef.TableNr == node->tRef.TableNr) &&
            (RNodes[i]->tRef.Version == node->tRef.Version))
          // Es Handelt sich um einen Hauptknoten, der darf beim Loeschen
          // Nicht mitgeloescht werden, da er ja als eigener Knoten
          // repliziert wird
          return ;
        }
      }
    LPDWORD lppID = LPDWORD(Parent->Get (node->pForeignVar));
    LPDWORD lppID1;
    if (node->pForeignVar1 != 0xFFFF)
      lppID1 = LPDWORD(Parent->Get (node->pForeignVar));
    else
      lppID1 = NULL;
    if (doIt = (lppID != NULL)) {
      if (GetBlockSize (lppID) == sizeof(DWORD)) 
        pID = *lppID ;
      else if (GetBlockSize (lppID) == sizeof(short)) 
        pID = DWORD ( *(short FAR *) lppID) ;
      else 
        WIN_ASSERT (FALSE);
      }
    if (lppID1 != NULL) {
      doID1 = TRUE ;
      if (GetBlockSize (lppID1) == sizeof(DWORD)) 
        pID1 = *lppID1 ;
      else if (GetBlockSize (lppID) == sizeof(short)) 
        pID1 = DWORD ( *(short FAR *) lppID1) ;
      else 
        WIN_ASSERT (FALSE);
      }
    }
  else
    doIt = TRUE ;

  if (doIt) {
    LPTABLEDEF td = GetTableAdmin()->GetTableDef (node->tRef.TableNr,node->tRef.Version);

    if (node->AnzSubNodes > 0) {
      // Auch die Subnodes muessen geloescht werden -> Die aktuellen
      // Saetze in einer Liste lesen
      //------------------------------------------------------------
      ParamBlock p;
      lmemset (&p,'\0',sizeof(p));
      p.AnzPars = 1;
      p.ptr[0] = GetGlobMem (sizeof(DWORD));
      *(DWORD FAR *) p.ptr[0] = pID;
      if (doID1) {
        p.AnzPars = 2;
        p.ptr[1] = GetGlobMem (sizeof(DWORD));
        *(DWORD FAR *) p.ptr[1] = pID1;
        }

      DBList FAR *recs = new DBList (td,0L,node->Selection,30,30,&p,FALSE);
      recs->SetOrder ("");

      for ( LPDBRECORD h = recs->GetFirst() ; h != NULL ; h = recs->GetNext (h) ) {
        // Und rekursiv weitermachen
        //--------------------------------
        for (int i = 0 ; i < node->AnzSubNodes ; i++)
          DeleteTransaction (node->rpSub[i],0L,h,stopOnTopNode);
        }

      delete recs;

      FreeGlobMem (p.ptr[0]);
      }

    // Loeschen der Saetze durch ein Excute Statement
    //------------------------------------------------
    int stmtLen = lstrlen(delpattern1) + lstrlen(td->GetName()) + lstrlen(delpattern2) + lstrlen(node->Selection) + 1 ;
    LPSTR delstmt = LPSTR(GetGlobMem (stmtLen));
    lstrcpy (delstmt,delpattern1);
    lstrcat (delstmt,td->GetName());
    lstrcat (delstmt,delpattern2);
    lstrcat (delstmt,node->Selection);

    if (doID1)
      Excute (delstmt,GetTransactionDLL(),&pID,sizeof(pID),VAR_LONG,&pID1,sizeof(pID1),VAR_LONG);
    else
      Excute (delstmt,GetTransactionDLL(),&pID,sizeof(pID),VAR_LONG);

    FreeGlobMem (delstmt);
    GetTableAdmin()->FreeTable (node->tRef.TableNr,node->tRef.Version);
    }
  }

void UpdateStatement (LPDBRECORD r,LPSTR ustmtbuffer,LPVOID FAR *params,int FAR *types,int FAR *size)
  {
  WORD v0;
  LPTABLEDEF td = r->GetTableDef (0,&v0);
  WORD KeySeg[MAX_PRIMARYSEGS] ;
  params[0] = params[1] = params[2] = NULL ;
  *ustmtbuffer = '\0' ;
  if (td->GetPrimKeySegs (KeySeg)) {
    for (int i = 0 ; i < MAX_PRIMARYSEGS ; i++) {
      if (KeySeg[i] != 0xFFFF) {
        WIN_ASSERT (i < 3);
        params[i] = r->Get(KeySeg[i]);
        size[i] = GetBlockSize(params[i]);
        LPVARDEF v = td->GetVarDef(KeySeg[i]);
        types[i] = v->mType ;
        char astmt[64];
        wsprintf (astmt,"%s = %%%d",LPSTR (v->GetName()),i + 1);
        if (i == 0)
          lstrcpy (ustmtbuffer,astmt);
        else {
          lstrcat (ustmtbuffer," AND ");
          lstrcat (ustmtbuffer,astmt);
          }
        }
      else
        break ;
      }
    }
  }

BOOL SetzeVersion (LPDBRECORD h,DWORD TableID,DWORD PrimKey,DWORD Version,DWORD RecordVersion,short fAussenStelle,BOOL GetVersion)
  {
  BOOL res = FALSE ;
  if (GetVersion) {
    h = Ask (SV,"TId = %1 AND SId = %2",
             &TableID,sizeof(TableID),VAR_LONG,
             &PrimKey,sizeof(PrimKey),VAR_LONG
            );
    }
  if (h != NULL) {
    h->Set (3,&Version,sizeof(Version));
    h->Set (4,&fAussenStelle,sizeof(fAussenStelle));
    
    Out (h,-1,DBCALLTYPE_STANDARDUPDATE,NULL,"TId = %1 AND SId = %2",
        &TableID,sizeof(TableID),VAR_LONG,
        &PrimKey,sizeof(PrimKey),VAR_LONG
        );
    }
  else {
    h = new DBRecord (SV);
    h->Set (1,&TableID,sizeof(TableID));
    h->Set (2,&PrimKey,sizeof(PrimKey));
    h->Set (3,&Version,sizeof(Version));
    h->Set (4,&fAussenStelle,sizeof(fAussenStelle));

    WIN_ASSERT (Out (h,-1,DBCALLTYPE_STANDARDINSERT,NULL,""));
    }

  delete h ;

  // Vermerken in der Fremddatenbank, dass die Replikation
  // funktioniert hat.
  //-------------------------------------------------------
  LPDBRECORD ra = new DBRecord (A2VFremd[fAussenStelle - 1]);
  ra->Set (0,&RecordVersion,sizeof(&RecordVersion));
  ra->Set (1,&AussenStelle,sizeof(AussenStelle));

  if (Out (ra,-1,DBCALLTYPE_STANDARDINSERT,NULL,"")) {
    // Der Fremdzugriff hat funktioniert -> Alles in Ordnung
    res = TRUE ;
    }
  else {
    // Eventuell existiert der Satz schon in der Fremddatenbank, 
    // das wird noch genauer ueberprueft
    LPDBRECORD ra1 = Ask (A2VFremd[fAussenStelle - 1],"RecordVersion = %1 AND AussenStelle = %2",
                          &RecordVersion,sizeof(&RecordVersion),VAR_LONG,
                          &AussenStelle,sizeof(AussenStelle),VAR_STRARR
                          ) ;
    if (ra1 == NULL) {
      // Probleme mit dem Fremddatenbankzugriff
      WIN_ASSERT_TEXT (FALSE,"Auf die Fremddatenbank kann nicht korrekt zugeriffen werden !");
      res = FALSE ;
      }
    else {
      delete ra1 ;
      res = TRUE ;
      }
    }

  delete ra ;

  return res ;
  }

BOOL CheckFileIn (BlobDesc FAR *bd,BOOL stopOnTopNode)
  {
  // Einlesen und Ueberprufung des Headers
  //---------------------------------------
  BOOL res = FALSE ;
  LPSTR buffer = LPSTR (GlobalLock (bd->hGmem));
  if ((bd->Size >= sizeof(RepBase)) && (lstrcmp (((RepBase FAR *)buffer)->Kennung,REPKENNUNG) == 0)) {
    // Ueberpruefen, ob Datensatz noch nicht in der Datenbank mit der Richtigen
    // Version vorhanden ist
    //-------------------------------------------------------------------------------
    WIN_ASSERT (IstAussenStelleAktiv (((RepBase FAR *)buffer)->AussenStelle));
    RepBase rb;
    lmemcpy (&rb,(RepBase FAR *)buffer,sizeof(rb));

    LPTABLEDEF tRoot = GetTableAdmin()->GetTableDef (RNodes[rb.RepNum]->tRef.TableNr,RNodes[rb.RepNum]->tRef.Version);
    LPDWORD tn = LPDWORD (t2iHash->GetData(tRoot->GetName()));

    LPDBRECORD h = Ask (SV,"TId = %1 AND SId = %2",
                  tn,sizeof(*tn),VAR_LONG,
                  &rb.PrimKey,sizeof(rb.PrimKey),VAR_LONG
                  );

    BOOL doIt;
    if (h != NULL) {
      doIt = ((!lmemcmp (&rb.AussenStelle,h->Get(4),sizeof(rb.AussenStelle))) ||
              (!lmemcmp (&rb.Version,h->Get(3),sizeof(rb.Version))));
      }
    else
      doIt = TRUE ;
    
    if (doIt) {
      BeginTransaction (FALSE);
      // Loeschen des Alten Baumes
      //----------------------------
      if ((rb.RepNum < AnzRepNodes - 1) &&
          (RNodes[rb.RepNum + 1]->tRef.TableNr == RNodes[rb.RepNum]->tRef.TableNr) &&
          (RNodes[rb.RepNum + 1]->updateModeIndex == 1) &&
          (RNodes[rb.RepNum]->updateModeIndex == 0))
        DeleteTransaction (RNodes[rb.RepNum + 1],rb.PrimKey,NULL,stopOnTopNode);
      else
        DeleteTransaction (RNodes[rb.RepNum],rb.PrimKey,NULL,stopOnTopNode);

      // Einfuegen des Neuen Baumes
      //------------------------------
      RecBase FAR *recb = (RecBase FAR *) (((RepBase FAR *)buffer) + 1);
      for (int i = 0 ; i < rb.AnzRecords ; i++) {
        LPTABLEDEF tn = GetTableAdmin ()->GetTableDef (recb->tRef.TableNr,recb->tRef.Version);
        LPDBRECORD r = new DBRecord (tn);
        VarBase FAR *vb = (VarBase FAR *) (recb + 1) ;

        for (int j = 0 ; j < recb->AnzVars ; j++) {
          r->Set (vb->VarID,vb + 1,vb->size);
          vb = (VarBase FAR *) (LPSTR (vb + 1) + vb->size) ;
          }

        if (!Out (r,-1,DBCALLTYPE_STANDARDINSERT,NULL,"")) {
          if (LastError () == UNIQUECONSTRAINEDFAILED) {
            // Quereinsteiger in den Baum -> Update
            //-------------------------------------
            LPVOID params[4];
            int partypes[4];
            int size[4];
            char ustmtbuffer[512];
            UpdateStatement (r,ustmtbuffer,params,partypes,size);
            Out (r,-1,DBCALLTYPE_STANDARDUPDATE,NULL,ustmtbuffer,
                        params[0],size[0],partypes[0],
                        params[1],size[1],partypes[1],
                        params[2],size[2],partypes[2]
                );
            }
          else
            WIN_ASSERT(FALSE);
          }

        if (recb->RecordVersion) {
          PrimKey k;
          r->CalcPrimKey (0,&k);
          res = SetzeVersion (NULL,
                  *(LPDWORD (t2iHash->GetData(tn->GetName()))),
                  *(LPDWORD (k.Data)),
                  recb->Version,
                  recb->RecordVersion,
                  rb.AussenStelle,
                  TRUE);
          }
        delete r ;
        GetTableAdmin ()->FreeTable (recb->tRef.TableNr,recb->tRef.Version);
        recb = (RecBase FAR *) vb ;
        }

      // Vermerken in der Fremddatenbank, dass die Replikation
      // funktioniert hat.
      //-------------------------------------------------------
      if (res = SetzeVersion (h,*tn,rb.PrimKey,rb.Version,rb.RecordVersion,rb.AussenStelle,FALSE))
        EndTransaction ();
      else
        AbortTransaction ();
      }
    else
      res = TRUE ;

    GetTableAdmin()->FreeTable (RNodes[rb.RepNum]->tRef.TableNr,RNodes[rb.RepNum]->tRef.Version);
    }
  return res;
  }

static char *CHECKINPATTERN = "%d Transaktionen eingearbeitet" ;
static DWORD TIdToDel[2],SIdToDel[2];
static int TToDel;
void PushToDelList (DWORD TId,DWORD SId)
  {
  WIN_ASSERT (TToDel < 2);
  TIdToDel[TToDel] = TId;
  SIdToDel[TToDel] = SId;
  TToDel ++ ;
  }
void DelFromList (int DontDelAtEnd)
  {
  for ( int i = 0 ; i < TToDel - DontDelAtEnd ; i++) {
    char delsql[256];
    wsprintf (delsql,"DELETE FROM C%d WHERE TId = %%1 AND SId = %%2",AussenStelle);
    Excute (delsql,GetTransactionDLL(),&TIdToDel[i],sizeof(TIdToDel[i]),VAR_LONG,
                                       &SIdToDel[i],sizeof(SIdToDel[i]),VAR_LONG);
    }
  i = 0 ;
  for ( int j = TToDel - DontDelAtEnd ; j < TToDel ; i ++ , j ++)
    TIdToDel[i] = TIdToDel[j] , SIdToDel[i] = SIdToDel[j] ;
  TToDel = i ;
  }
DLLExport void _export WINAPI CheckDBIn ()
  {
  IsInCheckIn = TRUE ;
  if (DoReplicate ()) {
    BOOL msgCreated = FALSE ;
    int tNum = 0;

    LoadRepNodes ();

    //
    // Durchsuchen des eigenen Directories nach entsprechenden Replikatorfiles
    //
    #ifdef WITH_DB
    ParamBlock p;
    lmemset (&p,'\0',sizeof(p));
    p.AnzPars = 0;

    DBList FAR *res = new DBList (C2[AussenStelle - 1],0L,"",30,30,&p,FALSE);
    res->SetOrder ("Prio,SId");

    for ( LPDBRECORD r = res->GetFirst (); r != NULL ; r = res->GetNext(r)) {
      if (!msgCreated)
        CreateMsgWin () , msgCreated = TRUE ;
      PaintMsgWnd (CHECKINPATTERN,tNum ++);

      BOOL doDel = CheckFileIn ((BlobDesc FAR *) r->Get(5),(*((DBINT FAR *) r->Get(4)) == UPDATEMODE_DELETE));

      if (doDel)
        PushToDelList (*(DWORD FAR *)r->Get(0),*(DWORD FAR *)r->Get(1));
      DelFromList (1);
      }

    DelFromList (0);

    delete res ;
    #else
    //
    // Durchsuchen des eigenen Directories nach entsprechenden Replikatorfiles
    //
    int j = AussenStellenIndex();
    static _find_t ft;
    static char Buffer1[256];
    lstrcpy (Buffer1,ed[j].ExternDir);
    lstrcat (Buffer1,"*.rep");
    int st = _dos_findfirst(Buffer1, _A_NORMAL, &ft);
    OFSTRUCT Of;
    while (st == 0) {
      if (!msgCreated)
        CreateMsgWin () , msgCreated = TRUE ;
      PaintMsgWnd (CHECKINPATTERN,tNum);

      char fname[256];
      lstrcpy (fname,ed[j].ExternDir);
      lstrcat (fname,ft.name);
      HFILE hf = OpenFile (fname,&Of,OF_READ | OF_SHARE_EXCLUSIVE);
      if (hf != HFILE_ERROR) {
        // Einarbeiten des Files
        //-----------------------------------------------------

        BOOL doDel = CheckFileIn (hf);
        PaintMsgWnd (CHECKINPATTERN,++ tNum);
        _lclose (hf);

        // Das File wird geloescht, danach nocheinmal mit einem
        // getfirst angefangen...
        //-----------------------------------------------------
        if (doDel) {
          OpenFile (fname,&Of,OF_DELETE);
          lstrcpy (Buffer1,ed[j].ExternDir);
          lstrcat (Buffer1,"*.rep");

          st = _dos_findfirst(Buffer1, _A_NORMAL, &ft);
          }
        else
          st = _dos_findnext(&ft);
        }
      else
        st = _dos_findnext(&ft);
      }
#endif
    if (msgCreated)
      DestroyMsgWin ();
    }
  IsInCheckIn = FALSE ;
  }

//---------------------------------------------------------------
// Holen des Tokens fuer einen Datensatz
//---------------------------------------------------------------
#define TOKEN_NOTOWNED   0
#define TOKEN_OWNED      1
#define TOKEN_AKTIVE     2

BOOL asDone[MAXAUSSEN];
void InitAsDone ()
  {
  for (int i = 0 ; i < MAXAUSSEN ; i++)
    asDone[i] = FALSE ;
  }

// Suchen des Index der naechsten noch nicht versuchten Aussenstelle,
// wobei, wenn moeglich, der Index der BestenAussenStelle genommen wird
short GetNextAussenStelle (short BesteAussenStelle)
  {
  // Untersuchen der BestenAussenStelle
  for (int i = 0 ; i < AnzahlExterne ; i++) {
    if (ed[i].Nummer == AussenStelle) continue ;
    if ((ed[i].Nummer == BesteAussenStelle) && (!asDone[i])) {
      asDone[i] = TRUE ;
      return i ;
      }
    }
  // Untersuchen der naechste freien AussenStelle
  for (i = 0 ; i < AnzahlExterne ; i++) {
    if (ed[i].Nummer == AussenStelle) continue ;
    if (!asDone[i]) {
      asDone[i] = TRUE ;
      return i ;
      }
    }
  // Nix mehr da
  return -1;
  }

#define DTWAIT  500L
static LONG TestTableID,TestSId,TestVersion;
static short TestAussenStelle;
#define TESTTIMER 467
BOOL CheckVersion ()
  {
  BOOL res ;
  HCURSOR oldCursor = SetCursor (LoadCursor (NULL,IDC_WAIT));

  CheckDBIn ();

  // Lesen der Version, vielleicht ist sie ja angekommen
  LPDBRECORD v = Ask (SV,"TId = %1 AND SId = %2",
                        &TestTableID,sizeof(TestTableID),VAR_LONG,
                        &TestSId,sizeof(TestSId),VAR_LONG
                    );

  if (v != NULL) {
    LONG lastVersion = *(LONG FAR *) v->Get (3);
    short lastAussenStelle = *(short FAR *) v->Get (4);
    if ((lastVersion == TestVersion) && (lastAussenStelle == TestAussenStelle)) {
      // Alles in Ordnung, die Wartebox kann geschlossen werden
      res = TRUE ;
      }
    else
      res = FALSE ;
    delete v;
    }
  else
    res = FALSE ;

  SetCursor (oldCursor);

  return res;
  }

DLLExport BOOL FAR PASCAL _export DlgProc (HWND hDlg, UINT message, WPARAM wP,
                                                               LPARAM lP)
  {
  BOOL res = FALSE;
  switch (message) {
    case WM_INITDIALOG :
      SetTimer (hDlg,TESTTIMER,1000L,NULL);
      break ;
    case WM_TIMER :
      if (wP == TESTTIMER) {
        if (CheckVersion ()) {
          KillTimer (hDlg, TESTTIMER);
          EndDialog (hDlg, TRUE) ;
          }
        res = TRUE ;
        }
      break ;
    case WM_COMMAND :
      CRACKER_VARS
      CRACK_MESSAGEsc

      switch (CRACKER_wID) {
        case IDCANCEL:
          // DeleteObject (hMyBitmap2);
          KillTimer (hDlg, TESTTIMER);
          EndDialog (hDlg, FALSE) ;
          return TRUE ;
        }
    }
  return res;
  }

DLLExport void _export WriteDataToNW (LPVOID Data,int Size);
BOOL WaitOnVersion (DWORD fNummer,DWORD tNum,DWORD pKey,short fremdAussenStelle)
  {
  TestTableID = tNum;
  TestSId = pKey;
  TestVersion = fNummer;
  TestAussenStelle = fremdAussenStelle;

  // WriteDataToNW (&fremdAussenStelle,sizeof(fremdAussenStelle));

  if (!CheckVersion ())
    return DialogBox (hLibInst,"DIALOG_3",GetActiveWindow(),DLGPROC(DlgProc));
  else
    return TRUE ;
  }

DLLExport LONG _export WINAPI GetDBToken (LPSTR TableName,LPVOID PrimKey,BOOL FAR *showLockedScreen)
  {
  DWORD res;

  *showLockedScreen = FALSE ;
  if (DoReplicate ()) {
    BOOL transaktionDone = FALSE ;
    short TVal;

    // Direkter Versuch
    //------------------------------------------------------------------
    WIN_ASSERT (GetBlockSize (PrimKey) == sizeof(LONG));
    LPDWORD tn = LPDWORD (t2iHash->GetData(TableName));
    WIN_ASSERT (tn != NULL);

    LPDBRECORD ownToken = Ask (T,"TId = %1 AND SId = %2",tn,sizeof(*tn),VAR_LONG,
                                                         PrimKey,GetBlockSize(PrimKey),VAR_LONG
                              );
    if (ownToken != NULL) {
      TVal = *(short FAR *) ownToken->Get (3);
      if (TVal == TOKEN_OWNED)
        res = *(DWORD FAR *) ownToken->Get(0);
      else
        res = 0L ;
      }
    else {
      TVal = -1 ;
      res = 0L ;
      }

    if (TVal < TOKEN_OWNED) {
      // Lesen der eigenen Version
      //------------------------------------------------------------------
      BOOL versionRead;
      LONG vNummer;
      short vAussenStelle;

      LPDBRECORD v = Ask (SV,"TId = %1 AND SId = %2",
                             tn,sizeof(*tn),VAR_LONG,
                             PrimKey,GetBlockSize(PrimKey),VAR_LONG
                         );
      if (v != NULL) {
        vAussenStelle = *(short FAR *) v->Get (4);
        vNummer = *(LONG FAR *) v->Get (3);
        versionRead = TRUE ;
        delete v;
        }
      else {
        vAussenStelle = -1;
        versionRead = FALSE ;
        vNummer = -1L;
        }

      // Lesen aller Fremddatenbanken und von dort die Version mit der 
      // eigenen Version vergleichen
      //------------------------------------------------------------------
      short zAussenStelle,bAussenStelle = vAussenStelle;
      short fremdAussenStelle;
      LPDBRECORD fremdToken = NULL;
      LONG fNummer;
      for ( InitAsDone() ; ((zAussenStelle = GetNextAussenStelle (bAussenStelle)) >= 0) ; ) {
        fremdToken = Ask (TFremd[zAussenStelle],"TId = %1 AND SId = %2",tn,sizeof(*tn),VAR_LONG,
                                                                        PrimKey,GetBlockSize(PrimKey),VAR_LONG
                         );
        LPDBRECORD fremdVersion = Ask (SVFremd[zAussenStelle],"TId = %1 AND SId = %2",
                                                              tn,sizeof(*tn),VAR_LONG,
                                                              PrimKey,GetBlockSize(PrimKey),VAR_LONG
                                      );
        if (fremdToken != NULL) {
          short fremdTVal = *(short FAR *) fremdToken->Get(3);
          if (fremdTVal == TOKEN_OWNED) {
            // Die Fremddatenbank hat den Token zum Abholen
            //------------------------------------------------------------
            if (fremdVersion != NULL) {
              fremdAussenStelle = *(short FAR *) fremdVersion->Get(4);
              if (fremdAussenStelle != AussenStelle) {
                fNummer = *(LONG FAR *) fremdVersion->Get(3);
                }
              else {
                // Die Fremddatenbank hat zwar das Token, hat den Satz jedoch
                // von mir bekommen und noch keinen Update durchgefuehrt!
                // -> Der Test kann gestartet werden.
                //-----------------------------------------------------------
                fNummer = -1;
                }
              delete fremdVersion;
              }
            else
              fNummer = -1;

            break ;
            }
          else if (fremdTVal == TOKEN_AKTIVE) {
            // Die Fremddatenbank hat den Token aktiv, es kann nix gemacht 
            // werden
            //------------------------------------------------------------
            *showLockedScreen = TRUE ;
            res = 0L;
            if (fremdVersion != NULL)
              delete fremdVersion;

            break ;
            }
          else {
            // Nix gewesen, es muss weitergesucht werden
            delete fremdToken ;
            fremdToken = NULL ;
            }
          }
        // Es muss weitergesucht werden
        if (fremdVersion != NULL) {
          bAussenStelle = *(short FAR *) fremdVersion->Get(4);
          delete fremdVersion;
          }
        else
          bAussenStelle = -1 ;
        }

      if (zAussenStelle == -1) {
        // Es wurde keine Aussenstelle gefunden, die ein Token besitzt ->
        // Bei sich selber darf das Token geholt werden !
        //
        // ACHTUNG:
        // --------
        //    Dies stellt eine kleine Sicherheitsluecke dar, da sich durch
        //    zeitlich unguenstiges Verhalten sich 2 Aussenstellen 
        //    gleichzeitig das Token holen koennten -> durch ein TOOL
        //    sollte sich eine Datenbank alle Token holen!
        //---------------------------------------------------------------
        if (!transaktionDone)
          BeginTransaction(FALSE) , transaktionDone = TRUE ;

        if (ownToken != NULL) {
          res = *(DWORD FAR *) ownToken->Get(0);
          short tval = TOKEN_AKTIVE;
          Excute ("UPDATE Token SET Value = %2 WHERE Nummer = %1",GetTransactionDLL(),&res,sizeof(res),VAR_LONG,
                                                                  &tval,sizeof(tval),VAR_STRARR
                 );
          }
        else {
          ownToken = new DBRecord (T);
          ownToken->Set(1,tn,sizeof(*tn));
          ownToken->Set(2,PrimKey,GetBlockSize(PrimKey));
          short tval = TOKEN_AKTIVE ;
          ownToken->Set(3,&tval,sizeof(tval));
          WIN_ASSERT (Out (ownToken,-1,DBCALLTYPE_STANDARDINSERT,&res,""));
          }
        }
      else {
        if (!*showLockedScreen) {
          WIN_ASSERT (fremdToken != NULL);
          // Es wurde eine Aussenstelle mit nicht aktivem Token gefunden
          //------------------------------------------------------------
          BOOL doChangeToken ;
          if ((fNummer != vNummer) && ((fNummer > 0L) || ((fNummer < 0L) && (vNummer < 0L))))
            // Version stimmt nicht ueberein -> Replikation abwarten
            //------------------------------------------------------
            doChangeToken = WaitOnVersion (fNummer,*tn,*(LONG FAR *) PrimKey,fremdAussenStelle);
          else
            // Version stimmt ueberein -> Token kann abgeholt werden
            //------------------------------------------------------
            doChangeToken = TRUE;

          if (doChangeToken) {
            // In einer Transaktion bei der Fremddatenbank das 
            // Token ruecksetzten und bei der eigenen setzten
            //---------------------------------------------------
            if (!transaktionDone)
              BeginTransaction(FALSE) , transaktionDone = TRUE ;

            short tfremdval = TOKEN_NOTOWNED;
            fremdToken->Set(3,&tfremdval,sizeof(tfremdval));
            WIN_ASSERT (Out (fremdToken,-1,DBCALLTYPE_STANDARDUPDATE,NULL,"Nummer = %1",fremdToken->Get(0),sizeof(LONG),VAR_LONG));

            if (ownToken != NULL) {
              res = *(DWORD FAR *) ownToken->Get(0);
              short tval = TOKEN_AKTIVE;
              Excute ("UPDATE Token SET Value = %2 WHERE Nummer = %1",GetTransactionDLL(),&res,sizeof(res),VAR_LONG,
                                                                      &tval,sizeof(tval),VAR_STRARR
                    );
              }
            else {
              ownToken = new DBRecord (T);
              ownToken->Set(1,tn,sizeof(*tn));
              ownToken->Set(2,PrimKey,GetBlockSize(PrimKey));
              short tval = TOKEN_AKTIVE ;
              ownToken->Set(3,&tval,sizeof(tval));
              WIN_ASSERT (Out (ownToken,-1,DBCALLTYPE_STANDARDINSERT,&res,""));
              }
            }
          else
            // Der Benutzer hats nicht abwarten koennen ->
            // keinen Schirm anzeigen, aber auch nicht freigeben
            //----------------------------------------------------
            res = 0L ;
          }
        delete fremdToken;
        }
      }
    else {
      if (TVal == TOKEN_AKTIVE) {
        // Irgendjemand vom eigenen System hat den Token aktiv
        //----------------------------------------------------
        *showLockedScreen = TRUE ;
        }
      }

    if (res > 0L) {
      // Eintragen, dass Token aktiv ist
      //------------------------------------------------------------------
      if (!transaktionDone)
        BeginTransaction(FALSE) , transaktionDone = TRUE ;

      if (TVal == TOKEN_OWNED) {
        // Update in der Token DB
        short tval = TOKEN_AKTIVE;
        Excute ("UPDATE Token SET Value = %2 WHERE Nummer = %1",GetTransactionDLL(),&res,sizeof(res),VAR_LONG,
                                                                &tval,sizeof(tval),VAR_STRARR
               );
        }

      // Insert in die AktiveToken DB
      LPDBRECORD n = new DBRecord (AT);
      n->Set (0,&res,sizeof(res),VAR_LONG);
      char nwAddress[32];
      GetNWAddress (nwAddress,sizeof(nwAddress));
      n->Set (1,nwAddress + 1,lstrlen(nwAddress));
      WIN_ASSERT (Out (n,-1,DBCALLTYPE_STANDARDINSERT,NULL,""));
      delete n ;
      }

    if (ownToken != NULL)
      delete ownToken;

    if (transaktionDone)
      EndTransaction ();
    }
  else
    res = 1L ;

  return res;
  }

//-----------------------------------------------
// Inaktivsetzten des zuletzt gelesenen Tokens
//-----------------------------------------------
DLLExport LONG _export WINAPI UnlockDBToken (LONG tnum)
  {
  if (DoReplicate ()) {
    short tval = TOKEN_OWNED ;
    Excute ("UPDATE Token SET Value = %2 WHERE Nummer = %1",GetTransactionDLL(),&tnum,sizeof(tnum),VAR_LONG,
                                                            &tval,sizeof(tval),VAR_STRARR
           );
    Excute ("DELETE FROM AktiveToken WHERE Token = %1",GetTransactionDLL(),&tnum,sizeof(tnum),VAR_LONG);
    }
  return 0L;
  }

//--------------------------------------------
// Inaktivsetzten aller eigenen Tokens
//--------------------------------------------
DLLExport void _export ClearMyTokens()
  {
  if (DoReplicate ()) {
    char nwaddress[32];
    GetNWAddress (nwaddress,sizeof(nwaddress));
    ParamBlock p;
    lmemset (&p,'\0',sizeof(p));
    p.AnzPars = 1;
    p.ptr[0] = GetGlobMem (lstrlen (nwaddress));
    lstrcpy (LPSTR(p.ptr[0]),nwaddress + 1);

    DBList FAR *res = new DBList (AT,0L,"NWAddress = %1",30,30,&p,FALSE);
    res->SetOrder ("NWAddress");
    short tval = TOKEN_OWNED ;
    for ( LPDBRECORD r = res->GetFirst (); r != NULL ; r = res->GetNext(r)) {
      Excute ("UPDATE Token SET Value = %2 WHERE Nummer = %1",GetTransactionDLL(),r->Get(0),sizeof(LONG),VAR_LONG,
                                                              &tval,sizeof(tval),VAR_STRARR
             );
      }
    FreeGlobMem (p.ptr[0]);
    delete res ;

    Excute ("DELETE FROM AktiveToken WHERE NWAddress = %1",GetTransactionDLL(),nwaddress + 1,lstrlen(nwaddress),VAR_STR);
    }
  }

