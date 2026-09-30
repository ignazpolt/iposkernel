//-----------------------------------------------------
// $Header:   P:/marille/clinicum/dbhelp/rev/dllname.cpv   1.2   30 Apr 1997 11:10:20   Hannes  $
// $Log:   P:/marille/clinicum/dbhelp/rev/dllname.cpv  $
// 
//    Rev 1.2   30 Apr 1997 11:10:20   Hannes
// 
//    Rev 1.1   02 Feb 1996 10:42:44   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.0   02 Jan 1996 22:17:34   HANNES
// Initial revision.
// DLLName.cpp ermitteln des Namens einer DLL
// aus dem INI File
//-----------------------------------------------------
#include <windows.h>
#include "dds32.h"

extern LPSTR WINAPI GetIniName();
void MyDLLName (LPSTR Path,LPSTR Symbname)
  {
  GetPrivateProfileString ("DataBase",Symbname,"dbbtrv.dll",
                            Path,64,
                            GetIniName()
                          );
  }
