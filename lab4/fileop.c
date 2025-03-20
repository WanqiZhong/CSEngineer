#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"
#include "fileop.h"

int saveStudentsToTextFile(const char* filename, STUDENT students[], int count) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("无法创建文件 %s\n", filename);
        return -1;
    }
    
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %s %.1f %.1f %.1f %.1f\n",
                students[i].id,
                students[i].name,
                students[i].score.iCS,
                students[i].score.PDP,
                students[i].score.DS,
                students[i].score.DL);
    }
    
    fclose(file);
    return count;
}


int loadStudentsFromTextFile(const char* filename, STUDENT students[], int maxCount) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("无法打开文件 %s\n", filename);
        return -1;
    }
    
    int count = 0;
    char line[256];
    
    while (fgets(line, sizeof(line), file) && count < maxCount) {
        
        STUDENT *student = &students[count];
        STUDENT *newStudent = (STUDENT *)malloc(sizeof(STUDENT));

        int errorFlag = 0;
        int scanResult = sscanf(line, "%s %s %f %f %f %f",
                               newStudent->id,
                               newStudent->name,
                               &newStudent->score.iCS,
                               &newStudent->score.PDP,
                               &newStudent->score.DS,
                               &newStudent->score.DL);
      
        if(scanResult != 6){
            printf("警告：文件 %s 的第 %d 行格式错误\n", filename, count + 1);
            errorFlag = 1;
            continue;
        }

        // 验证成绩范围
        if (newStudent->score.iCS < 0 || newStudent->score.iCS > 100 ||
            newStudent->score.PDP < 0 || newStudent->score.PDP > 100 ||
            newStudent->score.DS < 0 || newStudent->score.DS > 100 ||
            newStudent->score.DL < 0 || newStudent->score.DL > 100) {
            printf("警告：文件 %s 的第 %d 行成绩超出范围(0-100)\n", filename, count + 1);
            errorFlag = 1;
            continue;
        }

        for(int i = 0; i < strlen(newStudent->id) && !errorFlag; i++){
            if(!isdigit(newStudent->id[i])){
                printf("警告：文件 %s 的第 %d 行学号格式错误\n", filename, count + 1);
                errorFlag = 1;
                break;
            }
        }

        if(errorFlag){
            continue;
        }
        
        count++;
        strcpy(student->id, newStudent->id);
        strcpy(student->name, newStudent->name);
        student->score.iCS = newStudent->score.iCS;
        student->score.PDP = newStudent->score.PDP;
        student->score.DS = newStudent->score.DS;
        student->score.DL = newStudent->score.DL;

        if(count >= maxCount){
            printf("警告：文件 %s 中的学生数量超过了当前班级最大人数 %d\n", filename, maxCount);
            break;
        }
    }
    fclose(file);
    return count;
}


int saveStudentsToBinaryFile(const char* filename, STUDENT students[], int count) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("无法创建文件 %s\n", filename);
        return -1;
    }
    
    size_t written = fwrite(students, sizeof(STUDENT), count, file);
    fclose(file);
    
    return (int)written;
}


int loadStudentsFromBinaryFile(const char* filename, STUDENT students[], int maxCount) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("无法打开文件 %s\n", filename);
        return -1;
    }
    
    // 获取文件大小
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    // 计算文件中包含的记录数
    int recordCount = fileSize / sizeof(STUDENT);
    
    // 确保不超过最大记录数
    if (recordCount > maxCount) {
        printf("警告：文件 %s 中的学生数量超过了当前班级最大人数 %d\n", filename, maxCount);
        recordCount = maxCount;
    }
    
    // 读取数据
    size_t read = fread(students, sizeof(STUDENT), recordCount, file);

    // 检查读取的数据是否正确
    for(int i = 0; i < (int)read; i++){

        int errorFlag = 0;
        if(students[i].id == NULL || students[i].name == NULL || students[i].score.iCS == 0 || students[i].score.PDP == 0 || students[i].score.DS == 0 || students[i].score.DL == 0){
            printf("警告：文件 %s 的第 %d 行数据错误\n", filename, i + 1);
            errorFlag = 1;
        }

        for(int j = 0; j < strlen(students[i].id) && !errorFlag; j++){
            if(!isdigit(students[i].id[j])){
                printf("警告：文件 %s 的第 %d 行学号格式错误\n", filename, i + 1);
                errorFlag = 1;
                break;
            }
        }

        // 验证成绩范围
        if (!errorFlag && (students[i].score.iCS < 0 || students[i].score.iCS > 100 ||
            students[i].score.PDP < 0 || students[i].score.PDP > 100 ||
            students[i].score.DS < 0 || students[i].score.DS > 100 ||
            students[i].score.DL < 0 || students[i].score.DL > 100)) {
            printf("警告：文件 %s 的第 %d 行成绩超出范围(0-100)\n", filename, i + 1);
            errorFlag = 1;
        }


        if(errorFlag){
            for (int j = i; j < (int)read - 1; j++) {
                students[j] = students[j + 1];
            }
            recordCount--;
        }
        
    }
    fclose(file);
    return recordCount;
}