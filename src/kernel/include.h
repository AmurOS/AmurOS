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
#include "multiboot.h"
#include "colors.h"
static void *__std__malloc(unsigned int sz);
void __std__putc(char ch);
void __std__cursorPosition(int pos);
void __std__delete();
//#include "math.h"
#include "fpu.h"
#include "drivers/keyboard.h"
#include "drivers/sound.h"
#include "std.h"
#include "gdt.h"
#include "8259_pic.h"
#include "promtssh.h"
#include "isr.h"
#include "idt.h"

#include "bios32.h"
#include "drivers/cmos_clock.h"

#include "drivers/vesa.h"
#include "drivers/AmurGL.h"
#include "process.h"
#include "AGE/plasmaUI.h"
#include "AGE/window.h"
#include "AWS.h"

#include "drivers/vfs.h"

int cpuid_info(int print);
void __cpuid(byte32i type, byte32i *eax, byte32i *ebx, byte32i *ecx, byte32i *edx);
#include "shell.h"
