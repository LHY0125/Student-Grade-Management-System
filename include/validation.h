/**
 * @file validation.h
 * @brief 数据验证函数头文件
 * @note 包含学生信息各字段的验证函数声明
 */

#ifndef VALIDATION_H
#define VALIDATION_H

#include <stdbool.h>

// 数据验证函数

/**
 * @brief 验证成绩是否有效
 * @details 检查成绩是否在有效范围内（0-100分）
 * @param score 要验证的成绩值
 * @return 如果成绩有效返回true，否则返回false
 * @note 有效成绩范围为0.0到100.0（包含边界值）
 */
bool isValidScore(float score);

/**
 * @brief 验证学号是否有效
 * @details 检查学号格式是否符合要求：非空且长度在合理范围内
 * @param id 要验证的学号字符串
 * @return 如果学号有效返回true，否则返回false
 * @note 学号不能为空，长度必须在1到MAX_ID_LENGTH之间
 * @warning 如果id为NULL，返回false
 */
bool isValidStudentId(const char* id);

/**
 * @brief 验证姓名是否有效
 * @details 检查姓名格式是否符合要求：非空且长度在合理范围内
 * @param name 要验证的姓名字符串
 * @return 如果姓名有效返回true，否则返回false
 * @note 姓名不能为空，长度必须在1到MAX_NAME_LENGTH之间
 * @warning 如果name为NULL，返回false
 */
bool isValidName(const char* name);

/**
 * @brief 验证性别是否有效
 * @details 检查性别是否为'M'（男）或'F'（女）
 * @param gender 要验证的性别字符
 * @return 如果性别有效返回true，否则返回false
 * @note 只接受'M'或'F'两个值
 */
bool isValidGender(char gender);

/**
 * @brief 验证年龄是否有效
 * @details 检查年龄是否在合理范围内
 * @param age 要验证的年龄值
 * @return 如果年龄有效返回true，否则返回false
 * @note 有效年龄范围为MIN_AGE到MAX_AGE（包含边界值）
 */
bool isValidAge(int age);

/**
 * @brief 验证课程名称是否有效
 * @details 检查课程名称格式是否符合要求：非空且长度在合理范围内
 * @param courseName 要验证的课程名称字符串
 * @return 如果课程名称有效返回true，否则返回false
 * @note 课程名称不能为空，长度必须在1到MAX_COURSE_NAME_LENGTH之间
 * @warning 如果courseName为NULL，返回false
 */
bool isValidCourseName(const char* courseName);

/**
 * @brief 验证用户名是否有效
 * @details 检查用户名格式是否符合要求：非空、长度合理且只包含字母数字
 * @param username 要验证的用户名字符串
 * @return 如果用户名有效返回true，否则返回false
 * @note 用户名不能为空，长度必须在3到MAX_USERNAME_LENGTH之间，只能包含字母和数字
 * @warning 如果username为NULL，返回false
 */
bool isValidUsername(const char* username);

/**
 * @brief 验证密码强度是否符合要求
 * @details 检查密码是否满足最低安全要求
 * @param password 要验证的密码字符串
 * @return 如果密码有效返回true，否则返回false
 * @note 密码长度必须在6到MAX_PASSWORD_LENGTH之间
 * @warning 如果password为NULL，返回false
 */
bool isValidPassword(const char* password);

/**
 * @brief 验证数组索引是否在有效范围内
 * @details 检查索引是否在指定范围内，防止数组越界
 * @param index 要验证的索引值
 * @param maxIndex 最大有效索引值（不包含）
 * @return 如果索引有效返回true，否则返回false
 * @note 有效索引范围为0到maxIndex-1
 */
bool isValidIndex(int index, int maxIndex);

#endif // VALIDATION_H