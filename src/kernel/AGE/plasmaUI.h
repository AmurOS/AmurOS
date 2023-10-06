#define BITMAP_SIZE 8

#define HEIGHTBORDERTOP 15
#define BASEBORDER 2
#define CORNERRADIUS 0
#define MAINCOLOR __vesa_VBE_RGB(51, 51, 51)

typedef struct __plasmaUI_Button
{
    int x;
    int y;
    int width;
    int height;
    int color;
    int background;
    char *str;
    int cornerRadius;
} __plasmaUI_Button;

typedef struct __plasmaUI_Item
{
    int x;
    int y;
    int width;
    int height;
    int color;
    int background;
    char *str;
    int cornerRadius;
} __plasmaUI_Item;

typedef struct __plasmaUI_ProgressBar
{
    int num;
    int max : 10;
    int x;
    int y;
    int width;
    int height;
    int color;
    int background;
    int cornerRadius;
} __plasmaUI_ProgressBar;

typedef struct __plasmaUI_ListBox
{
    int items;
    int x;
    int y;
    int width;
    int height;
    int color;
    int background;
    int cornerRadius;
} __plasmaUI_ListBox;

void __plasmaUI_CreateButton(__plasmaUI_Button button)
{
    __vesa_RectR(button.x, button.y, button.width, button.height, button.cornerRadius, button.background);
    if (__std__strlen(button.str) > 0)
        __plasmaUI_drawString(button.x + (button.width - (__std__strlen(button.str) * BITMAP_SIZE)) / 2, button.y + (button.height / 2 - 4), button.color, button.str, __std__strlen(button.str));
}

void __plasmaUI_CreateProgressBar(__plasmaUI_ProgressBar bar)
{
    __vesa_RectR(bar.x, bar.y, bar.width, bar.height, bar.cornerRadius, bar.background);
    for (int i = 0; i <= bar.num; i++)
    {
        if (i <= 0)
            ;
        else
            __vesa_RectR(bar.x, bar.y, i * bar.width / 100, bar.height, bar.cornerRadius, bar.color);

        if (i == bar.max)
            break;
        else
            i++;
    }
}

void __plasmaUI_CreateListBox(__plasmaUI_ListBox box)
{
    __plasmaUI_Item item;
    item.width = box.width - 4;
    item.height = 10;
    item.color = __vesa_VBE_RGB(78, 78, 78);
    __vesa_RectR(box.x, box.y, box.width, box.height, 0, box.background);
    for (int i = 0; i < box.items; i++)
    {

        if (box.y + i * (item.height + 2) + 2 == box.height)
            __vesa_RectR(box.x + 2, box.y + i * (item.height + 2) + 2, item.width, item.height, 0, item.color);
        else
            break;
    }
}

void __plasmaUI_CreateVScroll()
{
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
void __plasmaUI_drawNumbitmaps(int index, int x, int y, int color)
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
                __vesa_putpixel(x, y, color);
            }
            pix >>= 1;
            x--;
        }
        x = temp;
        y++;
    }
}

// putpixels of A-Z bits from right-to-left
void __plasmaUI_drawAlphabitmaps(int index, int x, int y, int color)
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
                __vesa_putpixel(x, y, color);
            }
            pix >>= 1;
            x--;
        }
        x = temp;
        y++;
    }
}

void __plasmaUI_drawChar(int x, int y, int color, char ch)
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

void __plasmaUI_drawString(int x, int y, int color, char *str, int size)
{
    for (int i = 0; i < __std__strlen(str); i++)
    {
        __plasmaUI_drawChar(x, y, color, str[i]);
        x += BITMAP_SIZE;
    }
}