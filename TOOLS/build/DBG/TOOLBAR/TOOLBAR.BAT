del err

call makec ..\..\..\SOURCE\toolbar\*.cpp *.obj COMPDLL
if exist toolbar.dll if %ERRORLEVEL% equ 0 del toolbar.dll

call makec ..\..\..\SOURCE\toolbar\*.rc *.res RCCOMP
if exist toolbar.dll if %ERRORLEVEL% equ 0 del toolbar.dll

if not exist toolbar.dll call lnk.bat
