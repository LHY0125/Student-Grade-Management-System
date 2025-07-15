/**
 * @file system_utils.h
 * @brief 系统工具函数头文件
 * @note 包含系统初始化和清理相关函数声明
 */

#ifndef SYSTEM_UTILS_H
#define SYSTEM_UTILS_H

#include <stdbool.h>

// 系统初始化和清理函数
bool initializeSystem();                  // 初始化系统
bool createDataDirectories();             // 创建数据目录
void cleanupSystem();                     // 清理系统资源

#endif // SYSTEM_UTILS_H