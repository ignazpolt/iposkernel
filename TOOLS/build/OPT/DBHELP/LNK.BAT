COPY ..\..\..\SOURCE\DBHELP\DBHELP.L32

rc -r -v -dWIN32 -fodbhelp.res /I..\..\..\SOURCE\DBHELP /I..\..\..\SOURCE\Include /I..\..\..\SOURCE ..\..\..\SOURCE\DBHELP\dbhelp.rc

link /DLL /DEBUG @dbhelp.l32
if errorlevel 1 goto error
goto continue
:error
pause
:continue

copy dbhelp.dll ..\*.*
copy dbhelp.lib ..\*.*
copy dbhelp.exp ..\*.*
copy dbhelp.dll ..\restool\*.*
