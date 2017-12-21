#include "file.h"

file_t file_load(char * file_name) {
    file_t file;
    file.size = 0;
    file.buffer = 0;
    file.name = file_name;

    // Attempt to open file for reading
    FILE * fptr = fopen(file_name, "r");

    if (fptr) {
        // Calculate size
        fseek(fptr, 0L, SEEK_END);
        file.size = ftell(fptr);
        rewind(fptr);

        // Allocate, add one for \0
        file.buffer = malloc(file.size + 1);
        file.buffer[file.size] = '\0';

        // Read into buffer
        for (int i = 0; i < file.size; ++i) {
            fread(file.buffer + i, 1, 1, fptr);
        }

        // Close
        fclose(fptr);
    }

    return file;
}

void file_destroy(file_t * file) {
    free(file->buffer);
}
