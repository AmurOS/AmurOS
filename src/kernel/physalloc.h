#define PAGE_SIZE 0x1000		// 4kb fuer eine Seite
#define TOTAL_MEMORY 32			// RAM in MB

#define PHYSALLOC_STACKORIGIN	 0x402000		// hier befindet sich der kalloc stack

byte32i *stackp=(byte32i *)PHYSALLOC_STACKORIGIN;
byte32i freepages=0;

void *phys_alloc() {
	stackp-=sizeof(byte32i);
	byte32i addr=*stackp;
	freepages--;
	return addr;
}

void phys_free(byte32i addr) {
	*stackp=addr;
	stackp+=sizeof(byte32i);
	freepages++;
}