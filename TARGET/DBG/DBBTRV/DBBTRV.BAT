del err

call makec ..\..\..\SOURCE\dbbtrv\*.cpp *.obj COMPDLL
if exist dbbtrv.dll if %ERRORLEVEL% equ 0 del dbbtrv.dll

call makec ..\..\..\SOURCE\dbbtrv\*.rc *.res RCCOMP
if exist dbbtrv.dll if %ERRORLEVEL% equ 0 del dbbtrv.dll

if not exist dbbtrv.dll call lnk.bat
