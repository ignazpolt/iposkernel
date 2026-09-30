////////////////////////////////////////////////////
//  Dialogeditor
////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/restool/rev/dialed.cpv   1.55   30 Apr 1999 18:35:52   Wolfgang  $
//  $Log:   P:/marille/clinicum/restool/rev/dialed.cpv  $
// 
//    Rev 1.55   30 Apr 1999 18:35:52   Wolfgang
// 1.) String-Handling funktioniert jetzt auch bei Funktionsparametern.
// 
//    Rev 1.54   28 Apr 1999 18:15:44   Wolfgang
// 1.) Strings werden jetzt (hoffentlich ueberall) richtig behandelt, solange
//     keine \" vorkommen, die keine sind (z.B.: "siehe \"ABC\"": kein Problem,
//     "\c:128\blau\c:0\": DA HAUT'S UNS GEWALTIG AUF DIE NASE!).
// 
//    Rev 1.53   26 Mar 1999 18:14:10   Wolfgang
// 1.) Sortierungs-Button auch bei Menubefehl mitschalten.
// 
//    Rev 1.52   05 Oct 1998 11:25:38   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.51   10 Feb 1998 18:25:12   Gerhold
// 
//    Rev 1.50   15 Dec 1997 17:37:10   Hannes
// Diverse Verbesserungen
// 
//    Rev 1.49   05 Nov 1997 08:57:20   Gerhold
// 32 Bit
// 
//    Rev 1.48   28 Aug 1997 16:26:12   gerhold
// kleiner 16-32-Bit Fehler
// 
//    Rev 1.47   28 Aug 1997 15:48:28   gerhold
// Umstellung 32 Bit
// 
//    Rev 1.46   21 Oct 1996 18:57:34   HANNES
// Fehlerkorrekturen Editor
// 
//    Rev 1.45   22 Aug 1996 16:35:24   MARTIN
// die (hoffentlich) letzte Verwendung der alten Tabellen ausgemerzt.
// 
//    Rev 1.44   02 Jul 1996 15:51:52   GERHOLD
// mehrzeilige Scriptbefehle verbessert. WM_COMMAND ... hilo
// 
//    Rev 1.43   26 Feb 1996 12:45:14   GERHOLD
// Der Raster funktioniert ein bisschen besser. Das Selektionsrechteck bekommt
// jetzt immer die richtige Groesse.
// 
//    Rev 1.42   02 Feb 1996 10:50:14   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.41   20 Nov 1995 12:33:14   HANNES
// 
//    Rev 1.40   18 Oct 1995 11:11:54   GERHOLD
// GetRect wird bei ListHeader, PaintBottom, SetButton nicht aufgerufen.
// 
//    Rev 1.39   16 Oct 1995 13:30:52   GERHOLD
// PT_HOTKEY (4 Bytes)
// 
//    Rev 1.38   27 Sep 1995 17:42:54   GERHOLD
// DefFrmField.Next = &BindInnerListToOutList   (so stimmts jetzt)
// 
//    Rev 1.37   16 Sep 1995 02:05:22   HANNES
// 
//    Rev 1.36   07 Sep 1995 09:03:56   HANNES
// 
//    Rev 1.35   27 Aug 1995 13:00:38   HANNES
// 
//    Rev 1.34   24 Aug 1995 00:16:46   HANNES
// Debuggerverbesserungen
// 
//    Rev 1.33   23 Aug 1995 11:05:08   GERHOLD
// 
//    Rev 1.32   21 Jul 1995 16:55:16   GERHOLD
// Jetzt werden bei der Auswertung der Parameter im Formular-Editor die
// Beistriche in den Strings richtig interpretiert (FindEndPar). Bravo Gerhold
// 
//    Rev 1.31   10 Jul 1995 19:57:20   GERHOLD
// ColorRect
// 
//    Rev 1.30   17 May 1995 11:33:50   HANNES
// Direkte Eingabe von Texten im Editor (vorlaufig)
// 
//    Rev 1.29   10 Apr 1995 10:43:22   GERHOLD
// Hoffentlich funktioniert jetzt die Mehrfachloeschung von Screen-Objekten
// 
//    Rev 1.28   04 Apr 1995 12:13:26   HANNES
// 
//    Rev 1.27   31 Mar 1995 13:11:42   HANNES
//  
// 
//    Rev 1.26   27 Mar 1995 10:37:52   GERHOLD
// DBCALL_Listen implementiert
// 
//    Rev 1.25   20 Mar 1995 08:44:42   HANNES
//  
// 
//    Rev 1.24   08 Mar 1995 09:12:58   GERHOLD
// 
//    Rev 1.23   24 Feb 1995 11:09:18   GERHOLD
// Numerierung der Dialog-Elemente wird etwas anders gezeichnet
// 
//    Rev 1.22   16 Feb 1995 12:38:28   GERHOLD
// Loeschen von Elementen im Formular-Editor war falsch
// 
//    Rev 1.21   02 Jan 1995 12:20:28   HANNES
// 
//    Rev 1.20   02 Jan 1995 09:29:32   GERHOLD
// Umstellung auf MDI
// 
//    Rev 1.18   17 Oct 1994 14:54:20   HANNES
// Tracing
// 
//    Rev 1.17   05 Oct 1994 08:48:10   HANNES
// Header in den Listen..
// 
//    Rev 1.16   14 Sep 1994 16:58:02   GERHOLD
// Erweiterungen fuer Statuszeile
// 
//    Rev 1.15   05 Sep 1994 18:54:50   GERHOLD
// ShowColumnList, ShowObjectList, ShowPMObjectList werden jetzt angezeigt
// 
//    Rev 1.14   05 Sep 1994 13:18:52   GERHOLD
// Up-Down-Control
// 
//    Rev 1.13   26 Aug 1994 15:59:02   GERHOLD
// ToolTime, EditShortInt
// 
//    Rev 1.12   10 Aug 1994 12:08:12   GERHOLD
// Hotkeys in RESTOOL
// 
//    Rev 1.11   09 Aug 1994 10:07:46   HANNES
// No change.
// 
//    Rev 1.10   08 Aug 1994 17:36:28   GERHOLD
// Doppelclick auf Elemente ermoeglicht
// 
//    Rev 1.9   05 Aug 1994 20:54:56   HANNES
// FrmTime
// 
//    Rev 1.8   05 Aug 1994 11:59:44   GERHOLD
// XYFromRect, BmpTextPushButton
// 
//    Rev 1.7   01 Aug 1994 15:36:44   GERHOLD
// Drag & Drop fuer Farben
// 
//    Rev 1.6   25 Jul 1994 10:43:14   HANNES
// 
//    Rev 1.5   25 Jul 1994 09:34:18   GERHOLD
// Drag&Drop fuer Formate
// 
//    Rev 1.4   14 Jul 1994 14:25:38   GERHOLD
// Readformat, fntDeleteAllFormats raus, da ins Hauptprogramm verlagert
// 
//    Rev 1.3   13 Jul 1994 21:13:56   HANNES
// Fehlerkorrektur bei der Schirmbearbeitung
// 
//    Rev 1.2   12 Jul 1994 18:15:58   HANNES
// 
//    Rev 1.1   12 Jul 1994 14:41:46   HANNES
// Erweiterungen
// 
//    Rev 1.0   24 Jun 1994 16:54:44   HANNES
// Neuuebernahme clinicum
//
#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#include "globmem.h"
#include "restool.hpp"
#include "hash.hpp"
#include "wonscrip.hpp"
#define MODULENUM 103
#include "winass.hpp"

#define JUST_EM
#include "dds.hpp"

#include "font.hpp"
#include "cfield.hpp"
int FieldHasCaret;
#include "toolbar.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"

#include "drdrop.hpp"

#include "template.hpp"

#include "font.hpp"
#include "sc2d.hpp"
#include "printer.hpp"
#include "paint.hpp"

#include "hlines.hpp"
#include "misc.hpp"
#include "statbar.hpp"
#include "blandmdi.hpp"
#include "msdntb.h"

#include "tbdef.hpp"

// Prototyp aus resadmin.hpp
extern DLLExport DWORD _export FAR PASCAL GetBitmapID (LPSTR Name);
extern DLLExport void _export FAR PASCAL ReadResContent ();
extern DLLExport void _export FAR PASCAL UnloadResContent ();

hash FAR *defines;

char _MyScreenName [32];
char _MyObjectName [32];
char *_DefBmpName = "Dialogs";
HWND hRefWnd;
HWND hOptWnd ;
WORD ActType;
WORD FrmType;
extern HWND hFrmWnd;
extern HINSTANCE MyInstance;
extern LPSHOWOBJECT firstShow;

#define  MOVE_INITIALIZE       0
#define  MOVE_LBUTTONDOWN      1
#define  MOVE_LBUTTONUP        2
#define  MOVE_MOUSEMOVEFIRST   3
#define  MOVE_MOUSEMOVE        4


/*--------------< Zeichenbearbeitung >---------------------*/
inline BOOL IsSpaceChar (char ch) 
  {
  return ((ch == ' ') || (ch == '\t'));
  }

inline BOOL IsCommentChar (char ch)
  {
  return (ch == '$');
  }

inline BOOL IsSingleChar (char ch) 
  {
  return ((ch == '(') || (ch == ')') || (ch == '{') || (ch == '}') ||
          (ch == '+') || (ch == '-') || (ch == '*') || (ch == '/') ||
          (ch == ',') || (ch == ';'));
  }

inline BOOL IsConstChar(char ch)
  {
  return ((ch == '[') || (ch == ']'));
  }

inline BOOL IsStrChar(char ch)
  {
  return (ch == '"');
  }

inline BOOL IsEscapeChar(char ch)
  {
  return (ch == '\\');
  }

LPSTR TextLine::FirstWord ()
  {
  for (LPSTR h = Text ; *h && IsSpaceChar (*h) ; h++) ;
  return ((*h) && (!IsCommentChar (*h))) ? h : NULL ;
  }

LPSTR _NextWord (LPSTR h)
  {
  if (IsConstChar(*h)) {
    h++ ;
    for ( ; *h && !IsConstChar (*h) ; h++) ;
    if (*h) h++ ;
    }
  else if (IsStrChar(*h)) {
    h++ ;
    for ( ; *h && (!IsStrChar (*h) || IsEscapeChar (*(h - 1))) ; h++) ;
    if (*h) h++ ;
    }
  else if (!IsSingleChar (*h))
    for ( ; *h && !IsSpaceChar (*h) && !IsSingleChar(*h) ; h++) ;
  else
    h ++ ;
  for ( ; *h && IsSpaceChar (*h) ; h ++) ;
  return ((*h) && (!IsCommentChar (*h))) ? h : NULL ;
  }

#define WS_INIT   0
#define WS_CONST  1
LPSTR TextLine::NextWord (LPSTR h)
  {
  return _NextWord (h);
  }

/*--------------< Templates >------------------*/
LPSTR ScipEndingDigits (LPSTR txt)
  {
  static char tmpname[64];
  if (txt != NULL) {
    lstrcpy (tmpname,txt);
    for (LPSTR h = tmpname + lstrlen(txt) - 1 ; h > tmpname ; h--) {
      if ((*h >= '0') && (*h <= '9')) *h = '\0';
      else                            break ;
      }
    return tmpname;
    }
  else
    return NULL;
  }

LPSTR DialogElem::GetObjectName()
  {
  return templ->GetObjectName(Param);
  }

void DialogElem::UpdatePar (WORD Id,LPSTR text)
  {
  WIN_ASSERT (AnzParams > Id);
  LPSTR n = LPSTR(GetGlobMem (lstrlen(text)+1));
  lstrcpy (n,text);
  if (Param[Id] != NULL) FreeGlobMem (Param[Id]);
  Param[Id] = n;
  }

extern LPDIALOGELEM firstElem;
void DialogElem::AddToList ()
  {
  LPDIALOGELEM FAR *h = &firstElem ;
  for ( ; *h != NULL ; h = &(*h)->Next) ;
  *h = this ;
  }

void DialogElem::PushParToParList (LPSTR t)
  {
  LPSTR FAR *n = (LPSTR FAR *) GetGlobMem ((AnzParams + 1) * sizeof(LPSTR));
  if (Param != NULL) {
    lmemcpy (n,Param,AnzParams * sizeof(LPSTR));
    FreeGlobMem (Param);
    }
  Param = n;
  if (t != NULL) {
    n[AnzParams] = LPSTR(GetGlobMem (lstrlen(t)+1));
    lstrcpy (n[AnzParams],t);
    }
  else
    n[AnzParams] = LPSTR(GetGlobMem (1));
  AnzParams ++;
  }

#define EP_INIT     0
#define EP_BOPEN    1
#define EP_CONST    2
#define EP_COMMENT  3
#define EP_STRING   4

LPSTR NextChar (LPSTR t,LPLINE FAR *h,LPLINE last)
  {
  t ++ ;
  if (*t) return t;
  else {
    if (*h == last) return NULL;
    else {
      *h = (*h)->Next ;
      return (*h)->Text ;
      }
    }
  }

static int stcount;
static int oldstate[8];
inline void InitStateBuffer() { stcount = 0; }
inline void PushState(int state) { oldstate[stcount++] = state ; }
inline int  PopState() { return oldstate[--stcount] ; }
LPSTR PushChar (LPSTR t,char ch)
  {
  int l = (t != NULL) ? lstrlen(t) + 2 : 2 ;
  LPSTR n = LPSTR(GetGlobMem (l));
  if (t != NULL) {
    lstrcpy (n,t);
    FreeGlobMem (t);
    }
  n[lstrlen(n)] = ch;
  return n;
  }

void RemoveSpaces (LPSTR h)
  {
  LPSTR e = h + lstrlen(h) - 1;
  for ( ; e > h ; e--) {
    if (*e == ' ') 
      *e = '\0';
    else
      break ;
    }
  }

LPSTR FindEndPar (LPSTR t,LPSTR FAR *res,LPLINE FAR *h,LPLINE last)
  {
  int state = EP_INIT ;
  int bopencount = 0;
  BOOL charfound = FALSE ;
  *res = NULL;
  InitStateBuffer();
  for ( ; t != NULL ; ) {
    switch (state) {
      case EP_INIT :
        if ((*t == ',') || (*t == ')')) {
          RemoveSpaces (*res);
          return t;
          }

        if (*t != ' ') charfound = TRUE ;
        if (charfound) {
          if (*t == '$') { PushState(EP_INIT) ; state = EP_COMMENT ; }
          else {
            *res = PushChar (*res,*t);
            if (*t == '[') 
              { PushState(EP_INIT) ; state = EP_CONST ; }
            else if (*t == '(') 
              { PushState(EP_INIT) ; state = EP_BOPEN ; bopencount = 1; }
            else if ((*t == '"') && (*(t-1) != '\\')) 
              { PushState(EP_INIT) ; state = EP_STRING; }
            }
          }
        t = NextChar (t,h,last) ;
        break ;
      case EP_COMMENT :
        if (t[1] == '\0') state = PopState() ;
        t = NextChar (t,h,last);
        break ;
      case EP_CONST : 
        // Absichtlich keine String-Pruefung. Dadurch ist zwar ["abc]def"] 
        // illegal, aber ["\c:128\rot\c:0\"] funktioniert (falls es der 
        // Compiler auch schluckt)
        if (*t == '$') { PushState(EP_CONST) ; state = EP_COMMENT ; }
        else {
          *res = PushChar (*res,*t);
          if (*t == ']') state = PopState() ;
          }
        t = NextChar (t,h,last);
        break ;
      case EP_BOPEN :
        if (*t == '$') { PushState(EP_BOPEN) ; state = EP_COMMENT ; }
        else {
          *res = PushChar (*res,*t);
          if (*t == '[') 
            { PushState(EP_BOPEN) ; state = EP_CONST ; }
          else if ((*t == '"') && (*(t-1) != '\\')) 
            { PushState(EP_BOPEN) ; state = EP_STRING; }
          else if (*t == ')') 
            bopencount -- ;
          if (bopencount == 0) state = PopState();
          }
        t = NextChar (t,h,last);
        break ;
      case EP_STRING :
        *res = PushChar (*res,*t);
        if ((*t == '"') && (*(t-1) != '\\')) 
          state = PopState() ;
        t = NextChar (t,h,last);
        break ;
      }
    }
  return NULL;
  }

LPSTR DialogElem::PushPar (LPSTR t,LPLINE FAR *h,LPLINE last)
  {
  LPSTR res = NULL;
  t = FindEndPar (t,&res,h,last);
  if (t != NULL) {
    PushParToParList (res);
    }
  if (res != NULL) FreeGlobMem (res);
  return t;
  }

void DialogElem::GetParCopy (WORD _AnzParams,LPSTR FAR *_Param)
  {
  AnzParams = _AnzParams ;
  Param = (LPSTR FAR *) GetGlobMem (_AnzParams * sizeof(LPSTR));
  for (WORD i = 0 ; i < _AnzParams ; i++) {
    Param[i] = LPSTR (GetGlobMem (GetBlockSize (_Param[i])));
    lmemcpy (Param[i],_Param[i],GetBlockSize (_Param[i]));
    }
  }

LPVOID DialogElem::GetIntMem ()
  {
  if (templ->GetPrivSize() == sizeof(LPVOID))
    return templ->GetIntMem (parblock);
  else
    return NULL;
  }

void DialogElem::Reconnect (LPVOID old)
  {
  if (old != NULL) {
    templ->Reconnect (parblock,old);
    }
  }

void DialogElem::DelMem ()
  {
  if (Param != NULL) {
    for (WORD i = 0 ; i < AnzParams ; i++)
      FreeGlobMem (Param[i]);
    FreeGlobMem (Param);
    }
  if (parblock != NULL) {
    FreeGlobMem (parblock);
    }
  Param = NULL;
  AnzParams = 0;
  parblock = NULL;
  }

DialogElem::~DialogElem ()
  {
  DelMem ();
  }

void DialogElem::MarkEnd (LPLINE h,WORD e)
  { 
  eLine = h ; 
  ePos = e ; 
  parblock = templ->CreateParBlock (AnzParams,Param);
  templ->AnalyseExtraInfo (Param);
  }

void DeleteElems()
  {
  for (LPDIALOGELEM h = firstElem ; h != NULL ; ) {
    LPDIALOGELEM n = h->Next;
    delete h ;
    h = n ;
    }
  firstElem = NULL;
  }

LPSTR PushToCommand (LPSTR c,LPSTR cp)
  {
  WORD size = lstrlen (cp) + 1 ;
  if (c != NULL) size += (GetBlockSize(c) - 1) ;
  LPSTR n = LPSTR(GetGlobMem (size));
  if (c != NULL) lstrcpy (n,c) , FreeGlobMem (c);
  lstrcat (n,cp);
  return n;
  }

LPSTR PushToCommand (LPSTR c,LPSTR cp,WORD cps)
  {
  WORD size = cps + 1 ;
  if (c != NULL) size += (GetBlockSize(c) - 1) ;
  LPSTR n = LPSTR(GetGlobMem (size));
  if (c != NULL) lstrcpy (n,c) , FreeGlobMem (c);
  lmemcpy (n+lstrlen(n),cp,cps);
  return n;
  }

LPSTR DialogElem::GetCommand ()
  {
  LPSTR h = PushToCommand (NULL,templ->TemplateName);
  h = PushToCommand (h," (");
  for (WORD i = 0 ; i < AnzParams ; i++) {
    h = PushToCommand (h,Param[i]);
    if (i < AnzParams - 1)
      h = PushToCommand (h,",");
    }
  h = PushToCommand (h,")");

  return h;
  }

LPSTR DialogElem::GetCommand (WORD StartParam, WORD EndParam, BOOL bFirstLine)
  {
  LPSTR h = NULL;

  // der Funktionsname wird nur einmal in der ersten Zeile geschrieben
  if (bFirstLine) {
    h = PushToCommand (NULL,templ->TemplateName);
    h = PushToCommand (h," (");
    }
    
  for (WORD i = StartParam ; i < EndParam ; i++) {
    h = PushToCommand (h,Param[i]);
    if (i < AnzParams - 1)
      h = PushToCommand (h,",");
    }
    
  if (EndParam == AnzParams)
    h = PushToCommand (h,")");

  return h;
  }


struct parblockHD {
  WORD fncID;
  WORD parSize;
  tool FAR *t;
  };

void DialogElem::GetRect (HWND hWnd,LPRECT r)
  {
  if (templ->GetEdType() == EDTYPE_FORM) {
    GetDevRect (this,r);
    }
  else {
    if (templ->GetPrivSize() == sizeof(LPVOID)) {
      if (parblock != NULL) {
        parblockHD FAR *h = (parblockHD FAR *) parblock;
        tool FAR *t = h->t;
        if (t != NULL)
          CopyRect (r,LPRECT(&t->ToolRect));
        else
          SetRectEmpty (r);
        }
      else
        SetRectEmpty (r);
      }
    else {
      if (hWnd)
        GetClientRect (hWnd,r);
      else
        SetRectEmpty (r);
      }
    }
  }

void DialogElem::Invalidate (HWND hWnd,BOOL erase)
  {
  RECT r;
  GetRect (hWnd,&r);
  InflateRect (&r,5,5);
  InvalidateRect (hWnd,&r,erase);
  }

BOOL DialogElem::MoveAllowed ()
  {
  return templ->MoveAllowed();
  }

void DialogElem::OnChar (char ch)
  {
  templ->OnChar (this,ch);
  }

BOOL DialogElem::P1Hit (LPPOINT pt)
  {
  POINT p1 ;
  if (templ->IsThere(PT_P1)) {
    templ->GetPointPar (this,PT_P1,&p1.x,&p1.y);
    }
  else {
    templ->GetIntPar (this,PT_X1,&p1.x);
    templ->GetIntPar (this,PT_Y1,&p1.y);
    }
  templ->ToAbsDevKoords (&p1.x,&p1.y);
  return ((pt->x >= p1.x - 4) && (pt->x <= p1.x + 4) &&
          (pt->y >= p1.y - 4) && (pt->y <= p1.y + 4));
  }

BOOL DialogElem::P1Allowed ()
  {
  return templ->P1Allowed();
  }

BOOL DialogElem::P2Hit (LPPOINT pt)
  {
  POINT p2 ;
  if (templ->IsThere(PT_P2))
    templ->GetPointPar (this,PT_P2,&p2.x,&p2.y);
  else {
    templ->GetIntPar (this,PT_X2,&p2.x);
    templ->GetIntPar (this,PT_Y2,&p2.y);
    }
  templ->ToAbsDevKoords (&p2.x,&p2.y);
  return ((pt->x >= p2.x - 4) && (pt->x <= p2.x + 4) &&
          (pt->y >= p2.y - 4) && (pt->y <= p2.y + 4));
  }

BOOL DialogElem::P2Allowed ()
  {
  return templ->P2Allowed();
  }

void DialogElem::InitializeMove (int FAR *x,int FAR *y,int FAR *x1,int FAR *y1)
  {
  templ->InitializeMove (this,parblock,x,y,x1,y1);
  }

void DialogElem::InitializeP1 (int FAR *x,int FAR *y)
  {
  templ->InitializeP1 (this,parblock,x,y);
  }

void DialogElem::InitializeP2 (int FAR *x,int FAR *y)
  {
  templ->InitializeP2 (this,parblock,x,y);
  }

void DialogElem::InitializeHeight (int FAR *h)
  {
  templ->InitializeHeight (this,h);
  }

void DialogElem::InitializeWidth (int FAR *w)
  {
  templ->InitializeWidth (this,w);
  }

void DialogElem::Move (int x,int y,int x1,int y1)
  {
  templ->Move (this,x,y,x1,y1);
  }

void DialogElem::SetP1 (int x,int y)
  {
  templ->SetP1 (this,x,y);
  }

void DialogElem::SetP2 (int x,int y)
  {
  templ->SetP2 (this,x,y);
  }

void DialogElem::SetWidth (int x)
  {
  if (x < 3) x = 3 ;
  templ->SetIntPar (PT_WIDTH,x,parblock,Param);
  templ->DoEdit (this,EM_PRIVATE1);
  }

void DialogElem::SetHeight (int y)
  {
  if (y < 3) y = 3 ;
  templ->SetIntPar (PT_HEIGHT,y,parblock,Param);
  templ->DoEdit (this,EM_PRIVATE1);
  }

BOOL DialogElem::Hit (LPPOINT pt)
  {
  RECT r;
  GetRect (NULL,&r);
  return PtInRect (&r,*pt);
  }

BOOL DialogElem::ChangeHeightAllowed()
  {
  return templ->HeightAllowed();
  }

BOOL DialogElem::ChangeWidthAllowed()
  {
  return templ->WidthAllowed();
  }

BOOL DialogElem::HeightHit (LPPOINT pt)
  {
  RECT r;
  GetRect (NULL,&r);
  int xh = (r.right + r.left) / 2;
  int yh = r.bottom;
  return ((pt->x >= xh - 4) && (pt->x <= xh + 4) &&
          (pt->y >= yh - 4) && (pt->y <= yh + 4));
  }

BOOL DialogElem::WidthHit (LPPOINT pt)
  {
  RECT r;
  GetRect (NULL,&r);
  int xw = r.right ;
  int yw = (r.top + r.bottom) / 2;
  return ((pt->x >= xw - 4) && (pt->x <= xw + 4) &&
          (pt->y >= yw - 4) && (pt->y <= yw + 4));
  }

inline void PaintTinyRect (HDC hDC,int x,int y)
  {
//  Rectangle (hDC,x-4,y-4,x+4,y+4);
  RECT rc;
  rc.left = x-4;
  rc.top = y-4;
  rc.right = x+4;
  rc.bottom = y+4;
  ExtTextOut (hDC, rc.left, rc.top, ETO_OPAQUE, &rc, NULL, 0, NULL);
  }

void DialogElem::PaintSelected (HWND hWnd,HDC hDC)
  {
  RECT r;
  GetRect (hWnd,&r);
//  HPEN   OldPen   = SelectObject (hDC,GetStockObject (NULL_PEN));
//  HBRUSH OldBrush = SelectObject (hDC,CreateSolidBrush (RGB(0,0,0x80)));

  COLORREF OldBack = SetBkColor (hDC, RGB(0,0,0x80));

  PaintTinyRect (hDC,r.left,r.top);
  PaintTinyRect (hDC,r.left,r.bottom);
  PaintTinyRect (hDC,r.right,r.bottom);
  PaintTinyRect (hDC,r.right,r.top);
  PaintTinyRect (hDC,r.left,(r.top+r.bottom)/2);
  PaintTinyRect (hDC,r.right,(r.top+r.bottom)/2);
  PaintTinyRect (hDC,(r.left+r.right)/2,r.top);
  PaintTinyRect (hDC,(r.left+r.right)/2,r.bottom);
//  DeleteObject (SelectObject (hDC,OldBrush));
//  SelectObject (hDC,OldPen);
  
  SetBkColor (hDC, OldBack);
  }

#define PARSTATE_INIT    0
#define PARSTATE_BOPEN   1
LPSTR NextParDsc (LPSTR h)
  {
  int state = PARSTATE_INIT;
  BOOL ready = FALSE ;
  for ( ; !ready ; ) {
    switch (state) {
      case PARSTATE_INIT :
        if (*h == '\0') ready = TRUE ;
        if (*h == ',') ready = TRUE ;
        if (*h == '[') state = PARSTATE_BOPEN ;
        break ;
      case PARSTATE_BOPEN :
        if (*h == '\0') ready = TRUE ;
        if (*h == ']') state = PARSTATE_INIT ;
        break ;
      }
    if (!ready) h++;
    }
  if (*h == ',') h++;
  return h;
  }

WORD GetParType (LPSTR Name)
  {
  static struct {
    WORD  Type;
    LPSTR Name;
    } ParNameToParType[] = {
    { PT_OBJADDRESS , "oadd" } ,
    { PT_INT        , "int" } ,
    { PT_STRING     , "string" } ,
    { PT_UNKNOWN    , "void" } ,
    { PT_WIDTH      , "w" } ,
    { PT_HEIGHT     , "h" } ,
    { PT_X          , "x" } ,
    { PT_Y          , "y" } ,
    { PT_BX         , "bx" } ,
    { PT_BY         , "by" } ,
    { PT_BITMAP     , "bitmap" } ,
    { PT_DEC        , "dec" } ,
    { PT_POINT      , "point" } ,
    { PT_COLORVAR   , "colorvar" } ,
    { PT_P1         , "p1" } ,
    { PT_P2         , "p2" } ,
    { PT_X1         , "px1" } ,
    { PT_Y1         , "py1" } ,
    { PT_X2         , "px2" } ,
    { PT_Y2         , "py2" } ,
    { PT_WMF        , "bild" } ,
    { PT_FORMAT     , "format" } ,
    { PT_HOTKEY     , "shortcut" } ,
    { PT_TEXT       , "text" }
    };
  #define ANZTYPES  (sizeof(ParNameToParType) / sizeof(ParNameToParType[0]))
  for (int i = 0 ; i < ANZTYPES ; i++)
    if (mystrcmp (Name,ParNameToParType[i].Name)) return ParNameToParType[i].Type;

  WIN_ASSERT(FALSE);
  return PT_UNKNOWN;
  }

LPPARTEMPLATE PushToParTemplate (LPPARTEMPLATE pt,WORD Type)
  {
  LPPARTEMPLATE n;
  if (pt == NULL) 
    n = LPPARTEMPLATE (GetGlobMem (sizeof(*pt)));
  else {
    n = LPPARTEMPLATE (GetGlobMem (sizeof(*pt) + pt->AnzPars * sizeof(WORD)));
    lmemcpy (n,pt,GetBlockSize(pt));
    FreeGlobMem (pt);
    }
  pt = n;
  pt->p[pt->AnzPars] = Type;
  pt->AnzPars ++ ;
  return pt;
  }

static _EdTemplate *firstTemplate;

static _PushButton PushButton ;
static _CheckButton CheckButton ;
static _TextPushButton TextPushButton ;
static _TextCheckButton TextCheckButton ;
static _TextRadioButton TextRadioButton ;
static _ComboButton ComboButton ;
static _UpDown UpDown ;
static _ToolEdit ToolEdit ;
static _ToolZoom ToolZoom ;
static _ToolPage ToolPage ;
static _ToolDate ToolDate ;
static _ToolFloat ToolFloat ;
static _GroupBox GroupBox ;
static _StaticTool StaticTool ;
static _lShowList lShowList ;
static _StaticBitmap StaticBitmap ;
static _Line3D Line3D ;
static _ColorLine ColorLine ;
static _ColorRect ColorRect ;
static _ActionBox ActionBox ;
static _FlapMap FlapMap ;
static _ToolPwd ToolPwd ;
static _PushCheckButton PushCheckButton ;
static _TransparentBitmap TransparentBitmap ;
static _AnimationBitmap AnimationBitmap ;
static _ToolBEdit ToolBEdit ;
static _BmpFloat BmpFloat ;
static _ShowPermList ShowPermList ;
static _ShowStringList ShowStringList ;
static _ShowColumnList ShowColumnList ;
static _ShowObjectList ShowObjectList ;
static _ShowMPObjectList ShowMPObjectList ;
static _ExternDocument ExternDocument ;
static _XYFromRect XYFromRect;
static _BmpTextPushButton BmpTextPushButton;
static _ToolTime ToolTime;
static _ToolShortInt ToolShortInt;
static _ToolLongInt ToolLongInt;
static _ToolMoney ToolMoney;
static _CreateScreen CreateScreen ;
static _PaintStdHeader PaintStdHeader ;
static _PaintFullHeader PaintFullHeader ;
static _DBCallStringList DBCallStringList;
static _DBCallColumnList DBCallColumnList;
static _DBCallObjList DBCallObjList;
static _DBCallMPObjList DBCallMPObjList;
static _PaintFullButton PaintFullButton;
static _PaintStdButton PaintStdButton;
static _SetButtons SetButtons;
static _BindInnerListToOutList BindInnerListToOutList ;

static _DefFrmField DefFrmField ;
static _DefFrmDate DefFrmDate ;
static _DefFrmTime DefFrmTime ;
static _DefFrmDec DefFrmDec ;
static _DefFrmShort DefFrmShort ;
static _DefFrmLong DefFrmLong ;
static _DefFrmMoney DefFrmMoney ;
static _DefFrmSLDec DefFrmSLDec ;
static _DefFrmStrList DefFrmStrList ;
static _DefFrmLine DefFrmLine ;
static _DefFrmImage DefFrmImage ;
static _Trc_DefCont Trc_DefCont ;
static _Trc_DefPattern Trc_DefPattern ;
static _Trc_DefmPattern Trc_DefmPattern ;
static _Trc_DefLine Trc_DefLine ;
static _DefFrmSozNr DefFrmSozNr ;
static _DefFrmDevDec DefFrmDevDec ;
static _DefCheckBox DefCheckBox ;
static _DefFrmShortStrList DefFrmShortStrList ;
static _Trc_DefArc Trc_DefArc ;
static _DefPattern DefPattern ;
static _DefFrmTab DefFrmTab ;
static _DefFrmTabField DefFrmTabField ;
static _DefTabDecField DefTabDecField ;
static _DefFrmTabShortStrList DefFrmTabShortStrList ;
static _DefTabFlagField DefTabFlagField ;
static _DefCheckField DefCheckField ;
static _DefTabCheckField DefTabCheckField ;
static _DefFrmStrDivList DefFrmStrDivList ;
static _DefTabDate DefTabDate ;
static _DefFrmTabStrList DefFrmTabStrList ;
static _DefTabColDec DefTabColDec ;
static _DefFrmSlantField DefFrmSlantField ;
static _DefFrmSlantDec DefFrmSlantDec ;
static _DefFrmSlantSLDec DefFrmSlantSLDec ;
static _DefMovePattern DefMovePattern ;
static _DefFrmDefDec DefFrmDefDec ;
static _DefFrmMultiField DefFrmMultiField ;
static _DefTrcImage DefTrcImage ;
static _DefFrmStaticBitmap DefFrmStaticBitmap ;
static _DefActivationRegion DefActivationRegion ;
static _DefFrmBField DefFrmBField ;
static _Trc_DefRectangle Trc_DefRectangle ;

static GETDATA         ctgd;
static SETDATA         ctsd;
static SETCONNECTION   ctsc;
static CLEARCONNECTION ctcc;
static CALLCOMMAND     ctccmd;
static GETRESOURCE     ctgs;
static GETEXTFUNC      ctgf;
static ISUPDATEFROM    ciuf;
static EDITCALLBACK    edc;
static GETVARSIZE      edg;
static FREEPRIVDATA    frp;

struct ETBData {
  DialogElem FAR *e;
  };

hash *objHash;      // Hashtabelle mit den Objekt - Zeigern, Zugriff per Namen
LPVOID MyGetData (LPDIALOGELEM h,WORD Id)
  {
  switch (h->templ->pt->p[Id]) {
    case PT_OBJADDRESS :
      return (objHash != NULL) ? objHash->GetData 
        (ScanString(h->Param[Id])) : NULL ;
      break ;
    case PT_STRING :
    case PT_TEXT :
      {
      BOOL isConst;
      LPSTR res = ScanString (h->Param[Id],&isConst);
      if (isConst) return res;
      else         return NULL;
      }
      break ;
    case PT_POINT :
    case PT_P1 :
    case PT_P2 :
      return ScanPoint (h->Param[Id]);
      break ;
    case PT_COLORVAR :
    case PT_HOTKEY :
    case PT_X :
    case PT_Y :
    case PT_X1 :
    case PT_X2 :
    case PT_Y1 :
    case PT_Y2 :
    case PT_INT :
    case PT_FORMAT :
    case PT_WIDTH :
    case PT_HEIGHT :
    case PT_BX :
    case PT_BY :
      {
      return ScanIntVar (h->Param[Id]);
      }
      break ;
    case PT_DEC :
      {
      return ScanDecVar (h->Param[Id]);
      }
      break ;
    }
  return NULL;
  }

DLLExport LPVOID _export FAR PASCAL ETBGetData (LPVOID PrivData,DWORD Id)
  {
  ETBData FAR *d = (ETBData FAR *) PrivData;
  return MyGetData (d->e,WORD(Id));
  }

DLLExport int _export FAR PASCAL ETBGetVarSize (LPVOID PrivData,DWORD Id)
  {
  return -1;
  }

DLLExport void _export FAR PASCAL ETBFreePrivData (LPVOID PrivData)
  {
  }

DLLExport BOOL _export FAR PASCAL ETBIsUpdateFrom (LPVOID PrivData,DWORD Id)
  {
  return FALSE ;
  }

VOID MySetData (LPDIALOGELEM h,WORD Id,LPVOID Data,int size,LPVOID Cmd)
  {
  switch (h->templ->pt->p[Id]) {
    case PT_OBJADDRESS :
      {
      if (objHash == NULL) objHash = new hash (117,STRKEY);
      LPSTR name = ScanString (h->Param[Id]);
      LPVOID x = objHash->GetData (name);
      if (x != NULL) objHash->DelData (name);
      if (Data != NULL)
        objHash->SetData (name,Data,size);
      }
      break ;
    case PT_HOTKEY :
      if (Data != NULL) {
        char outstr[32];
        wsprintf (outstr,"%luL",*(LPLONG(Data)));
        h->UpdatePar (WORD(Id),outstr);
        }
      break ;
    }
  }

DLLExport VOID _export FAR PASCAL ETBSetData (LPVOID PrivData,DWORD Id,LPVOID Data,int size,LPVOID Cmd)
  {
  ETBData FAR *d = (ETBData FAR *) PrivData;
  MySetData (d->e,WORD(Id),Data,size,Cmd);
  }

DLLExport VOID _export FAR PASCAL ETBSetConnection (LPVOID PrivData,DWORD Id,LPVOID Cmd)
  {
  }

DLLExport VOID _export FAR PASCAL ETBClearConnection (LPVOID PrivData,DWORD Id,LPVOID Cmd)
  {
  }

DLLExport VOID _export FAR PASCAL ETBCallCommand (LPVOID PrivData,DWORD CmdOffset,LPVOID addr)
  {
  }

DLLExport GLOBALHANDLE _export FAR PASCAL ETBGetResource (DWORD Id)
  {
  DWORD DataSize;
  return ReadResourceData (Id,&DataSize);
  }


void DrawHeaderFrame (HDC hDC, int i, RECT r, LPDIALOGELEM stdhd, int TextOffset)
  {
  RECT rc1, rc2;

  if ((TextOffset) < int(stdhd->AnzParams)) {
    LPSTR txt = ScanString (stdhd->Param[TextOffset]);  // HeaderText
    ExtTextOut (hDC, r.left+100, r.top, ETO_CLIPPED, &r, txt, 
                lstrlen(txt), NULL);
    }

  rc1  = r;
  LPtoDP (hDC, LPPOINT(&rc1), 2);
  rc2 = rc1;

  if (i == 0)
    rc1.left--;
  rc1.top--;

  if (i > 0) {
    rc2.left += 2;
    rc1.left += 1;
    }
  rc2.right -= 1;
  rc1.right += 1;
  rc2.bottom -= 2;
  DPtoLP (hDC, LPPOINT(&rc1), 2);
  DPtoLP (hDC, LPPOINT(&rc2), 2);

  // das wird das schwarze umgebende Rechteck
  HPEN OldPen = (HPEN)SelectObject (hDC, GetStockObject(BLACK_PEN));
  HBRUSH OldBrush = (HBRUSH)SelectObject (hDC, GetStockObject(NULL_BRUSH));
  Rectangle (hDC, rc1.left, rc1.top, rc1.right, rc1.bottom);
  SelectObject (hDC, OldBrush);
    
  OldPen = (HPEN)SelectObject (hDC, GetStockObject(WHITE_PEN));
  MoveToEx (hDC, rc2.right, rc2.top, NULL);
  LineTo (hDC, rc2.left, rc2.top);
  LineTo (hDC, rc2.left, rc2.bottom);
  SelectObject (hDC, OldPen);

  OldPen = (HPEN)SelectObject (hDC, CreatePen(PS_SOLID, 0, RGB(0x80, 0x80, 0x80)));
  LineTo (hDC, rc2.right, rc2.bottom);
  LineTo (hDC, rc2.right, rc2.top);
  DeleteObject (SelectObject (hDC, OldPen));
  }

#define ANZZUGRIFF_ID 16
#define ANZZUGRIFF_ID_DBCALL  14
#define TYPE_STRINGLIST   0
#define TYPE_OBJECTLIST   1
#define TYPE_INVALIDLIST  2
#define HEADER_RATIO  12 / 10
void PaintNums (HWND hWnd,HWND hPaintWnd,HDC hDC);
HWND OutWnd;
static BOOL doPaintNums;

DLLExport LONG _export FAR PASCAL LstShowProc (HWND hWnd,unsigned msg,WPARAM wP,LPARAM lP)
  {
  LONG RetVal = 0;
  switch (msg) {
    case WM_PAINT :
      {
      PAINTSTRUCT ps;
      HDC hDC = BeginPaint (hWnd, &ps) ;
      RECT r, rc;
      GetClientRect (hWnd,&r);
      BOOL done = FALSE ;

      LPDIALOGELEM exttool = LPDIALOGELEM (GetWindowLong (hWnd,GWL_EXTTOOLPTR));
      LPDIALOGELEM stdhd = LPDIALOGELEM (GetWindowLong (hWnd,GWL_HEADERPTR));

      if (stdhd != NULL) {
        int ListType;
        int Format;
        int AnzColumns;
        int AnzParams;
        int FormatId;
      
        if ((exttool->templ->GetToolType() == DOEXTERN_SHOWSTRINGLIST) ||
            (exttool->templ->GetToolType() == DOEXTERN_SHOWCOLUMNLIST) ||
            (exttool->templ->GetToolType() == DOEXTERN_DBCALL_STRINGLIST) ||
            (exttool->templ->GetToolType() == DOEXTERN_DBCALL_COLUMNLIST)) 
           ListType = TYPE_STRINGLIST;
        else   
        if  ((exttool->templ->GetToolType() == DOEXTERN_SHOWOBJECTLIST) ||
             (exttool->templ->GetToolType() == DOEXTERN_SHOWMPOBJECTLIST) ||
             (exttool->templ->GetToolType() == DOEXTERN_DBCALL_OBJLIST) ||
             (exttool->templ->GetToolType() == DOEXTERN_DBCALL_MPOBJLIST))
           ListType = TYPE_OBJECTLIST;
        else
          ListType = TYPE_INVALIDLIST;   

        if (ListType == TYPE_STRINGLIST) {
          if ((exttool->templ->GetToolType() == DOEXTERN_DBCALL_STRINGLIST) ||
              (exttool->templ->GetToolType() == DOEXTERN_DBCALL_COLUMNLIST)) {
            if (exttool->AnzParams > 15) {
              int AnzZugriffe = int (ScanInt (exttool->Param[ANZZUGRIFF_ID_DBCALL]));
              FormatId = AnzZugriffe + 15 ;
              }
            else
              ListType = TYPE_INVALIDLIST;
            }
          else {
            if (exttool->AnzParams > 18) {
              int AnzZugriffe = int (ScanInt (exttool->Param[ANZZUGRIFF_ID]));
              FormatId = AnzZugriffe + 18 ;
              }
            else
              ListType = TYPE_INVALIDLIST;
            }
          if ((ListType == TYPE_STRINGLIST) && (exttool->AnzParams > WORD(FormatId+1))) {   // ab jetzt kommen Spalten
            Format = int (ScanInt (exttool->Param[FormatId]));
            AnzColumns = int (ScanInt (exttool->Param[FormatId+1]));
            AnzParams = exttool->AnzParams;
            }
          else
            ListType = TYPE_INVALIDLIST;
          } 
        if (ListType == TYPE_OBJECTLIST) {
          Format = int (ScanInt (stdhd->Param[1]));
          AnzColumns = (stdhd->AnzParams-2) / 2;
          AnzParams = stdhd->AnzParams;
          }
              
        if (ListType != TYPE_INVALIDLIST) {
          PaintContext pc;
          pc.SetDC (hDC);
          double cfact;
          GetResolutionCF (&cfact);
          pc.LogicalTwips (0,0,float(cfact));

          LPFORMATMETRIC fmt = GetFormatMetrics (0,MAPTYPE_TYPOGRAPHIC,Format);
          int LogHeight = fmt->yHeight;

          HFONT oldFont = (HFONT)SelectObject (hDC,
                            GetFontHandle (0,MAPTYPE_TYPOGRAPHIC,Format,255));
          SetTextAlign (hDC,TA_TOP | TA_LEFT);
          COLORREF OldBack = SetBkColor (hDC, RGB(0xC0, 0xC0, 0xC0));

          int top    = pc.YPHYStoLOG (r.top);
          int bottom = pc.YPHYStoLOG (r.bottom);

          // grauen Hintergrund des Headers zeichnen
          rc.left = 0;
          rc.right = pc.XPHYStoLOG (r.right);
          rc.top = top;
          rc.bottom = LogHeight * HEADER_RATIO;
          ExtTextOut (hDC, rc.left, rc.top, ETO_CLIPPED | ETO_OPAQUE, &rc, 
                      NULL, 0, NULL);

          int cindex;
          int x0 = 0;
          if (ListType == TYPE_STRINGLIST) 
            cindex = FormatId + 3 ; // Position der Spalten im Scriptbefehl
          else
            cindex = 2;
            
          done = TRUE ;
          for (int i = 0 ; i < AnzColumns ; i++) {
            if (i > 0) {              // mehr als eine Spalte ?
              MoveToEx (hDC,x0,top, NULL);    // dann Linien zeichnen
              LineTo (hDC,x0,bottom);
              }

            rc.left = x0;
            rc.top = top;
            rc.bottom = LogHeight * HEADER_RATIO;
            if (AnzParams > cindex) {
              if (ListType == TYPE_STRINGLIST)
                x0 += int (ScanInt (exttool->Param[cindex]));  // erhoehe x0 um die naechste Spalte
              else
                x0 += int (ScanInt (stdhd->Param[cindex+1]));  // erhoehe x0 um die naechste Spalte
              }
            else
              x0 = pc.XPHYStoLOG (r.right);                  // so, ich bin am Ende

            rc.right = x0;
            if (ListType == TYPE_STRINGLIST)
              DrawHeaderFrame (hDC, i, rc, stdhd, i+1);
            else  
              DrawHeaderFrame (hDC, i, rc, stdhd, i*2+2);

            cindex += 2;   // weiter zur naechsten Spalte
            }  // for

            if (AnzColumns > 1) {
              MoveToEx (hDC, x0, top, NULL);
              LineTo (hDC, x0, bottom);

              rc.left = x0;
              rc.right = pc.XPHYStoLOG (r.right);
              rc.top = top;
              rc.bottom = LogHeight * HEADER_RATIO;
              if (ListType == TYPE_STRINGLIST)
                DrawHeaderFrame (hDC, i, rc, stdhd, i+1);
              else  
                DrawHeaderFrame (hDC, i, rc, stdhd, i*2+2);
              }

            SetBkColor (hDC, OldBack);
            SelectObject (hDC, oldFont);
            pc.ResetMap ();
            }  // if (ListType != TYPE_INVALIDLIST)
          }  // if (stdhd != NULL)
        
      if (!done) {
        MoveToEx (hDC,r.left,r.top, NULL);
        LineTo (hDC,r.right,r.bottom);
        MoveToEx (hDC,r.left,r.bottom, NULL);
        LineTo (hDC,r.right,r.top);
        }
      if (doPaintNums)
        PaintNums (OutWnd,hWnd,hDC);
      EndPaint (hWnd, &ps) ;
      }
      break ;
    case WM_LBUTTONDOWN :
      {
      HILOCHUNK hilo;
      MAKECHUNKsc (hilo, DDSLIST_LBUTTON, hWnd);

#ifdef WIN32
      long WindowID = GetWindowLong (hWnd,GWL_ID);
#else
      WORD WindowID = GetWindowWord (hWnd,GWW_ID);
#endif

      SendMessage (GetParent(hWnd),
                   WM_COMMAND,
                   WPARAM(WindowID),
                   HILOCHUNKPARAM(hilo)
                  );
      }
      break ;
    default :
      RetVal = DefWindowProc (hWnd,msg,wP,lP);
    }
  return RetVal;
  }

void RegisterTestWnd()
  {
  static BOOL Registered;
  if (!Registered) {
    WNDCLASS wndclass;
    wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
    wndclass.lpfnWndProc   = LstShowProc ;
    wndclass.cbClsExtra    = 0 ;
    wndclass.cbWndExtra    = 5 * sizeof(LPVOID) ;
    wndclass.hInstance     = MyInstance ;
    wndclass.hIcon         = NULL ;
    wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
    wndclass.hbrBackground = (HBRUSH)GetStockObject (WHITE_BRUSH) ;
    wndclass.lpszMenuName  = NULL ;
    wndclass.lpszClassName = "LSTTEST" ;

    RegisterClass (&wndclass) ;
    Registered = TRUE ;
    }
  }

static int testlistid = 0x8000;
typedef ExternTool FAR *LPEXTERNTOOL;
DLLExport void _export FAR PASCAL TestList (
                                      LPVOID param,WORD Action,
                                      LPDEPAR p
                                  )
  {
  static LONG oldHeaderPtr = 0;
  static LPDIALOGELEM oldExternTool;
  RegisterTestWnd();
  switch (Action) {
    case DO_LOAD  :
      {
      ETBData FAR *d = (ETBData FAR *)p->load.privData;
      p->load.hWnd = CreateWindow ("LSTTEST",
                                    "",
                                    WS_CHILDWINDOW | WS_VISIBLE ,
                                    p->load.x,p->load.y,p->load.w,p->load.h,
                                    p->load.hWParent,
                                    (HMENU)testlistid++,
                                    MyInstance,
                                      NULL
                                  );
      d->e->hExtWnd = p->load.hWnd;
      SetWindowLong (d->e->hExtWnd,GWL_EXTTOOLPTR,LONG(d->e));
      if (d->e == oldExternTool)
        SetWindowLong (d->e->hExtWnd,GWL_HEADERPTR,oldHeaderPtr);
      oldExternTool = NULL;
      }
      break ;
    case DO_SETCONNECTION :
      {
      }
      break ;
    case DO_GETHELP :
      {
      p->gethelptext.helpText = NULL;
      }
      break ;
    case DO_UPDATE :
      {
      }
      break ;

    case DO_RESET :
      {
      ETBData FAR *d = (ETBData FAR *) p->reset.privData;
      oldHeaderPtr = GetWindowLong (d->e->hExtWnd,GWL_HEADERPTR);
      oldExternTool = d->e ;
      DestroyWindow (d->e->hExtWnd);
      }
      break ;
    }
  }

DOEXTERN TestListptr ()
  {
  return DOEXTERN (MakeProcInstance (FARPROC(TestList),MyInstance));
  }

DLLExport DOEXTERN _export FAR PASCAL ETBGetExtFunc (WORD FncNmbr,DOEXTERN old)
  {
  if (old != NULL) {
    FreeProcInstance ((FARPROC)old);
    return NULL;
    }
  else {
    return TestListptr ();
    }
  }

POINT ptStart;
void ScrollPTStart (int dx,int dy)
  {
  ptStart.x += dx;
  ptStart.y += dy;
  }

//-----------------------------------
// Liste aller selektierten Elemente
//-----------------------------------
struct FAR SelElem {
  SelElem FAR *Next;
  LPDIALOGELEM elem;
  int   xOld,yOld;
  int   x1Old,y1Old;
  
  RECT rcElem;
  void Move (HWND hWnd, int xn, int yn, short MoveState = MOVE_MOUSEMOVE/*BOOL EndMove = FALSE*/);
  void SetWidth (int w);
  void UpdateRect () { GetDevRect(elem, &rcElem); }
  };
typedef SelElem FAR *LPSELELEM;
LPSELELEM selList;

extern void toDev (LPPOINT pt);

void toDevKoord (LPPOINT pt)
  {
  if (hFrmWnd != 0) {
    toDev (pt);
    }
  else {
    double baseunit;
    GetBaseUnit (&baseunit);
    pt->x = int (double (pt->x) * baseunit) ;
    pt->y = int (double (pt->y) * baseunit) ;
    }
  }
//---------------------------------------------------------------------------
// verschieben des Rechtecks, welches das Element symbolisiert
//---------------------------------------------------------------------------
void SelElem::Move (HWND hWnd, int xn, int yn, short MoveState)
  {
  HDC hDC = GetDC (hWnd);

  // beim allerersten mal das Rechteck neu holen
  if ((MoveState == MOVE_MOUSEMOVEFIRST) ||
      (MoveState == MOVE_INITIALIZE))
    elem->GetRect (hWnd, &rcElem);

  // Beim Initialisieren noch nichts zeichnen
  if (MoveState != MOVE_INITIALIZE)
    DrawFocusRect (hDC,  &rcElem);       // an alter Position loeschen
    
  POINT pt;
  pt.x = xn;
  pt.y = yn;
  toDevKoord (&pt);
  OffsetRect (&rcElem, pt.x-rcElem.left, pt.y-rcElem.top);
    
  if (MoveState == MOVE_MOUSEMOVE)
    DrawFocusRect (hDC,  &rcElem);       // an neuer Position zeichnen

  ReleaseDC (hWnd, hDC);
  }

inline void SelElem::SetWidth (int w)
  { 
  POINT pt;
  pt.x = w;
  pt.y = 0;
  toDevKoord (&pt);
  rcElem.right = rcElem.left + pt.x;
  }

void AddToSelList (LPDIALOGELEM h,HWND hWnd,LPPOINT pt)
  {
  LPSELELEM n = LPSELELEM (GetGlobMem (sizeof(*n)));
  n->Next = NULL;
  n->elem = h;
  
  h->GetRect (hWnd, &n->rcElem);
//  GetDevRect (h, &n->rcElem);
  
  for (LPSELELEM FAR *x = &selList ; *x != NULL ; x = &(*x)->Next) ;
  *x = n;
    
  h->Invalidate (hWnd);
  }

void ClearSelList(HWND hWnd)
  {
  for (LPSELELEM x = selList ; x != NULL ; ) {
    LPSELELEM n = x->Next;
    x->elem->Invalidate (hWnd,TRUE);
    FreeGlobMem (x);
    x = n;
    }
  selList = NULL;
  }

//---------------------------------------------------------------------------
// Wird aus der EditCallBack bei EDC_CHAR aufgerufen und, falls ein und nur
// ein Element selektiert ist, an dieses Element weitergereicht, so es im
// Parameterblock ein PT_TEXT oder PT_STRING sein eigen nennt.
//---------------------------------------------------------------------------
void DoSelectedChar (HWND hWnd,char ch)
  {
  if ((selList != NULL) && (selList->Next == NULL)) {
    // nur CTRL-BACKSPACE ist erlaubt
    if ((GetKeyState(VK_CONTROL) < 0) && (ch != VK_BACK))
      return;
    
    if (ch == VK_TAB) {
      // selektiertes Element in der Liste aller Elemente suchen
      for (LPDIALOGELEM h = firstElem ; (h != NULL) && (h != selList->elem) ; h = h->Next);
      if (h == selList->elem) {    // gefunden => dann das naechste nehmen
        h = h->Next;
        
        if (h == NULL) h = firstElem;
        ClearSelList (hWnd);           // Liste loeschen
        AddToSelList (h, hWnd, NULL);  // neues Element wird selektiert
        }
      }
    else
      selList->elem->OnChar (ch);
    }
  }

void DelSelList()
  {
  for (LPSELELEM x = selList ; x != NULL ; ) {
    LPSELELEM n = x->Next;
    FreeGlobMem (x);
    x = n;
    }
  selList = NULL;
  }

BOOL MoveAllowed ()
  {
  BOOL res = TRUE ;
  for (LPSELELEM x = selList ; ((x != NULL) && (res)) ; x = x->Next)
    res = x->elem->MoveAllowed ();
  return ((res) && (selList != NULL)) ;
  }

void MoveSelected (HWND hWnd,int dx,int dy,BOOL doSnap,short MoveState)
  {
//  HDC hDC = GetDC (hWnd);
  for (LPSELELEM x = selList ; (x != NULL) ; x = x->Next) {
    if (x->xOld != -32767) {
      int xn = x->xOld + dx;
      int yn = x->yOld + dy;
      int x1n = x->x1Old + dx;
      int y1n = x->y1Old + dy;
      
      static int Oldxn = 0;
      static int Oldyn = 0;
      static int Oldx1n = 0;
      static int Oldy1n = 0;

      // Wenn das Raster eingeschaltet ist, verwende die Rasterpunkte zum
      // Positionieren, sonst die Hilfslinien.
      BOOL snapDone = FALSE;
      if ((doSnap) && (!x->elem->templ->AvoidSnap()))
        snapDone = ((TryToSnap (&xn,&yn,x->elem->templ->SnapXOffs(x->elem),x->elem->templ->SnapYOffs(x->elem))) ||
                    (TryToSnap (&x1n,&y1n,x->elem->templ->SnapX1Offs(x->elem),x->elem->templ->SnapY1Offs(x->elem))));
      if ((IsRasterEnabled()) && (!snapDone)) {
        int xmm, ymm;
        GetRasterUnits (&xmm, &ymm);
        
        float RasterX, RasterY;
        if (x->elem->templ->GetEdType() == EDTYPE_FORM) {
          RasterX = float(xmm * 144.0) / 2.54F;        // 0.5 cm
          RasterY = float(ymm * 144.0) / 2.54F;        // 0.5 cm
          }
        else {
          double baseunit;
          GetBaseUnit (&baseunit);

          RasterX = float(xmm);
          RasterY = float(ymm);
          }
        
        int Offset = 0;
        if (MoveState != MOVE_MOUSEMOVEFIRST) {
          xn = int(RasterX * (int(xn / RasterX)/* + 1*/))/* - x->elem->templ->SnapXOffs(x->elem)*/;
          yn = int(RasterY * (int(yn / RasterY)/* + 1*/))/* - x->elem->templ->SnapYOffs(x->elem)*/;
          }
        }
        
      if ((Oldxn != xn) || (Oldyn != yn) || (Oldx1n != x1n) || (Oldy1n != y1n) || 
          (MoveState == MOVE_LBUTTONUP)) {


//        if (IsRasterEnabled()) {
//          if ((MoveState != MOVE_MOUSEMOVEFIRST) && (MoveState != MOVE_LBUTTONUP))
//            x->Move (hWnd, xn, yn, MoveState);
//          }
//        else
          x->Move (hWnd, xn, yn, MoveState);

        if (MoveState == MOVE_LBUTTONUP) {
          x->elem->Invalidate (hWnd,TRUE);
          x->elem->Move (xn,yn,x1n,y1n);
          x->elem->Invalidate (hWnd);
          }
        
        Oldxn = xn;
        Oldyn = yn;
        Oldx1n = x1n;
        Oldy1n = y1n;
        }
      }
    }
//  ReleaseDC (hWnd, hDC);
  }


int SelCount();
//---------------------------------------------------------------------------
// wird von der CALLBACK-Funktion DoEditCallBack bei EDC_LBUTTONUP
// und EDC_MOUSEMOVE  aufgerufen
//---------------------------------------------------------------------------
void MoveSelected (HWND hWnd,LPPOINT pt,short MoveState/*BOOL EndMove = FALSE*/)
  {
  int dx = pt->x - ptStart.x ;
  int dy = pt->y - ptStart.y ;
  if (selList != NULL) {
    selList->elem->templ->ToLogKoords (&dx,&dy);
    }
  MoveSelected (hWnd,dx,dy,SelCount() == 1,MoveState);
  }

BOOL SelHit (LPPOINT pt) 
  {
  BOOL res = FALSE ;
  for (LPSELELEM x = selList ; ((x != NULL) && (!res)) ; x = x->Next)
    res = x->elem->Hit (pt);
  return res;
  }

int SelCount()
  {
  int res = 0;
  for (LPSELELEM x = selList ; (x != NULL) ; x = x->Next)
    res ++ ;
  return res;
  }
BOOL IsSelected (LPDIALOGELEM elem)
  {
  for (LPSELELEM x = selList ; (x != NULL) ; x = x->Next)
    if (x->elem == elem) return TRUE ;
  return FALSE ;
  }
void ChangeSelection (LPDIALOGELEM x1,LPDIALOGELEM x2)
  {
  for (LPSELELEM x = selList ; (x != NULL) ; x = x->Next) {
    if (x->elem == x1) {
      x->elem = x2;
      return ;
      }
    }
  }
void PaintSelected (HWND hWnd,HDC hDC)
  {
  for (LPSELELEM x = selList ; (x != NULL) ; x = x->Next)
    x->elem->PaintSelected (hWnd,hDC);
  }

BOOL ChangeHeight(LPPOINT pt)
  {
  return ((selList->elem->ChangeHeightAllowed()) &&
          (selList->elem->HeightHit(pt)));
  }

BOOL ChangeWidth(LPPOINT pt)
  {
  return ((selList->elem->ChangeWidthAllowed()) &&
          (selList->elem->WidthHit(pt)));
  }

BOOL ChangeP1(LPPOINT pt)
  {
  return ((selList->elem->P1Allowed()) &&
          (selList->elem->P1Hit(pt)));
  }

BOOL ChangeP2(LPPOINT pt)
  {
  return ((selList->elem->P2Allowed()) &&
          (selList->elem->P2Hit(pt)));
  }

void DoChangeWidth(HWND hWnd,LPPOINT pt)
  {
  int x0,y0;
  selList->elem->templ->GetOrigin(selList->elem,&x0,&y0);

  selList->elem->Invalidate (hWnd,TRUE);

  int xn = 0;
  int dx = pt->x - ptStart.x;
  selList->elem->templ->ToLogKoords (&dx,NULL);
  if ((x0 > -32000) && (!selList->elem->templ->AvoidSnap())) {
    xn = x0 + selList->xOld + dx;
    int yn = y0;
    
    BOOL snapDone = TryToSnap (&xn,&yn,0,0);
    if ((IsRasterEnabled()) && (!snapDone)) {
      int xmm, ymm;
      float RasterX;
      
      GetRasterUnits (&xmm, &ymm);
      
      if (selList->elem->templ->GetEdType() == EDTYPE_FORM) {
        RasterX = float(xmm * 144.0) / 2.54F;        // 0.5 cm
        }
      else {
        double baseunit;
        GetBaseUnit (&baseunit);

        RasterX = float(xmm);
        }

//      float RasterX = float(xmm * 144.0) / 2.54F;        // 0.5 cm

      xn = int(RasterX * (int(xn / RasterX)/* + 1*/));
      }

    dx = xn - x0 - selList->xOld;
    }
  selList->elem->SetWidth (selList->xOld + dx);
  selList->elem->Invalidate (hWnd);
  }

void DoChangeHeight(HWND hWnd,LPPOINT pt)
  {
  int x0,y0;
  selList->elem->templ->GetOrigin(selList->elem,&x0,&y0);
  selList->elem->Invalidate (hWnd,TRUE);
  int dy = pt->y - ptStart.y;
  selList->elem->templ->ToLogKoords (NULL,&dy);
  if ((x0 > -32000) && (y0 > -32000) && (!selList->elem->templ->AvoidSnap())) {
    int xn = x0;
    int yn = y0 + selList->yOld + dy;
    BOOL snapDone = TryToSnap (&xn,&yn,0,0);
    if ((IsRasterEnabled()) && (!snapDone)) {
      int xmm, ymm;
      float RasterY;

      GetRasterUnits (&xmm, &ymm);

      if (selList->elem->templ->GetEdType() == EDTYPE_FORM) {
        RasterY = float(ymm * 144.0) / 2.54F;        // 0.5 cm
        }
      else {
        double baseunit;
        GetBaseUnit (&baseunit);

        RasterY = float(ymm);
        }

//      float RasterY = float(ymm * 144.0) / 2.54F;        // 0.5 cm

      yn = int(RasterY * (int(yn / RasterY)/* + 1*/));
      }
    dy = yn - y0 - selList->yOld;
    }
  selList->elem->SetHeight (selList->yOld + dy);
  selList->elem->Invalidate (hWnd);
  }

void DoChangeP1(HWND hWnd,LPPOINT pt)
  {
  selList->elem->Invalidate (hWnd,TRUE);
  int dx = pt->x - ptStart.x;
  int dy = pt->y - ptStart.y;
  selList->elem->templ->ToLogKoords (&dx,&dy);
  int xn = selList->xOld + dx;
  int yn = selList->yOld + dy;
  if (!selList->elem->templ->AvoidSnap())
    TryToSnap (&xn,&yn,selList->elem->templ->SnapXOffs(selList->elem),selList->elem->templ->SnapYOffs(selList->elem));
  selList->elem->SetP1 (xn,yn);
  selList->elem->Invalidate (hWnd);
  }

void DoChangeP2(HWND hWnd,LPPOINT pt)
  {
  selList->elem->Invalidate (hWnd,TRUE);
  int dx = pt->x - ptStart.x;
  int dy = pt->y - ptStart.y;
  selList->elem->templ->ToLogKoords (&dx,&dy);
  int xn = selList->xOld + dx;
  int yn = selList->yOld + dy;
  if (!selList->elem->templ->AvoidSnap())
    TryToSnap (&xn,&yn,selList->elem->templ->SnapX1Offs(selList->elem),selList->elem->templ->SnapY1Offs(selList->elem));
  selList->elem->SetP2 (xn,yn);
  selList->elem->Invalidate (hWnd);
  }

int ModifyState;
BOOL ManipInitDone;
BOOL CaptureDone;
#define MDS_NONE    0
#define MDS_WIDTH   1
#define MDS_HEIGHT  2
#define MDS_MOVE    3
#define MDS_P1      4
#define MDS_P2      5

int CheckCursor (LPEDCMEM m)
  {
  int res = 0;
  if ((SelCount() == 1) && (ChangeWidth(&m->pt))) {
    SetCursor (LoadCursor (NULL,IDC_SIZEWE));
    res = 1;
    ModifyState = MDS_WIDTH;
    }
  else if ((SelCount() == 1) && (ChangeHeight(&m->pt))) {
    SetCursor (LoadCursor (NULL,IDC_SIZENS));
    res = 1;
    ModifyState = MDS_HEIGHT;
    }
  else if ((SelCount() == 1) && (ChangeP1(&m->pt))) {
    SetCursor (LoadCursor (NULL,IDC_SIZENESW));
    res = 1;
    ModifyState = MDS_P1;
    }
  else if ((SelCount() == 1) && (ChangeP2(&m->pt))) {
    SetCursor (LoadCursor (NULL,IDC_SIZENESW));
    res = 1;
    ModifyState = MDS_P2;
    }
  else if ((MoveAllowed()) && (SelHit (&m->pt))) {
    #ifdef WIN32
    SetCursor (LoadCursor (NULL,IDC_SIZEALL));
    #else
    SetCursor (LoadCursor (NULL,IDC_SIZE));
    #endif
    res = 1;
    ModifyState = MDS_MOVE;
    }
  else
    ModifyState = MDS_NONE;
  return res;
  }

int SetManipCursor ()
  {
  int res = 1;
  switch (ModifyState) {
    case MDS_WIDTH :
      SetCursor (LoadCursor (NULL,IDC_SIZEWE));
      break ;
    case MDS_HEIGHT :
      SetCursor (LoadCursor (NULL,IDC_SIZENS));
      break ;
    case MDS_P1 :
    case MDS_P2 :
      SetCursor (LoadCursor (NULL,IDC_SIZENESW));
      break ;
    case MDS_MOVE :
      #ifdef WIN32
      SetCursor (LoadCursor (NULL,IDC_SIZEALL));
      #else
      SetCursor (LoadCursor (NULL,IDC_SIZE));
      #endif
      break ;
    default :
      res = 0;
    }
  return res;
  }

//---------------------------------------------------------------------------
// wird bei erstmaligem LBUTTONDOWN auf ein Element aufgerufen
//---------------------------------------------------------------------------
void InitializeManipulation (HWND hWnd = 0)
  {
  ManipInitDone = TRUE;
  for (LPSELELEM x = selList ; (x != NULL) ; x = x->Next) {
    switch (ModifyState) {
      case MDS_MOVE :
        x->elem->InitializeMove(&x->xOld,&x->yOld,&x->x1Old,&x->y1Old);
        break;
      case MDS_HEIGHT :
        x->elem->InitializeHeight(&x->yOld);
        break;
      case MDS_WIDTH :
        x->elem->InitializeWidth(&x->xOld);
        break;
      case MDS_P1 :
        x->elem->InitializeP1(&x->xOld,&x->yOld);
        break;
      case MDS_P2 :
        x->elem->InitializeP2(&x->xOld,&x->yOld);
        break;
      }
    
    if ((ModifyState == MDS_MOVE) && IsRasterEnabled() && IsWindow(hWnd)) {
//      HDC hDC  = GetDC (hWnd);
      x->Move (hWnd, x->xOld, x->yOld, MOVE_INITIALIZE);
//      ReleaseDC (hWnd, hDC);
      }

    }
  }

LPDIALOGELEM wonEle;
int GetAnzEdEntrys ()
  {
  return wonEle->templ->pt->AnzPars;
  }

POINT oldPt;
BOOL AnythingHit (HWND hWnd,LPPOINT pt)
  {
  for (LPDIALOGELEM h = firstElem ; h != NULL ; h = h->Next) {
    if (!h->IsCreateScreen() &&  
       (h->templ != &PaintFullHeader) && (h->templ != &PaintStdHeader) &&
       (h->templ != &PaintFullButton) && (h->templ != &PaintStdButton) &&
       (h->templ != &SetButtons)      && (h->templ != &BindInnerListToOutList)) {
      RECT r;
      h->GetRect (hWnd,&r);
      if (PtInRect (&r,*pt)) return TRUE ;
      }
    }
  return FALSE ;
  }

//---------------------------------------------------------------------------
// zeichnet in den TOOLBAR-DIALOGEN ein Raster
//---------------------------------------------------------------------------
void PaintRaster (HWND hWnd, HDC hDC)
  {
  RECT rc;
  GetClientRect (hWnd, &rc);
  
  int xmm, ymm;
  GetRasterUnits (&xmm, &ymm);

  double baseunit;
  GetBaseUnit (&baseunit);

  if (IsRasterEnabled()) {
    float RasterX = float(baseunit * xmm);
    float RasterY = float(baseunit * ymm);
    if ((RasterX != 0) && (RasterY != 0)) {
    for (float py = float(0.0); py < (rc.bottom - rc.top); py += RasterY)
      for (float px = float(0.0); px < (rc.right - rc.left); px += RasterX)
        SetPixel (hDC, rc.left + int(px), rc.top + int(py), 0);
      }
    }
  
  }

extern HWND hWndStatusbar;  
void ShowKoords (int x,int y)
  {
  if (firstElem != NULL) {
    firstElem->templ->ToAbsLogKoords (&x,&y);
    char outtxt[5];
    wsprintf (outtxt, "%d", x);
    SendMessage (hWndStatusbar, SB_SETTEXT, 1, LONG(LPSTR(outtxt)));
    wsprintf (outtxt, "%d", y);
    SendMessage (hWndStatusbar, SB_SETTEXT, 0, LONG(LPSTR(outtxt)));
    }
  }

#ifdef WIN32
void ToWndKoord(long FAR &x,long FAR &y,HWND hWnd,HWND hPaint)
#else
void ToWndKoord(int FAR &x,int FAR &y,HWND hWnd,HWND hPaint)
#endif
  {
  if (hWnd == hPaint) return ;
  else {
    POINT pt ;
    pt.x = x ;
    pt.y = y ;
    ClientToScreen (hWnd,&pt);
    ScreenToClient (hPaint,&pt);
    x = pt.x ;
    y = pt.y ;
    }
  }

void PaintNums (HWND hWnd,HWND hPaintWnd,HDC hDC)
  {
  for (LPDIALOGELEM h = firstElem ; h != NULL ; h = h->Next) {
    if (h->templ->InsertAllowed()) {
      char outtxt[32];
      wsprintf (outtxt,"%d",h->templ->SortNum(h));
      RECT r;
      h->GetRect (hWnd,&r);
      ToWndKoord(r.left,r.top,hWnd,hPaintWnd);
      ToWndKoord(r.right,r.bottom,hWnd,hPaintWnd);

      if (RectVisible (hDC,&r)) {
        COLORREF old = SetTextColor (hDC,RGB(255,0,0));
        HFONT hOldFont = (HFONT)SelectObject (hDC,GetStockObject (SYSTEM_FONT));

        // schreibt den Text zentriert in das Element
        RECT rt;
        int xCenter = (r.left + r.right) / 2;

        int cx, cy;
#ifdef WIN32
        SIZE size;
        GetTextExtentPoint32 (hDC,outtxt,lstrlen(outtxt),&size);
        cx = size.cx;
        cy = size.cy;
#else
        LONG et = GetTextExtent (hDC,outtxt,lstrlen(outtxt));
        cx = LOWORD(et);
        cy = HIWORD(et);
#endif

        rt.left  = xCenter - cx/2 ;
        rt.right = xCenter + cx/2 + 1;
        rt.top  = (r.top + r.bottom) / 2 - cy/2 ;
        rt.bottom = (r.top + r.bottom) / 2 + cy/2 + 1;
        InflateRect (&rt, 2, 2);
        int radius = max ((rt.bottom - rt.top), (rt.right - rt.left));

        SetTextAlign (hDC,TA_TOP | TA_CENTER);
        Ellipse (hDC, xCenter - radius / 2, rt.top, rt.left + radius, rt.top + radius);
        ExtTextOut (hDC, xCenter, rt.top+2, 0, &rt, outtxt, lstrlen(outtxt), NULL);
        SelectObject (hDC,hOldFont);
        old = SetTextColor (hDC,old);
        }
      }
    }
  }

DLLExport void _export FAR PASCAL PaintSortCallBack (HWND hWnd,HDC hPaintDC)
  {
  if ((doPaintNums) && (IsWindow (OutWnd)))
    PaintNums (OutWnd,hWnd,hPaintDC);
  }

int DoEditCallBack (LPDIALOGELEM h,HWND hWnd,WORD Command,LPEDCMEM m)
  {
  int res = 0;
  static BOOL bElemMovedTheFirstTime = TRUE;  // das erste MouseMove nach LButtonDown!
  switch (Command) {
    //-------------------------------------------
    case EDC_LBUTTONDOWN   :
      if (hOptWnd)
        DestroyWindow (hOptWnd);
      hOptWnd = 0;
      if (ModifyState == MDS_NONE) {     // Cursor im Element
        if (h != NULL) {
          if (GetAsyncKeyState (VK_SHIFT) < 0) 
            AddToSelList (h,hWnd,&m->pt);
          else {
            ClearSelList(hWnd);
            AddToSelList (h,hWnd,&m->pt);
            }
          SetCapture (hWnd);
          CaptureDone = TRUE ;
          ptStart = m->pt;
          }
        else {
          ClearSelList(hWnd);
          SR_LButtonDown (hWnd,m->pt.x,m->pt.y);
          }
        ManipInitDone = FALSE ;
        }
      else {
        InitializeManipulation (hWnd);
        ptStart = m->pt;
        SetCapture (hWnd);
        CaptureDone = TRUE ;
        }
      oldPt.x = 32000;
      bElemMovedTheFirstTime = TRUE;
      break ;

    //-------------------------------------------
    case EDC_LBUTTONUP     :
      switch (ModifyState) {
        case MDS_MOVE :
          MoveSelected(hWnd,&m->pt,MOVE_LBUTTONUP);
          break ;
        case MDS_WIDTH :
          DoChangeWidth(hWnd,&m->pt);
          break ;
        case MDS_HEIGHT :
          DoChangeHeight(hWnd,&m->pt);
          break ;
        case MDS_P1 :
          DoChangeP1(hWnd,&m->pt);
          break ;
        case MDS_P2 :
          DoChangeP2(hWnd,&m->pt);
          break ;
        }
      if (CaptureDone)
        ReleaseCapture ();
      CaptureDone = FALSE ;
      if (ModifyState != MDS_NONE) {
        ManipInitDone = FALSE ;
        res = TRUE;
        }
      break ;
    //-------------------------------------------
    case EDC_LBUTTONDBLCLK :
      if (!WorkOnEle(hWnd))
        MessageBeep (0);
      break ;
    //-------------------------------------------
    case EDC_MOUSEMOVE     :
      ShowKoords (m->pt.x,m->pt.y);
      if (GetAsyncKeyState (VK_LBUTTON) < 0) {
        if ((m->pt.x != oldPt.x) || (m->pt.y != oldPt.y)) {
          switch (ModifyState) {
            case MDS_MOVE :
              MoveSelected(hWnd,&m->pt,bElemMovedTheFirstTime ? MOVE_MOUSEMOVEFIRST : MOVE_MOUSEMOVE);
              bElemMovedTheFirstTime = FALSE;  // wurde schon einmal bewegt
              break ;
            case MDS_WIDTH :
              DoChangeWidth(hWnd,&m->pt);
              break ;
            case MDS_HEIGHT :
              DoChangeHeight(hWnd,&m->pt);
              break ;
            case MDS_P1 :
              DoChangeP1(hWnd,&m->pt);
              break ;
            case MDS_P2 :
              DoChangeP2(hWnd,&m->pt);
              break ;
            }
          }
        oldPt = m->pt;
        }
      break ;
    //-------------------------------------------
    case EDC_SETCURSOR     :
      if (!IsHLineMoveing()) {
        if (GetAsyncKeyState (VK_LBUTTON) < 0) {
          if (!ManipInitDone)
            CheckCursor (m);
          res = SetManipCursor ();
          if ((!ManipInitDone) && (ModifyState != MDS_NONE)) {
            InitializeManipulation ();
            ptStart = m->pt;
            }
          }
        else
          res = CheckCursor (m);
        }
      if ((ModifyState == MDS_NONE) && (SelCount() == 0)) {
        // Vielleicht wollen die Linien noch etwas
        if ((IsHLineMoveing()) || (!AnythingHit (hWnd,&m->pt)))
          res = CheckCursorForHLines (m->pt.x,m->pt.y) ;
        else
          ResetHLineCursor ();
        }
      else
        ResetHLineCursor ();
      break ;
    //-------------------------------------------
    case EDC_PAINT         :
      PaintSelected (hWnd,m->hDC);
      if (doPaintNums)
        PaintNums (hWnd,hWnd,m->hDC);
      break ;
    //-------------------------------------------
    case EDC_HLINEPAINT    :
      PaintHLines (m->hDC);
      break ;
    //-------------------------------------------
    case EDC_PAINTRASTER :
      PaintRaster (hWnd,m->hDC);
      break;
    //-------------------------------------------
    case EDC_CHAR :
      DoSelectedChar (hWnd,m->ch);
      break ;
    }
  return res;
  }

//---------------------------------------------------------
// Wegen des Rasters ein Neuzeichnen der Fenster erzwingen
//---------------------------------------------------------
void SetDialogRaster (BOOL bShow)
  {
  EnableRaster (bShow);
  HWND hWnd = (firstElem->templ->GetEdType() == EDTYPE_FORM) ?
      hFrmWnd : OutWnd;
  InvalidateRect (hWnd, NULL, !bShow);
  }

void InvalidateChilds (HWND h)
  {
  for (HWND hWnd = GetWindow (h,GW_CHILD) ; hWnd ; hWnd = GetWindow (hWnd,GW_HWNDNEXT))
    InvalidateRect (hWnd,NULL,TRUE);
  }

void TogglePaintNums()
  {
  if (doPaintNums) {
    doPaintNums = FALSE ;
    }
  else {
    doPaintNums = TRUE ;
    }
  SendMessage (hWndToolbarDialog, TB_CHECKBUTTON, MI_SHOWSORT, MAKELPARAM(doPaintNums,0));
  HWND hWnd = (firstElem->templ->GetEdType() == EDTYPE_FORM) ?
      hFrmWnd : OutWnd;
  InvalidateRect (hWnd,NULL,TRUE);
  InvalidateChilds (hWnd);
  }

DLLExport int _export FAR PASCAL ETBEditCallBack (LPVOID pData,HWND hWnd,WORD Command,LPEDCMEM m)
  {
  OutWnd = hWnd;
  ETBData FAR *d = (ETBData FAR *) pData;
  if (Command == EDC_CHECKMSG) {
    BOOL done;
    m->cm.RetVal = SR_CheckMSG (m->cm.hWnd,m->cm.msg,m->cm.wP,m->cm.lP,&done);
    if (!done)
      m->cm.RetVal = CheckHLineMSG (m->cm.hWnd,m->cm.msg,m->cm.wP,m->cm.lP,&done);
    return done ;
    }
  else
    return DoEditCallBack ((d != NULL) ? d->e : NULL,hWnd,Command,m);
  }

extern void ReadFormatInfo (void);
static void EcToolInit ()
  {
  ctgd   = GETDATA         (MakeProcInstance (FARPROC(ETBGetData),MyInstance));
  ctsd   = SETDATA         (MakeProcInstance (FARPROC(ETBSetData),MyInstance));
  ctsc   = SETCONNECTION   (MakeProcInstance (FARPROC(ETBSetConnection),MyInstance));
  ctcc   = CLEARCONNECTION (MakeProcInstance (FARPROC(ETBClearConnection),MyInstance));
  ctccmd = CALLCOMMAND     (MakeProcInstance (FARPROC(ETBCallCommand),MyInstance));
  ctgs   = GETRESOURCE     (MakeProcInstance (FARPROC(ETBGetResource),MyInstance));
  ctgf   = GETEXTFUNC      (MakeProcInstance (FARPROC(ETBGetExtFunc),MyInstance));
  ciuf   = ISUPDATEFROM    (MakeProcInstance (FARPROC(ETBIsUpdateFrom),MyInstance));
  edc    = EDITCALLBACK    (MakeProcInstance (FARPROC(ETBEditCallBack),MyInstance));
  edg    = GETVARSIZE      (MakeProcInstance (FARPROC(ETBGetVarSize),MyInstance));
  frp    = FREEPRIVDATA    (MakeProcInstance (FARPROC(ETBFreePrivData),MyInstance));

  Initialize (ctgd,ctsd,ctsc,ctcc,ctccmd,ctgs,ctgf,ciuf);
  Initialize_Extended (NULL,NULL,NULL,edg,frp,NULL,NULL,NULL,NULL);
  }

void EcToolExit ()
  {
  if (ctgd   != NULL) FreeProcInstance ((FARPROC)ctgd  );
  if (ctsd   != NULL) FreeProcInstance ((FARPROC)ctsd  );
  if (ctsc   != NULL) FreeProcInstance ((FARPROC)ctsc  );
  if (ctcc   != NULL) FreeProcInstance ((FARPROC)ctcc  );
  if (ctccmd != NULL) FreeProcInstance ((FARPROC)ctccmd);
  if (ctgs   != NULL) FreeProcInstance ((FARPROC)ctgs  );
  if (ctgf   != NULL) FreeProcInstance ((FARPROC)ctgf  );
  if (ciuf   != NULL) FreeProcInstance ((FARPROC)ciuf  );
  if (edc    != NULL) FreeProcInstance ((FARPROC)edc   );
  if (edg    != NULL) FreeProcInstance ((FARPROC)edg   );
  if (frp    != NULL) FreeProcInstance ((FARPROC)frp   );

  for (_EdTemplate *h = firstTemplate ; h != NULL ; h = h->Next)
    h->DelExtraData();
  }

void EditTools ()
  {
  for (LPDIALOGELEM h = firstElem ; h != NULL ; h = h->Next) {
    h->templ->DoEdit (h,EM_LOAD | EM_CHANGETOTRUE);
    }
  ActivateControl (hRefWnd);
  }

void DestroyTools ()
  {
  for (LPDIALOGELEM h = firstElem ; h != NULL ; h = h->Next) {
    h->templ->DoEdit (h,EM_RESET);
    }
  }

#define SELFAULT_NONE       0
#define SELFAULT_SCREEN     1
#define SELFAULT_TYPE       2
BOOL DialogElem::IsCreateScreen()
  {
  return (templ == &CreateScreen) ;
  }
BOOL SelectionCorrect (WORD FAR *fault,WORD FAR *aType)
  {
  int res = 0;
  WORD Type = 0;
  BOOL TypeCorrect = TRUE;
  for (LPDIALOGELEM h = firstElem ; ((h != NULL) && (TypeCorrect)) ; h = h->Next) {
    WORD nType = h->templ->GetEdType ();
    TypeCorrect = ((Type == 0) || ((Type != 0) && (nType == Type)));
    Type = nType ;
    if (h->IsCreateScreen()) res ++;
    }
  if (!TypeCorrect)                        
    *fault = SELFAULT_TYPE ;
  else if ((Type == EDTYPE_DIALOG) && ((res != 1) || (firstElem->templ != &CreateScreen))) 
    *fault = SELFAULT_SCREEN ;
  else                     
    *fault = SELFAULT_NONE ;
    
  *aType = (*fault == SELFAULT_NONE) ? Type : EDTYPE_NONE ;
  return (*fault == SELFAULT_NONE) ;
  }

static void InitializeElems ()
  {
  static BOOL InitizlizeElemsDone;
  if (!InitizlizeElemsDone) {
    PushButton.TemplateName = "PushButton" ;
    CheckButton.TemplateName = "CheckButton" ;
    TextPushButton.TemplateName = "TextPushButton" ;
    TextCheckButton.TemplateName = "TextCheckButton" ;
    TextRadioButton.TemplateName = "TextRadioButton" ;
    ComboButton.TemplateName = "ComboButton" ;
    UpDown.TemplateName = "UpDown" ;
    ToolEdit.TemplateName = "ToolEdit" ;
    ToolZoom.TemplateName = "ToolZoom" ;
    ToolPage.TemplateName = "ToolPage" ;
    ToolDate.TemplateName = "ToolDate" ;
    ToolFloat.TemplateName = "ToolFloat" ;
    GroupBox.TemplateName = "GroupBox" ;
    StaticTool.TemplateName = "StaticTool" ;
    lShowList.TemplateName = "lShowList" ;
    StaticBitmap.TemplateName = "StaticBitmap" ;
    Line3D.TemplateName = "Line3D" ;
    ColorLine.TemplateName = "ColorLine" ;
    ColorRect.TemplateName = "ColorRect" ;
    ActionBox.TemplateName = "ActionBox" ;
    FlapMap.TemplateName = "FlapMap" ;
    ToolPwd.TemplateName = "ToolPwd" ;
    PushCheckButton.TemplateName = "PushCheckButton" ;
    TransparentBitmap.TemplateName = "TransparentBitmap" ;
    AnimationBitmap.TemplateName = "AnimationBitmap" ;
    ToolBEdit.TemplateName = "ToolBEdit" ;
    BmpFloat.TemplateName = "BmpFloat" ;
    ShowPermList.TemplateName = "ShowPermList" ;
    ShowStringList.TemplateName = "ShowStringList" ;
    ShowColumnList.TemplateName = "ShowColumnList" ;
    ShowObjectList.TemplateName = "ShowObjectList" ;
    ShowMPObjectList.TemplateName = "ShowMPObjectList" ;
    ExternDocument.TemplateName = "ExternDocument" ;
    XYFromRect.TemplateName = "XYFromRect";
    BmpTextPushButton.TemplateName = "BmpTextPushButton";
    ToolTime.TemplateName = "ToolTime";
    ToolShortInt.TemplateName = "ToolShortInt";
    CreateScreen.TemplateName = "CreateScreen" ;
    PaintStdHeader.TemplateName = "PaintStdHeader" ;
    PaintFullHeader.TemplateName = "PaintFullHeader" ;
    DBCallStringList.TemplateName = "DBCall_StringList";
    DBCallColumnList.TemplateName = "DBCall_ColumnList";
    DBCallObjList.TemplateName = "DBCall_ObjList";
    DBCallMPObjList.TemplateName = "DBCall_MPObjList";
    ToolLongInt.TemplateName = "ToolLongInt";
    ToolMoney.TemplateName = "ToolMoney";
    PaintFullButton.TemplateName = "PaintFullBottom" ;
    PaintStdButton.TemplateName = "PaintStdBottom" ;
    SetButtons.TemplateName = "SetButtons" ;
    BindInnerListToOutList.TemplateName  = "BindInnerListToOutList" ;

    DefFrmField.TemplateName = "DefFrmField" ;
    DefFrmTime.TemplateName = "DefFrmTime" ;
    DefFrmDate.TemplateName = "DefFrmDate" ;
    DefFrmDec.TemplateName = "DefFrmDec" ;
    DefFrmShort.TemplateName = "DefFrmShort" ;
    DefFrmLong.TemplateName = "DefFrmLong" ;
    DefFrmMoney.TemplateName = "DefFrmMoney" ;
    DefFrmSLDec.TemplateName = "DefFrmSLDec" ;
    DefFrmStrList.TemplateName = "DefFrmStrList" ;
    DefFrmLine.TemplateName = "DefFrmLine" ;
    DefFrmImage.TemplateName = "DefFrmImage" ;
    Trc_DefCont.TemplateName = "Trc_DefCont" ;
    Trc_DefPattern.TemplateName = "Trc_DefPattern" ;
    Trc_DefmPattern.TemplateName = "Trc_DefmPattern" ;
    Trc_DefLine.TemplateName = "Trc_DefLine" ;
    DefFrmSozNr.TemplateName = "DefFrmSozNr" ;
    DefFrmDevDec.TemplateName = "DefFrmDevDec" ;
    DefCheckBox.TemplateName = "DefCheckBox" ;
    DefFrmShortStrList.TemplateName = "DefFrmShortStrList" ;
    Trc_DefArc.TemplateName = "Trc_DefArc" ;
    DefPattern.TemplateName = "DefPattern" ;
    DefFrmTab.TemplateName = "DefFrmTab" ;
    DefFrmTabField.TemplateName = "DefFrmTabField" ;
    DefTabDecField.TemplateName = "DefTabDecField" ;
    DefFrmTabShortStrList.TemplateName = "DefFrmTabShortStrList" ;
    DefTabFlagField.TemplateName = "DefTabFlagField" ;
    DefCheckField.TemplateName = "DefCheckField" ;
    DefTabCheckField.TemplateName = "DefTabCheckField" ;
    DefFrmStrDivList.TemplateName = "DefFrmStrDivList" ;
    DefTabDate.TemplateName = "DefTabDate" ;
    DefFrmTabStrList.TemplateName = "DefFrmTabStrList" ;
    DefTabColDec.TemplateName = "DefTabColDec" ;
    DefFrmSlantField.TemplateName = "DefFrmSlantField" ;
    DefFrmSlantDec.TemplateName = "DefFrmSlantDec" ;
    DefFrmSlantSLDec.TemplateName = "DefFrmSlantSLDec" ;
    DefMovePattern.TemplateName = "DefMovePattern" ;
    DefFrmDefDec.TemplateName = "DefFrmDefDec" ;
    DefFrmMultiField.TemplateName = "DefFrmMultiField" ;
    DefTrcImage.TemplateName = "DefTrcImage" ;
    DefFrmStaticBitmap.TemplateName = "DefFrmStaticBitmap" ;
    DefActivationRegion.TemplateName = "DefActivationRegion" ;
    DefFrmBField.TemplateName = "DefFrmBField" ;
    Trc_DefRectangle.TemplateName = "Trc_DefRectangle" ;

    CheckButton.Next =            &PushButton ;
    TextPushButton.Next =         &CheckButton ;
    TextCheckButton.Next =        &TextPushButton ;
    TextRadioButton.Next =        &TextCheckButton ;
    ComboButton.Next =            &TextRadioButton ;
    UpDown.Next      =            &ComboButton ;
    ToolEdit.Next =               &UpDown ;
    ToolZoom.Next =               &ToolEdit ;
    ToolPage.Next =               &ToolZoom ;
    ToolDate.Next =               &ToolPage ;
    ToolFloat.Next =              &ToolDate ;
    GroupBox.Next =               &ToolFloat ;
    StaticTool.Next =             &GroupBox ;
    lShowList.Next =              &StaticTool ;
    StaticBitmap.Next =           &lShowList ;
    Line3D.Next =                 &StaticBitmap ;
    ColorLine.Next =              &Line3D ;
    ColorRect.Next =              &ColorLine ;
    ActionBox.Next =              &ColorRect ;
    FlapMap.Next =                &ActionBox ;
    ToolPwd.Next =                &FlapMap ;
    PushCheckButton.Next =        &ToolPwd ;
    TransparentBitmap.Next =      &PushCheckButton ;
    AnimationBitmap.Next =        &TransparentBitmap ;
    ToolBEdit.Next =              &AnimationBitmap ;
    BmpFloat.Next =               &ToolBEdit ;
    ShowPermList.Next =           &BmpFloat ;
    ShowStringList.Next =         &ShowPermList ;
    ShowColumnList.Next =         &ShowStringList ;
    ShowObjectList.Next =         &ShowColumnList ;
    ShowMPObjectList.Next =       &ShowObjectList ;
    ExternDocument.Next =         &ShowMPObjectList ;
    XYFromRect.Next =             &ExternDocument ;
    BmpTextPushButton.Next =      &XYFromRect ;
    ToolTime.Next =               &BmpTextPushButton ;
    ToolShortInt.Next =           &ToolTime ;
    CreateScreen.Next =           &ToolShortInt ;
    PaintStdHeader.Next =         &CreateScreen ;
    PaintFullHeader.Next =        &PaintStdHeader ;
    DBCallStringList.Next =       &PaintFullHeader;
    DBCallColumnList.Next =       &DBCallStringList;
    DBCallObjList.Next =          &DBCallColumnList;
    DBCallMPObjList.Next =        &DBCallObjList;
    ToolLongInt.Next =            &DBCallMPObjList;
    ToolMoney.Next =              &ToolLongInt;
    PaintFullButton.Next =        &ToolMoney;
    PaintStdButton.Next =         &PaintFullButton;
    SetButtons.Next =             &PaintStdButton;
    BindInnerListToOutList.Next = &SetButtons;
    
    DefFrmField.Next            = &BindInnerListToOutList ;
    DefFrmTime.Next             = &DefFrmField ;
    DefFrmDate.Next             = &DefFrmTime ;
    DefFrmDec.Next              = &DefFrmDate ;
    DefFrmShort.Next            = &DefFrmDec ;
    DefFrmLong.Next             = &DefFrmShort ;
    DefFrmMoney.Next            = &DefFrmLong ;
    DefFrmSLDec.Next            = &DefFrmMoney ;
    DefFrmStrList.Next          = &DefFrmSLDec ;
    DefFrmLine.Next             = &DefFrmStrList ;
    DefFrmImage.Next            = &DefFrmLine ;
    Trc_DefCont.Next            = &DefFrmImage ;
    Trc_DefPattern.Next         = &Trc_DefCont ;
    Trc_DefmPattern.Next        = &Trc_DefPattern ;
    Trc_DefLine.Next            = &Trc_DefmPattern ;
    DefFrmSozNr.Next            = &Trc_DefLine ;
    DefFrmDevDec.Next           = &DefFrmSozNr ;
    DefCheckBox.Next            = &DefFrmDevDec ;
    DefFrmShortStrList.Next     = &DefCheckBox ;
    Trc_DefArc.Next             = &DefFrmShortStrList ;
    DefPattern.Next             = &Trc_DefArc ;
    DefFrmTab.Next              = &DefPattern ;
    DefFrmTabField.Next         = &DefFrmTab ;
    DefTabDecField.Next         = &DefFrmTabField ;
    DefFrmTabShortStrList.Next  = &DefTabDecField ;
    DefTabFlagField.Next        = &DefFrmTabShortStrList ;
    DefCheckField.Next          = &DefTabFlagField ;
    DefTabCheckField.Next       = &DefCheckField ;
    DefFrmStrDivList.Next       = &DefTabCheckField ;
    DefTabDate.Next             = &DefFrmStrDivList ;
    DefFrmTabStrList.Next       = &DefTabDate ;
    DefTabColDec.Next           = &DefFrmTabStrList ;
    DefFrmSlantField.Next       = &DefTabColDec ;
    DefFrmSlantDec.Next         = &DefFrmSlantField ;
    DefFrmSlantSLDec.Next       = &DefFrmSlantDec ;
    DefMovePattern.Next         = &DefFrmSlantSLDec ;
    DefFrmDefDec.Next           = &DefMovePattern ;
    DefFrmMultiField.Next       = &DefFrmDefDec ;
    DefTrcImage.Next            = &DefFrmMultiField ;
    DefFrmStaticBitmap.Next     = &DefTrcImage ;
    DefActivationRegion.Next    = &DefFrmStaticBitmap ;
    DefFrmBField.Next           = &DefActivationRegion ;
    Trc_DefRectangle.Next       = &DefFrmBField ;
                       
    firstTemplate = &Trc_DefRectangle ;

    for (_EdTemplate *h = firstTemplate ; h != NULL ; h = h->Next)
      h->GetParTemplate();

    EcToolInit ();

    InitizlizeElemsDone = TRUE ;
    }
  }

LPDIALOGELEM GetDialogElem (LPSTR t,LPLINE l,WORD sPos)
  {
  for (_EdTemplate *h = firstTemplate ; h != NULL ; h = h->Next) {
    if (h->CheckName (t)) return h->GetElem (l,sPos);
    }
  return NULL;
  }

void LoadToolBmps ()
  {
  if (!BitmapToolsLoaded ()) {
    for (_EdTemplate *h = firstTemplate ; h != NULL ; h = h->Next) {
      char instring[32];
      LoadString (MyInstance,h->GetToolID(),instring,sizeof(instring));
      if ((h->GetEdType() == ActType) && (lstrcmp (instring,"y") == 0))
        AddBitmapTool (h->TemplateName,h->GetHelpIndex());
      }
    }
  }

/*---------< Aufruf des ganzen >-------------*/
BOOL AllowAnalyse ()
  {
  return (firstElem == NULL);
  }

void Msg (LPSTR text)
  {
  MessageBox (hRefWnd,text,"Fehler",MB_ICONEXCLAMATION | MB_OK | MB_TASKMODAL);
  }

WORD GetFormType (LPTEXTBLOCK bl)
  {
  WORD res = FORMTYPE_FORM ;
  BOOL done = FALSE ;
  for (LPLINE h = bl->FirstLine ; ((h != NULL) && (!done)) ; h = h->Next) {
    for (LPSTR p = h->Text ; ((*p) && (!done)) ; p++) {
      if (mystrcmp (p,"typ")) {
        p += 3 ;
        for ( ; *p == ' ' ; p ++) ;
        if (mystrcmp (p,"Simulation")) res = FORMTYPE_TRACING , done = TRUE ;
        else if (mystrcmp (p,"form"))  done = TRUE ;
        }
      }
    }
  if (!done) MessageBeep (0);
  return res;
  }

static LPLINE firstTextLine,firstShowLine;
void AnalyseBlock (HWND hWParent,LPTEXTBLOCK bl,LPLINE first,LPLINE last,hash FAR *hx)
  {
  doPaintNums = FALSE ;
  defines = hx;
  hRefWnd = hWParent;
  *_MyScreenName = *_MyObjectName = '\0';
  InitializeElems ();
  int state = STATE_INIT ;
  LPDIALOGELEM ele = NULL;
  LPSHOWOBJECT show = NULL;
  ReadResContent ();
  ActType = EDTYPE_NONE ;
  firstTextLine = NULL;
  for (LPLINE h = first ; ; h = h->Next) {
    if (!AnalyseForHLine (h)) {
      LPSTR t = h->FirstWord();
      while (t != NULL) {
        switch (state) {
          case STATE_INIT :
            // Ist Wort ein Templatename
            if ((ele = GetDialogElem (t,h,h->GetSPos(t))) != NULL) state = STATE_SEARCHBOPEN;
            if ((firstTextLine == NULL) && (ele != NULL)) firstTextLine = h;
            if (ele == NULL) {
              if ((show = GetShowElem (t,h,h->GetSPos(t))) != NULL) state = STATE_SEARCHBOPEN;
              if ((firstShowLine == NULL) && (show != NULL)) firstShowLine = h;
              }
            break ;
          case STATE_SEARCHBOPEN :
            if (mystrcmp (t,"(")) {
              state = STATE_PUSHPAR ;
              }
          case STATE_PUSHPAR :
            if (state == STATE_PUSHPAR) {
              if (mystrcmp (t,")")) {
                if (ele != NULL)
                  ele->MarkEnd (h,h->GetSPos(t)+1);
                else
                  show->MarkEnd (h,h->GetSPos(t)+1);
                state = STATE_INIT;
                }
              else {
                t = NextChar (t,&h,last) ;
                if (ele != NULL)
                  t = ele->PushPar (t,&h,last) ;
                else
                  t = show->PushPar (t,&h,last) ;
                }
              }
            break ;
          }
        if (state != STATE_PUSHPAR)
          t = h->NextWord(t);
        }
      }
    if (h == last) break ;
    }
  if (state != STATE_INIT) {
    Msg ("Ungueltiger Block");
    ClearHLines ();
    DeleteElems();
    DeleteShows();
    }
  else {
    WORD fault;
    if (SelectionCorrect (&fault,&ActType)) {
      if (ActType == EDTYPE_FORM)
        FrmType = GetFormType (bl);
      SetElemPtrs ();
      CreateDlgInsertMenu (hWParent);
      LoadToolBmps ();
      CreateToolWnd (hWParent);
      SetEditCallBack (edc);
      EditTools ();
      }
    else {
      switch (fault) {
        case SELFAULT_SCREEN :
          Msg ("Screen - Fehler");
          break ;
        case SELFAULT_TYPE :
          Msg ("Type - Konflikt");
          break ;
        }
      ClearHLines ();
      DeleteElems();
      DeleteShows();
      }
    }
  }

LPSTR PushToDef (LPSTR old,LPSTR Name)
  {
  static char *prefix = "  local obj ";
  LPSTR n;
  if (old != NULL) {
    n = LPSTR(GetGlobMem (lstrlen(Name) + 1 + GetBlockSize(old)));
    lstrcpy (n,old);
    FreeGlobMem (old);
    lstrcat (n,",");
    lstrcat (n,Name);
    }
  else {
    n = LPSTR(GetGlobMem (lstrlen(prefix) + lstrlen(Name) + 1));
    lstrcat (n,prefix);
    lstrcat (n,Name);
    }
  return n;
  }

LPSTR AddSemicolon (LPSTR old)
  {
  if (old != NULL) {
    LPSTR n = LPSTR (GetGlobMem (GetBlockSize (old) + 1));
    lstrcpy (n,old);
    lstrcat (n,";");
    FreeGlobMem (old);
    return n;
    }
  else
    return NULL;
  }

static BOOL InDestroying;
char StdPrefix[] = "  ";
char StdPostfix[] = ";";
LPSTR DialogElem::GetText ()
  {
  LPSTR Text = NULL;
  if (sLine != NULL) {

    LPSTR Command = NULL;

    // erstreckt sich der Scriptbefehl ueber mehrere Zeilen?
    //-------------------------------------------------------
    if (sLine != eLine) {
    
      // Der Scriptbefehl ist also in mehreren Zeilen, aber in welcher
      // Zeile sind welche Parameter?
      // Fuer jede Zeile werden nun der erste und der letzte Parameter
      // ermittelt, und die Funktion GetCommand bastelt nun aus diesen
      // Parametern die neue Zeile.
      int EndParam = 0;
      int bco = -1 ;
      for (LPLINE CurLine = sLine; CurLine != eLine->Next; CurLine = CurLine->Next) {
        int StartParam = EndParam;  // 1.Parameter in dieser Zeile
        
        int i = 0;
        // Anzahl der Leerzeichen vor dem Script bestimmen
        for (LPSTR h = CurLine->Text; *h && IsSpaceChar (*h) ; h++, i++) ;

        // Parameter von dieser Zeile ermitteln (CurLine ist aktuelle Zeile)
        LPSTR t = CurLine->FirstWord ();
        while (t != NULL) {
          // letzten Parameter dieser Zeile ermitteln
          if   (*t == '(')    bco ++ ;
          else if (*t == ')') bco -- ;
          if ((bco <= 0) && ((*t == ',') || (*t == ';')))  // Abschluss eines Parameters
            EndParam ++;                              
          t = CurLine->NextWord (t);
          }

        LPSTR TextBefore = LPSTR (GetGlobMem (i + 1));  // Leerzeichen vor dieser Zeile
        lmemcpy (TextBefore,CurLine->Text,i);

        LPSTR TextBehind = NULL;
        if (CurLine == eLine) {     // nur fuer die letzte Zeile dieses Befehls relevant
          TextBehind = LPSTR (GetGlobMem (lstrlen(eLine->Text) - ePos + 1));
          lmemcpy (TextBehind,eLine->Text+ePos,lstrlen(eLine->Text) - ePos);
          }

        // Parameter werden zu einer Textzeile gebastelt
        Command = GetCommand (WORD(StartParam), WORD(EndParam), CurLine == sLine);

        FreeGlobMem (CurLine->Text);

        CurLine->Text = LPSTR(GetGlobMem(lstrlen(Command) + 1 + i + (TextBehind != NULL ? lstrlen(TextBehind) : 0)));
        lstrcpy (CurLine->Text, TextBefore);
        lstrcat (CurLine->Text, Command);
        if (TextBehind != NULL)
          lstrcat (CurLine->Text, TextBehind);

        FreeGlobMem (Command);
          
        FreeGlobMem (TextBefore);
        if (TextBehind != NULL)
          FreeGlobMem (TextBehind);
        }
      }
    else {
      LPSTR TextBefore = LPSTR (GetGlobMem (sPos + 1));
      lmemcpy (TextBefore,sLine->Text,sPos);
      LPSTR TextBehind = LPSTR (GetGlobMem (lstrlen(eLine->Text) - ePos + 1));
      lmemcpy (TextBehind,eLine->Text+ePos,lstrlen(eLine->Text) - ePos);

      Command = GetCommand ();

      Text = LPSTR (GetGlobMem (lstrlen(TextBefore) + lstrlen(Command) + lstrlen(TextBehind) + 1));
      lstrcpy (Text,TextBefore);
      lstrcat (Text,Command);
      lstrcat (Text,TextBehind);
  
      FreeGlobMem (Command);
      FreeGlobMem (TextBefore);
      FreeGlobMem (TextBehind);
      }
    }
  else {
    LPSTR Command = GetCommand ();
    Text = LPSTR (GetGlobMem (lstrlen(StdPrefix) + lstrlen(Command) + lstrlen(StdPostfix) + 1));
    lstrcpy (Text,StdPrefix);
    lstrcat (Text,Command);
    lstrcat (Text,StdPostfix);

    FreeGlobMem (Command);
    }

  return Text;
  }
void DialogElem::FreeLines (LPLINE FAR *lSelected,LPLINE FAR *last)
  {
  if ((sLine != NULL) && (sLine != eLine)) {
    // Alle Nachfolgenden Zeilen loeschen
    for (LPLINE n = sLine->Next ; n != NULL ; ) {
      sLine->Next = n->Next ;
      if (n->Next != NULL) n->Next->Prev = sLine ;
      else                 *last = sLine;
      FreeGlobMem (n->Text);
      FreeGlobMem (n);
      if (n == *lSelected) *lSelected = sLine;
      if (n == eLine) break ;
      n = sLine->Next;
      }
    }
  }
LPLINE DialogElem::SetCommand (LPSTR Text,LPLINE ActLine,LPTEXTBLOCK bl)
  {
  if (sLine != NULL) {
    FreeGlobMem (sLine->Text);
    sLine->Text = LPSTR(GetGlobMem (lstrlen(Text)+1));
    lstrcpy (sLine->Text,Text);
    return sLine;
    }
  else
    return bl->InsertLineBefore (ActLine,Text);
  }

BOOL StoreDialog (LPTEXTBLOCK bl,LPLINE FAR *lSelected,LPLINE FAR *fSelected)
  {
  SendMessage (hWndToolbarDialog, TB_SETSTATE, MI_SHOWSORT, MAKELPARAM(TBSTATE_ENABLED,0));
  if (hOptWnd)
    DestroyWindow (hOptWnd);
  hOptWnd = 0;
  InDestroying = TRUE ;
  BOOL InBlock = FALSE ;
  if (firstElem != NULL) {
    DestroyToolWnd ();
    RemoveDlgInsertMenu (hRefWnd);
    DelSelList();
    DestroyTools ();
    LPDIALOGELEM x = firstElem;
    LPSTR DefCommand = NULL;
    for ( LPLINE h = bl->FirstLine ; h != NULL ; ) {
      if (h == firstTextLine) InBlock = TRUE ;
      if (IsHLine (h)) {
        // Alte Hilfsliniendefinitionen werden ausgelassen
        if (h == *fSelected) *fSelected = h->Next;
        h = bl->DelLine (h,lSelected);
        continue ;
        }
      if (InBlock) {
        if ((x != NULL) && ((h == x->sLine) || (x->sLine == NULL))) {
          if (x->IsDeleted) {
            LPLINE hl = x->sLine;
            if (hl != NULL) {
              BOOL last ;
              do {
                last = (hl == x->eLine);
                hl = bl->DelLine (hl,lSelected);
                } while (!last);
              }
            x = x->Next;
            h = hl;
            }
          else {
            // Nicht geloeschte Zeile
            if (x->sLine == NULL)
              DefCommand = PushToDef (DefCommand,x->GetObjectName());
            LPSTR Text = x->GetText();

            if (Text != NULL) {
              x->FreeLines (lSelected,&bl->LastLine);
              h = x->SetCommand (Text,h,bl);
              FreeGlobMem (Text);
              }
              
            h = h->Next;
            x = x->Next;
            }
          }
        else
          h = h->Next;
        }
      else
        h = h->Next;
      }

    // Schreiben der Show - Kommandos
    LPSHOWOBJECT s = firstShow;
    for ( h = bl->FirstLine ; h != NULL ; ) {
      if (h == firstShowLine) InBlock = TRUE ;
      if (InBlock) {
        if ((s != NULL) && ((h == s->sLine) || (s->sLine == NULL))) {
          if (s->IsDeleted) {
            LPLINE hl = s->sLine;
            if (hl != NULL) {
              BOOL last ;
              do {
                last = (hl == s->eLine);
                hl = bl->DelLine (hl,lSelected);
                } while (!last);
              }
            s = s->Next;
            h = s->sLine;
            }
          else {
            LPSTR Text = s->GetText();
            s->FreeLines (lSelected,&bl->LastLine);
            h = s->SetCommand (Text,h,bl);
            FreeGlobMem (Text);
            h = h->Next;
            s = s->Next;
            }
          }
        else
          h = h->Next;
        }
      else
        h = h->Next;
      }

    // Die Definitionen reinbringen
    if (DefCommand != NULL) {
      DefCommand = AddSemicolon (DefCommand);
      bl->InsertLineBehind ((*fSelected)->Prev,DefCommand);
      FreeGlobMem (DefCommand);
      }

    // Die Hilfsliniendefinition reinbringen
    LPLINE hdef = GetHDefLine ();
    if (hdef != NULL) {
      bl->InsertLineBehind ((*fSelected)->Prev,hdef->Text);
      FreeGlobMem (hdef->Text);
      FreeGlobMem (hdef);
      *fSelected = (*fSelected)->Prev;
      }
    ClearHLines ();

    // Alles wieder abbaueen
    DeleteElems ();
    DeleteShows();
    UnloadResContent ();
    SetEditCallBack (NULL);

    if (objHash != NULL) delete objHash ;
    objHash = NULL;
    bl->SetModified ();
    DestroyFrmWindow ();
    InDestroying = FALSE ;
    return TRUE ;
    }
  else {
    InDestroying = FALSE ;
    return FALSE ;
    }
  }

BOOL DestroyEdDialog ()
  {
  if (hOptWnd)
    DestroyWindow (hOptWnd);
  hOptWnd = 0;
  InDestroying = TRUE ;
  SendMessage (hWndToolbarDialog, TB_SETSTATE, MI_SHOWSORT, MAKELPARAM(TBSTATE_ENABLED,0));
  if (firstElem != NULL) {
    DestroyToolWnd ();
    RemoveDlgInsertMenu (hRefWnd);
    DelSelList();
    DestroyTools ();
    ClearHLines ();
    DeleteElems ();
    DeleteShows();
    UnloadResContent ();
    SetEditCallBack (NULL);
    DestroyFrmWindow ();

    if (objHash != NULL) delete objHash ;
    objHash = NULL;
    InDestroying = FALSE ;
    return TRUE ;
    }
  else {
    InDestroying = FALSE ;
    return FALSE ;
    }
  }

inline LPSTR DlgWndEntName()
  {
  return "DlgEdit";
  }

extern LPSTR IniFile();
void WriteDlgWndPos (HWND hWnd)
  {
  RECT r;
  GetWindowRect (hWnd,&r);
  char outstring[64];
  wsprintf (outstring,"%d",r.left);
  WritePrivateProfileString (DlgWndEntName(),"_X",outstring,IniFile());
  wsprintf (outstring,"%d",r.top);
  WritePrivateProfileString (DlgWndEntName(),"_Y",outstring,IniFile());
  }

#define DGLEDWIDTH    600
#define DLGEDHEIGHT   40
#define BTNWIDTH      40

HFONT OptFont;
void CreateOptFont ()
  {
  if (OptFont == 0) {
    HDC hDC = GetDC(NULL);
    int FntHeight;
    if (hDC) {
      FntHeight = MulDiv(-8, GetDeviceCaps(hDC, LOGPIXELSY), 72);
      ReleaseDC (NULL, hDC);
      }
    OptFont = CreateFont(FntHeight, 0, 0, 0, 700, 0, 0, 0,
          ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
          DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, "ARIAL");
//    LOGFONT lf;
//    lmemset (&lf,'\0',sizeof(lf));
//    lf.lfHeight = -11;
//    lf.lfWeight = 700;
//    lstrcpy (lf.lfFaceName,"Arial");
//    OptFont = CreateFontIndirect (&lf);
    }
  }

void DeleteOptFont ()
  {
  DeleteObject (OptFont);
  OptFont = 0;
  }

#define FNTHNUM   18
#define FNTHDENUM 10
int DlgEntHeight (int FAR *th = NULL)
  {
  HDC hDC = CreateDC ("DISPLAY",NULL,NULL,NULL);
  TEXTMETRIC tm;
  HFONT oldfont = (HFONT)SelectObject (hDC,OptFont);
  GetTextMetrics (hDC,&tm);
  SelectObject (hDC,oldfont);
  DeleteDC (hDC);
  if (th != NULL) *th = tm.tmHeight;
  return (tm.tmHeight * FNTHNUM) / FNTHDENUM ;
  }

void PaintParNames (HDC hDC, int yScroll)
  {
  RECT rc;

  int oldMode = SetBkMode (hDC,TRANSPARENT);
  HFONT OldFont = (HFONT)SelectObject (hDC,OptFont);

//  int x = 20 ;
//  int y = DLGEDHEIGHT / 2 - yScroll;
  TEXTMETRIC tm;
  GetTextMetrics (hDC, &tm);
  int dy = (tm.tmHeight * FNTHNUM) / FNTHDENUM ;

  rc.left = 20;
  rc.top = DLGEDHEIGHT / 2 - yScroll;
  rc.right = 140;
  rc.bottom = rc.top + dy;

  for (int i = 0 ; i < GetAnzEdEntrys () ; i++) {
    char outtxt[64], szBuf[64];
    wonEle->templ->GetParName (outtxt, i);

//    lmemset (szBuf, '.', sizeof(szBuf));
    for (int j = 0 ; j < sizeof(szBuf) ; j++)
      szBuf[j] = (j % 2) ? ' ' : '.';
    
    for (j = 0 ; outtxt[j] ; szBuf[j] = outtxt[j], j++);
    ExtTextOut (hDC, rc.left, rc.top, ETO_CLIPPED, &rc, szBuf, lstrlen(szBuf), NULL);
    rc.top += dy;
    rc.bottom += dy;
    }

  SelectObject (hDC,OldFont);
  SetBkMode (hDC,oldMode);
  }

LPSTR FAR *_Param;
WORD _AnzParams;
void GetParCopy ()
  {
  _AnzParams = wonEle->AnzParams;
  _Param = (LPSTR FAR *) GetGlobMem (_AnzParams * sizeof(LPSTR)) ;
  for (WORD i = 0 ; i < _AnzParams ; i++) {
    _Param[i] = LPSTR (GetGlobMem (lstrlen (wonEle->Param[i]) + 1));
    lstrcpy (_Param[i],wonEle->Param[i]);
    }
  }

void ReloadTool ()
  {
  HWND hWnd;
  if (wonEle->templ->GetEdType() == EDTYPE_FORM) 
    hWnd = hFrmWnd;
  else
    hWnd = OutWnd;
  wonEle->Invalidate (hWnd,TRUE);
  LPVOID old = wonEle->GetIntMem ();
  wonEle->DelMem();
  wonEle->GetParCopy (_AnzParams,_Param);
  wonEle->parblock = 
    wonEle->templ->CreateParBlock (_AnzParams,_Param);
  wonEle->Reconnect (old);
  wonEle->templ->DoEdit (wonEle,EM_PRIVATE1);
  wonEle->Invalidate (hWnd,FALSE);
  }

void DelParCopy ()
  {
  for (WORD i = 0 ; i < _AnzParams ; i++)
    FreeGlobMem (_Param[i]);
  FreeGlobMem (_Param);
  _Param = NULL;
  _AnzParams = 0;
  }

void UpdatePar (HWND hWnd,WORD wP)
  {
  char intxt[256];
  GetWindowText (GetDlgItem (hWnd,wP),intxt,sizeof(intxt));
  if (wP > _AnzParams) {
    if (*intxt) {
      MessageBeep (0);
      SetWindowText (GetDlgItem (hWnd,wP),"");
      }
    }
  else {
    if (wP == _AnzParams) {
      LPSTR FAR *n = (LPSTR FAR *) GetGlobMem ((_AnzParams + 1) * sizeof(LPSTR));
      lmemcpy (n,_Param,_AnzParams * sizeof(LPSTR));
      FreeGlobMem (_Param);
      _Param = n;
      _AnzParams ++ ;
      }
    if (_Param[wP] != NULL) FreeGlobMem (_Param[wP]);
    _Param[wP] = LPSTR (GetGlobMem (lstrlen(intxt) + 1));
    lstrcpy (_Param[wP],intxt);
    if (wonEle->templ->DoUpdateImmediate (wP))
      ReloadTool ();
    }
  }


void FAR GetParEdits (LPINT x, LPINT y, LPINT w, LPINT h, LPINT dy)
  {
  int th;

//  *x = DGLEDWIDTH / 3 ;
  *x = 150;
  *dy = DlgEntHeight (&th);
  *h = (th * (FNTHNUM - 2)) / FNTHDENUM ;
  *y = DLGEDHEIGHT / 2 - (*dy - th) / 2;
  *w = (DGLEDWIDTH * 2) / 3 - 20 - BTNWIDTH - GetSystemMetrics(SM_CXBORDER);
  }

//----------------------------------------------------------------------------
// erzeugt im "Eigenschaften"-Fenster des Dialog-Elementes die Edit-Elemente.
//----------------------------------------------------------------------------
#define BTNBASE 100
int DialedWindowHeight = 0;
WNDPROC DefEditProc,DefButtonProc;
DLLExport LONG _export FAR PASCAL EditProc (HWND hWnd,unsigned msg,WPARAM wP,LPARAM lP)
  {
  switch (msg) {
    case WM_CHAR :
      if (wP == '\t') return 0L ;
      break ;
    case WM_KEYDOWN :
      if (wP == VK_TAB) return 0L ;
      break ;
    case WM_KEYUP :
      if (wP == VK_TAB) {
        HWND hWndNext = GetWindow (hWnd,(GetKeyState (VK_SHIFT) < 0) ? GW_HWNDPREV : GW_HWNDNEXT);
        if (!IsWindow (hWndNext)) hWndNext = GetWindow (hWnd,(GetKeyState (VK_SHIFT) < 0) ? GW_HWNDLAST : GW_HWNDFIRST);
        if (IsWindow (hWndNext)) SetFocus (hWndNext);
        return 0L;
        }
    }
#ifdef STRICT
  return CallWindowProc (WNDPROC (DefEditProc),hWnd,msg,wP,lP);
#else
  return CallWindowProc (FARPROC(DefEditProc),hWnd,msg,wP,lP);
#endif
  }
DLLExport LONG _export FAR PASCAL ButtonProc (HWND hWnd,unsigned msg,WPARAM wP,LPARAM lP)
  {
  switch (msg) {
    case WM_CHAR :
      if (wP == '\t') return 0L ;
      break ;
    case WM_KEYDOWN :
      if (wP == VK_TAB) return 0L ;
      break ;
    case WM_KEYUP :
      if (wP == VK_TAB) {
        HWND hWndNext = GetWindow (hWnd,(GetKeyState (VK_SHIFT) < 0) ? GW_HWNDPREV : GW_HWNDNEXT);
        if (!IsWindow (hWndNext)) hWndNext = GetWindow (hWnd,(GetKeyState (VK_SHIFT) < 0) ? GW_HWNDLAST : GW_HWNDFIRST);
        if (IsWindow (hWndNext)) SetFocus (hWndNext);
        return 0L;
        }
    }
#ifdef STRICT
  return CallWindowProc (WNDPROC (DefButtonProc),hWnd,msg,wP,lP);
#else
  return CallWindowProc (FARPROC (DefButtonProc),hWnd,msg,wP,lP);
#endif
  }
void CreateParEdits (HWND hWnd)
  {
/*
  int x = DGLEDWIDTH / 3 ;
  int th;
  int dy = DlgEntHeight (&th);
  int h = (th * (FNTHNUM - 2)) / FNTHDENUM ;
  int y = DLGEDHEIGHT / 2 - (dy - th) / 2;
  int w = (DGLEDWIDTH * 2) / 3 - 20 - BTNWIDTH - GetSystemMetrics(SM_CXBORDER);
*/
  int x, y, w, h, dy;
  
  GetParEdits (&x, &y, &w, &h, &dy);

  int xb = x + w + 10 ;
  static FARPROC lpMyEditProc,lpMyButtonProc;
  if (lpMyEditProc == NULL)
    lpMyEditProc = MakeProcInstance((FARPROC)EditProc, MyInstance);
  if (lpMyButtonProc == NULL) 
    lpMyButtonProc = MakeProcInstance((FARPROC)ButtonProc, MyInstance);
  for (int i = 0 ; i < GetAnzEdEntrys () ; i++) {
    LPSTR param = (_AnzParams > WORD(i)) ? _Param[i] : NULL;
    HWND hEdit = CreateWindow ("Edit",param,WS_CHILD | WS_BORDER | WS_VISIBLE | ES_AUTOHSCROLL,
                  x,y,w,h,hWnd,(HMENU)i,MyInstance,NULL);
    DefEditProc = (WNDPROC)SetWindowLong(hEdit, GWL_WNDPROC, 
                                  (LONG)lpMyEditProc);
    SendMessage (hEdit,WM_SETFONT,WPARAM(OptFont),0L);
    // ein weiteres Fenster fuer die Eingabe? => Buttons zeichnen
    WORD Type;

    // jedes Edit-Element ist faehig fuer "TEXT - Drag & Drop"
    LPDRAGDROP textdrop = new Text_Drop (hEdit,hWnd);

    if (wonEle->templ->ShowButton(i, &Type)) {
      HWND hButton = CreateWindow ("Button",">",WS_CHILD | WS_BORDER | WS_VISIBLE | BS_PUSHBUTTON,
                    xb,y,BTNWIDTH,h,hWnd,HMENU(BTNBASE+i),MyInstance,NULL);
      DefButtonProc = (WNDPROC)SetWindowLong(hButton, GWL_WNDPROC, 
                                    (LONG)lpMyButtonProc);
      SendMessage (hButton,WM_SETFONT,WPARAM(OptFont),0L);
      }

    if (Type != DDTYPE_NONE)
      textdrop->AddType (Type);
/*
    switch (Type) {
      case DDTYPE_BITMAP :
        textdrop->AddType (
        new Bitmap_Drop (hEdit,hWnd);
        break ;
      case DDTYPE_VAR :
        new Var_Drop (hEdit,hWnd);
        break ;
      case DDTYPE_FORMAT:
        new Format_Drop (hEdit,hWnd);
        break ;
      case DDTYPE_COLOR:
        new Color_Drop (hEdit, hWnd);
        break;
      }    // switch(Type)
*/
    y += dy;
    }
  }


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
#define   SCROLL_RATIO   4
void DialedWndScroll (HWND hWnd, UINT msg, WORD Pos, WORD ScrollType)
  {
  int  xBar;                       // Where scrollbar is now.
  int  nMin;                       // Minumum scroll bar value.
  int  nMax;                       // Maximum scroll bar value.
  int  dx;                         // How much to move.
  int  nOneUnit;                   // # of pixels for LINEUP/LINEDOWN
  int  cxClient;                   // Width of client area.
  int  nHorzOrVert;                // Doing the horizontal or vertical?
  RECT rect;                       // Client area.
  
  GetClientRect (hWnd, &rect);
  
  if (msg == WM_HSCROLL) {
    nHorzOrVert = SB_HORZ;
    cxClient    = rect.right - rect.left;
    }
  else {
    nHorzOrVert = SB_VERT;
    cxClient    = rect.bottom - rect.top;
    }

  int th;
  nOneUnit = DlgEntHeight (&th);

//  nOneUnit = cxClient / SCROLL_RATIO;
  if (!nOneUnit)
    nOneUnit = 1;

  xBar = GetScrollPos (hWnd, nHorzOrVert);
  GetScrollRange (hWnd, nHorzOrVert, &nMin, &nMax);

  switch (ScrollType) {
    case SB_LINEDOWN:             // One line right.
      dx = nOneUnit;
      break;

    case SB_LINEUP:               // One line left.
      dx = -nOneUnit;
      break;

    case SB_PAGEDOWN:             // One page right.
      dx = cxClient;
      break;

    case SB_PAGEUP:               // One page left.
      dx = -cxClient;
      break;

    case SB_THUMBPOSITION:        // Absolute position.
      dx = Pos - xBar;
      break;

    default:                      // No change.
      dx = 0;
      break;
    }

  if (dx) {
    xBar += dx;

    if (xBar < nMin) {
      dx  -= xBar - nMin;
      xBar = nMin;
      }

    if (xBar > nMax) {
      dx  -= xBar - nMax;
      xBar = nMax;
      }

    if (dx) {
      SetScrollPos (hWnd, nHorzOrVert, xBar, TRUE);

      if (nHorzOrVert == SB_HORZ)
         ScrollWindow (hWnd, -dx, 0, NULL, NULL);
      else
         ScrollWindow (hWnd, 0, -dx, NULL, NULL);

      UpdateWindow (hWnd);
      }
    }
  }


//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void SetUpScrollBars (HWND hWnd, int cx, int cy)
  {
  RECT rc;
  int cyRange = 0;
  
  GetClientRect (hWnd, &rc);
  int cyWindow = rc.bottom - rc.top;
  
  if (cyWindow < DialedWindowHeight)
    cyRange = DialedWindowHeight - cyWindow - 1;
  
  SetScrollRange (hWnd, SB_VERT, 0, cyRange, TRUE);
  }


BOOL _export FAR PASCAL EnumMDIClientChildProc (HWND hWndChild, LPARAM lParam)
  {
  RECT rc;
  HWND hWndParent = HWND(LOWORD(lParam));
  int  Delta = int(HIWORD(lParam));

  GetWindowRect (hWndChild, &rc);
  ScreenToClient (hWndParent, LPPOINT(&rc));
  ScreenToClient (hWndParent, LPPOINT(&rc.right));

  MoveWindow (hWndChild, rc.left, rc.top - Delta, rc.right-rc.left, rc.bottom-rc.top, TRUE);

  return 1;
  }

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void DialedWndSize (HWND hWnd)
  {
  static int OldcyClient = 0;
  RECT rc;
  
  GetClientRect (hWnd, &rc);
  int cyScroll = GetScrollPos (hWnd, SB_VERT);

  SetUpScrollBars (hWnd, 0, DialedWindowHeight);
  int yScroll = GetScrollPos (hWnd, SB_VERT);
  int Delta = -(cyScroll - yScroll);

  if ((OldcyClient != 0) && (Delta != 0)) {
//    Delta = OldcyClient - (rc.bottom - rc.top);
/*  

    if ((cyScroll + rc.bottom) > DialedWindowHeight) {
        InvalidateRect (hWnd, NULL, FALSE);
      }
*/    
/*
    int x, y, w, h, dy;
    GetParEdits (&x, &y, &w, &h, &dy);
*/
    WNDENUMPROC wndEnumProc = (WNDENUMPROC)MakeProcInstance ((FARPROC)EnumMDIClientChildProc, MyInstance);
    EnumChildWindows (hWnd, wndEnumProc, MAKELONG(hWnd, Delta));
    FreeProcInstance (wndEnumProc);
    InvalidateRect (hWnd, NULL, FALSE);
    }
    
  OldcyClient = rc.bottom - rc.top;

  SetUpScrollBars (hWnd, 0, DialedWindowHeight);
  }

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void DialedWndPaint (HWND hWnd)
  {
  PAINTSTRUCT ps;
  HDC hDC = BeginPaint (hWnd, &ps) ;

  int yScroll  = GetScrollPos  (hWnd, SB_VERT);

  PaintParNames (hDC, yScroll);

//  SetWindowOrg (hDC, 0, GetScrollPos (hWnd, SB_VERT));
  EndPaint (hWnd, &ps);
  }
  
//----------------------------------------------------------------------------
// Dialog-Prozedur fuer das "Eigenschaften"-Fenster eines Dialogementes
//----------------------------------------------------------------------------
LONG _export FAR PASCAL DlgEdProc (HWND hWnd,unsigned msg,WPARAM wP,LPARAM lP)
  {
  LONG RetVal = 0;
  static BOOL InCreate;
  switch (msg) {
    case WM_CREATE :
      InCreate = TRUE ;
      GetParCopy ();
      CreateParEdits (hWnd);
      InCreate = FALSE ;
      break ;
      
    case WM_SIZE:
      {
      static BOOL bInSize = FALSE;

      // Check the semaphore, return if it's set.
      if (bInSize)
         return NULL;

      bInSize = TRUE;
      DialedWndSize (hWnd);
      bInSize = FALSE;
      }
      break;
        
    case WM_MOVE :
      WriteDlgWndPos (hWnd);
      break ;
    case WM_PAINT :
      {
      DialedWndPaint (hWnd);
      }
      break ;
    case WM_COMMAND :
      {
      CRACKER_VARS
      CRACK_MESSAGEsc
      if (CRACKER_wID >= BTNBASE) {
        wonEle->templ->DoAction (CRACKER_wID - BTNBASE);
        }
      else {
        #ifdef WIN32
        if ((HIWORD(wP) == EN_UPDATE) && (!InCreate)) {
        #else
        if ((HIWORD(lP) == EN_UPDATE) && (!InCreate)) {
        #endif
          UpdatePar (hWnd,CRACKER_wID);
          }
        }
      }
      break;

    case WM_VSCROLL:
      DialedWndScroll (hWnd, msg, LOWORD(lP), wP);
      break;
      
    case WM_DESTROY :
      RemoveAll (hWnd);
      ReloadTool ();
      DelParCopy ();
      DeleteOptFont ();
      hOptWnd = 0;
      break;
    default :
      return DefWindowProc (hWnd,msg,wP,lP);
    }
  return RetVal ;
  }

void RegisterDlgWindow ()
  {
  static BOOL Registered;
  if (!Registered) {
    WNDCLASS wndclass;
    wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
    wndclass.lpfnWndProc   = DlgEdProc ;
    wndclass.cbClsExtra    = 0 ;
    wndclass.cbWndExtra    = 0 ;
    wndclass.hInstance     = MyInstance ;
    wndclass.hIcon         = NULL ;
    wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
    wndclass.hbrBackground = (HBRUSH)GetStockObject (LTGRAY_BRUSH) ;
    wndclass.lpszMenuName  = 0 ;
    wndclass.lpszClassName = "DLGWND" ;

    RegisterClass (&wndclass) ;
    Registered = TRUE ;
    }
  }

void GetDlgWndPos (int FAR *x,int FAR *y)
  {
  *x = GetPrivateProfileInt (DlgWndEntName(),"_X",100,IniFile());
  *y = GetPrivateProfileInt (DlgWndEntName(),"_Y",100,IniFile());
  }

//----------------------------------------------------------------------------
// erzeugt das "Eigenschaften"-Fenster fuer ein Dialog-Element.
//----------------------------------------------------------------------------
void WorkOnEle (HWND hParent, LPDIALOGELEM ele)
  {
  wonEle = ele;
  RegisterDlgWindow ();
  int x,y;
  GetDlgWndPos (&x,&y);
  int AnzEnt = GetAnzEdEntrys ();
  CreateOptFont ();
  HWND hWnd = (firstElem->templ->GetEdType() == EDTYPE_FORM) ?
      hFrmWnd : OutWnd;
/*
  hOptWnd = CreateWindowEx (WS_EX_DLGMODALFRAME,
                            "DLGWND",
                            wonEle->templ->TemplateName,
                            WS_POPUPWINDOW | WS_CAPTION | 
                            WS_BORDER | WS_CLIPCHILDREN | 
                            WS_VISIBLE ,
                            x,y,DGLEDWIDTH,DLGEDHEIGHT + AnzEnt * DlgEntHeight() + 2 * GetSystemMetrics(SM_CYDLGFRAME),
                            hWnd,
                            NULL,                   
                            MyInstance,              
                            NULL
                            ) ;
*/
  DialedWindowHeight = DLGEDHEIGHT + AnzEnt * DlgEntHeight() + 2 * GetSystemMetrics(SM_CYDLGFRAME);
  hOptWnd = CreateWindow ("DLGWND",
                           wonEle->templ->TemplateName,
                           WS_POPUPWINDOW | WS_CAPTION | 
                           WS_BORDER | WS_THICKFRAME | 
                           WS_CLIPCHILDREN | WS_VSCROLL |
                           WS_VISIBLE ,
                           x,y,DGLEDWIDTH,DialedWindowHeight,
                           hWnd,
                           NULL,                   
                           MyInstance,              
                           NULL
                           );

  // Oben drueber schmeissen
  SetWindowPos (hOptWnd,
                    HWND_TOPMOST,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE
                );
  }

BOOL WorkOnEle (HWND hParent)
  {
  if ((SelCount() == 1) && (hOptWnd == 0)) {
    wonEle = selList->elem;
    WorkOnEle (hParent,selList->elem);
    return TRUE ;
    }
  else
    return FALSE ;
  }

void CreateDlgInsertMenu (HWND hWnd)
  {
#ifdef UEBERLEGT
  UINT MenuFlags;
  WORD j = 0, i = 0;
  HMENU hMainMenu = GetMenu (hWnd);
  HMENU hSubMenu = GetSubMenu (hMainMenu,1);
  for ( _EdTemplate *h = firstTemplate ; h != NULL ; h = h->Next , j++) {
    if ((h->InsertAllowed()) && (h->GetEdType() == ActType)) {
      MenuFlags = MF_STRING;
      if (!(i % 10))
        MenuFlags |= MF_MENUBARBREAK;
      AppendMenu (hSubMenu, MenuFlags, MI_DLGCOMMAND + j, h->TemplateName);
      i++;
      }
    }
#endif
  }

void RemoveDlgInsertMenu (HWND hWnd)
  {
#ifdef UEBERLEGT
  WORD j = 0;
  HMENU hMainMenu = GetMenu (hWnd);
  HMENU hSubMenu = GetSubMenu (hMainMenu,1);
  for ( _EdTemplate *h = firstTemplate ; h != NULL ; h = h->Next , j++)
    if ((h->InsertAllowed()) && (h->GetEdType() == ActType))
      RemoveMenu (hSubMenu,MI_DLGCOMMAND + j,MF_BYCOMMAND);
#endif
  }

void InsertCommand (WORD wP)
  {
  int ind = wP - MI_DLGCOMMAND ;
  int j   = 0;
  for ( _EdTemplate *h = firstTemplate ; h != NULL ; h = h->Next , j++)
    if ((h->InsertAllowed()) && (h->GetEdType() == ActType))
      if (j == ind) h->InsertNewElem ();
  }

void Duplicate ()
  {
  if (SelCount() == 1)
    selList->elem->templ->DuplicateElem (selList->elem);
  else
    MessageBeep (0);
  }

BOOL WorkOnScreen (HWND hParent)
  {
  BOOL found = FALSE ;
  for (LPDIALOGELEM h = firstElem ; ((h != NULL) && (selList == NULL)) ; 
                                  h = h->Next) {
    if (h->templ->WorkExtern()) {
      WorkOnEle (hParent,h);
      found = TRUE ;
      }
    }
  return found;
  }

void InsertTool (LPSTR Name,int x,int y)
  {
  for (_EdTemplate *h = firstTemplate; h != NULL ; h = h->Next) {
    if (lstrcmp (h->TemplateName,Name) == 0) {
      h->ToAbsLogKoords (&x,&y);
      h->InsertNewElem (x,y);
      }
    }
  }

void MarkShowForDel(LPDIALOGELEM x);
BOOL RemoveCommand ()
  {
  if (SelCount() == 1) {
    HWND hWnd = (firstElem->templ->GetEdType() == EDTYPE_FORM) ?
        hFrmWnd : OutWnd;
    selList->elem->Invalidate (hWnd,TRUE);
    selList->elem->templ->DoEdit(selList->elem,EM_RESET | EM_CLEAR);
    selList->elem->DelMem();
    selList->elem->IsDeleted = TRUE ;
    MarkShowForDel(selList->elem);
    FreeGlobMem (selList);
    selList = NULL;
    ActivateControl (hRefWnd);
    return TRUE ;
    }
  else
    return FALSE ;
  }

BOOL IsDialogOpen ()
  {
  return ((firstElem != NULL) && (!InDestroying)) ;
  }

BOOL IsWOnEleOpen()
  {
  return (hOptWnd != 0);
  }

BOOL MoveElems()
  {
  if (SelCount() >= 1) {
    ModifyState = MDS_MOVE;
    int dx,dy;
    HWND hWnd = (firstElem->templ->GetEdType() == EDTYPE_FORM) ?
        hFrmWnd : OutWnd;
    InitializeManipulation (hWnd);
    if (MoveDialog (hWnd,&dx,&dy)) {
      MoveSelected (hWnd,dx,dy,FALSE,TRUE);
      }
    return TRUE ;
    }
  return FALSE ;
  }

void SelectElems (HWND hWnd,LPRECT r)
  {
  for (LPDIALOGELEM h = firstElem ; h != NULL ; h = h->Next) {
    if (h->MoveAllowed ()) {
      RECT hr;
      h->GetRect (hWnd,&hr);
      POINT pt;
      pt.x = hr.left ;
      pt.y = hr.top ;
      if (PtInRect (r,pt))
        AddToSelList (h,hWnd,&pt);
      }
    }
  ModifyState = MDS_NONE;
  ManipInitDone = FALSE;
  }

//***************************************************************************
//*                                                                         *
//* Funktionen zum Aendern der Reihenfolge von Elementen                    *
//*                                                                         *
//***************************************************************************
LPDIALOGELEM GetPrev(LPDIALOGELEM e)
  {
  if (firstElem->templ->GetEdType() == EDTYPE_DIALOG) {
    for (LPDIALOGELEM h = firstElem ; h != NULL ; h = h->Next) {
      if (h->Next == e) return h;
      }
    return NULL ;
    }
  else {
    int Num = e->templ->SortNum (e);
    return GetShownElemByNmbr(Num - 1);
    }
  }

LPDIALOGELEM GetNext(LPDIALOGELEM e)
  {
  if (firstElem->templ->GetEdType() == EDTYPE_DIALOG) {
    return e->Next;
    }
  else {
    int Num = e->templ->SortNum (e);
    return GetShownElemByNmbr(Num + 1);
    }
  }

#define XCHG(A,B)               \
  lmemcpy (dummy,&A,sizeof(A)); \
  A = B;                        \
  lmemcpy (&B,dummy,sizeof(B))
BOOL ExChangeElem (LPDIALOGELEM x1,LPDIALOGELEM x2)
  {
  BOOL allowed = TRUE ;
  if ((x1 != NULL) && (x2 != NULL) &&
      (!x1->IsCreateScreen()) && (!x2->IsCreateScreen()) &&
      (allowed = ((x1->templ->ExChangeAllowed (x1,x2)) &&
                  (x2->templ->ExChangeAllowed (x2,x1))))) {
    BOOL x1sel = IsSelected (x1);
    BOOL x2sel = IsSelected (x2);
    // Die entscheidenden Elemente austauschen
    ////////////////////////////////////////////
    char dummy[128];
    XCHG(x1->templ     ,x2->templ     );
    XCHG(x1->parblock  ,x2->parblock  );
    XCHG(x1->IsDeleted ,x2->IsDeleted );
    XCHG(x1->hExtWnd   ,x2->hExtWnd   );
    XCHG(x1->AnzParams ,x2->AnzParams );
    XCHG(x1->Param     ,x2->Param     );
    if ((x1sel) && (!x2sel)) {
      ChangeSelection (x1,x2);
      }
    if ((!x1sel) && (x2sel)) {
      ChangeSelection (x2,x1);
      }
    return TRUE ;
    }
  if (!allowed) MessageBeep (0);
  return FALSE ;
  }

BOOL ExChange (LPDIALOGELEM x1,LPDIALOGELEM x2)
  {
  if (firstElem->templ->GetEdType() == EDTYPE_FORM)
    return ExChangeShow (x1,x2);
  else
    return ExChangeElem (x1,x2);
  }

void ReloadAll ()
  {
  for (LPDIALOGELEM h = firstElem ; h != NULL ; h = h->Next) {
    h->templ->DoEdit (h,EM_RESET);
    }
  for (h = firstElem ; h != NULL ; h = h->Next) {
    h->templ->DoEdit (h,EM_LOAD | EM_CHANGETOTRUE);
    }
  ActivateControl (hRefWnd);
  }

void IndenVordergrund ()
  {
  if (SelCount() > 0) {
    BOOL exchgdone = FALSE;
    for (LPSELELEM h = selList ; h != NULL ; h = h->Next) {
      exchgdone = exchgdone ||
              ExChange (h->elem,GetPrev(h->elem));
      }
    if (exchgdone) {
      HWND hWnd = (firstElem->templ->GetEdType() == EDTYPE_FORM) ?
          hFrmWnd : OutWnd;
      InvalidateRect (hWnd,NULL,TRUE);
      ReloadAll ();
      }
    }
  else
    MessageBeep (0);
  }

void IndenHintergrund ()
  {
  if (SelCount() > 0) {
    BOOL exchgdone = FALSE;
    for (LPSELELEM h = selList ; h != NULL ; h = h->Next) {
      exchgdone = exchgdone ||
          ExChange (h->elem,GetNext(h->elem));
      }
    if (exchgdone) {
      HWND hWnd = (firstElem->templ->GetEdType() == EDTYPE_FORM) ?
          hFrmWnd : OutWnd;
      InvalidateRect (hWnd,NULL,TRUE);
      ReloadAll ();
      }
    }
  else
    MessageBeep (0);
  }

void SetOrderOfElements ()
  {
  
  }
