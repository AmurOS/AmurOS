#define NO_IDT_DESCRIPTORS     256

extern void idt_set_entry(int index, byte32i base, bit8 seg_sel, byte flags);

extern void idt_init();