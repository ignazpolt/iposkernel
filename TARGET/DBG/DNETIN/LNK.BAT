COPY ..\..\..\SOURCE\DNETIN\dnetin.L32
COPY ..\..\..\SOURCE\DNETIN\dnetin32.def

rc -r -v -dWIN32 -fodnetin.res /I..\..\..\SOURCE\DNETIN /I..\..\..\SOURCE\Include /I..\..\..\SOURCE ..\..\..\SOURCE\DNETIN\dnetin.rc

link /DLL /DEBUG @dnetin.l32
if errorlevel 1 goto error
goto continue
:error
pause
:continue

copy dnetin.dll ..\*.*
copy dnetin.lib ..\*.*
copy dnetin.exp ..\*.*
copy dnetin.dll ..\restool\*.*

