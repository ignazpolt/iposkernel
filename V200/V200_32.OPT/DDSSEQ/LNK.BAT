COPY ..\..\%ACTVERS%.SRC\DDSSEQ\ddsseq.L32
COPY ..\..\%ACTVERS%.SRC\DDSSEQ\ddsseq32.def

rc -r -v -dWIN32 -foddsseq.res /I..\..\%ACTVERS%.SRC\DDSSEQ /I..\..\%ACTVERS%.SRC\Include /I..\..\%ACTVERS%.SRC ..\..\%ACTVERS%.SRC\DDSSEQ\ddsseq.rc

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
