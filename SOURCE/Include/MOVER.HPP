//---------------------------------------------------------------------------
// Deklaration fuer das Scrollbar-Element mit Text im Knopferl
//---------------------------------------------------------------------------
//    $Header:   P:/marille/clinicum/include/rev/mover.hpv   1.4   18 Mar 1996 16:58:06   GERHOLD  $
//    $Log:   P:/marille/clinicum/include/rev/mover.hpv  $
// 
//    Rev 1.4   18 Mar 1996 16:58:06   GERHOLD
// Statt BitButton -> MBitButton
// 
//    Rev 1.3   02 Feb 1996 11:00:40   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.2   14 Sep 1995 15:38:30   GERHOLD
// BitButton ist neu
// 
//    Rev 1.1   22 Mar 1995 15:28:26   GERHOLD
// 
//    Rev 1.0   20 Mar 1995 12:17:06   HANNES
// Initial revision.
//---------------------------------------------------------------------------
#define MS_DOWN  0x1
#define MS_UP    0x2

#define STATE_PRESSED    0x1
#define STATE_ENABLED    0x2
#define STATE_DECREASE   0x4
#define STATE_INCREASE   0x8

class FAR MButton {
 public:
  UINT fsState;
  RECT BtnRect;
  
  MButton ();
  virtual void Paint (HDC hDC);
  void InvalidateButton (HWND hWnd, BOOL bRedraw);
  virtual ~MButton ()
    {
    }

  LPVOID operator new (size_t size)
    { return GetGlobMem (size); }
  void operator delete (LPVOID obj) 
    { FreeGlobMem (obj) ; }
  };
typedef MButton FAR *LPBUTTON;


class FAR MBitButton : public MButton {
 protected:
  HBITMAP hBmp;
  int     AnzCol;
  int     AnzRow;
  int     Index;

 public:
  MBitButton::MBitButton (HBITMAP hbmp, int cols, int rows, int index);
  virtual void Paint (HDC hDC);
  };


class FAR MoveButton;
class TextButton : public MButton {
 public:
  cField FAR *field;
  int w,h,y0;
  int Format;
  BOOL Initialized;
  MoveButton FAR *Parent;

  void GetButtonExtent (HWND hWnd,int FAR *bw,int FAR *bh);
  TextButton (MoveButton FAR *p,int f)
    {
    Parent = p;
    Format = f ;
    }
  virtual void Paint (HDC hDC);
  void SetText (LPSTR lpText) { 
    if (field != NULL) {
      if (lpText != NULL) *field = lpText;
      else                *field = "" ;
      }
    }
  virtual ~TextButton ()
    {
    if (field != NULL)
      delete field ;
    }
  };
typedef TextButton FAR *LPTEXTBUTTON;


class FAR MoveButton {
 private:
  BOOL bTimerSet;
  
 protected:
  HWND  hMyWnd;                // Fensterhandle des gesamten Movers
  RECT  rcClient;              // Groesse des gesamten Steuerelementes
  int   MoveArea;              // Bereich in dem bewegt werden kann (Hoehe oder Breite)
  POINT ptCaptured;            // Mausposition im bewegten Knopf
  POINT ptOffs;                // Hilfsvariable
 
  // Hilfsvariablen fuer den Timer
  int   TimerInterval;
  int   Cnt;
  int   Incr;
  HBITMAP hBmp;               // Bitmaps fuer die beiden Knoepfe links und rechts

 public:
  BOOL  bHorz;                 // Horizontal oder Vertikal
  UINT     CurrentPos;         // Position des Knopfes in Pixel (innerhalb MoveArea)

  LPBUTTON btn[3];             // vorerst einmal 3 Stück
  LPBUTTON pCaptureButton;     // der momentan aktive Knopf

  MoveButton (BOOL bHorizontal,int Format);
  virtual ~MoveButton ();

  int   GetButtonWidth ();
  int   GetButtonHeight ();
  WORD  GetTextFormat ();     // Format fuer den Text im Knopf
  int   GetMoveArea ();

  void OnLButtonDown (POINT pt);
  void OnLButtonUp (POINT pt);
  void OnMouseMove (POINT pt);

  void PaintDecreaseButton (HDC hDC);
  void PaintIncreaseButton (HDC hDC);
  void PaintMoveButton (HDC hDC);
  void PaintMover (HDC hDC);
  void SetWindow (HWND hWnd);
  void SetMoveArea (RECT rc);

  void OnTimer (void);

  void InvalidateButton ()
    { 
    btn[2]->InvalidateButton (hMyWnd, TRUE);
    }
  void SetButtonTimer (void);
  void RemoveButtonTimer (void);

  // wird von Hannes veraendert!!!!!
          int  GetRange ()                            { return 0; }
  virtual void SetMoveRange (LONG rMin, LONG rMax)    { }
  virtual void SetMinMaxValues (LONG lMin, LONG lMax) { }

  virtual void WriteValue ()                              { }

  virtual void IncreaseValue (void)                       { }
  virtual void DecreaseValue (void)                       { }
  virtual void CalculateMoveRange (BOOL bOffset = FALSE)  { }
  virtual void CalculateMoverValue (int Size)             { }
  virtual void DoIt ()                                    { }
  virtual void GetMaxString (LPSTR maxstring) { *maxstring = '\0' ; }


  LPVOID operator new (size_t size)
    { return GetGlobMem (size); }
  void operator delete (LPVOID obj) 
    { FreeGlobMem (obj) ; }
  };
typedef MoveButton FAR *LPMOVEBUTTON;


#ifdef WIEDERMITTEST
class LongButton : public MoveButton {
 private:
  LONG  DummyValue;
  LONG  Min, Max;
  LONG  MinMove, MaxMove;
  
 public: 
  LongButton (BOOL bHorizontal) : MoveButton (bHorizontal) { DummyValue = 0; };

  // muessen vor dem Create aufgerufen werden
  virtual void SetMoveRange (LONG rMin, LONG rMax);
  virtual void SetMinMaxValues (LONG lMin, LONG lMax);

          int  GetRange ();
  virtual void CalculateMoveRange (BOOL bOffset = FALSE);

  virtual void WriteValue (LONG lValue);

  virtual void IncreaseValue (void);
  virtual void DecreaseValue (void);
  virtual void CalculateMoverValue (int Size);
  };
typedef LongButton FAR *LPLONGBUTTON;

class floatButton : public MoveButton {
 private:
  float floatValue;
  float Min, Max;
  float MinMove, MaxMove;
  float fStep;
  
 public:
  floatButton (BOOL bHorizontal) : MoveButton (bHorizontal) { floatValue = 0.0; fStep = 0.01; };

  virtual void SetMoveRange (float rMin, float rMax);
  virtual void SetMinMaxValues (float lMin, float lMax);

          float GetRange ();
  virtual void CalculateMoveRange (BOOL bOffset = FALSE);

  virtual void WriteValue (float fValue);

  virtual void IncreaseValue (void);
  virtual void DecreaseValue (void);
  virtual void CalculateMoverValue (int Size);
  };
typedef floatButton FAR *LPFLOATBUTTON;
#endif
