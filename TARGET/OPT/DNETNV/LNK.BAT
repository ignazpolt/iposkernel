COPY ..\..\..\SOURCE\DNETNV\dnetnv.L32
COPY ..\..\..\SOURCE\DNETNV\dnetnv32.def

rc -r -v -dWIN32 -fodnetnv.res /I..\..\..\SOURCE\DNETNV /I..\..\..\SOURCE\Include /I..\..\..\SOURCE ..\..\..\SOURCE\DNETNV\dnetnv.rc

link /DLL /DEBUG @dnetnv.l32
if errorlevel 1 goto error
goto continue
:error
pause
:continue

copy dnetnv.dll ..\*.*
copy dnetnv.lib ..\*.*
copy dnetnv.exp ..\*.*
copy dnetnv.dll ..\restool\*.*
