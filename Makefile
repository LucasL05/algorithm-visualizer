CC = gcc
CFLAGS = -Wall -Iinclude
LDFLAGS = -lraylib -pthread

SRC = src/main.c src/bars.c src/sorting.c src/main_menu.c src/screen.c
OUT = visualizer

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

clean:
	rm -f $(OUT)
