COPY ..\..\..\SOURCE\DDSMEM\DDSMEM.L32

rc -r -v -dWIN32 -foddsmem.res /I..\..\..\SOURCE\DDSMEM /I..\..\..\SOURCE\Include /I..\..\..\SOURCE ..\..\..\SOURCE\DDSMEM\ddsmem.rc

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
