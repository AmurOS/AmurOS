/*extern byte32i __vesa_vbe_rgb(byte red, byte green, byte blue);*/

extern void __vesa_clear(int color);
extern void __vesa_putpixel(int x, int y, int color);
extern int __vesa_init(byte32i width, byte32i height, byte32i bpp);

void __vesa_line(int x1, int y1, int x2, int y2, int color)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx, sy;

    if (x1 < x2)
        sx = 1;
    else
        sx = -1;

    if (y1 < y2)
        sy = 1;
    else
        sy = -1;

    int err = dx - dy;

    while (1) {
        __vesa_putpixel(x1, y1, color);

        if (x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;

        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }

        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

void __vesa_draw_rect(int x, int y, int width, int height, int color)
{
    __vesa_line(x, y, x, y + height, color);
    __vesa_line(x, y, x + width, y, color);
    __vesa_line(x + width, y, x + width, y + height, color);
    __vesa_line(x, y + height, x + width, y + height, color);
}

void __vesa_Rect(int x, int y, int width, int height, int color)
{
    for (int i = 0; i < height; i++)
    {
        __vesa_line(x, y + i, x + width, y + i, color);
    }
}

void __vesa_bresenham_circle(int xc, int yc, int x, int y, int color)
{
    __vesa_putpixel(xc + x, yc + y, color);
    __vesa_putpixel(xc - x, yc + y, color);
    __vesa_putpixel(xc + x, yc - y, color);
    __vesa_putpixel(xc - x, yc - y, color);
    __vesa_putpixel(xc + y, yc + x, color);
    __vesa_putpixel(xc - y, yc + x, color);
    __vesa_putpixel(xc + y, yc - x, color);
    __vesa_putpixel(xc - y, yc - x, color);
}

void __vesa_circle(int x, int y, int radius, int color)
{
    int x2 = 0, y2 = radius;
    int d = 3 - 2 * radius;
    __vesa_bresenham_circle(x, y, x2, y2, color);
    while (y2 >= x2)
    {
        x2++;
        if (d > 0)
        {
            y2--;
            d = d + 4 * (x2 - y2) + 10;
        }
        else
        {
            d = d + 4 * x2 + 6;
        }
        __vesa_bresenham_circle(x, y, x2, y2, color);
    }
}

void __vesa_circleF(int Xx, int Yy, int radius, int color)
{
    for (int y = -radius; y <= radius; y++)
        for (int x = -radius; x <= radius; x++)
            if (x * x + y * y < radius * radius - radius)
                __vesa_putpixel(Xx + x, Yy + y, color);
}

void __vesa_RectR(int x, int y, int width, int height, int radius, int color)
{
    // fill and draw round corner
    __vesa_circleF(x + radius, y + height - radius, radius, color);
    __vesa_circleF(x + width - radius, y + height - radius, radius, color);
    __vesa_circleF(x + width - radius, y + radius, radius, color);
    __vesa_circleF(x + radius, y + radius, radius, color);

    __vesa_Rect(x + radius, y, width - radius * 2, height, color);
    __vesa_Rect(x, y + radius, width, height - radius * 2, color);
}