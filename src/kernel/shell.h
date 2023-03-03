process __boot_process;
process __shell_process;

static long long __shell_pointer = 0;

void __shell_offset() {
    char *str = "";
    if (__shell_pointer != 0)
    	__std__printf("> ");
    __shell_pointer++;
    __std__scanf(str);
    if (__std__strcmp(str, "help") || __std__strcmp(str, "HELP"))
    {
        __std__printff("\nUse -soundhw pcspk in QEMU or choose pc speaker in emulator%s", SYSVER);
        __std__printc("\n>--------help list--------<", 112);
        __std__printf("\n= reboot  cls        music=");
        __std__printf("\n= sleep   videomode  help =");
        __std__printf("\n= test    echo            =");
        __std__printf("\n= sysver  setcursor       =");
        __std__printf("\n= beep    shutdown        =");
        __std__printf("\n= rand    wf              =");
        __std__printf("\n= rf      testfs          =");
        __std__printf("\n===========================");
    }
    else if (__std__strcmp(str, "reboot") || __std__strcmp(str, "REBOOT"))
    {
        reboot();
    }
    else if (__std__strcmp(str, "shutdown") || __std__strcmp(str, "SHUTDOWN"))
    {
        shutdown();
    }
    else if (__std__strcmp(str, "cls") || __std__strcmp(str, "CLS"))
    {
        __std__gotoxy(0, 0);
        __std__cls();
    }
    else if (__std__strcmp(str, "sleep") || __std__strcmp(str, "SLEEP"))
    {
        __std__sleep(0x10FFFFFF);
    }
    else if (__std__strcmp(str, "sysver") || __std__strcmp(str, "SYSVER"))
    {
        __std__printf(SYSVER);
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
        //__process_pop();
        __desktop_init();
        //__desktop_offset();
        __process_push(__desktop_process);
        __start_process(3);
        //__start_processes();
    }
    else if (__std__strstr(str, "wf ") || __std__strstr(str, "WF "))
    {
        char *Word, *String;
        int iWordLen = 0, StringLen = 0;

        char *firstWord, *otherString;
        int WordLen = 0, otherStringLen = 0;

        char *space = __std__strstr(str, " ");
        WordLen = space - str;
        otherStringLen = __std__strlen(str) - WordLen - 1;

        char *ispace = __std__strstr(__std__strncpy(otherString, &space[1], otherStringLen + 1), " ");
        iWordLen = ispace - __std__strncpy(otherString, &space[1], otherStringLen + 1);
        StringLen = __std__strlen(__std__strncpy(otherString, &space[1], otherStringLen + 1)) - iWordLen - 1;

        __fs_writefile(__std__strncpy(otherString, &space[1], otherStringLen + 1), __std__strlen(__std__strncpy(String, &ispace[1], StringLen + 1)), __std__strncpy(String, &ispace[1], StringLen + 1));
    }
    else if (__std__strstr(str, "rf ") || __std__strstr(str, "RF "))
    {
        char *firstWord, *otherString;
        int WordLen = 0, otherStringLen = 0;

        char *space = __std__strstr(str, " ");
        WordLen = space - str;
        otherStringLen = __std__strlen(str) - WordLen - 1;

        __std__newline();
        __std__printf(__fs_readfile(__std__strncpy(otherString, &space[1], otherStringLen + 1)));
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

        __std__newline();
        __std__printf(__std__strncpy(otherString, &space[1], otherStringLen + 1));
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

void __shell_init() {
    __shell_process.offset = *__shell_offset;
}

void __boot_offset() {
	__driver_audio_beeps();
    __std__cls();
    __driver_kb_idt_init();
    __std__printf(logo);
    __driver_kb_wait();
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
    create_descriptor(0, 0, 0);
    create_descriptor(0, 0x000FFFFF, (GDT_CODE_PL0));
    create_descriptor(0, 0x000FFFFF, (GDT_DATA_PL0));
    create_descriptor(0, 0x000FFFFF, (GDT_CODE_PL3));
    create_descriptor(0, 0x000FFFFF, (GDT_DATA_PL3));

    __shell_init();
    __process_push(__shell_process);
    __start_processes(2);
}

void __boot_init() {
    __boot_process.offset = *__boot_offset;
}