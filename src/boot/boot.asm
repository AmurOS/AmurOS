bits 32

section .text

global start
extern _kmain

start:
	cli
	mov esp, stack_space
	call _kmain
	hlt

section .bss
resb 8192; 8KB for stack
stack_space:
