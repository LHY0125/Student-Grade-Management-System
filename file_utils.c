/**
 * @file file_utils.c
 * @brief 文件操作工具函数实现文件
 * @note 实现文件和目录操作相关函数
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#ifdef _WIN32
#include <direct.h>
#include <io.h>
#else
#include <unistd.h>
#endif

#include "file_utils.h"

/**
 * @brief 检查文件是否存在
 * @details 使用access函数（Unix/Linux）或_access函数（Windows）检查文件是否存在且可读
 * @param filename 要检查的文件路径
 * @return 如果文件存在且可读返回true，否则返回false
 * @note 函数只检查文件是否存在，不检查文件内容
 * @warning 如果filename为NULL，返回false
 */
bool fileExists(const char *filename)
{
    if (filename == NULL)
        return false;

#ifdef _WIN32
    return _access(filename, 0) == 0;
#else
    return access(filename, F_OK) == 0;
#endif
}

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
bool createDirectory(const char *path)
{
    if (path == NULL)
        return false;

    // 检查目录是否已存在
    struct stat st = {0};
    if (stat(path, &st) == 0)
    {
        return true; // 目录已存在
    }

    // 创建目录
#ifdef _WIN32
    return _mkdir(path) == 0;
#else
    return mkdir(path, 0755) == 0;
#endif
}