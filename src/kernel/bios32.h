extern void BIOS32_START();
extern void BIOS32_END();
extern void *bios32_gdt_ptr;
extern void *bios32_gdt_entries;
extern void *bios32_idt_ptr;
extern void *bios32_in_reg16_ptr;
extern void *bios32_out_reg16_ptr;
extern void *bios32_int_number_ptr;

#define REBASE_ADDRESS(x)  (void*)(0x7c00 + (void*)x - (byte32i)BIOS32_START)

#define BIOS_CONVENTIONAL_MEMORY 0x7E00

IDT_PTR g_real_mode_gdt;
IDT_PTR g_real_mode_idt;

extern GDT g_gdt[NO_GDT_DESCRIPTORS];

void (*exec_bios32_function)() = (void *)0x7c00;

void bios32_init() {
    gdt_set_entry(6, 0, 0xffffffff, 0x9A, 0x0f);
    gdt_set_entry(7, 0, 0xffffffff, 0x92, 0x0f);
    g_real_mode_gdt.base_address = (byte32i)g_gdt;
    g_real_mode_gdt.limit = sizeof(g_gdt) - 1;
    g_real_mode_idt.base_address = 0;
    g_real_mode_idt.limit = 0x3ff;
}

void bios32_service(byte interrupt, REGISTERS16 *in, REGISTERS16 *out) {
    void *new_code_base = (void *)0x7c00;

    __std__memcpy(&bios32_gdt_entries, g_gdt, sizeof(g_gdt));
    g_real_mode_gdt.base_address = (byte32i)REBASE_ADDRESS((&bios32_gdt_entries));
    __std__memcpy(&bios32_gdt_ptr, &g_real_mode_gdt, sizeof(IDT_PTR));
    __std__memcpy(&bios32_idt_ptr, &g_real_mode_idt, sizeof(IDT_PTR));
    __std__memcpy(&bios32_in_reg16_ptr, in, sizeof(REGISTERS16));
    void *in_reg16_address = REBASE_ADDRESS(&bios32_in_reg16_ptr);
    __std__memcpy(&bios32_int_number_ptr, &interrupt, sizeof(byte));

    byte32i size = (byte32i)BIOS32_END - (byte32i)BIOS32_START;
    __std__memcpy(new_code_base, BIOS32_START, size);
    exec_bios32_function();
    in_reg16_address = REBASE_ADDRESS(&bios32_out_reg16_ptr);
    __std__memcpy(out, in_reg16_address, sizeof(REGISTERS16));

    gdt_init();
    idt_init();
}

void int86(byte interrupt, REGISTERS16 *in, REGISTERS16 *out) {
    bios32_service(interrupt, in, out);
}