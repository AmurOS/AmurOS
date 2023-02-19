char *__std__vidmem = (char *)0xb8000;
static byte __std__buffmem[1024 * 1024];
static int __std__next_index = 0;
// colors
enum colors
{
	// black background
	BLACK = 0x00,
	BLUE = 0x01,
	GREEN = 0x02,
	AQUA = 0x03,
	RED = 0x04,
	PURPLE = 0x05,
	YELLOW = 0x06,
	WHITE = 0x07,
	GREY = 0x08,
	BLUE1 = 0x09,
	GREEN1 = 0x0A,
	AQUA1 = 0x0B,
	RED1 = 0x0C,
	PURPLE1 = 0x0D,
	YELLOW1 = 0x0E,
	WHITE1 = 0x0F,
	// blue background
	BLACK01 = 0x10,
	BLUE01 = 0x11,
	GREEN01 = 0x12,
	AQUA01 = 0x13,
	RED01 = 0x14,
	PURPLE01 = 0x15,
	YELLOW01 = 0x16,
	WHITE01 = 0x17,
	GREY01 = 0x18,
	BLUE02 = 0x19,
	GREEN02 = 0x1A,
	AQUA02 = 0x1B,
	RED02 = 0x1C,
	PURPLE02 = 0x1D,
	YELLOW02 = 0x1E,
	WHITE02 = 0x1F,
	// green background
	BLACK11 = 0x20,
	BLUE11 = 0x21,
	GREEN11 = 0x22,
	AQUA11 = 0x23,
	RED11 = 0x24,
	PURPLE11 = 0x25,
	YELLOW11 = 0x26,
	WHITE11 = 0x27,
	GREY11 = 0x28,
	BLUE12 = 0x29,
	GREEN12 = 0x2A,
	AQUA12 = 0x2B,
	RED12 = 0x2C,
	PURPLE12 = 0x2D,
	YELLOW12 = 0x2E,
	WHITE12 = 0x2F,
	// aqua background
	BLACK21 = 0x30,
	BLUE21 = 0x31,
	GREEN21 = 0x32,
	AQUA21 = 0x33,
	RED21 = 0x34,
	PURPLE21 = 0x35,
	YELLOW21 = 0x36,
	WHITE21 = 0x37,
	GREY21 = 0x38,
	BLUE22 = 0x39,
	GREEN22 = 0x3A,
	AQUA22 = 0x3B,
	RED22 = 0x3C,
	PURPLE22 = 0x3D,
	YELLOW22 = 0x3E,
	WHITE22 = 0x3F,
	// red background
	BLACK31 = 0x40,
	BLUE31 = 0x41,
	GREEN31 = 0x42,
	AQUA31 = 0x43,
	RED31 = 0x44,
	PURPLE31 = 0x45,
	YELLOW31 = 0x46,
	WHITE31 = 0x47,
	GREY31 = 0x48,
	BLUE32 = 0x49,
	GREEN32 = 0x4A,
	AQUA32 = 0x4B,
	RED32 = 0x4C,
	PURPLE32 = 0x4D,
	YELLOW32 = 0x4E,
	WHITE32 = 0x4F,
	// purple background
	BLACK41 = 0x50,
	BLUE41 = 0x51,
	GREEN41 = 0x52,
	AQUA41 = 0x53,
	RED41 = 0x54,
	PURPLE41 = 0x55,
	YELLOW41 = 0x56,
	WHITE41 = 0x57,
	GREY41 = 0x58,
	BLUE42 = 0x59,
	GREEN42 = 0x5A,
	AQUA42 = 0x5B,
	RED42 = 0x5C,
	PURPLE42 = 0x5D,
	YELLOW42 = 0x5E,
	WHITE42 = 0x5F,
	// yellow background
	BLACK51 = 0x60,
	BLUE051 = 0x61,
	GREEN51 = 0x62,
	AQUA51 = 0x63,
	RED51 = 0x64,
	PURPLE51 = 0x65,
	YELLOW51 = 0x66,
	WHITE51 = 0x67,
	GREY51 = 0x68,
	BLUE52 = 0x69,
	GREEN52 = 0x6A,
	AQUA52 = 0x6B,
	RED52 = 0x6C,
	PURPLE52 = 0x6D,
	YELLOW52 = 0x6E,
	WHITE52 = 0x6F,
	// white background
	BLACK61 = 0x70,
	BLUE61 = 0x71,
	GREEN61 = 0x72,
	AQUA61 = 0x73,
	RED61 = 0x74,
	PURPLE61 = 0x75,
	YELLOW61 = 0x76,
	WHITE61 = 0x77,
	GREY61 = 0x78,
	BLUE62 = 0x79,
	GREEN62 = 0x7A,
	AQUA62 = 0x7B,
	RED62 = 0x7C,
	PURPLE62 = 0x7D,
	YELLOW62 = 0x7E,
	WHITE62 = 0x7F,
	// gray background
	BLACK71 = 0x80,
	BLUE71 = 0x18,
	GREEN71 = 0x82,
	AQUA71 = 0x83,
	RED71 = 0x84,
	PURPLE71 = 0x85,
	YELLOW71 = 0x86,
	WHITE71 = 0x87,
	GREY71 = 0x88,
	BLUE72 = 0x89,
	GREEN72 = 0x8A,
	AQUA72 = 0x8B,
	RED72 = 0x8C,
	PURPLE72 = 0x8D,
	YELLOW72 = 0x8E,
	WHITE72 = 0x8F,
	// blue1 background
	BLACK81 = 0x90,
	BLUE81 = 0x91,
	GREEN81 = 0x92,
	AQUA81 = 0x93,
	RED81 = 0x94,
	PURPLE81 = 0x95,
	YELLOW81 = 0x96,
	WHITE81 = 0x97,
	GREY81 = 0x98,
	BLUE82 = 0x99,
	GREEN82 = 0x9A,
	AQUA82 = 0x9B,
	RED82 = 0x9C,
	PURPLE82 = 0x9D,
	YELLOW82 = 0x9E,
	WHITE82 = 0x9F,
	// green1 background
	BLACK91 = 0xA0,
	BLUE91 = 0xA1,
	GREEN91 = 0xA2,
	AQUA91 = 0xA3,
	RED91 = 0xA4,
	PURPLE91 = 0xA5,
	YELLOW91 = 0xA6,
	WHITE91 = 0xA7,
	GREY91 = 0xA8,
	BLUE92 = 0xA9,
	GREEN92 = 0xAA,
	AQUA92 = 0xAB,
	RED92 = 0xAC,
	PURPLE92 = 0xAD,
	YELLOW92 = 0xAE,
	WHITE92 = 0xAF,
	// aqua1 background
	BLACKA1 = 0xB0,
	BLUEA1 = 0xB1,
	GREENA1 = 0xB2,
	AQUAA1 = 0xB3,
	REDA1 = 0xB4,
	PURPLEA1 = 0xB5,
	YELLOWA1 = 0xB6,
	WHITEA1 = 0xB7,
	GREYA1 = 0xB8,
	BLUEA2 = 0xB9,
	GREENA2 = 0xBA,
	AQUAA2 = 0xBB,
	REDA2 = 0xBC,
	PURPLEA2 = 0xBD,
	YELLOWA2 = 0xBE,
	WHITEA2 = 0xBF,
	// red1 background
	BLACKB1 = 0xC0,
	BLUEB1 = 0xC1,
	GREENB1 = 0xC2,
	AQUAB1 = 0xC3,
	REDB1 = 0xC4,
	PURPLEB1 = 0xC5,
	YELLOWB1 = 0xC6,
	WHITEB1 = 0xC7,
	GREYB1 = 0xC8,
	BLUEB2 = 0xC9,
	GREENB2 = 0xCA,
	AQUAB2 = 0xB,
	REDB2 = 0xCC,
	PURPLEB2 = 0xCD,
	YELLOWB2 = 0xCE,
	WHITEB2 = 0xCF,
	// purple1 background
	BLACKC1 = 0xD0,
	BLUEC1 = 0xD1,
	GREENC1 = 0xD2,
	AQUAC1 = 0xD3,
	REDC1 = 0xD4,
	PURPLEC1 = 0xD5,
	YELLOWC1 = 0xD6,
	WHITEC1 = 0xD7,
	GREYC1 = 0xD8,
	BLUEC2 = 0xD9,
	GREENC2 = 0xDA,
	AQUAC2 = 0xDB,
	REDC2 = 0xDC,
	PURPLEC2 = 0xDD,
	YELLOWC2 = 0xDE,
	WHITEC2 = 0xDF,
	// yellow1 background
	BLACKD1 = 0xE0,
	BLUED1 = 0xE1,
	GREEND1 = 0xE2,
	AQUAD1 = 0xE3,
	REDD1 = 0xE4,
	PURPLED1 = 0xE5,
	YELLOWD1 = 0xE6,
	WHITED1 = 0xE7,
	GREYD1 = 0xE8,
	BLUED2 = 0xE9,
	GREEND2 = 0xEA,
	AQUAD2 = 0xEB,
	REDD2 = 0xEC,
	PURPLED2 = 0xED,
	YELLOWD2 = 0xEE,
	WHITED2 = 0xEF,
	// white1 background
	BLACKE1 = 0xF0,
	BLUEE1 = 0xF1,
	GREENE1 = 0xF2,
	AQUAE1 = 0xF3,
	REDE1 = 0xF4,
	PURPLEE1 = 0xF5,
	YELLOWE1 = 0xF6,
	WHITEE1 = 0xF7,
	GREYE1 = 0xF8,
	BLUEE2 = 0xF9,
	GREENE2 = 0xFA,
	AQUAE2 = 0xFB,
	REDE2 = 0xFC,
	PURPLEE2 = 0xFD,
	YELLOWE2 = 0xFE,
	WHITEE2 = 0xFF
};
enum colors color = 7;

enum colors __std__color(enum colors c)
{
	color = c;
}
static void *__std__malloc(int sz)
{
	void *mem;
	if (sizeof __std__buffmem - __std__next_index < sz)
		return NULL;
	mem = &__std__buffmem[__std__next_index];
	__std__next_index += sz;
	return mem;
}

void __std__memcpy(void *dest, void *src, int n)
{
	char *csrc = (char *)src;
	char *cdest = (char *)dest;
	for (int i = 0; i < n; i++)
		cdest[i] = csrc[i];
}

void *__std__memset(uint32 *dst, char c, uint32 n)
{
	char *temp = ((char *)dst);
	for (; n != 0; n--)
		*temp++ = c;
	return dst;
}

void __std__sleep(byte32 __std__sleep_time)
{
	while (true)
	{
		asm("nop");
		__std__sleep_time--;
		if (__std__sleep_time <= 0)
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
	uint32 len;

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

void __std__symcol(char color)
{
	unsigned int i = (__std__cursory * COLUMNS_IN_LINE * BYTES_FOR_EACH_ELEMENT) + __std__cursorx;
	__std__vidmem[i] = color;
	i++;
}

void __std__newline()
{
	__std__cursory++;
	__std__cursorx = 0;
}

void __std__putc(char ch)
{
	unsigned int i = (__std__cursory * COLUMNS_IN_LINE * BYTES_FOR_EACH_ELEMENT) + __std__cursorx;
	if (ch == '\n')
	{
		__std__cursory++;
		return;
	}
	__std__vidmem[i] = ch;
	i++;
	__std__vidmem[i] = color;
	__std__cursorx += BYTES_FOR_EACH_ELEMENT;
}

void __std__clsym(int index)
{
	unsigned int i = (__std__cursory * COLUMNS_IN_LINE * BYTES_FOR_EACH_ELEMENT) + index;
	__std__vidmem[i] = ' ';
	i++;
	__std__vidmem[i] = color;
}

void __std__cls()
{
	unsigned int i = 0;
	while (i < (SCREENSIZE))
	{
		__std__vidmem[i] = ' ';
		i++;
		__std__vidmem[i] = color;
		i++;
	}
	__std__vidmem[0] = ' ';
	__std__vidmem[1] = color;
}

void __std__goto(int index)
{
	__std__vidmem[index] = __std__vidmem[index];
	__std__vidmem[index + 1] = color;
}

void __std__gotoxy(int x, int y)
{
	__std__cursory = y;
	__std__cursorx = x;
}

void __std__printf(char *message)
{
	unsigned int i = (__std__cursory * COLUMNS_IN_LINE * BYTES_FOR_EACH_ELEMENT);

	while (*message != 0)
	{
		if (*message == '\n')
		{
			__std__cursory++;
			i = (__std__cursory * COLUMNS_IN_LINE * BYTES_FOR_EACH_ELEMENT);
			*message++;
			//__std__cursory++;
		}
		else
		{
			__std__vidmem[i] = *message;
			*message++;
			i++;

			__std__vidmem[i] = color;
			i++;
			__std__cursorx += BYTES_FOR_EACH_ELEMENT;
		}
	}
}

void __std__printc(char *message, enum colors color)
{
	unsigned int i = (__std__cursory * COLUMNS_IN_LINE * BYTES_FOR_EACH_ELEMENT);

	while (*message != 0)
	{
		if (*message == '\n')
		{
			__std__cursory++;
			i = (__std__cursory * COLUMNS_IN_LINE * BYTES_FOR_EACH_ELEMENT);
			*message++;
			//__std__cursory++;
		}
		else
		{
			__std__vidmem[i] = *message;
			*message++;
			i++;
			__std__vidmem[i] = color;
			i++;
			__std__cursorx += BYTES_FOR_EACH_ELEMENT;
		}
	}
}

