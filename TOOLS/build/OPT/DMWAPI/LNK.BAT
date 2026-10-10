COPY ..\..\..\SOURCE\DMWAPI\dmwapi.L32

rc -r -v -dWIN32 -fodmwapi.res /I..\..\..\SOURCE\DMWAPI /I..\..\..\SOURCE\Include /I..\..\..\SOURCE ..\..\..\SOURCE\DMWAPI\dmwapi.rc

link /DLL /DEBUG @dmwapi.l32
if errorlevel 1 goto error
goto continue
:error
pause
:continue

copy dmwapi.dll ..\*.*
copy dmwapi.lib ..\*.*
copy dmwapi.exp ..\*.*
copy dmwapi.dll ..\restool\*.*
