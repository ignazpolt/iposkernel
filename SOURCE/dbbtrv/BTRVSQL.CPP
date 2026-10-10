//////////////////////////////////////////////////////////
//  Verbindung vom Btrieve zur SQL - Datenbank
//////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/dbbtrv/rev/btrvsql.cpv   1.9   08 Nov 1996 13:26:36   HANNES  $
//  $Log:   P:/marille/clinicum/dbbtrv/rev/btrvsql.cpv  $
// 
//    Rev 1.9   08 Nov 1996 13:26:36   HANNES
// QLong, Replikator
// 
//    Rev 1.8   31 Oct 1996 11:38:30   GERHOLD
// (LPSTR)GlobalLock !!!
// 
//    Rev 1.7   28 Oct 1996 08:40:18   HANNES
// Auch Grosse Felder im Buffer -> Neues BufferHandling
// 
//    Rev 1.6   02 Feb 1996 10:42:18   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.5   11 Sep 1995 17:53:56   HANNES
// 
//    Rev 1.4   16 Feb 1995 12:46:28   HANNES
// Erweiterung um SQL-Faehigkeiten
// 
//    Rev 1.3   16 Nov 1994 12:52:06   HANNES
// Buffergroesse fuer den geblockten Teil
// 
//    Rev 1.2   07 Nov 1994 11:41:56   HANNES
// Inifile - Handling
// 
//    Rev 1.1   31 Oct 1994 10:35:08   hannes
// Kleine Verfeinerungen
// 
//    Rev 1.0   19 Oct 1994 22:30:22   hannes
// Initial revision.
//
#define INC_OLE1

#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#include "globmem.h"
#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "tbbtrv.hpp"
#define MODULENUM 81
#include "winass.hpp"
#include "tbkw.h"
#include "tbfnc.hpp"
#include "dbrecord.hpp"
#include "sqlconn.hpp"

LPSTR tmpBuffer;
GLOBALHANDLE hGBuffer;
static LPSTR ClearName (LPSTR Name)
  {
  static char res[128];
  LPSTR r = res;
  for ( LPSTR h = Name ; *h ; h++) {
    if (*h == '_') *r++ = 'x' ;
    else           *r++ = *h ;
    }
  *r = '\0';
  return res;
  }

static LPSTR GetTypeName (LPSTR Name,WORD DataType,WORD VarLen)
  {
  switch (DataType) {
    case BDT_STRING    :
      wsprintf (tmpBuffer,"%s STRING(%d)",ClearName(Name),VarLen);
      break ;
    case BDT_INTEGER   :
      wsprintf (tmpBuffer,"%s INT(%d)",ClearName(Name),VarLen);
      break ;
    case BDT_FLOAT     :
      wsprintf (tmpBuffer,"%s FLOAT(%d)",ClearName(Name),VarLen);
      break ;
    case BDT_DATE      :
      wsprintf (tmpBuffer,"%s DATE(%d)",ClearName(Name),VarLen);
      break ;
    case BDT_TIME      :
      wsprintf (tmpBuffer,"%s TIME(%d)",ClearName(Name),VarLen);
      break ;
    case BDT_DECIMAL   :
      wsprintf (tmpBuffer,"%s DECIMAL(%d)",ClearName(Name),VarLen);
      break ;
    case BDT_MONEY     :
      wsprintf (tmpBuffer,"%s MONEY(%d)",ClearName(Name),VarLen);
      break ;
    case BDT_LOGICAL   :
      wsprintf (tmpBuffer,"%s LOGICAL(%d)",ClearName(Name),VarLen);
      break ;
    case BDT_NUMERIC   :
      wsprintf (tmpBuffer,"%s NUMERIC(%d)",ClearName(Name),VarLen);
      break ;
    case BDT_BFLOAT    :
      wsprintf (tmpBuffer,"%s FLOAT(%d)",ClearName(Name),VarLen);
      break ;
    case BDT_LSTRING   :
      wsprintf (tmpBuffer,"%s LSTRING(%d)",ClearName(Name),VarLen);
      break ;
    case BDT_ZSTRING   :
      if (VarLen <= 255) {
        wsprintf (tmpBuffer,"%s ZSTRING(%d)",ClearName(Name),VarLen);
        }
      else {
        *tmpBuffer = 0;
        char ActBuffer[64];
        for ( int i = 0 ; VarLen != 0 ; i++) {
          WORD torem ;
          if (VarLen >= 256)
            wsprintf (ActBuffer,
                (i > 10) ? "%.18s%d CHAR(%d) ,\r\n  " : "%.19s%d CHAR(%d) ,\r\n  ",
                      ClearName(Name),i,torem = 255);
          else
            wsprintf (ActBuffer,
                (i > 10) ? "%.18s%d CHAR(%d)" : "%.19s%d CHAR(%d)",
                      ClearName(Name),i,torem = VarLen);
          lstrcat (tmpBuffer,ActBuffer);
          VarLen -= torem ;
          }
        }
      break ;
    case BDT_UNSIGNED  :
      wsprintf (tmpBuffer,"%s INT(%d)",ClearName(Name),VarLen);
      break ;
    case BDT_AUTOINC   :
      if (OwnCounter())
        wsprintf (tmpBuffer,"%s INT(%d)",ClearName(Name),VarLen);
      else
        wsprintf (tmpBuffer,"%s AUTOINC(%d)",ClearName(Name),VarLen);
      break ;
    case DT_LDSTRING   :
      wsprintf (tmpBuffer,"%s LSTRING(%d)",ClearName(Name),VarLen);
      break ;
    case DT_KLDATE     :
      wsprintf (tmpBuffer,"%s INTEGER(%d)",ClearName(Name),VarLen);
      break ;
    case DT_PRIVATE   :
    case DT_SPRIVATE   :
      if (VarLen <= 255) {
        wsprintf (tmpBuffer,"%s CHAR(%d)",ClearName(Name),VarLen);
        }
      else {
        *tmpBuffer = 0;
        char ActBuffer[64];
        WORD torem ;
        for ( int i = 0 ; VarLen != 0 ; i++) {
          if (VarLen >= 256)
            wsprintf (ActBuffer,"%.19s%d CHAR(%d) ,\r\n  ",ClearName(Name),i,torem = 255);
          else
            wsprintf (ActBuffer,"%.19s%d CHAR(%d)",ClearName(Name),i,torem = VarLen);
          lstrcat (tmpBuffer,ActBuffer);
          VarLen -= torem ;
          }
        }
      break ;
    }
  return tmpBuffer;
  }
static LPSTR RecDesc (WORD ps,WORD flags)
  {
  lstrcpy (tmpBuffer,"  ");
  if (flags & FA_COMPRESS) {
    lstrcat (tmpBuffer,"DCOMPRESS ");
    }
  char psize[128];
  wsprintf (psize,"PAGESIZE %d",ps);
  lstrcat (tmpBuffer,psize);
  return tmpBuffer;
  }
extern LPSTR WINAPI makeIni(LPSTR txt);
static LPSTR GetIndexStmt (LPKEYDEF Key,WORD KeyNmbr,LPRECDESC h)
  {
  *tmpBuffer = '\0';
  WORD k = 0 ;
  for (WORD i = 0 ; ; i++) {
    if (k >= KeyNmbr) break ;
    if ((h->k[i].flag & KA_SEGMENTED) == 0) k ++ ;
    }
  LPVARTBL v = LPVARTBL (Key->Name + lstrlen(Key->Name) + 1) ;
  if (v->gSize > (sizeof(*v) - sizeof(v->v[0]))) {
    LPVBTRV x = &v->v[0];
    for ( ; x != NULL ; x = x->Next (v->gSize,v)) {
      lstrcat (tmpBuffer,"  ");
      char lName[128];
      wsprintf (lName,"%.20s",ClearName(x->Name));
      lstrcat (tmpBuffer,x->Name);
      if ((h->k[i].flag & KA_MODIFIABLE) != NULL)
        lstrcat (tmpBuffer," MOD");
      if ((h->k[i].flag & KA_SEGMENTED) != 0)
        lstrcat (tmpBuffer," SEG");
      if ((h->k[i].flag & KA_DUPLICATE) == 0)
        lstrcat (tmpBuffer," UNIQUE");
      if ((h->k[i].flag & (KA_NULL | KA_MANUAL)) != 0)
        lstrcat (tmpBuffer," NULL");
      if ((h->k[i].flag & (KA_ALT)) != 0) {
        char path[128];
        GetPrivateProfileString ("Collating","File","H:\\CLINICUM\\SOFTWORK.ALT",path,sizeof(path),makeIni("dbbtrv.ini"));
        lstrcat (tmpBuffer," '");
        lstrcat (tmpBuffer,path);
        lstrcat (tmpBuffer,"'");
        }
      if (x->Next (v->gSize,v) != NULL)
        lstrcat (tmpBuffer," ,\r\n");
      i++ ;
      }
    }
  return tmpBuffer;
  }

LPSTR GetFileName (LPBTRVTABLE t)
  {
  char Name[128],Path[128],def[32];
  lstrcpy (Name,t->GetFileRef());
  lstrncpy (def,Name,8);
  def[8] = '\0';
  lstrcat (def,".dat");
  GetPrivateProfileString ("Path",Name,def,Path,sizeof(Path),makeIni("dbbtrv.ini"));
  int i = 0 ;
  for ( LPSTR h = Path ; *h ; h++) {
    if (*h == '\\')
      i = 0 ;
    else
      tmpBuffer[i++] = *h ;
    }
  tmpBuffer[i++] = '\0' ;
  return tmpBuffer;
  }

LPSTR GetOutName (LPBTRVTABLE t)
  {
  char Name[128],Path[128],def[32];
  lstrcpy (Name,t->GetFileRef());
  lstrncpy (def,Name,8);
  def[8] = '\0';
  lstrcat (def,".dat");
  GetPrivateProfileString ("Path",Name,def,Path,sizeof(Path),makeIni("dbbtrv.ini"));
  int i = 0 ;
  for ( LPSTR h = Path ; *h ; h++) {
    if (*h == '\\')
      i = 0 ;
    else if (*h == '.')
      break ;
    else
      tmpBuffer[i++] = *h ;
    }
  tmpBuffer[i++] = '.' ;
  tmpBuffer[i++] = 'X' ;
  tmpBuffer[i++] = 'Q' ;
  tmpBuffer[i++] = 'L' ;
  tmpBuffer[i++] = '\0' ;
  return tmpBuffer;
  }

DLLExport LPSTR _export WINAPI DataDict_GetSqlPart (WORD Cmd,LPSTR TableName,LPVOID DLLData,WORD VarID,WORD KeyNmbr,LPSTR Buffer,WORD BufSize)
  {
  if (!hGBuffer) {
    hGBuffer = GlobalAlloc (GMEM_MOVEABLE,4096);
    tmpBuffer = (LPSTR)GlobalLock (hGBuffer);
    }
  *Buffer = '\0';
  LPBTRVTABLE t = LPBTRVTABLE(DLLData);
  switch (Cmd) {
    case SQLSTMT_GETOUTNAME :
      {
      lstrcpy (Buffer,GetOutName(t));
      }
      return Buffer;
    case SQLSTMT_HEADER :
      {
      wsprintf (Buffer,"CREATE TABLE %.20s USING '%s'\r\n",TableName,GetFileName (t));
      LPRECDESC h = t->GetDescRef(FALSE);
      lstrcat (Buffer,RecDesc (h->PageSize,h->flags));
      }
      return Buffer;
    case SQLSTMT_VARDEF :
      {
      LPVARTBL h = t->GetVarRef (FALSE);
      if (h != NULL) {
        LPVBTRV x = &h->v[0];
        for ( WORD i = 0 ; ((x != NULL) && (i < VarID)); x = x->Next (h->gSize,h) , i++ ) ;
        if (x != NULL) {
          if (i == 0) lstrcpy (Buffer,"  (\r\n");
          lstrcat (Buffer,"  ");
          char lName[128];
          wsprintf (lName,"%.20s",ClearName(x->Name));
          lstrcat (Buffer,GetTypeName (lName,x->DataType,x->VarLen));
          if (x->Next (h->gSize,h) != NULL)
            lstrcat (Buffer," ,");
          else {
            if ((t->BlockType == BLOCKTYPE_MARILLE) || (t->BlockType == BLOCKTYPE_MARILLE1)) {
              char tail[128];
              LPRECDESC h = t->GetDescRef(FALSE);
              wsprintf (tail," ,\r\n  mblocked NOTE (%d)",20000-h->RecordLength + 2);
              lstrcat (Buffer,tail);
              }
            }
          return Buffer ;
          }
        else
          return NULL ;
        }
      }
      break ;
    case SQLSTMT_BUTTOM :
      {
      lstrcpy (Buffer,"  )\r\nWITH INDEX (\r\n") ;
      LPKEYDEF Key = t->GetFirstKey (FALSE);
      LPRECDESC h = t->GetDescRef(FALSE);
      lstrcat (Buffer,GetIndexStmt(Key,0,h));
      if (t->GetNextKey(Key,FALSE) != NULL) lstrcat (Buffer," ,");
      else                                  lstrcat (Buffer,"\r\n );\r\n");
      return Buffer;
      }
      break ;
    case SQLSTMT_KEYSTMT :
      LPKEYDEF Key = t->GetFirstKey (FALSE);
      LPRECDESC h = t->GetDescRef(FALSE);
      for ( WORD i = 0 ; ((Key != NULL) && (i < KeyNmbr)) ; i++ , Key = t->GetNextKey (Key,FALSE) ) ;
      if (Key != NULL) {
        LPRECDESC h = t->GetDescRef(FALSE);
        lstrcat (Buffer,GetIndexStmt(Key,i,h));
        if (t->GetNextKey(Key,FALSE) != NULL) lstrcat (Buffer," ,");
        else                                  lstrcat (Buffer,"\r\n  );\r\n");
        return Buffer;
        }
      else
        return NULL;
      break ;
    }
  return NULL;
  }

