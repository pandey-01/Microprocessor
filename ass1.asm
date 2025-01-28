;Write x86/64 ALP to accept five hexadecimals numbers from user and store them in an array and display the accepted numbers
;Name : Anish Kumar Pandey
;DOP : 21/01/2025

%macro io 4 
	mov rax,%1
	mov rdi,%2
	mov rsi,%3
	mov rdx,%4
	syscall
%endmacro

section .data
	msg1 db "x86/64 ALP to accept five hexadecimals numbers from user and store them in an array and display the accepted numbers: ",20H
	msg1len equ $-msg1
	msg2 db "Enter: ", 20H
	msg2len equ $-msg2
	newline db 10
section .bss
	ascii_num resb 17
	hexnum resq 5

section .code
global _start
	_start:
	io 1,1,msg1,msg1len
	io 1,1,msg2,msg2len
	mov rsi, hexnum
	mov rcx, 5
	
	next1:
	push rcx 
	push rsi
	io 0,0,ascii_num,17
	
	call ascii_hex64 
	pop rsi
	pop rcx
	
	mov [rsi],rbx
	add rsi,8
	loop next1
	
	io 1,1,msg1,msg1len
	mov rsi, hexnum
	mov rcx, 5
	
	next2:
	mov rbx,[rsi]
	push rcx
	push rsi
	call hex_ascii64
	pop rsi
	pop rcx
	add rsi,8
	loop next2
	
	mov rax,60
	mov rdi, 0
	syscall
	
ascii_hex64:
	mov rsi,ascii_num
	mov rcx,16
	mov rbx,0
	next3:
		rol ebx, 4
		mov al, [rsi]
		cmp al, 39h
		jbe sub30h
		sub al,7h
		sub30h:
			sub al,30H
			add bl,al
			inc rsi
	loop next3
	ret
		
hex_ascii64:
	mov rsi,ascii_num
	mov rcx, 16
	
	next4:
		rol rbx,4
		mov al,bl
		and al,0Fh
		cmp al, 39h
		jbe add30h
		add al,7h
		add30h:
			add al,30h
			mov [rsi],al
			inc rsi
		loop next4
		io 1,1,ascii_num, 16
	ret
	
	
