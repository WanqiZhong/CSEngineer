#include <stdio.h>
#include "student.h"
#include "sort.h"

/* 比较函数，按iCS成绩降序排序 */
int cmpByICS(ElemType* a, ElemType* b) {
    const STUDENT* sa = (const STUDENT*)a;
    const STUDENT* sb = (const STUDENT*)b;
    if (sa->score.iCS > sb->score.iCS) return -1; 
    if (sa->score.iCS < sb->score.iCS) return 1;
    return 0;
}

/* 比较函数，按PDP成绩降序排序 */
int cmpByPDP(ElemType* a, ElemType* b) {
    const STUDENT* sa = (const STUDENT*)a;
    const STUDENT* sb = (const STUDENT*)b;
    if (sa->score.PDP > sb->score.PDP) return -1;
    if (sa->score.PDP < sb->score.PDP) return 1;
    return 0;
}

/* 比较函数，按DS成绩降序排序 */
int cmpByDS(ElemType* a, ElemType* b) {
    const STUDENT* sa = (const STUDENT*)a;
    const STUDENT* sb = (const STUDENT*)b;
    if (sa->score.DS > sb->score.DS) return -1;
    if (sa->score.DS < sb->score.DS) return 1;
    return 0;
}

/* 比较函数，按DL成绩降序排序 */
int cmpByDL(ElemType* a, ElemType* b) {
    const STUDENT* sa = (const STUDENT*)a;
    const STUDENT* sb = (const STUDENT*)b;
    if (sa->score.DL > sb->score.DL) return -1;
    if (sa->score.DL < sb->score.DL) return 1;
    return 0;
}

/* 比较函数，按总分降序排序 */
int cmpByTotal(ElemType* a, ElemType* b) {
    const STUDENT* sa = (const STUDENT*)a;
    const STUDENT* sb = (const STUDENT*)b;
    if (sa->score.total > sb->score.total) return -1;
    if (sa->score.total < sb->score.total) return 1;
    return 0;
}


int (*getCompareFunction(int courseIndex))(ElemType*, ElemType*) {
    switch (courseIndex) {
        case 0: return cmpByICS;
        case 1: return cmpByPDP;
        case 2: return cmpByDS;
        case 3: return cmpByDL;
        case 4: return cmpByTotal;
        default: return NULL;
    }
}

void sortStudentsByCourse(STUDENT students[], int count, int courseIndex) {
    int (*cmpFunc)(ElemType*, ElemType*) = getCompareFunction(courseIndex);
    if (cmpFunc == NULL) {
        printf("无效的课程索引\n");
        return;
    }
    
    // 使用快速排序算法
    QuickSort((ElemType*)students, count, cmpFunc);
}