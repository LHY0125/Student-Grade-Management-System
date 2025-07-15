/**
 * @file student_search.h
 * @brief 学生数据搜索和显示操作头文件
 * @note 声明学生数据的查找、显示等功能
 */

#ifndef STUDENT_SEARCH_H
#define STUDENT_SEARCH_H

#include "config.h"

/**
 * @brief 按学号查找学生
 * @details 根据用户输入的学号精确查找学生信息
 */
void searchStudentByID();

/**
 * @brief 按姓名查找学生
 * @details 根据用户输入的姓名进行模糊查找学生信息
 */
void searchStudentByName();

/**
 * @brief 显示所有学生信息
 * @details 以表格形式显示系统中所有学生的基本信息
 */
void displayAllStudents();

/**
 * @brief 显示单个学生详细信息
 * @param student 指向要显示信息的学生结构体的常量指针
 */
void displayStudentInfo(const Student *student);

#endif // STUDENT_SEARCH_H