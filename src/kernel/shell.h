process __shell_process;

void __shell_offset() {
	__std__cls();
    __driver_kb_idt_init();
    char *str = "";
    __std__printf(logo);
    __std__scanf(str);
    __std__color(31);
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
            __std__printc("\n\n>-----help list-----<", 112);
            __std__printf("\n= reboot  cls       =\n= sleep   videomode =\n= test    echo      =\n= sysver  setcursor =\n= beep              =\n=====================");
        }
        else if (__std__strcmp(str, "reboot") == true)
        {
            reboot();
        }
        else if (__std__strcmp(str, "cls"))
        {
        	__std__gotoxy(0, 0);
		    __std__cls();
		    __std__printc(HEADER, 112);
		    __std__printc(HEADER, 112);
		    __std__printc(HEADER, 112);
		    __std__printc(HEADER, 112);
		    __std__printc(HEADER, 112);
        }
        else if (__std__strcmp(str, "sleep") == true)
        {
            __std__sleep(0x10FFFFFF);
        }
        else if (__std__strcmp(str, "sysver"))
        {
            __std__printf(SYSVER);
        }
        else if (__std__strcmp(str, "videomode") == true)
        {
            videomode();
        }
        else if (__std__strcmp(str, "test") == true)
        {
            __std__printc("\nhello\nworld", 32);
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
            else{
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

void __shell_init() {
	__shell_process.offset = *__shell_offset;
}