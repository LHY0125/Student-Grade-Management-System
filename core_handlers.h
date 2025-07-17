/**
 * @file core_handlers.h
 * @brief 核心处理函数头文件
 * @note 包含主要的功能处理函数声明
 */

#ifndef CORE_HANDLERS_H
#define CORE_HANDLERS_H

#include "config.h"

// 核心处理函数声明

/**
 * @brief 处理基本功能菜单
 * @details 显示并处理学生信息管理的基本功能菜单循环
 *          提供学生信息的增删改查、排序等核心功能
 *          循环显示菜单直到用户选择返回主菜单
 * @note 包含的功能：
 *       - 添加学生信息
 *       - 删除学生信息
 *       - 修改学生信息
 *       - 按学号查找学生
 *       - 按姓名查找学生
 *       - 显示所有学生
 *       - 学生信息排序
 */
void handleBasicFunctions();

/**
 * @brief 处理统计功能菜单
 * @details 显示并处理统计分析功能菜单循环
 *          提供各种学生成绩的统计分析功能
 *          循环显示菜单直到用户选择返回主菜单
 * @note 包含的功能：
 *       - 课程统计分析
 *       - 成绩分布统计
 *       - 学生排名统计
 *       - 综合统计分析
 */
void handleStatistics();

/**
 * @brief 处理管理功能菜单
 * @details 显示并处理系统管理功能菜单循环，仅限管理员用户访问
 *          提供用户账户管理的各项功能
 *          循环显示菜单直到用户选择返回主菜单
 * @note 包含的功能：
 *       - 添加用户账户
 *       - 删除用户账户
 *       - 修改用户密码
 *       - 查看所有用户
 * @warning 此函数仅应在验证用户为管理员后调用
 */
void handleAdminFunctions();

/**
 * @brief 处理学生排序功能
 * @details 提供交互式的学生信息排序功能
 *          用户可选择排序依据（学号、姓名、总分、平均分）和排序顺序（升序、降序）
 *          排序完成后自动显示排序结果
 * @note 排序依据选项：
 *       1. 按学号排序
 *       2. 按姓名排序
 *       3. 按总分排序
 *       4. 按平均分排序
 * @note 排序顺序选项：
 *       1. 升序
 *       2. 降序
 */
void handleSortStudents();

#endif // CORE_HANDLERS_H