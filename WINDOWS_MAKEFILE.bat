@echo off
@mkdir "build"
@pause
@nasm -f elf32 "src\boot\boot.asm" -o boot.o
@move boot.o "build"
@nasm -f elf32 "src\boot\lib.asm" -o asmlib.o
@move asmlib.o "build"
@gcc -m32 -c "src\kernel\kernel.c" -o kernelc.o
@move kernelc.o "build"
@gcc -m32 -c "src\kernel\os\entry.c" -o os.o
@move os.o "build"
@copy link.ld "build"
@cd "build"
@ld -T link.ld -m i386pe -o kernel boot.o asmlib.o kernelc.o os.o -build-id=none
@objcopy -O elf32-i386 kernel kernel.elf
@del link.ld
@cd ".."
@cd
@copy "build\kernel.elf" "iso\boot"
@mkisofs -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -o amuros.iso iso
@pause

