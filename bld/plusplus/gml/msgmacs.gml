.sr $$msgcntr=-1
.sr $$msgpfx=''
.*
:cmt. :MSGGRP. Warn1
.gt msggrp del
.dm msggrp begin
.sr $$msgcntr=-1
.sr $$msgpfx=''
.dm msggrp end
.gt msggrp add msggrp att
.*
:cmt. :eMSGGRP. Warn1
.gt emsggrp del
.dm emsggrp begin
.if &e'&dohelp eq 0 .do begin
.   .endnote
.do end
.sr $$msgcntr=-1
.sr $$msgpfx=''
.dm emsggrp end
.gt emsggrp add emsggrp att
.*
:cmt. :MSGGRPSTR. W
.gt msggrpstr del
.dm msggrpstr begin
.sr $$msgpfx=&*
.dm msggrpstr end
.gt msggrpstr add msggrpstr att
.*
:cmt. :MSGGRPNUM. 100
.gt msggrpnum del
.dm msggrpnum begin
.sr $$msgcntr=&*
.sr $$msgcntr=&$$msgcntr.-1
.dm msggrpnum end
.gt msggrpnum add msggrpnum att
.*
:cmt. :MSGGRPTXT. Warning Level 1 Messages
.gt msggrptxt del
.dm msggrptxt begin
.if &e'&dohelp eq 0 .do begin
.   .section &*
.   .begnote
.do end
.dm msggrptxt end
.gt msggrptxt add msggrptxt att
.*
:cmt. :MSGLVL W1
.gt msglvl del
.dm msglvl begin
:cmt. .section &*
:cmt. .begnote
.dm msglvl end
.gt msglvl add msglvl att
.*
:cmt. :EMSGLVL.
.gt emsglvl del
.dm emsglvl begin
:cmt. .endnote
.dm emsglvl end
.gt emsglvl add emsglvl att
.*
:cmt. :MSGSYM. ERR_CALL_WATCOM
.gt msgsym del
.dm msgsym begin
.sr $$msgcntr=&$$msgcntr.+1
.sr $$msgnumb=&$$msgcntr.
.if &$$msgcntr. lt 100 .do begin
.   .sr $$msgnumb=/&'right('&$$msgcntr.',3,'0')/
.do end
.dm msgsym end
.gt msgsym add msgsym att
.*
:cmt. :MSGTXT. internal compiler error
.gt msgtxt del
.dm msgtxt begin
.cw $
.se *ttl="&'strip(&*)"
.if &'compare(&*ttl.,'filler') ne 0 .do begin
.   .if &e'&dohelp eq 0 .do begin
.   .   .keep
.   .   .note &$$msgpfx.&$$msgnumb
.   .   .us &*
.   .   .np
.   .do end
.   .el .do begin
:ZH2.&$$msgpfx.&$$msgnumb. &*ttl.
.   .   .cntents &$$msgpfx.&$$msgnumb. &*ttl.
.   .   .pu 1 .ixsect &$$msgpfx.&$$msgnumb. &*ttl.
:ZI1.&*ttl.
.   .   .pu 1 .ixline `&*ttl.`
.   .   .sr *ctxn=&$$msgcntr.+1
.   .   .if '&dotarget' eq 'os2' .do begin
.   .   .   .sr *ctxn=&$$msgcntr.+1+20000
.   .   .do end
.   .   .ctxstr &$$msgpfx.&$$msgnumb. &*ttl.
.   .   .pu 2 #define HLP_&'upper(&ctx_str.) &*ctxn
.   .   .np
.   .do end
.do end
.cw ;
.dm msgtxt end
.gt msgtxt add msgtxt att
.*
:cmt. :MSGJTXT. internal compiler error
.gt msgjtxt del
.dm msgjtxt begin
.dm msgjtxt end
.gt msgjtxt add msgjtxt att
.*
:cmt. :MSGATTR. attribute value
.gt msgattr del
.dm msgattr begin
.dm msgattr end
.gt msgattr add msgattr att
.*
:cmt. :ANSI
.gt ansi del
.dm ansi begin
.dm ansi end
.gt ansi add ansi att
:cmt. :ANSIERR
.gt ansierr del
.dm ansierr begin
.dm ansierr end
.gt ansierr add ansierr att
:cmt. :ANSIWARN
.gt ansiwarn del
.dm ansiwarn begin
.dm ansiwarn end
.gt ansiwarn add ansiwarn att
:cmt. :INFO
.gt info del
.dm info begin
.dm info end
.gt info add info att
:cmt. :WARNING
.gt warning del
.dm warning begin
.dm warning end
.gt warning add warning att
:cmt. :ERROR
.gt error del
.dm error begin
.dm error end
.gt error add error att
.*
:cmt. :errgood.
.gt errgood del
.dm errgood begin
.exam begin
.dm errgood end
.gt errgood add errgood att
.*
:cmt. :eerrgood.
.gt eerrgood del
.dm eerrgood begin
.exam end
.dm eerrgood end
.gt eerrgood add eerrgood att
.*
:cmt. :errbad.
.gt errbad del
.dm errbad begin
.exam begin
.dm errbad end
.gt errbad add errbad att
.*
:cmt. :eerrbad.
.gt eerrbad del
.dm eerrbad begin
.exam end
.dm eerrbad end
.gt eerrbad add eerrbad att
.*
:cmt. :errbreak.
.gt errbreak del
.dm errbreak begin
.exam break
.dm errbreak end
.gt errbreak add errbreak att
.*
.* close the header file
.*
.pu 2
