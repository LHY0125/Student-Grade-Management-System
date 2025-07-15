/**
 * @file file_utils.h
 * @brief 文件操作工具函数头文件
 * @note 包含文件和目录操作相关函数声明
 */

#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdbool.h>

// 文件操作函数
bool fileExists(const char* filename);    // 检查文件是否存在
bool createDirectory(const char* path);   // 创建目录

#endif // FILE_UTILS_H