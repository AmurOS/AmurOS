#define NO_GDT_DESCRIPTORS     8

typedef struct {
    bit8 segment_limit;
    bit8 base_low;
    byte base_middle;
    byte access;
    byte granularity;
    byte base_high;
} __attribute__((packed)) GDT;

typedef struct {
    bit8 limit;
    byte32i base_address;
} __attribute__((packed)) GDT_PTR;

GDT g_gdt[NO_GDT_DESCRIPTORS];
GDT_PTR g_gdt_ptr;

void gdt_set_entry(int index, byte32i base, byte32i limit, byte access, byte gran) {
    GDT *this = &g_gdt[index];

    this->segment_limit = limit & 0xFFFF;
    this->base_low = base & 0xFFFF;
    this->base_middle = (base >> 16) & 0xFF;
    this->access = access;

    this->granularity = (limit >> 16) & 0x0F;
    this->granularity = this->granularity | (gran & 0xF0);

    this->base_high = (base >> 24 & 0xFF);
}

void gdt_init() {
    g_gdt_ptr.limit = sizeof(g_gdt) - 1;
    g_gdt_ptr.base_address = (byte32i)g_gdt;

    // NULL segment
    gdt_set_entry(0, 0, 0, 0, 0);
    // code segment
    gdt_set_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    // data segment
    gdt_set_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    // user code segment
    gdt_set_entry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    // user data segment
    gdt_set_entry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    load_gdt((byte32i)&g_gdt_ptr);
}