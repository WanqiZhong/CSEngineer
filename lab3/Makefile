CC	= gcc -m64 -w

# COPT	= -O2
COPT	= -g

# 定义标准和三路快速排序的编译选项
std_quick_copt = $(COPT)
new_quick_copt = $(COPT) -DNewQuickSort

grarc	 = sort.a
grsrcs	 = swap.c selectsort.c bubblesort.c insertsort.c mergesort.c quicksort.c heapsort.c main.c
grobjs	 = swap.o selectsort.o bubblesort.o insertsort.o mergesort.o quicksort.o heapsort.o main.o
header   = sort.h

# 默认目标使用标准快排
runsort: $(grobjs)
	$(CC) $(COPT) -o runsort $(grobjs) 

# 新增目标，使用新快排
newquick: COPT += -DNewQuickSort
newquick: clean runsort
	@echo "Compiled with NewQuickSort enabled"

main.o: main.c sort.h
	$(CC) $(COPT) -c main.c -o main.o
swap.o: swap.c sort.h
	$(CC) $(COPT) -c swap.c -o swap.o
selectsort.o: selectsort.c sort.h
	$(CC) $(COPT) -c selectsort.c -o selectsort.o
bubblesort.o: bubblesort.c sort.h
	$(CC) $(COPT) -c bubblesort.c -o bubblesort.o
insertsort.o: insertsort.c sort.h
	$(CC) $(COPT) -c insertsort.c -o insertsort.o
mergesort.o: mergesort.c sort.h
	$(CC) $(COPT) -c mergesort.c -o mergesort.o
quicksort.o: quicksort.c sort.h
	$(CC) $(COPT) -c quicksort.c -o quicksort.o
heapsort.o: heapsort.c sort.h
	$(CC) $(COPT) -c heapsort.c -o heapsort.o

clean:
	rm -f $(grobjs) runsort