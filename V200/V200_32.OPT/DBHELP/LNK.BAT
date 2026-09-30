COPY ..\..\%ACTVERS%.SRC\DBHELP\DBHELP.L32

rc -r -v -dWIN32 -fodbhelp.res /I..\..\%ACTVERS%.SRC\DBHELP /I..\..\%ACTVERS%.SRC\Include /I..\..\%ACTVERS%.SRC ..\..\%ACTVERS%.SRC\DBHELP\dbhelp.rc

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
