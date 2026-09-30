//---------------------------------------------------------------------------
// Formatieren von Zahlen
// $Header:   P:/marille/clinicum/dmwapi/rev/fint.cpv   1.0   08 Nov 1996 15:01:06   HANNES  $
// $Log:   P:/marille/clinicum/dmwapi/rev/fint.cpv  $
// 
//    Rev 1.0   08 Nov 1996 15:01:06   HANNES
// Initial revision.
// 
//    Rev 1.0   08 Nov 1996 13:28:54   HANNES
// Initial revision.
//---------------------------------------------------------------------------
#include <windows.h>
#include <stdio.h>
#include <string.h>

#include "dds32.h"
#define NODDSDATA
#include "dds.hpp"
#include "date.hpp"
#include "globmem.h"


BOOL FillIn (LPSTR res,int pos,char ch)
  {
  int j ;
  if ((j = lstrlen(res)) > pos) {
    res[j+1] = '\0' ;
    for ( int i = j ; i > j - pos ; i--)
      res [i] = res[i-1];
    res[i] = ch ;
    return TRUE ;
    }
  else
    return FALSE ;
  }

void InsChar (LPSTR res,char ch)
  {
  int j = lstrlen(res) ;
  res[j+1] = '\0' ;
  for ( int i = j ; i > 0 ; i--)
    res [i] = res[i-1];
  res[0] = ch ;
  }

DLLExport void _export WINAPI GetShortStr (LPSTR res,DBINT i)
  {
  wsprintf (res, "%d", int (i));
  }

DLLExport void _export WINAPI GetLongStr (LPSTR res,LONG m,BOOL withTousendPt)
  {
  char buffer[64];
  LONG mp ;
  if (m < 0) mp = -m ;
  else       mp = m ;
  wsprintf (buffer, "%ld", mp);
  if (withTousendPt)
    for (int i = 3 ; FillIn(buffer,i,'.') ; i += 4) ;
  lstrcpy (res,buffer);
  if (m < 0) InsChar (res,'-') ;
  }

DLLExport void _export WINAPI GetMoneyStr (LPSTR res,LONG m)
  {
  char buffer[64];
  LONG mp ;
  if (m < 0) mp = -m ;
  else       mp = m ;
  wsprintf (buffer, "%ld", mp);
  int len = lstrlen(buffer);
  if (FillIn (buffer,2,',')) {
    for (int i = 6 ; FillIn(buffer,i,'.') ; i += 4) ;
    lstrcpy (res,buffer);
    }
  else {
    res[0] = '0' ;
    res[1] = ',' ;
    if (len == 2)
      lstrcpy (res+2,buffer) ;
    else {
      res[2] = '0' ;
      res[3] = *buffer ;
      res[4] = '\0' ;
      }
    }
  if (m < 0) InsChar (res,'-') ;
  }

DLLExport BOOL _export WINAPI sclongint (LPSTR txt, long FAR *i)
  {
  double f = 0;

  *i = 0;
  BOOL error = (*txt == '\0') ;
  BOOL signFound = FALSE ;
  LONG sign = 1L ;
  for ( ; ((*txt) && (!error)) ; txt ++) {
    if ((*txt == '-') && (!signFound) && (*i == 0))
      sign = -1L , signFound = TRUE ;
    else if ((*txt == '+') && (!signFound) && (*i == 0))
      sign = +1L , signFound = TRUE ;
    else if ((*txt >= '0') && (*txt <= '9')) {

      double lastnum = f;
      
      f = f * 10 + double(int(*txt - '0'));
      
      if (f > 2147483647.0) {
        f = lastnum;
        MessageBeep (0);
        error = TRUE;
        break;
        }
      }
    else if (*txt != '.')
      error = TRUE ;
    }

  if (error)
    *i = 0;
  else
    *i = long(f);
  
  *i *= sign ;
  return !error;
  }

DLLExport BOOL _export WINAPI scmony (LPSTR txt, long FAR *i)
  {
  double f = 0;
  
  *i = 0;
  BOOL error = (*txt == '\0') ;
  BOOL signFound = FALSE ;
  LONG sign = 1L ;
  int anzDigitsAfter = -1;
  for ( ; ((*txt) && (!error)) ; txt ++) {
    if ((*txt == '-') && (!signFound) && (*i == 0))
      sign = -1L , signFound = TRUE ;
    else if ((*txt == '+') && (!signFound) && (*i == 0))
      sign = +1L , signFound = TRUE ;
    else if ((*txt == ',') && (anzDigitsAfter == -1))
      anzDigitsAfter = 0 ;
    else if ((*txt >= '0') && (*txt <= '9')) {
      if (anzDigitsAfter < 2) {

        double lastnum = f;
        
        f = f * 10 + double(int(*txt - '0'));

        double limit;
        if (anzDigitsAfter < 0)
          limit = 21474836.47;
        else if (anzDigitsAfter == 0)
          limit = 214748364.7;
        else
          limit = 2147483647;

        if ((f > limit) || (anzDigitsAfter > 2)) {
          f = lastnum;
          MessageBeep (0);
          error = TRUE;
          break;
          }
        }
        
      if (anzDigitsAfter >= 0) anzDigitsAfter ++ ;
      if (anzDigitsAfter > 2) error = TRUE ;
      }
    else if (*txt != '.')
      error = TRUE ;
    }

  if (error)
    *i = 0;
  else {
    *i = long(f);
    if (anzDigitsAfter <= 0) *i = *i * 100L ;
    if (anzDigitsAfter == 1) *i = *i * 10L ;
    }
  
  *i *= sign ;
  return !error;
  }

DLLExport BOOL _export WINAPI scint (LPSTR txt, int FAR *i)
  {
  double f = 0;
  
  *i = 0;
  BOOL error = (*txt == '\0') ;
  BOOL signFound = FALSE ;
  int sign = 1 ;
  for ( ; ((*txt) && (!error)) ; txt ++) {
    if ((*txt == '-') && (!signFound) && (*i == 0))
      sign = -1 , signFound = TRUE ;
    else if ((*txt == '+') && (!signFound) && (*i == 0))
      sign = +1 , signFound = TRUE ;
    else if ((*txt >= '0') && (*txt <= '9')) {
      double lastnum = f;
      
      f = f * 10 + double(int(*txt - '0'));
      
      if (f > 32767.0) {
        f = lastnum;
        MessageBeep (0);
        error = TRUE;
        break;
        }
      }
    else if (*txt != '.')
      error = TRUE ;
    }

  if (error)
    *i = 0;
  else
    *i = int(f);
  
  *i *= sign ;
  return !error;
  }

