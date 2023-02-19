#include "include.h"
///  NOT WORKING((((  /////
#define BRAND_QEMU 1
#define BRAND_VBOX 2

void __cpuid(uint32 type, uint32 *eax, uint32 *ebx, uint32 *ecx, uint32 *edx)
{
    asm volatile("cpuid"
                 : "=a"(*eax), "=b"(*ebx), "=c"(*ecx), "=d"(*edx)
                 : "0"(type)); // put the type into eax
}

void shutdown()
{
    int brand = cpuid_info(0);
    // QEMU
    if (brand == BRAND_QEMU)
        outports(0x604, 0x2000);
    else
        // VirtualBox
        outports(0x4004, 0x3400);
}
int cpuid_info(int print)
{
    uint32 brand[12];
    uint32 eax, ebx, ecx, edx;
    uint32 type;

    __std__memset(brand, 0, sizeof(brand));
    __cpuid(0x80000002, (uint32 *)brand + 0x0, (uint32 *)brand + 0x1, (uint32 *)brand + 0x2, (uint32 *)brand + 0x3);
    __cpuid(0x80000003, (uint32 *)brand + 0x4, (uint32 *)brand + 0x5, (uint32 *)brand + 0x6, (uint32 *)brand + 0x7);
    __cpuid(0x80000004, (uint32 *)brand + 0x8, (uint32 *)brand + 0x9, (uint32 *)brand + 0xa, (uint32 *)brand + 0xb);

    if (print)
    {
        __std__printf("Brand: %s\n");
        __std__printf((char*)brand);
        for (type = 0; type < 4; type++)
        {
            __cpuid(type, &eax, &ebx, &ecx, &edx);
            __std__printf("type:0x%x, eax:0x%x, ebx:0x%x, ecx:0x%x, edx:0x%x\n");
            __std__printf((char*)type);
            __std__printf((char*)eax);
            __std__printf((char*)ebx);
            __std__printf((char*)ecx);
            __std__printf((char*)edx);
            __std__newline();
        }
    }

    if (__std__strstr((char*)brand, "QEMU") != NULL)
        return BRAND_QEMU;

    return BRAND_VBOX;
}

//io ports

/**
 * read a byte from given port number
 */
uint8 inportb(uint16 port);

/**
 * write a given byte to given port number
 */
void outportb(uint16 port, uint8 val);

/**
 * read 2 bytes(short) from given port number
 */
uint16 inports(uint16 port);

/**
 * write given 2(short) bytes to given port number
 */
void outports(uint16 port, uint16 data);

/**
 * read 4 bytes(long) from given port number
 */
uint32 inportl(uint16 port);

/**
 * write given 4 bytes(long) to given port number
 */
void outportl(uint16 port, uint32 data);

uint8 inportb(uint16 port) {
    uint8 ret;
    asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

/**
 * write a given byte to given port number
 */
void outportb(uint16 port, uint8 val) {
    asm volatile("outb %1, %0" :: "dN"(port), "a"(val));
}

/**
 * read 2 bytes(short) from given port number
 */
uint16 inports(uint16 port) {
    uint16 rv;
    asm volatile ("inw %1, %0" : "=a" (rv) : "dN" (port));
    return rv;
}

/**
 * write given 2 bytes(short) to given port number
 */
void outports(uint16 port, uint16 data) {
    asm volatile ("outw %1, %0" : : "dN" (port), "a" (data));
}

/**
 * read 4 bytes(long) from given port number
 */
uint32 inportl(uint16 port) {
    uint32 rv;
    asm volatile ("inl %%dx, %%eax" : "=a" (rv) : "dN" (port));
    return rv;
}

/**
 * write given 4 bytes(long) to given port number
 */
void outportl(uint16 port, uint32 data) {
    asm volatile ("outl %%eax, %%dx" : : "dN" (port), "a" (data));
}