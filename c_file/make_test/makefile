CC = gcc
CFLAGS = -Wall -std=c99
TARGET = myapp

$(TARGET): main.o
	$(CC) main.o -o $(TARGET)


main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

.PHONY: clean
clean:
	rm -f main.o $(TARGET)