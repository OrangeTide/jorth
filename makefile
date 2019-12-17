GOLINK=tools/GoLink.exe
LD64=x86_64-w64-mingw32-ld
LD32=i686-w64-mingw32-ld

all : jorth32.exe jorth64.exe
clean :
	$(RM) jorth64.exe jorth64.obj
	$(RM) jorth32.exe jorth32.obj
jorth32.exe : jorth32.obj
jorth64.exe : jorth64.obj
%64.obj : %.asm
	nasm -f win64 -o $@ $<
%32.obj : %.asm
	nasm -f win32 -o $@ $<
%64.exe : %64.obj
ifneq ($(USE_GOLINK),)
	$(GOLINK) /fo $@ /entry:Start kernel32.dll user32.dll $<
else
	$(LD64) -o $@ $< -lkernel32 -luser32
endif
%32.exe : %32.obj
ifneq ($(USE_GOLINK),)
	$(GOLINK) /fo $@ /entry:Start kernel32.dll user32.dll $<
else
	$(LD32) -o $@ $< -lkernel32 -luser32
endif
