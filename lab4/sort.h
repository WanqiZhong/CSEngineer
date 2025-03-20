#ifndef SORT_H
#define SORT_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "student.h"

/* 通用元素类型定义 */
typedef STUDENT ElemType;

/* 排序函数声明 */
void QuickSort(ElemType *A, int n, int (*cmp)(ElemType *, ElemType *));

/* 比较函数声明 */
int cmpByICS(ElemType* a, ElemType* b);
int cmpByPDP(ElemType* a, ElemType* b);
int cmpByDS(ElemType* a, ElemType* b);
int cmpByDL(ElemType* a, ElemType* b);
int cmpByTotal(ElemType* a, ElemType* b);

/* 交换函数声明 */
void Swap(ElemType *A, int i, int j);

/**
 * 获取课程对应的比较函数
 * 
 * @param courseIndex 课程索引 (0=iCS, 1=PDP, 2=DS, 3=DL, 4=total)
 * @return 比较函数指针
 */
int (*getCompareFunction(int courseIndex))(ElemType*, ElemType*);

/**
 * 对学生按指定课程成绩排序
 * 
 * @param students 学生数组
 * @param count 学生数量
 * @param courseIndex 课程索引
 */
void sortStudentsByCourse(STUDENT students[], int count, int courseIndex);

#endif /* SORT_H */ 