; header for assembler

title JohanJaegerProj6

.386
.model flat, stdcall
.stack 4096

ExitProcess proto, 
	dwExitCode:dword

; imports

include Irvine32.inc

WriteString proto
Crlf proto
ReadChar proto
WriteChar proto
ReadHex proto
WriteHex proto
WaitMsg proto
Clrscr proto

; data segment

.data
menu byte	"boolean calculator", 0, "                  ", 0,
			"1. x and y        ", 0,
			"2. x or y         ", 0, "3. not x          ", 0,
			"4. x xor y        ", 0, "5. exit program   ", 0

inputprompt byte "enter corresponding integer: ", 0
operandprompt byte "enter 32-bit hexadecimal operand: ", 0
resultheader byte "the result is: ", 0
thankyou byte "thank you for using the calculator. goodbye!", 0
pressanykey byte "press any key to continue... ", 0

table dword	"1", offset ander, "2", offset order, "3", offset notter, "4", offset xorer, "5", offset exitprogram
operands dword 0, 0

; code segment

.code

menushow proc uses ecx edx ; procedure prints menu on screen.
	mov ecx, 7
	mov edx, offset menu

	display:
		call WriteString
		call Crlf
		add edx, 19 ; each null-terminated string in menu consists of 19 bytes.

	loop display

	call Crlf
	ret
menushow endp

reqinput proc uses edx ; stores character-input encoding at al.
	mov edx, offset inputprompt
	call WriteString

	call ReadChar ; read character input.
	call WriteChar ; write input to screen.

	call Crlf
	call Crlf

	ret
reqinput endp

restartcalc proc
	call WaitMsg
	call Clrscr
	jmp main
restartcalc endp

findcall proc uses ebx ecx ; looks up corresponding procedure in table, based on al.
	mov ecx, 5
	mov ebx, offset table

	find:
		.if (al == byte ptr [ebx])
			call near ptr [ebx + type table] ; call corresponding procedure, which is adjacent to al.
			call restartcalc
			ret
		.endif
		add ebx, type table * 2 ; move to next character-procedure pair in table.

	loop find

	ret
findcall endp

reqoperands proc uses esi edx eax ; ecx is an argument, indicating how many operands are needed.
	mov esi, 0

	operandstore: ; this loop reads and stores operands.
		mov edx, offset operandprompt
		call WriteString
		call ReadHex
		mov operands[esi * type operands], eax
		inc esi
		call Crlf

	loop operandstore

	ret
reqoperands endp

ander proc uses edx eax
	mov ecx, 2
	call reqoperands ; request two operands.

	mov edx, offset resultheader
	call WriteString
	mov eax, operands[0 * type operands]
	and eax, operands[1 * type operands]
	call WriteHex ; display result of and operation.
	call Crlf
	call Crlf

	ret
ander endp

order proc uses edx eax
	mov ecx, 2
	call reqoperands ; request two operands.

	mov edx, offset resultheader
	call WriteString
	mov eax, operands[0 * type operands]
	or eax, operands[1 * type operands]
	call WriteHex ; display result of and operation.
	call Crlf
	call Crlf

	ret
order endp

notter proc uses edx eax
	mov ecx, 1
	call reqoperands ; request one operands.

	mov edx, offset resultheader
	call WriteString
	mov eax, operands[0 * type operands]
	not eax
	call WriteHex ; display result of and operation.
	call Crlf
	call Crlf

	ret
notter endp

xorer proc uses edx eax
	mov ecx, 2
	call reqoperands ; request two operands.

	mov edx, offset resultheader
	call WriteString
	mov eax, operands[0 * type operands]
	xor eax, operands[1 * type operands]
	call WriteHex ; display result of and operation.
	call Crlf
	call Crlf

	ret
xorer endp

exitprogram proc uses edx
	mov edx, offset thankyou
	call WriteString
	call Crlf
	invoke ExitProcess, 0 ; to prevent default infinite looping of calculator.
exitprogram endp

main proc
	call menushow ; show menu.
	call reqinput ; request input.
	call findcall ; call corresponding procedure.

	invoke ExitProcess, 0
main endp

END main
