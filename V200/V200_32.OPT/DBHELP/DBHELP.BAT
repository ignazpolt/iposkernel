del err

call makec ..\..\%ACTVERS%.SRC\dbhelp\*.cpp *.obj COMPDLL
if exist dbhelp.dll if %ERRORLEVEL% equ 0 del dbhelp.dll

call makec ..\..\%ACTVERS%.SRC\dbhelp\*.rc *.res RCCOMP
if exist dbhelp.dll if %ERRORLEVEL% equ 0 del dbhelp.dll

if not exist dbhelp.dll call lnk.bat
