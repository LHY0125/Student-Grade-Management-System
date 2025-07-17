/**
 * @file system_utils.c
 * @brief 系统工具函数实现文件
 * @note 实现系统初始化和清理相关函数
 */

#include <stdio.h>
#include <stdlib.h>
#include "system_utils.h"
#include "file_utils.h"
#include "io_utils.h"
#include "config.h"
#include "user_manage.h"
#include "student_io.h"
#include "statistical_analysis.h"

/**
 * @brief 初始化系统
 * @details 执行系统启动时的初始化操作，包括创建必要的数据目录
 *          调用createDataDirectories函数创建数据存储目录
 * @return 如果初始化成功返回true，否则返回false
 * @note 此函数应在程序启动时调用
 * @note 如果初始化失败，会输出错误信息
 */
bool initializeSystem()
{
    printInfo("正在初始化系统...");

    if (!createDataDirectories())
    {
        printError("系统初始化失败：无法创建数据目录");
        return false;
    }

    // 加载用户数据
    loadUsersFromFile();
    
    // 加载学生数据
    loadStudentsFromFile();
    
    // 初始化统计缓存
    initStatisticsCache();

    printSuccess("系统初始化完成");
    return true;
}

/**
 * @brief 创建数据目录
 * @details 创建程序运行所需的数据存储目录
 *          目前创建"data"目录用于存储学生数据文件
 * @return 如果目录创建成功或已存在返回true，否则返回false
 * @note 如果目录已存在，函数仍返回true
 * @note 可以根据需要扩展创建更多目录
 */
bool createDataDirectories()
{
    // 创建data目录
    if (!createDirectory("data"))
    {
        printError("无法创建data目录");
        return false;
    }

    return true;
}

/**
 * @brief 清理系统资源
 * @details 执行程序退出前的清理操作
 *          目前主要输出清理完成的提示信息
 * @note 此函数应在程序退出前调用
 * @note 可以根据需要添加更多清理操作，如关闭文件、释放内存等
 */
void cleanupSystem()
{
    printInfo("正在清理系统资源...");
    // 这里可以添加其他清理操作
    printSuccess("系统清理完成");
}