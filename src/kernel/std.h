volitile static char[SCREENSIZE+1] RAMBUFFER;
char *__std__vidmem = (char *)0xb8000;

int __std__strlen(const char *str);

static byte __std__buffmem[1024 * 1024];
static int __std__next_index = 0;
unsigned long int next = 1;
enum colors color = 7;

void __init_ram_buffer() {
	for (int i = 0; i < SCREENSIZE; i++) {
		STDRAM[i] = 0x00;
	}
	__std__printf("Initialized");
	__std__newline();
}

enum colors __std__color(enum colors c)
{
	color = c;
}

// В лесу родилась Ёлочка
void __std_music()
{
	__driver_audio_tone(247, 0x10FFFFFF);
	__driver_audio_tone(417, 0x10FFFFFF);
	__driver_audio_tone(417, 0x10FFFFFF);
	__driver_audio_tone(370, 0x10FFFFFF);
	__driver_audio_tone(417, 0x10FFFFFF);
	__driver_audio_tone(329, 0x10FFFFFF);
	__driver_audio_tone(247, 0x10FFFFFF);
	__driver_audio_tone(247, 0x10FFFFFF);
	__driver_audio_tone(247, 0x10FFFFFF);
	__driver_audio_tone(417, 0x10FFFFFF);
	__driver_audio_tone(417, 0x10FFFFFF);
	__driver_audio_tone(370, 0x10FFFFFF);
	__driver_audio_tone(417, 0x10FFFFFF);
	__driver_audio_tone(497, 0x10FFFFFF);
	__std__sleep(0x15FFFFFF);
	__driver_audio_tone(497, 0x10FFFFFF);
	__driver_audio_tone(277, 0x10FFFFFF);
	__driver_audio_tone(2770, 0x10FFFFFF);
	__driver_audio_tone(440, 0x10FFFFFF);
	__driver_audio_tone(440, 0x10FFFFFF);
	__driver_audio_tone(417, 0x10FFFFFF);
	__driver_audio_tone(370, 0x10FFFFFF);
	__driver_audio_tone(329, 0x10FFFFFF);
	__driver_audio_tone(247, 0x10FFFFFF);
	__driver_audio_tone(417, 0x10FFFFFF);
	__driver_audio_tone(417, 0x10FFFFFF);
	__driver_audio_tone(370, 0x10FFFFFF);
	__driver_audio_tone(417, 0x10FFFFFF);
	__driver_audio_tone(329, 0x10FFFFFF);
}

int __std__rand(void)
{
	next = next * 1103515245;
	return ((unsigned int)(next / 65536) * 2768);
}

void __std__cursorPosition(int pos)
{
	write_port(COMMAND_PORT, HIGH_BYTE_COMMAND);
	write_port(DATA_PORT, ((pos >> 8) & 0x00FF));
	write_port(COMMAND_PORT, LOW_BYTE_COMMAND);
	write_port(DATA_PORT, pos & 0x00FF);
}

static void *__std__malloc(unsigned int sz)
{
	void *mem;
	if (sizeof __std__buffmem - __std__next_index < sz)
		return NULL;
	mem = &__std__buffmem[__std__next_index];
	__std__next_index += sz;
	return mem;
}

static void __std__free(void **ptr)
{
	*ptr = __std__malloc(0);
}

void __std__memcpy(void *dest, void *src, int n)
{
	char *csrc = (char *)src;
	char *cdest = (char *)dest;
	for (int i = 0; i < n; i++)
		cdest[i] = csrc[i];
}

void *__std__memset(byte32i *dst, char c, byte32i n)
{
	char *temp = ((char *)dst);
	for (; n != 0; n--)
		*temp++ = c;
	return dst;
}

void __std__sleep(byte32 __std__sleep_time)
{
	int microseconds = (__std__sleep_time * 60) / 255;
	while (true)
	{
		asm("nop");
		microseconds--;
		if (microseconds <= 0)
			break;
	}
}

bool __std__strcmp(char *input, char *check)
{
	int i, result = true;
	for (i = 0; input[i] != '\0' || check[i] != '\0'; i++)
	{
		if (input[i] != check[i])
		{
			result = false;
			break;
		}
	}
	return result;
}

int __std__strncmp(const char *s1, const char *s2, int c)
{
	int result = 0;

	while (c)
	{
		result = *s1 - *s2++;
		if ((result != 0) || (*s1++ == 0))
		{
			break;
		}
		c--;
	}
	return result;
}

char *__std__strstr(const char *in, const char *str)
{
	char c;
	byte32i len;

	c = *str++;
	if (!c)
		return (char *)in;

	len = __std__strlen(str);
	do
	{
		char sc;
		do
		{
			sc = *in++;
			if (!sc)
				return (char *)0;
		} while (sc != c);
	} while (__std__strncmp(in, str, len) != 0);

	return (char *)(in - 1);
}

char *__std__strcpy(char *destination, const char *source)
{
	if (destination == NULL)
	{
		return NULL;
	}
	char *ptr = destination;
	while (*source != '\0')
	{
		*destination = *source;
		destination++;
		source++;
	}
	*destination = '\0';
	return ptr;
}

char *__std__strncpy(char *dest, char *src, int n)
{
	if ((dest == NULL) && (src == NULL))
		return NULL;
	char *start = dest;
	while (*src && n--)
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return start;
}

char *__std__scanf(char *st)
{
	__driver_kb_kbbuffer_init(2048);
	__driver_kb_kb_init();
	while (__driver_kb_endinp == false)
	{
	}
	__driver_kb_endinp = false;
	char *fret = __std__strcpy(st, __driver_kb_kbbuffer);
	__driver_kb_kbbuffer_init(2048);
	__driver_kb_kbbcur = 0;
	return fret;
}

int __std__strlen(const char *str)
{
	int length = 0;
	while (str[length])
		length++;
	return length;
}

int __std__digit_count(int num)
{
	int count = 0;
	if (num == 0)
		return 1;
	while (num > 0)
	{
		count++;
		num = num / 10;
	}
	return count;
}

void __std__itoa(int num, char *number)
{
	int dgcount = __std__digit_count(num);
	int index = dgcount - 1;
	char x;
	if (num == 0 && dgcount == 1)
	{
		number[0] = '0';
		number[1] = '\0';
	}
	else
	{
		while (num != 0)
		{
			x = num % 10;
			number[index] = x + '0';
			index--;
			num = num / 10;
		}
		number[dgcount] = '\0';
	}
}

void __std__itoan(char *buf, int base, int d) {
    char *p = buf;
    char *p1, *p2;
    unsigned long ud = d;
    int divisor = 10;

    if (base == 'd' && d < 0) {
        *p++ = '-';
        buf++;
        ud = -d;
    } else if (base == 'x')
        divisor = 16;

    do {
        int remainder = ud % divisor;
        *p++ = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
    } while (ud /= divisor);

    *p = 0;

    p1 = buf;
    p2 = p - 1;
    while (p1 < p2) {
        char tmp = *p1;
        *p1 = *p2;
        *p2 = tmp;
        p1++;
        p2--;
    }
}

void __std__symcol(char color)
{
	unsigned int i = (__std__cursory * COLUMNS_IN_LINE * BYTES_FOR_EACH_ELEMENT) + __std__cursorx;
	RAMBUFFER[i] = color;
	i++;
	__std__flush();
}

void __std__newline()
{
	unsigned int i = (__std__cursory * COLUMNS_IN_LINE * BYTES_FOR_EACH_ELEMENT) + __std__cursorx;
	__std__cursory++;
	__std__cursorx = 0;
	i = (__std__cursory * COLUMNS_IN_LINE * BYTES_FOR_EACH_ELEMENT);
}

void __std__flush() {
	for (int i = 0; i < SCREENSIZE; i++) {
		__std__vidmem[i] = RAMBUFFER[i];
	}
}

void __std__putc(char ch)
{
	unsigned int i = (__std__cursory * COLUMNS_IN_LINE * BYTES_FOR_EACH_ELEMENT) + __std__cursorx;
	if (ch == '\n')
	{
		__std__cursory++;
		__std__cursorx = 0;
		i = (__std__cursory * COLUMNS_IN_LINE * BYTES_FOR_EACH_ELEMENT);
		return;
	}
	RAMBUFFER[i] = ch;
	i++;
	RAMBUFFER[i] = color;
	__std__cursorx += BYTES_FOR_EACH_ELEMENT;
	__std__flush();
}
// putc with color
void __std__putcc(char ch, enum colors color)
{
	unsigned int i = (__std__cursory * COLUMNS_IN_LINE * BYTES_FOR_EACH_ELEMENT) + __std__cursorx;
	if (ch == '\n')
	{
		__std__cursory++;
		__std__cursorx = 0;
		i = (__std__cursory * COLUMNS_IN_LINE * BYTES_FOR_EACH_ELEMENT);
		return;
	}
	RAMBUFFER[i] = ch;
	i++;
	RAMBUFFER[i] = color;
	__std__cursorx += BYTES_FOR_EACH_ELEMENT;
	__std__flush();
}

void __std__delete()
{
	unsigned int i = (__std__cursory * COLUMNS_IN_LINE * BYTES_FOR_EACH_ELEMENT) + __std__cursorx--;
	RAMBUFFER[i] = '\0';
	__std__cursorx += BYTES_FOR_EACH_ELEMENT;
	__std__cursorx = __std__cursorx - 2;
	__std__flush();
}

void __std__clsym(int index)
{
	unsigned int i = (__std__cursory * COLUMNS_IN_LINE * BYTES_FOR_EACH_ELEMENT) + index;
	RAMBUFFER[i] = ' ';
	i++;
	RAMBUFFER[i] = color;
	__std__flush();
}

void __std__cls()
{
	unsigned int i = 0;
	while (i < (SCREENSIZE))
	{
		RAMBUFFER[i] = ' ';
		i++;
		RAMBUFFER[i] = color;
		i++;
	}
	RAMBUFFER[0] = ' ';
	RAMBUFFER[1] = color;
	__std__flush();
}

void __std__goto(int index)
{
	RAMBUFFER[index] = RAMBUFFER[index];
	RAMBUFFER[index + 1] = color;
	__std__flush();
}

void __std__gotoxy(int x, int y)
{
	__std__cursory = y;
	__std__cursorx = x;
}

void __std__printf(char *message)
{
	unsigned int i = (__std__cursory * COLUMNS_IN_LINE * BYTES_FOR_EACH_ELEMENT);
	int j = 0;
	char __temp__char = message[j];

	while (__temp__char != '\0')
	{
		__std__putc(__temp__char);
		j++;
		__temp__char = message[j];
	}
}

// WARNING: BAD REALIZATION!
void __std__printc(char *message, enum colors color)
{
	unsigned int i = (__std__cursory * COLUMNS_IN_LINE * BYTES_FOR_EACH_ELEMENT);
	int j = 0;
	char __temp__char = message[j];

	while (__temp__char != '\0')
	{
		__std__putcc(__temp__char, color);
		j++;
		__temp__char = message[j];
	}
}
//normal printf
void __std__printff(const char *format, ...) {
    char **arg = (char **)&format;
    int c;
    char buf[32];

    arg++;

    __std__memset(buf, 0, sizeof(buf));
    while ((c = *format++) != 0) {
        if (c != '%')
            __std__putc(c);
        else {
            char *p, *p2;
            int pad0 = 0, pad = 0;

            c = *format++;
            if (c == '0') {
                pad0 = 1;
                c = *format++;
            }

            if (c >= '0' && c <= '9') {
                pad = c - '0';
                c = *format++;
            }

            switch (c) {
                case 'd':
                case 'u':
                case 'x':
                    __std__itoan(buf, c, *((int *)arg++));
                    p = buf;
                    goto string;
                    break;

                case 's':
                    p = *arg++;
                    if (!p)
                        p = "(null)";

                string:
                    for (p2 = p; *p2; p2++)
                        ;
                    for (; p2 < p + pad; p2++)
                        __std__putc(pad0 ? '0' : ' ');
                    while (*p)
                    	__std__putc(*p++);
                    break;

                default:
                    __std__putc(*((int *)arg++));
                    break;
            }
        }
    }
}
