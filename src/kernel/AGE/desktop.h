process __desktop_process;

#define RIGHT VGA_MAX_WIDTH
#define LEFT 0
#define TOP 0
#define BOTTOM VGA_MAX_HEIGHT
#define WIDTHSCREEN VGA_MAX_WIDTH
#define HEIGHTSCREEN VGA_MAX_HEIGHT

char getInput()
{
    byte status;
    char keycode;

    write_port(0x20, 0x20);

    status = read_port(KEYBOARD_STATUS_PORT);
    if (status & 0x01)
    {
        keycode = read_port(KEYBOARD_DATA_PORT);
        if (keycode < 0)
            return;
        else
            return keycode;
    }
    return 0;
}

void TerminalTest()
{
    __desktop_windowINI win;
    char amuroslabel[] = "esc";
    win.title = amuroslabel;
    win.positionX = 4;
    win.positionY = 4;
    win.width = 105;
    if (getInput() == ENTER_KEY_CODE)
    {
        win.positionY++;
    }
    __plasmaUI_CreateWindow(win);
}
__plasmaUI_Button startbtn;
// так барсик, я вижу что ты тут хотел обновлять экран так что не пытайся покаб язнаю эту проблему и
// даже делал двойную буферизацию оно помагало но мерцания все еще были

void __desktop_offset()
{
    __graphics_init();
    __graphics_clear(BLACK);
    // clear_screen(BLACK);
    char amuroslabel[] = "AMUROS";

    //__graphics_RectR(40, 40, 60, 40, 10, RED);
    __plasmaUI_drawString(WIDTHSCREEN / 2 - (__std__strlen(amuroslabel) * BITMAP_SIZE), HEIGHTSCREEN / 2, WHITE01, amuroslabel, sizeof(amuroslabel));
    __desktop_taskbar();
    __desktop_toolbar();
    __plasmaUI_MessageBox("test msg", "hello derpy");
    TerminalTest();
}

// taskbar
void __desktop_taskbar()
{
    startbtn.x = LEFT + 2;
    startbtn.y = BOTTOM - HEIGHTTASKBAR - 2;
    startbtn.width = 10;
    startbtn.height = HEIGHTTASKBAR;
    startbtn.cornerRadius = 0;
    startbtn.color = BLUE01;
    startbtn.str = "a";
    // draw
    __plasmaUI_CreateButton(startbtn);
    __graphics_RectR(LEFT + 16, BOTTOM - HEIGHTTASKBAR - 2, WIDTHSCREEN - 20, HEIGHTTASKBAR, 0, BLUE01);
}

// toolbar
void __desktop_toolbar()
{
    __graphics_RectR(LEFT, TOP, WIDTHSCREEN, HEIGHTTASKBAR - 4, 0, BLUE01);
}

void __desktop_init()
{
    __desktop_process.offset = *__desktop_offset;
}