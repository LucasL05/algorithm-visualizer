CC = gcc

# Standard flags for normal production build
CFLAGS = -Wall -Iinclude -O2
LDFLAGS = -lraylib -pthread

SRC = src/main.c src/bars.c src/sorting.c src/menus.c src/screen.c
OUT = visualizer

# Optimized Valgrind profile (skips undef-value tracking to reduce GUI loop lag)
VALGRIND_FLAGS = --leak-check=full \
                 --show-leak-kinds=definite \
                 --track-origins=no

# ------------------------------------------------------------------------------
# Default Target: Typing 'make' ONLY compiles normally
# ------------------------------------------------------------------------------
all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

# ------------------------------------------------------------------------------
# Valgrind Target: Typing 'make valgrind' compiles with -g and auto-runs Valgrind
# ------------------------------------------------------------------------------
valgrind: CFLAGS = -Wall -Iinclude -g -O0
valgrind: clean $(OUT)
	valgrind $(VALGRIND_FLAGS) ./$(OUT)

# ------------------------------------------------------------------------------
# AddressSanitizer Target: Typing 'make asan' compiles with ASan and runs directly
# (Near-native execution speed, ideal for interactive Raylib apps)
# ------------------------------------------------------------------------------
asan: CFLAGS = -Wall -Iinclude -g -O0 -fsanitize=address,undefined
asan: LDFLAGS += -fsanitize=address,undefined
asan: clean $(OUT)
	LSAN_OPTIONS=suppress_leak_warnings=1:suppressions=lsan.supp ./$(OUT)

# ------------------------------------------------------------------------------
# Cleanup Target
# ------------------------------------------------------------------------------
clean:
	rm -f $(OUT)

.PHONY: all valgrind asan clean