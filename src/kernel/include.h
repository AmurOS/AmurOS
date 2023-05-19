#include "lib.h"
char *__driver_kb_kbbuffer = "";
bool __driver_kb_endinp = false;
int __driver_kb_kbbcur = 0;
int __std__cursorx = 0;
int __std__cursory = 0;
int useroffset = 1;
//VESA SCREEN SIZE///////
#define WIDTHSCREEN 1440
#define HEIGHTSCREEN 900
/////////////////////////
void keyboard_handler(void);
void pixel(void);
char read_port(bit8 port);
void write_port(bit8 port, byte data);
void outw(unsigned short port, unsigned short value) {
asm volatile ("outw %%ax,%%dx": :"dN"(port), "a"(value));
}
void outb(unsigned short port, unsigned char value) {
asm volatile ("outb %%al,%%dx": :"dN"(port), "a"(value));
}
byte inb(bit8 port) {
    byte ret;
    asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

void load_idt(byte32 *idt_ptr);
void reboot(void);
void __std_music();
void __driver_audio_beeps();
void __std__sleep(byte32 ms);
//#include "multiboot.h"
#include "colors.h"
static void *__std__malloc(unsigned int sz);
void __std__putc(char ch);
void __std__cursorPosition(int pos);
void __std__delete();
#include "math.h"
#include "fpu.h"
#include "drivers/keyboard.h"
#include "drivers/sound.h"
#include "drivers/vga.h"
#include "std.h"
#include "dict.h"
#include "gdt.h"
#include "isr.h"
#include "idt.h"
#include "8259_pic.h"
#include "bios32.h"
//#include "multitasking.h"
#include "drivers/cmos_clock.h"
#include "promtssh.h"
#include "drivers/vesa.h"
#include "AGE/graphic/jerboa.h"
#include "drivers/fs.h"
//#include "drivers/ide.h"
#include "drivers/atapi.h"
#include "process.h"
#include "drivers/mouse.h"
#include "AGE/plasmaUI.h"
#include "AGE/window.h"
#include "AGE/desktop.h"
#include "AGE/shell.h"
#include "shell.h"
