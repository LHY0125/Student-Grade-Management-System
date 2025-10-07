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
 *          解析CSV格式数据，包括学号、姓名、年龄、性别、课程信息等
 *          如果文件不存在，会初始化为空的学生列表
 * @note 会跳过CSV文件的头部行，最多加载MAX_STUDENTS个学生
 * @note 加载完成后会设置statsNeedUpdate标志为true
 * @warning 如果CSV格式不正确，可能导致数据解析错误
 * @see STUDENTS_FILE, MAX_STUDENTS, Student结构体
 */
void loadStudentsFromFile();

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
void saveStudentsToFile();

#endif // STUDENT_IO_H