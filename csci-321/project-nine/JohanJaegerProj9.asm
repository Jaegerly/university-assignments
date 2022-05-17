; header for assembler

title JohanJaegerProj9

.386
.model flat, stdcall
.stack 4096

ExitProcess proto, dwExitCode:dword

; imports

include Irvine32.inc

WriteString proto
Crlf proto
WriteDec proto
WaitMsg proto
ReadString proto
ReadChar proto
WriteChar proto

; data segment
sizestring = 31

.data
sourcestring byte sizestring dup(?)
targetstring byte sizestring dup(?)

sourceprompt byte "enter source string (string to search for): ", 0
targetprompt byte "enter target string (string to search in): ", 0
foundresultone byte "source string found at position ", 0
foundresulttwo byte " in target string (counting from 0).", 0
notfoundresult byte "source string could not be found in target string.", 0
continuemsg byte "do you want to do perform a new search? y/n (lowercase or uppercase): ", 0
errormsg byte "your input was not valid. please try again."

; code segment

.code

str_find proc uses esi edi,
	source: dword, ; offset for source string.
	target: dword ; offset for target string.

	local esistart: dword, ; esistart holds offset of first character in source string.
	solutionstart: dword ; solutionstart holds offset of first character in potential solution of target string.

	mov esi, source
	mov edi, target

	mov esistart, esi

	L1: ; executed every time a new substring in target string is considered.
		mov solutionstart, edi
	L2: ; compares characters in source string to those in target string.
		cld ; to ensure the upcoming decrements work.
		cmpsb

		jz L3
		jnz L4
	L3: ; if comparison of characters matches.
		cmp byte ptr [esi], 0 ; compare incremented location of source string to null character.
		jz L6
	L3A:
		cmp byte ptr [edi], 0 ; compare incremented location of target string to null character.
		jz L5

		jmp L2
	L4: ; else comparison of characters does not match.
		dec esi
		dec edi

		inc solutionstart
		mov edi, solutionstart ; check next possible substring
		cmp byte ptr [edi], 0 ; compare incremented location of target string to null character.
		jz L5

		cmp esi, esistart 
		.if !zero?
			mov esi, esistart ; if esi points to another character, only it must be readjusted.
		.endif
		jmp L1
	L5: ; if end of target string has been reached (i.e. no solution exists).
		cmp byte ptr [edi], 1 ; clear zero flag.
		jmp L7
	L6: ; if source string has been identified in target string.
		mov eax, solutionstart
	L7: 
		ret
str_find endp

read_str proc ; prompts user for source and target strings and stores them in memory.
	mov edx, offset sourceprompt
	call WriteString
	mov edx, offset sourcestring
	mov ecx, sizestring
	call ReadString

	mov edx, offset targetprompt
	call WriteString
	mov edx, offset targetstring
	call ReadString

	ret
read_str endp

solution_exists proc ; formats output. assumes solution to search exists.
	mov edx, offset foundresultone
	call WriteString

	sub eax, offset targetstring
	mov edx, eax
	call WriteDec

	mov edx, offset foundresulttwo
	call WriteString
		
	ret
solution_exists endp

continueprompt proc
	proceed:
		call Crlf
		call Crlf

		mov edx, offset continuemsg
		call WriteString

		call ReadChar
		call WriteChar

		call Crlf

		.if al == "y" || al == "Y"
			inc ecx
		.elseif al != "n" && al != "N"
			mov edx, offset errormsg
			call Crlf
			call WriteString
			jmp proceed
		.endif

	call Crlf

	ret
continueprompt endp

main proc
	mov ecx, 1

	interface:
		push ecx

		call read_str
		invoke str_find, addr sourcestring, addr targetstring

		jz L1
		jnz L2

		L1: ; if solution exists.
			call solution_exists
			jmp close

		L2: ; if solution does not exist.
			mov edx, offset notfoundresult
			call WriteString

		close:
			pop ecx
			call continueprompt

	loop interface

	; test: 0123ABAAABAAAABA789
	invoke ExitProcess, 0
main endp

END main
