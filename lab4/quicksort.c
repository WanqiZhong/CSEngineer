#include "sort.h"

/* 快速排序：选择一个基准元素，将小于基准的放左边，大于基准的放右边 */
void QuickSort(ElemType *A, int n, int (*cmp)(ElemType *, ElemType *))
{
    if(n<=1){
        return;
    }else if(n==2){
        if(cmp(A, A+1)>0)
        {
            Swap(A,0,1);
        }
        return;
    }
    int pivot = rand() % n; // 随机选择基准元素
    Swap(A, pivot, n-1); // 将基准元素放到末尾
    int i = 0, j = n-2;
    while(i<=j)
    {
        while(i<=j && cmp(A+i, A+n-1)<=0) // 找到左边大于基准的元素
        {
            i++;
        }
        while(i<=j && cmp(A+j, A+n-1)>0) // 找到右边小于等于基准的元素
        {
            j--;
        }
        if(i<j)
        {
            Swap(A,i,j); // 交换这两个元素
        }
    }
    Swap(A,i,n-1); // 将基准元素放到最终位置
    QuickSort(A, i, cmp); // 排序左半部分
    QuickSort(A+i+1, n-i-1, cmp); // 排序右半部分
    return;
} 


void QuickSort3Way(ElemType *A, int n, int (*cmp)(ElemType *, ElemType *))
{
    if(n<=1){
        return;
    }else if(n==2){
        if(cmp(A, A+1)>0)
        {
            Swap(A,0,1);
        }
        return;
    }
    int l = 0, r = n-1, i = 1;
    while(i<=r)
    {
        if(cmp(A+i, A+l)<0) // 找到左边大于基准的元素
        {
            Swap(A, l++, i++);
        }else if(cmp(A+i, A+r)>0) // 找到右边小于等于基准的元素
        {
            Swap(A, r--, i);
        }else{
            i++;
        }
    }
    QuickSort3Way(A, l, cmp); // 排序左半部分
    QuickSort3Way(A+r+1, n-r-1, cmp); // 排序右半部分
    return;
} 

void Swap(ElemType *A, int i, int j)
{
    ElemType tmp = *(A+i);
    *(A+i) = *(A+j);
    *(A+j) = tmp;
}