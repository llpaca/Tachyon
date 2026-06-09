CC      := gcc
CFLAGS  := -g -fno-omit-frame-pointer -Wall -Wextra -Iinclude -Isrc/arch/x86_64

TARGET  := tachyon

# ─── Sources ──────────────────────────────────────────────────────────────────

SRC_C   := $(shell find src/ -name "*.c")
SRC_ASM := $(shell find src/arch/x86_64 -name "*.S")

OBJ_C   := $(SRC_C:.c=.o)
OBJ_ASM := $(SRC_ASM:.S=.o)

OBJECTS := $(OBJ_C) $(OBJ_ASM)

# ─── Default ──────────────────────────────────────────────────────────────────
.PHONY: all run bench clean

all: $(TARGET)

# Link
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

# Compile C
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile ASM
%.o: %.S
	$(CC) -c $< -o $@

# ─── Benchmark ────────────────────────────────────────────────────────────────

BENCH_SRC := benchmarks/ctx_switch_bench.c
BENCH_BIN := benchmarks/ctx_switch_bench

bench: $(OBJECTS)
	$(CC) $(CFLAGS) $(BENCH_SRC) $(OBJECTS) -o $(BENCH_BIN)
	taskset -c 0 ./$(BENCH_BIN)

# ─── Run ──────────────────────────────────────────────────────────────────────
run: $(TARGET)
	taskset -c 0 ./$(TARGET)

# ─── Clean ────────────────────────────────────────────────────────────────────
clean:
	rm -f $(TARGET) $(OBJECTS) $(BENCH_BIN)