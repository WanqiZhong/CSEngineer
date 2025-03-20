#include "sort.h"

/* 归并排序：分而治之，将数组分成两半排序后合并 */
void MergeSort(ElemType *A, int n, int (*cmp)(ElemType *, ElemType *))
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
    int mid = n/2;
    MergeSort(A, mid, cmp); // 排序左半部分
    MergeSort(A+mid, n-mid, cmp); // 排序右半部分
    
    // 合并两个已排序的子数组
    ElemType *temp = (ElemType *)malloc(n * sizeof(ElemType));
    int i=0, j=mid, k=0;
    while(i<mid && j<n)
    {
        if(cmp(A+i, A+j)<0) // 取两个子数组中较小的元素
        {
            temp[k++] = A[i++];
        }else{
            temp[k++] = A[j++];
        }
    }
    while(i<mid) // 处理剩余的左半部分
    {
        temp[k++] = A[i++];
    }
    while(j<n) // 处理剩余的右半部分
    {
        temp[k++] = A[j++];
    }
    memcpy(A, temp, n * sizeof(ElemType)); // 拷贝回原数组
    free(temp);
    return;
} 