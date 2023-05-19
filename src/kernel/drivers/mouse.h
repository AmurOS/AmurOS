#define MOUSE_CMD_RESET     0xFF
#define MOUSE_CMD_RESEND     0xFE
#define MOUSE_CMD_SET_DEFAULTS     0xF6
#define MOUSE_CMD_DISABLE_PACKET_STREAMING     0xF5
#define MOUSE_CMD_ENABLE_PACKET_STREAMING     0xF4
#define MOUSE_CMD_SAMPLE_RATE     0xF3
#define MOUSE_CMD_MOUSE_ID     0xF2
#define MOUSE_CMD_REQUEST_SINGLE_PACKET     0xEB
#define MOUSE_CMD_STATUS     0xE9
#define MOUSE_CMD_RESOLUTION     0xE8

#define MOUSE_ACKNOWLEDGE      0xFA

#define PS2_CMD_PORT      0x64    // read/write PS/2 command register
#define MOUSE_DATA_PORT     0x60    // PS/2 data port register see https://wiki.osdev.org/%228042%22_PS/2_Controller


typedef struct {
    byte left_button: 1;
    byte right_button: 1;
    byte middle_button: 1;
    byte always_1: 1;
    byte x_sign: 1;
    byte y_sign: 1;
    byte x_overflow: 1;
    byte y_overflow: 1;
} MOUSE_STATUS;

int g_mouse_x_pos = 0, g_mouse_y_pos = 0;
MOUSE_STATUS g_status;

/**
 * read a byte from given port number
 */
byte inportb(bit8 port) {
    byte ret;
    asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

/**
 * write a given byte to given port number
 */
void outportb(bit8 port, byte val) {
    asm volatile("outb %1, %0" :: "dN"(port), "a"(val));
}

/**
 * read 2 bytes(short) from given port number
 */
bit8 inports(bit8 port) {
    bit8 rv;
    asm volatile ("inw %1, %0" : "=a" (rv) : "dN" (port));
    return rv;
}

/**
 * write given 2 bytes(short) to given port number
 */
void outports(bit8 port, bit8 data) {
    asm volatile ("outw %1, %0" : : "dN" (port), "a" (data));
}

/**
 * read 4 bytes(long) from given port number
 */
byte32i inportl(bit8 port) {
    byte32i rv;
    asm volatile ("inl %%dx, %%eax" : "=a" (rv) : "dN" (port));
    return rv;
}

/**
 * write given 4 bytes(long) to given port number
 */
void outportl(bit8 port, byte32i data) {
    asm volatile ("outl %%eax, %%dx" : : "dN" (port), "a" (data));
}


int mouse_getx() {
    return g_mouse_x_pos;
}

int mouse_gety() {
    return g_mouse_y_pos;
}

void mouse_wait(bool type) {
    byte32i time_out = 100000;
    if (type == false) {
        // suspend until status is 1
        while (time_out--) {
            if ((inportb(PS2_CMD_PORT) & 1) == 1) {
                return;
            }
        }
        return;
    } else {
        while (time_out--) {
            if ((inportb(PS2_CMD_PORT) & 2) == 0) {
                return;
            }
        }
    }
}

void mouse_write(byte data) {
    // sending write command
    mouse_wait(true);
    outportb(PS2_CMD_PORT, 0xD4);
    mouse_wait(true);
    // finally write data to port
    outportb(MOUSE_DATA_PORT, data);
}

byte mouse_read() {
    mouse_wait(false);
    return inportb(MOUSE_DATA_PORT);
}

void get_mouse_status(char status_byte, MOUSE_STATUS *status) {
    __std__memset(status, 0, sizeof(MOUSE_STATUS));
    if (status_byte & 0x01)
        status->left_button = 1;
    if (status_byte & 0x02)
        status->right_button = 1;
    if (status_byte & 0x04)
        status->middle_button = 1;
    if (status_byte & 0x08)
        status->always_1 = 1;
    if (status_byte & 0x10)
        status->x_sign = 1;
    if (status_byte & 0x20)
        status->y_sign = 1;
    if (status_byte & 0x40)
        status->x_overflow = 1;
    if (status_byte & 0x80)
        status->y_overflow = 1;
}

void print_mouse_info() {
    __std__gotoxy(0, 0);
    __std__printff("Mouse Demo X: %d, Y: %d\n", g_mouse_x_pos, g_mouse_y_pos);
    if (g_status.left_button) {
        __std__printff("Left button clicked");
    }
    if (g_status.right_button) {
        __std__printff("Right button clicked");
    }
    if (g_status.middle_button) {
        __std__printff("Middle button clicked");
    }
}

void mouse_handler(REGISTERS *r) {
    static byte mouse_cycle = 0;
    static char mouse_byte[3];

    switch (mouse_cycle) {
        case 0:
            mouse_byte[0] = mouse_read();
            get_mouse_status(mouse_byte[0], &g_status);
            mouse_cycle++;
            break;
        case 1:
            mouse_byte[1] = mouse_read();
            mouse_cycle++;
            break;
        case 2:
            mouse_byte[2] = mouse_read();
            g_mouse_x_pos = g_mouse_x_pos + mouse_byte[1];
            g_mouse_y_pos = g_mouse_y_pos - mouse_byte[2];

            if (g_mouse_x_pos < 0)
                g_mouse_x_pos = 0;
            if (g_mouse_y_pos < 0)
                g_mouse_y_pos = 0;
            if (g_mouse_x_pos > WIDTHSCREEN)
                g_mouse_x_pos = WIDTHSCREEN - 1;
            if (g_mouse_y_pos > HEIGHTSCREEN)
                g_mouse_y_pos = HEIGHTSCREEN - 1;

           // console_clear(COLOR_WHITE, COLOR_BLACK);
            //console_gotoxy(g_mouse_x_pos, g_mouse_y_pos);
            //console_putchar('X');
            print_mouse_info();
            mouse_cycle = 0;
            break;
    }
    isr_end_interrupt(IRQ_BASE + 12);
}

/**
 * available rates 10, 20, 40, 60, 80, 100, 200
 */
void set_mouse_rate(byte rate) {
    byte status;

    outportb(MOUSE_DATA_PORT, MOUSE_CMD_SAMPLE_RATE);
    status = mouse_read();
    if(status != MOUSE_ACKNOWLEDGE) {
        __std__printff("error: failed to send mouse sample rate command\n");
        return;
    }
    outportb(MOUSE_DATA_PORT, rate);
    status = mouse_read();
    if(status != MOUSE_ACKNOWLEDGE) {
        __std__printff("error: failed to send mouse sample rate data\n");
        return;
    }
}

void mouse_init() {
    byte status;

    g_mouse_x_pos = 5;
    g_mouse_y_pos = 2;

    __std__printff("\ninitializing mouse...\n");

    // enable mouse device
    mouse_wait(true);
    outportb(PS2_CMD_PORT, 0xA8);

    // print mouse id
    outportb(MOUSE_DATA_PORT, MOUSE_CMD_MOUSE_ID);
    status = mouse_read();
    __std__printff("mouse id: 0x%x\n", status);

    set_mouse_rate(MOUSE_CMD_SAMPLE_RATE);

    //outportb(MOUSE_DATA_PORT, MOUSE_CMD_RESOLUTION);
    //outportb(MOUSE_DATA_PORT, 0);

    // enable the interrupt
    mouse_wait(true);
    outportb(PS2_CMD_PORT, 0x20);
    mouse_wait(false);
    // get and set second bit
    status = (inportb(MOUSE_DATA_PORT) | 2);
    // write status to port
    mouse_wait(true);
    outportb(PS2_CMD_PORT, MOUSE_DATA_PORT);
    mouse_wait(true);
    outportb(MOUSE_DATA_PORT, status);

    // set mouse to use default settings
    mouse_write(MOUSE_CMD_SET_DEFAULTS);
    status = mouse_read();
    if(status != MOUSE_ACKNOWLEDGE) {
        __std__printff("error: failed to set default mouse settings\n");
        return;
    }

    // enable packet streaming to receive
    mouse_write(MOUSE_CMD_ENABLE_PACKET_STREAMING);
    status = mouse_read();
    if(status != MOUSE_ACKNOWLEDGE) {
        __std__printff("error: failed to enable mouse packet streaming\n");
        return;
    }

    // set mouse handler
    isr_register_interrupt_handler(IRQ_BASE + 12, mouse_handler);
}
