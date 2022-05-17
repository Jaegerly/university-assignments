; header for assembler

title JohanJaegerProj4

.386
.model flat, stdcall
.stack 4096
ExitProcess PROTO, dwExitCode:DWORD

; data segment

.data
	source byte "This is the string that will be reversed", 0
	target byte sizeof source dup('#')

; code segment

.code
main PROC
	mov esi, offset source + (sizeof source - 2) ; pointer for source
	mov edi, offset target ; pointer for target

	mov ecx, sizeof source - 1 ; an iteration for every character in source

	L1:
		mov al, [esi] ; storing source character in temporary register
		mov [edi], al ; moving source character to target string

		dec esi
		inc edi

		loop L1

	mov byte ptr [edi], 0 ; add null character to target

	INVOKE ExitProcess, 0
main ENDP

END main
