CC      := gcc
AR      := ar
CFLAGS  := -g -fno-omit-frame-pointer -Wall -Wextra -Iinclude -Isrc/arch/x86_64

TARGET  := libtachyon.a

# ─── Sources ──────────────────────────────────────────────────────────────────
SRC_C   := $(shell find src/ -name "*.c")
SRC_ASM := $(shell find src/arch/x86_64 -name "*.S")

OBJ_C   := $(SRC_C:.c=.o)
OBJ_ASM := $(SRC_ASM:.S=.o)

OBJECTS := $(OBJ_C) $(OBJ_ASM)

# ─── Default ──────────────────────────────────────────────────────────────────
.PHONY: all bench run clean

all: $(TARGET)

# Build static library — not an executable
$(TARGET): $(OBJECTS)
	$(AR) rcs $@ $^

# Compile C
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile ASM
%.o: %.S
	$(CC) -c $< -o $@

# ─── Benchmark ────────────────────────────────────────────────────────────────
BENCH_SRC := benchmarks/ctx_switch_bench.c
BENCH_BIN := benchmarks/ctx_switch_bench

bench: $(TARGET)
	$(CC) $(CFLAGS) $(BENCH_SRC) -L. -ltachyon -o $(BENCH_BIN)
	taskset -c 0 ./$(BENCH_BIN)

# ─── Clean ────────────────────────────────────────────────────────────────────
clean:
	rm -f $(TARGET) $(OBJECTS) $(BENCH_BIN)