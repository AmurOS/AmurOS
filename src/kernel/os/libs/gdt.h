#define NO_GDT_DESCRIPTORS     8
extern void gdt_set_entry(int index, byte32i base, byte32i limit, byte access, byte gran);
extern void gdt_init();