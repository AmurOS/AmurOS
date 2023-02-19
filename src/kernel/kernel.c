#include "include.h"
// header
char *header = "===================================Amur=========================================";
char *logo = "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
			 "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
			 "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@BPx<@@"
			 "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#dc<`    #@"
			 "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@BGi,         #@"
			 "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@gj^.             #@"
			 "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@8V^`                 #@"
			 "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@Rn!`                 `,<i@@"
			 "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#Rl~`               ,^lUR#@@@@@@"
			 "@#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#Si:             `??JOB@@@@@@@@@@@@@"
			 "@8^h#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#Dtr-            ,*nqQ@@@@@@@@@@@@@@@@@@@"
			 "@@@z,>XB@@@@@@@@@@@@@@@@@@@@@@@@@@Qqn*-          `!(J6B@@@@@@@@@@@@@@@@@@@@@@@@@"
			 "@@@@@qr`_rzdB@@@@@@@@@@@@@#QdX]^,         `?^}aR#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
			 "@@@@@@@@Rl=`  `-,=!!=:,-`        -:^|la6Q#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
			 "@@@@@@@@@@@@Qdhn]v(((vx}u2ePd$Q#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
			 "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
			 "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
			 "@@@@@@@@@@@@@@@@@@@@]`,BB@@@@@@#@@#@@@##@@@@@##@@@##@@@@@#@@@@@@@@@@@@@@@@@@@@@@"
			 "@@@@@@@@@@@@@@@@@@@n S#_-#@@@@V =Ux ~wn <@@@@  #@@  #@@@: ?VzW@@@@@@@@@@@@@@@@@@"
			 "@@@@@@@@@@@@@@@@@@? (nn}--8@@@V *@Q :@#``@@@@` D#E  #@@@: R@@@@@@@@@@@@@@@@@@@@@"
			 "@@@@@@@@@@@@@@@@@#eq@@@@QeZ@@@8eE@#eZ@@mm@@@@QX2eRhh@@@@Ze#@@@@@@@@@@@@@@@@@@@@@"
			 "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
			 "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
			 "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
			 "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";

void kmain(void)
{
	__std__cls();
	__driver_kb_idt_init();
	char *str = "";
	__std__printf(logo);
	__std__scanf(str);
	__std__color(31);
	__std__cls();
	__std__goto(0);
	__driver_kb_stopinp();
	__std__printf(header);
	__std__cursory++;
	__std__printf("Welcome to AmurOS!");;
	for (int i = 0;; i++)
	{
		if (i != 0)
			__std__printf(">");
		__std__scanf(str);
		if (__std__strcmp(str, "help") == true)
		{
			__std__printf("\n----help list----");
			__std__printf("\nreboot , cls\nsleep , videomode\ntest\n");
		}
		else if (__std__strcmp(str, "reboot") == true)
		{
			reboot();
		}
		else if (__std__strcmp(str, "cls"))
		{
			__std__cls();
			__std__cursory = 0;
			__std__printc(header, 31);
			__std__cursory = 1;
			__std__cursorx = 0;
		}
		else if (__std__strcmp(str, "sleep") == true)
		{
			__std__sleep(0x10FFFFFF);
		}
		else if (__std__strcmp(str, "videomode") == true)
		{
			videomode();
		}
		else if (__std__strcmp(str, "test") == true)
		{
			__std__printc("\nhello\nworld", 32);
		}
		__std__newline();
		if (__std__cursory > LINES - 1)
		{
			__std__cls();
			__std__cursory = 0;
			__std__printf(header);
			__std__cursory = 1;
			__std__cursorx = 0;
		}
	}
}