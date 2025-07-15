/**
 * @file student_io.h
 * @brief 学生数据文件输入输出操作头文件
 * @note 声明学生数据的文件读写、CSV解析等功能
 */

#ifndef STUDENT_IO_H
#define STUDENT_IO_H

#include "config.h"

/**
 * @brief 从CSV文件加载学生数据
 * @details 从STUDENTS_FILE指定的CSV文件中读取学生信息并加载到内存中
 */
void loadStudentsFromFile();

/**
 * @brief 将学生数据保存到CSV文件
 * @details 将内存中的所有学生数据以CSV格式保存到STUDENTS_FILE文件中
 */
void saveStudentsToFile();

#endif // STUDENT_IO_H