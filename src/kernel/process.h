/*#define MAXPROCESSES 100

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
*/
#define MAX_PROCESSES 100

typedef struct {
    int process_id;
    int is_running;
	void (*offset)();
} Process;

Process processes[MAX_PROCESSES];

int next_process_id = 1;
int current_process_index = -1;

int create_process(void (*offset)()) {
    if (next_process_id > MAX_PROCESSES) {
        //printf("Maximum number of processes reached.\n");
        return -1;
    }

    Process new_process;
    new_process.process_id = next_process_id++;
    new_process.is_running = 0;
	new_process.offset = offset;

    processes[next_process_id - 2] = new_process;

	return next_process_id - 2;
}

void run_process(int process_id) {
	current_process_index = process_id;
	processes[current_process_index].offset();
}

void delete_process(int process_id) {
	int i;
    for (i = 0; i < MAX_PROCESSES; i++) {
        if (processes[i].process_id == process_id) {
            processes[i] = (Process){NULL};
            break;
        }
    }

    if (i == MAX_PROCESSES) {
        //printf("Process with ID %d not found.\n", process_id);
    }
}