char *USERNAMENONAMEINAMUROSSHELLSRING = "userok";

bool __shell_cmd_commandcmp(char *str, char *arg)
{
    __std__toLowerCase(str);
    if (__std__strstr(str, arg))
        return true;
    else
        return false;
}

void __shell_cmd_ini(char *str)
{
    if (__shell_cmd_commandcmp(str, "help"))
    {
        __std__printff("\n%s\n", SYSVER);
        __std__printc(">--------help list--------<", 112);
        __std__printf("\n= reboot  cls        time   =");
        __std__printf("\n= sleep   echo              =");
        __std__printf("\n= startx  videotype         =");
        __std__printf("\n= sysinfo setcur            =");
        __std__printf("\n= cpuid   help              =");
        __std__printf("\n= rand    beep              =");
        __std__printf("\n= music   shut              =");
        __std__printf("\n=============================");
    }
    else if (__shell_cmd_commandcmp(str, "test")) 
    {
        __std__newline();
        create_file("file1.txt", 10);
        create_file("file2.txt", 20);
        create_file("file3.txt", 30);

        write_file("file1.txt", "1234567890a");
        write_file("file2.txt", "This is a sample file.");
        write_file("file3.txt", "1234567890abcdefghijklmnopqrstuvwxyz");

        delete_file("file2.txt");

        read_file("file1.txt");
        read_file("file2.txt");
        read_file("file3.txt");
    }
    else if (__shell_cmd_commandcmp(str, "startx"))
    {
        entrypoint();
    }
    else if (__shell_cmd_commandcmp(str, "reboot"))
    {
        write_port(0x64, 0xFE);
    }
    else if (__shell_cmd_commandcmp(str, "shut"))
    {
        __asm__("outw %%ax, %%dx"
                :
                : "a"(0x2000), "d"(0x604)); // worked on QEMU
    }
    else if (__shell_cmd_commandcmp(str, "time"))
    {
        __cmos_read_rtc();
        __std__printff("\n%d/%d/%d %d:%d:%d", __cmos_day, __cmos_month, __cmos_year, __cmos_hour, __cmos_minute, __cmos_second);
    }
    else if (__shell_cmd_commandcmp(str, "videotype"))
    {
        if (get_bios_area_video_type() == VIDEO_TYPE_COLOUR)
            __std__printff("\nVideo Type: Colour 0x20");
        else if (get_bios_area_video_type() == VIDEO_TYPE_MONOCHROME)
            __std__printff("\nVideo Type: Monochrome 0x30");
        else
            __std__printff("\nVideo Type: None 0x00");
    }
    else if (__shell_cmd_commandcmp(str, "cls"))
    {
        __std__cls();
        __std__gotoxy(0, 0);
        __std__printc(HEADER, 112);
        __std__gotoxy(0, 0);
    }
    else if (__shell_cmd_commandcmp(str, "sleep"))
    {
        __std__sleep(10000);
    }
    else if (__shell_cmd_commandcmp(str, "sysinfo"))
    {
        __std__cls();
        __std__gotoxy(0, 0);
        __std__printc(HEADER, 112);
        __std__gotoxy(0, 0);
        __std__printff("\nusername: %s", USERNAMENONAMEINAMUROSSHELLSRING);
        __std__printf(SYSVER);
        MULTIBOOT_INFO *mboot_info;
        byte32i i;
        __std__printff("magici: 0x%x\n", magici);
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
    else if (__shell_cmd_commandcmp(str, "cpuid"))
    {
        cpuid_info(1);
    }
    else if (__shell_cmd_commandcmp(str, "beep"))
    {
        __driver_audio_beeps();
    }
    else if (__shell_cmd_commandcmp(str, "music"))
    {
        __std_music();
    }
    /*else if (__shell_cmd_commandcmp(str, "test"))
    {
        // mouse_init();

        // available modes: 320×200	640×400	640×480	800×500	800×600	896×672	1024×640	1024×768	1152×720	1280×1024	1360×768	1440×900	1600×1200
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
    }*/
    else if (__shell_cmd_commandcmp(str, "rand"))
    {
        __std__printff("\n%d", __std__rand());
    }
    /*else if (__shell_cmd_commandcmp(str, "execute"))
    {
        __compiler_start();
        __std__cls();
        __shell_offset();
    }*/
    else if (__shell_cmd_commandcmp(str, "echo "))
    {
        __std__newline();
        __std__printff(str + 5);
    }
    else if (__shell_cmd_commandcmp(str, "setcur "))
    {
        if (__std__strcmp(str + __std__strlen("setcur "), "false"))
        {
            write_port(COMMAND_PORT, 0x0A);
            write_port(DATA_PORT, 0x20);
        }
        else
        {
            write_port(COMMAND_PORT, 0x0A);
            write_port(DATA_PORT, (read_port(DATA_PORT) & 0xC0) | 0);
            write_port(COMMAND_PORT, 0x0A);
            write_port(DATA_PORT, (read_port(DATA_PORT) & 0xC0) | 14);
        }
    }
    else if (__shell_cmd_commandcmp(str, "ata"))
    {
        __vesa_vbe_print_available_modes();
    }
}

void __shell()
{
    for (;;) {
        useroffset = __std__strlen(USERNAMENONAMEINAMUROSSHELLSRING) + 1;
        char *str = "";
        if (__shell_pointer != 0)
            __std__printff("%s@%s", USERNAMENONAMEINAMUROSSHELLSRING, "> ");
        __shell_pointer++;

        __std__scanf(str);

        __shell_cmd_ini(str);

        __std__newline();
        if (__std__cursory > LINES - 1)
        {
            __std__gotoxy(0, 0);
            __std__cls();
            __std__printc(HEADER, 112);
            __std__gotoxy(0, 1);
        }
        
        __std__cursorPosition((COLUMNS_IN_LINE * __std__cursory) + __driver_kb_kbbcur + useroffset + 1);
    }
}