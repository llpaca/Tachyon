CC      := gcc
AR      := ar
CFLAGS  := -g -fno-omit-frame-pointer -Wall -Wextra -Iinclude -Isrc/arch/x86_64

# Build dir 
BUILD       := build
OBJ_DIR     := $(BUILD)/obj
BIN_DIR     := $(BUILD)/bin

TARGET      := $(BUILD)/libtachyon.a

# Sources
SRC_C       := $(shell find src/ -name "*.c")
SRC_ASM     := $(shell find src/arch/x86_64 -name "*.S")

# Mirror the src/ tree under build/obj/
# e.g. src/arch/x86_64/context.S -> build/obj/src/arch/x86_64/context.o
OBJ_C       := $(patsubst %,$(OBJ_DIR)/%.o,$(SRC_C))
OBJ_ASM     := $(patsubst %,$(OBJ_DIR)/%.o,$(SRC_ASM))

OBJECTS     := $(OBJ_C) $(OBJ_ASM)

# Default
.PHONY: all bench clean

all: $(TARGET)

# Static library
$(TARGET): $(OBJECTS) | $(BUILD)
	$(AR) rcs $@ $^

# Compile C  — create parent dir first
$(OBJ_DIR)/%.c.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile ASM
$(OBJ_DIR)/%.S.o: %.S | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) -c $< -o $@

# Dir rules 
$(BUILD):
	@mkdir -p $(BUILD)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

# Benchmark 
BENCH_SRC   := benchmarks/ctx_switch_bench.c
BENCH_BIN   := $(BIN_DIR)/ctx_switch_bench

bench: $(TARGET) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(BENCH_SRC) -L$(BUILD) -ltachyon -o $(BENCH_BIN)
	taskset -c 0 $(BENCH_BIN)

# Clean
# Just nuke build/ — source tree stays untouched
clean:
	rm -rf $(BUILD)