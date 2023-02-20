section .multiboot_header
        ;multiboot spec
        align 4
        dd 0x1BADB002
        dd 0x00
        dd - (0x1BADB002 + 0x00)