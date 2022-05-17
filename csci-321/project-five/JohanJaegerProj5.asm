; header for assembler

title JohanJaegerProj5

.386
.model flat, stdcall
.stack 4096

ExitProcess PROTO, 
	dwExitCode:DWORD

; imports

include Irvine32.inc
RandomRange proto
WriteString proto
Crlf proto

; data segment
.data
	string byte 9 dup(?), 0

; code segment

.code
randstring proc uses eax ebx ecx
	; task: generates random string
	; parameters: 
		; 1. eax (desired length of string) 
		; 2. ebx (pointer to uninitialized string array)

	mov ecx, eax

	character:
		mov eax, 26
		call RandomRange
		add eax, 65 ; yields a number in the closed interval [65, 90]

		mov byte ptr [ebx], al ; append encoding to array
		inc ebx ; move one byte down the array

	loop character

	ret
randstring endp

main PROC
	mov eax, lengthof string - 1
	mov ebx, offset string
	mov ecx, 20

	tester: ; test randstring 20x
		call randstring

		; each time, output randstring
		mov edx, offset string
		call WriteString
		call Crlf

	loop tester

	INVOKE ExitProcess, 0
main ENDP

END main
