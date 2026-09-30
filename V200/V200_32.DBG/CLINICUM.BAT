del err
@echo "Nothing changed !" > dontlink

call makec ..\%ACTVERS%.SRC\expr.cpp ..\cobj\*.obj MAKEC1
if %ERRORLEVEL% equ 0 del dontlink
call makec ..\%ACTVERS%.SRC\*.c *.obj
if %ERRORLEVEL% equ 0 del dontlink
call makec ..\%ACTVERS%.SRC\*.cpp *.obj
if %ERRORLEVEL% equ 0 del dontlink

call makec ..\%ACTVERS%.SRC\*.rc *.res RCCOMP
if %ERRORLEVEL% equ 0 del dontlink

if not exist dontlink call lnk.bat

del dontlink
