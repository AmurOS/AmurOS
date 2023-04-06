// THERE WILL BE GRAPHICS IN THE FUTURE
// VGA GRAPHICS
static byte *g_vga_buffer;

#define VGA_MISC_READ 0x3CC
#define VGA_MISC_WRITE 0x3C2
#define VGA_SEQ_INDEX 0x3C4
#define VGA_SEQ_DATA 0x3C5
#define VGA_GC_INDEX 0x3CE
#define VGA_GC_DATA 0x3CF
#define VGA_AC_INDEX 0x3C0
#define VGA_AC_READ 0x3C1
#define VGA_AC_WRITE 0x3C0
#define VGA_CRTC_INDEX 0x3D4
#define VGA_CRTC_DATA 0x3D5
#define VGA_DAC_READ_INDEX 0x3C7
#define VGA_DAC_WRITE_INDEX 0x3C8
#define VGA_DAC_DATA 0x3C9
#define VGA_INSTAT_READ 0x3DA
#define VGA_ADDRESS 0xA0000
#define VGA_MAX_WIDTH 320
#define VGA_MAX_HEIGHT 200
#define VGA_MAX (VGA_MAX_WIDTH * VGA_MAX_HEIGHT)

__graphics_putpixel(bit8 x, bit8 y, byte color)
{
    bit8 index = 0;
    index = 320 * y + x;
    if (index < VGA_MAX)
        g_vga_buffer[index] = color;
}

void __graphics_line(bit8 x1, bit8 y1, bit8 x2, bit8 y2, byte color)
{
    if (y1 == y2)
    {
        for (bit8 i = x1; i <= x2; i++)
            __graphics_putpixel(i, y1, color);
        return;
    }

    if (x1 == x2)
    {
        for (bit8 i = y1; i <= y2; i++)
        {
            __graphics_putpixel(x1, i, color);
        }
        return;
    }
}

void _graphics_draw_rect(bit8 x, bit8 y, bit8 width, bit8 height, byte color)
{
    __graphics_line(x, y, x, y + height, color);
    __graphics_line(x, y, x + width, y, color);
    __graphics_line(x + width, y, x + width, y + height, color);
    __graphics_line(x, y + height, x + width, y + height, color);
}

void __graphics_fillrect(bit8 x, bit8 y, bit8 width, bit8 height, byte color)
{
    __graphics_line(x, y, x, y + height, color);
    __graphics_line(x, y, x + width, y, color);
    __graphics_line(x + width, y, x + width, y + height, color);
    __graphics_line(x, y + height, x + width, y + height, color);
    for (int i = 0; i < height; i++)
    {
        __graphics_line(x, y + i, x + width, y + i, color);
    }
}

void __graphics_bresenham_circle(int xc, int yc, int x, int y, byte color)
{
    __graphics_putpixel(xc + x, yc + y, color);
    __graphics_putpixel(xc - x, yc + y, color);
    __graphics_putpixel(xc + x, yc - y, color);
    __graphics_putpixel(xc - x, yc - y, color);
    __graphics_putpixel(xc + y, yc + x, color);
    __graphics_putpixel(xc - y, yc + x, color);
    __graphics_putpixel(xc + y, yc - x, color);
    __graphics_putpixel(xc - y, yc - x, color);
}

void __graphics_circle(bit8 x, bit8 y, bit8 radius, byte color)
{
    int x2 = 0, y2 = radius;
    int d = 3 - 2 * radius;
    __graphics_bresenham_circle(x, y, x2, y2, color);
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
        __graphics_bresenham_circle(x, y, x2, y2, color);
    }
}

void __graphics_circleF(bit8 Xx, bit8 Yy, bit8 radius, byte color)
{
     for (int y = -radius; y <= radius; y++)
        for (int x = -radius; x <= radius; x++)
            if (x*x + y*y < radius*radius - radius)
                __graphics_putpixel(Xx + x, Yy + y, color);
}

void __graphics_RectR(bit8 x, bit8 y, bit8 width, bit8 height, bit8 radius, byte color)
{
    // fill and draw round corner
    __graphics_circleF(x + radius, y + height - radius, radius, color);
    __graphics_circleF(x + width - radius, y + height - radius, radius, color);
    __graphics_circleF(x + width - radius, y + radius, radius, color);
    __graphics_circleF(x + radius, y + radius, radius, color);

    __graphics_fillrect(x + radius, y, width - radius * 2, height, color);
    __graphics_fillrect(x, y + radius, width, height - radius * 2, color);
}

void __graphics_clear(byte color)
{
    for (byte32i index = 0; index < VGA_MAX; index++)
        g_vga_buffer[index] = color;
}

void __graphics_init()
{
    set_miscellaneous_registers();
    set_sequencer_registers();
    set_crt_controller_registers();
    set_graphics_controller_registers();
    set_attribute_controller_registers();

    g_vga_buffer = (byte *)VGA_ADDRESS;
    __graphics_clear(BLACK);
}

// for ini

void set_miscellaneous_registers()
{
    write_port(VGA_MISC_WRITE, 0x63);
}

void set_sequencer_registers()
{
    write_port(VGA_SEQ_INDEX, 0);   // sequencer index
    write_port(VGA_SEQ_DATA, 0x03); // sequencer reset

    write_port(VGA_SEQ_INDEX, 1);   // sequencer index
    write_port(VGA_SEQ_DATA, 0x01); // clocking mode

    write_port(VGA_SEQ_INDEX, 2);   // sequencer index
    write_port(VGA_SEQ_DATA, 0x0F); // plane/map mask

    write_port(VGA_SEQ_INDEX, 3);   // sequencer index
    write_port(VGA_SEQ_DATA, 0x00); // character font

    write_port(VGA_SEQ_INDEX, 4);   // sequencer index
    write_port(VGA_SEQ_DATA, 0x0E); // memory mode register
}

void set_graphics_controller_registers()
{
    write_port(VGA_GC_INDEX, 0);   // gc index
    write_port(VGA_GC_DATA, 0x00); // set/reset register

    write_port(VGA_GC_INDEX, 1);   // gc index
    write_port(VGA_GC_DATA, 0x00); // enable set/reset register

    write_port(VGA_GC_INDEX, 2);   // gc index
    write_port(VGA_GC_DATA, 0x00); // color compare register

    write_port(VGA_GC_INDEX, 3);   // gc index
    write_port(VGA_GC_DATA, 0x00); // data rotate register

    write_port(VGA_GC_INDEX, 4);   // gc index
    write_port(VGA_GC_DATA, 0x00); // read plane select register

    write_port(VGA_GC_INDEX, 5);   // gc index
    write_port(VGA_GC_DATA, 0x40); // graphics mode register

    write_port(VGA_GC_INDEX, 6);   // gc index
    write_port(VGA_GC_DATA, 0x05); // miscellaneous register

    write_port(VGA_GC_INDEX, 7);   // gc index
    write_port(VGA_GC_DATA, 0x0F); // color dont care register

    write_port(VGA_GC_INDEX, 8);   // gc index
    write_port(VGA_GC_DATA, 0xFF); // bit mask register
}

void set_attribute_controller_registers()
{
    byte32i d;
    byte32i ac_data[21] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                           0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
                           0x41, 0x00, 0x0F, 0x00, 0x00};

    for (byte32i index = 0; index < 21; index++)
    {
        write_port(VGA_AC_INDEX, index);
        write_port(VGA_AC_WRITE, ac_data[index]);
    }
    d = read_port(VGA_INSTAT_READ);
    write_port(VGA_AC_INDEX, d | 0x20);
}

void set_crt_controller_registers()
{
    byte32i crtc_data[25] = {0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0xBF, 0x1F,
                             0x00, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                             0x9C, 0x0E, 0x8F, 0x28, 0x40, 0x96, 0xB9, 0xA3, 0xFF};

    for (byte32i index = 0; index < 25; index++)
    {
        write_port(VGA_CRTC_INDEX, index);
        write_port(VGA_CRTC_DATA, crtc_data[index]);
    }
}