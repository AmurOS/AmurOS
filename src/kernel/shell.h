process __shell_process;

void __shell_offset()
{
    _beep();
    __std__cls();
    __driver_kb_idt_init();
    char *str = "";
    __std__printf(logo);
    __std__sleep(0x10FFFFFF);
    __std__color(7);
    __std__cls();
    __std__goto(0);
    __driver_kb_stopinp();

    __std__gotoxy(0, 0);
    __std__cls();
    __std__printc(HEADER, 112);
    __std__gotoxy(0, 1);
    __std__printf("\nWelcome to AmurOS!\n");
    for (int i = 0;; i++)
    {
        if (i != 0)
            __std__printf("> ");
        __std__scanf(str);
        if (__std__strcmp(str, "help") == true)
        {
            __std__printf("\n\nUse -soundhw pcspk in QEMU or choose pc speaker in emulator");
            __std__printc("\n>-----help list-----<", 112);
            __std__printf("\n= reboot  cls       =\n= sleep   videomode =\n= test    echo      =\n= sysver  setcursor =\n= beep    shutdown  =\n=====================");
        }
        else if (__std__strcmp(str, "reboot") == true)
        {
            reboot();
        }
        else if (__std__strcmp(str, "shutdown") == true)
        {
            shutdown();
        }
        else if (__std__strcmp(str, "cls"))
        {
            __std__gotoxy(0, 0);
            __std__cls();
            __std__printc(HEADER, 112);
            __std__gotoxy(0, 1);
        }
        else if (__std__strcmp(str, "sleep") == true)
        {
            __std__sleep(0x10FFFFFF);
        }
        else if (__std__strcmp(str, "sysver"))
        {
            __std__printf(SYSVER);
        }
        else if (__std__strcmp(str, "beep"))
        {
            _beep();
        }
        else if (__std__strcmp(str, "music"))
        {
            music();
        }
        else if (__std__strcmp(str, "videomode") == true)
        {
            videomode();
        }
        else if (__std__strcmp(str, "test") == true)
        {
            __std__printc("\nhello\nworld\n", 32);
        }
        else if (__std__strstr(str, "echo "))
        {
            char *firstWord, *otherString;
            int WordLen = 0, otherStringLen = 0;

            char *space = __std__strstr(str, " ");
            WordLen = space - str;
            otherStringLen = __std__strlen(str) - WordLen - 1;

            __std__newline();
            __std__printf(__std__strncpy(otherString, &space[1], otherStringLen + 1));
        }
        else if (__std__strstr(str, "setcursor "))
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
    }
}

void __shell_init()
{
    __shell_process.offset = *__shell_offset;
}