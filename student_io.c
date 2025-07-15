/**
 * @file student_io.c
 * @brief 学生数据文件输入输出操作实现
 * @note 负责学生数据的文件读写、CSV解析等功能
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "globals.h"
#include "io_utils.h"
#include "string_utils.h"
#include "statistical_analysis.h"

/**
 * @brief 解析CSV行中的基本学生信息
 * @details 从CSV行中解析学号、姓名、年龄、性别等基本信息
 * @param student 指向要填充的学生结构体的指针
 * @param token 当前CSV token指针的指针
 * @return true 解析成功，false 解析失败
 */
static bool parseBasicStudentInfo(Student *student, char **token)
{
    // 学号
    if (*token == NULL) return false;
    strncpy(student->studentID, *token, MAX_ID_LENGTH - 1);
    
    // 姓名
    *token = strtok(NULL, ",");
    if (*token == NULL) return false;
    strncpy(student->name, *token, MAX_NAME_LENGTH - 1);
    
    // 年龄
    *token = strtok(NULL, ",");
    if (*token == NULL) return false;
    student->age = atoi(*token);
    
    // 性别
    *token = strtok(NULL, ",");
    if (*token == NULL) return false;
    student->gender = (*token)[0];
    
    // 课程数量
    *token = strtok(NULL, ",");
    if (*token == NULL) return false;
    student->courseCount = atoi(*token);
    
    return true;
}

/**
 * @brief 解析CSV行中的课程信息
 * @details 从CSV行中解析课程名称和成绩信息
 * @param student 指向要填充的学生结构体的指针
 * @param token 当前CSV token指针的指针
 */
static void parseCourseInfo(Student *student, char **token)
{
    // 课程和成绩
    for (int i = 0; i < student->courseCount && i < MAX_COURSES; i++)
    {
        // 课程名称
        *token = strtok(NULL, ",");
        if (*token == NULL) break;
        strncpy(student->courses[i], *token, MAX_COURSE_NAME_LENGTH - 1);
        
        // 成绩
        *token = strtok(NULL, ",");
        if (*token == NULL) break;
        student->scores[i] = atof(*token);
    }
}

/**
 * @brief 解析CSV行中的统计信息
 * @details 从CSV行中解析总分和平均分信息
 * @param student 指向要填充的学生结构体的指针
 * @param token 当前CSV token指针的指针
 */
static void parseStatisticsInfo(Student *student, char **token)
{
    // 总分
    *token = strtok(NULL, ",");
    if (*token != NULL)
    {
        student->totalScore = atof(*token);
    }
    
    // 平均分
    *token = strtok(NULL, ",");
    if (*token != NULL)
    {
        student->averageScore = atof(*token);
    }
}

/**
 * @brief 解析单行CSV学生数据
 * @details 解析一行CSV数据并填充学生结构体
 * @param line CSV行数据
 * @param student 指向要填充的学生结构体的指针
 * @return true 解析成功，false 解析失败
 */
static bool parseStudentLine(char *line, Student *student)
{
    memset(student, 0, sizeof(Student));
    
    // 解析CSV行
    char *token = strtok(line, ",");
    if (token == NULL) return false;
    
    // 解析基本信息
    if (!parseBasicStudentInfo(student, &token)) return false;
    
    // 解析课程信息
    parseCourseInfo(student, &token);
    
    // 解析统计信息
    parseStatisticsInfo(student, &token);
    
    return true;
}

/**
 * @brief 从CSV文件加载学生数据
 * @details 从STUDENTS_FILE指定的CSV文件中读取学生信息并加载到内存中
 *          解析CSV格式数据，包括学号、姓名、年龄、性别、课程信息等
 *          如果文件不存在，会初始化为空的学生列表
 * @note 会跳过CSV文件的头部行，最多加载MAX_STUDENTS个学生
 * @note 加载完成后会设置statsNeedUpdate标志为true
 * @warning 如果CSV格式不正确，可能导致数据解析错误
 * @see STUDENTS_FILE, MAX_STUDENTS, Student结构体
 */
void loadStudentsFromFile()
{
    FILE *file = fopen(STUDENTS_FILE, "r");
    if (file == NULL)
    {
        studentCount = 0;
        printInfo("学生数据文件不存在，将创建新文件。");
        return;
    }
    
    char line[1024];
    studentCount = 0;
    
    // 跳过CSV头部
    if (fgets(line, sizeof(line), file) == NULL)
    {
        fclose(file);
        studentCount = 0;
        return;
    }
    
    // 读取学生数据
    while (fgets(line, sizeof(line), file) != NULL && studentCount < MAX_STUDENTS)
    {
        Student *student = &students[studentCount];
        
        if (parseStudentLine(line, student))
        {
            studentCount++;
        }
    }
    
    fclose(file);
    
    // 更新统计信息
    statsNeedUpdate = true;
}

/**
 * @brief 将学生数据保存到CSV文件
 * @details 将内存中的所有学生数据以CSV格式保存到STUDENTS_FILE文件中
 *          包含完整的CSV头部和所有学生的详细信息
 *          保存成功后会重置dataModified标志
 * @note CSV格式包括：学号、姓名、年龄、性别、课程数量、各课程名称和成绩、总分、平均分
 * @note 对于课程数量不足MAX_COURSES的学生，会用空值填充
 * @warning 如果文件无法创建或写入，会显示错误信息
 * @see STUDENTS_FILE, MAX_COURSES, dataModified
 */
void saveStudentsToFile()
{
    FILE *file = fopen(STUDENTS_FILE, "w");
    if (file == NULL)
    {
        printError("无法保存学生数据！");
        return;
    }

    // 写入CSV头部
    fprintf(file, "学号,姓名,年龄,性别,课程数量");
    for (int i = 0; i < MAX_COURSES; i++)
    {
        fprintf(file, ",课程%d,成绩%d", i + 1, i + 1);
    }
    fprintf(file, ",总分,平均分\n");

    // 写入学生数据
    for (int i = 0; i < studentCount; i++)
    {
        Student *student = &students[i];

        // 基本信息
        fprintf(file, "%s,%s,%d,%c,%d",
                student->studentID,
                student->name,
                student->age,
                student->gender,
                student->courseCount);

        // 课程和成绩
        for (int j = 0; j < MAX_COURSES; j++)
        {
            if (j < student->courseCount)
            {
                fprintf(file, ",%s,%.2f", student->courses[j], student->scores[j]);
            }
            else
            {
                fprintf(file, ",,"); // 空的课程和成绩
            }
        }

        // 总分和平均分
        fprintf(file, ",%.2f,%.2f\n", student->totalScore, student->averageScore);
    }

    fclose(file);
    dataModified = false;

    printSuccess("学生数据已保存到CSV文件！");
}