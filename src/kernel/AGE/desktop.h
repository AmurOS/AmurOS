process __desktop_process;

#define RIGHT VGA_MAX_WIDTH
#define LEFT 0
#define TOP 0
#define BOTTOM VGA_MAX_HEIGHT
#define WIDTHSCREEN VGA_MAX_WIDTH
#define HEIGHTSCREEN VGA_MAX_HEIGHT
__plasmaUI_Button startbtn;

void __desktop_offset()
{
    __graphics_init();
    __plasmaUI_drawString(WIDTHSCREEN / 2, HEIGHTSCREEN / 2, WHITE01, "AMUROS");
    __desktop_taskbar();
}

void __desktop_taskbar()
{
    int height = 10;
    startbtn.x = LEFT + 2;
    startbtn.y = BOTTOM - height - 2;
    startbtn.width = 10;
    startbtn.height = height;
    startbtn.color = BLUE01; 
    startbtn.str = " ";
    // draw
    __plasmaUI_CreateButton(startbtn);
    __graphics_fillrect(LEFT + 16, BOTTOM - height - 2, WIDTHSCREEN - 20, height, BLUE01);
}

void __desktop_init()
{
    __desktop_process.offset = *__desktop_offset;
}