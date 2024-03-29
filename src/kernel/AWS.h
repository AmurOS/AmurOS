__plasmaUI_Button startbtn;

byte *VidMem;
byte *BackBuffer;
//byte BackBuffer[ScreenHeight * Pitch];

unsigned short ScrW, ScrH;
unsigned char Bpp, PixelStride;
int Pitch;

void InitVideo(unsigned short ScreenWidth, unsigned short ScreenHeight, unsigned char BitsPerPixel)
{
    PixelStride = (BitsPerPixel | 7) >> 3;
    Pitch = ScreenWidth * PixelStride;

    VidMem = ((byte *)g_vbe_buffer);
    BackBuffer = ((byte *)(__std__malloc(ScreenHeight * Pitch)));

    ScrW = ScreenWidth;
    ScrH = ScreenHeight;
    Bpp = BitsPerPixel;
}

void SwapBuffers()
{
    __std__memcpy(VidMem, BackBuffer, ScrH * Pitch);
}

void desktop()
{

    for (;;)
    {
        zero();
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

// taskbar
void __desktop_taskbar()
{
    int widthtaskbar = (WIDTHSCREEN - 20);
    __vesa_RectR(RIGHT/2 - widthtaskbar/2, BOTTOM - HEIGHTTASKBAR - 10, widthtaskbar, HEIGHTTASKBAR, 8, MAINCOLOR);
}

// toolbar
void __desktop_toolbar()
{
    __vesa_Rect(LEFT, TOP, WIDTHSCREEN, HEIGHTTASKBAR - 30, MAINCOLOR);
    __cmos_read_rtc();
    char *hour, minute;
    __std__itoa(__cmos_hour, hour);
    __std__itoa(__cmos_minute, minute);
    __plasmaUI_drawString((WIDTHSCREEN / 2) - (__std__strlen(__std__concat(hour, __std__concat(":", minute))) * BITMAP_SIZE), ((HEIGHTTASKBAR - 30) / 2 - BITMAP_SIZE / 2), __vesa_VBE_RGB(255, 255, 255), __std__concat(hour, __std__concat(":", minute)), sizeof(__std__concat(hour, __std__concat(":", minute))));
}

void __desktop_splashscreen()
{
    char amuroslabel[] = "AMUROS";
    __plasmaUI_drawString(WIDTHSCREEN / 2 - (__std__strlen(amuroslabel) * BITMAP_SIZE), HEIGHTSCREEN / 2, __vesa_VBE_RGB(255, 255, 255), amuroslabel, sizeof(amuroslabel));
    __std__sleep(20000);
    __vesa_clear(__vesa_VBE_RGB(0, 0, 0));
}

void __desktop_offset()
{
    InitVideo(WIDTHSCREEN, HEIGHTSCREEN, g_vbe_modeinfoblock.BitsPerPixel / 8);
    // mouse_init();
    __desktop_splashscreen();
    desktop();
}

void Initilization()
{
    __desktop_windowINI win;
    win.title = "test";
    win.positionX = 41;
    win.positionY = 41;
    win.height = 200;
    win.width = 200;
    win.func = zero();
    __plasmaUI_CreateWindow(win);
    __desktop_taskbar();
    __desktop_toolbar();
    __plasmaUI_MessageBox("test msg", "hello derpy");
}

void zero()
{
    
}

void entrypoint() {
    gdt_init();
    idt_init();
    int ret = __vesa_init(WIDTHSCREEN, HEIGHTSCREEN, 32);

    if (ret < 0)
    {
        int i;
        __sh_error("failed to init vesa graphics");
        __std__printff("rebooting... wait ");
        for(i = 9;i>0;i--){
            __std__printff("%d",i);
            __std__sleep(10000);
            __std__delChar();
        }
        
        if(i==0)
            reboot();
    }
    else
    {
        int desktop_index = create_process(&__desktop_offset);
        run_process(desktop_index);
    }
}