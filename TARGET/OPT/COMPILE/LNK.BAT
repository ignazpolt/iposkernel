COPY ..\..\..\SOURCE\COMPILE\COMPILE.L32

rc -r -v -dWIN32 -foddsmem.res /I..\..\..\SOURCE\COMPILE /I..\..\..\SOURCE\Include /I..\..\..\SOURCE ..\..\..\SOURCE\COMPILE\compile.rc

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
