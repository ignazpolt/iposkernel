del err

call makec ..\..\%ACTVERS%.SRC\ddsora\*.cpp *.obj COMPDLL1
if exist ddsora.dll if %ERRORLEVEL% equ 0 del ddsora.dll

call makec ..\..\%ACTVERS%.SRC\ddsora\*.rc *.res RCCOMP
if exist ddsora.dll if %ERRORLEVEL% equ 0 del ddsora.dll

if not exist ddsora.dll call lnk.bat
