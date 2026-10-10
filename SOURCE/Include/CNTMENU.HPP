//------------------------------------------------------------------------------------------------------------------------
// $Header:   P:/marille/clinicum/include/rev/cntmenu.hpv   1.0   29 Oct 1997 18:59:16   Hannes  $
// $Log:   P:/marille/clinicum/include/rev/cntmenu.hpv  $
// 
//    Rev 1.0   29 Oct 1997 18:59:16   Hannes
// Initial revision.
//------------------------------------------------------------------------------------------------------------------------
DLLExport void _export WINAPI FreeGlobalContextMenu ();
DLLExport void _export WINAPI AddGlobalContextMenu (WORD Kategorie,WORD Type,LPSTR Name,LPSTR ModName,LPSTR FuncName);
DLLExport WORD _export WINAPI GetFirstContextMenu (WORD Type,WORD Kategorie,LPSTR Buffer,int bSize);
DLLExport WORD _export WINAPI GetNextContextMenu (WORD Type,WORD Kategorie,WORD LastID,LPSTR Buffer,int bSize);
DLLExport void _export WINAPI CallContextMenu (WORD Id,LPVOID obj);

typedef void (* CALLCONTEXTFUNCTION) (LPSTR Mod,LPSTR Name,LPVOID obj);
