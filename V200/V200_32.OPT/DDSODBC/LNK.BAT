COPY ..\..\%ACTVERS%.SRC\DDSODBC\ddsodbc.l32
COPY ..\..\%ACTVERS%.SRC\DDSODBC\ddsodb32.def

rc -r -v -dWIN32 -foddsodbc.res /I..\..\%ACTVERS%.SRC\DDSODBC ^/I..\..\%ACTVERS%.SRC\Include ^/I..\..\%ACTVERS%.SRC ..\..\%ACTVERS%.SRC\DDSODBC\ddsodbc.rc

link /DLL /DEBUG @ddsodbc.l32
if errorlevel 1 goto error
goto continue
:error
pause
:continue

copy ddsodbc.dll ..\*.*
copy ddsodbc.lib ..\*.*
copy ddsodbc.exp ..\*.*
copy ddsodbc.dll ..\restool\*.*

