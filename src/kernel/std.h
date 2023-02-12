char *__std__vidmem = (char *) 0xb8000;
static byte __std__buffmem[1024 * 1024];
static int __std__next_index = 0;
static void *__std__malloc(int sz) {
    void *mem;
    if(sizeof __std__buffmem - __std__next_index < sz)
        return NULL;
    mem = &__std__buffmem[__std__next_index];
    __std__next_index += sz;
    return mem;
}

char* __std__strcpy(char* destination, const char* source) {
    if (destination == NULL) {
        return NULL;
    }
    char *ptr = destination;
    while (*source != '\0') {
        *destination = *source;
        destination++;
        source++;
    }
    *destination = '\0';
    return ptr;
}

char *__std__scanf(char *st) {
	__driver_kb_kbbuffer_init(2048);
	__driver_kb_kb_init();
	while(__driver_kb_endinp == false) {}
	__driver_kb_endinp = false;
	char *fret = __std__strcpy(st, __driver_kb_kbbuffer);
	__driver_kb_kbbuffer_init(2048);
	__driver_kb_kbbcur = 0;
	return fret;
}

int __std__strlen(const char* str) {
	int length = 0;
	while(str[length])
		length++;
	return length;
}

int __std__digit_count(int num) {
	int count = 0;
	if(num == 0)
		return 1;
	while(num > 0) {
		count++;
		num = num/10;
	}
	return count;
}

void __std__itoa(int num, char *number) {
	int dgcount = __std__digit_count(num);
	int index = dgcount - 1;
	char x;
	if(num == 0 && dgcount == 1) {
		number[0] = '0';
		number[1] = '\0';
	} else {
		while(num != 0) {
			x = num % 10;
			number[index] = x + '0';
		    index--;
			num = num / 10;
		}
		number[dgcount] = '\0';
	}
}

void __std__symcol(char color) {
	unsigned int i=(__std__cursory*COLUMNS_IN_LINE*BYTES_FOR_EACH_ELEMENT)+__std__cursorx;
	__std__vidmem[i]=color;
	i++;
}

void __std__newline() {
	__std__cursory++;
	__std__cursorx = 0;
}

void __std__putc(char ch) {
	unsigned int i=(__std__cursory*COLUMNS_IN_LINE*BYTES_FOR_EACH_ELEMENT)+__std__cursorx;
	if (ch == '\n') {
		__std__cursory++;
		return;
	}
	__std__vidmem[i]=ch;
	i++;
	__std__vidmem[i]=WHITE_TXT;
	__std__cursorx += BYTES_FOR_EACH_ELEMENT;
}

void __std__clsym(int index) {
	unsigned int i=(__std__cursory*COLUMNS_IN_LINE*BYTES_FOR_EACH_ELEMENT)+index;
	__std__vidmem[i]=' ';
	i++;
	__std__vidmem[i]=WHITE_TXT;
}

void __std__cls() {
	unsigned int i=0;
	while(i < (SCREENSIZE)) {
		__std__vidmem[i]=' ';
		i++;
		__std__vidmem[i]=WHITE_TXT;
		i++;
	}
	__std__vidmem[0]=' ';
	__std__vidmem[1]=WHITE_TXT;
}

void __std__printf(char *message) {
	unsigned int i=(__std__cursory*COLUMNS_IN_LINE*BYTES_FOR_EACH_ELEMENT);

	while(*message!=0) {
		if(*message=='\n') {
			__std__cursory++;
			i=(__std__cursory*COLUMNS_IN_LINE*BYTES_FOR_EACH_ELEMENT);
			*message++;
			__std__cursory++;
		} else {
			__std__vidmem[i]=*message;
			*message++;
			i++;
			__std__vidmem[i]=WHITE_TXT;
			i++;
			__std__cursorx += BYTES_FOR_EACH_ELEMENT;
		}
	}
}