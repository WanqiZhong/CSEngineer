#include "sort.h"

/* 插入排序：将未排序部分的元素插入到已排序部分的合适位置 */
void InsertSort(ElemType *A, int n, int (*cmp)(ElemType *, ElemType *))
{
    for(int i=1; i<n; i++)
    {
        int j = i-1;
        while(j>=0 && cmp(A+j, A+j+1)>0)
        {
            Swap(A,j,j+1);
            j--;
        }
    }
} 