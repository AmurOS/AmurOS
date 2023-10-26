// sysinfo
#define SYSVER "\nSystem: AmurOS\nversion: 0.0.8\nTeam: AmurOS-Dev\n"
// header
#define HEADER "                                      Amur                                      "

unsigned long magici;
unsigned long addri;

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

#include "include.h"

void kmain(unsigned long magic, unsigned long addr)
{
    addri = addr;
    magici = magic;
    
    gdt_init();
    idt_init();
    bios32_init();
    fpu_enable();
    __std__cls();
    __driver_kb_idt_init();
    __std__printf(logo);
    __std__sleep(1000);
    __std__color(7);
    __std__cls();
    __std__goto(0);
    __driver_kb_stopinp();

    __std__gotoxy(0, 0);
    __std__cls();
    __std__printc(HEADER, 112);
    __std__gotoxy(0, 1);
    __std__printf("\nWelcome to AmurOS!\n");
    __std__printf("Type 'help' to view the list of commands\n");

    int shell_index = create_process(&__shell);
    run_process(shell_index);
}

void __cpuid(byte32i type, byte32i *eax, byte32i *ebx, byte32i *ecx, byte32i *edx) {
    asm volatile("cpuid"
                : "=a"(*eax), "=b"(*ebx), "=c"(*ecx), "=d"(*edx)
                : "0"(type));
}

int cpuid_info(int print) {
    byte32i brand[12];
    byte32i eax, ebx, ecx, edx;
    byte32i type;

    __std__memset(brand, 0, sizeof(brand));
    __cpuid(0x80000002, (byte32i *)brand+0x0, (byte32i *)brand+0x1, (byte32i *)brand+0x2, (byte32i *)brand+0x3);
    __cpuid(0x80000003, (byte32i *)brand+0x4, (byte32i *)brand+0x5, (byte32i *)brand+0x6, (byte32i *)brand+0x7);
    __cpuid(0x80000004, (byte32i *)brand+0x8, (byte32i *)brand+0x9, (byte32i *)brand+0xa, (byte32i *)brand+0xb);

    if (print) {
        __std__printff("\nBrand: %s\n", brand);
        for(type = 0; type < 4; type++) {
            __cpuid(type, &eax, &ebx, &ecx, &edx);
            __std__printff("type:0x%x, eax:0x%x, ebx:0x%x, ecx:0x%x, edx:0x%x\n", type, eax, ebx, ecx, edx);
        }
    }
}