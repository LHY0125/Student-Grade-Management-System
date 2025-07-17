/**
 * @file system_utils.h
 * @brief 系统工具函数头文件
 * @note 包含系统初始化和清理相关函数声明
 */

#ifndef SYSTEM_UTILS_H
#define SYSTEM_UTILS_H

#include <stdbool.h>

// 系统初始化和清理函数

/**
 * @brief 初始化系统
 * @details 执行系统启动时的初始化操作，包括创建必要的数据目录
 *          调用createDataDirectories函数创建数据存储目录
 * @return 如果初始化成功返回true，否则返回false
 * @note 此函数应在程序启动时调用
 * @note 如果初始化失败，会输出错误信息
 */
bool initializeSystem();

/**
 * @brief 创建数据目录
 * @details 创建程序运行所需的数据存储目录
 *          目前创建"data"目录用于存储学生数据文件
 * @return 如果目录创建成功或已存在返回true，否则返回false
 * @note 如果目录已存在，函数仍返回true
 * @note 可以根据需要扩展创建更多目录
 */
bool createDataDirectories();

/**
 * @brief 清理系统资源
 * @details 执行程序退出前的清理操作
 *          目前主要输出清理完成的提示信息
 * @note 此函数应在程序退出前调用
 * @note 可以根据需要添加更多清理操作，如关闭文件、释放内存等
 */
void cleanupSystem();

#endif // SYSTEM_UTILS_H