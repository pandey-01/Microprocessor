section .data
	msg db "Enter your name  : ",10
	msglen equ $-msg
	msg2 db "your name is : ",20h
	msg2len equ $-msg2

section .bss 
	nm resb 15

section .code
	global _start
	_start:
	mov rax, 1
	mov rdi, 1
	mov rsi, msg
	mov rdx, msglen
	syscall

mov rax, 0
mov rdi, 0
mov rsi, nm
mov rdx, 15
syscall
	
	mov rax, 1
	mov rdi, 1
	mov rsi, msg2
	mov rdx, msg2len
	syscall

mov rax, 0
mov rdi, 0
mov rsi, nm
mov rdx, 15
syscall
