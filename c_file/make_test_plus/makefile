CC = gcc
INC = ./inc
CFLAGS = -Wall -std=c99 -O2 -I$(INC)
TARGET = myapp
OBJ_DIR = obj
SRCS = $(wildcard *.c) $(wildcard src/*.c)
# OBJ = $(SRCS:.c=.o)
# OBJ = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))  # 生成对应的 .o 文件路径
# OBJ = $(patsubst %.c,$(OBJ_DIR)/%.o,$(notdir $(SRCS)))#去掉文件路径，只留下文件名
OBJ = obj/main.o obj/src/say_hello.o
# OBJ = obj/main.o obj/say_hello.o
$(info SRCS = $(SRCS) )
$(info OBJ = $(OBJ) )


$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# 确保 obj 目录存在
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/src

.PHONY: clean
clean:
	rm -f $(OBJ_DIR)/*.o $(OBJ_DIR)/src/*.o $(TARGET)
