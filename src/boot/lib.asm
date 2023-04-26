bits 32
section .text

global _keyboard_handler
global _read_port
global _write_port
global _load_idt
global _reboot
extern ___driver_kb_keyboard_handler_main
_read_port:
	mov edx, [esp + 4]
	in al, dx
	ret

_write_port:
	mov   edx, [esp + 4]    
	mov   al, [esp + 4 + 4]  
	out   dx, al  
	ret

_load_idt:
	mov edx, [esp + 4]
	lidt [edx]
	sti
	ret

_keyboard_handler:                 
	call    ___driver_kb_keyboard_handler_main
	iretd

_reboot:
WKC:
    xor al, al
    in al, 0x64
    test al, 0x02
    jnz WKC

    mov al, 0xFC
    out 0x64, al

section .bss
resb 8192; 8KB for stack
stack_space:
