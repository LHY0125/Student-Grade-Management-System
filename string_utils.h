/**
 * @file string_utils.h
 * @brief 字符串处理工具函数头文件
 * @note 包含字符串操作相关函数声明
 */

#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <stdbool.h>

// 字符串处理函数
void trimString(char* str);               // 去除字符串首尾空白字符
bool isEmptyString(const char* str);      // 检查字符串是否为空

#endif // STRING_UTILS_H