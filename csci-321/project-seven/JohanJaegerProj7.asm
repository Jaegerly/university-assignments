; header for assembler

title JohanJaegerProj7

.386
.model flat, stdcall
.stack 4096

ExitProcess proto, 
	dwExitCode:dword

; imports

include Irvine32.inc

WriteString proto
Crlf proto
ReadDec proto
WriteDec proto
ReadChar proto
WaitMsg proto

; data segment

.data
welcome byte "bitwise multiplication offset unsigned integers", 0

firstprompt byte "enter the multiplicand: ", 0
secondprompt byte "enter the multiplier: ", 0

result byte "the result is ", 0
question byte "do you want to perform another calculation? y/n (all lower case): ", 0

; code segment

.code

BitwiseMultiply proc uses ebx ecx edx esi
	; factors: eax and ebx
	; return: eax

	mov edx, 0 ; accumulator.

	mov ecx, 32
	mov esi, -1 ; counter for current power of two.

	multiplication:
		shr ebx, 1
		inc esi

		.if carry? ; every time a power of two in ebx is identified.
			push eax ; use a copy of eax inside if statement for shifts.
			push ecx ; temporarily use cl for shl.
			
			mov ecx, esi

			shl eax, cl
			add edx, eax ; add multiplication of eax and power of two to accumulator.

			pop ecx
			pop eax
		.endif

	loop multiplication

	mov eax, edx
	ret

BitwiseMultiply endp

main proc
	mov ecx, 1
	
	interface: 
		mov edx, offset welcome
		call WriteString

		call Crlf
		call Crlf

		mov edx, offset firstprompt
		call WriteString
		call ReadDec

		mov ebx, eax

		mov edx, offset secondprompt
		call WriteString
		call ReadDec

		call BitwiseMultiply

		call Crlf

		mov edx, offset result
		call WriteString
		call WriteDec

		call Crlf

		mov edx, offset question
		call WriteString
		call ReadChar

		.if al == "y"
			inc ecx
		.endif

		call Crlf
		call Crlf

	loop interface

	call WaitMsg

	invoke ExitProcess, 0
main endp

END main
