del err

call makec ..\..\%ACTVERS%.SRC\dbclean\*.cpp *.obj COMPDLL
if exist dbclean.dll if %ERRORLEVEL% equ 0 del dbclean.dll

call makec ..\..\%ACTVERS%.SRC\dbclean\*.rc *.res RCCOMP
if exist dbclean.dll if %ERRORLEVEL% equ 0 del dbclean.dll

if not exist dbclean.dll call lnk.bat
