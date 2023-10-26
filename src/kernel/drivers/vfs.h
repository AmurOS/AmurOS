#define MAX_FILENAME_SIZE 32
#define MAX_FILE_COUNT 10

typedef struct {
    char filename[MAX_FILENAME_SIZE];
    int size;
    char* data;
} File;

File files[MAX_FILE_COUNT];
int file_count = 0;

void create_file(const char* filename, int size) {
    if (file_count == MAX_FILE_COUNT) {
        __std__printff("Maximum number of files reached.\n");
        return;
    }

    File new_file;

    __std__strncpy(new_file.filename, filename, MAX_FILENAME_SIZE);
    new_file.size = size;
    new_file.data = (char*)__std__malloc(size+1);

    files[file_count++] = new_file;
}

void write_file(const char* filename, const char* data) {
    int i;
    for (i = 0; i < file_count; i++) {
        File file = files[i];
        if (__std__strcmp(file.filename, filename) == 0) {
            __std__strncpy(file.data, data, file.size);
            file.data[file.size] = '\0';
            return;
        }
    }

    if (i == file_count) {
        __std__printf("File not found.\n");
    }
}

void read_file(const char* filename) {
    int i;
    for (i = 0; i < file_count; i++) {
        File file = files[i];
        if (__std__strcmp(file.filename, filename) == 0) {
            __std__printff("File: %s\n", file.filename);
            __std__printff("Size: %d bytes\n", file.size);
            __std__printff("Data: %s\n", file.data);
            return;
        }
    }

    if (i == file_count) {
        __std__printf("File not found.\n");
    }
}

void delete_file(const char* filename) {
    int i;
    for (i = 0; i < file_count; i++) {
        File file = files[i];
        if (__std__strcmp(file.filename, filename) == 0) {
            __std__free(&file.data);
            __std__free(&file);
            file_count--;

            for (int j = i; j < file_count; j++) {
                files[j] = files[j+1];
            }

            __std__printf("File deleted.\n");
            return;
        }
    }

    if (i == file_count) {
        __std__printf("File not found.\n");
    }
}

void print_files() {
    if (file_count == 0) {
        __std__printf("No files found.\n");
        return;
    }

    __std__printf("Files:\n");
    for (int i = 0; i < file_count; i++) {
        __std__printff("File: %s\n", files[i].filename);
        __std__printff("Size: %d bytes\n", files[i].size);
        __std__printf("\n");
    }
}