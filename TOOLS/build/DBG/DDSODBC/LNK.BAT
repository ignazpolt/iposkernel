COPY ..\..\..\SOURCE\DDSODBC\ddsodbc.l32
COPY ..\..\..\SOURCE\DDSODBC\ddsodb32.def

rc -r -v -dWIN32 -foddsodbc.res /I..\..\..\SOURCE\DDSODBC ^/I..\..\..\SOURCE\Include ^/I..\..\..\SOURCE ..\..\..\SOURCE\DDSODBC\ddsodbc.rc

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

