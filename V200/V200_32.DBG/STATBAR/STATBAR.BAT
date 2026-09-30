del err

call makec ..\..\%ACTVERS%.SRC\statbar\*.cpp *.obj COMPDLL
if exist statbar.dll if %ERRORLEVEL% equ 0 del statbar.dll

call makec ..\..\%ACTVERS%.SRC\statbar\*.rc *.res RCCOMP
if exist statbar.dll if %ERRORLEVEL% equ 0 del statbar.dll

if not exist statbar.dll call lnk.bat
