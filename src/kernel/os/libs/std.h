#define MAX_WORDS 1000
#define MAX_WORD_LEN 1000

//extern char *__std__vidmem;
extern int __std__strlen(const char *str);
//extern byte __std__buffmem;
//extern int __std__next_index;
//extern unsigned long int next;
static byte __malloc__buffmem[1024 * 1024];
static int __malloc__next_index = 0;
static void *malloc(unsigned int sz)
{
	void *mem;
	if (sizeof __malloc__buffmem - __malloc__next_index < sz)
		return NULL;
	mem = &__malloc__buffmem[__malloc__next_index];
	__malloc__next_index += sz;
	return mem;
}

//__std__malloc(0);
extern void __std__free(void **ptr);
extern enum colors color;
extern enum colors __std__color(enum colors c);
extern void __std_music();
extern int __std__rand(void);
extern void __std__srand(unsigned int seed);
extern int __std__rand_r(unsigned int *seed);
extern unsigned int __std__time(unsigned int *t);
extern void __std__cursorPosition(int pos);
extern void __std__cursorPos(byte x, byte y);
//extern void *__std__malloc(unsigned int sz);
//extern void __std__free(void **ptr);
extern void __std__memcpy(void *dest, void *src, int n);
extern void *__std__memset(byte32i *dst, char c, byte32i n);
extern void __std__sleep(byte32 ms);
extern void __std__nop_delay(byte32 cycles);
extern void __std__wait(byte32 us);
extern bool __std__strcmp(char *input, char *check);
extern int __std__strncmp(const char *s1, const char *s2, int c);
extern void __std__strcat(char *dest, const char *src);
extern char *__std__strchr(const char *str, int c);
extern char *__std__strtok(char *str, const char *delim);
extern char *__std__strstr(const char *in, const char *str);
extern void *__std__realloc(void *ptr, int size);
extern char *__std__strcpy(char *destination, const char *source);
extern char *__std__strncpy(char *dest, char *src, int n);
extern char *__std__scanf(char *st);
extern int __std__strlen(const char *str);
extern char** __std__strsplit(char* str, const char* tok);
extern void __std__toLowerCase(char str[]);
extern int __std__digit_count(int num);
extern void __std__itoa(int num, char *number);
extern void __std__itoan(char *buf, int base, int d);
extern void __std__symcol(char color);
extern void __std__newline();
extern void __std__putc(char ch);
extern void __std__putcc(char ch, enum colors color);
extern void __std__delete();
extern void __std__clsym(int index);
extern void __std__cls();
extern void __std__goto(int index);
extern void __std__gotoxy(int x, int y);
extern void __std__printf(char *message);
extern void __std__printc(char *message, enum colors color);
extern void __std__printff(const char *format, ...);