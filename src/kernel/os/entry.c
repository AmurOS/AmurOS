
#include "mainlib.h"
#include "AmurGL.h"

process __desktop_process;

__plasmaUI_Button startbtn;

byte *VidMem;
byte *BackBuffer;
// byte BackBuffer[ScreenHeight * Pitch];
unsigned short ScrW, ScrH;
unsigned char Bpp, PixelStride;
int Pitch;

void __desktop_toolbar();
void __desktop_taskbar();

void InitVideo(unsigned short ScreenWidth, unsigned short ScreenHeight, unsigned char BitsPerPixel)
{
    PixelStride = (BitsPerPixel | 7) >> 3;
    Pitch = ScreenWidth * PixelStride;

    VidMem = ((byte *)g_vbe_buffer);
    BackBuffer = ((byte *)(malloc(ScreenHeight * Pitch)));

    ScrW = ScreenWidth;
    ScrH = ScreenHeight;
    Bpp = BitsPerPixel;
}

void SwapBuffers()
{
    __std__memcpy(VidMem, BackBuffer, ScrH * Pitch);
}

void __desktop_offset()
{
    InitVideo(WIDTHSCREEN, HEIGHTSCREEN, g_vbe_modeinfoblock.BitsPerPixel / 8);

    desktop();
}

void desktop()
{
    for (;;)
    {
        Initilization();
        __vesa_update(g_vbe_buffer);
        __std__memset(BackBuffer, 0, ScrH * Pitch);
#if 1
        while ((inportb(0x3DA) & 0x08))
            ;
        while (!(inportb(0x3DA) & 0x08))
            ;
#endif
        SwapBuffers();
    }
}

void dd(){
    __vesa_putpixel(4,4,__vesa_VBE_RGB(56,2,34));
}

void Initilization()
{
    asm("cli");
    int hz = 200;
    int divisor = 1193180 / hz;     /* Calculate our divisor */
    outportb(0x43, 0x36);           /* Set our command byte 0x36 */
    outportb(0x40, divisor & 0xFF); /* Set low byte of divisor */
    outportb(0x40, divisor >> 8);   /* Set high byte of divisor */
    asm("sti");
    //__vesa_clear(__vesa_VBE_RGB(34,34,34));
    __plasmaUI_ProgressBar bar;
    __plasmaUI_ListBox box;
    __desktop_windowINI win;
    // test
    win.title = "test";
    win.positionX = 41;
    win.positionY = 41;
    win.height = 200;
    win.width = 200;

    __vesa_putpixel(mouse_getx(), mouse_gety(), __vesa_VBE_RGB(255, 255, 255));

    __plasmaUI_CreateWindow(win);
    ProcessCreate(dd, "toolbar");
    __desktop_toolbar();
    __desktop_taskbar();
}

// taskbar
void __desktop_taskbar()
{
    int widthtaskbar = (WIDTHSCREEN);
    __vesa_Rect(widthtaskbar, BOTTOM - HEIGHTTASKBAR, widthtaskbar, HEIGHTTASKBAR, MAINCOLOR);
}

// toolbar
void __desktop_toolbar()
{
    int heighttoolbar = HEIGHTTASKBAR - 20;
    __vesa_Rect(LEFT, TOP, WIDTHSCREEN, heighttoolbar, MAINCOLOR);
    __cmos_read_rtc();
    char *hour, minute;
    __std__itoa(__cmos_hour, hour);
    __std__itoa(__cmos_minute, minute);
    __plasmaUI_drawString((WIDTHSCREEN / 2) - (__std__strlen(__std__concat(hour, __std__concat(":", minute))) * BITMAP_SIZE), ((heighttoolbar) / 2 - BITMAP_SIZE / 2), __vesa_VBE_RGB(255, 255, 255), __std__concat(hour, __std__concat(":", minute)), sizeof(__std__concat(hour, __std__concat(":", minute))));
}

void __desktop_init()
{
    __desktop_process.offset = *__desktop_offset;
}
void setup_fault_handlers() {
	int i;
	vector_t v;
	
	v.eip = (unsigned)intr_fault_divide;
	v.access_byte = 0x8E;
	setvect(&v, 0);

	v.eip = (unsigned)intr_fault_bound;
	v.access_byte = 0x8E;
	setvect(&v, 5);
	
	v.eip = (unsigned)intr_fault_opcode;
	v.access_byte = 0x8E;
	setvect(&v, 6);

	v.eip = (unsigned)intr_fault_tss;
	v.access_byte = 0x8E;
	setvect(&v, 0x0A);

	v.eip = (unsigned)intr_fault_segment;
	v.access_byte = 0x8E;
	setvect(&v, 0x0B);

	v.eip = (unsigned)intr_fault_stack;
	v.access_byte = 0x8E;
	setvect(&v, 0x0C);

	v.eip = (unsigned)intr_fault_gpf;
	v.access_byte = 0x8E;
	setvect(&v, 0x0D);

	v.eip = (unsigned)intr_fault_pf;
	v.access_byte = 0x8E;
	setvect(&v, 0x0E);
}


/**/
void entrypoint()
{
    

    gdt_init();
    idt_init();

    int ret = __vesa_init(WIDTHSCREEN, HEIGHTSCREEN, 32);

    map_all();
    enable_paging();
    mouse_init();
    init_multitasking();

    kinit();

    asm("sti");

    if (ret < 0)
    {
        int i;
        __sh_error("failed to init vesa graphics");
        __std__printff("rebooting... wait ");
        for (i = 4; i > 0; i--)
        {
            __std__printff("%d", i);
            __std__sleep(5000);
            __std__delChar();
        }

        if (i == 0)
            reboot();
    }
    else
    {
        __desktop_init();
        __desktop_offset();
    }
}