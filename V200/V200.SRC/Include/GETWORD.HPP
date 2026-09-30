#define WMIN  16
struct FAR UWEntry {
  WORD Nmbr;
  UWEntry FAR *Next;
  BYTE kData[1];
  };
typedef UWEntry FAR *LPUWENT;

class FAR UniqueWord {
 private :
  int keySize;
  LPUWENT l;

 public :
  DLLExport _export WINAPI UniqueWord (int s);
  DLLExport _export WINAPI ~UniqueWord ();

  DLLExport void _export WINAPI RemoveNum (WORD n);
  DLLExport WORD _export WINAPI GetNum (LPVOID d);
  DLLExport WORD _export WINAPI FindNum (LPVOID d);
  DLLExport LPVOID _export WINAPI GetKey (WORD Nmbr);

  DLLExport LPVOID _export WINAPI operator new (size_t s);
  DLLExport void _export WINAPI operator delete (LPVOID obj);
  };

