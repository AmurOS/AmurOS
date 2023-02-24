#include "lib.h"
char *__driver_kb_kbbuffer = "";
bool __driver_kb_endinp = false;
int __driver_kb_kbbcur = 0;
int __std__cursorx = 0;
int __std__cursory = 0;
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
void load_idt(byte32 *idt_ptr);
void reboot(void);
void videomode(void);
void shutdown(void);
void __std_music();
void __driver_audio_beeps();
void __std__sleep(byte32 __std__sleep_time);
#include "colors.h"
static void *__std__malloc(unsigned int sz);
void __std__putc(char ch);
void __std__cursorPosition(int pos);
void __std__delete();
#include "drivers/keyboard.h"
#include "drivers/sound.h"
#include "drivers/graphics.h"
#include "std.h"
#include "dict.h"
#include "drivers/fs.h"
#include "process.h"
#include "shell.h"
