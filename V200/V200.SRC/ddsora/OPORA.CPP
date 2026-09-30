/*****************************************************************************
 FILE:              OPORA.CPP
 
 COPYRIGHT:         Glance AG (Steinmaur)
 
 PROJECT:           MedORA - Oracle - Anbindung an das Clinicum (Medica, Steinmaur)
 PRODUCT:           DDSORA.DLL
 
 AUTHOR:            Glance AG, CH-Steinmaur
                    Frank Loeliger
 
 DATE:              14.02.1996
 
 DESCRIPTION:       functionality of the database interface DLL
 
 ENVIRONMENT:       Windows Application
                    MS Visual C++ V1.50
                    Oracle Call Interface, Release 7.1
                    MKS - RCS is used for the revision controlling
 
 VERSION:           0.9   15.03.96 first freezed version  (beta released)
                    0.02  10.03.96 : Session together with HS and FL
                    0.1   The DLL is manually ported from the sybase DLL Rev 1.3
 
 STATUS:            beta released
 
 MODIFIED:
   02.04.96 BG  - CREATE SEQUENCE mit 'CACHE 1' ist nicht erlaubt, midestens 'CACHE 2' noetig;
          wir verzichten ab sofort auf diesen Parameter
     28.03.96 FL  - Map '= NULL' to ' IS  NULL' in Oracle's Version (AnalyseJoin and AnalyseSeq)
                - Routine myIsCharAlpha introduced
   25.03.96 FL  - Caching of sequence numbering set to 1
   18.03.96 FL  - integration of changes made by softworks
   14.03.96 FL  - some makeup preparing the freeze...
   13.03.96 FL  - Date and Time format are set by an appropriate ALTER SESSION command
   09.03.96 FL  - StandardInsert: the set differentiates betweene STRARR and LONG
                - Calcprimkey has to be called
                - NULL conversion from Oracle OCI to CLinicum values
                - changes made on original source integrated
   08.03.96 FL  - the binary coded variables (shorter than 128 characters) within GetVarString
                  has been incorrect.
                - the functionparameters for to_date have been in the wrong order
                - StandardInsert must not eliminate res->first and insstmt::StoreData
                  is not necessary!
                - Month must be adjusted when read from oracle
                - Set takes care of STRARR as well
 
   07.03.96 FL  - new routine adapted to the new return code behaviour
                - oracle informs about the end of rows earlier than sybase does,
                  we introduced a new state CS_LAST_DATA
                - Mapping of OCI_SUCCEED was not done correct in execute before
                - INSERT of LONG RAW Data does not need a 0x, but some "'".
   06.03.96 FL  - return code in Selectstatement returns now END_OF_DATA if no more data will
                  be available
   05.03.96 FL  - do not use local returnvariables
                - no subqueries
                - timelog more detailed.
   04.03.96 FL  - the automatically generated value must be returned to the caller
   02.03.96 FL  - a new class seqcheck and appropriate insert routines realized
                - Create Sequence added
   01.03.96 FL  - VARLEN for zero terminated strings adapted to deliver strings inkl.
                  the zero to clinicum
                - implementation of sequence numbers for autoinc
   29.02.96 FL  - ROWCOUNT added
                - Commit and Rollback added
   28.02.96 FL  - CreateTable has now symmetrical new and delete statements
                - Old Begin and Abort Transaction moved to sybase part of code
                - Outerjoin not applied if a subquery is generated
                - VarInd and VarRetCode introduced
   27.02.96 FL  - DOLOG disabled
                - Macro SUPPRESS_REDSCREEN_FORCREATE introduced to suppress the create question screen
                - Names starting with a '_' are converted into a Name starting with 'x'
                - Names of Indizes are made unique by appendig the Tablename (max 30 Characters)
                - VAR_CHAR greater than 254 char are mapped to varchar2
                - VAR_CHAR greater than 2000 char are mapped to LONG VARCHAR (max. one occurance per table)
   21.02.96 FL  main() routine deleted to use this module in the DLL
   20.02.96 FL  Return codes controlled
   19.02.96 FL  Structure ColInfo adapted,
                div. Compilererrors corrected
                Conversion of Date realized
   15.02.96 FL  BindColData, GetSybDataType, CreateTable and GetTypeName adapted to Oracle
   14.02.96 FL  new class oracle and dbase introduced
   14.02.96 FL  created this document based on sybase code
   09.02.96 BG  some comments
   04.06.96 HS  VAR_BLOB introduced
 
*****************************************************************************/

/*
  At this point the original source starts.

  Attn: The word 'sybase' was not been translated to 'oracle', intentionally.
        This ensures easier integration of adapted original code.

  All changes made to switch from sybase to oracle are commented as followed:
 
  A)
#if defined(DLL_ORACLE)         // the oracle code follows
#else                           // the sybase code follows
#endif                          // DLL_ORACLE
 
  B)  >>FL 14.02.96: comment          // the new code follows
      <<FL 14.02.96

  C)  // FL 14.02.96                  // one line added
 
  D)  special handling within routines
#if defined(ORACLE_CONVENTIONS) // the oracle code follows
#else                           // the sybase code follows  ORACLE_CONVENTIONS
#endif                          // ORACLE_CONVENTIONS
*/

//////////////////////////////////////////////////////////////
//  Anbindung an das Clinicum
//////////////////////////////////////////////////////////////
//
//
//  $Header:   P:/marille/clinicum/ddsora/rev/opora.cpv   1.113   07 Jun 2000 10:22:40   Wolfgang  $
//  $Log:   P:/marille/clinicum/ddsora/rev/opora.cpv  $
// 
//    Rev 1.113   07 Jun 2000 10:22:40   Wolfgang
// 1.) timestr fuer Log-Ausgabe korrigiert.
// 2.) DBOP_PARSE eingebaut.
// 
//    Rev 1.112   22 May 2000 19:26:22   Martin
// Aufruf von STARTUP eingebaut (laut Uwe, nur ORBIS)
// 
//    Rev 1.111   14 May 2000 14:15:42   Hannes
// Pausenstring eingebaut
// 
//    Rev 1.110   10 Apr 2000 12:34:48   Hannes
// 
//    Rev 1.109   17 Mar 2000 13:07:16   Martin
// Passwort aus SetUsername ist jetzt staerker als das aus floydst.dll
// 
//    Rev 1.108   07 Feb 2000 20:44:00   Martin
// oracmds.log in faults.log-Verzeichnis
// 
//    Rev 1.107   17 Jan 2000 21:05:38   Martin
// Einbau von UserOrb
// 
//    Rev 1.106   30 Nov 1999 17:41:24   Wolfgang
// 1.) Subselect ohne WHERE-Bedingung behandelt Klammer-Zu richtig.
// 
//    Rev 1.105   25 Nov 1999 03:06:48   Hannes
// $ - Abfrage mit LONGS...
// 
//    Rev 1.104   20 Oct 1999 07:52:08   Hannes
// 
//    Rev 1.103   08 Oct 1999 00:07:52   Hannes
// Verbesserte Syntax - Pruefung (GetFullFieldName...)
// 
//    Rev 1.102   24 Sep 1999 13:41:04   Martin
// CLTRANS in Orbis-Variante nicht erzeugen
// 
//    Rev 1.101   14 Sep 1999 08:33:02   Hannes
// kleine Fehlerkorrektur in AnalyseSeq
// 
//    Rev 1.100   13 Sep 1999 23:37:24   Hannes
// DscList als Member von sybstmt
// 
//    Rev 1.99   10 Sep 1999 15:18:38   Hannes
// Synonymgenerator
// 
//    Rev 1.98   20 Aug 1999 20:16:42   Martin
// Dieses scheiss ResetDscList auch noch in TestTableDef rein
// 
//    Rev 1.97   18 Aug 1999 10:09:14   Hannes
// Indikatorabfrage bei PLSQL Ausgabeparameter...
// 
//    Rev 1.96   13 Aug 1999 11:59:44   Martin
// OrderedHint in Orbis ausschalten
// 
//    Rev 1.95   12 Aug 1999 18:27:52   Martin
// Rights richtig
// 
//    Rev 1.94   12 Aug 1999 17:37:44   Martin
// default-Werte
// 
//    Rev 1.93   04 Aug 1999 10:39:52   Hannes
// Verbesserte Wortsuche..ÿ
// 
//    Rev 1.92   28 Jul 1999 11:58:52   Wolfgang
// 1.) ResetDscList in DBCurrentDateTime eingebaut.
// 
//    Rev 1.91   27 Jul 1999 08:41:30   Hannes
// Vergroesserung von MaxBlockedSize
// 
//    Rev 1.90   26 Jul 1999 13:39:04   Hannes
// Diverse kl. Verschoenerungen
// 
//    Rev 1.89   26 Jul 1999 08:13:44   Hannes
// Sequence - Name im ORBIS - Fall
// 
//    Rev 1.88   16 Jul 1999 18:19:46   Martin
// ORACLE_Check=Orbis eingebaut
// 
//    Rev 1.87   08 Jul 1999 08:45:28   Hannes
// StraigthForward...
// 
//    Rev 1.86   07 Jul 1999 07:52:42   Hannes
// Transaktionshandling mit Portokolliert...
// 
//    Rev 1.85   04 Jul 1999 23:42:50   Hannes
// Fehlerkorrektur Aufruf Variablenbindung...
// 
//    Rev 1.84   17 Jun 1999 12:04:14   Martin
// Fehler in Syncstatement korrigiert
// 
//    Rev 1.83   15 Jun 1999 16:26:04   WOLFGANG
// 1.) DBCurrentDateTime und datetimestmt neu.
// 
//    Rev 1.82   29 Apr 1999 12:36:24   Martin
// Testsequence: sequence does not exist ignoriert
// 
//    Rev 1.81   27 Apr 1999 01:46:48   Hannes
// Diverse Speicherfresser
// 
//    Rev 1.80   29 Mar 1999 11:35:00   Martin
// OrderStatement korrigiert, DelFromTableHash setzt nur IsTested aus FALSE
// 
//    Rev 1.79   16 Mar 1999 11:28:30   Hannes
// Minimaleinbau Prozedur - Rueckgabewerte
// 
//    Rev 1.78   08 Mar 1999 17:07:42   Hannes
// closedone in Ordnung gebracht
// 
//    Rev 1.77   08 Mar 1999 17:04:46   Hannes
// OOpen->CloseDone = FALSE
// 
//    Rev 1.76   05 Mar 1999 10:54:38   Hannes
// SyncStatement
// 
//    Rev 1.74   19 Feb 1999 17:21:38   Hannes
// Fehler bei DROP SYNONYM ignorieren
// 
//    Rev 1.73   15 Feb 1999 21:43:44   Hannes
// Sortiersegmente auch in der 2. Tabelle
// 
//    Rev 1.72   11 Feb 1999 11:39:02   Hannes
// Trigger vor dem Erzeugen loeschen
// 
//    Rev 1.71   05 Feb 1999 21:37:28   Martin
// verbessertes Errorhandling
// 
//    Rev 1.70   29 Jan 1999 10:44:56   Hannes
// Prototyp von GetVarString
// 
//    Rev 1.69   29 Jan 1999 10:36:52   Wolfgang
// 1.) MakeTimeStamp eingebaut.
// 2.) 0-Character beseitigt.
// 
//    Rev 1.68   28 Jan 1999 12:21:12   Hannes
// Erweiterte SQL - Syntax
// 
//    Rev 1.67   19 Jan 1999 19:27:16   Hannes
// SetUserName
// 
//    Rev 1.66   11 Jan 1999 08:27:34   Hannes
// Synonyme
// 
//    Rev 1.65   09 Oct 1998 18:18:02   Martin
// Synonymerzeugung, Sequenceueberpruefung, GRANT...
// 
//    Rev 1.64   10 Aug 1998 18:05:06   Martin
// Prefix-Fehler bei Sequences
// 
//    Rev 1.63   04 Aug 1998 17:56:26   Hannes
// Timestamp
// 
//    Rev 1.62   02 Jul 1998 10:27:04   Martin
// unnoetige CREATE TABLE Versuche beim UPDATE verhindert
// 
//    Rev 1.61   10 Jun 1998 12:24:32   Martin
// BigRbsName ...
// 
//    Rev 1.60   08 Jun 1998 18:57:22   Martin
// DatabasePassword in floydst.dll
// 
//    Rev 1.59   16 May 1998 14:12:30   Martin
// SortParam ...
// 
//    Rev 1.58   13 May 1998 14:03:54   Martin
// Sybase raus,
// AnalyseJoin ruft jetzt AnalyseSeq auf (Bitte GUT testen!)
// 
//    Rev 1.57   11 May 1998 20:22:40   Martin
// Strings brauchen ein 0-Byte am Ende.
// (Warum ist das solange gut gegangen !?!?)
// 
//    Rev 1.56   28 Apr 1998 16:45:58   Martin
// delete cc erst nach der letzten Verwendung ...
// 
//    Rev 1.55   15 Apr 1998 21:34:58   Hannes
// Erzeugen des Triggers beim Test unbedingt...
// 
//    Rev 1.54   19 Mar 1998 20:45:28   Hannes
// StraightForward mit Count -> Orderstatement verkuerzt
// 
//    Rev 1.53   06 Mar 1998 17:17:38   Hannes
// 
//    Rev 1.52   03 Mar 1998 20:03:42   Hannes
// Neue ORACLE - Collating Sequence
//
//    Rev 1.51   23 Feb 1998 20:03:46   Hannes
// Fehlender Sync - Parameter -> Syntaktische Korrektur
//
//    Rev 1.50   19 Jan 1998 16:51:42   Martin
// ActUserName caseinsensitiv
//
//    Rev 1.49   09 Jan 1998 18:12:46   Hannes
// AnalyseSeq in StamdardExecute
//
//    Rev 1.48   28 Nov 1997 16:40:54   Hannes
// Beim Testen: CloseDone = TRUE
//
//    Rev 1.47   21 Nov 1997 10:38:02   Hannes
// Verbesserung des For - STatements
//
//    Rev 1.46   24 Sep 1997 16:26:54   Hannes
// Fehlerkorrektur in der Sync - Statement
//
//    Rev 1.45   24 Jul 1997 12:14:56   Hannes
//
//    Rev 1.44   16 Jul 1997 16:44:44   Hannes
// Tabellennamen mit Versionsnummer
//
//    Rev 1.43   01 Jul 1997 17:08:14   Hannes
//
//    Rev 1.42   23 May 1997 11:00:58   Hannes
// Testen der Schluessel
//
//    Rev 1.41   15 Apr 1997 13:01:32   Martin
// Fehlerhandling etwas verbessert
//
//    Rev 1.40   10 Apr 1997 10:36:26   Hannes
// Erzeugen der Sequences
//
//    Rev 1.39   29 Jan 1997 16:50:52   HANNES
// GetRecCopy, Stack fuer Analyseseq
//
//    Rev 1.38   29 Jan 1997 15:18:34   HANNES
//
//    Rev 1.37   20 Jan 1997 11:56:08   HANNES
//
//    Rev 1.36   13 Jan 1997 11:13:52   MARTIN
// StationLog: nach jeder Zeile schliessen
//
//    Rev 1.35   10 Jan 1997 15:04:40   HANNES
// Fehlerkorrektur: Wenn ein SkipSpace ans ende des Strings gelangt, dann wird
// hinter dem String weitergeparst, was schlimme Folgen haben koennte??
//
//    Rev 1.34   08 Jan 1997 18:59:10   MARTIN
// mitloggen der letzten n SQL-statements
//
//    Rev 1.33   07 Jan 1997 18:08:56   MARTIN
// StoreRow fuer volle Tabellen -> VarID-Handling ...
//
//    Rev 1.32   17 Dec 1996 11:16:14   HANNES
//
//    Rev 1.31   17 Dec 1996 11:11:38   HANNES
// Stored Procedures
//
//    Rev 1.29   12 Dec 1996 19:13:26   MARTIN
// RetriesOnBlocked, CancelAlways, OrderedHint
//
//    Rev 1.28   06 Dec 1996 14:21:30   HANNES
//
//    Rev 1.27   05 Dec 1996 12:47:40   HANNES
//
//    Rev 1.26   05 Dec 1996 11:39:14   HANNES
//
//    Rev 1.25   05 Dec 1996 11:11:02   HANNES
//
//    Rev 1.24   26 Nov 1996 08:04:44   HANNES
// Automatischer Update
//
//    Rev 1.23   06 Nov 1996 18:38:30   MARTIN
// Umstellung orlon -> olog (ora72win.dll !)
//
//    Rev 1.22   30 Oct 1996 11:27:16   HANNES
// Schluesselsegmente fuer das Synccond am Ende des Parameterblockes, da die
// alten Parameter auch im Fall von GETNEXT,GETPREV benoetigt werden
//
//    Rev 1.21   16 Oct 1996 19:02:38   GERHOLD
// case DBOP_ENDOFCONVERSION :    return DBOP_SUCCESS;
//
//    Rev 1.20   01 Oct 1996 16:40:08   MARTIN
// Moeglichkeit eingebaut, in den extra join Bedingungen Parameter aus
// dem Script zu verwenden (war in Btrieve schon seit Juni 96 drin)
//
//    Rev 1.19   13 Sep 1996 16:47:26   HANNES
//
//    Rev 1.18   06 Sep 1996 11:06:24   HANNES
// Auch Views beim Testen verwenden
//
//    Rev 1.17   02 Sep 1996 10:26:08   HANNES
// Formatierung der BlockVarName, 2 Spaces eingerueckt
//
//    Rev 1.16   16 Aug 1996 21:27:52   MARTIN
// "=" -> "(+)=" auch wenn Nummer folgt (nicht nur bei %n) (AnalyseJoin)
//
//    Rev 1.15   16 Aug 1996 20:45:56   MARTIN
// peinlich: RecsToGet kann auch -1 sein (alle)
//
//    Rev 1.14   16 Aug 1996 19:36:52   MARTIN
// canDone leider raus (Begruendung: siehe dort)
//
//    Rev 1.13   13 Aug 1996 22:08:32   MARTIN
// 1.) VarID auch in Joins
// 2.) Listen schneller
//
//    Rev 1.12   13 Aug 1996 18:53:36   MARTIN
// AnalyseJoin: in SUB-Selects keine Alias-Namen
//
//    Rev 1.11   22 Jul 1996 18:33:26   MARTIN
// IS NULL Nicht im UPDATE Fall
//
//    Rev 1.10   10 Jul 1996 19:50:40   MARTIN
// nRows: bei views auch Blobs beruecksichtigen (nRows = 1)
//
//    Rev 1.9   05 Jul 1996 20:24:00   MARTIN
// -Logging verbessert
// -IS NOT NULL in AnalyseSeq
// -IS (NOT) NULL auch bei %1 = NULL
//
//    Rev 1.8   04 Jul 1996 16:32:08   MARTIN
// oql-file erzeugen
//
//    Rev 1.7   26 Jun 1996 12:18:34   MARTIN
// beim Blocked Teil: nCols(ti)-1 !!!!
//
//    Rev 1.6   24 Jun 1996 18:48:38   MARTIN
// IS NULL richtiggestellt, IS NOT NULL eingebaut
//
//    Rev 1.5   24 Jun 1996 17:20:54   MARTIN
// GetGlobMem (lstrlen(..) + 1 (!!!!) )
//
//    Rev 1.4   20 Jun 1996 23:11:20   MARTIN
//
//    Rev 1.3   18 Jun 1996 02:24:02   HANNES
//
//    Rev 1.2   17 Jun 1996 15:48:52   HANNES
//
//    Rev 1.1   31 May 1996 20:48:24   MARTIN
//
//    Rev 1.0   24 May 1996 14:38:46   JOERG
// Initial revision.
//Revision 1.23  1996/03/28  20:21:59  frank
//AnalyseSeq auch noch angepasst an IS NULL
//
//Revision 1.22  1996/03/28  18:49:40  frank
//INSERT Statemschine geaendert, so dass auch Ziffern erkannt werden
//
//Revision 1.21  1996/03/28  17:36:59  frank
//Abbildung '= NULL' auf 'IS NULL'
//
//Revision 1.18  1996/03/18  18:30:52  frank
//erste ausgelieferte version
//
// REINTEGRATED >>> FL 10.03.96
//    Rev 1.11   19 Mar 1996 21:15:36   MARTIN
// -outerjoins fuer hierarichisch tieferliegende Tabellen mitschleifen
// -indikator fuer Null - Werte
// -bei Joins auf die volle Tabellendefinition eingehen
// -Wherebedingung bei Listen auf ein EXEC abpruefen
//
//    Rev 1.10   08 Mar 1996 12:58:32   MARTIN
// HEX-Codierung in GetVarString->IsFixed->default korrigiert
//
//    Rev 1.9   08 Mar 1996 00:02:26   HANNES
// Null - Values
// Fehler in GetVarString
// Fehlerhandling 'unkritischer' Fehler
// Syntaxfehler in SyncStatement
//
//    Rev 1.8   04 Mar 1996 23:45:36   HANNES
// CHAR->VARCHAR, Default NULL, keine Leeren Strings in die Datenbank
//
//    Rev 1.7   04 Mar 1996 17:23:28   HANNES
// WhereDone dem SyncStatement uebergeben
// Speicherfresser in CreateTable
// VarLen dem GetVarString uebergeben
//
//    Rev 1.6   04 Feb 1996 15:40:54   hannes
// #define NOCOMPILE
//
//    Rev 1.5   02 Feb 1996 14:30:24   MARTIN
// dds32.h
//
//    Rev 1.4   01 Feb 1996 15:55:24   HANNES
// Feineres Handling der Joindefinition: Abhaengig von TypeOfJoin wird ein
// unterschiedliches Verhalten bezueglich inner / outer Join angewendet. Zu
// diesem Zwecke wurde der Compiler der Join - Definition erweitert:
// Neue Syntax: ... join [ inner | outer ] with ...
// Wird keines dieser neuen Schluesselwoerter im Compiler angegeben, dann blei
// das Standardverhalten erhalten.
//
// REINTEGRATED <<< FL 10.03.96
//Revision 1.14  1996/03/09  14:20:31  frank
//kleinere bugfixes
//
//Revision 1.13  1996/03/07  08:39:29  frank
//bis und mit patient
//
//Revision 1.12  1996/03/01  17:35:41  frank
//noch ohne Sequenz
//
//Revision 1.11  1996/03/01  08:27:48  frank
//dds startet sauber
//
//Revision 1.9  1996/02/26  09:50:58  frank
//creation is partly tested
//
//Revision 1.8  1996/02/23  14:34:54  frank
//first sucessfull dds _Test
//
//Revision 1.7  1996/02/22  09:15:57  frank
//first DLL version
//
//Revision 1.6  1996/02/19  20:23:41  frank
//date conversion and
//compilation errors
//typ
//
//Revision 1.5  1996/02/16  20:09:05  frank
//basically the execute and transactional part has been realized
//outerjoin handling has also been done
//first compilation steps and a not perfect mapping for VarLen
//has been done
//
//Revision 1.4  1996/02/15  18:58:16  frank
//CreateTable and BindColData ported
//Typemapping done
//
// Revision 1.3  1996/02/14  20:01:47  frank
//connection establishment ported
//
//Revision 1.2  1996/02/14  14:24:13  frank
//first comments bg
//
//
//    Rev 1.3   20 Jan 1996 11:17:00   HANNES
//
//    Rev 1.2   13 Jan 1996 15:44:28   HANNES
// Letze Version vor der Umstellung auf die CS - Library
//
//    Rev 1.1   02 Jan 1996 22:20:52   HANNES
//
//    Rev 1.0   04 Dec 1995 10:06:12   HANNES
// Initial revision.
//
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>           // >> FL 14.02.96
#include <ctype.h>            // >> FL 22.02.96
#include "dds32.h"
#define WIN3  1

#ifdef _DEBUG
  #define ORACLE_SHOWRESULTS  1
#endif

#include <string.h>
extern "C" {
  #include <oratypes.h>
  #include <ocidfn.h>       // LDA and CDA struct declarations
  #include <ociapr.h>
  #include "ocicons.h"      // oci constants additionally used
}
#include "syb2ora.hpp"      // additional oci porting routines

#define NODDSDATA
#include "dds.hpp"
#include "globmem.h"
#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#define MODULENUM 912
#include "winass.hpp"
#include "dbrecord.hpp"
#include "hash.hpp"
#define NOCOMPILE
#include "compile.hpp"
#include "resadmin.hpp"
#include "sqlconn.hpp"

#define OPORA_MAIN
#include "opora.hpp"

// fuer floydst.dll-Abfrage:
#include "lisencr.hpp"

#ifdef _DEBUG
  #define SUPPRESS_REDSCREEN_FORCREATE 1   // do not show the createmessage screen
  #define DEBUG_FIRST_CALL 1               // Show a red screen the first time DBCall is called
 
  static BOOL dbgfirst = TRUE;
#endif

static BOOL OrbisGetestet = FALSE;
static BOOL KundeIsOrbis = FALSE;
BOOL IsOrbis (void)
  {
  if (!OrbisGetestet) {
    char outstr[128];
    if (!SearchFSItem ("Kunde",outstr,sizeof(outstr)))
      lstrcpy(outstr,"Clinicum");
    if (!lstrcmp(outstr,"ORBIS"))
      KundeIsOrbis = TRUE;
    OrbisGetestet = TRUE;
    }
  return KundeIsOrbis;
  }

static int RetriesOnBlock = 0;
static BOOL CancelAlways = FALSE;
static BOOL NoOrderedHint = FALSE;
static int LogCount = 0;

BOOL DoLog(void)
  {
  static BOOL FirstTime = TRUE;
  static BOOL doLog;
  static BOOL ScrollLockOnly;
  if (FirstTime) {
    char buf[20];
    GetPrivateProfileString ("DataBase","DoLog", "no", buf, sizeof(buf),GetIniName());
    doLog = (lstrcmp(buf,"yes") == 0);
    GetPrivateProfileString ("DataBase","ScrollLockOnly", "no", buf, sizeof(buf),GetIniName());
    ScrollLockOnly = (lstrcmp(buf,"yes") == 0);
    RetriesOnBlock = GetPrivateProfileInt ("Oracle","RetriesOnBlock",0,GetIniName());
    GetPrivateProfileString ("Oracle","CancelAlways", "no", buf, sizeof(buf),GetIniName());
    char def[4];
    if (IsOrbis())
      strcpy(def,"no");
    else
      strcpy(def,"yes");
    GetPrivateProfileString ("Oracle","OrderedHint", def, buf, sizeof(buf),GetIniName());
    NoOrderedHint = (lstrcmp(buf,"no") == 0);
    LogCount = GetPrivateProfileInt ("Oracle","LogCount",0,GetIniName());
    FirstTime = FALSE ;
    }
  if (doLog && ScrollLockOnly) {
    return ((GetKeyState(VK_SCROLL) & 1) == 1);
    }
  return doLog;
  }

void ltoarechts(DWORD l,LPSTR a)
  {
  *a++ = char((l / 1000000L) % 10L) + '0';
  *a++ = char((l / 100000L) % 10L) + '0';
  *a++ = char((l / 10000L) % 10L) + '0';
  *a++ = char((l / 1000L) % 10L) + '0';
  *a++ = char((l / 100L) % 10L) + '0';
  *a++ = char((l / 10L) % 10L) + '0';
  *a++ = char(l % 10L) + '0';
  *a = '\0';
  }

extern DLLExport LPSTR _export WINAPI GetStationLogFile (LPSTR name);
static char winassstr[2048];
static char OraCmdsName[128];
static DWORD lastT;
void LogCmd (LPSTR txt,DWORD startT,DWORD endT,LPSTR ParamString)
  {
  OFSTRUCT Of;
  if (*OraCmdsName == '\0')
    lstrcpy(OraCmdsName,GetStationLogFile ("oracmds.log"));
  HFILE f;
  int retry = 0;
#define MAX_RETRY 20
  while (retry < MAX_RETRY) {
    f = OpenFile (OraCmdsName,&Of,OF_READWRITE | OF_SHARE_EXCLUSIVE);
    if (f == HFILE_ERROR) {
      if (Of.nErrCode == 32) {    // hat gerade jemand anderer geoeffnet ....
        DWORD t0 = GetTickCount ();
        while ((GetTickCount() - t0) < 200L);
        }
      else {
        f = OpenFile (OraCmdsName,&Of,OF_CREATE);
        _lclose(f);
        }
      retry++;
      }
    else
      retry = MAX_RETRY;
    }
  if (f >= 0) {
    _llseek (f,0L,SEEK_END);
    char timestr[64];
    // ltoarechts(time,timestr);
    wsprintf (timestr,"(P: %8ld) [%8ld - %8ld (= %5ld)] - ",startT - lastT,startT,endT,endT - startT);
    lastT = endT;
    _lwrite (f,timestr,lstrlen(timestr));
    _lwrite (f,txt,lstrlen(txt));
    if (ParamString != NULL) {
      _lwrite (f," (",2);
      _lwrite (f,ParamString,lstrlen(ParamString));
      _lwrite (f,")\r\n\r\n",5);
      }
    else
      _lwrite (f,"\r\n\r\n",4);
    _lclose (f);
    }
  else
    MessageBeep (0);
  }

static HFILE slf;
static char StationLogName[128];
static int StationLogNameLen = 0;
static int ActLogNum = 0;
void BeginStationLog (LPSTR txt,DWORD time)
  {
  OFSTRUCT Of;
  if (StationLogNameLen == 0) {
    lstrcpy(StationLogName,GetStationLogFile ("dbg.log"));
    StationLogNameLen = lstrlen(StationLogName);
    }
  StationLogName[StationLogNameLen - 2] = ((ActLogNum / 10) % 10) + '0';
  StationLogName[StationLogNameLen - 1] = (ActLogNum % 10) + '0';
  ActLogNum++;
  if (ActLogNum >= LogCount)
    ActLogNum = 0;
  int retry = 0;
  while (retry < MAX_RETRY) {
    slf = OpenFile (StationLogName,&Of,OF_CREATE);
    if (slf == HFILE_ERROR) {
      DWORD t0 = GetTickCount ();
      while ((GetTickCount() - t0) < 200L);
      retry++;
      }
    else
      retry = MAX_RETRY;
    }
  if (slf >= 0) {
    _llseek (slf,0L,SEEK_END);
    char mydate[64],mytime[64];
    char mydatetime[128];
    _strdate (mydate);
    _strtime (mytime);
    char timestr[15];
    ltoarechts(time,timestr);
    wsprintf(mydatetime,"%s, %s, %s - ",LPSTR(mydate),LPSTR(mytime),timestr);
    _lwrite (slf,mydatetime,lstrlen(mydatetime));
    _lwrite (slf,txt,lstrlen(txt));
    _lwrite (slf,"\r\n",2);
    _lclose (slf);
    }
  else
    MessageBeep (0);
  }

void WriteStationLog (LPSTR txt,DWORD time)
  {
  OFSTRUCT Of;
  int retry = 0;
#define MAX_RETRY 20
  while (retry < MAX_RETRY) {
    slf = OpenFile (StationLogName,&Of,OF_READWRITE | OF_SHARE_EXCLUSIVE);
    if (slf == HFILE_ERROR) {
      DWORD t0 = GetTickCount ();
      while ((GetTickCount() - t0) < 200L);
      retry++;
      }
    else
      retry = MAX_RETRY;
    }
  if (slf >= 0) {
    _llseek (slf,0L,SEEK_END);
    char timestr[15];
    ltoarechts(time,timestr);
    lstrcat(timestr," - ");
    _lwrite (slf,timestr,lstrlen(timestr));
    _lwrite (slf,txt,lstrlen(txt));
    _lwrite (slf,"\r\n",2);
    _lclose (slf);
    }
  else
    MessageBeep (0);
  }

void EndStationLog (void)
  {
  }

/*------< Klasse sybase zur Herstellung der Verbindung >--------*/
//#define MAXBLOCKEDSIZE  0x5000
#define MAXBLOCKEDSIZE  0xFFFF
struct TableData {
  BOOL IsTested;
  };
struct ColData {
  char TypeName[32];
  };

LongString FAR *VarAliasName;     // ATTN: the lifetime of this Name ends by the next call of GetAliasName !!!
LongString FAR *VarSequenceName;  // ATTN: the lifetime of this Name ends by the next call of GetSequenceName !!!
LPSTR GetAliasName (LPSTR Name)
  { // ensure alpha starting and namelen <= 30
  (*VarAliasName).Clear();
  if ( !isalpha(Name[0]) )
    (*VarAliasName) = (*VarAliasName) + PREFIX_ADAPTION + &Name[1];
  else
    (*VarAliasName) = (*VarAliasName) + Name;
  if (lstrlen((*VarAliasName).Ptr()) > cMAX_VARNAMESIZE) {
    char str[cMAX_VARNAMESIZE+1];
    lstrcpyn(str, (*VarAliasName).Ptr(), cMAX_VARNAMESIZE);
    str[cMAX_VARNAMESIZE] = 0;
    (*VarAliasName).Clear();
    (*VarAliasName) = (*VarAliasName) + str;
    } // if
  return (*VarAliasName).Ptr();
  } // GetAliasName

LPSTR GetKeyFieldName (LPSTR Name)
  {
  static char KFName[256];
  lstrcpy (KFName,"KF_");
  return strncat (KFName,GetAliasName (Name),cMAX_VARNAMESIZE - 3);
  }


LPSTR GetSequenceName (LPTABLEDEF td)
  {
  static char SPrefix[64];
  if (td->GetTableProperty ("ORACLE_SeqName",SPrefix,sizeof(SPrefix)) > 0) {
    return SPrefix;
    }
  char TCheck[64];
  if (td->GetTableProperty ("ORACLE_Check",TCheck,sizeof(TCheck)) > 0) {
    if ((lstrcmp(TCheck,"Orbis") == 0) && IsOrbis()) {
      if (td->GetTableProperty ("ORBIS_SeqName",SPrefix,sizeof(SPrefix)) > 0) {
        return SPrefix;
        }
      }
    }
  (*VarSequenceName).Clear();
  (*VarSequenceName) = (*VarSequenceName) + PREFIX_SEQUENCE + ORAGetTableName (td,FALSE);
  if (lstrlen((*VarSequenceName).Ptr()) > cMAX_SEQUENCENAME) {
    char str[cMAX_SEQUENCENAME+1];
    lstrcpyn(str, (*VarSequenceName).Ptr(), cMAX_SEQUENCENAME);
    str[cMAX_SEQUENCENAME] = 0;
    (*VarSequenceName).Clear();
    (*VarSequenceName) = (*VarSequenceName) + str;
    } // if
  return (*VarSequenceName).Ptr();
  } // GetSequenceName

#define MAXROWSBUFFERED   64

class FAR seqcheck : public sybstmt {
 private:
  long controlseqnum;
 public :
  seqcheck () : sybstmt () { controlseqnum = 0;}
  virtual int nRows (LPTABLEDEF ti,BOOL ignoreBlob = FALSE)
    { return 1 ; }
  virtual int nCols (LPTABLEDEF ti)
    { return 1 ; }
  virtual BOOL StoreData (LPTABLEDEF ti,int Row);
  virtual void GetColInfo(LPTABLEDEF ti);
  virtual ~seqcheck () { }
  long lastseqnum () { return controlseqnum; }
  };

class FAR insstmt : public sybstmt {
 public :
  int va ;
  insstmt () : sybstmt () { }
  virtual int nRows (LPTABLEDEF ti,BOOL ignoreBlob = FALSE)
    { return 1 ; }
  virtual int nCols (LPTABLEDEF ti)
    { return 1 ; }
  virtual BOOL StoreData (LPTABLEDEF ti,int Row);
  virtual void GetColInfo(LPTABLEDEF ti);
  virtual ~insstmt () { }
  };

class FAR tablecheck : public sybstmt {
 public :
  tablecheck () : sybstmt () { }
  virtual int nRows (LPTABLEDEF ti,BOOL ignoreBlob = FALSE)
    { return 300 ; }
  virtual int nCols (LPTABLEDEF ti)
    { return 1 ; }
  virtual BOOL StoreData (LPTABLEDEF ti,int Row);
  virtual void GetColInfo(LPTABLEDEF ti);
  virtual ~tablecheck () { }
  };

class FAR colcheck : public sybstmt {
 public :
  hash FAR *colhash;
  colcheck () : sybstmt ()
    {
    colhash = new hash (111,STRKEY);
    }
  virtual int nRows (LPTABLEDEF ti,BOOL ignoreBlob = FALSE)
    { return 300 ; }
  virtual int nCols (LPTABLEDEF ti)
    { return 2 ; }
  virtual BOOL StoreData (LPTABLEDEF ti,int Row);
  virtual void GetColInfo(LPTABLEDEF ti);
  virtual ~colcheck () { delete colhash ; }
  };

class FAR liststmt : public sybstmt {
 public :
  liststmt () : sybstmt () { }
  PrimKey kLast;
  virtual BOOL StoreData (LPTABLEDEF ti,int Row);
  virtual void GetColInfo(LPTABLEDEF ti);
  virtual ~liststmt () { }
  };

class FAR datetimestmt : public sybstmt {
 private:
  packdatetime datetime;
 public :
  datetimestmt () : sybstmt () { lmemset (&datetime, 0, sizeof (datetime));}
  virtual int nRows (LPTABLEDEF ti,BOOL ignoreBlob = FALSE)
    { return 1 ; }
  virtual int nCols (LPTABLEDEF ti)
    { return 1 ; }
  virtual BOOL StoreData (LPTABLEDEF ti,int Row);
  virtual void GetColInfo(LPTABLEDEF ti);
  virtual ~datetimestmt () { }
  void DateTime (FAR packdatetime * pdt) { *pdt = datetime; }
  };

LPSTR GetParNr (LPSTR h,int FAR *Nr)
  {
  *Nr = 0 ;
  for ( ; ((*h >= '0') && (*h <= '9')) ; h ++ ) {
    *Nr = *Nr * 10 + *h - '0' ;
    }
  (*Nr) ++ ;
  return h ;
  }

BOOL myIsCharAlpha(char ch)
  {
    return ( IsCharAlpha(ch) ||
             ((ch >= '0') && (ch <= '9')) ||
             (ch == '_')
           );
  } // myIsCharAlpha

BOOL myIsCharAlpha1(char ch,char ch1)
  {
    return ( IsCharAlpha(ch) ||
             ((ch >= '0') && (ch <= '9')) ||
             (ch == '_') ||
             ((ch == '.') && (ch1 >= '0') && (ch1 <= '9'))
           );
  } // myIsCharAlpha

// Stringvergleich: h muss mit Name als ganzes wort uebereinstimmen
BOOL mystrcmp (LPSTR h,LPSTR Name,int FAR *len)
  {
  for ( *len = 0 ; ; ) {
    if (*Name == '\0')   return (!myIsCharAlpha (*h));
    if (*h++ == *Name++) (*len) ++ ;
    else                 break ;
    }
  return FALSE ;
  }

BOOL kstrcmp (LPSTR h,LPSTR Name,int FAR *len,int tnum)
  {
  *len = 0;
  for ( LPSTR x = h ; (((*x) && (myIsCharAlpha (*x))) || (*x == '.')) ; x++) {
    if ((*x == '.') && (x > h)) {
      if ((x[-1] - '0') == tnum) {
        *len = x - h + 1;
        h = ++ x ;
        }
      break ;
      }
    }
  for ( ; ; ) {
    if (*Name == '\0')   return (!myIsCharAlpha (*h));
    if (*h++ == *Name++) (*len) ++ ;
    else                 break ;
    }
  return FALSE ;
  }

// Stringvergleich: h muss mit Name als uebereinstimmen (muss nicht ganzes wort sein)
BOOL mystrcmp1 (LPSTR h,LPSTR Name,int FAR *len)
  {
  for ( *len = 0 ; ; ) {
    if (*Name == '\0')   return TRUE ;
    if (*h++ == *Name++) (*len) ++ ;
    else                 break ;
    }
  return FALSE ;
  }

BOOL NextIsNullString (LPSTR h)
  {
  for (h++ ; ((*h == ' ') || (*h == '\t') || (*h == '\r') || (*h == '\n')) ; h++ ) ;
  return (strncmp(h, "NULL", 4) == 0);
  }

LPSTR PrevIsEqualSign (LPSTR h,LPSTR source)
  {
  for (h--; (h - source) >= 0; h--) {
    if ((*h == ' ') || (*h == '\t') || (*h == '\r') || (*h == '\n')) continue;
    if (*h == '=') return h;
    break;
    }
  return NULL;
  }

LPSTR PrevIsNotEqualSign (LPSTR h,LPSTR source)
  {
  for (h--; (h - source) >= 0; h--) {
    if ((*h == ' ') || (*h == '\t') || (*h == '\r') || (*h == '\n')) continue;
    if (*h == '>') {
      h--;
      if (*h == '<')
        return h;
      }
    break;
    }
  return NULL;
  }

BndList FAR *Top;
BndMem FAR *TopMem;
void PushToMemList (LPVOID data,int parNr,sb2 FAR *FAR *ind,ub2 FAR *FAR *alen)
  {
  BndMem FAR *node = (BndMem FAR *) GetGlobMem (sizeof (*node));
  node->Next = TopMem;
  node->data = data;
  node->parNr = parNr;
  if (ind != NULL)
    *ind = &node->ind;
  if (alen != NULL)
    *alen = &node->alen;
  TopMem = node;
  }
void FreeMemList ()
  {
  for ( ; (TopMem != NULL) ; ) {
    BndMem FAR *node = TopMem->Next ;
    FreeGlobMem (TopMem->data);
    FreeGlobMem (TopMem);
    TopMem = node ;
    }
  }
int AnzBindings = 1;
BndList FAR *PopFromBndList ()
  {
  if (Top != NULL) {
    BndList FAR *oldTop = Top ;
    Top = Top->Next ;
    AnzBindings -- ;
    return oldTop ;
    }
  else
    return NULL ;
  }

BndList FAR *GetLastBnd ()
  {
  if (Top != NULL) {
    for (BndList FAR *h = Top ; h->Next != NULL ; h = h->Next) ;
    return h ;
    }
  else
    return NULL ;
  }

BndList FAR *GetPrevBnd (BndList FAR *b)
  {
  if ((Top != NULL) && (b != Top)) {
    for (BndList FAR *h = Top ; ((h->Next != NULL) && (h->Next != b)) ; h = h->Next) ;
    return h ;
    }
  else
    return NULL ;
  }

char csPrefix (int Type)
  {
  switch (Type) {
    case CS_INT_TYPE :
      return 'I';
      break ;
    case CS_TEXT_TYPE :
      return 'S';
      break ;
    case CS_REAL_TYPE :
      return 'F';
      break ;
    case CS_IMAGE_TYPE :
      return 'M';
      break ;
    case CS_TEXT_TYPE_BIG :
      return 'T';
      break ;
    default :
      WIN_ASSERT (FALSE) ;
    }
  return '\0';
  }
int PushToBndList (int Type,LPVOID data,int Size,BOOL ownMem = FALSE,int parNr = -1,sb2 ind = 0,ub2 alen = 0)
  {
  BndList FAR *n = (BndList FAR *) GetGlobMem (sizeof(*n));
  n->Num = AnzBindings ;
  n->Type = Type ;
  n->parNr = parNr - 1;
  n->prefix = csPrefix (Type);
  if (ownMem) {
    n->data = GetGlobMem (Size + 1);
    lmemcpy (n->data,data,Size);
    if (parNr > 0) {
      PushToMemList (n->data,parNr,&n->indp,&n->alen);
      *n->indp = ind;
      *n->alen = alen;
      }
    else
      PushToMemList (n->data,parNr,NULL,NULL);
    }
  else
    n->data = data ;
  n->Next = Top ;
  n->Size = Size ;
  Top = n ;
  return AnzBindings++ ;
  }
void sybstmt::PushToDscList (int ParNum,LPDBREQUEST req)
  {
  BndList FAR *n = (BndList FAR *) GetGlobMem (sizeof(*n));
  n->Num = ParNum ;
  n->Next = NULL ;
  n->Type = req->ParamType [ParNum + 1];
  if (LastDsc) LastDsc->Next = n;
  LastDsc = n;
  if (TopDsc == NULL) TopDsc = n ;
  }

void sybstmt::ResetDscList ()
  {
  for ( ; TopDsc != NULL ; ) {
    BndList FAR *Next = TopDsc->Next;
    if (TopDsc->data) FreeGlobMem (TopDsc->data);
    FreeGlobMem (TopDsc);
    TopDsc = Next;
    }
  LastDsc = NULL;
  }


void FreeBndElem (BndList FAR *o)
  {
  FreeGlobMem (o);
  }
 
LPSTR GetFullFieldName (LPSTR h,LPSTR AliasName,int tnum,LPTABLEDEF ti,LPDBREQUEST req,BOOL useAlias,BOOL useKeyFields,BOOL FAR *translateNext)
  {
  *AliasName = '\0' ;
  if (IsCharAlpha(*h)) {
    // Es koennte sich um einen Feldnamen handeln
    if ((tnum > 0) && (ti->IsInternTable())) {
      LPPTABLE p = LPINTTABLE (ti->GetDLLDef())->GetTableByNum(tnum);
      for (int i = 0 ; i < int(p->AnzVars) ; i++) {
        LPVARDEF v = req->TableDef[tnum]->GetVarDef(p->VarID[i]);
        int len ;
        if (kstrcmp (h,v->GetName(),&len,tnum)) {
          LPSTR Name;
          if ((useKeyFields) && (v->Property & VPROP_CASEINSENSITIVE)) {
            Name = GetKeyFieldName (v->GetName());
            *translateNext = TRUE ;
            }
          else
            Name = GetAliasName (v->GetName());
          if (useAlias)
            sprintf (AliasName,"t%d.%s",tnum,Name);
          else
            sprintf (AliasName,"%s",Name);
          return h + len;
          }
        }
      for ( ; ((IsCharAlpha(*h)) || ((*h >= '0') && (*h <= '9'))) ; h++ ) ;
      return h ;
      }
    else {
      for (int i = 0 ; i < ti->GetAnzVars() ; i++) {
        ReqElem e;
        ti->GetReqElem (&e,i);

        LPVARDEF v;
        LPTABLEDEF td;
        if ((tnum >= 0) || (req == NULL)) {
          v = ti->GetVarDef(i);
          if (tnum < 0)
            e.TableNumber = -1;
          td = NULL;
          }
        else {
          td = req->TableDef[e.TableNumber];
          v = td->GetVarDef(e.VarID);
          }
        int len ;
        if (kstrcmp (h,v->GetName(),&len,e.TableNumber)) {
          LPSTR Name;
          if ((useKeyFields) && (v->Property & VPROP_CASEINSENSITIVE)) {
            Name = GetKeyFieldName (v->GetName());
            *translateNext = TRUE ;
            }
          else
            Name = GetAliasName (v->GetName());
          int tUse;
          if (tnum >= 0) tUse = tnum;
          else           tUse = e.TableNumber;
          if (useAlias)
            sprintf (AliasName,"t%d.%s",tUse,Name);
          else
            sprintf (AliasName,"%s",Name);
          return h + len;
          }
        }
      for ( ; ((IsCharAlpha(*h)) || ((*h >= '0') && (*h <= '9'))) ; h++ ) ;
      return h ;
      }
    }
  else
    return h + 1 ;
  }

BOOL NextIsSelect (LPSTR h)
  {
  int l;
  for ( ; ; h ++ ) {
    if ((*h != ' ') && (*h != '\r') && (*h != '\n') && (*h != '\t')) {
      return (mystrcmp (h,"SELECT",&l));
      }
    }
  return FALSE ;
  }

static LPSTR sqlmonth [] = {
  "JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OKT","NOV","DEC"
  };
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

int datSize (WORD mType)
  {
  if (mType == VAR_STR)
    return 255;
  else
    return sizeof(DWORD);
  }
int csType (WORD mType)
  {
  if (mType == VAR_STR)
    return CS_TEXT_TYPE;
  else
    return CS_SMALLINT_TYPE;
  }

LPSTR GetVarString (LPVOID data,int mType,BOOL FAR *doFree,int Size,BOOL doStatic,int parNr)
  {
  static char *null = "NULL" ;
  static char resstr[128];
  if (parNr > 0) {
    // Es muss auf jeden fall Speicher angefordert werden,
    // die Daten muessen (wenn data != NULL) umkopiert werden, 
    // alen und indp richtig setzt werden
    int nSize = datSize (mType);
    LPVOID nData = GetGlobMem (nSize);
    ub2 alen;
    sb2 ind;
    if (data != NULL) {
      switch (mType) {
        case VAR_DATE :
          {
          sprintf(LPSTR (nData), "%02.2d%02.2d%04.4d000000",
                        (int) (((packdate FAR *) data)->day),
                        (int) (((packdate FAR *) data)->month),
                        (int) (((packdate FAR *) data)->year)
                        );
          alen = nSize;
          ind = 0;
          }
          break ;
        default :
          int rSize;
          if (Size > 0) {
            rSize = min (GetBlockSize (data),min (nSize,Size));
            }
          else
            rSize = min (GetBlockSize (data),nSize);
          lmemcpy (nData,data,rSize);
          alen = nSize;
          ind = 0;
          break ;
        }
      }
    else {
      alen = 0;
      ind = OCI_IND_NULL;
      }
    char pattern[4];
    wsprintf (pattern,":%c%%d",csPrefix(csType(mType)));
    sprintf (resstr,pattern,PushToBndList (csType (mType),nData,nSize,TRUE,parNr,ind,alen));
    return resstr;
    }
  else {
    if (data == NULL) {
      *doFree = FALSE ;
      return null ;
      }
    if (IsFixed (mType)) {
      switch (mType) {
        case VAR_STRARR :
        case VAR_FLAG :
          if (doStatic) sprintf (resstr,"%d",*(short FAR *) data) ;
          else          sprintf (resstr,":I%d",PushToBndList (CS_SMALLINT_TYPE,data,sizeof(short)));
          break ;
        case VAR_DEC :
          if (doStatic) sprintf (resstr,"%f",*(float FAR *) data) ;
          else          sprintf (resstr,":F%d",PushToBndList (CS_REAL_TYPE,data,sizeof(float)));
          break ;
        case VAR_LONG :
        case VAR_DWORD :
          if (doStatic) sprintf (resstr,"%ld",* (LONG FAR *) data) ;
          else          sprintf (resstr,":I%d",PushToBndList (CS_INT_TYPE,data,sizeof(LONG)));
          break ;
        case VAR_DATE :
          if (doStatic)
            sprintf(resstr, "'%02.2d%02.2d%04.4d000000'",
                          (int) (((packdate FAR *) data)->day),
                          (int) (((packdate FAR *) data)->month),
                          (int) (((packdate FAR *) data)->year)
                          );
          else {
            char odate[64];
            sprintf(odate, "%02.2d%02.2d%04.4d000000",
                          (int) (((packdate FAR *) data)->day),
                          (int) (((packdate FAR *) data)->month),
                          (int) (((packdate FAR *) data)->year)
                          );
            wsprintf (resstr,":S%d",PushToBndList (CS_TEXT_TYPE,odate,lstrlen(odate) + 1,TRUE));
            }
          break ;
        case VAR_TIME :
          if (doStatic)
            sprintf(resstr, "'01010001%02.2d%02.2d%02.2d'",
                            (int) (((packtime FAR *) data)->hour),
                            (int) (((packtime FAR *) data)->minute),
                            (int) (((packtime FAR *) data)->second));
          else {
            char odate[64];
            sprintf(odate,"01010001%02.2d%02.2d%02.2d",
                          (int) (((packtime FAR *) data)->hour),
                          (int) (((packtime FAR *) data)->minute),
                          (int) (((packtime FAR *) data)->second));
            wsprintf (resstr,":S%d",PushToBndList (CS_TEXT_TYPE,odate,lstrlen(odate) + 1,TRUE));
            }
          break ;
        case VAR_DATETIME :
          if (doStatic)
            sprintf(resstr, "'%02.2d%02.2d%04.4d%02.2d%02.2d%02.2d'",
                            (int) (((packdatetime FAR *) data)->pd.day),
                            (int) (((packdatetime FAR *) data)->pd.month),
                            (int) (((packdatetime FAR *) data)->pd.year),
                            (int) (((packdatetime FAR *) data)->pt.hour),
                            (int) (((packdatetime FAR *) data)->pt.minute),
                            (int) (((packdatetime FAR *) data)->pt.second));
          else {
            char odate[64];
            sprintf(odate,"%02.2d%02.2d%04.4d%02.2d%02.2d%02.2d",
                            (int) (((packdatetime FAR *) data)->pd.day),
                            (int) (((packdatetime FAR *) data)->pd.month),
                            (int) (((packdatetime FAR *) data)->pd.year),
                            (int) (((packdatetime FAR *) data)->pt.hour),
                            (int) (((packdatetime FAR *) data)->pt.minute),
                            (int) (((packdatetime FAR *) data)->pt.second));
            wsprintf (resstr,":S%d",PushToBndList (CS_TEXT_TYPE,odate,lstrlen(odate) + 1,TRUE));
            }
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
          else {
            int mSize ;
            if (Size > 0)
              mSize = min(Size,int(GetBlockSize(data)));
            else
              mSize = GetBlockSize(data);
            wsprintf (resstr,":M%d",PushToBndList (CS_IMAGE_TYPE,data,mSize));
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
        else {
          *doFree = FALSE ;
          int mSize ;
          if (Size > 0)
            mSize = min(Size,int (GetBlockSize(data) - 1));
          else
            mSize = GetBlockSize(data) - 1;
          wsprintf (resstr,":T%d",PushToBndList (CS_TEXT_TYPE_BIG,data,mSize));
          return resstr;
          }
        }
      else {
        *doFree = FALSE ;
        return null ;
        }
      }
    else {
      // Binary - Datatype
      *doFree = FALSE ;
      wsprintf (resstr,":M%d",PushToBndList (CS_IMAGE_TYPE,data,GetBlockSize(data)));
      return resstr ;
      }
    }
  return NULL ;
  }
LPSTR GetParamString (LPDBREQUEST req,int parNr,BOOL FAR *doFree,BOOL useOld,sybstmt FAR *s,int memNr)
  {
  if (useOld)
    return GetVarString (s->oldParam[parNr-2],s->oldParamType[parNr-2],doFree,-1,FALSE,memNr);
  else
    return GetVarString (req->Param[parNr],req->ParamType[parNr],doFree,-1,FALSE,memNr);
  }

#define STATE_NORMAL        0
#define STATE_INSERTFOUND   1
#define STATE_TABLEFOUND    2

class TableStack {
 public :
  int sstackptr ;
  LPTABLEDEF sstacktt[10];
  BOOL sstackw[10];
  TableStack ()
    {
    sstackptr = 0 ;
    }
  void Push (LPTABLEDEF t,BOOL w)
    {
    sstacktt[sstackptr] = t ;
    sstackw[sstackptr++] = w ;
    }

  void Pop (LPTABLEDEF FAR &t,BOOL FAR &w)
    {
    t = sstacktt[--sstackptr] ;
    w = sstackw[sstackptr] ;
    }
  };

inline BOOL IsSpace (char ch)
  {
  return ((ch == ' ') || (ch == '\r') || (ch == '\t') || (ch == '\n'));
  }

LPSTR LongString::SkipSpace (LPSTR h,LPSTR FAR &lastStart)
  {
  if (IsSpace (*h)) {
    *this = *this + PartString (lastStart,h-lastStart);
    *this = *this + " " ;
    for ( ; IsSpace (*h) ; h ++ ) ;
    lastStart = h ;
    }
  return h ;
  }

LPSTR IsConst (LPSTR h,LPSTR BndRes)
  {
  if ((*h >= '0') && (*h <= '9')) {
    // Es handelt sich um eine zahl
    for ( LONG res = 0L ; ((*h >= '0') && (*h <= '9')) ; h++ ) {
      res = res * 10L + *h - '0' ;
      }
    wsprintf (BndRes,":I%d",PushToBndList (CS_INT_TYPE,&res,sizeof(res),TRUE));
    return h ;
    }
  else if (*h == '\'') {
    LPSTR start = ++ h ;
    for ( ; *h != '\'' ; h ++ ) ;
    *h = '\0' ;
    wsprintf (BndRes,":S%d",PushToBndList (CS_TEXT_TYPE,start,h - start + 1,TRUE));
    *h = '\'' ;
    h ++ ;
    return h ;
    }
  return NULL ;
  }

BOOL NextIsParam (LPSTR h)
  {
  for (h++ ; ((*h == ' ') || (*h == '\t') || (*h == '\r') || (*h == '\n')) ; h++ ) ;
  return (*h == '%') ;
  }

BOOL NextIsNumber (LPSTR h)
  {
  for (h++ ; ((*h == ' ') || (*h == '\t') || (*h == '\r') || (*h == '\n')) ; h++ ) ;
  return (*h >= '0') && (*h <= '9') ;
  }

LPSTR LongString::AnalyseSeq (sybstmt FAR *stmt,LPSTR source,BOOL translateNull,LPTABLEDEF ti,LPDBREQUEST req,BOOL useAlias,BOOL useOld,sybstmt FAR *s,BOOL whereFound,int AnzJoinSegs,LPSTR JoinName[],int tnum,BOOL UseOuter)
  {
  TableStack stk ;
  if (source == NULL) return NULL;
  if (*source == '+') source = source ++ ;    // Hinweis fuer einen Hint
  BOOL instring = FALSE ;
  BOOL InSubSelect = FALSE ;
  LPSTR lastStart = source ;
  int level ;
  int State = STATE_NORMAL ;
  WORD TableID,VarIDToCheck,Version ;
  BOOL TableFound = FALSE ;
  BOOL doInsertAutoinc = FALSE ;
  BOOL translateNext = FALSE ;
  LPTABLEDEF td = NULL ;
  LPTABLEDEF ttest = NULL ;
  BOOL NextIsTable = FALSE ;
  BOOL BindConst = FALSE ;
  BOOL doNormalCheck ;
  int len ;
  int AnzTablesFound;

  if (*source) {
    for (LPSTR h = source ; *h ; ) {
      if (instring) {
        switch (*h) {
          case '\'' :
            instring = FALSE ;
            char bndstring [32];
            *h = '\0' ;
            wsprintf (bndstring,":S%d",PushToBndList (CS_TEXT_TYPE,lastStart,h - lastStart + 1,TRUE));
            *h = '\'' ;
            h ++ ;
            *this = *this + bndstring ;
            lastStart = h ;
            if (translateNext) {
              *this = *this + ")" ;
              translateNext = FALSE ;
              }
            break ;
          default :
            h++ ;
          }
        }
      else {
        h = SkipSpace (h,lastStart);
        switch (State) {
          case STATE_NORMAL :
            switch (*h) {
              case '\0' :
                break ;
              case '\'' :
                if (translateNext) {
                  *this = *this + PartString (lastStart,h-lastStart) + "CLTRANS(";
                  }
                else {
                  *this = *this + PartString (lastStart,h-lastStart) ;
                  }
                h ++ ;
                lastStart = h ;
                instring = TRUE ;
                break ;
              case '%' :
              case '&' :
                {
                BOOL getOutParam;
                int memNr;
                if (*h == '&') getOutParam = TRUE;
                else           getOutParam = FALSE;
                LPSTR beg = h ;
                int parNr;
                h = GetParNr (h+1,&parNr);
                if ((AnzJoinSegs == 0) || (parNr >= (AnzJoinSegs + 2))) {
                  parNr -= AnzJoinSegs;
                  WIN_ASSERT (req != NULL);
                  BOOL doFree;
                  if (getOutParam) memNr = parNr;
                  else             memNr = -1;
                  LPSTR param = GetParamString (req,parNr,&doFree,useOld,s,memNr) ;
                  if ((strncmp(param, "NULL", 4) == 0) && (translateNull)) {
                    // auch hier muss aus "= NULL" "IS NULL" gemacht werden
                    LPSTR SignPos = PrevIsEqualSign(beg,source);
                    if (SignPos != NULL) {
                      *this = *this + PartString (lastStart,SignPos-lastStart) + " IS NULL ";
                      }
                    else {
                      SignPos = PrevIsNotEqualSign(beg,source);
                      if (SignPos != NULL) {
                        *this = *this + PartString (lastStart,SignPos-lastStart) + " IS NOT NULL ";
                        }
                      else {
                        *this = *this + PartString (lastStart,beg-lastStart) + param;
                        }
                      }
                    }
                  else {
                    *this = *this + PartString (lastStart,beg-lastStart) ;
                    if (translateNext) *this = *this + "CLTRANS (" + param + ")" ;
                    else               *this = *this + param ;
                    translateNext = FALSE ;
                    }
                  if (doFree)
                    FreeGlobMem (param);
                  }
                else {
                  *this = *this + PartString (lastStart,beg-lastStart) ;
                  *this = *this + JoinName[parNr-2] ;
                  }
                lastStart = h ;
                }
                break;
              case '$' :
                {
                LPSTR beg = h ;
                int parNr;
                h = GetParNr (h+1,&parNr);
                *this = *this + PartString (lastStart,beg-lastStart) ;
                if (stmt != NULL)
                  stmt->PushToDscList (parNr - 1,req); // Achtung: GetParNr zaehlt eins dazu
                lastStart = h ;
                }
                break ;
              case '=' :
                if (UseOuter && (NextIsParam (h) || NextIsNumber (h)) && (!InSubSelect)) {
                  // = wird durch (+)= ersetzt
                  *this = *this + PartString (lastStart,h-lastStart);
                  lastStart = h = h + 1 ;
                  *this = *this + "(+)=";
                  }
                if ((NextIsNullString (h)) && (translateNull)) {
                  *this = *this + PartString (lastStart,h-lastStart);
                  *this = *this + " IS ";
                  lastStart = h = h + 1;
                  }
                else {
                  h++;
                  }
                break ;
              case '<' :
                if ((h[1] == '>') && NextIsNullString (h + 1) && (translateNull)) {
                  *this = *this + PartString (lastStart,h-lastStart);
                  *this = *this + " IS NOT ";
                  lastStart = h = h + 2;
                  }
                else {
                  h++;
                  }
                break ;
              case '(' :
                h++ ;
                if (doInsertAutoinc)
                  level ++ ;
                else {
                  if (InSubSelect) level ++ ;
                  else if (NextIsSelect (h)) {
                    level = 1 ;
                    InSubSelect = TRUE ;
                    BindConst = FALSE ;
                    }
                  if (InSubSelect) {
                    stk.Push (ttest,whereFound);
                    ttest = NULL ;
                    whereFound = FALSE ;
                    }
                  }
                break ;
              case ')' :
                if (InSubSelect) {
                  if (ttest != NULL)
                    GetTableAdmin()->FreeTable (ttest->GetTableID(),ttest->GetVersion());
                  stk.Pop (ttest,whereFound);
                  }
                // Eventuell koennen hier negative Werte entstehen.
                // Bei InSubSelect wird sowieso auf 1 initialisiert und bei einem
                // INSERT kommen wir (hoffentlich) hier nicht vorbei ohne doInsertAutoinc.
                // Daher sollte das kein Problem sein.
                level -- ; 
                if ((doInsertAutoinc) && (level == 0)) {
                  *this = *this + PartString (lastStart,h-lastStart);
                  *this = *this + "," + GetSequenceName (td) + ".NEXTVAL" ;
                  lastStart = h ;
                  }
                h++ ;
                if (level == 0) InSubSelect = FALSE ;
                BindConst = FALSE ;
                break ;
              default :
                BOOL ttestfound = FALSE;
                doNormalCheck = FALSE ;
                if (NextIsTable) {
                  if (myIsCharAlpha(*h)) {
                    char TableName[65];
                    LPSTR x = TableName ;
                    LPSTR hStart = h ;
                    for ( int i = 0 ; myIsCharAlpha1 (*h,h[1]) ; i++ ) {
                      if (i < sizeof(TableName) - 1)
                        *x++ = *h++ ;
                      else
                        h ++ ;
                      }
                    *x++ = '\0' ;
                    WORD tTableID,tVersion;
                    tTableID = GetTableAdmin()->GetTableID (NULL,TableName,&ttestfound,&tVersion);
                    if (ttestfound) {
                      ttest = GetTableAdmin()->GetTableDef (tTableID,tVersion);
                      *this = *this + PartString (lastStart,hStart-lastStart);
                      *this = *this + ORAGetTableName (ttest,TRUE); // ttest->GetName();
                      lastStart = h ;
                      AnzTablesFound = AnzTablesFound + 1;
                      }
                    else if ((lstrcmp (TableName,"SET") == 0) || (lstrcmp (TableName,"WHERE") == 0) || (lstrcmp (TableName,"SELECT") == 0)) {
                      h = hStart ;
                      NextIsTable = FALSE ;
                      }
                    else h = hStart ;
                    }
                  // else
                  //  h ++ ;
                  }
                if (ttestfound)
                  break;
                if (mystrcmp (h,"IN",&len)) {
                  BindConst = TRUE;
                  h += len ;
                  NextIsTable = FALSE;
                  }
                else if (BindConst) {
                  char BndString[32];
                  LPSTR nh = IsConst (h,BndString);
                  if (nh != NULL) {
                    *this = *this + PartString (lastStart,h-lastStart);
                    lastStart = h = nh ;
                    *this = *this + BndString;
                    }
                  else
                    doNormalCheck = TRUE ;
                  }
                else
                  doNormalCheck = TRUE ;
                if (doNormalCheck) {
                  if ((ti != NULL) && (req != NULL) && (!InSubSelect)) {
                    char AliasName [256];
                    LPSTR behindField = GetFullFieldName(h,AliasName,tnum,ti,req,useAlias,whereFound,&translateNext);
                    if (*AliasName) {
                      *this = *this + PartString (lastStart,h-lastStart);
                      lastStart = h = behindField ;
                      *this = *this + AliasName;
                      }
                    else
                      h = behindField ;
                    }
                  else if ((ttest != NULL) && (whereFound)) {
                    char AliasName [256];
                    LPSTR behindField = GetFullFieldName (h,AliasName,(AnzTablesFound == 1) ? 0 : -1,ttest,NULL,((useAlias) && (!InSubSelect)),TRUE,&translateNext);
                    if (*AliasName) {
                      *this = *this + PartString (lastStart,h-lastStart);
                      lastStart = h = behindField ;
                      *this = *this + AliasName;
                      }
                    else
                      h = behindField ;
                    }
                  else if (mystrcmp (h,"WHERE",&len)) {
                    h += len ;
                    whereFound = TRUE ;
                    translateNull = TRUE ;
                    NextIsTable = FALSE;
                    }
                  else if (mystrcmp (h,"INSERT",&len)) {
                    h += len ;
                    State = STATE_INSERTFOUND ;
                    }
                  else if ((mystrcmp (h,"UPDATE",&len)) ||
                          (mystrcmp (h,"FROM",&len))) {
                    NextIsTable = TRUE ;
                    AnzTablesFound = 0;
                    h += len ;
                    }
                  else if (mystrcmp (h,"SELECT",&len)) {
                    NextIsTable = FALSE ;
                    h += len ;
                    }
                  else if (mystrcmp (h,"SET",&len)) {
                    NextIsTable = FALSE ;
                    h += len ;
                    }
                  else {
                    if (myIsCharAlpha(*h))
                      for ( h ++ ; myIsCharAlpha(*h) ; h ++ ) ;
                    else if (*h)
                      h++ ;
                    }
                  }
                break ;
              }
            break ;
          case STATE_INSERTFOUND :
            if (myIsCharAlpha(*h)) {
              char TableName[65];
              LPSTR x = TableName ;
              LPSTR hStart = h ;
              for ( ; myIsCharAlpha1 (*h,h[1]) ; ) {
                *x++ = *h++ ;
                }
              *x++ = '\0' ;
              TableID = GetTableAdmin()->GetTableID (NULL,TableName,&TableFound,&Version);
              if (TableFound) {
                td = GetTableAdmin()->GetTableDef (TableID,Version);
                *this = *this + PartString (lastStart,hStart-lastStart);
                *this = *this + ORAGetTableName (td,TRUE) ;
                lastStart = h ;
                LPCLKEYDEF k0 = td->GetKeyDef(0);
                if (k0->Attribute & CLKD_AUTOINC) {
                  VarIDToCheck = k0->VarID;
                  State = STATE_TABLEFOUND ;
                  }
                else
                  State = STATE_NORMAL ;
                }
              }
            else
              h ++ ;
            break ;   // STATE_INSERTFOUND ;
          case STATE_TABLEFOUND :
            switch (*h) {
              case '\'' :
                if (translateNext) {
                  *this = *this + PartString (lastStart,h-lastStart) + "CLTRANS(";
                  }
                else {
                  *this = *this + PartString (lastStart,h-lastStart) ;
                  }
                h ++ ;
                lastStart = h ;
                instring = TRUE ;
                break ;
              case ')' :
                *this = *this + PartString (lastStart,h-lastStart);
                *this = *this + "," + td->GetVarDef (VarIDToCheck)->GetName() ;
                lastStart = h ;
                h ++ ;
                level = 0 ;
                State = STATE_NORMAL ;
                doInsertAutoinc = TRUE ;
                break ;
              default :
                // Untersuchen, ob die Variable dem Autoinc - Feld entspricht
                if (myIsCharAlpha(*h)) {
                  if (mystrcmp (h,td->GetVarDef (VarIDToCheck)->GetName(),&len)) {
                    State = STATE_NORMAL ;    // Autoinc feld schon gesetzt
                    h += len ;
                    }
                  else {
                    for ( ; myIsCharAlpha (*h) ; h ++ ) ;
                    }
                  }
                else
                  h ++ ;
                break ;
              }
 
            break ;
          }
        }
      }
    if (lastStart != h)
       *this = *this + PartString (lastStart,h-lastStart);
    }
  else
    *this = *this + "" ;
  if (TableFound)
    GetTableAdmin()->FreeTable (TableID,Version);
  if (ttest != NULL)
    GetTableAdmin()->FreeTable (ttest->GetTableID(),ttest->GetVersion());
  return LPSTR (Ptr());
  }

LPSTR LongString::InsertDescending (LPSTR source)
  {
  LPSTR last = source ;
  for (LPSTR h = source ; ; h ++) {
    if ((*h == ',') || (*h == '\0')) {
      *this = *this + PartString (last,h - last) + " DESC" ;
      last = h ;
      if (*h == '\0') break ;
      }
    }
  return LPSTR (Ptr());
  }

WORD MyGetVarInd (LPTABLEDEF td,LPSTR pName)
  {
  for (int i = 0 ; i < td->GetAnzVars () ; i++) {
    if (lstrcmp (pName,td->GetVarDef(i)->GetName()) == 0) return i ;
    }
  return 0xFFFF ;
  }

BOOL NoMoreParams (LPSTR FAR *param,int SegNum,int AnzSegs)
  {
  if (SegNum == AnzSegs - 1) return TRUE ;
  else {
    for (int i = SegNum + 1; i < AnzSegs ; i++) {
      if (lstrcmp (param[i],"NULL") != 0) return FALSE ;
      }
    }
  return TRUE ;
  }

void GetSegCond (LongString FAR *buffer,int AnzSegs,int SegNum,LPSTR FAR *SegName,LPSTR FAR *param,LPSTR c,LPSTR ce)
  {
  if (lstrcmp (param[SegNum],"NULL") == 0)
    return ;
#ifdef UEBERLEGT
  if (SegNum == AnzSegs - 1) {
    *buffer = *buffer + "(" + SegName[SegNum] + " " + ce + " " + param[SegNum] + ")" ;
    }
  else {
    *buffer = *buffer + "((" + SegName[SegNum] + " " + c + " " + param[SegNum] + ") OR "
                        "((" + SegName[SegNum] + " = " + param[SegNum] + ") AND " ;
    GetSegCond (buffer,AnzSegs,SegNum + 1,SegName,param,c,ce);
    *buffer = *buffer + "))" ;
    }
#else
  if (NoMoreParams (param,SegNum,AnzSegs)) {
    *buffer = *buffer + "(" + SegName[SegNum] + " " + ce + " " + param[SegNum] + ")" ;
    }
  else {
    *buffer = *buffer + "((" + SegName[SegNum] + " " + ce + " " + param[SegNum] + ") AND "
                        "((" + SegName[SegNum] + c + param[SegNum] + ") OR " ;
    GetSegCond (buffer,AnzSegs,SegNum + 1,SegName,param,c,ce);
    *buffer = *buffer + "))" ;
    }
#endif
  }
LPSTR LongString::InsertSyncCond (LPSTR sync,LPDBREQUEST req,LPSTR c,LPSTR ce,BOOL FAR &doAnd)
  {
  LPSTR last = sync ;
  int pn = 0 ;
  LPSTR param[10];
  LPSTR SegName[10];

  // Segmentnamen und Paramenter ermitteln
  for (LPSTR h = sync ; ; h ++) {
    if ((*h == ',') || (*h == '\0')) {
      SegName[pn] = LPSTR(GetGlobMem(h - last + 1)) ;
      lmemcpy(SegName[pn],last, h - last);
      // Untersuchen, ob der Schluesselname verwendet worden ist
      //--------------------------------------------------------
      BOOL doTranslate = FALSE ;
      int len;
      if (mystrcmp1 (SegName[pn],"KF_",&len)) doTranslate = TRUE ;
      else {
        for (LPSTR h = SegName[pn]; *h ; h++) {
          if (mystrcmp1 (h,".KF_",&len)) doTranslate = TRUE ;
          }
        }
      BOOL doFree ;
      LPSTR res = GetVarString (req->SortParam[pn],req->SortParamType[pn],&doFree,-1,FALSE,0);
      int size = lstrlen(res) + 1;
      if (doTranslate)
        size += 9 ;
      param[pn] = LPSTR(GetGlobMem (size)) ;
      if (doTranslate)
        lstrcpy (param[pn],"CLTRANS(") ;
      lstrcat (param[pn],res);
      if (doFree)
        FreeGlobMem (res);
      if (doTranslate)
        lstrcat (param[pn],")") ;
      pn ++ ;
      if (*h == '\0') break ;
      h ++ ;
      last = h ;
      }
    }

  // Zusammenbasteln der Strings
  if (doAnd)
    *this = *this + " AND " ;
  GetSegCond (this,pn,0,SegName,param,c,ce);
  if (pn > 1)
    doAnd = TRUE ;


  // Daten wieder freigeben
  for (int i = 0 ; i < pn ; i++) {
    FreeGlobMem (SegName[i]) ;
    FreeGlobMem (param[i]) ;
    }

  return LPSTR (Ptr());
  }

BOOL IsNullAllowed (LPDBREQUEST req,LPTABLEDEF ti,LPCLRIDEF r)
  {
  WIN_ASSERT ((r->Type == CLJR_RISTANDARD) || (r->Type == CLJR_NEW));
  for (int i = 0 ; i < int(r->AnzSegs) ; i++) {
    ReqElem e;
    JoinDef FAR *jd = r->GetJDef();
    ti->GetReqElem (&e,jd->VarID[i]);
    if ((req->TableDef[e.TableNumber]->GetVarDef(e.VarID)->Property & VPROP_NOTNULL) == 0) return TRUE ;
    }
  return FALSE ;
  }

LPSTR LongString::AnalyseJoin (LPDBREQUEST req,LPTABLEDEF ti,int tnum,LPCLRIDEF r,LPSTR FAR *JoinSel,BOOL FAR *UseOuter,BOOL useOld,sybstmt FAR *s,BOOL translateNull)
  {
  LPSTR JoinName[32];
  // Ermitteln der Namen der Felder, die in den Join eingehen
  WIN_ASSERT ((r->Type == CLJR_RISTANDARD) || (r->Type == CLJR_NEW));
  for (int i = 0 ; i < int(r->AnzSegs) ; i++) {
    ReqElem e;
    JoinDef FAR *jd = r->GetJDef();
    ti->GetReqElem (&e,jd->VarID[i]);
    if (UseOuter[e.TableNumber])
      UseOuter[tnum] = TRUE ;
    char JN[66];
    sprintf (JN,"t%d.%s",e.TableNumber,
          req->TableDef[e.TableNumber]->GetVarDef(e.VarID)->GetName());
    JoinName[i] = LPSTR(GetGlobMem (lstrlen(JN)+1));
    lstrcpy (JoinName[i],JN);
    }

//  *this = *this + AnalyseSeq(r->name,translateNull,req->TableDef[tnum],req,TRUE,useOld,s,TRUE,r->AnzSegs,JoinName,tnum,UseOuter[tnum]);
  AnalyseSeq(NULL,r->name,translateNull,req->TableDef[tnum],req,TRUE,useOld,s,TRUE,r->AnzSegs,JoinName,tnum,UseOuter[tnum]);

  // Loeschen der Feldname
  for (i = 0 ; i < int(r->AnzSegs) ; i++)
    FreeGlobMem (JoinName[i]);
  return LPSTR(Ptr());
  }

struct MBlockHeader {
  WORD AnzVars;
  WORD BlockSize;
  };
struct MBlockVarHeader {
  WORD VarID;
  WORD VarSize;
  };

/*------------------------------------------------------*/
/* Vorbereiten eines Kommandos und dieses an            */
/* den Server senden                                    */
/*------------------------------------------------------*/
LPVOID sybstmt::GetSybDataType (CS_DATAFMT FAR *fmt,WORD mType,int maxSize,int nRows)
  {
  fmt->count = nRows ;
  switch (mType) {
    case VAR_LONG   :
    case VAR_DWORD  :
      fmt->datatype = CS_INT_TYPE ;
      fmt->maxlength = maxSize ;
      break ;
    case VAR_STRARR :
    case VAR_FLAG   :
      fmt->datatype = CS_SMALLINT_TYPE ;
      fmt->maxlength = maxSize ;
      break ;
    case VAR_DEC    :
      fmt->datatype = CS_REAL_TYPE ;
      fmt->maxlength = maxSize ;
      break ;
    case VAR_STR    :
      if (maxSize > 2000)
        fmt->datatype = CS_TEXT_TYPE_BIG;
      else if (maxSize > 254)
        fmt->datatype = CS_TEXT_TYPE ;
      else
        fmt->datatype = CS_CHAR_TYPE ;
      fmt->maxlength = maxSize ;
      fmt->format = CS_FMT_NULLTERM ;
      fmt->maxlength += 1;      // zero termination need additional space
      break ;
    case VAR_POINT  :
    case VAR_CONT   :
    case VAR_SCALE  :
    case VAR_OBJ    :
      if (maxSize > 254)
        fmt->datatype = CS_BINARY_TYPE ;
      else
        fmt->datatype = CS_IMAGE_TYPE ;
      fmt->maxlength = maxSize ;
      fmt->format = CS_FMT_UNUSED ;
      break ;
    case VAR_DATE   :
    case VAR_TIME   :
    case VAR_DATETIME   :
      fmt->datatype = CS_DATETIME_TYPE ;
      fmt->maxlength = sizeof(OCI_DATETIME) ;
      fmt->format = CS_FMT_UNUSED ;
      break ;
    case VAR_BLOB   :
      fmt->datatype = CS_IMAGE_TYPE ;
      fmt->format = CS_FMT_UNUSED ;
      fmt->maxlength = sizeof(DWORD);
      break ;
    }
  return GetGlobMem (int (fmt->maxlength) * nRows);
  }

LPVOID sybstmt::GetSybDataType_f (ub2 *ml,ub2 *dt,WORD mType,int maxSize)
  {
  switch (mType) {
    case VAR_LONG   :
    case VAR_DWORD  :
      *dt = CS_INT_TYPE ;
      *ml = sizeof(DWORD) ;
      break ;
    case VAR_STRARR :
    case VAR_FLAG   :
      *dt = CS_SMALLINT_TYPE ;
      *ml = sizeof(DBINT) ;
      break ;
    case VAR_DEC    :
      *dt = CS_REAL_TYPE ;
      *ml = sizeof(float) ;
      break ;
    case VAR_STR    :
      if (maxSize > 2000)
        *dt = CS_TEXT_TYPE_BIG;
      else if (maxSize > 254)
        *dt = CS_TEXT_TYPE ;
      else
        *dt = CS_CHAR_TYPE ;
      *ml = maxSize + 1;
      break ;
    case VAR_POINT  :
    case VAR_CONT   :
    case VAR_SCALE  :
    case VAR_OBJ    :
      if (maxSize > 254)
        *dt = CS_BINARY_TYPE ;
      else
        *dt = CS_IMAGE_TYPE ;
      *ml = maxSize ;
      break ;
    case VAR_DATE   :
    case VAR_TIME   :
    case VAR_DATETIME   :
      *dt = CS_DATETIME_TYPE ;
      *ml = sizeof(OCI_DATETIME) ;
      break ;
    case VAR_BLOB   :
      WIN_ASSERT(FALSE);
      break ;
    }
  return GetGlobMem (int (*ml));
  }

int sybstmt::nRows (LPTABLEDEF ti,BOOL ignoreBlob)
  {
  if ((blobCol >= 0) && (!ignoreBlob)) return 1 ;    // Damit oflng weiter gemacht werden kann
  if (dbMaxRows == 0) {
    if (RecsToGet > 0)
      dbMaxRows = RecsToGet ;
    else
      dbMaxRows = MAXROWSBUFFERED ;
    // Ausrechnen, wieviel Zeilen maximal platz haetten
    /////////////////////////////////////////////////////
    if (ti != NULL) {
      if (req->AnzElems > 0) {
        for (int i = 0 ; i < int (req->AnzElems) ; i++) {
          LPVARDEF v = req->TableDef[req->elem[i].TableNumber]->GetVarDef(req->elem[i].VarID);
#ifdef ALTE_VERSION
          int nMax = int (long (0x7FFF) / long(v->VarSize)) ;
          if (nMax < dbMaxRows) dbMaxRows = nMax ;
#else
          if (v->VarSize != 0xFFFF) {
            int nMax = int (long (0x7FFF) / long(v->VarSize)) ;
            if (nMax < dbMaxRows) dbMaxRows = nMax ;
            }
          else
            dbMaxRows = 1 ;
#endif
          }
        }
      else {
        for (int i = 0 ; (i < ti->GetAnzVars()) ; i++) {
          LPVARDEF v = ti->GetVarDef(i);
          if (v->VarSize != 0xFFFF) {
            int nMax = int (long (0x7FFF) / long(v->VarSize)) ;
            if (nMax < dbMaxRows) dbMaxRows = nMax ;
            }
          else
            dbMaxRows = 1 ;
          }
        }
      }
    else
      dbMaxRows = 1;
    }
  return dbMaxRows ;
  }

int sybstmt::nCols (LPTABLEDEF ti)
  {
  if (dbCols < 0) {
    if (ti != NULL) {
      if (req->AnzElems > 0)
        dbCols = int(req->AnzElems) ;   // Views duerfen keine blocked elemente besitzen
      else {
        BOOL blocked_Done = FALSE ;
        dbCols = 0 ;
        for (int i = 0 ; (i < ti->GetAnzVars()) ; i++) {
          LPVARDEF v = ti->GetVarDef(i);
          if (v->VarSize != 0xFFFF)
            dbCols ++ ;
          else {
            if (!blocked_Done)
              dbCols ++ ;
            blocked_Done = TRUE ;
            }
          }
        }
      }
    else
      dbCols = 0;
    }
  return dbCols ;
  }

void sybstmt::GetColInfo(LPTABLEDEF ti)
  {
  if (ColInfo == NULL) {
    blobCol = -1 ;
    LPVARDEF v;
    ColInfo = (_COLINFO FAR *) GetGlobMem (sizeof(*ColInfo) * nCols(ti));
    BOOL BlockedDone = FALSE ;
    // Ermitteln der Spalte, in der ein blob steht
    for (int i = 0 ; i < nCols(ti) ; i++) {
      if (req->AnzElems > 0)
        v = req->TableDef[req->elem[i].TableNumber]->GetVarDef(req->elem[i].VarID);
      else
        v = ti->GetVarDef(i);
      if (v->mType == VAR_BLOB) {
        blobCol = i ;
        }
      }
    for (i = 0 ; i < nCols(ti) ; i++) {
      if (req->AnzElems > 0)
        v = req->TableDef[req->elem[i].TableNumber]->GetVarDef(req->elem[i].VarID);
      else
        v = ti->GetVarDef(i);
      ColInfo[i].VarLen     = (VARLEN_TYPE FAR *) GetGlobMem (sizeof(*ColInfo[i].VarLen) * nRows(ti)) ;
      ColInfo[i].VarRetCode = (VARRETCODE_TYPE FAR *) GetGlobMem (sizeof(*ColInfo[i].VarRetCode) * nRows(ti)) ;
      ColInfo[i].VarInd     = (VARIND_TYPE FAR *) GetGlobMem (sizeof(*ColInfo[i].VarInd) * nRows(ti)) ;
      if (v->VarSize != 0xFFFF) {
        WIN_ASSERT (!BlockedDone);    // Der geblockte Teil muss hinten stehen
        ColInfo[i].VarData   = GetSybDataType (&ColInfo[i].VarFormat,v->mType,v->VarSize,nRows(ti));
        }
      else {
        ColInfo[i].VarData   = GetSybDataType (&ColInfo[i].VarFormat,VAR_OBJ,MAXBLOCKEDSIZE,nRows(ti));
        }
      }
    }
  }

BOOL sybstmt::BindColData (CS_COMMAND *cmd, LPTABLEDEF ti)
  {
  CS_RETCODE  retcode;
  BOOL correct = TRUE;
  int  i;
  GetColInfo(ti);
  if (ColInfo != NULL) {
    for (i=0; ((i < nCols(ti)) && (correct)); i++) {
      odefin(cmd, (sword)(i+1),
                (ub1 *)  ColInfo[i].VarData,            // the receive Buffer
                (sword)  ColInfo[i].VarFormat.maxlength,// size of one array element (max 64 K )
                (sword)  ColInfo[i].VarFormat.datatype, // abbilden
                (sword)  -1,                            // Kontrolle scale
                (sb2 *)  ColInfo[i].VarInd,             // indicator needed if arrays used
                (text *) 0,                             // fmt is not used in C
                (sword)  -1,                            // fmtl is not used in C
                (sword)  -1,                            // fmtt is not used in C
                (ub2 *)  ColInfo[i].VarLen,             // variable Length info of array
                (ub2 *)  ColInfo[i].VarRetCode          // returncode for this row
          );
      retcode = ocirethandling(dbase->lda, cmd);
      correct = (retcode == CS_SUCCEED);
      } // for
    } // if

  // Binden der expliziten Parameter
  i = 1 ;
  for ( BndList FAR *h = TopDsc ; h != NULL ; h = h->Next) {
    ub2 dt;
    h->data = GetSybDataType_f (&h->VarLen,&dt,h->Type,h->Size);
    odefin (cmd, i, 
            (ub1 *) h->data,
            h->VarLen,
            dt,
            (sword)  -1,                     // Kontrolle scale
            (sb2 *)  &h->VarInd,             // indicator needed if arrays used
            (text *) 0,                      // fmt is not used in C
            (sword)  -1,                     // fmtl is not used in C
            (sword)  -1,                     // fmtt is not used in C
            (ub2 *)  &h->VarLen,             // variable Length info of array
            (ub2 *)  &h->VarRetCode          // returncode for this row
           );
    retcode = ocirethandling(dbase->lda, cmd);
    correct = (retcode == CS_SUCCEED);
    i = i + 1 ;
    }

  return (correct);
  } // sybstmt::BindColData

//
// Ausfueheren eines Kommandos im Oracle
// Das speichern der Daten uebernehmen dann die
// virtuellen Funktion StoreData (bzw. die Vorbereitung
// dazu BindColData und deren virtuelle Funktionen)
//

extern void dbglog_starttimer(void);
LPSTR PushParam (LPSTR old,BndList FAR *bl)
  {
  char actString[256];
  switch (bl->Type) {
    case CS_SMALLINT_TYPE :
      if (GetBlockSize (bl->data) == 2)
        FormatOutTxt (actString,bl->data,VAR_STRARR);
      else
        FormatOutTxt (actString,bl->data,VAR_LONG);
      break ;
    case CS_REAL_TYPE :
      FormatOutTxt (actString,bl->data,VAR_DEC);
      break ;
    case CS_TEXT_TYPE :
    case CS_TEXT_TYPE_BIG :
      FormatOutTxt (actString,bl->data,VAR_STR);
      break ;
    case CS_IMAGE_TYPE :
    case OCI_DATE_TYPE :
      FormatOutTxt (actString,bl->data,VAR_OBJ);
      break ;
    }
  int l = lstrlen (actString);
  LPSTR res;
  if (old != NULL) {
    // Den neuen String nach vorne, da die Strings verkehrt herum aufgebaut werden
    res = LPSTR (GetGlobMem (GetBlockSize (old) + l + 1));
    lmemcpy (res,actString,l);
    res[l] = ',' ;
    lmemcpy (res + l + 1,old,GetBlockSize(old));
    FreeGlobMem (old);
    }
  else {
    res = LPSTR (GetGlobMem (l + 1));
    lmemcpy (res,actString,l);
    }
  return res;
  }

void TestCritical(int error)
  {
  // vorerst mal die wichtigen (Tablespace voll)
  if (((error >= 1626) && (error <= 1634)) ||
      ((error >= 1650) && (error <= 1659))) {
    WIN_ASSERT_TEXT(FALSE,"critical ORACLE error");
    }
  }

/************************************************************************
  execute

  purpose:  runs the SQL Statement (see OCI Manual).
            For Select Statements the handling is more complicated:
            - first all output columns are bound to the output variables
            - then as many rows as possible will be fetch together with the
              execution of the statement
            - the result is then moved form the bound array structure to the
              clinicum memory structure
            - then the fetch of additional rows is done.
  input:    cmdbuf     contains the SQL Statement in a NULL teerminated String
            ti         contains the table's structure informations
            con        contains the connection information. If this is set to
                       NULL, the dbase->connection will be used.
            bdsc       in case of an insert / update the description of the blob
                       ... The blob must be bind with obndrv to the variable
                       ":BLOB"
  output:   --
  return:   CS_SUCCEED   everything ok
            CS_FAIL      an error occured
            CS_END_DATA  no row has been found at all
            CS_LAST_DATA there are some rows, but this rows are the last ones
            CS_NOT_AVAIL the actual request is not yet available (at moment
                         thius is returned if the sequence number hasn't been defined
                         yet in the actual session)
*************************************************************************/

CS_RETCODE sybstmt::FetchMore (LPTABLEDEF ti)
  {
  ub4           i,rowsDone, rowsRead, rowsGot;
  int lastErrNr;
  CS_RETCODE    retcode = CS_FAIL;

  for ( BOOL doMore = TRUE ; doMore ; ) {
    doMore = FALSE ;
    // odefin: Bind all output variables
    if (BindColData (cmd,ti)) {
      // oexfet
      rowsDone = 0;
      rowsGot = cmd->rpc;
      BOOL first = TRUE;
      while ( (cmd->rc == OCI_SUCCESS)
              && ((RecsToGet <= 0)
                  || ((int)rowsDone < RecsToGet))) {
        int RecsToFetch = nRows(ti);
        if ((RecsToGet > 0) &&
            ((RecsToGet - (int)rowsDone) < RecsToFetch))
          RecsToFetch = (RecsToGet - (int)rowsDone);
        ofen((Cda_Def *)cmd, (sword)RecsToFetch);
        for (int j = 0; ((cmd->rc == 3123) || (cmd->rc == 3127)) && (j < RetriesOnBlock); j++) {
          DWORD t0 = GetTickCount ();
          while ((GetTickCount() - t0) < 200L);
          ofen((Cda_Def *)cmd, (sword)RecsToFetch);
          }
        lastErrNr = cmd->rc;
        ocirethandling(dbase->lda, cmd);
        if (cmd->rc == OCI_SUCCESS ||
            cmd->rc == OCI_WRN_NO_DATA_FOUND) {
          rowsRead = cmd->rpc - rowsGot;
          rowsGot = cmd->rpc ;
          for (i=0; i < rowsRead; i++) {
            BOOL done = StoreData(ti, (int)i);
            if (done) rowsDone++;
            if ((blobCol >= 0) && (done)) {
              // Read the part with the Blob
              DWORD bytesRead = 0L;
              #define BLOBBUFFER_SIZE   0x8000
              for ( GLOBALHANDLE hGres = GlobalAlloc (GMEM_MOVEABLE,BLOBBUFFER_SIZE) ; ;
                    hGres = GlobalReAlloc (hGres,bytesRead + BLOBBUFFER_SIZE,GMEM_MOVEABLE)) {
                ub4 retl;
                oflng (cmd,blobCol + 1,(ub1 *) ((char huge *) GlobalLock (hGres) + bytesRead) ,BLOBBUFFER_SIZE,24,&retl,bytesRead);
                lastErrNr = cmd->rc;
                ocirethandling(dbase->lda, cmd);
                if ((cmd->rc == OCI_SUCCESS) && ((retl > 0L) || (bytesRead > 0L))) {
                  GlobalUnlock (hGres);
                  bytesRead += retl ;
                  if (retl < BLOBBUFFER_SIZE) {
                    GlobalReAlloc (hGres,bytesRead,GMEM_MOVEABLE);
                    BlobDesc bdsc ;
                    bdsc.Size = bytesRead ;
                    bdsc.hGmem = hGres ;
                    res->act->rec[0]->Initialize (blobCol,&bdsc,sizeof(bdsc));
                    break ;
                    }
                  }
                else {
                  GlobalFree (hGres);
                  break ;
                  }
                }
              }
            } // for
          } // if
        } // while

      #ifdef _DEBUG
        char outtxt[256];
        sprintf (outtxt,"Anzahl gelesener Rows = %d", (int)rowsDone);
        DBG_ASSERT_TEXT(FALSE,"execute", outtxt);
      #endif
      // determine, whether the statement has been executed correctly
      if (cmd->rc == OCI_WRN_NO_DATA_FOUND) {
        retcode = CS_LAST_DATA;
        if (CancelAlways) ocan ((Cda_Def *) cmd);
        oclose((Cda_Def *) cmd);
        for (int i = 0; ((cmd->rc == 3123) || (cmd->rc == 3127)) && (i < RetriesOnBlock); i++) {
          DWORD t0 = GetTickCount ();
          while ((GetTickCount() - t0) < 200L);
          oclose((Cda_Def *) cmd);
          }
        ocirethandling(dbase->lda, cmd);
        closeDone = TRUE ;
        if (cmd->rc != OCI_SUCCESS) {
          retcode = CS_FAIL;
          } // if
        } // if
      else if (cmd->rc == OCI_SUCCESS) {
        retcode = CS_SUCCEED;
        } // if
      } // if BindColData
    else {
      retcode = CS_FAIL;
      } // else iff
    }
  return retcode;
  }

LPSTR ActCmdBuf = NULL;
LPSTR GetParamString()
  {
  LPSTR MyParamString = NULL;
  for ( BndList *bl = Top ; bl != NULL ; bl = bl->Next)
    MyParamString = PushParam (MyParamString,bl);
  return MyParamString;
  }

CS_RETCODE sybstmt::execute (LPSTR cmdbuf,LPTABLEDEF ti,CS_CONNECTION *con,LPBLOBDESC bdsc,BOOL doCursorClose)
  {
    ActCmdBuf = cmdbuf;
    LPSTR procName = ProcName (cmdbuf);

    #ifdef _DEBUG
    char outtxt[100];
    #endif

    CS_RETCODE    retcode = CS_FAIL;
    sword         sql_function;
    ub4           i, rowsDone, rowsRead, rowsGot;
    BndList FAR *bl ;
    int lastErrNr;
    LongString eStr;
    if (procName != NULL) {
      eStr = eStr + "BEGIN CLINICUM." + procName + " (:CUR" ;
      for ( BndList FAR *b = GetLastBnd () ; b != NULL ; b = GetPrevBnd (b) ) {
        char vname[32];
        wsprintf (vname,",:%c%d",b->prefix,b->Num);
        eStr = eStr + vname ;
        }
      eStr = eStr + "); END;" ;
      }

    text *c = (procName == NULL) ? (text *) cmdbuf : (text *)eStr.Ptr() ;

    BOOL doLog = DoLog();
    DWORD time;
    LPSTR ParamString;
    if (doLog) {
      time = GetTickCount();
      ParamString = NULL;
      }

    dbglog_starttimer();   // auf jeden Fall die Zeit messen

    DWORD lctime;
    if (LogCount > 0) {
      lctime = GetTickCount();
      BeginStationLog (LPSTR(c),lctime);
      }

    BOOL canDone = TRUE ;

    doNext = doIt = FALSE ;

    if (con == NULL) con = dbase->lda ;

    #ifdef _DEBUG
      sprintf (outtxt,"SQL len = %d", (int)strlen(cmdbuf));
      DBG_ASSERT_TEXT(FALSE, outtxt, (char *)cmdbuf);
    #endif

    // Allocate the structure for the cursor
    // cmd = (CS_COMMAND FAR *) GetGlobMem( sizeof(*cmd) ); already point to cmd_struct
    if (cmd != NULL) {
      // Open the structure for the cursor
      oopen((Cda_Def *) cmd, (Lda_Def *) con,
            (text *) 0, (sword) -1, (sword) -1, (text *) 0, (sword) -1);
      for (int ii = 0; ((cmd->rc == 3123) || (cmd->rc == 3127)) && (ii < RetriesOnBlock); ii++) {
        DWORD t0 = GetTickCount ();
        while ((GetTickCount() - t0) < 200L);
        oopen((Cda_Def *) cmd, (Lda_Def *) con,
              (text *) 0, (sword) -1, (sword) -1, (text *) 0, (sword) -1);
        }
      if (LogCount > 0) {
        WriteStationLog ("nach oopen",GetTickCount() - lctime);
        }
      lastErrNr = cmd->rc;
      ocirethandling(dbase->lda, cmd);
      if (cmd->rc == OCI_SUCCESS) {
        closeDone = FALSE ;

        // Parse the statement
        oparse( (Cda_Def *)cmd,
                (text *) c,
                (sb4)    -1,
                (sword)  (Op != DBOP_PARSE) ? OCI_DEFFLG_DEFERRED : 0,
                (ub4)    OCI_LNGFLG_ORACLE7 );
        if (LogCount > 0) {
          WriteStationLog ("nach oparse",GetTickCount() - lctime);
          }
        lastErrNr = cmd->rc;
        if (Op != DBOP_PARSE)
          ocirethandling(dbase->lda, cmd);
        if ((Op != DBOP_PARSE) && (cmd->rc == OCI_SUCCESS)) { // in the deferred mode, this is always true...
          sql_function = cmd->ft;
          // Bind all Inputvariables: no Inputvariables are specified at all.
          // is it a query ?
#ifdef UEBERLEGT
          for ( ; ((bl = PopFromBndList ()) != NULL) ; ) { }
#endif
          for (bl = Top ; bl != NULL ; bl = bl->Next) {
            char vname[32];
            wsprintf (vname,":%c%d",bl->prefix,bl->Num);
            if (bl->indp)
              obndra (cmd,(ub1 FAR *) vname,-1,
                      (ub1 FAR *)bl->data, // progv
                      bl->Size, // provl
                      bl->Type, // ftype
                      -1,       // scale
                      bl->indp, // indp
                      bl->alen, // alen
                      NULL,     // arcode
                      0L,       // maxsiz
                      NULL,     // cursiz
                      NULL,     // fmt*..
                      -1,-1);
            else
              obndrv (cmd,(ub1 FAR *) vname,-1,(ub1 FAR *)bl->data,bl->Size,bl->Type,-1,NULL,NULL,-1,-1);
            ocirethandling(dbase->lda, cmd);
            WIN_ASSERT (cmd->rc == OCI_SUCCESS);
            if (doLog)
              ParamString = PushParam (ParamString,bl);
#ifdef UEBERLEGT
            FreeBndElem (bl);
#endif
            }
          if (procName != NULL) {
            // Bind the cursor
            obndrv (cmd,(ub1 FAR *) ":CUR",-1,(ub1 FAR *)&cmd_fetch_struct,-1,SQLT_CUR,-1,NULL,NULL,-1,-1);
            ocirethandling(dbase->lda, cmd);
            WIN_ASSERT (cmd->rc == OCI_SUCCESS);
            }
          if (LogCount > 0) {
            WriteStationLog ("nach inputbind",GetTickCount() - lctime);
            }
          short n = 1;
          for ( BndList FAR *h = TopDsc ; h != NULL ; h = h->Next) {
            LONG s;
            odescr (cmd,n,&s,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
            if (s == 0L) s = 0x4000;      // Long Datentyp, aber trotzdem abholen was geht....
            h->Size = s;
            n = n + 1;
            }
          for ( BOOL doMore = TRUE ; doMore ; ) {
            doMore = FALSE ;
            switch (sql_function) {
              case (OCI_FT_SELECT) : {
                // odefin: Bind all output variables
                if (BindColData (cmd,ti)) {
                  if (LogCount > 0) {
                    WriteStationLog ("nach outputbind",GetTickCount() - lctime);
                    }
                  // oexfet
                  rowsDone = 0;
                  rowsGot = 0;
                  BOOL first = TRUE;
                  while ( (cmd->rc == OCI_SUCCESS)
                          && ((RecsToGet <= 0)
                              || ((int)rowsDone < RecsToGet))) {
                    if (procName) {
                      first = FALSE ;
                      canDone = FALSE ;
                      }
                    if (first) { // first time in this iteration
                      canDone = FALSE;
                      oexfet((Cda_Def *)cmd, (ub4)nRows(ti), (sword)canDone, (sword)0);
                      for (int i = 0; ((cmd->rc == 3123) || (cmd->rc == 3127)) && (i < RetriesOnBlock); i++) {
                        DWORD t0 = GetTickCount ();
                        while ((GetTickCount() - t0) < 200L);
                        oexfet((Cda_Def *)cmd, (ub4)nRows(ti), (sword)canDone, (sword)0);
                        }
                      if (LogCount > 0) {
                        WriteStationLog ("nach oexfet",GetTickCount() - lctime);
                        }
                      } // if
                    else { // the nth time in this iteration
                      WIN_ASSERT (!canDone);
                      int RecsToFetch = nRows(ti);
                      if ((RecsToGet > 0) &&
                          ((RecsToGet - (int)rowsDone) < RecsToFetch))
                        RecsToFetch = (RecsToGet - (int)rowsDone);
                      ofen((Cda_Def *)cmd, (sword)RecsToFetch);
                      for (int i = 0; ((cmd->rc == 3123) || (cmd->rc == 3127)) && (i < RetriesOnBlock); i++) {
                        DWORD t0 = GetTickCount ();
                        while ((GetTickCount() - t0) < 200L);
                        ofen((Cda_Def *)cmd, (sword)RecsToFetch);
                        }
                      if (LogCount > 0) {
                        WriteStationLog ("nach ofen",GetTickCount() - lctime);
                        }
                      } // else if
                    lastErrNr = cmd->rc;
                    ocirethandling(dbase->lda, cmd);
                    if (cmd->rc == OCI_SUCCESS ||
                        cmd->rc == OCI_WRN_NO_DATA_FOUND) {
                      rowsRead = cmd->rpc - rowsGot;
                      rowsGot = cmd->rpc ;
                      for (i=0; i < rowsRead; i++) {
                        BOOL done = StoreData(ti, (int)i);
                        if (done) rowsDone++;
                        if ((blobCol >= 0) && (done)) {
                          // Read the part with the Blob
                          DWORD bytesRead = 0L;
                          #define BLOBBUFFER_SIZE   0x8000
                          for ( GLOBALHANDLE hGres = GlobalAlloc (GMEM_MOVEABLE,BLOBBUFFER_SIZE) ; ;
                                hGres = GlobalReAlloc (hGres,bytesRead + BLOBBUFFER_SIZE,GMEM_MOVEABLE)) {
                            ub4 retl;
                            oflng (cmd,blobCol + 1,(ub1 *) ((char huge *) GlobalLock (hGres) + bytesRead) ,BLOBBUFFER_SIZE,24,&retl,bytesRead);
                            lastErrNr = cmd->rc;
                            ocirethandling(dbase->lda, cmd);
                            if ((cmd->rc == OCI_SUCCESS) && ((retl > 0L) || (bytesRead > 0L))) {
                              GlobalUnlock (hGres);
                              bytesRead += retl ;
                              if (retl < BLOBBUFFER_SIZE) {
                                GlobalReAlloc (hGres,bytesRead,GMEM_MOVEABLE);
                                BlobDesc bdsc ;
                                bdsc.Size = bytesRead ;
                                bdsc.hGmem = hGres ;
                                res->act->rec[0]->Initialize (blobCol,&bdsc,sizeof(bdsc));
                                break ;
                                }
                              }
                            else {
                              GlobalFree (hGres);
                              break ;
                              }
                            }
                          }
                        } // for
                      } // if
                    first = FALSE ;
                    } // while

                  #ifdef _DEBUG
                    char outtxt[256];
                    sprintf (outtxt,"Anzahl gelesener Rows = %d", (int)rowsDone);
                    DBG_ASSERT_TEXT(FALSE,"execute", outtxt);
                  #endif
                  // determine, whether the statement has been executed correctly
                  if (cmd->rc == OCI_WRN_NO_DATA_FOUND) {
                    retcode = CS_LAST_DATA;  // >> FL 07.03.96 StandardGet needs this information
                    if (rowsDone == 0) {
                      retcode = CS_END_DATA;
                      } // if
                    } // if
                  else if (cmd->rc == OCI_WRN_SEQ_NOT_YET_DEFINED) {
                    retcode = CS_NOT_AVAIL;
                    } // if
                  else if (cmd->rc == OCI_SUCCESS) {
                    retcode = CS_SUCCEED;
                    } // if
                  } // if BindColData
                else {
                  retcode = CS_FAIL;
                  } // else iff
                break;
                } // case
              case (OCI_FT_INSERT) :
              case (OCI_FT_UPDATE) :
              case (OCI_FT_DELETE) :
              default: {
                GLOBALHANDLE hGres ;
                if (bdsc != NULL) {
                  hGres = GlobalAlloc (GMEM_MOVEABLE,bdsc->Size + sizeof(DWORD));
                  ub1 FAR *buffer = (ub1 FAR *) GlobalLock (hGres);
                  *(DWORD FAR *) buffer = bdsc->Size;
                  hmemcpy (buffer + sizeof(DWORD),GlobalLock (bdsc->hGmem),bdsc->Size);
                  GlobalUnlock (bdsc->hGmem);
                  obndrv (cmd,(ub1 FAR *)":BLOB",-1,
                          buffer,-1,95,   // It is represented by a long varraw datatype
                          -1,NULL,NULL,-1,-1);
                  ocirethandling(dbase->lda, cmd);
                  }
                oexec((Cda_Def *)cmd);
                for (int i = 0; ((cmd->rc == 3123) || (cmd->rc == 3127)) && (i < RetriesOnBlock); i++) {
                  DWORD t0 = GetTickCount ();
                  while ((GetTickCount() - t0) < 200L);
                  oexec((Cda_Def *)cmd);
                  }
                if (LogCount > 0) {
                  WriteStationLog ("nach oexec",GetTickCount() - lctime);
                  }
                if (bdsc != NULL) {
                  GlobalUnlock (hGres);
                  GlobalFree (hGres);
                  }
                lastErrNr = cmd->rc;
                ocirethandling(dbase->lda, cmd);
                if (cmd->rc == OCI_SUCCESS) {
                  if (procName != NULL) {
                    closeDone = TRUE ;
                    oclose((Cda_Def *) cmd);
                    for (int i = 0; ((cmd->rc == 3123) || (cmd->rc == 3127)) && (i < RetriesOnBlock); i++) {
                      DWORD t0 = GetTickCount ();
                      while ((GetTickCount() - t0) < 200L);
                      oclose((Cda_Def *) cmd);
                      }
                    if (LogCount > 0) {
                      WriteStationLog ("nach oclose (PROC)",GetTickCount() - lctime);
                      }
                    ocirethandling(dbase->lda, cmd);
                    cmd = &cmd_fetch_struct ;
                    doMore = TRUE ;
                    sql_function = OCI_FT_SELECT ;
                    }
                  retcode = CS_SUCCEED;
                  } // if
                else {
                  retcode = CS_FAIL;
                  } // else
                break;
                } // case
              } // switch
            }
          } // if
        else if (Op == DBOP_PARSE) {
          // parseCmd muss durch den Aufrufer freigegeben werden!
          LPPARSERECBUFFER (res)->parseCmd = LPSTR(GetGlobMem (strlen (LPSTR (c)) + 1)) ;
          lstrcpy (LPPARSERECBUFFER (res)->parseCmd, LPSTR (c));
          if (cmd->rc != OCI_SUCCESS) {
            LPPARSERECBUFFER (res)->error    = (int) (Cda_Def *) cmd->rc;
            LPPARSERECBUFFER (res)->errorOfs = (int) (Cda_Def *) cmd->peo;
            // errorMsg muss durch den Aufrufer freigegeben werden!
            LPPARSERECBUFFER (res)->errorMsg = LPSTR(GetGlobMem (512)) ;
            sword n;
            n = oerhms ((Lda_Def *) con, (sb2) ((Cda_Def *) cmd->rc), 
                        (text *) (LPPARSERECBUFFER (res)->errorMsg), (sword) 512);
            if (*((LPPARSERECBUFFER (res)->errorMsg) + n - 1) == '\n')
              *((LPPARSERECBUFFER (res)->errorMsg) + n - 1) = '\0';
            retcode = CS_FAIL;
            }
          else
            retcode = CS_SUCCEED;
          }
        // close the cursor
        if ((doCursorClose) || (retcode != CS_SUCCEED)) {
          if ((CancelAlways) || (!canDone)) {
            ocan ((Cda_Def *) cmd);
            if (LogCount > 0) {
              WriteStationLog ("nach ocan",GetTickCount() - lctime);
              }
            }
          closeDone = TRUE ;
          oclose((Cda_Def *) cmd);  // ocan is not necessary (we hop this)
          for (int i = 0; ((cmd->rc == 3123) || (cmd->rc == 3127)) && (i < RetriesOnBlock); i++) {
            DWORD t0 = GetTickCount ();
            while ((GetTickCount() - t0) < 200L);
            oclose((Cda_Def *) cmd);
            }
          if (LogCount > 0) {
            WriteStationLog ("nach oclose",GetTickCount() - lctime);
            }
          ocirethandling(dbase->lda, cmd);
          if (cmd->rc != OCI_SUCCESS) {
            retcode = CS_FAIL;
            } // if
          } // if CursorClose
        }
      // FreeGlobMem(cmd); cmd points to cmd_struct all the time
      // cmd = NULL;
      }
    else {
      WIN_ASSERT_TEXT (FALSE,"execute_cmd: allocation of cursor failed");
      } // if

    #ifdef _DEBUG
    sprintf (outtxt,"execute retval = %d", (int)retcode);
    DBG_ASSERT_TEXT(FALSE, outtxt, "");
    #endif

#ifdef UEBERLEGT
    if ((retcode == CS_FAIL) && (!IsToIgnore (lastErrNr))) {
      LPSTR MyParamString = (LPSTR)GetGlobMem(lstrlen("STATEMENT:") + 1);
      sprintf (MyParamString,"STATEMENT:");
      for ( bl = Top ; bl != NULL ; bl = bl->Next)
        MyParamString = PushParam (MyParamString,bl);
      DBGFORCE_ASSERT_TEXT(FALSE, MyParamString, (char *)cmdbuf);
      FreeGlobMem(MyParamString);
      TestCritical(lastErrNr);
      } // if
#endif

    // Die Liste Mit den Bindings muss unbedingt aufgerauemt werden
    for ( ; ((bl = PopFromBndList ()) != NULL) ; ) {
      if (bl->indp != NULL) {
        // Fuer Strings: das Null - Zeichen mit dazugeben
        if (*bl->indp == OCI_IND_NULL)
          req->SetOutParam (bl->parNr,NULL,0);
        else
          req->SetOutParam (bl->parNr,bl->data,(*bl->alen) + ((bl->prefix == 'S') ? 1 : 0));
        }
      FreeBndElem (bl);
      }

    // Der Speicher der gebundenen Variablen wieder freigeben
    FreeMemList ();

    if (doLog) {
      // time = GetTickCount() - time;
      LogCmd (LPSTR(c),time,GetTickCount(),ParamString);
      if (ParamString != NULL)
        FreeGlobMem (ParamString);
      }

    if (LogCount > 0) {
      EndStationLog ();
      }

    // Pointer wieder richtig stellen
    cmd = &cmd_struct ;
    ActCmdBuf = NULL;
    return (retcode);
  } //sybase::execute

void seqcheck::GetColInfo(LPTABLEDEF t0)
  {
  if (ColInfo == NULL) {
    ColInfo = (_COLINFO FAR *) GetGlobMem (sizeof(*ColInfo));
    ColInfo[0].VarLen     = (VARLEN_TYPE FAR *) GetGlobMem (sizeof(*ColInfo[0].VarLen) * nRows(NULL)) ;
    ColInfo[0].VarData    = GetSybDataType (&ColInfo[0].VarFormat,VAR_LONG,sizeof(LONG),nRows(NULL));
    ColInfo[0].VarRetCode = (VARRETCODE_TYPE FAR *) GetGlobMem (sizeof(*ColInfo[0].VarRetCode) * nRows(NULL)) ;
    ColInfo[0].VarInd     = (VARIND_TYPE FAR *) GetGlobMem (sizeof(*ColInfo[0].VarInd) * nRows(NULL)) ;
    dbCols = 1;
    }
  }

BOOL seqcheck::StoreData (LPTABLEDEF ti,int row)
  {
    LPVOID data = LPVOID (LPSTR (ColInfo[0].VarData) + row * ColInfo[0].VarFormat.maxlength) ;
    int size = int (ColInfo[0].VarLen[row]);
    if (size == sizeof(long)) {
      controlseqnum = *(long *) data ;
      }
    else {
      controlseqnum = 0;
      }
  return TRUE ;
  }

void tablecheck::GetColInfo(LPTABLEDEF t0)
  {
  if (ColInfo == NULL) {
    blobCol = -1 ;
    dbCols = 1;
    ColInfo = (_COLINFO FAR *) GetGlobMem (sizeof(*ColInfo));
    ColInfo[0].VarLen    = (VARLEN_TYPE FAR *) GetGlobMem (sizeof(*ColInfo[0].VarLen) * nRows(t0)) ;
    ColInfo[0].VarData   = GetSybDataType (&ColInfo[0].VarFormat,VAR_STR,64,nRows(t0));
    ColInfo[0].VarRetCode = (VARRETCODE_TYPE FAR *) GetGlobMem (sizeof(*ColInfo[0].VarRetCode) * nRows(t0)) ;
    ColInfo[0].VarInd     = (VARIND_TYPE FAR *) GetGlobMem (sizeof(*ColInfo[0].VarInd) * nRows(t0)) ;
    }
  }

void colcheck::GetColInfo(LPTABLEDEF t0)
  {
  if (ColInfo == NULL) {
    blobCol = -1 ;
    dbCols = 2;
    ColInfo = (_COLINFO FAR *) GetGlobMem (2 * sizeof(*ColInfo));
    ColInfo[0].VarLen     = (VARLEN_TYPE FAR *) GetGlobMem (sizeof(*ColInfo[0].VarLen) * nRows(t0)) ;
    ColInfo[1].VarLen     = (VARLEN_TYPE FAR *) GetGlobMem (sizeof(*ColInfo[1].VarLen) * nRows(t0)) ;
    ColInfo[0].VarData    = GetSybDataType (&ColInfo[0].VarFormat,VAR_STR,64,nRows(t0));
    ColInfo[1].VarData    = GetSybDataType (&ColInfo[1].VarFormat,VAR_STR,11,nRows(t0));
    ColInfo[0].VarRetCode = (VARRETCODE_TYPE FAR *) GetGlobMem (sizeof(*ColInfo[0].VarRetCode) * nRows(t0)) ;
    ColInfo[1].VarRetCode = (VARRETCODE_TYPE FAR *) GetGlobMem (sizeof(*ColInfo[1].VarRetCode) * nRows(t0)) ;
    ColInfo[0].VarInd     = (VARIND_TYPE FAR *) GetGlobMem (sizeof(*ColInfo[0].VarInd) * nRows(t0)) ;
    ColInfo[1].VarInd     = (VARIND_TYPE FAR *) GetGlobMem (sizeof(*ColInfo[1].VarInd) * nRows(t0)) ;
    }
  }

BOOL tablecheck::StoreData (LPTABLEDEF ti,int row)
  {
  LPVOID data = LPVOID (LPSTR (ColInfo[0].VarData) + row * ColInfo[0].VarFormat.maxlength) ;
  int size = int (ColInfo[0].VarLen[row]);
  if (ColInfo[0].VarInd[row] != OCI_IND_NULL) {
    TableData d;
    d.IsTested = FALSE ;
    dbase->TableHash->SetData (LPSTR(data),&d,sizeof(d));
    }
  return TRUE ;
  }

BOOL colcheck::StoreData (LPTABLEDEF ti,int row)
  {
  LPSTR str = LPSTR (LPSTR (ColInfo[0].VarData) + row * ColInfo[0].VarFormat.maxlength) ;
  int size = int (ColInfo[0].VarLen[row]);
  int FAR *lpType = (int FAR *) (LPSTR (ColInfo[1].VarData) + row * ColInfo[1].VarFormat.maxlength) ;
  int size_1 = int (ColInfo[1].VarLen[row]);
  if ((ColInfo[0].VarInd[row] != OCI_IND_NULL) &&
      (ColInfo[1].VarInd[row] != OCI_IND_NULL)) {
    char VarName[128];
    lstrcpy (VarName,str);
    AnsiUpper (VarName);
    colhash->SetData (VarName,lpType,size_1);
    }
  return TRUE ;
  }

void datetimestmt::GetColInfo(LPTABLEDEF t0)
  {
  if (ColInfo == NULL) {
    ColInfo = (_COLINFO FAR *) GetGlobMem (sizeof(*ColInfo));
    ColInfo[0].VarLen     = (VARLEN_TYPE FAR *) GetGlobMem (sizeof(*ColInfo[0].VarLen) * nRows(NULL)) ;
    ColInfo[0].VarData    = GetSybDataType (&ColInfo[0].VarFormat,VAR_DATETIME,sizeof(packdatetime),nRows(NULL));
    ColInfo[0].VarRetCode = (VARRETCODE_TYPE FAR *) GetGlobMem (sizeof(*ColInfo[0].VarRetCode) * nRows(NULL)) ;
    ColInfo[0].VarInd     = (VARIND_TYPE FAR *) GetGlobMem (sizeof(*ColInfo[0].VarInd) * nRows(NULL)) ;
    dbCols = 1;
    }
  }

BOOL datetimestmt::StoreData (LPTABLEDEF ti,int row)
  {
  LPVOID data = LPVOID (LPSTR (ColInfo[0].VarData) + row * ColInfo[0].VarFormat.maxlength) ;
  int size = int (ColInfo[0].VarLen[row]);
  if (ColInfo[0].VarInd[row] != OCI_IND_NULL) {
    int rLen;
    LPVOID cd = ConvertToMData_f (VAR_DATETIME,data,size,&rLen);
    if (cd != NULL)
      datetime = * ((packdatetime FAR *) cd);
    }
  return TRUE ;
  }

static char UserNameSet[128],PassWordSet[128];
void GetConnectString (LPSTR buf, int bufLen, const LPSTR defUserName,BOOL forUpdate)
  {
  if (*UserNameSet) {
    lstrncpy (buf,UserNameSet,bufLen);
    }
  else {
    int rLen = 0;
    if (forUpdate)
      rLen = GetPrivateProfileString ("Oracle","UpdateUser", "", buf, bufLen,GetIniName());
    if (rLen == 0)
      GetPrivateProfileString ("Oracle","Username", defUserName, buf, bufLen,GetIniName());
    }
  } // GetConnectString

void _export FAR PASCAL SetUserName (LPSTR un,LPSTR pw)
  {
  lstrncpy (UserNameSet,un,sizeof(UserNameSet));
  lstrncpy (PassWordSet,pw,sizeof(PassWordSet));
  }

void sybase::FetchTableNames ()
  {
  tablecheck *h = new tablecheck ();
//  h->execute ("SELECT table_name FROM USER_TABLES",NULL);
  h->execute ("SELECT table_name FROM USER_TABLES UNION SELECT view_name AS tabel_name FROM USER_VIEWS",NULL);
  delete h; // >> FL 28.02.96 added to free the memory again.
  } // sybase:: FetchNames


//
// set the session parameters
// - default Date / Time Format
//
void sybase::AlterSession()
  {
    sybstmt *h = new sybstmt ();
    LongString s;
    if (IsOrbis()) {
      s.Clear();
      s = s + "BEGIN STARTUP; END;";
      h->execute (s.Ptr(),NULL);
      }
    s.Clear();
    s = s + "ALTER SESSION " +
            " SET NLS_DATE_FORMAT = '" + OCI_DATETIME_FORMAT + "' ";
    h->execute (s.Ptr(),NULL);
    s.Clear();
    s = s + "ALTER SESSION SET NLS_SORT=BINARY" ;
    h->execute (s.Ptr(),NULL);
    s.Clear();
    s = s + "ALTER SESSION SET OPTIMIZER_GOAL = FIRST_ROWS" ;
    h->execute (s.Ptr(),NULL);

    if (!IsOrbis()) {
      BOOL errWasSet1 = DBIgnoreError (ERRTYPE_OBJEXISTS,TRUE);
      BOOL errWasSet2 = DBIgnoreError (ERRTYPE_NOPRIVILEGS,TRUE);
      s.Clear ();
      s = s + "CREATE FUNCTION CLTrans (meintext IN VARCHAR2) RETURN VARCHAR2 AS" ;
      s = s + " BEGIN" ;
      s = s + "    RETURN Translate (meintext," ;
      s = s + "        '_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyzÄäÖöÜüß'," ;
      s = s + "        'ABDEFGHIJKMNOPQRUVWXZacdefgBDEFGHIJKMNOPQRUVWXZacdefgCCSSbbY');" ;
      s = s + " END;" ;
      h->execute (s.Ptr(),NULL);
      if (!errWasSet1)
        DBIgnoreError (ERRTYPE_OBJEXISTS,FALSE);
      if (!errWasSet2)
        DBIgnoreError (ERRTYPE_NOPRIVILEGS,FALSE);
      }
    delete h;
  } // sybase::AlterSession
 
//
// Initialisieren der Clientlib
//
 
CS_RETCODE sybase::Init ()
  {
    CS_RETCODE  retcode = CS_SUCCEED;
 
    // prepare the local data area
    lda = &slda;
    //lda = (Lda_Def *) (GetGlobMem (sizeof(Lda_Def)));
    //if (lda == NULL)
    //{
    //    WIN_ASSERT_TEXT (FALSE, "init: Memory allocation for lda failed");
    //  retcode = CS_FAIL;
    //} // if

    // prepare the host data area
    hda = shda;
    //hda = (ub1 *) (GetGlobMem (HDA_SIZE * sizeof(ub1)));
    //if (hda == NULL)
    //{
    //  FreeGlobMem(lda);
    //  WIN_ASSERT_TEXT (FALSE, "init: Memory allocation for hda failed");
    //  retcode = CS_FAIL;
    //} // if

    // callback functions are not installed
    // all error handling will be done by explicit return code
    // checks

    return retcode ;
  } // sybase::Init
 
CS_RETCODE sybase::Connect (LPSTR username, LPSTR password,LPSTR appname)
  {
    CS_RETCODE  retcode;
 
    // establish concurrent communications between
//    orlon(lda, hda, (text *)username, -1, (text *)password, -1, 0);
    olog(lda, hda, (text *)username, -1, (text *)password, -1, (text *)0, -1, OCI_LM_DEF);
    retcode = ocirethandling(lda, lda);
    if ( retcode != CS_SUCCEED ) {
      WIN_ASSERT_TEXT (FALSE, "connect: orlon() failed");
      } // if

    // set autocommit on
    if (retcode == CS_SUCCEED) {
      ocon(lda);
      retcode = ocirethandling(lda, lda);
      if ( retcode != CS_SUCCEED ) {
        WIN_ASSERT_TEXT (FALSE, "connect: ocon() failed");
        } // if
      } // if
 
    // the name of the applications is not used in the oracles interface.
    return retcode;
  } // sybase::Connect

extern hash *procHash ;
extern void FreeErrToIgnore ();
sybase::~sybase ()
  {
    CS_RETCODE  retcode;

    if (lda != NULL)
    {
      ologof(lda);
      retcode = ocirethandling(lda, lda);
      if (retcode != CS_SUCCEED) {
        WIN_ASSERT_TEXT (FALSE,"cleanup: ologof() failed");
      } // if
      // FreeGlobMem(lda);
    } // if
    if (TableHash != NULL) delete TableHash ;
    if (procHash != NULL) delete procHash ;
    if (VarAliasName != NULL) delete VarAliasName;
    if (VarSequenceName != NULL) delete VarSequenceName;
    FreeErrToIgnore ();

    //if (hda != NULL) {
    //  FreeGlobMem(hda);
    //} // if
  } // sybase::~sybase

void sybase::StartTableTest ()
  {
  if (!TablesFetched) {
    FetchTableNames ();
    TablesFetched = TRUE ;
    }
  }

char ActUserName[256];
char ActPassWord[256];
char BigRbsName[30];
sybase::sybase (LPSTR _username,LPSTR _password,LPSTR _appname,BOOL forUpdate)
  {
  VarAliasName = new LongString;
  VarSequenceName = new LongString;

  CS_RETCODE retcode;
  char hUserString[128];
  GetConnectString(hUserString, sizeof(hUserString), _username,forUpdate);
  lstrcpy (ActUserName,hUserString);
  for (LPSTR h = ActUserName ; *h ; h++) {
    if (*h == '@') *h = '\0' ;
    }
  AnsiUpper (ActUserName);

  // Bezeichnung des grossen rollback segments ermitteln
  GetPrivateProfileString ("Oracle","BigRbsName","RB1",BigRbsName,sizeof(BigRbsName) - 1,GetIniName());

  if (*PassWordSet) {
    lstrcpy(ActPassWord,PassWordSet);
    }
  else {
    // eventuell Passwort aus der floydst.dll holen:
    BOOL pwdGelesen = FALSE;
    if (forUpdate)
      pwdGelesen = SearchFSItem ("UpdatePassword",ActPassWord,sizeof(ActPassWord));
    if (!pwdGelesen) {
      if (!SearchFSItem ("DatabasePassword",ActPassWord,sizeof(ActPassWord)))
        lstrcpy(ActPassWord,_password);
      }
    }

  if ((retcode = Init ()) == CS_SUCCEED)
    retcode = Connect (hUserString,ActPassWord,_appname);
  if (retcode == CS_SUCCEED) {
    TableHash = new hash (111,STRKEY);
    dbase = this ;
    AlterSession();
    }
  if (retcode != CS_SUCCEED) {
    WIN_ASSERT_TEXT(FALSE,"sybase::sybase failed");
    } // if
  }

//
// Aufrauem - Prozedur:
//   Diese Funktion wird u.U zwei mal aufgerufen:
//   bei einem regulaeren Ausstieg durch DBReset
//   und auf jeden FALL durch den WEP! (fuer den
//      Fall das das Programm durch GP - Fehler abstuerzt)
//   d.h.:
//   die Funktion muss 2 maligen Einsprung zulassen, ohne
//   dadurch Fehler zu erzeugen
//
void _export FAR PASCAL DisConnect ()
  {
  if (dbase != NULL) {
    delete dbase;
    } // if
 
  dbase = NULL ;
  }

//
// Ermitteln des Typbezeichners eines Feldes, inkl. Angabe,
// ob eine Groesse beim Create - Statement verlangt wird.
// dabei kann durch k0 untersucht werden, ob es sich um ein
// AUTOINC Feld handelt.
//
LPSTR GetTypeName (LPVARDEF v,int vID,BOOL FAR *doSize,LPCLKEYDEF k0)
  {
    *doSize = FALSE ;
    switch (v->mType) {
      case VAR_LONG :
        if ((k0->VarID == WORD(vID)) && (k0->Attribute & CLKD_AUTOINC))
          return DB_TYPE_VAR_LONG_AUTO;                                             // ### FL Anpassen im Zuge der Sequenzierung
        else
          return DB_TYPE_VAR_LONG;
        break ;
      case VAR_DEC :
        return DB_TYPE_VAR_DEC;
        break ;
      case VAR_STR :
        if (v->VarSize > 2000)
          return DB_TYPE_VAR_STR_BIG;
        else if (v->VarSize > 254) {
          *doSize = TRUE;
          return DB_TYPE_VAR_STR;
          }
        else {
          *doSize = TRUE ;
          return DB_TYPE_VAR_STR_SMALL;
          }
        break ;
      case VAR_POINT :
        *doSize = TRUE ;
        return DB_TYPE_VAR_POINT;
        break ;
      case VAR_CONT :
        return DB_TYPE_VAR_CONT;
        break ;
      case VAR_STRARR :
        if ((k0->VarID == WORD(vID)) && (k0->Attribute & CLKD_AUTOINC))
          return DB_TYPE_VAR_STRARR_AUTO;                                           // ### FL Anpassen im Zuge der Sequenzierung
        else
          return DB_TYPE_VAR_STRARR ;
        break ;
      case VAR_FLAG :
        return DB_TYPE_VAR_FLAG ;
        break ;
      case VAR_SCALE :
        *doSize = TRUE ;
        return DB_TYPE_VAR_SCALE ;
        break ;
      case VAR_DATE :
        return DB_TYPE_VAR_DATE ;
        break ;
      case VAR_OBJ :
        if (v->VarSize > 254)
          return DB_TYPE_VAR_OBJ_BIG ;
        else {
          *doSize = TRUE ;
          return DB_TYPE_VAR_OBJ_SMALL ;
          }
        break ;
      case VAR_TIME :
        return DB_TYPE_VAR_TIME ;
        break ;
      case VAR_DATETIME :
        return DB_TYPE_VAR_TIMESTAMP ;
        break ;
      case VAR_BLOB :
        return DB_TYPE_VAR_OBJ_BIG ;
        break ;
      default :
        WIN_ASSERT(FALSE);
      }
    return NULL;
  } // GetTypeName

LPSTR BlockTypeName ()
  {
  return DB_TYPE_VAR_OBJ_BIG ;
  }

LPSTR BlockVarName ()
  {
  return "XXXBlockedXXX" ;
  }

BOOL TestAllIndex (LPTABLEDEF td);
void sybase::Testsequence (LPTABLEDEF td)
  {
  LPCLKEYDEF k0 = td->GetKeyDef(0); // determine the first key (is an autoinc one...)
  if (k0->Attribute & CLKD_AUTOINC) {  // there is an autoinc key
    LPVARDEF vdauto = td->GetVarDef (k0->VarID);  // determine the autoinc attribute

    long MaxVal;
    BOOL doCreate = FALSE;
    LongString s;
    seqcheck *max = new seqcheck();
    s = s + "SELECT MAX(" + vdauto->GetName() + ") FROM " + 
            ORAGetTableName (td,TRUE);
    int retcode = max->execute (s.Ptr(), td); // get the next valid sequence number
    if (retcode == CS_SUCCEED   ||
        retcode == CS_LAST_DATA || // >>> FL 07.03.96 : data got successfully, too
        retcode == CS_END_DATA) { // fill the autoinc field and add the field to the statement
      MaxVal = max->lastseqnum();
      }
    else
      MaxVal = 1L;
    delete max;

    s.Clear ();
    seqcheck *seq = new seqcheck();
    s = s + "SELECT " + GetSequenceName(td)
            + ".NEXTVAL FROM DUAL";

    BOOL IsSet = IgnoreOracleError (2289,TRUE);
    retcode = seq->execute (s.Ptr(), td); // get the next valid sequence number
    if (!IsSet) IgnoreOracleError (2289,FALSE);
    if (retcode == CS_SUCCEED   ||
        retcode == CS_LAST_DATA || // >>> FL 07.03.96 : data got successfully, too
        retcode == CS_END_DATA) { // fill the autoinc field and add the field to the statement
      long seqnum = seq->lastseqnum();
      if (seqnum <= MaxVal)
        doCreate = TRUE;
      else
        doCreate = FALSE;
      }
    else {
      doCreate = TRUE;
      }
    delete seq;

    if (doCreate) {
      s.Clear ();
      sybstmt *h = new sybstmt ();
      s = s + "DROP SEQUENCE " + GetSequenceName(td) ;
      BOOL IsSet = IgnoreOracleError (2289,TRUE);
      h->execute (s.Ptr(),NULL);
      if (!IsSet) IgnoreOracleError (2289,FALSE);
      s.Clear ();
      char Nr[32];
      wsprintf (Nr,"%ld",MaxVal + 1L);
      s = s + "CREATE SEQUENCE " + GetSequenceName(td) +
              " INCREMENT BY 1" + 
              " START WITH " + Nr + 
              " NOCYCLE";
      h->execute (s.Ptr(),NULL);
      delete h;
      UserOrb(GetSequenceName(td));
      }
    LPSTR SynSeq = GetSequenceName (td);
    DoSynonym (SynSeq,SynSeq,"SELECT");
    }
  }

BOOL sybase::TestTableDef (LPTABLEDEF td)
  {
  static char TCheck[32];
  if (td->GetTableProperty ("ORACLE_Check",TCheck,sizeof(TCheck)) > 0) {
    if (lstrcmp(TCheck,"no") == 0) return TRUE;
    if ((lstrcmp(TCheck,"Orbis") == 0) && IsOrbis()) return TRUE;
    }

  // Grrmtjfx !!!!
  // ResetDscList ();

  colcheck FAR *cc = new colcheck ();
  LongString s ;
  // ### FL the type information has to be transformed later (when typcheck will be done)
  char tableName[128];
  *tableName = '\0';
  lstrcpy(tableName, ORAGetTableName(td,TRUE));
  AnsiUpper(tableName);
  s = s + "SELECT column_name, data_type FROM USER_TAB_COLUMNS WHERE table_name = '" + tableName + "'";
  cc->execute (s.Ptr(),NULL) ;
  BOOL blockedDone = FALSE ;
  BOOL res = TRUE ;
  for (int i = 0 ; ((i < td->GetAnzVars ()) && (res)) ; i++) {
    char VarName[128];
    *VarName = '\0';
    LPVARDEF v = td->GetVarDef(i);
    if (v->VarSize != 0xFFFF) {
      lstrcpy (VarName,GetAliasName (v->GetName()));
      }
    else {
      if (!blockedDone) {
        lstrcpy (VarName,BlockVarName()) ;
        }
      blockedDone = TRUE ;
      }
    if (*VarName) {
      AnsiUpper (VarName);
      int FAR *d = (int FAR *) cc->colhash->GetData (VarName);
      if (d == NULL) res = FALSE ;    // Datentypvergleich wird (vorerst)
                                      // keiner gemacht !!!!!!!!
      cc->colhash->DelData (VarName);     // Variable aus der Hashtabelle
                                      // entfernen, da fertig gecheckt
      }
    if (v->Property & VPROP_CASEINSENSITIVE) {
      // Da muss noch ein Feld sein fuer die Zugriffe auf Strings
      //---------------------------------------------------------
      lstrcpy (VarName,GetKeyFieldName (v->GetName()));
      if (*VarName) {
        AnsiUpper (VarName);
        int FAR *d = (int FAR *) cc->colhash->GetData (VarName);
        if (d == NULL) res = FALSE ;    // Datentypvergleich wird (vorerst)
                                        // keiner gemacht !!!!!!!!
        cc->colhash->DelData (VarName);     // Variable aus der Hashtabelle
                                        // entfernen, da fertig gecheckt
        }
      }
    }
  // Nachsehen, ob wohl nicht zuviele Elemente in der Datenbank definiert
  // sind
  if (res) res = cc->colhash->IsHashEmpty ();
  if (res)
    TestAllIndex (td);

  if (res) {
    s.Clear ();
    if (TriggerStatement (cc,s,td))
      res = (cc->execute (s.Ptr(),NULL) == CS_SUCCEED);
    }

  delete cc ;

  if (res)
    dbase->Testsequence (td);

  if (res) {
    LPSTR SynTab = ORAGetTableName (td,TRUE);
    DoSynonym (SynTab,SynTab,"INSERT,UPDATE,DELETE,SELECT");
    }

  return res;
  }

void DoSynonym (LPSTR NewName,LPSTR OldName,LPSTR Rights)
  {
#ifdef UEBERLEGT
  sybstmt *h = new sybstmt ();
  if (IsOrbis()) {
    LongString s ;
    s = s + "CREATE PUBLIC SYNONYM " + NewName + " FOR " + OldName ;
    BOOL IsSet = IgnoreOracleError (955,TRUE);
    h->execute (s.Ptr(),NULL);
    if (!IsSet) IgnoreOracleError (955,FALSE);
    }
  if (Rights != NULL) {
    char buf[128];
    char def[32];
    if (IsOrbis())
      strcpy(def,"R_OU_CW");
    else
      *def = '\0';
    if (GetPrivateProfileString ("Oracle","Rights", def, buf, sizeof(buf),GetIniName()) > 0) {
      LongString s ;
      s = s + "GRANT " + Rights + " ON " + NewName + " TO " + buf ;
      h->execute (s.Ptr(),NULL);
      }
    }
  delete h;
#endif
  if (!IsOrbis()) {
    sybstmt *h = new sybstmt ();
    if (Rights != NULL) {
      char buf[128];
      char def[32];
      if (IsOrbis())
        strcpy(def,"R_OU_CW");
      else
        *def = '\0';
      if (GetPrivateProfileString ("Oracle","Rights", def, buf, sizeof(buf),GetIniName()) > 0) {
        LongString s ;
        s = s + "GRANT " + Rights + " ON " + NewName + " TO " + buf ;
        h->execute (s.Ptr(),NULL);
        }
      }
    delete h;
    }
  }

void DropSynonym (LPSTR Synonym)
  {
#ifdef UEBERLEGT
  if (IsOrbis()) {
    sybstmt *h = new sybstmt ();
    LongString s ;
    BOOL IsSet = IgnoreOracleError (1432,TRUE);
    s = s + "DROP PUBLIC SYNONYM " + Synonym ;
    h->execute (s.Ptr(),NULL);
    if (!IsSet) IgnoreOracleError (1432,FALSE);
    delete h;
    }
#endif
  }

void UserOrb (LPSTR ObjName)
  {
  if (IsOrbis()) {
    sybstmt *h = new sybstmt ();
    char objname[100];
    strcpy(objname, ObjName);
    AnsiUpper(objname);
    LongString s ;
    s = s + "BEGIN tool.user_orb ('" + objname + "'); END;";
    // BOOL IsSet = IgnoreOracleError (955,TRUE);
    h->execute (s.Ptr(),NULL);
    // if (!IsSet) IgnoreOracleError (955,FALSE);
    delete h;
    }
  }

BOOL sybase::CreateTable (LPTABLEDEF td,BOOL withIndex)
  {
  static char TCheck[32];
  if (td->GetTableProperty ("ORACLE_Check",TCheck,sizeof(TCheck)) > 0) {
    if (lstrcmp(TCheck,"no") == 0) return TRUE;
    if ((lstrcmp(TCheck,"Orbis") == 0) && IsOrbis()) return TRUE;
    }

  sybstmt *h = new sybstmt ();
  BOOL res = TRUE ;

  LongString s,c;
  s = s + "CREATE TABLE " + ORAGetTableName (td,TRUE) + "(";
  // CreateTableStatement...
  BOOL blockDone = FALSE ;
  BOOL first = TRUE ;
  for (int i = 0 ; i < td->GetAnzVars() ; i++) {
    LPVARDEF v = td->GetVarDef(i);
    if (v->VarSize != 0xFFFF) {
      if (!first)
        s = s + "," ;
      BOOL doSize;
      s = s + GetAliasName(v->GetName()) + " " + GetTypeName (v,i,&doSize,td->GetKeyDef(0));
      if (doSize) {
        int size = v->VarSize;
        s = s + "(" + size + ")" ;
        }
      if ((v->Property & VPROP_NOTNULL) != 0) {
        s = s + " NOT NULL" ;
        }
      if (v->Property & VPROP_CASEINSENSITIVE) {
        s = s + "," ;
        s = s + GetKeyFieldName(v->GetName()) + " " + GetTypeName (v,i,&doSize,td->GetKeyDef(0));
        if (doSize) {
          int size = v->VarSize;
          s = s + "(" + size + ")" ;
          }
        if ((v->Property & VPROP_NOTNULL) != 0) {
          s = s + " NOT NULL" ;
          }
        }
      }
    else {
      if (!blockDone) {
        if (!first)
          s = s + "," ;
        s = s + BlockVarName() + " " + BlockTypeName();
        blockDone = TRUE ;
        }
      }
    first = FALSE ;
    }

  // Table - Constraints UNIQUE (column1, column2)
  WORD        lastKeyNr = 0xFFFF;
  int         addConstraint = FALSE;
 
#ifdef WITH_UNIQUECONSTRAINT
  LPCLKEYDEF  k1;
  for (i = 0; ((i < td->GetAnzKeySegs()) && (withIndex)) ; i++) {
    k1 = td->GetKeyDef(i);  // key i does exist !
    if (k1 != NULL) { // just to be sure (we do not know the td structure
 
      if ( (k1->KeyNmbr != lastKeyNr) ) {   // Beginning of a new key
        if (addConstraint) {  // close last Constraint, if any
          s = s + ")";
          } // if
        addConstraint = ((k1->Attribute & CLKD_UNIQUE) != 0);
        if (addConstraint) {  // open next constraint, if any
          LPVARDEF v = td->GetVarDef (k1->VarID);
          s = s + ", UNIQUE ( " ;
          if (v->Property & VPROP_CASEINSENSITIVE)
            s = s + GetKeyFieldName(v->GetName()) ;
          else
            s = s + GetAliasName(v->GetName()) ;
          } // if
        lastKeyNr = k1->KeyNmbr;
        } // if
      else {
        if (addConstraint) {  // add column to constraint, if a constraint is opened
          LPVARDEF v = td->GetVarDef (k1->VarID);
          s = s + "," ;
          if (v->Property & VPROP_CASEINSENSITIVE)
            s = s + GetKeyFieldName(v->GetName()) ;
          else
            s = s + GetAliasName(v->GetName()) ;
          } // if
        } // else if

      } // if k1 != NULL
    } // for
#endif
 
  if (addConstraint) {  // there is one opened constraint left
    s = s + ")";        // close it
    } // if
 
  s = s + ")" ;
  if (h->execute (s.Ptr(),NULL) != CS_SUCCEED) res = FALSE ;
  LPSTR SynTab = ORAGetTableName (td,TRUE);
  DoSynonym (SynTab,SynTab,"INSERT,UPDATE,DELETE,SELECT");

  if ((res) && (withIndex)) {
    // CreateIndexStatements...
    WORD oldKeyNr = 0xFFFF;
    BOOL keyIsUnique = FALSE;      // only keys which are no unique keys are created hereby
    first = TRUE ;
    for (i = 0 ; ; i++) {
      LPCLKEYDEF k = (i < td->GetAnzKeySegs()) ? td->GetKeyDef (i) : NULL ;
      if ((k == NULL) || (k->KeyNmbr != oldKeyNr)) {
        if (!first) {
#ifdef WITH_UNIQUECONSTRAINT
          if (!keyIsUnique) {
#endif
            c = c + ")" ;
            if (h->execute (c.Ptr(),NULL) != CS_SUCCEED) {
              res = FALSE ;
              break ;
              }
#ifdef WITH_UNIQUECONSTRAINT
            } // if
#endif
          }
        if (k != NULL) {
          keyIsUnique = (k->Attribute & CLKD_UNIQUE) != 0;
#ifdef WITH_UNIQUECONSTRAINT
          if (!keyIsUnique) { // unique indices are already created in the create table statement
#endif
            // >> FL 27.02.96: prepare unique Indexname
            char str[cMAX_VARNAMESIZE+1];
            lstrncpy(str, k->name, cMAX_VARNAMESIZE);
            str[cMAX_VARNAMESIZE] = 0;
            strncat(str, ORAGetTableName(td,FALSE), cMAX_VARNAMESIZE - lstrlen(str));
            str[cMAX_VARNAMESIZE] = 0;

            // create the index
            c.Clear ();
            LPVARDEF v = td->GetVarDef (k->VarID);
            c = c + "CREATE " ;
            if (keyIsUnique)
              c = c + "UNIQUE " ;
            c = c + "INDEX \"" + str + "\" ON " + ORAGetTableName(td,TRUE) + "(" ;
            if (v->Property & VPROP_CASEINSENSITIVE)
              c = c + GetKeyFieldName(v->GetName()) ;
            else
              c = c + GetAliasName(v->GetName()) ;
            oldKeyNr = k->KeyNmbr;
            // << FL 27.02.96: prepare unique Indexname
#ifdef WITH_UNIQUECONSTRAINT
            } // if
#endif
          }
        else
          break ;
        }
      else {
        LPVARDEF v = td->GetVarDef (k->VarID);
        c = c + "," ;
        if (v->Property & VPROP_CASEINSENSITIVE)
          c = c + GetKeyFieldName(v->GetName()) ;
        else
          c = c + GetAliasName(v->GetName()) ;
        }
      first = FALSE ;
      }
 
    // ### FL Hier muss noch die Sequenz erstellt werden, sofern eine oder mehrere Sequenznummern
    // ### FL pro Tabelle erstellt werden müssen.
    c.Clear();
    if (withIndex) {
      // Waehrend der ALTER Tables muss keine Sequence erzeugt werden !!!
      c = c + "CREATE SEQUENCE " + GetSequenceName(td) +
              " INCREMENT BY 1" +
              " START WITH 1" +
              " NOCYCLE";
      h->execute (c.Ptr(),NULL);
      LPSTR SynSeq = GetSequenceName (td);
      DoSynonym (SynSeq,SynSeq,"SELECT");
      UserOrb(SynSeq);
      }
    }
  if (res) {
    s.Clear ();
    if (TriggerStatement (h,s,td))
      res = (h->execute (s.Ptr(),NULL) == CS_SUCCEED);
    }

  UserOrb(SynTab);

  s.Clear ();

  delete h;

  char tablename[100];             // >> FL 22.02.96
  strcpy(tablename, ORAGetTableName(td,TRUE));// >> FL 22.02.96
  AnsiUpper(tablename);            // >> FL 22.02.96
  TableData di;
  di.IsTested = TRUE ;
  TableHash->DelData (tablename);
  TableHash->SetData (tablename,&di,sizeof(di));

  return res ;
  }

void DelFromTableHash(LPTABLEDEF td)
  {
  char tablename[100];
  strcpy(tablename, ORAGetTableName(td,TRUE));
  AnsiUpper(tablename);
  TableData di;
  di.IsTested = FALSE ;
  dbase->TableHash->DelData (tablename);
  dbase->TableHash->SetData (tablename,&di,sizeof(di));
  }
static BOOL InCreate;
BOOL sybase::TestTable (LPTABLEDEF td)
  {
  if (!TablesFetched) return TRUE ;
  BOOL res = TRUE ;
  char tablename[100];             // >> FL 22.02.96
  strcpy(tablename, ORAGetTableName(td,TRUE));// >> FL 22.02.96
  AnsiUpper(tablename);            // >> FL 22.02.96
  TableData FAR *d = (TableData FAR *) TableHash->GetData (tablename);// >> FL 22.02.96
 
  if (d != NULL) {
    if (!d->IsTested) {
      if (!TestTableDef (td)) {
        char outtxt[256];
        sprintf (outtxt,"Tabelle %s stimmt nicht mit der Clientdefinition überein!",ORAGetTableName (td,FALSE));
        if (!InAlter ()) // Im Alterzweig wird die Fehlermeldung anders ausgegeben
          WIN_ASSERT_TEXT(FALSE,outtxt);
        res = FALSE ;
        }
      d->IsTested = TRUE ;
      }
    }
  else {
    // Die Tabelle gibts noch nicht -> Vater informieren
    static char TCheck[32];
    if (td->GetTableProperty ("ORACLE_Check",TCheck,sizeof(TCheck)) > 0) {
      if (lstrcmp(TCheck,"no") == 0) return TRUE;
      if ((lstrcmp(TCheck,"Orbis") == 0) && IsOrbis()) return TRUE;
      }
    char outtxt[256];
    sprintf (outtxt,"Tabelle %s nicht definiert! Continue zum Erstellen der Tabelle",ORAGetTableName (td,FALSE));
#ifndef SUPPRESS_REDSCREEN_FORCREATE
    if ((!InAlter ()) && (!InCreate))
      WIN_ASSERT_TEXT(FALSE,outtxt);
#endif
      CreateTable (td);
    }
  return res ;
  }

/*--------< Verwaltung eines Statements >---------*/
static char *UserName   = "dds@clinicum";
static char *PassWord   = "dds";
static char *AppName    = "SW - CLINICUM";

BOOL CheckFile (LPSYBSTMT stmt,BOOL first,BOOL forUpdate)
  {
  BOOL res = TRUE ;
  if (dbase == NULL)
    // Login to sybase
    dbase = new sybase (UserName,PassWord,AppName,forUpdate);
  if ((first) && (stmt != NULL)) {
    for (int i = 0 ; i < int(stmt->req->AnzTables) ; i++) {
      if (stmt->req->TableDef[i] != NULL)
        res = dbase->TestTable (stmt->req->TableDef[i]);
      }
    }
  return res;
  }

void CloseAllDataFiles ()
  {
  WIN_ASSERT (AnzOpenStatements == 0);
  if (dbase != NULL)
    delete dbase ;
  }

int sybstmt::StandardDelete ()
  {
  LongString s,w;
  LPTABLEDEF td = req->TableDef[0];

  LPSTR seq = w.AnalyseSeq (this,req->SelectionName,TRUE,td,req,FALSE,FALSE,NULL,TRUE) ;
  s = s + "DELETE FROM " + ORAGetTableName (td,TRUE) ;
  if ((seq != NULL) && (*seq))
    s = s + " WHERE " + seq ;

  CS_RETCODE ret = execute (s.Ptr(),td);

  return (ret == CS_SUCCEED) ? DBCALL_SUCCESS : DBCALL_ERROR ;
  }

#pragma optimize("", off)
BOOL HoldCaseInsensitives(LPTABLEDEF td)
  {
  for (int i = 0 ; i < td->GetAnzVars() ; i++) {
    if (td->GetVarDef(i)->Property & VPROP_CASEINSENSITIVE) return TRUE ;
    }
  return FALSE ;
  }

void sybstmt::SelectStatement (LPTABLEDEF ti,LongString FAR &s,int KeyNmbr,LPSTR hint)
  {
  if (req->AnzElems > 0) {
    // Auf jeden Fall mit alias Namen fuer Tabellen arbeiten
    s = s + "SELECT " ;
    if (!NoOrderedHint) s = s + "/*+ ORDERED */ ";
    if (hint != NULL) s = s + hint ;
    BOOL BlockedDone[CB_TABLEDEF];
    lmemset (BlockedDone,'\0',sizeof(BlockedDone));
    for (int i = 0 ; i < req->AnzElems ; i++) {
      int tnr = req->elem[i].TableNumber ;
      LPVARDEF v = req->TableDef[req->elem[i].TableNumber]->GetVarDef(req->elem[i].VarID);
      if (i > 0) s = s + "," ;
      if (v->VarSize != 0xFFFF) {
        s = s + "t" + tnr + "." + GetAliasName(v->GetName());
        }
      else {
        if (!BlockedDone[tnr]) {
          s = s + "t" + tnr + "." +
                BlockVarName ();
          BlockedDone[tnr] = TRUE ;
          }
        }
      }
    s = s + " FROM " ;
    for (i = 0 ; i < int (req->AnzTables) ; i++) {
      if (i > 0) {
        s = s + "," ;
        }
      s = s + ORAGetTableName (req->TableDef[i],TRUE) + " t" + i;
      if (KeyNmbr >= 0) {                       // ### FL noch unklar, wie Oracle diesen Hinweis verarbeiten soll
        WIN_ASSERT_TEXT (FALSE, "SelectStatement: KeyNmbr is not NULL !");
        } // if
      }
    }
  else {
    WIN_ASSERT (req->AnzTables == 1);
    s = s + "SELECT " ;
    BOOL blockedDone = FALSE ;
    for (int i = 0 ; i < req->TableDef[0]->GetAnzVars() ; i++) {
      LPVARDEF v = req->TableDef[0]->GetVarDef(i);
      if (v->VarID == 0xFFFF) {
        if (i > 0) s = s + ",t0." ;
        else s = s + "t0." ;
        s = s + GetAliasName (v->GetName()) ;
        }
      else {
        if (!blockedDone) {
          if (i > 0)
            s = s + ",t0." ;
          s = s + BlockVarName () ;
          }
        blockedDone = TRUE ;
        }
      }
    s = s + " FROM " ;

    for (i = 0 ; i < int (req->AnzTables) ; i++) {
      if (i > 0) {
        s = s + "," ;
        }
      s = s + ORAGetTableName (req->TableDef[i],TRUE) + " t" +  i;
      if (KeyNmbr >= 0)
        s = s + "(" + KeyNmbr + ")" ;           // ### FL noch unklar, ob Oracle dies verkraftet
      }
    }
  }

void sybstmt::WhereStatement (LongString FAR &s,LPTABLEDEF td,LPTABLEDEF ti,BOOL FAR &wheredone,BOOL useOld)
  {
  wheredone = FALSE ;
  LongString w;
  // LPSTR seq = w.AnalyseSeq (req->SelectionName,TRUE,td,req,TRUE,useOld,this,TRUE);
  LPSTR seq = w.AnalyseSeq (this,req->SelectionName,TRUE,ti,req,TRUE,useOld,this,TRUE,0,NULL,-1);
  int offs = int (s.size());
  LPSTR JoinSel[CB_TABLEDEF];
  for (int i = 0 ; i < CB_TABLEDEF ; i++)
    JoinSel[i] = NULL ;
  if ((seq != NULL) && (*seq)) {
    s = s + " WHERE (" + seq + ")" ;
    wheredone = TRUE ;
    }
  // Noch die Joins dazu
  BOOL UseOuter[CB_TABLEDEF] ;
  for (i = 0 ; i < CB_TABLEDEF ; i++)
    UseOuter[i] = FALSE ;
  for (i = 1 ; i < int (req->AnzTables) ; i++) {
    LongString js;
    if (wheredone)
      s = s + " AND (" ;
    else
      s = s + " WHERE (" ;
    LPCLRIDEF r = ti->GetRIDef(i-1) ;
    switch (r->TypeOfJoin) {
      case CLJT_USEDEFAULT :
        UseOuter[i] = IsNullAllowed(req,ti,ti->GetRIDef(i-1));
        break ;
      case CLJT_USEINNERJOIN :
        UseOuter[i] = FALSE ;
        break ;
      case CLJT_USEOUTERJOIN :
        UseOuter[i] = TRUE ;
        break ;
      default :
        WIN_ASSERT (FALSE) ;
      }
    s = s + js.AnalyseJoin (req,ti,i,r,JoinSel,UseOuter,useOld,this,TRUE) + ")";
    wheredone = TRUE ;
    }
  for (i = 0 ; i < CB_TABLEDEF ; i++)
    if (JoinSel[i] != NULL) FreeGlobMem (JoinSel[i]) ;
  }

void sybstmt::OrderStatement (LongString FAR &s,LPTABLEDEF td,WORD Op,BOOL UsePrimary)
  {
  LongString o;
  LPSTR os ;
  char PrimKeyOrder[256];
  BOOL descending = ((Op == DBOP_GETPREV) || (Op == DBOP_GETLAST)) ;
  if ((req->OrderStatement == NULL) || (*req->OrderStatement == '\0')) {
    if (UsePrimary) {
      *PrimKeyOrder = '\0' ;
      WORD KeySeg[MAX_PRIMARYSEGS] ;
      WIN_ASSERT(req->TableDef[0]->GetPrimKeySegs (KeySeg));
      for (int i = 0 ; i < MAX_PRIMARYSEGS ; i ++) {
        if (KeySeg[i] == 0xFFFF) break ;
        if (*PrimKeyOrder) lstrcat (PrimKeyOrder,",");
        lstrcat (PrimKeyOrder,req->TableDef[0]->GetVarDef(KeySeg[i])->GetName());
        }
      os = PrimKeyOrder;
      }
    else {
      WIN_ASSERT ((Op != DBOP_GETPREV) && (Op != DBOP_GETPREV)) ;
      os = NULL ;
      }
    }
  else
    os = req->OrderStatement ;
  if (os != NULL) {
    LPSTR order = o.AnalyseSeq (NULL,os,FALSE,td,req,TRUE,FALSE,NULL,TRUE,0,NULL,-1);
    LongString r;
    if (descending) {
      order = r.InsertDescending (order);
      }
    if ((order != NULL) && (*order))
      s = s + " ORDER BY " + order ;
    }
  }

/************************************************************************
  sybstmt::RowcountStatement

  purpose:  Adds the ROWNUM - condition to the where clause. Oracle evaluates
            the value of the ROWNUM Attribut before the ordering is done. So,
            we have to ensure, that the ROWNUM - condition is only added, if
            we can guarantee oracle uses an appropriate index (along the ordering).
  input:    w         contains the actual where - statement
            req       contains the clinicum request
            rowcnt    contains the number of rows to be retrieved
            whereDone Indicates whether the WHERE clasue is already included
  output:   w         the where statement contains the ROWNUM condition now
  return:   --
*************************************************************************/
void sybstmt::RowcountStatement (LongString FAR &w,LPDBREQUEST req,int rowcnt, BOOL &whereDone)
  {

    if ( (req->AnzTables == 1) ||           // only simple ordering for the moment
         (req->OrderStatement == NULL) ||   // or if no order statement is defined
         (*req->OrderStatement == '\0') ) {
      if (!whereDone) {
        w = w + " WHERE ";
        whereDone = TRUE;
        } // if
      else {
        w = w + " AND ";
        } // if else
      w = w + "(ROWNUM <= " + rowcnt + ") ";
      }
  } // sybstmt::RowcountStatement
 
void sybstmt::SyncStatement (LongString FAR &w,LPDBREQUEST req,LPTABLEDEF td,LPSTR c,LPSTR ce,BOOL whereDone)
  {
  LongString o;
  LPSTR os ;
  char PrimKeyOrder[256];
  if ((req->OrderStatement == NULL) || (*req->OrderStatement == '\0')) {
    *PrimKeyOrder = '\0' ;
    WORD KeySeg[MAX_PRIMARYSEGS] ;
    WIN_ASSERT(req->TableDef[0]->GetPrimKeySegs (KeySeg));
    for (int i = 0 ; i < MAX_PRIMARYSEGS ; i ++) {
      if (KeySeg[i] == 0xFFFF) break ;
      if (*PrimKeyOrder) lstrcat (PrimKeyOrder,",");
      lstrcat (PrimKeyOrder,req->TableDef[0]->GetVarDef(KeySeg[i])->GetName());
      }
    os = PrimKeyOrder;
    }
  else
    os = req->OrderStatement ;
  // int AnzJoinSegs,LPSTR JoinName[],int tnum,BOOL UseOuter
  LPSTR sync = o.AnalyseSeq (NULL,os,TRUE,td,req,TRUE,FALSE,NULL,TRUE,0,NULL,-1,FALSE);

  LongString r;
  BOOL doAnd = whereDone ;
  if (!whereDone)
    w = w + " WHERE " ;
  sync = r.InsertSyncCond (sync,req,c,ce,doAnd);

  if ((sync != NULL) && (*sync))
    w = w + sync ;
  }
#pragma optimize("", on)

#if defined(ORACLE_SHOWRESULTS)

/************************************************************************
  ShowResult

  purpose:  Displayes the result of a query
  input:    v           describes the structure and type of the column
            data        points to the buffer, into which the data will be written
            Size        contains the size of the data - buffer
  output:   --
  return:   --
*************************************************************************/
void sybstmt::ShowResult (LPVARDEF v,LPVOID data,int Size)
  {
  char str[1000];
  switch (v->mType) {
    case VAR_DATE : {
      sprintf(str, "\t%-8.8s", (char*)data);
      break ;
      }
    case VAR_TIME : {
      sprintf(str, "\t%-6.6s", &(((char*)data)[8]));
      break ;
      }
    case VAR_DATETIME : {
      sprintf(str, "\t%-16.16s", (char*)data);
      break ;
      }
    case VAR_LONG   :
    case VAR_DWORD  :
    case VAR_STRARR :
    case VAR_FLAG   :
      if (Size == 1) sprintf(str, "\t%hd", *(short*)data);
      if (Size == 2) sprintf(str, "\t%d", *(int*)data);
      if (Size == 4) sprintf(str, "\t%ld", *(long*)data);
      break ;
    case VAR_DEC    :
      sprintf(str, "\t%f", *(double*)data);
      break ;
    case VAR_STR    :
      if (Size > 900) {
        sprintf(str, "\t%.900s...", (char*)data);
        }
      else
        sprintf(str, "\t%s", (char*)data);
      break ;
    case VAR_POINT  :
    case VAR_CONT   :
    case VAR_SCALE  :
    case VAR_OBJ    :
      if (Size > 254)
        sprintf(str, "\t%254.254x..", (unsigned char*)data);
      else
        sprintf(str, "\t%*.*x..", (int)Size, (int)Size, (unsigned char*)data);
      break ;
    default :
      sprintf(str, "\t");
      break ;
      } // switch
    DBG_ASSERT_TEXT(FALSE, "RESULT", (char *)str);
  } // sybstmt::ShowResult
#endif // ORACLE_SHOWRESULTS
 
/************************************************************************
  ConvertToMData

  purpose:  Converts the Values returned by the select statement into the
            appropriate Clinicum data structures. This method should be called
            for every column.
  input:    v           describes the structure and type of the column
            data        points to the buffer, into which the data will be written
            Size        contains the size of the data - buffer
  output:   rSize       contains the effective size in bytes of the buffer
                        pointed by the return - pointer.
  return:   a Pointer to the RecBuffer 'res', which contains the fields
            'year', 'month' and 'day'.
*************************************************************************/
LPVOID sybstmt::ConvertToMData (LPVARDEF v,LPVOID data,int Size,int FAR *rSize)
  {
#if defined(ORACLE_SHOWRESULTS)
  ShowResult(v, data, Size);
#endif // ORACLE_SHOWRESULTS
  switch (v->mType) {
    case VAR_DATE : {
      static packdate res;
      char str[5];
      char *datastr = (char *)data;
      strncpy(str, (const char*)&datastr[0], 2);   str[2] = (char)0;
      res.day = BYTE(atoi(str));
      strncpy(str, (const char*)&datastr[2], 2);   str[2] = (char)0;
      res.month = BYTE(atoi(str));
      strncpy(str, (const char*)&datastr[4], 4);   str[4] = (char)0;
      res.year = WORD(atoi(str)) ;
      *rSize = sizeof(res);
      return &res ;
      break ;
      }
    case VAR_TIME : {
      static packtime res;
      char str[3];
      char *datastr = (char *)data;
      strncpy(str, (const char*)&datastr[8], 2);  str[2] = (char)0;
      res.hour = BYTE(atoi(str)) ;
      strncpy(str, (const char*)&datastr[10], 2); str[2] = (char)0;
      res.minute = BYTE(atoi(str)) ;
      strncpy(str, (const char*)&datastr[12], 2); str[2] = (char)0;
      res.second = BYTE(atoi(str)) ;
      res.hundred_second = 0 ;
      *rSize = sizeof(res);
      return &res;
      break ;
      }
    case VAR_DATETIME : {
      static packdatetime res;
      char str[5];
      char *datastr = (char *)data;
      strncpy(str, (const char*)&datastr[0], 2);   str[2] = (char)0;
      res.pd.day = BYTE(atoi(str));
      strncpy(str, (const char*)&datastr[2], 2);   str[2] = (char)0;
      res.pd.month = BYTE(atoi(str));
      strncpy(str, (const char*)&datastr[4], 4);   str[4] = (char)0;
      res.pd.year = WORD(atoi(str)) ;
      datastr = (char *)data;
      strncpy(str, (const char*)&datastr[8], 2);  str[2] = (char)0;
      res.pt.hour = BYTE(atoi(str)) ;
      strncpy(str, (const char*)&datastr[10], 2); str[2] = (char)0;
      res.pt.minute = BYTE(atoi(str)) ;
      strncpy(str, (const char*)&datastr[12], 2); str[2] = (char)0;
      res.pt.second = BYTE(atoi(str)) ;
      res.pt.hundred_second = 0 ;
      *rSize = sizeof(res);
      return &res;
      break ;
      }
    case VAR_STR:             // >> FL 01.03.96: Clinicum needs the length inclusive the zero value
      *rSize = int(Size + 1);
      // MF 11.5.98: Clinicum braucht nicht nur die Laenge,
      // sondern auch tatsaechlich ein 0-Byte am Ende !!!!
      ((LPSTR)data)[Size] = '\0';
      return data;
      break;                  // << FL 01.03.96: Clinicum needs the length inclusive the zero value
    case VAR_STRARR :
    case VAR_FLAG :
      *rSize = sizeof(DBINT) ;
      return data ;
      break ;
    default :
      *rSize = int(Size) ;
      return data;
      break ;
    } // switch

  return NULL ;
  } // sybstmt::ConvertToMData

LPVOID sybstmt::ConvertToMData_f (WORD mType,LPVOID data,int Size,int FAR *rSize)
  {
  switch (mType) {
    case VAR_DATE : {
      static packdate res;
      char str[5];
      char *datastr = (char *)data;
      strncpy(str, (const char*)&datastr[0], 2);   str[2] = (char)0;
      res.day = BYTE(atoi(str));
      strncpy(str, (const char*)&datastr[2], 2);   str[2] = (char)0;
      res.month = BYTE(atoi(str));
      strncpy(str, (const char*)&datastr[4], 4);   str[4] = (char)0;
      res.year = WORD(atoi(str)) ;
      *rSize = sizeof(res);
      return &res ;
      break ;
      }
    case VAR_TIME : {
      static packtime res;
      char str[3];
      char *datastr = (char *)data;
      strncpy(str, (const char*)&datastr[8], 2);  str[2] = (char)0;
      res.hour = BYTE(atoi(str)) ;
      strncpy(str, (const char*)&datastr[10], 2); str[2] = (char)0;
      res.minute = BYTE(atoi(str)) ;
      strncpy(str, (const char*)&datastr[12], 2); str[2] = (char)0;
      res.second = BYTE(atoi(str)) ;
      res.hundred_second = 0 ;
      *rSize = sizeof(res);
      return &res;
      break ;
      }
    case VAR_DATETIME : {
      static packdatetime res;
      char str[5];
      char *datastr = (char *)data;
      strncpy(str, (const char*)&datastr[0], 2);   str[2] = (char)0;
      res.pd.day = BYTE(atoi(str));
      strncpy(str, (const char*)&datastr[2], 2);   str[2] = (char)0;
      res.pd.month = BYTE(atoi(str));
      strncpy(str, (const char*)&datastr[4], 4);   str[4] = (char)0;
      res.pd.year = WORD(atoi(str)) ;
      datastr = (char *)data;
      strncpy(str, (const char*)&datastr[8], 2);  str[2] = (char)0;
      res.pt.hour = BYTE(atoi(str)) ;
      strncpy(str, (const char*)&datastr[10], 2); str[2] = (char)0;
      res.pt.minute = BYTE(atoi(str)) ;
      strncpy(str, (const char*)&datastr[12], 2); str[2] = (char)0;
      res.pt.second = BYTE(atoi(str)) ;
      res.pt.hundred_second = 0 ;
      *rSize = sizeof(res);
      return &res;
      break ;
      }
    case VAR_STR:             // >> FL 01.03.96: Clinicum needs the length inclusive the zero value
      *rSize = int(Size + 1);
      // MF 11.5.98: Clinicum braucht nicht nur die Laenge,
      // sondern auch tatsaechlich ein 0-Byte am Ende !!!!
      ((LPSTR)data)[Size] = '\0';
      return data;
      break;                  // << FL 01.03.96: Clinicum needs the length inclusive the zero value
    case VAR_STRARR :
    case VAR_FLAG :
      *rSize = sizeof(DBINT) ;
      return data ;
      break ;
    default :
      *rSize = int(Size) ;
      return data;
      break ;
    } // switch

  return NULL ;
  } // sybstmt::ConvertToMData_f

LPVOID sybstmt::FindData (LPVOID BlockData,WORD VarID,int FAR *Size)
  {
  MBlockHeader FAR *hd = (MBlockHeader FAR *) BlockData ;
  MBlockVarHeader FAR *vhd = (MBlockVarHeader FAR *) (hd + 1) ;
  for (WORD i = 0 ; i < hd->AnzVars ; i++) {
    if (vhd->VarID == VarID) {
      *Size = int (vhd->VarSize) ;
      return (vhd + 1) ;
      }
    vhd = (MBlockVarHeader FAR *) (LPSTR (vhd + 1) + vhd->VarSize);
    }
  return NULL ;
  }

void sybstmt::PushToBlocked (LPVOID Data,WORD VarID)
  {
  WORD nSize,oSize;
  if (BlockedData != NULL) {
    nSize = GetBlockSize (BlockedData) + GetBlockSize (Data) + sizeof (MBlockVarHeader) ;
    oSize = GetBlockSize (BlockedData) ;
    }
  else {
    nSize = sizeof(MBlockHeader) + GetBlockSize (Data) + sizeof (MBlockVarHeader) ;
    oSize = sizeof(MBlockHeader) ;
    }
  WIN_ASSERT (nSize <= MAXBLOCKEDSIZE);
  LPVOID nwBlockedData = GetGlobMem (nSize);
  if (BlockedData != NULL) {
    lmemcpy (nwBlockedData,BlockedData,oSize);
    FreeGlobMem (BlockedData);
    }
  MBlockHeader FAR *hd = (MBlockHeader FAR *) nwBlockedData ;
  MBlockVarHeader FAR *vhd = (MBlockVarHeader FAR *) (LPSTR (nwBlockedData) + oSize) ;
  hd->AnzVars += 1;
  hd->BlockSize = nSize;
  vhd->VarID = VarID;
  vhd->VarSize = GetBlockSize (Data);
  lmemcpy (vhd+1,Data,GetBlockSize (Data));

  BlockedData = nwBlockedData ;
  }

LPDBRECORD sybstmt::StoreRow (LPTABLEDEF ti,int row)
  {
  // Uebergabeparameter speichern
  for ( BndList FAR *h = TopDsc ; h != NULL ; h = h->Next) {
    if (h->VarInd != OCI_IND_NULL) {
      int rLen;
      LPVOID cd = ConvertToMData_f (h->Type,h->data,h->VarLen,&rLen);
      if (cd != NULL)
        req->SetOutParam (h->Num,cd,rLen);
      else
        req->SetOutParam (h->Num,NULL,0);
      }
    else
      req->SetOutParam (h->Num,NULL,0);
    }

  if ((req->AnzElems == 0) && (ti == NULL)) return NULL;
  LPDBRECORD rec = new DBRecord (req);
  LPVOID blockData = NULL ;
  int blockSize = 0;
  BOOL blockDone = FALSE ;
  if (req->AnzElems > 0) {
    // Stueck fuer Stueck aus den echten Tabellen abholen
    int j = 0 ;
    for (int i = 0 ; (i < int(req->AnzElems)) ; i++ ) {
      LPVARDEF v = req->TableDef[req->elem[i].TableNumber]->GetVarDef(req->elem[i].VarID);
      if (v->VarSize != 0xFFFF) {
        if (v->mType != VAR_BLOB) {
          LPVOID data = LPVOID (LPSTR (ColInfo[j].VarData) + row * ColInfo[j].VarFormat.maxlength) ;
          int size = int (ColInfo[j].VarLen[row]);
          if (ColInfo[j].VarInd[row] != OCI_IND_NULL) {
            int rLen;
            LPVOID cd = ConvertToMData (v,data,size,&rLen);
            if (cd != NULL)
              rec->Initialize (i,cd,rLen);
            }
  #if defined(ORACLE_SHOWRESULTS)
          else {
            char str[50];
            sprintf(str, "\tNULL");
            DBG_ASSERT_TEXT(FALSE, "RESULT", str);
            }
  #endif // ORACLE_SHOWRESULTS
          }
        j ++ ;
        }
      else {
        // Information aus dem geblockten Teil holen
        ///////////////////////////////////////////////////
        if (!blockDone) {
          blockData = LPVOID (LPSTR (ColInfo[j].VarData) + row * ColInfo[j].VarFormat.maxlength) ;
          blockSize = int (ColInfo[j].VarLen[row]);
          blockDone = TRUE ;
          j ++ ;
          }
        if (blockSize > 0) {
          int rLen;
          LPVOID d_int = FindData (blockData,v->VarID,&rLen);
          if (d_int != NULL)
            rec->Initialize (i,d_int,rLen);
          }
        }
      }
    }
  else {
    // Speichern einer vollen Tabelle
    //--------------------------------------------------------
    int j = 0 ;
    for (int i = 0 ; (i < ti->GetAnzVars()) ; i++) {
      LPVARDEF v = ti->GetVarDef(i);
      if (v->mType != VAR_BLOB) {
        if (v->VarSize != 0xFFFF) {
          LPVOID data = LPVOID (LPSTR (ColInfo[j].VarData) + row * ColInfo[i].VarFormat.maxlength) ;
          int size = int (ColInfo[j].VarLen[row]);
          if (ColInfo[j].VarInd[row] != OCI_IND_NULL) {
            int rLen;
            LPVOID cd = ConvertToMData (v,data,size,&rLen);
            if (cd != NULL)
              rec->Initialize (i,cd,rLen);
            }
#if defined(ORACLE_SHOWRESULTS)
          else {
            char str[50];
            sprintf(str, "\tNULL");
            DBG_ASSERT_TEXT(FALSE, "RESULT", str);
            }
#endif // ORACLE_SHOWRESULTS
          j ++ ;
          }
        else {
          // Information aus dem geblockten Teil holen
          ///////////////////////////////////////////////////
          if (!blockDone) {
            blockData = LPVOID (LPSTR (ColInfo[j].VarData) + row * ColInfo[nCols(ti)-1].VarFormat.maxlength) ;
            blockSize = int (ColInfo[j].VarLen[row]);
            blockDone = TRUE ;
            j++ ;
            }
          if (blockSize > 0) {
            int rLen;
            LPVOID d_int = FindData (blockData,v->VarID,&rLen);
            if (d_int != NULL)
              rec->Initialize (i,d_int,rLen);
            }
          }
        }
      else
        j ++ ;    // case VAR_BLOB
      }
    }
#if defined(ORACLE_SHOWRESULTS)
  DBG_ASSERT_TEXT(FALSE, "RESULT END", "");
#endif // ORACLE_SHOWRESULTS
  PrimKey k;
  rec->CalcPrimKey (0,&k);
  rec->SetPrimKey (&k);

  return rec;
  }

BOOL sybstmt::StoreData (LPTABLEDEF ti,int row)
  {
  LPDBRECORD r = StoreRow (ti,row);
  if (r != NULL) {
    res->AddLine (1,((Op == DBOP_GETNEXT) || (Op == DBOP_GETFIRST)) ? ADDLINEPOS_END : ADDLINEPOS_START);
    res->SetRes (0,r);
    }
  return TRUE ;
  }

void liststmt::GetColInfo(LPTABLEDEF ti)
  {
  if ((Op == DBOP_GETNEXT) || (Op == DBOP_GETPREV)) {
    kLast.SetKeyNull();
    kLast.PushKeySeg (req->Param[0],GetBlockSize(req->Param[0]));
    }
  sybstmt::GetColInfo (ti);
  }

BOOL liststmt::StoreData (LPTABLEDEF ti,int row)
  {
  LPDBRECORD rec = StoreRow (ti,row);
  if (rec == NULL) return TRUE ;
  if ((Op == DBOP_GETNEXT) || (Op == DBOP_GETPREV)) {
    if (!doNext) {
      doNext = (kLast == *rec->GetPrimKey ());
      }
    }
  else
    doIt = TRUE ;
  BOOL done ;
  if (doIt) {
    res->AddLine (1,((Op == DBOP_GETNEXT) || (Op == DBOP_GETFIRST)) ? ADDLINEPOS_END : ADDLINEPOS_START);
    res->SetRes (0,rec);
    done = TRUE ;
    }
  else {
    delete rec ;
    done = FALSE ;
    }
  doIt = doIt || doNext ;
  return done ;
  }

BOOL insstmt::StoreData (LPTABLEDEF ti,int row)
  {
  return TRUE ;
  }

void insstmt::GetColInfo(LPTABLEDEF t0)
  {
  LPVARDEF v;
  LPTABLEDEF ti = GetTableAdmin()->GetTableDef (req->GetTableID(),req->GetVersion());
  if (ti == req->TableDef[0]) {
    va = k0->VarID;
    v = ti->GetVarDef (va);
    }
  else {
    for (int i = 0 ; i < ti->GetAnzVars() ; i++) {
      ReqElem e;
      ti->GetReqElem (&e,i);
      if (e.VarID == k0->VarID) {
        va = i ;
        v = req->TableDef[req->elem[i].TableNumber]->GetVarDef(req->elem[i].VarID);
        break ;
        }
      }
    }
  if (ColInfo == NULL) {
    blobCol = -1;
    dbCols = 1;
    ColInfo = (_COLINFO FAR *) GetGlobMem (sizeof(*ColInfo));
    ColInfo[0].VarLen    = (VARLEN_TYPE FAR *) GetGlobMem (sizeof(*ColInfo[0].VarLen) * nRows(t0)) ;
    ColInfo[0].VarRetCode = (VARRETCODE_TYPE FAR *) GetGlobMem (sizeof(*ColInfo[0].VarRetCode) * nRows(t0)) ;
    ColInfo[0].VarInd     = (VARIND_TYPE FAR *) GetGlobMem (sizeof(*ColInfo[0].VarInd) * nRows(t0)) ;
    ColInfo[0].VarData   = GetSybDataType (&ColInfo[0].VarFormat,v->mType,v->VarSize,nRows(t0));
    }
  GetTableAdmin()->FreeTable (req->GetTableID(),req->GetVersion());
  }

int sybstmt::StandardGet ()
  {
  LongString s;
  LPTABLEDEF ti = GetTableAdmin()->GetTableDef (req->GetTableID(),req->GetVersion());

  SelectStatement (ti,s);
  BOOL wheredone;
  WhereStatement (s,req->TableDef[0],ti,wheredone);

  RecsToGet = 1 ;
  CS_RETCODE retcode = execute (s.Ptr(),ti);

  GetTableAdmin()->FreeTable (req->GetTableID(),req->GetVersion());
  if ((retcode == CS_SUCCEED) || (retcode == CS_LAST_DATA))  // >>> FL 07.03.96 after retrieving rows, this indicates
    return DBCALL_SUCCESS ;                                  // >>>             successfully read until end of data
  else if (retcode == CS_END_DATA)
    return DBCALL_NODATA ;
  else
    return DBCALL_ERROR ;
  }

int sybstmt::StandardInsert ()
  {
  // ResetDscList ();

  LongString s,v;
  s = s + "INSERT INTO " + ORAGetTableName (req->TableDef[0],TRUE) + " (" ;
  v = v + ") VALUES (" ;
  int correct = TRUE ;
  int AnzPars = 0;
  LPTABLEDEF ti = req->TableDef[0] ;

  // generate auto values (use oracle's sequences)
  int     OverwriteVarNr = 0;
  k0 = req->TableDef[0]->GetKeyDef(0); // determine the first key (is an autoinc one...)
  if (k0->Attribute & CLKD_AUTOINC) {  // there is an autoinc key
    LPVARDEF vdauto = req->TableDef[0]->GetVarDef (k0->VarID);  // determine the autoinc attribute
    if (! CheckOverwriteSequence(vdauto, &OverwriteVarNr) ) { // insert a new value (EnlargeInsert could be adapted?)
      correct = EnlargeInsertWithSequence (OverwriteVarNr, vdauto,s,v,&AnzPars);
      } // if
    else { // do overwrite attribut with the users value and adapt oracle's sequence number
      if (!InAlter ())
        SynchronizeSequence(vdauto, OverwriteVarNr);
      } // else if
    } // if

  LPBLOBDESC bdsc = NULL ;
  if (req->AnzElems > 0) {
    for (int i = 0 ; ((i < int(req->AnzElems)) && (correct)) ; i++) {
      if (req->elem[i].TableNumber == 0) {
        LPVARDEF vd = req->TableDef[0]->GetVarDef (req->elem[i].VarID);
        correct = EnlargeInsert (vd,i,s,v,&AnzPars,&bdsc);
        }
      }
    }
  else {
    for (int i = 0 ; ((i < ti->GetAnzVars()) && (correct)) ; i++) {
      LPVARDEF vd = ti->GetVarDef (i);
      correct = EnlargeInsert (vd,i,s,v,&AnzPars,&bdsc);
      }
    }
  correct = EnlargeInsert_Blocked (s,v,&AnzPars);
  s = s + LPSTR(v.Ptr()) + ")";

  CS_RETCODE retcode = execute (s.Ptr(),ti,NULL,bdsc);

  old = res->first->rec[0];
  RecBufferLine FAR *n = res->first->Next;
  FreeGlobMem (res->first);
  res->first = n;
  if (retcode == CS_SUCCEED) {
    res->AddLine (1,ADDLINEPOS_END);
    res->SetRes (0,GetRecCopy (old,-1,NULL,0));
    }
  return (retcode == CS_SUCCEED) ? DBCALL_SUCCESS : DBCALL_NODATA ;
  }

/************************************************************************
  sybstmt::CheckOverwriteSequence

  purpose:  evaluates whether an autoinc attribute is part of the
            field to be inserted by the request.
  input:    vdauto          describes the auto increment attribute
  output:   OverwriteVarNr  if the attribute is part of the insert statement (return TRUE)
                            the number of the attribute is returned. This number is also
                            returned, if the attribute is part of the statement and set to NULL.
  return:   TRUE            the caller wants to set the autoinc value by himself (overwrite)
            FALSE           the autoinc value may be set automatically
*************************************************************************/
BOOL sybstmt::CheckOverwriteSequence(LPVARDEF vdauto, int *OverwriteVarNr)
  {
    BOOL OverwriteAuto = FALSE;
    LPTABLEDEF ti = req->TableDef[0] ;
    if (req->AnzElems > 0) {
      for (int i = 0 ; ((i < int(req->AnzElems))) ; i++) {
        if (req->elem[i].TableNumber == 0) {
          LPVARDEF vd = req->TableDef[0]->GetVarDef (req->elem[i].VarID);
          if (strcmp(vd->GetName(),vdauto->GetName()) == 0) {
            *OverwriteVarNr = i;
            OverwriteAuto = (res->first->rec[0]->Get(*OverwriteVarNr) != NULL);
            break;
            } // if
          } // if
        } // for
      } // if
    else {
      for (int i = 0 ; ((i < ti->GetAnzVars())) ; i++) {
        LPVARDEF vd = ti->GetVarDef (i);
        if (strcmp(vd->GetName(),vdauto->GetName()) == 0) {
          *OverwriteVarNr = i;
          OverwriteAuto = (res->first->rec[0]->Get(*OverwriteVarNr) != NULL);
          break;
          } // if
        } // for
      } // else if
    return (OverwriteAuto);
  } // sybstmt::CheckOverwriteSequence
 
/************************************************************************
  sybstmt::EnlargeInsertWithSequence

  purpose:  append the automatic sequence numbering values to the
            statement and adjusts the autoinc field for the callers values
  input:    vdauto          describes the auto increment attribute
            overWriteVarNr  indicates the variable coming from the caller
            s               the insert statement
            v               the VALUES part of the insert statement
            AnzPars         the number of parameters already part of the statement
  output:   AnzPars         the number will be incremented by one
  return:   TRUE            the enlargement has been successfully done
            FALSE           the enlargement failed
*************************************************************************/
BOOL sybstmt::EnlargeInsertWithSequence (int overwriteVarNr, LPVARDEF vdauto,LongString FAR &s,LongString FAR &v,int *AnzPars)
  {
    BOOL correct = FALSE;
    LongString mnext;
    CS_RETCODE retcode;
    LPTABLEDEF ti = req->TableDef[0] ;
 
    seqcheck *seq = new seqcheck();
    mnext = mnext + "SELECT " + GetSequenceName( req->TableDef[0])
            + ".NEXTVAL FROM DUAL";
    retcode = seq->execute (mnext.Ptr(), ti); // get the next valid sequence number
    if (retcode == CS_SUCCEED   ||
        retcode == CS_LAST_DATA || // >>> FL 07.03.96 : data got successfully, too
        retcode == CS_END_DATA) { // fill the autoinc field and add the field to the statement
      long seqnum = seq->lastseqnum();
      // ### FL Fraglich: ist dieses Set ausreichend?
      if ( vdauto->mType == VAR_STRARR) {
        short seqnums = (short) seqnum;
        res->first->rec[0]->Set(overwriteVarNr, &seqnums, sizeof(seqnums)); // ### FL is a conversion necessary for STR_ARR fields? analog to GetVarString
        }
      else {
        res->first->rec[0]->Set(overwriteVarNr, &seqnum, sizeof(seqnum)); // ### FL is a conversion necessary for STR_ARR fields? analog to GetVarString
        }
 
      correct = TRUE;
      } // if
    delete seq;
    return (correct);
  } // sybstmt::EnlargeInsertWithSequence

/************************************************************************
  sybstmt::SynchronizeSequence

  purpose:  if the autoinc attribute is set by the caller (typically when some dataimport
            is done), the sequence number has to be synchronized to ensure unique values for
            following inserts.
            This is done by reading the sequence until it reaches a value greater or equal
            to the overwritten one.
            ATTN: this must be done only by one single user at a time. The database
                  should be empty (otherwise we cannot guarantee uniqueness of the
                  autoinc values).
  input:    OverwriteVarNr  the attribute in the request containing the value
  output:   --
  return:   --
*************************************************************************/
void sybstmt::SynchronizeSequence(LPVARDEF vdauto,int OverwriteVarNr)
  {
    BOOL       doFree;
    LongString mcurr, mnext;
    CS_RETCODE retcode;

    seqcheck   *seq = new seqcheck();
    LPVOID     Data = res->first->rec[0]->Get(OverwriteVarNr);
    LPSTR      r = GetVarString(Data, vdauto->mType, &doFree, -1,TRUE,0);
    long       OverwriteVal = atol(r);
    LPTABLEDEF ti = req->TableDef[0] ;

    // prepare statement: SELECT s_tablename.CURRVALL FROM DUAL
    mcurr = mcurr + "SELECT " + GetSequenceName( req->TableDef[0])
            + ".CURRVAL FROM DUAL";
    // prepare statement: SELECT s_tablename.NEXTVAL  FROM DUAL
    mnext = mnext + "SELECT " + GetSequenceName( req->TableDef[0] )
            + ".NEXTVAL FROM DUAL";
 
    retcode = seq->execute (mcurr.Ptr(), ti); // get the current sequence number
    while ((retcode == CS_NOT_AVAIL) || (seq->lastseqnum() < OverwriteVal)) {
      retcode = seq->execute (mnext.Ptr(), ti);
      } // while
    if (doFree) FreeGlobMem(r);
    delete seq;
  } // sybstmt::SynchronizeSequence

int sybstmt::StandardList (BOOL first,BOOL doCursorClose)
  {
  // Alte Cursor wieder zumachen, wenn noetig....
  //--------------------------------------------------
  if ((cmd != NULL) && (!closeDone)) {
    oclose((Cda_Def *) cmd);
    ocirethandling(dbase->lda, cmd);
    closeDone = TRUE ;
    }

  LongString s,w;
  LPTABLEDEF ti = NULL;
  if (req->AnzTables > 0) {
    ti = GetTableAdmin()->GetTableDef (req->GetTableID(),req->GetVersion());

    BOOL wheredone;
    WhereStatement (w,req->TableDef[0],ti,wheredone,((Op == DBOP_GETNEXT) || (Op == DBOP_GETPREV)));
 
    //  RowcountStatement(w,req,nRows(ti,TRUE), wheredone);
    if ((Op == DBOP_GETNEXT) || (Op == DBOP_GETPREV)) {
      // SyncStatement (w,req,req->TableDef[0],(Op == DBOP_GETPREV) ? "<" : ">",(Op == DBOP_GETPREV) ? "<=" : ">=",wheredone) ;
      SyncStatement (w,req,ti,(Op == DBOP_GETPREV) ? "<" : ">",(Op == DBOP_GETPREV) ? "<=" : ">=",wheredone) ;
      } // if
    LPSTR hint ;
    if ((req->SelectionName != NULL) && (*req->SelectionName == '+'))
      hint = " /*+ RULE */ " ;
    else
      hint = NULL ;
    SelectStatement (ti,s,-1,hint);
    s = s + LPSTR(w.Ptr());
    // OrderStatement (s,req->TableDef[0],Op,((RecsToGet > 0) && (!req->StraightForward)));
    OrderStatement (s,ti,Op,((RecsToGet > 0) && (!req->StraightForward)));
    }
  else {
    ResetDscList ();
    s.AnalyseSeq (this,req->SelectionName,FALSE,NULL,req,FALSE,FALSE,NULL,FALSE) ;
    OrderStatement (s,NULL,Op,FALSE);
    }

  CS_RETCODE retcode = execute (s.Ptr(),ti,NULL,NULL,doCursorClose);

  GetTableAdmin()->FreeTable (req->GetTableID(),req->GetVersion());

  if (retcode == CS_SUCCEED)
    return DBCALL_SUCCESS ;
  else if ((retcode == CS_END_DATA) || (retcode == CS_LAST_DATA)) // >>> FL 07.03.96 everything gotten
    return DBCALL_ENDOFFILE ;
  else
    return DBCALL_ERROR ;
  }

#pragma optimize("", off)
BOOL sybstmt::EnlargeInsert (LPVARDEF vd,int VarNr,LongString FAR &s,LongString FAR &v,int FAR *AnzPars,LPBLOBDESC FAR *bdsc)
  {
  LPVOID Data = res->first->rec[0]->Get(VarNr);
  BOOL correct = TRUE;
  if (Data != NULL) {
    if (vd->VarSize != 0xFFFF) {
      if (*AnzPars > 0) {
        s = s + "," ;
        v = v + "," ;
        }
      s = s + GetAliasName(vd->GetName()) ;
      BOOL doFree ;
      LPSTR r ;
      if (vd->mType != VAR_BLOB)
        r = GetVarString (Data,vd->mType,&doFree,vd->VarSize,FALSE,0);
      else
        r = ":BLOB" , doFree = FALSE , *bdsc = LPBLOBDESC (Data) ;
      correct = (r != NULL) ;
      if (correct) {
        v = v + r ;
        if (doFree) FreeGlobMem (r) ;
        (*AnzPars) ++ ;
        }
      }
    else {
      PushToBlocked (Data,vd->VarID);
      }
    }
  return correct ;
  }
BOOL sybstmt::EnlargeInsert_Blocked (LongString FAR &s,LongString FAR &v,int FAR *AnzPars)
  {
  BOOL correct = TRUE;
  if (BlockedData != NULL) {
    if (*AnzPars > 0) {
      s = s + "," ;
      v = v + "," ;
      }
    s = s + BlockVarName ();
    BOOL doFree ;
    LPSTR r = GetVarString (BlockedData,VAR_OBJ,&doFree,-1,FALSE,0) ;
    correct = (r != NULL) ;
    if (correct) {
      v = v + r ;
      if (doFree) FreeGlobMem (r) ;
      (*AnzPars) ++ ;
      }
    }
  return correct ;
  }
#pragma optimize("", on)

LPDBRECORD sybstmt::GetRecCopy (LPDBRECORD old,int PrimkeyID,LPVOID PrimKeyData,int PrimKeySize)
  {
  LPTABLEDEF ti = GetTableAdmin()->GetTableDef (req->GetTableID(),req->GetVersion());
  LPDBRECORD rec = new DBRecord (req);
  for (int i = 0 ; i < int(old->GetAnzVars()) ; i++) {
    if ((i == PrimkeyID) && (PrimKeyData != NULL))
      rec->Initialize (i,PrimKeyData,PrimKeySize);
    else {
      LPVOID data = old->Get(i);
      if (data != NULL) {
        LPVARDEF v = ti->GetVarDef (i);
        if (v->mType == VAR_BLOB) {
          LPBLOBDESC b = LPBLOBDESC(data);
          BlobDesc bn = *b ;
          bn.hGmem = GlobalAlloc (GMEM_MOVEABLE,b->Size);
          hmemcpy (GlobalLock (bn.hGmem),GlobalLock (b->hGmem),b->Size);
          rec->Initialize (i,&bn,sizeof(bn));
          }
        else
          rec->Initialize (i,data,GetBlockSize(data));
        }
      }
    }
  PrimKey k;
  rec->CalcPrimKey (0,&k);
  rec->SetPrimKey (&k);

  GetTableAdmin()->FreeTable (req->GetTableID(),req->GetVersion());

  return rec;
  }

BOOL IsModifiable (LPVARDEF v,int vID,LPCLKEYDEF k0)
  {
  switch (v->mType) {
    case VAR_LONG :
    case VAR_STRARR :
      if ((k0->VarID == WORD(vID)) && (k0->Attribute & CLKD_AUTOINC)) return FALSE ;
    default :
      return TRUE ;
    }
  }
#pragma optimize("", off)
BOOL sybstmt::EnlargeUpdate (LPVARDEF vd,int VarID,LongString FAR &s,int FAR *AnzPars,BOOL FAR &first,LPCLKEYDEF k0,LPBLOBDESC FAR *bdsc)
  {
  if (!IsModifiable(vd,VarID,k0)) return TRUE ;
  LPVOID Data = res->first->rec[0]->Get(VarID);
  BOOL correct = TRUE;
  if (vd->VarSize != 0xFFFF) {
    if (Data != NULL) {
      if (!first)
        s = s + "," ;
      BOOL doFree ;
      LPSTR vstring ;
      if (vd->mType != VAR_BLOB)
        vstring = GetVarString (Data,vd->mType,&doFree,vd->VarSize,FALSE,0);
      else
        vstring = ":BLOB" , doFree = FALSE , *bdsc = LPBLOBDESC (Data) ;
      if (vstring != NULL) {
        s = s + GetAliasName(vd->GetName()) + " = " + vstring ;
        if (doFree)
          FreeGlobMem (vstring);
        (*AnzPars) ++ ;
        correct = TRUE ;
        }
      else
        correct = FALSE ;
      }
    else {
      if (!first)
        s = s + "," ;
      s = s + GetAliasName(vd->GetName()) + " = NULL";
      correct = TRUE ;
      }
    first = FALSE ;
    }
  else {
    if (Data != NULL)
      PushToBlocked (Data,vd->VarID);
    ThereAreBlockedData = TRUE ;
    }
  return correct ;
  }
BOOL sybstmt::EnlargeUpdate_Blocked (LongString FAR &s,int FAR *AnzPars,BOOL FAR &first)
  {
  BOOL correct = TRUE;
  if (BlockedData != NULL) {
    if (!first)
      s = s + "," ;
    BOOL doFree ;
    LPSTR vstring = GetVarString (BlockedData,VAR_OBJ,&doFree,-1,FALSE,0);
    if (vstring != NULL) {
      s = s + BlockVarName () + " = " + vstring ;
      if (doFree)
        FreeGlobMem (vstring);
      (*AnzPars) ++ ;
      correct = TRUE ;
      }
    else
      correct = FALSE ;
    }
  else {
    if (ThereAreBlockedData) {
      if (!first)
        s = s + "," ;
      s = s + BlockVarName () + " = NULL";
      correct = TRUE ;
      }
    }
  first = FALSE ;
  return correct ;
  }
#pragma optimize("", on)

int sybstmt::StandardUpdate ()
  {
  LongString s,w;
  s = s + "UPDATE " + ORAGetTableName (req->TableDef[0],TRUE) + " SET " ;
  BOOL correct = TRUE ;
  int AnzPars = 0;
  BOOL first = TRUE ;
  LPCLKEYDEF k0 = req->TableDef[0]->GetKeyDef(0);
  LPTABLEDEF ti = req->TableDef[0] ;
  LPBLOBDESC bdsc = NULL;
  if (req->AnzElems > 0) {
    for (int i = 0 ; ((i < int(req->AnzElems)) && (correct)) ; i++) {
      if (req->elem[i].TableNumber == 0) {
        LPVARDEF vd = req->TableDef[0]->GetVarDef (req->elem[i].VarID);
        correct = EnlargeUpdate (vd,i,s,&AnzPars,first,k0,&bdsc);
        }
      }
    }
  else {
    for (int i = 0 ; ((i < ti->GetAnzVars()) && (correct)) ; i++) {
      LPVARDEF vd = ti->GetVarDef (i);
      correct = EnlargeUpdate (vd,i,s,&AnzPars,first,k0,&bdsc);
      }
    }
  correct = EnlargeUpdate_Blocked (s,&AnzPars,first);
  // Where Buffer
  LPSTR seq = w.AnalyseSeq (this,req->SelectionName,TRUE,req->TableDef[0],req,FALSE,FALSE,NULL,TRUE) ;
  if ((seq != NULL) && (*seq))
    s = s + " WHERE " + seq ;

  CS_RETCODE retcode = execute (s.Ptr(),ti,NULL,bdsc);

  // Die Zeile auf jeden Fall rausnehmen...
  RecBufferLine FAR *n = res->first->Next;
  FreeGlobMem (res->first);
  res->first = n;

  return (retcode == CS_SUCCEED) ? DBCALL_SUCCESS : DBCALL_NODATA ;
  }

int sybstmt::StandardExcute ()
  {
  LongString s;
  LPSTR seq = s.AnalyseSeq (this,req->SelectionName,FALSE,NULL,req,FALSE,FALSE,NULL,FALSE) ;

  CS_RETCODE retcode = execute (s.Ptr(),NULL);

  return ( (retcode == CS_SUCCEED) || (retcode == CS_LAST_DATA)) ? DBCALL_SUCCESS : DBCALL_NODATA ;// >>> FL 07.03.96 everything gotten
  }

int _export FAR PASCAL DBCall (WORD Op,int AnzLines,LPDBREQUEST req,LPVOID FAR *hstmt,RecBuffer FAR *res)
  {
  switch (Op) {
    case DBOP_ENDOFCONVERSION :
      return DBCALL_SUCCESS;
 
    case DBOP_RESET :
      // Statement wieder freigeben
      if (*hstmt != NULL) {
        LPSYBSTMT stmt = LPSYBSTMT (*hstmt);
        delete stmt;
        *hstmt = NULL ;
        }
      return DBCALL_SUCCESS;
    case DBOP_STARTOFUPDATE :
      DropPackage ();
      return DBCALL_SUCCESS;
    case DBOP_ENDOFUPDATE :
      CreatePackage ();
      return DBCALL_SUCCESS;
    default :
      LPSYBSTMT stmt = LPSYBSTMT (*hstmt);
      // Laufende Initialisierungen
      BOOL first ;
      if (stmt == NULL) {
        if (req->Type == DBCALLTYPE_STANDARDINSERT)
          stmt               = new insstmt();
        else if (req->Type == DBCALLTYPE_GETLIST)
          stmt               = new liststmt();
        else
          stmt               = new sybstmt();
        *hstmt             = stmt;
        first              = TRUE ;
        }
      else
        first              = FALSE ;
      stmt->retVal         = DBCALL_ERROR_NOACCESS;
      stmt->req            = req;
      stmt->Op             = Op;
      stmt->RecsToGet      = AnzLines;
      stmt->res            = res;
      if ((req->Type == DBCALLTYPE_TEST) || (req->Type == DBCALLTYPE_CREATE)) {
        if (req->Type == DBCALLTYPE_CREATE)
          InCreate = TRUE ;
        CheckFile (NULL,FALSE,TRUE);
        dbase->StartTableTest ();
        }
      BOOL cf = CheckFile (stmt,first,FALSE);
      if ((req->Type == DBCALLTYPE_TEST) || (req->Type == DBCALLTYPE_CREATE)) {
        // stmt->closeDone = TRUE ;
        return (cf) ? DBCALL_SUCCESS : DBCALL_NODATA ;
        }

      if (!req->foreignDone)
        req->BuildForeign ();   // Und noch die Fremdzugriffe ...
 
 
      #ifdef DEBUG_FIRST_CALL
        if (dbgfirst) {
          WIN_ASSERT_TEXT (FALSE, "DBCALL has been called");
          dbgfirst = FALSE;
        } // if
      #endif
 
      switch (req->Type) {
        case DBCALLTYPE_STANDARDDELETE :
          stmt->retVal = stmt->StandardDelete ();
          break ;
        case DBCALLTYPE_STANDARDGET :
          stmt->retVal = stmt->StandardGet ();
          stmt->GetOldStatementCopy ();
          break ;
        case DBCALLTYPE_GETLIST :
          if (((Op == DBOP_GETNEXT) || (Op == DBOP_GETPREV)) && (req->StraightForward)) {
            LPTABLEDEF ti = GetTableAdmin()->GetTableDef (req->GetTableID(),req->GetVersion());
            CS_RETCODE retcode = stmt->FetchMore (ti);
            GetTableAdmin()->FreeTable (req->GetTableID(),req->GetVersion());
            if (retcode == CS_SUCCEED)
              stmt->retVal = DBCALL_SUCCESS ;
            else if ((retcode == CS_END_DATA) || (retcode == CS_LAST_DATA)) // >>> FL 07.03.96 everything gotten
              stmt->retVal = DBCALL_ENDOFFILE ;
            else
              stmt->retVal = DBCALL_ERROR ;
            }
          else {
            stmt->retVal = stmt->StandardList (first,!req->StraightForward);
            if ((Op != DBOP_GETNEXT) && (Op != DBOP_GETPREV))
              stmt->GetOldStatementCopy ();
            }
          break ;
        case DBCALLTYPE_STANDARDINSERT :
          stmt->retVal = stmt->StandardInsert ();
          break ;
        case DBCALLTYPE_STANDARDUPDATE :
          stmt->retVal = stmt->StandardUpdate ();
          break ;
        case DBCALLTYPE_EXECUTE :
        case DBCALLTYPE_EXECUTESINGLE :
          if ((Op == DBOP_GETFIRST) || (Op == DBOP_PARSE)) {
            stmt->retVal = stmt->StandardExcute ();
            }
          break ;
        }
      stmt->StmtExit ();
      return stmt->retVal;
      break ;
    }

  return DBCALL_SUCCESS ;
  }

void _export FAR PASCAL DoBeginTransaction (BOOL large)
  {
  if (dbase == NULL)
    // Login to sybase
    dbase = new sybase (UserName,PassWord,AppName,FALSE);
  DBG_ASSERT_TEXT(FALSE,"Begin Transaction", "called");                             // ### FL wieder entfernen
  // set autocommit off
  if (large) {
    sybstmt *h = new sybstmt ();
    h->execute ("COMMIT",NULL);
    ocof(dbase->lda);
    CS_RETCODE retcode = ocirethandling(dbase->lda, dbase->lda);
    char SetTrans[80];
    wsprintf(SetTrans,"SET TRANSACTION USE ROLLBACK SEGMENT %s",BigRbsName);
    h->execute (SetTrans,NULL);
    delete h ;
    }
  else
    ocof(dbase->lda);
  CS_RETCODE retcode = ocirethandling(dbase->lda, dbase->lda);
  if ( retcode != CS_SUCCEED ) {
    WIN_ASSERT_TEXT (FALSE, "DoBeginTransaction: ocof() failed");
    } // if
  if (DoLog())
    LogCmd ("BEGINTRANSACTION",GetTickCount(),GetTickCount(),"");
  }

void _export FAR PASCAL DoEndTransaction ()
  {
  DBG_ASSERT_TEXT(FALSE,"Commit Transaction", "called");                            // ### FL wieder entfernen
  // commit
  ocom(dbase->lda);
  CS_RETCODE retcode = ocirethandling(dbase->lda, dbase->lda);
  if ( retcode != CS_SUCCEED ) {
    WIN_ASSERT_TEXT (FALSE, "DoEndTransaction: ocom() failed");
    } // if
  // set autocommit on
  ocon(dbase->lda);
  retcode = ocirethandling(dbase->lda, dbase->lda);
  if ( retcode != CS_SUCCEED ) {
    WIN_ASSERT_TEXT (FALSE, "DoEndTransaction: ocon() failed");
    } // if
  if (DoLog())
    LogCmd ("ENDTRANSACTION",GetTickCount(),GetTickCount(),"");
  }

BOOL hmemcmp (LPVOID c1,LPVOID c2,DWORD cmpSize)
  {
  char huge *h1 = (char huge *) c1;
  char huge *h2 = (char huge *) c2;
  BOOL res = TRUE ;
  for ( DWORD i = 0 ; i < cmpSize ; i++ ) {
    if (*h1++ != *h2++) {
      res = FALSE ;
      break ;
      }
    }
  return res;
  }

void _export FAR PASCAL DoAbortTransaction ()
  {
  DBG_ASSERT_TEXT(FALSE,"Abort Transaction", "called");                             // ### FL wieder entfernen
  // rollback
  orol(dbase->lda);
  CS_RETCODE retcode = ocirethandling(dbase->lda, dbase->lda);
  if ( retcode != CS_SUCCEED ) {
    WIN_ASSERT_TEXT (FALSE, "DoAbortTransaction: orol() failed");
    } // if
 
  // set autocommit on
  ocon(dbase->lda);
  retcode = ocirethandling(dbase->lda, dbase->lda);
  if ( retcode != CS_SUCCEED ) {
    WIN_ASSERT_TEXT (FALSE, "DoAbortTransaction: ocon() failed");
    } // if
  if (DoLog())
    LogCmd ("ABORTTRANSACTION",GetTickCount(),GetTickCount(),"");
  }


static char tmpBuffer[512];
extern LPSTR WINAPI makeIni(LPSTR txt);
LPSTR GetOutName (LPSTR TableName)
  {
  char Name[128],Path[128],def[32];
  lstrcpy (Name,TableName);
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
  tmpBuffer[i++] = 'O' ;
  tmpBuffer[i++] = 'Q' ;
  tmpBuffer[i++] = 'L' ;
  tmpBuffer[i++] = '\0' ;
  return tmpBuffer;
  }

DLLExport LPSTR _export WINAPI DataDict_GetSqlPart (WORD Cmd,LPSTR TableName,LPVOID DLLData,WORD VarID,WORD KeyNmbr,LPSTR Buffer,WORD BufSize)
  {
  BOOL InDBase = (VarAliasName != NULL);

  *Buffer = '\0';
  BOOL TableFound = FALSE ;
  WORD Version;
  WORD TableID = GetTableAdmin()->GetTableID (NULL,TableName,&TableFound,&Version);
  LPTABLEDEF td = NULL;
  if (TableFound)
    td = GetTableAdmin()->GetTableDef (TableID,Version);
  else
    return NULL;
  switch (Cmd) {
    case SQLSTMT_GETOUTNAME :
      {
      lstrcpy (Buffer,GetOutName(TableName));
      }
      return Buffer;
    case SQLSTMT_HEADER :
      {
      wsprintf (Buffer,"CREATE TABLE %s\r\n  (",TableName);
      }
      return Buffer;
    case SQLSTMT_VARDEF :
      {
      if (!InDBase) {
        VarAliasName = new LongString;
        VarSequenceName = new LongString;
        }
      BOOL blockDone = FALSE ;
      BOOL done = FALSE ;
      LongString s;
      for (int i = 0 ; i < td->GetAnzVars() ; i++) {
        LPVARDEF v = td->GetVarDef(i);
        if (v->VarSize != 0xFFFF) {
          if (done) {
            s = s + "," ;
            break;
            }
          if (i == int(VarID)) {
            BOOL doSize;
            s = s + "  " + GetAliasName(v->GetName()) + " " + GetTypeName (v,i,&doSize,td->GetKeyDef(0));
            if (doSize) {
              int size = v->VarSize;
              s = s + "(" + size + ")" ;
              }
            if ((v->Property & VPROP_NOTNULL) != 0) {
              s = s + " NOT NULL" ;
              }
            done = TRUE;
            }
          }
        else {
          if (!blockDone) {
            if (done) {
              s = s + "," ;
              break;
              }
            if (i == int(VarID)) {
              s = s + "  " + BlockVarName() + " " + BlockTypeName();
              done = TRUE;
              }
            blockDone = TRUE ;
            }
          }
        }
      if (!InDBase) {
        delete VarAliasName, VarAliasName = NULL;
        delete VarSequenceName, VarSequenceName = NULL;
        }
      if (done) {
        lstrcpy(Buffer,s.Ptr());
        return Buffer;
        }
      else
        return NULL;
      }
      break ;
    case SQLSTMT_BUTTOM :
      {
      if (!InDBase) {
        VarAliasName = new LongString;
        VarSequenceName = new LongString;
        }
      LongString s,c;
      // Table - Constraints UNIQUE (column1, column2)
      WORD        lastKeyNr = 0xFFFF;
      LPCLKEYDEF  k1;
      int         addConstraint = FALSE;

      for (int i = 0; i < td->GetAnzKeySegs(); i++) {
        k1 = td->GetKeyDef(i);  // key i does exist !
        if (k1 != NULL) { // just to be sure (we do not know the td structure

          if ( (k1->KeyNmbr != lastKeyNr) ) {   // Beginning of a new key
            if (addConstraint) {  // close last Constraint, if any
              s = s + ")\r\n";
              } // if
            addConstraint = ((k1->Attribute & CLKD_UNIQUE) != 0);
            if (addConstraint) {  // open next constraint, if any
              LPVARDEF v = td->GetVarDef (k1->VarID);
              s = s + "  ,UNIQUE (" + GetAliasName(v->GetName()) ;
              } // if
            lastKeyNr = k1->KeyNmbr;
            } // if
          else {
            if (addConstraint) {  // add column to constraint, if a constraint is opened
              LPVARDEF v = td->GetVarDef (k1->VarID);
              s = s + "," + GetAliasName(v->GetName()) ;
              } // if
            } // else if

          } // if k1 != NULL
        } // for

      if (addConstraint) {  // there is one opened constraint left
        s = s + ")\r\n";        // close it
        } // if

      s = s + "  );\r\n" ;

      // CreateIndexStatements...
      WORD oldKeyNr = 0xFFFF;
      BOOL keyIsUnique = FALSE;      // only keys which are no unique keys are created hereby
      BOOL first = TRUE ;
      for (i = 0 ; ; i++) {
        LPCLKEYDEF k = (i < td->GetAnzKeySegs()) ? td->GetKeyDef (i) : NULL ;
        if ((k == NULL) || (k->KeyNmbr != oldKeyNr)) {
          if (!first) {
            if (!keyIsUnique) {
              c = c + ");\r\n" ;
              s = s + c.Ptr();
              } // if
            }
          if (k != NULL) {
            keyIsUnique = (k->Attribute & CLKD_UNIQUE) != 0;
            if (!keyIsUnique) { // unique indices are already created in the create table statement
              // >> FL 27.02.96: prepare unique Indexname
              char str[cMAX_VARNAMESIZE+1];
              lstrncpy(str, k->name, cMAX_VARNAMESIZE);
              str[cMAX_VARNAMESIZE] = 0;
              strncat(str, ORAGetTableName (td,FALSE), cMAX_VARNAMESIZE - lstrlen(str));
              str[cMAX_VARNAMESIZE] = 0;

              // create the index
              c.Clear ();
              LPVARDEF v = td->GetVarDef (k->VarID);
              c = c + "CREATE " ;
              c = c + "INDEX \"" + str + "\" ON " + ORAGetTableName (td,TRUE) + "(" + GetAliasName(v->GetName()) ;
              oldKeyNr = k->KeyNmbr;
              // << FL 27.02.96: prepare unique Indexname
              } // if
            }
          else
            break ;
          }
        else {
          LPVARDEF v = td->GetVarDef (k->VarID);
          c = c + "," + GetAliasName(v->GetName()) ;
          }
        first = FALSE ;
        }

      // ### FL Hier muss noch die Sequenz erstellt werden, sofern eine oder mehrere Sequenznummern
      // ### FL pro Tabelle erstellt werden müssen.
      c.Clear();
      c = c + "CREATE SEQUENCE " + GetSequenceName(td) +
              " INCREMENT BY 1" +
              " START WITH 1" +
              " NOCYCLE";
      s = s + c.Ptr() + ";\r\n";

      lstrcpy(Buffer,s.Ptr());
      if (!InDBase) {
        delete VarAliasName, VarAliasName = NULL;
        delete VarSequenceName, VarSequenceName = NULL;
        }
      return Buffer;
      }
      break ;
    case SQLSTMT_KEYSTMT :
      return NULL;
      break ;
    }
  return NULL;
  }

static DWORD LastEndT;
DLLExport void _export WINAPI MakeTimeStamp (LPSTR Msg)
  {
  DWORD endt = GetTickCount () ;
  if (DoLog()) {
    LogCmd (Msg,LastEndT,endt,"");
    }
  LastEndT = endt;
  }

DLLExport BOOL _export FAR PASCAL DBCurrentDateTime (LPVOID pdt)
  {
  if (dbase != NULL) {
    // ResetDscList ();
    BOOL res;
    LongString s;
    datetimestmt *datetime = new datetimestmt();
    s = s + "SELECT SYSDATE FROM DUAL";
    CheckFile (NULL, FALSE, FALSE);
    int retcode = datetime->execute (s.Ptr(), NULL); // Datum holen
    if (retcode == CS_SUCCEED   ||
        retcode == CS_LAST_DATA || // >>> FL 07.03.96 : data got successfully, too
        retcode == CS_END_DATA) {
      datetime->DateTime ((packdatetime FAR *) pdt);
      res = TRUE;
      }
    else
      res = FALSE;
    delete datetime;
    return res;
    }
  else
    return FALSE; // Verbindung noch nicht aufgebaut
  }

