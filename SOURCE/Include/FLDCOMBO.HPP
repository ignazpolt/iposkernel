//////////////////////////////////////////////////////////////
//    Combo-Buttons für das cField
//////////////////////////////////////////////////////////////
//    $Header:   P:/marille/clinicum/include/rev/fldcombo.hpv   1.2   02 Feb 1996 11:00:30   GERHOLD  $
//    $Log:   P:/marille/clinicum/include/rev/fldcombo.hpv  $
// 
//    Rev 1.2   02 Feb 1996 11:00:30   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.1   04 Apr 1995 16:44:22   HANNES
// 
//    Rev 1.0   25 Jul 1994 09:45:26   GERHOLD
// Initial revision.
//////////////////////////////////////////////////////////////


class cFieldCombo {
 public:
  BOOL   ListIsDown;
  cField FAR *MyField;
  RECT   rcBtn;
  RECT   rcPoly;
  
  cFieldCombo (void);
  void OnSetFocus (cField FAR* field);
  void OnKillFocus (cField FAR* field);
  void OnPaint (HDC hDC, BOOL State,HWND hW);
  void BeginList (cField FAR* field);    
  void EndList (cField FAR* field);
  void OnMapChange (cField FAR *field);
  void PaintPoly (HDC hDC, HBRUSH hbr, HPEN hPen, LPPOINT pt, int Anz);
  BOOL OnLButtonDown (cField FAR* field, LPPOINT pt);

  BOOL GetBtnRect (cField *h,LPRECT r);
  };
