del err

call makec ..\..\..\SOURCE\ctool\*.cpp *.obj COMPDLL
if exist ctool.dll if %ERRORLEVEL% equ 0 del ctool.dll

call makec ..\..\..\SOURCE\ctool\*.rc *.res RCCOMP
if exist ctool.dll if %ERRORLEVEL% equ 0 del ctool.dll

if not exist ctool.dll call lnk.bat
