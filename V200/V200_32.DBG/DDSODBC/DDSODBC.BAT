del err

call makec ..\..\%ACTVERS%.SRC\ddsodbc\*.cpp *.obj COMPDLL
if exist ddsodbc.dll if %ERRORLEVEL% equ 0 del ddsodbc.dll

call makec ..\..\%ACTVERS%.SRC\ddsodbc\*.rc *.res RCCOMP
if exist ddsodbc.dll if %ERRORLEVEL% equ 0 del ddsodbc.dll

if not exist ddsodbc.dll call lnk.bat
