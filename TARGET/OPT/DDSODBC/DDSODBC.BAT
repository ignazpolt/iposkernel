del err

call makec ..\..\..\SOURCE\ddsodbc\*.cpp *.obj COMPDLL
if exist ddsodbc.dll if %ERRORLEVEL% equ 0 del ddsodbc.dll

call makec ..\..\..\SOURCE\ddsodbc\*.rc *.res RCCOMP
if exist ddsodbc.dll if %ERRORLEVEL% equ 0 del ddsodbc.dll

if not exist ddsodbc.dll call lnk.bat
