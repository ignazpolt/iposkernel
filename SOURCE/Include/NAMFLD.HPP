////////////////////////////////////////////////////////////
//      $ Header:       $
//      $ Log:          $
////////////////////////////////////////////////////////////
#ifndef NF_XOFF

#define NF_XOFF 6
#define NF_YOFF 6

class FAR MouseName {

 private :
  HBITMAP hBitmap;                 // Bitmap
  HBITMAP hBkBitmap;               // Bildschirm - Hintergrund
  HFONT hFnt;                      // Font, in dem geschrieben werden soll
  int xold,yold;                   // Koordinaten des alten Names fuer's loeschen
  HDC CreateMemDC (HDC hDisplay)   // Erzeugen eines Memory - Contextes
    { return CreateCompatibleDC (hDisplay) ; }
  void CreateBitmaps (HDC hDC1,HDC hDC,int width,int height)
    { hBitmap = CreateCompatibleBitmap (hDC1,width,height) ,
      hBkBitmap = CreateCompatibleBitmap (hDC,width,height) ; }
  void SelectBitmap (HDC hDC)
    { SelectObject (hDC,hBitmap); }
  void SelectBkBitmap (HDC hDC)
    { SelectObject (hDC,hBkBitmap); }
  void Blit (HDC,HDC,int,int);
  void ReadBk (HDC,HDC,int,int);
  void RestoreBk (HDC,HDC,int,int);
  void DeleteBitmaps ()
    { if (hBitmap)   DeleteObject (hBitmap) ;
      if (hBkBitmap) DeleteObject (hBkBitmap) ; }
  void GetWrPos (HWND,POINT &);

 public :
  void CreateFont (HDC);     // Font erzeugen und/oder Selektieren
  void Create (HWND,LPSTR);  // Erzeugen des Namens - Feldes
  void Show (HWND);          // Anzeigen des Namens im XOR - Modus
                             // (Position durch Asynchrones lesen der
                             // Mouseposition)
  BOOL Clear (HWND);         // abermaliges Schreiben zum Zwecke des
                             // Loeschens (wenn moeglich und noetig)

  inline void Destroy (void) { // Loeschen der Bitmaps
    if (hBitmap)   DeleteObject (hBitmap)   , hBitmap = 0 ;
    if (hBkBitmap) DeleteObject (hBkBitmap) , hBkBitmap = 0 ;
    if (hFnt)      DeleteObject (hFnt)      , hFnt = 0 ;
    }

  void Init ()
    { hFnt = NULL;
      hBitmap = NULL;
      hBkBitmap = NULL; xold = yold = -1; }
  void Exit ()
    { Destroy () ; }
  };

#endif

