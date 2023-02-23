char *__std__vidmem = (char *)0xb8000;

int __std__strlen(const char *str);

static byte __std__buffmem[1024 * 1024];
static int __std__next_index = 0;
unsigned long int next = 1;
enum colors color = 7;

enum colors __std__color(enum colors c)
{
	color = c;
}

int __std__rand(void)
{
  next = next * 1103515245;
  return((unsigned int)(next / 65536) * 2768);
}

void __std__cursorPosition(int pos)
{
	write_port(COMMAND_PORT, HIGH_BYTE_COMMAND);
	write_port(DATA_PORT, ((pos >> 8) & 0x00FF));
	write_port(COMMAND_PORT, LOW_BYTE_COMMAND);
	write_port(DATA_PORT, pos & 0x00FF);
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

void __std__symcol(char color)
{
	unsigned int i = (__std__cursory * COLUMNS_IN_LINE * BYTES_FOR_EACH_ELEMENT) + __std__cursorx;
	__std__vidmem[i] = color;
	i++;
}

void __std__newline()
{
	unsigned int i = (__std__cursory * COLUMNS_IN_LINE * BYTES_FOR_EACH_ELEMENT) + __std__cursorx;
	__std__cursory++;
	__std__cursorx = 0;
	i = (__std__cursory * COLUMNS_IN_LINE * BYTES_FOR_EACH_ELEMENT);
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
	__std__vidmem[i] = ch;
	i++;
	__std__vidmem[i] = color;
	__std__cursorx += BYTES_FOR_EACH_ELEMENT;
}

void __std__delete()
{
	unsigned int i = (__std__cursory * COLUMNS_IN_LINE * BYTES_FOR_EACH_ELEMENT) + __std__cursorx--;
	__std__vidmem[i] = '\0';
	__std__cursorx += BYTES_FOR_EACH_ELEMENT;
	__std__cursorx = __std__cursorx-2;
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
