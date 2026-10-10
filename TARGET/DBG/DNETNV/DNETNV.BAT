del err

call makec ..\..\..\SOURCE\dnetnv\*.cpp *.obj COMPDLL
if exist dnetnv.dll if %ERRORLEVEL% equ 0 del dnetnv.dll

call makec ..\..\..\SOURCE\dnetnv\*.rc *.res RCCOMP
if exist dnetnv.dll if %ERRORLEVEL% equ 0 del dnetnv.dll

if not exist dnetnv.dll call lnk.bat
