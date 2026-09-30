/////////////////////////////////////////////////////////////////////////
// $Header:   P:/marille/clinicum/rev/maindigi.cpv   1.5   10 Jun 1996 10:08:48   GERHOLD  $
// $Log:   P:/marille/clinicum/rev/maindigi.cpv  $
// 
//    Rev 1.5   10 Jun 1996 10:08:48   GERHOLD
// pragma packinterpr.cpp
// 
//    Rev 1.4   02 Feb 1996 10:34:54   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.3   24 Aug 1995 00:20:26   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.2   20 Mar 1995 12:04:24   HANNES
// Konstantenhanling, RunNmbr...
// 
//    Rev 1.1   20 Nov 1994 18:01:54   HANNES
// Digitizer reaktiviert
// 
//    Rev 1.0   24 Jun 1994 19:30:42   HANNES
// Neuuebernahme clinicum
//

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <dos.h>
#include "dds32.h"
#include "globmem.h"
#include "dds.hpp"
#include "dds.h"
#include "printer.hpp"
#include "sc2d.hpp"
#include "font.hpp"
#include "paint.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "scripthd.hpp"
#include "mdichild.hpp"

#include "digitize.hpp"

#define MODULENUM 136
#include "winass.hpp"

static DIGICNF digcnf;

#pragma pack(1)
struct SetDigCnf_param {
  WORD parSize;
  DWORD LibName;
  DWORD CnfStr;
  };
#pragma pack()

BOOL SetDigCnf (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetDigCnf_param FAR *par = (SetDigCnf_param FAR *) param;
    LPSTR lname = LPSTR (c->ReadlData (par->LibName));
    DBWIN_ASSERT ((lname != NULL) && (lstrlen(lname) < 13)) ;
    LPSTR cstr = LPSTR (c->ReadlData (par->CnfStr));
    DBWIN_ASSERT ((cstr != NULL) && (lstrlen(cstr) < 14)) ;
    lstrcpy (digcnf.CnfStr,cstr);
    lstrcpy (digcnf.LibName,lname);

    SetDigCnf (&digcnf);
    }
  return FALSE ;
  }

