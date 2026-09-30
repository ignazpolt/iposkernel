//---------------------------------------------------------------------------
// Templates fuer DialogBoxIndirect
//---------------------------------------------------------------------------
// $Header:   P:/marille/clinicum/include/rev/dlgtempl.hpv   1.5   11 Sep 1997 18:20:08   Gerhold  $
// $Log:   P:/marille/clinicum/include/rev/dlgtempl.hpv  $
// 
//    Rev 1.5   11 Sep 1997 18:20:08   Gerhold
// 16-32-Bit Aenderungen
// 
//    Rev 1.4   09 Sep 1997 18:29:50   Gerhold
// Jetzt gehts auch mit 32-Bit (Bravo Gerhold)
// 
//    Rev 1.3   14 Mar 1997 12:36:08   gerhold
// #ifndef WIN32 am Anfang
// 
//    Rev 1.2   25 Jul 1996 20:02:14   GERHOLD
// in WIN32 sind die Templates komplett anders aufgebaut! Sch....!
// 
//    Rev 1.1   02 Feb 1996 10:59:08   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.0   24 Apr 1995 15:47:00   GERHOLD
// Initial revision.
//---------------------------------------------------------------------------
#define IDLB_TEMPLATENAME  100
#define IDED_DESCRIPTION   101

#pragma pack(1)
struct FAR FontDef {
  WORD  wPointSize;     
#ifdef WIN32
  wchar_t  szFaceName[1];  
#else
  char  szFaceName[1];  
#endif
  };
#pragma pack()

#ifndef WIN32
  #define LPWSTR    LPSTR
  #define mylstrcpy lstrcpy
  #define mylstrlen lstrlen
  #define mystrsiz  lstrlen
#endif


#pragma pack(1)
class FAR DialogBoxHeader {
 public :
    DWORD lStyle;

#ifdef WIN32
    DWORD dwExtendedStyle;
    WORD  bNumberOfItems;
#else
    BYTE  bNumberOfItems;
#endif

    WORD  x;
    WORD  y;
    WORD  cx;
    WORD  cy;

#ifdef WIN32
    wchar_t  szMenuName[1];
    wchar_t  szClassName[1];
    wchar_t  szCaption[1];
#else
    char  szMenuName;
    char  szClassName;
    char  szCaption[1];
#endif

    char  reserve[128];

    char  BaseSize()
      {
      return sizeof(*this) - sizeof(reserve) ; 
      }

    void SetCaption (LPSTR Caption)
      {
#ifdef WIN32
      MultiByteToWideChar (CP_ACP, 0, (LPCSTR)Caption, -1, LPWSTR(szCaption), 128);
#else
      lstrcpy (szCaption,Caption);
#endif
      }

    void SetFont (int PointSize,LPSTR FontName)
      {
#ifdef WIN32
      int iCapLen = wcslen((wchar_t *)szCaption) * sizeof(wchar_t);
#else
      int iCapLen = lstrlen(szCaption);
#endif
      FontDef FAR *fd = (FontDef FAR *) (reserve + iCapLen) ;
      fd->wPointSize = PointSize ;

#ifdef WIN32
      MultiByteToWideChar (CP_ACP, 0, (LPCSTR)FontName, -1, (LPWSTR)fd->szFaceName, 128);
#else
      lstrcpy (fd->szFaceName,FontName);
#endif

      lStyle |= DS_SETFONT ;
      }

    int Size()
      {
#ifdef WIN32
      int iCapLen = wcslen((wchar_t *)szCaption) * sizeof(wchar_t);
#else
      int iCapLen = lstrlen(szCaption);
#endif
      int res = BaseSize() + iCapLen ; 
      if (lStyle & DS_SETFONT) {
        FontDef FAR *fd = (FontDef FAR *) (reserve + iCapLen) ;

#ifdef WIN32
        int iFaceLen = wcslen((wchar_t *)fd->szFaceName) * sizeof(wchar_t);
#else
        int iFaceLen = lstrlen(fd->szFaceName);
#endif
        res += (sizeof(*fd) + iFaceLen);
        }
      return res;
      }

    void Init (DWORD Style,WORD _x,WORD _y,WORD _cx,WORD _cy,LPSTR Caption)
      {
      lmemset (this,'\0',sizeof(*this));
      lStyle = Style ;

#ifdef WIN32
      dwExtendedStyle = 0;
#endif

      x = _x ;
      y = _y ;
      cx = _cx ;
      cy = _cy ;

#ifdef WIN32
      szMenuName[0] = L'\0';
      szClassName[0] = L'\0';
#else
      szMenuName = '\0';
      szClassName = '\0';
#endif

      SetCaption (Caption) ;
      }

    DialogBoxHeader (DWORD Style,WORD _x,WORD _y,WORD _cx,WORD _cy,LPSTR Caption)
      {
      Init (Style,_x,_y,_cx,_cy,Caption);
      }

    DialogBoxHeader (DWORD Style,WORD _x,WORD _y,WORD _cx,WORD _cy,LPSTR Caption,WORD wFont,LPSTR Font)
      {
      Init (Style,_x,_y,_cx,_cy,Caption);
      SetFont (wFont,Font);
      }

    };
#pragma pack()




#pragma pack(1)
class FAR ControlData {
 public :
#ifdef WIN32
    DWORD lStyle;
    DWORD dwExtendedStyle;
#endif
    WORD  x;
    WORD  y;
    WORD  cx;
    WORD  cy;
    WORD  wID;
#ifndef WIN32
    DWORD lStyle;
#endif
    union
    {
#ifdef WIN32
        struct {
          WORD FFFF;
          WORD iClass;
          } atom;
        wchar_t szClass[1];
#else
        BYTE iClass;     /* if (class & 0x80) */
        char szClass[1]; /* otherwise         */
#endif
    } ClassID;
  char reserve[128];

  int BaseSize()
    { return sizeof(*this) - sizeof(reserve) 
#ifdef WIN32
            - sizeof(ClassID.atom.iClass) 
#endif
    ;
    }
  void SetClass (LPSTR Class)
    {
#ifdef WIN32
    MultiByteToWideChar (CP_ACP, 0, (LPCSTR)Class, -1, ClassID.szClass, 128);
#else
    lstrcpy (ClassID.szClass,Class);
#endif
    }

#ifdef WIN32
  void SetClass (WORD Class)
    {
    ClassID.atom.FFFF = 0xFFFF;
    ClassID.atom.iClass = Class;
    }
#else
  void SetClass (BYTE Class)
    {
    ClassID.iClass = Class;
    }
#endif

  LPSTR GetText ()
    {
#ifdef WIN32
    if (ClassID.atom.FFFF == 0xFFFF) 
      return LPSTR ((BYTE FAR *)(this) + BaseSize() + sizeof(ClassID.atom.iClass)) ;
    else                             
      return LPSTR ((BYTE FAR *)(this) + wcslen((wchar_t *)ClassID.szClass) * sizeof(wchar_t) + BaseSize()) ;
#else
    if (ClassID.iClass & 0x80) return LPSTR ((BYTE FAR *)(this) + BaseSize()) ;
    else                       return LPSTR ((BYTE FAR *)(this) + mystrsiz(ClassID.szClass) + BaseSize()) ;
#endif
    }

  void SetText (LPSTR Text)
    {
    LPSTR szText = GetText ();

#ifdef WIN32
    MultiByteToWideChar (CP_ACP, 0, (LPCSTR)Text, -1, LPWSTR(szText), 128);
    int iPos = wcslen ((wchar_t *)szText) * sizeof(wchar_t);
    szText[iPos  + 1] = L'\0' ;
#else
    lstrcpy (szText,Text) ;
    szText[mylstrlen (szText) + 1] = '\0' ;
#endif
    }

  int Size ()
    {
    LPSTR szText = GetText ();
#ifdef WIN32
    return (BYTE FAR *)szText - (BYTE FAR *)(this) + wcslen((wchar_t *)szText) * sizeof(wchar_t) + 4 ;
#else
    return (BYTE FAR *)szText - (BYTE FAR *)(this) + mystrsiz(LPWSTR(szText)) + 2 ;
#endif
    }
#ifdef WIN32
  ControlData (WORD _x,WORD _y,WORD _cx,WORD _cy,WORD _wID,DWORD _lStyle,WORD _class,LPSTR Text)
#else
  ControlData (WORD _x,WORD _y,WORD _cx,WORD _cy,WORD _wID,DWORD _lStyle,BYTE _class,LPSTR Text)
#endif
    {
    lmemset (this,'\0',sizeof(*this));
#ifdef WIN32
    dwExtendedStyle = 0;
#endif
    x = _x ;
    y = _y ;
    cx = _cx ;
    cy = _cy ;
    wID = _wID ;
    lStyle = _lStyle ;
    SetClass (_class) ;
    SetText (Text) ;
    }
  ControlData (WORD _x,WORD _y,WORD _cx,WORD _cy,WORD _wID,DWORD _lStyle,LPSTR _class,LPSTR Text)
    {
#ifdef WIN32
    dwExtendedStyle = 0;
#endif
    x = _x ;
    y = _y ;
    cx = _cx ;
    cy = _cy ;
    wID = _wID ;
    lStyle = _lStyle ;
    SetClass (_class) ;
    SetText (Text) ;
    }
  };
#pragma pack()


#pragma pack(1)
class FAR DlgContainer
  {
#ifdef WIN32
 private:
  LPSTR lpwAlign (LPSTR lpIn)
    {
    ULONG ul;

    ul = (ULONG)lpIn;
    ul +=3;
    ul >>=2;
    ul <<=2;
    return LPSTR(ul);
    }

#endif

 public :
  GLOBALHANDLE res;
  int gSize ;
  DlgContainer (DialogBoxHeader FAR &hd)
    {
    gSize = hd.Size();
    res = GlobalAlloc (GHND, gSize);
    LPVOID lpData = GlobalLock (res);

    hd.bNumberOfItems = 0 ;

    lmemcpy (lpData, &hd, gSize);
    GlobalUnlock (res);
    }
  DlgContainer FAR & operator += (ControlData FAR &cd)
    {
    int nSize = cd.Size ();
/*
#ifdef WIN32
    GLOBALHANDLE nres = GlobalAlloc (GHND, gSize + nSize);
    LPVOID lpres = GlobalLock(nres);
    _fmemcpy (lpres, GlobalLock(res), gSize);
    _fmemcpy (LPSTR(lpres) + gSize, &cd, nSize);
    GlobalUnlock (res);
    GlobalFree (res);

    GlobalUnlock (nres);
    res = nres;
#else
*/
    res = GlobalReAlloc (res,gSize + nSize + 3,GHND);
#ifdef WIN32
    // die Dialogelemente muessen an 4-Byte Grenzen liegen!!!!

    LPVOID lpr = GlobalLock(res);
    LPSTR  lpAligned = lpwAlign(LPSTR(lpr)+gSize);
    short Offset = lpAligned - (LPSTR(lpr)+gSize);

    _fmemcpy (lpAligned,&cd,nSize);
    gSize += (nSize + Offset);
#else
    _fmemcpy (LPSTR(GlobalLock(res))+gSize,&cd,nSize);
    gSize += nSize ;
#endif
    GlobalUnlock (res);
// #endif

    ((DialogBoxHeader FAR *) (GlobalLock(res)))->bNumberOfItems ++ ;
    GlobalUnlock(res);
    return *this;
    }
  ~DlgContainer ()
    {
    GlobalFree (res);
    }
  };
#pragma pack()

#undef LPSTR


