void fpu_set_control_word(const bit8 cw) {
    asm volatile("fldcw %0" ::"m"(cw));
}

void fpu_enable() {
    byte32i cr4;
    asm volatile("mov %%cr4, %0" :"=r"(cr4));
    cr4 |= 0x200;
    asm volatile("mov %0, %%cr4" ::"r"(cr4));
    fpu_set_control_word(0x37F); // fpu init
    fpu_set_control_word(0x37E); // invalid operand exceptions
    fpu_set_control_word(0x37A); // divide by zero
}