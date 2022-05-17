; header for assembler

title JohanJaegerProj8

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
tests dword 5, 20, 24, 18, 11, 7, 432, 226, 26, 13 
intro byte "greatest common divisor of (", 0
comma byte ", ", 0
parenthesis byte ") calculated by ", 0
looping byte "looping: ", 0
recursion byte "recursion: ", 0

; code segment

.code

SimpleGCD proc ; non-recursive implenetation of euclidean algorithm.
	
	; has two stack parameters: 
	;	1. unsigned doubleword integer
	;	2. unsigned doubleword integer

	; returns result in eax.

	push ebp
	mov ebp, esp

	push edx ; used for division. 

	mov edx, 0
	mov eax, [ebp + 8] ; store value of closest stack parameter.

	.repeat
		div dword ptr [ebp + 12] ; divide closest by farthest.
		mov eax, [ebp + 12] ; store farthest in eax.
		mov [ebp + 12], edx ; store remainder in farthest.
		mov edx, 0 ; clear edx for next division.
	.until dword ptr [ebp + 12] <= 0 ; stop iteration when remainder is <= 0.

	pop edx

	pop ebp
	ret 8

SimpleGCD endp

RecursiveGCD proc
	; has two stack parameters: 
	;	1. unsigned doubleword integer
	;	2. unsigned doubleword integer

	; returns result in eax.

	push ebp
	mov ebp, esp

	.if dword ptr [ebp + 8] == 0 ; terminating condition: when closest parameter == 0.
		mov eax, [ebp + 12]
		jmp finish
	.endif

	; setting up edx:eax for division.

	mov edx, 0
	mov eax, [ebp + 12]

	div dword ptr [ebp + 8]

	; pushing arguments on stack.

	push dword ptr [ebp + 8]
	push edx ; currently stores remainder of division.

	call RecursiveGCD

	finish:
		pop ebp
		ret 8

RecursiveGCD endp

main proc
	mov esi, offset tests
	mov ecx, 5 ; counter for outer loop.

	runtests: ; each iteration corresponds to a pair.
		push ecx
		mov ecx, 2 ; counter for inner loop.

		twice: ; each pair is run twice: once for looping procedure and once for recursive one.
			push dword ptr [esi]
			push dword ptr [esi + 4]
			
			; print headers

			mov edx, offset intro
			call WriteString

			mov eax, [esi]
			call WriteDec

			mov edx, offset comma
			call WriteString

			mov eax, [esi + 4]
			call WriteDec

			mov edx, offset parenthesis
			call WriteString

			; employ algorithms.

			.if ecx == 2
				mov edx, offset looping
				call WriteString
				
				call SimpleGCD
			.else
				mov edx, offset recursion
				call WriteString
				
				call RecursiveGCD
			.endif

			call WriteDec
			call Crlf

		loop twice

		call Crlf

		pop ecx ; restore counter for outer loop.
		add esi, 8 ; proceded to next test case.
	loop runtests

	invoke ExitProcess, 0
main endp

END main
