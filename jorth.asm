;
; JORTH
;
; Copyright 2019 Jon Mayo
;
; Modification and redistribution is permitted. The works are without warranty.
;

global Start


%ifidn __OUTPUT_FORMAT__, win32
%define MessageBoxA _MessageBoxA@16
%define ExitProcess _ExitProcess@4
%endif

extern MessageBoxA
extern ExitProcess

%include	"win32n.inc"
%include	"invoke.inc"

section .data

	message		db "Test", 0
	title		db "Title", 0

section .text

Start:
	funcpreamble

	;; TODO: code up a main loop

	invoke	MessageBoxA,NULL,message,title,MB_OK

	funcpost

	; Terminate
	invoke ExitProcess,0
