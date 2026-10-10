COPY ..\..\..\SOURCE\CTOOL\ctool.L32

rc -r -v -dWIN32 -fotoolbar.res /I..\..\..\SOURCE\CTOOL /I..\..\..\SOURCE\Include /I..\..\..\SOURCE ..\..\..\SOURCE\CTOOL\toolbar.rc

link /DLL /DEBUG @ctool.l32
if errorlevel 1 goto error
goto continue
:error
pause
:continue

copy ctool.dll ..\*.*
copy ctool.lib ..\*.*
copy ctool.exp ..\*.*
copy ctool.dll ..\restool\*.*
