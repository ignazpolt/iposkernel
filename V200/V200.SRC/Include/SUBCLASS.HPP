#ifndef SUBCLASS_INCLUDED
#define SUBCLASS_INCLUDED

  BOOL WINAPI SubClassElements (HWND hDlg,HINSTANCE hInst);
  LONG WINAPI GetCtlColor (HWND hDlg,WORD wP,LONG lP,BOOL FAR &done);
  void WINAPI ListNCPaint (HWND hWnd);

  // Zeichnen eines Kommentar - Textes
  //    (wenn ds == NULL -> Loeschen des Fonts)
  void WINAPI DrawFlaggedText (
                                  HFONT FAR *hfnt,
                                  HFONT FAR *hIfnt,
                                  DRAWITEMSTRUCT FAR *ds = NULL,
                                  LPSTR Txt = NULL,
                                  BOOL Disabled = FALSE,
                                  BOOL Kursiv = FALSE,
                                  BOOL Red = FALSE,
                                  BOOL Gray = FALSE,
                                  int xpos = 0,
                                  int FAR *Tabs = NULL,
                                  int AnzTabs = 0
                                          );
  int WINAPI MeassureFlaggedText (HFONT FAR *hfnt);

#ifndef EDW_EXTRADATA
  #define EDW_EXTRADATA
struct edw_extradata {
  BOOL isDisabled,isKursiv,isRed;
  BOOL oisDisabled,oisKursiv,oisRed;
  HFONT hFnt;
  HFONT hIFnt;
  };
typedef edw_extradata FAR *LPEDWEX;
#endif

  LONG WINAPI SpcEdWinFunc (HWND,unsigned,WORD,LONG,BOOL FAR &,
                                        edw_extradata FAR *
                                       );

#endif
