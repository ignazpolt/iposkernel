///////////////////////////////////////////////////////
//
// wmfcache.hpp 
//
///////////////////////////////////////////////////////
//
// $Header:   P:/marille/clinicum/include/rev/wmfcache.hpv   1.4   05 Oct 1998 11:24:20   Gerhold  $
// $Log:   P:/marille/clinicum/include/rev/wmfcache.hpv  $
// 
//    Rev 1.4   05 Oct 1998 11:24:20   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.3   02 Feb 1996 10:59:06   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.2   24 Jun 1994 20:43:18   MARTIN
// 
//    Rev 1.1   24 Jun 1994 19:19:14   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.0   02 Dec 1992 16:09:42   HANNES
// Initial revision.
//
extern DLLExport HMETAFILE _export WINAPI GetHMF (WORD PicRec,WORD PicId);
extern DLLExport void _export WINAPI DelHMF (HMETAFILE hMF);
extern DLLExport void _export WINAPI DelAllhMF (void);
