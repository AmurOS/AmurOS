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

extern void bios32_init();
extern void bios32_service(byte interrupt, REGISTERS16 *in, REGISTERS16 *out);
extern void int86(byte interrupt, REGISTERS16 *in, REGISTERS16 *out);