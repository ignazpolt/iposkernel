COPY ..\..\..\SOURCE\DBCLEAN\DBCLEAN.L32

rc -r -v -dWIN32 -fodbclean.res /I..\..\..\SOURCE\DBCLEAN /I..\..\..\SOURCE\Include /I..\..\..\SOURCE ..\..\..\SOURCE\DBCLEAN\dbclean.rc

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

