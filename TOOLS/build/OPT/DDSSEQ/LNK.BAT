COPY ..\..\..\SOURCE\DDSSEQ\ddsseq.L32
COPY ..\..\..\SOURCE\DDSSEQ\ddsseq32.def

rc -r -v -dWIN32 -foddsseq.res /I..\..\..\SOURCE\DDSSEQ /I..\..\..\SOURCE\Include /I..\..\..\SOURCE ..\..\..\SOURCE\DDSSEQ\ddsseq.rc

link /DLL /DEBUG @ddsseq.l32
if errorlevel 1 goto error
goto continue
:error
pause
:continue

copy ddsseq.dll ..
copy ddsseq.lib ..
copy ddsseq.exp ..
copy ddsseq.dll ..\restool\*.*
