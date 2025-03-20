#ifndef PRINT_H
#define PRINT_H

#include "student.h"

/**
 * 打印表头
 */
void printHeader(void);

/**
 * 打印所有学生信息
 * 
 * @param students 学生数组
 * @param count 学生数量
 */
void printAllStudents(STUDENT students[], int count);

/**
 * 打印带有总分和平均分的学生信息
 * 
 * @param students 学生数组
 * @param count 学生数量
 */
void printStudentsWithTotalAndAverage(STUDENT students[], int count);

/**
 * 打印课程平均分
 * 
 * @param averages 平均分数组
 */
void printCourseAverages(float averages[4]);

/**
 * 打印成绩分布统计
 * 
 * @param courseIndex 课程索引
 * @param stats 统计结果
 */
void printGradeStatistics(int courseIndex, STATISTICS* stats);

/**
 * 打印菜单
 */
void printMenu(void);

#endif /* PRINT_H */ 