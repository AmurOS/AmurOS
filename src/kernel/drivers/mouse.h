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
} __MOUSE_STATUS;

int g_mouse_x_pos = 0, g_mouse_y_pos = 0;
__MOUSE_STATUS g_status;

int __mouse_getx() {
    return g_mouse_x_pos;
}

int __mouse_gety() {
    return g_mouse_y_pos;
}

void __mouse_wait(bool type) {
    byte32i time_out = 100000;
    if (type == false) {
        // suspend until status is 1
        while (time_out--) {
            if ((read_port(PS2_CMD_PORT) & 1) == 1) {
                return;
            }
        }
        return;
    } else {
        while (time_out--) {
            if ((read_port(PS2_CMD_PORT) & 2) == 0) {
                return;
            }
        }
    }
}

void __mouse_write(byte data) {
    // sending write command
    __mouse_wait(true);
    write_port(PS2_CMD_PORT, 0xD4);
    __mouse_wait(true);
    // finally write data to port
    write_port(MOUSE_DATA_PORT, data);
}

byte __mouse_read() {
    __mouse_wait(false);
    return read_port(MOUSE_DATA_PORT);
}

void __get_mouse_status(char status_byte, __MOUSE_STATUS *status) {  
    __std__memset(status, 0, sizeof(__MOUSE_STATUS));
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

void __print_mouse_info() {
    __std__gotoxy(0,0);
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

void __mouse_handler(REGISTERS *r) {
    static byte mouse_cycle = 0;
    static char mouse_byte[3];

    switch (mouse_cycle) {
        case 0:
            mouse_byte[0] = __mouse_read();
            __get_mouse_status(mouse_byte[0], &g_status);
            mouse_cycle++;
            break;
        case 1:
            mouse_byte[1] = __mouse_read();
            mouse_cycle++;
            break;
        case 2:
            mouse_byte[2] = __mouse_read();
            g_mouse_x_pos = g_mouse_x_pos + mouse_byte[1];
            g_mouse_y_pos = g_mouse_y_pos - mouse_byte[2];

            if (g_mouse_x_pos < 0)
                g_mouse_x_pos = 0;
            if (g_mouse_y_pos < 0)
                g_mouse_y_pos = 0;
            if (g_mouse_x_pos > COLUMNS_IN_LINE)
                g_mouse_x_pos = COLUMNS_IN_LINE - 1;
            if (g_mouse_y_pos > LINES)
                g_mouse_y_pos = LINES - 1;

            __std__cls();
            __std__gotoxy(g_mouse_x_pos, g_mouse_y_pos);
            __std__putc('X');
            __print_mouse_info();
            mouse_cycle = 0;
            break;
    }
    isr_end_interrupt(IRQ_BASE + 12);
}

/**
 * available rates 10, 20, 40, 60, 80, 100, 200
 */
void __set_mouse_rate(byte rate) {
    byte status;

    write_port(MOUSE_DATA_PORT, MOUSE_CMD_SAMPLE_RATE);
    status = __mouse_read();
    if(status != MOUSE_ACKNOWLEDGE) {
        __std__printff("error: failed to send mouse sample rate command\n");
        return;
    }
    write_port(MOUSE_DATA_PORT, rate);
    status = __mouse_read();
    if(status != MOUSE_ACKNOWLEDGE) {
        __std__printff("error: failed to send mouse sample rate data\n");
        return;
    }
}

void mouse_init() {
    byte status;

    g_mouse_x_pos = 5;
    g_mouse_y_pos = 2;

    __std__printff("initializing mouse...\n");

    // enable mouse device
    __mouse_wait(true);
    write_port(PS2_CMD_PORT, 0xA8);

    // print mouse id
    write_port(MOUSE_DATA_PORT, MOUSE_CMD_MOUSE_ID);
    status = __mouse_read();
    __std__printff("mouse id: 0x%x\n", status);

    __set_mouse_rate(10);

    //write_port(MOUSE_DATA_PORT, MOUSE_CMD_RESOLUTION);
    //write_port(MOUSE_DATA_PORT, 0);

    // enable the interrupt
    __mouse_wait(true);
    write_port(PS2_CMD_PORT, 0x20);
    __mouse_wait(false);
    // get and set second bit
    status = (read_port(MOUSE_DATA_PORT) | 2);
    // write status to port
    __mouse_wait(true);
    write_port(PS2_CMD_PORT, MOUSE_DATA_PORT);
    __mouse_wait(true);
    write_port(MOUSE_DATA_PORT, status);

    // set mouse to use default settings
    __mouse_write(MOUSE_CMD_SET_DEFAULTS);
    status = __mouse_read();
    if(status != MOUSE_ACKNOWLEDGE) {
        __std__printff("error: failed to set default mouse settings\n");
        return;
    }

    // enable packet streaming to receive
    __mouse_write(MOUSE_CMD_ENABLE_PACKET_STREAMING);
    status = __mouse_read();
    if(status != MOUSE_ACKNOWLEDGE) {
        __std__printff("error: failed to enable mouse packet streaming\n");
        return;
    }

    // set mouse handler
    isr_register_interrupt_handler(IRQ_BASE + 12, __mouse_handler);
}
