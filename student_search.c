/**
 * @file student_search.c
 * @brief 学生数据搜索和显示功能实现
 * @note 负责学生信息的查找、显示等功能
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "globals.h"
#include "io_utils.h"

// 函数前向声明
void displayStudentInfo(const Student *student);

/**
 * @brief 按学号查找学生
 * @details 根据用户输入的学号精确查找学生信息
 *          找到后显示该学生的详细信息
 * @note 查找方式：精确匹配学号
 * @warning 如果没有学生数据或未找到匹配学生，将显示相应提示信息
 */
void searchStudentByID()
{
    clearScreen();
    printHeader("按学号查找学生");

    if (studentCount == 0)
    {
        printWarning("暂无学生数据！");
        pauseSystem();
        return;
    }

    char studentID[MAX_ID_LENGTH];
    printf("\n");
    safeInputString("请输入学号", studentID, MAX_ID_LENGTH);

    for (int i = 0; i < studentCount; i++)
    {
        if (strcmp(students[i].studentID, studentID) == 0)
        {
            displayStudentInfo(&students[i]);
            pauseSystem();
            return;
        }
    }

    printError("未找到该学号的学生！");
    pauseSystem();
}

/**
 * @brief 按姓名查找学生
 * @details 根据用户输入的姓名进行模糊查找学生信息
 *          支持部分姓名匹配，显示所有匹配的学生详细信息
 * @note 查找方式：模糊匹配（包含子字符串）
 * @note 如果找到多个匹配学生，将全部显示
 * @warning 如果没有学生数据或未找到匹配学生，将显示相应提示信息
 */
void searchStudentByName()
{
    clearScreen();
    printHeader("按姓名查找学生");

    if (studentCount == 0)
    {
        printWarning("暂无学生数据！");
        pauseSystem();
        return;
    }

    char name[MAX_NAME_LENGTH];
    printf("\n");
    safeInputString("请输入姓名（支持模糊查找）", name, MAX_NAME_LENGTH);

    bool found = false;
    for (int i = 0; i < studentCount; i++)
    {
        if (strstr(students[i].name, name) != NULL)
        {
            if (!found)
            {
                printf("\n找到以下匹配的学生：\n");
                printSeparator();
                found = true;
            }
            displayStudentInfo(&students[i]);
            printf("\n");
        }
    }

    if (!found)
    {
        printError("未找到匹配的学生！");
    }

    pauseSystem();
}

/**
 * @brief 显示所有学生信息
 * @details 以表格形式显示系统中所有学生的基本信息
 *          包括学号、姓名、年龄、性别、总分和平均分
 * @note 显示格式：表格形式，便于查看和比较
 * @note 显示内容：学号、姓名、年龄、性别、总分、平均分
 * @note 同时显示总学生数统计
 * @warning 如果没有学生数据，将显示警告信息
 */
void displayAllStudents()
{
    clearScreen();
    printHeader("所有学生信息");

    if (studentCount == 0)
    {
        printWarning("暂无学生数据！");
        pauseSystem();
        return;
    }

    printf("\n");
    // 调整中文表头的对齐格式，考虑中文字符的显示宽度
    printf("%-12s %-10s %-6s %-6s %-10s %-8s\n",
           "学号", "姓名", "年龄", "性别", "总分", "平均分");
    printf("==========================================\n");

    for (int i = 0; i < studentCount; i++)
    {
        printf("%-10s %-10s %-4d %-4c %-8.2f %-8.2f\n",
               students[i].studentID,
               students[i].name,
               students[i].age,
               students[i].gender,
               students[i].totalScore,
               students[i].averageScore);
    }

    printf("\n总学生数: %d\n", studentCount);
    pauseSystem();
}

/**
 * @brief 显示单个学生详细信息
 * @details 显示指定学生的完整详细信息，包括基本信息和所有课程成绩
 * @param student 指向要显示信息的学生结构体的常量指针
 * @note 显示内容：
 *       - 基本信息：学号、姓名、年龄、性别、课程数量
 *       - 课程成绩：每门课程的名称和分数
 *       - 统计信息：总分和平均分
 * @warning 传入的student指针不能为NULL
 */
void displayStudentInfo(const Student *student)
{
    printf("\n学生详细信息：\n");
    printSeparator();
    printf("学号: %s\n", student->studentID);
    printf("姓名: %s\n", student->name);
    printf("年龄: %d\n", student->age);
    printf("性别: %c\n", student->gender);
    printf("课程数量: %d\n", student->courseCount);

    if (student->courseCount > 0)
    {
        printf("\n课程成绩：\n");
        for (int i = 0; i < student->courseCount; i++)
        {
            printf("  %s: %.2f分\n",
                   student->courses[i],
                   student->scores[i]);
        }
        printf("\n总分: %.2f\n", student->totalScore);
        printf("平均分: %.2f\n", student->averageScore);
    }
}