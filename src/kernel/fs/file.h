#define		SEEK_SET 			0
#define		SEEK_CUR 			1
#define		SEEK_END 			2
#define		TMP_MAX 			238328

#define P_tmpdir	"/temp/"

#ifndef _HAVE_OFF_T
#define _HAVE_OFF_T
typedef long int off_t;
#endif

/** This is the internal structure definition for a FILE*
 * stream.
 */
typedef struct
{
	int fd;				///< File descriptor. 
	void *data;			///< Data allocated by the OS.
	int eof;			///< EOF indicator for the stream.
	int error;			///< Error indicator for the stream.
	int cnt;
	int bufsiz;
	unsigned int mode;	///< The fcntl.h mode that the file was opened in.
	void* base;
	char* file;
	void *ptr;
} FILE;


typedef struct
{
  unsigned int __pos;
  unsigned int __state;
} fpos_t;

int open_filehandles=0;

FILE *fopen(char *path, char *mode) {
FILE *f=(FILE*) kalloc(sizeof(FILE));

	if ((__std__strcmp(mode, "r")==0) || (__std__strcmp(mode, "r+")==0) || (__std__strcmp(mode, "rb")==0)) {
		struct __fat32_dir_entry *entry = (struct __fat32_dir_entry*) kalloc(DIR_ENTRY_SIZE);
		fat32_find_file(path, entry);
		
		open_filehandles++;
		f->file=open_filehandles;
		f->bufsiz=entry->filesize;
		f->ptr=(char*) kalloc(entry->filesize+512);
		f->base=f->ptr;
		f->cnt=0;
		
		fat32_read_file(entry, f->ptr);
		
		return f;
	} else {
		return 0;	
	}

}

int fclose(FILE *f) {
	open_filehandles--;
	kfree(f->ptr);
	kfree(f);
}

unsigned int fread( void *ptr, unsigned int size, unsigned int nmemb, FILE *stream) {
	__std__memcpy(ptr, stream->ptr, size*nmemb);
	
	return (size*nmemb);
} 

int fseek(FILE *stream, long offset, int whence) {

	if (whence == SEEK_SET) {
		stream->ptr = stream->base + offset;
		stream->cnt = offset;	
	}
	
	if (whence == SEEK_CUR) {
		stream->ptr += offset;
		stream->cnt += offset;
	}
		
	if (whence == SEEK_END) {
		stream->ptr = stream->base + stream->bufsiz + offset;
		stream->cnt = stream->bufsiz + offset;
	}
	
	return 0;	
}

long ftell(FILE *stream) {
	return stream->cnt;	
}