// $Header:   P:/marille/clinicum/include/rev/test.hpv   1.1   02 Feb 1996 11:01:04   GERHOLD  $
// $Log:   P:/marille/clinicum/include/rev/test.hpv  $
// 
//    Rev 1.1   02 Feb 1996 11:01:04   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.0   24 Jun 1994 17:02:06   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.0   02 Dec 1992 16:06:30   HANNES
// Initial revision.
#ifndef TEST_INCLUDED

#define TEST_INCLUDED
//#define PROTOKOLL
//
//      TestUtility
//      Es werden Einige Varialen zum einfachen Einbau
//      von Testausgaben zur Verfuegung gestellt
//

class tUtil {
 public :
  static OFSTRUCT Of ;
  static HANDLE fd;
  static char FileName[50];
  void setfilename(char *);
  void close(void);
  tUtil& operator << (char FAR *);
  tUtil& operator << (WORD);
  tUtil& operator << (int);
  tUtil& operator << (LONG);
  };

#ifdef TEST_MAIN

OFSTRUCT tUtil::Of ;
HANDLE tUtil::fd = 0;
char tUtil::FileName[50];

#endif
#ifdef PROTOKOLL
#ifdef TEST_MAIN
tUtil tp;

#else
extern tUtil tp;
#endif
#endif


#endif

