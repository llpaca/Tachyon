CC := gcc

CFLAGS := -g -fno-omit-frame-pointer

TARGET := main

# Automatically find source files
C_SOURCES := $(shell find . -name "*.c")
ASM_SOURCES := $(shell find . -name "*.S")

# Generate object file names
C_OBJECTS := $(C_SOURCES:.c=.o)
ASM_OBJECTS := $(ASM_SOURCES:.S=.o)

OBJECTS := $(C_OBJECTS) $(ASM_OBJECTS)

# Default target
all: $(TARGET)

# Link all object files
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

# Compile C files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile Assembly files
%.o: %.S
	$(CC) -c $< -o $@

# Run pinned to CPU core 0
run: $(TARGET)
	taskset -c 0 ./$(TARGET)

# Clean generated files
clean:
	rm -f $(TARGET) $(OBJECTS)

.PHONY: all run clean