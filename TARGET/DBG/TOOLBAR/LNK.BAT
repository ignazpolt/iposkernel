COPY ..\..\..\SOURCE\TOOLBAR\toolbar.L32

rc -r -v -dWIN32 -fomsdntb.res /I..\..\..\SOURCE\TOOLBAR /I..\..\..\SOURCE\Include /I..\..\..\SOURCE ..\..\..\SOURCE\TOOLBAR\msdntb.rc

link /DLL /DEBUG @toolbar.l32
if errorlevel 1 goto error
goto continue
:error
pause
:continue

copy toolbar.dll ..\*.*
copy toolbar.lib ..\*.*
copy toolbar.exp ..\*.*
copy toolbar.dll ..\restool\*.*
