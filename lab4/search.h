#ifndef SEARCH_H
#define SEARCH_H

#include "student.h"

/**
 * 按姓名查找学生
 * 
 * @param students 学生数组
 * @param count 学生数量
 * @param name 要查找的姓名
 * @return 找到的学生索引，未找到返回-1
 */
int searchByName(STUDENT students[], int count, const char* name);

/**
 * 按学号查找学生
 * 
 * @param students 学生数组
 * @param count 学生数量
 * @param id 要查找的学号
 * @return 找到的学生索引，未找到返回-1
 */
int searchById(STUDENT students[], int count, const char* id);

/**
 * 显示单个学生的所有信息
 * 
 * @param student 学生指针
 */
void displayStudent(const STUDENT* student);

#endif /* SEARCH_H */
