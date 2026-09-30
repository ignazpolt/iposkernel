COPY ..\..\%ACTVERS%.SRC\HOOK\dmwhook.L32

rc -r -v -dWIN32 -fodmwhook.res /I..\..\%ACTVERS%.SRC\HOOK /I..\..\%ACTVERS%.SRC\Include /I..\..\%ACTVERS%.SRC ..\..\%ACTVERS%.SRC\HOOK\dmwhook.rc

link /DLL /DEBUG @dmwhook.l32
if errorlevel 1 goto error
goto continue
:error
pause
:continue

copy dmwhook.dll ..\*.*
copy dmwhook.lib ..\*.*
copy dmwhook.exp ..\*.*
copy dmwhook.dll ..\restool\*.*


