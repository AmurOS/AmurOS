bits 32
section .text

global _keyboard_handler
global _read_port
global _write_port
global _load_idt
global _reboot
global _BIOS32_START ; start memory address
global _BIOS32_END  ; end memory address
global _bios32_gdt_ptr  ; GDT pointer
global _bios32_gdt_entries ; GDT array entries
global _bios32_idt_ptr ; IDT pointer
global _bios32_in_reg16_ptr ; IN REGISTERS16 
global _bios32_out_reg16_ptr ; OUT REGISTERS16
global _bios32_int_number_ptr ; bios interrupt number to be called
extern ___driver_kb_keyboard_handler_main

%define REBASE_ADDRESS(x)  (0x7c00 + ((x) - _BIOS32_START))
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

global _load_gdt

_load_gdt:
    mov eax, [esp + 4]  ; get gdt pointer
    lgdt [eax]          ; load gdt

    mov ax, 0x10    ; kernel data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    cli             ; clear interrupts
    mov	eax, cr0    ; set bit 0 in cr0 to enter protected mode
    or eax, 1
    mov	cr0, eax

    jmp 0x08:far_jump   ; jump to far with code data segment
far_jump:
    ret

global __load_idt

__load_idt:
    mov eax, [esp + 4]
    lidt [eax]
    ret

extern _isr_irq_handler

_irq_handler:
    pusha                 ; push all registers
    mov ax, ds
    push eax              ; save ds

    mov ax, 0x10          ; load kernel data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    push esp
    call _isr_irq_handler
    pop esp

    pop ebx                ; restore kernel data segment
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx

    popa                ; restore all registers
    add esp, 0x8        ; restore stack for erro no been pushed

    sti                 ; re-enable interrupts
    iret


%macro _IRQ 2
  global _irq_%1
  _irq_%1:
    cli
    push byte 0
    push byte %2
    jmp _irq_handler
%endmacro


_IRQ 0, 32
_IRQ 1, 33
_IRQ 2, 34
_IRQ 3, 35
_IRQ 4, 36
_IRQ 5, 37
_IRQ 6, 38
_IRQ 7, 39
_IRQ 8, 40
_IRQ 9, 41
_IRQ 10, 42
_IRQ 11, 43
_IRQ 12, 44
_IRQ 13, 45
_IRQ 14, 46
_IRQ 15, 47

    extern _isr_exception_handler
    global _exception_0
    global _exception_1
    global _exception_2
    global _exception_3
    global _exception_4
    global _exception_5
    global _exception_6
    global _exception_7
    global _exception_8
    global _exception_9
    global _exception_10
    global _exception_11
    global _exception_12
    global _exception_13
    global _exception_14
    global _exception_15
    global _exception_16
    global _exception_17
    global _exception_18
    global _exception_19
    global _exception_20
    global _exception_21
    global _exception_22
    global _exception_23
    global _exception_24
    global _exception_25
    global _exception_26
    global _exception_27
    global _exception_28
    global _exception_29
    global _exception_30
    global _exception_31
    global _exception_128


exception_handler:
    pusha                 ; push all registers
    mov ax, ds
    push eax              ; save ds
    
    mov ax, 0x10          ; load kernel data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call _isr_exception_handler

    pop ebx             ; restore kernel data segment
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx

    popa                ; restore all registers
    add esp, 0x8        ; restore stack for erro no been pushed

    sti                 ; re-enable interrupts
    iret


_exception_0:
    cli
    push byte 0     ; store default err code(0)
    push 0          ; push exception number index in IDT
    jmp exception_handler

_exception_1:
    cli
    push byte 0     ; store default err code(0)
    push 1          ; push exception number index in IDT
    jmp exception_handler

_exception_2:
    cli
    push byte 0     ; store default err code(0)
    push 2          ; push exception number index in IDT
    jmp exception_handler

_exception_3:
    cli
    push byte 0     ; store default err code(0)
    push 3          ; push exception number index in IDT
    jmp exception_handler

_exception_4:
    cli
    push byte 0     ; store default err code(0)
    push 4          ; push exception number index in IDT
    jmp exception_handler

_exception_5:
    cli
    push byte 0     ; store default err code(0)
    push 5          ; push exception number index in IDT
    jmp exception_handler

_exception_6:
    cli
    push byte 0     ; store default err code(0)
    push 6          ; push exception number index in IDT
    jmp exception_handler

_exception_7:
    cli
    push byte 0     ; store default err code(0)
    push 7          ; push exception number index in IDT
    jmp exception_handler

_exception_8:
    cli
    push 8          ; push exception number index in IDT
    jmp exception_handler

_exception_9:
    cli
    push byte 0     ; store default err code(0)
    push 9          ; push exception number index in IDT
    jmp exception_handler

_exception_10:
    cli
    push 10          ; push exception number index in IDT
    jmp exception_handler

_exception_11:
    cli
    push 11          ; push exception number index in IDT
    jmp exception_handler

_exception_12:
    cli
    push 12          ; push exception number index in IDT
    jmp exception_handler

_exception_13:
    cli
    push 13          ; push exception number index in IDT
    jmp exception_handler

_exception_14:
    cli
    push 14          ; push exception number index in IDT
    jmp exception_handler

_exception_15:
    cli
    push byte 0     ; store default err code(0)
    push 15          ; push exception number index in IDT
    jmp exception_handler

_exception_16:
    cli
    push byte 0     ; store default err code(0)
    push 16          ; push exception number index in IDT
    jmp exception_handler

_exception_17:
    cli
    push byte 0     ; store default err code(0)
    push 17          ; push exception number index in IDT
    jmp exception_handler

_exception_18:
    cli
    push byte 0     ; store default err code(0)
    push 18          ; push exception number index in IDT
    jmp exception_handler

_exception_19:
    cli
    push byte 0     ; store default err code(0)
    push 19          ; push exception number index in IDT
    jmp exception_handler

_exception_20:
    cli
    push byte 0     ; store default err code(0)
    push 20          ; push exception number index in IDT
    jmp exception_handler

_exception_21:
    cli
    push byte 0     ; store default err code(0)
    push 21          ; push exception number index in IDT
    jmp exception_handler

_exception_22:
    cli
    push byte 0     ; store default err code(0)
    push 22          ; push exception number index in IDT
    jmp exception_handler

_exception_23:
    cli
    push byte 0     ; store default err code(0)
    push 23          ; push exception number index in IDT
    jmp exception_handler

_exception_24:
    cli
    push byte 0     ; store default err code(0)
    push 24          ; push exception number index in IDT
    jmp exception_handler

_exception_25:
    cli
    push byte 0     ; store default err code(0)
    push 25          ; push exception number index in IDT
    jmp exception_handler

_exception_26:
    cli
    push byte 0     ; store default err code(0)
    push 26          ; push exception number index in IDT
    jmp exception_handler

_exception_27:
    cli
    push byte 0     ; store default err code(0)
    push 27          ; push exception number index in IDT
    jmp exception_handler

_exception_28:
    cli
    push byte 0     ; store default err code(0)
    push 28          ; push exception number index in IDT
    jmp exception_handler

_exception_29:
    cli
    push byte 0     ; store default err code(0)
    push 29          ; push exception number index in IDT
    jmp exception_handler

_exception_30:
    cli
    push byte 0     ; store default err code(0)
    push 30          ; push exception number index in IDT
    jmp exception_handler

_exception_31:
    cli
    push byte 0     ; store default err code(0)
    push 31          ; push exception number index in IDT
    jmp exception_handler

_exception_128:
    cli
    push byte 0     ; store default err code(0)
    push 128          ; push exception number index in IDT
    jmp exception_handler

; 32 bit protected mode
_BIOS32_START:use32
    pusha
    ; save current esp to edx
    mov edx, esp
    ; jumping to 16 bit protected mode
    ; disable interrupts
    cli
    ; clear cr3 by saving cr3 data in ebx register
    xor ecx, ecx
    mov ebx, cr3
    mov cr3, ecx
    ; load new empty GDT
    lgdt [REBASE_ADDRESS(_bios32_gdt_ptr)]
    ; load new empty IDT
    lidt [REBASE_ADDRESS(_bios32_idt_ptr)]
    ; jump to 16 bit protected mode
    jmp 0x30:REBASE_ADDRESS(__protected_mode_16)

; 16 bit protected mode
__protected_mode_16:use16
    ; jumping to 16 bit real mode
    mov ax, 0x38
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ; turn off protected mode
    ; set bit 0 to 0
    mov eax, cr0
    and al,  ~0x01
    mov cr0, eax
    jmp 0x0:REBASE_ADDRESS(__real_mode_16)

; 16 bit real mode
__real_mode_16:use16
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov sp, 0x8c00
    ; enable bios interrupts to call
    sti
    ; save current context, all general, segment registers, flags
    pusha
    mov cx, ss
    push cx
    mov cx, gs
    push cx
    mov cx, fs
    push cx
    mov cx, es
    push cx
    mov cx, ds
    push cx
    pushf
    ; get current stack pointer & save it to current_esp
    mov ax, sp
    mov edi, current_esp
    stosw
    ; load our custom registers context
    mov esp, REBASE_ADDRESS(_bios32_in_reg16_ptr)
    ; only use some general register from the given context
    popa
    ; set a new stack for bios interrupt
    mov sp, 0x9c00
    ; call immediate interrupt opcode to execute context
    db 0xCD

_bios32_int_number_ptr: ; will be bios interrupt number passed
    ; put the actual interrupt number here
    db 0x00
    ; get our output context here
    mov esp, REBASE_ADDRESS(_bios32_out_reg16_ptr)
    add sp, 28 ; restore stack used for calling our context
    ; save current context, all general, segment registers, flags
    pushf
    mov cx, ss
    push cx
    mov cx, gs
    push cx
    mov cx, fs
    push cx
    mov cx, es
    push cx
    mov cx, ds
    push cx
    pusha
    ; restore the current_esp to continue
    mov esi, current_esp
    lodsw
    mov sp, ax
    ; restore all current context, all general, segment registers, flags
    popf
    pop cx
    mov ds, cx
    pop cx
    mov es, cx
    pop cx
    mov fs, cx
    pop cx
    mov gs, cx
    pop cx
    mov ss, cx
    popa

    ; jumping to 32 bit protected mode
    ; set bit 0 in cr0 to 1
    mov eax, cr0
    inc eax
    mov cr0, eax
    jmp 0x08:REBASE_ADDRESS(__protected_mode_32)

; 32 bit protected mode
__protected_mode_32:use32
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ; restore cr3
    mov cr3, ebx
    ; restore esp
    mov esp, edx
    sti
    popa
    ret


__padding:
    db 0x0
    db 0x0
    db 0x0
_bios32_gdt_entries:
    ; 8 gdt entries
    resb 64
_bios32_gdt_ptr:
    dd 0x00000000
    dd 0x00000000
_bios32_idt_ptr:
    dd 0x00000000
    dd 0x00000000
_bios32_in_reg16_ptr:
    resw 14
_bios32_out_reg16_ptr:
    dd 0xaaaaaaaa
    dd 0xaaaaaaaa
    dd 0xaaaaaaaa
    dd 0xaaaaaaaa
    dd 0xaaaaaaaa
    dd 0xaaaaaaaa
    dd 0xaaaaaaaa
current_esp:
    dw 0x0000

_BIOS32_END:



;-------------------------------------------------
;	Interrupt Service Routinen (teils ausgeliehen)
;-------------------------------------------------

; I shouldn't have to do this!
%macro PUSHB 1
	db 6Ah
	db %1
%endmacro

	
; $$$ CONTEXT SWITCHING + SOFTWARE MULTITASKING $$$
global _contextswitch
_contextswitch:
	pusha	; 32 byte push
	mov	eax, [esp+36]
	mov	[eax], esp
	mov	esp, [esp+40] ; $$$
	popa
	ret
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; name:			getvect
; action:		reads interrupt vector
; in:			[EBP + 12] = vector number
; out:			vector stored at address given by [EBP + 8]
; modifies:		EAX, EDX
; minimum CPU:		'386+
; notes:		C prototype:
;			typedef struct
;			{	unsigned access_byte, eip; } vector_t;
;			getvect(vector_t *v, unsigned vect_num);
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

global _getvect
_getvect:


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; name:			setvect
; action:		writes interrupt vector
; in:			[EBP + 12] = vector number,
;			vector stored at address given by [EBP + 8]
; out:			(nothing)
; modifies:		EAX, EDX
; minimum CPU:		'386+
; notes:		C prototype:
;			typedef struct
;			{	unsigned access_byte, eip; } vector_t;
;			getvect(vector_t *v, unsigned vect_num);
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

global _setvect
_setvect:

section .bss
resb 8192; 8KB for stack
stack_space:
