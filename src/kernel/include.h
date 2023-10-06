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
unsigned long inl(unsigned short port) { unsigned long ret;
     __asm__ __volatile__("in%L0 (%1)" : "=a" (ret) : "d" (port)); return ret; }
void outl(unsigned short port, unsigned long value) {
     __asm__ __volatile__("out%L0 (%1)" : :"a" (value), "d" (port)); }   
unsigned short inw (unsigned short int port)
{
  unsigned short _v;

  __asm__ __volatile__ ("inw %w1,%0":"=a" (_v):"Nd" (port));
  return _v;
}
void outw(unsigned short port, unsigned short value)
{
    __asm__ __volatile__("outw %%ax, %%dx" : : "d" (port), "a" (value));
} 
void outportl(unsigned short port, unsigned long value) {
     __asm__ __volatile__("out%L0 (%1)" : :"a" (value), "d" (port)); }
unsigned short inportw (unsigned short int port)
{
  unsigned short _v;

  __asm__ __volatile__ ("inw %w1,%0":"=a" (_v):"Nd" (port));
  return _v;
}
void outportw(unsigned short port, unsigned short value)
{
    __asm__ __volatile__("outw %%ax, %%dx" : : "d" (port), "a" (value));
}
void outb(unsigned port, unsigned val)
{
	__asm__ __volatile__("outb %b0,%w1"
		:
		: "a"(val), "d"(port));
}
unsigned inb(unsigned port)
{
	unsigned ret_val;

	__asm__ __volatile__("inb %w1,%b0"
		: "=a"(ret_val)
		: "d"(port));
	return ret_val;
}
void outportb(unsigned port, unsigned val)
{
	__asm__ __volatile__("outb %b0,%w1"
		:
		: "a"(val), "d"(port));
}
unsigned inportb(unsigned port)
{
	unsigned ret_val;

	__asm__ __volatile__("inb %w1,%b0"
		: "=a"(ret_val)
		: "d"(port));
	return ret_val;
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
#include "physalloc.h"
#include "paging.h"
#include "8259_pic.h"
#include "bios32.h"
//#include "multitasking.h"
#include "drivers/cmos_clock.h"
#include "promtssh.h"
#include "drivers/vesa.h"
#include "interrupts.h"
#include "kalloc.h"
#include "task.h"
#include "drivers/fs.h"
#include "drivers/ide.h"
#include "drivers/atapi.h"
#include "fs/fat32.h"
#include "fs/file.h"
#include "process.h"
#include "drivers/mouse.h"
#include "AGE/plasmaUI.h"
#include "AGE/window.h"
//#include "AGE/desktop.h"
#include "AGE/shell.h"
#include "compiler.h"
#include "shell.h"
