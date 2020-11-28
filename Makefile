# Basic stuff for compiling:
## the compiler
CC = gcc
## flags for compiler
CFLAGS = -g -Wall
## final output
TARGET = main_exec

# Folders
## "temporary" output for object files
BUILD_DIR = ./build
## "libraries" we use, ADTs
LIB_DIR = ./lib
## the main "driver", heart of the program
MAIN_DIR = ./src

# Processing folders
## get .c files
SRCS := $(shell find $(LIB_DIR)/body -name *.c) $(shell find $(MAIN_DIR) -name *.c)
## "foresee" .o files' paths
OBJS := $(SRCS:%.c=$(BUILD_DIR)/%.o)

# Processing headers
## headers for ADTs
INC_DIRS := $(LIB_DIR)/header
## Include them in compilation time
INC_FLAGS := $(addprefix -I, $(INC_DIRS))
LDFLAGS = -lm

./$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) $(INC_FLAGS) -o $@

run: ./$(TARGET)
	./$<

$(BUILD_DIR)/%.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

.PHONY: clean

clean:
	$(RM) -rf $(BUILD_DIR)

MKDIR_P ?= mkdir -p
