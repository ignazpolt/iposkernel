/* -------------------
 *      about.h 
 * -------------------
 *  for the DentoMedical Workstation
 *  Norbert
 *  30.11.92
 *
 * $Header:   P:/marille/clinicum/include/rev/about.h_v   1.4   05 Oct 1998 11:25:02   Gerhold  $
 * $Log:   P:/marille/clinicum/include/rev/about.h_v  $
 * 
 *    Rev 1.4   05 Oct 1998 11:25:02   Gerhold
 * Vorbereitung auf C6 (Type Casts)
 * 
 *    Rev 1.3   06 Aug 1997 10:11:44   gerhold
 * Windows-Version und Debug-Version
 * 
 *    Rev 1.2   02 Feb 1996 11:02:26   GERHOLD
 * 1.Umstellung auf 32 Bit
 * 
 *    Rev 1.1   04 Oct 1995 16:02:48   MARTIN
 * Clinicum raus
 * 
 *    Rev 1.0   24 Jun 1994 17:00:56   HANNES
 * Neuuebernahme clinicum
 * 
 *    Rev 1.0   02 Dec 1992 15:58:12   HANNES
 * Initial revision.
 *
 */

#define IDM_ABOUT     1
#define USER_ID       100
#define B_VERSNUM     101
#define VERSION       105
#define SYSRESOURCES  106
#define FREESPACE     107
#define PRODUCTNAME   110
#define WIN_VERSION   111
#define DBG_VERSION   112

void ShowAbout (HINSTANCE);
