/*https://wiki.osdev.org/8259_PIC */
#define PIC1 0x20
#define PIC2 0xA0
#define PIC1_COMMAND PIC1
#define PIC1_DATA (PIC1+1)
#define PIC2_COMMAND PIC2
#define PIC2_DATA (PIC2+1)

#define PIC_EOI 0x20

#define ICW1 0x11
#define ICW4_8086 0x01

void pic8259_init() {
    byte a1, a2;

    a1 = read_port(PIC1_DATA);
    a2 = read_port(PIC2_DATA);

    write_port(PIC1_COMMAND, ICW1);
    write_port(PIC2_COMMAND, ICW1);

    write_port(PIC1_DATA, 0x20);
    write_port(PIC2_DATA, 0x28);

    write_port(PIC1_DATA, 4);
    write_port(PIC2_DATA, 2);

    write_port(PIC1_DATA, ICW4_8086);
    write_port(PIC2_DATA, ICW4_8086);

    write_port(PIC1_DATA, a1);
    write_port(PIC2_DATA, a2);
}

void pic8259_eoi(byte irq) {
    if(irq >= 0x28)
        write_port(PIC2, PIC_EOI);
    write_port(PIC1, PIC_EOI);
}
