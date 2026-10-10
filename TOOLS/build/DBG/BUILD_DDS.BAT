del err
@echo "Nothing changed !" > dontlink

if %ERRORLEVEL% equ 0 del dontlink
call makec ..\..\SOURCE\*.c *.obj
if %ERRORLEVEL% equ 0 del dontlink
call makec ..\..\SOURCE\*.cpp *.obj
if %ERRORLEVEL% equ 0 del dontlink

call makec ..\..\SOURCE\*.rc *.res RCCOMP
if %ERRORLEVEL% equ 0 del dontlink

if not exist dontlink call lnk.bat

del dontlink
