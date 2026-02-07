CC := gcc
CFLAGS := -std=c99 -Wall -Wextra -Wpedantic -Iinclude -O2
LDFLAGS := 

SRC_DIR := src
INC_DIR := include
TEST_DIR := tests
BUILD_DIR := build
BIN_DIR := bin

SERVER_BIN := $(BIN_DIR)/sqliter
TEST_BIN := $(BIN_DIR)/sqliter_tests

SERVER_SRCS := \
			   	$(SRC_DIR)/main.c

SERVER_OBJS := $(SERVER_SRCS:%.c=$(BUILD_DIR)/%.o)

TEST_SRCS := \
			 	$(TEST_DIR)/tests.c

TEST_OBJS := $(TEST_SRCS:%.c=$(BUILD_DIR)/%.o)

all: $(SERVER_BIN)

$(SERVER_BIN): $(SERVER_OBJS)
		@mkdir -p $(BIN_DIR)
			$(CC) $(SERVER_OBJS) -o $@ $(LDFLAGS)

tests: $(TEST_BIN)

$(TEST_BIN): $(TEST_OBJS)
		@mkdir -p $(BIN_DIR)
			$(CC) $(TEST_OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: %.c
		@mkdir -p $(dir $@)
			$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all tests clean

