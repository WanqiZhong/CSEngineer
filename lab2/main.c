#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fileop.h"

/*
    打印使用帮助信息
*/
void printUsage(const char* programName) {
    printf("使用方式: %s [-h] [-tr INPUT_FILE] [-tw INPUT_FILE OUTPUT_FILE] [-fw OUTPUT_FILE_PREFIX] [-fr INPUT_FILE] [-sw OUTPUT_FILE] [-sr INPUT_FILE]\n\n", programName);
    printf("可选参数:\n");
    printf("  -h, --help                  显示帮助信息\n");
    printf("  -tr INPUT_FILE              读取指定文本文件并显示内容\n");
    printf("  -tw INPUT_FILE OUTPUT_FILE  读取指定文本文件并写入到输出文件\n");
    printf("  -fw OUTPUT_PATH             浮点与字符数组文件写操作\n");
    printf("  -fr INPUT_FILE              浮点数组二进制文件读取操作\n");
    printf("  -sw OUTPUT_FILE             结构体数组文件写操作\n");
    printf("  -sr INPUT_FILE              结构体数组文件读取操作\n");
}

/*
    生成测试用的浮点数组
*/
void generateFloatArray(float* array, int size) {
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        array[i] = (float)rand() / RAND_MAX * 1000.0f;
    }
}

/*
    生成测试用的字符数组
*/
void generateCharArray(char* array, int size) {
    srand(time(NULL) + 100);  // 使用不同的种子
    for (int i = 0; i < size; i++) {
        array[i] = 'A' + (rand() % 26);
    }
}

/*
    生成测试用的结构体数组
*/
void generateStudentArray(Student* students, int count) {
    srand(time(NULL) + 200);  // 使用不同的种子
    char names[10][10] = {"Zhangsan", "Lisi", "Wangwu", "Zhaoliu", "Liuqi", "Zhansan", "Lisi", "Wangwu", "Zhaoliu", "Liuqi"};
    
    for (int i = 0; i < count; i++) {
        students[i].id = 2021110000 + i;
        strcpy(students[i].name, names[i % 10]);
        
        for (int j = 0; j < 3; j++) {
            students[i].scores[j] = 60.0f + (float)(rand() % 41);
        }
        students[i].scores[3] = 50.0f + (float)(rand() % 31);
    }
}

int main(int argc, char* argv[]) {
    Student students[MAX_RECORDS];
    char* programName = argv[0];
    
    if (argc < 2) {
        printf("错误: 缺少必要参数\n");
        printUsage(programName);
        return 1;
    }
    
    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        printUsage(programName);
        return 0;
    } else if (strcmp(argv[1], "-tr") == 0) {
        if (argc < 3) {
            printf("错误: -tr 选项需要一个参数: INPUT_FILE\n");
            return 1;
        }
        
        const char* inputFile = argv[2];
        int count = readStudentsFromTextFile(inputFile, students, MAX_RECORDS);
        
        if (count >= 0) {
            printf("执行文本读取操作\n");
            printf("从文件 %s 读取了 %d 条记录：\n", inputFile, count);
            for (int i = 0; i < count; i++) {
                printStudent(&students[i]);
            }
        } else {
            printf("错误: 从文件 %s 读取失败\n", inputFile);
            return 1;
        }
    } else if (strcmp(argv[1], "-tw") == 0) {
        if (argc < 4) {
            printf("错误: -tw 选项需要两个参数: INPUT_FILE OUTPUT_FILE\n");
            return 1;
        }
        
        const char* inputFile = argv[2];
        const char* outputFile = argv[3];
        int count = readStudentsFromTextFile(inputFile, students, MAX_RECORDS);
        
        if (count > 0) {
            int written = writeStudentsToTextFile(outputFile, students, count);
            if (written >= 0) {
                printf("执行文本读取和写入操作\n");
                printf("从文件 '%s' 读取了 %d 条记录\n", inputFile, count);
                printf("写入 %d 条记录到文件 '%s'\n", written, outputFile);
            } else {
                printf("错误: 写入文件 %s 失败\n", outputFile);
                return 1;
            }
        } else {
            printf("错误: 从文件 %s 读取失败\n", inputFile);
            return 1;
        }
    } else if (strcmp(argv[1], "-fw") == 0) {
     
        printf("执行浮点与字符数组文件写操作\n");
        if (argc < 3) {
            printf("错误: -fw 选项需要一个参数: OUTPUT_PATH\n");
            return 1;
        }

        const char* outputFilePath = argv[2];
        float floatArray[100];
        char charArray[100];
        
        generateFloatArray(floatArray, 100);
        generateCharArray(charArray, 100);
        

        // 根据 outputFilePath 作为路径，生成浮点数组二进制文件名和文本文件名
        char floatBinFileName[256];
        char floatTxtFileName[256];
        char charBinFileName[256];
        char charTxtFileName[256];
        
        sprintf(floatBinFileName, "%s/float_bin.dat", outputFilePath);
        sprintf(floatTxtFileName, "%s/float_txt.txt", outputFilePath);
        sprintf(charBinFileName, "%s/char_bin.dat", outputFilePath);
        sprintf(charTxtFileName, "%s/char_txt.txt", outputFilePath);
    

        int floatBinWritten = writeFloatArrayToBinaryFile(floatBinFileName, floatArray, 100);
        int floatTxtWritten = writeFloatArrayToTextFile(floatTxtFileName, floatArray, 100);
        int charBinWritten = writeCharArrayToBinaryFile(charBinFileName, charArray, 100);
        int charTxtWritten = writeCharArrayToTextFile(charTxtFileName, charArray, 100);
        
        printf("浮点数组二进制文件写入：%d 个元素\n", floatBinWritten);
        printf("浮点数组文本文件写入：%d 个元素\n", floatTxtWritten);
        printf("字符数组二进制文件写入：%d 个元素\n", charBinWritten);
        printf("字符数组文本文件写入：%d 个元素\n", charTxtWritten);
        
        // 显示文件大小
        FILE *f1 = fopen(floatBinFileName, "rb");
        FILE *f2 = fopen(floatTxtFileName, "r");
        FILE *f3 = fopen(charBinFileName, "rb");
        FILE *f4 = fopen(charTxtFileName, "r");
        
        if (f1 && f2 && f3 && f4) {
            fseek(f1, 0, SEEK_END);
            fseek(f2, 0, SEEK_END);
            fseek(f3, 0, SEEK_END);
            fseek(f4, 0, SEEK_END);
            
            long size1 = ftell(f1);
            long size2 = ftell(f2);
            long size3 = ftell(f3);
            long size4 = ftell(f4);
            
            printf("\n文件大小比较：\n");
            printf("浮点数组二进制文件：%ld 字节\n", size1);
            printf("浮点数组文本文件：%ld 字节\n", size2);
            printf("字符数组二进制文件：%ld 字节\n", size3);
            printf("字符数组文本文件：%ld 字节\n", size4);
            
            fclose(f1);
            fclose(f2);
            fclose(f3);
            fclose(f4);
        }
        
    } else if (strcmp(argv[1], "-fr") == 0) {
    
        printf("执行浮点数组二进制文件读取操作\n");
        if (argc < 3) {
            printf("错误: -fr 选项需要一个参数: BINARY_FILE\n");
            return 1;
        }
        
        const char* binaryFile = argv[2];
        float floatArray[100] = {0};
        int count = readFloatArrayFromBinaryFile(binaryFile, floatArray, 100);
        
        if (count >= 0) {
            printf("从二进制文件读取了 %d 个浮点数\n", count);
            for (int i = 0; i < 100 && i < count; i++) {
                printf("%.6f ", floatArray[i]);
                if ((i + 1) % 5 == 0) printf("\n");
            }
            printf("\n");
        } else {
            printf("错误: 读取二进制文件失败\n");
            return 1;
        }
    } else if (strcmp(argv[1], "-sw") == 0) {

        if (argc < 3) {
            printf("错误: -sw 选项需要一个参数: OUTPUT_FILE\n");
            return 1;
        }
        
        const char* outputFile = argv[2];
        printf("执行结构体数组二进制文件写入操作\n");
        
        // 准备测试数据
        Record testRecords[10];
        generateStudentArray(testRecords, 10);
        
        // 写入文件
        int written = writeRecordsToBinaryFile(outputFile, testRecords, 10);
        
        if (written >= 0) {
            printf("写入 %d 个结构体到二进制文件 '%s'\n", written, outputFile);
        } else {
            printf("错误: 写入二进制文件失败\n");
            return 1;
        }
    } else if (strcmp(argv[1], "-sr") == 0) {
        
        if (argc < 3) {
            printf("错误: -sr 选项需要一个参数：INPUT_FILE\n");
            return 1;
        }
        
        const char* binaryFile = argv[2];
        printf("执行结构体数组二进制文件读取测试\n");
        
        // 读取文件
        Record readRecords[MAX_RECORDS];
        int count = readRecordsFromBinaryFile(binaryFile, readRecords, MAX_RECORDS);
        
        if (count > 0) {
            // 显示文件信息
            FILE *f = fopen(binaryFile, "rb");
            if (f) {
                fseek(f, 0, SEEK_END);
                long size = ftell(f);
                fclose(f);
                printf("二进制文件大小：%ld 字节\n", size);
                printf("结构体大小：%ld 字节\n", sizeof(Student));
                printf("结构体数量：%ld 个\n", size / sizeof(Student));
            }
            
            printf("\n从二进制文件读取了 %d 个结构体\n", count);
            printf("结构体内容：\n");
            for (int i = 0; i < count; i++) {
                printRecord(&readRecords[i]);
            }
        } else {
            printf("错误: 读取二进制文件失败\n");
            return 1;
        }
    } else {
        printf("错误: 不支持的选项: %s\n", argv[1]);
        printUsage(programName);
        return 1;
    }
    
    return 0;
}