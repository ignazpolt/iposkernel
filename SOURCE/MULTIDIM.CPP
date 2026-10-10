//////////////////////////////////////////////////////////////////////////////
//   Mehrdimensionale Arrays
//////////////////////////////////////////////////////////////////////////////
//   $Header:   P:/marille/clinicum/rev/multidim.cpv   1.4   25 Jul 1996 19:51:52   GERHOLD  $
//   $Log:   P:/marille/clinicum/rev/multidim.cpv  $
// 
//    Rev 1.4   25 Jul 1996 19:51:52   GERHOLD
// #pragma pack(1)
// 
//    Rev 1.3   10 Jun 1996 10:09:56   GERHOLD
// pragma pack
// 
//    Rev 1.2   18 May 1996 20:41:02   GERHOLD
// Speicherfreigabe (MARTIN), ]
// #pragma pack...
// 
//    Rev 1.1   02 Feb 1996 10:35:36   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.0   12 Oct 1995 11:14:24   MARTIN
// Initial revision.
//
//////////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <stdio.h>
#include "dds32.h"
#include "dds.hpp"
#include "globmem.h"
#include "printer.hpp"
#include "sc2d.hpp"
#include "font.hpp"
#include "paint.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "scripthd.hpp"
#include "mdiChild.hpp"

#define MODULENUM 161
#include "winass.hpp"

#include "hash.hpp"
typedef hash FAR *LPHASH;
typedef short FAR *LPSHORT;

// defines fuer MultiDim:
#define MDTYPE_VARIABEL  0
#define MDTYPE_FIX       1
#define MDTYPE_HASH      2

#define BUFFER_SIZE 16384

#pragma pack(1)
struct FAR MDIndexDef {
  short type;
  union {
    struct {
      short minind;
      } v;
    struct {
      short minind;
      short maxind;
      } f;
    struct {
      short hashdim;
      } h;
    } addl;
  };
#pragma pack()
typedef MDIndexDef FAR *LPMDINDEXDEF;

struct FAR MultiDim {
 private:
  HFILE actHandle;   // Filehandle fuer LoadFromFile
  LPSTR actBuffer;   // Buffer fuer LoadFromFile
  int actOffset;     // Offset fuer LoadFromFile
  LPVOID root;       // Wurzel der Datenstruktur
 public:
  int anzdim;
  LPMDINDEXDEF IndexDef[1];

 private:
  inline BYTE ReadNextChar()
    {
    if (actOffset >= BUFFER_SIZE) {
      if (actOffset == BUFFER_SIZE) {
        int bytesRead = _lread (actHandle, actBuffer, BUFFER_SIZE);
        if (bytesRead == BUFFER_SIZE) {
          actOffset = 1;
          return actBuffer[0];
          }
        if (bytesRead > 0) {
          for (int i = BUFFER_SIZE - 1; bytesRead > 0 ; bytesRead--, i--)
            actBuffer[i] = actBuffer[bytesRead - 1];
          actOffset = i + 2;
          return actBuffer[actOffset - 1];
          }
        actOffset = BUFFER_SIZE + 1;   // ich bin am Ende ...
        }
      return 0;
      }
    return actBuffer[actOffset++];
    }
  inline WORD ReadNextWord()
    {
//    return ReadNextChar() | (WORD(ReadNextChar()) << 8);
    WORD res = ReadNextChar();
    res |= (WORD(ReadNextChar()) << 8);
    return res;
    }
 public:
  void Write(LPVOID FAR *IndexVal, LPVOID data)
    {
    LPVOID FAR *InsertAt = &root;
    for (int i = 0; i < anzdim; i++) {
      LPVOID actEbene = *InsertAt;
      switch (IndexDef[i]->type) {
        case MDTYPE_VARIABEL:
          {
          short newindex = *LPSHORT(IndexVal[i]) - IndexDef[i]->addl.v.minind;
          short maxindex = GetBlockSize(actEbene) / sizeof(LPVOID);
          if (newindex >= maxindex) {
            LPVOID oldEbene = actEbene;
            actEbene = GetGlobMem((newindex + 1) * sizeof(LPVOID));
            if (oldEbene != NULL) {
              lmemcpy(actEbene,oldEbene,GetBlockSize(oldEbene));
              FreeGlobMem(oldEbene);
              }
            *InsertAt = actEbene;
            }
          InsertAt = (LPVOID FAR *)actEbene + newindex;
          }
          break;
        case MDTYPE_FIX:
          {
          short newindex = *LPSHORT(IndexVal[i]);
          DBWIN_ASSERT((newindex >= IndexDef[i]->addl.f.minind) &&
                       (newindex <= IndexDef[i]->addl.f.maxind));
          newindex -= IndexDef[i]->addl.v.minind;
          if (actEbene == NULL) {
            actEbene = GetGlobMem((IndexDef[i]->addl.f.maxind -
                                   IndexDef[i]->addl.f.minind +
                                   1) * sizeof(LPVOID));
            *InsertAt = actEbene;
            }
          InsertAt = (LPVOID FAR *)actEbene + newindex;
          }
          break;
        case MDTYPE_HASH:
          {
          if (actEbene == NULL) {
            actEbene = new hash (IndexDef[i]->addl.h.hashdim,VOIDKEY);
            *InsertAt = actEbene;
            }
          LPVOID FAR *newhash = (LPVOID FAR *)(LPHASH(actEbene)->GetDatav(IndexVal[i],GetBlockSize(IndexVal[i])));
          if (newhash == NULL) {
            LPVOID nullPtr = NULL;
            LPHASH(actEbene)->SetDatav(IndexVal[i],&nullPtr,sizeof(LPVOID),GetBlockSize(IndexVal[i]));
            newhash = (LPVOID FAR *)(LPHASH(actEbene)->GetDatav(IndexVal[i],GetBlockSize(IndexVal[i])));
            }
          InsertAt = newhash;
          }
          break;
        default:
          DBWIN_ASSERT (FALSE);
        }
      }
    if (*InsertAt != NULL) FreeGlobMem(*InsertAt);
    if (data != NULL) {
      *InsertAt = GetGlobMem(GetBlockSize(data));
      lmemcpy(*InsertAt,data,GetBlockSize(data));
      }
    else
      *InsertAt = NULL;
    }
  LPVOID Read(LPVOID FAR *IndexVal)
    {
    LPVOID actEbene = root;
    for (int i = 0; i < anzdim; i++) {
      if (actEbene == NULL) return NULL;
      switch (IndexDef[i]->type) {
        case MDTYPE_VARIABEL:
          {
          short newindex = *LPSHORT(IndexVal[i]) - IndexDef[i]->addl.v.minind;
          short maxindex = GetBlockSize(actEbene) / sizeof(LPVOID);
          if (newindex >= maxindex) return NULL;
          actEbene = ((LPVOID FAR *)actEbene)[newindex];
          }
          break;
        case MDTYPE_FIX:
          {
          short newindex = *LPSHORT(IndexVal[i]);
          if ((newindex <IndexDef[i]->addl.f.minind) ||
              (newindex > IndexDef[i]->addl.f.maxind))
            return NULL;
          newindex -= IndexDef[i]->addl.v.minind;
          actEbene = ((LPVOID FAR *)actEbene)[newindex];
          }
          break;
        case MDTYPE_HASH:
          {
          LPVOID FAR *newhash = (LPVOID FAR *)(LPHASH(actEbene)->GetDatav(IndexVal[i],GetBlockSize(IndexVal[i])));
          if (newhash == NULL) return NULL;
          actEbene = *newhash;
          }
          break;
        default:
          DBWIN_ASSERT (FALSE);
        }
      }
    return actEbene;
    }
  void LoadFromFile(HFILE handle)
    {
    actHandle = handle;
    actBuffer = (LPSTR)GetGlobMem(BUFFER_SIZE);
    actOffset = BUFFER_SIZE;
    do {
      LPVOID FAR *IndexVal = (LPVOID FAR *)GetGlobMem(anzdim * sizeof(LPVOID));
      for (int index = 0; index < anzdim; index++) {
        if (IndexDef[index]->type == MDTYPE_HASH) {
          int keylen = (int)ReadNextWord();
          LPSTR k = (LPSTR)GetGlobMem(keylen);
          IndexVal[index] = k;
          for (int i = 0; i < keylen; i++)
            *k++ = ReadNextChar();
          }
        else {
          LPWORD s = (LPWORD)GetGlobMem(sizeof(WORD));
          IndexVal[index] = s;
          *s = ReadNextWord();
          }
        }
      int datalen = (int)ReadNextWord();
      if (datalen > 0) {
        LPSTR data = (LPSTR)GetGlobMem(datalen);
        for (int i = 0; i < datalen; i++)
          data[i] = ReadNextChar();
        Write(IndexVal,data);
        FreeGlobMem (data);
        }
      for (int i = 0 ; i < anzdim ; i++)
        if (IndexVal[i] != NULL) FreeGlobMem (IndexVal[i]);
      FreeGlobMem (IndexVal);
      } while (actOffset <= BUFFER_SIZE);
    FreeGlobMem(actBuffer);
    }
  void FreeEbene(int dim, LPVOID actEbene)
    {
    if (actEbene != NULL) {
      if (dim < anzdim) {
        switch (IndexDef[dim]->type) {
          case MDTYPE_VARIABEL:
          case MDTYPE_FIX:
            {
            short anzindex = GetBlockSize(actEbene) / sizeof(LPVOID);
            for (int i = 0; i < anzindex; i++)
              FreeEbene(dim + 1,((LPVOID FAR *)actEbene)[i]);
            FreeGlobMem(actEbene);
            }
            break;
          case MDTYPE_HASH:
            {
            hash FAR *h = (hash FAR *)actEbene;
            for (int i = 0 ; i < int (h->hash_dimension) ; i++) {
              for (LPhash_entry e = h->Table + i ; e != NULL ; ) {
                if (!h->is_empty (e)) {
                  if (e->Data != NULL) {
                    FreeEbene(dim + 1,*((LPVOID FAR *)(e->Data)));
                    }
                  }
                LPhash_entry next = e->Next ;
                e = next;
                }
              }
            delete h;
            }
            break;
          default:
            DBWIN_ASSERT (FALSE);
          }
        }
      else {
        FreeGlobMem(actEbene);
        }
      }
    }
  void FreeAll()
    {
    // einfach den ganzen Block freigeben ...
    FreeEbene(0,root);
    // jetzt noch die Indexdefinitionen freigeben
    for (int i = 0; i < anzdim; i++)
      FreeGlobMem(IndexDef[i]);
    }
  };
typedef MultiDim FAR *LPMULTIDIM;

#pragma pack(1)
struct DefMultiDim_param {
  WORD  parSize;
  DWORD MDObj;
  DWORD anzdim;
  DWORD freepar[1];
  };
#pragma pack()

BOOL DefMultiDim (mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & EM_LOAD) {
    DefMultiDim_param FAR *par = (DefMultiDim_param FAR *) param;
    DBINT FAR *lpanzdim = (DBINT FAR *)c->ReadlData (par->anzdim);
    DBWIN_ASSERT ((lpanzdim != NULL) && (*lpanzdim > 0));
    LPMULTIDIM md = (LPMULTIDIM)GetGlobMem(sizeof(MultiDim) + (*lpanzdim - 1) * sizeof(LPMDINDEXDEF));
    md->anzdim = *lpanzdim;
    LPDWORD actpar = par->freepar;
    for (int i = 0; i < md->anzdim; i++) {
      md->IndexDef[i] = (LPMDINDEXDEF)GetGlobMem(sizeof(MDIndexDef));
      DBINT FAR *lptype = (DBINT FAR *)c->ReadlData(*actpar++);
      DBWIN_ASSERT (lptype != NULL);
      md->IndexDef[i]->type = *lptype;
      switch (*lptype) {
        case MDTYPE_VARIABEL:
          {
          LPINT lpminind = (LPINT)c->ReadlData(*actpar++);
          DBWIN_ASSERT (lpminind != NULL);
          md->IndexDef[i]->addl.v.minind = *lpminind;
          }
          break;
        case MDTYPE_FIX:
          {
          LPINT lpminind = (LPINT)c->ReadlData(*actpar++);
          DBWIN_ASSERT (lpminind != NULL);
          md->IndexDef[i]->addl.f.minind = *lpminind;
          LPINT lpmaxind = (LPINT)c->ReadlData(*actpar++);
          DBWIN_ASSERT (lpmaxind != NULL);
          md->IndexDef[i]->addl.f.maxind = *lpmaxind;
          }
          break;
        case MDTYPE_HASH:
          {
          LPINT lphashdim = (LPINT)c->ReadlData(*actpar++);
          DBWIN_ASSERT (lphashdim != NULL);
          md->IndexDef[i]->addl.h.hashdim = *lphashdim;
          }
          break;
        default:
          DBWIN_ASSERT (FALSE);
        }
      }
    c->WritelData (par->MDObj, &md, sizeof(md), LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    DefMultiDim_param FAR *par = (DefMultiDim_param FAR *) param;
    LPMULTIDIM FAR* lpmd = (LPMULTIDIM FAR *)c->ReadlData (par->MDObj);
    if ((lpmd != NULL) && (*lpmd)) {
      (*lpmd)->FreeAll();
      FreeGlobMem(*lpmd);
      c->DellData (par->MDObj, LPSTR(param)-sizeof(WORD));
      }
    }
  return FALSE;
  }


#pragma pack(1)
struct WriteMultiDim_param {
  WORD  parSize;
  DWORD MDObj;
  DWORD data;
  DWORD index[1];
  };
#pragma pack()

BOOL WriteMultiDim (mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    WriteMultiDim_param FAR *par = (WriteMultiDim_param FAR *) param;
    int anzpars = (par->parSize - sizeof(WriteMultiDim_param)) / sizeof(DWORD) + 1;
    LPMULTIDIM FAR* lpmd = (LPMULTIDIM FAR *)c->ReadlData (par->MDObj);
    DBWIN_ASSERT ((lpmd != NULL) && (*lpmd)) ;
    DBWIN_ASSERT ((*lpmd)->anzdim == anzpars);
    LPVOID data = c->ReadlData (par->data);
    LPVOID FAR *IndexVal = (LPVOID FAR *)GetGlobMem(anzpars * sizeof(LPVOID));
    for (int i = 0; i < anzpars; i++)
      IndexVal[i] = c->ReadlData(par->index[i]);
    (*lpmd)->Write(IndexVal,data);
    FreeGlobMem (IndexVal);
    }
  if (mode & EM_FIXCONNECTION) {
    WriteMultiDim_param FAR *par = (WriteMultiDim_param FAR *) param;
    int anzpars = (par->parSize - sizeof(WriteMultiDim_param)) / sizeof(DWORD) + 1;
    for (int i = 0; i < anzpars; i++)
      c->SetlConnection(par->index[i],LPSTR(param)-sizeof(WORD));
    c->SetlConnection(par->data,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    WriteMultiDim_param FAR *par = (WriteMultiDim_param FAR *) param;
    int anzpars = (par->parSize - sizeof(WriteMultiDim_param)) / sizeof(DWORD) + 1;
    for (int i = 0; i < anzpars; i++)
      c->ClearlConnection(par->index[i],LPSTR(param)-sizeof(WORD));
    c->ClearlConnection(par->data,LPSTR(param)-sizeof(WORD));
    }
  return FALSE;
  }


#pragma pack(1)
struct ReadMultiDim_param {
  WORD  parSize;
  DWORD MDObj;
  DWORD data;
  DWORD index[1];
  };
#pragma pack()

BOOL ReadMultiDim (mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    ReadMultiDim_param FAR *par = (ReadMultiDim_param FAR *) param;
    int anzpars = (par->parSize - sizeof(ReadMultiDim_param)) / sizeof(DWORD) + 1;
    LPMULTIDIM FAR* lpmd = (LPMULTIDIM FAR *)c->ReadlData (par->MDObj);
    DBWIN_ASSERT ((lpmd != NULL) && (*lpmd)) ;
    DBWIN_ASSERT ((*lpmd)->anzdim == anzpars);
    LPVOID FAR *IndexVal = (LPVOID FAR *)GetGlobMem(anzpars * sizeof(LPVOID));
    for (int i = 0; i < anzpars; i++)
      IndexVal[i] = c->ReadlData(par->index[i]);
    LPVOID data = (*lpmd)->Read(IndexVal);
    if (data != NULL)
      c->WritelData(par->data,data,GetBlockSize(data),LPSTR(param)-sizeof(WORD));
    else
      c->DellData(par->data,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    ReadMultiDim_param FAR *par = (ReadMultiDim_param FAR *) param;
    int anzpars = (par->parSize - sizeof(ReadMultiDim_param)) / sizeof(DWORD) + 1;
    for (int i = 0; i < anzpars; i++)
      c->SetlConnection(par->index[i],LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    ReadMultiDim_param FAR *par = (ReadMultiDim_param FAR *) param;
    int anzpars = (par->parSize - sizeof(ReadMultiDim_param)) / sizeof(DWORD) + 1;
    for (int i = 0; i < anzpars; i++)
      c->ClearlConnection(par->index[i],LPSTR(param)-sizeof(WORD));
    }
  return FALSE;
  }


#pragma pack(1)
struct LoadMultiDim_param {
  WORD  parSize;
  DWORD MDObj;
  DWORD FileHandle;
  };
#pragma pack()

BOOL LoadMultiDim (mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & EM_LOAD) {
    LoadMultiDim_param FAR *par = (LoadMultiDim_param FAR *) param;
    HFILE FAR* lphFile = (HFILE FAR *)c->ReadlData (par->FileHandle);
    DBWIN_ASSERT ((lphFile != NULL) && (*lphFile)) ;
    LPMULTIDIM FAR* lpmd = (LPMULTIDIM FAR *)c->ReadlData (par->MDObj);
    DBWIN_ASSERT ((lpmd != NULL) && (*lpmd)) ;
    (*lpmd)->LoadFromFile(*lphFile);
    }
  return FALSE;
  }

