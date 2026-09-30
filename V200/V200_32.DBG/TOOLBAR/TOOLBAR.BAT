del err

call makec ..\..\%ACTVERS%.SRC\toolbar\*.cpp *.obj COMPDLL
if exist toolbar.dll if %ERRORLEVEL% equ 0 del toolbar.dll

call makec ..\..\%ACTVERS%.SRC\toolbar\*.rc *.res RCCOMP
if exist toolbar.dll if %ERRORLEVEL% equ 0 del toolbar.dll

if not exist toolbar.dll call lnk.bat
