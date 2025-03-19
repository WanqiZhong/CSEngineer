#include "sort.h"

/* 冒泡排序：相邻元素比较，每轮将最大元素移到末尾 */
void BubbleSort(ElemType *A, int n, int (*cmp)(ElemType *, ElemType *))
{
    for(int i=0; i<n-1; i++)
    {
        for(int j=0; j<n-i-1; j++)
        {
            if(cmp(A+j, A+j+1)>0)
            {
                Swap(A,j,j+1);
            }
        }
    }
} 