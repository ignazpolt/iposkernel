if "%ACTVERS%"=="" set "ACTVERS=V200"

del err

call makec gendict.cpp *.obj MAKEC1
if exist ddsmem.dll if %ERRORLEVEL% equ 0 del restool.exe
call makec genres.cpp *.obj MAKEC1
if exist ddsmem.dll if %ERRORLEVEL% equ 0 del restool.exe
call makec genfull.cpp *.obj MAKEC1
if exist ddsmem.dll if %ERRORLEVEL% equ 0 del restool.exe

call makec ..\..\..\SOURCE\restool\gendict.cpp *.obj MAKEC1
if exist ddsmem.dll if %ERRORLEVEL% equ 0 del restool.exe
call makec ..\..\..\SOURCE\restool\genres.cpp *.obj MAKEC1
if exist ddsmem.dll if %ERRORLEVEL% equ 0 del restool.exe
call makec ..\..\..\SOURCE\restool\genfull.cpp *.obj MAKEC1
if exist ddsmem.dll if %ERRORLEVEL% equ 0 del restool.exe

call makec ..\..\..\SOURCE\restool\*.cpp *.obj
if exist ddsmem.dll if %ERRORLEVEL% equ 0 del restool.exe

call makec ..\..\..\SOURCE\ctool\myline.cpp myline.obj
if exist ddsmem.dll if %ERRORLEVEL% equ 0 del restool.exe

call makec ..\..\..\SOURCE\restool\*.rc *.res RCCOMP
if exist ddsmem.dll if %ERRORLEVEL% equ 0 del restool.exe

if not exist restool.exe call lnk.bat
