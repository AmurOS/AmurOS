#define NO_IDT_DESCRIPTORS     256

typedef struct {
    bit8 base_low;
    bit8 segment_selector;
    byte zero;
    byte type;
    bit8 base_high;
} __attribute__((packed)) IDT;

typedef struct {
    bit8 limit; 
    byte32i base_address;
} __attribute__((packed)) IDT_PTR;

IDT g_idt[NO_IDT_DESCRIPTORS];
IDT_PTR g_idt_ptr;

void idt_set_entry(int index, byte32i base, bit8 seg_sel, byte flags) {
    IDT *this = &g_idt[index];

    this->base_low = base & 0xFFFF;
    this->segment_selector = seg_sel;
    this->zero = 0;
    this->type = flags | 0x60;
    this->base_high = (base >> 16) & 0xFFFF;
}

void idt_init() {
    g_idt_ptr.base_address = (byte32i)g_idt;
    g_idt_ptr.limit = sizeof(g_idt) - 1;
    pic8259_init();

    idt_set_entry(0, (byte32i)exception_0, 0x08, 0x8E);
    idt_set_entry(1, (byte32i)exception_1, 0x08, 0x8E);
    idt_set_entry(2, (byte32i)exception_2, 0x08, 0x8E);
    idt_set_entry(3, (byte32i)exception_3, 0x08, 0x8E);
    idt_set_entry(4, (byte32i)exception_4, 0x08, 0x8E);
    idt_set_entry(5, (byte32i)exception_5, 0x08, 0x8E);
    idt_set_entry(6, (byte32i)exception_6, 0x08, 0x8E);
    idt_set_entry(7, (byte32i)exception_7, 0x08, 0x8E);
    idt_set_entry(8, (byte32i)exception_8, 0x08, 0x8E);
    idt_set_entry(9, (byte32i)exception_9, 0x08, 0x8E);
    idt_set_entry(10, (byte32i)exception_10, 0x08, 0x8E);
    idt_set_entry(11, (byte32i)exception_11, 0x08, 0x8E);
    idt_set_entry(12, (byte32i)exception_12, 0x08, 0x8E);
    idt_set_entry(13, (byte32i)exception_13, 0x08, 0x8E);
    idt_set_entry(14, (byte32i)exception_14, 0x08, 0x8E);
    idt_set_entry(15, (byte32i)exception_15, 0x08, 0x8E);
    idt_set_entry(16, (byte32i)exception_16, 0x08, 0x8E);
    idt_set_entry(17, (byte32i)exception_17, 0x08, 0x8E);
    idt_set_entry(18, (byte32i)exception_18, 0x08, 0x8E);
    idt_set_entry(19, (byte32i)exception_19, 0x08, 0x8E);
    idt_set_entry(20, (byte32i)exception_20, 0x08, 0x8E);
    idt_set_entry(21, (byte32i)exception_21, 0x08, 0x8E);
    idt_set_entry(22, (byte32i)exception_22, 0x08, 0x8E);
    idt_set_entry(23, (byte32i)exception_23, 0x08, 0x8E);
    idt_set_entry(24, (byte32i)exception_24, 0x08, 0x8E);
    idt_set_entry(25, (byte32i)exception_25, 0x08, 0x8E);
    idt_set_entry(26, (byte32i)exception_26, 0x08, 0x8E);
    idt_set_entry(27, (byte32i)exception_27, 0x08, 0x8E);
    idt_set_entry(28, (byte32i)exception_28, 0x08, 0x8E);
    idt_set_entry(29, (byte32i)exception_29, 0x08, 0x8E);
    idt_set_entry(30, (byte32i)exception_30, 0x08, 0x8E);
    idt_set_entry(31, (byte32i)exception_31, 0x08, 0x8E);
    idt_set_entry(32, (byte32i)irq_0, 0x08, 0x8E);
    idt_set_entry(33, (byte32i)irq_1, 0x08, 0x8E);
    idt_set_entry(34, (byte32i)irq_2, 0x08, 0x8E);
    idt_set_entry(35, (byte32i)irq_3, 0x08, 0x8E);
    idt_set_entry(36, (byte32i)irq_4, 0x08, 0x8E);
    idt_set_entry(37, (byte32i)irq_5, 0x08, 0x8E);
    idt_set_entry(38, (byte32i)irq_6, 0x08, 0x8E);
    idt_set_entry(39, (byte32i)irq_7, 0x08, 0x8E);
    idt_set_entry(40, (byte32i)irq_8, 0x08, 0x8E);
    idt_set_entry(41, (byte32i)irq_9, 0x08, 0x8E);
    idt_set_entry(42, (byte32i)irq_10, 0x08, 0x8E);
    idt_set_entry(43, (byte32i)irq_11, 0x08, 0x8E);
    idt_set_entry(44, (byte32i)irq_12, 0x08, 0x8E);
    idt_set_entry(45, (byte32i)irq_13, 0x08, 0x8E);
    idt_set_entry(46, (byte32i)irq_14, 0x08, 0x8E);
    idt_set_entry(47, (byte32i)irq_15, 0x08, 0x8E);
    idt_set_entry(128, (byte32i)exception_128, 0x08, 0x8E);

    _load_idt((byte32i)&g_idt_ptr);
    asm volatile("sti");
}
