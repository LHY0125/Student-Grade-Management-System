/**
 * @file main_menu.c
 * @brief 主菜单实现文件
 * @note 实现各种菜单显示功能
 */

#include <stdio.h>
#include "main_menu.h"
#include "config.h"
#include "io_utils.h"
#include "globals.h"

/**
 * @brief 显示主菜单
 * @details 显示学生成绩管理系统的主菜单界面，包括当前用户信息和可用功能选项
 *          根据用户权限动态显示菜单项（管理员可看到系统管理功能）
 * @note 菜单选项：
 *       1. 基本功能管理（所有用户）
 *       2. 统计分析功能（所有用户）
 *       3. 系统管理功能（仅管理员）
 *       0. 退出系统
 */
void displayMainMenu()
{
	printHeader("学生成绩管理系统 - 主菜单");
	printf("\n");
	printf("当前用户: %s %s\n", currentUser,
		   isCurrentUserAdmin ? "(管理员)" : "(普通用户)");
	printf("\n");
	printf("1. 基本功能管理\n");
	printf("2. 统计分析功能\n");
	if (isCurrentUserAdmin)
	{
		printf("3. 系统管理功能\n");
	}
	printf("0. 退出系统\n");
	printf("\n");
	printSeparator();
}

/**
 * @brief 显示基本功能菜单
 * @details 显示学生信息管理的基本功能菜单，包括增删改查和排序功能
 *          同时显示当前系统中的学生总数
 * @note 菜单功能：
 *       1. 添加学生信息
 *       2. 删除学生信息
 *       3. 修改学生信息
 *       4. 按学号查找学生
 *       5. 按姓名查找学生
 *       6. 显示所有学生
 *       7. 学生信息排序
 *       0. 返回主菜单
 */
void displayBasicFunctionsMenu()
{
	printHeader("基本功能管理");
	printf("\n");
	printf("1. 添加学生信息\n");
	printf("2. 删除学生信息\n");
	printf("3. 修改学生信息\n");
	printf("4. 按学号查找学生\n");
	printf("5. 按姓名查找学生\n");
	printf("6. 显示所有学生\n");
	printf("7. 学生信息排序\n");
	printf("0. 返回主菜单\n");
	printf("\n");
	printf("当前学生总数: %d\n", studentCount);
	printf("\n");
	printSeparator();
}

/**
 * @brief 显示统计功能菜单
 * @details 显示统计分析功能菜单，提供各种数据统计和分析选项
 *          显示当前学生总数和系统平均分（如果有学生数据）
 * @note 菜单功能：
 *       1. 课程统计分析
 *       2. 成绩分布统计
 *       3. 分数段统计
 *       4. 综合统计分析
 *       0. 返回主菜单
 */
void displayStatisticsMenu()
{
	printHeader("统计分析功能");
	printf("\n");
	printf("1. 课程统计分析\n");
	printf("2. 成绩分布统计\n");
	printf("3. 分数段统计\n");
	printf("4. 综合统计分析\n");
	printf("0. 返回主菜单\n");
	printf("\n");
	printf("当前学生总数: %d\n", studentCount);
	if (studentCount > 0)
	{
		printf("系统平均分: %.2f\n", overallAverageScore);
	}
	printf("\n");
	printSeparator();
}

/**
 * @brief 显示管理功能菜单
 * @details 显示系统管理功能菜单，仅管理员可访问
 *          提供用户账户管理功能，显示当前用户总数
 * @note 菜单功能：
 *       1. 添加用户账户
 *       2. 删除用户账户
 *       3. 修改用户密码
 *       4. 查看所有用户
 *       0. 返回主菜单
 * @warning 此菜单仅限管理员用户访问
 */
void displayAdminMenu()
{
	printHeader("系统管理功能");
	printf("\n");
	printf("1. 添加用户账户\n");
	printf("2. 删除用户账户\n");
	printf("3. 修改用户密码\n");
	printf("4. 查看所有用户\n");
	printf("0. 返回主菜单\n");
	printf("\n");
	printf("当前用户总数: %d\n", userCount);
	printf("\n");
	printSeparator();
}