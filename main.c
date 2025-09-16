/**
* @brief 主程序入口
* @brief 学生成绩管理系统主程序
* @details 学生成绩管理系统的主入口函数，负责系统初始化、用户登录验证、
*          主菜单循环处理和系统清理等核心流程
*          程序流程：设置编码 -> 系统初始化 -> 用户登录 -> 主菜单循环 -> 数据保存 -> 系统清理
* @return 程序退出状态码：0表示正常退出，-1表示异常退出
* @note 系统预设用户账户：
*       1. admin - 密码：123456（管理员权限）
*       2. teacher - 密码：password（普通用户权限）
* @note 编译运行命令：
*       gcc -std=c17 -o student_system.exe *.c -I.
        ./student_system
        或者用Makefile编译
        make run
        make clean
* @warning 登录失败超过MAX_LOGIN_ATTEMPTS次会强制退出程序
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#include <direct.h>
#else
#include <sys/stat.h>
#include <unistd.h>
#endif

#include "config.h"
#include "globals.h"
#include "main_menu.h"
#include "user_manage.h"
#include "statistical_analysis.h"
#include "io_utils.h"
#include "system_utils.h"
#include "core_handlers.h"
#include "student_io.h"

int main()
{
    // 设置控制台编码为UTF-8
#ifdef _WIN32
    system("chcp 65001 > nul"); // 设置控制台编码为UTF-8
    SetConsoleOutputCP(65001);  // 设置控制台输出编码
    SetConsoleCP(65001);        // 设置控制台输入编码
#endif

    // 初始化系统
    if (!initializeSystem())
    {
        printError("系统初始化失败！");
        return -1;
    }

    // 显示欢迎信息
    clearScreen();
    printHeader("学生成绩管理系统");
    printf("\n");
    printInfo("欢迎使用学生成绩管理系统！");
    printf("\n");
    pauseSystem();

    // 用户登录
    int loginAttempts = 0;
    while (loginAttempts < MAX_LOGIN_ATTEMPTS)
    {
        clearScreen();
        printHeader("用户登录");

        if (loginSystem())
        {
            printSuccess("登录成功！");
            printf("欢迎您，%s%s\n", currentUser,
                   isCurrentUserAdmin ? " (管理员)" : " (普通用户)");
            pauseSystem();
            break;
        }
        else
        {
            loginAttempts++;
            if (loginAttempts < MAX_LOGIN_ATTEMPTS)
            {
                printError("登录失败！请检查用户名和密码。");
                printf("剩余尝试次数：%d\n", MAX_LOGIN_ATTEMPTS - loginAttempts);
                pauseSystem();
            }
        }
    }

    // 登录失败次数过多，退出程序
    if (loginAttempts >= MAX_LOGIN_ATTEMPTS)
    {
        printError("登录失败次数过多，程序将退出！");
        cleanupSystem();
        return -1;
    }

    // 主程序循环
    int choice;
    do
    {
        clearScreen();
        displayMainMenu();
        choice = safeInputInt("请选择功能", MENU_EXIT, MENU_ADMIN);

        switch (choice)
        {
        case MENU_BASIC_FUNCTIONS:
            handleBasicFunctions();
            break;
        case MENU_STATISTICS:
            handleStatistics();
            break;
        case MENU_ADMIN:
            if (isCurrentUserAdmin)
            {
                handleAdminFunctions();
            }
            else
            {
                printError("您没有管理员权限！");
                pauseSystem();
            }
            break;
        case MENU_EXIT:
            // 保存数据并退出
            if (dataModified)
            {
                printInfo("正在保存数据...");
                saveStudentsToFile();
                saveUsersToFile();
                printSuccess("数据保存完成！");
            }
            printInfo("感谢使用学生成绩管理系统！");
            break;
        default:
            printError("无效的选择！");
            pauseSystem();
            break;
        }
    } while (choice != MENU_EXIT);

    // 清理系统资源
    cleanupSystem();
    
    return 0;
}