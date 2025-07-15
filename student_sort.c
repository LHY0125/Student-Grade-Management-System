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
 * @brief 排序学生信息
 * @details 根据指定的排序依据和顺序对学生数组进行排序
 *          使用冒泡排序算法实现
 * @param criteria 排序依据（SORT_BY_ID, SORT_BY_NAME, SORT_BY_TOTAL_SCORE, SORT_BY_AVERAGE_SCORE）
 * @param order 排序顺序（SORT_ASCENDING升序, SORT_DESCENDING降序）
 * @note 排序依据选项：
 *       - SORT_BY_ID: 按学号排序
 *       - SORT_BY_NAME: 按姓名排序
 *       - SORT_BY_TOTAL_SCORE: 按总分排序
 *       - SORT_BY_AVERAGE_SCORE: 按平均分排序
 * @note 排序算法：冒泡排序（适合小规模数据）
 * @note 排序完成后会设置dataModified标志
 */
void sortStudents(int criteria, int order)
{
    if (studentCount <= 1)
        return;

    // 使用冒泡排序
    for (int i = 0; i < studentCount - 1; i++)
    {
        for (int j = 0; j < studentCount - 1 - i; j++)
        {
            bool shouldSwap = false;

            switch (criteria)
            {
            case SORT_BY_ID:
                shouldSwap = (order == SORT_ASCENDING) ? strcmp(students[j].studentID, students[j + 1].studentID) > 0 : strcmp(students[j].studentID, students[j + 1].studentID) < 0;
                break;
            case SORT_BY_NAME:
                shouldSwap = (order == SORT_ASCENDING) ? strcmp(students[j].name, students[j + 1].name) > 0 : strcmp(students[j].name, students[j + 1].name) < 0;
                break;
            case SORT_BY_TOTAL_SCORE:
                shouldSwap = (order == SORT_ASCENDING) ? students[j].totalScore > students[j + 1].totalScore : students[j].totalScore < students[j + 1].totalScore;
                break;
            case SORT_BY_AVERAGE_SCORE:
                shouldSwap = (order == SORT_ASCENDING) ? students[j].averageScore > students[j + 1].averageScore : students[j].averageScore < students[j + 1].averageScore;
                break;
            }

            if (shouldSwap)
            {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    dataModified = true;
}