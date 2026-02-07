CC := gcc
CFLAGS := -std=c99 -Wall -Wextra -Wpedantic -Iinclude -O2
LDFLAGS := 

SRC_DIR := src
INC_DIR := include
TEST_DIR := tests
BUILD_DIR := build
BIN_DIR := bin

SQLITER_BIN := $(BIN_DIR)/sqliter
TEST_BIN := $(BIN_DIR)/sqliter_tests

SQLITER_SRCS := \
			   	$(SRC_DIR)/main.c

SQLITER_OBJS := $(SQLITER_SRCS:%.c=$(BUILD_DIR)/%.o)

TEST_SRCS := \
			 	$(TEST_DIR)/tests.c

TEST_OBJS := $(TEST_SRCS:%.c=$(BUILD_DIR)/%.o)

all: $(SQLITER_BIN)

$(SQLITER_BIN): $(SQLITER_OBJS)
		@mkdir -p $(BIN_DIR)
			$(CC) $(SQLITER_OBJS) -o $@ $(LDFLAGS)

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

