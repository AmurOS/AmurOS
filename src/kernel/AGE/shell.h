process __shellnew_process;
void __shellnew_offset()
{
    // available modes: 320×200	640×400	640×480	800×500	800×600	896×672	1024×640	1024×768	1152×720	1280×1024	1360×768	1440×900	1600×1200
    int ret = __vesa_init(1280, 1024, 32);
    if (ret < 0)
    {
        __std__printff("\nfailed to init vesa graphics");
    }
    else
    {
        gdt_init();
        idt_init();
        char *str = "";
        
        for (;;)
        {
            __std__scanf(str);
            __vesa_update(g_vbe_buffer);
            __plasmaUI_drawString(500, 500, __vesa_VBE_RGB(255, 255, 255), str, sizeof(str));
        }
    }
}

void __shellnew_init()
{
    __shellnew_process.offset = *__shellnew_offset;
}