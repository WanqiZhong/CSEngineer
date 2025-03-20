#ifndef STUDENT_H
#define STUDENT_H

#define MAX_STUDENTS 45
#define NAME_LENGTH 32
#define ID_LENGTH 20

/* 课程结构体 */
typedef struct {
    float iCS;    
    float PDP;    
    float DS;     
    float DL;     
    float total;  
    float average; 
} COURSE;

/* 学生结构体 */
typedef struct {
    char id[ID_LENGTH];        
    char name[NAME_LENGTH];    
    COURSE score;              
} STUDENT;

/* 成绩等级枚举 */
typedef enum {
    A,       // 优秀（90~100）
    B,       // 良好（80~89）
    C,       // 中等（70~79）
    D,       // 及格（60~69）
    F        // 不及格（0~59）
} GRADE_LEVEL;

/* 统计结构体 */
typedef struct {
    int count[5];        
    float percent[5];   
} STATISTICS;

#endif /* STUDENT_H */