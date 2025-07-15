/**
 * @file student_crud.h
 * @brief 学生数据增删改操作头文件
 * @note 声明学生数据的创建、删除、修改等CRUD功能
 */

#ifndef STUDENT_CRUD_H
#define STUDENT_CRUD_H

#include "config.h"

/**
 * @brief 添加新学生
 * @details 交互式添加新学生信息，包括基本信息和课程成绩
 */
void addStudent();

/**
 * @brief 删除学生
 * @details 根据学号删除指定学生的所有信息
 */
void deleteStudent();

/**
 * @brief 修改学生信息
 * @details 交互式修改学生的基本信息和课程成绩
 */
void modifyStudent();

#endif // STUDENT_CRUD_H