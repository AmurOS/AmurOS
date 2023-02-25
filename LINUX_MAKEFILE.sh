#!/bin/bash
mkdir build
nasm -f elf src/boot/multiboot.asm -o multiboot.o
mv multiboot.o build
nasm -f elf32 src/boot/boot.asm -o boot.o
mv boot.o build
nasm -f elf32 src/boot/lib.asm -o asmlib.o
mv asmlib.o build
gcc -m32 -c src/kernel/kernel.c -o kernelc.o
mv kernelc.o build
cp link.ld build
cd build
ld -T link.ld -m i386pe -o kernel multiboot.o boot.o asmlib.o kernelc.o -build-id=none
objcopy -O elf32-i386 kernel kernel.elf
rm link.ld
cd ..
copy build/kernel.elf iso/boot
mkisofs -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -o amuros.iso iso