#define MULTIBOOT_MAGIC_HEADER 0x1BADB002
#define MULTIBOOT_BOOTLOADER_MAGIC 0x2BADB002

#define NULL '\0'
//#define new(t) __std__malloc(sizeof(t))
#define bool int
#define true 1
#define false 0
#define bit8 unsigned short int
#define byte unsigned char
#define byte32 unsigned long
#define byte32i unsigned int
#define byte64 unsigned long long

#define LINES 25
#define COLUMNS_IN_LINE 80
#define BYTES_FOR_EACH_ELEMENT 2
#define SCREENSIZE BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE * LINES

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define IDT_SIZE 256
#define INTERRUPT_GATE 0x8e
#define KERNEL_CODE_SEGMENT_OFFSET 0x08

#define COMMAND_PORT 0x3D4
#define DATA_PORT 0x3D5
#define HIGH_BYTE_COMMAND 14
#define LOW_BYTE_COMMAND 15

#define ENTER_KEY_CODE 0x1C
#define BACKSPACE_KEY_CODE 0x0E
#define TAB_KEY_CODE 0x0F

byte keyboard_map[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', 0,	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};
byte Capskeyboard_map[128] =
{
    0,  27, '!', '@', '#', '$', '%', '^', '&', '*',	/* 9 */
  '(', ')', '_', '+', 0,	/* Backspace */
  '\t',			/* Tab */
  'Q', 'W', 'E', 'R',	/* 19 */
  'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',	/* 39 */
 '\"', '~',   0,		/* Left shift */
 '|', 'Z', 'X', 'C', 'V', 'B', 'N',			/* 49 */
  'M', '<', '>', '?',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

byte32i b8atb32(byte *arr) {
  return (byte32i)arr[0] << 24 | (byte32i)arr[1] << 16 | (byte32i)arr[2] << 8 | (byte32i)arr[3];
}


int b8ati(byte *arr) {
  return (int)(arr[0] << 24 | arr[1] << 16 | arr[2] << 8 | arr[3]);
}

bool arraycmp(byte *f, byte *s, byte32i size) {
    for (byte32i i = 0; i < size; i++) {
        if (f[i] != s[i])
            return false;
    }
    return true;
}

byte *btarrev(byte *arr)
{
  byte *narr = arr;
  int n = sizeof(narr) / sizeof(*narr);

  for (int i = 0; i < n / 2; i++) {
      int temp = narr[n - i - 1];
      narr[n - i - 1] = narr[i];
      narr[i] = temp;
  }
  return narr;
}


typedef struct
{
    struct
    {
        byte32i k_start_addr;
        byte32i k_end_addr;
        byte32i k_len;
        byte32i text_start_addr;
        byte32i text_end_addr;
        byte32i text_len;
        byte32i data_start_addr;
        byte32i data_end_addr;
        byte32i data_len;
        byte32i bss_start_addr;
        byte32i bss_end_addr;
        byte32i bss_len;
    } kernel;

    struct
    {
        byte32i total_memory;
    } system;

    struct
    {
        byte32i start_addr;
        byte32i end_addr;
        byte32i size;
    } available;
} KERNEL_MEMORY_MAP;

extern KERNEL_MEMORY_MAP g_kmap;

KERNEL_MEMORY_MAP g_kmap;

static long long __shell_pointer = 0;

/* The Multiboot header. */
typedef struct
{
    byte32i magici;
    byte32i flags;
    byte32i checksum;
    byte32i header_addr;
    byte32i load_addr;
    byte32i load_end_addr;
    byte32i bss_end_addr;
    byte32i entry_addr;
} _MULTIBOOT_HEADER;

/* The symbol table for a.out. */
typedef struct
{
    byte32i tabsize;
    byte32i strsize;
    byte32i addr;
    byte32i reserved;
} AOUT_SYMBOL_TABLE;

/* The section header table for ELF. */
typedef struct
{
    byte32i num;
    byte32i size;
    byte32i addr;
    byte32i shndx;
} ELF_SECTION_HEADER_TABLE;

typedef struct
{
    /* required, defined in entry.asm */
    byte32i flags;

    /* available low-high memory from BIOS, present if flags[0] is set(MEMINFO in entry.asm) */
    byte32i mem_low;
    byte32i mem_high;

    /* "root" partition, present if flags[1] is set(BOOTDEVICE in entry.asm) */
    byte32i boot_device;

    /* kernel command line, present if flags[2] is set(CMDLINE in entry.asm) */
    byte32i cmdline;

    /* no of modules loaded, present if flags[3] is set(MODULECOUNT in entry.asm) */
    byte32i modules_count;
    byte32i modules_addr;

    /* symbol table info, present if flags[4] & flags[5] is set(SYMT in entry.asm) */
    union
    {
        AOUT_SYMBOL_TABLE aout_sym;
        ELF_SECTION_HEADER_TABLE elf_sec;
    } u;

    /* memory mapping, present if flags[6] is set(MEMMAP in entry.asm) */
    byte32i mmap_length;
    byte32i mmap_addr;

    /* drive info, present if flags[7] is set(DRIVE in entry.asm) */
    byte32i drives_length;
    byte32i drives_addr;

    /* ROM configuration table, present if flags[8] is set(CONFIGT in entry.asm) */
    byte32i config_table;

    /* boot loader name, present if flags[9] is set(BOOTLDNAME in entry.asm) */
    byte32i boot_loader_name;

    /* Advanced Power Management(APM) table, present if flags[10] is set(APMT in entry.asm) */
    byte32i apm_table;

    /* video info, present if flags[11] is set(VIDEO in entry.asm) */
    byte32i vbe_control_info;
    byte32i vbe_mode_info;
    bit8 vbe_mode;
    bit8 vbe_interface_seg;
    bit8 vbe_interface_off;
    bit8 vbe_interface_len;

    /* video framebufer info, present if flags[12] is set(VIDEO_FRAMEBUF in entry.asm)  */
    byte32i framebuffer_addr;
    byte32i framebuffer_pitch;
    byte32i framebuffer_width;
    byte32i framebuffer_height;
    byte framebuffer_bpp;
    byte framebuffer_type; // indexed = 0, RGB = 1, EGA = 2

} MULTIBOOT_INFO;

typedef enum
{
    MULTIBOOT_MEMORY_AVAILABLE = 1,
    MULTIBOOT_MEMORY_RESERVED,
    MULTIBOOT_MEMORY_ACPI_RECLAIMABLE,
    MULTIBOOT_MEMORY_NVS,
    MULTIBOOT_MEMORY_BADRAM
} MULTIBOOT_MEMORY_TYPE;

typedef struct
{
    byte32i size;
    byte32i addr_low;
    byte32i addr_high;
    byte32i len_low;
    byte32i len_high;
    MULTIBOOT_MEMORY_TYPE type;
} MULTIBOOT_MEMORY_MAP;
