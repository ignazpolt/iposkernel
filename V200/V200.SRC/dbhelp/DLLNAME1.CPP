//-----------------------------------------------------
// $Header:   P:/marille/clinicum/dbhelp/rev/dllname1.cpv   1.1   02 Feb 1996 10:42:48   GERHOLD  $
// $Log:   P:/marille/clinicum/dbhelp/rev/dllname1.cpv  $
// 
//    Rev 1.1   02 Feb 1996 10:42:48   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.0   02 Jan 1996 22:17:36   HANNES
// Initial revision.
// DLLName.cpp ermitteln des Namens einer DLL
// aus dem INI File
//-----------------------------------------------------
#include <windows.h>
#include "dds32.h"

extern LPSTR WINAPI GetIniName();
void MyDLLName (LPSTR Path,LPSTR Symbname)
  {
  char p1[128];
  GetPrivateProfileString ("DataBase",Symbname,"dbbtrv.dll",
                            p1,128,
                            GetIniName()
                          );
  LPSTR h1 = p1 ;
  LPSTR h2 = Path ;
  for ( ; *h1 ; ) {
    if (*h1 == '.')
      *h2 ++ = '1' ;
    *h2 ++ = *h1 ++ ;
    }
  *h2 = '\0' ;
  }
