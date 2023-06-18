@ECHO OFF
tasm /m2 code.asm
tlink /3 code.obj
del *.obj
del *.map