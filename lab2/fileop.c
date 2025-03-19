#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileop.h"

int writeFloatArrayToBinaryFile(const char* filename, float* data, int count) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("无法创建二进制文件 %s\n", filename);
        return -1;
    }
    
    size_t written = fwrite(data, sizeof(float), count, file);
    fclose(file);
    
    return (int)written;
}

int writeFloatArrayToTextFile(const char* filename, float* data, int count) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("无法创建文本文件 %s\n", filename);
        return -1;
    }
    
    int written = 0;
    for (int i = 0; i < count; ++i) {
        if (fprintf(file, "%.6f\n", data[i]) > 0) {
            written++;
        }
    }
    
    fclose(file);
    return written;
}

int writeCharArrayToBinaryFile(const char* filename, char* data, int count) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("无法创建二进制文件 %s\n", filename);
        return -1;
    }
    
    size_t written = fwrite(data, sizeof(char), count, file);
    fclose(file);
    
    return (int)written;
}


int writeCharArrayToTextFile(const char* filename, char* data, int count) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("无法创建文本文件 %s\n", filename);
        return -1;
    }
    
    int written = 0;
    for (int i = 0; i < count; ++i) {
        if (fprintf(file, "%c", data[i]) > 0) {
            written++;
        }
    }
    
    fclose(file);
    return written;
}

int readFloatArrayFromBinaryFile(const char* filename, float* data, int maxCount) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("无法打开二进制文件 %s\n", filename);
        return -1;
    }
    
    size_t read = fread(data, sizeof(float), maxCount, file);
    fclose(file);
    
    return (int)read;
}

int writeRecordsToBinaryFile(const char* filename, Record* records, int count) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("无法创建二进制文件 %s\n", filename);
        return -1;
    }
    
    size_t written = fwrite(records, sizeof(Record), count, file);
    fclose(file);
    
    return (int)written;
}

int readRecordsFromBinaryFile(const char* filename, Record* records, int maxRecords) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("无法打开二进制文件 %s\n", filename);
        return -1;
    }
    
    // 获取文件大小
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    // 计算文件中包含的结构体数量
    int recordCount = fileSize / sizeof(Record);
    
    // 确保不超过最大记录数
    if (recordCount > maxRecords) {
        recordCount = maxRecords;
        printf("警告：文件 %s 中的记录数超过最大记录数 %d\n", filename, maxRecords);
    }
    
    // 读取数据
    size_t read = fread(records, sizeof(Record), recordCount, file);
    fclose(file);
    
    return (int)read;
}


int readStudentsFromTextFile(const char* filename, Student* students, int maxRecords) {
    int count = 0;
    char line[256];

    // 打开文本文件
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("无法打开文本文件 %s\n", filename);
        return -1;
    }

    // 读取文件中的每一行
    while (fgets(line, sizeof(line), file) && count < maxRecords) {
        // 获得一个学生记录
        Student* student = &students[count];
        
        // 使用sscanf解析一行数据
        int result = sscanf(line, "%lu %s %f %f %f %f", 
               &student->id, student->name, 
               &student->scores[0], &student->scores[1], &student->scores[2], 
               &student->scores[3]);
        
        // 检查是否读取了6个字段
        if (result == 6) { 
            count++;
        } else {
            printf("警告：行 %d 格式不正确\n", count + 1);
        }
    }
    fclose(file);
    return count;
}

void printStudent(Student* student) {
    printf("%lu %s %.1f %.1f %.1f %.0f\n", 
        student->id, student->name, 
        student->scores[0], student->scores[1], student->scores[2], 
        student->scores[3]);
}

void printRecord(Record* record) {
    printf("%lu %s %.1f %.1f %.1f %.0f\n", 
        record->id, record->name, 
        record->scores[0], record->scores[1], record->scores[2], 
        record->scores[3]);
}

int writeStudentsToTextFile(const char* filename, Student* students, int count) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("无法创建文件 %s\n", filename);
        return -1;
    }
    
    for (int i = 0; i < count; ++i) {
        fprintf(file, "%lu %s %.1f %.1f %.1f %.0f\n", 
            students[i].id, students[i].name, 
            students[i].scores[0], students[i].scores[1], students[i].scores[2], 
            students[i].scores[3]);
    }
    
    fclose(file);
    return count;
}