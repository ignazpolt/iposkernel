/////////////////////////////////////////////////////////////////////
//
//      eigene Kompressionsalgorithmen
//
/////////////////////////////////////////////////////////////////////
// $Header:   P:/marille/clinicum/image/rev/imgcompr.cpv   1.3   04 Mar 1998 13:24:46   Martin  $
// $Log:   P:/marille/clinicum/image/rev/imgcompr.cpv  $
// 
//    Rev 1.3   04 Mar 1998 13:24:46   Martin
// ExtendPutBit und ExtendGetBit nicht mehr near
// 
//    Rev 1.2   16 Jul 1997 16:03:00   Martin
// jetzt aber hoffentlich wirklich 32 Bit-faehig gemacht
// 
//    Rev 1.1   28 Apr 1997 15:04:42   Martin
// 32-bit-faehig
// 
//    Rev 1.0   25 Apr 1997 12:31:32   Martin
// Initial revision.
// 
// 

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <dos.h>

#include "dds32.h"

#include "globmem.h"
#define JUST_EM
#include "dds.hpp"
#define MIMAGE_CLASS
#include "image.hpp"
#define MODULENUM 180
#include "winass.hpp"

#define NUMCODEBITS 5                   // ld Anzahl der Codewerte
#define MAXORDER (1 << NUMCODEBITS)     // Anzahl der Codewerte
#define MAXBYTESPERLINE 4096
#ifndef WIN32
static BYTE substline[MAXBYTESPERLINE];
#endif

#define BLATT 0
#define KNOTEN 1

#pragma pack(1)
struct near EncodeKnoten {
  short AnzBits;
  char Code[MAXORDER];
  };
#pragma pack()
static EncodeKnoten near EncodeArray[MAXORDER];
static EncodeKnoten near actEncodeKnoten;

static GLOBALHANDLE near hRes;
static LONG near absOffset;
static LPLONG near resptr;
#define RESOFFSET (*((unsigned near *)(&resptr)))
static LONG near actMuster;
static LONG near actOutVal;
#ifdef WIN32
static LONG resbase;
#endif

static void near InitPutBit(short InitialSize)
  {
  LPSTR res = (LPSTR)GlobalLock(hRes);
  resptr = (LPLONG)(res + InitialSize);
  absOffset = 0;
#ifdef WIN32
  resbase = (LONG)res + absOffset;
#endif
  actMuster = 1;
  actOutVal = 0;
  }

static void ExtendPutBit()
  {
  hRes = GlobalReAlloc(hRes,absOffset + 0x20000,GMEM_MOVEABLE);
  if (hRes == NULL) {
    WIN_ASSERT_TEXT(FALSE,"Kompression: zu wenig Speicher (2)");
    return;
    }
  char huge *res = (char huge *)GlobalLock(hRes);
  absOffset += 0x10000;
#ifdef WIN32
  resbase = (LONG)res + absOffset;
#endif
  resptr = (LPLONG)(res + absOffset);
  }

inline void PutBit(char Bit)
  {
  if (Bit)
    actOutVal |= actMuster;
  if ((actMuster <<= 1) == 0) {
    *resptr = actOutVal;
#ifdef WIN32
    if (((RESOFFSET += sizeof(LONG)) - resbase) == 0x10000) // Segmentsprung
#else
    if ((RESOFFSET += sizeof(LONG)) == 0) // Segmentsprung
#endif
      ExtendPutBit();
    actMuster = 1;
    actOutVal = 0;
    }
  }

static void near EndPutBit()
  {
  // letzte Bits noch raus
  while (actMuster != 1)
    PutBit(0);
  // noch schrumpfen auf tatsaechlich benoetigte Groesse
#ifdef WIN32
  hRes = GlobalReAlloc(hRes,absOffset + (LONG)(RESOFFSET - resbase),GMEM_MOVEABLE);
#else
  hRes = GlobalReAlloc(hRes,absOffset + (LONG)(RESOFFSET),GMEM_MOVEABLE);
#endif
  }

inline void PutInd(short ind)
  {
  ind += (MAXORDER / 2);
#if NUMCODEBITS == 5
  PutBit((char)ind & 0x10);
  PutBit((char)ind & 0x08);
  PutBit((char)ind & 0x04);
  PutBit((char)ind & 0x02);
  PutBit((char)ind & 0x01);
#else
  bitte anpassen !
#endif
  }

inline void PutCode(short ind)
  {
  EncodeKnoten near *actEle = EncodeArray + ((MAXORDER / 2) + ind);
#ifdef DEBUG
  WIN_ASSERT(actEle->AnzBits > 0);
#endif
  for (short i = 0; i < actEle->AnzBits; i++)
    PutBit(actEle->Code[i]);
  }

inline void PutRestCode(BYTE absval)
  {
  PutCode(-(MAXORDER / 2));
  PutBit(absval & 0x80);
  PutBit(absval & 0x40);
  PutBit(absval & 0x20);
  PutBit(absval & 0x10);
  PutBit(absval & 0x08);
  PutBit(absval & 0x04);
  PutBit(absval & 0x02);
  PutBit(absval & 0x01);
  }

#pragma pack(1)
static struct {
  short anz;
  short ind;
  } near ord[MAXORDER];
#pragma pack()
static short near anzsum[MAXORDER + 1];  // + 1: auf jeden Fall eine 0 dahinter

static void near TeileHuffman(short min, short max, short minanz, short maxanz)
  {
  short midanz = (minanz + maxanz) / 2;
  short mid = min + (max - min) / 4;       // geschaetzter Teilungsindex
  while (anzsum[mid] > midanz) mid++;
  while (anzsum[mid] < midanz) mid--;
  // welcher der beiden mittleren Teilungspunkte ist guenstiger ?
  if ((anzsum[mid] - midanz) > (midanz - anzsum[mid+1])) mid++;
  if (mid <= min) mid = min + 1;   // minimale Breite 1
  // jetzt ist mid der optimale Teilungsindex
  actEncodeKnoten.Code[actEncodeKnoten.AnzBits++] = 0;
  if ((mid - min) <= 1) {
    // Code pushen und in Array fuer Komprimierung eintragen (Bitwert 0)
    PutBit(BLATT);
    PutInd(ord[min].ind);
    EncodeArray[(MAXORDER / 2) + ord[min].ind] = actEncodeKnoten;
    }
  else {
    PutBit(KNOTEN);
    // rekursiver Aufruf
    TeileHuffman(min,mid,minanz,anzsum[mid]);
    }
  actEncodeKnoten.Code[actEncodeKnoten.AnzBits-1] = 1;
  if ((max - mid) <= 1) {
    // Code pushen und in Array fuer Komprimierung eintragen (Bitwert 1)
    PutBit(BLATT);
    PutInd(ord[mid].ind);
    EncodeArray[(MAXORDER / 2) + ord[mid].ind] = actEncodeKnoten;
    }
  else {
    PutBit(KNOTEN);
    // rekursiver Aufruf
    TeileHuffman(mid,max,anzsum[mid],maxanz);
    }
  actEncodeKnoten.AnzBits--;
  }

static void near ComprLine(BYTE FAR *lastline, BYTE FAR *actline, short bytesperline)
  {
  static short near delta[MAXBYTESPERLINE];
  static short near anz[512];
  for (short i = 0; i < 512; i++)
    anz[i] = 0;
  for (i = 0; i < bytesperline; i++) {
    delta[i] = actline[i] - lastline[i];
    anz[256 + delta[i]]++;
    }
  short sum = ord[0].anz = anz[256];
  ord[0].ind = 0;
  short newanz;
  for (i = 1; i < (MAXORDER / 2); i++) {
    sum += newanz = anz[256 + i];
    for (short j = i * 2 - 1; (j > 0) && (ord[j - 1].anz < newanz); j--)
      ord[j] = ord[j - 1];
    ord[j].ind = i;
    ord[j].anz = newanz;
    sum += newanz = anz[256 - i];
    for (j = i * 2; (j > 0) && (ord[j - 1].anz < newanz); j--)
      ord[j] = ord[j - 1];
    ord[j].ind = -i;
    ord[j].anz = newanz;
    }
  // Anzahl der Ausreisser bestimmen und auch noch einsortieren
  short rest = bytesperline - sum;
  newanz = rest * 2;  // doppelt bewerten, da Code auf jeden Fall laenger
  short maxanz = bytesperline + rest;  // -> Gesamthaeufigkeit anpassen !
  for (short j = MAXORDER - 1; (j > 0) && (ord[j - 1].anz < newanz); j--)
    ord[j] = ord[j - 1];
  ord[j].ind = -(MAXORDER / 2);
  ord[j].anz = newanz;
  anzsum[0] = maxanz;
  for (short anzcodes = 1; anzcodes < MAXORDER; anzcodes++) {
    short actanz;
    if ((actanz = ord[anzcodes - 1].anz) != 0)
      anzsum[anzcodes] = anzsum[anzcodes - 1] - actanz;
    else {
#ifdef DEBUG
      WIN_ASSERT(anzsum[anzcodes - 1] == 0);
#endif
      anzcodes--;
      break;
      }
    }
  // jetzt Code-Baum aufbauen
  lmemset(EncodeArray,'\0',sizeof(EncodeArray));
  TeileHuffman(0,anzcodes,maxanz,0);
#ifdef DEBUG
  WIN_ASSERT(actEncodeKnoten.AnzBits == 0);
#endif
  for (i = 0; i < bytesperline; i++) {
    if ((delta[i] > -(MAXORDER / 2)) && (delta[i] < (MAXORDER / 2)))
      PutCode(delta[i]);
    else
      PutRestCode(actline[i]);
    }
  }

// Delta-Huffman-Kompression (fuer Roentgenbilder gut geeignet )
DLLExport GLOBALHANDLE _export WINAPI DIBToDeltaHuffman(GLOBALHANDLE hDib)
  {
  LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
  LONG bytesperline = ByteWidth(lpbi->biWidth,lpbi->biBitCount);
  if (bytesperline > MAXBYTESPERLINE) {
    WIN_ASSERT_TEXT(FALSE,"Bild zu breit fuer diese Art der Komprimierung !");
    return NULL;
    }
  if (lpbi->biSize & 3L) {
    WIN_ASSERT_TEXT(FALSE,"Bildheadergroesse nicht durch 4 teilbar !");
    return NULL;
    }
  DWORD dwColorTableSize = (DWORD)(DibNumColors(lpbi) * sizeof(RGBQUAD));
  dwColorTableSize += lpbi->biSize;
  BYTE FAR *actline = ((BYTE FAR *)lpbi) + dwColorTableSize;
  dwColorTableSize += bytesperline;
  hRes = GlobalAlloc (GMEM_MOVEABLE,0x10000);
  if (hRes == NULL) {
    WIN_ASSERT_TEXT(FALSE,"Kompression: zu wenig Speicher (1)");
    return NULL;
    }
  // DIBHeader, ColorTable und erste Zeile des Bildes auf jeden Fall kopieren
  LPVOID res = GlobalLock(hRes);
  lmemcpy(res,lpbi,(int)dwColorTableSize);
  InitPutBit((short)dwColorTableSize);
  BYTE huge *line = ((BYTE huge *)actline) + bytesperline;
  BYTE FAR *lastline;
  for (short j = 1 ; j < lpbi->biHeight; j++) {
    lastline = actline;
    BYTE huge *nextline = line + bytesperline;
#ifndef WIN32
    if (FP_SEG(line) == FP_SEG(nextline)) {
#endif
      actline = (BYTE FAR *)line;
#ifndef WIN32
      }
    else {
      actline = substline;
      hmemcpy(actline,line,bytesperline);
      }
#endif
    line = nextline;
    ComprLine(lastline,actline,(short)bytesperline);
    }
  EndPutBit();
  if (GlobalSize(hRes) > GlobalSize(hDib)) {
    // ist wohl nicht der geeignete Kompressionsalgorithmus
    // fuer dieses Bild -> dann schon lieber unkomprimiert
    GlobalFree(hRes);
    return NULL;
    }
  return hRes;
  }


// Dekomprimierung

static void near InitGetBit(short InitialSize)
  {
  LPSTR res = (LPSTR)GlobalLock(hRes);
  resptr = (LPLONG)(res + InitialSize - sizeof(LONG));
  absOffset = 0;
#ifdef WIN32
  resbase = (LONG)res + absOffset;
#endif
  actMuster = 0;
  // actOutVal wird im ersten NextBit() initialisiert
  }

static void ExtendGetBit()
  {
  char huge *res = (char huge *)GlobalLock(hRes);
  absOffset += 0x10000;
#ifdef WIN32
  resbase = (LONG)res + absOffset;
#endif
  resptr = (LPLONG)(res + absOffset);
  }

inline LONG TestBit()
  {
  return actOutVal & actMuster;
  }

#ifdef DEBUG
static long near actanzbits;
#endif

inline void NextBit()
  {
#ifdef DEBUG
  actanzbits++;
#endif
  if ((actMuster <<= 1) == 0) {
#ifdef WIN32
    if (((RESOFFSET += sizeof(LONG)) - resbase) == 0x10000) // Segmentsprung
#else
    if ((RESOFFSET += sizeof(LONG)) == 0) // Segmentsprung
#endif
      ExtendGetBit();
    actMuster = 1;
    actOutVal = *resptr;
    }
  }

inline short GetInd()
  {
  short res = 0;
#if NUMCODEBITS == 5
  NextBit();
  if (TestBit()) res |= 0x10;
  NextBit();
  if (TestBit()) res |= 0x08;
  NextBit();
  if (TestBit()) res |= 0x04;
  NextBit();
  if (TestBit()) res |= 0x02;
  NextBit();
  if (TestBit()) res |= 0x01;
#else
  bitte anpassen !
#endif
  res -= (MAXORDER / 2);
  return res;
  }

#ifdef DEBUG
static long near anzausreisser;
#endif

inline BYTE GetByte()
  {
#ifdef DEBUG
  anzausreisser++;
#endif
  BYTE res = 0;
  NextBit();
  if (TestBit()) res |= 0x80;
  NextBit();
  if (TestBit()) res |= 0x40;
  NextBit();
  if (TestBit()) res |= 0x20;
  NextBit();
  if (TestBit()) res |= 0x10;
  NextBit();
  if (TestBit()) res |= 0x08;
  NextBit();
  if (TestBit()) res |= 0x04;
  NextBit();
  if (TestBit()) res |= 0x02;
  NextBit();
  if (TestBit()) res |= 0x01;
  return res;
  }

#pragma pack(1)
struct near DecodeKnoten {
  short IsBlatt;
  short Val;
  DecodeKnoten near *On0;
  DecodeKnoten near *On1;
  };
#pragma pack()
static DecodeKnoten near DecodeArray[MAXORDER * 2];
static short near actDecodeKnotenInd;

static DecodeKnoten near *GetKnotenBaum()
  {
  DecodeKnoten near *actDecodeKnoten = DecodeArray + actDecodeKnotenInd++;
  NextBit();
  if (TestBit()) {    // KNOTEN
    actDecodeKnoten->IsBlatt = FALSE;
    actDecodeKnoten->On0 = GetKnotenBaum();
    actDecodeKnoten->On1 = GetKnotenBaum();
    }
  else {              // BLATT
    actDecodeKnoten->IsBlatt = TRUE;
    actDecodeKnoten->Val = GetInd();
    }
  return actDecodeKnoten;
  }

#ifdef DEBUG
static long near anzcodebits;
static long near anzdatabits;
#endif

static void near DecomprLine(BYTE FAR *lastline, BYTE FAR *actline, short bytesperline)
  {
#ifdef DEBUG
  actanzbits = 0;
#endif
  DecodeArray[0].IsBlatt = FALSE;
  actDecodeKnotenInd = 1;
  DecodeArray[0].On0 = GetKnotenBaum();
  DecodeArray[0].On1 = GetKnotenBaum();
#ifdef DEBUG
  anzcodebits += actanzbits;
  actanzbits = 0;
#endif
  for (short i = 0; i < bytesperline; i++) {
    DecodeKnoten near *actDecodeKnoten = DecodeArray;
    while (!actDecodeKnoten->IsBlatt) {
      NextBit();
      if (TestBit())
        actDecodeKnoten = actDecodeKnoten->On1;
      else
        actDecodeKnoten = actDecodeKnoten->On0;
      }
    if (actDecodeKnoten->Val == -(MAXORDER / 2))
      actline[i] = GetByte();
    else {
#ifdef DEBUG
      short val = lastline[i] + actDecodeKnoten->Val;
      WIN_ASSERT((val >= 0) && (val < 256));
#endif
      actline[i] = (BYTE)(lastline[i] + actDecodeKnoten->Val);
      }
    }
#ifdef DEBUG
  anzdatabits += actanzbits;
#endif
  }

// Delta-Huffman-Dekompression (fuer Roentgenbilder gut geeignet)
DLLExport GLOBALHANDLE _export WINAPI DeltaHuffmanToDIB(GLOBALHANDLE hMem)
  {
#ifdef DEBUG
  anzcodebits = 0;
  anzdatabits = 0;
#endif
  hRes = hMem;
  LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)GlobalLock(hRes);
  LONG bytesperline = ByteWidth(lpbi->biWidth,lpbi->biBitCount);
  DWORD dwColorTableSize = (DWORD)(DibNumColors(lpbi) * sizeof(RGBQUAD));
  dwColorTableSize += lpbi->biSize;
  GLOBALHANDLE hDib = GlobalAlloc(GMEM_MOVEABLE,dwColorTableSize + lpbi->biHeight * bytesperline);
  if (hDib == NULL) {
    WIN_ASSERT_TEXT(FALSE,"Dekompression: zu wenig Speicher (1)");
    return NULL;
    }
  LPVOID res = GlobalLock(hDib);
  BYTE FAR *actline = ((BYTE FAR *)res) + dwColorTableSize;
  dwColorTableSize += bytesperline;
  // DIBHeader, ColorTable und erste Zeile des Bildes auf jeden Fall kopieren
  lmemcpy(res,lpbi,(int)dwColorTableSize);
  InitGetBit((short)dwColorTableSize);
  BYTE huge *line = ((BYTE huge *)actline) + bytesperline;
  BYTE FAR *lastline;
  for (short j = 1 ; j < lpbi->biHeight; j++) {
    lastline = actline;
    BYTE huge *nextline = line + bytesperline;
#ifndef WIN32
    if (FP_SEG(line) == FP_SEG(nextline)) {
#endif
      actline = (BYTE FAR *)line;
      DecomprLine(lastline,actline,(short)bytesperline);
#ifndef WIN32
      }
    else {
      actline = substline;
      DecomprLine(lastline,actline,(short)bytesperline);
      hmemcpy(line,actline,bytesperline);
      }
#endif
    line = nextline;
    }
  return hDib;
  }

