#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;

InputBuffer* new_input_buffer(void);
void print_prompt(void);
void print_motd(void);
void read_input(InputBuffer*);
void close_buffer(InputBuffer*);

int main(int argc, char *argv[]) {
    print_motd();

    InputBuffer* input_buffer = new_input_buffer();
    while (1) {
        print_prompt();
        read_input(input_buffer);

        if (strcmp(input_buffer->buffer, ".exit") == 0) {
            close_buffer(input_buffer);
            exit(EXIT_SUCCESS);
        } else {
            printf("Unrecognized command: %s\n", input_buffer->buffer);
        }
    } 
    return 0;
}

InputBuffer* new_input_buffer(void) {
    InputBuffer* input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;

    return input_buffer;
}

void print_prompt(void) {
    printf("sqliter> ");
}

void print_motd(void) {
    time_t now = time(NULL);
    struct tm* tm_info = localtime(&now);

    char date[20];
    strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", tm_info);
    printf("SQLiter version 0.1.0 %s\n", date);
}

void read_input(InputBuffer* input_buffer) {
    ssize_t bytes_read = getline(
        &(input_buffer->buffer), 
        &(input_buffer->buffer_length), 
        stdin
    );

    if (bytes_read <= 0) {
        printf("Error reading input.\n");
        exit(EXIT_FAILURE);
    }

    if (input_buffer->buffer[bytes_read - 1] == '\n') {
        input_buffer->input_length = bytes_read - 1;
        input_buffer->buffer[bytes_read - 1] = '\0';
    } else {
        input_buffer->input_length = bytes_read;
    }
}

void close_buffer(InputBuffer* input_buffer) {
    free(input_buffer->buffer);
    free(input_buffer);
}