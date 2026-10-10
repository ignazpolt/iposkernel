COPY ..\..\..\SOURCE\HOOK\dmwhook.L32

rc -r -v -dWIN32 -fodmwhook.res /I..\..\..\SOURCE\HOOK /I..\..\..\SOURCE\Include /I..\..\..\SOURCE ..\..\..\SOURCE\HOOK\dmwhook.rc

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


