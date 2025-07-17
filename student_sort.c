/**
 * @file student_sort.c
 * @brief 学生数据排序功能实现
 * @note 负责学生信息的排序操作
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "globals.h"

/**
 * @brief 比较函数 - 按学号排序
 * @param a 指向第一个学生的指针
 * @param b 指向第二个学生的指针
 * @return 比较结果：负数表示a<b，0表示a=b，正数表示a>b
 */
static int compareByID(const void *a, const void *b)
{
    const Student *studentA = (const Student *)a;
    const Student *studentB = (const Student *)b;
    int result = strcmp(studentA->studentID, studentB->studentID);
    return (currentSortOrder == SORT_ASCENDING) ? result : -result;
}

/**
 * @brief 比较函数 - 按姓名排序
 * @param a 指向第一个学生的指针
 * @param b 指向第二个学生的指针
 * @return 比较结果：负数表示a<b，0表示a=b，正数表示a>b
 */
static int compareByName(const void *a, const void *b)
{
    const Student *studentA = (const Student *)a;
    const Student *studentB = (const Student *)b;
    int result = strcmp(studentA->name, studentB->name);
    return (currentSortOrder == SORT_ASCENDING) ? result : -result;
}

/**
 * @brief 比较函数 - 按总分排序
 * @param a 指向第一个学生的指针
 * @param b 指向第二个学生的指针
 * @return 比较结果：负数表示a<b，0表示a=b，正数表示a>b
 */
static int compareByTotalScore(const void *a, const void *b)
{
    const Student *studentA = (const Student *)a;
    const Student *studentB = (const Student *)b;
    if (studentA->totalScore < studentB->totalScore)
        return (currentSortOrder == SORT_ASCENDING) ? -1 : 1;
    else if (studentA->totalScore > studentB->totalScore)
        return (currentSortOrder == SORT_ASCENDING) ? 1 : -1;
    else
        return 0;
}

/**
 * @brief 比较函数 - 按平均分排序
 * @param a 指向第一个学生的指针
 * @param b 指向第二个学生的指针
 * @return 比较结果：负数表示a<b，0表示a=b，正数表示a>b
 */
static int compareByAverageScore(const void *a, const void *b)
{
    const Student *studentA = (const Student *)a;
    const Student *studentB = (const Student *)b;
    if (studentA->averageScore < studentB->averageScore)
        return (currentSortOrder == SORT_ASCENDING) ? -1 : 1;
    else if (studentA->averageScore > studentB->averageScore)
        return (currentSortOrder == SORT_ASCENDING) ? 1 : -1;
    else
        return 0;
}

/**
 * @brief 排序学生信息
 * @details 根据指定的排序依据和顺序对学生数组进行排序
 *          使用qsort标准库函数实现，时间复杂度O(n log n)
 * @param criteria 排序依据（SORT_BY_ID, SORT_BY_NAME, SORT_BY_TOTAL_SCORE, SORT_BY_AVERAGE_SCORE）
 * @param order 排序顺序（SORT_ASCENDING升序, SORT_DESCENDING降序）
 * @note 排序依据选项：
 *       - SORT_BY_ID: 按学号排序
 *       - SORT_BY_NAME: 按姓名排序
 *       - SORT_BY_TOTAL_SCORE: 按总分排序
 *       - SORT_BY_AVERAGE_SCORE: 按平均分排序
 * @note 排序算法：快速排序（qsort标准库函数，时间复杂度O(n log n)）
 * @note 排序完成后会设置dataModified标志
 */
void sortStudents(int criteria, int order)
{
    if (studentCount <= 1)
        return;

    // 设置全局排序参数
    currentSortCriteria = criteria;
    currentSortOrder = order;

    // 选择对应的比较函数并使用qsort进行排序
    switch (criteria)
    {
    case SORT_BY_ID:
        qsort(students, studentCount, sizeof(Student), compareByID);
        break;
    case SORT_BY_NAME:
        qsort(students, studentCount, sizeof(Student), compareByName);
        break;
    case SORT_BY_TOTAL_SCORE:
        qsort(students, studentCount, sizeof(Student), compareByTotalScore);
        break;
    case SORT_BY_AVERAGE_SCORE:
        qsort(students, studentCount, sizeof(Student), compareByAverageScore);
        break;
    default:
        return; // 无效的排序依据
    }

    dataModified = true;
}