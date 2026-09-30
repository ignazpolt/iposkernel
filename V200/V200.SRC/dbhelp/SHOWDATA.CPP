///////////////////////////////////////////////////////////////////
//  Formatierung allgemeiner Daten
///////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/dbhelp/rev/showdata.cpv   1.13   24 Nov 1998 18:04:14   Hannes  $
//  $Log:   P:/marille/clinicum/dbhelp/rev/showdata.cpv  $
// 
//    Rev 1.13   24 Nov 1998 18:04:14   Hannes
// Formatierung des Datums mit d.m.yyyy
// 
//    Rev 1.12   21 Aug 1998 14:47:30   Hannes
// 
//    Rev 1.11   06 Aug 1998 09:27:00   Hannes
// Datumsformat
// 
//    Rev 1.10   04 Aug 1998 17:54:56   Hannes
// Timestamp
// 
//    Rev 1.9   10 Sep 1997 22:56:08   Hannes
// 
//    Rev 1.8   14 Jan 1997 16:06:08   HANNES
// 
//    Rev 1.7   26 Nov 1996 07:54:12   HANNES
// Automatischer Update
// 
//    Rev 1.6   08 Nov 1996 13:27:40   HANNES
// Einbau des Replikators
// 
//    Rev 1.5   04 Feb 1996 15:37:04   gerhold
// Teile von DBHELP in DDSMEM
// 
//    Rev 1.4   02 Feb 1996 10:42:50   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.3   16 Sep 1995 22:27:42   HANNES
// 
//    Rev 1.2   27 Mar 1995 13:19:20   HANNES
// 
//    Rev 1.1   05 Aug 1994 19:54:34   HANNES
// 
//    Rev 1.0   24 Jun 1994 16:44:50   HANNES
// Neuuebernahme clinicum
//
#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#include "globmem.h"
#define NODDSDATA
#include "dds.hpp"
#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#define MODULENUM 101
#include "winass.hpp"
#include "hash.hpp"
#define NOCOMPILE
#include "compile.hpp"
#include "dbrecord.hpp"

#include "sc2d.hpp"

void ToDec (LPSTR res,float v)
  {
  v *= float (10.0);
  LONG h ;
  if (v > 0.0) h = LONG(v + 0.5);
  else         h = LONG(v - 0.5);
  char xstr[20];
  wsprintf (xstr,"%ld",h);
  if (lstrlen(xstr) > 1) {
    lmemcpy (res,xstr,lstrlen(xstr)-1);
    res[lstrlen(xstr)-1] = '\0';
    lstrcat (res,".");
    lstrcat (res,xstr+lstrlen(xstr)-1);
    }
  else {
    lstrcpy (res,"0.");
    lstrcat (res,xstr);
    }
  }

static char HexChar(char n)
  {
  if (n <= 9) return (n + '0');
  else        return (n - 10 + 'A');
  }

static void ToHex (LPSTR res,LPSTR data,int size)
  {
  int j = 0;
  for (int i = 0 ; i < size ; i++) {
    // res[j++] = HexChar((data[size - 1 - i] & 0xF0) >> 4);
    // res[j++] = HexChar(data[size - 1 - i] & 0x0F);
    res[j++] = HexChar((data[i] & 0xF0) >> 4);
    res[j++] = HexChar(data[i] & 0x0F);
    }
  res[j] = '\0';
  }

DLLExport void _export WINAPI FormatOutTxt (LPSTR res,LPVOID data,WORD mType)
  {
  if (data == NULL)
    *res = '\0';
  else {
    switch (mType) {
      case VAR_DEC :
        ToDec (res,*((float FAR *) data));
        break ;
      case VAR_QLONG :
        ToDec (res,float (*((long double FAR *) data)));
        break ;
      case VAR_FLAG :
      case VAR_STRARR :
        wsprintf (res,"%d",*(short FAR *)(data));
        break ;
      case VAR_DATE :
        FormatDate (res,(packdate FAR *)data,"d.m.yyyy");
        break ;
      case VAR_TIME :
        writeTimeStr (res,0,(packtime FAR *)data);
        break ;
      case VAR_STR :
        wsprintf (res,"%.127s",LPSTR(data));
        break ;
      case VAR_LONG :
      case VAR_DWORD :
        wsprintf (res,"%ld",*LPDWORD(data));
        break ;
      case VAR_POINT :
        lstrcpy (res,"<");
        ToDec (res+lstrlen(res),((fpt FAR *) data)->x);
        lstrcat (res,",");
        ToDec (res+lstrlen(res),((fpt FAR *) data)->y);
        lstrcat (res,">");
        break ;
      case VAR_DATETIME :
        writeShortDateStr (res,(packdate FAR *)data);
        lstrcat (res," ");
        writeTimeStr (res + lstrlen (res),0,&((packdatetime FAR *)data)->pt);
        break ;
      case VAR_SCALE :
        lstrcpy (res,"<(");
        ToDec (res+lstrlen(res),((tr2 FAR *) data)->A[0][0]);
        lstrcat (res,",");
        ToDec (res+lstrlen(res),((tr2 FAR *) data)->A[0][1]);
        lstrcat (res,"),(");
        ToDec (res+lstrlen(res),((tr2 FAR *) data)->A[1][0]);
        lstrcat (res,",");
        ToDec (res+lstrlen(res),((tr2 FAR *) data)->A[1][1]);
        lstrcat (res,"),(");
        ToDec (res+lstrlen(res),((tr2 FAR *) data)->B[0]);
        lstrcat (res,",");
        ToDec (res+lstrlen(res),((tr2 FAR *) data)->B[1]);
        lstrcat (res,")>");
        break ;
      default :
        ToHex (res,LPSTR (data),min(GetBlockSize(data),32));
      }
    }
  }


