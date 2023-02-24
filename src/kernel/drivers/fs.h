#define MEGABYTE(n) n*1048576

volatile int __fs_fpointer = 0;
volatile char *__fs_ramdisk = "";
dict_t **__fs_files;

void __fs_initdisk() {
	__fs_files = dictAlloc();
	__fs_ramdisk = (char *)__std__malloc(MEGABYTE(256));
}

char *__fs_reads(int start, int size) {
	char *mem = (char*)__std__malloc(size);
	for (int i = 0; i < size; i++) {
		mem[i] = __fs_ramdisk[start+i];
	}
	return mem;
}

void __fs_writes(int start, int size, byte *mem) {
	for (int i = 0; i < size; i++) {
		__fs_ramdisk[start+i] = mem[i];
	}
}

void __fs_newfile(char *name, int size, byte *mem) {
	addItem(__fs_files, name, __fs_fpointer);
	__fs_writes(__fs_fpointer, size, mem);
}

void __fs_writefile(char *name, int size, byte *mem) {
	if (getItem(__fs_files, name) == NULL) {
		__fs_newfile(name, size, mem);
	}
	__fs_writes((int)getItem(__fs_files, name), size, mem);
}

char *__fs_readfile(char *name, int size) {
	int offset = (int)getItem(__fs_files, name);
	return __fs_reads(offset, size);
}