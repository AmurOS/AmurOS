typedef struct
{
    char VbeSignature[4];      /* VBE Signature */
    bit8 VbeVersion;           /* VBE version number */
    char *OEMStringPtr;        /* Pointer to OEM string */
    byte32i Capabilities;      /* Capabilities of video card */
    byte32i *VideoModePtr;     /* Pointer to supported modes */
    bit8 TotalMemory;          /* Number of 64kb memory blocks */
    bit8 OemSoftwareRev;       /* VBE implementation Software revision */
    byte32i OemVendorNamePtr;  /* Pointer to Vendor Name String */
    byte32i OemProductNamePtr; /* Pointer to Product Name String */
    byte32i OemProductRevPtr;  /* Pointer to Product Revision String */
    char reserved[222];        /* Pad to 256 byte block size */
    char OemData[256];         /* Data Area for OEM Strings */
} __attribute__((packed)) __vesa_VBE20_INFOBLOCK;

typedef struct
{
    // Mandatory information for all VBE revisions
    bit8 ModeAttributes;      /* Mode attributes */
    byte WinAAttributes;      /* Window A attributes */
    byte WinBAttributes;      /* Window B attributes */
    bit8 WinGranularity;      /* Window granularity in k */
    bit8 WinSize;             /* Window size in k */
    bit8 WinASegment;         /* Window A segment */
    bit8 WinBSegment;         /* Window B segment */
    void (*WinFuncPtr)(void); /* Pointer to window function */
    bit8 BytesPerScanLine;    /* Bytes per scanline */

    // Mandatory information for VBE 1.2 and above
    bit8 XResolution;        /* Horizontal resolution */
    bit8 YResolution;        /* Vertical resolution */
    byte XCharSize;          /* Character cell width */
    byte YCharSize;          /* Character cell height */
    byte NumberOfPlanes;     /* Number of memory planes */
    byte BitsPerPixel;       /* Bits per pixel */
    byte NumberOfBanks;      /* Number of CGA style banks */
    byte MemoryModel;        /* Memory model type */
    byte BankSize;           /* Size of CGA style banks */
    byte NumberOfImagePages; /* Number of images pages */
    byte Reserved;           /* Reserved */

    // Direct color fields
    byte RedMaskSize;         /* Size of direct color red mask */
    byte RedFieldPosition;    /* Bit posn of lsb of red mask */
    byte GreenMaskSize;       /* Size of direct color green mask */
    byte GreenFieldPosition;  /* Bit posn of lsb of green mask */
    byte BlueMaskSize;        /* Size of direct color blue mask */
    byte BlueFieldPosition;   /* Bit posn of lsb of blue mask */
    byte RsvdMaskSize;        /* Size of direct color res mask */
    byte RsvdFieldPosition;   /* Bit posn of lsb of res mask */
    byte DirectColorModeInfo; /* Direct color mode attributes */

    // Mandatory information for VBE 2.0 and above
    byte32i PhysBasePtr;        /* physical address for flat frame buffer */
    byte32i OffScreenMemOffset; /* pointer to start of off screen memory */
    bit8 OffScreenMemSize;      /* amount of off screen memory in 1k units */
    byte Reserved2[206];        /* remainder of ModeInfoBlock */
} __vesa_VBE20_MODEINFOBLOCK;

#define __vesa_VBE_RGB(r, g, b) __vesa_vbe_rgb(r, g, b)
#define __vesa_VBE_HEX(hexValue) __vesa_vbe_hex(hexValue)

__vesa_VBE20_INFOBLOCK g_vbe_infoblock;
__vesa_VBE20_MODEINFOBLOCK g_vbe_modeinfoblock;
int g_selected_mode = -1;
byte32i g_width = 0, g_height = 0;
byte32i *g_vbe_buffer = NULL;

byte32i __vesa_vbe_rgb(byte red, byte green, byte blue)
{
    byte32i color = red;
    color <<= 16;
    color |= (green << 8);
    color |= blue;
    return color;
}

byte32i __vesa_vbe_hex(int hex)
{
    int r, g, b;
    r = ((hex >> 16) & 0xFF) / 255.0; // Extract the RR byte
    g = ((hex >> 8) & 0xFF) / 255.0;  // Extract the GG byte
    b = ((hex)&0xFF) / 255.0;         // Extract the BB byte
    return __vesa_VBE_RGB(r, g, b);
}

int __vesa_get_vbe_info()
{
    REGISTERS16 in = {0}, out = {0};
    in.ax = 0x4F00;
    in.di = BIOS_CONVENTIONAL_MEMORY;
    int86(0x10, &in, &out);
    __std__memcpy(&g_vbe_infoblock, (void *)BIOS_CONVENTIONAL_MEMORY, sizeof(__vesa_VBE20_INFOBLOCK));
    return (out.ax == 0x4F);
}

void __vesa_get_vbe_mode_info(bit8 mode, __vesa_VBE20_MODEINFOBLOCK *mode_info)
{
    REGISTERS16 in = {0}, out = {0};
    in.ax = 0x4F01;
    in.cx = mode;
    in.di = BIOS_CONVENTIONAL_MEMORY + 1024;
    int86(0x10, &in, &out);
    __std__memcpy(mode_info, (void *)BIOS_CONVENTIONAL_MEMORY + 1024, sizeof(__vesa_VBE20_MODEINFOBLOCK));
}

void __vesa_vbe_set_mode(byte32i mode)
{
    REGISTERS16 in = {0}, out = {0};
    in.ax = 0x4F02;
    in.bx = mode;
    int86(0x10, &in, &out);
}

byte32i __vesa_vbe_find_mode(byte32i width, byte32i height, byte32i bpp)
{
    bit8 *mode_list = (bit8 *)g_vbe_infoblock.VideoModePtr;
    bit8 mode = *mode_list++;
    while (mode != 0xffff)
    {
        __vesa_get_vbe_mode_info(mode, &g_vbe_modeinfoblock);
        if (g_vbe_modeinfoblock.XResolution == width && g_vbe_modeinfoblock.YResolution == height && g_vbe_modeinfoblock.BitsPerPixel == bpp)
        {
            return mode;
        }
        mode = *mode_list++;
    }
    return -1;
}

void __vesa_vbe_print_available_modes()
{
    __std__cls();
    __std__gotoxy(0,0);
    __std__sleep(1000);
    __vesa_VBE20_MODEINFOBLOCK modeinfoblock;

    bit8 *mode_list = (bit8 *)g_vbe_infoblock.VideoModePtr;
    bit8 mode = *mode_list++;
    while (mode != 0xffff)
    {
        __vesa_get_vbe_mode_info(mode, &modeinfoblock);
        __std__printff("Mode: %d, X: %d, Y: %d\n", mode, modeinfoblock.XResolution, modeinfoblock.YResolution);
        mode = *mode_list++;
    }
}

void __vesa_update(unsigned long *buf){
    unsigned long c;
    unsigned long *p = g_vbe_buffer, *p2 = buf;

    for (c = 0; c < WIDTHSCREEN * HEIGHTSCREEN; c++)
    {
        *p = *p2;
        p++;
        p2++;
    }
}

int __vesa_init(byte32i width, byte32i height, byte32i bpp)
{
    __std__printff("\ninitializing vesa vbe 2.0\n");
    if (!__vesa_get_vbe_info())
    {
        __sh_error("No VESA VBE 2.0 detected");
        return -1;
    }
#define PRINT_MODES 0
#if PRINT_MODES
    __std__printff("\nModes:");
    __vesa_vbe_print_available_modes();
    return 1;
#else
    g_selected_mode = __vesa_vbe_find_mode(width, height, bpp);
    if (g_selected_mode == -1)
    {
        __sh_error("failed to find mode for %dx%d", width, height);
        return -1;
    }
    __std__printff("\nselected mode: %d ", g_selected_mode);
    g_width = g_vbe_modeinfoblock.XResolution;
    g_height = g_vbe_modeinfoblock.YResolution;
    g_vbe_buffer = (byte32i *)g_vbe_modeinfoblock.PhysBasePtr;
    __vesa_vbe_set_mode(g_selected_mode);
#endif

    return 0;
}

