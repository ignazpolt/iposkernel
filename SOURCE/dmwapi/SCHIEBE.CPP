/////////////////////////////////////////////////////////////////////
//      Bedienung der Schiebelehre
/////////////////////////////////////////////////////////////////////
//
// $Header:   P:/marille/clinicum/dmwapi/rev/schiebe.cpv   1.9   30 Jan 1998 15:46:14   Martin  $
// $Log:   P:/marille/clinicum/dmwapi/rev/schiebe.cpv  $
// 
//    Rev 1.9   30 Jan 1998 15:46:14   Martin
// parallele Schiebelehre unter Windows95 32-Bit-faehig gemacht
// 
//    Rev 1.8   20 Sep 1997 18:11:52   Hannes
// CheckTimer tut jetzt nur mehr dann etwas, wenn es der richtige Timer ist.
// 
//    Rev 1.7   19 Jun 1997 18:17:24   Martin
// oops, 16 Bit-Version restauriert ...
// 
//    Rev 1.6   19 Jun 1997 16:39:04   Martin
// 32-Bit-faehig gemacht
// 
//    Rev 1.5   18 Jun 1997 19:32:02   Martin
// serielle Schiebelehre
// 
//    Rev 1.4   17 Dec 1996 17:11:36   MARTIN
// Fuer die 32 Bit integration ausgeklammert
// 
//    Rev 1.3   02 Feb 1996 10:46:38   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.2   08 Dec 1994 22:08:14   GERHOLD
// NEAR Function eleminiert
// 
//    Rev 1.1   31 Oct 1994 10:40:42   hannes
// SetSLTimer (funktioniert immer noch nicht)
// 
//    Rev 1.0   24 Jun 1994 16:48:58   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.3   10 Jun 1993 18:50:22   HANNES
// MyIni Umstellung
// 
//    Rev 1.2   07 Jun 1993 11:22:46   HANNES
// IBM ..
// 
//    Rev 1.1   03 Jun 1993 19:09:32   HANNES
// Schiebelehre fuer IBM modifiert
// 
//    Rev 1.0   02 Jun 1993 19:35:36   HANNES
// Initial revision.
// 
//    Rev 1.3   14 Feb 1993 16:04:20   HANNES
// Verschiedene Versuche mit dem Drucker..
// 
//    Rev 1.2   21 Jan 1993 22:36:42   HANNES
// vorerst passende Funktion der Schiebelehre
// 
//    Rev 1.1   13 Jan 1993 18:52:32   HANNES
// Negative Zahlen der Schiebelehre
// 
//    Rev 1.0   02 Dec 1992 15:42:34   HANNES
// Initial revision.
//

#include <windows.h>
#include <stdio.h>
#include <dos.h>
#include "dds32.h"
#include "schiebe.hpp"
#include "ddsmsg.h"
#define MODULENUM 182
#include "winass.hpp"

//{ ======================================================================== }
//{                                                                          }
//{  Das Interface in KÅrze:                                                 }
//{                                                                          }
//{  Wenn der PC /SelectIN (Pin 17) auf HIGH legt, reagiert der Drucker      }
//{  nicht mehr auf Daten. Das aktiviert daher das Interface.                }
//{                                                                          }
//{  Zur Eingabe dient das Signal /Strobe (Pin 1).                           }
//{  Dazu mu· dieses Signal vorher auf HIGH programmiert werden.             }
//{                                                                          }
//{  An /Strobe liegt dabei das Taktsignal der Schiebelehre, wenn die        }
//{  Drucker-Datenleitung D4 HIGH ist, das Ready-Signal der Lehre, wenn      }
//{  D0 HIGH ist, und die seriellen Daten, wenn D1 HIGH ist.                 }
//{                                                                          }
//{  D2 auf HIGH aktiviert das /Request - Signal zur Schiebelehre.           }
//{                                                                          }
//{ ======================================================================== }
//
//{ ----------------------------------------------------- }
//{ Die BITS & Pieces:                                    }
//{ ----------------------------------------------------- }
//{                                                       }
//{ D0 .. D2  = [Portadr+0] Bits 0..2                     }
//{ SelectIn  = [Portadr+2] Bit 3 invertiert              }
//{ Strobe    = [Portadr+2] Bit 0 invertiert              }
//{ AutoFeed  = [Portadr+2] Bit 1 invertiert              }
//{                                                       }
//{ ----------------------------------------------------- }

#define SCHIEBESECTION  "Schiebelehre"
#define PORT            "Port"
#define SETTINGS        "Settings"
#define MPXDELAY        "MpxDelay"
#define ANZTRY          "AnzTry"
#define MAXDELAY        "MaxDelay"
#define USEIBM          "UserIBM"

extern LPSTR WINAPI GetIniName ();
#ifndef MYINI
  #define MYINI GetIniName ()
#endif
BOOL lstrncmp (LPSTR p1,LPSTR p2,int n)
  {
  int res = 0;
  for (int i = 0 ; i < n ; i++) {
    res = p2[i] - p1[i] ;
    if (res != 0) break ;
    }
  return res ;
  }

static BOOL Serial = FALSE;
static WORD SerialPort;
static char ComModeStr[50];
static WORD IniPortAdr = 0x378;

static int n;
BYTE AusByte = 0x10;
BYTE AusByte1 = 0x1E;
static WORD c_MpxDelay = 0xF0;
static WORD AnzTry = 4 ;
static BYTE OldPort0,OldPort2;
const BYTE c_MpxReady = 1;
const BYTE c_MpxData  = 2;
#define c_Strobe 1
static BYTE c_MaxDelay = 2;      // Timer Ticks 
const BYTE c_MpxClock = 8;
const BYTE c_Request  = 4;

const BYTE c_RequestData  = 6 ;
const BYTE c_RequestClock = 12 ;

BYTE c_SelectIn = 8;
BYTE c_notInit = 4;
// const BYTE c_Strobe   = 1;
BYTE c_AutoFeed = 2;


static int GetPrivateSLInt(LPSTR Name,LPSTR Def)
  {
  char InStr[40];
  GetPrivateProfileString (SCHIEBESECTION,Name,Def,
                              InStr,sizeof(InStr),
                              MYINI
                          );
  int i = 0;
  for ( LPSTR h = InStr ; ((*h >= '0') && (*h <= '9')) ; h ++) {
    i = *h - '0' + i * 10;
    }
  return i;
  }

static int GetPrivateSLHex(LPSTR Name,LPSTR Def)
  {
  char InStr[40];
  GetPrivateProfileString (SCHIEBESECTION,Name,Def,
                              InStr,sizeof(InStr),
                              MYINI
                          );
  int i = 0;
  for ( LPSTR h = InStr ; ((*h >= '0') && (*h <= '9')) || ((*h >= 'A') && (*h <= 'F')) ; h ++) {
    if ((*h >= 'A') && (*h <= 'F'))
      i = *h - 'A' + 10 + i * 16;
    else
      i = *h - '0' + i * 16;
    }
  return i;
  }

static void CheckProfile ()
  {
  static BOOL ProfileChecked;
  if (!ProfileChecked) {
    char LPTstr[32];
    GetPrivateProfileString (SCHIEBESECTION,PORT,"No",
                                LPTstr,sizeof(LPTstr),
                                MYINI
                             );
    if (lstrncmp (AnsiUpper (LPTstr),"LPT",3) == 0) {
      n = LPTstr[3] - '0' ;
      }
    else if (lstrncmp (AnsiUpper (LPTstr),"COM",3) == 0) {
      Serial = TRUE;
      SerialPort = LPTstr[3] - '0' ;
      GetPrivateProfileString (SCHIEBESECTION,SETTINGS,"9600,n,8,1",
                              ComModeStr,sizeof(ComModeStr),MYINI);
      }
    else
      n = -1;

    GetPrivateProfileString (SCHIEBESECTION,USEIBM,"No",
                                LPTstr,sizeof(LPTstr),
                                MYINI
                             );
    if (lstrcmp (LPTstr,"yes") == 0) {
      AusByte = 0x10;
      AusByte1 = 0x1E;
      }
    else {
      AusByte = 0xF0;
      AusByte1 = 0xFE;
      }
    c_MpxDelay = GetPrivateSLInt(MPXDELAY,"242");
    AnzTry = GetPrivateSLInt(ANZTRY,"4");
    c_MaxDelay = GetPrivateSLInt(MAXDELAY,"2");
    IniPortAdr = GetPrivateSLHex("PortAdr","378");

    ProfileChecked = TRUE ;
    }
  }

#define MAXWNDS 10
static HWND actWnd[MAXWNDS];
static int WndCount;
static HWND hWndAct;

#ifdef WIN32
HANDLE nCID = INVALID_HANDLE_VALUE;
#else
int nCID = -1;
#endif

DCB CommDCB;
#define TXQUEUE          0
#define RXQUEUE          1

static WORD FAR *PortAdresses;
#ifdef WIN32
static HANDLE lpId;
#else
static int lpId;
#endif
static BOOL SLInit() 
  {
  CheckProfile ();

  if (Serial) {
#ifdef WIN32
    if (nCID == INVALID_HANDLE_VALUE) {
      char ComStr[50];
      wsprintf(ComStr,"COM%d",(int)SerialPort);
      nCID = CreateFile(ComStr,
                        GENERIC_READ | GENERIC_WRITE,
                        0,                            /* comm devices must be opened w/exclusive-access */
                        NULL,                         /* no security attrs */
                        OPEN_EXISTING,                /* comm devices must use OPEN_EXISTING */
                        0,                            /* not overlapped I/O */
                        NULL);                        /* hTemplate must be NULL for comm devices */
      if (nCID == INVALID_HANDLE_VALUE) {
        MessageBeep(0);
        return FALSE;
        }

      char Com2Str[50];
      wsprintf(Com2Str,"%s:%s",LPSTR(ComStr),LPSTR(ComModeStr));
      if (BuildCommDCB(Com2Str,&CommDCB) < 0) {
        MessageBeep(0);
        return FALSE;
        }
      if (SetCommState(nCID,&CommDCB) == FALSE) {
        MessageBeep(0);
        return FALSE;
        }

      long xxx = GetTickCount();
      while ((GetTickCount() - xxx) < 500L);
      }

    PurgeComm(nCID, PURGE_TXABORT | PURGE_RXABORT	| PURGE_TXCLEAR | PURGE_RXCLEAR);
#else
    if (nCID < 0) {
      char ComStr[50];
      wsprintf(ComStr,"COM%d",(int)SerialPort);
      nCID = OpenComm(ComStr,1024,1024);
      if (nCID < 0) {
        MessageBeep(0);
        return FALSE;
        }

      char Com2Str[50];
      wsprintf(Com2Str,"%s:%s",LPSTR(ComStr),LPSTR(ComModeStr));
      if (BuildCommDCB(Com2Str,&CommDCB) < 0) {
        MessageBeep(0);
        return FALSE;
        }
      if (SetCommState(&CommDCB) < 0) {
        MessageBeep(0);
        return FALSE;
        }

      long xxx = GetTickCount();
      while ((GetTickCount() - xxx) < 500L);
      }

    FlushComm(nCID,TXQUEUE);
    FlushComm(nCID,RXQUEUE);
#endif

    return TRUE;
    }
  else {
#ifdef WIN32
    // WIN_ASSERT_TEXT(FALSE,"32 Bit: Nur serielle Schiebelehre unterstuetzt !");
    // PortAdresses = (WORD FAR *)0x0040 0008;
    PortAdresses = (WORD FAR *)0x408;
    // LPT1 mit OpenComm aufmachen
    lpId = CreateFile("LPT1",
                      GENERIC_READ | GENERIC_WRITE,
                      0,                            /* comm devices must be opened w/exclusive-access */
                      NULL,                         /* no security attrs */
                      OPEN_EXISTING,                /* comm devices must use OPEN_EXISTING */
                      0,                            /* not overlapped I/O */
                      NULL);                        /* hTemplate must be NULL for comm devices */
#else
    FP_SEG(PortAdresses) = 0x0040;
    FP_OFF(PortAdresses) = 0x0008;
    // LPT1 mit OpenComm aufmachen
    lpId = OpenComm ("LPT1",100,100);
#endif
    return TRUE ;
    }
  }

static void SLDone() 
  {
#ifdef WIN32
  if (!Serial) {
    if ((WndCount == 0) && (lpId != INVALID_HANDLE_VALUE))
      CloseHandle (lpId);
    }
#else
  if (!Serial) {
    if ((WndCount == 0) && (lpId >= 0))
      CloseComm (lpId);
    }
#endif
  }

#ifdef WIN32
#define ASM     __asm

void FAR MPXDelay ()
  {
  ASM {
    PUSH SI
    MOV   SI, c_MpxDelay
 _l_MpxDly:
    DEC   SI
    JNZ   _l_MpxDly
    POP SI
    }
  }

static WORD PortAdr;
short HWPresent()
  {
  short res;
  ASM {
    MOV DX, PortAdr

    // $AA -> Datenport, wieder einlesen, vergleichen }
    MOV AX, 0xAAAA
    out DX, AL
    in  AL, DX
    CMP AL, AH
    JNE _l_noHard

    // $55 -> Datenport, wieder einlesen, vergleichen }
    MOV AX, 0x5555
    out DX, AL
    in  AL, DX
    CMP AL, AH
    JNE _l_noHard

    //  OK, vorhanden
    MOV AX, 0x0001
    JMP _l_end

   _l_noHard:
    // nein, Portadresse ohne Bezug auf vorhandene Hardware (z.B. unter NetWare) }
    MOV AX, 0x0000
   _l_end:
    MOV res,AX 
    }
  return res;
  }

inline BYTE PortIn (WORD Addr)
  {
  BYTE res;
  ASM {
    MOV DX,Addr
    in AL,DX
    mov res,AL;
    }
  return res;
  }

inline void PortOut (WORD Addr,BYTE chartowrite)
  {
  ASM {
    MOV DX,Addr
    MOV AL,chartowrite
    out DX,AL
    }
  }

void DruckerEin ()
  {
  PortOut (PortAdr+0,OldPort0);
  MPXDelay ();
//  PortOut (PortAdr+2,OldPort2 | c_SelectIn | c_notInit);
  PortOut (PortAdr+2,0xF0 | c_SelectIn);
  MPXDelay ();
  MPXDelay ();
  MPXDelay ();
  MPXDelay ();
  MPXDelay ();
  PortOut (PortAdr+2,0xF0 | c_SelectIn | c_notInit);
  MPXDelay ();
  MPXDelay ();
  MPXDelay ();
  MPXDelay ();
  MPXDelay ();
  }

void DruckerAus ()
  {
  OldPort2 = PortIn (PortAdr+2);
  PortOut(PortAdr+2,AusByte1);          // /Stb, /AutoFd, /Init, /SelectIn auf HIGH }
  MPXDelay();
  PortOut(PortAdr+0,c_MpxReady);
  MPXDelay();
  PortOut(PortAdr+2,AusByte);          // /Stb, /AutoFd, /Init, /SelectIn auf HIGH }
  PortOut(PortAdr+0,c_MpxReady);
  MPXDelay ();
  }

short willSenden ();
short LiesMesswert(BYTE FAR *w);
BOOL CheckInterface (BYTE ParPort,BYTE FAR *M)
  {
  // BYTE p;
  BOOL res = FALSE ;

  // zulÑssige Nummer? 
  if ((ParPort < 1) || (ParPort > 3)) return FALSE ;

  // BIOS: Port vorhanden? 
  // PortAdr = PortAdresses[ParPort-1];
  PortAdr = IniPortAdr;
  if (PortAdr == 0) return FALSE ;

  // BIOS: Wenn der Port dieselbe Adresse wie ein numerisch niedrigerer hat, gibt's ihn nicht! }
  // for (p = 1 ; p <= BYTE(ParPort-1) ; p++)
  //   if (PortAdr == PortAdresses[p-1]) return FALSE ;

  OldPort0 = PortIn(PortAdr+0);

  // gibt's den Port in Hardware oder ist er nur simuliert? }
  ASM {
    CLI ;
    }
  DruckerAus ();
  res = ((willSenden()) && (LiesMesswert(M)));
  ASM {
    STI ;
    }
  return res;
  }

short willSenden () {
  short res = FALSE ;
  ASM {
    MOV   DX, PortAdr    ; PortAdr

    MOV   AH, 0xFF
    MOV   AL, c_MpxReady
    out   DX, AL         ; Schiebelehre Ready auf Strobe schalten

    INC   DX
    INC   DX

    CALL  MPXDelay

    MOV   CX,AnzTry
 _l_checkstrobe :
    in    AL, DX
    AND   AH, AL
    TEST  AH,c_Strobe
    JZ    _l_retFALSE
    CALL  MPXDelay
    LOOP  _l_checkstrobe

    MOV   AL, AH
    XOR   AH, AH

    TEST  AL, c_Strobe   ; Strobe = Schiebelehre Ready auf bit 1 -> bit 0
    JNZ   _l_retTRUE;
 _l_retFALSE :
    XOR AX,AX
    MOV   res, AX
    JMP _l_endwillsenden;
 _l_retTRUE :
    MOV   res, AX
 _l_endwillsenden :
    }
  return res ;
  }

static DWORD Ticks;
void StarteZeitMessung()
  {
  Ticks = GetTickCount();
  }

BOOL EndZeitErreicht()
  {
  return ((GetTickCount() - Ticks) > (DWORD(c_MaxDelay) * 56L));
  }

short LiesMesswert(BYTE FAR *w)
  {
  short res;
  ASM {

    MOV   DX, PortAdr    ; PortAdr

    MOV   AL, c_MpxReady
    out   DX, AL         ; Schiebelehre Ready auf Strobe schalten

    INC   DX
    INC   DX

; _l_wtRdy:
;    MOV   AX, 0x40
;    MOV   ES, AX
;    ; aktuelle Zeit lesen f. Timeout 
;    MOV   BL, ES:[0x6C]        ; TimerTicks, niederwertigstes Byte 
    PUSH  DX
    CALL  StarteZeitMessung
    POP   DX

 _l_chkRdy:
    in    AL, DX
    TEST  AL, c_Strobe
    JNZ   _l_isRdy

;    MOV   BH, BL
;    ADD   BH, c_MaxDelay      ; jetzt BL = Startzeit, BH = Endzeit 
;    MOV   AL, ES:[0x6C]
;
;    JC    _l_Test2             ; Carry von ADD: enthÑlt Zeitintervall Wert 0 ? 
;    CMP   AL, BL              ; 0 nicht enthalten - Test ob Zeit < Startzeit 
;    JB    _l_err1
;    CMP   AL, BH              ; Test, ob Zeit > Endzeit 
;    JA    _l_err1
;    JMP   _l_chkRdy
;
; _l_Test2:
;    CMP   AL, BL              ; 0 enthalten - Test ob Zeit >= Startzeit 
;    JAE   _l_chkRdy
;    CMP   AL, BH              ; Test, ob Zeit < Endzeit 
;    JBE   _l_chkRdy
;    JMP   _l_err1
;
; _l_err1:
;    JMP   _l_error

    PUSH  DX
    CALL  EndZeitErreicht
    POP   DX
    CMP   EAX, 0
    JZ    _l_chkRdy
    JMP   _l_error

 _l_isRdy:
    ; OK, Schiebelehre will Daten liefern - Anfordern & Umschalten auf Empfang! 

    DEC   DX
    DEC   DX
    MOV   AL, c_MpxClock
    out   DX, AL

    CALL  MPXDelay

    MOV   EDI, w        ; dort kommen die Daten hin 

; _l_isReady:

    ; 13 Zeichen empfangen = 1 Datensatz 

    MOV   CX, 13
    CLD

    MOV   AL, c_RequestClock

;    CLI                 ; ... ohne INTs, bis alle Nibbles da sind 

    out   DX, AL
    INC   DX
    INC   DX

 _l_rxChar:
    XOR   BL, BL

   ; ein Zeichen = 4 bits empfangen 
   ; Die Schleife fÅr die einzelnen bits ist hier 'ausgerollt' worden 

   ; -------------------- Bit 0 lesen -------------------- 

; _l_wtClkL0:           ; wir warten, bis Clk auf LOW geht = unser Bit auf 1 
    XOR   SI,SI
 _l_chkClkL0:
    in    AL, DX
    TEST  AL, c_Strobe
    JNZ   _l_rdBit0
    DEC   SI            ; Timeout-ZÑhlschleife: geht spÑtestens beim 80786 schief ... 
    JZ    _l_err2
    JMP   _l_chkClkL0

 _l_rdBit0:
    DEC   DX
    DEC   DX
    MOV   AL, c_RequestData
    out   DX, AL
    INC   DX
    INC   DX

    CALL  MPXDelay

    in    AL, DX        ; jetzt ist das Datenbit gÅltig - rein damit  
    MOV   AH, AL        ; zwischenlagern                              

    DEC   DX
    DEC   DX
    MOV   AL, c_RequestClock
    out   DX, AL
    INC   DX
    INC   DX

    CALL  MPXDelay

    TEST  AH, c_Strobe  
    JNZ   _l_wtClkH0
    OR    BL, 1         ; dieses war Bit 0 

 _l_wtClkH0:           ; ... und irgendwann wird Clk wieder High! 
    XOR   SI, SI
 _l_chkClkH0:
    in    AL, DX
    TEST  AL, c_Strobe
    JZ    _l_wtClkL1
    DEC   SI
    JZ    _l_err2
    JMP   _l_chkClkH0

   ; -------------------- Bit 1 lesen -------------------- 

 _l_wtClkL1:           ; und nun noch dreimal dasselbe ! 
    XOR   SI,SI
 _l_chkClkL1:
    in    AL, DX
    TEST  AL, c_Strobe
    JNZ   _l_rdBit1
    DEC   SI         
    JZ    _l_err2
    JMP   _l_chkClkL1

 _l_err2:
    JMP   _l_error

 _l_rdBit1:
    DEC   DX
    DEC   DX
    MOV   AL, c_RequestData
    out   DX, AL
    INC   DX
    INC   DX

    CALL  MPXDelay
  
    in    AL, DX        ; jetzt ist das Datenbit gÅltig - rein damit  
    MOV   AH, AL        ; zwischenlagern                              
  
    DEC   DX
    DEC   DX
    MOV   AL, c_RequestClock
    out   DX, AL
    INC   DX
    INC   DX
  
    CALL  MPXDelay
  
    TEST  AH, c_Strobe  
    JNZ   _l_wtClkH1
    OR    BL, 2      
  
 _l_wtClkH1:        
    XOR   SI, SI
 _l_chkClkH1:
    in    AL, DX
    TEST  AL, c_Strobe
    JZ    _l_wtClkL2
    DEC   SI
    JZ    _l_err2
    JMP   _l_chkClkH1

   ; -------------------- Bit 2 lesen -------------------- 

 _l_wtClkL2:
    XOR   SI,SI
 _l_chkClkL2:
    in    AL, DX
    TEST  AL, c_Strobe
    JNZ   _l_rdBit2
    DEC   SI         
    JZ    _l_err2
    JMP   _l_chkClkL2

 _l_rdBit2:
    DEC   DX
    DEC   DX
    MOV   AL, c_RequestData
    out   DX, AL
    INC   DX
    INC   DX

    CALL  MPXDelay

    in    AL, DX        ; jetzt ist das Datenbit gÅltig - rein damit  
    MOV   AH, AL        ; zwischenlagern                              
    DEC   DX
    DEC   DX
    MOV   AL, c_RequestClock
    out   DX, AL
    INC   DX
    INC   DX

    CALL  MPXDelay
  
    TEST  AH, c_Strobe  
    JNZ   _l_wtClkH2
    OR    BL, 4      
  
 _l_wtClkH2:        
    XOR   SI, SI
 _l_chkClkH2:
    in    AL, DX
    TEST  AL, c_Strobe
    JZ    _l_wtClkL3
    DEC   SI
    JZ    _l_error
    JMP   _l_chkClkH2
  
   ; -------------------- Bit 3 lesen -------------------- 
  
 _l_wtClkL3:
    XOR   SI,SI
 _l_chkClkL3:
    in    AL, DX
    TEST  AL, c_Strobe
    JNZ   _l_rdBit3
    DEC   SI         
    JZ    _l_error
    JMP   _l_chkClkL3
  
 _l_rdBit3:
    DEC   DX
    DEC   DX
    MOV   AL, c_RequestData
    out   DX, AL
    INC   DX
    INC   DX

    CALL  MPXDelay
    
    in    AL, DX        ; jetzt ist das Datenbit gÅltig - rein damit  
    MOV   AH, AL        ; zwischenlagern                              
    DEC   DX
    DEC   DX
    MOV   AL, c_RequestClock
    out   DX, AL
    INC   DX
    INC   DX
  
    CALL  MPXDelay
  
    TEST  AH, c_Strobe  
    JNZ   _l_wtClkH3
    OR    BL, 8      
  
 _l_wtClkH3:        
    XOR   SI, SI
 _l_chkClkH3:
    in    AL, DX
    TEST  AL, c_Strobe
    JZ    _l_storebyte
    DEC   SI
    JZ    _l_error
    JMP   _l_chkClkH3
  
 _l_rxChar1:
    JMP _l_rxChar

   ; ------ fertig --- ab damit ! ----------- 

 _l_storebyte:
    MOV   AL, BL
    STOSB
    LOOP  _l_rxChar1

;    STI
  
    DEC   DX
    DEC   DX
    MOV   AL, c_MpxReady
    out   DX, AL        ; Request inaktiv 

    MOV   ESI, w
    MOV   BX, 0x0F0F     ; prÅfen, ob die ersten 4 Bytes = $0f sind 

; _l_ChkSync:
    LODSW
    CMP   AX, BX
    JNE   _l_error
    LODSW
    CMP   AX, BX
    JNE   _l_error

; _l_ok:
    MOV   AX, 1
    JMP   _l_end

 _l_error:
    XOR   AX, AX

 _l_end:
    MOV res,AX
    }
  return res;
  }


void InterfaceAus ()
  {
  DruckerEin ();
  }


#else   // 16 BIT


#define ASM     __asm

void FAR MPXDelay ()
  {
  ASM {
    PUSH SI
    MOV   SI, c_MpxDelay
 _l_MpxDly:
    DEC   SI
    JNZ   _l_MpxDly
    POP SI
    }
  }

static WORD PortAdr;
BOOL HWPresent()
  {
  BOOL res;
  ASM {
    MOV DX, PortAdr

    // $AA -> Datenport, wieder einlesen, vergleichen }
    MOV AX, 0xAAAA
    OUT DX, AL
    IN  AL, DX
    CMP AL, AH
    JNE _l_noHard

    // $55 -> Datenport, wieder einlesen, vergleichen }
    MOV AX, 0x5555
    OUT DX, AL
    IN  AL, DX
    CMP AL, AH
    JNE _l_noHard

    //  OK, vorhanden
    MOV AX, 0x0001
    JMP _l_end

   _l_noHard:
    // nein, Portadresse ohne Bezug auf vorhandene Hardware (z.B. unter NetWare) }
    MOV AX, 0x0000
   _l_end:
    MOV res,AX 
    }
  return res;
  }

inline BYTE PortIn (WORD Addr)
  {
  BYTE res;
  ASM {
    MOV DX,Addr
    IN AL,DX
    mov res,AL;
    }
  return res;
  }

inline void PortOut (WORD Addr,BYTE chartowrite)
  {
  ASM {
    MOV DX,Addr
    MOV AL,chartowrite
    OUT DX,AL
    }
  }

void DruckerEin ()
  {
  PortOut (PortAdr+0,OldPort0);
  MPXDelay ();
//  PortOut (PortAdr+2,OldPort2 | c_SelectIn | c_notInit);
  PortOut (PortAdr+2,0xF0 | c_SelectIn);
  MPXDelay ();
  MPXDelay ();
  MPXDelay ();
  MPXDelay ();
  MPXDelay ();
  PortOut (PortAdr+2,0xF0 | c_SelectIn | c_notInit);
  MPXDelay ();
  MPXDelay ();
  MPXDelay ();
  MPXDelay ();
  MPXDelay ();
  }

void DruckerAus ()
  {
  OldPort2 = PortIn (PortAdr+2);
  PortOut(PortAdr+2,AusByte1);          // /Stb, /AutoFd, /Init, /SelectIn auf HIGH }
  MPXDelay();
  PortOut(PortAdr+0,c_MpxReady);
  MPXDelay();
  PortOut(PortAdr+2,AusByte);          // /Stb, /AutoFd, /Init, /SelectIn auf HIGH }
  PortOut(PortAdr+0,c_MpxReady);
  MPXDelay ();
  }

BOOL willSenden ();
BOOL LiesMesswert(BYTE FAR *w);
BOOL CheckInterface (BYTE ParPort,BYTE FAR *M)
  {
  BYTE p;
  BOOL res = FALSE ;

  // zulÑssige Nummer? 
  if ((ParPort < 1) || (ParPort > 3)) return FALSE ;

  // BIOS: Port vorhanden? 
  PortAdr = PortAdresses[ParPort-1];
  if (PortAdr == 0) return FALSE ;

  // BIOS: Wenn der Port dieselbe Adresse wie ein numerisch niedrigerer hat, gibt's ihn nicht! }
  for (p = 1 ; p <= BYTE(ParPort-1) ; p++)
    if (PortAdr == PortAdresses[p-1]) return FALSE ;

  OldPort0 = PortIn(PortAdr+0);

  // gibt's den Port in Hardware oder ist er nur simuliert? }
  ASM {
    CLI ;
    }
  DruckerAus ();
  res = ((willSenden()) && (LiesMesswert(M)));
  ASM {
    STI ;
    }
  return res;
  }

BOOL willSenden () {
  BOOL res = FALSE ;
  ASM {
    MOV   DX, PortAdr    ; PortAdr

    MOV   AH, 0xFF
    MOV   AL, c_MpxReady
    OUT   DX, AL         ; Schiebelehre Ready auf Strobe schalten

    INC   DX
    INC   DX

    CALL  MPXDelay

    MOV   CX,AnzTry
 _l_checkstrobe :
    IN    AL, DX
    AND   AH, AL
    TEST  AH,c_Strobe
    JZ    _l_retFALSE
    CALL  MPXDelay
    LOOP  _l_checkstrobe

    MOV   AL, AH
    XOR   AH, AH

    TEST  AL, c_Strobe   ; Strobe = Schiebelehre Ready auf bit 1 -> bit 0
    JNZ   _l_retTRUE;
 _l_retFALSE :
    XOR AX,AX
    MOV   res, AX
    JMP _l_endwillsenden;
 _l_retTRUE :
    MOV   res, AX
 _l_endwillsenden :
    }
  return res ;
  }

BOOL LiesMesswert(BYTE FAR *w)
  {
  BOOL res;
  ASM {

    MOV   DX, PortAdr    ; PortAdr

    MOV   AL, c_MpxReady
    OUT   DX, AL         ; Schiebelehre Ready auf Strobe schalten

    INC   DX
    INC   DX

; _l_wtRdy:
    MOV   AX, 0x40
    MOV   ES, AX
    ; aktuelle Zeit lesen f. Timeout 
    MOV   BL, ES:[0x6C]        ; TimerTicks, niederwertigstes Byte 

 _l_chkRdy:
    IN    AL, DX
    TEST  AL, c_Strobe
    JNZ   _l_isRdy

    MOV   BH, BL
    ADD   BH, c_MaxDelay      ; jetzt BL = Startzeit, BH = Endzeit 
    MOV   AL, ES:[0x6C]

    JC    _l_Test2             ; Carry von ADD: enthÑlt Zeitintervall Wert 0 ? 
    CMP   AL, BL              ; 0 nicht enthalten - Test ob Zeit < Startzeit 
    JB    _l_err1
    CMP   AL, BH              ; Test, ob Zeit > Endzeit 
    JA    _l_err1
    JMP   _l_chkRdy

 _l_Test2:
    CMP   AL, BL              ; 0 enthalten - Test ob Zeit >= Startzeit 
    JAE   _l_chkRdy
    CMP   AL, BH              ; Test, ob Zeit < Endzeit 
    JBE   _l_chkRdy
    JMP   _l_err1

 _l_err1:
    JMP   _l_error


 _l_isRdy:
    ; OK, Schiebelehre will Daten liefern - Anfordern & Umschalten auf Empfang! 

    DEC   DX
    DEC   DX
    MOV   AL, c_MpxClock
    OUT   DX, AL

    CALL  MPXDelay

    LES   DI, w        ; dort kommen die Daten hin 

; _l_isReady:

    ; 13 Zeichen empfangen = 1 Datensatz 

    MOV   CX, 13
    CLD

    MOV   AL, c_RequestClock

;    CLI                 ; ... ohne INTs, bis alle Nibbles da sind 

    OUT   DX, AL
    INC   DX
    INC   DX

 _l_rxChar:
    XOR   BL, BL

   ; ein Zeichen = 4 bits empfangen 
   ; Die Schleife fÅr die einzelnen bits ist hier 'ausgerollt' worden 

   ; -------------------- Bit 0 lesen -------------------- 

; _l_wtClkL0:           ; wir warten, bis Clk auf LOW geht = unser Bit auf 1 
    XOR   SI,SI
 _l_chkClkL0:
    IN    AL, DX
    TEST  AL, c_Strobe
    JNZ   _l_rdBit0
    DEC   SI            ; Timeout-ZÑhlschleife: geht spÑtestens beim 80786 schief ... 
    JZ    _l_err2
    JMP   _l_chkClkL0

 _l_rdBit0:
    DEC   DX
    DEC   DX
    MOV   AL, c_RequestData
    OUT   DX, AL
    INC   DX
    INC   DX

    CALL  MPXDelay

    IN    AL, DX        ; jetzt ist das Datenbit gÅltig - rein damit  
    MOV   AH, AL        ; zwischenlagern                              

    DEC   DX
    DEC   DX
    MOV   AL, c_RequestClock
    OUT   DX, AL
    INC   DX
    INC   DX

    CALL  MPXDelay

    TEST  AH, c_Strobe  
    JNZ   _l_wtClkH0
    OR    BL, 1         ; dieses war Bit 0 

 _l_wtClkH0:           ; ... und irgendwann wird Clk wieder High! 
    XOR   SI, SI
 _l_chkClkH0:
    IN    AL, DX
    TEST  AL, c_Strobe
    JZ    _l_wtClkL1
    DEC   SI
    JZ    _l_err2
    JMP   _l_chkClkH0

   ; -------------------- Bit 1 lesen -------------------- 

 _l_wtClkL1:           ; und nun noch dreimal dasselbe ! 
    XOR   SI,SI
 _l_chkClkL1:
    IN    AL, DX
    TEST  AL, c_Strobe
    JNZ   _l_rdBit1
    DEC   SI         
    JZ    _l_err2
    JMP   _l_chkClkL1

 _l_err2:
    JMP   _l_error

 _l_rdBit1:
    DEC   DX
    DEC   DX
    MOV   AL, c_RequestData
    OUT   DX, AL
    INC   DX
    INC   DX

    CALL  MPXDelay
  
    IN    AL, DX        ; jetzt ist das Datenbit gÅltig - rein damit  
    MOV   AH, AL        ; zwischenlagern                              
  
    DEC   DX
    DEC   DX
    MOV   AL, c_RequestClock
    OUT   DX, AL
    INC   DX
    INC   DX
  
    CALL  MPXDelay
  
    TEST  AH, c_Strobe  
    JNZ   _l_wtClkH1
    OR    BL, 2      
  
 _l_wtClkH1:        
    XOR   SI, SI
 _l_chkClkH1:
    IN    AL, DX
    TEST  AL, c_Strobe
    JZ    _l_wtClkL2
    DEC   SI
    JZ    _l_err2
    JMP   _l_chkClkH1

   ; -------------------- Bit 2 lesen -------------------- 

 _l_wtClkL2:
    XOR   SI,SI
 _l_chkClkL2:
    IN    AL, DX
    TEST  AL, c_Strobe
    JNZ   _l_rdBit2
    DEC   SI         
    JZ    _l_err2
    JMP   _l_chkClkL2

 _l_rdBit2:
    DEC   DX
    DEC   DX
    MOV   AL, c_RequestData
    OUT   DX, AL
    INC   DX
    INC   DX

    CALL  MPXDelay

    IN    AL, DX        ; jetzt ist das Datenbit gÅltig - rein damit  
    MOV   AH, AL        ; zwischenlagern                              
    DEC   DX
    DEC   DX
    MOV   AL, c_RequestClock
    OUT   DX, AL
    INC   DX
    INC   DX

    CALL  MPXDelay
  
    TEST  AH, c_Strobe  
    JNZ   _l_wtClkH2
    OR    BL, 4      
  
 _l_wtClkH2:        
    XOR   SI, SI
 _l_chkClkH2:
    IN    AL, DX
    TEST  AL, c_Strobe
    JZ    _l_wtClkL3
    DEC   SI
    JZ    _l_error
    JMP   _l_chkClkH2
  
   ; -------------------- Bit 3 lesen -------------------- 
  
 _l_wtClkL3:
    XOR   SI,SI
 _l_chkClkL3:
    IN    AL, DX
    TEST  AL, c_Strobe
    JNZ   _l_rdBit3
    DEC   SI         
    JZ    _l_error
    JMP   _l_chkClkL3
  
 _l_rdBit3:
    DEC   DX
    DEC   DX
    MOV   AL, c_RequestData
    OUT   DX, AL
    INC   DX
    INC   DX

    CALL  MPXDelay
    
    IN    AL, DX        ; jetzt ist das Datenbit gÅltig - rein damit  
    MOV   AH, AL        ; zwischenlagern                              
    DEC   DX
    DEC   DX
    MOV   AL, c_RequestClock
    OUT   DX, AL
    INC   DX
    INC   DX
  
    CALL  MPXDelay
  
    TEST  AH, c_Strobe  
    JNZ   _l_wtClkH3
    OR    BL, 8      
  
 _l_wtClkH3:        
    XOR   SI, SI
 _l_chkClkH3:
    IN    AL, DX
    TEST  AL, c_Strobe
    JZ    _l_storebyte
    DEC   SI
    JZ    _l_error
    JMP   _l_chkClkH3
  
 _l_rxChar1:
    JMP _l_rxChar

   ; ------ fertig --- ab damit ! ----------- 

 _l_storebyte:
    MOV   AL, BL
    STOSB
    LOOP  _l_rxChar1

;    STI
  
    DEC   DX
    DEC   DX
    MOV   AL, c_MpxReady
    OUT   DX, AL        ; Request inaktiv 

    LDS   SI, w
    MOV   BX, 0x0F0F     ; prÅfen, ob die ersten 4 Bytes = $0f sind 

; _l_ChkSync:
    LODSW
    CMP   AX, BX
    JNE   _l_error
    LODSW
    CMP   AX, BX
    JNE   _l_error

; _l_ok:
    MOV   AX, 1
    JMP   _l_end

 _l_error:
    XOR   AX, AX

 _l_end:
    MOV res,AX
    }
  return res;
  }


void InterfaceAus ()
  {
  DruckerEin ();
  }
#endif

static BOOL PushWnd (HWND hWnd)
  {
  if (WndCount < MAXWNDS) {
    actWnd[WndCount++] = hWnd;
    return TRUE ;
    }
  else return FALSE ;
  }

static BOOL RemoveWndFromStack (HWND hWnd)
  {
  BOOL found = FALSE ;
  for (int i = 0 ; i < WndCount ; i) {
    if (found) {
      actWnd[i] = actWnd[i+1];
      i++;
      }
    else {
      if (found = (actWnd[i] == hWnd))
        WndCount -- ;
      else
        i++ ;
      }
    }
  return found ;
  }

DLLExport BOOL _export WINAPI SetSLTimer (HWND hWnd)
  {
  BOOL res ;
  RemoveWndFromStack (hWnd);
  if (PushWnd(hWnd)) {
    if (hWndAct)
      ResetSLTimer(hWndAct);
    hWndAct = hWnd;
    res = ((SLInit ()) && (SetTimer (hWndAct,1,50,NULL) != 0)) ;
    if (!res)
      RemoveWndFromStack (hWnd);
    }
  else res = FALSE ;
  return res ;
  }

DLLExport void _export WINAPI ResetSLTimer (HWND hWnd)
  {
  if (hWndAct == hWnd) {
    SLDone ();
    KillTimer (hWndAct,1);
    hWndAct = 0;
    }
  }

DLLExport void _export WINAPI CloseSLTimer (HWND hWnd)
  {
  RemoveWndFromStack (hWnd);
  if ((WndCount == 0) && Serial) {
#ifdef WIN32
    if (nCID >= 0) {
      PurgeComm(nCID, PURGE_TXABORT | PURGE_RXABORT	| PURGE_TXCLEAR | PURGE_RXCLEAR);
      CloseHandle(nCID);
      nCID = INVALID_HANDLE_VALUE;
      }
#else
    if (nCID >= 0) {
      FlushComm(nCID,TXQUEUE);
      FlushComm(nCID,RXQUEUE);
      CloseComm(nCID);
      nCID = -1;
      }
#endif
    }
  }

static BOOL IsInPrinting = FALSE ;
static int Lptid;
BOOL OpenLPT ()
  {
  return TRUE ;
  }            

DLLExport void _export WINAPI SetStartPrinting ()
  {
  }

DLLExport void _export WINAPI SetEndPrinting ()
  {
  }

static int CharsInSLString = 0;
static char SLString[50];

static void VerarbeiteSLString(HWND hWnd)
  {
  for (int i = 0; i < CharsInSLString; i++) {
    if (SLString[i] == '\r') {
      if (i == 8) {
        if (((SLString[0] == '+') || (SLString[0] == '-')) &&
            (SLString[1] >= '0') && (SLString[1] <= '9') &&
            (SLString[2] >= '0') && (SLString[2] <= '9') &&
            (SLString[3] >= '0') && (SLString[3] <= '9') &&
            (SLString[4] >= '0') && (SLString[4] <= '9') &&
            (SLString[5] == '.') &&
            (SLString[6] >= '0') && (SLString[6] <= '9') &&
            (SLString[7] >= '0') && (SLString[7] <= '9')) {
          LONG val = (LONG(SLString[1] - '0') * 100000L) +
                     (LONG(SLString[2] - '0') * 10000L) +
                     (LONG(SLString[3] - '0') * 1000L) +
                     (LONG(SLString[4] - '0') * 100L) +
                     (LONG(SLString[6] - '0') * 10L) +
                     (LONG(SLString[7] - '0'));
          if (SLString[0] == '-')
            val = -val;
          SendMessage (hWnd,WMU_VALREAD,0,val);
          }
        }
      i++;
      for (int j = 0; i < CharsInSLString; i++, j++) {
        SLString[j] = SLString[i];
        }
      CharsInSLString -= i;
      break;
      }
    }
  }

DLLExport BOOL _export WINAPI CheckTimer (HWND hWnd,WPARAM wP,LPARAM lp) 
  {
  if (hWndAct == hWnd) {   // bin ich ueberhaupt gemeint ????
    BYTE M[13];

    CheckProfile ();

    MSG msg;
    if (!PeekMessage (&msg,NULL,0,0,PM_NOYIELD | PM_NOREMOVE)) {
      if (Serial) {
#ifdef WIN32
        if (nCID != INVALID_HANDLE_VALUE) {
          COMSTAT CommState;
          DWORD dwCommError;
          ClearCommError(nCID, &dwCommError, &CommState);
          if (CommState.cbInQue) {
            if ((CharsInSLString + CommState.cbInQue) < sizeof(SLString)) {
              DWORD AnzRead;
              ReadFile(nCID, SLString + CharsInSLString, CommState.cbInQue, &AnzRead, NULL);
              CharsInSLString += CommState.cbInQue;
              VerarbeiteSLString(hWnd);
              }
            }
          }
#else
        if (nCID >= 0) {
          COMSTAT CommState;
          GetCommError(nCID,&CommState);
          if (CommState.cbInQue) {
            if ((CharsInSLString + CommState.cbInQue) < sizeof(SLString)) {
              ReadComm(nCID, SLString + CharsInSLString, CommState.cbInQue);
              CharsInSLString += CommState.cbInQue;
              VerarbeiteSLString(hWnd);
              }
            }
          }
#endif
        }
#ifdef WIN32
      else {
        if ((n > 0) && (OpenLPT())) {
          if (CheckInterface (n,M)) {
            // Interpretieren des gelesenen Wertes
            LONG val = 0L;
            for (int i = 5 ; i <= 10 ; i++)
              val = val * 10 + M[i];
            if (M[4] > 7)
              val = -val ;
            // Weiterleiten des Messwertes
            SendMessage (hWnd,WMU_VALREAD,0,val);
            }
          // Interface noch ausschalten
          InterfaceAus() ;
          } // if (InterfaceEin())
        }
#else
      else {
        if ((n > 0) && (OpenLPT())) {
          if (CheckInterface (n,M)) {
            // Interpretieren des gelesenen Wertes
            LONG val = 0L;
            for (int i = 5 ; i <= 10 ; i++)
              val = val * 10 + M[i];
            if (M[4] > 7)
              val = -val ;
            // Weiterleiten des Messwertes
            SendMessage (hWnd,WMU_VALREAD,0,val);
            }
          // Interface noch ausschalten
          InterfaceAus() ;
          } // if (InterfaceEin())
        }
#endif
      }
    }
  return TRUE ;
  }

