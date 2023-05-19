#define RIGHT WIDTHSCREEN
#define LEFT 0
#define TOP 0
#define BOTTOM HEIGHTSCREEN

#define HEIGHTTASKBAR 45
#define BITMAP_SIZE 8

#define HEIGHTBORDERTOP 15
#define BASEBORDER 5
#define CORNERRADIUS 5
#define MAINCOLOR __vesa_VBE_RGB(51,51,51)

#define MULTIBOOT_MAGIC_HEADER 0x1BADB002
#define MULTIBOOT_BOOTLOADER_MAGIC 0x2BADB002

#define NULL '\0'
//#define new(t) __std__malloc(sizeof(t))
#define bool int
#define true 1
#define false 0
#define bit8 unsigned short int
#define byte unsigned char
#define byte32 unsigned long
#define byte32i unsigned int
#define byte64 unsigned long long

#define LINES 25
#define COLUMNS_IN_LINE 80
#define BYTES_FOR_EACH_ELEMENT 2
#define SCREENSIZE BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE * LINES

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define IDT_SIZE 256
#define INTERRUPT_GATE 0x8e
#define KERNEL_CODE_SEGMENT_OFFSET 0x08

#define COMMAND_PORT 0x3D4
#define DATA_PORT 0x3D5
#define HIGH_BYTE_COMMAND 14
#define LOW_BYTE_COMMAND 15

#define ENTER_KEY_CODE 0x1C
#define BACKSPACE_KEY_CODE 0x0E
#define TAB_KEY_CODE 0x0F

#define WIDTHSCREEN 1440
#define HEIGHTSCREEN 900

extern void gdt_init();
extern void idt_init();

typedef struct process{
	int id;
	void (*offset)();
} process;

typedef struct __plasmaUI_Button
{
    int x;
    int y;
    int width;
    int height;
    int color;
    int background;
    char *str;
    int cornerRadius;
} __plasmaUI_Button;

typedef struct __plasmaUI_windowINI
{
    int positionX;
    int positionY;
    int height;
    int width;
    int cornRadius;
    char *title;
    int color;
    void *(func);
} __desktop_windowINI;

extern void __plasmaUI_CreateButton(__plasmaUI_Button button);
extern void __plasmaUI_drawNumbitmaps(int index, int x, int y, int color);
extern void __plasmaUI_drawAlphabitmaps(int index, int x, int y, int color);
extern void __plasmaUI_drawChar(int x, int y, int color, char ch);
extern void __plasmaUI_drawString(int x, int y, int color, char *str, int size);
extern void __plasmaUI_CreateWindow(__desktop_windowINI window);
extern void __plasmaUI_MessageBox(char *title, char *message);

#include "libs/cmos.h"
#include "libs/std.h"

typedef struct
{
    char VbeSignature[4];      /* VBE Signature */
    bit8 VbeVersion;           /* VBE version number */
    char *OEMStringPtr;        /* Pointer to OEM string */
    byte32i Capabilities;      /* Capabilities of video card */
    byte32i *VideoModePtr;     /* Pointer to supported modes */
    bit8 TotalMemory;          /* Number of 64kb memory blocks */
    bit8 OemSoftwareRev;       /* VBE implementation Software revision */
    byte32i OemVendorNamePtr;  /* Pointer to Vendor Name String */
    byte32i OemProductNamePtr; /* Pointer to Product Name String */
    byte32i OemProductRevPtr;  /* Pointer to Product Revision String */
    char reserved[222];        /* Pad to 256 byte block size */
    char OemData[256];         /* Data Area for OEM Strings */
} __attribute__((packed)) __vesa_VBE20_INFOBLOCK;

typedef struct
{
    // Mandatory information for all VBE revisions
    bit8 ModeAttributes;      /* Mode attributes */
    byte WinAAttributes;      /* Window A attributes */
    byte WinBAttributes;      /* Window B attributes */
    bit8 WinGranularity;      /* Window granularity in k */
    bit8 WinSize;             /* Window size in k */
    bit8 WinASegment;         /* Window A segment */
    bit8 WinBSegment;         /* Window B segment */
    void (*WinFuncPtr)(void); /* Pointer to window function */
    bit8 BytesPerScanLine;    /* Bytes per scanline */

    // Mandatory information for VBE 1.2 and above
    bit8 XResolution;        /* Horizontal resolution */
    bit8 YResolution;        /* Vertical resolution */
    byte XCharSize;          /* Character cell width */
    byte YCharSize;          /* Character cell height */
    byte NumberOfPlanes;     /* Number of memory planes */
    byte BitsPerPixel;       /* Bits per pixel */
    byte NumberOfBanks;      /* Number of CGA style banks */
    byte MemoryModel;        /* Memory model type */
    byte BankSize;           /* Size of CGA style banks */
    byte NumberOfImagePages; /* Number of images pages */
    byte Reserved;           /* Reserved */

    // Direct color fields
    byte RedMaskSize;         /* Size of direct color red mask */
    byte RedFieldPosition;    /* Bit posn of lsb of red mask */
    byte GreenMaskSize;       /* Size of direct color green mask */
    byte GreenFieldPosition;  /* Bit posn of lsb of green mask */
    byte BlueMaskSize;        /* Size of direct color blue mask */
    byte BlueFieldPosition;   /* Bit posn of lsb of blue mask */
    byte RsvdMaskSize;        /* Size of direct color res mask */
    byte RsvdFieldPosition;   /* Bit posn of lsb of res mask */
    byte DirectColorModeInfo; /* Direct color mode attributes */

    // Mandatory information for VBE 2.0 and above
    byte32i PhysBasePtr;        /* physical address for flat frame buffer */
    byte32i OffScreenMemOffset; /* pointer to start of off screen memory */
    bit8 OffScreenMemSize;      /* amount of off screen memory in 1k units */
    byte Reserved2[206];        /* remainder of ModeInfoBlock */
} __vesa_VBE20_MODEINFOBLOCK;

extern __vesa_VBE20_INFOBLOCK g_vbe_infoblock;
extern __vesa_VBE20_MODEINFOBLOCK g_vbe_modeinfoblock;
extern byte32i *g_vbe_buffer;

/*extern process __desktop_process;

extern void InitVideo(unsigned short ScreenWidth, unsigned short ScreenHeight, unsigned char BitsPerPixel);
extern void SwapBuffers();
extern void __desktop_offset();
extern void desktop();
extern void Initilization();

extern int i;
extern void fun();

extern void __desktop_taskbar();
extern void __desktop_toolbar();
extern void __desktop_init();
extern void __desktop_splashscreen();*/

#define RIGHT WIDTHSCREEN
#define LEFT 0
#define TOP 0
#define BOTTOM HEIGHTSCREEN
#define __vesa_VBE_RGB(r, g, b) __vesa_vbe_rgb(r, g, b)
#define HEIGHTTASKBAR 45