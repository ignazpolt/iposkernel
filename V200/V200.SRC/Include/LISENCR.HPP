//
//  $Header:   P:/marille/clinicum/include/rev/lisencr.hpv   1.1   02 Feb 1996 11:00:00   GERHOLD  $
//  $Log:   P:/marille/clinicum/include/rev/lisencr.hpv  $
// 
//    Rev 1.1   02 Feb 1996 11:00:00   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.0   24 Jun 1994 17:01:46   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.1   20 Oct 1993 13:45:04   HANNES
// Neue Lizenz - DLL
// 
//    Rev 1.0   18 Mar 1993 09:08:08   HANNES
// Initial revision.
//
#define ENCRIPTLEN   512 - sizeof(DWORD)

DLLExport BOOL _export WINAPI GetFSBuffer (LPSTR res,int Size);
DLLExport BOOL _export WINAPI SearchFSItem (LPSTR str,LPSTR Item,int ItemSize);


