del err

call makec ..\..\..\SOURCE\image\*.cpp *.obj COMPDLL1
if exist tiffimg.dll if %ERRORLEVEL% equ 0 del tiffimg.dll

call makec ..\..\..\SOURCE\image\*.c *.obj COMPDLL1
if exist tiffimg.dll if %ERRORLEVEL% equ 0 del tiffimg.dll

call makec ..\..\..\SOURCE\image\*.rc *.res RCCOMP
if exist tiffimg.dll if %ERRORLEVEL% equ 0 del tiffimg.dll

if not exist tiffimg.dll call lnk.bat
