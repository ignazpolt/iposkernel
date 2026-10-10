del err

call makec ..\..\..\SOURCE\hook\*.cpp *.obj COMPDLL
if exist dmwhook.dll if %ERRORLEVEL% equ 0 del dmwhook.dll

call makec ..\..\..\SOURCE\hook\*.rc *.res RCCOMP
if exist dmwhook.dll if %ERRORLEVEL% equ 0 del dmwhook.dll

if not exist dmwhook.dll call lnk.bat
