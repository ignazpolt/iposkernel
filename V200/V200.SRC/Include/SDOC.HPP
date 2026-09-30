////////////////////////////////////////////////////
//  Dokumente in Dokumenten....
////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/include/rev/sdoc.hpv   1.2   02 Feb 1996 11:01:02   GERHOLD  $
//  $Log:   P:/marille/clinicum/include/rev/sdoc.hpv  $
// 
//    Rev 1.2   02 Feb 1996 11:01:02   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.1   24 Jun 1994 19:18:36   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.0   04 Oct 1993 09:48:14   HANNES
// Initial revision.
//
#ifdef SDOC
#define SDOC_INCLUDED
struct ObjectDef ;
class sFormDoc : public Form {
 public :
  sFormDoc (WORD AnzRun,LPSCRIPTCONTENT scent) : Form (AnzRun,scent)
    { }
  ObjectDef FAR *Anchore;
  mdiChild *parent;
  void PrepareContext (PaintContext *pc);
  BOOL ParentScaleChange (BOOL dorecalc = TRUE);
  void GetRectForParent (LPRECT dest,LPRECT source);
  virtual void Rescale (LPRECT);

  virtual void LoadData ()
    {
    ExCute (EM_LOAD | EM_FIXCONNECTION);
    }
  virtual void Reset ()
    {
    ExCute (EM_RESET);
    }

  virtual ~sFormDoc ()
    { MyHandle = 0 ; }

  virtual BOOL IsSmallDoc()
    { return TRUE ; }

  void LogToParentLog (fpt FAR *dest,fpt FAR *source);
  void ParentLogToLog (fpt FAR *dest,fpt FAR *source);
  LPVOID FAR *GetTransformList (int FAR *Anz);
  void PushToTransformList (LPVOID p);
  void doAllParentTransforms ();
  };
#endif

