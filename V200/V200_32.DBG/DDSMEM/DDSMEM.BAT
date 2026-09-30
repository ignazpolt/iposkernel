del err

call makec ..\..\%ACTVERS%.SRC\ddsmem\*.cpp *.obj COMPDLL
if exist ddsmem.dll if %ERRORLEVEL% equ 0 del ddsmem.dll

call makec ..\..\%ACTVERS%.SRC\ddsmem\*.rc *.res RCCOMP
if exist ddsmem.dll if %ERRORLEVEL% equ 0 del ddsmem.dll

if not exist ddsmem.dll call lnk.bat
