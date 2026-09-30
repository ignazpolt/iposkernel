///////////////////////////////////////////////////////////////////////
//  Verbindung zu einer SQL Datenbank
///////////////////////////////////////////////////////////////////////
#include <windows.h>
#include <stdio.h>
#include <dos.h>
#include "dds32.h"

#include "globmem.h"
#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#define MODULENUM 17
#include "winass.hpp"
#include "sqlconn.hpp"

extern LPSTR WINAPI GetIniName ();
void GetBatTemplate (LPSTR t)
  {
  GetPrivateProfileString ("DataBase","sqlbat","%s",t,128,GetIniName());
  }

#define STMTSZ  8192
DLLExport void _export WINAPI ConnectToSQL (LPTABLEDEF t,DLLHANDLE actdll,LPSTR FName)
  {
  LPSTR Buffer = LPSTR (GetGlobMem (STMTSZ));
  // 1. FileName
  LPDLLADMIN dlladmin = GetDLLAdmin();

#ifdef WIN32
  LPVOID DLLData = t->GetDLLDef();
#else
  LPVOID DLLData = t->GetDLLDef();
  if (FP_SEG(DLLData) == 0) {
    DLLData = LPVOID (GlobalLock (FP_OFF(DLLData)));
    }
#endif

  LPSTR res = dlladmin->GetDLLEntry(actdll)->DataDict_GetSQLPart (
                SQLSTMT_GETOUTNAME,t->GetName(),DLLData,0,0,Buffer,STMTSZ
                                                                  );
  if (res != NULL) {
    lstrcpy (FName,res);

    OFSTRUCT Of;
    HFILE fi = OpenFile (res,&Of,OF_CREATE | OF_WRITE);

    // 1. Header
    res = dlladmin->GetDLLEntry(actdll)->DataDict_GetSQLPart (
                  SQLSTMT_HEADER,t->GetName(),DLLData,0,0,Buffer,STMTSZ
                                                                    );
    _lwrite (fi,LPSTR(res),lstrlen(res));
    _lwrite (fi,LPSTR("\r\n"),2);

    // 2. Variablen
    for ( int i = 0 ; ; i++) {
      res = dlladmin->GetDLLEntry(actdll)->DataDict_GetSQLPart (
                  SQLSTMT_VARDEF,t->GetName(),DLLData,i,0,Buffer,STMTSZ
                                                                );
      if (res == NULL) break;
      _lwrite (fi,LPSTR(res),lstrlen(res));
      _lwrite (fi,LPSTR("\r\n"),2);
      }

    // 3. Abschluss des eigentlichen Createstatements
    res = dlladmin->GetDLLEntry(actdll)->DataDict_GetSQLPart (
                SQLSTMT_BUTTOM,t->GetName(),DLLData,0,0,Buffer,STMTSZ
                                                              );
    _lwrite (fi,LPSTR(res),lstrlen(res));
    _lwrite (fi,LPSTR("\r\n"),2);

    // 4. Allfaellig weitere Schluessel
    for ( i = 1 ; ; i++) {
      res = dlladmin->GetDLLEntry(actdll)->DataDict_GetSQLPart (
                SQLSTMT_KEYSTMT,t->GetName(),DLLData,0,i,Buffer,STMTSZ
                                                              );
      if (res == NULL) break ;

      _lwrite (fi,LPSTR(res),lstrlen(res));
      _lwrite (fi,LPSTR("\r\n"),2);
      }

    // Tabelle fertig
    _lclose (fi);
    }
  FreeGlobMem (Buffer);
  }

DLLExport void _export WINAPI ConnectToSQL (HWND hWndWorkArea,LPSTR FName)
  {
  // Oeffnen der Ausgabedatei
  OFSTRUCT Ofb;
  // Abklappern aller Data - Dictionarys
  LPVOID h;
  LPTABLEDEF t;
  LPDLLADMIN dlladmin = GetDLLAdmin();

  HFILE fib = OpenFile (FName,&Ofb,OF_CREATE | OF_WRITE);

  for ( t = GetTableAdmin()->GetFirstTableDef (&h) ;
              t != NULL ;
                    t = GetTableAdmin()->GetNextTableDef (&h) ) {
    DLLHANDLE actdll = t->GetDLLHandle ();
    char tmpName[128];
    ConnectToSQL (t,actdll,tmpName);

    char tmpstr[128];
    GetBatTemplate (tmpstr);
    _lwrite (fib,LPSTR(tmpstr),lstrlen(tmpstr));
    _lwrite (fib,LPSTR(tmpName),lstrlen(tmpName));
    _lwrite (fib,LPSTR("\r\n"),2);
    }

  _lclose (fib);

  // fertig
  }
