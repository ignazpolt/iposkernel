/* ----------------------------------------
 *             ddsmsg.h
 * ----------------------------------------
 *
 * $Header:   P:/marille/clinicum/include/rev/ddsmsg.h_v   1.5   09 Oct 1998 18:45:34   Wolfgang  $
 * $Log:   P:/marille/clinicum/include/rev/ddsmsg.h_v  $
 * 
 *    Rev 1.5   09 Oct 1998 18:45:34   Wolfgang
 * 1.) WMU_SOCKETEVENT neu.
 * 
 *    Rev 1.4   12 Jan 1998 18:22:44   Hannes
 * 
 *    Rev 1.3   26 Aug 1997 17:36:02   Hannes
 * WM_VSCROLL -> WMU_VSCROLL
 * 
 *    Rev 1.2   02 Feb 1996 11:02:32   GERHOLD
 * 1.Umstellung auf 32 Bit
 * 
 *    Rev 1.1   17 Oct 1994 11:00:34   HANNES
 * 
 *    Rev 1.0   24 Jun 1994 17:00:58   HANNES
 * Neuuebernahme clinicum
 * 
 *    Rev 1.12   03 Mar 1994 22:05:52   HANNES
 * WMU_OLEDELETEOBJ
 * 
 *    Rev 1.11   04 Feb 1994 17:01:16   HANNES
 * WMU_RECINDCHANGED
 * 
 *    Rev 1.10   25 Jan 1994 16:23:58   MARTIN
 * neue Message WMU_PLAYSOUND
 * 
 *    Rev 1.9   04 Jan 1994 17:16:54   HANNES
 * Neue Meldung des Digitizers: WMU_DIGDEL
 * 
 *    Rev 1.8   28 Oct 1993 12:40:24   MARTIN
 * WMU_DESTROYBUBBLE
 * 
 *    Rev 1.7   05 Sep 1993 22:18:50   HANNES
 * einige Alte meldungen geschmissen
 * 
 *    Rev 1.6   18 Aug 1993 10:37:32   HANNES
 * WMU_DESTROYDDSLIST
 * 
 *    Rev 1.5   22 Feb 1993 17:22:04   HANNES
 * WMU_CRPRESSED,WMU_ESCPRESSED
 * 
 *    Rev 1.4   18 Jan 1993 16:51:38   HANNES
 * Neue Meldung: WMU_GETCATEGORY
 * 
 *    Rev 1.3   17 Dec 1992 15:57:52   HANNES
 * Neue Meldungen (fuer den Digitizer: WMU_GETNEXT..)
 * 
 *    Rev 1.2   10 Dec 1992 11:55:48   HANNES
 * Neue Meldung, dass der Scanner mit der Eingabe starten will
 * (letzte Moeglichkeit, das noch zu verhindern bzw. Anderen Vorschlag zu
 * machen)
 * 
 *    Rev 1.1   05 Dec 1992 13:10:04   HANNES
 * Um Meldungen in Verbindung mit dmwhook erweitert
 * 
 *    Rev 1.0   02 Dec 1992 16:01:20   HANNES
 * Initial revision.
 *
 */

#define WM_USER0      (WM_USER +0x400)
#define WM_USER1            (WM_USER0+0x100)

#define WMU_SCROLLVAL         (WM_USER0+ 0)
#define WMU_STATECHANGE         (WM_USER0+ 1)
#define WMU_DIALOGCLOSE         (WM_USER0+ 2)
#define WMU_DOSCROLL            (WM_USER0+ 3)
#define WMU_SELCHANGE           (WM_USER0+ 4)
#define WMU_GETNEWSEL           (WM_USER0+ 5)
#define WMU_FORMATCHANGE        (WM_USER0+ 6)
#define WMU_VSIZECHANGE         (WM_USER0+ 7)
#define WMU_HSIZECHANGE         (WM_USER0+ 8)
#define WMU_FIELDVSIZECHANGE    (WM_USER0+ 9)
#define WMU_FIELDHSIZECHANGE    (WM_USER0+10)
#define WMU_COMMENTENTERED      (WM_USER0+11)
#define WMU_DESTROYCHILD        (WM_USER0+12)
#define WMU_DESTROYLIST         (WM_USER0+13)
#define WMU_NEWDATAKEY          (WM_USER0+14)  // Eingaberecord hat Schluessel gekriegt
#define WMU_SELECTNEWDATA       (WM_USER0+15)  // Aufforderung an alle Fenster, den Patienten zu wechseln
// #define WMU_NAMECHANGED         (WM_USER0+16)  // Name hat sich geaendert
// #define WMU_COMMENTCHANGED      (WM_USER0+17)  // Kommentar hat sich geaendert
#define WMU_CLOSEHLP            (WM_USER0+18)  // Hilfefenster wieder schliessen
#define WMU_DIGITIZED           (WM_USER0+19)  // Digitizereingabe ist fertig
#define WMU_CALLCOMMAND         (WM_USER0+20)  // Die wohl am haeufigsten ausgesendete Meldung
#define WMU_CHECKCOMM           (WM_USER0+21)  // ser. Schnittstelle soll nach Daten ueberprueft werden
#define WMU_CLOSECOMM           (WM_USER0+22)  // ser. Schnittstelle soll wieder geschlossen werden
#define WMU_CARETSET            (WM_USER0+23)  // Caret in einem Feld wurde gesetzt
#define WMU_EDSTRINGUPDATE      (WM_USER0+24)  // String in dem Editfeld hat sich geaendert
// #define WMU_DATECHANGED         (WM_USER0+25)  // Datum hat sich geaendert -> ueberall Update
#define WMU_CLOSEGAUSS          (WM_USER0+26)  // Gaussfenster wuenscht Abbruch
#define WMU_CLOSEHISTO          (WM_USER0+26)  // Histofenster will gschlossen werden
#define WMU_GETPREFPOS          (WM_USER0+27)  // Ein Kindfenster wuenscht die bevorzugten Koordinaten 
#define WMU_STOREPREFPOS        (WM_USER0+28)  // Ein Kindfenster will die Koordinaten speichern
#define WMU_SHOWPATINFO         (WM_USER0+29)  // Name muss neuerlich angezeigt werden
#define WMU_PARDEACTIVATE       (WM_USER0+30)  // Dokumentenfenster wird inaktiv
// #define WMU_XFACTCHANGED        (WM_USER0+31)  // Vergroesserungsfaktor hat sich geaendert -> ueberall Update
#define WMU_EDSTRINGCHANGE      (WM_USER0+32)  // Return im Editfeld gedrueckt
#define WMU_GETMAINDATA         (WM_USER0+33)  // Abfrage nach dem Hauptdatentyp
#define WMU_ZOOMSIZECHANGE      (WM_USER0+34)  // Zoom - Fenstergroesse hat sich geaendert
#define WMU_GETLUCORNER         (WM_USER0+35)  // Zoom - Fenster will die Koordinaten des dargestellen Rechteckes wissen
#define WMU_ZOOMWINPRESSED      (WM_USER0+36)  // Im Zoom - Fenster ist eine Eingabe vorgenommen worden
#define WMU_CLOSEZOOM           (WM_USER0+37)  // Zoom - Fenster 
#define WMU_CLOSESUBFORM        (WM_USER0+41)  // Subform will geschlossen werden
#define WMU_FONTCHANGE          (WM_USER0+42)  // Layout eines Formats hat sich geaendert
#define WMU_GETCATEGORY         (WM_USER0+43)  // Ermitteln der Dokumentenkategorie
#define WMU_HIDEDOCLIST         (WM_USER0+44)  // Die Dokumentenliste will versteckt werden
#define WMU_CRPRESSED           (WM_USER0+45)  // Kind benachrichtigt Vater von gedruecktem CR
#define WMU_ESCPRESSED          (WM_USER0+46)  // Kind benachrichtigt Vater von gedruecktem ESC
#define WMU_DESTROYDDSLIST      (WM_USER0+47)  // Liste wurde zerstoert
#define WMU_DESTROYBUBBLE       (WM_USER0+48)  // Hilfe-Bubble zerstoeren
#define WMU_RECCHANGED          (WM_USER0+49)  // Recordtyp hat sich veraendert
#define WMU_DELETEOBJ           (WM_USER0+50)  // OLE - Objekt will geloescht werden
#define WMU_EXITZOOMMODE        (WM_USER0+51)  // Zoom soll wieder ausgeschalten werden
#define WMU_SOCKETEVENT         (WM_USER0+52)  // WinSocket-Event aufgetreten (WSAAsyncSelect)

#define WMU_USER_INITIATE   (WM_USER1+ 0)
#define WMU_ENDDDE          (WM_USER1+ 1)

#define SBU_THUMBVAL      (SB_ENDSCROLL+1)
#define CLR_SELDAY          (WM_USER1+2)        // Ein Tag soll selektiert werden
#define CLR_SETMINFO        (WM_USER1+3)        // Information ueber einen Tag
#define CLR_DESELDAY        (WM_USER1+4)        // Ein Tag soll deselektiert werden
#define CLR_RESET           (WM_USER1+5)        // Ein Tag soll deselektiert werden
#define CLR_DBLCLK          (WM_USER1+6)        // Ein Tag wurde doppelgeklickt
#define CLR_SELCHANGE       (WM_USER1+7)        // Ein Tag wurde selektiert
#define CLR_GETCURSEL       (WM_USER1+8)        // Abfrage des zuletzt selektierten Tages
#define CLR_DISABLEITEM     (WM_USER1+9)        // Tag nicht zur Selektion zulassen
#define HBT_TRACKLEFT       (WM_USER1+10)       // Knoefchen ist gedruckt
#define HBT_TRACKRIGHT      (WM_USER1+11)       // Knoefchen ist gedruckt
#define HBT_SETTEXTCOLOR    (WM_USER1+12)       // Textfarbe einstellen
#define WMU_XFERDONE        (WM_USER1+13)       // Scanning ist abgeschlossen
#define WMU_VALREAD         (WM_USER1+14)       // Schiebelehre hat einen Wert eingelesen

#define WMU_MOUSEOUTOFWND   (WM_USER1+15)       // Mouse hat das Fenster verlassen
#define WMU_MOUSEINWND      (WM_USER1+17)       // Mouse betritt gerade wieder das Fenster

#define WMU_SCANSTART       (WM_USER1+18)       // Fenster wird benachrichtigt, dass das
                                                // Scannen starten Soll


#define WMU_DIGNEXT         (WM_USER1+20)       // Digitizer will weiterschalten
#define WMU_DIGPREV         (WM_USER1+21)       // -"- wieder zurueck
#define WMU_DIGDEL          (WM_USER1+22)       // Punkt loeschen

#define WMU_PLAYSOUND       (WM_USER1+23)       // Sound abspielen
#define WMU_HSCROLL         (WM_USER1+24)       // Sound abspielen
#define WMU_VSCROLL         (WM_USER1+25)       // Sound abspielen
#define WMU_GETTEXT         (WM_USER1+26)       // Sound abspielen

