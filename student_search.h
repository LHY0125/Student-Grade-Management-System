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
 *          找到后显示该学生的详细信息
 * @note 查找方式：精确匹配学号
 * @warning 如果没有学生数据或未找到匹配学生，将显示相应提示信息
 */
void searchStudentByID();

/**
 * @brief 按姓名查找学生
 * @details 根据用户输入的姓名进行模糊查找学生信息
 *          支持部分姓名匹配，显示所有匹配的学生详细信息
 * @note 查找方式：模糊匹配（包含子字符串）
 * @note 如果找到多个匹配学生，将全部显示
 * @warning 如果没有学生数据或未找到匹配学生，将显示相应提示信息
 */
void searchStudentByName();

/**
 * @brief 显示所有学生信息
 * @details 以表格形式显示系统中所有学生的基本信息
 *          包括学号、姓名、年龄、性别、总分和平均分
 * @note 显示格式：表格形式，便于查看和比较
 * @note 显示内容：学号、姓名、年龄、性别、总分、平均分
 * @note 同时显示总学生数统计
 * @warning 如果没有学生数据，将显示警告信息
 */
void displayAllStudents();

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
void displayStudentInfo(const Student *student);

#endif // STUDENT_SEARCH_H