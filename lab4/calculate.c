#include <stdio.h>
#include "calculate.h"


void calculateStudentTotalAndAverage(STUDENT* student) {
    student->score.total = student->score.iCS + student->score.PDP + 
                          student->score.DS + student->score.DL;
    student->score.average = student->score.total / 4.0;
}


void calculateAllStudentsTotalAndAverage(STUDENT students[], int count) {
    for (int i = 0; i < count; i++) {
        calculateStudentTotalAndAverage(&students[i]);
    }
}


void calculateCourseAverages(STUDENT students[], int count, float averages[4]) {
    float sum_iCS = 0, sum_PDP = 0, sum_DS = 0, sum_DL = 0;
    
    for (int i = 0; i < count; i++) {
        sum_iCS += students[i].score.iCS;
        sum_PDP += students[i].score.PDP;
        sum_DS += students[i].score.DS;
        sum_DL += students[i].score.DL;
    }
    
    averages[0] = count > 0 ? sum_iCS / count : 0;
    averages[1] = count > 0 ? sum_PDP / count : 0;
    averages[2] = count > 0 ? sum_DS / count : 0;
    averages[3] = count > 0 ? sum_DL / count : 0;
}


GRADE_LEVEL getGradeLevel(float score) {
    if (score >= 90) return A;
    if (score >= 80) return B;
    if (score >= 70) return C;
    if (score >= 60) return D;
    return F;
}


void analyzeGradeDistribution(STUDENT students[], int count, int courseIndex, STATISTICS* stats) {
    // 初始化统计数据
    for (int i = 0; i < 5; i++) {
        stats->count[i] = 0;
        stats->percent[i] = 0.0;
    }
    
    // 统计各等级人数
    for (int i = 0; i < count; i++) {
        float score;
        switch (courseIndex) {
            case 0: score = students[i].score.iCS; break;
            case 1: score = students[i].score.PDP; break;
            case 2: score = students[i].score.DS; break;
            case 3: score = students[i].score.DL; break;
            default: score = 0; break;
        }
        
        GRADE_LEVEL level = getGradeLevel(score);
        stats->count[level]++;
    }
    
    // 计算百分比
    if (count > 0) {
        for (int i = 0; i < 5; i++) {
            stats->percent[i] = (float)stats->count[i] / count * 100;
        }
    }
}