#define C_MOV   0x01
#define C_SET   0x02
#define C_GET   0x05
#define C_STOR  0x06
#define C_JMP   0x07
#define C_JMPZ  0x08
#define C_GRT   0x09
#define C_LT    0x0a
#define C_EQ  0x0b
#define C_NEQ 0x0c
#define C_MGRT  0x0d
#define C_MLT   0x0e
#define C_MEQ   0x0f
#define C_MNEQ  0x10
#define C_ADD 0x11
#define C_SUB   0x12
#define C_MUL   0x13
#define C_DIV   0x14
#define C_MADD  0x15
#define C_MSUB  0x16
#define C_MMUL  0x17
#define C_MDIV  0x18
#define C_HLT   0x1b

unsigned char* hexstr_to_char(char* hexstr) {
    int len = sizeof((char *)hexstr) * sizeof(char *);
    if (len % 2 != 0)
        return (unsigned char*){0x00};
    int final_len = len / 2;
    unsigned char* chrs = (unsigned char*)__std__malloc((final_len+1) * sizeof(*chrs));
    for (int i=0, j=0; j<final_len; i+=2, j++)
        chrs[j] = (hexstr[i] % 32 + 9) % 25 * 16 + (hexstr[i+1] % 32 + 9) % 25;
    chrs[final_len] = '\0';
    return chrs;
}

void print_command(unsigned char *commands) {
    for (int i = 0; i < 8; i++) {
        switch (commands[i]) {
            case C_MOV:
                __std__printf("MOV\n");
                break;
            default:
                break;
        }
    }
}

int pointer = 0;
unsigned char *commands[65535];

void clear_list() {
    for (int i = 0; i < 65535; i++) {
        commands[i] = NULL;
    }
}

void __compiler_start() {
    __std__cls();
    __driver_kb_kbbcur = 0;
    useroffset = 0;
    __std__gotoxy(0, 0);
    __std__printf("AmurOS BVE 1.0\n\n");

    for (;;) {
        __std__printf("\n> ");
        char *command = "";
        __std__scanf(command);
        if (__std__strcmp(command, "add ")) {
            char *line = __std__strsplit(command, " ")[1];
            int len = (sizeof((char *)line) * sizeof(char *))/2;
            commands[pointer] = hexstr_to_char(line);
            //commands[pointer][len] = '\0';
            //__std__printf(hexstr_to_char(line));
            //__std__printf("\n\n");
            //__std__printf(commands[pointer]);
            pointer++;
            commands[pointer] = NULL;
        }
        else if (__std__strcmp(command, "run")) {
            //TODO: СДЕЛАТЬ ЭТО
            //__std__printf(commands[pointer-1]);
            __std__cls();
            __compiler_execute(commands[pointer-1]);
            __driver_kb_kbbcur = 0;
            __std__gotoxy(0, 0);
        }
        else if (__std__strcmp(command, "exit")) {
            break;
        }
        else if (__std__strcmp(command, "list")) {
            __std__newline();
            for (int i = 0; i < pointer; i++) {
                print_command(commands[i]);
                __std__newline();
            }
        }
        else if (__std__strcmp(command, "clear")) {
            clear_list();
        }
    }
}

void __compiler_execute(unsigned char *program) {
    //int program_length = 65535;//(sizeof((char *)program) * sizeof(char *)) / 2 + PROGMEMADDR + 1;
    //unsigned char *memory = (unsigned char *)__std__malloc(program_length);
    foreach(unsigned char *value, program) {
        switch (*value) {
            case C_MOV: {
                __std__printf("It's move command\n");
                break;
            }
        }
    }
}