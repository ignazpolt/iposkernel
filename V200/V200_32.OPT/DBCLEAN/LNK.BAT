COPY ..\..\%ACTVERS%.SRC\DBCLEAN\DBCLEAN.L32

rc -r -v -dWIN32 -fodbclean.res /I..\..\%ACTVERS%.SRC\DBCLEAN /I..\..\%ACTVERS%.SRC\Include /I..\..\%ACTVERS%.SRC ..\..\%ACTVERS%.SRC\DBCLEAN\dbclean.rc

link /DLL /DEBUG @dbclean.l32
if errorlevel 1 goto error
goto continue
:error
pause
:continue

copy dbclean.dll ..\*.*
copy dbclean.lib ..\*.*
copy dbclean.exp ..\*.*
copy dbclean.dll ..\restool\*.*

