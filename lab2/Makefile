CC = gcc
CFLAGS = -Wall -g

# 默认目标：编译主程序
all: main

# 编译fileop.c 生成目标文件，但不链接
fileop.o: fileop.c fileop.h
	$(CC) $(CFLAGS) -c fileop.c

# 使用fileop.o目标文件编译主程序
main: main.c fileop.o
	$(CC) $(CFLAGS) -o main main.c fileop.o

# 清理生成的文件
clean:
	rm -f main *.o