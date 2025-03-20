#ifndef CALCULATE_H
#define CALCULATE_H

#include "student.h"

/**
 * 计算单个学生的总分和平均分
 * 
 * @param student 学生指针
 */
void calculateStudentTotalAndAverage(STUDENT* student);

/**
 * 计算所有学生的总分和平均分
 * 
 * @param students 学生数组
 * @param count 学生数量
 */
void calculateAllStudentsTotalAndAverage(STUDENT students[], int count);

/**
 * 计算每门课程的平均分
 * 
 * @param students 学生数组
 * @param count 学生数量
 * @param averages 存储各科平均分的数组
 */
void calculateCourseAverages(STUDENT students[], int count, float averages[4]);

/**
 * 获取成绩等级
 * 
 * @param score 成绩
 * @return 等级枚举值
 */
GRADE_LEVEL getGradeLevel(float score);

/**
 * 对指定课程成绩进行统计分析
 * 
 * @param students 学生数组
 * @param count 学生数量
 * @param courseIndex 课程索引 (0=iCS, 1=PDP, 2=DS, 3=DL)
 * @param stats 统计结果
 */
void analyzeGradeDistribution(STUDENT students[], int count, int courseIndex, STATISTICS* stats);

#endif /* CALCULATE_H */