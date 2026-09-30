del err

call makec ..\..\%ACTVERS%.SRC\image\*.cpp *.obj COMPDLL1
if exist tiffimg.dll if %ERRORLEVEL% equ 0 del tiffimg.dll

call makec ..\..\%ACTVERS%.SRC\image\*.c *.obj COMPDLL1
if exist tiffimg.dll if %ERRORLEVEL% equ 0 del tiffimg.dll

call makec ..\..\%ACTVERS%.SRC\image\*.rc *.res RCCOMP
if exist tiffimg.dll if %ERRORLEVEL% equ 0 del tiffimg.dll

if not exist tiffimg.dll call lnk.bat
