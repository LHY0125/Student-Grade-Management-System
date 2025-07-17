/**
 * @file file_utils.h
 * @brief 文件操作工具函数头文件
 * @note 包含文件和目录操作相关函数声明
 */

#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdbool.h>

// 文件操作函数

/**
 * @brief 检查文件是否存在
 * @details 使用access函数（Unix/Linux）或_access函数（Windows）检查文件是否存在且可读
 * @param filename 要检查的文件路径
 * @return 如果文件存在且可读返回true，否则返回false
 * @note 函数只检查文件是否存在，不检查文件内容
 * @warning 如果filename为NULL，返回false
 */
bool fileExists(const char* filename);

/**
 * @brief 创建目录
 * @details 使用mkdir函数创建指定路径的目录
 *          在Windows下使用_mkdir，在Unix/Linux下使用mkdir
 * @param path 要创建的目录路径
 * @return 如果目录创建成功或已存在返回true，否则返回false
 * @note 如果目录已存在，函数返回true
 * @note 函数不会递归创建父目录
 * @warning 如果path为NULL，返回false
 */
bool createDirectory(const char* path);

#endif // FILE_UTILS_H