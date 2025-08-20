CC = gcc
CFLAGS = -Wall -g
SRC = src/main.c src/cli.c src/engine.c src/wal.c src/btree.c
TARGET = main

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET) src/*.o