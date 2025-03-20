#ifndef FILEOP_H
#define FILEOP_H

#define MAX_RECORDS 1000

// 定义学生记录结构体
typedef struct {
    unsigned long id;
    char name[32];
    float scores[4];
} Student;
typedef Student Record;

/**
 * @brief 从文本文件读取学生记录
 * @param filename 文本文件名
 * @param students 学生记录数组，每个元素是一个学生记录
 * @param maxRecords 最大学生记录数
 * @return count 读取的学生记录数，失败返回-1
 */
int readStudentsFromTextFile(const char* filename, Student* students, int maxRecords);

/**
 * @brief 将学生记录写入文本文件
 * @param filename 文本文件名
 * @param students 学生记录数组，每个元素是一个学生记录
 * @param count 学生记录数
 * @return count 写入的学生记录数，失败返回-1
 */
int writeStudentsToTextFile(const char* filename, Student* students, int count);

/**
 * @brief 打印学生记录
 * @param student 学生记录指针
 */
void printStudent(Student* student);

/**
 * @brief 打印记录
 * @param record 记录指针
 */
void printRecord(Record* record);

/**
 * @brief 将浮点数组写入二进制文件
 * @param filename 文件名
 * @param data 浮点数数组
 * @param count 数组元素个数
 * @return 成功写入为正数，失败返回-1
 */
int writeFloatArrayToBinaryFile(const char* filename, float* data, int count);

/**
 * @brief 将浮点数组写入文本文件
 * @param filename 文件名
 * @param data 浮点数数组
 * @param count 数组元素个数
 * @return 成功写入为正数，失败返回-1
 */
int writeFloatArrayToTextFile(const char* filename, float* data, int count);

/**
 * @brief 将字符数组写入二进制文件
 * @param filename 文件名
 * @param data 字符数组
 * @param count 数组元素个数
 * @return 成功写入为正数，失败返回-1
 */
int writeCharArrayToBinaryFile(const char* filename, char* data, int count);

/**
 * @brief 将字符数组写入文本文件
 * @param filename 文件名
 * @param data 字符数组
 * @param count 数组元素个数
 * @return 成功写入为正数，失败返回-1
 */
int writeCharArrayToTextFile(const char* filename, char* data, int count);

/**
 * @brief 从二进制文件读取浮点数组
 * @param filename 文件名
 * @param data 浮点数数组（用于存储读取的数据）
 * @param maxCount 最大读取元素个数
 * @return 成功读取为正数，失败返回-1
 */
int readFloatArrayFromBinaryFile(const char* filename, float* data, int maxCount);

/**
 * @brief 将结构体数组写入二进制文件
 * @param filename 文件名
 * @param students 学生记录数组
 * @param count 学生记录数
 * @return 成功写入为正数，失败返回-1
 */
int writeRecordsToBinaryFile(const char* filename, Record* records, int count);

/**
 * @brief 从二进制文件读取未知长度的结构体数组
 * @param filename 文件名
 * @param students 学生记录数组（用于存储读取的数据）
 * @param maxRecords 最大读取结构体个数
 * @return 成功读取为正数，失败返回-1
 */
int readRecordsFromBinaryFile(const char* filename, Record* records, int maxRecords);

#endif /* FILEOP_H */