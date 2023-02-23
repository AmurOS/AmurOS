struct IDT_entry
{
	bit8 offset_lowerbits;
	bit8 selector;
	byte zero;
	byte type_attr;
	bit8 offset_higherbits;
};

struct IDT_entry __driver_kb_IDT[IDT_SIZE];

void __driver_kb_idt_init(void)
{
	byte32 keyboard_address;
	byte32 idt_address;
	byte32 idt_ptr[2];
	keyboard_address = (byte32)keyboard_handler;
	__driver_kb_IDT[0x21].offset_lowerbits = keyboard_address & 0xffff;
	__driver_kb_IDT[0x21].selector = KERNEL_CODE_SEGMENT_OFFSET;
	__driver_kb_IDT[0x21].zero = 0;
	__driver_kb_IDT[0x21].type_attr = INTERRUPT_GATE;
	__driver_kb_IDT[0x21].offset_higherbits = (keyboard_address & 0xffff0000) >> 16;
	write_port(0x20, 0x11);
	write_port(0xA0, 0x11);
	write_port(0x21, 0x20);
	write_port(0xA1, 0x28);
	write_port(0x21, 0x00);
	write_port(0xA1, 0x00);
	write_port(0x21, 0x01);
	write_port(0xA1, 0x01);
	write_port(0x21, 0xff);
	write_port(0xA1, 0xff);
	idt_address = (byte32)__driver_kb_IDT;
	idt_ptr[0] = (sizeof(struct IDT_entry) * IDT_SIZE) + ((idt_address & 0xffff) << 16);
	idt_ptr[1] = idt_address >> 16;
	load_idt(idt_ptr);
}

void __driver_kb_kb_init(void)
{
	write_port(0x21, 0xFD);
}

void __driver_kb_kb_stop(void)
{
	write_port(0x21, 0xFF);
}

void __driver_kb_stopinp(void)
{
	__driver_kb_kbbcur++;
	__driver_kb_kbbuffer[__driver_kb_kbbcur] = '\0';
	__driver_kb_endinp = true;
	__driver_kb_kb_stop();
	return;
}

void __driver_kb_keyboard_handler_main(void)
{
	byte status;
	char keycode;

	write_port(0x20, 0x20);

	status = read_port(KEYBOARD_STATUS_PORT);
	if (status & 0x01)
	{
		keycode = read_port(KEYBOARD_DATA_PORT);
		if (keycode < 0)
			return;

		if (keycode == ENTER_KEY_CODE)
		{
			__driver_kb_kbbcur++;
			__driver_kb_kbbuffer[__driver_kb_kbbcur] = '\0';
			__driver_kb_endinp = true;
			__std__cursorPosition((COLUMNS_IN_LINE * (__std__cursory + 1)) + 1);
			__driver_kb_kb_stop();
			return;
		}
		if (keycode == BACKSPACE_KEY_CODE)
		{
			if (__driver_kb_kbbcur != 0)
			{
				__driver_kb_kbbcur--;
				__std__cursorx--;
				__driver_kb_kbbuffer[__driver_kb_kbbcur] = '\0';
				__std__cursorPosition((COLUMNS_IN_LINE * __std__cursory) + __driver_kb_kbbcur + 1);
				__std__delete();
			}
			return;
		}
		if (keycode == TAB_KEY_CODE)
		{
			__driver_kb_kbbcur +=4;
			__std__cursorx += 4;
			__driver_kb_kbbuffer[__driver_kb_kbbcur] = '\0';
			__std__cursorPosition((COLUMNS_IN_LINE * __std__cursory) + __driver_kb_kbbcur--);
			__std__putc('\0');
			return;
		}

		__driver_kb_kbbuffer[__driver_kb_kbbcur] = keyboard_map[(byte)keycode];
		__driver_kb_kbbcur++;
		__std__cursorPosition((COLUMNS_IN_LINE * __std__cursory) + __driver_kb_kbbcur + 1);
		__std__putc(keyboard_map[(byte)keycode]);
	}
}

void __driver_kb_kbbuffer_init(int size)
{
	__driver_kb_kbbuffer = (char *)__std__malloc(size);
}