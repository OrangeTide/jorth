; macros to call functions on Windows

%ifidn __OUTPUT_FORMAT__, win64
;;
;; Windows 64-bit
;;
%macro movreg 2
		%ifnum %2
			%if %2 == 0
				xor	%1,%1
			%elif %2 <= 4294967295
				mov	%1D,word %2
			%else
				mov	%1,qword %2
			%endif
		%else
			mov	%1,qword %2
		%endif
%endmacro

;; 64-bit STDCALL:
;; RCX	1st
;; RDX	2nd
;; R8	3rd
;; R9	4th
;; stack for remaining arguments
%imacro invoke 1-*
	%rotate 1
	%if %0 > 1
		movreg	RCX,%1
		%rotate 1
		%if %0 > 2
			movreg	RDX,%1
			%rotate 1
			%if %0 > 3
				movreg	R8,%1
				%rotate 1
				%if %0 > 4
					movreg	R9,%1
					%rotate 1
					%if %0 > 5
						%assign max %0-5
						%assign i 32
						%rep max
							mov	RAX,qword %1
							mov	qword [RSP+i],RAX
							%assign i i+8
							%rotate 1
						%endrep
					%endif
				%endif
			%endif
		%endif
	%endif
	call	%1
%endmacro

%macro funcpreamble 0
	sub	RSP, 8			; Align the stack to a multiple of 16 bytes
	sub	RSP, 32			; 32 bytes of shadow space

%endmacro

%macro funcpost 0
	add	RSP, 32			; Remove the 32 bytes
%endmacro

%elifidn __OUTPUT_FORMAT__, win32
;;
;; Windows 32-bit
;;

%imacro invoke 1-*
	%rotate -1
	%assign max %0-1
	%assign i 32
	%rep max
		push	%1
		%rotate -1
	%endrep
	call %1
%endmacro

%macro funcpreamble 0
	push	EBP
	mov	EBP,ESP
%endmacro

%macro funcpost 0
	pop	EBP
	retn	16	;; TODO: code this up correctly
%endmacro

%else
%error Unsupported format
%endif
