COPY ..\..\%ACTVERS%.SRC\COMPILE\COMPILE.L32

rc -r -v -dWIN32 -foddsmem.res /I..\..\%ACTVERS%.SRC\COMPILE /I..\..\%ACTVERS%.SRC\Include /I..\..\%ACTVERS%.SRC ..\..\%ACTVERS%.SRC\COMPILE\compile.rc

link /DLL /DEBUG @compile.l32
if errorlevel 1 goto error
goto continue
:error
pause
:continue

copy compile.dll ..\*.* 
copy compile.lib ..\*.*
copy compile.exp ..\*.*
copy compile.dll ..\restool\*.* 
