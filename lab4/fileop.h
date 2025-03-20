#ifndef FILEOP_H
#define FILEOP_H

#include "student.h"
#include <ctype.h>

/**
 * 保存学生记录到文本文件
 * 
 * @param filename 文件名
 * @param students 学生数组
 * @param count 学生数量
 * @return 成功写入的记录数，失败返回-1
 */
int saveStudentsToTextFile(const char* filename, STUDENT students[], int count);

/**
 * 从文本文件读取学生记录
 * 
 * @param filename 文件名
 * @param students 学生数组
 * @param maxCount 最大记录数
 * @return 成功读取的记录数，失败返回-1
 */
int loadStudentsFromTextFile(const char* filename, STUDENT students[], int maxCount);

/**
 * 保存学生记录到二进制文件
 * 
 * @param filename 文件名
 * @param students 学生数组
 * @param count 学生数量
 * @return 成功写入的记录数，失败返回-1
 */
int saveStudentsToBinaryFile(const char* filename, STUDENT students[], int count);

/**
 * 从二进制文件读取学生记录
 * 
 * @param filename 文件名
 * @param students 学生数组
 * @param maxCount 最大记录数
 * @return 成功读取的记录数，失败返回-1
 */
int loadStudentsFromBinaryFile(const char* filename, STUDENT students[], int maxCount);

#endif /* FILEOP_H */ 