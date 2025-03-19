CC	= gcc -m64 -w

# COPT	= -O2
COPT	= -g

# 定义标准和三路快速排序的编译选项
STD_QUICK_COPT = $(COPT)
NEW_QUICK_COPT = $(COPT) -DNewQuickSort

GRARC	 = sort.a
GRSRCS	 = swap.c SelectSort.c BubbleSort.c InsertSort.c MergeSort.c QuickSort.c HeapSort.c main.c
GROBJS	 = swap.o selectsort.o bubblesort.o insertsort.o mergesort.o quicksort.o heapsort.o main.o
HEADER   = sort.h

# 默认目标使用标准快排
runsort: $(GROBJS)
	$(CC) $(COPT) -o runsort $(GROBJS) 

# 新增目标，使用新快排
newquick: COPT += -DNewQuickSort
newquick: clean runsort
	@echo "Compiled with NewQuickSort enabled"

main.o: main.c sort.h
	$(CC) $(COPT) -c main.c -o main.o
swap.o: swap.c sort.h
	$(CC) $(COPT) -c swap.c -o swap.o
selectsort.o: SelectSort.c sort.h
	$(CC) $(COPT) -c SelectSort.c -o selectsort.o
bubblesort.o: BubbleSort.c sort.h
	$(CC) $(COPT) -c BubbleSort.c -o bubblesort.o
insertsort.o: InsertSort.c sort.h
	$(CC) $(COPT) -c InsertSort.c -o insertsort.o
mergesort.o: MergeSort.c sort.h
	$(CC) $(COPT) -c MergeSort.c -o mergesort.o
quicksort.o: QuickSort.c sort.h
	$(CC) $(COPT) -c QuickSort.c -o quicksort.o
heapsort.o: HeapSort.c sort.h
	$(CC) $(COPT) -c HeapSort.c -o heapsort.o

clean:
	rm -f $(GROBJS) runsort