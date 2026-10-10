///////////////////////////////////////////////////////////////////////
//  Konvertierungsfunktionen beim Arbeiten mit Btrieve - Datenbanken
///////////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/dbbtrv/rev/dcbtrv.cpv   1.35   10 Jan 2000 10:14:24   Hannes  $
//  $Log:   P:/marille/clinicum/dbbtrv/rev/dcbtrv.cpv  $
// 
//    Rev 1.35   10 Jan 2000 10:14:24   Hannes
// 
//    Rev 1.34   21 Aug 1998 10:44:26   Hannes
// Timestamp die 25.
// 
//    Rev 1.33   10 Aug 1998 17:03:40   Hannes
// Umstellen des Timestamps auf UNSIGNED
// 
//    Rev 1.32   04 Aug 1998 17:55:34   Hannes
// Timestamp
// 
//    Rev 1.31   06 Feb 1998 07:58:28   Hannes
// Shorts ... Benutzung als binaere Daten, wenn groesse groesser als 4! ist
// 
//    Rev 1.30   04 Dec 1996 11:18:14   HANNES
// zusaetzliche Absicherung im Block - Teil
// 
//    Rev 1.29   02 Dec 1996 12:35:14   HANNES
// Fehlerkorrekturen
// 
//    Rev 1.28   26 Nov 1996 08:00:12   HANNES
// Automatischer Update
// 
//    Rev 1.27   08 Nov 1996 13:26:46   HANNES
// QLong, Replikator
// 
//    Rev 1.26   03 Sep 1996 10:05:18   HANNES
// Konvertierungsfunktion fuer Short
// 
//    Rev 1.25   17 Jun 1996 15:38:28   HANNES
// Einbau von BLOBS
// 
//    Rev 1.24   22 May 1996 12:12:04   MARTIN
// SetMinShort bzw. SetMinLong jenachdem, ob AUTOINC oder nicht
// 
//    Rev 1.23   02 Feb 1996 10:42:34   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.22   22 Sep 1995 15:44:04   MARTIN
// Setmins von Datum und Zeit korrigiert
// 
//    Rev 1.21   17 Sep 1995 18:03:18   MARTIN
// Time-NULL-Value auf 0/0/0/0 geaendert
// 
//    Rev 1.20   12 Sep 1995 09:45:00   HANNES
// Nullvalue des Datums
// 
//    Rev 1.19   12 Apr 1995 12:27:50   HANNES
// 
//    Rev 1.18   02 Mar 1995 16:40:12   GERHOLD
// 
//    Rev 1.17   24 Feb 1995 11:14:34   HANNES
//  
// 
//    Rev 1.16   16 Feb 1995 12:46:20   HANNES
// Erweiterung um SQL-Faehigkeiten
// 
//    Rev 1.15   31 Jan 1995 15:38:36   HANNES
// 
//    Rev 1.14   24 Jan 1995 10:58:58   HANNES
// Schluesseldefinition in das Clientdictionary mit aufegenommen
// 
//    Rev 1.13   10 Jan 1995 17:28:10   HANNES
// Syntaxkorrektur fuer 8er Compiler
// 
//    Rev 1.12   15 Dec 1994 18:37:46   HANNES
// 
//    Rev 1.11   07 Dec 1994 14:21:16   GERHOLD
// alle Umwandlungen von *(DWORD(xxx)) -> *(DWORD)xxx  etc.
// 
//    Rev 1.10   16 Nov 1994 12:52:18   HANNES
// Initialisierung von Private
// 
//    Rev 1.9   07 Nov 1994 11:42:58   HANNES
// Hundertstel sekunden
// 
//    Rev 1.8   31 Oct 1994 16:39:14   joerg
// lstrncpy in SetString umgebaut
// 
//    Rev 1.7   31 Oct 1994 10:36:56   hannes
// Initialize verbessert
// 
//    Rev 1.6   17 Oct 1994 14:56:26   HANNES
// Nullvalue - Handling fuer Punkte
// 
//    Rev 1.5   20 Sep 1994 11:22:32   HANNES
// 
//    Rev 1.4   24 Aug 1994 19:41:18   HANNES
// Kleine Fehler bei BDT_STRING
// 
//    Rev 1.3   10 Aug 1994 12:07:44   HANNES
// Time Eingebaut
// 
//    Rev 1.2   05 Aug 1994 17:08:10   HANNES
// 
//    Rev 1.1   17 Jul 1994 14:38:34   HANNES
// Umorganisation der Primaerschluesselvergabe
// 
//    Rev 1.0   24 Jun 1994 16:43:22   HANNES
// Neuuebernahme clinicum
#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#include "globmem.h"
#define NODDSDATA
#include "dds.hpp"
#include "tbbtrv.hpp"
#define MODULENUM 84
#include "winass.hpp"
#include "btrieve.hpp"
#include "hash.hpp"
#include "compile.hpp"

static char convbuffer[2048];
float fbuffer;
typedef LPVOID (* GETFNC) (LPVOID data,WORD dataSize,WORD dataType,WORD FAR *rSize);
typedef void   (* SETFNC) (LPVOID res,WORD rSize,WORD dataType,LPVOID data,WORD dataSize);
typedef void   (* INIFNC) (LPVOID res,WORD rSize,WORD dataType);

LPVOID GetFloats (LPVOID data,WORD dataSize,WORD dataType,WORD FAR *rSize)
  {
  switch (dataType) {
    case BDT_FLOAT :
      *rSize = dataSize;
      return (*((float FAR *) data) <= 1.0E10) ? data : LPVOID(NULL) ;
    case DT_PRIVATE :
      if (dataSize == 8) {
        *rSize = 8;
        return (*((float FAR *) data) <= 1.0E10) ? data : LPVOID(NULL) ;
        }
      else
        WIN_ASSERT (FALSE);
      break ;
    case BDT_UNSIGNED :
      if (dataSize == 2) {
        if (* ((WORD FAR *) data) != 0xFFFF) {
          *rSize = sizeof(float);
          fbuffer = float( * ((WORD FAR *) data));
          return &fbuffer;
          }
        else 
          return NULL ;
        }
      if (dataSize == 4) {
        if (* ((DWORD FAR *) data) != 0xFFFFFFFF) {
          *rSize = sizeof(float);
          fbuffer = float( * ((DWORD FAR *) data));
          return &fbuffer;
          }
        else
          return NULL;
        }
      WIN_ASSERT(FALSE);
      return NULL;
    case BDT_INTEGER :
      if (dataSize == 2) {
        if ( * ((short FAR *) data) != 0x8000) {
          *rSize = sizeof(float);
          fbuffer = float( * ((short FAR *) data));
          return &fbuffer;
          }
        else
          return NULL;
        }
      if (dataSize == 4) {
        if (* ((LONG FAR *) data) != 0x80000000) {
          *rSize = sizeof(float);
          fbuffer = float( * ((LONG FAR *) data));
          return &fbuffer;
          }
        else
          return NULL;
        }
      WIN_ASSERT(FALSE);
    default :
      WIN_ASSERT(FALSE);
    }
  return NULL;
  }
void SetFloats (LPVOID res,WORD rSize,WORD dataType,LPVOID data,WORD dataSize)
  {
  if (data != NULL) {
    float f = *((float FAR *) data);
    switch (dataType) {
      case BDT_FLOAT :
        *((float FAR *) res) = f;
        break ;
      case BDT_UNSIGNED :
        if (rSize == 2) {
          *((WORD FAR *) res) = WORD(f);
          break ;
          }
        if (rSize == 4) {
          *((DWORD FAR *) res) = DWORD(f);
          break ;
          }
        WIN_ASSERT (FALSE);
      case BDT_INTEGER :
        if (rSize == 2) {
          *((short FAR *) res) = short (f);
          break ;
          }
        if (rSize == 4) {
          *((LONG FAR *) res) = LONG(f);
          break ;
          }
        WIN_ASSERT (FALSE);
        break ;
      case DT_PRIVATE :
        WIN_ASSERT (rSize == 8);
        WIN_ASSERT (dataSize == 8);
        lmemcpy (res,data,rSize);
        break ;
      default :
        WIN_ASSERT (FALSE);
      }
    }
  else {
    switch (dataType) {
      case BDT_FLOAT :
        *((float FAR *) res) = float(1.0E11);
        break ;
      case BDT_UNSIGNED :
        if (rSize == 2) {
          *((WORD FAR *) res )= 0xFFFF;
          break ;
          }
        if (rSize == 4) {
          *((DWORD FAR *) res) = 0xFFFFFFFF;
          break ;
          }
        WIN_ASSERT (FALSE);
      case BDT_INTEGER :
        if (rSize == 2) {
          *((int FAR *) res) = 0x8000;
          break ;
          }
        if (rSize == 4) {
          *((LONG FAR *) res) = 0x80000000;
          break ;
          }
        WIN_ASSERT (FALSE);
        break ;
      case DT_PRIVATE :
        *((float FAR *) res) = float(1.0E11);
        break ;
      default :
        WIN_ASSERT (FALSE);
      }
    }
  }
void IniFloats (LPVOID res,WORD rSize,WORD dataType)
  {
  switch (dataType) {
    case BDT_FLOAT :
      *((float FAR *) res) = float(1.0E11);
      break ;
    case BDT_UNSIGNED :
      if (rSize == 2) {
        *((WORD FAR *)res) = 0xFFFF;
        break ;
        }
      if (rSize == 4) {
        *((DWORD FAR *)res) = 0xFFFFFFFF;
        break ;
        }
      WIN_ASSERT (FALSE);
    case BDT_INTEGER :
      if (rSize == 2) {
        *((short FAR *)res) = short(0x8000);
        break ;
        }
      if (rSize == 4) {
        *((LONG FAR *)res) = 0x80000000;
        break ;
        }
      WIN_ASSERT (FALSE);
    case DT_PRIVATE :
      WIN_ASSERT (rSize == 8);
      *((float FAR *) res) = float(1.0E11) ;
      break ;
    }
  }
void SetFloatMin (LPVOID res,WORD rSize,WORD dataType)
  {
  switch (dataType) {
    case BDT_FLOAT :
      *((float FAR *) res) = float(-1.0E20);
      break ;
    case BDT_UNSIGNED :
      if (rSize == 2) {
        *((WORD FAR *)res) = 0;
        break ;
        }
      if (rSize == 4) {
        *((DWORD FAR *)res) = 0;
        break ;
        }
      WIN_ASSERT (FALSE);
    case BDT_INTEGER :
      if (rSize == 2) {
        *((short FAR *)res) = short(0x8000);
        break ;
        }
      if (rSize == 4) {
        *((LONG FAR *)res) = 0x80000000;
        break ;
        }
      WIN_ASSERT (FALSE);
    }
  }
void SetFloatMax (LPVOID res,WORD rSize,WORD dataType)
  {
  switch (dataType) {
    case BDT_FLOAT :
      *((float FAR *) res) = float(1.0E20);
      break ;
    case BDT_UNSIGNED :
      if (rSize == 2) {
        *((WORD FAR *)res) = 0xFFFF;
        break ;
        }
      if (rSize == 4) {
        *((DWORD FAR *)res) = 0xFFFFFFFF;
        break ;
        }
      WIN_ASSERT (FALSE);
    case BDT_INTEGER :
      if (rSize == 2) {
        *((short FAR *)res) = 0x7FFF;
        break ;
        }
      if (rSize == 4) {
        *((LONG FAR *)res) = 0x7FFFFFFF;
        break ;
        }
      WIN_ASSERT (FALSE);
    }
  }

LPVOID GetPrivate (LPVOID data,WORD dataSize,WORD dataType,WORD FAR *rSize)
  {
  switch (dataType) {
    case DT_SPRIVATE :
      *rSize = *(LPWORD)data;
      if (*rSize == 0xFFFF) *rSize = 0;
      return (*rSize) ? (LPSTR(data) + sizeof(WORD)) : LPVOID(NULL);
    default :
      {
      BOOL isSet = FALSE ;
      for (WORD i = 0 ; ((i < dataSize) && (!isSet)) ; i++) {
        if (((LPSTR)data)[i] != 0xFF) isSet = TRUE ;
        }
      if (isSet) {
        *rSize = dataSize;
        return data;
        }
      else {
        *rSize = 0;
        return NULL;
        }
      }
    }
  return NULL;
  }
void SetPrivate (LPVOID res,WORD rSize,WORD dataType,LPVOID data,WORD dataSize)
  {
  switch (dataType) {
    case DT_PRIVATE :
      if (data != NULL) {
        WORD size = min(rSize,dataSize);
        lmemcpy (res,data,size);
        if (size < rSize)
          lmemset (LPSTR(res)+size,'\0',rSize-size);
        }
      else {
        for (WORD i = 0 ; i < rSize ; i++) 
          ((BYTE FAR *)res)[i] = 0xFF ;
        }
      break;
    case DT_SPRIVATE :
      if (data != NULL) {
        BOOL doSetNULL = FALSE;
        if (dataSize > rSize - sizeof(WORD) - 1) {
          dataSize = rSize - sizeof(WORD);
          doSetNULL = TRUE ;
          }
        lmemcpy (LPSTR(res)+sizeof(WORD),data,dataSize);
        *(LPWORD)res = dataSize;
        if (doSetNULL) {
          (LPSTR(res)+sizeof(WORD))[dataSize-1] = '\0';
          }
        }
      else
        *(LPWORD)res = 0;
      break;
    case BDT_UNSIGNED :
      if (data != NULL) {
        WIN_ASSERT(dataSize >= rSize);
        lmemcpy (LPSTR(res),data,rSize);
        }
      else
        lmemset(res,'\0',sizeof(res));
      break;
    }
  }
void IniPrivate (LPVOID res,WORD rSize,WORD dataType)
  {
  WORD i ;
  switch (dataType) {
    case DT_PRIVATE :
      for (i = 0 ; i < rSize ; i++) 
        ((BYTE FAR *)res)[i] = 0xFF ;
      break ;
    case DT_SPRIVATE :
      lmemset (res,'\0',rSize);
      break ;
    }
  }
void SetPrivateMin (LPVOID res,WORD rSize,WORD dataType)
  {
  lmemset (res,'\0',rSize);
  }
void SetPrivateMax (LPVOID res,WORD rSize,WORD dataType)
  {
  lmemset (res,0xFF,rSize);
  }
BOOL spacePadd;
LPVOID GetString (LPVOID data,WORD dataSize,WORD dataType,WORD FAR *rSize)
  {
  switch (dataType) {
    case BDT_ZSTRING :
      if (spacePadd) {
        // Spezialbehandlung fuer XFile...
        lmemcpy (convbuffer,data,dataSize);
        convbuffer[dataSize] = '\0' ;
        *rSize = dataSize ;
        return convbuffer ;
        }
    case DT_SPRIVATE :
      *rSize = lstrlen(LPSTR(data))+1;
      return (*rSize > 1) ? data : NULL ;
    case DT_LDSTRING :
    case BDT_LSTRING :
      lmemcpy (convbuffer,LPSTR(data)+1,BYTE(*(LPSTR(data))));
      convbuffer[*((LPSTR)data)] = '\0';
      if (dataType == DT_LDSTRING)
        OemToAnsi (convbuffer,convbuffer);
      *rSize = lstrlen(convbuffer)+1;
      return (*rSize > 1) ? convbuffer : LPVOID(NULL);
    case BDT_STRING :
      {
      LPSTR h = LPSTR(data);
      for (WORD i = 0 ; i < dataSize ; i++) {
        if (*h) convbuffer[i] = *h++;
        else    convbuffer[i] = '\0';
        }
      convbuffer[i] = '\0';
      *rSize = lstrlen(convbuffer)+1;
      }
      return convbuffer;
      break ;
    default :
      WIN_ASSERT(FALSE);
    }
  return NULL;
  }

void PaddString (LPSTR res,WORD rSize)
  {
  BOOL doPadd = FALSE ;
  for (WORD i = 0 ; i < rSize ; i++) {
    if (doPadd) *res ++ = ' ' ;
    else {
      if (*res == '\0') *res ++ = ' ' ;
      else              res ++ ;
      }
    }
  }
void SetString (LPVOID res,WORD rSize,WORD dataType,LPVOID data,WORD dataSize)
  {
  switch (dataType) {
    case BDT_ZSTRING :
    case DT_SPRIVATE :
      lmemset (res,'\0',rSize);
      if (data != NULL) {
        if (spacePadd) {
          int len = lstrlen (LPSTR(data)) ;
          if (len >= int(dataSize))
            lmemcpy (LPSTR(res),LPSTR(data),dataSize);
          else {
            lstrcpy (LPSTR(res),LPSTR(data));
            PaddString (LPSTR(res),rSize);
            }
          }
        else
          lstrncpy (LPSTR(res),LPSTR(data),rSize-1);
        }
      break ;
    case DT_LDSTRING :
    case BDT_LSTRING :
      if (data != NULL) {
        WIN_ASSERT (rSize < sizeof(convbuffer));
        WORD s = lstrlen(LPSTR(data));
        WIN_ASSERT (s + 2 < sizeof(convbuffer));
        lstrcpy (convbuffer+1,LPSTR(data));
        if (dataType == DT_LDSTRING)
          AnsiToOem (convbuffer+1,convbuffer+1);
        if (s > rSize - 1) s = rSize - 1;
        *convbuffer = char(s);
        if (s + 1 < rSize)
          lmemset (convbuffer + s + 1,'\0',rSize - s);
        lmemcpy (res,convbuffer,rSize);
        }
      else
        lmemset (res,'\0',rSize);
      break ;
    case BDT_STRING :
      {
      LPSTR h = LPSTR(data);
      for (WORD i = 0 ; i < rSize ; i++) {
        if (*h) ((LPSTR)res)[i] = *h++;
        else    ((LPSTR)res)[i] = '\0';
        }
      }
      break ;
    default :
      WIN_ASSERT(FALSE);
    }
  }
void IniString (LPVOID res,WORD rSize,WORD dataType)
  {
  lmemset (res,'\0',rSize);
  }
void SetStringMin (LPVOID res,WORD rSize,WORD dataType)
  {
  lmemset (res,'\0',rSize);
  }
void SetStringMax (LPVOID res,WORD rSize,WORD dataType)
  {
  lmemset (res,0xFF,rSize-1);
  ((char FAR *) (res))[rSize-1] = '\0';
  }

LPVOID GetCont (LPVOID data,WORD dataSize,WORD dataType,WORD FAR *rSize)
  {
  *rSize = *(LPWORD)data;
  return (*rSize) ? (LPVOID (LPSTR(data) + sizeof(WORD))) : LPVOID(NULL);
  }
void SetCont (LPVOID res,WORD rSize,WORD dataType,LPVOID data,WORD dataSize)
  {
  lmemset (res,'\0',rSize);
  if (data != NULL) {
    WIN_ASSERT (rSize >= dataSize + sizeof(WORD));
    *((LPWORD)res) = dataSize;
    lmemcpy (LPSTR(res)+sizeof(WORD),data,dataSize);
    }
  }
void IniCont (LPVOID res,WORD rSize,WORD dataType)
  {
  lmemset (res,'\0',rSize);
  }

LPVOID GetShort (LPVOID data,WORD dataSize,WORD dataType,WORD FAR *rSize)
  {
  if ((dataSize >= 2) && (dataSize <= 4)) {
    *rSize = 2;
    return (*(LPWORD (data)) != 0xFFFF) ? data : LPVOID(NULL) ;
    }
  else if (dataSize > 4) {
    *rSize = dataSize;
    return data;
    }
  else {
    convbuffer[0] = *LPSTR(data);
    convbuffer[1] = '\0';
    *rSize = 2;
    return (convbuffer[0] != 0xFF) ? convbuffer : LPVOID(NULL) ;
    }
  }
void SetShort (LPVOID res,WORD rSize,WORD dataType,LPVOID data,WORD dataSize)
  {
  if (data != NULL)
    *((LPWORD)res) = WORD ((dataSize >= 2) ? *(LPWORD(data)) : *(LPSTR(data)));
  else
    *((LPWORD)res) = 0xFFFF;
  }
void IniShort (LPVOID res,WORD rSize,WORD dataType)
  {
  *((LPWORD)res) = 0xFFFF;
  }
void SetShortMin (LPVOID res,WORD rSize,WORD dataType)
  {
  if (dataType == BDT_AUTOINC)
    *((LPWORD)res) = 0x0000;
  else
    *((LPWORD)res) = 0x8000;
  }
void SetShortMax (LPVOID res,WORD rSize,WORD dataType)
  {
  *((LPWORD)res) = 0x7FFF;
  }

LPVOID GetLong (LPVOID data,WORD dataSize,WORD dataType,WORD FAR *rSize)
  {
  *rSize = 4;
  if (dataSize >= 4) {
    return (*(LPDWORD (data)) != 0x80000000) ? data : LPVOID(NULL) ;
    }
  else {
    lmemset (convbuffer,'\0',4);
    lmemcpy (convbuffer,data,dataSize);
    return (convbuffer);
    }
  }
void SetLong (LPVOID res,WORD rSize,WORD dataType,LPVOID data,WORD dataSize)
  {
  if (data != NULL) {
    WORD s = min(rSize,dataSize);
    lmemcpy (res,data,s);
    if (s < rSize)
      lmemset (LPSTR(res)+s,'\0',rSize-s);
    }
  else {
    if (rSize == 2)
      *((LPWORD)res) = 0x8000;
    else if (rSize == 4)
      *((LPDWORD)res) = 0x80000000;
    else if (rSize == 1)
      *((LPDWORD)res) = 0x80;
    else
      WIN_ASSERT (FALSE);
    }
  }
void IniLong (LPVOID res,WORD rSize,WORD dataType)
  {
  if (rSize == 4)
    *((LPDWORD)res) = 0x80000000;
  else if (rSize == 2)
    *((LPWORD)res) = 0x8000;
  else
    WIN_ASSERT(FALSE);
  }
void IniBlob (LPVOID res,WORD rSize,WORD dataType)
  {
  if (rSize == 4)
    *((LPDWORD)res) = 0;
  else
    WIN_ASSERT(FALSE);
  }
void SetLongMin (LPVOID res,WORD rSize,WORD dataType)
  {
  if (rSize == 4) {
    if (dataType == BDT_AUTOINC)
      *((LPDWORD)res) = 0x00000000;
    else
      *((LPDWORD)res) = 0x80000000;
    }
  else if (rSize == 2) {
    if (dataType == BDT_AUTOINC)
      *((LPWORD)res) = 0x0000;
    else
      *((LPWORD)res) = 0x8000;
    }
  else if (rSize == 1) {
    *((BYTE FAR *)res) = 0x80;
    }
  else
    WIN_ASSERT(FALSE);
  }
void SetLongMax (LPVOID res,WORD rSize,WORD dataType)
  {
  if (rSize == 4)
    *((LPDWORD)res) = 0x7FFFFFFF;
  else if (rSize == 2)
    *((LPWORD)res) = 0x7FFF;
  else if (rSize == 1)
    *((BYTE FAR *)res) = 0x7F;
  else
    WIN_ASSERT(FALSE);
  }
LPVOID GetQLong (LPVOID data,WORD dataSize,WORD dataType,WORD FAR *rSize)
  {
  switch (dataType) {
    case DT_PRIVATE :
      if (dataSize == 10) {
        *rSize = 10;
        return (*((long double FAR *) data) < 1.0E99) ? data : LPVOID(NULL) ;
        }
      else
        WIN_ASSERT (FALSE);
      break ;
    default :
      WIN_ASSERT(FALSE);
    }
  return NULL;
  }
void SetQLong (LPVOID res,WORD rSize,WORD dataType,LPVOID data,WORD dataSize)
  {
  switch (dataType) {
    case DT_PRIVATE :
      WIN_ASSERT (dataSize == 10);
      if (data != NULL)
        lmemcpy (res,data,dataSize);
      else
        * (long double FAR *) res = (long double) 1.0E100 ;
      break ;
    default :
      WIN_ASSERT(FALSE);
    }
  }
void IniQLong (LPVOID res,WORD rSize,WORD dataType)
  {
  switch (dataType) {
    case DT_PRIVATE :
      * (long double FAR *) res = (long double) 1.0E100 ;
      break ;
    }
  }
void SetQLongMin (LPVOID res,WORD rSize,WORD dataType)
  {
  switch (dataType) {
    case DT_PRIVATE :
      * (long double FAR *) res = (long double) -1.0E99 ;
      break ;
    }
  }
void SetQLongMax (LPVOID res,WORD rSize,WORD dataType)
  {
  switch (dataType) {
    case DT_PRIVATE :
      * (long double FAR *) res = (long double) 1.0E99 ;
      break ;
    }
  }

LPVOID GetDWord (LPVOID data,WORD dataSize,WORD dataType,WORD FAR *rSize)
  {
  *rSize = 4;
  if (dataSize >= 4) {
    return (*(LPDWORD (data)) != 0xFFFFFFFF) ? data : LPVOID(NULL) ;
    }
  else {
    lmemset (convbuffer,'\0',4);
    lmemcpy (convbuffer,data,dataSize);
    return (convbuffer);
    }
  }
void IniDWord (LPVOID res,WORD rSize,WORD dataType)
  {
  if (rSize == 4)
    *((LPDWORD)res) = 0xFFFFFFFF;
  else if (rSize == 2)
    *((LPWORD)res) = 0xFFFF;
  else
    WIN_ASSERT(FALSE);
  }
void SetDWord (LPVOID res,WORD rSize,WORD dataType,LPVOID data,WORD dataSize)
  {
  if (data != NULL) {
    WORD s = min(rSize,dataSize);
    lmemcpy (res,data,s);
    if (s < rSize)
      lmemset (LPSTR(res)+s,'\0',rSize-s);
    }
  else 
    IniDWord (res,rSize,dataType);
  }
void SetDWordMin (LPVOID res,WORD rSize,WORD dataType)
  {
  if (rSize == 4)
    *((LPDWORD)res) = 0;
  else if (rSize == 2)
    *((LPWORD)res) = 0;
  else
    WIN_ASSERT(FALSE);
  }
void SetDWordMax (LPVOID res,WORD rSize,WORD dataType)
  {
  if (rSize == 4)
    *((LPDWORD)res) = 0xFFFFFFFF;
  else if (rSize == 2)
    *((LPWORD)res) = 0xFFFF;
  else
    WIN_ASSERT(FALSE);
  }

#pragma pack(1)
  struct bdt { BYTE day ; BYTE month ; WORD year ; } ;
#pragma pack()
LPVOID GetDate (LPVOID data,WORD dataSize,WORD dataType,WORD FAR *rSize)
  {
  packdate FAR *pd = (packdate FAR *) convbuffer;
  *rSize = sizeof(*pd);
  switch (dataType) {
    case BDT_DATE :
      if ((((bdt FAR *) data)->year != 0xFFFF) && 
          (!((((bdt FAR *) data)->year == 0) &&
             (((bdt FAR *) data)->month == 0) && 
             (((bdt FAR *) data)->day == 0)))) {
        pd->day   = ((bdt FAR *) data)->day;
        pd->month = ((bdt FAR *) data)->month;
        pd->year  = ((bdt FAR *) data)->year;
        return convbuffer;
        }
      else
        return NULL;
    case DT_KLDATE :
      if (*((LONG FAR *) data) != 0x80000000) {
        UnPackTime (*((LONG FAR *) data),pd);
        return convbuffer;
        }
      else
        return NULL;
    }
  return NULL;
  }
void SetDate (LPVOID res,WORD rSize,WORD dataType,LPVOID data,WORD dataSize)
  {
  packdate FAR *pd = (packdate FAR *) data;
  switch (dataType) {
    case BDT_DATE :
    case DT_PRIVATE :
      if (pd != NULL) {
        ((bdt FAR *) res)->day   = pd->day   ; 
        ((bdt FAR *) res)->month = pd->month ; 
        ((bdt FAR *) res)->year  = pd->year  ;
        }
      else {
        ((bdt FAR *) res)->day   = 0 ;
        ((bdt FAR *) res)->month = 0 ;
        ((bdt FAR *) res)->year  = 0 ;
        }
      break ;
    case DT_KLDATE :
      if (pd != NULL)
        *((LONG FAR *) res) = PackTime (pd);
      else
        *((LONG FAR *) res) = 0x80000000;
      break;
    default :
      WIN_ASSERT(FALSE);
    }
  }
void IniDate (LPVOID res,WORD rSize,WORD dataType)
  {
  switch (dataType) {
    case BDT_DATE :
      ((bdt FAR *) res)->day   = 0 ; 
      ((bdt FAR *) res)->month = 0 ; 
      ((bdt FAR *) res)->year  = 0 ;
      break ;
    case DT_KLDATE :
      *((LONG FAR *) res) = 0x80000000;
      break ;
    }
  }
void SetDateMin (LPVOID res,WORD rSize,WORD dataType)
  {
  switch (dataType) {
    case BDT_DATE :
      ((bdt FAR *) res)->day   = 0   ;    // frueher 1 !!!!
      ((bdt FAR *) res)->month = 0   ; 
      ((bdt FAR *) res)->year  = 0x0000 ;
      break ;
    case DT_KLDATE :
      *((LONG FAR *) res) = 0x80000000;
      break ;
    }
  }
void SetDateMax (LPVOID res,WORD rSize,WORD dataType)
  {
  switch (dataType) {
    case BDT_DATE :
      ((bdt FAR *) res)->day   = 0   ; 
      ((bdt FAR *) res)->month = 0   ; 
      ((bdt FAR *) res)->year  = 0x7FFF ;
      break ;
    case DT_KLDATE :
      *((LONG FAR *) res) = 0x7FFFFFFF;
      break ;
    }
  }
struct btime { BYTE hundred_second ; BYTE second ; BYTE minute ; BYTE hour ; } ;
LPVOID GetTime (LPVOID data,WORD dataSize,WORD dataType,WORD FAR *rSize)
  {
  packtime FAR *pt = (packtime FAR *) convbuffer;
  *rSize = sizeof(*pt);
  switch (dataType) {
    case BDT_TIME :
      if ((((btime FAR *) data)->hour != 0xFF) &&
          (!((((btime FAR *) data)->hour == 0) &&
             (((btime FAR *) data)->minute == 0) &&
             (((btime FAR *) data)->second == 0) &&
             (((btime FAR *) data)->hundred_second == 0)))) {
        pt->hour           = ((btime FAR *) data)->hour;
        pt->minute         = ((btime FAR *) data)->minute;
        pt->second         = ((btime FAR *) data)->second;
        pt->hundred_second = 0;
        return convbuffer;
        }
      else
        return NULL;
      break ;
    default :
      WIN_ASSERT(FALSE);
      return NULL ;
    }
  return NULL;
  }
void SetTime (LPVOID res,WORD rSize,WORD dataType,LPVOID data,WORD dataSize)
  {
  packtime FAR *pt = (packtime FAR *) data;
  switch (dataType) {
    case BDT_TIME :
    case DT_PRIVATE :
      if ((pt != NULL) && (pt->hour != 0xFF)) {
        ((btime FAR *) res)->hour           = pt->hour           ;
        ((btime FAR *) res)->minute         = pt->minute         ;
        ((btime FAR *) res)->second         = pt->second         ;
        if ((((btime FAR *) res)->hour == 0) &&
            (((btime FAR *) res)->minute == 0) &&
            (((btime FAR *) res)->second == 0))
          ((btime FAR *) res)->hundred_second = 1;
        else
          ((btime FAR *) res)->hundred_second = 0;
        }
      else {
        ((btime FAR *) res)->hour           = 0 ;
        ((btime FAR *) res)->minute         = 0 ;
        ((btime FAR *) res)->second         = 0 ;
        ((btime FAR *) res)->hundred_second = 0 ;
        }
      break ;
    default :
      WIN_ASSERT(FALSE);
    }
  }
void IniTime (LPVOID res,WORD rSize,WORD dataType)
  {
  switch (dataType) {
    case BDT_TIME :
      ((btime FAR *) res)->hour           = 0 ;
      ((btime FAR *) res)->minute         = 0 ;
      ((btime FAR *) res)->second         = 0 ;
      ((btime FAR *) res)->hundred_second = 0 ;
      break ;
    }
  }
void SetTimeMin (LPVOID res,WORD rSize,WORD dataType)
  {
  switch (dataType) {
    case BDT_TIME :
      ((btime FAR *) res)->hour           = 0 ;
      ((btime FAR *) res)->minute         = 0 ;
      ((btime FAR *) res)->second         = 0 ;
      ((btime FAR *) res)->hundred_second = 0 ;
      break ;
    }
  }
void SetTimeMax (LPVOID res,WORD rSize,WORD dataType)
  {
  switch (dataType) {
    case BDT_TIME :
      ((btime FAR *) res)->hour           = 23 ;
      ((btime FAR *) res)->minute         = 59 ;
      ((btime FAR *) res)->second         = 59 ;
      ((btime FAR *) res)->hundred_second = 99 ;
      break ;
    }
  }

void SetDateTimeMax (LPVOID res,WORD rSize,WORD dataType)
  {
  ((bdt FAR *) (LPSTR(res) + sizeof(btime)))->day   = 0   ; 
  ((bdt FAR *) (LPSTR(res) + sizeof(btime)))->month = 0   ; 
  ((bdt FAR *) (LPSTR(res) + sizeof(btime)))->year  = 0x7FFF ;
  ((btime FAR *) res)->hour           = 23 ;
  ((btime FAR *) res)->minute         = 59 ;
  ((btime FAR *) res)->second         = 59 ;
  ((btime FAR *) res)->hundred_second = 99 ;
  }

void SetDateTimeMin (LPVOID res,WORD rSize,WORD dataType)
  {
  ((bdt FAR *) (LPSTR(res) + sizeof(btime)))->day   = 0   ; 
  ((bdt FAR *) (LPSTR(res) + sizeof(btime)))->month = 0   ; 
  ((bdt FAR *) (LPSTR(res) + sizeof(btime)))->year  = 0 ;
  ((btime FAR *) res)->hour           = 0 ;
  ((btime FAR *) res)->minute         = 0 ;
  ((btime FAR *) res)->second         = 0 ;
  ((btime FAR *) res)->hundred_second = 0 ;
  }

void IniDateTime (LPVOID res,WORD rSize,WORD dataType)
  {
  SetDateTimeMin (res,rSize,dataType);
  }

void SetDateTime (LPVOID res,WORD rSize,WORD dataType,LPVOID data,WORD dataSize)
  {
  packdatetime FAR *pdt = (packdatetime FAR *) data;
  if (pdt != NULL) {
    ((bdt FAR *) (LPSTR(res) + sizeof(btime)))->day   = pdt->pd.day   ; 
    ((bdt FAR *) (LPSTR(res) + sizeof(btime)))->month = pdt->pd.month ; 
    ((bdt FAR *) (LPSTR(res) + sizeof(btime)))->year  = pdt->pd.year  ;
    ((btime FAR *) res)->hour           = pdt->pt.hour    ;
    ((btime FAR *) res)->minute         = pdt->pt.minute  ;
    ((btime FAR *) res)->second         = pdt->pt.second  ;
    ((btime FAR *) res)->hundred_second = 0 ;
    }
  else
    lmemset (res,'\0',rSize);
  }

LPVOID GetDateTime (LPVOID data,WORD dataSize,WORD dataType,WORD FAR *rSize)
  {
  packdatetime FAR *pdt = (packdatetime FAR *) convbuffer;
  pdt->pd.day   = ((bdt FAR *) (LPSTR(data) + sizeof(btime)))->day   ; 
  pdt->pd.month = ((bdt FAR *) (LPSTR(data) + sizeof(btime)))->month ; 
  pdt->pd.year  = ((bdt FAR *) (LPSTR(data) + sizeof(btime)))->year  ;
  pdt->pt.hour    = ((btime FAR *) data)->hour   ;
  pdt->pt.minute  = ((btime FAR *) data)->minute ;
  pdt->pt.second  = ((btime FAR *) data)->second ;

  if ((pdt->pd.day != 0) ||
      (pdt->pd.month != 0) ||
      (pdt->pd.year != 0) ||
      (pdt->pt.hour != 0) ||
      (pdt->pt.minute != 0) ||
      (pdt->pt.second != 0)) {
    *rSize = sizeof(*pdt);
    return pdt;
    }
  else {
    *rSize = 0 ;
    return NULL ;
    }
  }

static GETFNC getfnc[] = {
  GetLong,           // VAR_LONG      
  GetFloats,         // VAR_DEC       
  GetString,         // VAR_STR       
  GetFloats,         // VAR_POINT     
  GetCont,           // VAR_CONT      
  GetShort,          // VAR_STRARR    
  GetShort,          // VAR_FLAG      
  GetFloats,         // VAR_SCALE     
  NULL,              // VAR_PICTURE   
  GetDate,           // VAR_DATE      
  NULL,              // VAR_PROC      
  NULL,              // VAR_IMAGE     
  GetDWord,          // VAR_DWORD     
  GetPrivate,        // VAR_OBJ       
  NULL,              // VAR_BITMAP    
  GetTime,           // VAR_TIME
  GetQLong,          // VAR_QLONG
  GetLong,           // VAR_BLOB
  GetDateTime        // VAR_DATETIME
  };
static SETFNC setfnc[] = {
  SetLong,           // VAR_LONG      
  SetFloats,         // VAR_DEC       
  SetString,         // VAR_STR       
  SetFloats,         // VAR_POINT     
  SetCont,           // VAR_CONT      
  SetShort,          // VAR_STRARR    
  SetShort,          // VAR_FLAG      
  SetFloats,         // VAR_SCALE     
  NULL,              // VAR_PICTURE   
  SetDate,           // VAR_DATE      
  NULL,              // VAR_PROC      
  NULL,              // VAR_IMAGE     
  SetDWord,          // VAR_DWORD     
  SetPrivate,        // VAR_OBJ       
  NULL,              // VAR_BITMAP    
  SetTime,           // VAR_TIME
  SetQLong,          // VAR_QLONG
  SetLong,           // VAR_BLOB
  SetDateTime        // VAR_DATETIME
  };
static INIFNC inifnc[] = {
  IniLong,           // VAR_LONG      
  IniFloats,         // VAR_DEC       
  IniString,         // VAR_STR       
  IniFloats,         // VAR_POINT     
  IniCont,           // VAR_CONT      
  IniShort,          // VAR_STRARR    
  IniShort,          // VAR_FLAG      
  IniFloats,         // VAR_SCALE     
  NULL,              // VAR_PICTURE   
  IniDate,           // VAR_DATE      
  NULL,              // VAR_PROC      
  NULL,              // VAR_IMAGE     
  IniDWord,          // VAR_DWORD     
  IniPrivate,        // VAR_OBJ       
  NULL,              // VAR_BITMAP    
  IniTime,           // VAR_TIME
  IniQLong,          // VAR_QLONG
  IniBlob,           // VAR_BLOB
  IniDateTime        // VAR_DATETIME
  };
static INIFNC setminfnc[] = {
  SetLongMin,        // VAR_LONG      
  SetFloatMin,       // VAR_DEC       
  SetStringMin,      // VAR_STR       
  NULL,              // VAR_POINT     
  NULL,              // VAR_CONT      
  SetShortMin,       // VAR_STRARR    
  SetShortMin,       // VAR_FLAG      
  NULL,              // VAR_SCALE     
  NULL,              // VAR_PICTURE   
  SetDateMin,        // VAR_DATE      
  NULL,              // VAR_PROC      
  NULL,              // VAR_IMAGE     
  SetDWordMin,       // VAR_DWORD     
  SetPrivateMin,     // VAR_OBJ       
  NULL,              // VAR_BITMAP    
  SetTimeMin,        // VAR_TIME
  SetQLongMin,       // VAR_QLONG
  SetLongMin,        // VAR_BLOB
  SetDateTimeMin     // VAR_DATETIME
  };
static INIFNC setmaxfnc[] = {
  SetLongMax,        // VAR_LONG      
  SetFloatMax,       // VAR_DEC       
  SetStringMax,      // VAR_STR       
  NULL,              // VAR_POINT     
  NULL,              // VAR_CONT      
  SetShortMax,       // VAR_STRARR    
  SetShortMax,       // VAR_FLAG      
  NULL,              // VAR_SCALE     
  NULL,              // VAR_PICTURE   
  SetDateMax,        // VAR_DATE      
  NULL,              // VAR_PROC      
  NULL,              // VAR_IMAGE     
  SetDWordMax,       // VAR_DWORD     
  SetPrivateMax,     // VAR_OBJ       
  NULL,              // VAR_BITMAP    
  SetTimeMax,        // VAR_TIME
  SetQLongMax,       // VAR_QLONG
  SetLongMax,        // VAR_BLOB
  SetDateTimeMax     // VAR_DATETIME
  };

#define KLBDIMENSION  17
#define MBDIMENSION   111
struct KLBlock { 
  BYTE Id ; 
  WORD BlockSize ;
  };
struct MBlockRoot {
  WORD GesSlems;
  int AnzElems;
  };
struct MBlockElem {
  WORD Id;
  WORD ElemSize;
  };

hash FAR *GetBlockedData (LPBTRVTABLE t,LPVOID dataBuffer,unsigned bufferSize,WORD mapType)
  {
  hash FAR *x = NULL;
  switch (mapType) {
    case MAPTYPE_KLBLOCKED :
      x = new hash (KLBDIMENSION,WORDKEY);
      if (t->bdsc.lOffset < bufferSize) {
        // Setzen der einzelnen Bloecke
        LPWORD maxLen = LPWORD(LPSTR(dataBuffer) + t->bdsc.lOffset);
        WORD l = (t->bdsc.AnzChars == 1) ? (*maxLen & 0x00FF) : *maxLen;
        KLBlock FAR *klb = 
          (KLBlock FAR *) (LPSTR(maxLen) + t->bdsc.AnzChars);
        KLBlock FAR *end = (KLBlock FAR *) (LPSTR(klb) + l);
        for ( ; klb < end ; 
                klb = (KLBlock FAR *) (LPSTR(klb+1) + klb->BlockSize))
          x->SetDataW (klb->Id,&klb->BlockSize, // Achtung: Laengenwort mit
                                                // in die Daten aufnehmen, Offset
                                                // von -2 ist erlaubt !!!
                               klb->BlockSize + sizeof(klb->BlockSize)
                      );
        }
      break ;
    case MAPTYPE_MBLOCKED :
      x = new hash (MBDIMENSION,WORDKEY);
      if (t->BlockType == BLOCKTYPE_MARILLE) {
        // Am beginn Steht die Groesse und Anzahl Elemente !
        //////////////////////////////////////////////////////
        if (t->bdsc.lOffset + sizeof(MBlockRoot) <= bufferSize) {
          LPSTR bufferEnd = LPSTR(dataBuffer) + bufferSize ;
          MBlockRoot FAR *r = (MBlockRoot FAR *) (LPSTR(dataBuffer) + t->bdsc.lOffset);
          MBlockElem FAR *e = (MBlockElem FAR *) (r+1);
          for (int i = 0 ; i < r->AnzElems ; i++) {
            MBlockElem FAR *eNext = (MBlockElem FAR *) (LPSTR(e + 1) + e->ElemSize);
            if (LPSTR(eNext) < bufferEnd) {
              x->SetDataW (e->Id,e + 1,e->ElemSize);
              }
            else {
              LPSTR h = LPSTR(GetGlobMem (e->ElemSize));
              // Den Rest hinter der ElemSize mit '\0' auffuellen
              // (Durch Aenderungen mit SQLScope kann der Datenblock
              //  zusammengeschossen werden... moeglichst defensiv programmiert)
              lmemcpy (h,e + 1,bufferEnd - LPSTR(e+1));
              x->SetDataW (e->Id,h,e->ElemSize);
              FreeGlobMem (h);
              break ;
              }
            e = eNext ;
            }
          }
        }
      else {
        // Am beginn Steht nur die Groesse 
        ///////////////////////////////////
        if (t->bdsc.lOffset + sizeof(WORD) <= bufferSize) {
          LPWORD r = LPWORD (LPSTR(dataBuffer) + t->bdsc.lOffset);
          MBlockElem FAR *e   = (MBlockElem FAR *) (r+1);
          MBlockElem FAR *end = (MBlockElem FAR *) (LPSTR(e) + *r);
          for ( ; e < end ; ) {
            x->SetDataW (e->Id,e + 1,e->ElemSize);
            e = (MBlockElem FAR *) (LPSTR(e + 1) + e->ElemSize);
            }
          }
        }
      break ;
    }
  return x;
  }

LPVOID VarDesc::Extract (LPBTRVTABLE t,LPVOID dataBuffer,unsigned bufferSize,WORD FAR *rSize,LPVOID FAR *hData)
  {
  // Ermitteln eines Zeigers auf die Ausgangsdaten
  switch (mapType) {
    case MAPTYPE_FIELD :
      {
      LPVBTRV v = LPVBTRV (LPSTR(t->GetVarRef(FALSE)) + b.dOffs);
      LPVOID data = LPSTR(dataBuffer) + v->VarOffset;
      GETFNC cfnc = getfnc[mType];
      WIN_ASSERT(cfnc != NULL);
      return (* cfnc) (data,v->VarLen,v->DataType,rSize);
      }
    case MAPTYPE_KLBLOCKED :
      {
      WIN_ASSERT (hData != NULL);
      hash FAR *x = (hash FAR *) *hData;
      LPVOID res;
      if (x == NULL) {
        x = GetBlockedData (t,dataBuffer,bufferSize,mapType);
        *(hash FAR * FAR *)hData = x;
        }
      LPSTR data = LPSTR(x->GetDataW (b.kl.BlockID));
      WORD VarMaxLen = GetBlockSize (data) - (b.kl.VarOffset + sizeof(WORD));
      if ((data != NULL) && (VarMaxLen > 0)) {
        // Na versuchen wirs mal
        LPVOID edata = LPSTR(data) + b.kl.VarOffset + sizeof(WORD);
        GETFNC cfnc = getfnc[mType];
        WIN_ASSERT(cfnc != NULL);
        WORD MinValue = min(VarMaxLen,b.kl.VarLen);
        return (* cfnc) (edata, MinValue, b.kl.DataType, rSize);
        }
      else
        res = NULL;
      return res;
      }
      break ;
    case MAPTYPE_MBLOCKED :
      {
      WIN_ASSERT (hData != NULL);
      hash FAR *x = (hash FAR *) *hData;
      if (x == NULL) {
        x = GetBlockedData (t,dataBuffer,bufferSize,mapType);
        *(hash FAR * FAR *)hData = x;
        }
      LPVOID res = x->GetDataW (b.m.VarID);
      if (res != NULL)
        *rSize = GetBlockSize(res);
      else
        *rSize = 0;
      return res;
      }
    default :
      WIN_ASSERT(FALSE);
      return NULL;
    }
  }

void FreeHData (LPVOID hData)
  {
  if (hData != NULL) {
    hash FAR *h = (hash FAR *) hData;
    delete h;
    }
  }

LPVOID VarDesc::Extract_extended (LPBTRVTABLE t,LPVOID data,unsigned bufferSize,WORD FAR *rSize)
  {
  // Ermitteln eines Zeigers auf die Ausgangsdaten
  LPVBTRV v = LPVBTRV (LPSTR(t->GetVarRef(FALSE)) + b.dOffs);
  GETFNC cfnc = getfnc[mType];
  WIN_ASSERT(cfnc != NULL);
  return (* cfnc) (data,v->VarLen,v->DataType,rSize);
  }

void VarDesc::SetData (LPBTRVTABLE t,LPVOID dataBuffer,unsigned FAR *bufferSize,LPVOID data,LPVOID FAR *hData)
  {
  // Ermitteln eines Zeigers auf die Ausgangsdaten
  switch (mapType) {
    case MAPTYPE_FIELD :
      {
      LPVBTRV v   = LPVBTRV (LPSTR(t->GetVarRef(FALSE)) + b.dOffs);
      LPVOID res  = LPSTR(dataBuffer) + v->VarOffset;
      SETFNC cfnc = setfnc[mType];
      WIN_ASSERT(cfnc != NULL);
      (* cfnc) (res,v->VarLen,v->DataType,data,GetBlockSize(data));
      }
      break ;
    case MAPTYPE_KLBLOCKED :
      {
      WIN_ASSERT (hData != NULL);
      hash FAR *x = (hash FAR *) *hData;
      if (x == NULL) {
        x = GetBlockedData (t,dataBuffer,*bufferSize,mapType);
        *(hash FAR * FAR *)hData = x;
        }
      LPSTR hdata = LPSTR(x->GetDataW (b.kl.BlockID));
      int MinLen = b.kl.VarOffset + b.kl.VarLen + sizeof(WORD);
      LPSTR n;
      if ((hdata == NULL) || (int(GetBlockSize (hdata)) < MinLen)) {
        n = LPSTR (GetGlobMem (MinLen));
        if (hdata != NULL) lmemcpy (n,hdata,GetBlockSize(hdata)) ;
        }
      else {
        n = LPSTR(GetGlobMem (GetBlockSize(hdata)));
        lmemcpy (n,hdata,GetBlockSize(hdata));
        }
      LPVOID edata = LPSTR(n) + b.kl.VarOffset + sizeof(WORD);
      SETFNC cfnc = setfnc[mType];
      * LPWORD(n) = GetBlockSize(n) - sizeof(WORD);
      (* cfnc) (edata,b.kl.VarLen,b.kl.DataType,data,GetBlockSize(data));
      if (data != NULL)
        x->ChangeDataW(b.kl.BlockID,n,GetBlockSize(n));
      else
        x->SetDataW(b.kl.BlockID,n,GetBlockSize(n));
      FreeGlobMem (n);
      }
      break ;
    case MAPTYPE_MBLOCKED :
      {
      WIN_ASSERT (hData != NULL);
      hash FAR *x = (hash FAR *) *hData;
      if (x == NULL) {
        x = GetBlockedData (t,dataBuffer,*bufferSize,mapType);
        *(hash FAR * FAR *)hData = x;
        }
      LPVOID d = x->GetDataW (b.m.VarID);
      if (d != NULL)
        x->ChangeDataW (b.m.VarID,data,GetBlockSize(data));
      else
        x->SetDataW (b.m.VarID,data,GetBlockSize(data));
      }
      break ;
    }
  }

void VarDesc::SetNULLData (LPBTRVTABLE t,LPVOID dataBuffer,unsigned FAR *bufferSize,LPVOID FAR *hData)
  { 
  switch (mapType) {
    case MAPTYPE_FIELD :
      {
      LPVBTRV v   = LPVBTRV (LPSTR(t->GetVarRef(FALSE)) + b.dOffs);
      LPVOID res  = LPSTR(dataBuffer) + v->VarOffset;
      INIFNC cfnc = inifnc[mType];
      WIN_ASSERT(cfnc != NULL);
      (* cfnc) (res,v->VarLen,v->DataType);
      }
      break ;
    case MAPTYPE_KLBLOCKED :
      {
      if (hData == NULL) return;
      hash FAR *x = (hash FAR *) *hData;
      if (x == NULL) {
        x = GetBlockedData (t,dataBuffer,*bufferSize,mapType);
        *(hash FAR * FAR *)hData = x;
        }
      LPSTR data = LPSTR(x->GetDataW (b.kl.BlockID));
      int MinLen = b.kl.VarOffset + b.kl.VarLen + sizeof(WORD);
      if ((data != NULL) && (int(GetBlockSize (data)) >= MinLen)) {
        LPSTR n = LPSTR(GetGlobMem (GetBlockSize(data)));
        lmemcpy (n,data,GetBlockSize(data));
        LPVOID edata = LPSTR(n) + b.kl.VarOffset + sizeof(WORD);
        INIFNC cfnc = inifnc[mType];
        * LPWORD(n) = GetBlockSize(n) - sizeof(WORD);
        (* cfnc) (edata,b.kl.VarLen,b.kl.DataType);
        x->ChangeDataW(b.kl.BlockID,n,GetBlockSize(n));
        FreeGlobMem (n);
        }
      }
      break ;
    case MAPTYPE_MBLOCKED :
      {
      if (hData == NULL) return;
      hash FAR *x = (hash FAR *) *hData;
      if (x == NULL) {
        x = GetBlockedData (t,dataBuffer,*bufferSize,mapType);
        *(hash FAR * FAR *)hData = x;
        }
      LPSTR data = LPSTR(x->GetDataW (b.kl.BlockID));
      if (data != NULL)
        x->DelDataW (b.m.VarID);
      }
      break ;
    }
  }

void SetHData (LPBTRVTABLE t,LPVOID dataBuffer,unsigned FAR *bufferSize,LPVOID hData)
  {
  if (hData != NULL) {
    hash FAR *h = (hash FAR *) hData;
    // Hashtabelle Abgrasen
    switch (t->BlockType) {
      case BLOCKTYPE_MARILLE1 :
        {
        LPWORD r = LPWORD (LPSTR(dataBuffer) + t->bdsc.lOffset);
        *r = 0;
        *bufferSize = t->bdsc.lOffset + sizeof(*r);
        MBlockElem FAR *b = (MBlockElem FAR *) (r+1);
        for (int i = 0 ; i < int (h->hash_dimension) ; i++) {
          for (LPhash_entry e = h->Table + i ; e != NULL ; ) {
            if (!h->is_empty (e)) {
              // Schluessel Speichern
              b->Id = e->key.wKey;
              // Daten Speichern
              b->ElemSize = e->wDataSize;
              lmemcpy (b+1,e->Data,e->wDataSize);
              *bufferSize += sizeof(*b) + e->wDataSize;
              *r += sizeof(*b) + e->wDataSize;
              b = (MBlockElem FAR *) (LPSTR(b+1) + e->wDataSize) ;
              }
            e = h->NextEnt (e);
            }
          }
        }
        break ;
      case BLOCKTYPE_KL       :
        {
        LPWORD wmaxLen = LPWORD(LPSTR(dataBuffer) + t->bdsc.lOffset);
        LPBYTE bmaxLen = LPBYTE(LPSTR(dataBuffer) + t->bdsc.lOffset);
        if (t->bdsc.AnzChars == 1) *bmaxLen = 0;
        else                       *wmaxLen = 0;
        KLBlock FAR *klb = 
          (KLBlock FAR *) (LPSTR(wmaxLen) + t->bdsc.AnzChars);
        for (int i = 0 ; i < int (h->hash_dimension) ; i++) {
          for (LPhash_entry e = h->Table + i ; e != NULL ; ) {
            if (!h->is_empty (e)) {
              // Schluessel Speichern
              klb->Id = BYTE(e->key.wKey);
              // Daten Speichern
              lmemcpy (&klb->BlockSize,e->Data,e->wDataSize);
              WIN_ASSERT(klb->BlockSize + sizeof(WORD) == e->wDataSize);
              *bufferSize += sizeof(*klb) + klb->BlockSize;
              if (t->bdsc.AnzChars == 1) 
                *bmaxLen += BYTE(sizeof(*klb) + klb->BlockSize);
              else                       
                *wmaxLen += sizeof(*klb) + klb->BlockSize;
              klb = (KLBlock FAR *) (LPSTR(klb + 1) + klb->BlockSize);
              }
            e = h->NextEnt (e);
            }
          }
        }
        break ;
      case BLOCKTYPE_MARILLE  :
        {
        MBlockRoot FAR *r = (MBlockRoot FAR *) (LPSTR(dataBuffer) + t->bdsc.lOffset);
        r->GesSlems = sizeof(*r);
        r->AnzElems  = 0;
        *bufferSize = t->bdsc.lOffset + sizeof(*r);
        MBlockElem FAR *b = (MBlockElem FAR *) (r+1);
        for (int i = 0 ; i < int (h->hash_dimension) ; i++) {
          for (LPhash_entry e = h->Table + i ; e != NULL ; ) {
            if (!h->is_empty (e)) {
              // Schluessel Speichern
              b->Id = e->key.wKey;
              // Daten Speichern
              b->ElemSize = e->wDataSize;
              lmemcpy (b+1,e->Data,e->wDataSize);
              *bufferSize += sizeof(*b) + e->wDataSize;
              r->GesSlems += sizeof(*b) + e->wDataSize;
              r->AnzElems ++ ;
              b = (MBlockElem FAR *) (LPSTR(b+1) + e->wDataSize) ;
              }
            e = h->NextEnt (e);
            }
          }
        }
        break ;
      case BLOCKTYPE_NONE     :
        WIN_ASSERT (FALSE);
        break ;
      }
    delete h;
    }
  }

static BYTE mTypToConv[24] = {
/* BDT_STRING    0 */ VAR_STR ,
/* BDT_INTEGER   1 */ VAR_LONG ,
/* BDT_FLOAT     2 */ VAR_DEC ,
/* BDT_DATE      3 */ VAR_DATE ,
/* BDT_TIME      4 */ VAR_TIME ,
/* BDT_DECIMAL   5 */ VAR_DEC ,
/* BDT_MONEY     6 */ VAR_LONG ,
/* BDT_LOGICAL   7 */ VAR_FLAG ,
/* BDT_NUMERIC   8 */ VAR_LONG ,
/* BDT_BFLOAT    9 */ VAR_DEC ,
/* BDT_LSTRING   10*/ VAR_STR ,
/* BDT_ZSTRING   11*/ VAR_STR , 
/*12*/ 0xFF , 
/*13*/ 0xFF,
/* BDT_UNSIGNED  14*/ VAR_OBJ ,
/* BDT_AUTOINC   15*/ VAR_LONG , 
/*16*/ 0xFF , 
/*17*/ 0xFF , 
/*18*/ 0xFF , 
/*19*/ 0xFF , 
/* DT_PRIVATE    20*/ VAR_DATETIME ,
/* DT_LDSTRING   21*/ VAR_STR ,
/* DT_KLDATE     22*/ VAR_DATE ,
/* DT_SPRIVATE   23*/ VAR_OBJ 
  };
LPVOID VBtrv::Extract (LPVOID data,WORD FAR *rSize)
  {
  // Ermitteln eines Zeigers auf die Ausgangsdaten
  WORD mType = WORD(mTypToConv[DataType]);
  GETFNC cfnc = getfnc[mType];
  WIN_ASSERT(cfnc != NULL);
  return (* cfnc) (data,VarLen,DataType,rSize);
  }
void VBtrv::SetData (LPVOID res,LPVOID data)
  {
  // Ermitteln eines Zeigers auf die Ausgangsdaten
  WORD mType = WORD(mTypToConv[DataType]);
  if ((DataType == BDT_INTEGER) && (VarLen == 2))
    mType = VAR_STRARR ;    // extra Ummappen der short integer
  if ((DataType == BDT_UNSIGNED) && (VarLen == 8))
    mType = VAR_DATETIME ;    // extra Ummappen der Time - Stamps

  SETFNC cfnc = setfnc[mType];
  WIN_ASSERT(cfnc != NULL);
  (* cfnc) (res,VarLen,DataType,data,GetBlockSize(data));
  }
void VBtrv::SetMinData (LPVOID res)
  {
  // Ermitteln eines Zeigers auf die Ausgangsdaten
  WORD mType = WORD(mTypToConv[DataType]);
  INIFNC cfnc = setminfnc[mType];
  WIN_ASSERT(cfnc != NULL);
  (* cfnc) (res,VarLen,DataType);
  }
void VBtrv::SetMaxData (LPVOID res)
  {
  // Ermitteln eines Zeigers auf die Ausgangsdaten
  WORD mType = WORD(mTypToConv[DataType]);
  INIFNC cfnc = setmaxfnc[mType];
  WIN_ASSERT(cfnc != NULL);
  (* cfnc) (res,VarLen,DataType);
  }
