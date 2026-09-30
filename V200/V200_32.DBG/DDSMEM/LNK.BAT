COPY ..\..\%ACTVERS%.SRC\DDSMEM\DDSMEM.L32

rc -r -v -dWIN32 -foddsmem.res /I..\..\%ACTVERS%.SRC\DDSMEM /I..\..\%ACTVERS%.SRC\Include /I..\..\%ACTVERS%.SRC ..\..\%ACTVERS%.SRC\DDSMEM\ddsmem.rc

link /DLL /DEBUG @ddsmem.l32
if errorlevel 1 goto error
goto continue
:error
pause
:continue

copy ddsmem.dll ..\*.* 
copy ddsmem.lib ..\*.*
copy ddsmem.exp ..\*.*
copy ddsmem.dll ..\restool\*.* 
