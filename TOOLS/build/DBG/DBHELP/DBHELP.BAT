del err

call makec ..\..\..\SOURCE\dbhelp\*.cpp *.obj COMPDLL
if exist dbhelp.dll if %ERRORLEVEL% equ 0 del dbhelp.dll

call makec ..\..\..\SOURCE\dbhelp\*.rc *.res RCCOMP
if exist dbhelp.dll if %ERRORLEVEL% equ 0 del dbhelp.dll

if not exist dbhelp.dll call lnk.bat
