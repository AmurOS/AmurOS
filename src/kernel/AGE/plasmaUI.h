#define BITMAP_SIZE 8

#define HEIGHTBORDERTOP 10
#define BASEBORDER 2
#define CORNERRADIUS 3

#define HEIGHTTASKBAR 10

typedef struct __plasmaUI_Button
{
    int x;
    int y;
    int width;
    int height;
    char color;
    char *str;
    int cornerRadius;
} __plasmaUI_Button;

// window form
typedef struct __plasmaUI_windowINI
{
    int positionX;
    int positionY;
    int height;
    int width;
    int cornRadius;
    bool fullScreen;
    char *title;
    char color:WHITE;
} __desktop_windowINI;

void __plasmaUI_CreateButton(__plasmaUI_Button button)
{
    __graphics_RectR(button.x, button.y, button.width, button.height, button.cornerRadius, button.color);
    if (__std__strlen(button.str) > 0)
        __plasmaUI_drawString(button.x + (button.width - (__std__strlen(button.str) * BITMAP_SIZE)) / 2, button.y + (button.height / 2 - 4), WHITE, button.str, __std__strlen(button.str));
}

void __plasmaUI_CreateWindow(__desktop_windowINI window)
{

    // title, control box
    window.cornRadius = CORNERRADIUS;
    __plasmaUI_Button close;
    close.cornerRadius = 1;
    close.color = RED;
    close.width = 10 - 3;
    close.height = HEIGHTBORDERTOP - 3;
    close.str = "x";

    if (window.fullScreen == true)
    {
        close.x = VGA_MAX_WIDTH - BASEBORDER * 6 - 1;
        close.y = 0 + 1;

        __graphics_RectR(0, 0, VGA_MAX_WIDTH - 1, VGA_MAX_HEIGHT - HEIGHTTASKBAR - 3, window.cornRadius, BLUE01);
        __plasmaUI_drawString(BASEBORDER, (HEIGHTBORDERTOP / 2 - 4), WHITE, window.title, __std__strlen(window.title));
        __plasmaUI_CreateButton(close);
        // window control in window
        // base
        __graphics_fillrect(BASEBORDER, HEIGHTBORDERTOP, (VGA_MAX_WIDTH - 1) - BASEBORDER * 2, VGA_MAX_HEIGHT - HEIGHTBORDERTOP - BASEBORDER - HEIGHTTASKBAR - 3, window.color);
    }
    else
    {
        close.x = window.positionX + window.width - BASEBORDER * 6;
        close.y = window.positionY + 1;
        __graphics_RectR(window.positionX, window.positionY, window.width, window.height, window.cornRadius, BLUE01);
        __plasmaUI_drawString(window.positionX + BASEBORDER, window.positionY + (HEIGHTBORDERTOP / 2 - 4), WHITE, window.title, __std__strlen(window.title));
        __plasmaUI_CreateButton(close);
        // window control in window
        // base
        __graphics_fillrect(window.positionX + BASEBORDER-1, window.positionY + HEIGHTBORDERTOP, window.width - BASEBORDER * 2 +2, window.height - HEIGHTBORDERTOP - BASEBORDER, window.color);
    }
}

void __plasmaUI_MessageBox(char *title, char *message)
{
    __desktop_windowINI window;
    window.cornRadius = 2;
    window.height = 50;
    window.width = 80;
    window.positionX = VGA_MAX_WIDTH / 2;
    window.positionY = VGA_MAX_HEIGHT / 2;
    window.title = title;
    window.color = WHITE;
    if (__std__strlen(message) * BITMAP_SIZE > window.width)
        window.width = __std__strlen(message) * BITMAP_SIZE + BITMAP_SIZE;
    __plasmaUI_CreateWindow(window);
    __plasmaUI_drawString(window.positionX + BASEBORDER + 2, window.positionY + HEIGHTBORDERTOP + 4, BLACK91, message, __std__strlen(message));

    //__driver_audio_tone(247, 0x10FFFFFF);
}

// draw string and font
byte bitmaps_0_9[10][BITMAP_SIZE] = {
    // 0
    {0b00111100,
     0b01111110,
     0b01100110,
     0b01101110,
     0b01110110,
     0b01100110,
     0b01111110,
     0b00111100},

    // 1
    {0b00011000,
     0b01111000,
     0b01111000,
     0b00011000,
     0b00011000,
     0b00011000,
     0b00111100,
     0b00111100},

    // 2
    {0b00111100,
     0b01111110,
     0b01001110,
     0b00011100,
     0b00111000,
     0b01110000,
     0b01111110,
     0b01111110},

    // 3
    {0b01111100,
     0b01111100,
     0b00001110,
     0b00111110,
     0b00111110,
     0b00001110,
     0b01111100,
     0b01111100},

    // 4
    {0b00001100,
     0b00011100,
     0b00111100,
     0b01101100,
     0b01111100,
     0b01111100,
     0b00001100,
     0b00001100},

    // 5
    {0b01111110,
     0b01111110,
     0b01100000,
     0b01111100,
     0b01111110,
     0b00001110,
     0b01111110,
     0b01111100},

    // 6
    {0b00011100,
     0b00111100,
     0b00110000,
     0b01111000,
     0b01111100,
     0b01100110,
     0b01101110,
     0b01111100},

    // 7
    {0b01111110,
     0b01111110,
     0b00000110,
     0b00001100,
     0b00001100,
     0b00011000,
     0b00110000,
     0b00110000},

    // 8
    {0b00111100,
     0b01111110,
     0b01100110,
     0b00111100,
     0b00111100,
     0b01100110,
     0b01111110,
     0b00111100},

    // 9
    {0b00111100,
     0b01111110,
     0b01100110,
     0b01111110,
     0b00111110,
     0b00000110,
     0b01111110,
     0b01111100},
};

byte bitmaps_A_Z[26][BITMAP_SIZE] = {
    // A
    {0b00011000,
     0b00111100,
     0b01100110,
     0b01100110,
     0b01111110,
     0b01111110,
     0b01100110,
     0b01100110},

    // B
    {0b01111100,
     0b01100110,
     0b01100110,
     0b01111110,
     0b01111110,
     0b01100110,
     0b01100110,
     0b01111100},

    // C
    {0b00111110,
     0b01111110,
     0b01100000,
     0b01100000,
     0b01100000,
     0b01100000,
     0b01111110,
     0b00111110},

    // D
    {0b01111100,
     0b01111110,
     0b01100110,
     0b01100110,
     0b01100110,
     0b01100110,
     0b01111110,
     0b01111100},

    // E
    {0b01111110,
     0b01111110,
     0b01100000,
     0b01111000,
     0b01111000,
     0b01100000,
     0b01111110,
     0b01111110},

    // F
    {0b01111110,
     0b01111110,
     0b01100000,
     0b01111100,
     0b01111100,
     0b01100000,
     0b01100000,
     0b01100000},

    // G
    {0b01111110,
     0b01111110,
     0b01100000,
     0b01100000,
     0b01101110,
     0b01100110,
     0b01111110,
     0b01111110},

    // H
    {0b01100110,
     0b01100110,
     0b01100110,
     0b01111110,
     0b01111110,
     0b01100110,
     0b01100110,
     0b01100110},

    // I
    {0b01111110,
     0b01111110,
     0b00011000,
     0b00011000,
     0b00011000,
     0b00011000,
     0b01111110,
     0b01111110},
    // J
    {0b00111110,
     0b00111110,
     0b00001100,
     0b00001100,
     0b01101100,
     0b01101100,
     0b01111100,
     0b01111100},

    // K
    {0b01100010,
     0b01100110,
     0b01101100,
     0b01111000,
     0b01110000,
     0b01111000,
     0b01101100,
     0b01100110},

    // L
    {0b01100000,
     0b01100000,
     0b01100000,
     0b01100000,
     0b01100000,
     0b01100000,
     0b01111110,
     0b01111110},

    // M
    {0b00100100,
     0b01111110,
     0b01111110,
     0b01111110,
     0b01100110,
     0b01100110,
     0b01100110,
     0b01100110},

    // N
    {0b01100110,
     0b01100110,
     0b01110110,
     0b01111110,
     0b01111110,
     0b01101110,
     0b01100110,
     0b01100110},

    // O
    {0b00111100,
     0b01111110,
     0b01100110,
     0b01100110,
     0b01100110,
     0b01100110,
     0b01111110,
     0b00111100},

    // P
    {0b01111100,
     0b01111110,
     0b01100110,
     0b01111110,
     0b01111100,
     0b01100000,
     0b01100000,
     0b01100000},

    // Q
    {0b00111100,
     0b01111110,
     0b01100110,
     0b01100110,
     0b01100110,
     0b01111110,
     0b00111000,
     0b00011100},

    // R
    {0b01111100,
     0b01111110,
     0b01100110,
     0b01111110,
     0b01111100,
     0b01111000,
     0b01101100,
     0b01100110},

    // S
    {0b00111110,
     0b01111110,
     0b01110010,
     0b00111000,
     0b00011100,
     0b01001110,
     0b01111110,
     0b01111100},

    // T
    {0b01111110,
     0b01111110,
     0b00011000,
     0b00011000,
     0b00011000,
     0b00011000,
     0b00011000,
     0b00011000},

    // U
    {0b01100110,
     0b01100110,
     0b01100110,
     0b01100110,
     0b01100110,
     0b01100110,
     0b01111110,
     0b00111100},

    // V
    {0b01100110,
     0b01100110,
     0b01100110,
     0b01100110,
     0b01100110,
     0b01100110,
     0b00111100,
     0b00011000},

    // W
    {0b01100110,
     0b01100110,
     0b01100110,
     0b01100110,
     0b01111110,
     0b00111100,
     0b01111110,
     0b01100110},

    // X
    {0b01100110,
     0b01100110,
     0b01100110,
     0b00111100,
     0b00111100,
     0b01100110,
     0b01100110,
     0b01100110},

    // Y
    {0b01100110,
     0b01100110,
     0b01100110,
     0b01100110,
     0b00111100,
     0b00011000,
     0b00011000,
     0b00011000},

    // Z
    {0b01111110,
     0b01111110,
     0b00001110,
     0b00011100,
     0b00111000,
     0b01110000,
     0b01111110,
     0b01111110}

};
// putpixels of 0-9 bits from right-to-left
void __plasmaUI_drawNumbitmaps(bit8 index, bit8 x, bit8 y, byte color)
{
    bit8 temp = 0, pix = 0;

    for (byte i = 0; i < BITMAP_SIZE; i++)
    {
        temp = x;
        x += BITMAP_SIZE;
        pix = bitmaps_0_9[index][i];
        while (pix > 0)
        {
            if (pix & 1)
            {
                __graphics_putpixel(x, y, color);
            }
            pix >>= 1;
            x--;
        }
        x = temp;
        y++;
    }
}

// putpixels of A-Z bits from right-to-left
void __plasmaUI_drawAlphabitmaps(bit8 index, bit8 x, bit8 y, byte color)
{
    bit8 temp = 0, pix = 0;

    for (byte i = 0; i < BITMAP_SIZE; i++)
    {
        temp = x;
        x += BITMAP_SIZE;
        pix = bitmaps_A_Z[index][i];
        while (pix > 0)
        {
            if (pix & 1)
            {
                __graphics_putpixel(x, y, color);
            }
            pix >>= 1;
            x--;
        }
        x = temp;
        y++;
    }
}

void __plasmaUI_drawChar(bit8 x, bit8 y, byte color, char ch)
{
    if (ch >= '0' && ch <= '9')
    {
        __plasmaUI_drawNumbitmaps(ch - '0', x, y, color);
    }
    else if (ch >= 'A' && ch <= 'Z')
    {
        __plasmaUI_drawAlphabitmaps((ch - '0') - 17, x, y, color);
    }
    else if (ch >= 'a' && ch <= 'z')
    {
        __plasmaUI_drawAlphabitmaps(((ch - 32) - '0') - 17, x, y, color);
    }
}

void __plasmaUI_drawString(bit8 x, bit8 y, byte color, char *str, int size)
{
    for (int i = 0; i < __std__strlen(str); i++)
    {
        __plasmaUI_drawChar(x, y, color, str[i]);
        x += BITMAP_SIZE;
    }
}