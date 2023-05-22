#define MEGABYTE(n) n*1048576

static int __fs_fpointer = 1;
static char *__fs_ramdisk = "";
dict_t **__fs_files;

char *malloc_ptr;
void *newmalloc(int size)
{
  void *ret;
  ret = (void*)malloc_ptr;
  malloc_ptr += size;
  return ret;
}

void __fs_initdisk() {
	__fs_files = dictAlloc();
	__fs_ramdisk = (char *)newmalloc(MEGABYTE(256));
	__fs_ramdisk[0] = 0;
}

char *__fs_reads(int start, int size) {
	char *mem = (char*)newmalloc(size);
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
	byte32i usize = (unsigned)size;
	__fs_writes(__fs_fpointer, 4, (byte*)&usize);
	__fs_writes(__fs_fpointer+4, size, mem);
}

void __fs_writefile(char *name, int size, byte *mem) {
	if (getItem(__fs_files, name) == -1) {
		__fs_newfile(name, size, mem);
	}
	byte32i usize = (unsigned)size;
	int offset = (int)getItem(__fs_files, name);
	__fs_writes(offset, 4, (byte*)&usize);
	__fs_writes(offset+4, size, mem);
}

char *__fs_readfile(char *name) {
	int val = (int)getItem(__fs_files, name);
	//if (val == 0)
	//	return "Error";
	byte *size = __fs_reads(val, 4);
	byte *nsize = btarrev(size);
	return __fs_reads(val+4, b8ati(size));
}
