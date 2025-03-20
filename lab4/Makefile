CC = gcc
CFLAGS = -Wall -g

# 目标文件
OBJS = main.o search.o calculate.o print.o fileop.o sort.o quicksort.o

# 默认目标
all: student_system

# 编译主程序
student_system: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# 模块编译规则
main.o: main.c student.h search.h fileop.h sort.h print.h calculate.h
	$(CC) $(CFLAGS) -c $< -o $@

search.o: search.c student.h search.h
	$(CC) $(CFLAGS) -c $< -o $@

calculate.o: calculate.c student.h calculate.h
	$(CC) $(CFLAGS) -c $< -o $@

print.o: print.c student.h print.h
	$(CC) $(CFLAGS) -c $< -o $@

fileop.o: fileop.c student.h fileop.h
	$(CC) $(CFLAGS) -c $< -o $@

sort.o: sort.c sort.h
	$(CC) $(CFLAGS) -c $< -o $@

quicksort.o: quicksort.c sort.h
	$(CC) $(CFLAGS) -c $< -o $@

# 清理生成的文件
clean:
	rm -f *.o student_system