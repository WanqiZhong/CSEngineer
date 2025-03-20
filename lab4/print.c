#include <stdio.h>
#include "student.h"


void printHeader() {
    printf("\n%-12s %-10s %-10s %-10s %-10s %-10s\n", 
           "学号", "姓名", "iCS", "PDP", "DS", "DL");
    printf("--------------------------------------------------------\n");
}


void printAllStudents(STUDENT students[], int count) {
    printHeader();
    for (int i = 0; i < count; i++) {
        printf("%-12s %-10s %-8.1f %-8.1f %-8.1f %-8.1f\n", 
               students[i].id, 
               students[i].name, 
               students[i].score.iCS, 
               students[i].score.PDP, 
               students[i].score.DS, 
               students[i].score.DL);
    }
    printf("--------------------------------------------------------\n");
}


void printStudentsWithTotalAndAverage(STUDENT students[], int count) {
    printf("\n%-12s %-12s %-9s %-9s %-9s %-9s %-9s %-9s\n", 
           "学号", "姓名", "iCS", "PDP", "DS", "DL", "总分", "平均分");
    printf("------------------------------------------------------------------------\n");
    
    for (int i = 0; i < count; i++) {
        printf("%-12s %-10s %-8.1f %-8.1f %-8.1f %-8.1f %-8.1f %-8.1f\n", 
               students[i].id, 
               students[i].name, 
               students[i].score.iCS, 
               students[i].score.PDP, 
               students[i].score.DS, 
               students[i].score.DL,
               students[i].score.total,
               students[i].score.average);
    }
    printf("------------------------------------------------------------------------\n");
}


void printCourseAverages(float averages[4]) {
    printf("\n课程平均分统计：\n");
    printf("计算机系统(iCS): %.2f\n", averages[0]);
    printf("程序设计实践(PDP): %.2f\n", averages[1]);
    printf("数据结构(DS): %.2f\n", averages[2]);
    printf("数字逻辑(DL): %.2f\n", averages[3]);
}


void printGradeStatistics(int courseIndex, STATISTICS* stats) {
    char* courseName;
    switch (courseIndex) {
        case 0: courseName = "计算机系统(iCS)"; break;
        case 1: courseName = "程序设计实践(PDP)"; break;
        case 2: courseName = "数据结构(DS)"; break;
        case 3: courseName = "数字逻辑(DL)"; break;
        default: courseName = "未知课程"; break;
    }
    
    printf("\n%s 成绩分布统计：\n", courseName);
    printf("优秀(90~100): %d人 (%.2f%%)\n", stats->count[A], stats->percent[A]);
    printf("良好(80~89): %d人 (%.2f%%)\n", stats->count[B], stats->percent[B]);
    printf("中等(70~79): %d人 (%.2f%%)\n", stats->count[C], stats->percent[C]);
    printf("及格(60~69): %d人 (%.2f%%)\n", stats->count[D], stats->percent[D]);
    printf("不及格(0~59): %d人 (%.2f%%)\n", stats->count[F], stats->percent[F]);
}


void printMenu() {
    printf("\n=== 学生成绩管理系统 ===\n");
    printf("1. Append record\n");
    printf("2. Search by name\n");
    printf("3. Search by ID\n");
    printf("4. Modify by ID\n");
    printf("5. Delete by ID\n");
    printf("6. Calculate total and average score of every student\n");
    printf("7. Calculate average score of every course\n");
    printf("8. Sort in descending order by course score\n");
    printf("9. Statistic analysis for every course\n");
    printf("10. Save record\n");
    printf("11. Load record\n");
    printf("0. Exit\n");
    printf("Please enter your choice: ");
}