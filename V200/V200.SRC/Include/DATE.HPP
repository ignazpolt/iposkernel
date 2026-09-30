////////////////////////////////
//    Datumsroutinen
/////////////////////////////////
//  $Header:   P:/marille/clinicum/include/rev/date.hpv   1.3   15 Jun 1999 16:20:56   THOMAS  $
//  $Log:   P:/marille/clinicum/include/rev/date.hpv  $
// 
//    Rev 1.3   15 Jun 1999 16:20:56   THOMAS
// 1.) GetActTimeStr entfernt.
// 
//    Rev 1.2   05 Mar 1999 16:14:24   Wolfgang
// 1.) readTimeStr neu.
// 
//    Rev 1.1   02 Feb 1996 10:59:12   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.0   24 Jun 1994 17:01:08   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.1   02 Jun 1993 19:39:00   HANNES
// Funktionen in die DLL ausgelagert
// 
//    Rev 1.0   02 Mar 1993 22:36:14   HANNES
// Initial revision.
#define DMY     0
#define MDY     1
#define YMD     2

DLLExport BOOL _export WINAPI DateFromString (LPSTR txt,int format,packdate FAR *pd);
DLLExport void _export WINAPI StringFromDate (LPSTR txt,int format,BOOL usename,BOOL useabbr,packdate FAR *pd);
DLLExport void _export WINAPI DiffYears (double FAR *res,packdate FAR *d1,packdate FAR *d0);
DLLExport void _export WINAPI numStringFromDate (LPSTR txt,packdate FAR *pd);
DLLExport BOOL _export WINAPI readDateStr (LPSTR txt,packdate FAR *pd);
DLLExport BOOL _export WINAPI readTimeStr (LPSTR txt, BYTE Format, packtime FAR *pt);
DLLExport void _export WINAPI writeDateStr (LPSTR txt,packdate FAR *pd);
DLLExport void _export WINAPI writeShortDateStr (LPSTR txt,packdate FAR *pd);

