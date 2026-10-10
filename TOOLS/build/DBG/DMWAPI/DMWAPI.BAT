del err

call makec ..\..\..\SOURCE\dmwapi\*.cpp *.obj COMPDLL1
if exist dmwapi.dll if %ERRORLEVEL% equ 0 del dmwapi.dll

call makec ..\..\..\SOURCE\dmwapi\*.rc *.res RCCOMP
if exist dmwapi.dll if %ERRORLEVEL% equ 0 del dmwapi.dll

if not exist dmwapi.dll call lnk.bat

