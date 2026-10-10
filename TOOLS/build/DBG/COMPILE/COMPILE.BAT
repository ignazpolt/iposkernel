del err

call makec ..\..\..\SOURCE\compile\*.cpp *.obj COMPDLL
if exist compile.dll if %ERRORLEVEL% equ 0 del compile.dll

call makec ..\..\..\SOURCE\compile\*.rc *.res RCCOMP
if exist compile.dll if %ERRORLEVEL% equ 0 del compile.dll

if not exist compile.dll call lnk.bat
