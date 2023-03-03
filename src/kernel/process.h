#define MAXPROCESSES 100

volatile int __processes_pointer = 0;

typedef struct process{
	int id;
	void (*offset)();
} process;

volatile process __processes[MAXPROCESSES];

void __process_pop() {
	if (__processes_pointer-1 <= 0)
		return;
	__processes_pointer--;
	__processes[__processes_pointer] = (process){NULL};
}

void __process_push(process prcs) {
	if (__processes_pointer+1 >= MAXPROCESSES)
		return;
	__processes_pointer++;
	prcs.id = __processes_pointer;
	__processes[__processes_pointer] = prcs;
}

void __start_process(int i) {
	if (__processes[i].id != NULL)
		__processes[i].offset();
}

void __start_processes() {
	for (;;) {
		for (int i = 2; i < MAXPROCESSES; i++) {
			if (__processes[i].id != NULL)
				__processes[i].offset();
		}
	}
}