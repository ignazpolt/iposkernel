del err

call makec ..\..\..\SOURCE\ddsmem\*.cpp *.obj COMPDLL
if exist ddsmem.dll if %ERRORLEVEL% equ 0 del ddsmem.dll

call makec ..\..\..\SOURCE\ddsmem\*.rc *.res RCCOMP
if exist ddsmem.dll if %ERRORLEVEL% equ 0 del ddsmem.dll

if not exist ddsmem.dll call lnk.bat
