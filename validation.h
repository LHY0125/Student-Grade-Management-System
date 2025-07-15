/**
 * @file validation.h
 * @brief 数据验证函数头文件
 * @note 包含学生信息各字段的验证函数声明
 */

#ifndef VALIDATION_H
#define VALIDATION_H

#include <stdbool.h>

// 数据验证函数
bool isValidScore(float score);           // 验证成绩是否有效
bool isValidStudentId(const char* id);    // 验证学号是否有效
bool isValidName(const char* name);       // 验证姓名是否有效
bool isValidGender(char gender);          // 验证性别是否有效
bool isValidAge(int age);                 // 验证年龄是否有效

#endif // VALIDATION_H