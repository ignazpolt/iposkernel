del err

call makec ..\..\..\SOURCE\dbclean\*.cpp *.obj COMPDLL
if exist dbclean.dll if %ERRORLEVEL% equ 0 del dbclean.dll

call makec ..\..\..\SOURCE\dbclean\*.rc *.res RCCOMP
if exist dbclean.dll if %ERRORLEVEL% equ 0 del dbclean.dll

if not exist dbclean.dll call lnk.bat
