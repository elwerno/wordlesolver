CC = gcc
CFLAGS = -Wall -Wextra -std=c11
BUILD_DIR = build
PYTHON = python3
SCRIPTS_DIR = scripts
SRC_DIR = src
TARGET = wordlesolver

SRCS = $(wildcard $(SRC_DIR)/*.c)

OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: database
database:
	$(PYTHON) $(SCRIPTS_DIR)/wordsParser.py

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: run
run: $(TARGET)
	./$(TARGET)
