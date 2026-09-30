//////////////////////////////////////////////////////////////
//  ODBC - Anbindung an das Clinicum
//////////////////////////////////////////////////////////////
//
//  $Header:   P:/marille/clinicum/ddsodbc/rev/altodbc.cpv   1.21   09 Sep 1999 22:18:38   Hannes  $
//  $Log:   P:/marille/clinicum/ddsodbc/rev/altodbc.cpv  $
// 
//    Rev 1.21   09 Sep 1999 22:18:38   Hannes
// SQL Syntax auch in ODBC
// 
//    Rev 1.20   25 Apr 1999 19:05:26   Martin
// Namen auf jeden Fall auf 30 Zeichen begrenzen (nicht nur CTEMP_)
// 
//    Rev 1.19   21 Aug 1998 14:46:30   Martin
// mehrere Fehler in SybAny korrigiert (DEFAULT, DBSpaceChanged, CreateAllIndex)
// 
//    Rev 1.18   04 Aug 1998 17:56:56   Hannes
// Timestamp
// 
//    Rev 1.17   27 Jul 1998 13:28:48   Hannes
// DBSpace - Handling
// 
//    Rev 1.16   17 Jun 1998 19:47:08   Martin
// DEFAULT statement korrigiert
// 
//    Rev 1.15   17 Jun 1998 17:33:22   Martin
// identity_insert im SQL Server ermoeglicht (bei Umschaufeln)
// 
//    Rev 1.14   17 May 1998 17:53:36   Hannes
// Update beim Aendern der Stringgroesse
// 
//    Rev 1.13   06 Mar 1998 17:26:10   Hannes
// Prototyp Transaktionshandling
// 
//    Rev 1.12   06 Feb 1998 22:36:40   Hannes
// 
//    Rev 1.11   31 Oct 1997 12:50:30   Hannes
// Timestampfunktion, Diverse Fehlerkorr.
// 
//    Rev 1.10   28 Oct 1997 17:30:52   Martin
// PRIMARY KEY kann sich jetzt aendern (in Sybase Anywhere)
// 
//    Rev 1.9   23 Oct 1997 10:59:54   Gerhold
// strcpy -> lstrcpy
// 
//    Rev 1.8   19 Oct 1997 21:25:44   Martin
// bei _Id's einzeln updaten
// 
//    Rev 1.7   16 Oct 1997 21:19:44   Martin
// Tabellennamen sind auch auf 30 Zeichen beschraenkt !!!! (CTEMP_...)
// 
//    Rev 1.6   24 Sep 1997 09:30:40   Hannes
// Update auch fuer Microsoft SQL - Server
// 
//    Rev 1.5   20 Dec 1996 16:39:54   HANNES
// 
//    Rev 1.4   20 Dec 1996 16:30:08   HANNES
// 
//    Rev 1.3   20 Dec 1996 16:24:08   HANNES
// 
//    Rev 1.2   20 Dec 1996 16:10:26   HANNES
// Nachfragen bei Fehlern
// 
//    Rev 1.1   17 Dec 1996 11:58:40   HANNES
// Groessenaenderungen beruecksichtigt
// 
//    Rev 1.0   26 Nov 1996 08:02:22   HANNES
// Initial revision.
// 
#include <windows.h>
#include <stdio.h>
#include <sql.h>
#include <sqlext.h>
#include "dds32.h"

#define NODDSDATA
#include "dds.hpp"
#include "globmem.h"
#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#define MODULENUM 174
#include "winass.hpp"
#include "dbrecord.hpp"
#include "hash.hpp"

#define NOCOMPILE
#include "compile.hpp"

#include "opodbc.hpp"
#include "tbdiff.hpp"

static BOOL _inAlter;
BOOL InAlter ()
  {
  return _inAlter ;
  }
BOOL holdBlocked (LPTABLEDEF td)
  {
  for (int i = 0 ; i < td->GetAnzVars() ; i++)
    if (td->GetVarDef(i)->VarID != 0xFFFF) return TRUE ;
  return FALSE ;
  }
static LPTABLEDEF intTable;
BOOL AskForContinue (LPSTR msg,LPSTR TableName,BOOL doCat = TRUE)
  {
  char outtxt[512];
  wsprintf (outtxt,msg,TableName);
  if (doCat)
    lstrcat (outtxt,"\r\nBitte Setzen Sie nur dann fort, wenn Sie sich ganz sicher sind, daß der Fehler ignoriert werden darf\r\n\r\nSoll trotzdem fortgesetzt werden?");
  int ret = MessageBox (GetActiveWindow (),outtxt,"WARNUNG!",MB_TASKMODAL | MB_ICONHAND | MB_YESNO);
  return (ret == IDYES) ;
  }

void MarkTableFromINTName (LPTABLEDEF tnew)
  {
  if (tnew) {
    WIN_ASSERT (intTable == NULL);
    intTable = tnew ;
    }
  else
    intTable = NULL ;
  }
LPSTR ODBCGetTableName (LPTABLEDEF t)
  {
  static char TNamBuffer[72];
  if (t == intTable) {
    lstrcpy (TNamBuffer,"CTEMP_");
    lstrcat (TNamBuffer,t->GetName());
    }
  else
    lstrcpy (TNamBuffer,t->GetName());
  if (dbase->DatabaseType == DT_MSSQLSERVER)
    TNamBuffer[30] = '\0';
  return TNamBuffer;
  }

inline BOOL IsFixed (int varType)
  {
  return ((varType == VAR_STRARR) || (varType == VAR_LONG) ||
          (varType == VAR_FLAG) || (varType == VAR_DEC) ||
          (varType == VAR_DWORD) || (varType == VAR_DATE) ||
          (varType == VAR_TIME) || (varType == VAR_POINT) || 
          (varType == VAR_SCALE) || (varType == VAR_DATETIME)) ;
  }
inline BOOL IsChar (int varType)
  {
  return (varType == VAR_STR) ;
  }
LPSTR GetVarString (LPVOID data,int mType,BOOL FAR *doFree,int Size,BOOL doStatic)
  {
  static char *null = "NULL" ;
  static char resstr[128];
  if (data == NULL) {
    *doFree = FALSE ;
    return null ;
    }
  if (IsFixed (mType)) {
    switch (mType) {
      case VAR_STRARR :
      case VAR_FLAG :
        sprintf (resstr,"%d",*(short FAR *) data) ;
        break ;
      case VAR_DEC :
        sprintf (resstr,"%f",*(float FAR *) data) ;
        break ;
      case VAR_LONG :
      case VAR_DWORD :
        sprintf (resstr,"%ld",* (LONG FAR *) data) ;
        break ;
      case VAR_DATE :
        sprintf(resstr, "'%04.4d%02.2d%02.2d'", 
                       (int) (((packdate FAR *) data)->year),
                       (int) (((packdate FAR *) data)->month),
                       (int) (((packdate FAR *) data)->day)
                       );
        break ;
      case VAR_TIME :
        sprintf(resstr, "'%02.2d:%02.2d:%02.2d'", 
                        (int) (((packtime FAR *) data)->hour),
                        (int) (((packtime FAR *) data)->minute),
                        (int) (((packtime FAR *) data)->second));
        break ;
      case VAR_DATETIME :
        sprintf(resstr, "'%04.4d%02.2d%02.2d %02.2d:%02.2d:%02.2d'", 
                        (int) (((packdatetime FAR *) data)->pd.year),
                        (int) (((packdatetime FAR *) data)->pd.month),
                        (int) (((packdatetime FAR *) data)->pd.day),
                        (int) (((packdatetime FAR *) data)->pt.hour),
                        (int) (((packdatetime FAR *) data)->pt.minute),
                        (int) (((packdatetime FAR *) data)->pt.second));
        break ;
      default :
        // binaere Codierung
        if (doStatic) {
          LPSTR b = LPSTR(data);
          int len = GetBlockSize(b);
          LPSTR res = resstr ;
          *res ++ = '\'' ;
          for (int i = 0 ; i < len ; i++) {
            char h = (*b & 0xF0) >> 4 ;
            *res ++ = (h < 10) ? h + '0' : h - 10 + 'A' ;
            h = *b & 0x0F ;
            *res ++ = (h < 10) ? h + '0' : h - 10 + 'A' ;
            b ++ ;
            }
          *res ++ = '\'' ;
          *res ++ = '\0' ;
          }
      break ;
      }
    *doFree = FALSE ;
    return resstr ;
    }
  else if (IsChar(mType)) {
    if ((data != NULL) && ((*(LPSTR)data) != '\0')) {
      if (doStatic) {
        *doFree = TRUE ;
        int len = 0 ;
        for (LPSTR h = LPSTR(data) ; *h ; h++ ) {
          if (*h == '\'') len ++ ;
          len ++ ;
          if ((Size > 0) && (len >= Size - 1)) break ;
          }
        LPSTR res = LPSTR(GetGlobMem (len + 3)) ;
        *res = '\'' ;
        int i = 0 ;
        h = LPSTR(data) ;
        for (LPSTR h1 = res + 1 ; 
                ((*h) && ((i < Size - 1) || (Size <= 0))) ; 
                    *h1 ++ = *h++ , i ++ ) {
          if (*h == '\'') *h1++ = '\'' ;
          }
        *doFree = TRUE ;
        *h1 ++ = '\'' ;
        return res ;
        }
      }
    else {
      *doFree = FALSE ;
      return null ;
      }
    }
  return NULL ;
  }

void DefaultStatement (LongString FAR &s,LPVARDEF v,int AnzDefs,DefVal FAR *dv)
  {
  for (int i = 0 ; i < AnzDefs ; i++) {
    if (lstrcmp(v->GetName(),dv[i].VarName) == 0) {
      BOOL doFree;
      LPSTR vs = GetVarString (dv[i].DefaultValue,dv[i].mType,&doFree,
                    GetBlockSize (dv[i].DefaultValue),TRUE);
      s = s + " DEFAULT " + vs ;

      if (doFree)
        FreeGlobMem (vs);
      }
    }
  }

LPSTR MSIndexName (LPSTR kName,LPTABLEDEF td)
  {
  static char chnBuffer[31];
  char myBuffer[256];
  lstrcpy (myBuffer,kName);
  lstrcat (myBuffer,td->GetName());
  lstrncpy (chnBuffer,myBuffer,30);

  return chnBuffer;
  }

void DelFromTableHash(LPTABLEDEF td)
  {
  char tablename[100];
  lstrcpy(tablename, ODBCGetTableName(td));
  // AnsiUpper(tablename);
  dbase->TableHash->DelData (tablename);
  }

BOOL NeuerAutoInc (TableDifference FAR *tx,LPTABLEDEF tnew)
  {
  if ((tx->AnzKeysToDrop () > 0) && 
      (tx->AnzKeysToAdd () > 0) &&
      (tx->KeysToDrop[0] == 0) &&
      (tx->KeysToAdd[0] == 0) &&
      ((tnew->GetKeyDef(0)->Attribute & CLKD_AUTOINC) == CLKD_AUTOINC))
    return TRUE ;
  else
    return FALSE ;
  }

BOOL IdChanged (TableDifference FAR *tx,LPTABLEDEF tnew,LPTABLEDEF told)
  {
  for (int i = 0 ; i < tx->AnzModified () ; i++) {
    LPVARDEF vnew = tnew->GetVarDef(tx->Modified[i]);
    LPVARDEF vold = told->GetVarDef(tx->VarIDFrom (tx->Modified[i]));
    if (((vnew->VarSize == 0xFFFF) && (vold->VarSize != 0xFFFF)) ||
        ((vnew->VarSize != 0xFFFF) && (vold->VarSize == 0xFFFF)))
      return TRUE ;
    }
  return FALSE ;
  }

BOOL DtChanged (TableDifference FAR *tx,LPTABLEDEF tnew,LPTABLEDEF told)
  {
  for (int i = 0 ; i < tx->AnzModified () ; i++) {
    LPVARDEF vnew = tnew->GetVarDef(tx->Modified[i]);
    LPVARDEF vold = told->GetVarDef(tx->VarIDFrom (tx->Modified[i]));
    if (((vold->mType == VAR_STR) && (vnew->mType == VAR_STR)) &&
        (((vold->VarSize <= 254) && (vnew->VarSize > 254)) ||
         ((vold->VarSize > 254) && (vnew->VarSize <= 254))))
      return TRUE ;
    }
  return FALSE ;
  }

BOOL DBSpaceChanged (LPTABLEDEF nw,LPTABLEDEF old)
  {
  char b1[256],b2[256];
  int s1 = old->GetTableProperty ("SQLANY_DBSPACE",b1,sizeof(b1));
  int s2 = nw->GetTableProperty ("SQLANY_DBSPACE",b2,sizeof(b2));
  if ((s1 != s2) || ((s1 > 0) && (lstrcmp (b1,b2) != 0))) return TRUE ;
  else                                                    return FALSE ;
  }

extern int _export FAR PASCAL DBCall (WORD Op,int AnzLines,LPDBREQUEST req,LPVOID FAR *hstmt,RecBuffer FAR *res);
#define STEPWITH  10

BOOL SameDef (LPTABLEDEF old,LPTABLEDEF nw)
  {
  char b1[256],b2[256];
  int s1 = old->GetTableProperty ("SQLANY_DBSPACE",b1,sizeof(b1));
  int s2 = nw->GetTableProperty ("SQLANY_DBSPACE",b2,sizeof(b2));
  if ((s1 == s2) && (lstrcmp (b1,b2) == 0)) return TRUE ;
  else                                      return FALSE ;
  }

DLLExport BOOL _export WINAPI DBAlter (LPTABLEDEF told,LPTABLEDEF tnew,int AnzDefs,DefVal FAR *dv,__ALTERSUCCESS alts)
  {
  static char TCheck[32];
  if (tnew->GetTableProperty ("ODBC_Check",TCheck,sizeof(TCheck)) > 0) {
    if (lstrcmp(TCheck,"no") == 0) {
      BeginTransaction (FALSE);   // Von aussen, damit die Sync hinhaut...
      return DBCALL_SUCCESS;
      }
    }

  _inAlter = TRUE ;
  TableDifference td(told,tnew,(WORD) ~VPROP_CASEINSENSITIVE,(WORD) ~VPROP_CASEINSENSITIVE);

  CheckFile (NULL,FALSE);
  dbase->StartTableTest ();

  BOOL error = FALSE;
  error = !dbase->TestTable (told);
  HSTMT hstmt = dbase->GetStatementHandle ();

  if ((error) && (AskForContinue ("Alte Tabelle %s stimmt nicht mit der Definition ueberein",told->GetName())))
    error = FALSE ;

  if ((!td.NoDifference()) || (!SameDef (told,tnew))) {
    // 1. Alle alten Schluessel wegschmeissen
    LongString s ;
    for (int i = 0 ; ((i < td.AnzKeysToDrop()) && (!error)) ; i++) {
      s.Clear ();
      LPSTR KeyName = NULL ;
      for (int j = 0 ; j < told->GetAnzKeySegs() ; j++) {
        LPCLKEYDEF k = told->GetKeyDef(j);
        if (k->KeyNmbr == WORD(td.KeysToDrop[i])) {
          KeyName = k->name;
          break ;
          }
        }
      if (KeyName != NULL) {
        if (dbase->DatabaseType == DT_MSSQLSERVER)
          s = s + "DROP INDEX " + told->GetName() + "." + MSIndexName (KeyName,told);
        else
          s = s + "DROP INDEX " + KeyName + told->GetName();
        error = !dbase->TestRetCode (hstmt,SQLExecDirect (hstmt,s.Ptr(),SQL_NTS));
        }
      else
        error = TRUE ;
      if ((dbase->DatabaseType != DT_MSSQLSERVER) && (td.KeysToDrop[i] == 0)) {
        s.Clear ();
        s = s + "ALTER TABLE " + told->GetName() + " DROP PRIMARY KEY" ;
        error = error | (!dbase->TestRetCode (hstmt,SQLExecDirect (hstmt,s.Ptr(),SQL_NTS)));
        }
      if ((error) && (AskForContinue ("Beim Löschen von Schlüsseln sind Fehler aufgetreten",told->GetName())))
        error = FALSE ;
      }

    s.Clear ();

    BOOL doneWithCopy = FALSE ;
    if (((dbase->DatabaseType == DT_MSSQLSERVER) &&
         ((td.AnzVarsToDrop () > 0) || (td.AnzModified () > 0) || 
          (IdChanged (&td,tnew,told)) || (AnzDefs > 0))) ||
         ((dbase->DatabaseType != DT_MSSQLSERVER) && 
          ((NeuerAutoInc (&td,tnew)) ||
           (IdChanged (&td,tnew,told)) ||
           (DtChanged (&td,tnew,told)) ||
           (DBSpaceChanged (tnew,told)))
         )
       ) {
      BOOL EinzelnSchaufeln;
      if (holdBlocked(told) || holdBlocked(tnew))
        EinzelnSchaufeln = TRUE;   // sobald irgendein _Id im Spiel ist ...
      else
        EinzelnSchaufeln = FALSE;

      // Es muss umgeschaufelt werden
      //------------------------------------------------------------------------------------------------------
      BOOL askDone = FALSE ;
      error = !dbase->TestTable (told);
      if (error) {
        if (AskForContinue ("Alte Tabelle %s stimmt nicht mit der Definition ueberein",told->GetName()))
          error = FALSE ;
        askDone = TRUE ;
        }
      LongString s;
      MarkTableFromINTName (tnew);
      if (!error) {
        // Sicherheitshalber die Zwischentabelle noch einmal
        // droppen
        s = s + "DROP TABLE " + ODBCGetTableName (tnew);
        SQLExecDirect (hstmt,s.Ptr(),SQL_NTS);
        s.Clear ();
        }

      DWORD row = 0L ;
      if (EinzelnSchaufeln) {
        if (!error)
          DelFromTableHash(tnew);

        // Bilden einer Liste auf das alte file
        DBList FAR *res = NULL;
        if (!error) {
          static ParamBlock p;
          lmemset (&p,'\0',sizeof(p));
          p.AnzPars = 0;

          res = new DBList (told,0L,"",100,100,&p,FALSE);
          res->SetOrder ("");
          if (res == NULL) error = TRUE ;
          }

        // Alle Datensaetze in das neue File umkopieren
        if (!error) {
          InitializeDefVal (dv,AnzDefs,tnew);
          for (LPDBRECORD h = res->GetFirst(); ((h != NULL) && (!error)) ; h = res->GetNext(h)) {
            DBRecord FAR *n = ConvertRecord (tnew,h,&td,AnzDefs,dv);

            LPDBREQUEST req = InitializeRequest ("",-1,DBCALLTYPE_STANDARDINSERT,0L);
            WORD TableID = tnew->GetTableID();
            WORD Version = tnew->GetVersion();
            req->SetTableID(TableID,Version);
            req->AddTableDef (TableID,Version);
            req->SetParam (1,&TableID,sizeof(TableID));
            req->AnzParam = 0;

            RecBuffer rb;
            lmemset (&rb,'\0',sizeof(rb));
            rb.AddLine (1,ADDLINEPOS_START);
            rb.act->rec[0] = n ;

            LPVOID hstmt = NULL;
            int stat = DBCall (DBOP_GET,1,req,&hstmt,&rb);
            DBCall (DBOP_RESET,0,NULL,&hstmt,NULL);

            rb.Clear ();
            req->ClearParams();
            req->FreeTableDefs();
            FreeRequest (req);

            delete n ;

            error = (stat != DBCALL_SUCCESS);

            res->ThrowAtHead(h);

            row ++ ;
            if ((row % STEPWITH) == 0L)
              (* alts) (row) ;
            }
          }
        if (res != NULL)
          delete res ;
        }
      else {
        if (!error)
          error = !dbase->CreateTable (tnew,FALSE); // Ohne Schluessel

        // Dazufuegen der Default - Constraint
        for ( int i = 0 ; i < AnzDefs ; i ++) {
          s.Clear ();
          for ( int j = 0 ; j < tnew->GetAnzVars () ; j++) {
            LPVARDEF v = tnew->GetVarDef(j);
            if (lstrcmp(v->GetName(),dv[i].VarName) == 0) {
              s = s + "ALTER TABLE " + ODBCGetTableName (tnew) ;
              if (dbase->DatabaseType == DT_MSSQLSERVER) {
                s = s + " ADD " ;
                DefaultStatement (s,v,AnzDefs,dv);
                s = s + " FOR " + dbase->GetAliasName (v->GetName());
                }
              else {
                s = s + " MODIFY " + dbase->GetAliasName (v->GetName());
                DefaultStatement (s,v,AnzDefs,dv);
                }
              SQLExecDirect (hstmt,s.Ptr(),SQL_NTS);
              }
            }
          }

        // Zusammenbasteln eines Vernuenftigen INSERT Strings
        if (!error) {
          LPCLKEYDEF k0;
          if (dbase->DatabaseType == DT_MSSQLSERVER) {
            k0 = tnew->GetKeyDef(0);
            if ((k0->Attribute & CLKD_AUTOINC)) {
              s.Clear ();
              s = s + "SET IDENTITY_INSERT " + ODBCGetTableName(tnew) + " ON" ;
              SQLExecDirect (hstmt,s.Ptr(),SQL_NTS);
              }
            }
          s.Clear ();
          s = s + "INSERT INTO " + ODBCGetTableName (tnew) + " (" ;
          BOOL first = TRUE ;
          for (int i = 0 ; i < told->GetAnzVars () ; i++) {
            if (td.IsToCopy (i)) {
              if (!first) s = s + "," ;
              s = s + dbase->GetAliasName (told->GetVarDef(i)->GetName()) ;
              first = FALSE ;
              }
            }
          s = s + ") SELECT " ;
          first = TRUE ;
          for (i = 0 ; i < told->GetAnzVars () ; i++) {
            if (td.IsToCopy (i)) {
              if (!first) s = s + "," ;
              s = s + dbase->GetAliasName (told->GetVarDef(i)->GetName()) ;
              first = FALSE ;
              }
            }
          s = s + " FROM " + told->GetName ();

          // SET Transaction um moeglichst keinen Ueberlauf auf dem
          // Rollback segment zu provozieren (ev. spaeter auch einmal
          // ein anderes Rollbacksegment angeben lassen)
          BeginTransaction (TRUE);
          SQLExecDirect (hstmt,s.Ptr(),SQL_NTS);
          EndTransaction ();
          if (dbase->DatabaseType == DT_MSSQLSERVER) {
            if ((k0->Attribute & CLKD_AUTOINC)) {
              s.Clear ();
              s = s + "SET IDENTITY_INSERT " + ODBCGetTableName(tnew) + " OFF" ;
              SQLExecDirect (hstmt,s.Ptr(),SQL_NTS);
              }
            }
          }
        }

      s.Clear ();
      if (!error) {
        // Jetzt wird die alte Tabelle gedroppt und von der Zwischentabelle
        // wird wieder alles rueberkopiert
        s = s + "DROP TABLE " + told->GetName ();
        SQLExecDirect (hstmt,s.Ptr(),SQL_NTS);
        }

      s.Clear ();
      if (EinzelnSchaufeln) {
        if (!error)
          DelFromTableHash(told);

        DBList FAR *res = NULL;
        if (!error) {
          static ParamBlock p;
          lmemset (&p,'\0',sizeof(p));
          p.AnzPars = 0;

          res = new DBList (tnew,0L,"",100,100,&p,FALSE);
          res->SetOrder ("");
          if (res == NULL) error = TRUE ;
          }

        if (!error) {
          for (LPDBRECORD h = res->GetFirst(); ((h != NULL) && (!error)) ; h = res->GetNext(h)) {
            LPDBREQUEST req = InitializeRequest ("",-1,DBCALLTYPE_STANDARDINSERT,0L);
            WORD TableID = tnew->GetTableID();
            WORD Version = tnew->GetVersion();
            req->SetTableID(TableID,Version);
            req->AddTableDef (TableID,Version);
            req->SetParam (1,&TableID,sizeof(TableID));
            req->AnzParam = 0;

            RecBuffer rb;
            lmemset (&rb,'\0',sizeof(rb));
            rb.AddLine (1,ADDLINEPOS_START);
            rb.act->rec[0] = h ;

            LPVOID hstmt = NULL;
            MarkTableFromINTName (NULL);
            int stat = DBCall (DBOP_GET,1,req,&hstmt,&rb);
            DBCall (DBOP_RESET,0,NULL,&hstmt,NULL);
            MarkTableFromINTName (tnew);

            rb.Clear ();
            req->ClearParams();
            req->FreeTableDefs();
            FreeRequest (req);

            error = (stat != DBCALL_SUCCESS);

            res->ThrowAtHead(h);

            row ++ ;
            if ((row % STEPWITH) == 0L)
              (* alts) (row) ;
            }
          }
        if (res != NULL)
          delete res ;
        }
      else {
        if (!error) {
          MarkTableFromINTName (NULL);
          error = !dbase->CreateTable (tnew,FALSE);
          MarkTableFromINTName (tnew);
          }

        if (!error) {
          LPCLKEYDEF k0;
          if (dbase->DatabaseType == DT_MSSQLSERVER) {
            k0 = tnew->GetKeyDef(0);
            if ((k0->Attribute & CLKD_AUTOINC)) {
              s = s + "SET IDENTITY_INSERT " + tnew->GetName() + " ON" ;
              SQLExecDirect (hstmt,s.Ptr(),SQL_NTS);
              s.Clear ();
              }
            }
          s = s + "INSERT INTO " + tnew->GetName () + " (" ;
          BOOL first = TRUE ;
          for (int i = 0 ; i < tnew->GetAnzVars () ; i++) {
            if (!first) s = s + "," ;
            s = s + dbase->GetAliasName (tnew->GetVarDef(i)->GetName()) ;
            first = FALSE ;
            }
          s = s + ") SELECT " ;
          first = TRUE ;
          for (i = 0 ; i < tnew->GetAnzVars () ; i++) {
            if (!first) s = s + "," ;
            s = s + dbase->GetAliasName (tnew->GetVarDef(i)->GetName()) ;
            first = FALSE ;
            }
          s = s + " FROM " + ODBCGetTableName (tnew);

          // SET Transaction um moeglichst keinen Ueberlauf auf dem
          // Rollback segment zu provozieren (ev. spaeter auch einmal
          // ein anderes Rollbacksegment angeben lassen)
          BeginTransaction (TRUE);
          SQLExecDirect (hstmt,s.Ptr(),SQL_NTS);
          EndTransaction ();
          if (dbase->DatabaseType == DT_MSSQLSERVER) {
            if ((k0->Attribute & CLKD_AUTOINC)) {
              s.Clear ();
              s = s + "SET IDENTITY_INSERT " + tnew->GetName() + " OFF" ;
              SQLExecDirect (hstmt,s.Ptr(),SQL_NTS);
              }
            }

          // Alle Schluessel auf dem neuen File erzeugen
          MarkTableFromINTName (NULL);
          if (!dbase->CreateAllIndex (tnew)) error = TRUE ;
          MarkTableFromINTName (tnew);
          }
        }

      s.Clear ();
      if (!error) {
        // Die Zwischentabelle kann gedroppt werden
        s = s + "DROP TABLE " + ODBCGetTableName (tnew);
        if (!dbase->TestRetCode (hstmt,SQLExecDirect (hstmt,s.Ptr(),SQL_NTS))) error = TRUE ;
        s.Clear ();
        }

      MarkTableFromINTName (NULL);

      doneWithCopy = TRUE ;
      }
    else {
      // 2. Alle alten Spalten rausloeschen (sofern sich nicht
      //    geblockt sind)
      if (!error) {
        BOOL dropDone = FALSE ;
        for (int i = 0 ; i < td.AnzVarsToDrop () ; i ++) {
          LPVARDEF v = told->GetVarDef(td.VarsToDrop[i]) ;
          if (v->VarID == 0xFFFF) {
            if (!dropDone) s = s + "ALTER TABLE " + told->GetName() + " DROP " ;
            else           s = s + ", DROP " ;
            s = s + dbase->GetAliasName (v->GetName());
            dropDone = TRUE ;
            }
          }
        // Wenn keine geblockte Spalte mehr vorhanden ist, dann auch
        // die die geblockte Spalte rausnehmen
        if ((holdBlocked(told)) && (!holdBlocked(tnew))) {
          if (!dropDone) s = s + "ALTER TABLE " + told->GetName() + " DROP " ;
          else           s = s + ", DROP " ;
          s = s + dbase->BlockVarName () ;
          dropDone = TRUE ;
          }
        if (dropDone) {
          error = !dbase->TestRetCode (hstmt,SQLExecDirect (hstmt,s.Ptr(),SQL_NTS));
          if ((error) && (AskForContinue ("Beim Drop von Spalten sind Fehler aufgetreten",told->GetName())))
            error = FALSE ;
          }
        }
      }

    // 3. Alle neuen Spalten dazunehmen (sofern nicht geblockt)
    if (!doneWithCopy) {
      s.Clear ();
      if (!error) {
        BOOL addDone = FALSE ;
        for (int i = 0 ; i < td.AnzVarsToAdd() ; i++) {
          LPVARDEF v = tnew->GetVarDef(td.VarsToAdd[i]);
          if (v->VarID == 0xFFFF) {
            if (!addDone) s = s + "ALTER TABLE " + tnew->GetName() + " ADD " ;
            else          s = s + "," ;
            if ((!addDone) && (dbase->DatabaseType != DT_MSSQLSERVER)) s = s + "(" ;
            BOOL doSize;
            s = s + dbase->GetAliasName(v->GetName()) + " " + dbase->GetTypeName (v,td.VarsToAdd[i],&doSize,tnew->GetKeyDef(0));
            if (doSize) {
              int size = v->VarSize;
              s = s + "(" + size + ")" ;
              }
            if (dbase->DatabaseType == DT_MSSQLSERVER) {
              error = !dbase->TestRetCode (hstmt,SQLExecDirect (hstmt,s.Ptr(),SQL_NTS));
              if ((error) && (AskForContinue ("Beim Hinzufügen von Spalten sind Fehler aufgetreten",told->GetName())))
                error = FALSE ;
              s.Clear ();
              }
            else
              addDone = TRUE ;
            }
          }
        // Wenn keine geblockte Spalte vorhanden war, aber jetzt eine dazugekommen ist,
        // dann die geblockte Spalte dazunehmen
        if ((holdBlocked(tnew)) && (!holdBlocked(told))) {
          if (!addDone) s = s + "ALTER TABLE " + tnew->GetName() + " ADD " ;
          else          s = s + "," ;
          if ((!addDone) && (dbase->DatabaseType != DT_MSSQLSERVER)) s = s + "(" ;
          s = s + dbase->BlockVarName() + " " + dbase->BlockTypeName();
          addDone = TRUE ;
          }
        if (addDone) {
          if (dbase->DatabaseType != DT_MSSQLSERVER) s = s + ")" ;
          error = !dbase->TestRetCode (hstmt,SQLExecDirect (hstmt,s.Ptr(),SQL_NTS));
          if ((error) && (AskForContinue ("Beim Hinzufügen von Spalten sind Fehler aufgetreten",told->GetName())))
            error = FALSE ;
          s.Clear ();
          }
        }
      }

    // 4. Alle neuen Defaultwerte per update dazuhaengen
    if ((dbase->DatabaseType != DT_MSSQLSERVER) && (!doneWithCopy)) {
      s.Clear () ;
      if ((!error) && (AnzDefs > 0)) {
        s = s + "UPDATE " + tnew->GetName() + " SET " ;
        for (int i = 0 ; i < AnzDefs ; i++) {
          if (i > 0) s = s + "," ;
          s = s + dbase->GetAliasName (dv[i].VarName) + " = ?" ;
          }
        error = (!dbase->TestRetCode (hstmt,SQLPrepare (hstmt,s.Ptr(),SQL_NTS)));

        SLONG llen[128] ;
        ConvertBuffer cb;
        for (i = 0 ; ((i < AnzDefs) && (!error)) ; i++) {
          SLONG precision = GetTypePrecision(dv[i].mType,dv[i].DefaultValue);
          llen[i] = precision;
          LPVOID sdata = ConvertTo(dv[i].mType,dv[i].DefaultValue,&cb,llen + i);
          SDWORD len = llen[i];
          if (sdata == NULL) llen[i] = SQL_NULL_DATA ;
          else if (llen[i] == 0) llen[i] = SQL_LEN_DATA_AT_EXEC(0);
          error = (!dbase->TestRetCode (hstmt,
                        SQLBindParameter (hstmt,i+1,
                        SQL_PARAM_INPUT,
                        GetCType(dv[i].mType),
                        GetSQLType(dv[i].mType,precision),
                        precision,
                        0,
                        sdata,
                        len,
                        llen + i
                    )));
          }
        if (!error)
          error = (!dbase->TestRetCode (hstmt,SQLExecute (hstmt)));
        if ((error) && (AskForContinue ("Beim Update von Spalten auf den Defaultwert sind Fehler aufgetreten",told->GetName())))
          error = FALSE ;
        }
      }

    // 5. Alle Spalten, die per add dazugekommen sind bzw. die sich auf NOT
    //     NULL geaendert haben, werden auf NOT NULL modifiziert
    if ((dbase->DatabaseType != DT_MSSQLSERVER) && (!doneWithCopy)) {
      s.Clear ();
      if (!error) {
        BOOL modifyDone = FALSE ;
        for (int i = 0 ; i < td.AnzVarsToAdd() ; i++) {
          LPVARDEF v = tnew->GetVarDef(td.VarsToAdd[i]);
          if ((v->Property & VPROP_NOTNULL) && (v->VarID == 0xFFFF)) {
            if (!modifyDone) s = s + "ALTER TABLE " + tnew->GetName() + " MODIFY " ;
            else             s = s + ", MODIFY " ;
            s = s + dbase->GetAliasName (v->GetName()) + " NOT NULL" ;
            modifyDone = TRUE ;
            }
          }
        for (i = 0 ; i < td.AnzModified() ; i++) {
          LPVARDEF v = tnew->GetVarDef(td.Modified[i]);
          LPVARDEF vold = told->GetVarDef(td.VarIDFrom (td.Modified[i]));
          if ((v->VarID == 0xFFFF) && 
              ((v->Property & VPROP_NOTNULL) && ((vold->Property & VPROP_NOTNULL) == 0)) ||
              (((v->Property & VPROP_NOTNULL) == 0) && (vold->Property & VPROP_NOTNULL))) {
            if (!modifyDone) s = s + "ALTER TABLE " + tnew->GetName() + " MODIFY " ;
            else             s = s + ", MODIFY " ;
            if (v->Property & VPROP_NOTNULL)
              s = s + dbase->GetAliasName (v->GetName()) + " NOT NULL" ;
            else
              s = s + dbase->GetAliasName (v->GetName()) + " NULL" ;
            modifyDone = TRUE ;
            }
          }
        if (modifyDone) {
          error = !dbase->TestRetCode (hstmt,SQLExecDirect (hstmt,s.Ptr(),SQL_NTS));
          if ((error) && (AskForContinue ("Beim Ändern von Spalten auf NOT NULL sind Fehler aufgetreten",told->GetName())))
            error = FALSE ;
          }
        }
      }

    // 6. Alle modifizierten Spalten aendern (sofern groessenaenderung angebracht wurde)
    //-----------------------------------------------------------------------------------
    if ((dbase->DatabaseType != DT_MSSQLSERVER) && (!doneWithCopy)) {
      s.Clear ();
      if (!error) {
        BOOL first = TRUE ;
        // Die Groessen ev. nachaendern (sofern sie wirklich groesser geworden sind)
        //-------------------------------------------------------------------------------------------------
        for (int i = 0 ; (i < td.AnzModified()) ; i++) {
          LPVARDEF vold = told->GetVarDef(td.VarIDFrom (td.Modified[i])) ;
          LPVARDEF vnew = tnew->GetVarDef(td.Modified[i]) ;
          BOOL doSize;
          LPSTR TypeName = dbase->GetTypeName (vnew,td.Modified[i],&doSize,tnew->GetKeyDef(0));
          if ((vold->VarSize < vnew->VarSize) && (vold->mType == vnew->mType) && (doSize)) {
            if (first) s = s + "ALTER TABLE " + tnew->GetName () + " MODIFY " ;
            else       s = s + ", MODIFY " ;
            s = s + dbase->GetAliasName (vnew->GetName()) + " " + TypeName + "(" + vnew->VarSize + ")" ;
            first = FALSE ;
            }
          }
        if (!first) {
          error = !dbase->TestRetCode (hstmt,SQLExecDirect (hstmt,s.Ptr(),SQL_NTS));
          if ((error) && (AskForContinue ("Beim Ändern der Spaltengröße sind Fehler aufgetreten",told->GetName())))
            error = FALSE ;
          }
        }
      }
    
    // 7. All neuen Schluessel dazuhaengen
    for (i = 0 ; ((i < td.AnzKeysToAdd()) && (!error)) ; i++) {
      BOOL keyDone = FALSE ;
      s.Clear ();
      for (int j = 0 ; j < tnew->GetAnzKeySegs() ; j++) {
        LPCLKEYDEF k = tnew->GetKeyDef(j);
        if (k->KeyNmbr == WORD(td.KeysToAdd[i])) {
          if (!keyDone) { 
            s = s + "CREATE " ;
            if (k->Attribute & CLKD_UNIQUE) s = s + "UNIQUE " ;
            s = s + "INDEX " ;

            if (dbase->DatabaseType == DT_MSSQLSERVER)
              s = s + MSIndexName (k->name,tnew) ;
            else
              s = s + k->name + tnew->GetName() ;
              
            s = s + " ON " +
                tnew->GetName() + " (" ;
            }
          else
            s = s + "," ;
          s = s + dbase->GetAliasName (tnew->GetVarDef(k->VarID)->GetName());
          keyDone = TRUE ;
          }
        }
      if (keyDone) {
        s = s + ")" ;
        error = (!dbase->TestRetCode (hstmt,SQLExecDirect (hstmt,s.Ptr(),SQL_NTS)));
        if ((error) && (AskForContinue ("Beim Erzeugen von Schlüsseln sind Fehler aufgetreten",tnew->GetName())))
          error = FALSE ;
        }
      if ((dbase->DatabaseType != DT_MSSQLSERVER) && (td.KeysToAdd[i] == 0) && (!doneWithCopy)) {
        // den PRIMARY KEY erzeugen
        BOOL keyDone = FALSE ;
        s.Clear ();
        for (int j = 0 ; j < tnew->GetAnzKeySegs() ; j++) {
          LPCLKEYDEF k = tnew->GetKeyDef(j);
          if (k->KeyNmbr == 0) {
            if (!keyDone)
              s = s + "ALTER TABLE " + tnew->GetName() + " ADD PRIMARY KEY (";
            else
              s = s + "," ;
            s = s + dbase->GetAliasName (tnew->GetVarDef(k->VarID)->GetName());
            keyDone = TRUE ;
            }
          }
        if (keyDone) {
          s = s + ")" ;
          error = (!dbase->TestRetCode (hstmt,SQLExecDirect (hstmt,s.Ptr(),SQL_NTS)));
          if ((error) && (AskForContinue ("Beim Erzeugen vom Primärschlüssel sind Fehler aufgetreten",tnew->GetName())))
            error = FALSE ;
          }
        }
      }

    // Fertig
    }

  dbase->FreeStatementHandle (hstmt);
  _inAlter = FALSE ;
  if (!error) {
    BeginTransaction (FALSE);   // Von aussen, damit die Sync hinhaut...
    return DBCALL_SUCCESS;
    }
  else
    return DBCALL_ERROR;
  }


      
