del err

call makec ..\..\%ACTVERS%.SRC\dbbtrv\*.cpp *.obj COMPDLL
if exist dbbtrv.dll if %ERRORLEVEL% equ 0 del dbbtrv.dll

call makec ..\..\%ACTVERS%.SRC\dbbtrv\*.rc *.res RCCOMP
if exist dbbtrv.dll if %ERRORLEVEL% equ 0 del dbbtrv.dll

if not exist dbbtrv.dll call lnk.bat
