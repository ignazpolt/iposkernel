////////////////////////////////////////////////////////////
//  Indizess der DLL - Funktionen
////////////////////////////////////////////////////////////
/*  $Header:   P:/marille/clinicum/include/rev/dlladmin.h_v   1.16   03 Dec 1999 02:37:48   Hannes  $
 *  $Log:   P:/marille/clinicum/include/rev/dlladmin.h_v  $
 * 
 *    Rev 1.16   03 Dec 1999 02:37:48   Hannes
 * ErrorText
 * 
 *    Rev 1.15   15 Jun 1999 16:20:48   THOMAS
 * 1.) _DBCURRENTDATETIME neu.
 * 
 *    Rev 1.14   05 Feb 1999 21:38:00   Martin
 * verbessertes Errorhandling
 * 
 *    Rev 1.13   19 Jan 1999 19:27:04   Hannes
 * SetUserName
 * 
 *    Rev 1.12   09 Oct 1998 18:45:52   Wolfgang
 * 1.) _NET_NWADDRESSSTRTOBIN und _NET_NWADDRESSBINTOSTR neu.
 * 2.) _NET_NWSOCKETFAMILY, _NET_NWADDRESSSIZE und _NET_NWSOCKETPROTOCOL neu.    
 * 
 *    Rev 1.11   31 Oct 1997 12:50:02   Hannes
 * Timestampfunktion
 * 
 *    Rev 1.10   14 Jan 1997 16:17:14   HANNES
 * Neue Prozedure DBPOINTER
 * 
 *    Rev 1.9   26 Nov 1996 08:07:40   HANNES
 * Automatischer Update
 * 
 *    Rev 1.8   05 Apr 1996 14:48:10   MARTIN
 * Abgleich Schweiz
 * 
 * dnetapi included
 *
 *    Rev 1.7   31 Jan 1996 18:11:22   HANNES
 * rshelp - Verwaltung
 * 
 *    Rev 1.6   16 Feb 1995 13:02:10   HANNES
 *  
 * 
 *    Rev 1.5   29 Jan 1995 11:46:56   HANNES
 * 
 *    Rev 1.4   09 Jan 1995 12:11:38   HANNES
 * Debugger eingebaut
 * 
 *    Rev 1.3   31 Oct 1994 10:42:40   hannes
 * Transaktionen
 * 
 *    Rev 1.2   19 Oct 1994 22:35:20   hannes
 * Einbindung SQL Konverter
 * 
 *    Rev 1.1   04 Jul 1994 14:46:56   HANNES
 * IsViewAllowed
 * 
 *    Rev 1.0   24 Jun 1994 17:00:58   HANNES
 * Neuuebernahme clinicum
 * 
 *    Rev 1.1   19 Apr 1994 10:53:20   HANNES
 * 
 *    Rev 1.0   19 Apr 1994 10:48:54   HANNES
 * Initial revision.
*/

#define _DATARES_SETTABLEDEF             0
#define _DATARES_SETROWDEF               1
#define _DATARES_GETTABLEDEF             2
#define _DATARES_GETFIRSTROWDEF          3
#define _DATARES_GETNEXTROWDEF           4
#define _DATARES_SETFULLTABLEDEF         5
#define _DATARES_GETFULLTABLEDEF         6
#define _DATARES_GETFIRSTTABLEDEF        7
#define _DATARES_GETNEXTTABLEDEF         8
#define _DATARES_SETDICTCONT             9
#define _DATARES_GETDICTCONT             10
#define _DATARES_SETDOCDEF               11
#define _DATARES_GETDOCDEF               12
#define _DATARES_GETFIRSTDOC             13
#define _DATARES_GETNEXTDOC              14
#define _DATARES_SETDOCCONT              15
#define _DATARES_GETDOCCONT              16
#define _DATARES_SETRESOURCE             17
#define _DATARES_GETRESOURCE             18
#define _DBRESET                         19
#define _DATADICT_TABLEDEF               20
#define _DATADICT_FREETABLEDEF           21
#define _DBCALL                          22
#define _DATADICT_VARDEF                 23
#define _DATADICT_FREEVARDEF             24
#define _DATADICT_GETMTYPE               25
#define _DATADICT_GETACCESSLIST          26
#define _DATADICT_GETVARDESCEXTRA        27
#define _DATADICT_ISFOREIGNKEY           28
#define _DATARES_CLEARROWDEFS            29
#define _DATADICT_ISPRIMARY              30
#define _DATARES_GETFIRSTRESOURCE        31
#define _DATARES_GETNEXTRESOURCE         32
#define _DATARES_GETRESCONT              33
#define _DATARES_SETRESCONT              34
#define _DATARES_SETFUNCDEF              35
#define _DATARES_GETFUNCDEF              36
#define _DATADICT_ISACCESSFORVIEW        37
#define _DATADICT_GETSQLPART             38
#define _DOBEGINTRANSACTION              39
#define _DOENDTRANSACTION                40
#define _DOABORTTRANSACTION              41
#define _DATADICT_GETVARPROPERTY         42
#define _DATARES_GETSERVERSOURCE         43
#define _DATADICT_LASTSERVERSOURCE       44
#define _DATARES_SETSERVERSOURCE         45
#define _DATADICT_NEWTABLEDEF            46
#define _DATARES_DELTABLEDEF             47
#define _DBHELP_GET                      48
#define _DBHELP_PUT                      49

#define _NET_GETUNIQUEADDRESS            50
#define _NET_SETSTATIONSEMAPHOR          51
#define _NET_CLEARSTATIONSEMAPHOR        52 
#define _NET_CHECKSTATIONSEMAPHOR        53
#define _NET_SETSEMA                     54
#define _NET_CLEARSEMA                   55
#define _NET_TESTSEMA                    56
#define _NET_GETCONNECTIONNMBR           57
#define _NET_SEMAPHOREAVAILABLE          58

#define _DBALTER                         59
#define _DBIGNOREERROR                   60
#define _DBPOINT                         61
#define _MAKETIMESTAMP                   62

#define _NET_NWADDRESSSTRTOBIN           63
#define _NET_NWADDRESSBINTOSTR           64
#define _NET_NWSOCKETFAMILY              65
#define _NET_NWADDRESSSIZE               66
#define _NET_NWSOCKETPROTOCOL            67

#define _SETUSERNAME                     68
#define _DBGETLASTERROR                  69
#define _DBCURRENTDATETIME               70
#define _DBGETLASTERRORTEXT              71

#define _SETDBLOGSTATE                   72

