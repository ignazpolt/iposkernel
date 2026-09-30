// $Header:   P:/marille/clinicum/include/rev/winass.hpv   1.4   05 Feb 1999 21:38:02   Martin  $
// $Log:   P:/marille/clinicum/include/rev/winass.hpv  $
// 
//    Rev 1.4   05 Feb 1999 21:38:02   Martin
// verbessertes Errorhandling
// 
//    Rev 1.3   02 Feb 1996 11:00:16   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.2   24 Aug 1995 00:12:18   HANNES
// Debuggerverbesserun
// 
//    Rev 1.1   09 Dec 1994 14:27:28   HANNES
// 
//    Rev 1.0   24 Jun 1994 17:01:24   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.2   11 Oct 1993 11:43:32   HANNES
// Erweiterung um WIN_ASSERT_TEXT
// 
//    Rev 1.1   17 Aug 1993 11:50:36   MARTIN
// win_ass_failed in DLL ausgelagert
// 
//    Rev 1.0   20 Jan 1993 16:02:14   MARTIN
// Initial revision.

extern DLLExport void _export WINAPI win_ass_failed      (int modnum, int line);
extern DLLExport void _export WINAPI win_ass_failed_text (int modnum, int line, LPSTR text);
extern DLLExport void _export WINAPI dbwin_ass_failed      (int modnum, int line);
extern DLLExport void _export WINAPI dbwin_ass_failed_text (int modnum, int line, LPSTR text);
extern DLLExport LPSTR _export WINAPI ModName (int modnum);

#ifdef NICHT_AUF_JEDEN_FALL_DBWIN_ASSERT
#define WIN_ASSERT(cond) { if (!(cond)) win_ass_failed(MODULENUM, __LINE__); }
#define WIN_ASSERT_TEXT(cond,text) { if (!(cond)) win_ass_failed_text(MODULENUM, __LINE__, text); }
#endif
#define WIN_ASSERT(cond) { if (!(cond)) dbwin_ass_failed(MODULENUM, __LINE__); }
#define WIN_ASSERT_TEXT(cond,text) { if (!(cond)) dbwin_ass_failed_text(MODULENUM, __LINE__, text); }
#define DBWIN_ASSERT(cond) { if (!(cond)) dbwin_ass_failed(MODULENUM, __LINE__); }
#define DBWIN_ASSERT_TEXT(cond,text) { if (!(cond)) dbwin_ass_failed_text(MODULENUM, __LINE__, text); }

