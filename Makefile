# ZACK Makefile

CC=clang-9
CFLAGS=-Wall -Iinclude -O2 -std=c11
LDFLAGS=-lncurses

ofiles= editor.o g_main.o g_setup.o main.o map_load.o map_update.o render.o

all: ech1 zack ech2

.SILENT: ech1 ech2

%.o: %.c
	$(CC) $(CFLAGS) -c $^

zack: $(ofiles)
	@echo "\033[38;5;23m"
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

ech1:
	echo "\033[2J\033[38;5;34m"

ech2:
	echo "\033[38;5;178m"

clean : $(ofiles)
	mv $^ ./o/