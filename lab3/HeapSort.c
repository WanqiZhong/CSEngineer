#include "sort.h"

/* 堆排序：构建最大堆，然后依次取出堆顶元素 */
void HeapSort(ElemType *A, int n, int (*cmp)(ElemType *, ElemType *))
{
    // 构建最大堆
    for(int i = n/2-1; i >= 0; i--){
        Heapify(A, n, i, cmp);
    }
    // 一个个从堆顶取出元素
    for(int i = n-1; i > 0; i--){
        Swap(A, 0, i); // 将堆顶元素放到已排序部分的开头
        Heapify(A, i, 0, cmp); // 对剩余元素重新构建堆
    }
    return;
}

/* 调整堆的函数，确保以i为根的子树满足堆的性质 */
void Heapify(ElemType *A, int n, int i, int(*cmp)(ElemType *, ElemType *))
{
    int parent = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if(right < n && cmp(A+right, A+parent) > 0){
        parent = right;
    }

    if(left < n && cmp(A+left, A+parent) > 0){
        parent = left;
    }    

    if(parent != i){
        Swap(A, parent, i); 
        Heapify(A, n, parent, cmp);
    }
    return;
} 