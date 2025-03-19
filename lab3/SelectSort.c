#include "sort.h"

/* 选择排序：每次选择未排序部分的最小元素放到已排序部分的末尾 */
void SelectSort(ElemType *A, int n, int (*cmp)(ElemType *, ElemType *))
{
    for(int i=0; i<n-1; i++)
    {
        int j=i; // j指向当前找到的最小元素
        for(int k=i+1; k<n; k++)
        {
            if(cmp(A+j, A+k)>0) // 如果找到更小的元素
            {
                j=k;
            }
        }
        Swap(A,i,j); // 将最小元素放到已排序部分的末尾
    }
}
