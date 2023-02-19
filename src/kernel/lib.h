
#define NULL 0
#define new(t) malloc(sizeof(t))
#define bool int
#define true 1
#define false 0
#define bit8 unsigned short int
#define byte unsigned char
#define byte32 unsigned long
#define byte32i unsigned int
#define byte64 unsigned long long

#define LINES 25
#define COLUMNS_IN_LINE 80
#define BYTES_FOR_EACH_ELEMENT 2
#define SCREENSIZE BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE * LINES

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define IDT_SIZE 256
#define INTERRUPT_GATE 0x8e
#define KERNEL_CODE_SEGMENT_OFFSET 0x08

#define ENTER_KEY_CODE 0x1C

#define KEY_A 'a'
#define KEY_B 'b'
#define KEY_C 'c'
#define KEY_D 'd'
#define KEY_E 'e'
#define KEY_F 'f'
#define KEY_G 'g'
#define KEY_H 'h'
#define KEY_I 'i'
#define KEY_J 'j'
#define KEY_K 'k'
#define KEY_L 'l'
#define KEY_M 'm'
#define KEY_N 'n'
#define KEY_O 'o'
#define KEY_P 'p'
#define KEY_Q 'q'
#define KEY_R 'r'
#define KEY_S 's'
#define KEY_T 't'
#define KEY_U 'u'
#define KEY_V 'v'
#define KEY_W 'w'
#define KEY_X 'x'
#define KEY_Y 'y'
#define KEY_Z 'z'
#define KEY_1 '1'
#define KEY_2 '2'
#define KEY_3 '3'
#define KEY_4 '4'
#define KEY_5 '5'
#define KEY_6 '6'
#define KEY_7 '7'
#define KEY_8 '8'
#define KEY_9 '9'
#define KEY_0 '0'
#define KEY_MINUS '-'
#define KEY_EQUAL '='
#define KEY_SQUARE_OPEN_BRACKET '['
#define KEY_SQUARE_CLOSE_BRACKET ']'
#define KEY_SEMICOLON ';'
#define KEY_BACKSLASH '\\'
#define KEY_COMMA ','
#define KEY_DOT '.'
#define KEY_FORESLHASH '//'
#define KEY_F1 0
#define KEY_F2 0
#define KEY_F3 0
#define KEY_F4 0
#define KEY_F5 0
#define KEY_F6 0
#define KEY_F7 0
#define KEY_F8 0
#define KEY_F9 0
#define KEY_F10 0
#define KEY_F11 0
#define KEY_F12 0
#define KEY_BACKSPACE 0
#define KEY_DELETE 0
#define KEY_DOWN 0
#define KEY_END 0
#define KEY_ENTER '\b'
#define KEY_ESC 0
#define KEY_HOME 0
#define KEY_INSERT 0
#define KEY_KEYPAD_5 0
#define KEY_KEYPAD_MUL 0
#define KEY_KEYPAD_Minus 0
#define KEY_KEYPAD_PLUS 0
#define KEY_KEYPAD_DIV 0
#define KEY_LEFT 0
#define KEY_PAGE_DOWN 0
#define KEY_PAGE_UP 0
#define KEY_PRINT_SCREEN 0
#define KEY_RIGHT 0
#define KEY_SPACE 0
#define KEY_TAB 0
#define KEY_UP 0


byte keyboard_map[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', 0,	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};
