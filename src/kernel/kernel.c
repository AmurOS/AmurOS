#include "include.h"

void kmain(void) {
	__std__cls();
	
	__driver_kb_idt_init();
	char* str = "";
	__std__scanf(str);
	__std__newline();
	__std__printf(str);
	__std__newline();
	
	__std__scanf(str);
	__std__newline();
	__std__printf(str);
	__std__newline();
}