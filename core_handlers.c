/**
 * @file core_handlers.c
 * @brief 核心处理函数实现文件
 * @note 实现主要的功能处理函数
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "core_handlers.h"
#include "config.h"
#include "globals.h"
#include "main_menu.h"
#include "user_manage.h"
#include "student_io.h"
#include "student_crud.h"
#include "student_search.h"
#include "student_sort.h"
#include "statistical_analysis.h"
#include "io_utils.h"

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
void handleBasicFunctions()
{
    int choice;
    do
    {
        clearScreen();
        displayBasicFunctionsMenu();
        choice = safeInputInt("请选择功能", BASIC_BACK, BASIC_SORT_STUDENTS);

        switch (choice)
        {
        case BASIC_ADD_STUDENT:
            addStudent();
            break;
        case BASIC_DELETE_STUDENT:
            deleteStudent();
            break;
        case BASIC_MODIFY_STUDENT:
            modifyStudent();
            break;
        case BASIC_SEARCH_BY_ID:
            searchStudentByID();
            break;
        case BASIC_SEARCH_BY_NAME:
            searchStudentByName();
            break;
        case BASIC_DISPLAY_ALL:
            displayAllStudents();
            break;
        case BASIC_SORT_STUDENTS:
            handleSortStudents();
            break;
        case BASIC_BACK:
            break;
        default:
            printError("无效的选择！");
            pauseSystem();
            break;
        }
    } while (choice != BASIC_BACK);
}

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
void handleStatistics()
{
    int choice;
    do
    {
        clearScreen();
        displayStatisticsMenu();
        choice = safeInputInt("请选择功能", STATS_BACK, STATS_OVERALL_ANALYSIS);

        switch (choice)
        {
        case STATS_COURSE_ANALYSIS:
            displayCourseStatistics();
            break;
        case STATS_SCORE_DISTRIBUTION:
            displayScoreDistribution();
            break;
        case STATS_SCORE_RANGES:
            displayStudentRanking();
            break;
        case STATS_OVERALL_ANALYSIS:
            displayOverallStatistics();
            break;
        case STATS_BACK:
            break;
        default:
            printError("无效的选择！");
            pauseSystem();
            break;
        }
    } while (choice != STATS_BACK);
}

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
void handleAdminFunctions()
{
    int choice;
    do
    {
        clearScreen();
        displayAdminMenu();
        choice = safeInputInt("请选择功能", ADMIN_BACK, ADMIN_VIEW_USERS);

        switch (choice)
        {
        case ADMIN_ADD_USER:
            addUserAccount();
            break;
        case ADMIN_DELETE_USER:
            deleteUserAccount();
            break;
        case ADMIN_MODIFY_PASSWORD:
            modifyUserPassword();
            break;
        case ADMIN_VIEW_USERS:
            viewAllUsers();
            break;
        case ADMIN_BACK:
            break;
        default:
            printError("无效的选择！");
            pauseSystem();
            break;
        }
    } while (choice != ADMIN_BACK);
}

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
void handleSortStudents()
{
    clearScreen();
    printHeader("学生排序");

    printf("排序依据：\n");
    printf("1. 按学号排序\n");
    printf("2. 按姓名排序\n");
    printf("3. 按总分排序\n");
    printf("4. 按平均分排序\n");

    int criteria = safeInputInt("请选择排序依据", SORT_BY_ID, SORT_BY_AVERAGE_SCORE);

    printf("\n排序顺序：\n");
    printf("1. 升序\n");
    printf("2. 降序\n");

    int order = safeInputInt("请选择排序顺序", SORT_ASCENDING, SORT_DESCENDING);

    sortStudents(criteria, order);

    printf("\n排序完成！\n");
    displayAllStudents();
}