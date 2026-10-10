//////////////////////////////////////////////////////
//  Editieren von Bitmaps
//////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/ctool/rev/pedit.cpv   1.16   05 Oct 1998 11:06:56   Gerhold  $
//  $Log:   P:/marille/clinicum/ctool/rev/pedit.cpv  $
// 
//    Rev 1.16   05 Oct 1998 11:06:56   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.15   27 Feb 1998 20:22:48   Martin
// NOCOLLAPSE raus
// 
//    Rev 1.14   24 Apr 1997 14:10:20   Hannes
// 
//    Rev 1.13   19 Dec 1996 08:31:10   HANNES
// Palette als 4 Byte
// 
//    Rev 1.12   25 Jul 1996 19:57:04   GERHOLD
// int far *  =>  DBINT FAR *
// 
//    Rev 1.11   16 Jun 1996 18:46:30   GERHOLD
// DrawEdge -> MyDrawEdge
// 
//    Rev 1.10   02 Feb 1996 10:41:56   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.9   31 Oct 1995 13:52:20   MARTIN
// SelectPalette(hOldPal) ...
// 
//    Rev 1.8   24 Sep 1995 19:08:34   MARTIN
// 
//    Rev 1.7   20 Sep 1995 20:44:00   GERHOLD
// einfuegen von Monochromen Bitmaps korrigiert
// 
//    Rev 1.6   16 Sep 1995 16:35:20   GERHOLD
// GetNearestPaletteIndex "+1"
// 
//    Rev 1.5   16 Sep 1995 02:22:14   HANNES
// 
//    Rev 1.4   16 Sep 1995 02:14:04   GERHOLD
// 
//    Rev 1.3   12 Sep 1995 17:32:38   GERHOLD
// Einfuegen ohne Vertikale Spiegelung
// 
//    Rev 1.2   11 Sep 1995 17:37:54   HANNES
// 
//    Rev 1.1   08 Sep 1995 10:11:44   MARTIN
// kleine Aenderungen an BitEdit
// 
//    Rev 1.0   07 Sep 1995 09:02:44   HANNES
// Initial revision.
//
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <dos.h>
#include "dds32.h"
#define MODULENUM  158
#include "winass.hpp"
#ifndef MAPTYPE_GEOMETRIC
#define MAPTYPE_GEOMETRIC     1     // 1 log. Einheit = 0.04 mm
#define MAPTYPE_TYPOGRAPHIC   2     // 1 log. Einheit = 1/1440 Zoll
#endif
#include "globmem.h"
#include "cfield.hpp"
#include "wordwin.hpp"
#include "hash.hpp"
#include "toolbar.hpp"
#include "font.hpp"
#define NODDSDATA
#include "dds.hpp"
#include "data.hpp"

#pragma pack(1)
struct SetToolPalette_param {
  WORD parSize;
  union {
    HPALETTE hPal;
    DWORD dummy4Byte;
    } p;
  DWORD screen;
  DWORD Color[16];
  };
#pragma pack()

DLLExport void _export WINAPI SetToolPalette (LPVOID privData,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetToolPalette_param FAR *par = (SetToolPalette_param FAR *) param;
    WIN_ASSERT (par->parSize == sizeof(*par));
    LPLOGPALETTE lpl = LPLOGPALETTE (GetGlobMem (sizeof (*lpl) + 16 * sizeof(PALETTEENTRY)));
    lpl->palVersion = 0x300 ;
    lpl->palNumEntries = 16 ;
    for ( int i = 0 ; i < 16 ; i++) {
      DWORD FAR *clr = (DWORD FAR *) (* GetData) (privData,par->Color[i]) ;
      WIN_ASSERT (clr != NULL);
      lpl->palPalEntry[i].peRed = GetRValue(*clr);
      lpl->palPalEntry[i].peGreen = GetGValue(*clr);
      lpl->palPalEntry[i].peBlue = GetBValue(*clr);
      lpl->palPalEntry[i].peFlags = NULL ; // PC_NOCOLLAPSE ;
      }
    par->p.hPal = CreatePalette (lpl);
    LPSCREEN FAR *llps = (LPSCREEN FAR *) (* GetData) (privData,par->screen);
    WIN_ASSERT ((llps != NULL) && (*llps != NULL));
    (*llps)->SetPalette (par->p.hPal);
    (*llps)->PalUseCount ++ ;
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    SetToolPalette_param FAR *par = (SetToolPalette_param FAR *) param;
    LPSCREEN FAR *llps = (LPSCREEN FAR *) (* GetData) (privData,par->screen);
    if ((llps != NULL) && (*llps != NULL)) {
      (*llps)->SetPalette (0);
      (*llps)->PalUseCount -- ;
      }
    DeleteObject (par->p.hPal);
    }
  }

// Implementierung eines Palettentools
/////////////////////////////////////////////
void ToolPalette::FixConnection ()
  {
  (* SetConnection) (privData,Param()->Disabled,StructData);
  (* SetConnection) (privData,Param()->w, StructData);
  (* SetConnection) (privData,Param()->h, StructData);
  (* SetConnection) (privData,Param()->SelIndex, StructData);
  }
LPSTR ToolPalette::GetHelpText ()
  {
  return (LPSTR) (* GetData) (privData,Param()->Help);
  }
void ToolPalette::GetRect ()
  {
  int x0 = ToDevKoordX(tx);
  int y0 = ToDevKoordY(ty, Parent->Layer);
  SetRect (LPRECT (&ToolRect), x0, y0, 
              x0 + ToDevX(tw), 
              y0 + ToDevY(th)
          );
  if (ty >= 0)
    Parent->CheckLayerHeight (ToDevKoordY (ty) + th);
  }
BOOL ToolPalette::HitTest (LPPOINT pt)
  {
  int _x = (pt->x - ToolRect.left) / dx - 2 ;
  int _y = (pt->y - ToolRect.top) / dy ;
  if ((_x >= 0) && (_x < 8) && (_y >= 0) && (_y < 2) && (ActColor != _y * 8 + _x)) {
    ActColor = _y * 8 + _x ;
    (* SetData) (privData,Param()->SelIndex,&ActColor,sizeof(ActColor),Param());
    RECT r;
    SetRect (&r,ToolRect.left,ToolRect.top,ToolRect.left + 2 * dx,ToolRect.top + 2 * dy);
    InvalidateRect (Parent->Parent->hWndToolbar(),&r,FALSE);
    }
  return FALSE ;
  }
void ToolPalette::Invalidate (BOOL doErase)
  {
  RECT rc;

  CopyRect (&rc, LPRECT(&ToolRect));
  InflateRect (&rc, 3, 3);
  InvalidateRect (Parent->Parent->hWndToolbar(), LPRECT (&rc), doErase);
  }
void ToolPalette::Load ()
  {
  DBINT FAR *lpx = (DBINT FAR*)(* GetData)(privData, Param()->hd._x);
  DBINT FAR *lpy = (DBINT FAR*)(* GetData)(privData, Param()->hd._y);
  DBWIN_ASSERT ((lpx != NULL) && (lpy != NULL));
  tx = *lpx;
  ty = *lpy;
  DBINT FAR *lpw = (DBINT FAR *)(* GetData)(privData, Param()->w);
  DBWIN_ASSERT (lpw != NULL);
  tw = *lpw;
  DBINT FAR *lph = (DBINT FAR *)(* GetData)(privData, Param()->h);
  DBWIN_ASSERT (lph != NULL);
  th = *lph;
  dx = ToDevKoordX(tw) / 10 ;
  dy = ToDevKoordY(th) / 2 ;
  DBINT FAR *lpActColor = (DBINT FAR *)(* GetData)(privData, Param()->SelIndex);
  if (lpActColor != NULL)
    ActColor = *lpActColor;
  else
    ActColor = 1;
  GetRect ();
  }
void ToolPalette::MoveTool ()
  {
  int y0 = ToDevKoordY(ty,Parent->Layer);
  int dy = y0 - ToolRect.top;
  if (dy != 0) {
    Invalidate (TRUE);
    OffsetRect (LPRECT (&ToolRect),0,dy);
                              ToolRect.left,ToolRect.top,
    Invalidate (FALSE);
    }
  }
void ToolPalette::PaintTool (HDC hDC, HDC hmemDC)
  {
  MyDrawEdge (hDC, LPRECT(&ToolRect), MY_EDGE_HWND, MY_BF_ADJUST);

  HPALETTE hPal = Parent->Parent->hPal;
  WIN_ASSERT (hPal);
  HPALETTE hOldPal = SelectPalette (hDC,hPal,FALSE);
  RealizePalette (hDC);
  HPEN hOldPen = (HPEN)SelectObject (hDC,GetStockObject (NULL_PEN));
  COLORREF clrOld = SetBkColor (hDC,RGB(0xFF,0xFF,0xFF));
  int oldMode = SetBkMode (hDC,OPAQUE);
  for (int i = 0 ; i < 16 ; i++) {
    // Die Palettenrechtecke ...
    HBRUSH hBr;
    if (i == 0)
      hBr = (HBRUSH)SelectObject (hDC,CreateHatchBrush (HS_BDIAGONAL,RGB(0,0,0)));
    else {
      PALETTEENTRY pe;
      GetPaletteEntries (hPal,i,1,&pe);
      hBr = (HBRUSH)SelectObject (hDC,CreateSolidBrush (PALETTEINDEX(i)));
      }
    int xr = ToolRect.left + dx * ((i % 8) + 2) ;
    int yr = ToolRect.top + dy * (i / 8) ;
    Rectangle (hDC,xr,yr,xr + dx + 1,yr + dy + 1);
    if (i == ActColor) {
      // Das Aktive Rechteck zeichnen
      Rectangle (hDC,ToolRect.left,ToolRect.top,ToolRect.left + 2 * dx + 1,ToolRect.top + 2 * dy + 1);
      }
    DeleteObject (SelectObject (hDC,hBr));
    }
  SetBkMode (hDC,oldMode);
  SetBkColor (hDC,clrOld);
  SelectObject (hDC,hOldPen);
  if (hOldPal)
    SelectPalette (hDC, hOldPal, TRUE);
  }
void ToolPalette::Reset (BOOL doClear)
  {
  if (IsWindow (Parent->Parent->hWndToolbar()))
    Invalidate (TRUE);
  (* ClearConnection) (privData,Param()->Disabled,StructData);
  (* ClearConnection) (privData, Param()->w, StructData);
  (* ClearConnection) (privData, Param()->h, StructData);
  (* ClearConnection) (privData, Param()->SelIndex, StructData);
  }

/*--------------------------------------------*/
/*  Editieren eines Bitmaps                   */
/*--------------------------------------------*/
void BitEdit::FixConnection ()
  {
  (* SetConnection) (privData,Param()->Disabled,StructData);
  (* SetConnection) (privData, Param()->maxX, StructData);
  (* SetConnection)(privData, Param()->maxY, StructData);
  (* SetConnection)(privData, Param()->plane, StructData);
  (* SetConnection)(privData, Param()->SelIndex, StructData);
  (* SetConnection) (privData,Param()->bm.bmList, StructData);
  }
LPSTR BitEdit::GetHelpText ()
  {
  return (LPSTR) (* GetData) (privData,Param()->Help);
  }
void BitEdit::GetRect ()
  {
  int x0 = ToDevKoordX(tx);
  int y0 = ToDevKoordY(ty, Parent->Layer);
  if (drawGrid)
    SetRect (LPRECT (&ToolRect), x0, y0, 
                x0 + px * dx + 1, 
                y0 + py * dx + 1
            );
  else
    SetRect (LPRECT (&ToolRect), x0, y0, 
                x0 + px * dx, 
                y0 + py * dx
            );
  }
void BitEdit::InvalidateAct ()
  {
  RECT r;
  r.left   = ToolRect.left + x * dx ;
  r.top    = ToolRect.top + y * dx ;
  r.right  = r.left + dx + 1;
  r.bottom = r.top + dx + 1;
  InvalidateRect (Parent->Parent->hWndToolbar(),&r,FALSE);
  }

void BitEdit::InvalidateAct (int x,int y)
  {
  RECT r;
  r.left   = ToolRect.left + x * dx ;
  r.top    = ToolRect.top + y * dx ;
  r.right  = r.left + dx + 1;
  r.bottom = r.top + dx + 1;
  InvalidateRect (Parent->Parent->hWndToolbar(),&r,FALSE);
  }

BOOL BitEdit::HitTest (LPPOINT pt)
  {
  if (PtInRect(LPRECT(&ToolRect), *pt))
    return TRUE ;
  else
    return FALSE ;
  }
void BitEdit::Invalidate (BOOL doErase)
  {
  RECT rc;

  CopyRect (&rc, LPRECT(&ToolRect));
  InflateRect (&rc, 4, 4);
  InvalidateRect (Parent->Parent->hWndToolbar(), LPRECT (&rc), doErase);
  }

inline int GetImgByteWidth (int px)
  {
  return ((px * 4 + 31) & ~31) >> 3 ;
  }
inline int GetPictByteWidth (int type,int px)
  {
  switch (type) {
    case 0 :
      return ((px * 4 + 7) & ~7) >> 3 ;
    case 1 :
      return ((px * 32 + 7) & ~7) >> 3 ;
    }
  return ((px + 7) & ~7) >> 3 ;
  }
void BitEdit::Load ()
  {
  DBINT FAR *lpx = (DBINT FAR*)(* GetData)(privData, Param()->bm.hd._x);
  DBINT FAR *lpy = (DBINT FAR*)(* GetData)(privData, Param()->bm.hd._y);
  DBWIN_ASSERT ((lpx != NULL) && (lpy != NULL));
  tx = *lpx;
  ty = *lpy;
  DBINT FAR *maxx = (DBINT FAR *)(* GetData)(privData, Param()->maxX);
  DBINT FAR *maxy = (DBINT FAR *)(* GetData)(privData, Param()->maxY);
  DBINT FAR *lpdx = (DBINT FAR *)(* GetData)(privData, Param()->bm.w);
  DBINT FAR *lpdy = (DBINT FAR *)(* GetData)(privData, Param()->bm.h);
  DBWIN_ASSERT ((maxx != NULL) && (maxy != NULL) && (lpdx != NULL) && (lpdy != NULL)) ;
  gx = px = *lpdx;
  gy = py = *lpdy;
  int dx1 = ToDevX (*maxx) / px ;
  int dx2 = ToDevX (*maxy) / py ;
  dx = min (dx1,dx2);
  DBINT FAR *lptype = (DBINT FAR *)(* GetData)(privData, Param()->typ);
  DBWIN_ASSERT (lptype != NULL);
  type = *lptype ;
  if (type == 1) {
    DBINT FAR *lpPlane = (DBINT FAR *)(* GetData)(privData, Param()->plane);
    DBWIN_ASSERT (lpPlane != NULL);
    plane = (0x00000001) << *(lpPlane) ;
    }
  DBINT FAR *lpActColor = (DBINT FAR *)(* GetData)(privData, Param()->SelIndex);
  DBWIN_ASSERT (lpActColor != NULL);
  ActColor = *lpActColor ;

  pbw = GetPictByteWidth (type,px) ;
  lpNwBits = LPBYTE (GetGlobMem (pbw * py));
  IsEnabled = TRUE ;
  LPVOID lpoldBits = (* GetData) (privData,Param()->pict);
  if ((lpoldBits != NULL) && (GetBlockSize (lpoldBits) == GetBlockSize(lpNwBits)))
    lmemcpy (lpNwBits,lpoldBits,GetBlockSize(lpNwBits));
  if (lpoldBits == NULL)
    (* SetData ) (privData,Param()->pict,lpNwBits,GetBlockSize(lpNwBits),Param());
  GetRect ();
  obw = GetImgByteWidth (px) ;
  lpGBits = (BYTE huge *) (GetGlobMem (obw * py));
  LoadBitmap ();
  }
void BitEdit::Update ()
  {
  if (type == 1) {
    DBINT FAR *lpPlane = (DBINT FAR *)(* GetData)(privData, Param()->plane);
    DBWIN_ASSERT (lpPlane != NULL);
    plane = (0x00000001) << *(lpPlane) ;
    Invalidate (FALSE);
    }
  DBINT FAR *lpActColor = (DBINT FAR *)(* GetData)(privData, Param()->SelIndex);
  DBWIN_ASSERT (lpActColor != NULL);
  ActColor = *lpActColor ;
  if ((* IsUpdateFrom) (privData,Param()->bm.bmList)) {
    LoadBitmap();
    Invalidate (FALSE);
    }
  }
void BitEdit::MoveTool ()
  {
  int y0 = ToDevKoordY(ty,Parent->Layer);
  int dy = y0 - ToolRect.top;
  if (dy != 0) {
    Invalidate (TRUE);
    OffsetRect (LPRECT (&ToolRect),0,dy);
                              ToolRect.left,ToolRect.top,
    Invalidate (FALSE);
    }
  }
BYTE bmask[8] = { 0x80 , 0x40 , 0x20 , 0x10 , 0x08 , 0x04 , 0x02 , 0x01 } ;
inline int BitEdit::GetNewColor (int i,int j)
  {
  switch (type) {
    case 0 :    // 16 Bit
      if (i & 1)
        return * (lpNwBits + pbw * j + i / 2) & 0xF ;
      return *(lpNwBits + pbw * j + i / 2) >> 4 ;
    case 1 :
      return ((*((DWORD FAR *) (lpNwBits + pbw * j + i * 4)) & plane) != 0L) ;
    }
  return ((*(lpNwBits + pbw * j + i / 8) & bmask[i & 7]) != 0) ;
  }
inline void BitEdit::SetBit (int i,int j)
  {
  switch (type) {
    case 0 :    // 16 Bit
      if (i & 1)
        *(lpNwBits + pbw * j + i / 2) = (*(lpNwBits + pbw * j + i / 2) & 0xF0) | (BYTE(ActColor) & 0x0F) ;
      else
        *(lpNwBits + pbw * j + i / 2) = (*(lpNwBits + pbw * j + i / 2) & 0x0F) | (BYTE(ActColor) << 4) ;
      break ;
    case 1 :
      if (ActColor != 0)
        *((DWORD FAR *) (lpNwBits + pbw * j + i * 4)) |= plane ;
      else
        *((DWORD FAR *) (lpNwBits + pbw * j + i * 4)) &= ~plane ;
      break ;
    default :
      if (ActColor != 0)
        *(lpNwBits + pbw * j + i / 8) |= bmask[i & 7];
      else
        *(lpNwBits + pbw * j + i / 8) &= ~bmask[i & 7];
      break ;
    }
  }
inline void BitEdit::SetBit (int i,int j,int Color)
  {
  switch (type) {
    case 0 :    // 16 Bit
      if (i & 1)
        *(lpNwBits + pbw * j + i / 2) = (*(lpNwBits + pbw * j + i / 2) & 0xF0) | (BYTE(Color) & 0x0F) ;
      else
        *(lpNwBits + pbw * j + i / 2) = (*(lpNwBits + pbw * j + i / 2) & 0x0F) | (BYTE(Color) << 4) ;
      break ;
    case 1 :
      if (Color != 0)
        *((DWORD FAR *) (lpNwBits + pbw * j + i * 4)) |= plane ;
      else
        *((DWORD FAR *) (lpNwBits + pbw * j + i * 4)) &= ~plane ;
      break ;
    default :
      if (Color != 0)
        *(lpNwBits + pbw * j + i / 8) |= bmask[i & 7];
      else
        *(lpNwBits + pbw * j + i / 8) &= ~bmask[i & 7];
      break ;
    }
  }
void BitEdit::SetBitI (int i,int j)
  {
  SetBit (i,j);
  InvalidateAct (i,j);
  }
inline int BitEdit::GetOldColor (int i,int j)
  {
  if (i & 1)
    return *((BYTE FAR *) lpGBits + obw * (gy - j - 1) + i / 2) & 0xF ;
  return *((BYTE FAR *) lpGBits + obw * (gy - j - 1) + i / 2) >> 4 ;
  }
inline int BitEdit::GetMixColor (int i,int j)
  {
  int color = GetNewColor (i,j);
  if (color == 0) color = GetOldColor (i,j);
  return color;
  }
void BitEdit::PaintTool (HDC hDC, HDC hmemDC)
  {
  MyDrawEdge (hDC, LPRECT(&ToolRect), MY_EDGE_HWND, MY_BF_ADJUST);

  HPALETTE hPal = Parent->Parent->hPal;
  WIN_ASSERT (hPal);
  HPALETTE hOldPal = SelectPalette (hDC,hPal,FALSE);
  RealizePalette (hDC);

  HPEN hOldPen;
  if (drawGrid)
    hOldPen = (HPEN)SelectObject (hDC,GetStockObject (BLACK_PEN)) ;
  else
    hOldPen = (HPEN)SelectObject (hDC,GetStockObject (NULL_PEN)) ;

  for (int i = 0 ; i < px ; i++) {
    for (int j = 0 ; j < py ; j++) {
      RECT r;
      int x0 = ToolRect.left + i * dx ;
      int y0 = ToolRect.top + j * dx ;
      SetRect (&r,x0,y0,x0 + dx + 1,y0 + dx + 1);
      if (RectVisible (hDC,&r)) {
        SetBkColor (hDC,PALETTEINDEX(GetMixColor(i,j)));
        ExtTextOut (hDC,x0,y0,ETO_OPAQUE,&r,"",0,NULL);
        if (drawGrid) {
          MoveToEx (hDC,r.left,r.top, NULL);
          LineTo (hDC,r.left,r.bottom);
          LineTo (hDC,r.right,r.bottom);
          LineTo (hDC,r.right,r.top);
          LineTo (hDC,r.left,r.top);
          }
        }
      }
    }
  if ((Parent->Parent->ToolWithFocus == this) && (GetFocus() == Parent->Parent->hWndToolbar())) {
    HPEN hN = (HPEN)SelectObject (hDC,CreatePen (PS_SOLID,0,RGB(255,0,0)));
    SelectObject (hDC,GetStockObject (NULL_BRUSH));
    int x0 = ToolRect.left + x * dx ;
    int y0 = ToolRect.top + y * dx ;
    Rectangle (hDC,x0,y0,x0 + dx + 1,y0 + dx + 1);
    DeleteObject (SelectObject (hDC,hN));
    }
  SelectObject (hDC,hOldPen);
  if (hOldPal)
    SelectPalette (hDC, hOldPal, TRUE);
  }

// Die Listen noch aufraemen
void BitMerge::DeleteRIList ()
  {
  for ( RIList FAR *r = l ; r != NULL ; ) {
    for ( IDList FAR *i = r->idl ; i != NULL ; ) {
      IDList FAR *in = i->Next ;
      FreeGlobMem (i) ;
      i = in ;
      }
    RIList FAR *next = r->Next ;
    FreeGlobMem (r);
    r = next ;
    }
  l = NULL ;
  delete riHash ;
  riHash = NULL ;
  }
void BitEdit::Reset (BOOL doClear)
  {
  if (IsWindow (Parent->Parent->hWndToolbar()))
    Invalidate (TRUE);
  (* ClearConnection) (privData,Param()->Disabled,StructData);
  (* ClearConnection) (privData, Param()->maxX, StructData);
  (* ClearConnection)(privData, Param()->maxY, StructData);
  (* ClearConnection)(privData, Param()->plane, StructData);
  (* ClearConnection)(privData, Param()->SelIndex, StructData);
  (* SetConnection) (privData,Param()->bm.bmList, StructData);

  FreeGlobMem (lpGBits);
  FreeGlobMem (lpNwBits);

  DeleteRIList ();
  }
inline LONG ByteWidth (LONG w, WORD BitCount)
  { return (((w * (DWORD)BitCount) + 31) & ~31) >> 3; }
WORD DibNumColors (VOID FAR *pv)
  {
  int                   Bits;
  LPBITMAPINFOHEADER    lpbi;
  LPBITMAPCOREHEADER    lpbc;

  lpbi = ((LPBITMAPINFOHEADER)pv);
  lpbc = ((LPBITMAPCOREHEADER)pv);

  /*    With the BITMAPINFO format headers, the size of the palette
  *    is in biClrUsed, whereas in the BITMAPCORE - style headers, it
  *    is dependent on the bits per pixel ( = 2 raised to the power of
  *    bits/pixel).
  */
  if (lpbi->biSize != sizeof(BITMAPCOREHEADER)){
    if (lpbi->biClrUsed != 0)
      return (WORD)lpbi->biClrUsed;
    Bits = lpbi->biBitCount;
    }
  else Bits = lpbc->bcBitCount;

  switch (Bits){
    case 1:
      return 2;

    case 4:
      return 16;

    case 8:
      return 256;

    default:
      // A 24 bitcount DIB has no color table
      return 0;
    }
  }
inline BYTE FAR *hugeptr_add (BYTE FAR *p1,DWORD o)
  { 
  return (BYTE FAR *) ((BYTE huge *)p1 + o); 
  }
inline BYTE FAR *NextScanLine (BYTE FAR *px,BYTE FAR *base)
  {
  DWORD offs = (BYTE huge *) px - (BYTE huge *) base ;
  if ((offs % 4) != 0) {
    px = hugeptr_add (px,4 - (offs % 4));
    }
  return px ;
  }
void BitEdit::SetBits (GLOBALHANDLE hDIB)
  {
  LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);
  lpbi->biSizeImage = ByteWidth(lpbi->biWidth,lpbi->biBitCount)*lpbi->biHeight;
  DWORD dwColorTableSize = (DWORD)(DibNumColors(lpbi) * sizeof(RGBQUAD));
  LPSTR lpBits = ((LPSTR)lpbi) + lpbi->biSize + dwColorTableSize;
  LPLOGPALETTE lpl = LPLOGPALETTE (GetGlobMem (sizeof (*lpl) + 15 * sizeof(PALETTEENTRY)));
  lpl->palVersion = 0x300 ;
  lpl->palNumEntries = 15 ;
  GetPaletteEntries (Parent->Parent->hPal,1,15,lpl->palPalEntry);
  HPALETTE hInsPal = CreatePalette (lpl);
  if (lpbi->biBitCount == 24) {
    char huge *src = ((char huge *)lpbi) + lpbi->biSize + dwColorTableSize;
    LONG srcwidth = ByteWidth (lpbi->biWidth,24);
    for (int i = int(lpbi->biHeight - 1) ; i >= 0 ; i-- ) {
      char huge *nextsrc = src + srcwidth;
      unsigned char huge *s = (unsigned char huge *)src;
      for (int j = 0 ; j < lpbi->biWidth ; j++) {
        unsigned char b = *s++;
        unsigned char g = *s++;
        unsigned char r = *s++;
        if ((x + j < px) && (y + i < py))
          if (type > 0)
            SetBit (x + j,y + i,GetNearestPaletteIndex(hInsPal,RGB(r,g,b))+1);
          else
            SetBit (x + j,y + i,GetNearestPaletteIndex(hInsPal,RGB(r,g,b)));
        }
      src = nextsrc ;
      }
    }
  else if (lpbi->biBitCount == 8) {
    BYTE FAR *Px = ((BYTE FAR *)lpbi) + lpbi->biSize + dwColorTableSize;
    BYTE FAR *Px0 = Px ;
    for (int i = int (lpbi->biHeight - 1) ; i >= 0 ; i -- ) {
      for (int j = 0 ; j < lpbi->biWidth ; j++) {
        if ((x + j < px) && (y + i < py)) {
          RGBQUAD FAR *q = (RGBQUAD FAR *) (lpbi + 1) + *Px;
          if (type > 0)
            SetBit (x + j,y + i,GetNearestPaletteIndex(hInsPal,RGB(q->rgbRed,q->rgbGreen,q->rgbBlue)));
          else
            SetBit (x + j,y + i,GetNearestPaletteIndex(hInsPal,RGB(q->rgbRed,q->rgbGreen,q->rgbBlue))+1);
          }
        Px = hugeptr_add (Px,1);
        }
      Px = NextScanLine (Px,Px0);
      }
    }
  DeleteObject (hInsPal);
  FreeGlobMem (lpl);
  }
#define WIDTHBYTES(bits)      (((bits) + 31) / 32 * 4)
#define IS_WIN30_DIB(lpbi)  ((*(LPDWORD) (lpbi)) == sizeof (BITMAPINFOHEADER))
void InitBitmapInfoHeader (LPBITMAPINFOHEADER lpBmInfoHdr,
                                        DWORD dwWidth,
                                        DWORD dwHeight,
                                          int nBPP)
  {
  lmemset (lpBmInfoHdr, 0, sizeof (BITMAPINFOHEADER));

  lpBmInfoHdr->biSize      = sizeof (BITMAPINFOHEADER);
  lpBmInfoHdr->biWidth     = dwWidth;
  lpBmInfoHdr->biHeight    = dwHeight;
  lpBmInfoHdr->biPlanes    = 1;

  if (nBPP <= 1)
     nBPP = 1;
  else if (nBPP <= 4)
     nBPP = 4;
  else if (nBPP <= 8)
     nBPP = 8;
  else
     nBPP = 24;

  lpBmInfoHdr->biBitCount  = nBPP;
  lpBmInfoHdr->biSizeImage = WIDTHBYTES (dwWidth * nBPP) * dwHeight;
  }
static WORD PaletteSize (LPSTR lpbi)
  {
  if (IS_WIN30_DIB (lpbi))
     return (DibNumColors (lpbi) * sizeof (RGBQUAD));
  else
     return (DibNumColors (lpbi) * sizeof (RGBTRIPLE));
  }
LPSTR FindDIBBits (LPSTR lpbi)
  {
  return (lpbi + *(LPDWORD)lpbi + PaletteSize (lpbi));
  }
HANDLE BitmapToDIB (HBITMAP hBitmap, HPALETTE hPal)
  {
  BITMAP             Bitmap;
  BITMAPINFOHEADER   bmInfoHdr;
  LPBITMAPINFOHEADER lpbmInfoHdr;
  LPSTR              lpBits;
  HDC                hMemDC;
  HANDLE             hDIB;
  HPALETTE           hOldPal = NULL;

     // Do some setup -- make sure the Bitmap passed in is valid,
     //  get info on the bitmap (like its height, width, etc.),
     //  then setup a BITMAPINFOHEADER.

  if (!hBitmap)
    return NULL;

  if (!GetObject (hBitmap, sizeof (Bitmap), (LPSTR) &Bitmap))
    return NULL;

  InitBitmapInfoHeader (&bmInfoHdr,
                        Bitmap.bmWidth,
                        Bitmap.bmHeight,
                        Bitmap.bmPlanes * Bitmap.bmBitsPixel);


  // Now allocate memory for the DIB.  Then, set the BITMAPINFOHEADER
  //  into this memory, and find out where the bitmap bits go.

  hDIB = GlobalAlloc (GHND, sizeof (BITMAPINFOHEADER) +
            PaletteSize ((LPSTR) &bmInfoHdr) + bmInfoHdr.biSizeImage);

  if (!hDIB)
     return NULL;

  lpbmInfoHdr  = (LPBITMAPINFOHEADER) GlobalLock (hDIB);
  *lpbmInfoHdr = bmInfoHdr;
  lpBits       = FindDIBBits ((LPSTR) lpbmInfoHdr);


     // Now, we need a DC to hold our bitmap.  If the app passed us
     //  a palette, it should be selected into the DC.

  hMemDC       = GetDC (NULL);

  if (hPal) {
    hOldPal = SelectPalette (hMemDC, hPal, FALSE);
    RealizePalette (hMemDC);
    }



  // Were finally ready to get the DIB.  Call the driver and let
  //  it party on our bitmap.  It will fill in the color table,
  //  and bitmap bits of our global memory block.

  if (!GetDIBits (hMemDC,
                  hBitmap,
                  0,
                  Bitmap.bmHeight,
                  lpBits,
                  (LPBITMAPINFO) lpbmInfoHdr,
                  DIB_RGB_COLORS)) {
    GlobalUnlock (hDIB);
    GlobalFree (hDIB);
    hDIB = NULL;
    }
  else
     GlobalUnlock (hDIB);


  // Finally, clean up and return.

  if (hOldPal)
    SelectPalette (hMemDC, hOldPal, FALSE);

  ReleaseDC (NULL, hMemDC);

  return hDIB;
  }

void BitEdit::InsertFromClipboard ()
  {
  HBITMAP    hBitmap;
  HPALETTE   hPal;
  if (OpenClipboard (GetFocus ())) {
    if (IsClipboardFormatAvailable (CF_BITMAP)) {
      hBitmap = (HBITMAP)GetClipboardData (CF_BITMAP);

      if (IsClipboardFormatAvailable (CF_PALETTE))
        hPal = (HPALETTE)GetClipboardData (CF_PALETTE);
      else
        hPal = (HPALETTE)GetStockObject (DEFAULT_PALETTE);

      GLOBALHANDLE hDIB = BitmapToDIB (hBitmap, hPal);
      if (hDIB) {
        SetBits (hDIB);
        GlobalFree (hDIB);
        }
      }
    CloseClipboard ();
    }
  }

BOOL BitEdit::OnChar (WORD wP)
  {
  switch (wP) {
    case VK_DOWN :
      if (y < py - 1) {
        InvalidateAct ();
        y += 1 ;
        if (GetKeyState (VK_SHIFT)) SetBit (x,y);
        InvalidateAct ();
        }
      break ;
    case VK_UP :
      if (y > 0) {
        InvalidateAct ();
        y -= 1 ;
        if (GetKeyState (VK_SHIFT)) SetBit (x,y);
        InvalidateAct ();
        }
      break ;
    case VK_RIGHT :
      if (x < px - 1) {
        InvalidateAct ();
        x += 1 ;
        if (GetKeyState (VK_SHIFT)) SetBit (x,y);
        InvalidateAct ();
        }
      break ;
    case VK_LEFT :
      if (x > 0) {
        InvalidateAct ();
        x -= 1 ;
        if (GetKeyState (VK_SHIFT)) SetBit (x,y);
        InvalidateAct ();
        }
      break ;
    case VK_SPACE :
      InvalidateAct ();
      SetBit (x,y);
      (* SetData ) (privData,Param()->pict,lpNwBits,GetBlockSize(lpNwBits),Param());
      break ;
    case VK_INSERT :
      InsertFromClipboard ();
      Invalidate (FALSE);
      break ;
    default :
      return FALSE ;
    }
  return TRUE ;
  }

void BitEdit::PaintLine ()
  {
  if ((x1 != x) || (y1 != y)) {
    HDC hDC = GetDC (Parent->Parent->hWndToolbar());
    HPEN hOldPen = (HPEN)SelectObject (hDC,GetStockObject (WHITE_PEN));
    int oldMode = SetROP2 (hDC,R2_XORPEN);
    MoveToEx (hDC,ToolRect.left + x * dx + dx / 2,ToolRect.top + y * dx + dx / 2, NULL);
    LineTo (hDC,ToolRect.left + x1 * dx + dx / 2,ToolRect.top + y1 * dx + dx / 2);
    SetROP2 (hDC,oldMode);
    SelectObject (hDC,hOldPen);
    ReleaseDC (Parent->Parent->hWndToolbar(),hDC);
    }
  }

void BitEdit::PaintRect ()
  {
  if ((x1 != x) || (y1 != y)) {
    HDC hDC = GetDC (Parent->Parent->hWndToolbar());
    HPEN hOldPen = (HPEN)SelectObject (hDC,GetStockObject (WHITE_PEN));
    HBRUSH hOldBrush = (HBRUSH)SelectObject (hDC,GetStockObject (NULL_BRUSH));
    int oldMode = SetROP2 (hDC,R2_XORPEN);
    Rectangle (hDC,ToolRect.left + x * dx + dx / 2,ToolRect.top + y * dx + dx / 2,ToolRect.left + x1 * dx + dx / 2,ToolRect.top + y1 * dx + dx / 2);
    SetROP2 (hDC,oldMode);
    SelectObject (hDC,hOldBrush);
    SelectObject (hDC,hOldPen);
    ReleaseDC (Parent->Parent->hWndToolbar(),hDC);
    }
  }

struct FInfo {
  FInfo FAR *Next;
  int x;
  int y;
  };
static FInfo FAR *ffirst;
void PutFifo (int x,int y)
  {
  FInfo FAR *n = (FInfo FAR *) GetGlobMem (sizeof(*n)) ;
  n->x = x ;
  n->y = y ;
  n->Next = ffirst ;
  ffirst = n ;
  }
BOOL GetFifo (int FAR *x,int FAR *y)
  {
  if (ffirst) {
    *x = ffirst->x ;
    *y = ffirst->y ;
    FInfo FAR *h = ffirst ;
    ffirst = ffirst->Next ;
    FreeGlobMem (h);
    return TRUE ;
    }
  else
    return FALSE ;
  }
BOOL BitEdit::IsPixelSet (int x,int y)
  {
  return FP[y * px + x] ;
  }
void BitEdit::MarkPixelSet (int x,int y)
  {
  FP[y * px + x] = TRUE ;
  }
void BitEdit::FillPixel (int x,int y,int color)
  {
  PutFifo (x,y);
  for ( ; GetFifo (&x,&y) ; ) {
    if ((GetMixColor (x,y) == color) && (!IsPixelSet(x,y))) {
      SetBitI (x,y);
      MarkPixelSet (x,y);
      if (x < px - 1) PutFifo (x+1,y);
      if (x > 0) PutFifo (x-1,y);
      if (y < py - 1) PutFifo (x,y+1);
      if (y > 0) PutFifo (x,y-1);
      }
    }
  }

void BitEdit::On_LButtonDown (LPPOINT pt)
  {
  DenyBusyCursor();
  switch (EditMode) {
    case BMODE_SETFOCUS  :
      InvalidateAct ();
      x = (pt->x - ToolRect.left) / dx ;
      y = (pt->y - ToolRect.top) / dx ;
      InvalidateAct ();
      break ;
    case BMODE_SETPOINT  :
      InvalidateAct ();
      x = (pt->x - ToolRect.left) / dx ;
      y = (pt->y - ToolRect.top) / dx ;
      SetBit (x,y);
      (* SetData ) (privData,Param()->pict,lpNwBits,GetBlockSize(lpNwBits),Param());
      InvalidateAct ();
      break ;
    case BMODE_SETLINE   :
    case BMODE_SETRECT   :
      InvalidateAct ();
      x = (pt->x - ToolRect.left) / dx ;
      y = (pt->y - ToolRect.top) / dx ;
      x1 = x ; y1 = y ;
      InvalidateAct ();
      break ;
    case BMODE_FILL      :
      {
      InvalidateAct ();
      x = (pt->x - ToolRect.left) / dx ;
      y = (pt->y - ToolRect.top) / dx ;
      int color = GetMixColor (x,y);
      FP = LPSTR(GetGlobMem (px * py)) ;
      FillPixel (x,y,color);
      (* SetData ) (privData,Param()->pict,lpNwBits,GetBlockSize(lpNwBits),Param());
      FreeGlobMem (FP);
      InvalidateAct ();
      }
      break ;
    }
  }

int BitEdit::ClipX(int x)
  {
  return max (0,min(x,px-1)) ;
  }
int BitEdit::ClipY(int y)
  {
  return max (0,min(y,py-1)) ;
  }

void BitEdit::On_MouseMove (LPPOINT pt)
  {
  int nx,ny;
  switch (EditMode) {
    case BMODE_SETPOINT  :
      nx = ClipX((pt->x - ToolRect.left) / dx) ;
      ny = ClipY((pt->y - ToolRect.top) / dx) ;
      if ((nx != x) || (ny != y)) {
        InvalidateAct ();
        x = nx , y = ny ;
        SetBit (x,y);
        (* SetData ) (privData,Param()->pict,lpNwBits,GetBlockSize(lpNwBits),Param());
        InvalidateAct ();
        }
      break ;
    case BMODE_SETLINE   :
      nx = ClipX((pt->x - ToolRect.left) / dx) ;
      ny = ClipY((pt->y - ToolRect.top) / dx) ;
      if ((nx != x1) || (ny != y1)) {
        PaintLine () ;
        x1 = nx , y1 = ny ;
        PaintLine () ;
        }
      break ;
    case BMODE_SETRECT   :
      nx = ClipX((pt->x - ToolRect.left) / dx) ;
      ny = ClipY((pt->y - ToolRect.top) / dx) ;
      if ((nx != x1) || (ny != y1)) {
        PaintRect () ;
        x1 = nx , y1 = ny ;
        PaintRect () ;
        }
      break ;
    }
  }

void BitEdit::SetLine ()
  {
  if ((x1 != x) || (y1 != y)) {
    double ddx = x1 - x ;
    double ddy = y1 - y ;
    if (fabs(ddx) > fabs(ddy)) {
      if (ddx > 0.0) {
        for (int i = 0 ; i <= (x1 - x) ; i++) {
          SetBitI (x + i,int (double(y) + double(i) * ddy / ddx + 0.5));
          }
        }
      else {
        for (int i = 0 ; i <= (x - x1) ; i++) {
          SetBitI (x1 + i,int (double(y1) + double(i) * ddy / ddx + 0.5));
          }
        }
      }
    else {
      if (ddy > 0.0) {
        for (int i = 0 ; i <= (y1 - y) ; i++) {
          SetBitI (int (double(x) + double(i) * ddx / ddy + 0.5),y + i);
          }
        }
      else {
        for (int i = 0 ; i <= (y - y1) ; i++) {
          SetBitI (int (double(x1) + double(i) * ddx / ddy + 0.5),y1 + i);
          }
        }
      }
    }
  else
    SetBitI (x,y);
  }

void BitEdit::SetRectangle ()
  {
  if ((x1 != x) || (y1 != y)) {
    for (int i = min(x,x1) ; i <= max(x,x1) ; i++) {
      for (int j = min(y,y1) ; j <= max(y,y1) ; j++) {
        SetBitI (i,j);
        }
      }
    }
  }

BOOL BitEdit::On_LButtonUp (LPPOINT pt)
  {
  AllowBusyCursor();
  switch (EditMode) {
    case BMODE_SETLINE   :
      PaintLine () ;
      x1 = ClipX((pt->x - ToolRect.left) / dx) ;
      y1 = ClipY((pt->y - ToolRect.top) / dx) ;
      SetLine () ;
      x = x1 ;
      y = y1 ;
      x1 = y1 = -1 ;
      (* SetData ) (privData,Param()->pict,lpNwBits,GetBlockSize(lpNwBits),Param());
      break ;
    case BMODE_SETRECT   :
      PaintRect () ;
      x1 = ClipX((pt->x - ToolRect.left) / dx) ;
      y1 = ClipY((pt->y - ToolRect.top) / dx) ;
      SetRectangle () ;
      x = x1 ;
      y = y1 ;
      x1 = y1 = -1 ;
      (* SetData ) (privData,Param()->pict,lpNwBits,GetBlockSize(lpNwBits),Param());
      break ;
    }
  return TRUE ;
  }

#pragma pack(1)
struct SetBitEditMode_param {
  WORD parSize;
  DWORD tool;
  DWORD mode;
  };
#pragma pack()

DLLExport void _export WINAPI SetBitEditMode (LPVOID privData,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetBitEditMode_param FAR *par = (SetBitEditMode_param FAR *) param;
    BitEdit FAR * FAR * lpbe = (BitEdit FAR * FAR *) (* GetData) (privData,par->tool);
    DBINT FAR *mode = (DBINT FAR *)((* GetData) (privData,par->mode));
    if ((lpbe != NULL) && (*lpbe != NULL) && (mode != NULL)) {
      switch (*mode) {
        case BMODE_TOGGLEGRID :
          (*lpbe) -> drawGrid = !(*lpbe) -> drawGrid ;
          (*lpbe) -> Invalidate(TRUE);
          break ;
        default :
          (*lpbe) -> EditMode = *mode ;
          (*lpbe) -> x1 = -1 ;
          (*lpbe) -> y1 = -1 ;
          break ;
        }
      }
    }
  }

/*--------------------------------------*/
/*        Bitmap - Mischoperationen     */
/*--------------------------------------*/
void BitMerge::EmptyRect (LPRECT r)
  {
  for (int i = r->top ; i < r->bottom ; i++) {
    BYTE huge *scstart = lpGBits + DWORD(gy - 1 - i) * DWORD(obw) + r->left / 2;
    BYTE huge *scend = lpGBits + DWORD(gy - 1 - i) * DWORD(obw) + r->right / 2;
#ifndef WIN32
    if (FP_SEG(scstart) == FP_SEG(scend))
#endif
      lmemset (scstart,'\0',LPSTR(scend) - LPSTR(scstart));
#ifndef WIN32
    else
      for (BYTE huge *h = scstart ; h < scend ; *h++ = '\0') ;
#endif
    }
  }
// 16 Farben
void BitMerge::AB_16L (LPRECT r,BYTE FAR * source,BOOL mVert)
  {
  for (int i = r->top ; i < r->bottom ; i++ ) {
    BYTE huge *scstart;
    BYTE huge *scend;
    if (mVert) {
      int i1 = r->bottom + r->top - 1 - i ;
      scstart = lpGBits + DWORD(gy - 1 - i1) * DWORD(obw) + r->left / 2;
      scend = lpGBits + DWORD(gy - 1 - i1) * DWORD(obw) + r->right / 2;
      }
    else {
      scstart = lpGBits + DWORD(gy - 1 - i) * DWORD(obw) + r->left / 2;
      scend = lpGBits + DWORD(gy - 1 - i) * DWORD(obw) + r->right / 2;
      }
#ifndef WIN32
    if (FP_SEG(scstart) == FP_SEG(scend)) {
#endif
      for (BYTE FAR *h = scstart ; h < scend ; ) {
        if ((*source & 0x0F) != 0) {  // niederes Nibbel gesetzt
          if ((*source & 0xF0) != 0)
            *h ++ = *source ++ ;    // beide Nibbel gesetzt
          else
            *h ++ = (*h & 0xF0) | *source++ ; // nur niederes Nibbel gesetzt
          }
        else {
          if ((*source & 0xF0) != 0)
            *h ++ = (*h & 0x0F) | *source++ ;  // nur hohes Nibbel gesetzt
          else
            h++ , source ++ ;
          }
        }
#ifndef WIN32
      }
    else {
      for (BYTE huge *h = scstart ; h < scend ; ) {
        if ((*source & 0x0F) != 0) {
          if ((*source & 0xF0) != 0)
            *h ++ = *source ++ ;    // source voll gesetzt
          else
            *h ++ = (*h & 0xF0) | *source++ ; // nur niederes Nibbel gesetzt
          }
        else {
          if ((*source & 0xF0) != 0)
            *h++ = (*h & 0x0F) | *source++ ;  // nur hohes Nibbel gesetzt
          else
            h++ , source ++ ;
          }
        }
      }
#endif
    }
  }
void BitMerge::AB_16R (LPRECT r,BYTE FAR * bsource,BOOL mVert)
  {
  for (int i = r->top ; i < r->bottom ; i++ ) {
    BYTE huge *scstart;
    BYTE huge *scend;
    if (mVert) {
      int i1 = r->bottom + r->top - 1 - i ;
      scstart = lpGBits + DWORD(gy - 1 - i1) * DWORD(obw) + r->left / 2;
      scend = lpGBits + DWORD(gy - 1 - i1) * DWORD(obw) + r->right / 2;
      }
    else {
      scstart = lpGBits + DWORD(gy - 1 - i) * DWORD(obw) + r->left / 2;
      scend = lpGBits + DWORD(gy - 1 - i) * DWORD(obw) + r->right / 2;
      }
    BYTE FAR *source = bsource + (i - r->top + 1) * (r->right - r->left) / 2 - 1 ;
#ifndef WIN32
    if (FP_SEG(scstart) == FP_SEG(scend)) {
#endif
      for (BYTE FAR *h = scstart ; h < scend ; ) {
        if ((*source & 0x0F) != 0) {  // niederes Nibbel gesetzt
          if ((*source & 0xF0) != 0)
            *h ++ = (*source >> 4) | (*source << 4) , source -- ;    // beide Nibbel gesetzt
          else {
            *h ++ = (*h & 0x0F) | (*source << 4) , source -- ; // nur niederes Nibbel gesetzt
            }
          }
        else {
          if ((*source & 0xF0) != 0)
            *h ++ = (*h & 0xF0) | (*source >> 4) , source -- ;  // nur hohes Nibbel gesetzt
          else
            h++ , source -- ;
          }
        }
#ifndef WIN32
      }
    else {
      for (BYTE huge *h = scstart ; h < scend ; ) {
        if ((*source & 0x0F) != 0) {  // niederes Nibbel gesetzt
          if ((*source & 0xF0) != 0)
            *h ++ = (*source >> 4) | (*source << 4) , source -- ;    // beide Nibbel gesetzt
          else {
            *h ++ = (*h & 0x0F) | (*source << 4) , source -- ; // nur niederes Nibbel gesetzt
            }
          }
        else {
          if ((*source & 0xF0) != 0)
            *h ++ = (*h & 0xF0) | (*source >> 4) , source -- ;  // nur hohes Nibbel gesetzt
          else
            h++ , source -- ;
          }
        }
      }
#endif
    }
  }
void BitMerge::AB_32L (LPRECT r,DWORD plane,DWORD FAR * source,BOOL mVert,int Color)
  {
  // 32 Bit -> mit Plane AND ...
  BYTE nColor = BYTE (Color);
  BYTE hColor = BYTE (Color) << 4 ;
  BYTE bColor = nColor | hColor ;
  for (int i = r->top ; i < r->bottom ; i++) {
    BYTE huge *scstart;
    BYTE huge *scend;
    if (mVert) {
      int i1 = r->bottom + r->top - 1 - i ;
      scstart = lpGBits + DWORD(gy - 1 - i1) * DWORD(obw) + r->left / 2;
      scend = lpGBits + DWORD(gy - 1 - i1) * DWORD(obw) + r->right / 2;
      }
    else {
      scstart = lpGBits + DWORD(gy - 1 - i) * DWORD(obw) + r->left / 2;
      scend = lpGBits + DWORD(gy - 1 - i) * DWORD(obw) + r->right / 2;
      }
#ifndef WIN32
    if (FP_SEG(scstart) == FP_SEG(scend)) {
#endif
      for (BYTE FAR *h = scstart ; h < scend ; ) {
        if ((*source ++ & plane) != 0L) {
          // niederes Nibbel gesetzt
          if ((*source ++ & plane) != 0L)
            // hohes und niederes Nibbel gesetzt
            *h++ = bColor ;
          else
            *h ++ = (*h & 0x0F) | hColor ;
          }
        else {
          if ((*source ++ & plane) != 0L)
            *h++ = (*h & 0xF0) | nColor ;
          else
            h++ ; // voll transparent
          }
        }
#ifndef WIN32
      }
    else {
      for (BYTE huge *h = scstart ; h < scend ; ) {
        if ((*source ++ & plane) != 0L) {
          // niederes Nibbel gesetzt
          if ((*source ++ & plane) != 0L)
            // hohes und niederes Nibbel gesetzt
            *h++ = bColor ;
          else
            *h ++ = (*h & 0x0F) | hColor ;
          }
        else {
          if ((*source ++ & plane) != 0L)
            *h++ = (*h & 0xF0) | nColor ;
          else
            h++ ; // voll transparent
          }
        }
      }
#endif
    }
  }
void BitMerge::AB_32R (LPRECT r,DWORD plane,DWORD FAR * bsource,BOOL mVert,int Color)
  {
  // 32 Bit -> mit Plane AND ...
  BYTE nColor = BYTE (Color);
  BYTE hColor = BYTE (Color) << 4 ;
  BYTE bColor = nColor | hColor ;
  for (int i = r->top ; i < r->bottom ; i++) {
    BYTE huge *scstart;
    BYTE huge *scend;
    if (mVert) {
      int i1 = r->bottom + r->top - 1 - i ;
      scstart = lpGBits + DWORD(gy - 1 - i1) * DWORD(obw) + r->left / 2;
      scend = lpGBits + DWORD(gy - 1 - i1) * DWORD(obw) + r->right / 2;
      }
    else {
      scstart = lpGBits + DWORD(gy - 1 - i) * DWORD(obw) + r->left / 2;
      scend = lpGBits + DWORD(gy - 1 - i) * DWORD(obw) + r->right / 2;
      }
    DWORD FAR * source = bsource + (i - r->top + 1) * (r->right - r->left) - 1 ;
#ifndef WIN32
    if (FP_SEG(scstart) == FP_SEG(scend)) {
#endif
      for (BYTE FAR *h = scstart ; h < scend ; ) {
        if ((*source -- & plane) != 0L) {
          // hohes Nibbel gesetzt
          if ((*source -- & plane) != 0L)
            // hohes und niederes Nibbel gesetzt
            *h++ = bColor ;
          else
            *h ++ = (*h & 0x0F) | hColor ;
          }
        else {
          if ((*source -- & plane) != 0L)
            *h++ = (*h & 0xF0) | nColor ;
          else
            h++ ; // voll transparent
          }
        }
#ifndef WIN32
      }
    else {
      for (BYTE huge *h = scstart ; h < scend ; ) {
        if ((*source -- & plane) != 0L) {
          // hohes Nibbel gesetzt
          if ((*source -- & plane) != 0L)
            // hohes und niederes Nibbel gesetzt
            *h++ = bColor ;
          else
            *h ++ = (*h & 0x0F) | hColor ;
          }
        else {
          if ((*source -- & plane) != 0L)
            *h++ = (*h & 0xF0) | nColor ;
          else
            h++ ; // voll transparent
          }
        }
      }
#endif
    }
  }
void BitMerge::AB_1L (LPRECT r,BYTE FAR * bsource,BOOL mVert,int Color)
  {
  static BYTE rnOffs[4] = { 0x40 , 0x10 , 0x04 , 0x01 } ;
  static BYTE rhOffs[4] = { 0x80 , 0x20 , 0x08 , 0x02 } ;
  BYTE nColor = BYTE (Color);
  BYTE hColor = BYTE (Color) << 4 ;
  BYTE bColor = nColor | hColor ;
  BYTE rColor[256],rMask[256];
  rColor[0] = 0 ;
  rMask[0] = 0xFF ;
  BYTE sMask[4];
  for (int i = 0 ; i < 4 ; i++) {
    rColor[rnOffs[i]] = nColor ;
    rColor[rhOffs[i]] = hColor ;
    rColor[rhOffs[i] + rnOffs[i]] = bColor ;
    rMask[rnOffs[i]] = 0xF0 ;
    rMask[rhOffs[i]] = 0x0F ;
    rMask[rhOffs[i] + rnOffs[i]] = 0 ;
    sMask[i] = rnOffs[i] + rhOffs[i] ;
    }
  int lw = ((r->right - r->left + 7) & ~7) >> 3 ;
  for (i = r->top ; i < r->bottom ; i++) {
    BYTE huge *scstart;
    BYTE huge *scend;
    if (mVert) {
      int i1 = r->bottom + r->top - 1 - i ;
      scstart = lpGBits + DWORD(gy - 1 - i1) * DWORD(obw) + r->left / 2;
      scend = lpGBits + DWORD(gy - 1 - i1) * DWORD(obw) + r->right / 2;
      }
    else {
      scstart = lpGBits + DWORD(gy - 1 - i) * DWORD(obw) + r->left / 2;
      scend = lpGBits + DWORD(gy - 1 - i) * DWORD(obw) + r->right / 2;
      }
    BYTE FAR *source = bsource + (i - r->top) * lw ;
    int j = 0 ;
#ifndef WIN32
    if (FP_SEG(scstart) == FP_SEG(scend)) {
#endif
      for (BYTE FAR *h = scstart ; h < scend ; ) {
        BYTE sx = *source & sMask[j];
        *h++ = (*h & rMask[sx]) | rColor[sx] ;
        if (j < 3) j ++ ;
        else {
          j = 0 ;
          source ++ ;
          }
        }
#ifndef WIN32
      }
    else {
      for (BYTE huge *h = scstart ; h < scend ; ) {
        BYTE sx = *source & sMask[j];
        *h++ = (*h & rMask[sx]) | rColor[sx] ;
        if (j < 3) j ++ ;
        else {
          j = 0 ;
          source ++ ;
          }
        }
      }
#endif
    }
  }
void BitMerge::AB_1R (LPRECT r,BYTE FAR * bsource,BOOL mVert,int Color)
  {
  static BYTE rnOffs[4] = { 0x80 , 0x20 , 0x08 , 0x02 } ;
  static BYTE rhOffs[4] = { 0x40 , 0x10 , 0x04 , 0x01 } ;
  BYTE nColor = BYTE (Color);
  BYTE hColor = BYTE (Color) << 4 ;
  BYTE bColor = nColor | hColor ;
  BYTE rColor[256],rMask[256];
  rColor[0] = 0 ;
  rMask[0] = 0xFF ;
  BYTE sMask[4];
  for (int i = 0 ; i < 4 ; i++) {
    rColor[rnOffs[i]] = nColor ;
    rColor[rhOffs[i]] = hColor ;
    rColor[rhOffs[i] + rnOffs[i]] = bColor ;
    rMask[rnOffs[i]] = 0x0F ;
    rMask[rhOffs[i]] = 0xF0 ;
    rMask[rhOffs[i] + rnOffs[i]] = 0 ;
    sMask[i] = rnOffs[i] + rhOffs[i] ;
    }
  int lw = ((r->right - r->left + 7) & ~7) >> 3 ;
  for (i = r->top ; i < r->bottom ; i++) {
    BYTE huge *scstart;
    BYTE huge *scend;
    if (mVert) {
      int i1 = r->bottom + r->top - 1 - i ;
      scstart = lpGBits + DWORD(gy - 1 - i1) * DWORD(obw) + r->left / 2;
      scend = lpGBits + DWORD(gy - 1 - i1) * DWORD(obw) + r->right / 2;
      }
    else {
      scstart = lpGBits + DWORD(gy - 1 - i) * DWORD(obw) + r->left / 2;
      scend = lpGBits + DWORD(gy - 1 - i) * DWORD(obw) + r->right / 2;
      }
    BYTE FAR *source = bsource + (i - r->top + 1) * lw - 1 ;
    int j = ((r->right - r->left) / 2 - 1) % 4 ;
#ifndef WIN32
    if (FP_SEG(scstart) == FP_SEG(scend)) {
#endif
      for (BYTE FAR *h = scstart ; h < scend ; ) {
        BYTE sx = *source & sMask[j];
        *h++ = (*h & rMask[sx]) | rColor[sx] ;
        if (j > 0) j -- ;
        else {
          j = 3 ;
          source -- ;
          }
        }
#ifndef WIN32
      }
    else {
      for (BYTE huge *h = scstart ; h < scend ; ) {
        BYTE sx = *source & sMask[j];
        *h++ = (*h & rMask[sx]) | rColor[sx] ;
        if (j > 0) j -- ;
        else {
          j = 3 ;
          source -- ;
          }
        }
      }
#endif
    }
  }
void BitMerge::AddBitmap (LPRECT r,int type,DWORD plane,BOOL mVert,BOOL mHorz,int Color,BYTE FAR * bData)
  {
  switch (type) {
    case 0 :
      {
      // 16 Farben
      if (mHorz)
        AB_16R (r,bData,mVert);
      else
        AB_16L (r,bData,mVert);
      }
      break ;
    case 1 :
      {
      if (mHorz)
        AB_32R (r,plane,(DWORD FAR *) bData,mVert,Color);
      else
        AB_32L (r,plane,(DWORD FAR *) bData,mVert,Color);
      }
      break ;
    default :
      {
      // monchrom
      if (mHorz)
        AB_1R (r,bData,mVert,Color);
      else
        AB_1L (r,bData,mVert,Color);
      }
    }
  }
#define ABSTATE_TEST  0
#define ABSTATE_LOAD  1
RIList FAR *BitMerge::GetRIList (LPRECT r)
  {
  if (riHash != NULL) {
    RIList FAR *FAR *res = (RIList FAR * FAR *)
      riHash->GetDatav (r,sizeof(*r));

    if (res != NULL) 
      return *res ;
    else             
      return NULL ;
    }
  else
  // for (RIList FAR *res = l ; res != NULL ; res = res->Next) {
  //  if (lmemcmp (&res->r,r,sizeof(res->r))) return res ;
  //  }
    return NULL ;
  }

void BitMerge::Invalidate (LPRECT r)
  {
  RECT rh;
  rh = *r ;
  OffsetRect (&rh,ToolRect.left,ToolRect.top);
  InvalidateRect (Parent->Parent->hWndToolbar(),&rh,FALSE);
  }

RIList FAR *BitMerge::InsertRIList (LPRECT r)
  {
  RIList FAR *res = (RIList FAR *) GetGlobMem (sizeof(*res)) ;
  res->Next = l ;
  l = res ;
  res->r = *r ;
  Invalidate (&res->r);
  DBWIN_ASSERT ((r->left & 1) == 0) ;
  DBWIN_ASSERT ((r->right & 1) == 0) ;
  DBWIN_ASSERT (r->left >= 0) ;
  DBWIN_ASSERT (r->top >= 0) ;
  DBWIN_ASSERT (r->right <= (ToolRect.right - ToolRect.left));
  DBWIN_ASSERT (r->bottom <= (ToolRect.bottom - ToolRect.top));
  if (riHash == NULL) riHash = new hash (57,VOIDKEY);
  riHash->SetDatav (r,&res,sizeof(res),sizeof(*r));
  return res ;
  }

void RIList::PrepareTest ()
  {
  IsCorrect = TRUE ;
  for (IDList FAR *i = idl ; i != NULL ; i = i->Next ) {
    i->IsDone = FALSE ;
    }
  }

BOOL RIList::TestID (int type,DWORD pictID,BOOL mVert,BOOL mHorz,DWORD plane,int Color)
  {
  for (IDList FAR *i = idl ; i != NULL ; i = i->Next ) {
    if ((i->pict == pictID) && (i->type == type) && 
        (i->mVert == mVert) && (i->mHorz == mHorz) &&
        (i->plane == plane) && (i->Color == Color)) {
      i->IsDone = TRUE ;
      return TRUE ;
      }
    }
  return FALSE ;
  }

void RIList::InsertID (int type,DWORD pictID,BOOL mVert,BOOL mHorz,DWORD plane,int Color)
  {
  IDList FAR *n = (IDList FAR *) GetGlobMem (sizeof(*n));
  n->pict = pictID ;
  n->type = type ;
  n->mVert = mVert ;
  n->mHorz = mHorz ;
  n->plane = plane ;
  n->Color = Color ;
  n->Next = idl ;
  n->IsDone = TRUE ;
  idl = n ;
  }

static BitMerge FAR *am;
struct ZList {
  RECT r;
  int type;
  DWORD plane,pictID;
  BOOL mVert,mHorz;
  int Color;
  BYTE FAR *bData;
  ZList FAR *Next;
  };
struct ZList FAR *zhead,FAR *ztail;
void ZwischenSpeichern (LPRECT r,int type,
      DWORD plane,DWORD pictID,BOOL mVert,BOOL mHorz,int Color,BYTE FAR *bData)
  {
  ZList FAR *z = (ZList FAR *) GetGlobMem (sizeof(*z)) ;
  z->Next = NULL ;
  if (zhead == NULL)
    zhead = z ;
  if (ztail != NULL)
    ztail->Next = z ;
  ztail = z ;
  z->r = *r;
  z->type = type;
  z->plane = plane;
  z->pictID = pictID;
  z->mVert = mVert;
  z->mHorz = mHorz;
  z->Color = Color;
  z->bData = bData;
  }

void ZwischenListeLoeschen ()
  {
  for ( ; zhead != NULL ; ) {
    ZList FAR *z = zhead->Next ;
    FreeGlobMem (zhead);
    zhead = z ;
    }
  ztail = zhead = NULL ;
  }

DLLExport void _export WINAPI AddBitmap (LPRECT r,int type,
      DWORD plane,DWORD pictID,BOOL mVert,BOOL mHorz,int Color,BYTE FAR *bData)
  {
  switch (am->State) {
    case ABSTATE_TEST :
      {
      RIList FAR *x = am->GetRIList (r);
      if ((x != NULL) && (!x->TestID (type,pictID,mVert,mHorz,plane,Color)))
        x->IsCorrect = FALSE;
      ZwischenSpeichern (r,type,plane,pictID,mVert,mHorz,Color,bData);
      }
      break ;
    case ABSTATE_LOAD :
      {
      RIList FAR *x = am->GetRIList (r);
      if (x == NULL) x = am->InsertRIList (r);
      if (!x->IsCorrect) {
        if (!x->TestID (type,pictID,mVert,mHorz,plane,Color))
          x->InsertID(type,pictID,mVert,mHorz,plane,Color) ;
        am->AddBitmap (r,type,plane,mVert,mHorz,Color,bData);
        }
      }
      break ;
    }
  }

inline void AddBitmap_extern (LPRECT r,int type,
      DWORD plane,DWORD pictID,BOOL mVert,BOOL mHorz,int Color,BYTE FAR *bData)
  {
  AddBitmap (r,type,plane,pictID,mVert,mHorz,Color,bData);
  }
void BitMerge::PrepareTest ()
  {
  for (RIList FAR *r = l ; r != NULL ; r = r->Next) {
    r->PrepareTest ();
    }
  }

void BitMerge::CleanLists ()
  {
  RIList FAR *prev = NULL ;
  for ( RIList FAR *r = l ; r != NULL ; ) {
    // Alle nicht gebrauchten IDs raushauen
    IDList FAR *ip = NULL ;
    for ( IDList FAR *i = r->idl ; i != NULL ; ) {
      IDList FAR *in = i->Next ;
      if (!i->IsDone) {
        if (ip != NULL) ip->Next = i->Next ;
        else            r->idl = i->Next ;
        FreeGlobMem (i) ;
        r->IsCorrect = FALSE ;
        }
      else
        ip = i ;
      i = in ;
      }
    RIList FAR *next = r->Next ;
    if (!r->IsCorrect) {
      Invalidate (&r->r);
      EmptyRect (&r->r);
      }
    if (r->idl == NULL) {
      if (prev == NULL) l = r->Next ;
      else              prev->Next = r->Next ;
      riHash->DelDatav (&r->r,sizeof(r->r));
      FreeGlobMem (r);
      }
    else
      prev = r ;
    r = next ;
    }
  }

void BitMerge::LoadBitmap ()
  {
  // Bei Allen Listen die Flags richtig setzen
  PrepareTest ();
  // Den Test durchfuehren
  LPVOID x ;
  am = this ;
  State = ABSTATE_TEST ;
  for ( x = NULL ; ((x = (* NextBitMap) (privData,am->Param()->bmList,am->Param()->cbProc,x)) != NULL) ; ) ;
  // Nicht mehr benoetigte Eintraege loeschen
  CleanLists ();
  // Und alles Laden
  State = ABSTATE_LOAD ;
//  for ( x = NULL ; ((x = (* NextBitMap) (privData,am->Param()->bmList,am->Param()->cbProc,x)) != NULL) ; ) ;
  for ( ZList FAR *h = zhead ; h != NULL ; h = h->Next)
    AddBitmap_extern (&h->r,h->type,
                  h->plane,h->pictID,h->mVert,h->mHorz,h->Color,h->bData);
  ZwischenListeLoeschen ();
  am = NULL ;
  }

void BitMerge::GetRect ()
  {
  int x0 = ToDevKoordX(tx);
  int y0 = ToDevKoordY(ty, Parent->Layer);
  SetRect (LPRECT (&ToolRect), x0, y0, 
              x0 + gx, 
              y0 + gy
          );
  if (ty >= 0)
    Parent->CheckLayerHeight (ToDevKoordY (ty));
  }

void BitMerge::Load ()
  {
  DBINT FAR *lpx = (DBINT FAR*)(* GetData)(privData, Param()->hd._x);
  DBINT FAR *lpy = (DBINT FAR*)(* GetData)(privData, Param()->hd._y);
  DBWIN_ASSERT ((lpx != NULL) && (lpy != NULL));
  tx = *lpx;
  ty = *lpy;
  DBINT FAR *lpdx = (DBINT FAR *)(* GetData)(privData, Param()->w);
  DBINT FAR *lpdy = (DBINT FAR *)(* GetData)(privData, Param()->h);
  DBWIN_ASSERT ((lpdx != NULL) && (lpdy != NULL)) ;
  gx = *lpdx;
  gy = *lpdy;
  DBWIN_ASSERT ((gx & 1) == 0) ;    // Nur gerade Breiten

  GetRect ();
  obw = GetImgByteWidth (gx) ;
  hGmem = GlobalAlloc (GMEM_FIXED | GMEM_ZEROINIT,DWORD (obw) * DWORD(gy));
  lpGBits = (BYTE huge *) GlobalLock (hGmem);
  LoadBitmap ();
  }

void BitMerge::FixConnection ()
  {
  (* SetConnection) (privData,Param()->bmList,StructData);
  }

void BitMerge::Invalidate (BOOL doClear)
  {
  InvalidateRect (Parent->Parent->hWndToolbar(),LPRECT(&ToolRect),doClear);
  }

void BitMerge::Reset (BOOL doClear)
  {
  if (hGmem) { GlobalUnlock (hGmem) ; GlobalFree (hGmem) ; }
  if (IsWindow (Parent->Parent->hWndToolbar()))
    Invalidate (TRUE);
  (* ClearConnection) (privData,Param()->bmList,StructData);
  RIList FAR *prev = NULL ;
  DeleteRIList ();
  l = NULL ;
  }

void BitMerge::Update ()
  {
  LoadBitmap ();
  }

void BitMerge::PaintTool (HDC hDC, HDC hmemDC)
  {
  char buffer[sizeof(BITMAPINFO) + sizeof(WORD) * 15] ;
  BITMAPINFO FAR *bi = (BITMAPINFO *) buffer;
  bi->bmiHeader.biSize           = sizeof(bi->bmiHeader);
  bi->bmiHeader.biWidth          = gx ;
  bi->bmiHeader.biHeight         = gy ;
  bi->bmiHeader.biPlanes         = 1 ;
  bi->bmiHeader.biBitCount       = 4 ;
  bi->bmiHeader.biCompression    = 0 ;
  bi->bmiHeader.biSizeImage      = DWORD(obw) * DWORD(gy) ;
  bi->bmiHeader.biXPelsPerMeter  = 75 ;
  bi->bmiHeader.biYPelsPerMeter  = 75 ;
  bi->bmiHeader.biClrUsed        = 16 ;
  bi->bmiHeader.biClrImportant   = 16 ;
  WORD FAR *pind = (WORD FAR *) &bi->bmiColors[0] ;
  for (int i = 0 ; i < 16 ; i++)
    pind[i] = i ;
  SetDIBitsToDevice (hDC,ToolRect.left,ToolRect.top,gx,gy,0,0,0,gy,
                     lpGBits,bi,DIB_PAL_COLORS
                    ) ;
  }


