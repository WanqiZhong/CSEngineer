#include "sort.h"

// #define Debug
int dataType = STUDENT;

// 提供比较函数
int   cmp(ElemType * a, ElemType *b);
// 生成随机数据
void  generateData(ElemType * A, int num);
void  randName(char * name);
void  randID(char * id);
// 格式化输出
void  output(ElemType A[],int n, char * info);
void  printUsage(const char* programName);
void  generateFloatArray(float *arr, int size, float duplicateRate);

int main(int argc, char **argv)
{
   size_t t1, t2;
   int size;
   ElemType *orig, *toSort;
   int (*cmpare)(ElemType * a, ElemType *b);
   void (*sortFunc)(ElemType *, int, int (*)(ElemType *, ElemType *)) = &SelectSort; // 默认选择排序
   char algorithmName[20] = "选择排序"; // 默认算法名称
   char dataTypeName[20] = "结构体";   // 默认数据类型名称
   cmpare = &cmp;
   float duplicateRates[] = {0.0, 0.05, 0.1, 0.2, 0.4, 0.8};

   // 参数不足显示帮助
   if(argc < 2) {
       printUsage(argv[0]);
       return 1;
   }
   
   // 检查是否需要显示帮助
   if(strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
       printUsage(argv[0]);
       return 0;
   }

   // 读取数组大小
   if(argc < 3) {
       printf("错误: 缺少数组大小参数\n");
       return 1;
   }
   
   sscanf(argv[1], "%d", &size);
   if(size <= 0) {
       printf("错误: 数组大小必须大于0\n");
       return 1;
   }

   // 处理数据类型参数
    int allTest = 1;
   if(argc >= 3) {
       if(strcmp(argv[2], "-i") == 0) {
           dataType = INT;
           strcpy(dataTypeName, "整数");
       } else if(strcmp(argv[2], "-f") == 0) {
           dataType = FLOAT;
           strcpy(dataTypeName, "浮点数");
       } else if(strcmp(argv[2], "-d") == 0) {
           dataType = DOUBLE;
           strcpy(dataTypeName, "双精度浮点数");
       } else if(strcmp(argv[2], "-s") == 0) {
           dataType = STUDENT;
           strcpy(dataTypeName, "结构体");
       } else if(strcmp(argv[2], "-a") == 0) {
            dataType = FLOAT;
            strcpy(dataTypeName, "浮点数");
            allTest = 6;
            printf("浮点数重复数据测试\n");  
            printf("强制设定数组大小为1000000\n");
            printf("强制使用快速排序\n");
            size = 1000000;
            #ifdef NewQuickSort   // 在编译选项中启用
                sortFunc = &QuickSort3Way; 
                strcpy(algorithmName, "三路快速排序");
            #else
                sortFunc = &QuickSort;
                strcpy(algorithmName, "快速排序");
            #endif
       } else {
           printf("错误: 无效的数据类型参数\n");
           printUsage(argv[0]);
           return 1;
       }
   }

   // 处理排序算法参数
   if(argc >= 4) {
       if(strcmp(argv[3], "-s") == 0) {
           sortFunc = &SelectSort;
           strcpy(algorithmName, "选择排序");
       } else if(strcmp(argv[3], "-b") == 0) {
           sortFunc = &BubbleSort;
           strcpy(algorithmName, "冒泡排序");
       } else if(strcmp(argv[3], "-i") == 0) {
           sortFunc = &InsertSort;
           strcpy(algorithmName, "插入排序");
       } else if(strcmp(argv[3], "-m") == 0) {
           sortFunc = &MergeSort;
           strcpy(algorithmName, "归并排序");
       } else if(strcmp(argv[3], "-q") == 0) {
           sortFunc = &QuickSort;
           strcpy(algorithmName, "快速排序");
       } else if(strcmp(argv[3], "-h") == 0) {
           sortFunc = &HeapSort;
           strcpy(algorithmName, "堆排序");
       } else if(strcmp(argv[3], "-a") == 0) {
            #ifdef NewQuickSort
                sortFunc = &QuickSort3Way;
                strcpy(algorithmName, "三路快速排序");
            #else
                sortFunc = &QuickSort;
                strcpy(algorithmName, "快速排序");
            #endif
           allTest = 6;
           printf("测试所有排序算法\n");
       } else {
           printf("错误: 无效的排序算法参数\n");
           printUsage(argv[0]);
           return 1;
       }
   }

   // 分配内存并生成数据
   orig = (ElemType*) malloc(sizeof(ElemType) * size);
   toSort = (ElemType*) malloc(sizeof(ElemType) * size);
   generateData(orig, size);

    for (int i = 0; i < allTest; i++) {
        if(allTest == 6){
            if(strcmp(argv[2], "-a") == 0){
                generateFloatArray(orig, size, duplicateRates[i]);
                memcpy(toSort, orig, size * sizeof(ElemType));
                printf("重复率: %.0f%%\n", duplicateRates[i]*100);
            }
            else{
                memcpy(toSort, orig, size * sizeof(ElemType));  // 复制原始数据到toSort，确保在每次排序前数据不变
                switch(i) {
                    case 0:
                        sortFunc = &SelectSort;
                        strcpy(algorithmName, "选择排序");
                        break;
                    case 1:
                        sortFunc = &BubbleSort;
                        strcpy(algorithmName, "冒泡排序");
                        break;
                    case 2:
                        sortFunc = &InsertSort;
                        strcpy(algorithmName, "插入排序");
                        break;
                    case 3:
                        sortFunc = &MergeSort;
                        strcpy(algorithmName, "归并排序");
                        break;
                    case 4:
                        #ifdef NewQuickSort
                            sortFunc = &QuickSort3Way;
                            strcpy(algorithmName, "三路快速排序");
                        #else
                            sortFunc = &QuickSort;
                            strcpy(algorithmName, "快速排序");
                        #endif
                        break;
                    case 5:
                        sortFunc = &HeapSort;
                        strcpy(algorithmName, "堆排序");
                        break;
                }
            }
        }else{
            memcpy(toSort, orig, size * sizeof(ElemType));
        }      
    #ifdef Debug
        output(toSort, size, "排序前: ");
    #endif
        printf("数据类型: %s\n", dataTypeName);
        printf("使用算法: %s\n", algorithmName);
        t1 = clock();  // 记录排序开始时间
        sortFunc(toSort, size, cmpare);
        t2 = clock();  // 记录排序结束时间
    #ifdef Debug
        output(toSort, size, "排序后: ");
    #endif
        printf("在 %f 秒内对 %d 个对象进行排序\n", (t2-t1)/((double)CLOCKS_PER_SEC), size);  
    }
   
   // 释放内存
   free(orig);
   free(toSort);
   return 0;
}

int cmp(ElemType * a, ElemType *b)
{
    if(dataType == INT)
    {
        if(*((int*)a) == *((int*)b))
            return 0;
        else if (*((int*)a) > *((int*)b))
            return 1;
        else
            return -1;
    }
    else if(dataType == FLOAT)
    {
        if(*((float*)a) == *((float*)b))
            return 0;
        else if (*((float*)a) > *((float*)b))
            return 1;
        else
            return -1;
    }
    else if(dataType == DOUBLE)
    {
        if(*((double*)a) == *((double*)b))
            return 0;
        else if (*((double*)a) > *((double*)b))
            return 1;
        else
            return -1;
    }
    else
    {
        STU * pa = (STU *)a;
        STU * pb = (STU *)b;
        if(pa->total == pb->total)
            return 0;
        else if (pa->total > pb->total)
            return 1;
        else
            return -1;
    }
}

/*
    根据数据类型生成随机测试数据
 */
void  generateData(ElemType * A, int num)
{
    if(dataType == INT)
    {
        // 生成整型随机数，范围[0, 10*num)
        for(int i=0; i<num; i++)
        {
            *((int*)(A+i)) = rand()%(10*num);
        }
    }
    else if(dataType == FLOAT)
    {
        // 生成浮点型随机数，范围[0, 10*num)
        for(int i=0; i<num; i++)
        {
            *((float*)(A+i)) = rand()%(10*num);
        }
    }
    else if(dataType == DOUBLE)
    {
        // 生成双精度型随机数，范围[0, 10*num)
        for(int i=0; i<num; i++)
        {
            *((double*)(A+i)) = rand()%(10*num);
        }
    }
    else
    {
        // 生成学生结构体随机数据
        // 包括随机学号、姓名和5门课程成绩
        for(int i=0; i<num; i++)
        {
            randID(((STU*)(A+i))->id);
            randName( ((STU*)(A+i))->name);
            ((STU*)(A+i))->total = 0;
            for(int j=0; j<5; j++)
            {
                // 生成两位小数的随机成绩
                ((STU*)(A+i))->score[j] = (rand()%10000)/((double) 100);
                ((STU*)(A+i))->total += ((STU*)(A+i))->score[j];
            }
        }
    }
}

void generateFloatArray(float *arr, int size, float duplicateRate) {
    // 设置随机种子
    srand(time(NULL));
    
    // 计算重复元素数量
    int duplicateCount = (int)(size * duplicateRate);
    int uniqueCount = size - duplicateCount;
    
    // 生成所有唯一元素
    for (int i = 0; i < uniqueCount; i++) {
        arr[i] = (float)rand() / RAND_MAX * 1000000.0;
    }
    
    // 如果有重复元素，选择一个值进行重复
    if (duplicateCount > 0) {
        float duplicateValue = arr[0]; // 使用第一个元素作为重复值
        
        // 填充重复元素
        for (int i = uniqueCount; i < size; i++) {
            arr[i] = duplicateValue;
        }
    }
}

void  printUsage(const char* programName)
{
    printf("使用方式: %s [size] [data_type] [sort_algorithm]\n\n", programName);
    printf("参数:\n");
    printf("size: 数组大小\n");
    printf("data_type: 数据类型， -i 整数， -f 浮点数， -d 双精度浮点数， -s 结构体， -a 浮点数重复数据测试\n");
    printf("sort_algorithm: 排序算法， -s 选择排序， -b 冒泡排序， -i 插入排序， -m 归并排序， -q 快速排序， -h 堆排序，  -a 测试所有\n");
}

void  randName(char * name)
{
    char ALPHA[26]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char alpha[26]="abcdefghijklmnopqrstuvwxyz";
    int len = 1+ rand()%18;
    // 从ALPHA中随机选择一个字符作为姓名首字母
    name[0] = ALPHA[rand()%26];
    for(int i=1; i<len; i++)
    {
        // 从alpha中随机选择一个字符作为姓名其他字符
        name[i] = alpha[rand()%26];
    }
    name[len] = '\0';

}
void  randID(char * id)
{
    char buf[20] = "2021031";
    char buf1[3];
    char buf2[5];
    int classNo = rand()%100; // 生成0-99之间的随机班级号
    int stuNo = rand()%10000; // 生成0-9999之间的随机学号
    sprintf(buf1, "%02d", classNo); // 将班级号格式化为2位数字
    buf1[2] = '\0'; // 添加字符串结束符
    sprintf(buf2,  "%04d", stuNo); // 将学号格式化为4位数字
    buf2[4] = '\0'; // 添加字符串结束符
    strcat(buf, buf1); 
    strcat(buf, buf2);
    strcpy(id, buf);
}

void output(ElemType A[],int n, char * info)
{
    printf("%s\n", info);
    switch(dataType)
    {
    case INT:
        for(int i=0; i<n; i++){
            printf("%d ", *((int*)(A+i)));
        }
        printf("\n");
        break;

    case FLOAT:
        for(int i=0; i<n; i++){
            printf("%f ", *((float*)(A+i)));
        }
        printf("\n");
        break;
    case DOUBLE:
        for(int i=0; i<n; i++){
            printf("%f ", *((double*)(A+i)));
        }
        printf("\n");
        break;
    case STUDENT:
        for(int i=0; i<n; i++){
            printf("%s %-20s ", ((STU*)(A+i))->id, ((STU*)(A+i))->name);
            for(int j=0; j<5; j++)
            {
                printf("%f ", ((STU*)(A+i))->score[j]);
            }
            printf("%f \n", ((STU*)(A+i))->total);
        }
        break;
    default:
        break;
    }
}
