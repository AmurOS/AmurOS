int openapps = 0;
// window form
typedef struct __plasmaUI_windowINI
{
    int positionX;
    int positionY;
    int height;
    int width;
    int cornRadius;
    char *title;
    int color;
    void *(func);
} __desktop_windowINI;

void __plasmaUI_CreateWindow(__desktop_windowINI window)
{
    __desktop_windowINI win;
    win.func = window.func;
    openapps++;
    // title, control box
    window.cornRadius = CORNERRADIUS;
    window.color = __vesa_VBE_RGB(200, 200, 200);
    __plasmaUI_Button close;
    close.cornerRadius = 3;
    close.color = __vesa_VBE_RGB(255, 255, 255);
    close.background = __vesa_VBE_RGB(36,36,36);
    close.width = 20 - 2;
    close.height = HEIGHTBORDERTOP - 3;
    close.str = "x";

    close.x = window.positionX + window.width - BASEBORDER * 2 - 12;
    close.y = window.positionY + 1;

    __vesa_Rect(window.positionX, window.positionY, window.width, window.height, MAINCOLOR);
    __plasmaUI_drawString(window.positionX + window.width/2 - __std__strlen(window.title)*2 - close.width, window.positionY + (HEIGHTBORDERTOP / 2 - 4), __vesa_VBE_RGB(255, 255, 255), window.title, __std__strlen(window.title));
    __plasmaUI_CreateButton(close);
    // window control in window
    // base
    __vesa_Rect(window.positionX + BASEBORDER - 1, window.positionY + HEIGHTBORDERTOP+2, window.width - BASEBORDER * 2 + 2, window.height - HEIGHTBORDERTOP - BASEBORDER - 2, window.color);
}

void __plasmaUI_MessageBox(char *title, char *message)
{
    __desktop_windowINI window;
    window.cornRadius = 2;
    window.height = 200;
    window.width = 300;
    window.positionX = WIDTHSCREEN / 2 - window.width / 2;
    window.positionY = HEIGHTSCREEN / 2 - window.height / 2;
    window.title = title;
    window.color = __vesa_VBE_RGB(200, 200, 200);
    if (__std__strlen(message) * BITMAP_SIZE > window.width)
        window.width = __std__strlen(message) * BITMAP_SIZE + BITMAP_SIZE;
    __plasmaUI_CreateWindow(window);
    __plasmaUI_drawString(window.positionX + BASEBORDER + 2, window.positionY + HEIGHTBORDERTOP + 4, __vesa_VBE_RGB(0, 0, 0), message, __std__strlen(message));
}