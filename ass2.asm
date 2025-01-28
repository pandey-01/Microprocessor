%macro io 4 
	mov rax,%1
	mov rdi,%2
	mov rsi,%3
	mov rdx,%4
	syscall
%endmacro
section .data
	msg1 db " Write an x86/64 ALP to accept a string and to display its length : ",0ah
	msg1len equ $-msg1
	msg2 db "Enter: ", 0ah
	msg2len equ $-msg2
	newline db 10
	len db 0
section .bss
	str1 resb 20

section .code
global _start
	_start:
	io 1,1,msg1,msg1len
	io 1,1,msg2,msg2len
	io 0,0,str1,20
	dec rax
	mov rbx,rax
	call hex_ascii64
	
	mov rsi,str1
	
	mov rax,60
	mov rdi,1
	syscall
	
	
hex_ascii64:
	mov rsi,str1
	mov rcx, 2
	
	next4:
		rol bl,4
		mov al,bl
		and al,0fh
		cmp al, 39h
		jbe add30h
		add al,7H
		add30h:
			add al,30h
			mov [rsi],al
			inc rsi
		loop next4
		io 1,1,str1,2
	ret
