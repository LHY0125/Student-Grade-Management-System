/**
 * @file student_sort.h
 * @brief 学生数据排序操作头文件
 * @note 声明学生数据的排序功能
 */

#ifndef STUDENT_SORT_H
#define STUDENT_SORT_H

#include "config.h"

/**
 * @brief 排序学生信息
 * @details 根据指定的排序依据和顺序对学生数组进行排序
 * @param criteria 排序依据（SORT_BY_ID, SORT_BY_NAME, SORT_BY_TOTAL_SCORE, SORT_BY_AVERAGE_SCORE）
 * @param order 排序顺序（SORT_ASCENDING升序, SORT_DESCENDING降序）
 */
void sortStudents(int criteria, int order);

#endif // STUDENT_SORT_H