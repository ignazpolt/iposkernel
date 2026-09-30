// Einfacher Compiler zur Berechnung von Expressions
// $Header:   P:/marille/clinicum/rev/expr.cpv   1.57   05 May 2000 16:35:12   Martin  $
// $Log:   P:/marille/clinicum/rev/expr.cpv  $
// 
//    Rev 1.57   05 May 2000 16:35:12   Martin
// Unterhose etwas weiter gemacht.
// (MAX_IFS von 64 auf 256 erhoeht)
// 
//    Rev 1.56   21 Apr 2000 08:47:18   Hannes
// 
//    Rev 1.55   03 Apr 2000 17:20:22   Wolfgang
// 1.) Addieren/Subtrahieren von Zeiten im Composer.
// 
//    Rev 1.54   15 Dec 1999 18:20:14   Martin
// SaveContext: ifstack mit 0 initialisieren
// 
//    Rev 1.53   15 Dec 1999 00:14:56   Martin
// Grrmtjfx !!!!
// 
//    Rev 1.52   04 Aug 1999 10:39:30   Hannes
// Neue Syntax fuer Dep...
// 
//    Rev 1.51   27 Apr 1999 01:46:02   Hannes
// Abhaengigkeiten in Forstatements
// 
//    Rev 1.50   28 Jan 1999 12:19:42   Hannes
// Vergleiche mit Timestamps
// 
//    Rev 1.49   13 Jan 1999 17:27:46   Martin
// bei for-Schleifen-Variablen ein _f%d zum Eindeutigmachen
// 
//    Rev 1.48   02 Nov 1998 19:30:12   Hannes
// ForSchleife: NULL im Initblock
// 
//    Rev 1.47   23 Oct 1998 10:05:46   Hannes
// Verbesserungen FOR - Schleife
// 
//    Rev 1.46   14 Sep 1998 03:23:56   Hannes
// TRUE / FALSE
// 
//    Rev 1.45   06 Aug 1998 20:42:54   Hannes
// Keyword TRUE / FALSE
// 
//    Rev 1.44   04 Aug 1998 18:37:56   Hannes
// 
//    Rev 1.43   04 Aug 1998 14:23:56   Hannes
// CONTEXT: Fehlerkorrekturen / Contextspeichern und Freigeben an den richtigen
// Stellen
// 
//    Rev 1.42   04 Aug 1998 11:10:12   Hannes
// 
//    Rev 1.41   24 Jul 1998 20:15:24   Hannes
// Keywort "DEFCONTEXT"
// 
//    Rev 1.40   10 Jul 1998 21:38:54   Hannes
// For - Schleife
// 
//    Rev 1.39   08 Jul 1998 11:00:48   Hannes
// 
//    Rev 1.38   17 May 1998 17:51:44   Hannes
// Variable viele Parameter
// 
//    Rev 1.37   24 Mar 1998 17:45:18   Martin
// t4a raus
// 
//    Rev 1.36   19 Mar 1998 17:58:22   Hannes
// CopyList bei der aussersten Schleife
// 
//    Rev 1.35   12 Mar 1998 18:58:16   Hannes
// Bindung des ! - Operators
// 
//    Rev 1.34   13 Feb 1998 09:27:28   Hannes
// Flag -> Short ... Autokonvertierung
// 
//    Rev 1.33   02 Feb 1998 20:34:10   Hannes
// BInWAllowed: Woerter durch eckige Klammern implementieren
// 
//    Rev 1.32   26 Jan 1998 20:00:08   Hannes
// NULL als Schluesselwort
// 
//    Rev 1.31   16 Jan 1998 15:27:20   Hannes
// Listenfarben
// 
//    Rev 1.30   05 Jan 1998 07:53:42   Hannes
// Einsparungen im Scriptheader
// 
//    Rev 1.29   05 Dec 1997 17:45:52   Hannes
// diverse Verbesserungen
// 
//    Rev 1.28   05 Nov 1997 16:17:42   Hannes
// 
//    Rev 1.27   29 Oct 1997 19:00:12   Hannes
// Textbausteine
// 
//    Rev 1.26   22 Oct 1997 21:29:48   Hannes
// 
//    Rev 1.25   21 Oct 1997 11:43:44   Martin
// Datentyp vom IF-Zweig richtig uebernehmen
// 
//    Rev 1.24   29 Sep 1997 21:02:18   Martin
// "+" fuer VAR_POINT eingetragen
// 
//    Rev 1.23   27 Sep 1997 14:02:54   Martin
// * fuer Type scale eingetragen
// 
//    Rev 1.22   04 Sep 1997 20:11:48   Hannes
// Verbesserte Syntax -> SubCodes auch von Funktionen aus Aufrufbar
// 
//    Rev 1.21   13 Aug 1997 16:30:10   Hannes
// 
//    Rev 1.20   08 Aug 1997 00:09:34   HANNES
// No change.
// 
//    Rev 1.19   07 Aug 1997 11:53:14   Hannes
// 
//    Rev 1.18   16 Jul 1997 11:56:40   Hannes
// 
//    Rev 1.17   14 Jul 1997 12:50:02   Hannes
// 
//    Rev 1.16   11 Jul 1997 18:49:44   Hannes
// 
//    Rev 1.15   08 Jul 1997 11:59:20   Hannes
// 
//    Rev 1.14   01 Jul 1997 14:38:24   Hannes
// 
//    Rev 1.13   27 Jun 1997 19:36:48   HANNES
// 
//    Rev 1.12   25 Jun 1997 09:03:44   Hannes
// 
//    Rev 1.11   20 Jun 1997 20:20:26   Hannes
// 
//    Rev 1.10   20 Jun 1997 20:13:14   Hannes
// 
//    Rev 1.9   16 Jun 1997 11:38:00   Hannes
// Operator - Zulaessigkeit: eigenes Handles
// 
//    Rev 1.8   16 Jun 1997 07:48:04   Hannes
// Rueckgabe des resultierenden Datentypes
// 
//    Rev 1.7   27 May 1997 11:27:18   Hannes
// Verbesserte Konvertierungsfunktion, extern definierbar
// 
//    Rev 1.6   12 May 1997 08:38:58   Hannes
// Verschiedene Verbesserungen, speziell bei den Konvertierungskosten
// 
//    Rev 1.5   07 Apr 1997 14:20:46   Hannes
// 
//    Rev 1.4   17 Mar 1997 10:00:22   Hannes
// Sinnlose Funktionen raus
// 
//    Rev 1.3   13 Mar 1997 19:00:38   Hannes
// Zweite Erweiterungen
// 
//    Rev 1.2   28 Feb 1997 14:43:06   Hannes
// Fehlerkorrekturen, Erweiterungen
// 
//    Rev 1.1   19 Feb 1997 13:34:12   Hannes
// Near / Far Conversion Fehler
// 
//    Rev 1.0   19 Feb 1997 12:23:00   Hannes
// Initial revision.
//--------------------------------------------------------------------

#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#include "globmem.h"
#include "dds.hpp"
#include "hash.hpp"
#include "compile.hpp"
#define MODULENUM 178
#include "winass.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "scripthd.hpp"
#include "printer.hpp"
#include "sc2d.hpp"
#include "font.hpp"
#include "paint.hpp"
#include "mdichild.hpp"
#include "multipro.hpp"

#include "cntmenu.hpp"

#define SCFUNC        100
#define LOOPERATOR    101
#define HIOPERATOR    102
#define CMPOPERATOR   103

//--------------------------------------------------
// Vorinstallierte Funktionen
//--------------------------------------------------
LPVOID ToGlobMem (LPVOID data,int dSize)
  {
  LPVOID res = GetGlobMem (dSize);
  lmemcpy (res,data,dSize);
  return res;
  }
#ifdef MIST
LPVOID AddString (LPVOID FAR *args)
  {
  if ((args[0] != NULL) && (args[1] != NULL)) {
    int size = lstrlen(LPSTR(args[0])) + lstrlen(LPSTR(args[1])) + 1 ;
    LPSTR res = LPSTR(GetGlobMem (size));
    lstrcpy (res,LPSTR(args[0]));
    lstrcat (res,LPSTR(args[1]));
    return res ;
    }
  else if (args[0] != NULL)
    return ToGlobMem (args[0],lstrlen(LPSTR(args[0])) + 1);
  else if (args[1] != NULL)
    return ToGlobMem (args[1],lstrlen(LPSTR(args[1])) + 1);
  else
    return NULL ;
  }
LPVOID AddShort (LPVOID FAR *args)
  {
  if ((args[0] != NULL) && (args[1] != NULL)) {
    DBINT FAR *res = (DBINT FAR *) GetGlobMem (sizeof(DBINT));
    *res = * (DBINT FAR *) args[0] + * (DBINT FAR *) args[1];
    return res ;
    }
  else
    return NULL ;
  }
LPVOID SubShort (LPVOID FAR *args)
  {
  if ((args[0] != NULL) && (args[1] != NULL)) {
    DBINT FAR *res = (DBINT FAR *) GetGlobMem (sizeof(DBINT));
    *res = * (DBINT FAR *) args[0] - * (DBINT FAR *) args[1];
    return res ;
    }
  else
    return NULL ;
  }
LPVOID MulShort (LPVOID FAR *args)
  {
  if ((args[0] != NULL) && (args[1] != NULL)) {
    DBINT FAR *res = (DBINT FAR *) GetGlobMem (sizeof(DBINT));
    *res = * (DBINT FAR *) args[0] * * (DBINT FAR *) args[1];
    return res ;
    }
  else
    return NULL ;
  }
LPVOID DivShort (LPVOID FAR *args)
  {
  if ((args[0] != NULL) && (args[1] != NULL) && (* (DBINT FAR *) args[1])) {
    DBINT FAR *res = (DBINT FAR *) GetGlobMem (sizeof(DBINT));
    *res = * (DBINT FAR *) args[0] / * (DBINT FAR *) args[1];
    return res ;
    }
  else
    return NULL ;
  }
LPVOID AddLong (LPVOID FAR *args)
  {
  if ((args[0] != NULL) && (args[1] != NULL)) {
    LONG FAR *res = (LONG FAR *) GetGlobMem (sizeof(LONG));
    *res = * (LONG FAR *) args[0] + * (LONG FAR *) args[1];
    return res ;
    }
  else
    return NULL ;
  }
LPVOID SubLong (LPVOID FAR *args)
  {
  if ((args[0] != NULL) && (args[1] != NULL)) {
    LONG FAR *res = (LONG FAR *) GetGlobMem (sizeof(LONG));
    *res = * (LONG FAR *) args[0] - * (LONG FAR *) args[1];
    return res ;
    }
  else
    return NULL ;
  }
LPVOID MulLong (LPVOID FAR *args)
  {
  if ((args[0] != NULL) && (args[1] != NULL)) {
    LONG FAR *res = (LONG FAR *) GetGlobMem (sizeof(LONG));
    *res = * (LONG FAR *) args[0] * * (LONG FAR *) args[1];
    return res ;
    }
  else
    return NULL ;
  }
LPVOID DivLong (LPVOID FAR *args)
  {
  if ((args[0] != NULL) && (args[1] != NULL) && (* (LONG FAR *) args[1])) {
    LONG FAR *res = (LONG FAR *) GetGlobMem (sizeof(LONG));
    *res = * (LONG FAR *) args[0] / * (LONG FAR *) args[1];
    return res ;
    }
  else
    return NULL ;
  }
LPVOID AddFloat (LPVOID FAR *args)
  {
  if ((args[0] != NULL) && (args[1] != NULL)) {
    float FAR *res = (float FAR *) GetGlobMem (sizeof(float));
    *res = * (float FAR *) args[0] + * (float FAR *) args[1];
    return res ;
    }
  else
    return NULL ;
  }
LPVOID SubFloat (LPVOID FAR *args)
  {
  if ((args[0] != NULL) && (args[1] != NULL)) {
    float FAR *res = (float FAR *) GetGlobMem (sizeof(float));
    *res = * (float FAR *) args[0] - * (float FAR *) args[1];
    return res ;
    }
  else
    return NULL ;
  }
LPVOID MulFloat (LPVOID FAR *args)
  {
  if ((args[0] != NULL) && (args[1] != NULL)) {
    float FAR *res = (float FAR *) GetGlobMem (sizeof(float));
    *res = * (float FAR *) args[0] * * (float FAR *) args[1];
    return res ;
    }
  else
    return NULL ;
  }
LPVOID DivFloat (LPVOID FAR *args)
  {
  if ((args[0] != NULL) && (args[1] != NULL) && 
      ((*((float FAR *) args[1]) > 0.001) || (*((float FAR *) args[1]) < -0.001))) {
    float FAR *res = (float FAR *) GetGlobMem (sizeof(float));
    *res = * (float FAR *) args[0] / * (float FAR *) args[1];
    return res ;
    }
  else
    return NULL ;
  }
LPVOID ShortToString (LPVOID FAR *args)
  {
  if (args[0] != NULL) {
    char buffer[32];
    wsprintf (buffer,"%d",*(DBINT FAR *) args[0]);
    return ToGlobMem (buffer,lstrlen(buffer));
    }
  else
    return NULL ;
  }
LPVOID LongToString (LPVOID FAR *args)
  {
  if (args[0] != NULL) {
    char buffer[32];
    wsprintf (buffer,"%ld",*(LONG FAR *) args[0]);
    return ToGlobMem (buffer,lstrlen(buffer));
    }
  else
    return NULL ;
  }
LPVOID FloatToString (LPVOID FAR *args)
  {
  if (args[0] != NULL) {
    static char buffer[32];
    float f = *(float FAR *) args[0];
    sprintf (buffer,"%.1f",f);
    return ToGlobMem (buffer,lstrlen(buffer));
    }
  else
    return NULL ;
  }
LPVOID DateToString (LPVOID FAR *args)
  {
  if (args[0] != NULL) {
    char buffer[256];
    FormatDate (buffer,(packdate FAR *)args[0],"d.m.yy");
    return ToGlobMem (buffer,lstrlen(buffer));
    }
  else
    return NULL ;
  }
LPVOID TimeToString (LPVOID FAR *args)
  {
  if (args[0] != NULL) {
    char buffer[256];
    FormatTime (buffer,(packtime FAR *)args[0],"hh:mm");
    return ToGlobMem (buffer,lstrlen(buffer));
    }
  else
    return NULL ;
  }
#endif

#define VAR_FREE  0xFFFF
typedef LPVOID (* VFUNC) (LPVOID FAR *args);
#define MAX_TYPES 5
struct FAR _vfunc {
  LPSTR Name;
  VFUNC f;
  BYTE  opType;
  WORD  AnzArgs;
  WORD  types[MAX_TYPES];
  } vfunc [] =
  { 
  { "+" , NULL , LOOPERATOR , 2 , { VAR_STR , VAR_STR , VAR_STR } } ,
  { "+" , NULL , LOOPERATOR , 2 , { VAR_STRARR , VAR_STRARR , VAR_STRARR } } ,
  { "-" , NULL , LOOPERATOR , 2 , { VAR_STRARR , VAR_STRARR , VAR_STRARR } } ,
  { "*" , NULL , HIOPERATOR , 2 , { VAR_STRARR , VAR_STRARR , VAR_STRARR } } ,
  { "/" , NULL , HIOPERATOR , 2 , { VAR_STRARR , VAR_STRARR , VAR_STRARR } } ,
  { "+" , NULL , LOOPERATOR , 2 , { VAR_LONG , VAR_LONG , VAR_LONG } } ,
  { "-" , NULL , LOOPERATOR , 2 , { VAR_LONG , VAR_LONG , VAR_LONG } } ,
  { "*" , NULL , HIOPERATOR , 2 , { VAR_LONG , VAR_LONG , VAR_LONG } } ,
  { "/" , NULL , HIOPERATOR , 2 , { VAR_LONG , VAR_LONG , VAR_LONG } } ,
  { "+" , NULL , LOOPERATOR , 2 , { VAR_DEC , VAR_DEC , VAR_DEC } } ,
  { "-" , NULL , LOOPERATOR , 2 , { VAR_DEC , VAR_DEC , VAR_DEC } } ,
  { "*" , NULL , HIOPERATOR , 2 , { VAR_DEC , VAR_DEC , VAR_DEC } } ,
  { "/" , NULL , HIOPERATOR , 2 , { VAR_DEC , VAR_DEC , VAR_DEC } } ,
  { "+" , NULL , LOOPERATOR , 2 , { VAR_QLONG , VAR_QLONG , VAR_QLONG } } ,
  { "-" , NULL , LOOPERATOR , 2 , { VAR_QLONG , VAR_QLONG , VAR_QLONG } } ,
  { "*" , NULL , HIOPERATOR , 2 , { VAR_QLONG , VAR_QLONG , VAR_QLONG } } ,
  { "/" , NULL , HIOPERATOR , 2 , { VAR_QLONG , VAR_QLONG , VAR_QLONG } } ,
  { "+" , NULL , LOOPERATOR , 2 , { VAR_TIME , VAR_TIME , VAR_TIME } } ,
  { "-" , NULL , LOOPERATOR , 2 , { VAR_TIME , VAR_TIME , VAR_TIME } } ,
  { ">=" , NULL , CMPOPERATOR , 2 , { VAR_FLAG , VAR_DEC , VAR_DEC } } ,
  { "<=" , NULL , CMPOPERATOR , 2 , { VAR_FLAG , VAR_DEC , VAR_DEC } } ,
  { "<"  , NULL , CMPOPERATOR , 2 , { VAR_FLAG , VAR_DEC , VAR_DEC } } ,
  { ">"  , NULL , CMPOPERATOR , 2 , { VAR_FLAG , VAR_DEC , VAR_DEC } } ,
  { "==" , NULL , CMPOPERATOR , 2 , { VAR_FLAG , VAR_DEC , VAR_DEC } } ,
  { "!=" , NULL , CMPOPERATOR , 2 , { VAR_FLAG , VAR_DEC , VAR_DEC } } ,
  { ">=" , NULL , CMPOPERATOR , 2 , { VAR_FLAG , VAR_DATETIME , VAR_DATETIME } } ,
  { "<=" , NULL , CMPOPERATOR , 2 , { VAR_FLAG , VAR_DATETIME , VAR_DATETIME } } ,
  { "<"  , NULL , CMPOPERATOR , 2 , { VAR_FLAG , VAR_DATETIME , VAR_DATETIME } } ,
  { ">"  , NULL , CMPOPERATOR , 2 , { VAR_FLAG , VAR_DATETIME , VAR_DATETIME } } ,
  { "==" , NULL , CMPOPERATOR , 2 , { VAR_FLAG , VAR_DATETIME , VAR_DATETIME } } ,
  { "!=" , NULL , CMPOPERATOR , 2 , { VAR_FLAG , VAR_DATETIME , VAR_DATETIME } } ,
  { ">=" , NULL , CMPOPERATOR , 2 , { VAR_FLAG , VAR_STRARR , VAR_STRARR } } ,
  { "<=" , NULL , CMPOPERATOR , 2 , { VAR_FLAG , VAR_STRARR , VAR_STRARR } } ,
  { "<"  , NULL , CMPOPERATOR , 2 , { VAR_FLAG , VAR_STRARR , VAR_STRARR } } ,
  { ">"  , NULL , CMPOPERATOR , 2 , { VAR_FLAG , VAR_STRARR , VAR_STRARR } } ,
  { "==" , NULL , CMPOPERATOR , 2 , { VAR_FLAG , VAR_STRARR , VAR_STRARR } } ,
  { "!=" , NULL , CMPOPERATOR , 2 , { VAR_FLAG , VAR_STRARR , VAR_STRARR } } ,
  { ">=" , NULL , CMPOPERATOR , 2 , { VAR_FLAG , VAR_LONG , VAR_LONG } } ,
  { "<=" , NULL , CMPOPERATOR , 2 , { VAR_FLAG , VAR_LONG , VAR_LONG } } ,
  { "<"  , NULL , CMPOPERATOR , 2 , { VAR_FLAG , VAR_LONG , VAR_LONG } } ,
  { ">"  , NULL , CMPOPERATOR , 2 , { VAR_FLAG , VAR_LONG , VAR_LONG } } ,
  { "==" , NULL , CMPOPERATOR , 2 , { VAR_FLAG , VAR_LONG , VAR_LONG } } ,
  { "!=" , NULL , CMPOPERATOR , 2 , { VAR_FLAG , VAR_LONG , VAR_LONG } } ,
  { ">=" , NULL , CMPOPERATOR , 2 , { VAR_FLAG , VAR_STR , VAR_STR } } ,
  { "<=" , NULL , CMPOPERATOR , 2 , { VAR_FLAG , VAR_STR , VAR_STR } } ,
  { "<"  , NULL , CMPOPERATOR , 2 , { VAR_FLAG , VAR_STR , VAR_STR } } ,
  { ">"  , NULL , CMPOPERATOR , 2 , { VAR_FLAG , VAR_STR , VAR_STR } } ,
  { "==" , NULL , CMPOPERATOR , 2 , { VAR_FLAG , VAR_STR , VAR_STR } } ,
  { "!=" , NULL , CMPOPERATOR , 2 , { VAR_FLAG , VAR_STR , VAR_STR } } ,
  { ">=" , NULL , CMPOPERATOR , 2 , { VAR_FLAG , VAR_DATE , VAR_DATE } } ,
  { "<=" , NULL , CMPOPERATOR , 2 , { VAR_FLAG , VAR_DATE , VAR_DATE } } ,
  { "<"  , NULL , CMPOPERATOR , 2 , { VAR_FLAG , VAR_DATE , VAR_DATE } } ,
  { ">"  , NULL , CMPOPERATOR , 2 , { VAR_FLAG , VAR_DATE , VAR_DATE } } ,
  { "==" , NULL , CMPOPERATOR , 2 , { VAR_FLAG , VAR_DATE , VAR_DATE } } ,
  { "!=" , NULL , CMPOPERATOR , 2 , { VAR_FLAG , VAR_DATE , VAR_DATE } } ,
  { ">=" , NULL , CMPOPERATOR , 2 , { VAR_FLAG , VAR_TIME , VAR_TIME } } ,
  { "<=" , NULL , CMPOPERATOR , 2 , { VAR_FLAG , VAR_TIME , VAR_TIME } } ,
  { "<"  , NULL , CMPOPERATOR , 2 , { VAR_FLAG , VAR_TIME , VAR_TIME } } ,
  { ">"  , NULL , CMPOPERATOR , 2 , { VAR_FLAG , VAR_TIME , VAR_TIME } } ,
  { "==" , NULL , CMPOPERATOR , 2 , { VAR_FLAG , VAR_TIME , VAR_TIME } } ,
  { "!=" , NULL , CMPOPERATOR , 2 , { VAR_FLAG , VAR_TIME , VAR_TIME } } ,
  { "*" , NULL , HIOPERATOR , 2 , { VAR_SCALE , VAR_SCALE , VAR_SCALE } } ,
  { "+" , NULL , LOOPERATOR , 2 , { VAR_POINT , VAR_POINT , VAR_POINT } } ,
  { ">=" , NULL , CMPOPERATOR , 2 , { VAR_FLAG , VAR_QLONG , VAR_QLONG } } ,
  { "<=" , NULL , CMPOPERATOR , 2 , { VAR_FLAG , VAR_QLONG , VAR_QLONG } } ,
  { "<"  , NULL , CMPOPERATOR , 2 , { VAR_FLAG , VAR_QLONG , VAR_QLONG } } ,
  { ">"  , NULL , CMPOPERATOR , 2 , { VAR_FLAG , VAR_QLONG , VAR_QLONG } } ,
  { "==" , NULL , CMPOPERATOR , 2 , { VAR_FLAG , VAR_QLONG , VAR_QLONG } } ,
  { "!=" , NULL , CMPOPERATOR , 2 , { VAR_FLAG , VAR_QLONG , VAR_QLONG } } 
  } ;
#define VFUNC_BASE 1000

class ExpCompiler : public compiler {
 public :
  virtual DLLExport void _export WINAPI LoadKwHash (void);
  virtual DLLExport void _export WINAPI LoadAddHash (void);
  virtual DLLExport BOOL _export WINAPI TestError (void);
  virtual DLLExport void _export WINAPI InstallBuffer(LPVOID d);
  virtual DLLExport BOOL _export WINAPI BInWAllowed()
    {
    return TRUE ;
    }
  void DeinstallBuffer ()
    {
    FreeGlobMem (buffer_start);
    }
  virtual DLLExport BOOL _export AllowOperator()
    // { return TRUE ; }
    { return opAllowed ; }

  ExpCompiler () : compiler (NULL) { }
  };

DBINT lastErrLine,lastErrCol;
DLLExport BOOL _export WINAPI ExpCompiler::TestError (void)
  {
  // Nix tun, das Resultat wird zurueckgegeben
  if (wError != 0) {
    lastErrLine = DBINT(LineNr);
    lastErrCol = DBINT(column);
    return TRUE ;
    }
  return FALSE ;
  }

#define KWCOLON       0
#define KWIF          1
#define KWSEMICOLON   2
#define KWBRACEOPEN   3
#define KWBRACECLOSE  4
#define KWAND         5
#define KWOR          6
#define KWNOT         7
#define KWEXPEND      8
#define KWNULL        9
#define KWFOR         10
#define KWRETURN      11
#define KWCONTEXT     12
#define KWTRUE        13
#define KWFALSE       14

DLLExport void _export WINAPI ExpCompiler::InstallBuffer(LPVOID d)
  {
  int oldsize = lstrlen(LPSTR(d));
  buffer_start = LPSTR (GetGlobMem (oldsize + 7));
  lmemcpy (buffer_start,d,oldsize);
  lstrcpy (buffer_start + oldsize," _end_");
  actptr = buffer_start;
  // buffer_start = LPSTR(d) ;
  // actptr = LPSTR(d) ;

  LineNr = 1;
  IncLineNr = 1;
  column = 1;
  }

DLLExport void _export WINAPI ExpCompiler::LoadKwHash ()
  {
  hash *h = FixKwHash ();
  struct {
    WORD kw;
    LPSTR Text;
    } mykw[] = {
    { KWCOLON      , ","   } ,
    { KWIF         , "IF"  } ,
    { KWSEMICOLON  , ";"   } ,
    { KWBRACEOPEN  , "("   } ,
    { KWBRACECLOSE , ")"   } ,
    { KWAND        , "&&" } ,
    { KWOR         , "||"  } ,
    { KWNOT        , "!" } ,
    { KWNULL       , "NULL" } ,
    { KWFOR        , "FOR" } ,
    { KWRETURN     , "RETURN" } ,
    { KWCONTEXT    , "CONTEXT" } ,
    { KWTRUE       , "TRUE" } ,
    { KWFALSE      , "FALSE" } ,
    { KWEXPEND     , "_end_" }
    } ;
  for (int i = 0 ; i < sizeof(mykw) / sizeof(mykw[0]) ; i++) {
    h->SetData (mykw[i].Text,&mykw[i].kw,sizeof(mykw[i].kw)) ;
    }
  ReleaseKwHash ();
  }

extern DWORD VirtFunctionsAddress (LPSTR FunctionName,LPSTR ModName,LPSCRIPTCONTENT FAR *lpsc,LPWORD destind,BOOL checkOwn,WORD FAR *restyp);
struct FAR FuncDef {
  WORD  Type;
  LPSTR AliasName;
  LPSTR FuncName;
  WORD  VarType[1];
  int AnzArgs ()
    {
    return (GetBlockSize(this) - sizeof(*this)) / sizeof(WORD) ;
    }
  } ;

struct FAR ParseDefinition {
  WORD  GetModuleOffs;
  WORD  GetFunctionOffs;
  WORD  FuncFunctionOffs;
  WORD  DTFunctionOffs;
  WORD  SubFunctionOffs;
  WORD  SetListFunctionOffs;
  ExpCompiler FAR *exc;
  DWORD GetProcAddr;
  DWORD FuncProcAddr;
  DWORD DTProcAddr;
  DWORD SubProcAddr;
  DWORD SetListProcAddr;
  LPSCRIPTCONTENT scent;
  LPWORD gpdestInd;
  LPWORD fpdestInd;
  LPWORD dtdestInd;
  LPWORD spdestInd;
  LPWORD sldestInd;
  FuncDef FAR *FAR *cf;
  int AnzFuncs()
    {
    return (GetBlockSize(cf) / sizeof(cf[0])) ;
    }

  void AddFuncDef (FuncDef FAR *x)
    {
    FuncDef FAR * FAR * ncf = (FuncDef FAR * FAR *) GetGlobMem ((AnzFuncs() + 1) * sizeof(cf[0]));
    ncf[AnzFuncs()] = x;
    if (cf != NULL) {
      lmemcpy (ncf,cf,GetBlockSize(cf));
      FreeGlobMem (cf);
      }
    cf = ncf;
    }

  void InitializeGetProc ()
    {
    if (GetProcAddr == 0L) {
      char resName[256];
      WORD getArgs[3];
      getArgs[0] = VAR_STRARR ;
      getArgs[1] = VAR_STR ;
      getArgs[2] = VAR_STR ;
      GetFunctionName (LPSTR(this) + GetFunctionOffs,resName,3,getArgs);
      scent = GetScriptEntry(LPSTR(this) + GetModuleOffs);
      DBWIN_ASSERT (scent != NULL);
      WORD rType;
      GetProcAddr = GetFunctionsAddress (resName,scent->ExportDef,&gpdestInd,&rType);
      }
    }

  void InitializeSubProc ()
    {
    if (SubProcAddr == 0L) {
      char resName[256];
      WORD getArgs[5];
      getArgs[0] = VAR_STRARR ;
      getArgs[1] = VAR_STR ;
      getArgs[2] = VAR_STR ;
      getArgs[3] = VAR_STR ;
      getArgs[4] = VAR_STRARR ;
      GetFunctionName (LPSTR(this) + SubFunctionOffs,resName,5,getArgs);
      scent = GetScriptEntry(LPSTR(this) + GetModuleOffs);
      DBWIN_ASSERT (scent != NULL);
      WORD rType;
      SubProcAddr = GetFunctionsAddress (resName,scent->ExportDef,&spdestInd,&rType);
      }
    }

  void InitializeSetListProc ()
    {
    if (SetListProcAddr == 0L) {
      char resName[256];
      WORD slArgs[3];
      slArgs[0] = VAR_STRARR ;
      slArgs[1] = VAR_STR ;
      slArgs[2] = VAR_STR ;
      GetFunctionName (LPSTR(this) + SetListFunctionOffs,resName,3,slArgs);
      scent = GetScriptEntry(LPSTR(this) + GetModuleOffs);
      DBWIN_ASSERT (scent != NULL);
      WORD rType;
      SetListProcAddr = GetFunctionsAddress (resName,scent->ExportDef,&sldestInd,&rType);
      }
    }

  void InitializeFuncProc ()
    {
    if (FuncProcAddr == 0L) {
      char resName[256];
      WORD getArgs[1];
      getArgs[0] = VAR_STR ;
      GetFunctionName (LPSTR(this) + FuncFunctionOffs,resName,1,getArgs);
      scent = GetScriptEntry(LPSTR(this) + GetModuleOffs);
      DBWIN_ASSERT (scent != NULL);
      WORD rType;
      FuncProcAddr = GetFunctionsAddress (resName,scent->ExportDef,&fpdestInd,&rType);
      }
    }

  void InitializeDTProc ()
    {
    if (DTProcAddr == 0L) {
      char resName[256];
      WORD getArgs[1];
      getArgs[0] = VAR_STRARR ;
      GetFunctionName (LPSTR(this) + DTFunctionOffs,resName,1,getArgs);
      scent = GetScriptEntry(LPSTR(this) + GetModuleOffs);
      DBWIN_ASSERT (scent != NULL);
      WORD rType;
      DTProcAddr = GetFunctionsAddress (resName,scent->ExportDef,&dtdestInd,&rType);
      }
    }
  } FAR *prdef;

DLLExport void _export WINAPI ExpCompiler::LoadAddHash ()
  {
  hAddHash = new hash (37,STRKEY);
  WORD hData[2];
  for (int i = 0 ; i < prdef->AnzFuncs() ; i++) {
    hData[0] = prdef->cf[i]->Type;
    hData[1] = prdef->cf[i]->Type;
    hAddHash->SetData (prdef->cf[i]->AliasName,hData,sizeof(hData));
    }
  for (i = 0 ; i < sizeof(vfunc) / sizeof(vfunc[0]) ; i++) {
    hData[0] = vfunc[i].opType;
    hData[1] = vfunc[i].opType;
    hAddHash->SetData (vfunc[i].Name,hData,sizeof(hData));
    }
  }

#define MAX_VARS 64
LPWORD GetSourceTableInd(LPSCRIPTCONTENT scdest,LPSCRIPTCONTENT scsource,LPWORD destInd)
  {
  static WORD sourceInd[64];
  int atr = int(destInd[0]);
  for (int i = 0 ; i < atr ; i++) {
    for ( TableRef tr = scdest->TRef[destInd[i + 1]] ; ; ) {
      LPTABLEDEF td = GetTableAdmin()->GetTableDef (tr.TableNr,tr.Version);
      TableRef trp;
      trp.TableNr = td->GetParentID();
      trp.Version = td->GetParentVersion();
      GetTableAdmin()->FreeTable (tr.TableNr,tr.Version);
      if (trp.TableNr != 0) tr = trp ;
      else                  break ;
      }
    // Suchen des Tabellenindex im aktuellen Script
    for ( int j = 0 ; j < int(scsource->AnzTables) ; j++) {
      if (lmemcmp (&scsource->TRef[j],&tr,sizeof(tr))) break ;
      }
    if (j == int(scsource->AnzTables)) return NULL ;
    else sourceInd[i] = WORD(j) ;
    }
  return sourceInd;
  }

extern void SetLastFunctionData (LPVOID FAR *vals,int ap,mdiChild *c);
void CallFunction (DWORD FuncAddr,mdiChild *c,LPSCRIPTCONTENT scchild,LPWORD destInd,int AnzPars,LPVOID FAR *vals,int AnzValsRet,LPVOID FAR *ValsRet)
  {
  // Aufruf der eigentlichen Funktion
  //--------------------------------------------------
  mdiChild *n = new ExpChild (scchild);
  n->_ccount_base = PushBlock (c->_ccount->Copy());
  n->outContext = (c->outContext) ? c->outContext : c ;
  LPWORD sourceInd = GetSourceTableInd(scchild,c->schd,destInd);
  DBWIN_ASSERT_TEXT(sourceInd != NULL,"Inkompatibler Kontext");
  n->SetContextRecords (c,destInd[0],destInd + 1,sourceInd);
  SetLastFunctionData (vals,AnzPars,c);
  MultiProc FAR *mp = new MultiProc (n,FuncAddr);
  mp->AddProcAtTail(0);
  {
  SetExtraInfo extra(n,mp->CorrOffs(),mp->CorrOffs());
  n->ResetCount ();
  mp->ExCuteLast (EM_LOAD | EM_CHANGETOTRUE,&extra);
  } // Destruktor von extra
  SetLastFunctionData (vals,AnzPars,c);
  {
  SetExtraInfo extra(n,mp->CorrOffs(),mp->CorrOffs());
  n->ResetCount ();
  mp->ExCuteLast (EM_RESET | EM_CLEAR,&extra);
  } // Destruktor von extra
  mp->RemoveLast ();
  delete mp ;

  // Daten wieder zurueckuebernehmen
  //--------------------------------------------------
  LPDBRECORD r1 = n->rr->GetRecord (DYNLOCALDATA);
  for (int i = 0 ; i < AnzValsRet ; i++) {
    LPVOID data = r1->Get(i);
    if (data != NULL) {
      ValsRet[i] = GetGlobMem (GetBlockSize(data));
      lmemcpy (ValsRet[i],data,GetBlockSize(data));
      }
    else
      ValsRet[i] = NULL ;
    }

  // Wieder aufraeumen
  //--------------------------------------------------
  // Die Nextsameverbindungen loesen
  if (r1 != NULL) { delete r1 ; n->rr->SetRecord (DYNLOCALDATA,NULL); }
  LPDBRECORD r2 = n->rr->GetRecord (STATICLOCALDATA);
  if (r2 != NULL) { delete r2 ; n->rr->SetRecord (STATICLOCALDATA,NULL); }
  
  delete n;
  }

#define STACKDP       256
#define CONDDP        64
#define UNKNOWNCODE             1
#define INCOMPATIBLEDATATYPES   2

static mdiChild *parseChild;
static ExpCompiler FAR *exc;
static BOOL dosyntaxCheck;
#define MAX_IFS 256
struct IFExpr {
  LPSTR Cond;
  LPSTR IfExpression;
  LPSTR ElseExpression;
  WORD  IfType;
  WORD  ElseType;
  LPSTR datatype;
  } ;

// Daten, die im Context gerettet werden muessen!
struct ContextData {
  WORD   expVarType[STACKDP];
  WORD   expFuncId[STACKDP];
  LPSTR  expVarVal[STACKDP];
  IFExpr ifstack[MAX_IFS];
  int stackPtr;
  int ifstackptr;
  int ifsstackptr[MAX_IFS];
  int sstackptr;
  LPSTR actConnect;
  BOOL doConnect;
  LPSTR varpattern;
  BOOL retAllowed;
  };
static WORD hforNum = 0;
static int hShouldBe = -1;
static ContextData cd;

#define MAX_FOR_STATEMENTS      64
static int ForStmtCounter;
#define MAX_DEP   5
static struct _ForStmt {
  LPSTR hvarname;
  LPSTR hz;
  LPSTR formel;
  LPSTR formelListe;
  LPSTR lstAlias;
  LPSTR lstDep;
  LPSTR hzNext;
  LPSTR formelNext;
  int anzDep;
  LPSTR depStr[MAX_DEP];
  WORD fType;
  } ForStmt[MAX_FOR_STATEMENTS];
void ClearForStmt ()
  {
  for (int i = 0 ; i < ForStmtCounter ; i++) {
    if (ForStmt[i].hvarname) FreeGlobMem (ForStmt[i].hvarname) , ForStmt[i].hvarname = NULL ;
    if (ForStmt[i].hz) FreeGlobMem (ForStmt[i].hz) , ForStmt[i].hz = NULL ;
    if (ForStmt[i].formel) FreeGlobMem (ForStmt[i].formel) , ForStmt[i].formel = NULL ;
    if (ForStmt[i].formelListe) FreeGlobMem (ForStmt[i].formelListe) , ForStmt[i].formelListe = NULL ;
    if (ForStmt[i].hzNext) FreeGlobMem (ForStmt[i].hzNext) , ForStmt[i].hzNext = NULL ;
    if (ForStmt[i].formelNext) FreeGlobMem (ForStmt[i].formelNext) , ForStmt[i].formelNext = NULL ;
    if (ForStmt[i].lstAlias) FreeGlobMem (ForStmt[i].lstAlias) , ForStmt[i].lstAlias = NULL ;
    if (ForStmt[i].lstDep) FreeGlobMem (ForStmt[i].lstDep) , ForStmt[i].lstDep = NULL ;
    for ( int j = 0 ; (j < ForStmt[i].anzDep) ; j++) {
      FreeGlobMem (ForStmt[i].depStr[j]) , 
      ForStmt[i].depStr[j] = NULL ;
      }
    ForStmt[i].anzDep = 0;
    }
  }

void MarkForBlock (LPSTR varPattern,LPSTR res,LPSTR hilfsZeilen,WORD fType)
  {
  if (varPattern != NULL) {
    ForStmt[ForStmtCounter].hvarname = LPSTR(GetGlobMem (lstrlen(varPattern) + 1));
    lstrcpy (ForStmt[ForStmtCounter].hvarname,varPattern);
    }
  if (res != NULL) {
    ForStmt[ForStmtCounter].formel = LPSTR(GetGlobMem (lstrlen(res) + 1));
    lstrcpy (ForStmt[ForStmtCounter].formel,res);
    }
  if (hilfsZeilen != NULL) {
    ForStmt[ForStmtCounter].hz = LPSTR(GetGlobMem (lstrlen(hilfsZeilen) + 1));
    lstrcpy (ForStmt[ForStmtCounter].hz,res);
    }
  ForStmt[ForStmtCounter].fType = fType;
  }

void AddForDep (LPSTR dep)
  {
  if ((dep != NULL) && (ForStmt[ForStmtCounter].anzDep < MAX_DEP)) {
    ForStmt[ForStmtCounter].depStr[ForStmt[ForStmtCounter].anzDep] = dep;
    ForStmt[ForStmtCounter].anzDep ++ ;
    }
  else
    exc->wError = PARERROR ;
  }

void MarkListVar (LPSTR res,LPSTR lstAlias,LPSTR dep)
  {
  if (res != NULL) {
    ForStmt[ForStmtCounter].formelListe = LPSTR(GetGlobMem (lstrlen(res) + 1));
    lstrcpy (ForStmt[ForStmtCounter].formelListe,res);
    }
  if (lstAlias != NULL) {
    ForStmt[ForStmtCounter].lstAlias = LPSTR(GetGlobMem (lstrlen(lstAlias) + 1));
    lstrcpy (ForStmt[ForStmtCounter].lstAlias,lstAlias);
    }
  if ((dep != NULL) && (*dep != NULL)) {
    ForStmt[ForStmtCounter].lstDep = LPSTR(GetGlobMem (lstrlen(dep) + 1));
    lstrcpy (ForStmt[ForStmtCounter].lstDep,dep);
    }
  }

void MarkNextBlock (LPSTR res,LPSTR hilfsZeilen)
  {
  if (res != NULL) {
    ForStmt[ForStmtCounter].formelNext = LPSTR(GetGlobMem (lstrlen(res) + 1));
    lstrcpy (ForStmt[ForStmtCounter].formelNext,res);
    }
  if (hilfsZeilen != NULL) {
    ForStmt[ForStmtCounter].hzNext = LPSTR(GetGlobMem (lstrlen(hilfsZeilen) + 1));
    lstrcpy (ForStmt[ForStmtCounter].hzNext,hilfsZeilen);
    }
  ForStmtCounter ++ ;
  }

// static int rstackPtr;
void pushRes ()
  {
  // rstackPtr++ ;
  }
void ClearStack (int from)
  {
  for (int i = from ; i < cd.stackPtr ; i++)
    if (cd.expVarVal[i] != NULL) FreeGlobMem (cd.expVarVal[i]) , cd.expVarVal[i] = NULL;
  cd.stackPtr = from ;
  }

void ClearIfStack ()
  {
  for (int i = 0 ; i < cd.ifstackptr ; i++) {
    if (cd.ifstack[i].Cond != NULL) FreeGlobMem (cd.ifstack[i].Cond) , cd.ifstack[i].Cond = NULL ;
    if (cd.ifstack[i].IfExpression != NULL) FreeGlobMem (cd.ifstack[i].IfExpression) , cd.ifstack[i].IfExpression = NULL ;
    if (cd.ifstack[i].ElseExpression != NULL) FreeGlobMem (cd.ifstack[i].ElseExpression) , cd.ifstack[i].ElseExpression = NULL ;
    if (cd.ifstack[i].datatype != NULL) FreeGlobMem (cd.ifstack[i].datatype) , cd.ifstack[i].datatype = NULL ;
    }
  cd.ifstackptr = cd.sstackptr = 0 ;
  }
extern LPSTR PushString (LPSTR old,LPSTR str,int l);
extern LPSTR GetStringMem ();
struct KType {
  WORD t1,t2;
  int Kosten;
  LPSTR kb,ke;
  } ;
struct KTypeList {
  KType t;
  KTypeList FAR * Next ;
  };
KTypeList FAR *ktlist;
void AddToKTypeList (WORD t1,WORD t2,LPSTR kb,LPSTR ke,int Kosten)
  {
  KTypeList FAR *n = (KTypeList FAR *) GetGlobMem (sizeof(*n));
  n->t.t1 = t1 ;
  n->t.t2 = t2 ;
  n->t.Kosten = Kosten ;
  n->t.kb = LPSTR (GetGlobMem (lstrlen(kb) + 1));
  lstrcpy (n->t.kb,kb);
  n->t.ke = LPSTR (GetGlobMem (lstrlen(ke) + 1));
  lstrcpy (n->t.ke,ke);
  n->Next = ktlist;
  ktlist = n;
  }

void DelKTypeList ()
  {
  for ( ; (ktlist != NULL) ; ) {
    KTypeList FAR *n = ktlist->Next ;
    FreeGlobMem (ktlist->t.kb);
    FreeGlobMem (ktlist->t.ke);
    FreeGlobMem (ktlist);
    ktlist = n;
    }
  }

int KKosten (WORD t1,WORD t2,LPSTR FAR *kb,LPSTR FAR *ke,BOOL useOwn)
  {
  KType kf[] = 
    {
    { VAR_STRARR , VAR_STR , 10 , "ToString (" , ",\"%d\")" } ,
    { VAR_LONG   , VAR_STR , 10 , "ToString (" , ",\"%ld\")" } ,
    { VAR_DEC    , VAR_STR , 10 , "ToString (" , ",\"%.1f\")" } ,
    { VAR_DATE   , VAR_STR , 10 , "FormatDate (" , ",\"d.m.yy\")" } ,
    { VAR_TIME   , VAR_STR , 10 , "FormatTime (" , ",\"hh:mm\")" } ,
    { VAR_LONG   , VAR_STRARR , 5 , "ToShort (" , ")" } ,
    { VAR_DEC    , VAR_STRARR , 7 , "ToShort (" , ")" } ,
    { VAR_STRARR , VAR_LONG  , 2 , "ToLong (" , ")" } ,
    { VAR_DEC    , VAR_LONG  , 3 , "ToLong (" , ")" } ,
    { VAR_LONG   , VAR_DEC   , 1 , "ToFloat (" , ")" } ,
    { VAR_STRARR , VAR_DEC   , 2 , "ToFloat (" , ")" } ,
    { VAR_STRARR , VAR_FLAG  , 5 , "ToFlag (" , ")" } ,
    { VAR_LONG   , VAR_FLAG  , 5 , "ToFlag (" , ")" } ,
    { VAR_FLAG   , VAR_STRARR , 7 , "ToShort (" , ")" } 
    };
  *kb = *ke = NULL ;
  if ((t1 == VAR_FREE) || (t2 == VAR_FREE)) {
    return NULL ;
    }
  for (int i = 0 ; (i < (sizeof(kf) / sizeof(kf[0]))) ; i++) {
    if ((useOwn) && (t1 == t2)) {
       return 0 ;
       }
    if ((t1 == kf[i].t1) && (t2 == kf[i].t2)) {
      *kb = kf[i].kb ;
      *ke = kf[i].ke ;
      return kf[i].Kosten ;
      }
    }
  for (KTypeList FAR *x = ktlist ; x != NULL ; x = x->Next) {
    if ((t1 == x->t.t1) && (t2 == x->t.t2)) {
      *kb = x->t.kb ;
      *ke = x->t.ke ;
      return x->t.Kosten ;
      }
    }
  if (t1 == t2)
    return 0 ;
  else
    return -1;
  }
BOOL mitVariablenDeklaration (LPSTR h)
  {
  for ( ; *h ; h++)
    if (*h == '.') return FALSE ;
  return TRUE ;
  }
LPSTR GetHString (LPSTR res = NULL,BOOL mitConnect = FALSE)
  {
  for (int i = cd.ifstackptr - 1 ; i >= 0 ; i--) {
    char varnamp[64],varnam[64];
    lstrcpy (varnamp,cd.varpattern);
    lstrcat (varnamp,"_%d");
    wsprintf (varnam,varnamp,i + 1);
    if (mitVariablenDeklaration (varnam)) {
      res = PushString (res,cd.ifstack[i].datatype,lstrlen(cd.ifstack[i].datatype));
      res = PushString (res," ",1);
      res = PushString (res,varnam,lstrlen(varnam));
      res = PushString (res,cd.actConnect,lstrlen(cd.actConnect));
      }
    if (cd.ifstack[i].IfExpression)
      res = PushString (res,"if (",4);
    else
      res = PushString (res,"if (!",5);
    res = PushString (res,cd.ifstack[i].Cond,lstrlen(cd.ifstack[i].Cond));
    res = PushString (res,") ",2);
    if (cd.ifstack[i].IfExpression) {
      res = PushString (res,varnam,lstrlen(varnam));
      res = PushString (res," = ",3);
      res = PushString (res,cd.ifstack[i].IfExpression,lstrlen(cd.ifstack[i].IfExpression));
      if (cd.ifstack[i].ElseExpression) {
        res = PushString (res,"; else ",7);
        res = PushString (res,varnam,lstrlen(varnam));
        res = PushString (res," = ",3);
        res = PushString (res,cd.ifstack[i].ElseExpression,lstrlen(cd.ifstack[i].ElseExpression));
        }
      res = PushString (res,"; ",2);
      }
    else {
      res = PushString (res,varnam,lstrlen(varnam));
      res = PushString (res," = ",3);
      res = PushString (res,cd.ifstack[i].ElseExpression,lstrlen(cd.ifstack[i].ElseExpression));
      res = PushString (res,"; ",2);
      }
    if (i > 0) {
      if ((cd.actConnect) && (mitConnect))
        res = PushString (res,cd.actConnect,lstrlen(cd.actConnect));
      res = PushString (res,"\r\n",2);
      }
    }
  return res;
  }

BOOL IsString (LPSTR str,int l)
  {
  int i = 0 ;
  for (LPSTR h = str ; (i < l) ; str ++ , i++)
    if ((*h) && (*h != ' ') && (*h != '\r') && (*h != '\t')) return TRUE ;
  return FALSE ;
  }

LPSTR GetDataType (WORD mTyp)
  {
  LPSTR scres = (LPSTR)GetGlobMem(32);
  *scres = '\0';

  // Die Funktion noch bekannt geben
  LPVOID InVals[2],OutVals[1];
  prdef->InitializeDTProc ();
  InVals[0] = NULL;
  OutVals[0] = NULL;
  InVals[1] = GetGlobMem (sizeof(WORD));
  lmemcpy (LPSTR(InVals[1]),&mTyp,sizeof(mTyp));
  CallFunction (prdef->DTProcAddr,parseChild,prdef->scent,prdef->dtdestInd,2,InVals,1,OutVals);
  if (InVals[1] != NULL)
    FreeGlobMem (InVals[1]);
  if (OutVals[0] != NULL) {
    lstrcpy (scres,LPSTR (OutVals[0]));
    FreeGlobMem (OutVals[0]);
    }
  return scres ;
  }

LPSTR PushParam (LPSTR old,LPSTR param,WORD t1,WORD t2,BOOL useOwn = TRUE)
  {
  LPSTR kb,ke;
  if (t2 == VAR_FREEPAR) t2 = t1 ;
  int Kosten = KKosten (t1,t2,&kb,&ke,useOwn);
  if (Kosten >= 0) {
    if (kb != NULL)
      old = PushString (old,kb,lstrlen(kb));
    old = PushString (old,param,lstrlen(param));
    if (ke != NULL)
      old = PushString (old,ke,lstrlen(ke));
    return old;
    }
  else
    return NULL;
  }

DLLExport void _export PopCondition ()
  {
  cd.sstackptr -- ;
  int actptr = cd.ifsstackptr[cd.sstackptr];
  cd.ifstack[actptr].ElseExpression = cd.expVarVal[cd.stackPtr - 1],cd.expVarVal[cd.stackPtr - 1] = NULL ;
  cd.ifstack[actptr].ElseType = cd.expVarType[cd.stackPtr - 1] ;

  if (cd.ifstack[actptr].IfType == cd.ifstack[actptr].ElseType) {
    if (cd.ifstack[actptr].datatype != NULL) FreeGlobMem (cd.ifstack[actptr].datatype) , cd.ifstack[actptr].datatype = NULL ;
    cd.ifstack[actptr].datatype = GetDataType (cd.ifstack[actptr].IfType);
    cd.expVarType[cd.stackPtr - 1] = cd.ifstack[actptr].IfType;
    }
  else {
    LPSTR i2ekb,i2eke,e2ikb,e2ike;
    int IfToElse = KKosten (cd.ifstack[actptr].IfType,cd.ifstack[actptr].ElseType,&i2ekb,&i2eke,FALSE);
    int ElseToIf = KKosten (cd.ifstack[actptr].ElseType,cd.ifstack[actptr].IfType,&e2ikb,&e2ike,FALSE);
    if ((IfToElse > 0) && ((IfToElse <= ElseToIf) || (ElseToIf < 0))) {
      // Der Ifzweig wird auf den gleichen Datentyp gebracht, wie der Else Typ
      LPSTR nIf = PushParam (NULL,cd.ifstack[actptr].IfExpression,cd.ifstack[actptr].IfType,cd.ifstack[actptr].ElseType);
      FreeGlobMem (cd.ifstack[actptr].IfExpression);
      cd.ifstack[actptr].IfExpression = GetStringMem ();
      if (cd.ifstack[actptr].datatype != NULL) FreeGlobMem (cd.ifstack[actptr].datatype) , cd.ifstack[actptr].datatype = NULL ;
      cd.ifstack[actptr].datatype = GetDataType (cd.ifstack[actptr].ElseType);
      cd.expVarType[cd.stackPtr - 1] = cd.ifstack[actptr].ElseType;
      }
    else if ((ElseToIf > 0) && ((ElseToIf <= IfToElse) || (IfToElse < 0))) {
      // Der Elsezweig wird auf den gleichen Datentyp gebracht, wie der If Typ
      LPSTR nElse = PushParam (NULL,cd.ifstack[actptr].ElseExpression,cd.ifstack[actptr].ElseType,cd.ifstack[actptr].IfType);
      FreeGlobMem (cd.ifstack[actptr].ElseExpression);
      cd.ifstack[actptr].ElseExpression = GetStringMem();
      if (cd.ifstack[actptr].datatype != NULL) FreeGlobMem (cd.ifstack[actptr].datatype) , cd.ifstack[actptr].datatype = NULL ;
      cd.ifstack[actptr].datatype = GetDataType (cd.ifstack[actptr].IfType);
      cd.expVarType[cd.stackPtr - 1] = cd.ifstack[actptr].IfType;
      }
    else if (cd.ifstack[actptr].IfType == 0xFFFF) {
      if (cd.ifstack[actptr].datatype != NULL) FreeGlobMem (cd.ifstack[actptr].datatype) , cd.ifstack[actptr].datatype = NULL ;
      cd.ifstack[actptr].datatype = GetDataType (cd.ifstack[actptr].ElseType);
      cd.expVarType[cd.stackPtr - 1] = cd.ifstack[actptr].ElseType;
      }
    else if (cd.ifstack[actptr].ElseType == 0xFFFF) {
      if (cd.ifstack[actptr].datatype != NULL) FreeGlobMem (cd.ifstack[actptr].datatype) , cd.ifstack[actptr].datatype = NULL ;
      cd.ifstack[actptr].datatype = GetDataType (cd.ifstack[actptr].IfType);
      cd.expVarType[cd.stackPtr - 1] = cd.ifstack[actptr].IfType;
      }
    else
      exc->wError = PARERROR ;
    }

  char varnr[32];
  wsprintf (varnr,"_%d",actptr + 1);
  cd.expVarVal[cd.stackPtr - 1] = LPSTR (GetGlobMem (lstrlen(cd.varpattern) + lstrlen(varnr) + 1));
  lstrcpy (cd.expVarVal[cd.stackPtr - 1],cd.varpattern);
  lstrcat (cd.expVarVal[cd.stackPtr - 1],varnr);
  }

DLLExport void _export ToggleCondition ()
  {
  int actptr = cd.ifsstackptr[cd.sstackptr - 1];
  cd.ifstack[actptr].IfExpression = cd.expVarVal[cd.stackPtr - 1] , cd.expVarVal[cd.stackPtr - 1] = NULL;
  cd.ifstack[actptr].IfType = cd.expVarType[cd.stackPtr - 1] ;
  ClearStack (cd.stackPtr - 1);    // Ueberfluessiges Resultat wieder weg
  }

LPSTR GetCondition ()
  {
  LPSTR res = cd.expVarVal[-- cd.stackPtr] ;
  cd.expVarVal[cd.stackPtr] = NULL ;
  return res;
  }

DLLExport void _export WriteCondition ()
  {
  cd.ifstack[cd.ifstackptr - 1].Cond = GetCondition ();
  cd.ifsstackptr[cd.sstackptr] = cd.ifstackptr - 1;
  cd.sstackptr ++ ;
  }

DLLExport void _export MarkCondStart ()
  {
  }

DLLExport void _export MarkIfStart ()
  {
  DBWIN_ASSERT (cd.ifstackptr < MAX_IFS);
  cd.ifstackptr ++ ;
  }

DLLExport void _export PushNode ()
  {
  prdef->InitializeGetProc ();
  LPVOID InVals[3],OutVals[2];
  InVals[0] = InVals[1] = NULL ;
  LPSTR NodeName = LPSTR(GlobalLock (exc->hPars0)) + sizeof(WORD);
  InVals[2] = GetGlobMem (lstrlen(NodeName) + 1);
  lstrcpy (LPSTR(InVals[2]),NodeName);
  CallFunction (prdef->GetProcAddr,parseChild,prdef->scent,prdef->gpdestInd,3,InVals,2,OutVals);
  if (OutVals[0] == NULL)
    exc->wError = UNKNOWNCODE ;
  else {
    if (OutVals[1])
      cd.expVarVal[cd.stackPtr] = LPSTR(OutVals[1]);
    else {
      cd.expVarVal[cd.stackPtr] = LPSTR(InVals[2]);
      InVals[2] = NULL;
      }
    cd.expVarType[cd.stackPtr] = *(DBINT FAR *)OutVals[0];
    FreeGlobMem (OutVals[0]);
    cd.stackPtr ++ ;
    }
  if (InVals[2] != NULL)
    FreeGlobMem (InVals[2]);
  }
DLLExport void _export PushString ()
  {
  cd.expVarType[cd.stackPtr] = VAR_STR ;
  LPSTR str = LPSTR(GlobalLock (exc->hPars0)) + sizeof(WORD);
  int l = lstrlen(str);
  cd.expVarVal[cd.stackPtr] = LPSTR (GetGlobMem (l + 3));
  lstrcpy (cd.expVarVal[cd.stackPtr] + 1,str);
  cd.expVarVal[cd.stackPtr][0] = '"' ;
  cd.expVarVal[cd.stackPtr][l + 1] = '"' ;
  cd.stackPtr ++ ;
  }
DLLExport void _export PushShort ()
  {
  cd.expVarType[cd.stackPtr] = VAR_STRARR ;
  char string[32];
  wsprintf (string,"%d",DBINT(exc->scv.v.int_val));
  cd.expVarVal[cd.stackPtr] = LPSTR(GetGlobMem (lstrlen (string) + 1)) ;
  lstrcpy (cd.expVarVal[cd.stackPtr],string);
  cd.stackPtr ++ ;
  }
DLLExport void _export PushLong ()
  {
  cd.expVarType[cd.stackPtr] = VAR_LONG ;
  char string[32];
  wsprintf (string,"%ldL",LONG(exc->scv.v.int_val));
  cd.expVarVal[cd.stackPtr] = LPSTR(GetGlobMem (lstrlen (string) + 1)) ;
  lstrcpy (cd.expVarVal[cd.stackPtr],string);
  cd.stackPtr ++ ;
  }
DLLExport void _export PushTRUE ()
  {
  cd.expVarType[cd.stackPtr] = VAR_FLAG ;
  char string[32];
  wsprintf (string,"flag(TRUE)");
  cd.expVarVal[cd.stackPtr] = LPSTR(GetGlobMem (lstrlen (string) + 1)) ;
  lstrcpy (cd.expVarVal[cd.stackPtr],string);
  cd.stackPtr ++ ;
  }
DLLExport void _export PushFALSE ()
  {
  cd.expVarType[cd.stackPtr] = VAR_FLAG ;
  char string[32];
  wsprintf (string,"flag(FALSE)");
  cd.expVarVal[cd.stackPtr] = LPSTR(GetGlobMem (lstrlen (string) + 1)) ;
  lstrcpy (cd.expVarVal[cd.stackPtr],string);
  cd.stackPtr ++ ;
  }
DLLExport void _export PushNull ()
  {
  cd.expVarType[cd.stackPtr] = VAR_FREE ;
  char string[32];
  lstrcpy (string,"NULL");
  cd.expVarVal[cd.stackPtr] = LPSTR(GetGlobMem (lstrlen (string) + 1)) ;
  lstrcpy (cd.expVarVal[cd.stackPtr],string);
  cd.stackPtr ++ ;
  }
DLLExport void _export PushReturn ()
  {
  if (cd.retAllowed) {
    cd.expVarVal[cd.stackPtr] = LPSTR(GetGlobMem (lstrlen (ForStmt[ForStmtCounter].hvarname) + 1)) ;
    lstrcpy (cd.expVarVal[cd.stackPtr],ForStmt[ForStmtCounter].hvarname) ;
    cd.expVarType[cd.stackPtr] = ForStmt[ForStmtCounter].fType ;
    cd.stackPtr ++ ;
    }
  else
    exc->wError = SEM_ERROR;
  }
DLLExport void _export PushFloat ()
  {
  char string[32];
  cd.expVarType[cd.stackPtr] = VAR_DEC ;
  sprintf (string,"%f",exc->scv.v.float_val);
  cd.expVarVal[cd.stackPtr] = LPSTR(GetGlobMem (lstrlen (string) + 1)) ;
  lstrcpy (cd.expVarVal[cd.stackPtr],string);
  cd.stackPtr ++ ;
  }

#define VAR_FUNCTION 0xFFFD
#define VAR_OPERATOR 0xFFFE

void SetFlag (int i,BOOL res)
  {
  cd.expVarVal[i]  = LPSTR(GetGlobMem (sizeof(DBINT))) ;
  *(DBINT FAR *) cd.expVarVal[i] = res;
  cd.expVarType[i] = VAR_FLAG;
  }

void SetFlag (int i,LPSTR r1,LPSTR r2,LPSTR connect)
  {
  if (cd.expVarVal[i]) FreeGlobMem (cd.expVarVal[i]) , cd.expVarVal[i] = NULL ;
  cd.expVarVal[i]  = PushString (cd.expVarVal[i],"(",1) ;
  cd.expVarVal[i]  = PushString (cd.expVarVal[i],r1,lstrlen(r1)) ;
  cd.expVarVal[i]  = PushString (cd.expVarVal[i],connect,lstrlen(connect)) ;
  cd.expVarVal[i]  = PushString (cd.expVarVal[i],r2,lstrlen(r2)) ;
  cd.expVarVal[i]  = PushString (cd.expVarVal[i],")",1) ;
  cd.expVarVal[i]  = GetStringMem ();
  cd.expVarType[i] = VAR_FLAG;
  }

void SetFlag (int i,LPSTR r1,LPSTR connect)
  {
  if (cd.expVarVal[i]) FreeGlobMem (cd.expVarVal[i]) , cd.expVarVal[i] = NULL ;
  cd.expVarVal[i]  = PushString (cd.expVarVal[i],"(",1) ;
  cd.expVarVal[i]  = PushString (cd.expVarVal[i],connect,lstrlen(connect)) ;
  cd.expVarVal[i]  = PushString (cd.expVarVal[i],"(",1) ;
  cd.expVarVal[i]  = PushString (cd.expVarVal[i],r1,lstrlen(r1)) ;
  cd.expVarVal[i]  = PushString (cd.expVarVal[i],"))",2) ;
  cd.expVarVal[i]  = GetStringMem ();
  cd.expVarType[i] = VAR_FLAG;
  }

#define FUNC_AND  0xFFFF
#define FUNC_OR   0xFFFE
#define FUNC_NOT  0xFFFD
int KonvertierungsKosten (WORD FAR *t1,WORD FAR *t2,int Anz)
  {
  int res = 0 ;
  LPSTR kb,ke;
  for (int i = 0 ; i < Anz ; i++) {
    if (t2[i] == VAR_FREEPAR) break ;
    int ract = KKosten (t1[i],t2[i],&kb,&ke,FALSE);
    if (ract < 0) return -1 ;     // Keine Konvertierung gefunden
    res = res + ract ;
    }
  return res ;
  }

BOOL VariableAnzahlParameter (WORD FAR *vtypes,int anzargs)
  {
  for (int i = 0 ; i < anzargs ; i++) {
    if (vtypes[i] == VAR_FREEPAR) return TRUE ;
    }
  return FALSE ;
  }

BOOL FuncID (LPSTR Alias,LPSTR FAR &rName,WORD opType,WORD FAR *rType,WORD AnzIn,WORD FAR *varType,WORD FAR *FAR *ftypes)
  {
  // 1. Durchsuchen aller vorinstallierten Funktionen
  int besteKosten = 10000 ;
  BOOL res = FALSE ;
  *ftypes = NULL;
  for (int i = 0 ; i < sizeof(vfunc) / sizeof(vfunc[0]) ; i++) {
    if ((lstrcmp (Alias,vfunc[i].Name) == 0) && 
        (opType == vfunc[i].opType) &&
        ((vfunc[i].AnzArgs == AnzIn) || (VariableAnzahlParameter (vfunc[i].types + 1,vfunc[i].AnzArgs)))) {
      int aKosten = KonvertierungsKosten (varType,vfunc[i].types + 1,AnzIn) ;
      if ((aKosten >= 0) && (aKosten < besteKosten)) {
        *rType = vfunc[i].types[0] ;
        *ftypes = vfunc[i].types + 1;
        besteKosten = aKosten;
        rName = Alias ;
        res = TRUE ;
        }
      }
    }
  // 2. Durchsuchen aller vom Script installierten Funktionen
  for (i = 0 ; i < prdef->AnzFuncs() ; i++) {
    if ((prdef->cf[i]->Type == opType) &&
        (lstrcmp (Alias,prdef->cf[i]->AliasName) == 0) &&
        ((WORD(prdef->cf[i]->AnzArgs()) == AnzIn) ||
        (VariableAnzahlParameter (prdef->cf[i]->VarType + 1,WORD(prdef->cf[i]->AnzArgs()))))
       ) {
      int aKosten = KonvertierungsKosten (varType,prdef->cf[i]->VarType + 1,AnzIn) ;
      if ((aKosten >= 0) && (aKosten < besteKosten)) {
        rName = prdef->cf[i]->FuncName;
        *rType = prdef->cf[i]->VarType[0] ;
        *ftypes = prdef->cf[i]->VarType + 1;
        besteKosten = aKosten;
        res = TRUE ;
        }
      }
    }

  return res ;
  }

DLLExport void _export PopFunction ()
  {
  for (int i = cd.stackPtr - 1 ; i >= 0 ; i--)
    if ((cd.expVarType[i] == VAR_FUNCTION) || (cd.expVarType[i] == VAR_OPERATOR)) break ;
  WORD funcID = cd.expFuncId[i];
  if (funcID == FUNC_AND) {
    LPSTR r1 = GetCondition();
    LPSTR r2 = GetCondition();
    SetFlag(i,r1,r2," && ");
    }
  else if (funcID == FUNC_OR) {
    LPSTR r1 = GetCondition();
    LPSTR r2 = GetCondition();
    SetFlag(i,r1,r2," || ");
    }
  else if (funcID == FUNC_NOT) {
    LPSTR r1 = GetCondition();
    SetFlag(i,r1,"!");
    }
  else {
    WORD anzIn = cd.stackPtr - i - 1 ;
    WORD rType;
    LPSTR fName = cd.expVarVal[i];
    WORD FAR *ftypes;
    if (FuncID (LPSTR(cd.expVarVal[i]),fName,funcID,&rType,anzIn,cd.expVarType + i + 1,&ftypes)) {
      LPVOID resVal = NULL;
      cd.expVarVal[i] = NULL ; 
      if (cd.expVarType[i] == VAR_FUNCTION) {
        cd.expVarVal[i] = PushString (cd.expVarVal[i],fName,lstrlen(fName));
        cd.expVarVal[i] = PushString (cd.expVarVal[i],"(",1);
        WORD k = 0 ;
        for (WORD j = 0 ; j < anzIn ; j++) {
          cd.expVarVal[i] = PushParam (cd.expVarVal[i],cd.expVarVal[i + j + 1],cd.expVarType[i + j + 1],ftypes[k]);
          if (ftypes[k] != VAR_FREEPAR) k ++ ;
          if (j < anzIn - 1)
            cd.expVarVal[i] = PushString (cd.expVarVal[i],",",1);
          }
        cd.expVarVal[i] = PushString (cd.expVarVal[i],")",1);
        }
      else {
        cd.expVarVal[i] = PushString (cd.expVarVal[i],"(",1) ;
        cd.expVarVal[i] = PushParam (cd.expVarVal[i],cd.expVarVal[i + 1],cd.expVarType[i + 1],ftypes[0]);
        cd.expVarVal[i] = PushString (cd.expVarVal[i]," ",1);
        cd.expVarVal[i] = PushString (cd.expVarVal[i],fName,lstrlen(fName));
        cd.expVarVal[i] = PushString (cd.expVarVal[i]," ",1);
        cd.expVarVal[i] = PushParam (cd.expVarVal[i],cd.expVarVal[i + 2],cd.expVarType[i + 2],ftypes[1]);
        cd.expVarVal[i] = PushString (cd.expVarVal[i],")",1) ;
        }
      ClearStack (i + 1);
      cd.expVarVal[i]  = GetStringMem ();
      cd.expVarType[i] = rType;

      // Die Funktion noch bekannt geben
      LPVOID InVals[1],OutVals[1];
      prdef->InitializeFuncProc ();
      InVals[0] = GetGlobMem (lstrlen(fName) + 1);
      lstrcpy (LPSTR(InVals[0]),fName);
      CallFunction (prdef->FuncProcAddr,parseChild,prdef->scent,prdef->fpdestInd,1,InVals,0,OutVals);
      if (InVals[0] != NULL)
        FreeGlobMem (InVals[0]);
      }
    else
      exc->wError = INCOMPATIBLEDATATYPES;
    }
  }

DLLExport void _export opOn ()
  {
  exc->opAllowed = TRUE ;
  }

DLLExport void _export PushFunction ()
  {
  LPSTR AliasName = LPSTR(GlobalLock (exc->hPars0)) + sizeof(WORD) ;
  cd.expVarType[cd.stackPtr] = VAR_FUNCTION ;
  cd.expVarVal[cd.stackPtr] = LPSTR (GetGlobMem (lstrlen(AliasName) + 1)) ;
  lstrcpy (cd.expVarVal[cd.stackPtr],AliasName);
  cd.expFuncId[cd.stackPtr] = exc->scv.v.k_ident;
  cd.stackPtr ++ ;
  }

DLLExport void _export PushAnd ()
  {
  cd.expVarType[cd.stackPtr] = cd.expVarType[cd.stackPtr - 1];
  cd.expVarVal[cd.stackPtr] = cd.expVarVal[cd.stackPtr - 1];
  cd.expVarType[cd.stackPtr - 1] = VAR_OPERATOR ;
  cd.expVarVal[cd.stackPtr - 1] = NULL ;
  cd.expFuncId[cd.stackPtr - 1] = FUNC_AND;
  cd.stackPtr ++ ;
  }

DLLExport void _export PushOr ()
  {
  cd.expVarType[cd.stackPtr] = cd.expVarType[cd.stackPtr - 1];
  cd.expVarVal[cd.stackPtr] = cd.expVarVal[cd.stackPtr - 1];
  cd.expVarType[cd.stackPtr - 1] = VAR_OPERATOR ;
  cd.expVarVal[cd.stackPtr - 1] = NULL ;
  cd.expFuncId[cd.stackPtr - 1] = FUNC_OR;
  cd.stackPtr ++ ;
  }

DLLExport void _export PushNot ()
  {
  cd.expVarType[cd.stackPtr] = VAR_OPERATOR ;
  cd.expVarVal[cd.stackPtr] = NULL ;
  cd.expFuncId[cd.stackPtr] = FUNC_NOT;
  cd.stackPtr ++ ;
  }

DLLExport void _export PushOperator ()
  {
  LPSTR Name = LPSTR(GlobalLock (exc->hPars0)) + sizeof(WORD);
  cd.expVarType[cd.stackPtr] = cd.expVarType[cd.stackPtr - 1];
  cd.expVarVal[cd.stackPtr] = cd.expVarVal[cd.stackPtr - 1];
  cd.expVarType[cd.stackPtr - 1] = VAR_OPERATOR ;
  cd.expVarVal[cd.stackPtr - 1] = LPSTR (ToGlobMem (Name,lstrlen(Name) + 1)) ;
  cd.expFuncId[cd.stackPtr - 1] = exc->scv.v.k_ident;
  GlobalUnlock (exc->hPars0);
  cd.stackPtr ++ ;
  }

DLLExport void _export PushCondition ()
  {
  pushRes ();
  }

DLLExport void _export GetSubItem ()
  {
  PopFunction ();
  LPSTR SubName = LPSTR(GlobalLock (exc->hPars0)) + sizeof(WORD);

  prdef->InitializeSubProc ();
  LPVOID InVals[5],OutVals[2];
  InVals[0] = InVals[1] = NULL ;
  InVals[2] = GetGlobMem (lstrlen(SubName));
  lstrcpy (LPSTR(InVals[2]),SubName + 1);
  InVals[3] = GetGlobMem (lstrlen(cd.expVarVal [cd.stackPtr - 1]) + 1);
  lstrcpy (LPSTR(InVals[3]),cd.expVarVal [cd.stackPtr - 1]);
  InVals[4] = GetGlobMem (sizeof(DBINT));
  *(DBINT FAR *) InVals[4] = cd.expVarType [cd.stackPtr - 1];

  CallFunction (prdef->SubProcAddr,parseChild,prdef->scent,prdef->spdestInd,5,InVals,2,OutVals);

  if (OutVals[0] == NULL)
    exc->wError = UNKNOWNCODE ;
  else {
    if (OutVals[1])
      cd.expVarVal[cd.stackPtr - 1] = LPSTR(OutVals[1]);
    else {
      cd.expVarVal[cd.stackPtr - 1] = LPSTR(InVals[4]);
      InVals[4] = NULL;
      }
    cd.expVarType[cd.stackPtr - 1] = *(DBINT FAR *)OutVals[0];
    FreeGlobMem (OutVals[0]);
    }
  if (InVals[2] != NULL)
    FreeGlobMem (InVals[2]);
  if (InVals[3] != NULL)
    FreeGlobMem (InVals[3]);
  if (InVals[4] != NULL)
    FreeGlobMem (InVals[4]);
  }

#define MAX_FORS  8     // Maximal 8 geschachtelte fors
static int ContextPtr = 0;
static ContextData FAR *ContextStack[MAX_FORS];
DLLExport void _export SaveContext ()
  {
  ContextStack[ContextPtr] = (ContextData FAR *) GetGlobMem (sizeof(ContextData));
  *ContextStack[ContextPtr] = cd;
  //ClearIfStack ();
  //ClearStack (0);
  lmemset(cd.ifstack,'\0',sizeof(cd.ifstack));
  cd.stackPtr = cd.ifstackptr = cd.sstackptr = 0;
  ContextPtr ++ ;
  cd.actConnect = ", " ;
  cd.doConnect = FALSE ;
  char vorNum[32];
  sprintf (vorNum,"_f%d",hforNum);
  cd.varpattern = LPSTR (GetGlobMem (lstrlen (ContextStack[0]->varpattern) + lstrlen(vorNum) + 1));
  lstrcpy (cd.varpattern,ContextStack[0]->varpattern);
  lstrcat (cd.varpattern,vorNum);
  hforNum = hforNum + 1;
  }

DLLExport void _export RestoreContext ()
  {
  ClearIfStack ();
  ClearStack(0);
  FreeGlobMem (cd.varpattern);
  cd = *ContextStack[-- ContextPtr] ;
  FreeGlobMem (ContextStack [ContextPtr]);
  }

DLLExport void _export ClearContext ()
  {
  for ( ; (ContextPtr > 0) ; RestoreContext ()) ;
  ClearIfStack ();
  ClearStack(0);
  hforNum = 0;
  }

DLLExport void _export PushDep ()
  {
  prdef->InitializeGetProc ();
  LPVOID InVals[3],OutVals[2];
  InVals[0] = InVals[1] = NULL ;
  LPSTR NodeName = LPSTR(GlobalLock (exc->hPars0)) + sizeof(WORD);
  InVals[2] = GetGlobMem (lstrlen(NodeName) + 1);
  lstrcpy (LPSTR(InVals[2]),NodeName);
  CallFunction (prdef->GetProcAddr,parseChild,prdef->scent,prdef->gpdestInd,3,InVals,2,OutVals);
  if (OutVals[0] == NULL)
    exc->wError = UNKNOWNCODE ;
  else {
    if (OutVals[1])
      AddForDep (LPSTR(OutVals[1]));
    else {
      AddForDep (LPSTR(InVals[2]));
      InVals[2] = NULL;
      }
    FreeGlobMem (OutVals[0]);
    }
  if (InVals[2] != NULL)
    FreeGlobMem (InVals[2]);
  }

DLLExport void _export PopHVarInit ()
  {
  // Die Fertige Formel merken
  //---------------------------
  if (exc->wError == 0) {
    LPSTR res = cd.expVarVal[0] ;
    cd.expVarVal[0] = NULL ;
    WORD fType,rType = cd.expVarType[0];
    fType = rType;

    // Die aktuell gueltive Variable wird als Resultatvariable verwendet.
    LPSTR hilfsZeilen = GetHString (NULL,TRUE);
    MarkForBlock (cd.varpattern,res,hilfsZeilen,fType);

    // Und aufputzen ...
    RestoreContext ();
    SaveContext ();
    }
  }

void SetListContextProcMit (BOOL doMit,LPSTR es)
  {
  // Die Fertige Formel merken
  //---------------------------
  if (exc->wError == 0) {
    LPSTR res = cd.expVarVal[0] ;
    cd.expVarVal[0] = NULL ;
    WORD rType = cd.expVarType[0];
    // 
    // Jetzt mit dem entsprechenden Datentyp die Liste setzen
    // 
    prdef->InitializeSetListProc ();
    LPVOID InVals[4],OutVals[4];
    InVals[0] = NULL;
    InVals[1] = GetGlobMem (sizeof(DBINT));
    InVals[2] = NULL;
    if (es) {
      InVals[3] = GetGlobMem (lstrlen(es) + 1);
      lstrcpy (LPSTR(InVals[3]),es);
      }
    else
      InVals[3] = NULL;
    *((WORD FAR *) InVals[1]) = rType;

    CallFunction (prdef->SetListProcAddr,parseChild,prdef->scent,prdef->sldestInd,4,InVals,4,OutVals);

    //
    // Den naechsten Teil der Expression
    // -> die aktuelle gueltige varpattern wird als resultatvariable
    //

    MarkListVar (res,LPSTR (OutVals[0]),LPSTR(OutVals[2]));

    if (InVals[1] != NULL)
      FreeGlobMem (InVals[1]);
    if (InVals[3] != NULL)
      FreeGlobMem (InVals[3]);
    if (OutVals[0] != NULL)
      FreeGlobMem (OutVals[0]);
    if (OutVals[1] != NULL)
      FreeGlobMem (OutVals[1]);
    if (OutVals[2] != NULL)
      FreeGlobMem (OutVals[2]);
    if (OutVals[3] != NULL)
      FreeGlobMem (OutVals[3]);

    if (doMit) {
      RestoreContext ();
      SaveContext ();
      cd.retAllowed = TRUE;
      }
    }
  }

void SetListContextProc (BOOL doMit)
  {
  SetListContextProcMit (doMit,NULL);
  }

DLLExport void _export SetListContext ()
  {
  SetListContextProc (TRUE);
  }

DLLExport void _export SetListContextExtra ()
  {
  LPSTR Name = LPSTR(GlobalLock (exc->hPars0)) + sizeof(WORD);
  SetListContextProcMit (TRUE,Name);
  }

DLLExport void _export SetListContextOhne ()
  {
  SetListContextProc (FALSE);
  }

DLLExport void _export EndFor ()
  {
  if (exc->wError == 0) {
    LPSTR res = cd.expVarVal[0] ;   // Weiterschalt - Formel
    cd.expVarVal[0] = NULL ;
    WORD rType = cd.expVarType[0];
    // if (hShouldBe >= 0) {
    if (ForStmt[ForStmtCounter].fType == VAR_FREE) ForStmt[ForStmtCounter].fType = rType; // Fuer den Fall, dass mit NULL initialisiert wurde
    if (ForStmt[ForStmtCounter].fType != rType) {
    // LPSTR res1 = PushParam (NULL,res,rType,hShouldBe,FALSE);
      LPSTR res1 = PushParam (NULL,res,rType,ForStmt[ForStmtCounter].fType,FALSE);
      FreeGlobMem (res);
      res = GetStringMem() ;
      if (res1 == NULL) exc->wError = PARERROR ;
      }

    // Die aktuell gueltive Variable wird als Resultatvariable verwendet.
    LPSTR hilfsZeilen = GetHString (NULL,TRUE);

    MarkNextBlock (res,hilfsZeilen);
    }

  RestoreContext ();

  cd.expVarVal[cd.stackPtr] = LPSTR(GetGlobMem (lstrlen (ForStmt[ForStmtCounter - 1].hvarname) + 1)) ;
  lstrcpy (cd.expVarVal[cd.stackPtr],ForStmt[ForStmtCounter - 1].hvarname) ;
  cd.expVarType[cd.stackPtr] = ForStmt[ForStmtCounter - 1].fType ;
  cd.stackPtr ++ ;

  // Listenvariable zuruecksetzen
  prdef->InitializeSetListProc ();
  LPVOID InVals[3],OutVals[2];
  InVals[0] = NULL;
  InVals[1] = NULL;
  InVals[2] = NULL;

  CallFunction (prdef->SetListProcAddr,parseChild,prdef->scent,prdef->sldestInd,3,InVals,2,OutVals);
  }

DLLExport void _export EndContext ()
  {
  // Listenvariable zuruecksetzen
  prdef->InitializeSetListProc ();
  LPVOID InVals[2],OutVals[1];
  InVals[0] = NULL;
  InVals[1] = NULL;

  CallFunction (prdef->SetListProcAddr,parseChild,prdef->scent,prdef->sldestInd,2,InVals,1,OutVals);
  }

#define INITERM(A,B) ((struct syntax_node *) ((A) + ((B) << 8)))
extern syntax_node f2,f3,expression,condition,t2a,h1,e1,l1,a1,c1;
syntax_node op_lo         = { NULL , NULL , TRUE  , INITERM(LOOPERATOR,0) , PushOperator } ;

syntax_node op_hi         = { NULL , NULL , TRUE  , INITERM(HIOPERATOR,0) , PushOperator } ;

syntax_node f5a           = { NULL  , NULL  , TRUE  , INITERM(FREECHAR,0), PopFunction } ;
syntax_node f5            = { NULL  , &f5a  , TRUE  , INITERM(UNKNOWNIDENT,0), GetSubItem } ;

syntax_node f4            = { &f3  , &f2  , TRUE  , INITERM(KEYWORD,KWCOLON), NULL } ;
syntax_node f3            = { &f4  , NULL , FALSE , &expression, NULL } ;
syntax_node f2            = { &f5  , &f3  , TRUE  , INITERM(KEYWORD,KWBRACECLOSE), opOn } ;
syntax_node f1            = { &f2  , NULL , TRUE  , INITERM(KEYWORD,KWBRACEOPEN), NULL } ;
syntax_node fcall         = { &f1  , NULL , TRUE  , INITERM(SCFUNC,0), PushFunction } ;

syntax_node s8            = { NULL , NULL , TRUE  , INITERM(KEYWORD,KWFALSE), PushFALSE } ;
syntax_node s7            = { NULL , &s8  , TRUE  , INITERM(KEYWORD,KWTRUE), PushTRUE } ;
syntax_node s6            = { NULL , &s7  , TRUE  , INITERM(KEYWORD,KWRETURN), PushReturn } ;
syntax_node s5            = { NULL , &s6  , TRUE  , INITERM(KEYWORD,KWNULL), PushNull } ;
syntax_node s4            = { NULL , &s5  , TRUE  , INITERM(T_LINTEGER,0), PushLong } ;
syntax_node s3            = { NULL , &s4  , TRUE  , INITERM(DECIMAL,0), PushFloat } ;
syntax_node s2            = { NULL , &s3  , TRUE  , INITERM(T_INTEGER,0), PushShort } ;
syntax_node s1            = { NULL , &s2  , TRUE  , INITERM(STRING,0), PushString } ;
syntax_node symbol        = { NULL , &s1  , TRUE  , INITERM(UNKNOWNIDENT,0), PushNode } ;

extern syntax_node dep1;
syntax_node dep3          = { &dep1 , NULL  , TRUE   , INITERM(KEYWORD,KWCOLON) , NULL } ;
syntax_node dep2          = { NULL  , &dep3 , TRUE   , INITERM(KEYWORD,KWBRACECLOSE) , NULL } ;
syntax_node dep1          = { &dep2 , NULL  , TRUE   , INITERM(UNKNOWNIDENT,0) , PushDep } ;
syntax_node dep           = { &dep1 , NULL  , TRUE   , INITERM(KEYWORD,KWBRACEOPEN) , NULL } ;


syntax_node t5e           = { NULL , NULL , TRUE   , INITERM(KEYWORD,KWBRACECLOSE) , NULL } ;
syntax_node t5d           = { &t5e , NULL , FALSE  , &expression , EndContext } ;
syntax_node t5c           = { &t5d , NULL , TRUE   , INITERM(KEYWORD,KWSEMICOLON) , RestoreContext } ;
syntax_node t5b           = { &t5c , NULL , FALSE  , &expression , SetListContextOhne } ;             // Listenvariable
syntax_node t5a           = { &t5b , NULL , TRUE   , INITERM(KEYWORD,KWBRACEOPEN) , SaveContext } ;
syntax_node t5            = { &t5a , NULL , TRUE   , INITERM(KEYWORD,KWCONTEXT) , NULL } ;

syntax_node t4g           = { NULL  , NULL  , TRUE   , INITERM(KEYWORD,KWBRACECLOSE) , NULL } ;
syntax_node t4f           = { &t4g  , NULL  , FALSE  , &expression , EndFor } ;
syntax_node t4e2          = { &t4f  , NULL  , TRUE   , INITERM(KEYWORD,KWSEMICOLON) , SetListContext } ;
syntax_node t4e1          = { &t4f  , NULL  , TRUE   , INITERM(KEYWORD,KWSEMICOLON) , NULL } ;
syntax_node t4d1          = { &t4e1 , &t4e2 , TRUE   , INITERM(UNKNOWNIDENT,0) , SetListContextExtra } ;             // Listenvariable
syntax_node t4d           = { &t4d1 , NULL  , FALSE  , &expression , NULL } ;             // Listenvariable
syntax_node t4c           = { &t4d  , NULL  , TRUE   , INITERM(KEYWORD,KWSEMICOLON) , NULL } ;
syntax_node t4b           = { &t4c  , NULL  , FALSE  , &expression , PopHVarInit } ;                       // Initialbelegung
syntax_node t4a0          = { &t4b  , &t4b  , FALSE  , &dep , NULL } ;
syntax_node t4a           = { &t4a0 , NULL  , TRUE   , INITERM(KEYWORD,KWBRACEOPEN) , SaveContext } ;
syntax_node t4            = { &t4a  , &t5   , TRUE   , INITERM(KEYWORD,KWFOR) , NULL } ;

syntax_node t3i           = { NULL , NULL , TRUE   , INITERM(KEYWORD,KWBRACECLOSE) , PopCondition } ;
syntax_node t3h           = { NULL , NULL , TRUE   , INITERM(KEYWORD,KWBRACECLOSE) , PopCondition } ;
syntax_node t3g           = { &t3i , &t3h , FALSE  , &expression , NULL } ;
syntax_node t3f           = { &t3g , NULL , TRUE   , INITERM(KEYWORD,KWSEMICOLON) , ToggleCondition } ;
syntax_node t3e           = { &t3g , NULL , TRUE   , INITERM(KEYWORD,KWSEMICOLON) , ToggleCondition } ;
syntax_node t3d           = { &t3f , &t3e , FALSE  , &expression , NULL } ;
syntax_node t3c           = { &t3d , NULL , TRUE   , INITERM(KEYWORD,KWSEMICOLON) , WriteCondition } ;
syntax_node t3b           = { &t3c , NULL , FALSE  , &condition , PushCondition } ;
syntax_node t3a           = { &t3b , NULL , TRUE   , INITERM(KEYWORD,KWBRACEOPEN) , MarkCondStart } ;
syntax_node t3            = { &t3a , &t4  , TRUE   , INITERM(KEYWORD,KWIF) , MarkIfStart } ;

syntax_node t2b           = { NULL , NULL , TRUE   , INITERM(KEYWORD,KWBRACECLOSE) , NULL } ;
syntax_node t2a           = { &t2b , NULL , FALSE  , &expression , NULL } ;
syntax_node t2            = { &t2a , &t3  , TRUE   , INITERM(KEYWORD,KWBRACEOPEN) , NULL } ;

syntax_node t1            = { NULL , &t2  , FALSE  , &fcall , NULL } ;
syntax_node yesexpression = { NULL , &t1  , FALSE  , &symbol , NULL } ;

syntax_node yes = { NULL , NULL , FALSE   , &yesexpression , NULL } ;
syntax_node not = { NULL , NULL , FALSE   , &yesexpression , PopFunction } ;
syntax_node topexpression = { &not  , &yes , TRUE   , INITERM(KEYWORD,KWNOT) , PushNot } ;


syntax_node h3            = { NULL , NULL , TRUE  , INITERM(FREECHAR,0) , NULL } ;
syntax_node h2            = { &h1  , NULL , FALSE , &topexpression , PopFunction } ;
syntax_node h1            = { &h2  , &h3  , FALSE , &op_hi , NULL } ;
syntax_node hiexpression  = { &h1  , NULL , FALSE , &topexpression , opOn } ;

syntax_node l3            = { NULL , NULL , TRUE  , INITERM(FREECHAR,0) , NULL } ;
syntax_node l2            = { &l1  , NULL , FALSE , &hiexpression , PopFunction } ;
syntax_node l1            = { &l2  , &l3  , FALSE , &op_lo , NULL } ;
syntax_node loexpression  = { &l1  , NULL , FALSE , &hiexpression , opOn } ;

syntax_node c3             = { NULL , NULL , TRUE  , INITERM(FREECHAR,0) , NULL } ;
syntax_node c2             = { &c1  , NULL , FALSE , &loexpression , PopFunction } ;
syntax_node c1             = { &c2  , &c3  , TRUE  , INITERM(CMPOPERATOR,0) , PushOperator } ;
syntax_node cmpexpression  = { &c1  , NULL , FALSE , &loexpression , NULL } ;

syntax_node a3               = { NULL , NULL , TRUE  , INITERM(FREECHAR,0) , NULL } ;
syntax_node a2               = { &a1  , NULL , FALSE , &cmpexpression , PopFunction } ;
syntax_node a1               = { &a2  , &a3  , TRUE  , INITERM(KEYWORD,KWAND) , PushAnd } ;
syntax_node andexpression    = { &a1  , NULL , FALSE , &cmpexpression , NULL } ;

syntax_node e3            = { NULL , NULL , TRUE  , INITERM(FREECHAR,0) , NULL } ;
syntax_node e2            = { &e1  , NULL , FALSE , &andexpression , PopFunction } ;
syntax_node e1            = { &e2  , &e3  , TRUE  , INITERM(KEYWORD,KWOR) , PushOr } ;
syntax_node expression    = { &e1  , NULL , FALSE , &andexpression , NULL } ;

syntax_node condition     = { &e1  , NULL , FALSE , &expression , NULL } ;

syntax_node p1            = { NULL , NULL , TRUE , INITERM(KEYWORD,KWEXPEND) , NULL } ;
syntax_node prog          = { &p1  , NULL , FALSE , &expression , NULL } ;

#pragma pack(1)
struct FAR DefineParse_param {
  WORD  parSize;
  DWORD res;    // Zeiger mit der Definition
  DWORD GetFunction;
  DWORD FuncFunction;
  DWORD DTFunction;
  DWORD SubFunction;
  DWORD SetListFunction;
  };
#pragma pack()

WORD PushString (ParseDefinition FAR * FAR &res,LPSTR Str)
  {
  WORD Offs = GetBlockSize(res);
  LPSTR n = LPSTR(GetGlobMem (Offs + lstrlen(Str) + 1));
  lmemcpy (n,res,Offs);
  lstrcpy (n + Offs,Str);
  FreeGlobMem (res);
  res = (ParseDefinition FAR *) n;
  return Offs;
  }

BOOL DefineParse (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    DefineParse_param FAR *par = (DefineParse_param FAR *) param;
    ParseDefinition FAR *res;
    res = (ParseDefinition FAR *) GetGlobMem (sizeof (*res));
    WORD nOffs = PushString (res,c->schd->fName);
    res->GetModuleOffs = nOffs;
    LPSTR GetFunction = LPSTR(c->ReadlData (par->GetFunction));
    DBWIN_ASSERT (GetFunction != NULL);
    nOffs = PushString (res,GetFunction);
    res->GetFunctionOffs = nOffs ;
    LPSTR FuncFunction = LPSTR(c->ReadlData (par->FuncFunction));
    DBWIN_ASSERT (FuncFunction != NULL);
    nOffs = PushString (res,FuncFunction);
    res->FuncFunctionOffs = nOffs ;
    LPSTR DTFunction = LPSTR(c->ReadlData (par->DTFunction));
    DBWIN_ASSERT (DTFunction != NULL);
    nOffs = PushString (res,DTFunction);
    res->DTFunctionOffs = nOffs ;
    LPSTR SubFunction = LPSTR(c->ReadlData (par->SubFunction));
    DBWIN_ASSERT (SubFunction != NULL);
    nOffs = PushString (res,SubFunction);
    res->SubFunctionOffs = nOffs ;
    if (par->parSize >= sizeof (*par)) {
      LPSTR SetListFunction = LPSTR(c->ReadlData (par->SetListFunction));
      DBWIN_ASSERT (SetListFunction != NULL);
      nOffs = PushString (res,SetListFunction);
      res->SetListFunctionOffs = nOffs ;
      }
    c->WritelData (par->res,&res,sizeof(res),LPSTR(param) - sizeof(WORD));
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    DefineParse_param FAR *par = (DefineParse_param FAR *) param;
    ParseDefinition FAR *FAR *res = (ParseDefinition FAR *FAR *) c->ReadlData (par->res);
    DBWIN_ASSERT ((res != NULL) && (*res != NULL)) ;
    delete (*res)->exc;
    for ( int i = 0 ; i < (*res)->AnzFuncs() ; i++) {
      FreeGlobMem ((*res)->cf[i]->AliasName);
      FreeGlobMem ((*res)->cf[i]->FuncName);
      FreeGlobMem ((*res)->cf[i]);
      }
    if ((*res)->cf != NULL)
      FreeGlobMem ((*res)->cf);
    FreeGlobMem (*res);
    }
  return FALSE ;
  }

#pragma pack(1)
struct FAR AddParseFunction_param {
  WORD parSize;
  DWORD res;
  DWORD Type;
  DWORD AliasName;
  DWORD FuncName;
  DWORD AnzVTypes;
  DWORD vtype[1];
  };
#pragma pack()
BOOL AddParseFunction (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    AddParseFunction_param FAR *par = (AddParseFunction_param FAR *) param;
    LPSTR AliasName = LPSTR (c->ReadlData (par->AliasName));
    LPSTR FuncName = LPSTR (c->ReadlData (par->FuncName));
    ParseDefinition FAR *FAR *res = (ParseDefinition FAR *FAR *) c->ReadlData (par->res);
    DBWIN_ASSERT ((AliasName != NULL) && (FuncName != NULL) && (res != NULL) && (*res != NULL));
    DBINT AnzVarTypes = c->ReadConstInt (par->AnzVTypes);
    FuncDef FAR *n = (FuncDef FAR *) GetGlobMem (sizeof(*n) + (AnzVarTypes - 1) * sizeof(WORD));
    n->AliasName = LPSTR (GetGlobMem (lstrlen(AliasName) + 1)); lstrcpy (n->AliasName,AliasName);
    n->FuncName = LPSTR (GetGlobMem (lstrlen(FuncName) + 1)); lstrcpy (n->FuncName,FuncName);
    n->Type = WORD(c->ReadConstInt (par->Type));
    for (DBINT i = 0 ; i < AnzVarTypes ; i++)
      n->VarType[i] = WORD(c->ReadConstInt(par->vtype[i]));
    (*res)->AddFuncDef (n);
    }
  return FALSE ;
  }

BOOL StartParse (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    DefineParse_param FAR *par = (DefineParse_param FAR *) param;
    ParseDefinition FAR *FAR *res = (ParseDefinition FAR * FAR *) c->ReadlData (par->res);
    DBWIN_ASSERT ((res != NULL) && (*res != NULL)) ;
    prdef = *res ;
    (*res)->exc = new ExpCompiler ();
    (*res)->exc->PrepareParse ();
    }
  return FALSE ;
  }


#pragma pack(1)
struct FAR ParseExpression_param {
  WORD  parSize;
  DWORD pdef;
  DWORD expression;
  DWORD error;        // Error - Wert
  DWORD res;          // Konvertierte Formel
  DWORD shouldBe;     // Resultat - Type
  DWORD hilfsZeilen;  // Hilfszeilen
  DWORD varpattern;   // Hilfsvariablen - Prototyp
  DWORD errLine;
  DWORD errCol;
  DWORD rtype;
  DWORD connect;
  BOOL withRType()
    {
    return (parSize >= sizeof(*this) - sizeof(DWORD));
    }
  BOOL withConnect()
    {
    return (parSize >= sizeof(*this));
    }
  };
#pragma pack()

static ParseExpression_param FAR * parseParam;
static LPCMDCOUNT ccountcopy;
static WORD ParseExtraType;
static LPVOID ParseExtraData;
static int ParseExtraSize;
static DWORD ParseOwnerID;
LPVOID ParseExpression (mdiChild *c,LPVOID param,WORD mode,WORD FAR *error,WORD FAR *rType)
  {
  LPVOID res = NULL ;
  ParseExpression_param FAR *par = (ParseExpression_param FAR *)param;
  *error = 0;
  if (mode & (EM_LOAD | EM_UPDATE)) {
    LPSTR expstr = LPSTR (c->ReadlData (par->expression));
    if (expstr != NULL) {
      parseChild = c ;
      prdef = * ((ParseDefinition FAR *FAR *) c->ReadlData (par->pdef));
      exc = prdef->exc ;
      parseParam = par ;
      cd.sstackptr = cd.ifstackptr = cd.stackPtr = ForStmtCounter = 0 ;
      ccountcopy = c->_ccount->Copy();
      ParseExtraType = c->_ExtraType ;
      ParseExtraData = c->_ExtraData ;
      ParseExtraSize = c->_ExtraSize ;
      ParseOwnerID   = c->OwnerID();
      exc->ParseNow (expstr,&prog,NULL);
      FreeGlobMem (ccountcopy);
      exc->DeinstallBuffer ();
      if (exc->wError == 0) {
        res = cd.expVarVal[0] ;
        cd.expVarVal[0] = NULL ;
        *rType = cd.expVarType[0];
        }
      *error = exc->wError ;
      ClearStack (0);
      }
    }
  return res;
  }

BOOL CheckExpression (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    WORD error,rtype;
    ParseExpression_param FAR *par = (ParseExpression_param FAR *)param;
    dosyntaxCheck = TRUE;
    cd.varpattern = LPSTR (c->ReadlData (par->varpattern));
    DBWIN_ASSERT (cd.varpattern != NULL);
    if (par->withConnect ()) {
      cd.actConnect = LPSTR(c->ReadlData (par->connect));
      cd.doConnect = TRUE ;
      DBWIN_ASSERT (cd.actConnect != NULL);
      }
    else {
      cd.actConnect = "; " ;
      cd.doConnect = FALSE ;
      }
    DBINT FAR *shouldBe = (DBINT FAR *) c->ReadlData (par->shouldBe);
    if (shouldBe != NULL)
      hShouldBe = *shouldBe;
    else
      hShouldBe = -1;
    LPSTR res = LPSTR (ParseExpression (c,param,mode,&error,&rtype));
    dosyntaxCheck = FALSE;
    if ((error == 0) && (res != NULL)) {
      if (shouldBe != NULL) {
        LPSTR res1 = PushParam (NULL,res,rtype,*shouldBe,FALSE);
        FreeGlobMem (res);
        res = GetStringMem() ;
        if (res1 == NULL) error = PARERROR ;
        }
      }
    else
      res = NULL ;
    if ((res != NULL) && (error == 0)) {
      c->WritelData (par->res,res,lstrlen(res) + 1,LPSTR(param) - sizeof(WORD));
      LPSTR hf = NULL ;
      for (int i = 0 ; i < ForStmtCounter ; i++ ) {
        hf = PushString (hf,"obj l",5) ;
        hf = PushString (hf,ForStmt[i].hvarname,lstrlen(ForStmt[i].hvarname)) ;
        hf = PushString (hf," = FVEC.GetList (",17) ;
        hf = PushString (hf,ForStmt[i].formelListe,lstrlen(ForStmt[i].formelListe));
        hf = PushString (hf,");\r\n",4);
        hf = PushString (hf,"for ( ",6);
        if ((ForStmt[i].lstDep) || (ForStmt[i].anzDep > 0))
          hf = PushString (hf,"(",1);
        BOOL depDone = FALSE;
        if (ForStmt[i].lstDep) {
          hf = PushString (hf,ForStmt[i].lstDep,lstrlen(ForStmt[i].lstDep));
          depDone = TRUE ;
          }
        for (int j = 0 ; j < ForStmt[i].anzDep ; j++) {
          if (depDone)
            hf = PushString (hf,",",1);
          hf = PushString (hf,ForStmt[i].depStr[j],lstrlen(ForStmt[i].depStr[j]));
          depDone = TRUE ;
          }
        if ((ForStmt[i].lstDep) || (ForStmt[i].anzDep > 0))
          hf = PushString (hf,")",1);

        hf = PushString (hf," ; ",3);
        if (ForStmt[i].hz) {
          hf = PushString (hf,ForStmt[i].hz,lstrlen(ForStmt[i].hz));
          hf = PushString (hf," , ",3);
          }
        LPSTR dt = GetDataType (ForStmt[i].fType);
        hf = PushString (hf,dt,lstrlen(dt));
        FreeGlobMem(dt);
        hf = PushString (hf," ",1);
        hf = PushString (hf,ForStmt[i].hvarname,lstrlen(ForStmt[i].hvarname));
        hf = PushString (hf," = " ,3);
        hf = PushString (hf,ForStmt[i].formel,lstrlen(ForStmt[i].formel));
        hf = PushString (hf," ; innerlist l",14);
        hf = PushString (hf,ForStmt[i].hvarname,lstrlen(ForStmt[i].hvarname));
        hf = PushString (hf," ",1);
        hf = PushString (hf,ForStmt[i].lstAlias,lstrlen(ForStmt[i].lstAlias));
        hf = PushString (hf," ; ",3);

        if (ForStmt[i].hzNext) {
          hf = PushString (hf,ForStmt[i].hzNext,lstrlen(ForStmt[i].hzNext));
          hf = PushString (hf," , ",3);
          }

        hf = PushString (hf,ForStmt[i].hvarname,lstrlen(ForStmt[i].hvarname));
        hf = PushString (hf," = " ,3);
        hf = PushString (hf,ForStmt[i].formelNext,lstrlen(ForStmt[i].formelNext));
        hf = PushString (hf," );" ,3);
        }

      LPSTR hilfsZeilen = GetHString (hf);
      if (hilfsZeilen != NULL)
        c->WritelData (par->hilfsZeilen,hilfsZeilen,lstrlen(hilfsZeilen) + 1,LPSTR(param) - sizeof(WORD));
      else
        c->DellData (par->hilfsZeilen,LPSTR(param) - sizeof(WORD));
      if (par->withRType())
        c->WritelData (par->rtype,&rtype,sizeof(DBINT),LPSTR(param) - sizeof(WORD));
      }
    else {
      c->WritelData (par->errLine,&lastErrLine,sizeof(lastErrLine),LPSTR(param) - sizeof(WORD));
      c->WritelData (par->errCol,&lastErrCol,sizeof(lastErrCol),LPSTR(param) - sizeof(WORD));
      }
    ClearIfStack ();
    ClearForStmt ();
    c->WritelData (par->error,&error,sizeof(error),LPSTR(param) - sizeof(WORD));
    if (res != NULL) FreeGlobMem (res);
    ClearContext();
    }
  return FALSE ;
  }

#pragma pack(1)
struct FAR AddParseConversion_param {
  WORD parSize;
  DWORD t1;
  DWORD t2;
  DWORD Kosten;
  DWORD kb;
  DWORD ke;
  };
#pragma pack()

BOOL AddParseConversion (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    AddParseConversion_param FAR *par = (AddParseConversion_param FAR *) param;
    DBINT FAR *t1 = (DBINT FAR *) c->ReadlData (par->t1);
    DBINT FAR *t2 = (DBINT FAR *) c->ReadlData (par->t2);
    DBINT FAR *Kosten = (DBINT FAR *) c->ReadlData (par->Kosten);
    LPSTR kb = LPSTR (c->ReadlData (par->kb));
    LPSTR ke = LPSTR (c->ReadlData (par->ke));
    DBWIN_ASSERT ((t1 != NULL) && (t2 != NULL) && (Kosten != NULL) && (kb != NULL) && (ke != NULL));
    
    AddToKTypeList (*t1,*t2,kb,ke,*Kosten);
    }
  return FALSE ;
  }

extern mdiChild FAR *GetMainToolInst ();
DLLExport void _export ccf (LPSTR ModName,LPSTR FuncName,LPVOID obj)
  {
  char resName[128];
  WORD getArgs[1];
  getArgs[0] = VAR_OBJ ;
  GetFunctionName (FuncName,resName,1,getArgs);
  LPSCRIPTCONTENT scent = GetScriptEntry (ModName);
  DBWIN_ASSERT (scent != NULL);
  WORD rType;
  LPWORD gpdestInd;
  DWORD GetProcAddr = GetFunctionsAddress (resName,scent->ExportDef,&gpdestInd,&rType);
  LPVOID inData[1];
  inData[0] = GetGlobMem (sizeof(LPVOID));
  *((LPVOID FAR *) (inData[0])) = obj;
  CallFunction (GetProcAddr,GetMainToolInst(),scent,gpdestInd,1,inData,0,NULL);
  FreeGlobMem (inData[0]);
  }

CALLCONTEXTFUNCTION GetCallContextFunction ()
  {
  return CALLCONTEXTFUNCTION (MakeProcInstance (FARPROC(ccf),WBase::hInstance));
  }

#pragma pack(1)
struct SetContextFunction_param {
  WORD parSize;
  DWORD Type;
  DWORD Kategorie;
  DWORD Text;
  DWORD ModName;
  DWORD FuncName;
  };
#pragma pack()

BOOL SetContextFunction (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetContextFunction_param FAR *par = (SetContextFunction_param FAR *) param;
    AddGlobalContextMenu (*(WORD FAR *) c->ReadlData (par->Kategorie),
                          *(WORD FAR *) c->ReadlData (par->Type),
                          (LPSTR) c->ReadlData (par->Text),
                          (LPSTR) c->ReadlData (par->ModName),
                          (LPSTR) c->ReadlData (par->FuncName));
    }
  return FALSE ;
  }

