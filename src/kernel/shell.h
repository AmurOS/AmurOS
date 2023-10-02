char *USERNAMENONAMEINAMUROSSHELLSTRING = "derpy";

extern void entrypoint();

process __boot_process;
process __shell_process;
// отстой

void __shell_offset()
{
    useroffset = __std__strlen(USERNAMENONAMEINAMUROSSHELLSTRING) + 1;
    char *str = "";
    if (__shell_pointer != 0)
        __std__printff("%s@%s", USERNAMENONAMEINAMUROSSHELLSTRING, "> ");
    __shell_pointer++;
    __std__scanf(str);

    __shell_cmd_ini(str);

    __std__newline();
    // ini cursor //ини курсор))))))))))))))))))))))))))))))))))
    __std__cursorPosition((COLUMNS_IN_LINE * __std__cursory) + __driver_kb_kbbcur + useroffset + 1);
}

void __shell_init()
{
    __shell_process.offset = *__shell_offset;
}

void __boot_offset()
{
    gdt_init();
    idt_init();
    bios32_init();
    fpu_enable();

    //__std__cls();
    __driver_kb_idt_init();
    //__std__printff(logo);
    //__std__sleep(1000);
    //__std__color(7);
    //__std__cls();
    __std__goto(0);
    __driver_kb_stopinp();
    __fs_initdisk();

    __std__cls();
    __std__printff("Welcome to AmurOS!\n");
    __std__printff("Type 'help' to view the list of commands");

    __shell_init();
    __process_push(__shell_process);
    __start_processes(2);
}

void __boot_init()
{
    __boot_process.offset = *__boot_offset;
}

void __shell_cmd_ini(char *str)
{
    if (__std__strcmp(str, "help"))
    {
        __std__printff("%s", SYSVER);
        __std__printff("\n reboot  cls        help");
        __std__printff("\n sleep   run        shutdown");
        __std__printff("\n time                   ");
        __std__printff("\n sysinfo setcur     echo");
        __std__printff("\n cpuid   music      beep");
        __std__printff("\n rand    mkfile         ");
        __std__printff("\n rdfile  testfs         ");
    }
    else if (__std__strcmp(str, "run"))
    {
        entrypoint();
    }
    else if (__std__strcmp(str, "reboot"))
    {
        write_port(0x64, 0xFE);
    }
    else if (__std__strcmp(str, "shutdown"))
    {
        __asm__("outw %%ax, %%dx"
                :
                : "a"(0x2000), "d"(0x604)); // worked on QEMU
    }
    else if (__std__strcmp(str, "time"))
    {
        __cmos_read_rtc();
        __std__printff("\n%d/%d/%d %d:%d:%d", __cmos_day, __cmos_month, __cmos_year, __cmos_hour, __cmos_minute, __cmos_second);
    }
    else if (__std__strcmp(str, "videotype"))
    {
        if (get_bios_area_video_type() == VIDEO_TYPE_COLOUR)
            __std__printff("\nVideo Type: Colour 0x20");
        else if (get_bios_area_video_type() == VIDEO_TYPE_MONOCHROME)
            __std__printff("\nVideo Type: Monochrome 0x30");
        else
            __std__printff("\nVideo Type: None 0x00");
    }
    else if (__std__strcmp(str, "cls"))
    { 
        __std__cls();
        __std__gotoxy(0, -1);
    }
    else if (__std__strcmp(str, "sleep"))
    {
        __std__sleep(10000);
    }
    else if (__std__strcmp(str, "sysinfo"))
    {
        __std__printff("\nusername: %s", USERNAMENONAMEINAMUROSSHELLSTRING);
        __std__printff(SYSVER);
        MULTIBOOT_INFO *mboot_info;
        byte32i i;
        __std__printff("\nmagici: 0x%x\n", magici);
        if (magici == MULTIBOOT_BOOTLOADER_MAGIC)
        {
            mboot_info = (MULTIBOOT_INFO *)addri;
            __std__printff("  flags: 0x%x\n", mboot_info->flags);
            __std__printff("  mem_low: 0x%x KB\n", mboot_info->mem_low);
            __std__printff("  mem_high: 0x%x KB\n", mboot_info->mem_high);
            __std__printff("  boot_device: 0x%x\n", mboot_info->boot_device);
            __std__printff("  cmdline: %s\n", (char *)mboot_info->cmdline);
            __std__printff("  modules_count: %d\n", mboot_info->modules_count);
            __std__printff("  modules_addr: 0x%x\n", mboot_info->modules_addr);
            __std__printff("  mmap_length: %d\n", mboot_info->mmap_length);
            __std__printff("  mmap_addr: 0x%x\n", mboot_info->mmap_addr);
            __std__printff("  memory map:-\n");
            for (i = 0; i < mboot_info->mmap_length; i += sizeof(MULTIBOOT_MEMORY_MAP))
            {
                MULTIBOOT_MEMORY_MAP *mmap = (MULTIBOOT_MEMORY_MAP *)(mboot_info->mmap_addr + i);
                __std__printff("    size: %d, addr: 0x%x%x, len: %d%d, type: %d\n",
                               mmap->size, mmap->addr_low, mmap->addr_high, mmap->len_low, mmap->len_high, mmap->type);
            }
            __std__printff("  boot_loader_name: %s\n", (char *)mboot_info->boot_loader_name);
            __std__printff("  vbe_control_info: 0x%x\n", mboot_info->vbe_control_info);
            __std__printff("  vbe_mode_info: 0x%x\n", mboot_info->vbe_mode_info);
            __std__printff("  apm_table:%d\n", mboot_info->apm_table);
            __std__printff("  framebuffer_addr: 0x%x\n", mboot_info->framebuffer_addr);
            __std__printff("  framebuffer_width: %d\n", mboot_info->framebuffer_width);
            __std__printff("  framebuffer_height: %d\n", mboot_info->framebuffer_height);
            __std__printff("  framebuffer_type: %d", mboot_info->framebuffer_type);
            if (get_bios_area_video_type() == VIDEO_TYPE_COLOUR)
                __std__printff("\nVideo Type: Colour 0x20");
            else if (get_bios_area_video_type() == VIDEO_TYPE_MONOCHROME)
                __std__printff("\nVideo Type: Monochrome 0x30");
            else
                __std__printff("\nVideo Type: None 0x00");
        }
        else
        {
            __sh_error("invalid multiboot magici number\n");
        }
    }
    else if (__std__strcmp(str, "cpuid"))
    {
        cpuid_info(1);
    }
    else if (__std__strcmp(str, "beep"))
    {
        __driver_audio_beeps();
    }
    else if (__std__strcmp(str, "music"))
    {
        __std_music();
    }
    else if (__std__strcmp(str, "mkfile "))
    {
        __std__printff("\n%s", "Enter file content: ");
        useroffset = __std__strlen("Enter file content: ");
        char *a = __std__scanf("");

        __fs_writefile("test", sizeof((char *)a) * sizeof(char *), a);
        useroffset = __std__strlen(USERNAMENONAMEINAMUROSSHELLSTRING) + 1;
    }
    else if (__std__strcmp(str, "rdfile "))
    {
        __std__printff("\n%s", __fs_readfile(__std__strsplit(str, " ")[1]));
    }
    else if (__std__strcmp(str, "test"))
    {
        // mouse_init();

        // available modes: 320×200	640×400	640×480	800×500	800×600	896×672	1024×640	1024×768	1152×720	1280×1024	1360×768	1440×900	1600×1200
        int ret = __vesa_init(WIDTHSCREEN, HEIGHTSCREEN, 32);
        if (ret < 0)
        {
            int i;
            __sh_error("failed to init vesa graphics");
            __std__printff("rebooting... wait ");
            for (i = 9; i > 0; i--)
            {
                __std__printff("%d", i);
                __std__sleep(10000);
                __std__delChar();
            }

            if (i == 0)
                reboot();
        }
        else
        {
            byte32i x = 0;
            for (byte32i c = 0; c < 267; c++)
            {
                for (byte32i i = 0; i < 1024; i++)
                {
                    __vesa_putpixel(x, i, __vesa_VBE_RGB(c % 255, 0, 0));
                }
                x++;
            }
            for (byte32i c = 0; c < 267; c++)
            {
                for (byte32i i = 0; i < 1024; i++)
                {
                    __vesa_putpixel(x, i, __vesa_VBE_RGB(0, c % 255, 0));
                }
                x++;
            }
            for (byte32i c = 0; c < 267; c++)
            {
                for (byte32i i = 0; i < 1024; i++)
                {
                    __vesa_putpixel(x, i, __vesa_VBE_RGB(0, 0, c % 255));
                }
                x++;
            }
        }
    }
    else if (__std__strcmp(str, "rand"))
    {
        __std__printff("\n%d", __std__rand());
    }
    else if (__std__strcmp(str, "execute"))
    {
        __compiler_start();
        __std__cls();
        __shell_offset();
    }
    else if (__std__strcmp(str, "testfs1"))
    {
        __fs_writefile("test", 4, "abcd");
        __fs_writefile("test", 4, "efgk");
    }
    else if (__std__strcmp(str, "testfs2"))
    {
        __std__printff("\n");
        __std__printff(__fs_readfile("test"));
        __std__printff("\n");
        __std__printff(__fs_readfile("test"));
    }
    else if (__std__strstr(str, "echo "))
    {
        __std__newline();
        __std__printff(str + 5);
    }
    else if (__std__strcmp(str, "atapi"))
    {
        __std__printff(fopen("/", "0"));
    }
}
