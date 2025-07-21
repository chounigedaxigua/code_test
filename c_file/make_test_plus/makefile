CC = gcc
INC = ./inc
CFLAGS = -Wall -std=c99 -O2 -I$(INC)
TARGET = myapp
OBJ_DIR = obj
SRCS = $(wildcard *.c) $(wildcard src/*.c)
OBJ = $(SRCS:.c=.o)



$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJ) $(TARGET)


  