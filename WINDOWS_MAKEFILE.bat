@echo off
@mkdir "build"
@pause
@nasm -f elf "src\boot\multiboot.asm" -o multiboot.o
@move multiboot.o "build"
@nasm -f elf32 "src\boot\boot.asm" -o boot.o
@move boot.o "build"
@nasm -f elf32 "src\boot\lib.asm" -o asmlib.o
@move asmlib.o "build"
@gcc -m32 -c "src\kernel\kernel.c" -o kernelc.o
@move kernelc.o "build"
@copy link.ld "build"
@cd "build"
@ld -T link.ld -m i386pe -o kernel multiboot.o boot.o asmlib.o kernelc.o -build-id=none
@objcopy -O elf32-i386 kernel kernel.elf
@del link.ld
@pause
