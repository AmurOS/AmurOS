char* USERNAMENONAMEINAMUROSSHELLSRING = "frostysf";

process __boot_process;
process __shell_process;

char* __shell__user__setPointerNOUSER(char* string){
    if(string == ""){
        __std__printf("> ");
    }else{
        __std__printff("%s@%s",USERNAMENONAMEINAMUROSSHELLSRING,string);
        __std__newline();
        __std__printf("> ");
        __std__cursorPosition((COLUMNS_IN_LINE * __std__cursory) + __driver_kb_kbbcur + 1);
    }
}

void __shell_offset()
{

    char *str = "";
    if (__shell_pointer != 0)
        __shell__user__setPointerNOUSER("/user");
    __shell_pointer++;
    __std__scanf(str);
    if (__std__strcmp(str, "help") || __std__strcmp(str, "HELP"))
    {
        __std__printff("\nUse -soundhw pcspk in QEMU or choose pc speaker in emulator%s", SYSVER);
        __std__printc(">--------help list--------<", 112);
        __std__printf("\n= reboot  cls        help =");
        __std__printf("\n= sleep   videomode  shut =");
        __std__printf("\n= test    echo            =");
        __std__printf("\n= sysver  setcursor       =");
        __std__printf("\n= beep    music           =");
        __std__printf("\n= rand    wf              =");
        __std__printf("\n= rf      testfs          =");
        __std__printf("\n===========================");
    }
    else if (__std__strcmp(str, "reboot") || __std__strcmp(str, "REBOOT"))
    {
        write_port(0x64, 0xFE);
    }
    else if (__std__strcmp(str, "shut") || __std__strcmp(str, "SHUT"))
    {
        __asm__("outw %%ax, %%dx"
                :
                : "a"(0x2000), "d"(0x604)); // worked on QEMU
    }
    else if (__std__strcmp(str, "cls") || __std__strcmp(str, "CLS"))
    {
        __std__cls();
        __std__gotoxy(0, 0);
        __std__printc(HEADER, 112);
        __std__gotoxy(0, 0);
    }
    else if (__std__strcmp(str, "sleep") || __std__strcmp(str, "SLEEP"))
    {
        __std__sleep(10000);
    }
    else if (__std__strcmp(str, "sysver") || __std__strcmp(str, "SYSVER"))
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
            __std__printff("  framebuffer_addr: 0x%x\n", mboot_info->framebuffer_addr);
            __std__printff("  framebuffer_width: %d\n", mboot_info->framebuffer_width);
            __std__printff("  framebuffer_height: %d\n", mboot_info->framebuffer_height);
            __std__printff("  framebuffer_type: %d", mboot_info->framebuffer_type);
        }
        else
        {
            __std__printff("invalid multiboot magici number\n");
        }
    }
    else if (__std__strcmp(str, "beep") || __std__strcmp(str, "BEEP"))
    {
        __driver_audio_beeps();
    }
    else if (__std__strcmp(str, "music") || __std__strcmp(str, "MUSIC"))
    {
        __std_music();
    }
    else if (__std__strcmp(str, "videomode") || __std__strcmp(str, "VIDEOMODE"))
    {
        __desktop_init();
        __process_push(__desktop_process);
        __start_process(3);
    }
    else if (__std__strstr(str, "wf ") || __std__strstr(str, "WF "))
    {       
        __fs_writefile(__std__strtok(str, " ")[1], sizeof((char*)__std__strsplit(str," ")[2]) * sizeof(char*), (char*)__std__strsplit(str," ")[2]);
    }
    else if (__std__strstr(str, "rf ") || __std__strstr(str, "RF "))
    {
        __std__printff("\n%s", __fs_readfile(__std__strsplit(str, " ")[1]));
    }
    else if (__std__strcmp(str, "test") || __std__strcmp(str, "TEST"))
    {
        __std__printc("\nhello\nworld", 32);
    }
    else if (__std__strcmp(str, "rand") || __std__strcmp(str, "RAND"))
    {
        __std__printff("\n%d", __std__rand());
    }
    else if (__std__strcmp(str, "testfs") || __std__strcmp(str, "TESTFS"))
    {
        __fs_writefile("test", 4, "abcd");
        __std__printf("\n");
        __std__printf(__fs_readfile("test"));
        //__fs_readfile("test");
        __fs_writefile("test", 4, "efgk");
        __std__printf("\n");
        __std__printf(__fs_readfile("test"));
    }
    else if (__std__strstr(str, "echo ") || __std__strcmp(str, "ECHO"))
    {
        char *firstWord, *otherString;
        int WordLen = 0, otherStringLen = 0;

        char *space = __std__strstr(str, " ");
        WordLen = space - str;
        otherStringLen = __std__strlen(str) - WordLen - 1;

        __std__printff("\n%s", __std__strncpy(otherString, &space[1], otherStringLen + 1));
    }
    else if (__std__strstr(str, "setcursor ") || __std__strcmp(str, "SETCURSOR"))
    {
        char *firstWord, *otherString;
        int WordLen = 0, otherStringLen = 0;

        char *space = __std__strstr(str, " ");
        WordLen = space - str;
        otherStringLen = __std__strlen(str) - WordLen - 1;

        if (__std__strcmp(__std__strncpy(otherString, &space[1], otherStringLen + 1), "false"))
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

    __std__newline();
    if (__std__cursory > LINES - 1)
    {
        __std__gotoxy(0, 0);
        __std__cls();
        __std__printc(HEADER, 112);
        __std__gotoxy(0, 1);
    }
    // ini cursor //ини курсор))))))))))))))))))))))))))))))))))
    __std__cursorPosition((COLUMNS_IN_LINE * __std__cursory) + __driver_kb_kbbcur + 1);
}

void __shell_init()
{
    __shell_process.offset = *__shell_offset;
}

void __boot_offset()
{
    __driver_audio_beeps();
    __std__cls();
    __driver_kb_idt_init();
    __std__printf(logo);
    __std__sleep(1000);
    __std__color(7);
    __std__cls();
    __std__goto(0);
    __driver_kb_stopinp();
    __fs_initdisk();

    __std__gotoxy(0, 0);
    __std__cls();
    __std__printc(HEADER, 112);
    __std__gotoxy(0, 1);
    __std__printf("\nWelcome to AmurOS!\n");
    __std__printf("Type 'help' to view the list of commands\n");

    __shell_init();
    __process_push(__shell_process);
    __start_processes(2);
}

void __boot_init()
{
    __boot_process.offset = *__boot_offset;
}