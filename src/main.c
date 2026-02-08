#define _POSIX_C_SOURCE 200809L

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

typedef struct {
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;

typedef enum {
    META_COMMAND_ERROR,
    META_COMMAND_EXIT,
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND,
} MetaCommandResult;

typedef enum {
    PREPARE_STATEMENT_SUCCESS,
    PREPARE_STATEMENT_UNRECOGNIZED_STATEMENT,
} PrepareStatementResult;

typedef enum {
    STATEMENT_INSERT,
    STATEMENT_SELECT,
} StatementType;

typedef struct {
    StatementType type;
} Statement;

InputBuffer* new_input_buffer(void);
void print_prompt(void);
void print_motd(void);
void read_input(InputBuffer*);
void close_buffer(InputBuffer*);
MetaCommandResult handle_meta_command(const InputBuffer*);
PrepareStatementResult prepare_statement(const InputBuffer*, Statement*);
void execute_statement(Statement*);

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    print_motd();

    InputBuffer* input_buffer = new_input_buffer();
    while (1) {
        print_prompt();
        read_input(input_buffer);

        if (input_buffer->buffer[0] == '.') {
            switch (handle_meta_command(input_buffer)) {
                case (META_COMMAND_SUCCESS):
                    continue;
                case (META_COMMAND_UNRECOGNIZED_COMMAND):
                    printf("Unrecognized command: %s\n", input_buffer->buffer);
                    continue;
                case (META_COMMAND_ERROR):
                    printf("Error processing command: %s\n", input_buffer->buffer);
                    continue;
                case (META_COMMAND_EXIT):
                    close_buffer(input_buffer);
                    exit(EXIT_SUCCESS);
            }
        }

        Statement statement;
        switch (prepare_statement(input_buffer, &statement)) {
            case (PREPARE_STATEMENT_SUCCESS):
                break;
            case (PREPARE_STATEMENT_UNRECOGNIZED_STATEMENT):
                printf("Unrecognized statement: %s\n", input_buffer->buffer);
                continue;
        }
        execute_statement(&statement);
        printf("Executed.\n");
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

MetaCommandResult handle_meta_command(const InputBuffer* input_buffer) {
    if (strcmp(input_buffer->buffer, ".exit") == 0) return META_COMMAND_EXIT;

    return META_COMMAND_UNRECOGNIZED_COMMAND;
} 

PrepareStatementResult prepare_statement(const InputBuffer* input_buffer, Statement* statement) {
    if (strncmp(input_buffer->buffer, "insert", 6) == 0) {
        statement->type = STATEMENT_INSERT;
        return PREPARE_STATEMENT_SUCCESS;
    }

    if (strcmp(input_buffer->buffer, "select") == 0) {
        statement->type = STATEMENT_SELECT;
        return PREPARE_STATEMENT_SUCCESS;
    }

    return PREPARE_STATEMENT_UNRECOGNIZED_STATEMENT;
}

void execute_statement(Statement* statement) {
    switch (statement->type) {
        case (STATEMENT_INSERT):
            printf("This is where an insert statement would be handled.\n");
            break;
        case (STATEMENT_SELECT):
            printf("This is where a select statement would be handled.\n");
            break;
    }
}