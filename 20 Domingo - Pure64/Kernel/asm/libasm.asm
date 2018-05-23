GLOBAL cpuVendor
GLOBAL getSeconds
GLOBAL getMinutes
GLOBAL getHours
GLOBAL readKey

section .text

cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret

getSeconds:
	push rbp
	mov rbp, rsp
	mov rax, 0
	mov al, 0
	out 70h, al
	in al, 71h
	mov rsp, rbp
	pop rbp
	ret

getMinutes:
	push rbp
	mov rbp, rsp
	mov rax, 0
	cli
	mov al, 2
	out 70h, al
	in al, 71h
	sti
	mov rsp, rbp
	pop rbp
	ret

getHours:
	push rbp
	mov rbp, rsp
	mov rax, 0
	mov al, 4
	out 70h, al
	in al, 71h
	mov rsp, rbp
	pop rbp
	ret

readKey:
	mov rax,0
	in al, 60h
	ret
