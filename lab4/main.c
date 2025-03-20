#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>
#include "student.h"
#include "print.h"
#include "search.h"
#include "sort.h"
#include "fileop.h"
#include "calculate.h"

// 打印函数
void printMenu();
void printAllStudents(STUDENT students[], int count);
void printStudentsWithTotalAndAverage(STUDENT students[], int count);
void printCourseAverages(float averages[4]);
void printGradeStatistics(int courseIndex, STATISTICS* stats);

// 搜索函数
int searchByName(STUDENT students[], int count, const char* name);
int searchById(STUDENT students[], int count, const char* id);
void displayStudent(const STUDENT* student);

// 计算函数
void calculateStudentTotalAndAverage(STUDENT* student);
void calculateAllStudentsTotalAndAverage(STUDENT students[], int count);
void calculateCourseAverages(STUDENT students[], int count, float averages[4]);
void analyzeGradeDistribution(STUDENT students[], int count, int courseIndex, STATISTICS* stats);

// 文件操作函数
int saveStudentsToTextFile(const char* filename, STUDENT students[], int count);
int loadStudentsFromTextFile(const char* filename, STUDENT students[], int maxCount);
int saveStudentsToBinaryFile(const char* filename, STUDENT students[], int count);
int loadStudentsFromBinaryFile(const char* filename, STUDENT students[], int maxCount);

// 排序函数
void sortStudentsByCourse(STUDENT students[], int count, int courseIndex);

// 全局变量
STUDENT students[MAX_STUDENTS];  // 学生数组
int studentCount = 0;            // 当前学生数量
int classStudentCount = 0;       // 班级学生数量

/**
 * 添加一个学生记录
 */
void appendRecord() {
    if (studentCount >= classStudentCount) {
        printf("错误: 已达到班级最大学生数量 %d\n", classStudentCount);
        return;
    }
    
    STUDENT newStudent;
    
    printf("请输入学生信息:\n");
    printf("学号: ");
    char id[ID_LENGTH];
    int readFlag = 0;

    scanf("%s", id);
    
    // 检查是否纯数字
    for(int i = 0; i < strlen(id); i++){
        if(!isdigit(id[i])){
            printf("错误: 学号必须是纯数字\n");
            while (getchar() != '\n');
            return;
        }
    }
    strcpy(newStudent.id, id);
    
    // 检查学号是否已存在
    if (searchById(students, studentCount, id) != -1) {
        printf("错误: 学号 %s 已存在\n", newStudent.id);
        return;
    }
    
    printf("姓名: ");
    scanf("%s", newStudent.name);
    
    printf("计算机系统(iCS)成绩: ");
    readFlag = scanf("%f", &newStudent.score.iCS);
    if (readFlag != 1) {
        printf("错误: 成绩读取错误\n");
        // 清空缓冲区
        while (getchar() != '\n');
        return;
    }
    if (newStudent.score.iCS < 0 || newStudent.score.iCS > 100) {
        printf("错误: 成绩必须在0-100分之间\n");
        return;
    }
    
    printf("程序设计实践(PDP)成绩: ");
    readFlag = scanf("%f", &newStudent.score.PDP);
    if (readFlag != 1) {
        printf("错误: 成绩读取错误\n");
        while (getchar() != '\n');
        return;
    }
    if (newStudent.score.PDP < 0 || newStudent.score.PDP > 100) {
        printf("错误: 成绩必须在0-100分之间\n");
        return;
    }
    
    printf("数据结构(DS)成绩: ");
    readFlag = scanf("%f", &newStudent.score.DS);
    if (readFlag != 1) {
        printf("错误: 成绩读取错误\n");
        while (getchar() != '\n');
        return;
    }
    if (newStudent.score.DS < 0 || newStudent.score.DS > 100) {
        printf("错误: 成绩必须在0-100分之间\n");
        return;
    }
    
    printf("数字逻辑(DL)成绩: ");
    readFlag = scanf("%f", &newStudent.score.DL);
    if (readFlag != 1) {
        printf("错误: 成绩读取错误\n");
        while (getchar() != '\n');
        return;
    }
    if (newStudent.score.DL < 0 || newStudent.score.DL > 100) {
        printf("错误: 成绩必须在0-100分之间\n");
        return;
    }
    
    // 计算总分和平均分
    calculateStudentTotalAndAverage(&newStudent);
    
    // 添加到学生数组
    students[studentCount++] = newStudent;
    
    printf("成功添加学生记录\n");
}

/**
 * 通过姓名查找学生
 */
void searchStudentByName() {
    if(studentCount == 0){
        printf("当前没有学生记录\n");
        return;
    }
    
    char name[NAME_LENGTH];
    
    printf("请输入要查找的学生姓名: ");
    scanf("%s", name);
    
    int index = searchByName(students, studentCount, name);
    if (index != -1) {
        printf("找到学生信息:\n");
        printHeader();
        displayStudent(&students[index]);
    } else {
        printf("未找到姓名为 %s 的学生\n", name);
    }
}

/**
 * 通过学号查找学生
 */
void searchStudentById() {
    if(studentCount == 0){
        printf("当前没有学生记录\n");
        return;
    }

    char id[ID_LENGTH];
    
    printf("请输入要查找的学生学号: ");
    scanf("%s", id);
    
    int index = searchById(students, studentCount, id);
    if (index != -1) {
        printf("找到学生信息:\n");
        displayStudent(&students[index]);
    } else {
        printf("未找到学号为 %s 的学生\n", id);
    }
}

/**
 * 修改学生记录
 */
void modifyStudentById() {
    if(studentCount == 0){
        printf("当前没有学生记录\n");
        return;
    }

    char id[ID_LENGTH];
    
    printf("请输入要修改的学生学号: ");
    scanf("%s", id);
    
    int index = searchById(students, studentCount, id);
    if (index != -1) {
        printf("找到学生，当前信息:\n");
        printHeader();
        displayStudent(&students[index]);
        
        STUDENT newStudent;
        int readFlag = 0;
        
        printf("\n请输入新的成绩信息:\n");
        
        printf("计算机系统(iCS)成绩: ");
        readFlag = scanf("%f", &newStudent.score.iCS);
        if (readFlag != 1) {
            printf("错误: 成绩读取错误\n");
            while (getchar() != '\n');
            return;
        }
        if (newStudent.score.iCS < 0 || newStudent.score.iCS > 100) {
            printf("错误: 成绩必须在0-100分之间\n");
            return;
        }
        
        printf("程序设计实践(PDP)成绩: ");
        readFlag = scanf("%f", &newStudent.score.PDP);
        if (readFlag != 1) {
            printf("错误: 成绩读取错误\n");
            while (getchar() != '\n');
            return;
        }
        if (newStudent.score.PDP < 0 || newStudent.score.PDP > 100) {
            printf("错误: 成绩必须在0-100分之间\n");
            return;
        }
        printf("数据结构(DS)成绩: ");
        readFlag = scanf("%f", &newStudent.score.DS);
        if (readFlag != 1) {
            printf("错误: 成绩读取错误\n");
            while (getchar() != '\n');
            return;
        }
        if (newStudent.score.DS < 0 || newStudent.score.DS > 100) {
            printf("错误: 成绩必须在0-100分之间\n");
            return;
        }

        printf("数字逻辑(DL)成绩: ");
        readFlag = scanf("%f", &newStudent.score.DL);
        if (readFlag != 1) {
            printf("错误: 成绩读取错误\n");
            while (getchar() != '\n');
            return;
        }
        if (newStudent.score.DL < 0 || newStudent.score.DL > 100) {
            printf("错误: 成绩必须在0-100分之间\n");
            return;
        }

        students[index].score = newStudent.score;
        // 重新计算总分和平均分
        calculateStudentTotalAndAverage(&students[index]);
        
        printf("成功修改学生信息\n");
    } else {
        printf("未找到学号为 %s 的学生\n", id);
    }
}

/**
 * 删除学生记录
 */
void deleteStudentById() {
    if(studentCount == 0){
        printf("当前没有学生记录\n");
        return;
    }

    char id[ID_LENGTH];
    
    printf("请输入要删除的学生学号: ");
    scanf("%s", id);
    
    int index = searchById(students, studentCount, id);
    if (index != -1) {
        printf("找到学生，即将删除:\n");
        displayStudent(&students[index]);
        
        // 确认删除
        char confirm;
        printf("确认删除? (Y/N): ");
        scanf(" %c", &confirm);
        
        if (confirm == 'Y' || confirm == 'y') {
            for (int i = index; i < studentCount - 1; i++) {
                students[i] = students[i + 1];
            }
            studentCount--;
            
            printf("成功删除学生记录\n");
        } else {
            printf("取消删除操作\n");
        }
    } else {
        printf("未找到学号为 %s 的学生\n", id);
    }
}

/**
 * 计算并显示所有学生的总分和平均分
 */
void calculateAndDisplayTotalAndAverage() {
    calculateAllStudentsTotalAndAverage(students, studentCount);
    printStudentsWithTotalAndAverage(students, studentCount);
}

/**
 * 计算并显示各科平均分
 */
void calculateAndDisplayCourseAverages() {
    float averages[4];
    calculateCourseAverages(students, studentCount, averages);
    printCourseAverages(averages);
}

/**
 * 按课程成绩排序并显示
 */
void sortAndDisplayByCourse() {
    int courseIndex;
    printf("请选择排序的课程:\n");
    printf("0. 计算机系统(iCS)\n");
    printf("1. 程序设计实践(PDP)\n");
    printf("2. 数据结构(DS)\n");
    printf("3. 数字逻辑(DL)\n");
    printf("4. 总分\n");
    printf("请输入选择(0-4): ");
    scanf("%d", &courseIndex);
    
    if (courseIndex < 0 || courseIndex > 4) {
        printf("无效的课程选择\n");
        return;
    }
    
    STUDENT sortedStudents[MAX_STUDENTS];
    memcpy(sortedStudents, students, studentCount * sizeof(STUDENT));
    
    // 排序
    sortStudentsByCourse(sortedStudents, studentCount, courseIndex);
    
    // 显示排序结果
    char *courseNames[] = {"计算机系统(iCS)", "程序设计实践(PDP)", 
                          "数据结构(DS)", "数字逻辑(DL)", "总分"};
    printf("\n按%s降序排序结果:\n", courseNames[courseIndex]);
    printAllStudents(sortedStudents, studentCount);
}

/**
 * 统计分析各科成绩分布并显示
 */
void statisticAnalysisForCourses() {
    STATISTICS stats;
    
    printf("\n=== 各科成绩统计分析 ===\n");
    
    // 分别统计各科成绩
    for (int i = 0; i < 4; i++) {
        analyzeGradeDistribution(students, studentCount, i, &stats);
        printGradeStatistics(i, &stats);
    }
}

/**
 * 保存学生记录到文件
 */
void saveRecordToFile() {
    int fileType;
    char filename[100];
    
    printf("请选择文件类型:\n");
    printf("1. 文本文件\n");
    printf("2. 二进制文件\n");
    printf("请输入选择(1-2): ");
    scanf("%d", &fileType);
    
    int result;
    if (fileType == 1) {
        result = saveStudentsToTextFile(filename, students, studentCount);
    } else if (fileType == 2) {
        result = saveStudentsToBinaryFile(filename, students, studentCount);
    } else {
        printf("无效的文件类型选择\n");
        while (getchar() != '\n');
        return;
    }
    
    printf("请输入文件名: ");
    scanf("%s", filename);

    if (result >= 0) {
        printf("成功保存 %d 条记录到文件 %s\n", result, filename);
    } else {
        printf("保存文件失败\n");
    }
}

/**
 * 从文件加载学生记录
 */
void loadRecordFromFile() {
    int fileType;
    char filename[100];
    
    printf("请选择文件类型:\n");
    printf("1. 文本文件\n");
    printf("2. 二进制文件\n");
    printf("请输入选择(1-2): ");
    scanf("%d", &fileType);
    
    int result;
    if (fileType == 1) {
        result = loadStudentsFromTextFile(filename, students, classStudentCount);
    } else if (fileType == 2) {
        result = loadStudentsFromBinaryFile(filename, students, classStudentCount);
    } else {
        printf("无效的文件类型选择\n");
        while (getchar() != '\n');
        return;
    }

    printf("请输入文件名: ");
    scanf("%s", filename);
    
    if (result >= 0) {
        studentCount = result;
        printf("成功从文件 %s 加载 %d 条记录\n", filename, result);
    } else {
        printf("加载文件失败\n");
    }
}

/**
 * 主函数
 */
int main() {
    int choice;
    
    printf("欢迎使用学生成绩管理系统\n");
    
    // 读取班级人数
    do {
        printf("请输入班级人数(最多%d人): ", MAX_STUDENTS);
        scanf("%d", &classStudentCount);
        if (classStudentCount <= 0 || classStudentCount > MAX_STUDENTS) {
            printf("输入的班级人数应当在1-%d之间\n", MAX_STUDENTS);
            while (getchar() != '\n');
        }
    } while (classStudentCount <= 0 ||classStudentCount > MAX_STUDENTS);
    
    do {
        printMenu();
        scanf("%d", &choice);
        printf("========================================\n");
        
        switch (choice) {
            case 1:  // 添加记录
                appendRecord();
                break;
                
            case 2:  // 按姓名查询
                searchStudentByName();
                break;
                
            case 3:  // 按学号查询
                searchStudentById();
                break;
                
            case 4:  // 修改记录
                modifyStudentById();
                break;
                
            case 5:  // 删除记录
                deleteStudentById();
                break;
                
            case 6:  // 计算总分和平均分
                calculateAndDisplayTotalAndAverage();
                break;
                
            case 7:  // 计算各科平均分
                calculateAndDisplayCourseAverages();
                break;
                
            case 8:  // 按成绩排序
                sortAndDisplayByCourse();
                break;
                
            case 9:  // 统计分析
                statisticAnalysisForCourses();
                break;
                
            case 10:  // 保存记录
                saveRecordToFile();
                break;
                
            case 11:  // 加载记录
                loadRecordFromFile();
                break;
                
            case 0:  // 退出
                printf("退出程序\n");
                break;
                
            default:
                printf("无效的选择，请重新输入\n");
                while (getchar() != '\n');

        }
        // 延时
        sleep(1);
        
    } while (choice != 0);    
    return 0;
}