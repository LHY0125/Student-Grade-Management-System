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
 * @details 交互式地添加新学生信息，包括基本信息和课程成绩
 *          验证学号唯一性、姓名格式、年龄范围等
 *          自动计算总分和平均分
 * @note 会检查学生数量是否已达上限MAX_STUDENTS
 * @note 学号必须唯一，不能与现有学生重复
 * @warning 如果学生数量已满，会显示错误信息并返回
 * @see MAX_STUDENTS, isValidStudentId(), isValidName()
 */
void addStudent();

/**
 * @brief 删除学生
 * @details 提供交互式界面删除指定学号的学生信息
 *          包含确认机制，防止误删除操作
 * @note 删除流程：
 *       1. 输入要删除的学生学号
 *       2. 查找并显示学生信息
 *       3. 用户确认删除操作
 *       4. 删除学生并重新排列数组
 *       5. 更新数据修改和统计更新标志
 * @warning 删除操作不可逆，请谨慎操作
 * @warning 如果没有学生数据，将显示警告信息
 */
void deleteStudent();

/**
 * @brief 修改学生信息
 * @details 提供交互式界面修改指定学生的各项信息
 *          支持修改姓名、年龄、性别和课程成绩等信息
 * @note 修改选项：
 *       1. 修改姓名
 *       2. 修改年龄
 *       3. 修改性别
 *       4. 修改课程成绩（包括修改现有成绩、添加新课程、删除课程）
 * @note 课程成绩修改包含：
 *       - 修改现有课程成绩
 *       - 添加新课程
 *       - 删除课程
 * @warning 修改课程信息后会自动重新计算总分和平均分
 */
void modifyStudent();

#endif // STUDENT_CRUD_H